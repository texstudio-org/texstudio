#include "smallUsefulFunctions.h"
#include "latexcompleter_config.h"
#include "qdocumentline_p.h"
#include "qdocument.h"
#include <QBuffer>
#include "codesnippet.h"

const QString CommonEOW = QString("~!#$%^&*()_+{}|:\"\\<>?,./;[]-= \t\n\r`'") + QChar(171) + QChar(187) + QChar(8223) + QChar(8222) + QChar(8221) + QChar(8220) /* <= fancy quotation marks */;
const QString Punctation = "!():\"?,.;-~";
const QString EscapedChars = "%&_";
const QString CharacterAlteringChars = "\"'^`";

const int LatexParser::MAX_STRUCTURE_LEVEL = 10;
const int RUNAWAYLIMIT=10; // limit lines to process multi-line arguments in order to prevent processing to the end of document if the arbument is unclosed

LatexParser *LatexParserInstance = 0;

LatexParser::LatexParser()
{
	if (!LatexParserInstance) {
		LatexParserInstance = this;
		init();
	}
}

LatexParser::~LatexParser()
{
	if (LatexParserInstance == this) {
		LatexParserInstance = 0;
	}
}

LatexParser &LatexParser::getInstance()
{
	Q_ASSERT(LatexParserInstance);
	return *LatexParserInstance;
}

void LatexParser::init()
{
	environmentCommands = QSet<QString>::fromList(QStringList() << "\\begin" << "\\end" << "\\newenvironment" << "\\renewenvironment");
	mathStartCommands  << "$" << "$$" << "\\(" << "\\[" ;
	mathStopCommands  << "$" << "$$" << "\\)" << "\\]" ;

	possibleCommands.clear();
	possibleCommands["tabular"] = QSet<QString>::fromList(QStringList() << "&" );
	possibleCommands["array"] = QSet<QString>::fromList(QStringList() << "&" );
	possibleCommands["tabbing"] = QSet<QString>::fromList(QStringList() << "\\<" << "\\>" << "\\=" << "\\+");
	possibleCommands["normal"] = QSet<QString>::fromList(QStringList() << "\\\\" << "\\_" << "\\-" << "$" << "$$" << "\\$" << "\\#" << "\\{" << "\\}" << "\\S" << "\\'" << "\\`" << "\\^" << "\\=" << "\\." << "\\u" << "\\v" << "\\H" << "\\t" << "\\c" << "\\d" << "\\b" << "\\o" << "\\O" << "\\P" << "\\l" << "\\L" << "\\&" << "\\~" << "\\" << "\\," << "\\%" << "\\\"");
	possibleCommands["math"] = QSet<QString>::fromList(QStringList() << "_" << "^" << "\\$" << "\\#" << "\\{" << "\\}" << "\\S" << "\\," << "\\!" << "\\;" << "\\:" << "\\\\" << "\\ " << "\\|");
	possibleCommands["%definition"] << "\\newcommand" << "\\renewcommand" << "\\newcommand*" << "\renewcommand*" << "\\providecommand" << "\\newlength" << "\\let";
	possibleCommands["%usepackage"] << "\\usepackage" << "\\documentclass";
	possibleCommands["%graphics"] << "\\includegraphics";
	possibleCommands["%bibitem"] << "\\bibitem";
	possibleCommands["%cite"]  << "\\cite" <<  "\\nptextcite"  ;
	possibleCommands["%label"] << "\\label";
	possibleCommands["%bibliography"] << "\\bibliography";
	possibleCommands["%file"] << "\\include" << "\\input" << "\\import" << "\\includeonly" << "\\includegraphics" << "\\bibliographystyle" << "\\bibliography";
	possibleCommands["%ref"] = QSet<QString>();  // will all be populated via cwl
	possibleCommands["%include"] << "\\include" << "\\input";
	possibleCommands["%import"] << "\\import" << "\\importfrom" << "\\subimport" << "\\subimportfrom";
	commandDefs.clear();
}

int LatexReader::nextToken(const QString &line, int &index, bool inOption, bool detectMath)
{
	bool inWord = false;
	bool inCmd = false;
	//bool reparse=false;
	bool singleQuoteChar = false;
	bool doubleQuoteChar = false;
	bool ignoreBrace = false;
	bool ignoreClosingBrace = false;
	int start = -1;
	int i = index;
	for (i = (i > 0 ? i : 0); i < line.size(); i++) {
		QChar cur = line.at(i);
		if (ignoreBrace && cur == '{') {
			ignoreBrace = false;
			ignoreClosingBrace = true;
			continue;
		} else ignoreBrace = false;
		if (ignoreClosingBrace && cur == '}') {
			ignoreClosingBrace = false;
			continue;
		}
		if (doubleQuoteChar)
			//if (cur == '\'') break; // check for words starting with "' (german quotation mark)
			if (CommonEOW.contains(cur)) break; // check for all quotation marks
		doubleQuoteChar = false;
		if (inCmd) {
			if (CommonEOW.indexOf(cur) >= 0 || cur.isDigit()) {
				if (i - start == 1) i++;
				break;
			}
		} else if (inWord) {
			if (cur == '\\') {
				if (i + 1 >= line.size()) break;
				const QChar &c = line.at(i + 1);
				if (c == '-' || c == '&') i++; //allow \& in the middle/end of words, e.g. C&A
				else if (CharacterAlteringChars.contains(c)) {
					ignoreBrace = true;
					i++;//ignore word separation marker
				} else break;
			} else if (cur == '"') { //ignore " like in "-, "", "| "a
				if (i + 1 < line.size()) {
					QChar nextChar = line.at(i + 1);
					if (nextChar == '-' || nextChar == '"' || nextChar == '|')  i++;
					else if (!nextChar.isLetterOrNumber()) break;
				} else break;
			} else if (cur == '\'') {
				if (singleQuoteChar) break;	 //no word's with two '' => output
				else singleQuoteChar = true; //but accept one
			} else if (cur == '.' || cur == '-') {
				if (i > 0 && line.at(i - 1).isLetter())
					i++; //take '.' or '-' into word, so that abbreviations/hyphenations, at least German ones, are checked correctly
				if (cur == '-' &&  i < line.size() && line.at(i).isLetter())
					; // continue with composite words
				else
					break;
			} else if (CommonEOW.indexOf(cur) >= 0 && !inOption) {
				break;
			} else if (cur == '}' || cur == ']') break;

		} else if (cur == '\\') {
			if (i + 1 >= line.size()) break;
			const QChar &nextc = line.at(i + 1);
			if (CharacterAlteringChars.contains(nextc))  {
				inWord = true;
				start = i;
				ignoreBrace = true;
				i++;
			} else if (EscapedChars.contains(nextc)) {
				i++;
				Q_ASSERT(start == -1);
			} else {
				start = i;
				inCmd = true;
			}
		} else if (cur == '{' || cur == '}' || cur == '%' || cur == '[' || cur == ']') {
			index = i + 1;
			return i;
		} else if (detectMath && cur == '$') {
			start = i;
			i++;
			if (i < line.size() && line[i] == '$')
				i++; //detect $$
			break;
		} else if (detectMath && (cur == '_' || cur == '^' || cur == '&')) {
			start = i;
			i++;
			break;
		} else if ((CommonEOW.indexOf(cur) < 0 && cur != '\'' ) || cur == '"') {
			start = i;
			inWord = true;
			doubleQuoteChar = ( cur == '"');
		} else if (Punctation.contains(cur)) {
			start = i;
			i++;
			while (i < line.length() && line.at(i) == '-') i++; //convert LaTeX --- to a single -
			break;
		}
	}
	if (singleQuoteChar && i - 1 < line.size() && i > 0 && line.at(i - 1) == '\'')
		i--; //remove ' when a word ends with it  (starting is handled because ' does not start a word)
	index = i;
	return start;
}

QString getCommonEOW()
{
	return CommonEOW;
}

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


int findClosingBracket(const QString &word, int &start, QChar oc, QChar cc)
{
	int i = 0;
	if (start < 0) start = word.indexOf(oc, i);
	i = start > -1 ? start : 0;
	int stop = word.indexOf(cc, i);
	i = word.indexOf(oc, i + 1);
	while (i > 0 && stop > 0 && i < stop) {
		stop = word.indexOf(cc, stop + 1);
		i = word.indexOf(oc, i + 1);
	}
	return stop;
}

int findOpeningBracket(const QString &word, int start, QChar oc, QChar cc)
{
	int i = start;
	int n = 0;
	while (i > -1) {
		QChar ch = word.at(i);
		if (ch == oc) {
			n--;
			if (n < 0)
				break;
		}
		if (ch == cc) {
			n++;
		}
		i--;
	}
	return i;
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
	start = s.indexOf("\\texorpdfstring");
	while (start >= 0) {
		// first arg
		int i = startOfArg(s, start + 15);
        if (i < 0){
            if(start+15>=s.length()){ // argument is only \texorpdfstring
                s.clear();
                break;
            }
            continue;  // no arguments for \\texorpdfstring
        }
		i++;
		stop = findClosingBracket(s, i);
		if (stop < 0) continue;

		// second arg
		i = startOfArg(s, stop + 1);
		if (i < 0) continue;  // no arguments for \\texorpdfstring
		i++;
		stop = findClosingBracket(s, i);
		if (stop < 0) continue;

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
int findCommandWithArgsFromTL(const TokenList &tl, Tokens &cmd, TokenList &args, int offset, bool parseComment)
{
	int result = -1;
	for (int i = 0; i < tl.length(); i++) {
		cmd = tl.at(i);
		if (!parseComment && cmd.type == Tokens::comment)
			return -1;
		if (i < offset)
			continue;
		if (cmd.type != Tokens::command)
			continue;
		// Token is command
		result = i;
		// now, collect arguments
		i++;
		int level = cmd.level;
		for (; i < tl.length(); i++) {
			Tokens tk = tl.at(i);
			if (tk.type == Tokens::comment)
				break;
			if (tk.level < level)
				break;
			if (tk.level == level) {
				args.append(tk);
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

/// returns true if the options are complete, false if the scanning ended while still in the options
bool LatexParser::resolveCommandOptions(const QString &line, int column, QStringList &values, QList<int> *starts)
{
	const QString BracketsOpen("[{(");
	const QString BracketsClose("]})");
	int start = column;
	int stop = -1;
	int type;
	// check if between command and options is located text or other command
	int abort = line.indexOf(QRegExp("(\\s|\\\\)"), start + 1);
	while (start < line.length()) {
		// find first available bracket after position start
		int found = -1;
		type = -1;
		for (int i = 0; i < BracketsOpen.size(); i++) {
			int zw = line.indexOf(BracketsOpen[i], start);
			if (zw > -1 && (zw < found || found == -1)) {
				found = zw;
				type = i;
			}
		}
		if (type < 0) break;
		// check if only space between cmd and opening bracket
		if (abort > 0) {
			if ((found - abort) > 0) {
				QString test = line.mid(abort, found - abort);
				test = test.simplified();
				test.remove(' ');
				if (!test.isEmpty())
					break;
			}
			abort = -1;
		}
		// check wether a word letter appears before (next command text ...)
		if (stop > -1) {
			stop = line.indexOf(QRegExp("\\S+"), start);
		}
		if (stop < found && stop > -1) break;
		// find apropriate closing bracket.
		int lvl = 0;
		stop = -1;
		for (int i = found + 1; i < line.length(); i++) {
			QChar c = line[i];
			if (lvl == 0 && c == BracketsClose[type]) {
				stop = i;
				break;
			}
			if (BracketsOpen.contains(c)) {
				lvl++;
			}
			if (lvl > 0 && BracketsClose.contains(c)) {
				lvl--;
			}
		}
		if (found > -1 && stop > -1) {
			values << line.mid(found, stop - found + 1);
			if (starts)
				starts->append(found);
			start = stop + 1;
		} else return false;
	}
	return true;
}
/*!
 * \brief remove option brackets from text on 'option'
 * \param option text
 * \return option without []
 */
QString LatexParser::removeOptionBrackets(const QString &option)
{
	if (option.isNull() || option.length() < 2) return option;
	if ((option.at(0) == '{' && option.at(option.length() - 1) == '}') ||
	        (option.at(0) == '[' && option.at(option.length() - 1) == ']'))
		return option.mid(1, option.length() - 2);
	return option;
}
/*!
 * \brief determines level of structure in a section-command
 * \param cmd latex command
 * \return level of stucture
 */
int LatexParser::structureCommandLevel(const QString &cmd) const
{
	for (int i=0; i<=MAX_STRUCTURE_LEVEL; i++) {
		if (possibleCommands[QString("%structure%1").arg(i)].contains(cmd)) {
			return i;
		}
	}
	return -1;
}

/*! return a number for a context
 * 0 unknown
 * 1 command
 * 2 option \command[option]{arg}
 * 3 argument \command{arg}
 * 4 argument 2   \command{arg}{arg2}
 * etc
 * \warning obsolete for lexer-based token system, though still in use in some code
 */
int LatexParser::findContext(QString &line, int &column) const
{

	if (line.isEmpty())
		return 0;
	QString eow = "\\[]{}$";
	int i = column;
	if (i >= line.length())
		i = line.length();
	if (i > 0)
		i--; // character left of pos is to be checked
	else
		return 0; // no context can be detected at line start (old behavior)
	while (i >= 0 && !eow.contains(line.at(i)))
		i--;
	if (i < 0)
		return 0; // no eow found
	QChar ch = line.at(i);
	if (ch == '\\') {
		// command found
		int start = i;
		i++;
		while (i < line.length() && !eow.contains(line.at(i)))
			i++;
		line = line.mid(start, i - start);
		column = start;
		return 1;
	}
	int start_ref = findOpeningBracket(line, i);
	int start_opt = findOpeningBracket(line, i, '[', ']');
	int ret = 0;
	if (start_ref > start_opt) {
		// assuming we are in command argument
		ret = 3;
		i = start_ref - 1;
	} else {
		if (start_opt > -1) {
			//assuming we are in command option
			ret = 2;
			i = start_opt - 1;
		}
	}
	if (ret == 0)
		return 0;

	int n = 0;
	QString openBrackets = "[{";
	QString closeBrackets = "]}";
	eow = getCommonEOW();
	eow.remove(' ');
	int stop = i;
	while (i > -1) {
		ch = line.at(i);
		if (openBrackets.contains(ch)) {
			//TODO check if correct bracket was opened ...
			n--;
			if (n < 0)
				break;
			i--;
			stop = i;
			continue;
		}
		if (closeBrackets.contains(ch)) {
			n++;
			if (ch == '}')
				++ret;  //going through another braces pair, [] is not checked
			i--;
			continue;
		}
		if (n == 0 && eow.contains(ch)) {
			if (ch == '\\') {
				//TODO: check if not \\ (newline) was found
				line = line.mid(i, stop - i + 1).simplified();
				column = i;
				return ret;
			} else { // this is a overly strict interpretation of command syntax
				return 0;
			}
		}
		i--;
	}

	return 0;
}

LatexParser::ContextType LatexParser::findContext(const QString &line, int column, QString &command, QString &value) const
{
	command = line;
	int col = column; //remember column
	int temp = findContext(command, column);
	QStringList vals;
	resolveCommandOptions(line, column, vals);
	value = "";
	if (!vals.isEmpty()) {
		value = vals.takeFirst();
		if (value.startsWith('[') && temp != 2) {
			if (!vals.isEmpty()) {
				value = vals.takeFirst();
			}
		}
		if (value.startsWith('{') || value.startsWith('['))
			value.remove(0, 1);
		if (value.endsWith('}') || value.endsWith(']'))
			value.chop(1);
	}
	switch (temp) {
	case 0:
		return Unknown;
	case 1:
		return Command;
	case 3:
		if (specialTreatmentCommands.contains(command)) {
			QSet<QPair<QString, int> > helper = specialTreatmentCommands.value(command);
			QPair<QString, int> elem;
			foreach (elem, helper) {
				if (elem.second == 1)
					return ArgEx;
			}
		}
		// check key/val
		{
			QStringList keys = possibleCommands.keys();
			bool handled = false;
			QString elem;
			QStringList checkOptions;
			checkOptions <<  "key%1" + command << "key%1" + command + "#c";

			foreach (elem, checkOptions) {
				if (keys.contains(elem)) {
					handled = true;
					command = elem.mid(4);
					break;
				}
			}

			if (handled) {
				// check that cursor is within keyval
				bool isKey = false;
				for (int i = col; col > 0; col--) {
					if (line.at(i - 1).isLetter())
						continue;
					if (line.at(i - 1) == '{' || line.at(i - 1) == ',')
						isKey = true;
					break;
				}
				if (isKey)
					return Keyval;
				else
					return KeyvalValue;
			}
		}
		// normal context
		if (environmentCommands.contains(command))
			return Environment;
		else if (possibleCommands["%label"].contains(command))
			return Label;
		else if (possibleCommands["%ref"].contains(command))
			return Reference;
		else if (possibleCommands["%usepackage"].contains(command))
			return Package;
		else if (possibleCommands["%cite"].contains(command))
			return Citation;
		else if (possibleCommands["%citeExtendedCommand"].contains(command))
			return Citation_Ext;
		else if (possibleCommands["%graphics"].contains(command))
			return Graphics;
		else return Option;
	case 2:
		// find possible commands for keyval completion
	{
		if (specialTreatmentCommands.contains(command)) {
			QSet<QPair<QString, int> > helper = specialTreatmentCommands.value(command);
			QPair<QString, int> elem;
			foreach (elem, helper) {
				if (elem.second == 0)
					return OptionEx;
			}
		}
		QStringList keys = possibleCommands.keys();
		QString arg;
		if (!vals.isEmpty()) {
			arg = vals.first();
			if (arg.startsWith('{') )
				arg.remove(0, 1);
			if (arg.endsWith('}'))
				arg.chop(1);
		}
		bool handled = false;
		QString elem;
		QStringList checkOptions;
		checkOptions << "key%" + command + "/" + arg << "key%" + command + "/" + arg + "#c" << "key%" + command << "key%" + command + "#c";

		foreach (elem, checkOptions) {
			if (keys.contains(elem)) {
				handled = true;
				command = elem.mid(4);
				break;
			}
		}

		if (handled) {
			// check that cursor is within keyval
			bool isKey = false;
			for (int i = col; col > 0; col--) {
				if (line.at(i - 1).isLetter())
					continue;
				if (line.at(i - 1) == '[' || line.at(i - 1) == ',')
					isKey = true;
				break;
			}
			if (isKey)
				return Keyval;
			else
				return KeyvalValue;
		}
	}
	default:
		return Unknown;
	}
}

int LatexParser::commentStart(const QString &text)
{
	if (text.startsWith("%")) return 0;
	QString test = text;
	test.replace("\\\\", "  ");
	int cs = test.indexOf(QRegExp("[^\\\\]%")); // find start of comment (if any)
	if (cs > -1) return cs + 1;
	else return -1;
}
/// remove comments from 'text'
QString LatexParser::cutComment(const QString &text)
{
	return text.left(LatexParser::commentStart(text));
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

uint joinUnicodeSurrogate(const QChar &highSurrogate, const QChar &lowSurrogate)
{
	uint uhigh = highSurrogate.unicode();
	uint ulow = lowSurrogate.unicode();
	uint code = 0x10000;
	code += (uhigh & 0x03FF) << 10;
	code += (ulow & 0x03FF);
	return code;
}

QTextCodec *QTextCodecForTeXShopName(const QByteArray &enc)
{
	//copied and modified from texworks
	if (enc == "utf-8 unicode") return QTextCodec::codecForName("UTF-8");
	if (enc == "standard unicode") return QTextCodec::codecForName("UTF-16");
	if (enc == "windows cyrillic") return QTextCodec::codecForName("Windows-1251");
	if (enc == "isolatin") return QTextCodec::codecForName("ISO 8859-1");
	if (enc == "isolatin2") return QTextCodec::codecForName("ISO 8859-2");
	if (enc == "isolatin5") return QTextCodec::codecForName("ISO 8859-5");
	if (enc == "isolatin9") return QTextCodec::codecForName("ISO 8859-9");
	if (enc == "macosroman") return QTextCodec::codecForName("Apple Roman");
	//      "MacJapanese",          "",
	//      "DOSJapanese",          "",
	if (enc == "sjis_x0213") return QTextCodec::codecForName("Shift-JIS");
	if (enc == "euc_jp") return QTextCodec::codecForName("EUC-JP");
	//      "JISJapanese",          "",
	//      "MacKorean",            "",
	//      "Mac Cyrillic",         "",
	//      "DOS Cyrillic",         "",
	//      "DOS Russian",          "",
	if (enc == "koi8_r") return QTextCodec::codecForName("KOI8-R");
	if (enc == "gb 18030") return QTextCodec::codecForName("GB18030-0");
	//      "Mac Chinese Traditional",      "",
	//      "Mac Chinese Simplified",       "",
	//      "DOS Chinese Traditional",      "",
	//      "DOS Chinese Simplified",       "",
	//      "GBK",                          "",
	//      "GB 2312",                      "",
	return 0;
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

QTextCodec *LatexParser::QTextCodecForLatexName(QString str)
{
	if (str.contains(',')) { //multiple options are allowed
		foreach (const QString &splitter, str.split(',')) {
			QTextCodec *codec = QTextCodecForLatexName(splitter);
			if (codec) return codec;
		}
	}
	str = str.toLower(); //probably unnecessary
	if (str.startsWith("x-")) str = str.mid(2); //needed for inputenx encodings used as parameters for inputenc

	//encodings as defined by inputenc 1.1d (2008/03/30)
	//popular first
	if (str == "utf8" || str == "utf8x") return QTextCodec::codecForName("UTF-8");
	if (str.startsWith("latin")) return QTextCodec::codecForName(qPrintable(str));
	//as in the docu
	if (str == "ascii") return QTextCodec::codecForName("latin1"); //this is wrong (should be latin1 limited to 0x00-0x7f)
	//if (str == "decmulti") return??
	//if (str == "next") ??
	if (str.startsWith("cp") && (str.length() == 5 || str.length() == 6)
	        && (str[2] >= '0') && (str[2] <= '9')
	        && (str[3] >= '0') && (str[3] <= '9')
	        && (str[4] >= '0') && (str[4] <= '9') &&
	        (str.length() == 5 || ((str[5] >= '0') && (str[5] <= '9')))) return QTextCodec::codecForName(qPrintable(str));
	//if (str == "cp437de") return QTextCodec::codecForName("??");
	if (str == "applemac") return QTextCodec::codecForName("macintosh");
	if (str == "macce") return QTextCodec::codecForName("macintosh"); //wrong, should be Macintosh Central European code page.
	if (str == "ansinew") return QTextCodec::codecForName("cp1252");

	//additional encodings by inputenx
	if (str == "us-ascii" || str == "clean7bit" || str == "ascii-print" || str == "ascii-printable") return QTextCodec::codecForName("latin1"); //this is wrong (should be latin1 limited to 0x00-0x7f)
	//if (str == "atari" || )str == "atarist" ||  return QTextCodec::codecForName("???")
	//if (str == "dec-mcs") return??
	if (str == "koi8-r") return QTextCodec::codecForName("KOI8-R");
	if (str.startsWith("iso-8859-")) return QTextCodec::codecForName(qPrintable(str));
	if (str == "iso88595") return QTextCodec::codecForName("ISO-8859-5");
	if (str == "mac-ce" || str == "mac-centeuro") return QTextCodec::codecForName("macintosh"); //wrong, should be Macintosh Central European code page.
	if (str == "mac-cyrillic" || str == "maccyr" || str == "mac-ukrainian" || str == "macukr") return QTextCodec::codecForName("macintosh"); //wrong, should be Macintosh Cyrillic
	//if (str == "nextstep, next?

	//return QTextCodec::codecForName(str); //try it anyways
	return 0;
}

QStringList LatexParser::latexNamesForTextCodec(const QTextCodec *codec)
{
	// *INDENT-OFF*  (astyle-config)
	switch (codec->mibEnum()) {
		//case 0 : return QStringList(); // "System"
		case 4 : return QStringList() << "latin1"; // "ISO-8859-1"
		case 5 : return QStringList() << "latin2"; // "ISO-8859-2"
		case 6 : return QStringList() << "latin3"; // "ISO-8859-3"
		case 7 : return QStringList() << "latin4"; // "ISO-8859-4"
		//case 8 : return QStringList(); // "ISO-8859-5"
		//case 10 : return QStringList(); // "ISO-8859-7"
		case 12 : return QStringList() << "latin5"; // "ISO-8859-9"
		//case 13 : return QStringList(); // "ISO-8859-10"
		//case 17 : return QStringList(); // "Shift_JIS"
		//case 18 : return QStringList(); // "EUC-JP"
		//case 38 : return QStringList(); // "EUC-KR"
		//case 39 : return QStringList(); // "ISO-2022-JP"
		//case 85 : return QStringList(); // "ISO-8859-8"
		//case 82 : return QStringList(); // "ISO-8859-6"
		case 106 : return QStringList() << "utf8" << "utf8x"; // "UTF-8"
		//case 109 : return QStringList(); // "ISO-8859-13"
		//case 110 : return QStringList(); // "ISO-8859-14"
		case 111 : return QStringList() << "latin9"; // "ISO-8859-15"
		case 112 : return QStringList() << "latin10"; // "ISO-8859-16"
		//case 113 : return QStringList(); // "GBK"
		//case 114 : return QStringList(); // "GB18030"
		//case 1013 : return QStringList(); // "UTF-16BE"
		//case 1014 : return QStringList(); // "UTF-16LE"
		//case 1015 : return QStringList(); // "UTF-16"
		//case 1017 : return QStringList(); // "UTF-32"
		//case 1018 : return QStringList(); // "UTF-32BE"
		//case 1019 : return QStringList(); // "UTF-32LE"
		//case 2004 : return QStringList(); // "roman8"
		case 2009 : return QStringList() << "cp850"; // "IBM850"
		//case 2025 : return QStringList(); // "GB2312"
		//case 2026 : return QStringList(); // "Big5"
		//case 2084 : return QStringList(); // "KOI8-R"
		case 2086 : return QStringList() << "cp866"; // "IBM866"
		//case 2088 : return QStringList(); // "KOI8-U"
		//case 2101 : return QStringList(); // "Big5-HKSCS"
		//case 2107 : return QStringList(); // "TSCII"
		case 2250 : return QStringList() << "cp1250"; // "windows-1250"
		case 2251 : return QStringList() << "cp1251"; // "windows-1251"
		case 2252 : return QStringList() << "cp1252" << "ansinew"; // "windows-1252"
		//case 2253 : return QStringList(); // "windows-1253"
		//case 2254 : return QStringList(); // "windows-1254"
		//case 2255 : return QStringList(); // "windows-1255"
		//case 2256 : return QStringList(); // "windows-1256"
		case 2257 : return QStringList() << "cp1257"; // "windows-1257"
		//case 2258 : return QStringList(); // "windows-1258"
		//case 2259 : return QStringList(); // "TIS-620"
		//case -165 : return QStringList(); // "WINSAMI2"
		case -168 : return QStringList() << "applemac"; // "Apple Roman"
		//case -874 : return QStringList(); // "IBM874"
		//case -3008 : return QStringList(); // "Iscii-Mlm"
		//case -3007 : return QStringList(); // "Iscii-Knd"
		//case -3006 : return QStringList(); // "Iscii-Tlg"
		//case -3005 : return QStringList(); // "Iscii-Tml"
		//case -3004 : return QStringList(); // "Iscii-Ori"
		//case -3003 : return QStringList(); // "Iscii-Gjr"
		//case -3002 : return QStringList(); // "Iscii-Pnj"
		//case -3001 : return QStringList(); // "Iscii-Bng"
		//case -3000 : return QStringList(); // "Iscii-Dev"
		//case -949 : return QStringList(); // "cp949"
	}
	// *INDENT-ON*  (astyle-config)
	return QStringList();
}

QTextCodec *guessEncodingBasic(const QByteArray &data, int *outSure)
{
	const char *str = data.data();
	int size = data.size();
	QTextCodec *guess = 0;
	int sure = 1;
	if (size > 0) {
		unsigned char prev = str[0];
		int goodUtf8 = 0;
		int badUtf8 = 0;
		int badIso1 = 0;
		int utf16le = 0, utf16be = 0;
		if (prev >= 0x80 && prev <= 0x9F) badIso1++;
		for (int i = 1; i < size; i++) {
			unsigned char cur = str[i];
			if (cur >= 0x80 && cur <= 0x9F) badIso1++;
			if ((cur & 0xC0) == 0x80) {
				if ((prev & 0xC0) == 0xC0) goodUtf8++;
				else if ((prev & 0x80) == 0x00) badUtf8++;
			} else {
				if ((prev & 0xC0) == 0xC0) badUtf8++;
				//if (cur==0) { if (i & 1 == 0) utf16be++; else utf16le++;}
				if (prev == 0) {
					if ((i & 1) == 1) utf16be++;
					else utf16le++;
				}
			}
			prev = cur;
		}
		// less than 0.1% of the characters can be wrong for utf-16 if at least 1% are valid (for English text)
		if (utf16le > utf16be) {
			if (utf16be <= size / 1000 && utf16le >= size / 100 && utf16le >= 2) {
				guess = QTextCodec::codecForMib(MIB_UTF16LE);
				sure = 2;
			}
		} else {
			if (utf16le <= size / 1000 && utf16be >= size / 100 && utf16be >= 2) {
				guess = QTextCodec::codecForMib(MIB_UTF16BE);
				sure = 2;
			}
		}
		if (!guess) {
			if (goodUtf8 > 10 * badUtf8) {
				guess = QTextCodec::codecForMib(MIB_UTF8);
				sure = 2;
			} else {
				if (badIso1 > 0) guess = QTextCodec::codecForMib(MIB_WINDOWS1252);
				else guess = QTextCodec::codecForMib(MIB_LATIN1);
				if (badUtf8 == 0) sure = 0;
			}
		}
	} else sure = 0;
	if (outSure) *outSure = sure;
	return guess;
}

void LatexParser::guessEncoding(const QByteArray &data, QTextCodec *&guess, int &sure)
{
	if (guess && (guess->mibEnum() == MIB_UTF16LE || guess->mibEnum() == MIB_UTF16BE)) {
		sure = 100;
		return;
	}
	int headerSize = data.indexOf("\\begin{document}");
	if (headerSize == -1) headerSize = data.size();
	//search for % *!TeX +encoding *= *...\n
	//slow c like search, without encoding we can't get a qstring, and bytearray neither supports
	//regexp nor case insensitive search
	int index = data.indexOf('=');
	static const char *searchedLC = "%!tex encoding";
	static const char *searchedUC = "%!TEX ENCODING";
	static const int searchedLast = 13;
	Q_ASSERT(searchedLC[searchedLast] == 'g');
	while (index >= 0 && index < headerSize) {
		int temp = index - 1;
		int sp = searchedLast;
		const char *d = data.constData();
		for (; temp >= 0 && sp >= 0; temp--)
			if (searchedLC[sp] == d[temp]) sp--;
			else if (searchedUC[sp] == d[temp]) sp--;
			else if (d[temp] == ' ') ;
			else break;
		if (sp == -1) {
			int end = lineEnd(data, index);
			QByteArray encName = data.mid(index + 1, end - index - 1).trimmed();
			QTextCodec *codec = QTextCodec::codecForName(encName);
			if (!codec)
				codec = QTextCodecForTeXShopName(encName.toLower());
			if (codec) {
				sure = 100;
				guess = codec;
				return;
			}
		}
		index = data.indexOf('=', index + 1);
	}

	QString encoding = getEncodingFromPackage(data, headerSize, "inputenc");
	if (encoding.isEmpty())
		encoding = getEncodingFromPackage(data, headerSize, "inputenx");
	if (!encoding.isEmpty()) {
		QTextCodec *codec = QTextCodecForLatexName(encoding);
		if (codec) {
			sure = 100;
			guess = codec;
			return;
		}
	}
	return;
}

int LatexParser::lineStart(const QByteArray &data, int index)
{
	int n = qMax(data.lastIndexOf('\n', index), data.lastIndexOf('\r', index));
	int o = data.lastIndexOf("\x20\x29", index);
	if (n < 0 && o < 0) return 0;
	if (n > o) return n + 1; // skip over character
	else return n + 2; // skip over both chars
}

int LatexParser::lineEnd(const QByteArray &data, int index)
{
	int n = data.indexOf('\n', index);
	int r = data.indexOf('\r', index);
	if (n < 0) n = r; // prevent non-existing value (-1) to be smaller than existing one in qMin
	else if (r < 0) r = n;
	n = qMin(n, r);

	r = data.indexOf("\x20\x29", index); // unicode paragraph separator, note this is equivalent to " )" in ASCII but this duplication is ok for the current usecase of lineEnd()
	if (n < 0) n = r;
	else if (r < 0) r = n;
	n = qMin(n, r);
	if (n >= 0) return n;
	return data.size();
}

/*! search for first \usepackage[.*]{<packageName>} outside of a comment
 * returns the string inside the square brackets
 */
QString LatexParser::getEncodingFromPackage(const QByteArray &data, int headerSize, const QString &packageName)
{
	QByteArray packageEndToken(QString("]{%1}").arg(packageName).toLatin1());
	QByteArray packageStartToken("\\usepackage[");
	int index = data.indexOf(packageEndToken);
	while (index >= 0 && index < headerSize) {
		int lStart = lineStart(data, index);
		int lEnd = lineEnd(data, index);
		QByteArray line(data.mid(lStart, lEnd - lStart));
		int encEnd = index - lStart;
		int encStart = line.lastIndexOf(packageStartToken, encEnd);
		if (encStart >= 0) {
			encStart += packageStartToken.length();
			int commentStart = line.lastIndexOf('%', encEnd);
			if (commentStart < 0) {
				return QString(line.mid(encStart, encEnd - encStart));
			}
		}
		index = data.indexOf(packageEndToken, index + 1);
	}
	return QString();
}

void LatexParser::append(const LatexParser &elem)
{
	QHash<QString, QSet<QString> >::const_iterator i = elem.possibleCommands.constBegin();
	while (i != elem.possibleCommands.constEnd()) {
		QString key = i.key();
		QSet<QString> set = i.value();
		possibleCommands[key].unite(set);
		++i;
	}
	foreach (const QString key, elem.environmentAliases.keys()) {
		QStringList values = elem.environmentAliases.values(key);
		foreach (const QString value, values) {
			if (!environmentAliases.contains(key, value))
				environmentAliases.insert(key, value);
		}
	}
	specialTreatmentCommands.unite(elem.specialTreatmentCommands);
	specialDefCommands.unite(elem.specialDefCommands);
	commandDefs.unite(elem.commandDefs);
	mapSpecialArgs.unite(elem.mapSpecialArgs);
}

void LatexParser::clear()
{
	init();
}

void LatexParser::substract(const LatexParser &elem)
{
	QHash<QString, QSet<QString> >::const_iterator i = elem.possibleCommands.constBegin();
	while (i != elem.possibleCommands.constEnd()) {
		QString key = i.key();
		QSet<QString> set = i.value();
		possibleCommands[key].subtract(set);
		++i;
	}
	foreach (QString key, elem.commandDefs.keys()) {
		commandDefs.remove(key);
	}
}

void LatexParser::importCwlAliases()
{
	QString fn = findResourceFile("completion/cwlAliases.dat");
	QFile tagsfile(fn);
	if (tagsfile.open(QFile::ReadOnly)) {
		QString line;
		QString alias;
		while (!tagsfile.atEnd()) {
			line = tagsfile.readLine().trimmed();
			if (line.startsWith("#"))
				continue;
			if (line.endsWith(":")) {
				alias = line.left(line.length() - 1);
				continue;
			}
			if (!alias.isEmpty())
				packageAliases.insertMulti(alias, line);
		}
	}
}

LatexReader::LatexReader(): index(0), wordStartIndex(0), lp(&LatexParser::getInstance())
{
	Q_ASSERT(this->lp);
}

LatexReader::LatexReader(const QString &line): lp(&LatexParser::getInstance())
{
	Q_ASSERT(this->lp);
	setLine(line);
}

LatexReader::LatexReader(const LatexParser &lp, const QString &line): lp(&lp)
{
	Q_ASSERT(this->lp);
	setLine(line);
}

LatexReader::LatexReader(const LatexParser &lp, const QString &line, QMap<QString, QString> &replacementList): lp(&lp)
{
	Q_ASSERT(this->lp);
	setLine(line);
	mReplacementList = replacementList;
}
/*! Returns the next word (giving meaning to the nextToken tokens)
 * line: line to be examined
 * index: start index as input and returns the first character after the found word
 * outWord: found word (length can differ from index - wordStartIndex for text words)
 * wordStartIndex: start of the word
 * returnCommands: if this is true it returns \commands (NW_COMMAND), "normal" "text"  NW_TEXT and % (NW_COMMENT)  [or NW_NOTHING at the end]
 *                 "    "  is false it only returns normal text (NW_TEXT, without things like filenames after \include), environment names
 *                           (NW_ENVIRONMENT, they are treated as text in the other mode) and % (NW_COMMENT)       [or NW_NOTHING at the end]
 * \return the type of outWord
 * \warning obsolete with lexer based token system
 */
LatexReader::NextWordFlag LatexReader::nextWord(bool returnCommands)
{
	int reference = -1;
	bool inOption = false;
	bool inEnv = false;
	bool inReferenz = false;
	int inReferenzExt = 0;
	while ((wordStartIndex = nextToken(line, index, inEnv, !inReferenz)) != -1) {
		word = line.mid(wordStartIndex, index - wordStartIndex);
		if (word.length() == 0) return NW_NOTHING; //should never happen
		switch (word.at(0).toLatin1()) {
		case '%':
			return NW_COMMENT; //return comment start
		case '[':
			if (!lastCommand.isEmpty()) inOption = true;
			break;
		case ']':
			inOption = false;
			break;
		case '{':
			if (reference != -1)
				reference = wordStartIndex + 1;
			if (!lastCommand.isEmpty()) inOption = true;
			if (lp->environmentCommands.contains(lastCommand)) inEnv = true;
			break; //ignore
		case '}':
			if (inReferenzExt > 1) {
				inReferenzExt--;
			} else {
				if (reference != -1) {
					NextWordFlag result = NW_NOTHING;
					if (lp->possibleCommands["%ref"].contains(lastCommand)) result = NW_REFERENCE;
					else if (lp->possibleCommands["%label"].contains(lastCommand)) result = NW_LABEL;
					else if (lp->possibleCommands["%cite"].contains(lastCommand)) result = NW_CITATION;
					else if (lp->possibleCommands["%usepackage"].contains(lastCommand)) result = NW_PACKAGE;
					else if (lp->possibleCommands["%citeExtendedCommand"].contains(lastCommand)) result = NW_CITATION;
					if (result != NW_NOTHING) {
						wordStartIndex = reference;
						--index;
						word = line.mid(reference, index - reference);
						return result;
					}
				}
				lastCommand = "";
				inOption = false;
				inEnv = false;
			}
			break;//command doesn't matter anymore
		case '$':
		case '^':
		case '&':
			return NW_COMMAND;
		case '_':
			if (!inOption) {
				return NW_COMMAND;
			}
			break;
		case '\\':
			if (word.length() == 1 || !(EscapedChars.contains(word.at(1)) || CharacterAlteringChars.contains(word.at(1)))) {
				if (returnCommands) return NW_COMMAND;
				if (lp->possibleCommands["%ref"].contains(word) || lp->possibleCommands["%label"].contains(word) || lp->possibleCommands["%cite"].contains(word) || lp->possibleCommands["%usepackage"].contains(word)) {
					reference = index; //todo: support for nested brackets like \cite[\xy{\ab{s}}]{miau}
					lastCommand = word;
					inReferenz = true;
				}
				if (lp->possibleCommands["%citeExtendedCommand"].contains(word)) {
					QString line;
					foreach (line, lp->possibleCommands["%citeExtended"]) {
						if (line.startsWith(word))
							break;
						line.clear();
					}
					if (!line.isEmpty()) {
						reference = index; //todo: support for nested brackets like \cite[\xy{\ab{s}}]{miau}
						lastCommand = word;
						line = line.remove(QRegExp("[.*]"));
						int pos = line.indexOf("%<bibid%>");
						line = line.left(pos);
						inReferenzExt = line.count("{");
					}
				}
				if (lp->optionCommands.contains(lastCommand) || lastCommand.isEmpty() || word == "\\begin" || word == "\\end") {
					lastCommand = word;
				}
				break;
			} else {
				;   //first character is escaped, fall through to default case
			}
		default:
			//if (reference==-1) {
			if (!inOption && !lastCommand.isEmpty()) {
				inOption = false;
				lastCommand = "";
			}
			//if (word.length() == 2 && word[0] == '"' && CommonEOW.contains(word[1]))
			//	return NW_PUNCTATION; //some quotation mark
			if (word.length() > 1 && (word.contains('\\') || word.contains('"'))) {
				//word=latexToPlainWord(word); //remove special chars
				word = latexToPlainWordwithReplacementList(word, mReplacementList); //remove special chars
				if (word.isEmpty()) continue;
			}
			if (lp->environmentCommands.contains(lastCommand))
				return NW_ENVIRONMENT;
			if (lastCommand.isEmpty() || lp->optionCommands.contains(lastCommand)) {
				if (word.length() && Punctation.contains(word[0])) {
					if (word.length() > 1) word = word[0];
					return NW_PUNCTATION;
				}
				return NW_TEXT;
			}
			//}
		}
	}
	return NW_NOTHING;
}

/*! searches the next text words and ignores command options, environments or comments
 * returns false if none is found
 * \warning obsolete with lexer based token system
 */
bool LatexReader::nextTextWord()
{
	NextWordFlag flag = NW_PUNCTATION;
	//flag can be nothing, text, comment, environment/punctation
	//text/comment returns false, text returns true, environment/punctation is ignored
	while (flag == NW_ENVIRONMENT || flag == NW_PUNCTATION)
		flag = nextWord(false);
	return flag == NW_TEXT;
}

const QString &LatexReader::getLine() const
{
	return line;
}

void LatexReader::setLine(const QString &line)
{
	this->line = line;
	this->index = 0;
	this->wordStartIndex = 0;
}

typedef QPair<int, int> PairIntInt;

LatexPackage loadCwlFile(const QString fileName, LatexCompleterConfig *config, QStringList conditions)
{
	CodeSnippetList words;
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	LatexPackage package;

	QFile tagsfile("cwl:" + fileName);
	bool skipSection = false;
	if (tagsfile.exists() && tagsfile.open(QFile::ReadOnly)) {
		QString line;
		QTextStream stream(&tagsfile);
		stream.setCodec("UTF-8");
		QRegExp rxCom("^(\\\\\\w+\\*?)(\\[.+\\])*\\{(.*)\\}");  // expression for \cmd[opt]{arg} (cmd may be starred, [opt] can appear arbitrary often)
		QRegExp rxCom2("^(\\\\\\w+\\*?)\\[(.+)\\]");            // expression for \cmd[opt]      (cmd may be starred)
		QRegExp rxCom3("^(\\\\\\w+\\*?)");                      // expression for \cmd           (cmd may be starred)
		rxCom.setMinimal(true);
		QStringList keywords;
		keywords << "text" << "title" << "%<text%>" << "%<title%>";
		QStringList specialTreatment;
		specialTreatment << "color";
		QString keyvals;
		while (!stream.atEnd()) {
			line = stream.readLine().trimmed();
			if (line.startsWith("#endif")) {
				// end of conditional section
				skipSection = false;
				continue;
			}
			if (line.startsWith("#ifOption:")) {
				QString condition = line.mid(10);
				skipSection = !(conditions.contains(condition) || conditions.contains(condition+"=true"));
				continue;
			}
			if (skipSection) // skip conditional sections (if condition is not met)
				continue;

			if (line.startsWith("#include:")) {
				//include additional cwl file
				QString fn = line.mid(9);
				if (!fn.isEmpty()) {
					if (fileName != fn + ".cwl" && !package.requiredPackages.contains(fn + ".cwl"))
						package.requiredPackages << fn + ".cwl";
				}
			}
			if (line.startsWith("#keyvals:")) {
				// start reading keyvals
				keyvals = line.mid(9);
				continue;
			}
			if (line.startsWith("#endkeyvals")) {
				// end of reading keyvals
				keyvals.clear();
				continue;
			}

			if (!keyvals.isEmpty()) {
				// read keyval (name stored in "keyvals")
				package.possibleCommands["key%" + keyvals] << line;
				QString key;
				CommandDescription cd = extractCommandDefKeyVal(line, key);
				if (cd.args > 0) {
					if (key.endsWith("="))
						key.chop(1);
					package.commandDescriptions.insert(keyvals + "/" + key, cd);
				}
				continue;
			}
			if (line.startsWith("#repl:")) {
				// start reading keyvals
				package.possibleCommands["%replace"] << line.mid(6);
				continue;
			}

			if (!line.isEmpty() && !line.startsWith("#") && !line.startsWith(" ")) {
				//hints for commands usage (e.g. in mathmode only) are separated by #
				int sep = line.indexOf('#');
				QString valid;
				QStringList env;
				QString definition;
				bool uncommon = false;
				bool hideFromCompletion = false;
				CodeSnippet::Type type = CodeSnippet::none;
				if (sep > -1) {
					valid = line.mid(sep + 1);
					line = line.left(sep);
					if (valid.startsWith("*")) {
						valid = valid.mid(1);
						uncommon = true;
					}
					// second time split for specialDef
					int sep = valid.indexOf('#');
					if (sep > -1) {
						definition = valid.mid(sep + 1);
						valid = valid.left(sep);
					}
					// normal valid
					if (valid.startsWith("/")) {
						env = valid.mid(1).split(',');
						valid = "e";
					}
					if (valid.contains("\\")) {
						int i = valid.indexOf("\\");
						QString zw = valid.mid(i + 1);
						env = zw.split(',');
						valid = valid.left(i);
					}
					if (valid.contains('S')) {
						hideFromCompletion = true;
						valid.remove('S');
					}
				}

				// parse for spell checkable commands
				int res = rxCom.indexIn(line);
				if (keywords.contains(rxCom.cap(3))) {
					package.optionCommands << rxCom.cap(1);
				}

				if (specialTreatment.contains(rxCom.cap(3))) {
					package.specialTreatmentCommands[rxCom.cap(1)].insert(qMakePair(rxCom.cap(3), 1));
				}
				rxCom2.indexIn(line); // for commands which don't have a braces part e.g. \item[text]
				int res3 = rxCom3.indexIn(line); // for commands which don't have a options either e.g. \node (asas)

				// get commandDefinition
				CommandDescription cd = extractCommandDef(line, valid);
				QString cmd = rxCom3.cap(1);
				if (cmd == "\\begin") {
					if (!package.commandDescriptions.contains(cmd)) {
						// one insertion of a general \begin-command
						CommandDescription cd;
						cd.args = 1;
						cd.argTypes << Tokens::beginEnv;
						package.commandDescriptions.insert(cmd, cd);
					}
					cmd = rxCom.cap();
				}
				if (package.commandDescriptions.contains(cmd)) {
					CommandDescription cd_old = package.commandDescriptions.value(cmd);
                    if(cd_old.args == cd.args && cd_old.optionalArgs > cd.optionalArgs ){
                        cd = cd_old;
                    }
                    if (cd_old.args < cd.args && cd_old.args>0){
						cd = cd_old;
                        qDebug()<<"inconsistent command arguments:"<<cmd<<fileName;
                        // commands with different numbers of mandatory arguments are not distinguished by the parser and lead to unreliable results.
                        // the lower numer of mandatory arguments is handled only (however not an command with zero arguments)
                        // this leads to incomplete handling e.g. for hyperref (which disregards any standards and distinguishes command based on the presence of an optional argument)
					}

				}
				package.commandDescriptions.insert(cmd, cd);

				valid.remove('N'); // remove newtheorem declaration


				if (keywords.contains(rxCom2.cap(2))) {
					package.optionCommands << rxCom2.cap(1);
				}
				if (valid.contains('d')) { // definition command
					if (res > -1) {
						package.possibleCommands["%definition"] << rxCom.cap(1);
					}
					valid.remove('d');
				}
				if (valid.contains('i')) { // include like command
					if (res > -1) {
						package.possibleCommands["%include"] << rxCom.cap(1);
					}
					valid.remove('i');
				}
				if (valid.contains('l')) { // label command
					if (res > -1) {
						package.possibleCommands["%label"] << rxCom.cap(1);
					}
					valid.remove('l');
				}
				if (valid.contains('r')) { // ref command
					if (res > -1) {
						package.possibleCommands["%ref"] << rxCom.cap(1);
					}
					valid.remove('r');
				}
				if (valid.contains('L')) {
					if (valid.contains("L0")) {
						valid.remove("L0");
						if (res > -1) {
							package.possibleCommands["%structure0"] << rxCom.cap(1);
						}
					} else if (valid.contains("L1")) {
						valid.remove("L1");
						if (res > -1) {
							package.possibleCommands["%structure1"] << rxCom.cap(1);
						}
					} else if (valid.contains("L2")) {
						valid.remove("L2");
						if (res > -1) {
							package.possibleCommands["%structure2"] << rxCom.cap(1);
						}
					} else if (valid.contains("L3")) {
						valid.remove("L3");
						if (res > -1) {
							package.possibleCommands["%structure3"] << rxCom.cap(1);
						}
					} else if (valid.contains("L4")) {
						valid.remove("L4");
						if (res > -1) {
							package.possibleCommands["%structure4"] << rxCom.cap(1);
						}
					} else if (valid.contains("L5")) {
						valid.remove("L5");
						if (res > -1) {
							package.possibleCommands["%structure5"] << rxCom.cap(1);
						}
					}else if (valid.contains("L6")) {
						valid.remove("L6");
						if (res > -1) {
							package.possibleCommands["%structure6"] << rxCom.cap(1);
						}
					}else if (valid.contains("L7")) {
						valid.remove("L7");
						if (res > -1) {
							package.possibleCommands["%structure7"] << rxCom.cap(1);
						}
					}else if (valid.contains("L8")) {
						valid.remove("L8");
						if (res > -1) {
							package.possibleCommands["%structure8"] << rxCom.cap(1);
						}
					}else if (valid.contains("L9")) {
						valid.remove("L9");
						if (res > -1) {
							package.possibleCommands["%structure9"] << rxCom.cap(1);
						}
					}
				}
				if (valid.contains('V')) { // verbatim command
					if (res > -1) {
						package.possibleCommands["%verbatimEnv"] << rxCom.cap(3);
                                                env<< "verbatim";
					}
					valid.remove('V');
				}
				if (valid.contains('s')) { // special def
					if (res > -1) {
						package.specialDefCommands.insert(rxCom.cap(1), definition);
					} else {
						if (res3 > -1)
							package.specialDefCommands.insert(rxCom3.cap(1), definition);
					}
					if (definition.startsWith('%')) {
						if (config)
							config->specialCompletionKeys.insert(definition);
					} else {
						if (definition.length() > 2) {
							QString helper = definition.mid(1, definition.length() - 2);
							if (helper.startsWith('%')) {
								if (config)
									config->specialCompletionKeys.insert(helper);
							}
						}
					}
					valid.remove('s');
				}
				if (valid.contains('c')) { // cite command
					if (res > -1) {
						package.possibleCommands["%cite"] << rxCom.cap(1);
						// replace argument (possibly keylist) with @
						int p = rxCom.pos(3);
						int l = rxCom.cap(3).length();
						if (p >= 0) {
							line.replace(p, l, "@");
						}
					}
					valid.remove('c');
				}
				if (valid.contains('C')) { // cite command
					if (res > -1) {
						if (!line.contains("%")) {
							int start = 0;
							if (line.startsWith("\\begin")) {
								start = line.indexOf("}") + 1;
							}
							//add placeholders to brackets like () to (%<..%>)
							const QString brackets = "{}[]()<>";
							int lastOpen = -1, openType = -1;
							for (int i = start; i < line.size(); i++) {
								int index = brackets.indexOf(line[i]);
								if (index >= 0) {
									if (index % 2 == 0) {
										lastOpen = i;
										openType = index / 2;
									} else {
										if (lastOpen == -1 || openType != index / 2)
											continue;
										if (lastOpen == i - 1)
											continue;
										line.insert(lastOpen + 1, "%<");
										i += 2;
										line.insert(i, "%>");
										lastOpen = -1;
										i += 2;
									}
								}
							}
						}
						package.possibleCommands["%citeExtended"] << line.simplified();
						if (!line.startsWith("\\begin")) // HANDLE begin extra
							package.possibleCommands["%citeExtendedCommand"] << rxCom.cap(1);
						line.replace("%<bibid%>", "@");
						//hideFromCompletion=true;
					}
					valid.remove('C');
				}
				if (valid.contains('g')) { // definition command
					if (res > -1) {
						package.possibleCommands["%graphics"] << rxCom.cap(1);
					}
					valid.remove('g');
				}
				if (valid.contains('u')) { // usepackage command
					if (res > -1) {
						package.possibleCommands["%usepackage"] << rxCom.cap(1);
					}
					valid.remove('u');
				}
				if (valid.contains('b')) { // usepackage command
					if (res > -1) {
						package.possibleCommands["%bibliography"] << rxCom.cap(1);
						package.possibleCommands["%file"] << rxCom.cap(1);
					}
					valid.remove('b');
				}
				if (valid.contains('U')) { // url command
					if (res > -1) {
						package.possibleCommands["%url"] << rxCom.cap(1);
					}
					valid.remove('U');
				}
				if (valid.contains('D')) { // todo command
					if (res > -1) {
						package.possibleCommands["%todo"] << rxCom.cap(1);
					}
					valid.remove('D');
				}
				if (valid.contains('B')) { // color
					package.possibleCommands["%color"] << line;
					hideFromCompletion = true;
				}
				if (valid.contains('L')) { // a length/height
					type = CodeSnippet::length;
					valid.remove('L');
				}
				// normal commands for syntax checking
				// will be extended to distinguish between normal and math commands
				if (valid.isEmpty() || valid.contains('n')) {
					if (res > -1) {
						if (rxCom.cap(1) == "\\begin" || rxCom.cap(1) == "\\end") {
							package.possibleCommands["normal"] << rxCom.cap(1) + "{" + rxCom.cap(3) + "}";
						} else {
							package.possibleCommands["normal"] << rxCom.cap(1);
						}
					} else {
						if (!cmd.isEmpty())
							package.possibleCommands["normal"] << cmd;
						else
							package.possibleCommands["normal"] << line.simplified();
					}
				}
				if (valid.contains('m')) { // math commands
					if (res > -1) {
						if (rxCom.cap(1) == "\\begin" || rxCom.cap(1) == "\\end") {
							package.possibleCommands["math"] << rxCom.cap(1) + "{" + rxCom.cap(3) + "}";
						} else {
							package.possibleCommands["math"] << rxCom.cap(1);
						}
					} else {
						if (!cmd.isEmpty())
							package.possibleCommands["math"] << cmd;
						else
							package.possibleCommands["math"] << line.simplified();
					}
				}
				if (valid.contains('t')) { // tabular commands
					if (res > -1) {
						if (rxCom.cap(1) == "\\begin" || rxCom.cap(1) == "\\end") {
							package.possibleCommands["tabular"] << rxCom.cap(1) + "{" + rxCom.cap(3) + "}";
							package.possibleCommands["array"] << rxCom.cap(1) + "{" + rxCom.cap(3) + "}";
						} else {
							package.possibleCommands["tabular"] << rxCom.cap(1);
							package.possibleCommands["array"] << rxCom.cap(1);
						}
					} else {
						if (cmd.isEmpty())
							cmd = line.simplified();
						package.possibleCommands["tabular"] << cmd;
						package.possibleCommands["array"] << cmd;
					}
				}
				if (valid.contains('T')) { // tabbing support
					if (res == -1) {
						package.possibleCommands["tabbing"] << cmd;
					}
				}
				if (valid.contains('e') && !env.isEmpty()) { // tabbing support
					if (res == -1) {
						foreach (const QString &elem, env)
							package.possibleCommands[elem] << cmd;
					} else {
						QString cmd = rxCom.cap(1);
						if (cmd == "\\begin" || cmd == "\\end") {
							cmd = line.simplified();
						}
						foreach (const QString &elem, env)
							package.possibleCommands[elem] << cmd;
					}
				}
				if (!valid.contains('e') && !env.isEmpty()) { // set env alias
					if (res > -1) {
						if (rxCom.cap(1) == "\\begin") {
							QString envName = rxCom.cap(3);
							if (!envName.isEmpty()) {
								foreach (const QString &elem, env)
									package.environmentAliases.insert(rxCom.cap(3), elem);
							}
						}
					}
				}
				// normal parsing for completer
				if (hideFromCompletion)
					continue; // command for spell checking only (auto parser)
				// remove special option classification e.g. %l
				line.remove(QRegExp("%[a-zA-Z]+")); // not n
				if (!line.contains("%")) {
					//add placeholders to brackets like () to (%<..%>)
					const QString brackets = "{}[]()<>";
					int lastOpen = -1, openType = -1;
					for (int i = 0; i < line.size(); i++) {
						int index = brackets.indexOf(line[i]);
						if (index >= 0) {
							if (index % 2 == 0) {
								lastOpen = i;
								openType = index / 2;
							} else {
								if (lastOpen == -1 || openType != index / 2)
									continue;
								if (i - lastOpen < 2) // ignore empty arguments, feature request 888
									continue;
								if (i - lastOpen == 2 && line.mid(lastOpen + 1, 1) == "@") //ignore single @ (to be replaced with bibid in completer)
									continue;
								line.insert(lastOpen + 1, "%<");
								i += 2;
								line.insert(i, "%>");
								/*if (lastOpen+2 == i-1) {  // deactivated, feature request 888
								    line.insert(i, QApplication::translate("CodeSnippet", "something"));
								    i+=QApplication::translate("CodeSnippet", "something").length();
								}*/
								lastOpen = -1;
								i += 2;
							}
						}
					}
					if (line.startsWith("\\begin") || line.startsWith("\\end")) {
						int i = line.indexOf("%<", 0);
						line.replace(i, 2, "");
						i = line.indexOf("%>", 0);
						line.replace(i, 2, "");
						if (line.endsWith("\\item"))
							line.chop(5);

					}
				}

				if (!words.contains(line)) {
					CodeSnippet cs = CodeSnippet(line);
					CodeSnippetList::iterator it = qLowerBound(words.begin(), words.end(), cs);
					it = words.insert(it, cs);
					uint hash = qHash(line);
					int len = line.length();
					it->index = hash;
					it->snippetLength = len;
					it->usageCount = uncommon ? -1 : 0;
					it->type = type;
					if (config) {
						QList<QPair<int, int> >res = config->usage.values(hash);
						foreach (const PairIntInt &elem, res) {
							if (elem.first == it->snippetLength) {
								it->usageCount = elem.second;
								break;
							}
						}
					}
				}
			}
		}
	} else {
		//qDebug() << "Completion file not found:" << fileName;
		package.packageName = "<notFound>";
		package.notFound = true;
	}

	QApplication::restoreOverrideCursor();
	package.completionWords = words;
	return package;
}

LatexPackage::LatexPackage() : notFound(false)
{
	completionWords.clear();
	packageName.clear();
}

QString LatexPackage::makeKey(const QString &cwlFilename, const QString &options)
{
	return QString("%1#%2").arg(options).arg(cwlFilename);
}

QString LatexPackage::keyToCwlFilename(const QString &key)
{
	int i = key.indexOf('#');
	if (i < 0) return key;
	else return key.mid(i + 1);
}

QString LatexPackage::keyToPackageName(const QString &key)
{
	// Workaround since there is currently no reliable way to determine the packageName from LatexPackage directly (the attribute with the same name contains the key and sometimes nothing).
	QString name = LatexPackage::keyToCwlFilename(key);
	if (name.endsWith(".cwl"))
		name.remove(name.length() - 4, 4);
	if (name.startsWith("class-"))
		name.remove(0, 6);
	return name;
}

QStringList LatexPackage::keyToOptions(const QString &key)
{
	int i = key.indexOf('#');
	if (i < 0) return QStringList();
	QString zw=key.left(i);
    QStringList result=zw.split(',');
    for(int k=0;k<result.size();k++){
        QString elem=result.value(k);
        if(elem.contains('%')){
           i=elem.indexOf('%');
           elem=elem.left(i);
        }
        elem=elem.simplified();
        result[k]=elem;
    }
    return result;
}

void LatexPackage::unite(LatexPackage &add, bool forCompletion)
{
	if (forCompletion) {
		completionWords.unite(add.completionWords); //expensive
		return;
	}
	optionCommands.unite(add.optionCommands);
	environmentAliases.unite(add.environmentAliases);
	specialTreatmentCommands.unite(add.specialTreatmentCommands);
	specialDefCommands.unite(add.specialDefCommands);
	//commandDescriptions.unite(add.commandDescriptions); //expensive
	foreach (QString elem, add.commandDescriptions.keys()) {
		if (commandDescriptions.contains(elem)) {
			CommandDescription cd = commandDescriptions.value(elem);
			CommandDescription cd_neu = add.commandDescriptions.value(elem);
			if (cd_neu.args > cd.args) {
				//simple selection criteria
				commandDescriptions.insert(elem, add.commandDescriptions.value(elem));
            }else{
                // when same number of args (>0), general arg is considered inferior
                if( (cd_neu.args==cd.args) && (cd.args>0)){
                    if(cd_neu.optionalArgs>cd.optionalArgs){
                        // same number of arguments but more optional arguments
                        commandDescriptions.insert(elem, add.commandDescriptions.value(elem));
                    }else{
                        if(cd_neu.optionalArgs==cd.optionalArgs){
                            bool override=true;
                            for(int i=0;i<cd.args;i++){
                                if(cd_neu.argTypes.at(i)==Tokens::generalArg)
                                    override=false;
                            }
                            for(int i=0;i<cd.optionalArgs;i++){
                                if(cd_neu.optTypes.at(i)==Tokens::generalArg)
                                    override=false;
                            }
                            if(override)
                                commandDescriptions.insert(elem, add.commandDescriptions.value(elem));
                        }
                    }
                }
            }
		} else {
			commandDescriptions.insert(elem, add.commandDescriptions.value(elem));
		}
	}

	//possibleCommands.unite(add.possibleCommands);
	foreach (const QString &elem, add.possibleCommands.keys()) { //expensive
		QSet<QString> set2 = add.possibleCommands[elem];
		QSet<QString> set = possibleCommands[elem];
		set.unite(set2);
		possibleCommands[elem] = set;
	}
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

QString getArg(const TokenList &tl, Tokens::TokenType type){
    for (int i = 0; i < tl.length(); i++) {
        Tokens tk = tl.at(i);

        if (tk.subtype==type) {
            QString result;
            QString line=tk.getText();
            if (Tokens::tkBraces().contains(tk.type)) {
                result = line.mid(1, line.length() - 2);
            }
            if (Tokens::tkOpen().contains(tk.type)) {
                result = line.mid( 1) + findRestArg(tk.dlh, Tokens::opposite(tk.type), RUNAWAYLIMIT);
            }
            if (Tokens::tkClose().contains(tk.type)) {
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

QString getArg(TokenList tl, QDocumentLineHandle *dlh, int argNumber, ArgumentList::ArgType type)
{
	// argNumber 0 -> first argument
    QDocument *doc=dlh->document();
    int lineNr=doc->indexOf(dlh);

	QList<Tokens::TokenType> tkTypes;
	if (type == ArgumentList::Mandatory) {
		tkTypes.append(Tokens::braces);
		tkTypes.append(Tokens::word);
		tkTypes.append(Tokens::command);
		tkTypes.append(Tokens::commandUnknown);
		tkTypes.append(Tokens::number);
		tkTypes.append(Tokens::openBrace);
	} else {
		tkTypes.append(Tokens::squareBracket);
		tkTypes.append(Tokens::openSquare);
	}
    int cnt=0;
	int k = 0;
    int level=0;
    if(!tl.isEmpty()){
        level=tl.first().level;
    }
    while( (lineNr)<doc->lineCount() && cnt<RUNAWAYLIMIT){
        QString line = dlh->text();
        for (int i = 0; i < tl.length(); i++) {
            Tokens tk = tl.at(i);
            if(tk.level>level)
                continue; //only use tokens from the same option-level

            if (tkTypes.contains(tk.type)) {
                QString result;
                if (Tokens::tkBraces().contains(tk.type)) {
                    result = line.mid(tk.start + 1, tk.length - 2);
                }
                if (Tokens::tkOpen().contains(tk.type)) {
                    result = line.mid(tk.start + 1, tk.length) + findRestArg(dlh, Tokens::opposite(tk.type), RUNAWAYLIMIT);
                }
                if (Tokens::tkClose().contains(tk.type)) {
                    result = line.mid(tk.start + 1, tk.length);
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
			}
        }
        lineNr++;
        dlh=doc->line(lineNr).handle();
        if(dlh)
            tl= dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
        cnt++;
    }


	return QString();
}

QString findRestArg(QDocumentLineHandle *dlh, Tokens::TokenType type, int count)
{
	// dlh is current line, next line will be checked here!!!
	if (count < 0)
		return QString(); // limit search depth
	QDocument *document = dlh->document();
	int index = document->indexOf(dlh);
	if (index + 1 >= document->lines())
		return QString(); // last line reached
	dlh = document->line(index + 1).handle();
	TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	QString result = dlh->text();
	for (int i = 0; i < tl.length(); i++) {
		Tokens tk = tl.at(i);
		if (tk.type == type) {
			// closing found
			return result.left(tk.start);
		}
		if (Tokens::tkClose().contains(tk.type)) {
			// wrong closing found/ syntax problem
			//return value anyway
			return result.left(tk.start + 1);
		}
	}
	return result + findRestArg(dlh, type, count - 1);
}
/// display tokentype for debugging
QDebug operator<<(QDebug dbg, Tokens::TokenType tk) {
	dbg << "TokenType(" << qPrintable(Tokens::tokenTypeName(tk)) << ")";
	return dbg;
}
/// display content of token for debugging
QDebug operator<<(QDebug dbg, Tokens tk) {
	dbg << qPrintable("Token(\"" + tk.getText() + "\"){"
					  + QString("type: %1, ").arg(Tokens::tokenTypeName(tk.type))
					  + QString("subtype: %1, ").arg(Tokens::tokenTypeName(tk.subtype))
					  + QString("arglevel: %1").arg(tk.argLevel)
					  + "}"
					  );
	return dbg;
}
/// display content of tokenlist for debugging
void qDebugTokenList(TokenList tl) {
	qDebug() << "TokenList:";
	foreach (const Tokens &tk, tl) {
		qDebug() << "  " << tk;
	}
}
/// text for token for easier debugging
QString Tokens::tokenTypeName(TokenType t) {
#define LITERAL_ENUM(e) case e: return #e;
	switch(t) {
	LITERAL_ENUM(none)
	LITERAL_ENUM(word)
	LITERAL_ENUM(command)
	LITERAL_ENUM(braces)
	LITERAL_ENUM(bracket)
	LITERAL_ENUM(squareBracket)
	LITERAL_ENUM(openBrace)
	LITERAL_ENUM(openBracket)
	LITERAL_ENUM(openSquare)
	LITERAL_ENUM(closeBrace)
	LITERAL_ENUM(closeBracket)
	LITERAL_ENUM(closeSquareBracket)
	LITERAL_ENUM(math)
	LITERAL_ENUM(comment)
	LITERAL_ENUM(commandUnknown)
	LITERAL_ENUM(label)
	LITERAL_ENUM(bibItem)
	LITERAL_ENUM(file)
	LITERAL_ENUM(imagefile)
	LITERAL_ENUM(bibfile)
	LITERAL_ENUM(keyValArg)
	LITERAL_ENUM(keyVal_key)
	LITERAL_ENUM(keyVal_val)
	LITERAL_ENUM(list)
	LITERAL_ENUM(text)
	LITERAL_ENUM(env)
	LITERAL_ENUM(beginEnv)
	LITERAL_ENUM(def)
	LITERAL_ENUM(labelRef)
	LITERAL_ENUM(package)
	LITERAL_ENUM(width)
	LITERAL_ENUM(placement)
	LITERAL_ENUM(colDef)
	LITERAL_ENUM(title)
	LITERAL_ENUM(url)
	LITERAL_ENUM(documentclass)
	LITERAL_ENUM(beamertheme)
	LITERAL_ENUM(packageoption)
	LITERAL_ENUM(color)
	LITERAL_ENUM(verbatimStart)
	LITERAL_ENUM(verbatimStop)
	LITERAL_ENUM(verbatim)
	LITERAL_ENUM(symbol)
	LITERAL_ENUM(punctuation)
	LITERAL_ENUM(number)
	LITERAL_ENUM(generalArg)
	LITERAL_ENUM(defArgNumber)
	LITERAL_ENUM(optionalArgDefinition)
	LITERAL_ENUM(definition)
	LITERAL_ENUM(defWidth)
	LITERAL_ENUM(labelRefList)
	LITERAL_ENUM(specialArg)
	LITERAL_ENUM(newTheorem)
	LITERAL_ENUM(newBibItem)
	LITERAL_ENUM(_end)
	default: return "UnknownTokenType";
	}
#undef LITERAL_ENUM
}
/*!
 * \brief define all possible group tokens
 */
QSet<Tokens::TokenType> Tokens::tkBraces()
{
	QSet<TokenType> result;
	result.insert(braces);
	result.insert(bracket);
	result.insert(squareBracket);
	return result;
}
/*! define tokens which describe a mandatory argument
 */
QSet<Tokens::TokenType> Tokens::tkArg()
{
	QSet<TokenType> result;
	result.insert(openBrace);
	result.insert(braces);
	result.insert(word);
	return result;
}
/*! define tokens which describe an optional argument
 */
QSet<Tokens::TokenType> Tokens::tkOption()
{
	QSet<TokenType> result;
	result.insert(squareBracket);
	result.insert(openSquare);
	return result;
}
/*!
 * \brief define open group tokens
 */
QSet<Tokens::TokenType> Tokens::tkOpen()
{
	QSet<TokenType> result;
	result.insert(openBrace);
	result.insert(openBracket);
	result.insert(openSquare);
	return result;
}
/*!
 * \brief define close group tokens
 */
QSet<Tokens::TokenType> Tokens::tkClose()
{
	QSet<TokenType> result;
	result.insert(closeBrace);
	result.insert(closeBracket);
	result.insert(closeSquareBracket);
	return result;
}
/*! define argument-types (tokens) which are a single argument
 * .e.g. \label{abc}
 */
QSet<Tokens::TokenType> Tokens::tkSingleArg()
{
	QSet<TokenType> result;
	result.insert(label);
	result.insert(labelRef);
	result.insert(url);
	result.insert(file);
	result.insert(imagefile);
	result.insert(env);
	result.insert(beginEnv);
	result.insert(documentclass);
	result.insert(beamertheme);
	result.insert(def);
	return result;
}
/*! define argument-types (tokens) which consist of comma-separated lists
 * .e.g. \usepackage{pck1,pck2}
 */
QSet<Tokens::TokenType> Tokens::tkCommalist()
{
	QSet<TokenType> result;
	result.insert(bibItem);
	result.insert(package);
	result.insert(packageoption);
	result.insert(bibfile);
	result.insert(labelRefList);
	return result;
}
/*! get opposite tokentype for a bracket type tokentype
 */
Tokens::TokenType Tokens::opposite(TokenType type)
{
	switch (type) {
	case closeBrace:
		return openBrace;
	case closeBracket:
		return openBracket;
	case closeSquareBracket:
		return openSquare;
	case openBrace:
		return closeBrace;
	case openBracket:
		return closeBracket;
	case openSquare:
		return closeSquareBracket;
	default:
		return none;
	}
}
/*!
 * \brief get close token for open or complete tokentype
 * \param type
 * \return closed tokentype
 */
Tokens::TokenType Tokens::closed(TokenType type)
{
	switch (type) {
	case closeBrace:
		return braces;
	case closeBracket:
		return bracket;
	case closeSquareBracket:
		return squareBracket;
	case openBrace:
		return braces;
	case openBracket:
		return bracket;
	case openSquare:
		return squareBracket;
	default:
		return none;
	}

}
/*!
 * \brief compare tokens
 * \param v
 * \return equal
 */
bool Tokens::operator ==(const Tokens &v) const
{
	return (this->dlh == v.dlh) && (this->length == v.length) && (this->level == v.level) && (this->type == v.type);
}

/*!
 * \brief get text which is represented by the token
 * \return text of token
 */
QString Tokens::getText()
{
	dlh->lockForRead();
	QString result = dlh->text().mid(start, length);
	dlh->unlock();
	return result;
}
Tokens::TokenType tokenTypeFromCwlArg(QString arg, QString definition)
{
	int i = arg.indexOf('%');
	// type from suffix
	if (i >= 0) {
		QString suffix = arg.mid(i);
		if (suffix == "%plain") return Tokens::generalArg;
		if (suffix == "%text") return Tokens::text;
		if (suffix == "%title") return Tokens::title;
		if (suffix == "%l") return Tokens::width;
		if (suffix == "%cmd") return Tokens::def;
		if (suffix == "%keyvals") return Tokens::keyValArg;
		if (suffix == "%ref") return Tokens::labelRef;
		if (suffix == "%labeldef") return Tokens::label;
		if (suffix == "%special") {
			Tokens::TokenType type = Tokens::specialArg;
			arg.chop(8);
			if (LatexParserInstance) {
				if (!LatexParserInstance->mapSpecialArgs.values().contains("%" + arg)) {
					int cnt = LatexParserInstance->mapSpecialArgs.count();
					LatexParserInstance->mapSpecialArgs.insert(cnt, "%" + arg);
					type = Tokens::TokenType(type + cnt);
				}
			}
			return type;
		}
	}
	// type from name
	if (arg == "text") return Tokens::text;
	if (arg == "title" || arg == "short title" ) return Tokens::title;
	if (arg == "package") return Tokens::package;
	if (arg == "cols" || arg == "preamble") return Tokens::colDef;
	if (arg == "color") return Tokens::color;
	if (arg == "width" || arg == "length" || arg == "height") return Tokens::width;
	if (arg == "bib files" || arg == "bib file") return Tokens::bibfile;
	if (arg == "command" || arg == "cmd") return Tokens::def;
	if (arg == "def" || arg == "definition" || arg == "begdef" || arg == "enddef") return Tokens::definition; // actual definition: \newcommand def defArgNumber definition
	if (arg == "args") return Tokens::defArgNumber;
	if (arg == "citekey") return Tokens::newBibItem;
	if (arg == "default") return Tokens::optionalArgDefinition;
	if (arg == "newlength") return Tokens::defWidth;
	if (arg == "file") return Tokens::file;
	if (arg == "imagefile") return Tokens::imagefile;
	if (arg.contains("URL")) return Tokens::url;
	if (arg.contains("keys") || arg == "keyvals" || arg == "%<options%>") return Tokens::keyValArg;
	if (arg == "options") return Tokens::packageoption;
	if (arg == "class") return Tokens::documentclass;
	if (arg == "beamertheme") return Tokens::beamertheme;
	if (arg == "keylist" || arg == "bibid") return Tokens::bibItem;
	if (arg == "placement" || arg == "position") return Tokens::placement;
    if (arg == "key"  && definition.contains('l')) return Tokens::label;
	if (arg == "key" || arg == "key1" || arg == "key2") return Tokens::labelRef;
	if ((arg == "envname" || arg=="environment name") && definition.contains('N')) return Tokens::newTheorem;
	if ((arg == "label" || arg == "%<label%>") && definition.contains('r')) return Tokens::labelRef;  // reference with keyword label
	if ((arg == "label" || arg == "%<label%>") && definition.contains('l')) return Tokens::label;
	if (arg == "labellist") return Tokens::labelRefList;
	return Tokens::generalArg;
}

/*!
\brief extract command defintion from cwl line

\a line contains a command with arguments.
The argument names have special meanings which are recognized by the function and used accordingly.

argument name | description
----------|----------
\em text or ends with \em \%text| The spellchecker will operate inside this argument (by default arguments are not spellchecked).
\em title or <em> short title</em>| The spellchecker will operate inside this argument (by default arguments are not spellchecked). Furthermore the argument will be set in bold text (like in section)
\em bibid or \em keylists| If used in a command classified as "C". See the classifier description below.
\em cmd,\em command or ends with \em \%cmd| defintion for command, e.g. \\newcommand{cmd}. This "cmd" will considered to have no arguments and convey no functionality.
\em def or \em definition| actual defintion for command, e.g. \\newcommand{cmd}{definition}. This "definition" will ignored for syntax check.
\em args| number of arguments for command, e.g. \\newcommand{cmd}[args]{definition}.
\em package|package name, e.g. \\usepackage{package}
\em citekey|definition of new citation key name, e.g. \\bibitem{citekey}
\em title or <em> short title</em>|section name, e.g. \\section{title}
\em color|color name, e.g. \\textcolor{color}
\em width,\em length,\em height or ends with \em \%l|width or length option e.g. \\abc{size\%l}
\em cols or \em preamble|columns defintion in tabular,etc. , e.g. \\begin{tabular}{cols}
\em file|file name
\em URL|URL
\em options|package options, e.g. \\usepackage[options]
\em imagefile|file name of an image
\em key|label/ref key
\em label with option #r or key ending with \em \%ref|ref key
\em label with option #l or key ending with \em \%labeldef|defines a label
\em labellist|list of labels as employed by cleveref
<em>bib file</em> or <em>bib files</em>|bibliography file
\em class|document class
\em placement or \em position|position of env
\em beamertheme|beamer theme, e.g. \\usebeamertheme{beamertheme}
\em keys,\em keyvals or \em \%<options\%>|key/value list
\em envname|environment name for \\newtheorem, e.g. \\newtheorem{envname}#N (classification N needs to be present !)
\em ends with %plain|ignore a special meaning of the key

 * \param line command definition until '#'
 * \param definition context information right of '#'
 * \return command definition
 */
CommandDescription extractCommandDef(QString line, QString definition)
{
	QRegExp rxCom("^(\\\\\\w+\\*?)");
	int i = rxCom.indexIn(line);
	QString command = rxCom.cap();
	line = line.mid(command.length());
	const QString specialChars = "{[(";
	const QString specialChars2 = "}])";
	CommandDescription cd;
	if (line.isEmpty())
		return cd;
	QChar c = line.at(0);
	int loop = 1;
	while (specialChars.contains(c)) {
		int j = specialChars.indexOf(c);
		QChar closingChar = specialChars2.at(j);
		i = line.indexOf(closingChar);
		QString arg = line.mid(1, i - 1);
		Tokens::TokenType type = Tokens::generalArg; // assume that unknown argument is not a text
		if (loop == 1 && command == "\\begin") {
			type = Tokens::beginEnv;
		} else if (loop == 1 && command == "\\end") {
			type = Tokens::env;
		} else {
			type = tokenTypeFromCwlArg(arg, definition);
		}
		if (!arg.isEmpty()) { //ignore empty arguments
			switch (j) {
			case 0:
				cd.args = cd.args + 1;
				cd.argTypes.append(type);
				break;
			case 1:
				cd.optionalArgs = cd.optionalArgs + 1;
				cd.optTypes.append(type);
				break;
			case 2:
				cd.bracketArgs = cd.bracketArgs + 1;
				cd.bracketTypes.append(type);
				break;
			default:
				break;
			}
		}
		if (i < 0)
			break;
		line = line.mid(i + 1);
		if (line.isEmpty())
			break;
		c = line.at(0);
		loop++;
	}
	return cd;
}


CommandDescription::CommandDescription(): optionalArgs(0), bracketArgs(0), args(0), level(0)
{

}

QString tokenTypesToString(const QList<Tokens::TokenType>& types)
{
	QStringList res;
	for (int i=0;i<types.length();i++) res << QString("%1").arg((int)types[i]);
	return res.join(" ");
}

QString CommandDescription::toDebugString() const
{
    return QString("%1:%2:%3").arg(tokenTypesToString(optTypes)).arg(tokenTypesToString(argTypes)).arg(tokenTypesToString(bracketTypes));
}

bool CommandDescription::operator==(const CommandDescription &v) const
{
    return (this->optionalCommandName==v.optionalCommandName && this->args==v.args && this->argTypes==v.argTypes && this->level==v.level && this->optionalArgs==v.optionalArgs && this->optTypes==v.optTypes && this->bracketArgs==v.bracketArgs && this->bracketTypes==v.bracketTypes);
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
TokenList getArgContent(Tokens &tk)
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
	Tokens tk;
	// adapt strategy after token type (word, closed , open)
	if (pos >= 0 && pos < tl.length()) {
		tk = tl.at(pos);
		if (tk.type == Tokens::word) {
			result.append(tk);
			return result;
		}
		if (Tokens::tkBraces().contains(tk.type)) {
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
		Tokens tk = tl.at(i);
		if (tk.start > pos) {
			break;
		}
		if (Tokens::tkOpen().contains(tk.type)) {
			stack.push(tk);
		}
        if (Tokens::tkClose().contains(tk.type) && !stack.isEmpty() ) {
            if (stack.top().type == Tokens::opposite(tk.type) && (tk.start<pos)) {
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
				ts.pop();
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
		if (ts.top().start + ts.top().length == pos && !Tokens::tkBraces().contains(ts.top().type)) // equal is accceptable for other than braces
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
Tokens getTokenAtCol(QDocumentLineHandle *dlh, int pos, bool first)
{
	if (!dlh) return Tokens();
	TokenList tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	Tokens tk;
	for (int i = 0; i < tl.length(); i++) {
		Tokens elem = tl.at(i);
		if (elem.start > pos)
			break;
		if (elem.start + elem.length > pos) {
			tk = elem; // get deepest element at col
			if (first)
				break;
		}
		if (!Tokens::tkBraces().contains(elem.type) && !Tokens::tkClose().contains(elem.type) && elem.start + elem.length >= pos) { // get abc|} -> abc
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
		Tokens elem = tl.at(i);
		if (elem.start > pos)
			break;
		if (elem.start + elem.length > pos) {
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
QString getCommandFromToken(Tokens tk)
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
                    Tokens tk_group=stack.top();
                    if(tk_group.dlh){
                        tl<< tk_group.dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
                    }
                }
            }
            tl<< dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();

            Tokens result = getCommandTokenFromToken(tl, tk);
            if (result.type == Tokens::command) {
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
Tokens getCommandTokenFromToken(TokenList tl, Tokens tk)
{
	Tokens result;
	int tkPos = tl.indexOf(tk);
	int level = tk.level - 1;
	if (Tokens::tkBraces().contains(tk.type) || Tokens::tkOpen().contains(tk.type) || Tokens::tkClose().contains(tk.type)) {
		level = tk.level; //command is at same level
	}
	if (tk.subtype == Tokens::keyVal_val) {
		level = tk.level - 2; // command is 2 levels up
	}
	for (int i = tkPos - 1; i >= 0; i--) {
		Tokens elem = tl.at(i);
		if (elem.level == level && (elem.type == Tokens::command || elem.type == Tokens::commandUnknown) ) {
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
	Tokens present, previous;
	present.type = Tokens::none;
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
				present.type = Tokens::none;
				verbatimSymbol = QChar();
				continue;
			}
		}
		if (present.type == Tokens::command && c == '@') {
			continue; // add @ as letter to command
		}
		if (present.type == Tokens::command && present.start == i - 1 && (c.isSymbol() || c.isPunct())) {
			// handle \$ etc
			present.length = i - present.start + 1;
			lexed.append(present);
			present.type = Tokens::none;
			continue;
		}
		if (c == '%') {
			if (present.type != Tokens::none) {
				present.length = i - present.start;
				lexed.append(present);
			}
			present.type = Tokens::comment;
			present.length = 1;
			lexed.append(present);
			present.type = Tokens::none;
			continue;
		}

		if (specialChars.contains(c) || c.isSpace() || c.isPunct() || c.isSymbol()) {
			//close token
			if (present.type != Tokens::none) {
				present.length = i - present.start;
				lexed.append(present);
				present.type = Tokens::none;
			}
		} else {
			if (present.type == Tokens::none) {
				if (c.isLetter()) {
					present.type = Tokens::word;
				} else {
					present.type = Tokens::number;
				}
				present.start = i;
			} else { // separate numbers and text (latex considers \test1 as two tokens ...)
				if (c.isDigit() && present.type != Tokens::number) {
					present.length = i - present.start;
					lexed.append(present);
					present.start = i;
					present.type = Tokens::number;
					continue;
				}
				if (c.isLetter() && present.type == Tokens::number) {
					present.length = i - present.start;
					lexed.append(present);
					present.start = i;
					present.type = Tokens::word;
					continue;
				}
			}
			continue;
		}
		//start new Token
		present.start = i;
		if (c == '\\') {
			present.type = Tokens::command;
			continue;
		}

		int l = specialChars.indexOf(c);
		if (l > -1 && l < 3) {
			present.type = Tokens::TokenType(int(Tokens::openBrace) + l);
			present.length = 1;
			lexed.append(present);
			present.type = Tokens::none;
			continue;
		}
		if (l > 2) {
			present.type = Tokens::TokenType(int(Tokens::closeBrace) + (l - 3));
			present.length = 1;
			lexed.append(present);
			present.type = Tokens::none;
			continue;
		}
		if (c.isSymbol()) {
			present.type = Tokens::symbol;
			present.length = 1;
			lexed.append(present);
			present.type = Tokens::none;
			continue;
		}
		if (c.isPunct()) {
			present.type = Tokens::punctuation;
			present.length = 1;
			lexed.append(present);
			present.type = Tokens::none;
			continue;
		}

	}
	if (present.type != Tokens::none) {
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
		if (stack.top().type == Tokens::verbatim) {
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

	for (int i = 0; i < tl.length(); i++) {
		Tokens &tk = tl[i];
		/* parse tokenlist
		 * check commands (1. syn check)
		 * tie options/arguments to commands
		 * lex otpions (key/val, comma separation,words,single arg,label etc)
		 * => reclassification of arguments
		 */
		if (!verbatimSymbol.isNull()) {
			// handle \verb+ ... +  etc.
			if (tk.type == Tokens::symbol) {
				QString smb = line.mid(tk.start, 1);
				if (smb == verbatimSymbol) {
                                    // stop verbatimSymbol mode
                                    verbatimSymbol.clear();
                                    continue;
				}
			}
			tk.type = Tokens::verbatim;
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
			if (tk.type != Tokens::command)
				continue;
			QString cmd = line.mid(tk.start, tk.length);
			if (cmd != "\\end")
				continue;
			if (i + 2 >= tl.length()) // not enough tokens to handle \end{verbatim
				continue;
			Tokens tk2 = tl.at(i + 1);
			Tokens tk3 = tl.at(i + 2);
			if (tk2.type == Tokens::openBrace && tk3.type == Tokens::word) {
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
		if (tk.type == Tokens::comment)
			break; // stop at comment start
		if (tk.type == Tokens::command) {
			QString command = line.mid(tk.start, tk.length);
			if (tl.length() > i + 1 && tl.at(i + 1).type == Tokens::punctuation && line.mid(tl.at(i + 1).start, 1) == "*") {
				// add * to command
				i++;
				command.append("*");
			}
			if (command == "\\verb" || command == "\\verb*") {
				// special treament for verb
				if (i + 1 < tl.length() && tl.at(i + 1).type == Tokens::symbol && tl.at(i + 1).start == tk.start + tk.length) {
					// well formed \verb
					verbatimSymbol = line.mid(tl.at(i + 1).start, 1);
                    i++;
				}
				// not valid \verb
				if (!stack.isEmpty()) {
					tk.subtype = stack.top().subtype;
					if (tk.subtype == Tokens::keyValArg && lastEqual > -1) {
						tk.subtype = Tokens::keyVal_val;
					}
				}
				tk.level = level;
				lexed << tk;

				continue;
			} else {
				if (!stack.isEmpty()) {
					tk.subtype = stack.top().subtype;
					if (tk.subtype == Tokens::keyValArg && lastEqual > -1) {
						tk.subtype = Tokens::keyVal_val;
						if (!commandStack.isEmpty() && lp.commandDefs.contains(commandStack.top().optionalCommandName + "/" + keyName)) {
							CommandDescription cd = lp.commandDefs.value(commandStack.top().optionalCommandName + "/" + keyName);
							tk.subtype = cd.argTypes.value(0, Tokens::keyVal_val);
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
					if ((cd.args > 0 || cd.optionalArgs > 0 || cd.bracketArgs > 0 ) && tk.subtype != Tokens::def) { // don't interpret commands in defintion (\newcommand{def})
                        cd.optionalCommandName=command;
						commandStack.push(cd);
					}
				} else {
					tk.type = Tokens::commandUnknown;
				}
				tk.level = level;
				lexed << tk;
			}
			continue;
		}
		if (Tokens::tkOpen().contains(tk.type)) {
			if (!commandStack.isEmpty() && commandStack.top().level == level) {
				CommandDescription &cd = commandStack.top();
				if (tk.type == Tokens::openBrace) {
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
				if (tk.type == Tokens::openSquare) {
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
				if (tk.type == Tokens::openBracket) {
					if (cd.bracketArgs > 0) {
						cd.bracketArgs--;
						tk.subtype = cd.bracketTypes.takeFirst();
					} else {
						lexed << tk;
						continue;
					}
				}
				tk.level = level;
				tk.argLevel = RUNAWAYLIMIT; // run-away prevention
				stack.push(tk);
				lexed << tk;
				level++;
            }else{
                if(tk.type==Tokens::openBrace){ // check braces within arguments, not brackets/squareBrackets
                    tk.level = level;
                    tk.argLevel = 0; // run-away prevention, reduced if no command is used
                    stack.push(tk);
                    lexed << tk;
                    level++;
                }
            }
			continue;
		}
		if (Tokens::tkClose().contains(tk.type)) {
			// special treament for brackets as they don't have any syntaxtical meaning except with some commands
			if (tk.type == Tokens::closeBracket ) {
				if (stack.isEmpty())
					continue;
				if (stack.top().type != Tokens::opposite(tk.type))
					continue; //closing bracket is ignored if no correct open is present
			}
			if (!stack.isEmpty() && stack.top().type == Tokens::opposite(tk.type)) {
				Tokens tk1 = stack.pop();

				if (Tokens::tkCommalist().contains(tk1.subtype)) {
					lastComma = -1;
				}
				if (tk1.subtype == Tokens::keyValArg) {
					lastComma = -1;
					if (lastEqual > -1e6) {
						if (!lexed.isEmpty() && lexed.last().type == Tokens::keyVal_key) {
							// no value added, add empty key_val
							Tokens tk0;
							tk0.start = tk.start;
							tk0.length = 0;
							tk0.dlh = dlh;
							tk0.type = Tokens::keyVal_val;
							tk0.subtype = Tokens::keyVal_val;
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
						if (Tokens::tkSingleArg().contains(tk1.subtype) || tk1.subtype >= Tokens::specialArg) { // all special args are assumed single word arguments
							// join all args for intended single word argument
							// first remove all argument tokens
							for (int k = j + 1; k < lexed.length();) {
								lexed.removeAt(k);
							}
							Tokens tk2;
							tk2.dlh = dlh;
							tk2.start = lexed[j].start + 1;
							tk2.length = tk.start - lexed[j].start - 1;
							tk2.type = tk1.subtype;
							tk2.level = level;
							lexed << tk2;
							if (tk2.type == Tokens::beginEnv) {
								// special treatment for \begin ...
								QString env = line.mid(tk2.start, tk2.length);
								// special treatment for verbatim
								if (lp.possibleCommands["%verbatimEnv"].contains(env)) {
									verbatimMode = true;
									Tokens tk3;
									tk3.dlh = dlh;
									tk3.level = level - 1;
									tk3.type = Tokens::verbatim;
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
						lexed[j].type = Tokens::closed(tk.type);
						level--;
						// remove commands from commandstack with higher level, as they can't have any valid arguments anymore
						while (!commandStack.isEmpty() && commandStack.top().level > level) {
							commandStack.pop();
						}
					} else { // opening not found, whyever (should not happen)
						level--;
						tk.level = level;
						lexed.append(tk);
					}
				} else {
					level--;
					tk.level = level;
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
		if (!stack.isEmpty() && stack.top().level == level - 1 && Tokens::tkCommalist().contains(stack.top().subtype)) {
			// handle commalist
			if (tk.type == Tokens::punctuation && line.mid(tk.start, 1) == ",") {
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
		if (!stack.isEmpty() && stack.top().level < level && stack.top().subtype == Tokens::keyValArg) {
			// handle keyval
			if (tk.type == Tokens::punctuation && line.mid(tk.start, 1) == ",") {
				lastComma = -1;
				if (lastEqual > -1e6) {
					if (!lexed.isEmpty() && lexed.last().type == Tokens::keyVal_key) {
						// no value added, add empty key_val
						Tokens tk0;
						tk0.start = tk.start;
						tk0.length = 0;
						tk0.type = Tokens::keyVal_val;
						tk0.subtype = Tokens::keyVal_val;
						tk0.level = level;
						lexed << tk0;
					}
					level = lastEqual;
				}
				lastEqual = -1e6;
				continue;
			}
			if (tk.type == Tokens::symbol && line.mid(tk.start, 1) == "=") {
				lastComma = 1;
				lastEqual = level;
				level++;
				continue;
			}
			if (lastComma < 0) {
				tk.level = level;
				tk.type = Tokens::keyVal_key;
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
					tk.subtype = Tokens::keyVal_val;
					if (!commandStack.isEmpty() && lp.commandDefs.contains(commandStack.top().optionalCommandName + "/" + keyName)) {
						CommandDescription cd = lp.commandDefs.value(commandStack.top().optionalCommandName + "/" + keyName);
						tk.subtype = cd.argTypes.value(0, Tokens::keyVal_val);
					}
					lexed << tk;
				}
			}
			continue;
		}
		if (tk.type == Tokens::symbol) {
			// special treatment for $ as mathstart
			if (line.mid(tk.start, 2) == "$$") {
			    tk.type = Tokens::command;
			    tk.level = level;
			    tk.length=2;
			    lexed << tk;
			    i++;
			    continue;
			}
			if (line.mid(tk.start, 1) == "$") {		    
			    tk.type = Tokens::command;
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
		if (tk.type == Tokens::punctuation) {
			if (line.mid(tk.start, 1) == "&") {
				// special treatment for & in tabular
				tk.type = Tokens::command;
				tk.level = level;
				lexed << tk;
				continue;
			}
			if (line.mid(tk.start, 1) == "\"") {
				// special treatment for " (used for umlauts in german)
				if (i + 1 < tl.length()) {
					Tokens tk2 = tl.at(i + 1);
					if (tk2.start == tk.start + 1 && tk2.type == Tokens::word) {
						i = i + 1;
						tk.length = tk2.length + 1;
						tk.type = Tokens::word;
					}
					if (!lexed.isEmpty() && lexed.last().type == Tokens::word) {
						if (lexed.last().start + lexed.last().length == tk.start) {
							lexed.last().length += tk.length;
							continue;
						}
					}
				}
			}
		}
		if (tk.type == Tokens::word || tk.type == Tokens::number || tk.type == Tokens::symbol || tk.type == Tokens::punctuation) {
			tk.level = level;
			if (!stack.isEmpty()) {
				tk.subtype = stack.top().subtype;
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
			}
			lexed << tk;
		}
	}
	{
		// remove tokens from stack which are not intended for mulitline: (
		QMutableVectorIterator<Tokens> i(stack);
		while (i.hasNext()) {
			Tokens &tk = i.next();
			if (tk.type == Tokens::openBracket) {
				i.remove();
			} else if ((tk.type == Tokens::openBrace || tk.type == Tokens::openSquare ) && tk.dlh == dlh) {
				// set length to whole line after brace
				tk.length = line.length() - tk.start;
			}
		}
	}
	{
		// change length of openBrace (length to end of line)
		QMutableListIterator<Tokens> i(lexed);
		while (i.hasNext()) {
			Tokens &tk = i.next();
			if (tk.type == Tokens::openBrace && tk.dlh == dlh) {
				// set length to whole line after brace
				tk.length = line.length() - tk.start;
			}
		}
	}

	dlh->setCookie(QDocumentLine::LEXER_COOKIE, QVariant::fromValue<TokenList>(lexed));
	// run-away prevention
	// reduce argLevel by 1, remove all elements with level <0
    // TODO: needs to be applied on commandStack as well !!!
	for (int i = 0; i < stack.size(); i++) {
		if (stack[i].type == Tokens::verbatim)
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
	Tokens tk;
	if (!ts.isEmpty()) {
		tk = ts.top();
		if (tk.type == Tokens::word && tk.subtype == Tokens::none && ts.size() > 1) {

			// set brace type
			ts.pop();
			tk = ts.top();
		}
	}

	Tokens::TokenType type = tk.type;
	if (tk.subtype != Tokens::none)
		type = tk.subtype;

	int result = 0;
	switch (type) {
	case Tokens::width:
		result = 512;
		break;
	default:
		;
	}
	return result;
}

CommandDescription extractCommandDefKeyVal(QString line, QString &key)
{
	CommandDescription cd;
	int i = line.indexOf("#");
	if (i < 0)
		return cd;
	key = line.left(i);
	QString vals = line.mid(i + 1);
	if (vals == "#L") {
		cd.args = 1;
		cd.argTypes << Tokens::width;
	}
	return cd;
}
