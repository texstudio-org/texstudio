//This file has been taken from KILE, merged together with their outputfilter

/************************************************************************************
    begin                : Die Sep 16 2003
    copyright            : (C) 2003 by Jeroen Wijnhout (wijnhout@science.uva.nl)
 ************************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// 2007-03-12 dani
//  - use KileDocument::Extensions

#include "latexoutputfilter.h"


using namespace std;

QColor LatexLogEntry::textColors[LT_MAX] = {QColor(Qt::black), QColor(230, 32, 32), QColor(234, 136, 32), QColor(58, 58, 230), QColor(Qt::darkBlue)};

/*textColors[LT_NONE] = QColor(Qt::black);
textColors[LT_ERROR] = QColor(230, 32, 32);
textColors[LT_WARNING] = QColor(234, 136, 32);
textColors[LT_BADBOX] = QColor(58, 58, 230);
*/

//====================texstudio log data struct=======================
LatexLogEntry::LatexLogEntry()
	: file(""), type(LT_NONE), oldline(-1), logline(-1), message("")
{
}

LatexLogEntry::LatexLogEntry(QString aFile, LogType aType, int aOldline, int aLogline, QString aMessage)
	: file(aFile), type(aType), oldline(aOldline), logline(aLogline), message(aMessage)
{
}

QString LatexLogEntry::niceMessage(bool richFormat) const
{
	QString pre = "";
	switch (type) {
	case LT_BADBOX:
		pre = QObject::tr("BadBox: ");
		break;
	case LT_WARNING:
		pre = QObject::tr("Warning: ");
		break;
	case LT_ERROR:
		pre = QObject::tr("Error: ");
		break;
	default:
		;
	}

	if (!richFormat) {
		return pre + message;
	}

	int beginBold = -1;
	int endBold = -1;

	if (type == LT_WARNING) { // hilight quoted strings 'citation' and `label'
		beginBold = message.indexOf(" `");
		if (beginBold < 0) {
			beginBold = message.indexOf(" \'");
		}
		if (beginBold >= 0) {
			endBold = message.indexOf('\'', beginBold + 2);
		}
	} else if (type == LT_ERROR) {
		if (message.startsWith("Undefined control sequence ")) {
			beginBold = 27; // size of above string
		}
	}

	// WORKAROUND: Even with <nobr> or style=\"white-space: nowrap\" Qt still breaks at hyphens
	// see: https://bugreports.qt-project.org/browse/QTBUG-1135
	// and: https://bugreports.qt-project.org/browse/QTBUG-6092
	// replacing with non-breaking hyphen did not work on Win7 (character not displayed correctly)
	// therefore we use fixed widths
	// TODO: still does not work correctly for multiple rows
	//   apparently only the first row determines the <td> width
	//   so if later rows are larger, they are still wrapped
	int width;

	QString fmtMsg = message;
	if (beginBold >= 0) {
		if (endBold >= 0)
			fmtMsg.insert(endBold, "</b>");
		else
			fmtMsg.append("</b>");
		fmtMsg.insert(beginBold, "<b>");

		QFont f = QToolTip::font();
		QFontMetrics fm(f);
		width = fm.width(message, beginBold);
		width += fm.width(message.mid(endBold));
		f.setBold(true);
		fm = QFontMetrics(f);
		width += fm.width(message.mid(beginBold, endBold - beginBold));
	} else {
		width = QFontMetrics(QToolTip::font()).width(message);
	}

	return QString("<tr><td style=\"color: %1\">%2</td><td width=\"%3\"><nobr>%4</nobr></td>").arg(textColors[type].name()).arg(pre).arg(width).arg(fmtMsg);
}

void LatexLogEntry::clear()
{
	file = "";
	type = LT_NONE;
	oldline = -1;
	logline = -1;
	message = "";
}


//===========================OutputFilter===============================
OutputFilter::OutputFilter() : QObject(),
	m_nOutputLines(0), m_log(QString())
{
}

OutputFilter::~ OutputFilter()
{
}

short OutputFilter::parseLine(const QString & /*strLine*/, short /*dwCookie*/)
{
	return 0;
}

bool OutputFilter::onTerminate()
{
	return true;
}

void OutputFilter::setSource(const QString &src)
{
	m_source = src;
	m_srcPath = QFileInfo(src).path();
}

bool OutputFilter::run(const QTextDocument *log)
{
	short sCookie = 0;
	QString s;
	//QFile f(logfile);

	m_log.clear();
	m_nOutputLines = 0;

	//if(f.open(QIODevice::ReadOnly)) {
	QString pt = log->toPlainText();
	QTextStream t(&pt, QIODevice::ReadOnly);
	while (!t.atEnd()) {
// 			KILE_DEBUG() << "line " << m_nOutputLines << endl;
		s = t.readLine();
		sCookie = parseLine(s, sCookie);
		++m_nOutputLines;

		m_log += s + '\n';
	}
	/*f.close();
	}
	else {
	QMessageBox::warning(0,"MakerX", tr("Cannot open log file; did you run LaTeX?"));
	return false;
	}*/

	return onTerminate();
}

/*!
Returns the zero based index of the currently parsed line in the output file.
*/
int OutputFilter::GetCurrentOutputLine() const
{
	return m_nOutputLines;
}

//=========================LatexOutputFilter===============================

LatexOutputFilter::LatexOutputFilter() : OutputFilter(),
	m_nErrors(0),
	m_nWarnings(0),
	m_nBadBoxes(0),
	m_nParens(0)
{
}

LatexOutputFilter::~ LatexOutputFilter()
{
}

bool LatexOutputFilter::OnPreCreate()
{
	m_nErrors = 0;
	m_nWarnings = 0;
	m_nBadBoxes = 0;

	return true;
}

bool LatexOutputFilter::fileExists(const QString &name)
{
	return absoluteFileName(name) != "";
}

QString LatexOutputFilter::absoluteFileName(const QString &name)
{
	static QFileInfo fi;
	if (m_filelookup.contains(name))
		return m_filelookup[name];

	if (QDir::isAbsolutePath(name)) {
		fi.setFile(name);
		if (fi.exists() && !fi.isDir()) {
			m_filelookup[name] = fi.absoluteFilePath();
			return m_filelookup[name];
		} else {
			m_filelookup[name] = "";
			return m_filelookup[name];
		}
	}

	fi.setFile(path() + '/' + name);
	if (fi.exists() && !fi.isDir()) {
		m_filelookup[name] = fi.absoluteFilePath();
		return m_filelookup[name];
	}

	fi.setFile(path() + '/' + name + ".tex");//m_extensions->latexDocumentDefault());
	if (fi.exists() && !fi.isDir()) {
		m_filelookup[name] = fi.absoluteFilePath();
		return m_filelookup[name];
	}

	/*	// try to determine the LaTeX source file
		QStringList extlist = m_extensions->latexDocuments().split(' ');
		for(QStringList::Iterator it = extlist.begin(); it!=extlist.end(); ++it) {
			fi.setFile(path() + '/' + name + (*it));
			if(fi.exists() && !fi.isDir()) {
			m_filelookup[name]=fi.absoluteFilePath();
			return m_filelookup[name];
			}
		}*/

	m_filelookup[name] = "";
	return m_filelookup[name];
}


// There are basically two ways to detect the current file TeX is processing:
//	1) Use \Input (i.c.w. srctex.sty or srcltx.sty) and \include exclusively. This will
//	cause (La)TeX to print the line ":<+ filename"  in the log file when opening a file,
//	":<-" when closing a file. Filenames pushed on the stack in this mode are marked
//	as reliable.
//
//	2) Since people will probably also use the \input command, we also have to be
//	to detect the old-fashioned way. TeX prints '(filename' when opening a file and a ')'
//	when closing one. It is impossible to detect this with 100% certainty (TeX prints many messages
//	and even text (a context) from the TeX source file, there could be unbalanced parentheses),
//	so we use a heuristic algorithm. In heuristic mode a ')' will only be considered as a signal that
//	TeX is closing a file if the top of the stack is not marked as "reliable".
//	Also, when scanning for a TeX error linenumber (which sometimes causes a context to be printed
//	to the log-file), updateFileStack is not called, helping not to pick up unbalanced parentheses
//	from the context.

/*!
 * Parses the given line for the start of new files or the end of
 * old files.
 */
void LatexOutputFilter::updateFileStack(const QString &strLine, short &dwCookie)
{
	//KILE_DEBUG() << "==LatexOutputFilter::updateFileStack()================" << endl;

	static QString strPartialFileName;

	switch (dwCookie) {
	//we're looking for a filename
	case Start :
	case HeuristicSearch :
	case ExpectingFileName :
	case InFileName :
	case InQuotedFileName :
		//TeX is opening a file
		if (strLine.startsWith(":<+ ")) {
// 				KILE_DEBUG() << "filename detected" << endl;
			//grab the filename, it might be a partial name (i.e. continued on the next line)
			strPartialFileName = strLine.mid(4).trimmed();

			//change the cookie so we remember we aren't sure the filename is complete
			dwCookie = FileName;
		}
		//TeX closed a file
		else if (strLine.startsWith(":<-")) {
			PRINT_FILE_STACK("pop1", m_stackFile.top().file());
			m_stackFile.pop();
			dwCookie = Start;
		} else {
			//fallback to the heuristic detection of filenames
			updateFileStackHeuristic2(strLine, dwCookie);
		}
		break;

	case FileName :
		//The partial filename was followed by '(', this means that TeX is signalling it is
		//opening the file. We are sure the filename is complete now. Don't call updateFileStackHeuristic
		//since we don't want the filename on the stack twice.
		if (strLine.startsWith('(') || strLine.startsWith("\\openout")) {
			//push the filename on the stack and mark it as 'reliable'
			m_stackFile.push(LOFStackItem(strPartialFileName, true));
			PRINT_FILE_STACK("pushed", strPartialFileName);
			strPartialFileName.clear();
			dwCookie = Start;
			updateFileStackHeuristic2(strLine, dwCookie);
		} else if (strLine.startsWith(":<-")) {
			// nothing to do file was immediately closed again
			dwCookie = Start;
		}
		//The partial filename was followed by an TeX error, meaning the file doesn't exist.
		//Don't push it on the stack, instead try to detect the error.
		else if (strLine.startsWith('!')) {
// 				KILE_DEBUG() << "oops!" << endl;
			dwCookie = Start;
			strPartialFileName.clear();
			detectError(strLine, dwCookie);
		} else if (strLine.startsWith("No file")) {
// 				KILE_DEBUG() << "No file: " << strLine << endl;
			dwCookie = Start;
			strPartialFileName.clear();
			detectWarning(strLine, dwCookie);
		}
		//Partial filename still isn't complete.
		else {
// 				KILE_DEBUG() << "\tpartial file name, adding" << endl;
			strPartialFileName = strPartialFileName + strLine.trimmed();
		}
		break;

	default:
		break;
	}
}

bool LatexOutputFilter::likelyNoFileStart(const QString &s, const QChar &nextChar)
{
	if (s.length() < 2) {
		if (nextChar == ')') return true; // a (r) string -> likely no file
		else return false; // can't tell because it may be partial
	}

	QChar c0 = s.at(0);
	QChar c1 = s.at(1);
	if (c0 == '/') return false;  // abs. linux filename
	if (c0.isLetter() && c1 == ':') return false;  // abs. win filename
	if (c0 == '.' && (c1 == '/' || c1 == '\\')) return false;  // rel. filename
	return true;
}

// returns true if the given string exists as a file or ends with an extension of 1-4 characters, e.g. ".tex" or ".jpeg"
bool LatexOutputFilter::fileNameLikelyComplete(const QString &partialFileName)
{
	static QRegExp extensionRx(".*\\.\\w{1,4}$");
	return QFileInfo(partialFileName).exists() || extensionRx.exactMatch(partialFileName);
}

void LatexOutputFilter::updateFileStackHeuristic2(const QString &strLine, short &dwCookie)
{
	static QString partialFileName;
	if (dwCookie == Start) partialFileName.clear();

	QChar c;
	int fnStart = 0;
	for (int i = 0; i < strLine.length(); i++) {
		// if (!partialFileName.isEmpty()) qDebug() << partialFileName;
		c = strLine.at(i);
		switch (dwCookie) {
		case Start:
			if (c == '(') {
				dwCookie = ExpectingFileName;
				continue;
			}
			if (c == ')') {
				if (m_stackFile.count() >= 1 && !m_stackFile.top().reliable()) {
					PRINT_FILE_STACK("pop2", m_stackFile.top().file());
					m_stackFile.pop();
				}
			}
			break;
		case ExpectingFileName:
			if (c == ')') {
				dwCookie = Start;
				continue;
			} else if (c == '"') {
				dwCookie = InQuotedFileName;
				fnStart = i + 1;
				continue;
			} else {
				dwCookie = InFileName;
				fnStart = i;
				continue;
			}
			break;
		case InQuotedFileName:
			if (c == '"') {
				partialFileName += strLine.mid(fnStart, i - fnStart);
				m_stackFile.push(LOFStackItem(partialFileName));
				PRINT_FILE_STACK("push1", partialFileName);
				partialFileName.clear();
				dwCookie = Start;
				continue;
			}
			break;
		case InFileName:
			if (c == ')') {
				partialFileName += strLine.mid(fnStart, i - fnStart);
				fnStart = i;
				// qDebug() << strLine << partialFileName << fileNameLikelyComplete(partialFileName);
				// we can only guess if the ')' is in the filename or terminates it
				if (fileNameLikelyComplete(partialFileName) || likelyNoFileStart(partialFileName, c)) {
					partialFileName.clear(); // we don't have to push the filename, because it's directly closed again
					dwCookie = Start;
					continue;
				}
			}
			if (c.isSpace() || c == '(') {
				partialFileName += strLine.mid(fnStart, i - fnStart);
				fnStart = i;
				// we can only guess if the space is in the filename or terminates it
				if (fileNameLikelyComplete(partialFileName) || likelyNoFileStart(partialFileName, c)) {
					// We need likelyNoFileStart together with the space a an abort criterion for
					// file scanning in normal text.
					// It may seem strange at first, that we also push if likelyNoFileStart, but
					// we have to put something on the stack (assuming there is a corresponding
					// closing bracket - the more likely case than a missing bracket). Otherwise
					// we would erronously step down in the stack.
					// The pushed value (even if its false) will only make for a local error, but
					// is may even be correct since likelyNoFileStart is also just a heuristic.
					m_stackFile.push(LOFStackItem(partialFileName));
					PRINT_FILE_STACK("push2", partialFileName);
					partialFileName.clear();
					if (c == '(') {
						dwCookie = ExpectingFileName;
					} else {
						dwCookie = Start;
					}
					continue;
				}
			}
		}
	}
	// special handling at end of line:
	if (dwCookie == InFileName) {
		partialFileName += strLine.mid(fnStart);
		if (strLine.length() < 78  // a)  line is not full: file name must be at end;
		        || fileExists(partialFileName) // or b) if line is full and the file exists: assume at filename end, otherwise continue with next line
		   ) {
			m_stackFile.push(LOFStackItem(partialFileName));
			PRINT_FILE_STACK("push3", partialFileName);
			partialFileName.clear();
			dwCookie = Start;
		}
	} else if (dwCookie == InQuotedFileName) {
		partialFileName += strLine.mid(fnStart);
	}
}

/*** this is the old heuristics. It's unused right now and will be removed in short. For the moment it remains for testing ***/
void LatexOutputFilter::updateFileStackHeuristic(const QString &strLine, short &dwCookie)
{
	//KILE_DEBUG() << "==LatexOutputFilter::updateFileStackHeuristic()================";
	static QString strPartialFileName;
	static bool quotedFileName = false;
	bool expectFileName = (dwCookie == HeuristicSearch);
	int index = 0;

	// handle special case (bug fix for 101810)
	if (expectFileName && strLine.length() > 0 && strLine[0] == ')') {
		m_stackFile.push(LOFStackItem(strPartialFileName));
		PRINT_FILE_STACK("push", strPartialFileName);
		expectFileName = false;
		dwCookie = Start;
	}

	//scan for parentheses and grab filenames
	for (int i = 0; i < strLine.length(); ++i) {
		/*
		We're expecting a filename. If a filename really ends at this position one of the following must be true:
			1) Next character is a space, the file before the space exists and no " was read
			historical notes: Next character is a space (indicating the end of a filename (yes, there can't spaces in the
			path, this is a TeX limitation).
		comment by tbraun: there is a workround \include{{"file name"}} according to http://groups.google.com/group/comp.text.tex/browse_thread/thread/af873534f0644e4f/cd7e0cdb61a8b837?lnk=st&q=include+space+tex#cd7e0cdb61a8b837,
		but this is currently not supported by kile.

			2) We're at the end of the line, the filename is probably continued on the next line.
			3) The TeX was closed already, signalled by the ')'.
		*/

		bool isLastChar = (i + 1 == strLine.length());
		bool nextIsTerminator = isLastChar
		                        ? false
		                        : ( (strLine[i + 1].isSpace()
		                             && !quotedFileName
		                             && fileExists(strPartialFileName + strLine.mid(index, i - index + 1)))
		                            || strLine[i + 1] == ')');

		if (expectFileName && (isLastChar || nextIsTerminator)) {
			//KILE_DEBUG() << "Update the partial filename " << strPartialFileName << endl;
			strPartialFileName =  strPartialFileName + strLine.mid(index, i - index + 1);

			if (strPartialFileName.startsWith('"')) strPartialFileName.remove(0, 1), quotedFileName = true;
			if (strPartialFileName.endsWith('"')) strPartialFileName.remove(strPartialFileName.length() - 1, 1);

			if (strPartialFileName.isEmpty()) { // nothing left to do here
				continue;
			}

			//FIXME: improve these heuristics
			if ((isLastChar && (i < 78)) || nextIsTerminator || fileExists(strPartialFileName)) {
				m_stackFile.push(LOFStackItem(strPartialFileName));
				PRINT_FILE_STACK("push 4", strPartialFileName);
				// KILE_DEBUG() << "\tpushed (i = " << i << " length = " << strLine.length() << "): " << strPartialFileName << endl;
				expectFileName = false;
				dwCookie = Start;
			}
			//Guess the filename is continued on the next line, only if the current strPartialFileName does not exist, see bug # 162899
			else if (isLastChar) {
				if (fileExists(strPartialFileName)) {
					m_stackFile.push(LOFStackItem(strPartialFileName));
					PRINT_FILE_STACK("push 5", strPartialFileName);
					//KILE_DEBUG() << "pushed (i = " << i << " length = " << strLine.length() << "): " << strPartialFileName << endl;
					expectFileName = false;
					dwCookie = Start;
				} else {
					//KILE_DEBUG() << "Filename spans more than one line." << endl;
					dwCookie = HeuristicSearch;
				}
			}
			//bail out
			else {
				dwCookie = Start;
				strPartialFileName.clear();
				expectFileName = false;
				quotedFileName = false;
			}
		}
		//TeX is opening a file
		else if (strLine[i] == '(') {
			//we need to extract the filename
			expectFileName = true;
			strPartialFileName.clear();
			quotedFileName = false;
			dwCookie = Start;

			//this is were the filename is supposed to start
			index = i + 1;
		}
		//TeX is closing a file
		else if (strLine[i] == ')') {
			// KILE_DEBUG() << "\tpopping : " << m_stackFile.top().file() << endl;
			//If this filename was pushed on the stack by the reliable ":<+-" method, don't pop
			//a ":<-" will follow. This helps in preventing unbalanced ')' from popping filenames
			//from the stack too soon.
			if (m_stackFile.count() > 1 && !m_stackFile.top().reliable()) {
				PRINT_FILE_STACK("pop3", m_stackFile.top().file());
				m_stackFile.pop();
			} else {
				//KILE_DEBUG() << "\t\toh no, forget about it!";
			}
		}
	}
}

/*!
 * Forwards the currently parsed item to the item list.
 */
void LatexOutputFilter::flushCurrentItem()
{
	//KILE_DEBUG() << "==LatexOutputFilter::flushCurrentItem()================" << endl;
	int nItemType = m_currentItem.type;

	while ( m_stackFile.count() > 0 && (!fileExists(m_stackFile.top().file())) && (m_stackFile.count() > 1)) {
		PRINT_FILE_STACK("pop4", m_stackFile.top().file());
		m_stackFile.pop();
	}

	m_currentItem.file = m_stackFile.count() <= 0 ? "" : absoluteFileName(m_stackFile.top().file());

	switch (nItemType) {
	case LT_ERROR:
		++m_nErrors;
		m_infoList.push_back(m_currentItem);
		//qDebug() << "Flushing Error in" << m_currentItem.file << "@" << m_currentItem.oldline << " reported in line " << m_currentItem.logline <<  endl;
		break;

	case LT_WARNING:
		++m_nWarnings;
		m_infoList.push_back(m_currentItem);
		//qDebug() << "Flushing Warning in " << m_currentItem.file << "@" << m_currentItem.oldline << " reported in line " << m_currentItem.logline << endl;
		break;

	case LT_BADBOX:
		++m_nBadBoxes;
		m_infoList.push_back(m_currentItem);
		//qDebug() << "Flushing BadBox in " << m_currentItem.file << "@" << m_currentItem.oldline << " reported in line " << m_currentItem.logline << endl;
		break;

	default:
		break;
	}
	m_currentItem.clear();
}


/*!
 * detect a Latex3 info message
 *
 * An info message has the following pattern
 * .................................................
 * . pkgname info: "message"
 * .
 * . Text
 * .................................................
 *
 * \return true if the line could be processed.
 */
bool LatexOutputFilter::detectLatex3Info(const QString &strLine, short &dwCookie)
{
	switch (dwCookie) {
	case Start:
		if (strLine.startsWith("........................................")) {
			dwCookie = Latex3Info;
			m_currentItem.message = QString();
			m_currentItem.logline = GetCurrentOutputLine();
			m_currentItem.type = LT_INFO;
			return true;
		}
		return false;
	case Latex3Info:
		if (strLine.startsWith("........................................") || !strLine.startsWith('.')) {
			// regular or unexpected end.
			flushCurrentItem();
			dwCookie = Start;
		} else {
			QString line = strLine.mid(1).trimmed();    // discard first char (which is '.') and spaces
			if (line.length() > 0) {
				if (m_currentItem.message.length() > 0)
					m_currentItem.message.append(' ');
			}
		}
		return true;
	}
	qDebug("unhandled cookie state in detectLatex3Info");  // should not happen
	return false;
}

bool LatexOutputFilter::detectError(const QString &strLine, short &dwCookie)
{
	//KILE_DEBUG() << "==LatexOutputFilter::detectError(" << strLine.length() << ")================" << endl;

	bool found = false, flush = false;

	static QRegExp reLaTeXError("^! (?:Lua|La)TeX Error(?: \\<\\\\directlua \\>:(?:[0-9]*))?: (.*)$", Qt::CaseInsensitive);
	static QRegExp rePDFLaTeXError("^Error: (?:lua|pdf)latex (.*)$", Qt::CaseInsensitive);
	static QRegExp reTeXError("^! (.*)$");
	static QRegExp rePackageError("^! Package (.*) Error:(.*)$", Qt::CaseInsensitive);
	static QRegExp reLatex3Error("^!\\s+(\\S.*)");
	static QRegExp reLatex3ErrorHeader("^1\\s*(.*error:\\s*.*)", Qt::CaseInsensitive);
	static QRegExp reLineNumber("^(\\.{3} )?l\\.([0-9]+)(.*)");

	switch (dwCookie) {
	case Start :
		if (strLine.startsWith("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")) {
			found = true;
			dwCookie = Latex3Error;
			m_currentItem.message = QString();
			m_currentItem.logline = GetCurrentOutputLine();
		} else if (reLaTeXError.indexIn(strLine) != -1) {
			//KILE_DEBUG() << "\tError : " <<  reLaTeXError.cap(1) << endl;
			m_currentItem.message = reLaTeXError.cap(1);
			found = true;
		} else if (rePDFLaTeXError.indexIn(strLine) != -1) {
			//KILE_DEBUG() << "\tError : " <<  rePDFLaTeXError.cap(1) << endl;
			m_currentItem.message = rePDFLaTeXError.cap(1);
			found = true;
		} else if (reTeXError.indexIn(strLine) != -1) {
			//KILE_DEBUG() << "\tError : " <<  reTeXError.cap(1) << endl;
			m_currentItem.message = reTeXError.cap(1);
			found = true;
		} else if (rePackageError.indexIn(strLine) != -1) {
			//KILE_DEBUG() << "\tError : " <<  reTeXError.cap(1) << endl;
			m_currentItem.message = rePackageError.cap(1) + ":" + rePackageError.cap(2);
			found = true;
		}
		if (found && dwCookie != Latex3Error) { // already handled for Latex3Error above
			dwCookie = strLine.endsWith('.') ? LineNumber : Error;
			m_currentItem.logline = GetCurrentOutputLine();
		}
		break;

	case Error :
		//KILE_DEBUG() << "\tError (cont'd): " << strLine << endl;
		if (strLine.endsWith('.')) {
			dwCookie = LineNumber;
			m_currentItem.message = m_currentItem.message + strLine;
		} else if (GetCurrentOutputLine() - m_currentItem.logline > 3) {
			//kWarning() << "\tBAILING OUT: error description spans more than three lines" << endl;
			dwCookie = Start;
			flush = true;
		}
		break;
	case Latex3Error:
		if (!strLine.startsWith('!') || strLine.startsWith("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!") || strLine.startsWith("!.......................................")) {
			found = false;
			flush = false;
			dwCookie = Latex3ErrorEnd;
		} else {
			if (strLine.contains("documentation for further information.") || strLine.contains("Type <return> to continue.")) {
				// ignore these lines:
				//  ! See the mymodule documentation for further information.
				// 	! Type <return> to continue.
				found = true;
			} else if (reLatex3ErrorHeader.indexIn(strLine) != -1) {
				if (!m_currentItem.message.isEmpty()) m_currentItem.message += ' ';
				m_currentItem.message += reLatex3ErrorHeader.cap(1);
				found = true;
			} else if (reLatex3Error.indexIn(strLine) != -1) {
				if (!m_currentItem.message.isEmpty()) m_currentItem.message += ' ';
				m_currentItem.message += reLatex3Error.cap(1);
				found = true;
			}
		}
		break;
	case Latex3ErrorEnd:
		if (strLine.trimmed().isEmpty()) {
			found = true;
		} else {
			dwCookie = LineNumber;
		}
        break; // was probably forgotten
	case LineNumber :
		//KILE_DEBUG() << "\tLineNumber " << endl;
		if (reLineNumber.indexIn(strLine) != -1) {
			dwCookie = Start;
			flush = true;
			//KILE_DEBUG() << "\tline number: " << reLineNumber.cap(1) << endl;
			m_currentItem.oldline = reLineNumber.cap(2).toInt();
			m_currentItem.message = m_currentItem.message + reLineNumber.cap(3);
		} else if (GetCurrentOutputLine() - m_currentItem.logline > 10) {
			dwCookie = Start;
			flush = true;
			//kWarning() << "\tBAILING OUT: did not detect a TeX line number for an error" << endl;
			m_currentItem.oldline = 0;
		}
		break;

	default :
		break;
	}

	if (found) {
		m_currentItem.type = LT_ERROR;
	}

	if (flush) {
		m_currentItem.message = m_currentItem.message.simplified();
		flushCurrentItem();
	}

	return found;
}

bool LatexOutputFilter::detectWarning(const QString &strLine, short &dwCookie)
{
	//KILE_DEBUG() << "==LatexOutputFilter::detectWarning(" << strLine.length() << ")================" << endl;

	bool found = false, flush = false;
	QString warning;

	static QRegExp reLaTeXWarning("^(((! )?(La|pdf|Lua)TeX)|Package|Class) .*Warning.*:(.*)", Qt::CaseInsensitive);
	static QRegExp reLatex3Warning("^\\*\\s+(\\S.*)");
	static QRegExp reLatex3WarningHeader("^\\*\\s*(.*warning:\\s*.*)", Qt::CaseInsensitive);
	static QRegExp reNoFile("^No file (.*)");
	static QRegExp reNoAsyFile("File .* does not exist."); // FIXME can be removed when http://sourceforge.net/tracker/index.php?func=detail&aid=1772022&group_id=120000&atid=685683 has promoted to the users

	switch (dwCookie) {
	//detect the beginning of a warning
	case Start :
		if (strLine.startsWith("****************************************")) {
			found = true;
			dwCookie = MaybeLatex3Warning; // cannot decide yet, some packages just insert a starred line as separator. A Latex3Warning will start the next line with a star (will be checked later on).
			m_currentItem.message = QString();
			m_currentItem.logline = GetCurrentOutputLine();
		} else if (reLaTeXWarning.indexIn(strLine) != -1) {
			warning = reLaTeXWarning.cap(5);
			//KILE_DEBUG() << "\tWarning found: " << warning << endl;
			found = true;
			dwCookie = Start;
			m_currentItem.logline = GetCurrentOutputLine();
			//do we expect a line number?
			flush = detectLaTeXLineNumber(warning, dwCookie, strLine.length());
			m_currentItem.message = warning;
		} else if (reNoFile.indexIn(strLine) != -1) {
			found = true;
			flush = true;
			m_currentItem.oldline = (0);
			m_currentItem.message = (reNoFile.cap(0));
			m_currentItem.logline = GetCurrentOutputLine();
		} else if (reNoAsyFile.indexIn(strLine) != -1) {
			found = true;
			flush = true;
			m_currentItem.oldline = (0);
			m_currentItem.message = (reNoAsyFile.cap(0));
			m_currentItem.logline = GetCurrentOutputLine();
		}

		break;

	//warning spans multiple lines, detect the end
	case Warning :
		warning = m_currentItem.message + strLine;
		//KILE_DEBUG() << "'\tWarning (cont'd) : " << warning << endl;
		flush = detectLaTeXLineNumber(warning, dwCookie, strLine.length());
		m_currentItem.message = (warning);
		break;
	case MaybeLatex3Warning:
		if (!strLine.startsWith('*')) {
			found = false;
			flush = false;
			dwCookie = Start;
			break;
		}
		// no break,
        [[gnu::fallthrough]];
	case Latex3Warning:
		if (!strLine.startsWith('*') || strLine.startsWith("****************************************")) {
			found = false;
			flush = true;
			dwCookie = Start;
		} else {
			if (reLatex3WarningHeader.indexIn(strLine) != -1) {
				if (!m_currentItem.message.isEmpty()) m_currentItem.message += ' ';
				m_currentItem.message += reLatex3WarningHeader.cap(1);
				found = true;
			} else if (reLatex3Warning.indexIn(strLine) != -1) {
				if (!m_currentItem.message.isEmpty()) m_currentItem.message += ' ';
				m_currentItem.message += reLatex3Warning.cap(1);
				found = true;
			}
		}
		break;
	default:
		break;
	}

	if (found) {
		m_currentItem.type = LT_WARNING;
	}

	if (flush) {
		m_currentItem.message = m_currentItem.message.simplified();
		flushCurrentItem();
	}

	return found;
}

bool LatexOutputFilter::detectLaTeXLineNumber(QString &warning, short &dwCookie, int len)
{
	//KILE_DEBUG() << "==LatexOutputFilter::detectLaTeXLineNumber(" << warning.length() << ")================" << endl;

	static QRegExp reLaTeXLineNumber("(.*) on input[ ]?line ([0-9]+)\\.$", Qt::CaseInsensitive);
	static QRegExp reInternationalLaTeXLineNumber("(.*)([0-9]+)\\.$", Qt::CaseInsensitive);
	if ((reLaTeXLineNumber.indexIn(warning) != -1) || (reInternationalLaTeXLineNumber.indexIn(warning) != -1)) {
		//KILE_DEBUG() << "een" << endl;
		m_currentItem.oldline = (reLaTeXLineNumber.cap(2).toInt());
		warning = reLaTeXLineNumber.cap(1);
		dwCookie = Start;
		return true;
	} else if (warning.endsWith('.')) {
		//KILE_DEBUG() << "twee" << endl;
		m_currentItem.oldline = (0);
		dwCookie = Start;
		return true;
	}
	//bailing out, did not find a line number
	else if ((GetCurrentOutputLine() - m_currentItem.logline > 4) || (len == 0)) {
		//KILE_DEBUG() << "drie current " << GetCurrentOutputLine() << " " <<  m_currentItem.outputLine() << " len " << len << endl;
		m_currentItem.oldline = (0);
		dwCookie = Start;
		return true;
	}
	//error message is continued on the other line
	else {
		//KILE_DEBUG() << "vier" << endl;
		dwCookie = Warning;
		return false;
	}
}

bool LatexOutputFilter::detectBadBox(const QString &strLine, short &dwCookie)
{
	//KILE_DEBUG() << "==LatexOutputFilter::detectBadBox(" << strLine.length() << ")================" << endl;

	bool found = false, flush = false;
	QString badbox;

	static QRegExp reBadBox("^(Over|Under)(full \\\\[hv]box .*)", Qt::CaseInsensitive);

	switch (dwCookie) {
	case Start :
		if (reBadBox.indexIn(strLine) != -1) {
			found = true;
			dwCookie = ExpectingBadBoxTextQoute;
			badbox = strLine;
			flush = detectBadBoxLineNumber(badbox, dwCookie, strLine.length());
			m_currentItem.message = (badbox);
		}
		break;

	case BadBox :
		badbox = m_currentItem.message + strLine;
		flush = detectBadBoxLineNumber(badbox, dwCookie, strLine.length());
		m_currentItem.message = (badbox);
		break;

	default:
		break;
	}

	if (found) {
		m_currentItem.type = (LT_BADBOX);
		m_currentItem.logline = GetCurrentOutputLine();
	}

	if (flush) {
		flushCurrentItem();
	}

	return found;
}

// Badboxes may have and additional line displaying the problematic text:
//   Underfull \hbox (badness 10000) in paragraph at lines 827--831
//   \T1/cmr/m/n/12 against it (de-pend-ing
// We use the font definition pattern at the start to identify the line as such
//
bool LatexOutputFilter::isBadBoxTextQuote(const QString &strLine)
{
	static QRegExp reBadBoxTextQoute("\\\\\\S+/\\S+/\\S+/\\S+/");
	return (reBadBoxTextQoute.indexIn(strLine) >= 0);
}

bool LatexOutputFilter::detectBadBoxLineNumber(QString &strLine, short &dwCookie, int len)
{
	//KILE_DEBUG() << "==LatexOutputFilter::detectBadBoxLineNumber(" << strLine.length() << ")================" << endl;

	static QRegExp reBadBoxLines("(.*) at lines ([0-9]+)--([0-9]+)", Qt::CaseInsensitive);
	static QRegExp reBadBoxLine("(.*) at line ([0-9]+)", Qt::CaseInsensitive);
	//Use the following only, if you know how to get the source line for it.
	// This is not simple, as TeX is not reporting it.
	static QRegExp reBadBoxOutput("(.*)has occurred while \\\\output is active^", Qt::CaseInsensitive);

	if (reBadBoxLines.indexIn(strLine) != -1) {
		dwCookie = ExpectingBadBoxTextQoute;
		strLine = reBadBoxLines.cap(1);
		int n1 = reBadBoxLines.cap(2).toInt();
		int n2 = reBadBoxLines.cap(3).toInt();
		m_currentItem.oldline = (n1 < n2 ? n1 : n2);
		return true;
	} else if (reBadBoxLine.indexIn(strLine) != -1) {
		dwCookie = ExpectingBadBoxTextQoute;
		strLine = reBadBoxLine.cap(1);
		m_currentItem.oldline = (reBadBoxLine.cap(2).toInt());
		//KILE_DEBUG() << "\tBadBox@" << reBadBoxLine.cap(2) << "." << endl;
		return true;
	} else if (reBadBoxOutput.indexIn(strLine) != -1) {
		dwCookie = ExpectingBadBoxTextQoute;
		strLine = reBadBoxLines.cap(1);
		m_currentItem.oldline = (0);
		return true;
	}
	//bailing out, did not find a line number
	else if ((GetCurrentOutputLine() - m_currentItem.logline > 3) || (len == 0)) {
		dwCookie = Start;
		m_currentItem.oldline = (0);
		return true;
	} else {
		dwCookie = BadBox;
	}

	return false;
}

short LatexOutputFilter::parseLine(const QString &strLine, short dwCookie)
{
	//KILE_DEBUG() << "==LatexOutputFilter::parseLine(" << strLine.length() << ")================" << endl;

	switch (dwCookie) {

	case ExpectingBadBoxTextQoute:
		if (isBadBoxTextQuote(strLine)) {
			dwCookie = Start;
			break; // next line
		} else {
			dwCookie = Start; // reset and treat currently independently
		}
	// fall-through - no break
	case Start :
		if (detectBadBox(strLine, dwCookie))
			break;
		if (detectWarning(strLine, dwCookie))
			break;
		if (detectLatex3Info(strLine, dwCookie))
			break;
		if (detectError(strLine, dwCookie))
			break;
		updateFileStack(strLine, dwCookie);
		break;

	case Warning :
	case Latex3Warning :
		detectWarning(strLine, dwCookie);
		break;

	case Latex3Info :
		detectLatex3Info(strLine, dwCookie);
		break;

	case Error :
	case Latex3Error :
	case Latex3ErrorEnd :
	case LineNumber :
		detectError(strLine, dwCookie);
		break;

	case BadBox :
		detectBadBox(strLine, dwCookie);
		break;

	case FileName :
	case HeuristicSearch :
	case ExpectingFileName :
	case InFileName :
	case InQuotedFileName :
		updateFileStack(strLine, dwCookie);
		break;

	default:
		dwCookie = Start;
		break;
	}

	return dwCookie;
}

// split old Run() into three parts
// - Run()             : parse the logfile
// - updateInfoLists() : needed by QuickPreview
// - sendProblems()    : emit signals
//
// dani 18.02.2005

bool LatexOutputFilter::run(const QTextDocument *log)
{
	m_filelookup.clear();
	m_infoList.clear();
	m_nErrors = m_nWarnings = m_nBadBoxes = m_nParens = 0;
	m_stackFile.clear();
	QString mainfile = QFileInfo(source()).fileName();
	m_stackFile.push(LOFStackItem(mainfile, true));
	PRINT_FILE_STACK("push", mainfile);

	return OutputFilter::run(log);
}
/*
void LatexOutputFilter::updateInfoLists(const QString &texfilename, int selrow, int docrow)
{
	// get a short name for the original tex file
	QString filename = "./" + QFileInfo(texfilename).fileName();
	setSource(texfilename);

	//print detailed error info
	for(int i = 0; i < m_infoList.count(); ++i) {
		// perhaps correct filename and line number in OutputInfo
		OutputInfo *info = &(*m_infoList)[i];
		info->setSource(filename);

		int linenumber = selrow + info->sourceLine() - docrow;
		if(linenumber < 0) {
			linenumber = 0;
		}
		info->setSourceLine(linenumber);
	}
}

void LatexOutputFilter::sendProblems()
{
	QString message;
	int type;
	QList<KileWidget::LogWidget::ProblemInformation> problemList;

	//print detailed error info
	for(QList<LatexOutputInfo>::iterator i = m_infoList.begin();
	                                     i != m_infoList.end(); ++i) {
		LatexOutputInfo info = *i;
		message = info.source() + ':' + QString::number(info.sourceLine()) + ':' + info.message();
		switch(info.type()) {
			case LatexOutputInfo::LT_BADBOX:
				type = KileTool::ProblemBadBox;
				break;
			case LatexOutputInfo::LT_ERROR:
				type = KileTool::ProblemError;
				break;
			case LatexOutputInfo::LT_WARNING:
				type = KileTool::ProblemWarning;
				break;
			default:
				type = KileTool::Info;
				break;
		}
		KileWidget::LogWidget::ProblemInformation problem;
		problem.type = type;
		problem.message = message;
		problem.outputInfo = info;
		problemList.push_back(problem);
	}
	emit(problems(problemList));
}
*/
