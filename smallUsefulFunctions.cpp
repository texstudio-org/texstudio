#include "smallUsefulFunctions.h"

#ifdef Q_WS_MAC
#include <CoreFoundation/CFURL.h>
#include <CoreFoundation/CFBundle.h>
#endif

const QString CommonEOW="~!@#$%^&*()_+{}|:\"\\<>?,./;[]-= \t\n\r`+ï¿½´";
const QString EscapedChars="%&_";
const QString CharacterAlteringChars="\"";

QSet<QString> LatexParser::refCommands = QSet<QString>::fromList(QStringList() << "\\ref" << "\\pageref");
QSet<QString> LatexParser::labelCommands = QSet<QString>::fromList(QStringList() << "\\label");
QSet<QString> LatexParser::citeCommands = QSet<QString>::fromList(QStringList() << "\\cite" << "\\citet" << "\\citetitle" << "\\citep" << "\\citeauthor" << "\\footcite" << "\\nocite"  << "\\nptextcite" << "\\parencite" << "\\textcite");
QSet<QString> LatexParser::environmentCommands = QSet<QString>::fromList(QStringList() << "\\begin" << "\\end" << "\\newenvironment" << "\\renewenvironment");
QSet<QString> LatexParser::optionCommands; // = QSet<QString>::fromList(QStringList() << LatexParser::refCommands.toList() << LatexParser::labelCommands.toList() << "\\includegraphics" << "\\usepackage" << "\\documentclass" << "\\include" << "\\input" << "\\hspace" << "\\vspace");
QStringList LatexParser::structureCommands = QStringList(); //see texmaker.cpp

QString getCommonEOW() {
	return CommonEOW;
}

QStringList findResourceFiles(const QString& dirName, const QString& filter) {
	QStringList searchFiles;
	QString dn = dirName;
	if (dn.endsWith('/')||dn.endsWith(QDir::separator())) dn=dn.left(dn.length()-1); //remove / at the end
	if (!dn.startsWith('/')&&!dn.startsWith(QDir::separator())) dn="/"+dn; //add / at beginning
	searchFiles<<":"+dn; //resource fall back
	searchFiles<<QCoreApplication::applicationDirPath() + dn; //windows new
	// searchFiles<<QCoreApplication::applicationDirPath() + "/data/"+fileName; //windows new
#if defined( Q_WS_X11 )
	searchFiles<<PREFIX"/share/texmakerx"+dn; //X_11
#endif
#ifdef Q_WS_MAC
        CFURLRef appUrlRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
        CFStringRef macPath = CFURLCopyFileSystemPath(appUrlRef,
                                                      kCFURLPOSIXPathStyle);
        const char *pathPtr = CFStringGetCStringPtr(macPath,
                                                    CFStringGetSystemEncoding());
        searchFiles<<QString(pathPtr)+"/Contents/Resources"+dn; //Mac
        CFRelease(appUrlRef);
        CFRelease(macPath);
#endif

	QStringList result;
	foreach(const QString& fn, searchFiles) {
		QDir fic(fn);
		if (fic.exists() && fic.isReadable()) 
			result<< fic.entryList(QStringList(filter),QDir::Files,QDir::Name);
	}
	// sort and remove double entries
	result.sort();

	QMutableStringListIterator i(result);
	QString old="";
	while(i.hasNext()){
		QString cmp=i.next();
		if(cmp==old) i.remove();
		else old=cmp;
	}
	return result;
}

QString findResourceFile(const QString& fileName, bool allowOverride, QStringList additionalPreferredPaths, QStringList additionalFallbackPaths) {
	QStringList searchFiles;

	if (!allowOverride) searchFiles<<":/"; //search first in included resources (much faster)

	foreach (const QString& s, additionalPreferredPaths)
		if (s.endsWith('/') || s.endsWith('\\')) searchFiles << s;
		else searchFiles << s + "/";
#ifdef Q_WS_X11
	searchFiles<<PREFIX"/share/texmakerx/"; //X_11
#endif
#ifdef Q_WS_MAC
	searchFiles<<QCoreApplication::applicationDirPath() + "/../Resources/"; //macx
#endif
	searchFiles<<QCoreApplication::applicationDirPath() + "/"; //windows old
	searchFiles<<QCoreApplication::applicationDirPath() + "/dictionaries/"; //windows new
	searchFiles<<QCoreApplication::applicationDirPath() + "/translations/"; //windows new
	searchFiles<<QCoreApplication::applicationDirPath() + "/help/"; //windows new
	searchFiles<<QCoreApplication::applicationDirPath() + "/utilities/"; //windows new
	// searchFiles<<QCoreApplication::applicationDirPath() + "/data/"; //windows new

	if (allowOverride) searchFiles<<":/"; //resource fall back

	foreach (const QString& s, additionalFallbackPaths)
		if (s.endsWith('/') || s.endsWith('\\')) searchFiles << s;
		else searchFiles << s + "/";

	foreach(const QString& fn, searchFiles) {
		QFileInfo fic(fn + fileName);
		if (fic.exists() && fic.isReadable())
			return fn + fileName;
	}
	return "";
}

bool isFileRealWritable(const QString& filename) {
#ifdef Q_WS_WIN
	//thanks to Vistas virtual folders trying to open an unaccessable file can create it somewhere else
	return QFileInfo(filename).isWritable();
#endif
	QFile fi(filename);
	bool result=false;
	if (fi.exists()) result=fi.open(QIODevice::ReadWrite);
	else {
		result=fi.open(QIODevice::WriteOnly);
		fi.remove();
	}
	return result;
}

bool isExistingFileRealWritable(const QString& filename) {
	return QFileInfo(filename).exists() && isFileRealWritable(filename);
}

QString ensureTrailingDirSeparator(const QString& dirPath){
	if (dirPath.endsWith("/")) return dirPath;
	if (dirPath.endsWith(QDir::separator())) return dirPath;
#ifdef Q_WS_WIN
	if (dirPath.endsWith("\\")) return dirPath; //you can create a directory named \ on linux
#endif
	return dirPath+"/";
}


int x11desktop_env() {
	// 0 : no kde ; 3: kde ; 4 : kde4 ;
	QString kdesession= ::getenv("KDE_FULL_SESSION");
	QString kdeversion= ::getenv("KDE_SESSION_VERSION");
	if (!kdeversion.isEmpty()) return 4;
	if (!kdesession.isEmpty()) return 3;
	return 0;
}


QString latexToPlainWord(const QString& word) {
	QList<QPair<QString,QString> > replaceList;
	replaceList.append(QPair<QString, QString> ("\\-","")); //Trennung [separation] (german-babel-package also: \")
	replaceList.append(QPair<QString, QString> ("\\/","")); //ligatur preventing (german-package also: "|)
	replaceList.append(QPair<QString, QString> ("\"~","-")); //- ohne Trennung (without separation)
	//german-babel-package: "- (\- but also normal break),  "= ( like - but also normal break), "" (umbruch ohne bindestrich)
	replaceList.append(QPair<QString, QString> ("\"-",""));
	replaceList.append(QPair<QString, QString> ("\"a","\xE4"));
	replaceList.append(QPair<QString, QString> ("\"o","\xF6"));
	replaceList.append(QPair<QString, QString> ("\"u","\xFC"));
	replaceList.append(QPair<QString, QString> ("\"s","\xDF"));
	replaceList.append(QPair<QString, QString> ("\"A","\xC4"));
	replaceList.append(QPair<QString, QString> ("\"O","\xD6"));
	replaceList.append(QPair<QString, QString> ("\"U","\xDC"));
	replaceList.append(QPair<QString, QString> ("\\\"{a}","\xE4"));
	replaceList.append(QPair<QString, QString> ("\\\"{o}","\xF6"));
	replaceList.append(QPair<QString, QString> ("\\\"{u}","\xFC"));
	replaceList.append(QPair<QString, QString> ("\\\"{A}","\xC4"));
	replaceList.append(QPair<QString, QString> ("\\\"{O}","\xD6"));
	replaceList.append(QPair<QString, QString> ("\\\"{U}","\xDC"));
	replaceList.append(QPair<QString, QString> ("\"|",""));
	replaceList.append(QPair<QString, QString> ("\"",""));
	//replaceList.append(QPair<QString, QString> ("\"\"","")); redunant
	replaceList.append(QPair<QString, QString> ("\\","")); // eliminating backslash which might remain from accents like \"a ...

	QString result=word;
	for (QList<QPair<QString,QString> >::const_iterator it=replaceList.begin(); it!=replaceList.end(); ++it)
		result.replace(it->first,it->second);

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

int findClosingBracket(const QString& word,int &start) {
	int i=0;
	if(start<0) start=word.indexOf("{",i);
	i=start>-1 ? start : 0;
	int stop=word.indexOf("}",i);
	i=word.indexOf("{",i+1);
	while (i>0 && stop>0 && i<stop) {
		stop=word.indexOf("}",stop+1);
		i=word.indexOf("{",i+1);
	}
	return stop;
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

bool localAwareLessThan(const QString &s1, const QString &s2) {
	return QString::localeAwareCompare(s1,s2)<0;
}


int nextToken(const QString &line,int &index,bool abbreviation,bool inOption) {
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
		if(doubleQuoteChar && cur=='\'') break; // check for words staring with "' (german quotation mark)
		else doubleQuoteChar=false;
		if (inCmd) {
			if (CommonEOW.indexOf(cur)>=0) {
				if (i-start==1) i++;
				break;
			}
		} else if (inWord) {
			if (cur=='\\') {
				if (i+1<line.size() && (line.at(i+1)=='-'||EscapedChars.indexOf(line.at(i+1))>=0||CharacterAlteringChars.indexOf(line.at(i+1))>=0))  {
					if(CharacterAlteringChars.indexOf(line.at(i+1))>=0) ignoreBrace=true;
					i++;//ignore word separation marker and _ respectively
					//reparse=true;
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
			} else if (cur=='.' && abbreviation) {
				i++; //take '.' into word, so that abbreviations, at least German ones, are checked correctly
				break;
			} else if (CommonEOW.indexOf(cur)>=0 && !inOption) {
				break;
			    } else if(cur=='}' || cur==']') break;

		} else if (cur=='\\') {
			if (i+1<line.size() && (EscapedChars.indexOf(line.at(i+1))>=0||CharacterAlteringChars.indexOf(line.at(i+1))>=0))  {
				inWord=true;
				start=i;
				if(CharacterAlteringChars.indexOf(line.at(i+1))>=0) ignoreBrace=true;
				i++;
			}else{
				start=i;
				inCmd=true;
			}
		} else if (cur=='{' || cur=='}' || cur=='%' || cur=='[' || cur==']') {
			index=i+1;
			return i;
                } else if ((CommonEOW.indexOf(cur)<0 && cur!='\'' )|| cur=='"') {
			start=i;
			inWord=true;
			doubleQuoteChar= ( cur == '"');
		}
	}
	if (singleQuoteChar && i-1<line.size() && line.at(i-1)=='\'') 
		i--; //remove ' when a word ends with it  (starting is handled because ' does not start a word)
	index=i;
	return start;
}


NextWordFlag nextWord(const QString &line,int &index,QString &outWord,int &wordStartIndex, bool returnCommands,bool abbreviations) {
	int reference=-1;
	QString lastCommand="";
	bool inOption=false;
	bool inEnv=false;
	while ((wordStartIndex = nextToken(line, index,abbreviations,inEnv))!=-1) {
		outWord=line.mid(wordStartIndex,index-wordStartIndex);
		if (outWord.length()==0) return NW_NOTHING; //should never happen
		switch (outWord.at(0).toAscii()) {
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
			if(LatexParser::environmentCommands.contains(lastCommand)) inEnv=true;
			break; //ignore
		case '}':
			if (reference!=-1) {
			    if (LatexParser::refCommands.contains(lastCommand)){
					wordStartIndex=reference;
					--index;
					outWord=line.mid(reference,index-reference);
					return NW_REFERENCE;
				} else {
					if (LatexParser::labelCommands.contains(lastCommand)){
						wordStartIndex=reference;
						--index;
						outWord=line.mid(reference,index-reference);
						return NW_LABEL;
					} else {
						if (LatexParser::citeCommands.contains(lastCommand)){
							wordStartIndex=reference;
							--index;
							outWord=line.mid(reference,index-reference);
							return NW_CITATION;
						}
					}
				}
			}
			lastCommand="";
			inOption=false;
			inEnv=false;
			break;//command doesn't matter anymore
		case '\\':
			if (outWord.length()==1 || !(EscapedChars.contains(outWord.at(1)) || CharacterAlteringChars.contains(outWord.at(1)))) {
				if (returnCommands) return NW_COMMAND;
				if (LatexParser::refCommands.contains(outWord)||LatexParser::labelCommands.contains(outWord)||LatexParser::citeCommands.contains(outWord)){
					reference=index; //todo: support for nested brackets like \cite[\xy{\ab{s}}]{miau}
					lastCommand=outWord;
				}
				if (LatexParser::optionCommands.contains(lastCommand)||lastCommand.isEmpty()) {
					lastCommand=outWord;
				}
				break;
			} else {;} //first character is escaped, fall through to default case
		default:
			if (reference==-1) {
				if(!inOption && !lastCommand.isEmpty()){
					inOption=false;
					lastCommand="";
				}
				if (outWord.contains("\\")||outWord.contains("\""))
					outWord=latexToPlainWord(outWord); //remove special chars
				if (LatexParser::environmentCommands.contains(lastCommand))
					return NW_ENVIRONMENT;
				if (LatexParser::optionCommands.contains(lastCommand)||lastCommand.isEmpty())
					return NW_TEXT;
			}
		}
	}
	return NW_NOTHING;
}

bool nextTextWord(const QString & line, int &index, QString &outWord, int &wordStartIndex) {
	NextWordFlag flag;
	//flag can be nothing, text, comment, environment
	//text/comment returns false, text returns true, environment is ignored
	while ((flag=nextWord(line,index,outWord,wordStartIndex,false))==NW_ENVIRONMENT)
		;
	return flag==NW_TEXT;
}

QString findToken(const QString &line,const QString &token){
	int tagStart=line.indexOf(token);
	if (tagStart!=-1) {
		tagStart+=token.length();
		int tagEnd=line.indexOf("}",tagStart);
		if (tagEnd!=-1) return line.mid(tagStart,tagEnd-tagStart);
		else return line.mid(tagStart); //return everything after line if there is no }
	}
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

bool findCommandWithArg(const QString &line,QString &cmd, QString &outName, QString &outArg, QString &remainder){
	outName="";
	outArg="";
	remainder="";
	QRegExp token("\\\\\\w+");
	int tagStart=token.indexIn(line);
	int commentStart=line.indexOf(QRegExp("(^|[^\\\\])%")); // find start of comment (if any)
	if (tagStart!=-1 && (commentStart>tagStart || commentStart==-1)) {
		cmd=token.cap(0);
		tagStart+=cmd.length();
		int i=tagStart;
		int start=-1;
		start=line.indexOf("{",i);
		i=start>-1 ? start : 0;
		int stop=line.indexOf("}",i);
		i=line.indexOf("{",i+1);
		while (i>0 && stop>0 && i<stop) {
			stop=line.indexOf("}",stop+1);
			i=line.indexOf("{",i+1);
		}
		if (stop<0) stop=line.length();
		outName=line.mid(start+1,stop-start-1);
		remainder=line.mid(stop+1);
		return true;
	}
	return false;

}



QToolButton* createComboToolButton(QWidget *parent,const QStringList& list,const int height,const QFontMetrics fm,const QObject * receiver, const char * member,QString defaultElem,QToolButton *combo){
	if(combo==0) combo=new QToolButton(parent);
	combo->setPopupMode(QToolButton::MenuButtonPopup);
	combo->setMinimumHeight(height);

	QAction *mAction=0;
	// remove old actions
	foreach(mAction, combo->actions()){
		combo->removeAction(mAction);
	}
	if(list.isEmpty()){
		mAction=new QAction("<"+QApplication::tr("none")+">",combo);
	} else {
		mAction=new QAction(list[0],combo);
	}
	QObject::connect(mAction, SIGNAL(triggered()),receiver,member);
	combo->setDefaultAction(mAction);
	QMenu *mMenu=new QMenu(combo);
	int max=0;
	foreach(QString elem,list){
		mAction=mMenu->addAction(elem,receiver,member);
		max=qMax(max,fm.width(elem+"        "));
		if(elem==defaultElem) combo->setDefaultAction(mAction);
	}
	combo->setMinimumWidth(max);
	combo->setMenu(mMenu);
	return combo;
}

QToolButton* comboToolButtonFromAction(QAction* action){
	if (!action) return 0;
	QToolButton *button = qobject_cast<QToolButton*>(action->parent());
	if (!button) {
		QMenu* menu=qobject_cast<QMenu*>(action->parent());
		if (!menu) return 0;
		button=qobject_cast<QToolButton*>(menu->parent());
		if (!button) return 0;
	}
	return button;
}

bool hasAtLeastQt(int major, int minor){
	QStringList vers=QString(qVersion()).split('.');
	if (vers.count()<2) return false;
	int ma=vers[0].toInt();
	int mi=vers[1].toInt();
	return (ma>major) || (ma==major && mi>=minor);
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

void addEnvironmentToDom(QDomDocument& doc,const QString EnvironName,const QString EnvironMode){
	QDomElement root= doc.documentElement();
	QDomElement tag = doc.createElement("context");
	tag.setAttribute("id","myVerb");
	tag.setAttribute("format",EnvironMode);
	tag.setAttribute("transparency","true");
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

int LatexParser::findContext(QString &line,int col){
	int start_command=col;
	int start_ref=col;
	int start_close=col;
	int stop=col;
	int bow=col;
	QString helper=line.mid(0,col);
	start_command=helper.lastIndexOf("\\");
	start_ref=helper.lastIndexOf("{");
	start_close=helper.lastIndexOf("}");
	bow=helper.lastIndexOf("[");
	if(bow<helper.lastIndexOf(" ")) bow=helper.lastIndexOf(" ");
	helper=line.mid(col,line.length());
	if((start_command>start_ref)&&(start_command>start_close)&&(start_command>bow)){
		helper=line.mid(start_command);
		stop=helper.indexOf("{");
		if(stop>-1) stop=stop;
		else {
			stop=helper.indexOf("[");
			int stop2=helper.indexOf(" ");
			if(stop==-1) stop=stop2;
			if(stop2==-1) stop2=stop;
			if(stop2<stop) stop=stop2;
		}
		if(stop==-1) stop=helper.length();
		line=helper.mid(0,stop);
		return 1;
	}
	if((start_ref>start_command)&&(start_command>start_close)){
		stop=helper.indexOf("}")+col;
		line=line.mid(start_command,stop-start_command);
		return 2;
	}
	return 0;
}

LatexParser::ContextType LatexParser::findContext(const QString &line, int column, QString &command, QString& value){
	command=line;
	int temp=findContext(command,column);
	int a=command.indexOf("{");
	if (a>=0) {
		int b=command.indexOf("}");
		if (b<0) b = command.length();
		value=command.mid(a+1,b-a-1);
		command=command.left(a);
	} else {
		int a=line.indexOf("{",column);
		int b=line.indexOf("}",column);
		value=line.mid(a+1,b-a-1);
	}
	switch (temp) {
		case 0: return Unknown;
		case 1: return Command;
		case 2: 
			if (LatexParser::environmentCommands.contains(command))
				return Environment;
			else if (LatexParser::labelCommands.contains(command))
				return Label;
			else if (LatexParser::refCommands.contains(command))
				return Reference;
			else if (LatexParser::citeCommands.contains(command))
				return Citation;
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

QString getRelativeBaseNameToPath(const QString & file,QString basepath){
	basepath.replace(QDir::separator(),"/");
	if (basepath.endsWith("/")) basepath=basepath.left(basepath.length()-1);

	QFileInfo fi(file);
	QString filename = fi.fileName();
	QString path = fi.path();
	if (path.endsWith("/")) path=path.left(path.length()-1);
	QStringList basedirs = basepath.split("/");
	QStringList dirs = path.split("/");
	//QStringList basedirs = QStringList::split("/", basepath, false);
	//QStringList dirs = QStringList::split("/", path, false);

	int nDirs = dirs.count();

	while (dirs.count() > 0 && basedirs.count() > 0 &&  dirs[0] == basedirs[0]) {
		dirs.pop_front();
		basedirs.pop_front();
	}

	if (nDirs != dirs.count()) {
		path = dirs.join("/");

		if (basedirs.count() > 0) {
			for (int j=0; j < basedirs.count(); ++j) {
				path = "../" + path;
			}
		}

		//if (path.length()>0 && path.right(1) != "/") path = path + "/";
	} else {
		path = fi.path();
	}

	if (path.length()>0 && !path.endsWith("/") && !path.endsWith("\\")) path+="/"; //necessary if basepath isn't given

	return path+fi.completeBaseName();
}

QString getPathfromFilename(const QString &compFile){
	if (compFile.isEmpty()) return "";
	QString dir=QFileInfo(compFile).absolutePath();
	if (!dir.endsWith("/") && !dir.endsWith(QDir::separator())) dir.append(QDir::separator());
	return dir;
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

QTextCodec* LatexParser::guessEncoding(const QByteArray& data){
	int headerSize = data.indexOf("\\begin{document}");
	if (headerSize == -1) headerSize = data.size();
	//search for \usepackage[.*]{inputenc} outside of a comment
	int index = data.indexOf("]{inputenc}");
	while (index >= 0) {
		if (index >= headerSize) return 0;
		int previous = data.lastIndexOf("\\usepackage[",index);
		if (previous >= 0){
			int commentStart = data.lastIndexOf('%',index);
			int commentEnd = qMax(data.lastIndexOf('\n',index),data.lastIndexOf('\r',index));
			if (commentStart <= commentEnd) {
				QString encoding = QString(data.mid(previous+12, index - (previous + 12)));
				QTextCodec* codec = QTextCodecForLatexName(encoding);
				if (codec) return codec;
			}
		}
		index = data.indexOf("]{inputenc}", index + 1);
	}
	//search for \usepackage[.*]{inputenx} outside of a comment
	index = data.indexOf("]{inputenx}");
	while (index >= 0) {
		if (index >= headerSize) return 0;
		int previous = data.lastIndexOf("\\usepackage[",index);
		if (previous >= 0){
			int commentStart = data.lastIndexOf('%',index);
			int commentEnd = qMax(data.lastIndexOf('\n',index),data.lastIndexOf('\r',index));
			if (commentStart <= commentEnd) {
				QString encoding = QString(data.mid(previous+12, index - (previous + 12)));
				QTextCodec* codec = QTextCodecForLatexName(encoding);
				if (codec) return codec;
			}
		}
		index = data.indexOf("]{inputenx}", index + 1);
	}
	return 0;
}
