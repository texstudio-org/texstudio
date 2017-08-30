#include "smallUsefulFunctions.h"
#include "qdocumentline_p.h"
#include "qdocument.h"
#include <QBuffer>
#include "latexparser/latexparser.h"


const int RUNAWAYLIMIT=30; // limit lines to process multi-line arguments in order to prevent processing to the end of document if the arbument is unclosed


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
    if(result.startsWith("\""))
        result=result.mid(1);
    if(result.endsWith("\""))
        result.chop(1);
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

/*!
 * Searches for the first latex command in line starting at offset. Comments are ignored.
 *
 * \warning obsolete with lexer-based token system
 * \param cmd the command name, e.g. \section
 * \param args a list of the arguments including their brackets, e.g. "[arg1]", "{arg2}"
 * \param argStarts a list of the starting positions of the arguments in line (if not needed, you can pass 0 in)
 *
 * \return Returns the starting position of cmd in line, or -1 if no command was found.
 */
int findCommandWithArgs(const QString &line, QString &cmd, QStringList &args, QList<int> *argStarts, int offset, bool parseComment)
{
	// true means that a command is found, with or without arguments ...
	// otherwise a command before the interesting command leads to quiting the loop
	static QRegExp rxCmd("\\\\\\w+\\*?");
	static QRegExp rxComment("(^|[^\\\\])%");
	int cmdStart = rxCmd.indexIn(line, offset);
	int commentStart = parseComment ? -1 : rxComment.indexIn(line);
	if (cmdStart == -1 || (commentStart >= 0 && commentStart < cmdStart)) {
		return -1;  // no command found
	}
	cmd = rxCmd.cap(0);
	LatexParser::resolveCommandOptions(line, cmdStart, args, argStarts);
	return cmdStart;
}

/*!
 * returns the position of the first command token after offset
 * args  Tokenlist with all token after command at the same level (top level args, no content)
 *
 */
int findCommandWithArgsFromTL(const TokenList &tl, Token &cmd, TokenList &args, int offset, bool parseComment)
{
	int result = -1;
	for (int i = 0; i < tl.length(); i++) {
		cmd = tl.at(i);
		if (!parseComment && cmd.type == Token::comment)
			return -1;
		if (i < offset)
			continue;
        if (cmd.type == Token::commandUnknown){
            return i;
        }
		if (cmd.type != Token::command)
			continue;
		// Token is command
		result = i;
		// now, collect arguments
		i++;
        int level = cmd.level+1;
        QDocumentLineHandle *t_dlh=cmd.dlh;
        int t_end=cmd.start+cmd.length;
		for (; i < tl.length(); i++) {
			Token tk = tl.at(i);
			if (tk.type == Token::comment)
				break;
			if (tk.level < level)
				break;
			if (tk.level == level) {
                if( (tk.start>=t_end) || (tk.dlh!=t_dlh) ){
                    args.append(tk);
                    t_dlh=tk.dlh;
                    t_end=tk.start+tk.length;
                }
			}
		}
		break;
	}
	return result;
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



/*!
 * returns the content (i.e. String without brackets) of the index-th argument
 */
QString ArgumentList::argContent(int index) const
{
	return LatexParser::removeOptionBrackets(this->at(index));
}

/*!
 * returns the content (i.e. String without brackets) index-th argument of the
 * specified type
 */
QString ArgumentList::argContent(int index, ArgumentList::ArgType type) const
{
	for (int i = 0; i < size(); i++) {
		if (argType(i) == type) {
			if (index == 0)
				return argContent(i);
			else
				index--;
		}
	}
	return QString();
}

/*!
 * returns the type of the index-th argument
 */
ArgumentList::ArgType ArgumentList::argType(int index) const
{
	return (this->at(index)[0] == '[') ? Optional : Mandatory;
}

/*!
 * returns the number of arguments of the specified type
 */
int ArgumentList::count(ArgumentList::ArgType type) const
{
	int count = 0;
	for (int i = 0; i < size(); i++) {
		if (argType(i) == type) {
			count++;
		}
	}
	return count;
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
	QLabel lLabel(0, Qt::ToolTip);
	lLabel.setFont(QToolTip::font());
	lLabel.setMargin(1 + lLabel.style()->pixelMetric(QStyle::PM_ToolTipLabelFrameWidth, 0, &lLabel));
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

QString getArg(const TokenList &tl, Token::TokenType type){
    for (int i = 0; i < tl.length(); i++) {
        Token tk = tl.at(i);

        if (tk.subtype==type) {
            QString result;
            QString line=tk.getText();
            if (Token::tkBraces().contains(tk.type)) {
                result = line.mid(1, line.length() - 2);
            }
            if (Token::tkOpen().contains(tk.type)) {
                result = line.mid( 1) + findRestArg(tk.dlh, Token::opposite(tk.type), RUNAWAYLIMIT);
            }
            if (Token::tkClose().contains(tk.type)) {
                result = line.left(line.length()-1);
            }
            if (result.isEmpty()) {
                result = line;
            }
            return result;
        }
    }
    return QString();
}

QString getArg(TokenList tl, QDocumentLineHandle *dlh, int argNumber, ArgumentList::ArgType type,bool enableMultiLineSearch)
{
	// argNumber 0 -> first argument
    QDocument *doc=dlh->document();
    int lineNr=doc->indexOf(dlh);

	// do only create the relevant token sets once and keep them around for later use for speedup.
	static const QSet<Token::TokenType> tokensForMandatoryArg = QSet<Token::TokenType>()
														  << Token::braces
														  << Token::word
														  << Token::command
														  << Token::commandUnknown
														  << Token::number
														  << Token::openBrace;
	static const QSet<Token::TokenType> tokensForMandatoryBraceArg = QSet<Token::TokenType>() << Token::braces;
	static const QSet<Token::TokenType> tokensForOptionalArg = QSet<Token::TokenType>() << Token::squareBracket << Token::openSquare;

	const QSet<Token::TokenType> *searchTokens = 0;

	if (type == ArgumentList::Mandatory) {
		searchTokens = &tokensForMandatoryArg;
	} else if (type == ArgumentList::MandatoryWithBraces) {
		searchTokens = &tokensForMandatoryBraceArg;
	} else {
		searchTokens = &tokensForOptionalArg;
	}
	REQUIRE_RET(searchTokens, QString());

    int cnt=0;
	int k = 0;
    int level=1;
    if(!tl.isEmpty()){
        level=tl.first().level;
    }
    while( (lineNr)<doc->lineCount() && cnt<RUNAWAYLIMIT){
        QString line = dlh->text();
        for (int i = 0; i < tl.length(); i++) {
            Token tk = tl.at(i);
            if(tk.level>level)
                continue; //only use tokens from the same option-level


            if (searchTokens->contains(tk.type)) {
                if(tk.argLevel==-1)
                    continue; // token is part of argument
                QString result;
                if (Token::tkBraces().contains(tk.type) || Token::tkOpen().contains(tk.type) || Token::tkClose().contains(tk.type)) {
                    if (Token::tkOpen().contains(tk.type)) {
                        int len=tk.innerStart()+ tk.innerLength();
                        if(len<line.length()){
                            // comment ends line
                            result=line.mid(tk.innerStart(), tk.innerLength());
                        }else{
                            // line break acts as space in latex
                            result=line.mid(tk.innerStart(), tk.innerLength())+" ";
                        }
                        result.append(findRestArg(dlh, Token::opposite(tk.type), RUNAWAYLIMIT));
                    }else{
                        result = line.mid(tk.innerStart(), tk.innerLength());
                    }
                }
                if (result.isEmpty()) {
                    result = line.mid(tk.start, tk.length);
                }
                if (k == argNumber)
                    return result;
                else
                    k++;
			} else {
                if (type == ArgumentList::Optional)
                    return QString(); //optional argument can't follow mandatory one
                if (type==ArgumentList::MandatoryWithBraces && tk.type!=Token::squareBracket){
                    //mandatorywithbraces can't have other arguments except optional
                    return QString();
                }
			}
        }
        if(!enableMultiLineSearch)
            break;
        lineNr++;
        dlh=doc->line(lineNr).handle();
        if(dlh)
            tl= dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
        cnt++;
    }


	return QString();
}

QString findRestArg(QDocumentLineHandle *dlh, Token::TokenType type, int count)
{
	// dlh is current line, next line will be checked here!!!
    if (count <= 0)
		return QString(); // limit search depth
	QDocument *document = dlh->document();
	int index = document->indexOf(dlh);
	if (index + 1 >= document->lines())
		return QString(); // last line reached
	dlh = document->line(index + 1).handle();
	TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	QString result = dlh->text();
    if(!tl.isEmpty()){
        int len=tl.last().start+tl.last().length;
        if(len<result.length()){// comment present or untranslated characters (e.g. comma)
            // make sure it is a comment !!!!
            int j=result.indexOf("%",len);
            if(j>=len){
                result=result.left(j); // avoid comments
            }else{
                result.append(" "); // in case of multiline arguments, linebreak is considered as space in latex
            }
        }else{
            result.append(" "); // in case of multiline arguments, linebreak is considered as space in latex
        }
    }
	for (int i = 0; i < tl.length(); i++) {
		Token tk = tl.at(i);
		if (tk.type == type) {
			// closing found
			return result.left(tk.start);
		}
		if (Token::tkClose().contains(tk.type)) {
			// wrong closing found/ syntax problem
			//return value anyway
			return result.left(tk.start + 1);
		}
	}
	return result + findRestArg(dlh, type, count - 1);
}


/*!
 * \brief get content of argument
 *
 * Handles multiline arguments.
 * To avoid performance impact on unclosed arguments, the maximum number of processed lines is limited to 10.
 * This is called run-away prevention.
 * \param tk argument top-level
 * \return tokenlist with all tokens within the argument
 */
TokenList getArgContent(Token &tk)
{
	TokenList results;
	QDocumentLineHandle *dlh = tk.dlh;
	if (!dlh)
		return results;
	dlh->lockForRead();
	TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	dlh->unlock();
	for (int i = 0; i < tl.length(); i++) {
		if (tk == tl.at(i)) {
			results = getArgContent(tl, i, tk.level);
			break;
		}
	}
	return results;
}
/*!
 * \brief get content of argument
 *
 * Handles multiline arguments.
 * To avoid performance impact on unclosed arguments, the maximum number of processed lines is limited to 10.
 * This is called run-away prevention.
 * \param tl tokenlist of current line
 * \param pos number of token in tokenlist
 * \param level of argument
 * \param runAwayPrevention counts down to zero for subsequent lines to prevent unlimited processing of lines on unclosed arguments
 * \return tokenlist with all tokens within the argument
 */
TokenList getArgContent(TokenList &tl, int pos, int level, int runAwayPrevention)
{
	TokenList result;
	if (runAwayPrevention < 0)
		return result;
	bool finished = false;
	Token tk;
	// adapt strategy after token type (word, closed , open)
	if (pos >= 0 && pos < tl.length()) {
		tk = tl.at(pos);
		if (tk.type == Token::word) {
			result.append(tk);
			return result;
		}
		if (Token::tkBraces().contains(tk.type)) {
			//closed , no spill in next line
			runAwayPrevention = 0; // in case there is no token after the last usable one
		}
	}

	for (int i = pos + 1; i < tl.length(); i++) {
		tk = tl.at(i);
		if (tk.level < level) {
			finished = true;
			break; // end reached
		}
		if (tk.level == level) {
			result.append(tk);
		}
		//ignore other levels
	}
	if (!finished && tk.dlh) {
		//getRestArgfrom
		QDocument *document = tk.dlh->document();
		int index = document->indexOf(tk.dlh);
		TokenList tl;
		while (index + 1 < document->lines()) {
			QDocumentLineHandle *dlh = document->line(index + 1).handle();
			tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
			if (!tl.isEmpty())
				break;
			index++;
		}
		if (!tl.isEmpty())
			result.append(getArgContent(tl, -1, level - tk.level, runAwayPrevention - 1));
	}
	return result;
}
/*!
 * \brief get context at line/column
 *
 * return a tokenstack of the context situation
 * It contains (possibly) command/argument/word
 * \param dlh linehandle
 * \param pos column
 * \return tokenstack
 */
TokenStack getContext(QDocumentLineHandle *dlh, int pos)
{
	dlh->lockForRead();
	TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	dlh->unlock();
	QDocument *doc = dlh->document();
	int lineNr = doc->indexOf(dlh);
	TokenStack stack;
	if (lineNr > 0) {
		QDocumentLineHandle *previous = doc->line(lineNr - 1).handle();
		previous->lockForRead();
		stack = previous->getCookie(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
		previous->unlock();
	}
	// find innermost token at pos
	TokenStack ts;
	for (int i = 0; i < tl.length(); i++) {
		Token tk = tl.at(i);
		if (tk.start > pos) {
			break;
		}
		if (Token::tkOpen().contains(tk.type)) {
			stack.push(tk);
		}
        if (Token::tkClose().contains(tk.type) && !stack.isEmpty() ) {
            if (stack.top().type == Token::opposite(tk.type) && (tk.start<pos)) {
				stack.pop();
			}
            continue;
        }



		if (ts.isEmpty()) {
			ts.push(tk);
		} else {
			// if level identical, replace top
			// if level > , add
			// if level < , remove and replace
			if (ts.top().level == tk.level) {
                int top_end=ts.top().start+ts.top().length;
                if(top_end<pos){
                    ts.pop();
                }
				ts.push(tk);
			} else {
				if (ts.top().level < tk.level) {
					ts.push(tk);
				} else {
					ts.pop();
					if (ts.isEmpty()) {
						ts.push(tk);
					} else {
						ts.pop();
						ts.push(tk);
					}
				}
			}

		}
	} //for
	while (!ts.isEmpty()) {
		// check that pos is within stack
		if (ts.top().start + ts.top().length > pos)
			break;
		if (ts.top().start + ts.top().length == pos && !Token::tkBraces().contains(ts.top().type)) // equal is accceptable for other than braces
			break;
		ts.pop();
	}
	stack << ts;
	return stack;
}
/*!
 * \brief get token at column
 * \param dlh linehandle
 * \param pos columns number
 * \param first get first token that encompasses \a pos, otherwise the latest token which fulfils the condition is returned
 * \return found token
 */
Token getTokenAtCol(QDocumentLineHandle *dlh, int pos, bool first)
{
	if (!dlh) return Token();
	TokenList tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	Token tk;
	for (int i = 0; i < tl.length(); i++) {
		Token elem = tl.at(i);
		if (elem.start > pos)
			break;
		if (elem.start + elem.length >= pos) {
			tk = elem; // get deepest element at col
			if (first)
				break;
		}
		if (!Token::tkBraces().contains(elem.type) && !Token::tkClose().contains(elem.type) && elem.start + elem.length >= pos) { // get abc|} -> abc
			tk = elem; // get deepest element at col
			if (first)
				break;
		}
	}
	return tk;
}
/*!
 * \brief get token at column
 * \param tl tokenlist of line
 * \param pos column
 * \param first first get first token that encompasses \a pos, otherwise the latest token which fulfils the condition is returned
 * \return number of token, -1 if not found
 */
int getTokenAtCol(TokenList &tl, int pos, bool first)
{
	int result = -1;
	for (int i = 0; i < tl.length(); i++) {
		Token elem = tl.at(i);
		if (elem.start > pos)
			break;
		if (elem.start + elem.length >= pos) {
			result = i; // get deepest element at col
			if (first)
				break;
		}
	}
	return result;
}

/*!
 * tk is an argument token (inner content)
 * it assumes that the command is at level--
 * at the moment, only single line detection
 */
QString getCommandFromToken(Token tk)
{
    // don't use outside of main thread as "previous" may be invalid
    if(!tk.optionalCommandName.isEmpty())
        return tk.optionalCommandName;

    QString cmd;
	QDocumentLineHandle *dlh = tk.dlh;
	if (dlh) {
        TokenList tl;
        QDocument *doc = dlh->document();
        if(doc){ // doc is NULL if line was deleted in the meantime
            int lineNr = doc->indexOf(dlh);
            if (lineNr > 0) {
                QDocumentLineHandle *previous = doc->line(lineNr - 1).handle();
                TokenStack stack=previous->getCookieLocked(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
                if(!stack.isEmpty()){
                    Token tk_group=stack.top();
                    if(tk_group.dlh){
                        tl<< tk_group.dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
                    }
                }
            }
            tl<< dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();

            Token result = getCommandTokenFromToken(tl, tk);
            if (result.type == Token::command) {
                cmd = result.getText();
            }
        }
	}
	return cmd;
}
/*!
 * \brief get token which represents the command of which \a tk is a argument
 * \param tl tokenlist of line
 * \param tk token which is argument of a command
 * \return token of command
 */
Token getCommandTokenFromToken(TokenList tl, Token tk)
{
	Token result;
	int tkPos = tl.indexOf(tk);
	int level = tk.level - 1;
	if (tk.subtype == Token::keyVal_val) {
		level = tk.level - 2; // command is 2 levels up
	}
	for (int i = tkPos - 1; i >= 0; i--) {
		Token elem = tl.at(i);
		if (elem.level == level && (elem.type == Token::command || elem.type == Token::commandUnknown) ) {
			result = elem;
			break;
		}
		if (elem.level < level)
			break;
	}
	return result;
}
/*!
 * Realizes the first pass lexing
 * Following functionality is implemented:
 * + separate the the text into words,symbols
 * + assign each symbol/word a basic context like word,command,symbol,open/close brace etc.
 * + set tokenlist as LEXER_RAW_COOKIE on line
 * + remove cookie LEXER_COOKIE (as it is invalid)
 * \param dlh linehandle
 * \return tokenlist
 */
TokenList simpleLexLatexLine(QDocumentLineHandle *dlh)
{
	// dumbed down lexer in order to allow full parallelization and full change of verbatim/non-verbatim later on
	TokenList lexed;
	if (!dlh)
		return lexed;
	dlh->lockForWrite();
	QString s = dlh->text();
	Token present, previous;
	present.type = Token::none;
	present.dlh = dlh;
	present.argLevel = 0;
	QChar verbatimSymbol;
	const QString specialChars = "{([})]";
	int i = 0;
	for (; i < s.length(); i++) {
		QChar c = s.at(i);
		if (!verbatimSymbol.isNull()) {
			if (c == verbatimSymbol) {
				present.length = 1;
				lexed.append(present);
				present.type = Token::none;
				verbatimSymbol = QChar();
				continue;
			}
		}
		if (present.type == Token::command && c == '@') {
			continue; // add @ as letter to command
		}
		if (present.type == Token::command && present.start == i - 1 && (c.isSymbol() || c.isPunct())) {
			// handle \$ etc
			present.length = i - present.start + 1;
			lexed.append(present);
			present.type = Token::none;
			continue;
		}
		if (c == '%') {
			if (present.type != Token::none) {
				present.length = i - present.start;
				lexed.append(present);
			}
			present.type = Token::comment;
			present.length = 1;
            present.start = i;
			lexed.append(present);
			present.type = Token::none;
			continue;
		}

		if (specialChars.contains(c) || c.isSpace() || c.isPunct() || c.isSymbol()) {
			//close token
			if (present.type != Token::none) {
				present.length = i - present.start;
				lexed.append(present);
				present.type = Token::none;
			}
		} else {
			if (present.type == Token::none) {
				if (c.isLetter()) {
					present.type = Token::word;
				} else {
					present.type = Token::number;
				}
				present.start = i;
			} else { // separate numbers and text (latex considers \test1 as two tokens ...)
				if (c.isDigit() && present.type != Token::number) {
					present.length = i - present.start;
					lexed.append(present);
					present.start = i;
					present.type = Token::number;
					continue;
				}
				if (c.isLetter() && present.type == Token::number) {
					present.length = i - present.start;
					lexed.append(present);
					present.start = i;
					present.type = Token::word;
					continue;
				}
			}
			continue;
		}
		//start new Token
		present.start = i;
		if (c == '\\') {
			present.type = Token::command;
			continue;
		}

		int l = specialChars.indexOf(c);
		if (l > -1 && l < 3) {
			present.type = Token::TokenType(int(Token::openBrace) + l);
			present.length = 1;
			lexed.append(present);
			present.type = Token::none;
			continue;
		}
		if (l > 2) {
			present.type = Token::TokenType(int(Token::closeBrace) + (l - 3));
			present.length = 1;
			lexed.append(present);
			present.type = Token::none;
			continue;
		}
		if (c.isSymbol()) {
			present.type = Token::symbol;
			present.length = 1;
			lexed.append(present);
			present.type = Token::none;
			continue;
		}
		if (c.isPunct()) {
			present.type = Token::punctuation;
			present.length = 1;
			lexed.append(present);
			present.type = Token::none;
			continue;
		}

	}
	if (present.type != Token::none) {
		present.length = i - present.start;
		lexed.append(present);
		previous = present;
	}
	dlh->setCookie(QDocumentLine::LEXER_RAW_COOKIE, QVariant::fromValue<TokenList>(lexed));
    dlh->removeCookie(QDocumentLine::LEXER_COOKIE);
	dlh->unlock();
	return lexed;
}


#define GCC_VERSION (__GNUC__ * 10000 \
                               + __GNUC_MINOR__ * 100 \
                               + __GNUC_PATCHLEVEL__)

bool latexDetermineContexts2(QDocumentLineHandle *dlh, TokenStack &stack, CommandStack &commandStack, const LatexParser &lp)
{
	if (!dlh)
	    return false;
	dlh->lockForWrite();
	TokenList tl = dlh->getCookie(QDocumentLine::LEXER_RAW_COOKIE).value<TokenList>();
	TokenStack oldRemainder = dlh->getCookie(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
	CommandStack oldCommandStack = dlh->getCookie(QDocumentLine::LEXER_COMMANDSTACK_COOKIE).value<CommandStack >();
	QString line = dlh->text();
	bool verbatimMode = false;
	int level = 0;
	if (!stack.isEmpty()) {
	    if (stack.top().type == Token::verbatim) {
		verbatimMode = true;
	    } else {
		level = stack.top().level + 1;
	    }
	}
	TokenList lexed;

	QString verbatimSymbol;
	int lastComma = -1;
	int lastEqual = -1e6;
	QString keyName;

	int lineLength=line.length();

	for (int i = 0; i < tl.length(); i++) {
	    Token &tk = tl[i];
	    /* parse tokenlist
	     * check commands (1. syn check)
	     * tie options/arguments to commands
	     * lex otpions (key/val, comma separation,words,single arg,label etc)
	     * => reclassification of arguments
	     */
        if (!verbatimSymbol.isNull()) {
            // handle \verb+ ... +  etc.
            if (tk.type == Token::symbol) {
                QString smb = line.mid(tk.start, 1);
                if (smb == verbatimSymbol) {
                    // stop verbatimSymbol mode
                    verbatimSymbol.clear();
                    continue;
                }
            }
            tk.type = Token::verbatim;
            if (!stack.isEmpty()) {
                tk.subtype = stack.top().subtype;
            }
            tk.level = level;
            lexed << tk;
            continue;
        }
	    // different handling for verbatimMode (verbatim-env, all content is practically ignored)
        if (verbatimMode) {
            // verbatim handling
            // just look for closing (\end{verbatim})
            if (tk.type != Token::command)
                continue;
            QString cmd = line.mid(tk.start, tk.length);
            if (cmd != "\\end")
                continue;
            if (i + 2 >= tl.length()) // not enough tokens to handle \end{verbatim
                continue;
            Token tk2 = tl.at(i + 1);
            Token tk3 = tl.at(i + 2);
            if (tk2.type == Token::openBrace && tk3.type == Token::word) {
                QString env = line.mid(tk3.start, tk3.length);
                if (lp.possibleCommands["%verbatimEnv"].contains(env)) { // incomplete check if closing correspondents to open !
                    verbatimMode = false;
                    stack.pop();
                } else
                    continue;
            } else
                continue;
        }
	    // non-verbatim handling
	    if (tk.type == Token::comment){
            lineLength=tk.start; // limit linelength to comment start
            break; // stop at comment start
	    }
	    if (tk.type == Token::command) {
            QString command = line.mid(tk.start, tk.length);
            if (tl.length() > i + 1 && tl.at(i + 1).type == Token::punctuation && line.mid(tl.at(i + 1).start, 1) == "*") {
                // add * to command
                i++;
                command.append("*");
            }
            if (command == "\\verb" || command == "\\verb*") {
                // special treament for verb
                if (i + 1 < tl.length() && tl.at(i + 1).type == Token::symbol && tl.at(i + 1).start == tk.start + tk.length) {
                    // well formed \verb
                    verbatimSymbol = line.mid(tl.at(i + 1).start, 1);
                    i++;
                }
                // not valid \verb
                if (!stack.isEmpty()) {
                    tk.subtype = stack.top().subtype;
                    if (tk.subtype == Token::keyValArg && lastEqual > -1) {
                        tk.subtype = Token::keyVal_val;
                    }
                }
                tk.level = level;
                lexed << tk;

                continue;
            } else {
                if (!stack.isEmpty()) {
                    tk.subtype = stack.top().subtype;
                    if (tk.subtype == Token::keyValArg && lastEqual > -1) {
                        tk.subtype = Token::keyVal_val;
                        if (!commandStack.isEmpty() && lp.commandDefs.contains(commandStack.top().optionalCommandName + "/" + keyName)) {
                            CommandDescription cd = lp.commandDefs.value(commandStack.top().optionalCommandName + "/" + keyName);
                            tk.subtype = cd.argTypes.value(0, Token::keyVal_val);
                        }
                    }

                }
                if (!commandStack.isEmpty() && commandStack.top().level == level) {
                    //possible command argument without brackets
                    CommandDescription &cd = commandStack.top();
                    if (cd.args > 0) {
                        cd.optionalArgs = 0; // no optional arguments after mandatory
                        cd.bracketArgs = 0;
                        cd.args--;
                        tk.subtype = cd.argTypes.takeFirst();
                    }
                    if (cd.args <= 0) {
                        // unknown arg, stop handling this command
                        commandStack.pop();
                    }
                }
                if (lp.commandDefs.contains(command)) {
                    CommandDescription cd = lp.commandDefs.value(command);
                    cd.level = level;
                    if ((cd.args > 0 || cd.optionalArgs > 0 || cd.bracketArgs > 0 ) && tk.subtype != Token::def) { // don't interpret commands in defintion (\newcommand{def})
                        cd.optionalCommandName=command;
                        commandStack.push(cd);
                    }
                } else {
                    tk.type = Token::commandUnknown;
                }
                tk.level = level;
                lexed << tk;
            }
            continue;
        }
        if (Token::tkOpen().contains(tk.type)) {
            if (!commandStack.isEmpty() && commandStack.top().level == level) {
                CommandDescription &cd = commandStack.top();
                if (tk.type == Token::openBrace) {
                    if (cd.args > 0) {
                        //cd.optionalArgs=0; // argument order (option/mandatory) is not checked, e.g \newcommad{cmd}[argNumber][default]{definition}
                        cd.args--;
                        tk.subtype = cd.argTypes.takeFirst();
                    } else {
                        // ignore
                        lexed << tk;
                        continue;
                    }
                }
                if (tk.type == Token::openSquare) {
                    if (cd.optionalArgs > 0) {
                        cd.optionalArgs--;
                        tk.subtype = cd.optTypes.takeFirst();
                    } else {
                        // unexpected optional argument
                        // ignore
                        lexed << tk;
                        continue;
                    }
                }
                if (tk.type == Token::openBracket) {
                    if (cd.bracketArgs > 0) {
                        cd.bracketArgs--;
                        tk.subtype = cd.bracketTypes.takeFirst();
                    } else {
                        lexed << tk;
                        continue;
                    }
                }

                tk.level = level; // push old level on stack in order to restore that level later and to distinguish between arguments and arbitrary braces
                tk.argLevel = RUNAWAYLIMIT; // run-away prevention
                stack.push(tk);
                tk.level++;
                lexed << tk;
                level++;
            }else{
                if(tk.type==Token::openBrace){ // check braces within arguments, not brackets/squareBrackets
                    //level++; // not an argument
                    tk.level = level;
                    tk.argLevel = RUNAWAYLIMIT; // run-away prevention, needs to be >0 as otherwise closing barces are misinterpreted
                    if (!stack.isEmpty()) {
                        tk.subtype = stack.top().subtype;
                    }
                    stack.push(tk);
                    lexed << tk;
                }
            }
            continue;
        }
	    if (Token::tkClose().contains(tk.type)) {
		// special treament for brackets as they don't have any syntaxtical meaning except with some commands
            if (tk.type == Token::closeBracket ) {
                if (stack.isEmpty())
                    continue;
                if (stack.top().type != Token::opposite(tk.type))
                    continue; //closing bracket is ignored if no correct open is present
            }
            if (!stack.isEmpty() && stack.top().type == Token::opposite(tk.type)) {
                Token tk1 = stack.pop();

                if (Token::tkCommalist().contains(tk1.subtype)) {
                    lastComma = -1;
                }
                if (tk1.subtype == Token::keyValArg) {
                    lastComma = -1;
                    if (lastEqual > -1e6) {
                        if (!lexed.isEmpty() && lexed.last().type == Token::keyVal_key) {
                            // no value added, add empty key_val
                            Token tk0;
                            tk0.start = tk.start;
                            tk0.length = 0;
                            tk0.dlh = dlh;
                            tk0.type = Token::keyVal_val;
                            tk0.subtype = Token::keyVal_val;
                            tk0.level = level;
                            lexed << tk0;
                        }
                        level = lastEqual;
                    }
                    lastEqual = -1e6;
                }
                if (tk1.dlh == dlh) { // same line
                    int j = lexed.length() - 1;
                    while (j >= 0 && lexed.at(j).start > tk1.start)
                        j--;
                    if (j >= 0 && lexed.at(j).start == tk1.start) {
                        if (Token::tkSingleArg().contains(tk1.subtype) || tk1.subtype >= Token::specialArg) { // all special args are assumed single word arguments
                            // join all args for intended single word argument
                            // first remove all argument tokens
                            for (int k = j + 1; k < lexed.length();) {
                                lexed.removeAt(k);
                            }
                            Token tk2;
                            tk2.dlh = dlh;
                            tk2.start = lexed[j].start + 1;
                            tk2.length = tk.start - lexed[j].start - 1;
                            tk2.type = tk1.subtype;
                            tk2.level = level;
                            lexed << tk2;
                            if (tk2.type == Token::beginEnv) {
                                // special treatment for \begin ...
                                QString env = line.mid(tk2.start, tk2.length);
                                // special treatment for verbatim
                                if (lp.possibleCommands["%verbatimEnv"].contains(env)) {
                                    verbatimMode = true;
                                    Token tk3;
                                    tk3.dlh = dlh;
                                    tk3.level = level - 1;
                                    tk3.type = Token::verbatim;
                                    stack.push(tk3);
                                } else { // only care for further arguments if not in verbatim mode (see minted)
                                    CommandDescription cd = lp.commandDefs.value("\\begin{" + env + "}", CommandDescription());
                                    if (cd.args > 1) {
                                        cd.args--;
                                        cd.argTypes.takeFirst();
                                        cd.optionalCommandName="\\begin{" + env + "}";
                                        commandStack.push(cd);
                                    }
                                }
                            }
                        }
                        lexed[j].length = tk.start - tk1.start + 1;
                        lexed[j].type = Token::closed(tk.type);
                        level=tk1.level; // restore original level
                        // remove commands from commandstack with higher level, as they can't have any valid arguments anymore
                        while (!commandStack.isEmpty() && commandStack.top().level > level) {
                            commandStack.pop();
                        }
                    } else { // opening not found, whyever (should not happen)
                        //level--;
                        tk.level = level;
                        lexed.append(tk);
                    }
                } else {
                    // closing brace in later line ...
                    tk.level = level;
                    tk.subtype=tk1.subtype;
                    level=tk1.level; // restore original level
                    lexed.append(tk);
                }
                if (!commandStack.isEmpty() && commandStack.top().level == level) {
                    CommandDescription &cd = commandStack.top();
                    if (cd.args <= 0 && cd.bracketArgs <= 0) {
                        // all args handled, stop handling this command
                        commandStack.pop();
                    }
                }
                continue;
            }
            // ignore unopened close
        }
        if (!stack.isEmpty() && stack.top().level == level - 1 && Token::tkCommalist().contains(stack.top().subtype)) {
            // handle commalist
            if (tk.type == Token::punctuation && line.mid(tk.start, 1) == ",") {
                lastComma = -1;
                continue;
            }
            if (lastComma < 0) {
                tk.level = level;
                tk.type = stack.top().subtype;
                lexed << tk;
                lastComma = lexed.length() - 1;
            } else {
                lexed[lastComma].length = tk.start + tk.length - lexed[lastComma].start;
            }
            continue;
        }
        if (!stack.isEmpty() && stack.top().level < level && stack.top().subtype == Token::keyValArg) {
            // handle keyval
            if (tk.type == Token::punctuation && line.mid(tk.start, 1) == ",") {
                lastComma = -1;
                if (lastEqual > -1e6) {
                    if (!lexed.isEmpty() && lexed.last().type == Token::keyVal_key) {
                        // no value added, add empty key_val
                        Token tk0;
                        tk0.start = tk.start;
                        tk0.length = 0;
                        tk0.type = Token::keyVal_val;
                        tk0.subtype = Token::keyVal_val;
                        tk0.level = level;
                        lexed << tk0;
                    }
                    level = lastEqual;
                }
                lastEqual = -1e6;
                continue;
            }
            if (tk.type == Token::symbol && line.mid(tk.start, 1) == "=") {
                lastComma = 1;
                lastEqual = level;
                level++;
                continue;
            }
            if (lastComma < 0) {
                tk.level = level;
                tk.type = Token::keyVal_key;
                if(!commandStack.isEmpty()){
                    CommandDescription &cd = commandStack.top();
                    tk.optionalCommandName=cd.optionalCommandName;
                }
                keyName = line.mid(tk.start, tk.length);
                lexed << tk;
                lastComma = lexed.length() - 1;
            } else {
                if (lastEqual <= -1e6) {
                    lexed[lastComma].length = tk.start + tk.length - lexed[lastComma].start;
                } else {
                    tk.level = level;
                    tk.subtype = Token::keyVal_val;
                    if (!commandStack.isEmpty() && lp.commandDefs.contains(commandStack.top().optionalCommandName + "/" + keyName)) {
                        CommandDescription cd = lp.commandDefs.value(commandStack.top().optionalCommandName + "/" + keyName);
                        tk.type = cd.argTypes.value(0, Token::keyVal_val); // onyl types can be set in key_val as they ned to be recognaized later
                        if(!lexed.isEmpty() && lexed.last().type==tk.type && lexed.last().subtype==tk.subtype){
                            lexed.last().length=tk.start+tk.length-lexed.last().start;
                            continue;
                        }
                    }
                    lexed << tk;
                }
            }
            continue;
        }
        if (tk.type == Token::symbol) {
            // special treatment for $ as mathstart
            if (line.mid(tk.start, 2) == "$$") {
                tk.type = Token::command;
                tk.level = level;
                tk.length=2;
                lexed << tk;
                i++;
                continue;
            }
            if (line.mid(tk.start, 1) == "$") {
                tk.type = Token::command;
                tk.level = level;
                if(i+1<tl.length()){
                    if(line.mid(tk.start,2)=="$$"){
                        i=i+1;
                        tk.length=2;
                    }
                }
                lexed << tk;
                continue;
            }
        }
        if (tk.type == Token::punctuation) {
            if (line.mid(tk.start, 1) == "&") {
                // special treatment for & in tabular
                tk.type = Token::command;
                tk.level = level;
                lexed << tk;
                continue;
            }
            if (line.mid(tk.start, 1) == "\"") {
                // special treatment for " (used for umlauts in german)
                if (i + 1 < tl.length()) {
                    Token tk2 = tl.at(i + 1);
                    if (tk2.start == tk.start + 1 && tk2.type == Token::word) {
                        i = i + 1;
                        tk.length = tk2.length + 1;
                        tk.type = Token::word;
                    }
                    if (!lexed.isEmpty() && lexed.last().type == Token::word) {
                        if (lexed.last().start + lexed.last().length == tk.start) {
                            lexed.last().length += tk.length;
                            continue;
                        }
                    }
                }
            }
        }
        if (tk.type == Token::word || tk.type == Token::number || tk.type == Token::symbol || tk.type == Token::punctuation) {
            tk.level = level;
            if (!stack.isEmpty()) {
                tk.subtype = stack.top().subtype;
                tk.argLevel=-1; // tk is part of brace
            }
            if (!commandStack.isEmpty() && commandStack.top().level == level) {
                //possible command argument without brackets
                CommandDescription &cd = commandStack.top();
                if (cd.args > 0) {
                    cd.optionalArgs = 0; // no optional arguments after mandatory
                    cd.args--;
                    tk.subtype = cd.argTypes.takeFirst();
                }
                if (cd.args <= 0) {
                    // unknown arg, stop handling this command
                    commandStack.pop();
                }
                tk.level++; // needs tk level be increased
            }
            lexed << tk;
        }
    }
    {
        // remove tokens from stack which are not intended for mulitline: (
        QMutableVectorIterator<Token> i(stack);
        while (i.hasNext()) {
            Token &tk = i.next();
            if (tk.type == Token::openBracket) {
                i.remove();
            } else if ((tk.type == Token::openBrace || tk.type == Token::openSquare ) && tk.dlh == dlh) {
                // set length to whole line after brace
                tk.length = lineLength - tk.start;
            }
        }
    }
    {
        // change length of openBrace/openBracket (length to end of line)
        QMutableListIterator<Token> i(lexed);
        while (i.hasNext()) {
            Token &tk = i.next();
            if ((tk.type == Token::openBrace || tk.type == Token::openSquare ) && tk.dlh == dlh) {
                // set length to whole line after brace
                tk.length = lineLength - tk.start;
            }
        }
    }

    dlh->setCookie(QDocumentLine::LEXER_COOKIE, QVariant::fromValue<TokenList>(lexed));
    // run-away prevention
    // reduce argLevel by 1, remove all elements with level <0
    // TODO: needs to be applied on commandStack as well !!!
    for (int i = 0; i < stack.size(); i++) {
        if (stack[i].type == Token::verbatim)
            continue;
        stack[i].argLevel = stack[i].argLevel - 1;
        if (stack[i].argLevel < 0) {
            stack.remove(i);
            i--;
        }
    }
    dlh->setCookie(QDocumentLine::LEXER_REMAINDER_COOKIE, QVariant::fromValue<TokenStack>(stack));
    dlh->setCookie(QDocumentLine::LEXER_COMMANDSTACK_COOKIE, QVariant::fromValue<CommandStack>(commandStack));
    dlh->unlock();

    bool remainderChanged = (stack != oldRemainder) || (commandStack != oldCommandStack) ;

    return remainderChanged;
}
/*!
 * \brief get completer context
 * \param dlh linehandle
 * \param column
 * \return 512 if token at column is 'width'
 */
int getCompleterContext(QDocumentLineHandle *dlh, int column)
{
	TokenStack ts = getContext(dlh, column);
	Token tk;
	if (!ts.isEmpty()) {
		tk = ts.top();
		if (tk.type == Token::word && tk.subtype == Token::none && ts.size() > 1) {

			// set brace type
			ts.pop();
			tk = ts.top();
		}
	}

	Token::TokenType type = tk.type;
    if (tk.subtype != Token::none && tk.subtype != Token::keyVal_val)
		type = tk.subtype;

	int result = 0;
	switch (type) {
	case Token::width:
		result = 512;
		break;
	default:
		;
	}
	return result;
}

