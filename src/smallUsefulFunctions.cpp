#include "smallUsefulFunctions.h"
#include "qdocumentline_p.h"
#include "qdocument.h"
#include <QBuffer>
#include "latexparser/latexparser.h"



/*
QList<QPair<QString,QString> > latexToPlainWordReplaceList =
 QList<QPair<QString,QString> >()
 << QPair<QString, QString> ("\\-","") //Trennung [separation] (german-babel-package also: \")
 << QPair<QString, QString> ("\\/","") //ligatur preventing (german-package also: "|)
 << QPair<QString, QString> ("\"~","-") //- ohne Trennung (without separation)
//german-babel-package: "- (\- but also normal break),  "= ( like - but also normal break), "" (umbruch ohne bindestrich)
 << QPair<QString, QString> ("\"-","")
 << QPair<QString, QString> ("\"a","\xE4")
 << QPair<QString, QString> ("\"o","\xF6")
 << QPair<QString, QString> ("\"u","\xFC")
 << QPair<QString, QString> ("\"s","\xDF")
 << QPair<QString, QString> ("\"A","\xC4")
 << QPair<QString, QString> ("\"O","\xD6")
 << QPair<QString, QString> ("\"U","\xDC")
 << QPair<QString, QString> ("\\\"{a}","\xE4")
 << QPair<QString, QString> ("\\\"{o}","\xF6")
 << QPair<QString, QString> ("\\\"{u}","\xFC")
 << QPair<QString, QString> ("\\\"{A}","\xC4")
 << QPair<QString, QString> ("\\\"{O}","\xD6")
 << QPair<QString, QString> ("\\\"{U}","\xDC")
 << QPair<QString, QString> ("\"|","")
 << QPair<QString, QString> ("\"","")
//	<< QPair<QString, QString> ("\"\"","") redunant
 << QPair<QString, QString> ("\\",""); // eliminating backslash which might remain from accents like \"a ...
*/
/*!
 * \brief transformCharacter
 * Transform a character from a tex encoded to utf
 * e.g. "a -> ä
 * \param c
 * \param context
 * \return tranformed character
 */
QChar transformCharacter(const QChar &c, const QChar &context)
{
	// *INDENT-OFF*  (astyle-config)
	switch (context.toLatin1()) {
	case '"':  // umlaut
		switch (c.toLatin1()){
		case 'a': return QChar(0xE4);
		case 'e': return QChar(0xEB);
		case 'i': return QChar(0xEF);
		case 'o': return QChar(0xF6);
		case 'u': return QChar(0xFC);
		case 'A': return QChar(0xC4);
		case 'E': return QChar(0xCB);
		case 'I': return QChar(0xCF);
		case 'O': return QChar(0xD6);
		case 'U': return QChar(0xDC);
		case 's': return QChar(0xDF);
		default: return c;
		}
	case '`':  // grave
		switch (c.toLatin1()){
		case 'a': return QChar(0xE0);
		case 'e': return QChar(0xE8);
		case 'i': return QChar(0xEC);
		case 'o': return QChar(0xF2);
		case 'u': return QChar(0xF9);
		case 'A': return QChar(0xC0);
		case 'E': return QChar(0xC8);
		case 'I': return QChar(0xCC);
		case 'O': return QChar(0xD2);
		case 'U': return QChar(0xD9);
		default: return c;
		}
	case '\'':  // acute
		switch (c.toLatin1()){
		case 'a': return QChar(0xE1);
		case 'e': return QChar(0xE9);
		case 'i': return QChar(0xED);
		case 'o': return QChar(0xF3);
		case 'u': return QChar(0xFA);
		case 'y': return QChar(0xFD);
		case 'A': return QChar(0xC1);
		case 'E': return QChar(0xC9);
		case 'I': return QChar(0xCD);
		case 'O': return QChar(0xD3);
		case 'U': return QChar(0xDA);
		case 'Y': return QChar(0xDD);
		default: return c;
		}
	case '^':  // circumflex
		switch (c.toLatin1()){
		case 'a': return QChar(0xE2);
		case 'e': return QChar(0xEA);
		case 'i': return QChar(0xEE);
		case 'o': return QChar(0xF4);
		case 'u': return QChar(0xFB);
		case 'A': return QChar(0xC2);
		case 'E': return QChar(0xCA);
		case 'I': return QChar(0xCE);
		case 'O': return QChar(0xD4);
		case 'U': return QChar(0xDB);
		default: return c;
		}
	case '~':  // tilde
		switch (c.toLatin1()){
		case 'a': return QChar(0xE3);
		case 'n': return QChar(0xF1);
		case 'o': return QChar(0xF5);
		case 'A': return QChar(0xC3);
		case 'N': return QChar(0xD1);
		case 'O': return QChar(0xD5);
		default: return c;
		}
	case 'c':  // cedille
		switch (c.toLatin1()){
		case 'c': return QChar(0xE7);
		case 'C': return QChar(0xC7);
		default: return c;
		}
	}
	return c;
	// *INDENT-ON*  (astyle-config)
}

QString latexToPlainWord(const QString &word)
{

	/*	QString result=word;
	for (QList<QPair<QString,QString> >::const_iterator it=latexToPlainWordReplaceList.begin(); it!=latexToPlainWordReplaceList.end(); ++it)
	result.replace(it->first,it->second);*/
	QString result;
	result.reserve(word.length());
	for (int i = 0; i < word.length(); i++) {
		if (word[i] == '\\') {
			//decode all meta characters starting with a backslash (c++ syntax: don't use an actual backslash there or it creates a multi line comment)
			i++;
			if (i >= word.length()) break;
			switch (word[i].toLatin1()) {
			case '-': //Trennung [separation] (german-babel-package also: \")
			case '/': //ligatur preventing (german-package also: "|)
				break;

			case '"':
			case '\'':
			case '^':
			case '`':
			case '~':
			case 'c':
				if (i + 3 < word.length()) {
					if (word[i + 1] == '{' && word[i + 3] == '}') {
						result.append(transformCharacter(word[i + 2], word[i]));
						i += 3;
						break;
					}
				}
				if (i + 1 < word.length()) {
					if (word[i + 1] == '\\' || word[i + 1] == '"')
						break;  //ignore "
					result.append(transformCharacter(word[i + 1], word[i]));
					i++;
					break;
				}
				i--; //repeat with "
				break;
			default:
				i--; //repeat with current char
			}
		} /* else if (word[i] == '"') {     // replacement from german package is handled extra
			//decode all meta characters starting with "
			i++;
			if (i>=word.length()) break;
			switch (word[i].toLatin1()) {
			case '~':
				result.append('-'); //- ohne Trennung (without separation)
				break;
			case '-':
			case '|': //babel package, separation
			case '"':  //ignore ""
				break;
			default:
                result.append(transformCharacter(word[i], '"'));

			}
        }*/ else result.append(word[i]);
	}

	return result;
}
QString latexToPlainWordwithReplacementList(const QString &word, QMap<QString, QString> &replacementList )
{
	QString result;
	QString w = latexToPlainWord(word);
    if (!replacementList.isEmpty()){
        while (!w.isEmpty()) {
            bool replaced = false;
            foreach (const QString elem, replacementList.keys()) {
                if (w.startsWith(elem)) {
                    result.append(replacementList.value(elem));
                    w = w.mid(elem.length());
                    replaced = true;
                    break;
                }
            }
            if (!replaced) {
                result.append(w.left(1));
                w = w.mid(1);
            }
        }
    }else{
        result=w;
    }
    // remove leading and trailing "
    if(result.startsWith("\"")){
        result=result.mid(1);
    }
    if(result.endsWith("\"")){
        result.chop(1);
    }
	return result;
}

QString textToLatex(const QString &text)
{
	QList<QPair<QString, QString> > replaceList;
	// replacements for resevered characters according to
	// http://en.wikibooks.org/wiki/LaTeX/Basics#Reserved_Characters
	replaceList.append(QPair<QString, QString> ("\\", "\\textbackslash{}"));
	replaceList.append(QPair<QString, QString> ("{", "\\{"));
	replaceList.append(QPair<QString, QString> ("}", "\\}"));
	replaceList.append(QPair<QString, QString> ("#", "\\#"));
	replaceList.append(QPair<QString, QString> ("$", "\\$"));
	replaceList.append(QPair<QString, QString> ("%", "\\%"));
	replaceList.append(QPair<QString, QString> ("&", "\\&"));
	replaceList.append(QPair<QString, QString> ("~", "\\~{}"));
	replaceList.append(QPair<QString, QString> ("_", "\\_"));
	replaceList.append(QPair<QString, QString> ("^", "\\^{}"));

	QString result = text;
	for (QList<QPair<QString, QString> >::const_iterator it = replaceList.begin(); it != replaceList.end(); ++it)
		result.replace(it->first, it->second);

	return result;
}


int startOfArg(const QString &s, int index) {
	for (int i=index; i < s.length(); i++) {
		if (s.at(i).isSpace()) continue;
		if (s.at(i) == '{') return i;
		return -1;
	}
	return -1;
}

/*!
 * Parses a Latex string to a plain string.
 * Specifically, this substitues \texorpdfstring and removes explicit hyphens.
 */
QString latexToText(QString s)
{
	// substitute \texorpdfstring
	int start, stop;
	int texorpdfstringLength = 15;
	start = s.indexOf("\\texorpdfstring");
	while (start >= 0 && start < s.length()) {

		// first arg
		int i = startOfArg(s, start + texorpdfstringLength);
		if (i < 0) {  // no arguments for \\texorpdfstring
			start += texorpdfstringLength;
			start = s.indexOf("\\texorpdfstring", start);
			continue;
		}
		i++;
		stop = findClosingBracket(s, i);
		if (stop < 0) {  // missing closing bracket for first argument of \\texorpdfstring
			start += texorpdfstringLength;
			start = s.indexOf("\\texorpdfstring", start);
			continue;
		}

		// second arg
		i = startOfArg(s, stop + 1);
		if (i < 0) {  // no second arg for \\texorpdfstring
			start += texorpdfstringLength;
			start = s.indexOf("\\texorpdfstring", start);
			continue;
		}
		i++;
		stop = findClosingBracket(s, i);
		if (stop < 0) {
			start += texorpdfstringLength;
			start = s.indexOf("\\texorpdfstring", start);
			continue;  // no second arg for \\texorpdfstring
		}
		s.remove(stop, 1);
		s.remove(start, i - start);
		start = s.indexOf("\\texorpdfstring", start);
	}
	// remove discretionary  hyphenations
	s.remove("\\-");
	return s;
}

// joins all the input lines trimming whitespace. A new line is started on comments and empty lines
QStringList joinLinesExceptCommentsAndEmptyLines(const QStringList &lines)
{
#define flush_tmpLine() if (!tmpLine.isEmpty()) { joinedLines.append(tmpLine); tmpLine.clear(); }

	QStringList joinedLines;
	QString tmpLine;
	foreach (const QString &l, lines) {
		QString rtrimmedLine = trimRight(l);

		if (rtrimmedLine.isEmpty()) { // empty line as separator
			flush_tmpLine();
			joinedLines.append(rtrimmedLine);
			continue;
		}

		if (tmpLine.isEmpty()) {
			tmpLine.append(rtrimmedLine);
		} else {
			tmpLine.append(" " + rtrimmedLine.trimmed());
		}
		int commentStart = LatexParser::commentStart(rtrimmedLine);
		if (commentStart >= 0) {
			flush_tmpLine();
		}
	}
	flush_tmpLine();
	return joinedLines;
}

// splits lines after maximal number of chars while keeping track of indentation and comments
QStringList splitLines(const QStringList &lines, int maxCharPerLine, const QRegExp &breakChars)
{
	QStringList splittedLines;
	int maxIndent = maxCharPerLine / 2 * 3;
	foreach (QString line, lines) {
		int textStart = 0;
		while (textStart < line.length() && line.at(textStart).isSpace() && textStart < maxIndent) textStart++;
		if (textStart >= line.length()) { // empty line
			splittedLines << line;
			continue;
		}
		int maxCharPerLineWithoutIndent = maxCharPerLine - textStart;
		QString indent = line.left(textStart);
		line = line.mid(textStart);

		bool inComment = false;
		while (line.length() > maxCharPerLineWithoutIndent) {
			if (inComment) line.prepend("% ");
			int breakAt = line.lastIndexOf(breakChars, maxCharPerLineWithoutIndent);
			if (breakAt <= 3) breakAt = -1;
			QString leftPart = line.left(breakAt);
			splittedLines << indent + leftPart;
			if (breakAt >= 0) {
				line.remove(0, breakAt + 1);
				inComment = inComment || (LatexParser::commentStart(leftPart) >= 0);
			} else {
				line.clear();
				break;
			}
		}
		if (line.length() > 0) {
			if (inComment) line.prepend("% ");
			splittedLines << indent + line;
		}
	}
	return splittedLines;
}

bool localeAwareLessThan(const QString &s1, const QString &s2)
{
	return QString::localeAwareCompare(s1, s2) < 0;
}

// removes whitespace from the beginning of the string
QString trimLeft(const QString &s)
{
	int j;
	for (j = 0; j < s.length(); j++)
		if (s[j] != ' ' && s[j] != '\t' && s[j] != '\r' && s[j] != '\n') break;
	return s.mid(j);
}

// removes whitespace from the end of the string
QString trimRight(const QString &s)
{
	if (s.isEmpty()) return QString();
	int j;
	for (j = s.length() - 1; j >= 0; j--)
		if (s[j] != ' ' && s[j] != '\t' && s[j] != '\r' && s[j] != '\n') break;
	return s.left(j + 1);
}
/*!
 * \brief get argument after command 'token'
 *
 * handles latex comments correctly
 * \warning obsolete with lexer based token system
 * \param line text of one line
 * \param token latexcommand
 * \return text after token
 */
QString findToken(const QString &line, const QString &token)
{
	int tagStart = line.indexOf(token);
	int commentStart = line.indexOf(QRegExp("(^|[^\\\\])%")); // find start of comment (if any)
	if (tagStart != -1 && (commentStart > tagStart || commentStart == -1)) {
		tagStart += token.length();
		int tagEnd = line.indexOf("}", tagStart);
		if (tagEnd != -1) return line.mid(tagStart, tagEnd - tagStart);
		else return line.mid(tagStart); //return everything after line if there is no }
	}
	return "";
}
/*!
 * \brief get argument after command 'token'
 *
 * handles latex comments correctly
 * \warning obsolete with lexer based token system
 * \param line text of one line
 * \param token latexcommand
 * \param start column number
 * \return text after token
 */
QString findToken(const QString &line, const QString &token, int &start)
{
	int tagStart = line.indexOf(token, start);
	int commentStart = line.indexOf(QRegExp("(^|[^\\\\])%")); // find start of comment (if any)
	if (tagStart != -1 && (commentStart > tagStart || commentStart == -1)) {
		tagStart += token.length();
		int tagEnd = line.indexOf("}", tagStart);
		start = tagStart;
		if (tagEnd != -1) return line.mid(tagStart, tagEnd - tagStart);
		else return line.mid(tagStart); //return everything after line if there is no }
	}
	start = -2;
	return "";
}
/*!
 * \brief get argument after command 'token'
 *
 * handles latex comments correctly
 * \warning obsolete with lexer based token system
 * \param line text of one line
 * \param token regexp to search
 * \return text after token
 */
QString findToken(const QString &line, QRegExp &token)
{
	//ATTENTION: token is not const because, you can't call cap on const qregexp in qt < 4.5
	int tagStart = 0;
	QString s = line;
	tagStart = token.indexIn(line);
	int commentStart = line.indexOf(QRegExp("(^|[^\\\\])%")); // find start of comment (if any)
	if (tagStart != -1 && (commentStart > tagStart || commentStart == -1)) {
		s = s.mid(tagStart + token.cap(0).length(), s.length());
		return s;
	}
	return "";
}

bool findTokenWithArg(const QString &line, const QString &token, QString &outName, QString &outArg)
{
	outName = "";
	outArg = "";
	int tagStart = line.indexOf(token);
	int commentStart = line.indexOf(QRegExp("(^|[^\\\\])%")); // find start of comment (if any)
	if (tagStart != -1 && (commentStart > tagStart || commentStart == -1)) {
		tagStart += token.length();
		int tagEnd = line.indexOf("}", tagStart);
		if (tagEnd != -1) {
			outName = line.mid(tagStart, tagEnd - tagStart);
			int curlyOpen = line.indexOf("{", tagEnd);
			int optionStart = line.indexOf("[", tagEnd);
			if (optionStart < curlyOpen || (curlyOpen == -1 && optionStart != -1)) {
				int optionEnd = line.indexOf("]", optionStart);
				if (optionEnd != -1) outArg = line.mid(optionStart + 1, optionEnd - optionStart - 1);
				else outArg = line.mid(optionStart + 1);
			}
		} else outName = line.mid(tagStart); //return everything after line if there is no }
		return true;
	}
	return false;
}

/*! returns the command at pos (including \) in outCmd. pos may be anywhere in the command name (including \) but
 * not in command options. Return value is the index of the first char after the command (or pos if there was no command
 * \warning obsolete with lexer-based token system
 */
// TODO: currently does not work for command '\\'
int getCommand(const QString &line, QString &outCmd, int pos)
{
	int start = pos;

	while (line.at(start) != '\\') { // find beginning
		if (!isCommandChar(line.at(start)) || start == 0) return pos; // no command
		start--;
	}

	int i = pos + 1;
	for (; i < line.length(); i++)
		if (!isCommandChar(line.at(i))) break;
	outCmd = line.mid(start, i - start);
	return i;
}

/*! returns command option list. pos has to be at the beginning of the first bracket
 * posBehind returns the position after the last bracket, you may pass the same variable as in pos
 * \warning obsolete with lexer-based token system
 */
QList<CommandArgument> getCommandOptions(const QString &line, int pos, int *posBehind)
{
	static QMap<QChar, QChar> cbs;
	if (cbs.isEmpty()) {
		cbs[QChar('{')] = QChar('}');
		cbs[QChar('[')] = QChar(']');
	}

	QList<CommandArgument> options;

	int start = pos;
	if (posBehind) *posBehind = start;
	if (pos >= line.length()) return options;
	QChar oc = line[start];
	if (!cbs.contains(oc)) return options;

	for (int num = 1;; num++) {
		int end = findClosingBracket(line, start, oc, cbs[oc]);
		if (end < 0) break; // open without close
		CommandArgument arg;
		arg.isOptional = (oc == '[');
		arg.number = num;
		arg.value = line.mid(start + 1, end - start - 1);
		options.append(arg);
		start = end + 1;
		if (posBehind) *posBehind = start;
		if (start >= line.length() || !cbs.contains(line[start])) break; // close on last char or last option reached
		else oc = line[start];
	}
	return options;
}

/* returns the item at pos in a colon separated list of options (empty on colon
 * e.g. getParamItem("{one, two, three}", 7) returns "two"
 * \warning obsolete with lexer-based token system
 */
QString getParamItem(const QString &line, int pos, bool stopAtWhiteSpace)
{
	REQUIRE_RET(pos <= line.length(), QString());
	int start;
	int curlCount = 0;
	int squareCount = 0;
	QString openDelim(",{[");
	if (stopAtWhiteSpace) openDelim += " \t\n\r";
	for (start = pos; start > 0; start--) {
		QChar c = line.at(start - 1);
		if (c == '}' && openDelim.contains('{')) curlCount++;
		if (c == '{') {
			if (curlCount-- <= 0) break;
			else continue;
		}
		if (c == ']' && openDelim.contains('[')) squareCount++;
		if (c == '[') {
			if (squareCount-- <= 0) break;
			else continue;
		}
		if (openDelim.contains(c)) break;
	}
	int end = pos;
	QString closeDelim(",]}");
	if (stopAtWhiteSpace) closeDelim += " \t\n\r";
	curlCount = 0;
	squareCount = 0;
	for (end = pos; end < line.length(); end++) {
		QChar c = line.at(end);
		if (c == '{' && closeDelim.contains('}')) curlCount++;
		if (c == '}') {
			if (curlCount-- <= 0) break;
			else continue;
		}
		if (c == '[' && closeDelim.contains(']')) squareCount++;
		if (c == ']') {
			if (squareCount-- <= 0) break;
			else continue;
		}
		if (closeDelim.contains(c)) break;
	}
	return line.mid(start, end - start);
}

QRegExp generateRegExp(const QString &text, const bool isCase, const bool isWord, const bool isRegExp)
{
	Qt::CaseSensitivity cs = isCase ? Qt::CaseSensitive : Qt::CaseInsensitive;
	QRegExp m_regexp;
	if ( isRegExp ) {
		m_regexp = QRegExp(text, cs, QRegExp::RegExp);
	} else if ( isWord ) {
		//todo: screw this? it prevents searching of "world!" and similar things
		//(qtextdocument just checks the surrounding character when searching for whole words, this would also allow wholewords|regexp search)
		m_regexp = QRegExp(
		               QString("\\b%1\\b").arg(QRegExp::escape(text)),
		               cs,
		               QRegExp::RegExp
		           );
	} else {
		m_regexp = QRegExp(text, cs, QRegExp::FixedString);
	}
	return m_regexp;
}

QStringList regExpFindAllMatches(const QString &searchIn, const QRegExp &regexp, int cap)
{
	int offset = regexp.indexIn(searchIn);
	QStringList res;
	while (offset > -1) {
		res << regexp.cap(cap);
		offset = regexp.indexIn(searchIn, offset + regexp.matchedLength());
	}
	return res;
}

/*!
 * a multi-match equivalent of QString::indexOf(QString)
 */
QList<int> indicesOf(const QString &line, const QString &word, Qt::CaseSensitivity cs)
{
	QList<int> columns;
	int col = 0;
	while (col < line.length() - 1) {
		col = line.indexOf(word, col, cs);
		if (col < 0) break;
		columns.append(col);
		col++;
	}
	return columns;
}

/*!
 * a multi-match equivalent of QString::indexOf(QRegExp)
 */
QList<int> indicesOf(const QString &line, const QRegExp &rx)
{
	QList<int> columns;
	int col = 0;
	// exact match
	while (col < line.length() - 1) {
		col = line.indexOf(rx, col);
		if (col < 0) break;
		columns.append(col);
		col++;
	}
	return columns;
}

void addEnvironmentToDom(QDomDocument &doc, const QString &EnvironName, const QString &EnvironMode, bool completeParentheses)
{
	QDomElement root = doc.documentElement();
	QDomElement tag = doc.createElement("context");
	tag.setAttribute("id", EnvironMode == "numbers" ? "mathMyEnv" : "myVerb");
	tag.setAttribute("format", EnvironMode);
	if (EnvironMode != "comment") tag.setAttribute("transparency", "true");
	QDomElement child1 = doc.createElement("start");
	child1.setAttribute("parenthesis", QString("my%1:open%2").arg(EnvironName).arg(completeParentheses ? "" : "@nocomplete"));
	child1.setAttribute("fold", "true");
	child1.setAttribute("format", "extra-keyword");
	child1.setAttribute("parenthesisWeight", "30");
	QDomText dtxt = doc.createTextNode(QString("\\\\begin{%1}").arg(EnvironName));
	child1.appendChild(dtxt);
	QDomElement child2 = doc.createElement("stop");
	child2.setAttribute("parenthesis", QString("my%1:close%2").arg(EnvironName).arg(completeParentheses ? "" : "@nocomplete"));
	child2.setAttribute("fold", "true");
	child2.setAttribute("format", "extra-keyword");
	child2.setAttribute("parenthesisWeight", "30");
	QDomText dtxt2 = doc.createTextNode(QString("\\\\end{%1}").arg(EnvironName));
	child2.appendChild(dtxt2);

	tag.appendChild(child1);
	tag.appendChild(child2);

	if (EnvironMode == "numbers") {
		QDomElement child3 = doc.createElement("word");
		child3.setAttribute("id", "keywords/single");
		child3.setAttribute("format", "math-keyword");
		child3.appendChild(doc.createTextNode("\\\\[a-zA-Z]+"));
		tag.appendChild(child3);
	}

	//insert before the first context with the same format, so that transparency is actually used
	QDomNode insertAt;
	for (int i = 0; i < root.childNodes().size(); i++)
		if (root.childNodes().item(i).attributes().namedItem("format").nodeValue() == EnvironMode) {
			insertAt = root.childNodes().item(i);
			break;
		}
	root.insertBefore(tag, insertAt);
}

/*! adds entries for structure commands to the Dom of a QNFA file
 * commands are taken from possibleCommands["%structure0"] to possibleCommands["%structureN"]
 */
void addStructureCommandsToDom(QDomDocument &doc , const QHash<QString, QSet<QString> > &possibleCommands)
{
	QDomElement root = doc.documentElement();

	QDomNode parent;
	for (int i = root.childNodes().size() - 1; i >= 0; i--) {
		if (root.childNodes().item(i).attributes().namedItem("id").nodeValue() == "keywords/structure") {
			parent = root.childNodes().item(i);
			break;
		}
	}
	if (parent.isNull()) {
		return;
	}

	while (!parent.firstChild().isNull()) {
		parent.removeChild(parent.firstChild());
	}

	for (int level = 0; level <= LatexParser::MAX_STRUCTURE_LEVEL; level++) {
		foreach (const QString &cmd, possibleCommands[QString("%structure%1").arg(level)]) {
			QDomElement child = doc.createElement("word");
			QString name = cmd;
			name.remove('\\');
			child.setAttribute("parenthesis", QString("structure%1:boundary@nomatch").arg(level));
			child.setAttribute("parenthesisWeight", QString("%1").arg(8 - level));
			child.setAttribute("fold", "true");
			name = cmd;
			name.replace('\\', "\\\\");  // words are regexps, so we have to escape the slash
			QDomText dtxt = doc.createTextNode(name);
			child.appendChild(dtxt);
			parent.appendChild(child);
		}
	}
}



/*!
 * \brief convert a list of integer in one string with a textual representation of said integers
 *
 * The numbers are given as text, separated by commas
 * \param ints list of integer
 * \return string containg a textual list of integers
 */
QString intListToStr(const QList<int> &ints)
{
	QString s = "";
	foreach (int i, ints) {
		s.append(QString::number(i) + ',');
	}
	if (s.length() > 0)
		s.remove(s.length() - 1, 1); // remove last ','
	return s;
}

QList<int> strToIntList(const QString &s)
{
	QList<int> ints;
	bool ok;
	foreach (const QString &si, s.split(',')) {
		int i = si.toInt(&ok);
		if (ok) ints << i;
	}
	return ints;
}

// minimal json parser
// only supports strings as values, i.e.
// { "key1" : "val1", "key2" : "val2"}
// This is just a quick solution. If more complexity is requires, one should resort to QJson or the JSON support in Qt 5
bool minimalJsonParse(const QString &text, QHash<QString, QString> &map)
{
	int len = text.length();
	int col = text.indexOf('{');
	while (true) {
		QString key;
		QString val;
		int startStr, endStr;
		startStr = text.indexOf('"', col + 1);
		if (startStr < 0) return true;
		endStr = startStr;
		while (endStr >= 0) {
			endStr = text.indexOf('"', endStr + 1);
			if (text.at(endStr - 1) != '\\') break;
		}
		if (endStr < 0) return false;
		key = text.mid(startStr + 1, endStr - startStr - 1); // +1 / -1 outer removes qoutes
		key.replace("\\\"", "\"");

		col = endStr + 1;
		while (col < len && text.at(col).isSpace()) col++;
		if (col >= len || (text.at(col)) != ':') return false;
		col++;
		while (col < len && text.at(col).isSpace()) col++;

		if (col >= len || (text.at(col)) != '"') return false;
		startStr = col;
		endStr = startStr;
		while (endStr >= 0) {
			endStr = text.indexOf('"', endStr + 1);
			if (text.at(endStr - 1) != '\\') break;
		}
		if (endStr < 0) return false;
		val = text.mid(startStr + 1, endStr - startStr - 1); // +1 / -1 outer removes qoutes
		val.replace("\\\"", "\"");
		map[key] = val;

		col = endStr + 1;
		while (col < len && text.at(col).isSpace()) col++;
		if (col >= len) return false;
		if (text.at(col) == '}') return true;
		if (text.at(col) != ',') return false;
	}
	return true;
}

QString formatJsonStringParam(const QString &id, const QString &val, int minIdWidth)
{
	QString s = enquoteStr(id);
	while (s.length() < minIdWidth) s += ' ';
	s += " : " + enquoteStr(val);
	return s;
}

QString enquoteStr(const QString &s)
{
	QString res = s;
	res.replace('"', "\\\"");
	res.prepend('"');
	res.append('"');
	return res;
}

QString dequoteStr(const QString &s)
{
	QString res = s;
	if (res.endsWith('"') && !res.endsWith("\\\""))
		res.remove(res.length() - 1, 1);
	if (res.startsWith('"'))
		res.remove(0, 1);
	res.replace("\\\"", "\"");
	return res;
}

/** add a quotation around the string if it does not already have one. **/
QString quotePath(const QString &s)
{
	if (s.startsWith('"') || !s.contains(' ')) return QString(s);
	return QString("\"%1\"").arg(s);
}

/** if the string is surrounded by qoutes, remove these **/
QString removeQuote(const QString &s)
{
	if (s.length() >= 2 && s.startsWith('"') && s.endsWith('"')) {
		return s.mid(1, s.length() - 2);
	}
	return s;
}

QString removePathDelim(const QString &s)
{
	// we use the explicit chars intentionally and not QDir::separator()
	// because it shall also work for / on windows (many paths are internally
	// represented with / as delimiter
	if (s.endsWith('/') || s.endsWith('\\')) {
		return s.left(s.length() - 1);
	}
	return s;
}

QString removeAccents(const QString &s) {
	QString diacriticLetters = QString::fromUtf8("ŠŒŽšœžŸ¥µÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýÿ");
	QStringList noDiacriticLetters = QStringList() << "S"<<"OE"<<"Z"<<"s"<<"oe"<<"z"<<"Y"<<"Y"<<"u"<<"A"<<"A"<<"A"<<"A"<<"A"<<"A"<<"AE"<<"C"<<"E"<<"E"<<"E"<<"E"<<"I"<<"I"<<"I"<<"I"<<"D"<<"N"<<"O"<<"O"<<"O"<<"O"<<"O"<<"O"<<"U"<<"U"<<"U"<<"U"<<"Y"<<"s"<<"a"<<"a"<<"a"<<"a"<<"a"<<"a"<<"ae"<<"c"<<"e"<<"e"<<"e"<<"e"<<"i"<<"i"<<"i"<<"i"<<"o"<<"n"<<"o"<<"o"<<"o"<<"o"<<"o"<<"o"<<"u"<<"u"<<"u"<<"u"<<"y"<<"y";

	QString output = "";
	for (int i = 0; i < s.length(); i++) {
		QChar c = s[i];
		int dIndex = diacriticLetters.indexOf(c);
		if (dIndex < 0) {
			output.append(c);
		} else {
			QString replacement = noDiacriticLetters[dIndex];
			output.append(replacement);
		}
	}

	return output;
}

QString makeLatexLabel(const QString &s) {
	QString sNorm = removeAccents(s).normalized(QString::NormalizationForm_KD).toLower();
	sNorm.replace(' ', '-');
	sNorm.remove(QRegExp("[^a-z0-9\\-]"));
	return sNorm;
}

/*! Splits a command string into the command an arguments.
 *  This respects quoted arguments. Output redirection operators are separate tokens
 */
QStringList tokenizeCommandLine(const QString &commandLine) {
#define FLUSH(x) { if (!x.isEmpty()) { result << x; } x = ""; }
	QStringList result;
	QString currentToken = "";
	currentToken.reserve(30);
	bool inQuote = false;
	bool escape= false;

	foreach (const QChar &c, commandLine) {
		if (c.isSpace()) {
			if (inQuote) {
				currentToken.append(c);
			} else {
				FLUSH(currentToken)
			}
		} else if (c == '\\') {
			escape = !escape;
			currentToken.append(c);
			continue;
		} else if (c == '"') {
			if (!escape) inQuote = !inQuote;
			currentToken.append(c);
		} else if (c == '>') {
			if (inQuote) {
				currentToken.append(c);
			} else if (currentToken == "2"){
				currentToken.append(c);
				FLUSH(currentToken);
			} else {
				FLUSH(currentToken)
				currentToken = c;
				FLUSH(currentToken)
			}
		} else {
			currentToken.append(c);
		}
		escape = false;
	}
	FLUSH(currentToken)

	return result;
#undef FLUSH
}

QStringList extractOutputRedirection(const QStringList &commandArgs, QString &stdOut, QString &stdErr) {
	QStringList extracted;
	bool extracted_finished = false;
	for (int i=0; i<commandArgs.length(); i++) {
		if (commandArgs[i] == ">" && i < commandArgs.length()-1) {
			stdOut = commandArgs[i+1];
			i += 1;
			extracted_finished = true;
		} else if (commandArgs[i].startsWith(">")) {
			stdOut = commandArgs[i].mid(1);
			extracted_finished = true;
		} else if (commandArgs[i] == "2>" && i < commandArgs.length()-1) {
			stdErr = commandArgs[i+1];
			i += 1;
			extracted_finished = true;
		} else if (commandArgs[i].startsWith("2>")) {
			stdErr = commandArgs[i].mid(2);
			extracted_finished = true;
		} else {
			if (!extracted_finished)
				extracted << commandArgs[i];
		}
	}
	return extracted;
}


uint joinUnicodeSurrogate(const QChar &highSurrogate, const QChar &lowSurrogate)
{
	uint uhigh = highSurrogate.unicode();
	uint ulow = lowSurrogate.unicode();
	uint code = 0x10000;
	code += (uhigh & 0x03FF) << 10;
	code += (ulow & 0x03FF);
	return code;
}


QString getImageAsText(const QPixmap &AImage, const int w)
{
	QByteArray ba;
	QBuffer buffer(&ba);
	buffer.open(QIODevice::WriteOnly);
	AImage.save(&buffer, "PNG");
	QString text = w < 0 ? QString("<img src=\"data:image/png;base64,%1\">").arg(QString(buffer.data().toBase64())) : QString("<img src=\"data:image/png;base64,%1\" width=%2 >").arg(QString(buffer.data().toBase64())).arg(w);
	return text;
}

/*!
 * Shows a tooltip at the given position (pos = top left corner).
 * If the tooltip does not fit on the screen, it's attempted to position it to the left including
 * a possible relatedWidgetWidth offset (pos - relatedWidgetWidth = top right corner).
 * If there is not enough space as well the text is shown in the position (left/right) of maxium
 * available space and the text lines are shortend to fit the available space.
 */
void showTooltipLimited(QPoint pos, QString text, int relatedWidgetWidth)
{
	text.replace("\t", "    "); //if there are tabs at the position in the string, qt crashes. (13707)
	QRect screen = QApplication::desktop()->availableGeometry(pos);
	// estimate width of coming tooltip
	// rather dirty code
	bool textWillWarp = Qt::mightBeRichText(text);
    QLabel lLabel(nullptr, Qt::ToolTip);
	lLabel.setFont(QToolTip::font());
    lLabel.setMargin(1 + lLabel.style()->pixelMetric(QStyle::PM_ToolTipLabelFrameWidth, nullptr, &lLabel));
	lLabel.setFrameStyle(QFrame::StyledPanel);
	lLabel.setAlignment(Qt::AlignLeft);
	lLabel.setIndent(1);
	lLabel.setWordWrap(textWillWarp);
	lLabel.ensurePolished();
	lLabel.setText(text);
	lLabel.adjustSize();
	int textWidthInPixels = lLabel.width() + 10; // +10 good guess

	if (pos.x() - screen.x() + textWidthInPixels <= screen.width()) {
		// tooltip fits at the requested position
		QToolTip::showText(pos, text);
	} else {
		// try positioning the tooltip left of the releated widget
		QPoint posLeft(pos.x() - textWidthInPixels - relatedWidgetWidth, pos.y());
		if (posLeft.x() >= screen.x()) {
			QToolTip::showText(posLeft, text);
		} else {
			// text does not fit to the left
			// choose the position left/right with the maximum available space
			int availableWidthLeft = (pos.x() - screen.x()) - relatedWidgetWidth;
			int availableWidthRight = screen.width() - (pos.x() - screen.x());
			int availableWidth = qMax(availableWidthLeft, availableWidthRight);
			bool positionLeft = availableWidthLeft > availableWidthRight;
			if (!textWillWarp) {
				// shorten text lines to fit textwidth (only feasible if the tooltip does not wrap)
				QStringList lines = text.split("\n");
				int maxLength = 0;
				QString maxLine;
				foreach (const QString line, lines) {
					if (line.length() > maxLength) {
						maxLength = line.length();
						maxLine = line;
					}
				}
				int averageWidth = lLabel.fontMetrics().averageCharWidth();
				maxLength = qMin(maxLength, availableWidth / averageWidth);
				while (textWidthInPixels > availableWidth && maxLength > 10) {
					maxLength -= 2;
					for (int i = 0; i < lines.count(); i++) {
						lines[i] = lines[i].left(maxLength);
					}
					lLabel.setText(lines.join("\n"));
					lLabel.adjustSize();
					textWidthInPixels = lLabel.width() + 10;
				}
				text = lines.join("\n");
			}
			if (positionLeft) {
				posLeft.setX(pos.x() - textWidthInPixels - relatedWidgetWidth);
				QToolTip::showText(posLeft, text);
			} else {
				QToolTip::showText(pos, text);
			}
		}
	}
}

QString truncateLines(const QString &s, int maxLines)
{
	int lineCount = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '\n') lineCount++;
		if (lineCount >= maxLines) {
			return s.left(i + 1) + "...";
		}
	}
	return s;
}

/*
 * Utility function for most recent strings, e.g. for filenames
 * The item is inserted at the front and removed if present in the rest of the list.
 * The list will not get longer than maxLength.
 * Returns true if the list contents changed (i.e. item was not already in first place)
 */
bool addMostRecent(const QString &item, QStringList &mostRecentList, int maxLength)
{
	int p = mostRecentList.indexOf(item);
	bool changed = (p != 0);
	if (!changed) return changed;

	if (p > 0) mostRecentList.removeAt(p);
	mostRecentList.prepend(item);
	if (mostRecentList.count() > maxLength) mostRecentList.removeLast();
	return changed;
}


#define GCC_VERSION (__GNUC__ * 10000 \
                               + __GNUC_MINOR__ * 100 \
                               + __GNUC_PATCHLEVEL__)

