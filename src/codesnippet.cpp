#include "codesnippet.h"

#include "qeditor.h"
#include "qdocumentcursor.h"
#include "qdocumentline.h"
#include "filechooser.h"
#include "latexdocument.h"
#include "smallUsefulFunctions.h"

#include <algorithm>

int CodeSnippetPlaceHolder::offsetEnd() const
{
	return offset + length;
}

inline void translatePlaceholder(const QString &content, QString &curLine, CodeSnippetPlaceHolder &ph, int columnshift = 0)
{
	bool translatable = (ph.flags & CodeSnippetPlaceHolder::Translatable) && !CodeSnippet::debugDisableAutoTranslate;
	if (translatable)
		for (int i = 0; i < content.length(); i++)
			if (!content[i].toLatin1()) { //don't translate non ascii placeholders
				translatable = false;
				break;
			}
	QString trans = !translatable ? content : QApplication::translate("CodeSnippet_PlaceHolder", content.toLatin1().constData());
	if (columnshift < 0) {
		curLine = curLine.left(curLine.length() + columnshift) + trans + curLine.right(-columnshift);
		ph.offset += columnshift;
		//todo: allow positive shift
	} else curLine += trans;
	ph.length = trans.length();
}

void parseSnippetPlaceHolder(const QString &snippet, int &i, QString &curLine, CodeSnippetPlaceHolder &ph)
{
	if (i >= snippet.length())
		return; // avoid possible crash
	QString tmpPlaceHolderContent;
	ph.offset = curLine.length();
	ph.length = 0;
	ph.id = -1;
	ph.flags = 0;
	for (; i < snippet.length(); i++) {
		if (snippet.at(i) == '%' && i + 1 < snippet.length()) {
			i++;
			switch (snippet.at(i).toLatin1()) {
			case'|':
				ph.flags |= CodeSnippetPlaceHolder::AutoSelect;
				break;
			case '>':
				translatePlaceholder(tmpPlaceHolderContent, curLine, ph);
				return;
			case '%':
				tmpPlaceHolderContent += '%';
				ph.length++;
				break;
			case ':':
				goto secondLevelBreak;
			default:
				tmpPlaceHolderContent += "%";
				tmpPlaceHolderContent += snippet.at(i);
				ph.length++;
			}
		} else tmpPlaceHolderContent += snippet.at(i);
	}


secondLevelBreak:
    int snippetEnd=-1;
	if (i >= snippet.length()) return;
	if ((snippet.at(i) != ':') || ((snippetEnd = snippet.indexOf("%>", i)) == -1)) return;

	QString options = snippet.mid(i + 1, snippetEnd - i - 1);
	i = snippetEnd + 1;
	int columnshift = 0;
	foreach (const QString &s, options.split(",")) {
		QString t = s.trimmed();
		if (t == "mirror") ph.flags |= CodeSnippetPlaceHolder::Mirror;
		else if (t == "multiline") ph.flags |= CodeSnippetPlaceHolder::PreferredMultilineAutoSelect;
		else if (t.startsWith("id:")) ph.id = t.remove(0, 3).toInt();
		else if (t.startsWith("columnShift:", Qt::CaseInsensitive)) columnshift = t.remove(0, 12).toInt();
		else if (t.startsWith("select")) ph.flags |= CodeSnippetPlaceHolder::AutoSelect;
		else if (t == "persistent") ph.flags |= CodeSnippetPlaceHolder::Persistent;
		else if (t == "translatable") ph.flags |= CodeSnippetPlaceHolder::Translatable;
	}

	translatePlaceholder(tmpPlaceHolderContent, curLine, ph, columnshift);
}

bool CodeSnippet::autoReplaceCommands = true;
bool CodeSnippet::debugDisableAutoTranslate = false;

CodeSnippet::CodeSnippet(const QString &newWord, bool replacePercentNewline)
{
	QString realNewWord = expandCode(newWord);
	cursorLine = -1;
	cursorOffset = -1;
	anchorOffset = -1;
	usageCount = 0;
	index = 0;
	snippetLength = 0;
	type = none;
	QString curLine;

	curLine.reserve(realNewWord.length());
	word.reserve(realNewWord.length());
	bool escape = false;
	bool hasPlaceHolder = false, hasMirrors = false, hasAutoSelectPlaceHolder = false;
	placeHolders.append(QList<CodeSnippetPlaceHolder>()); //during the creation this contains a line more than lines

	CodeSnippetPlaceHolder tempPlaceholder;
	bool firstLine = true;
	for (int i = 0; i < realNewWord.length(); i++) {
		QChar currentChar = realNewWord.at(i);
		if (!escape) {
			if (currentChar == QChar('\n')) {
				lines.append(curLine);
				placeHolders.append(QList<CodeSnippetPlaceHolder>());
				curLine.clear();
				firstLine = false;
			} else if (currentChar == QChar('%')) escape = true;
			else {
				curLine += currentChar;
				word.append(currentChar);
				if (firstLine) {
					switch (currentChar.toLatin1()) {
					case '{':
					case '}':
						sortWord.append('!');
						break;
					case '[':
						sortWord.append('"');
						break;
					case '*':
						sortWord.append('#');
						break;
					default:
						sortWord.append(currentChar);
					}
				}
			}
		} else {
			escape = false;
			switch (currentChar.toLatin1()) {
			case '%':
				word += '%';
				curLine += '%';
				if (firstLine)
					sortWord.append(currentChar);
				break;
			case '|':
				cursorLine = lines.count(); //first line is 0
				anchorOffset = cursorOffset;
				cursorOffset = curLine.length();
				break;
			case '<':
				i++;
				parseSnippetPlaceHolder(realNewWord, i, curLine, tempPlaceholder);
				hasPlaceHolder = true;
				if (tempPlaceholder.flags & CodeSnippetPlaceHolder::AutoSelect) hasAutoSelectPlaceHolder = true;
				if (tempPlaceholder.flags & CodeSnippetPlaceHolder::Mirror) hasMirrors = true;
				placeHolders.last().append(tempPlaceholder);
				//	foundDescription = true;
				break;
			case '\n':
				curLine += "%";
				word += "%";
			// no break
                [[clang::fallthrough]];
			case '\\':
				if (currentChar.toLatin1() == '\n' || replacePercentNewline) {
					lines.append(curLine);
					placeHolders.append(QList<CodeSnippetPlaceHolder>());
					curLine.clear();
					firstLine = false;
					//curLine+="\n";
					break;
				}
                [[clang::fallthrough]];
			default: // escape was not an escape character ...
				curLine += '%';
				curLine += currentChar;
				word.append('%');
				word.append(currentChar);
				if (firstLine)
					sortWord.append(currentChar);
			}
		}
	}
	lines.append(curLine);
	if (cursorLine == -1 && hasPlaceHolder && !hasAutoSelectPlaceHolder) //use first placeholder at new selection if nothing else is set
		for (int i = 0; i < placeHolders.count(); i++)
			if (placeHolders[i].count() > 0)
				placeHolders[i].first().flags |= CodeSnippetPlaceHolder::AutoSelect;

	if (hasMirrors) {
		for (int l = 0; l < placeHolders.count(); l++)
			for (int i = 0; i < placeHolders[l].size(); i++)
				if (placeHolders[l][i].flags & CodeSnippetPlaceHolder::Mirror) {
					for (int lm = 0; lm < placeHolders.count(); lm++)
						for (int im = 0; im < placeHolders[lm].size(); im++)
							if ((placeHolders[l][i].id == placeHolders[lm][im].id) &&
							        !(placeHolders[lm][im].flags & CodeSnippetPlaceHolder::Mirrored)) {
								placeHolders[lm][im].flags |= CodeSnippetPlaceHolder::Mirrored;
								goto secondLevelBreak;
							}
secondLevelBreak:
					;
				}
	}
	if (anchorOffset == -1) anchorOffset = cursorOffset;
	/*
	sortWord=lines.first().toLower(); //only sort by first line which is visible in completer (otherwise \begin{frame} comes after \begin{frame}[xy])
	sortWord.replace("{","!");//js: still using dirty hack, however order should be ' '{[* abcde...
	sortWord.replace("}","!");// needs to be replaced as well for sorting \bgein{abc*} after \bgein{abc}
	sortWord.replace("[","\"");//(first is a space->) !"# follow directly in the ascii table
	sortWord.replace("*","#");
	*/
}

bool CodeSnippet::operator< (const CodeSnippet &cw) const
{
	return cw.sortWord > sortWord;
}

bool CodeSnippet::operator== (const CodeSnippet &cw) const
{
	return cw.word == word;
}

/*!
 * expands special snipets such as environment templates
 */
QString CodeSnippet::expandCode(const QString &code)
{
	if (code == "%<%:TEXMAKERX-GENERIC-ENVIRONMENT-TEMPLATE%>" ||
	        code == "%<%:TEXSTUDIO-GENERIC-ENVIRONMENT-TEMPLATE%>") {
		// environment template
		return "\\begin{%<" + QObject::tr("*environment-name*") + "%:select,id:2%>}\n"
		       "%<" + QObject::tr("content...") + "%:select,multiline%>\n"
		       "\\end{%<" + QObject::tr("*environment-name*") + "%:mirror,id:2%>}";
	} else if (code.startsWith("\\begin{") &&
	           !code.contains("\n") && !code.contains("%\\") &&  // only a single line
	           code.lastIndexOf("\\") == 0) {                   // only one latex command in the line
		// plain \begin{env}
		int p = code.indexOf("{") + 1;
		QString environmentName = code.mid(p, code.indexOf("}") - p); //contains the {}
		return code + "\n" + environmentContent(environmentName) + "\n\\end{" + environmentName + "}";
	}
	return code;

}

/*!
 * returns the content to be inserted into an environment upon environment snippet expansion
 * This is currently hard coded for the most common cases. Might become user-definable in the future
 * (via addition to the snippet code (what would that imply for cwls?) or other means
 */
QString CodeSnippet::environmentContent(const QString &envName)
{
	if (envName == "enumerate" || envName == "itemize") {
		return "\\item %|";
	} else if (envName == "description") {
		return "\\item[%<" + QObject::tr("label") + "%:multiline%>] %<" + QObject::tr("description") + "%>";
	} else {
		return "%<" + QObject::tr("content...") + "%:multiline%>";
	}
}

void CodeSnippet::insert(QEditor *editor) const
{
	if (!editor) return;
	QDocumentCursor c = editor->cursor();
	insertAt(editor, &c);
}

void CodeSnippet::insertAt(QEditor *editor, QDocumentCursor *cursor, PlaceholderMode placeholderMode, bool byCompleter, bool isKeyVal) const
{
	if (lines.empty() || !editor || !cursor) return;

	int phrmCursorLine = -1;
	int phrmCursorOffset = -1;
	int phrmCursorLineRemovedChars = 0;

	QString line;
	// construct text
	if (placeholderMode == PlaceholdersRemoved) {
		for (int l = 0; l < lines.count(); l++) {
			QString ln = lines[l];
			for (int i = placeHolders[l].count() - 1; i >= 0; i--) {
				ln.remove(placeHolders[l][i].offset, placeHolders[l][i].length);
			}
			line.append(ln);
			if (l < lines.count() - 1)
				line.append("\n");

			if (phrmCursorOffset == -1 && placeHolders[l].count() >> 0) {
				// set cursor in place of first placeholder
				phrmCursorLine = l;
				phrmCursorLineRemovedChars = lines[l].length() - ln.length();
				phrmCursorOffset = placeHolders[l][0].offset;
			}
		}
	} else {
		line = lines.join("\n");
	}

	//find filechooser escape %(   %)
	QRegExp rx("%\\((.+)%\\)");
	int pos = rx.indexIn(line, 0);
	if (pos > -1) {
        FileChooser sfDlg(nullptr, QApplication::tr("Select a File"));
		sfDlg.setFilter(rx.cap(1));
		LatexDocument *doc = qobject_cast<LatexDocument *>(cursor->document());
		QString path = doc->parent->getCompileFileName();
		path = getPathfromFilename(path);
		QString directory;
		if (path.isEmpty()) directory = QDir::homePath();
		else directory = path;
		sfDlg.setDir(directory);
		if (sfDlg.exec()) {
			QString fn = sfDlg.fileName();
			if (!path.isEmpty())
				fn = getRelativeBaseNameToPath(fn, path);
			line.replace(rx, fn);
		} else return;
	}

	QString savedSelection;
	bool alwaysSelect = false;
	bool editBlockOpened = false;
	if (cursor->hasSelection()) {
		savedSelection = cursor->selectedText();
		editBlockOpened = true;
		cursor->beginEditBlock();
		// TODO: This is a workaround. clearLanguageMatches() does not work properly
		// after removeSelectedText() See https://sourceforge.net/p/texstudio/bugs/708/
		// reason: MatchLists in QDocumentPrivate.m_matches are not updated during
		// removeSelectedText()
		editor->document()->clearLanguageMatches();
		cursor->removeSelectedText();
	} else if (!editor->cutBuffer.isEmpty()) {
		savedSelection = editor->cutBuffer;
		editor->cutBuffer.clear();
		alwaysSelect = true;
	}
	bool multiLineSavedSelection = savedSelection.contains("\n");
	QDocumentCursor selector = *cursor;
	QDocumentLine curLine = cursor->line();

	// on multi line commands, replace environments only
	if (autoReplaceCommands && byCompleter && lines.size() > 1 && line.contains("\\begin{")) {
		QString curLine = cursor->line().text();
		int wordBreak = curLine.indexOf(QRegExp("\\W"), cursor->columnNumber());
		int closeCurl = curLine.indexOf("}", cursor->columnNumber());
		int openCurl = curLine.indexOf("{", cursor->columnNumber());
		int openBracket = curLine.indexOf("[", cursor->columnNumber());
		if (closeCurl > 0) {
			if (openBracket < 0) openBracket = 1e9;
			if (openCurl < 0) openCurl = 1e9;
			if (wordBreak < 0) wordBreak = 1e9;
			if (closeCurl < openBracket && (closeCurl <= wordBreak || openCurl <= wordBreak)) {
				QString oldEnv;
				if (closeCurl < openCurl)
					oldEnv = curLine.mid(cursor->columnNumber(), closeCurl - cursor->columnNumber());
				else
					oldEnv = curLine.mid(openCurl + 1, closeCurl - openCurl - 1);
				QRegExp rx("\\\\begin\\{(.+)\\}");
				rx.setMinimal(true);
				rx.indexIn(line);
				QString newEnv = rx.cap(1);
				// remove curly brakets as well
				QDocument *doc = cursor->document();
				QString searchWord = "\\end{" + oldEnv + "}";
				QString inhibitor = "\\begin{" + oldEnv + "}";
				bool backward = false;
				int step = 1;
				int startLine = cursor->lineNumber();
				//int startCol=cursor.columnNumber();
				int endLine = doc->findLineContaining(searchWord, startLine + step, Qt::CaseSensitive, backward);
				int inhibitLine = doc->findLineContaining(inhibitor, startLine + step, Qt::CaseSensitive, backward); // not perfect (same line end/start ...)
				while (inhibitLine > 0 && endLine > 0 && inhibitLine * step < endLine * step) {
					endLine = doc->findLineContaining(searchWord, endLine + step, Qt::CaseSensitive, backward); // not perfect (same line end/start ...)
					inhibitLine = doc->findLineContaining(inhibitor, inhibitLine + step, Qt::CaseSensitive, backward);
				}
				QString endText = doc->line(endLine).text();
				int start = endText.indexOf(searchWord);
				int offset = searchWord.indexOf("{");
				int length = searchWord.length() - offset - 1;
				selector.moveTo(endLine, start + 1 + offset);
				selector.movePosition(length - 1, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
				selector.replaceSelectedText(newEnv);
				cursor->movePosition(closeCurl - cursor->columnNumber() + 1, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
				QString first = lines.first();
				int pos = first.indexOf('{');
				pos = first.indexOf('{', pos + 1); //pos of second {
				if (pos > -1)
					first.remove(pos, first.length() - pos);
				editor->document()->clearLanguageMatches();
				editor->insertText(*cursor, first);
				if (editBlockOpened) cursor->endEditBlock();
				return;
			}
		}
	}

	int baseLine = cursor->lineNumber();
	int baseLineIndent = cursor->columnNumber(); //text before inserted word moves placeholders to the right
	int lastLineRemainingLength = curLine.text().length() - baseLineIndent; //last line will has length: indentation + codesnippet + lastLineRemainingLength
	if (editor->flag(QEditor::AutoInsertLRM) && cursor->isRTL()
	        && line.size() > 2 && (line.at(0).direction() == QChar::DirL || line.at(1).direction() == QChar::DirL) //starts with strong left-to-right
	        && line[line.length() - 1].direction() == QChar::DirON) //but ends with weak (e.g. "foobar{}", backslash is handled by completer)
		line += QChar(LRM);
	editor->document()->clearLanguageMatches();
	editor->insertText(*cursor, line); //don't use cursor->insertText to keep autoindentation working

    if (editBlockOpened && savedSelection.isEmpty()) cursor->endEditBlock();

	// on single line commands only: replace command
	if (byCompleter && autoReplaceCommands && lines.size() == 1 && (line.startsWith('\\') || isKeyVal) ) {
		if (cursor->nextChar().isLetterOrNumber() || cursor->nextChar() == QChar('{') || cursor->nextChar() == QChar('=')) {
			QString curLine = cursor->line().text();
			int wordBreak = curLine.indexOf(QRegExp("\\W"), cursor->columnNumber());
			int wordBreakEqual = curLine.indexOf("=", cursor->columnNumber());
			int closeCurl = curLine.indexOf("}", cursor->columnNumber());
			int openCurl = curLine.indexOf("{", cursor->columnNumber());
			int openBracket = curLine.indexOf("[", cursor->columnNumber());
			if (!line.contains("{")) {
				if (openBracket < 0) openBracket = 1e9;
				if (closeCurl < 0) closeCurl = 1e9;
				if (openCurl < 0) openCurl = 1e9;
				if (wordBreakEqual < 0) wordBreakEqual = 1e9;
				if (wordBreak <= openBracket && wordBreak <= closeCurl && wordBreak <= openCurl) {
					if (wordBreak < 0)
						cursor->movePosition(wordBreak - cursor->columnNumber(), QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
					else {
						if (isKeyVal && wordBreak == wordBreakEqual)
							wordBreak = wordBreakEqual + 1;
						cursor->movePosition(wordBreak - cursor->columnNumber(), QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
					}
					cursor->removeSelectedText();
					return;
				}
			} else {
				if (openCurl > -1) {
					if (openBracket < 0) openBracket = 1e9;
					if (closeCurl < 0) closeCurl = 1e9;
					if (openCurl < openBracket && openCurl < closeCurl && openCurl <= wordBreak) {
						cursor->movePosition(openCurl - cursor->columnNumber(), QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
						cursor->removeSelectedText();
						int curl = line.length() - line.indexOf("{");
						cursor->movePosition(curl, QDocumentCursor::PreviousCharacter, QDocumentCursor::KeepAnchor);
						cursor->removeSelectedText();
						return;
					}
				}
			}
		}
	}

	Q_ASSERT(placeHolders.size() == lines.count());
	bool usePlaceholders = (placeholderMode == PlacehodersActive);
	if (usePlaceholders) {
		//check if there actually are placeholders to insert
		usePlaceholders = false;
		for (int l = 0; l < lines.count(); l++)
			usePlaceholders |= placeHolders[l].size();
	}

	int autoSelectPlaceholder = -1;
	if (usePlaceholders) {
		if (editor->currentPlaceHolder() != -1 &&
		        editor->getPlaceHolder(editor->currentPlaceHolder()).cursor.isWithinSelection(*cursor))
			editor->removePlaceHolder(editor->currentPlaceHolder()); //remove currentplaceholder to prevent nesting
		for (int l = 0; l < lines.count(); l++) {
			//if (l<mLines.count()-1) cursor->insertLine();
			for (int i = 0; i < placeHolders[l].size(); i++) {
				if (placeHolders[l][i].flags & CodeSnippetPlaceHolder::Mirror) continue;
				PlaceHolder ph;
				ph.length = placeHolders[l][i].length;
				ph.cursor = getCursor(editor, placeHolders[l][i], l, baseLine, baseLineIndent, lastLineRemainingLength);
				ph.autoRemove = !(placeHolders[l][i].flags & CodeSnippetPlaceHolder::Persistent);
				if (!ph.cursor.isValid()) continue;
				editor->addPlaceHolder(ph);
				if (placeHolders[l][i].flags & CodeSnippetPlaceHolder::Mirrored) {
					int phId = editor->placeHolderCount() - 1;
					for (int lm = 0; lm < placeHolders.size(); lm++)
						for (int im = 0; im < placeHolders[lm].size(); im++)
							if (placeHolders[lm][im].flags & CodeSnippetPlaceHolder::Mirror &&
							        placeHolders[lm][im].id == placeHolders[l][i].id)
								editor->addPlaceHolderMirror(phId, getCursor(editor, placeHolders[lm][im], lm, baseLine, baseLineIndent, lastLineRemainingLength));
				}
				if ((placeHolders[l][i].flags & CodeSnippetPlaceHolder::AutoSelect) &&
				        ((autoSelectPlaceholder == -1) ||
				         (multiLineSavedSelection && (placeHolders[l][i].flags & CodeSnippetPlaceHolder::PreferredMultilineAutoSelect))))
					autoSelectPlaceholder = editor->placeHolderCount() - 1;

			}
		}
	}


	//place cursor
	int curOffset = cursorOffset;
	int anchOffset = anchorOffset;
	int cursLine = cursorLine;
	if (placeholderMode == PlaceholdersRemoved) {
		curOffset = phrmCursorOffset;
		anchOffset = phrmCursorOffset;
		cursLine = phrmCursorLine;
	}

	if (curOffset != -1) {
		int realAnchorOffset = anchOffset; //will be moved to the right if text is already inserted on this line
		if (cursLine > 0) {
			if (cursLine >= lines.size()) return;
			if (!selector.movePosition(cursLine, QDocumentCursor::Down, QDocumentCursor::MoveAnchor))
				return;
			//if (editor->flag(QEditor::AutoIndent))
			realAnchorOffset += selector.line().length() - (lines[cursLine].length() - phrmCursorLineRemovedChars);
			if (cursLine + 1 == lines.size())
				realAnchorOffset -= lastLineRemainingLength;
		} else realAnchorOffset += baseLineIndent;
		selector.setColumnNumber(realAnchorOffset);
		bool ok = true;
		if (curOffset > anchOffset)
			ok = selector.movePosition(curOffset - anchOffset, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
		else if (curOffset < anchOffset)
			ok = selector.movePosition(anchOffset - curOffset, QDocumentCursor::PreviousCharacter, QDocumentCursor::KeepAnchor);
		if (!ok) return;
		editor->setCursor(selector);
	} else if (autoSelectPlaceholder != -1) {
		editor->setPlaceHolder(autoSelectPlaceholder, true); //this moves the cursor to that placeholder
	} else {
		editor->setCursor(*cursor); //place after insertion
		return;
	}
	if (!savedSelection.isEmpty()) {
        QDocumentCursor oldCursor = editor->cursor();
        //editor->cursor().insertText(savedSelection, true);
        cursor->moveTo(editor->cursor());
        if(oldCursor.hasSelection())
            cursor->moveTo(oldCursor.anchorLineNumber(),oldCursor.anchorColumnNumber(),QDocumentCursor::KeepAnchor);
        cursor->insertText(savedSelection, true);
        cursor->endEditBlock(); // necessary to generate undo stack when ctrl+b on selection (bug #135)
        if (!cursor->hasSelection() && alwaysSelect) {
            cursor->movePosition(savedSelection.length(), QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
		}
        editor->setCursor(*cursor);
		if (autoSelectPlaceholder != -1) editor->setPlaceHolder(autoSelectPlaceholder, true); //this synchronizes the placeholder mirrors with the current placeholder text
	}
}

void CodeSnippet::setName(const QString &newName)
{
	name = newName;
}

QString CodeSnippet::getName() const
{
	return name;
}

QDocumentCursor CodeSnippet::getCursor(QEditor *editor, const CodeSnippetPlaceHolder &ph, int snippetLine, int baseLine, int baseLineIndent, int lastLineRemainingLength) const
{
	QDocumentCursor cursor = editor->document()->cursor(baseLine + snippetLine, ph.offset);
	if (snippetLine == 0) cursor.movePosition(baseLineIndent, QDocumentCursor::NextCharacter);
	else {
		cursor.movePosition(cursor.line().length() - lines[snippetLine].length(), QDocumentCursor::NextCharacter);
		if (snippetLine + 1 == lines.size())
			cursor.movePosition(lastLineRemainingLength, QDocumentCursor::PreviousCharacter);
	}
	return cursor;
}

void CodeSnippetList::unite(CodeSnippetList &lst)
{
	this->append(lst);
	CodeSnippetList::iterator middle = this->end() - lst.length();
	std::inplace_merge(this->begin(), middle, this->end());
}

void CodeSnippetList::unite(const QList<CodeSnippet> &lst)
{
	this->append(lst);
	CodeSnippetList::iterator middle = this->end() - lst.length();
	std::inplace_merge(this->begin(), middle, this->end());
}

void CodeSnippetList::insert(const QString &elem)
{
	CodeSnippet cs(elem);
	cs.usageCount = 2;
	QList<CodeSnippet>::iterator it = qLowerBound(this->begin(), this->end(), cs);
	QList<CodeSnippet>::insert(it, cs);
}
