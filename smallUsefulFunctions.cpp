#include "smallUsefulFunctions.h"
#include "latexcompleter_config.h"
#include "qdocumentline.h"
#include <QMutex>
#include <QBuffer>

extern const char* TEXSTUDIO_SVN_VERSION;

int getSimplifiedSVNVersion(QString svnVersion) {
	int cutoff = svnVersion.indexOf(QRegExp("[^0-9]"));
	if (cutoff < 0)
		return svnVersion.toInt();
	else
		return svnVersion.left(cutoff).toInt();
}

bool txsConfirm(const QString &message){
	return QMessageBox::question(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes;
}
bool txsConfirmWarning(const QString &message){
	return QMessageBox::warning(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes;
}
QMessageBox::StandardButton txsConfirmWarning(const QString &message, QMessageBox::StandardButtons buttons){
	return QMessageBox::warning(QApplication::activeWindow(), TEXSTUDIO, message, buttons, QMessageBox::Yes);
}
void txsInformation(const QString &message){
	QMessageBox::information(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Ok);
}
void txsWarning(const QString &message){
	QMessageBox::warning(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Ok);
}
void txsWarning(const QString &message, bool &noWarnAgain){
	QMessageBox msgBox(QMessageBox::Warning, TEXSTUDIO, message, QMessageBox::Ok, QApplication::activeWindow());
	QCheckBox cbNoWarnAgain(QCoreApplication::translate("Texmaker", "Do not warn again.", "General warning dialog"), &msgBox);
	cbNoWarnAgain.setChecked(noWarnAgain);
	cbNoWarnAgain.blockSignals(true); // quick hack to prevent closing the message box
	msgBox.addButton(&cbNoWarnAgain, QMessageBox::ActionRole);
	msgBox.exec();
	noWarnAgain = cbNoWarnAgain.isChecked();
}

void txsCritical(const QString &message){
	QMessageBox::critical(QApplication::activeWindow(), TEXSTUDIO, message, QMessageBox::Ok);
}


#ifdef Q_OS_WIN
#include <windows.h>
#endif
bool getDiskFreeSpace(const QString &path, quint64 &freeBytes) {
#ifdef Q_OS_WIN
	wchar_t d[path.size()+1];
	int len = path.toWCharArray(d);
	d[len] = 0;

	ULARGE_INTEGER freeBytesToCaller;
	freeBytesToCaller.QuadPart = 0L;

	if( !GetDiskFreeSpaceEx( d, &freeBytesToCaller, NULL, NULL ) ) {
		qDebug() << "ERROR: Call to GetDiskFreeSpaceEx() failed on path" << path;
		return false;
	}
	freeBytes = freeBytesToCaller.QuadPart;
	return true;
#else
	return false;
#endif
}



#ifdef Q_WS_MAC
#include <CoreFoundation/CFURL.h>
#include <CoreFoundation/CFBundle.h>
#endif

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
    possibleCommands["normal"]=QSet<QString>::fromList(QStringList() << "\\\\" << "\\-" << "$" << "$$" << "\\$" << "\\#" << "\\{" << "\\}" << "\\S" << "\\'" << "\\`" << "\\^" << "\\=" <<"\\." <<"\\u" <<"\\v" << "\\H" << "\\t" << "\\c" << "\\d" << "\\b" << "\\oe" << "\\OE" << "\\ae" << "\\AE" << "\\aa" << "\\AA" << "\\o" << "\\O" << "\\l" << "\\L" << "\\~" << "\\ " << "\\,");
    possibleCommands["math"]=QSet<QString>::fromList(QStringList() << "_" << "^" << "\\$" << "\\#" << "\\{" << "\\}" << "\\S" << "\\," << "\\!" << "\\;" << "\\:" << "\\\\" << "\\ " << "\\|");
    possibleCommands["%definition"] << "\\newcommand" << "\\renewcommand" << "\\newcommand*" << "\renewcommand*" << "\\providecommand" << "\\DeclareMathOperator" << "\\DeclareMathSymbol" <<"\\newlength" << "\\DeclareRobustCommand";
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
			if (CommonEOW.indexOf(cur)>=0) {
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


QStringList findResourceFiles(const QString& dirName, const QString& filter, QStringList additionalPreferredPaths) {
	QStringList searchFiles;
	QString dn = dirName;
	if (dn.endsWith('/')||dn.endsWith(QDir::separator())) dn=dn.left(dn.length()-1); //remove / at the end
	if (!dn.startsWith('/')&&!dn.startsWith(QDir::separator())) dn="/"+dn; //add / at beginning
	searchFiles<<":"+dn; //resource fall back
	searchFiles.append(additionalPreferredPaths);
	searchFiles<<QCoreApplication::applicationDirPath() + dn; //windows new
	// searchFiles<<QCoreApplication::applicationDirPath() + "/data/"+fileName; //windows new

#if !defined(PREFIX)
#define PREFIX ""
#endif
	
#if defined( Q_WS_X11 )
	searchFiles<<PREFIX"/share/texstudio"+dn; //X_11
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
	searchFiles<<PREFIX"/share/texstudio/"; //X_11
	searchFiles<<PREFIX"/share/texmakerx/"; //X_11
	if (fileName.endsWith(".html")) searchFiles<<PREFIX"/share/doc/texstudio/html/";  //for Debian package
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
			return fic.canonicalFilePath();
	}
	QString newFileName=fileName.split("/").last();
	if(!newFileName.isEmpty()){
		foreach(const QString& fn, searchFiles) {
			QFileInfo fic(fn + newFileName);
			if (fic.exists() && fic.isReadable())
				return fic.canonicalFilePath();
		}
	}
	return "";
}

bool modernStyle;
bool useSystemTheme;
QString getRealIconFile(const QString& icon){
	if (icon.isEmpty() || icon.startsWith(":/")) return icon;
	if (modernStyle && QFileInfo(":/modern/images/modern/"+icon).exists())
		return ":/modern/images/modern/"+icon;
	else if (!modernStyle && QFileInfo(":/classic/images/classic/"+icon).exists())
		return ":/classic/images/classic/"+icon;
	else if (QFileInfo(":/images/"+icon).exists())
		return ":/images/"+icon;
	return icon;
}

QIcon getRealIcon(const QString& icon){
	if (icon.isEmpty()) return QIcon();
	if (icon.startsWith(":/")) return QIcon(icon);
#if QT_VERSION >= 0x040600
	if (useSystemTheme && QIcon::hasThemeIcon(icon)) return QIcon::fromTheme(icon);
#endif
	return QIcon(getRealIconFile(icon.contains(".")?icon:(icon+".png")));
}

bool isFileRealWritable(const QString& filename) {
#ifdef Q_WS_WIN
#if QT_VERSION >= 0x040700
    //bug in 4.7 still present in 4.8.0
	return (QFileInfo(filename).exists() && QFileInfo(filename).isWritable()) ||
	              (!QFileInfo(filename).exists() && QFileInfo(QFileInfo(filename).absolutePath()).isWritable());
#else
	//thanks to Vistas virtual folders trying to open an unaccessable file can create it somewhere else
	return QFileInfo(filename).isWritable();
#endif
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

QString replaceFileExtension(const QString& filename, const QString& newExtension, bool appendIfNoExt) {
	QFileInfo fi(filename);
	QString ext = newExtension.startsWith('.') ? newExtension.mid(1) : newExtension;
	if (fi.suffix().isEmpty()) {
		if (appendIfNoExt)
			return filename + '.' + ext;
		else
			return QString();
	}

	return filename.left(filename.length()-fi.completeSuffix().length()) + ext;
}



int x11desktop_env() {
	// 0 : no kde ; 3: kde ; 4 : kde4 ;
	QString kdesession= ::getenv("KDE_FULL_SESSION");
	QString kdeversion= ::getenv("KDE_SESSION_VERSION");
	if (!kdeversion.isEmpty()) return 4;
	if (!kdesession.isEmpty()) return 3;
	return 0;
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
	switch (c.toAscii()){
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
			switch (word[i].toAscii()) {
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
			switch (word[i].toAscii()) {
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

bool localAwareLessThan(const QString &s1, const QString &s2) {
	return QString::localeAwareCompare(s1,s2)<0;
}

// removes whitespace from the beginning of the string
QString trimLeft(const QString &s) {
	int j;
	for (j=0; j<s.length();j++)
		if (s[j]!=' ' && s[j]!='\t' && s[j]!='\r' && s[j]!='\n') break;
	return s.mid(j);
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
                    if(first.startsWith('['))
                        return false; //two options [..][...]
                }else{
                    return false; //no argument after option
                }
            }
            optionStart=start+1;
            remainder=line.mid(start+first.length());
            outName=LatexParser::removeOptionBrackets(first);
            return true;
        }
    }
	return false;
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


QToolButton* createComboToolButton(QWidget *parent,const QStringList& list, int height, const QObject * receiver, const char * member,QString defaultElem,QToolButton *combo){	
	const QFontMetrics &fm = parent->fontMetrics();
	if (height == -1) height = 0;
	else if (height == 0) {
		if (parent->property("innerButtonHeight").isValid()) height =parent->property("innerButtonHeight").toInt();
		else {
			height = parent->height() - 2;
			parent->setProperty("innerButtonHeight", height);
		}
	}
	
	if (combo==0) 
		combo=new QToolButton(parent);
	if (height != 0)
		combo->setMinimumHeight(height);
	combo->setPopupMode(QToolButton::MenuButtonPopup);
	
	// remove old actions
	foreach(QAction * mAction, combo->actions())
		combo->removeAction(mAction);
	
	QMenu *mMenu=new QMenu(combo);
	int max=0;
	bool defaultSet = false;
	foreach(const QString& elem,list){
		QAction* mAction=mMenu->addAction(elem,receiver,member);
		max=qMax(max,fm.width(elem+"        "));
		if(elem==defaultElem) {
			combo->setDefaultAction(mAction);
			defaultSet = true;
		}
	}
	if (!defaultSet){
		if(list.isEmpty())
			combo->setDefaultAction(new QAction("<"+QApplication::tr("none")+">",combo));
		else
			combo->setDefaultAction(mMenu->actions().first());
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

QToolButton* createToolButtonForAction(QAction* action) {
	QToolButton *tb = new QToolButton();
	if (!action->icon().isNull())
		tb->setIcon(action->icon());
	else
		tb->setText(action->text());
	tb->setToolTip(action->toolTip());
	tb->setCheckable(action->isCheckable());
	tb->setChecked(action->isChecked());
	tb->connect(tb, SIGNAL(clicked(bool)), action, SLOT(setChecked(bool)));
	tb->connect(action, SIGNAL(toggled(bool)), tb, SLOT(setChecked(bool)));
	return tb;
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

void LatexParser::resolveCommandOptions(const QString &line, int column, QStringList &values, QList<int> *starts){
	const QString BracketsOpen("[{");
	const QString BracketsClose("]}");
	int start=column;
	int stop=-1;
	int type;
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
	QString eow="\\[]{} ";
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

QString getRelativeBaseNameToPath(const QString & file,QString basepath,bool baseFile,bool keepSuffix){
	basepath.replace(QDir::separator(),"/");
	if (basepath.endsWith("/")) basepath=basepath.left(basepath.length()-1);
	
	QFileInfo fi(file);
	QString filename = fi.fileName();
	QString path = fi.path();
	if (path.endsWith("/")) path=path.left(path.length()-1);
	QStringList basedirs = basepath.split("/");
    if(baseFile && !basedirs.isEmpty()) basedirs.removeLast();
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
	
    if(keepSuffix)
        return path+filename;
    return path+fi.completeBaseName();
}

QString getPathfromFilename(const QString &compFile){
	if (compFile.isEmpty()) return "";
	QString dir=QFileInfo(compFile).absolutePath();
	if (!dir.endsWith("/") && !dir.endsWith(QDir::separator())) dir.append(QDir::separator());
	return dir;
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



// convenience function for unique connections independent of the Qt version
bool connectUnique(const QObject * sender, const char * signal, const QObject * receiver, const char * method) {
#if QT_VERSION >= 0x040600
	return QObject::connect(sender, signal, receiver, method, Qt::UniqueConnection);
#else
	disconnect(sender, signal, receiver, method);
	return connect(sender, signal, receiver, method);
#endif
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
		char prev=str[0];
		int good=0;int bad=0;
		int utf16le=0, utf16be = 0;
		for (int i=1;i<size;i++) {
			char cur = str[i];
			if ((cur & 0xC0) == 0x80) {
				if ((prev & 0xC0) == 0xC0) good++;
				else if ((prev & 0x80) == 0x00) bad++;
			} else {
				if ((prev & 0xC0) == 0xC0) bad++;
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
			if (utf16be <= size / 1000 && utf16le >= size / 100 && utf16le >= 2) guess = QTextCodec::codecForName("UTF-16LE");
		} else {
			if (utf16le <= size / 1000 && utf16be >= size / 100 && utf16be >= 2) guess = QTextCodec::codecForName("UTF-16BE");
		}
		if (!guess){
			if (good > 10*bad) guess = QTextCodec::codecForName("UTF-8");
			else {
				guess = QTextCodec::codecForName("ISO-8859-1");
				if (bad == 0) sure = 0;
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
		switch (word.at(0).toAscii()) {
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
        QRegExp rxCom("^(\\\\\\w+\\*?)(\\[.+\\])*\\{(.*)\\}");
        QRegExp rxCom2("^(\\\\\\w+\\*?)\\[(.+)\\]");
		rxCom.setMinimal(true);
		QStringList keywords;
		keywords << "text" << "title";
		while (!tagsfile.atEnd()) {
			line = tagsfile.readLine().trimmed();
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


void ThreadBreaker::sleep(int s){
	QThread::sleep(s);
}

void ThreadBreaker::msleep(unsigned long ms)
{
	QThread::msleep(ms);
};

void ThreadBreaker::forceTerminate(QThread* t){
	if (!t) t = QThread::currentThread();
	t->setTerminationEnabled(true);
	t->terminate();
}

SafeThread::SafeThread():QThread(0),crashed(false){}
SafeThread::SafeThread(QObject* parent):QThread(parent), crashed(false){}

void SafeThread::wait(unsigned long time){
	if (crashed) return;
	QThread::wait(time);
}

QString getImageAsText(const QPixmap &AImage) {
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    AImage.save(&buffer, "PNG");
    return QString("<img src=\"data:image/png;base64,%1\">").arg(QString(buffer.data().toBase64()));
}
