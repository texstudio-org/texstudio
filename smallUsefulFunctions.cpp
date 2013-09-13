#include "smallUsefulFunctions.h"
#include "latexcompleter_config.h"
#include "qdocumentline.h"
#include <QBuffer>

const QString CommonEOW=QString("~!#$%^&*()_+{}|:\"\\<>?,./;[]-= \t\n\r`'") + QChar(171) + QChar(187) + QChar(8223) + QChar(8222) + QChar(8221) + QChar(8220) /* <= fancy quotation marks */;
const QString Punctation="!():\"?,.;-";
const QString EscapedChars="%&_";
const QString CharacterAlteringChars="\"";

LatexParser* LatexParserInstance = 0;

LatexParser::LatexParser(){
	if (!LatexParserInstance) {
		LatexParserInstance = this;
		init();
	}
}

LatexParser& LatexParser::getInstance(){
	Q_ASSERT(LatexParserInstance);
	return *LatexParserInstance;
}

void LatexParser::init(){
    //refCommands = QSet<QString>::fromList(QStringList() << "\\ref" << "\\pageref"  << "\\cref" << "\\Cref");
    //labelCommands = QSet<QString>::fromList(QStringList() << "\\label");
    //citeCommands = QSet<QString>::fromList(QStringList() << "\\cite" << "\\citet" << "\\citetitle" << "\\citep" << "\\citeauthor" << "\\footcite" << "\\nocite"  << "\\nptextcite" << "\\parencite" << "\\textcite");
	environmentCommands = QSet<QString>::fromList(QStringList() << "\\begin" << "\\end" << "\\newenvironment" << "\\renewenvironment");
    //definitionCommands = QSet<QString>::fromList(QStringList() << "\\newcommand" << "\\renewcommand" << "\\newcommand*" << "\renewcommand*" << "\\providecommand" << "\\DeclareMathOperator" <<"\\newlength");
	mathStartCommands = QSet<QString>::fromList(QStringList() << "$" << "$$" << "\\(" << "\\[" );
	mathStopCommands = QSet<QString>::fromList(QStringList() << "$" << "$$" << "\\)" << "\\]" );
    //tabularEnvirons = QSet<QString>::fromList(QStringList() << "tabular" << "tabularx" << "longtable");
    //fileCommands = QSet<QString>::fromList(QStringList() << "\\include" << "\\input" << "\\includegraphics" <<"\\bibliographystyle" << "\\bibliography");
    //includeCommands = QSet<QString>::fromList(QStringList() << "\\include" << "\\input");
    //graphicsIncludeCommands = QSet<QString>::fromList(QStringList() << "\\includegraphics" );
    //usepackageCommands = QSet<QString>::fromList(QStringList() << "\\usepackage" << "\\documentclass");

    possibleCommands.clear();
    possibleCommands["tabular"]=QSet<QString>::fromList(QStringList() << "&" );
    possibleCommands["array"]=QSet<QString>::fromList(QStringList() << "&" );
    possibleCommands["tabbing"]=QSet<QString>::fromList(QStringList() << "\\<" << "\\>" << "\\=" << "\\+");
    possibleCommands["normal"]=QSet<QString>::fromList(QStringList() << "\\\\" << "\\-" << "$" << "$$" << "\\$" << "\\#" << "\\{" << "\\}" << "\\S" << "\\'" << "\\`" << "\\^" << "\\=" <<"\\." <<"\\u" <<"\\v" << "\\H" << "\\t" << "\\c" << "\\d" << "\\b" << "\\oe" << "\\OE" << "\\ae" << "\\AE" << "\\aa" << "\\AA" << "\\o" << "\\O" << "\\P" << "\\l" << "\\L" << "\\~" << "\\ " << "\\,");
    possibleCommands["math"]=QSet<QString>::fromList(QStringList() << "_" << "^" << "\\$" << "\\#" << "\\{" << "\\}" << "\\S" << "\\," << "\\!" << "\\;" << "\\:" << "\\\\" << "\\ " << "\\|");
    possibleCommands["%definition"] << "\\newcommand" << "\\renewcommand" << "\\newcommand*" << "\renewcommand*" << "\\providecommand" << "\\DeclareMathOperator" << "\\DeclareMathSymbol" <<"\\newlength" << "\\DeclareRobustCommand" << "\\let";
    possibleCommands["%usepackage"] << "\\usepackage" << "\\documentclass";
    possibleCommands["%graphics"] << "\\includegraphics";
    possibleCommands["%bibitem"]<< "\\bibitem";
    possibleCommands["%cite"]  << "\\cite" <<  "\\nptextcite"  ;
    possibleCommands["%label"] << "\\label";
    possibleCommands["%bibliography"] << "\\bibliography";
    possibleCommands["%file"] << "\\include" << "\\input" << "\\includeonly" << "\\includegraphics" <<"\\bibliographystyle" << "\\bibliography";
    possibleCommands["%ref"] << "\\ref" << "\\pageref";
    possibleCommands["%include"] << "\\include" << "\\input";
}

int LatexReader::nextToken(const QString &line,int &index, bool inOption,bool detectMath) {
	bool inWord=false;
	bool inCmd=false;
	//bool reparse=false;
	bool singleQuoteChar=false;
	bool doubleQuoteChar=false;
	bool ignoreBrace=false;
	bool ignoreClosingBrace=false;
	int start=-1;
	int i=index;
	for (i=(i>0?i:0); i<line.size(); i++) {
		QChar cur = line.at(i);
		if(ignoreBrace && cur=='{'){
			ignoreBrace=false;
			ignoreClosingBrace=true;
			continue;
		} else ignoreBrace=false;
		if(ignoreClosingBrace && cur=='}'){
			ignoreClosingBrace=false;
			continue;
		}
		if(doubleQuoteChar)
			//if (cur == '\'') break; // check for words starting with "' (german quotation mark)
			if (CommonEOW.contains(cur)) break; // check for all quotation marks
		doubleQuoteChar=false;
		if (inCmd) {
			if (CommonEOW.indexOf(cur)>=0 || cur.isDigit()) {
				if (i-start==1) i++;
				break;
			}
		} else if (inWord) {
			if (cur=='\\') {
				if (i+1>=line.size()) break;
				const QChar& c = line.at(i+1);
				if (c=='-' || c == '&') i++; //allow \& in the middle/end of words, e.g. C&A
				else if (CharacterAlteringChars.contains(c)) {
					ignoreBrace=true;
					i++;//ignore word separation marker
				} else break;
			} else if (cur=='"') {  //ignore " like in "-, "", "| "a
				if (i+1<line.size()){
					QChar nextChar=line.at(i+1);
					if(nextChar=='-' || nextChar=='"' || nextChar=='|')  i++; 
					else if(!nextChar.isLetterOrNumber()) break;
				}
				else break;
			} else if (cur=='\'') {
				if (singleQuoteChar) break;	 //no word's with two '' => output
				else singleQuoteChar=true;   //but accept one
			} else if (cur=='.') {
				if (i>0 && line.at(i-1).isLetter())
					i++; //take '.' into word, so that abbreviations, at least German ones, are checked correctly
				break;
			} else if (CommonEOW.indexOf(cur)>=0 && !inOption) {
				break;
			} else if(cur=='}' || cur==']') break;
			
		} else if (cur=='\\') {
			if (i+1>=line.size()) break;
			const QChar& nextc = line.at(i+1);
			if (CharacterAlteringChars.contains(nextc))  {
				inWord=true;
				start=i;
				ignoreBrace=true;
				i++;
			} else if (EscapedChars.contains(nextc)) {
				i++;
				Q_ASSERT(start==-1);
			} else {
				start=i;
				inCmd=true;
			}
		} else if (cur=='{' || cur=='}' || cur=='%' || cur=='[' || cur==']') {
			index=i+1;
			return i;
		} else if (detectMath && cur=='$'){
			start=i;
			i++;
			if (i < line.size() && line[i] == '$') 
				i++; //detect $$
			break;
		} else if (detectMath && (cur=='_' || cur=='^' || cur=='&')){
			start=i;
			i++;
			break;
		} else if ((CommonEOW.indexOf(cur)<0 && cur!='\'' )|| cur=='"') {
			start=i;
			inWord=true;
			doubleQuoteChar= ( cur == '"');
		} else if (Punctation.contains(cur)){
			start=i;
			i++;
			while (i < line.length() && line.at(i) == '-') i++; //convert LaTeX --- to a single -
			break;
		}
	}
	if (singleQuoteChar && i-1<line.size() && i > 0 && line.at(i-1)=='\'')
		i--; //remove ' when a word ends with it  (starting is handled because ' does not start a word)
	index=i;
	return start;
}

QString getCommonEOW() {
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
QChar transformCharacter(const QChar& c){
    switch (c.toLatin1()){
	case 'a': return QChar(0xE4);
	case 'o': return QChar(0xF6);
	case 'u': return QChar(0xFC);
	case 'A': return QChar(0xC4);
	case 'O': return QChar(0xD6);
	case 'U': return QChar(0xDC);
	case 's': return QChar(0xDF);
	default: return c;
	}
}

QString latexToPlainWord(const QString& word) {
	/*	QString result=word;
 for (QList<QPair<QString,QString> >::const_iterator it=latexToPlainWordReplaceList.begin(); it!=latexToPlainWordReplaceList.end(); ++it)
  result.replace(it->first,it->second);*/
	QString result;
	result.reserve(word.length());
	for (int i=0;i<word.length();i++){
		if (word[i] == '\\') {
			//decode all meta characters starting with a backslash (c++ syntax: don't use an actual backslash there or it creates a multi line comment)
			i++;
			if (i>=word.length()) break;
            switch (word[i].toLatin1()) {
			case '-': //Trennung [separation] (german-babel-package also: \")
			case '/': //ligatur preventing (german-package also: "|)
				break;
				
			case '"':
				if (i+3 < word.length()) {
					if (word[i+1] == '{' && word[i+3] == '}') {
						result.append(transformCharacter(word[i+2]));
						i+=3;
					} else if (word[i+1] == '\\' || word[i+1] == '"');  //ignore "
					else i--; //repeat with "
				} else if (i +1 < word.length() && (word[i+1] == '\\' || word[i+1] == '"'));  //ignore "
				else i--; //repeat with "
				break;
			default:
				i--; //repeat with current char
			}
		} else if (word[i] == '"') {
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
				result.append(transformCharacter(word[i]));
				
			}
		} else result.append(word[i]);
	}
	
	return result;
}

QString extractSectionName(const QString& word, bool precut) {
	int i=0;
	int start=-1;
	if(!precut) start=word.indexOf("{",i);
	i=start>-1 ? start : 0;
	int stop=word.indexOf("}",i);
	i=word.indexOf("{",i+1);
	while (i>0 && stop>0 && i<stop) {
		stop=word.indexOf("}",stop+1);
		i=word.indexOf("{",i+1);
	}
	if (stop<0) stop=word.length();
	return word.mid(start+1,stop-start-1);
}

int findClosingBracket(const QString& word,int &start,QChar oc,QChar cc) {
	int i=0;
	if(start<0) start=word.indexOf(oc,i);
	i=start>-1 ? start : 0;
	int stop=word.indexOf(cc,i);
	i=word.indexOf(oc,i+1);
	while (i>0 && stop>0 && i<stop) {
		stop=word.indexOf(cc,stop+1);
		i=word.indexOf(oc,i+1);
	}
	return stop;
}

int findOpeningBracket(const QString& word,int start,QChar oc,QChar cc) {
	int i=start;
	int n=0;
	while (i>-1) {
		QChar ch=word.at(i);
		if(ch==oc){
			n--;
			if(n<0)
				break;
		}
		if(ch==cc){
			n++;
		}
		i--;
	}
	return i;
}

QString textToLatex(const QString& text) {
	QList<QPair<QString,QString> > replaceList;
	replaceList.append(QPair<QString, QString> ("\\","\\verb+\\+"));
	replaceList.append(QPair<QString, QString> ("{","\\{"));
	replaceList.append(QPair<QString, QString> ("}","\\}"));
	replaceList.append(QPair<QString, QString> ("#","\\#"));
	replaceList.append(QPair<QString, QString> ("$","\\$"));
	replaceList.append(QPair<QString, QString> ("%","\\%"));
	replaceList.append(QPair<QString, QString> ("&","\\&"));
	replaceList.append(QPair<QString, QString> ("~","\\~{}"));
	replaceList.append(QPair<QString, QString> ("_","\\_"));
	replaceList.append(QPair<QString, QString> ("^","\\^"));
	
	QString result=text;
	for (QList<QPair<QString,QString> >::const_iterator it=replaceList.begin(); it!=replaceList.end(); ++it)
		result.replace(it->first,it->second);
	
	return result;
}

QString& parseTexOrPDFString(QString& s) {
	int start, stop;
	start = s.indexOf("\\texorpdfstring");
	while (start >= 0) {
		stop = start+15;
		stop = findClosingBracket(s, stop);
		if (stop < 0) return s;
		s.remove(start, stop-start+1);
		if (s[start] == '{') {
			s.remove(start, 1); // 2nd opening bracket
			stop = findClosingBracket(s, start);
			s.remove(stop, 1);  // 2nd closing bracket
		}
		start = s.indexOf("\\texorpdfstring");
	}
	return s;
}

// joins all the input lines trimming whitespace. A new line is started on comments and empty lines
QStringList joinLinesExceptCommentsAndEmptyLines(const QStringList& lines) {
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
QStringList splitLines(const QStringList& lines, int maxCharPerLine, const QRegExp& breakChars) {
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
				line.remove(0, breakAt+1);
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


bool localeAwareLessThan(const QString &s1, const QString &s2) {
	return QString::localeAwareCompare(s1,s2)<0;
}

// removes whitespace from the beginning of the string
QString trimLeft(const QString &s) {
	int j;
	for (j=0; j<s.length(); j++)
		if (s[j]!=' ' && s[j]!='\t' && s[j]!='\r' && s[j]!='\n') break;
	return s.mid(j);
}

// removes whitespace from the end of the string
QString trimRight(const QString &s) {
	if (s.isEmpty()) return QString();
	int j;
	for (j=s.length()-1; j>=0; j--)
		if (s[j]!=' ' && s[j]!='\t' && s[j]!='\r' && s[j]!='\n') break;
	return s.left(j+1);
}


QString findToken(const QString &line,const QString &token){
	int tagStart=line.indexOf(token);
	int commentStart=line.indexOf(QRegExp("(^|[^\\\\])%")); // find start of comment (if any)
	if (tagStart!=-1 && (commentStart>tagStart || commentStart==-1)) {
		tagStart+=token.length();
		int tagEnd=line.indexOf("}",tagStart);
		if (tagEnd!=-1) return line.mid(tagStart,tagEnd-tagStart);
		else return line.mid(tagStart); //return everything after line if there is no }
	}
	return "";
}

QString findToken(const QString &line,const QString &token,int &start){
	int tagStart=line.indexOf(token,start);
	int commentStart=line.indexOf(QRegExp("(^|[^\\\\])%")); // find start of comment (if any)
	if (tagStart!=-1 && (commentStart>tagStart || commentStart==-1)) {
		tagStart+=token.length();
		int tagEnd=line.indexOf("}",tagStart);
		start=tagStart;
		if (tagEnd!=-1) return line.mid(tagStart,tagEnd-tagStart);
		else return line.mid(tagStart); //return everything after line if there is no }
	}
	start=-2;
	return "";
}

QString findToken(const QString &line,QRegExp &token){
	//ATTENTION: token is not const because, you can't call cap on const qregexp in qt < 4.5
	int tagStart=0;
	QString s=line;
	tagStart=token.indexIn(line);
	int commentStart=line.indexOf(QRegExp("(^|[^\\\\])%")); // find start of comment (if any)
	if (tagStart!=-1 && (commentStart>tagStart || commentStart==-1)) {
		s=s.mid(tagStart+token.cap(0).length(),s.length());
		return s;
	}
	return "";
}
bool findTokenWithArg(const QString &line,const QString &token, QString &outName, QString &outArg){
	outName="";
	outArg="";
	int tagStart=line.indexOf(token);
	int commentStart=line.indexOf(QRegExp("(^|[^\\\\])%")); // find start of comment (if any)
	if (tagStart!=-1 && (commentStart>tagStart || commentStart==-1)) {
		tagStart+=token.length();
		int tagEnd=line.indexOf("}",tagStart);
		if (tagEnd!=-1) {
			outName=line.mid(tagStart,tagEnd-tagStart);
			int curlyOpen=line.indexOf("{",tagEnd);
			int optionStart=line.indexOf("[",tagEnd);
			if (optionStart<curlyOpen || (curlyOpen==-1 && optionStart!=-1)) {
				int optionEnd=line.indexOf("]",optionStart);
				if (optionEnd!=-1) outArg=line.mid(optionStart+1,optionEnd-optionStart-1);
				else outArg=line.mid(optionStart+1);
			}
		} else outName=line.mid(tagStart); //return everything after line if there is no }
		return true;
	}
	return false;
}

bool findCommandWithArg(const QString &line,QString &cmd, QString &outName, QString &outArg, QString &remainder,int &optionStart){
    // true means that a command is found, with or without arguments ...
    // otherwise a command before the interesting command leads to quiting the loop
	outName="";
	outArg="";
	remainder="";
	optionStart=-1;
	QRegExp token("\\\\\\w+\\*?");
	int tagStart=token.indexIn(line);
	int commentStart=line.indexOf(QRegExp("(^|[^\\\\])%")); // find start of comment (if any)
	if (tagStart!=-1 && (commentStart>tagStart || commentStart==-1)) {
		cmd=token.cap(0);
        QStringList values;
        QList<int> starts;
        LatexParser::resolveCommandOptions(line,tagStart,values,&starts);
        if(values.size()>0){
            QString first=values.takeFirst();
            int start=starts.takeFirst();
            if(first.startsWith('[')){
                if(values.size()>0){
                    first=values.takeFirst();
                    start=starts.takeFirst();
                    if(first.startsWith('[')){
                        remainder=line.mid(start+first.length()); //two options [..][...]
                        return true;
                    }
                }else{
                    remainder=line.mid(start+first.length()); //no argument after option
                    return true;
                }
            }
            optionStart=start+1;
            remainder=line.mid(start+first.length());
            outName=LatexParser::removeOptionBrackets(first);
            return true;
        }
        remainder=line.mid(tagStart+cmd.length());
        return true;
    }
    return false; // no command found
}

// returns the command at pos (including \) in outCmd. pos may be anywhere in the command name (including \) but
// not in command options. Return value is the index of the first char after the command (or pos if there was no command
// TODO: currently does not work for command '\\'
int getCommand(const QString &line, QString &outCmd, int pos) {
	int start=pos;

	while(line.at(start) != '\\') { // find beginning
		if (!isCommandChar(line.at(start)) || start==0) return pos; // no command
		start--;
	}

	int i=pos+1;
	for (; i<line.length(); i++)
		if (!isCommandChar(line.at(i))) break;
	outCmd = line.mid(start, i-start);
	return i;
}

// returns command option list. pos has to be at the beginning of the first bracket
// posBehind returns the position after the last bracket, you may pass the same variable as in pos
QList<CommandArgument> getCommandOptions(const QString &line, int pos, int *posBehind) {
	static QMap<QChar, QChar> cbs;
	if (cbs.isEmpty()) {
		cbs[QChar('{')] = QChar('}');
		cbs[QChar('[')] = QChar(']');
	}

	QList<CommandArgument> options;

	int start = pos;
	if (posBehind) *posBehind=start;
	if (pos >= line.length()) return options;
	QChar oc = line[start];
	if (!cbs.contains(oc)) return options;

	for (int num=1;;num++) {
		int end = findClosingBracket(line, start, oc, cbs[oc]);
		if (end<0) break; // open without close
		CommandArgument arg;
		arg.isOptional = (oc=='[');
		arg.number = num;
		arg.value = line.mid(start+1, end-start-1);
		options.append(arg);
		start=end+1;
		if (posBehind) *posBehind=start;
		if (start >= line.length() || !cbs.contains(line[start])) break; // close on last char or last option reached
	}
	return options;
}

// returns the item at pos in a colon separated list of options (empty on colon
// e.g. getParamItem("{one, two, three}", 7) returns "two"
QString getParamItem(const QString &line, int pos, bool stopAtWhiteSpace) {
	REQUIRE_RET(pos <= line.length(), QString());
	int start;
	int curlCount = 0;
	int squareCount = 0;
	QString openDelim(",{[");
	if (stopAtWhiteSpace) openDelim += " \t\n\r";
	for (start = pos; start > 0; start--) {
		QChar c = line.at(start-1);
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
	return line.mid(start, end-start);
}

QRegExp generateRegExp(const QString &text,const bool isCase,const bool isWord, const bool isRegExp){
	Qt::CaseSensitivity cs= isCase ? Qt::CaseSensitive : Qt::CaseInsensitive;
	QRegExp m_regexp;
	if ( isRegExp )
	{
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

QStringList regExpFindAllMatches(const QString& searchIn, const QRegExp& regexp, int cap){
	int offset = regexp.indexIn(searchIn);
	QStringList res;
	while (offset > -1){
		res << regexp.cap(cap);
		offset = regexp.indexIn(searchIn, offset + regexp.matchedLength());
	}
	return res;
}

void addEnvironmentToDom(QDomDocument& doc,const QString& EnvironName,const QString& EnvironMode){
	QDomElement root= doc.documentElement();
	QDomElement tag = doc.createElement("context");
	tag.setAttribute("id",EnvironMode=="numbers"?"mathMyEnv":"myVerb");
	tag.setAttribute("format",EnvironMode);
	if (EnvironMode != "comment") tag.setAttribute("transparency","true");
	QDomElement child1 = doc.createElement("start");
	child1.setAttribute("parenthesis",QString("my%1:open").arg(EnvironName));
	child1.setAttribute("fold","true");
	child1.setAttribute("format","extra-keyword");
	child1.setAttribute("parenthesisWeight", "30");
	QDomText dtxt=doc.createTextNode(QString("\\\\begin{%1}").arg(EnvironName));
	child1.appendChild(dtxt);
	QDomElement child2 = doc.createElement("stop");
	child2.setAttribute("parenthesis",QString("my%1:close").arg(EnvironName));
	child2.setAttribute("fold","true");
	child2.setAttribute("format","extra-keyword");
	child2.setAttribute("parenthesisWeight", "30");
	QDomText dtxt2=doc.createTextNode(QString("\\\\end{%1}").arg(EnvironName));
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
	for (int i=0;i<root.childNodes().size();i++)
		if (root.childNodes().item(i).attributes().namedItem("format").nodeValue() == EnvironMode){
			insertAt = root.childNodes().item(i);
			break;
		}
	root.insertBefore(tag,insertAt);
}

void LatexParser::resolveCommandOptions(const QString &line, int column, QStringList &values, QList<int> *starts){
	const QString BracketsOpen("[{");
	const QString BracketsClose("]}");
	int start=column;
    int stop=-1;
	int type;
    // check if between command and options is located text or other command
    int abort=line.indexOf(QRegExp("(\\s|\\\\)"),start+1);
    //qDebug()<<abort;
	while(start<line.length()){
		// find first available bracket after position start
		int found=-1;
		type=-1;
		for(int i=0;i<BracketsOpen.size();i++){
			int zw=line.indexOf(BracketsOpen[i],start);
			if(zw>-1 && (zw<found||found==-1)){
				found=zw;
				type=i;
			}
		}
		if(type<0) break;
        // check if only space between cmd and opening bracket
        if(abort>0){
            if((found-abort)>0){
                QString test=line.mid(abort,found-abort);
                test=test.simplified();
                test.remove(' ');
                if(!test.isEmpty())
                    break;
            }
            abort=-1;
        }
		// check wether a word letter appears before (next command text ...)
		if(stop>-1){
			stop=line.indexOf(QRegExp("\\S+"),start);
		}
		if(stop<found && stop>-1) break;
		// find apropriate closing bracket.
		int lvl=0;
		stop=-1;
		for(int i=found+1;i<line.length();i++){
			QChar c=line[i];
			if(lvl==0 && c==BracketsClose[type]){
				stop=i;
				break;
			}
			if(BracketsOpen.contains(c)){
				lvl++;
			}
			if(lvl>0 && BracketsClose.contains(c)){
				lvl--;
			}
		}
		if(found>-1 && stop>-1){
			values << line.mid(found,stop-found+1);
			if(starts)
				starts->append(found);
			start=stop+1;
		} else break;
	}
}

QString LatexParser::removeOptionBrackets(const QString &option) {
	if (option.isNull() || option.length()<2) return option;
	if ((option.at(0) == '{' && option.at(option.length()-1) == '}') ||
	              (option.at(0) == '[' && option.at(option.length()-1) == ']'))
		return option.mid(1, option.length()-2);
	return option;
}

int LatexParser::findContext(QString &line,int &column) const{
	if(line.isEmpty())
		return 0;
    QString eow="\\[]{} $";
	int i=column;
	if(i>=line.length())
		i=line.length()-1;
	if(i>0)
		i--; // character left of pos is to be checked
	else
		return 0; // no context can be detected at line start (old behavior)
	while (i>=0 && !eow.contains(line.at(i)))
		i--;
	if(i<0)
		return 0; // no eow found
	QChar ch=line.at(i);
	if(ch=='\\'){
		// command found
		int start=i;
		i++;
		while (i<line.length() && !eow.contains(line.at(i)))
			i++;
		line=line.mid(start,i-start);
		column=start;
		return 1;
	}
	int start_ref=findOpeningBracket(line,i);
	int start_opt=findOpeningBracket(line,i,'[',']');
	int ret=0;
	if(start_ref>start_opt){
		// assuming we are in command argument
		ret=2;
		i=start_ref-1;
	}else{
		if(start_opt>-1){
			//assuming we are in command option
			ret=3;
			i=start_opt-1;
		}
	}
	if(ret==0)
		return 0;
	
	int n=0;
	QString openBrackets="[{";
	QString closeBrackets="]}";
	eow=getCommonEOW();
	int stop=i;
	while (i>-1) {
		ch=line.at(i);
		if(openBrackets.contains(ch)){
			//TODO check if correct bracket was opened ...
			n--;
			if(n<0)
				break;
			i--;
			stop=i;
			continue;
		}
		if(closeBrackets.contains(ch)){
			n++;
			i--;
			continue;
		}
		if(n==0 && eow.contains(ch)){
			if(ch=='\\'){
				//TODO: check if not \\ (newline) was found
				line=line.mid(i,stop-i+1);
				column=i;
				return ret;
			}else{ // this is a overly strict interpretation of command syntax
				return 0;
			}
		}
		i--;
	}
	
	return 0;
}

LatexParser::ContextType LatexParser::findContext(const QString &line, int column, QString &command, QString& value) const{
	command=line;
	int temp=findContext(command,column);
	QStringList vals;
	resolveCommandOptions(line,column,vals);
	value="";
	if(!vals.isEmpty()){
		value=vals.takeFirst();
		if(value.startsWith('[')){
			if(!vals.isEmpty()){
				value=vals.takeFirst();
			}
		}
		if(value.startsWith('{'))
			value.remove(0,1);
		if(value.endsWith('}'))
			value.chop(1);
	}
	switch (temp) {
	case 0: return Unknown;
	case 1: return Command;
	case 2:
		if (environmentCommands.contains(command))
			return Environment;
        else if (possibleCommands["%label"].contains(command))
			return Label;
        else if (possibleCommands["%ref"].contains(command))
			return Reference;
        else if (possibleCommands["%cite"].contains(command))
			return Citation;
        else if (possibleCommands["%graphics"].contains(command))
            return Graphics;
		else return Option;
	default: return Unknown;
	}
}

int LatexParser::commentStart(const QString& text){
	if(text.startsWith("%")) return 0;
	QString test=text;
	test.replace("\\\\","  ");
	int cs=test.indexOf(QRegExp("[^\\\\]%")); // find start of comment (if any)
	if(cs>-1) return cs+1;
	else return -1;
}

QString LatexParser::cutComment(const QString& text){
	return text.left(LatexParser::commentStart(text)); // remove comments
}

QString intListToStr(const QList<int> &ints) {
	QString s = "";
	foreach (int i, ints) {
		s.append(QString::number(i)+',');
	}
	if (s.length()>0)
		s.remove(s.length()-1, 1); // remove last ','
	return s;
}

QList<int> strToIntList(const QString &s) {
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
bool minimalJsonParse(const QString &text, QHash<QString, QString> &map) {
	int len = text.length();
	int col = text.indexOf('{');
	while (true) {
		QString key;
		QString val;
		int startStr, endStr;
		startStr = text.indexOf('"', col+1);
		if (startStr < 0) return true;
		endStr = startStr;
		while (endStr >= 0) {
			endStr = text.indexOf('"',endStr+1);
			if (text.at(endStr-1) != '\\') break;
		}
		if (endStr < 0) return false;
		key = text.mid(startStr+1, endStr-startStr-1); // +1 / -1 outer removes qoutes
		key.replace("\\\"", "\"");

		col = endStr +1;
		while (col < len && text.at(col).isSpace()) col++;
		if (col >= len || (text.at(col)) != ':') return false;
		col++;
		while (col < len && text.at(col).isSpace()) col++;

		if (col >= len || (text.at(col)) != '"') return false;
		startStr = col;
		endStr = startStr;
		while (endStr >= 0) {
			endStr = text.indexOf('"',endStr+1);
			if (text.at(endStr-1) != '\\') break;
		}
		if (endStr < 0) return false;
		val = text.mid(startStr+1, endStr-startStr-1); // +1 / -1 outer removes qoutes
		val.replace("\\\"", "\"");
		map[key] = val;

		col = endStr +1;
		while (col < len && text.at(col).isSpace()) col++;
		if (col >= len) return false;
		if (text.at(col) == '}') return true;
		if (text.at(col) != ',') return false;
	}
	return true;
}


QString formatJsonStringParam(const QString &id, const QString &val, int minIdWidth) {
	QString s = enquoteStr(id);
	while (s.length() < minIdWidth) s += ' ';
	s += " : " + enquoteStr(val);
	return s;
}

QString enquoteStr(const QString &s) {
	QString res = s;
	res.replace('"', "\\\"");
	res.prepend('"');
	res.append('"');
	return res;
}

QString dequoteStr(const QString &s) {
	QString res = s;
	if (res.endsWith('"') && !res.endsWith("\\\""))
		res.remove(res.length()-1, 1);
	if (res.startsWith('"'))
		res.remove(0, 1);
	res.replace("\\\"", "\"");
	return res;
}



QTextCodec* QTextCodecForTeXShopName(const QByteArray& enc){
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

QTextCodec* LatexParser::QTextCodecForLatexName(QString str){
	if (str.contains(',')) { //multiple options are allowed
		foreach (const QString& splitter, str.split(',')){
			QTextCodec* codec = QTextCodecForLatexName(splitter);
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
	if (str.startsWith("cp") && (str.length()==5 || str.length()==6)
	              && (str[2] >= '0') && (str[2] <= '9')
	              && (str[3] >= '0') && (str[3] <= '9')
	              && (str[4] >= '0') && (str[4] <= '9') &&
	              (str.length()==5 || ((str[5] >= '0') && (str[5] <= '9')))) return QTextCodec::codecForName(qPrintable(str));
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
	if (str == "mac-ce" || str=="mac-centeuro") return QTextCodec::codecForName("macintosh"); //wrong, should be Macintosh Central European code page.
	if (str == "mac-cyrillic" || str=="maccyr" || str=="mac-ukrainian" || str=="macukr") return QTextCodec::codecForName("macintosh"); //wrong, should be Macintosh Cyrillic
	//if (str == "nextstep, next?
	
	//return QTextCodec::codecForName(str); //try it anyways
	return 0;
}

QStringList LatexParser::latexNamesForTextCodec(const QTextCodec *codec) {
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
		//case 2086 : return QStringList(); // "IBM866"
		//case 2088 : return QStringList(); // "KOI8-U"
		//case 2101 : return QStringList(); // "Big5-HKSCS"
		//case 2107 : return QStringList(); // "TSCII"
		case 2250 : return QStringList() << "cp1250"; // "windows-1250"
		//case 2251 : return QStringList(); // "windows-1251"
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
	return QStringList();
}

int lineEnd(const QByteArray& data, int index){
	int r = data.indexOf('\n',index);
	if (r != -1) return r;
	r = data.indexOf('\r',index);
	if (r != -1) return r;
	r = data.indexOf("\x20\x29",index);
	if (r != -1) return r;
	return data.size();
}

QTextCodec * guessEncodingBasic(const QByteArray& data, int * outSure){
	const char* str = data.data();
	int size = data.size();
	QTextCodec* guess = 0;
	int sure = 1;
	if (size>0) {
		unsigned char prev=str[0];
		int goodUtf8=0;int badUtf8=0;
		int badIso1 = 0;
		int utf16le=0, utf16be = 0;
		if (prev >= 0x80 && prev <= 0x9F) badIso1++;
		for (int i=1;i<size;i++) {
			unsigned char cur = str[i];
			if (cur >= 0x80 && cur <= 0x9F) badIso1++;
			if ((cur & 0xC0) == 0x80) {
				if ((prev & 0xC0) == 0xC0) goodUtf8++;
				else if ((prev & 0x80) == 0x00) badUtf8++;
			} else {
				if ((prev & 0xC0) == 0xC0) badUtf8++;
				//if (cur==0) { if (i & 1 == 0) utf16be++; else utf16le++;}
				if (prev==0) {
					if ((i & 1) == 1) utf16be++;
					else utf16le++;
				}
			}
			prev=cur;
		}
		// less than 0.1% of the characters can be wrong for utf-16 if at least 1% are valid (for English text)
		if (utf16le > utf16be) {
			if (utf16be <= size / 1000 && utf16le >= size / 100 && utf16le >= 2) guess = QTextCodec::codecForMib(MIB_UTF16LE);
		} else {
			if (utf16le <= size / 1000 && utf16be >= size / 100 && utf16be >= 2) guess = QTextCodec::codecForMib(MIB_UTF16BE);
		}
		if (!guess){
			if (goodUtf8 > 10*badUtf8) guess = QTextCodec::codecForMib(MIB_UTF8);
			else {
				if (badIso1 > 0) guess = QTextCodec::codecForMib(MIB_WINDOWS1252);
				else guess = QTextCodec::codecForMib(MIB_LATIN1);
				if (badUtf8 == 0) sure = 0;
			}
		}
	}
	if (outSure) *outSure = sure;
	return guess;
}


void LatexParser::guessEncoding(const QByteArray& data, QTextCodec *&guess, int &sure){
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
	static const char * searchedLC = "%!tex encoding";
	static const char * searchedUC = "%!TEX ENCODING";
	static const int searchedLast = 13; Q_ASSERT(searchedLC[searchedLast] == 'g');
	while (index >= 0 && index < headerSize) {
		int temp = index-1;
		int sp = searchedLast;
		const char * d = data.constData();
		for (;temp >= 0 && sp >= 0; temp--)
			if (searchedLC[sp] == d[temp]) sp--;
			else if (searchedUC[sp] == d[temp]) sp--;
			else if (d[temp] == ' ') ;
			else break;
		if (sp == -1) {
			int end = lineEnd(data, index);
			QByteArray encName = data.mid(index+1, end-index-1).trimmed();
			QTextCodec* codec = QTextCodec::codecForName(encName);
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
	
	//search for \usepackage[.*]{inputenc} outside of a comment
	index = data.indexOf("]{inputenc}");
	while (index >= 0 && index < headerSize) {
		int previous = data.lastIndexOf("\\usepackage[",index);
		if (previous >= 0){
			int commentStart = data.lastIndexOf('%',index);
			int commentEnd = lineEnd(data, index);
			if (commentStart <= commentEnd) {
				QString encoding = QString(data.mid(previous+12, index - (previous + 12)));
				QTextCodec* codec = QTextCodecForLatexName(encoding);
				if (codec) {
					sure = 100;
					guess = codec;
					return;
				}
			}
		}
		index = data.indexOf("]{inputenc}", index + 1);
	}
	
	//search for \usepackage[.*]{inputenx} outside of a comment
	index = data.indexOf("]{inputenx}");
	while (index >= 0 && index < headerSize) {
		int previous = data.lastIndexOf("\\usepackage[",index);
		if (previous >= 0){
			int commentStart = data.lastIndexOf('%',index);
			int commentEnd = lineEnd(data,index);
			if (commentStart <= commentEnd) {
				QString encoding = QString(data.mid(previous+12, index - (previous + 12)));
				QTextCodec* codec = QTextCodecForLatexName(encoding);
				if (codec) {
					sure = 100;
					guess = codec;
					return;
				}
			}
		}
		index = data.indexOf("]{inputenx}", index + 1);
	}
	return;
}

void LatexParser::append(const LatexParser& elem){
	QHash<QString, QSet<QString> >::const_iterator i = elem.possibleCommands.constBegin();
	while (i != elem.possibleCommands.constEnd()) {
		QString key=i.key();
		QSet<QString> set=i.value();
		possibleCommands[key].unite(set);
		++i;
	}
	foreach(const QString key,elem.environmentAliases.keys()){
	    QStringList values=elem.environmentAliases.values(key);
	    foreach(const QString value,values){
		if(!environmentAliases.contains(key,value))
		    environmentAliases.insert(key,value);
	    }
	}
}

void LatexParser::clear(){
	init();
}

void LatexParser::substract(const LatexParser& elem){
	QHash<QString, QSet<QString> >::const_iterator i = elem.possibleCommands.constBegin();
	while (i != elem.possibleCommands.constEnd()) {
		QString key=i.key();
		QSet<QString> set=i.value();
		possibleCommands[key].subtract(set);
		++i;
	}
}

void LatexParser::importCwlAliases(){
	QString fn=findResourceFile("completion/cwlAliases.dat");
	QFile tagsfile(fn);
	if (tagsfile.open(QFile::ReadOnly)) {
		QString line;
		QString alias;
		while (!tagsfile.atEnd()) {
			line = tagsfile.readLine().trimmed();
			if(line.startsWith("#"))
				continue;
			if(line.endsWith(":")){
				alias=line.left(line.length()-1);
				continue;
			}
			if(!alias.isEmpty())
				packageAliases.insertMulti(alias,line);
		}
	}
}

LatexReader::LatexReader():lp(&LatexParser::getInstance()){Q_ASSERT(this->lp);}
LatexReader::LatexReader(const QString& line): lp(&LatexParser::getInstance()){Q_ASSERT(this->lp);setLine(line);}
LatexReader::LatexReader(const LatexParser& lp, const QString& line):lp(&lp){Q_ASSERT(this->lp);setLine(line);}


LatexReader::NextWordFlag LatexReader::nextWord(bool returnCommands){
	int reference=-1;
	bool inOption=false;
	bool inEnv=false;
	bool inReferenz=false;
	while ((wordStartIndex = nextToken(line, index,inEnv,!inReferenz))!=-1) {
		word=line.mid(wordStartIndex,index-wordStartIndex);
		if (word.length()==0) return NW_NOTHING; //should never happen
        switch (word.at(0).toLatin1()) {
		case '%':
			return NW_COMMENT; //return comment start
		case '[':
			if(!lastCommand.isEmpty()) inOption=true;
			break;
		case ']':
			inOption=false;
			break;
		case '{':
			if (reference!=-1)
				reference=wordStartIndex+1;
			if(!lastCommand.isEmpty()) inOption=true;
			if(lp->environmentCommands.contains(lastCommand)) inEnv=true;
			break; //ignore
		case '}':
			if (reference!=-1) {
				NextWordFlag result = NW_NOTHING;
                if (lp->possibleCommands["%ref"].contains(lastCommand)) result = NW_REFERENCE;
                else if (lp->possibleCommands["%label"].contains(lastCommand)) result = NW_LABEL;
                else if (lp->possibleCommands["%cite"].contains(lastCommand)) result = NW_CITATION;
				if (result != NW_NOTHING) {
					wordStartIndex=reference;
					--index;
					word=line.mid(reference,index-reference);
					return result;
				}
			}
			lastCommand="";
			inOption=false;
			inEnv=false;
			break;//command doesn't matter anymore
		case '$': case '^': case '&':
			return NW_COMMAND;
		case '_':
			if(!inOption){
				return NW_COMMAND;
			}
			break;
		case '\\':
			if (word.length()==1 || !(EscapedChars.contains(word.at(1)) || CharacterAlteringChars.contains(word.at(1)))) {
				if (returnCommands) return NW_COMMAND;
                if (lp->possibleCommands["%ref"].contains(word)||lp->possibleCommands["%label"].contains(word)||lp->possibleCommands["%cite"].contains(word)){
					reference=index; //todo: support for nested brackets like \cite[\xy{\ab{s}}]{miau}
					lastCommand=word;
					inReferenz=true;
				}
				if (lp->optionCommands.contains(lastCommand)||lastCommand.isEmpty()||word=="\\begin"||word=="\\end") {
					lastCommand=word;
				}
				break;
			} else {;} //first character is escaped, fall through to default case
		default:
			//if (reference==-1) {
			if(!inOption && !lastCommand.isEmpty()){
				inOption=false;
				lastCommand="";
			}
			//if (word.length() == 2 && word[0] == '"' && CommonEOW.contains(word[1]))
			//	return NW_PUNCTATION; //some quotation mark
			if (word.length() > 1 && (word.contains('\\')||word.contains('"'))){
				word=latexToPlainWord(word); //remove special chars			
				if (word.isEmpty()) continue;
			}
			if (lp->environmentCommands.contains(lastCommand))
				return NW_ENVIRONMENT;
			if (lastCommand.isEmpty() || lp->optionCommands.contains(lastCommand)){
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

bool LatexReader::nextTextWord(){
	NextWordFlag flag = NW_PUNCTATION;
	//flag can be nothing, text, comment, environment/punctation
	//text/comment returns false, text returns true, environment/punctation is ignored
	while (flag == NW_ENVIRONMENT || flag == NW_PUNCTATION) 
		flag = nextWord(false);
	return flag==NW_TEXT;
}

const QString& LatexReader::getLine() const{
	return line;
}
void LatexReader::setLine(const QString& line){
	this->line = line;
	this->index = 0;
	this->wordStartIndex = 0;
}

LatexPackage loadCwlFile(const QString fileName,LatexCompleterConfig *config) {
	QStringList words;
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	LatexPackage package;
	
	QStringList addPaths;
	if(config)
		addPaths<<config->importedCwlBaseDir;
	QString fn=findResourceFile("completion/"+fileName,false,addPaths);
	
	QFile tagsfile(fn);
	if (!fn.isEmpty() && tagsfile.open(QFile::ReadOnly)) {
	    QString line;
	    QTextStream stream(&tagsfile);
	    QRegExp rxCom("^(\\\\\\w+\\*?)(\\[.+\\])*\\{(.*)\\}");
	    QRegExp rxCom2("^(\\\\\\w+\\*?)\\[(.+)\\]");
	    rxCom.setMinimal(true);
	    QStringList keywords;
	    keywords << "text" << "title";
	    while (!stream.atEnd()) {
		line = stream.readLine().trimmed();
		if(line.startsWith("#include:")){
		    //include additional cwl file
		    QString fn=line.mid(9);
		    if(!fn.isEmpty()){
			if(fileName!=fn+".cwl" && !package.requiredPackages.contains(fn+".cwl"))
			    package.requiredPackages<<fn+".cwl";
		    }
		}
		if (!line.isEmpty() && !line.startsWith("#") && !line.startsWith(" ")) {
		    //hints for commands usage (e.g. in mathmode only) are separated by #
		    int sep=line.indexOf('#');
		    QString valid;
		    QStringList env;
		    bool uncommon=false;
		    bool hideFromCompletion=false;
		    if(sep>-1){
			valid=line.mid(sep+1);
			line=line.left(sep);
			if(valid.startsWith("*")){
			    valid=valid.mid(1);
			    uncommon=true;
			}
			if(valid.startsWith("/")){
			    env=valid.mid(1).split(',');
			    valid="e";
			}
			if(valid.contains("\\")){
			    int i=valid.indexOf("\\");
			    QString zw=valid.mid(i+1);
			    env=zw.split(',');
			    valid=valid.left(i);
			}
			if(valid.contains('S')){
			    hideFromCompletion=true;
			    valid.remove('S');
			}
		    }
            // parse for spell checkable commands
            int res=rxCom.indexIn(line);
            if(keywords.contains(rxCom.cap(3))){
                package.optionCommands << rxCom.cap(1);
            }
            rxCom2.indexIn(line); // for commands which don't have a braces part e.g. \item[text]
            if(keywords.contains(rxCom2.cap(2))){
                package.optionCommands << rxCom2.cap(1);
            }
            if(valid.contains('d')){ // definition command
                if(res>-1){
                    package.possibleCommands["%definition"] << rxCom.cap(1);
                }
                valid.remove('d');
            }
            if(valid.contains('i')){ // include like command
                if(res>-1){
                    package.possibleCommands["%include"] << rxCom.cap(1);
                }
                valid.remove('i');
            }
            if(valid.contains('l')){ // label command
                if(res>-1){
                    package.possibleCommands["%label"] << rxCom.cap(1);
                }
                valid.remove('l');
            }
            if(valid.contains('r')){ // ref command
                if(res>-1){
                    package.possibleCommands["%ref"] << rxCom.cap(1);
                }
                valid.remove('r');
            }
            if(valid.contains('c')){ // cite command
                if(res>-1){
                    package.possibleCommands["%cite"] << rxCom.cap(1);
                }
                valid.remove('c');
            }
            if(valid.contains('C')){ // cite command
                if(res>-1){
                    if(!line.contains("%")){
                        line.replace("{","{%<");
                        line.replace("}","%>}");
                    }
                    package.possibleCommands["%citeExtended"] << line.simplified();
                    hideFromCompletion=true;
                }
                valid.remove('C');
            }
            if(valid.contains('g')){ // definition command
                if(res>-1){
                    package.possibleCommands["%graphics"] << rxCom.cap(1);
                }
                valid.remove('g');
            }
            if(valid.contains('u')){ // usepackage command
                if(res>-1){
                    package.possibleCommands["%usepackage"] << rxCom.cap(1);
                }
                valid.remove('u');
            }
            if(valid.contains('b')){ // usepackage command
                if(res>-1){
                    package.possibleCommands["%bibliography"] << rxCom.cap(1);
                    package.possibleCommands["%file"] << rxCom.cap(1);
                }
                valid.remove('b');
            }
            if(valid.contains('U')){ // url command
                if(res>-1){
                    package.possibleCommands["%url"] << rxCom.cap(1);
                }
                valid.remove('U');
            }
		    // normal commands for syntax checking
		    // will be extended to distinguish between normal and math commands
		    if(valid.isEmpty() || valid.contains('n')){
			if(res>-1){
			    if(rxCom.cap(1)=="\\begin" || rxCom.cap(1)=="\\end"){
				package.possibleCommands["normal"] << rxCom.cap(1)+"{"+rxCom.cap(3)+"}";
			    } else {
				package.possibleCommands["normal"] << rxCom.cap(1);
			    }
			} else {
			    package.possibleCommands["normal"] << line.simplified();
			}
		    }
		    if(valid.contains('m')){ // math commands
			if(res>-1){
			    if(rxCom.cap(1)=="\\begin" || rxCom.cap(1)=="\\end"){
				package.possibleCommands["math"] << rxCom.cap(1)+"{"+rxCom.cap(3)+"}";
			    } else {
				package.possibleCommands["math"] << rxCom.cap(1);
			    }
			} else {
			    package.possibleCommands["math"] << line.simplified();
			}
		    }
		    if(valid.contains('t')){ // tabular commands
			if(res>-1){
			    if(rxCom.cap(1)=="\\begin" || rxCom.cap(1)=="\\end"){
				package.possibleCommands["tabular"] << rxCom.cap(1)+"{"+rxCom.cap(3)+"}";
				package.possibleCommands["array"] << rxCom.cap(1)+"{"+rxCom.cap(3)+"}";
			    } else {
				package.possibleCommands["tabular"] << rxCom.cap(1);
				package.possibleCommands["array"] << rxCom.cap(1);
			    }
			} else {
			    package.possibleCommands["tabular"] << line.simplified();
			    package.possibleCommands["array"] << line.simplified();
			}
		    }
		    if(valid.contains('T')){ // tabbing support
			if(res==-1){
			    package.possibleCommands["tabbing"] << line.simplified();
			}
		    }
		    if(valid.contains('e') && !env.isEmpty()){ // tabbing support
			if(res==-1){
			    foreach(const QString& elem,env)
				package.possibleCommands[elem] << line.simplified();
			}
		    }
		    if(!valid.contains('e') && !env.isEmpty()){ // set env alias
			if(res>-1){
			    if(rxCom.cap(1)=="\\begin"){
				QString envName=rxCom.cap(3);
				if(!envName.isEmpty()){

				    foreach(const QString& elem,env)
					package.environmentAliases.insert(rxCom.cap(3),elem);
				}
			    }
			}
		    }
		    // normal parsing for completer
		    if(hideFromCompletion)
			continue; // command for spell checking only (auto parser)
		    if (line.startsWith("\\pageref")||line.startsWith("\\ref")) continue;
		    if (!line.contains("%")){
			//add placeholders to brackets like () to (%<..%>)
			const QString brackets = "{}[]()<>";
			int lastOpen = -1, openType = -1;
			for (int i = 0; i < line.size(); i++) {
			    int index = brackets.indexOf(line[i]);
			    if (index>=0) {
				if (index % 2 == 0) {
				    lastOpen = i;
				    openType = index/2;
				} else {
				    if (lastOpen == -1 || openType != index/2)
					continue;
				    line.insert(lastOpen+1, "%<");
				    i+=2;
				    line.insert(i, "%>");
				    if (lastOpen+2 == i-1) {
					line.insert(i, QApplication::translate("CodeSnippet", "something"));
					i+=QApplication::translate("CodeSnippet", "something").length();
				    }
				    lastOpen = -1;
				    i+=2;
				}
			    }
			}
			if (line.startsWith("\\begin")||line.startsWith("\\end")) {
			    int i=line.indexOf("%<",0);
			    line.replace(i,2,"");
			    i=line.indexOf("%>",0);
			    line.replace(i,2,"");
			    if (line.endsWith("\\item"))
				line.chop(5);

			}
		    }
		    if(!words.contains(line)){
			words.append(line);
			if(uncommon && config){
			    int hash=qHash(line);
			    int len=line.length();
			    QList<QPair<int,int> >res=config->usage.values(hash);
			    for(int i=0;i<res.count();i++){
				QPair<int,int> elem=res.at(i);
				if(elem.first==len){
				    uncommon=false;
				    break;
				}
			    }
			    if(uncommon){
				config->usage.insert(hash,qMakePair(len,-1));
			    }

			}
		    }
		}
	    }
	}else{
	    //qDebug() << "Completion file not found:" << fileName;
	    package.packageName="<notFound>";
	}
	
	QApplication::restoreOverrideCursor();
	package.completionWords=words;
	return package;
    }

LatexPackage::LatexPackage(){
	completionWords.clear();
	packageName.clear();
}

void LatexPackage::unite(LatexPackage &add){
	completionWords.append(add.completionWords);
	optionCommands.unite(add.optionCommands);
	environmentAliases.unite(add.environmentAliases);
	//possibleCommands.unite(add.possibleCommands);
	foreach(const QString& elem,add.possibleCommands.keys()){
		QSet<QString> set2=add.possibleCommands[elem];
		QSet<QString> set=possibleCommands[elem];
		set.unite(set2);
		possibleCommands[elem]=set;
	}
}


QString getImageAsText(const QPixmap &AImage) {
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    AImage.save(&buffer, "PNG");
    return QString("<img src=\"data:image/png;base64,%1\">").arg(QString(buffer.data().toBase64()));
}

void showTooltipLimited(QPoint tt,QString topic,int width){
    topic.replace("\t","    "); //if there are tabs at the position in the string, qt crashes. (13707)
    QRect screen = QApplication::desktop()->availableGeometry();
    // estimate width of coming tooltip
    // rather dirty code
    QLabel lLabel(0,Qt::ToolTip);
    lLabel.setFont(QToolTip::font());
    lLabel.setMargin(1 + lLabel.style()->pixelMetric(QStyle::PM_ToolTipLabelFrameWidth, 0, &lLabel));
    lLabel.setFrameStyle(QFrame::StyledPanel);
    lLabel.setAlignment(Qt::AlignLeft);
    lLabel.setIndent(1);
    //lLabel.setWordWrap(true);
    //lLabel.ensurePolished();
    lLabel.setText(topic);
    lLabel.adjustSize();


    int textWidthInPixels = lLabel.width()+10; // +10 good guess

    if (screen.width()-textWidthInPixels>=tt.x()) QToolTip::showText(tt, topic);//-90
    else {
        //list->mapToGlobal
        QPoint tt2(tt.x()-textWidthInPixels-width, tt.y());

        // check if text left from list would fit
        bool reCalc=false;
        if(tt2.x()<0){
            //determine max usable width
            int w=tt.x()-width;
            if(screen.width()-tt.x()>w){
                w=screen.width()-tt.x();
                tt2=tt;
            }else{
                reCalc=true;
            }
            // shorten text to fit textwidth
            QStringList lTopic=topic.split("\n");
            int maxLength=0;
            QString maxLine;
            foreach(const QString elem,lTopic){
                if(elem.length()>maxLength){
                    maxLength= elem.length();
                    maxLine=elem;
                }
            }
            while(textWidthInPixels>w && maxLength>10){
                maxLength--;
                lLabel.setText(maxLine.left(maxLength));
                lLabel.adjustSize();
                textWidthInPixels=lLabel.width()+10;
            }
            for(int i=0;i<lTopic.count();i++){
                lTopic[i]=lTopic[i].left(maxLength);
            }
            topic=lTopic.join("\n");
        }
        if(reCalc){
            tt2.setX(tt.x()-textWidthInPixels-width);
        }
        QToolTip::showText(tt2, topic);
    }
}
