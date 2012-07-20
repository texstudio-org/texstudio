#include "buildmanager.h"

#include "smallUsefulFunctions.h"
#include "configmanagerinterface.h"

#include "userquickdialog.h"

#ifdef Q_WS_WIN
#include "windows.h"
#endif

#ifdef Q_WS_WIN
#define ON_WIN(x) x
#define ON_NIX(x)
#else
#define ON_WIN(x) 
#define ON_NIX(x) x
#endif

static const QString DEPRECACTED_TMX_INTERNAL_PDF_VIEWER = "tmx://internal-pdf-viewer";

const QString BuildManager::TXS_CMD_PREFIX = "txs:///";

int BuildManager::autoRerunLatex = 5;
QString BuildManager::autoRerunCommands;

#define CMD_DEFINE(up, id) const QString BuildManager::CMD_##up = BuildManager::TXS_CMD_PREFIX + #id;
CMD_DEFINE(LATEX, latex) CMD_DEFINE(PDFLATEX, pdflatex) CMD_DEFINE(XELATEX, xelatex) CMD_DEFINE(LUALATEX, lualatex) CMD_DEFINE(LATEXMK, latexmk)
CMD_DEFINE(VIEW_DVI, view-dvi) CMD_DEFINE(VIEW_PS, view-ps) CMD_DEFINE(VIEW_PDF, view-pdf) CMD_DEFINE(VIEW_LOG, view-log)
CMD_DEFINE(DVIPNG, dvipng) CMD_DEFINE(DVIPS, dvips) CMD_DEFINE(DVIPDF, dvipdf) CMD_DEFINE(PS2PDF, ps2pdf) CMD_DEFINE(GS, gs) CMD_DEFINE(MAKEINDEX, makeindex) CMD_DEFINE(TEXINDY, texindy) CMD_DEFINE(METAPOST, metapost) CMD_DEFINE(ASY, asy) CMD_DEFINE(BIBTEX, bibtex) CMD_DEFINE(SVN, svn) CMD_DEFINE(SVNADMIN, svnadmin)
CMD_DEFINE(COMPILE, compile) CMD_DEFINE(VIEW, view) CMD_DEFINE(BIBLIOGRAPHY, bibliography) CMD_DEFINE(INDEX, index) CMD_DEFINE(QUICK, quick) CMD_DEFINE(RECOMPILE_BIBLIOGRAPHY, recompile-bibliography)
CMD_DEFINE(VIEW_PDF_INTERNAL, view-pdf-internal) CMD_DEFINE(CONDITIONALLY_RECOMPILE_BIBLIOGRAPHY, conditionally-recompile-bibliography)
CMD_DEFINE(INTERNAL_PRE_COMPILE, internal-pre-compile)
#undef CMD_DEFINE

QString searchBaseCommand(const QString &cmd, QString options);
QString getCommandLineViewDvi();
QString getCommandLineViewPs();
QString getCommandLineViewPdfExternal();
QString getCommandLineGhostscript();

CommandInfo::CommandInfo(): user(false), meta(false), rerunCompiler(false), guessFunc(0){}

QString CommandInfo::guessCommandLine() const{
	if (guessFunc) {
		QString temp = (*guessFunc)();
		if (!temp.isEmpty()) return temp;
	}
	
	if (!baseName.isEmpty()){
		//search it
		QString bestCommand = searchBaseCommand(baseName, defaultArgs);
		if (!bestCommand.isEmpty()) return bestCommand; 
	}
	
	if (metaSuggestionList.size() > 0)
		return metaSuggestionList.first();
	
	return "";
}

void CommandInfo::setCommandLine(const QString& cmdString){
	if (cmdString=="<default>") commandLine = guessCommandLine();
	if (cmdString==BuildManager::tr("<unknown>")) commandLine = "";
	else {
		//force commands to include options (e.g. file name)
		QString trimmed = cmdString.trimmed();
		QString unquote = trimmed;
		if (trimmed.startsWith('"') && trimmed.endsWith('"')) unquote = trimmed.mid(1,trimmed.length()-2);
		if (baseName != "" &&
		              ((unquote == baseName) ||
		               (   (unquote.endsWith(QDir::separator() + baseName) || unquote.endsWith("/" + baseName))
		                   && (!unquote.contains(" ") || (!unquote.contains('"') && unquote != trimmed)) //spaces mean options, if not everything is quoted
		                   && (QFileInfo(unquote).exists())		      
		                   )
		               ))
			commandLine = cmdString + " " + defaultArgs;
		else
			commandLine = cmdString;
	}
}

QString CommandInfo::getPrettyCommand() const{
	if (commandLine.isEmpty() && metaSuggestionList.isEmpty()) return BuildManager::tr("<unknown>");
	else return commandLine;
}

QString CommandInfo::getProgramName(const QString& commandLine){
	QString cmdStr = commandLine.trimmed();
	int p=-1;
	if (cmdStr.startsWith('"')) p = cmdStr.indexOf('"',1)+1;
	else if (cmdStr.contains(' ')) p = cmdStr.indexOf(' ');
	if (p==-1) p = cmdStr.length(); //indexOf failed if it returns -1
	return cmdStr.mid(0, p);
}

QString CommandInfo::getProgramName() const{
	return getProgramName(commandLine);
}

ExpandingOptions::ExpandingOptions(const QFileInfo &mainFile, const QFileInfo &currentFile, const int currentLine): mainFile(mainFile), currentFile(currentFile), currentLine(currentLine), nestingDeep(0), canceled(false){
	override.removeAll = false;
}

/*
QString BuildManager::getLatexCommandExecutable(LatexCommand cmd){
 QString cmdStr = getLatexCommand(cmd).trimmed();
 int p=-1;
 if (cmdStr.startsWith('"')) p = cmdStr.indexOf('"',1)+1;
 else if (cmdStr.contains(' ')) p = cmdStr.indexOf(' ')+1;
 if (p==-1) p = cmdStr.length(); //indexOf failed if it returns -1
 return cmdStr.mid(0, p);
}*/

CommandToRun::CommandToRun(){}
CommandToRun::CommandToRun(const QString& cmd): command(cmd){}

QString BuildManager::chainCommands(const QString& a){ return a; }
QString BuildManager::chainCommands(const QString& a, const QString& b) { return a + "|" + b; }
QString BuildManager::chainCommands(const QString& a, const QString& b, const QString& c) { return a + "|" + b + "|" + c; }
QString BuildManager::chainCommands(const QString& a, const QString& b, const QString& c, const QString& d)  { return a + "|" + b + "|" + c + "|" + d;  }



BuildManager::BuildManager(): processWaitedFor(0)
     #ifdef Q_WS_WIN
     , pidInst(0)
     #endif
{
	initDefaultCommandNames();
	connect(this, SIGNAL(commandLineRequested(QString,QString*,bool*)), SLOT(commandLineRequestedDefault(QString,QString*,bool*)));
}
BuildManager::~BuildManager() {
	//remove preview file names
	foreach(const QString& elem,previewFileNames)
		removePreviewFiles(elem);
#ifdef Q_WS_WIN
	if (pidInst) DdeUninitialize(pidInst);
#endif
}

void BuildManager::initDefaultCommandNames(){
	REQUIRE (commands.isEmpty());
	
	//id, platform-independent command, display name, command line
	registerCommand("latex",       "latex",        "LaTeX",       "-src -interaction=nonstopmode %.tex", "Tools/Latex");
	registerCommand("pdflatex",    "pdflatex",     "PdfLaTeX",    "-synctex=1 -interaction=nonstopmode %.tex", "Tools/Pdflatex");
	registerCommand("xelatex",     "xelatex",      "XeLaTeX",     "-synctex=1 -interaction=nonstopmode %.tex", "");
	registerCommand("lualatex",    "lualatex",     "LuaLaTeX",    "-synctex=1 -interaction=nonstopmode %.tex", "");
	registerCommand("view-dvi",    "",             tr("DVI Viewer"), "%.dvi", "Tools/Dvi", &getCommandLineViewDvi);
	registerCommand("view-ps",     "",             tr("PS Viewer"), "%.ps", "Tools/Ps", &getCommandLineViewPs);
	registerCommand("view-pdf-external","",        tr("External PDF Viewer"), "%.pdf", "Tools/Pdf", &getCommandLineViewPdfExternal);
	registerCommand("dvips",       "dvips",        "DviPs",       "-o %.ps %.dvi", "Tools/Dvips");
	registerCommand("dvipng",      "dvipng",       "DviPng",      "-T tight -D 120 %.dvi", "Tools/Dvipng");
	registerCommand("ps2pdf",      "ps2pdf",       "Ps2Pdf",      "%.ps", "Tools/Ps2pdf");
	registerCommand("dvipdf",      "dvipdf;dvipdfm",       "DviPdf",      "%.dvi", "Tools/Dvipdf");
	registerCommand("bibtex",      "bibtex",       "BibTeX",       ON_WIN("%") ON_NIX("%.aux"),  "Tools/Bibtex"); //miktex bibtex will stop (appears like crash in txs) if .aux is attached
	registerCommand("bibtex8",     "bibtex8",      "BibTeX 8-Bit", ON_WIN("%") ON_NIX("%.aux")); 
	registerCommand("biber",       "biber",        "biber" ,       "%"); //todo: correct parameter?
	registerCommand("makeindex",   "makeindex",    "Makeindex",   "%.idx", "Tools/Makeindex");
	registerCommand("texindy",     "texindy",      "Texindy", "");
	registerCommand("makeglossary","makeglossary;makeglossaries", "Makeglossary", "");
	registerCommand("metapost",    "mpost",        "Metapost",    "-interaction=nonstopmode ?me)", "Tools/Metapost");
	registerCommand("asy",         "asy",          "Asymptote",   "?m*.asy", "Tools/Asy");
	registerCommand("gs",          "gs;mgs",           "Ghostscript", "\"?am.ps\"", "Tools/Ghostscript", &getCommandLineGhostscript);
	QStringList ltxmk_cmds;
	ltxmk_cmds << "latexmk -pdf -silent -pdflatex=\"pdflatex -synctex=1 %%O %%S\" %" << "latexmk -dvi -silent -latex=\"latex -src %%O %%S\" %";
	registerCommand("latexmk",     "Latexmk", ltxmk_cmds,"",false);
	
	
	QStringList descriptionList;
	descriptionList << tr("compile & view") << tr("Postscipt chain") << tr("DVI chain") << tr("PDF chain") << tr("DVI-PDF-chain") << tr("DVI-PS-PDF-chain") << tr("asy-DVI-chain") << tr("asy-PDF-chain");
	registerCommand("quick", tr("Quickbuild"), QStringList() << "txs:///compile | txs:///view" << "txs:///ps-chain" << "txs:///dvi-chain" << "txs:///pdf-chain" << "txs:///dvi-pdf-chain" << "txs:///dvi-ps-pdf-chain" << "txs:///asy-dvi-chain" << "txs:///asy-pdf-chain" /* too long breaks design<< "latex -interaction=nonstopmode %.tex|bibtex %.aux|latex -interaction=nonstopmode %.tex|latex -interaction=nonstopmode %.tex| txs:///view-dvi"*/, "Tools/Userquick",true,descriptionList);
	
	descriptionList.clear();
	descriptionList<< tr("Use pdflatex") << tr("Use latex") << tr("Use xelatex") << tr("Use lualatex") << tr("Use latexmk");
	registerCommand("compile", tr("Default Compiler"), QStringList() << "txs:///pdflatex" << "txs:///latex" << "txs:///xelatex" << "txs://lualatex" << "txs:///latexmk","",true,descriptionList);
	descriptionList.clear();
	descriptionList<<tr("Use PDF viewer") << tr("Use DVI viewer") << tr("Use postscript viewer") << tr("Use internal PDF viewer") << tr("Use internal PDF viewer embedded in TeXstudio") << tr("Use external PDF viewer");
	registerCommand("view", tr("Default Viewer"), QStringList() << "txs:///view-pdf" << "txs:///view-dvi" << "txs:///view-ps" << "txs:///view-pdf-internal" << "txs:///view-pdf-internal --embedded" << "txs:///view-pdf-external","",true,descriptionList);
	descriptionList.clear();
	descriptionList<< tr("Use internal PDF viewer") << tr("Use internal PDF viewer embedded in TeXstudio")  << tr("Use external PDF viewer");
	registerCommand("view-pdf", tr("PDF Viewer"), QStringList() << "txs:///view-pdf-internal" << "txs:///view-pdf-internal --embedded" << "txs:///view-pdf-external","",true,descriptionList);
	descriptionList.clear();
	descriptionList<< tr("Use bibtex") << tr("Use bibtex8") << tr("Use biber");
	registerCommand("bibliography", tr("Default Bibliography"), QStringList() << "txs:///bibtex" << "txs:///bibtex8" << "txs:///biber","",true,descriptionList);
	descriptionList.clear();
	descriptionList<< tr("Use bibtex") << tr("Use bibtex8") << tr("Use biber");
	registerCommand("index", tr("Default Index Tool"), QStringList() << "txs:///makeindex" << "txs:///texindy","",true,descriptionList);
	
	registerCommand("ps-chain", tr("PS Chain"), QStringList() << "txs:///latex | txs:///dvips | txs:///view-ps");
	registerCommand("dvi-chain", tr("DVI Chain"), QStringList() << "txs:///latex | txs:///view-dvi");
	registerCommand("pdf-chain", tr("PDF Chain"), QStringList() << "txs:///pdflatex | txs:///view-pdf");
	registerCommand("dvi-pdf-chain", tr("DVI->PDF Chain"), QStringList() << "txs:///latex | txs:///dvipdf | txs:///view-pdf");
	registerCommand("dvi-ps-pdf-chain", tr("DVI->PS->PDF Chain"), QStringList() << "txs:///latex | txs:///dvips | txs:///ps2pdf | txs:///view-pdf");
	registerCommand("asy-dvi-chain", tr("Asymptote DVI Chain"), QStringList() << "txs:///latex | txs:///asy | txs:///latex | txs:///view-dvi");
	registerCommand("asy-pdf-chain", tr("Asymptote PDF Chain"), QStringList() << "txs:///pdflatex | txs:///asy | txs:///pdflatex | txs:///view-pdf");
	
	registerCommand("pre-compile", tr("Precompile"), QStringList() << "", "Tools/Precompile");
	registerCommand("internal-pre-compile", tr("Internal Precompile"), QStringList() << "txs:///pre-compile | txs:///conditionally-recompile-bibliography");
	registerCommand("recompile-bibliography", tr("Recompile Bibliography"), QStringList() << "txs:///compile | txs:///bibliography | txs:///compile");
	
	
	registerCommand("svn",         "svn",          "SVN",         "", "Tools/SVN");
	registerCommand("svnadmin",    "svnadmin",     "SVNADMIN",    "", "Tools/SVNADMIN");
	
	internalCommands << CMD_VIEW_PDF_INTERNAL << CMD_CONDITIONALLY_RECOMPILE_BIBLIOGRAPHY << CMD_VIEW_LOG;
}

CommandInfo& BuildManager::registerCommand(const QString& id, const QString& basename, const QString& displayName, const QString& args, const QString& oldConfig, const GuessCommandLineFunc guessFunc, bool user ){
	CommandInfo ci;
	ci.id = id;
	ci.baseName = basename;
	ci.displayName = displayName;
	ci.defaultArgs = args;
	ci.deprecatedConfigName = oldConfig;
	ci.guessFunc = guessFunc;
	ci.user = user;
	if (!user) commandSortingsOrder << id;
	return commands.insert(id, ci).value();
}

CommandInfo& BuildManager::registerCommand(const QString& id, const QString& displayname, const QStringList& alternatives, const QString& oldConfig, const bool metaCommand, const QStringList simpleDescriptions){
	CommandInfo ci;
	ci.id = id;
	ci.displayName = displayname;
	ci.metaSuggestionList = alternatives;
	ci.simpleDescriptionList=simpleDescriptions;
	ci.meta=metaCommand;
	ci.deprecatedConfigName = oldConfig;
	commandSortingsOrder << id;
	return commands.insert(id, ci).value();
}
QString BuildManager::getCommandLine(const QString& id, bool* user){
	QString result;
	emit commandLineRequested(id.trimmed(), &result, user);
	return result;
}

QStringList BuildManager::parseExtendedCommandLine(QString str, const QFileInfo &mainFile, const QFileInfo &currentFile, int currentline) {
	str=str+" "; //end character  so str[i++] is always defined
	QStringList result; result.append("");
	for (int i=0; i<str.size(); i++) {
		QString add;
		if (str.at(i)==QChar('%')) {
			if (str.at(i+1)==QChar('%')) add=str.at(++i);
			else add="\""+mainFile.completeBaseName()+"\"";
		} else if (str.at(i)==QChar('@')) {
			if (str.at(i+1)==QChar('@')) add=str.at(++i);
			else add=QString::number(currentline);
		} else if (str.at(i)==QChar('?')) {
			if (str.at(++i)==QChar('?')) add="?";
			else {
				QString command, commandRem;
				QString* createCommand = &command;
				int endMode=0;
				bool fullSearch = false;
				while (i<str.size()) {
					if (str.at(i)==QChar(')')) {
						endMode=1;
						break;
					} else if (str.at(i)==QChar(' ')||str.at(i)==QChar('\t')) {
						endMode=2;
						break;
					} else if (str.at(i)==QChar('\"')) {
						endMode=3;
						break;
					} else if (str.at(i)==QChar('.') && !fullSearch) {
						endMode=4;
						break;
					} else if (str.at(i)==QChar('*')) {
						fullSearch = true;
						createCommand = &commandRem;
					}
					(*createCommand)+=str.at(i);
					i++;
				}
				bool useCurrentFile=command.startsWith("c:");
				const QFileInfo& selectedFile=(useCurrentFile && !currentFile.fileName().isEmpty())?currentFile:mainFile;
				if (useCurrentFile) command=command.mid(2);
				bool absPath = command.startsWith('a');
				//check only sane commands
				if (command=="ame") command=QDir::toNativeSeparators(selectedFile.absoluteFilePath());
				else if (command=="am") {
					command=QDir::toNativeSeparators(selectedFile.absoluteFilePath());
					if (selectedFile.suffix()!="") command.chop(1+selectedFile.suffix().length());
				} else if (command=="a") {
					command=QDir::toNativeSeparators(selectedFile.absolutePath());
					if (!command.endsWith(QDir::separator())) command+=QDir::separator();
				} else if (command=="me") command=selectedFile.fileName();
				else if (command=="m") command=selectedFile.completeBaseName();
				else if (command=="e") command=selectedFile.suffix();
				else continue; //invalid command
				//TODO: relative paths rme, rm, re
				command.append(commandRem);
				switch (endMode) {
				case 2:
					command+=" ";
					break;
				case 3:
					command="\""+command+"\"";
					break;
				case 4:
					command+=".";
					break;
				default:
					;
				}
				if (!fullSearch) add = command;
				else {
					QDir dir(QFileInfo(mainFile).absoluteDir());
					if (command.contains("/")) command = command.mid(command.lastIndexOf("/")+1);
					QStringList commands = QDir(dir).entryList(QStringList() << command.trimmed(), QDir::Files);
					QString mid;
					if (absPath) {
						mid = dir.canonicalPath();
						if (!mid.endsWith('/')) mid+="/";
					}
					QStringList temp = result;
					result.clear();
					for (int i=0;i<temp.size();i++)
						for (int j=0;j<commands.size();j++)
							result.append(temp[i]+mid+commands[j]);
				}
			}
		} else add=str.at(i);
		if (!add.isEmpty())
			for (int i=0;i<result.size();i++)
				result[i] += add;
	}
	//  QMessageBox::information(0,"",str+"->"+result,0);
	for (int i=0;i<result.size();i++) result[i] = result[i].trimmed(); //remove useless characters
	return result;
}



QString BuildManager::findFileInPath(QString fileName) {
/*#ifdef Q_WS_MAC
	QProcess *myProcess = new QProcess();
	myProcess->start("bash -l -c \"echo $PATH\"");
	myProcess->waitForFinished(3000);
	if(myProcess->exitStatus()==QProcess::CrashExit) return "";
	QByteArray res=myProcess->readAllStandardOutput();
	delete myProcess;
	QString path(res);
#else*/
	QStringList env= QProcess::systemEnvironment();    //QMessageBox::information(0,env.join("  \n"),env.join("  \n"),0);
	int i=env.indexOf(QRegExp("^PATH=.*", Qt::CaseInsensitive));
	if (i==-1) return "";
	QString path=env[i].mid(5); //skip path=
//#endif
#ifdef Q_WS_WIN
	if (!fileName.contains('.')) fileName+=".exe";
	QStringList paths=path.split(";"); //windows
#else
	QStringList paths=path.split(":"); //linux
#endif
	foreach(const QString& p, paths)
		if (p.endsWith("/") && QFileInfo(p+fileName).exists()) return (p+fileName);
		else if (p.endsWith("\\") && QFileInfo(p+fileName).exists()) return (p+fileName);
		else if (QFileInfo(p+"/"+fileName).exists()) return (p+"\\"+fileName);
	return "";
}

#ifdef Q_WS_WIN
typedef BOOL (* AssocQueryStringAFunc)(DWORD, DWORD, const char*, const char*, char*, DWORD*);
QString W32_FileAssociation(QString ext) {
	if (ext=="") return "";
	if (ext[0]!=QChar('.')) ext='.'+ext;
	QString result="";
	QByteArray ba=ext.toLocal8Bit();
	HMODULE mod = LoadLibraryA("shlwapi.dll");
	AssocQueryStringAFunc assoc=(AssocQueryStringAFunc)(GetProcAddress(mod,"AssocQueryStringA"));
	if (assoc) {
		const DWORD ASSOCSTR_COMMAND = 1;
		char buf[1024];
		DWORD buflen=1023;
		if (assoc(0, ASSOCSTR_COMMAND, ba.data(), "open", &buf[0], &buflen)==S_OK) {
			buf[buflen]=0;
			result=QString::fromAscii(buf);
			result.replace("%1","?am"+ext);
			//QMessageBox::information(0,result,result,0);
		};
	}
	FreeLibrary(mod);
	return result;
}
QString addPathDelimeter(const QString& a){
	return ((a.endsWith("/") || a.endsWith("\\"))?a:(a+"\\"));
}
QStringList getProgramFilesPaths(){
	QStringList res;
	QString a=getenv("PROGRAMFILES");
	if (!a.isEmpty()) res << addPathDelimeter(a);
	a=getenv("PROGRAMFILES(X86)");
	if (!a.isEmpty()) res << addPathDelimeter(a);
	if (a != "C:/Program Files" && QDir("C:/Program Files").exists()) res << "C:/Program Files/";
	if (a != "C:/Program Files (x86)" && QDir("C:/Program Files (x86)").exists()) res << "C:/Program Files (x86)/";
	if (a + " (x86)" != "C:/Program Files (x86)" && QDir(a+" (x86)").exists()) res << (a+" (x86)");
	return res;
}
static QString miktexpath = "<search>";
QString getMiKTeXBinPathReal() {
	QSettings reg("HKEY_CURRENT_USER\\Software", QSettings::NativeFormat);
	QString mikPath = reg.value("MiK/MikTeX/CurrentVersion/MiKTeX/Install Root", "").toString();
	if (!mikPath.isEmpty())
		return addPathDelimeter(mikPath)+"miktex\\bin\\";
	foreach (const QString& d, getProgramFilesPaths())
		foreach (const QString& p, QDir(d).entryList(QStringList(), QDir::AllDirs, QDir::Time))
			if (p.toLower().contains("miktex") && QDir(d+addPathDelimeter(p)+"miktex\\bin\\").exists())
				return d+addPathDelimeter(p)+"miktex\\bin\\";
	static const QStringList candidates = QStringList() << "C:\\miktex\\miktex\\bin" << "C:\\tex\\texmf\\miktex\\bin" << "C:\\miktex\\bin";
	foreach (const QString& d, candidates)
		if (QDir(d).exists())
			return d + "\\";
	return "";
}
QString getMiKTeXBinPath() {
	if (miktexpath == "<search>") miktexpath = getMiKTeXBinPathReal();
	return miktexpath;
}
QString getTeXLiveBinPath() {
	//check for uninstall entry
	foreach (const QString& baseKey, QStringList() << "HKEY_CURRENT_USER" << "HKEY_LOCAL_MACHINE") {
		QSettings reg(baseKey+ "\\Software", QSettings::NativeFormat);
		QString uninstall = reg.value("microsoft/windows/currentversion/uninstall/TeXLive2010/UninstallString", "").toString();
		if (uninstall.isEmpty()) uninstall = reg.value("microsoft/windows/currentversion/uninstall/TeXLive2009/UninstallString", "").toString();
		if (uninstall.isEmpty()) uninstall = reg.value("microsoft/windows/currentversion/uninstall/TeXLive2008/UninstallString", "").toString();
		if (!uninstall.isEmpty()) {
			int p = uninstall.indexOf("\\tlpkg\\", 0, Qt::CaseInsensitive);
			QString path = p>0?uninstall.left(p):"";
			if (QDir(path+"\\bin\\win32").exists())
				return path+"\\bin\\win32\\";
		}
	}
	//check for path
	QString pdftex = BuildManager::findFileInPath("pdftex.exe");
	int p = pdftex.indexOf("\\bin\\", 0, Qt::CaseInsensitive);
	if (p<=0) return "";
	QString path = pdftex.left(p);
	if (!QFileInfo(path+"\\release-texlive.txt").exists()) return "";
	return path+"\\bin\\win32\\";
}
QString findGhostscriptDLL() { //called dll, may also find an exe
	//registry
	for (int type=0; type<=1; type++)
		for (int pos=0; pos<=1; pos++) {
			QString regBase=QString(pos==0?"HKEY_CURRENT_USER":"HKEY_LOCAL_MACHINE")+"\\Software\\"+QString(type==0?"GPL":"AFPL")+" Ghostscript";
			QSettings reg(regBase, QSettings::NativeFormat);
			QStringList version=reg.childGroups();
			if (version.empty()) continue;
			version.sort();
			for (int i=version.size()-1; i>=0; i--) {
				QString dll=reg.value(version[i]+"/GS_DLL","").toString();
				if (!dll.isEmpty()) return dll;
			}
		}
	//environment
	QStringList env= QProcess::systemEnvironment();    //QMessageBox::information(0,env.join("  \n"),env.join("  \n"),0);
	int i=env.indexOf(QRegExp("^GS_DLL=.*", Qt::CaseInsensitive));
	if (i>-1)
		return env[i].mid(7); //skip gs_dll=
	//file search
	foreach (const QString& p, getProgramFilesPaths())
		if (QDir(p+"gs").exists())
			foreach (const QString& gsv, QDir(p+"gs").entryList(QStringList() << "gs*.*", QDir::Dirs, QDir::Time)){
				QString x = p+"gs/"+gsv+"/bin/gswin32c.exe";
				if (QFile::exists(x)) return x;
			}
	return "";
}
#endif

QString searchBaseCommand(const QString &cmd, QString options) {
	foreach(QString command,cmd.split(";")){
		QString fileName=command   ON_WIN(+ ".exe");
		if (!options.startsWith(" ")) options=" "+options;
		if (!BuildManager::findFileInPath(fileName).isEmpty())
			return fileName+options; //found in path
		else {
			//platform dependent mess
#ifdef Q_WS_WIN
			//Windows MikTex
			QString mikPath=getMiKTeXBinPath();
			if (!mikPath.isEmpty() && QFileInfo(mikPath+fileName).exists())
				return "\""+mikPath+fileName+"\" "+options; //found
			//Windows TeX Live
			QString livePath=getTeXLiveBinPath();
			if (!livePath.isEmpty() && QFileInfo(livePath+fileName).exists())
				return "\""+livePath+fileName+"\" "+options; //found
#endif
#ifdef Q_WS_MACX
			QStringList paths;
			paths << "/usr/bin/texbin/" << "/usr/local/bin/" << "/usr/texbin/";
			paths << "/usr/local/teTeX/bin/i386-apple-darwin-current/" << "/usr/local/teTeX/bin/powerpc-apple-darwin-current/" << "/usr/local/teTeX/bin/x86_64-apple-darwin-current/";
			
			for (int i=2012; i>=2007; i--) {
				//paths << QString("/usr/texbin MACTEX/TEXLIVE%i").arg(i); from texmaker comment
				paths << QString("/usr/local/texlive/%i/bin/x86_64-darwin/").arg(i);
				paths << QString("/usr/local/texlive/%i/bin/i386-darwin/").arg(i);
				paths << QString("/usr/local/texlive/%i/bin/powerpc-darwin/").arg(i);
			}
			foreach (const QString& p, paths)
				if (QFileInfo(p+fileName).exists())
					return p+fileName+options;
#endif
		}
	}
	return "";
}

ExpandedCommands BuildManager::expandCommandLine(const QString& str, ExpandingOptions& options){
	QRegExp re(QRegExp::escape(TXS_CMD_PREFIX) + "([^/ [{]+)(/?)((\\[[^\\]*]+\\]|\\{[^}]*\\})*) ?(.*)");
	
	options.nestingDeep++;
	if (options.canceled) return ExpandedCommands();
	if (options.nestingDeep > maxExpandingNestingDeep) {
		if (!txsConfirmWarning(tr("The command has been expanded to %1 levels. Do you want to continue expanding \"%2\"?").arg(options.nestingDeep).arg(str))){
			options.canceled = true;
			return ExpandedCommands();
		}
	}
	
	ExpandedCommands res;
	QStringList splitted = str.split("|");
	foreach (const QString& split, splitted) { //todo: ignore | in strings
		QString subcmd = split.trimmed();
		
		if (!subcmd.startsWith(TXS_CMD_PREFIX))  {
			RunCommandFlags  flags = getSingleCommandFlags(subcmd);
			
			if (options.override.removeAll)
				subcmd = CommandInfo::getProgramName(subcmd);
			if (!options.override.append.isEmpty())
				subcmd += " " + options.override.append.join(" "); //todo: simplify spaces???
			//Regexp matching parameters
			//Unescaped: .*(-abc(=([^ ]*|"([^"]|\"([^"])*\")*"))?).*
			//Doesn't support nesting deeper than \"
			static QString parameterMatching = "(=([^ ]*|\"([^\"]|\\\"([^\"])*\\\")*\"))?";   
			for (int i=0;i<options.override.remove.size();i++){
				const QString& rem = options.override.remove[i];
				QRegExp removalRegex(" (-?" + QRegExp::escape(rem)+(rem.contains("=")?"":parameterMatching)+")");
				subcmd.replace(removalRegex, " ");
			}
			for (int i=0;i<options.override.replace.size();i++){
				const QString& rem = options.override.replace[i].first;
				QRegExp replaceRegex(" (-?" + QRegExp::escape(rem)+parameterMatching+")");
				int pos = replaceRegex.indexIn(subcmd);
				QString rep = " " + rem+options.override.replace[i].second;
				if (pos < 0) subcmd.insert(CommandInfo::getProgramName(subcmd).length(), rep);
				else {
					subcmd.replace(pos, replaceRegex.matchedLength(), rep);
					pos += rep.length();
					int newpos;
					while ( (newpos = replaceRegex.indexIn(subcmd, pos)) >= 0)
						subcmd.replace(newpos, replaceRegex.matchedLength(), " ");
				}
			}
			
			foreach (const QString& c, parseExtendedCommandLine(subcmd, options.mainFile, options.currentFile, options.currentLine)) {
				CommandToRun temp(c);
				temp.flags = flags;
				res.commands << temp;
			}
		} else if (re.exactMatch(subcmd)){	
			const QString& cmdName = re.cap(1);
			const QString& slash = re.cap(2);
			QString modifiers = re.cap(3);
			QString parameters = re.cap(5);
			if (slash != "/" && !modifiers.isEmpty()) { txsInformation(tr("You have used txs:///command[... or txs:///command{... modifiers, but we only support modifiers of the form txs:///command/[... or txs:///command/{... with an slash suffix to keep the syntax purer.")); modifiers.clear(); }
			if (options.override.removeAll) parameters.clear(), modifiers.clear();
			
			bool user;
			QString cmd = getCommandLine(cmdName, &user);
			if (cmd.isEmpty()) { 
				if (options.nestingDeep == 1) txsWarning(tr("Command %1 not defined").arg(subcmd)); 
				else if (cmdName != "pre-compile") qDebug() << tr("Command %1 not defined").arg(subcmd); //pre-compile is expecte
				continue; 
			}
			
			int space = cmd.indexOf(' ');
			if (space == -1) space = cmd.size();
			if (cmd.startsWith(TXS_CMD_PREFIX) && internalCommands.contains(cmd.left(space))) {
				res.commands << CommandToRun(cmd + " " + parameters);
				res.commands.last().parentCommand = res.commands.last().command;
				continue;
			}
			
			//parse command modifiers
			bool removeAllActivated = false;
			int replacePrepended = 0, removePrepended = 0;
			if (!modifiers.isEmpty()) {
				//matching combinations like [-abc][-foo=bar]{-xasa...} 
				QRegExp modifierRegexp("^((\\[([^=\\]]+)(=[^\\]]+)?\\])|(\\{([^}]*)\\}))");
				while (modifierRegexp.indexIn(modifiers) >= 0) {
					if (!modifierRegexp.cap(3).isEmpty()) {
						replacePrepended++;
						options.override.replace.prepend(QPair<QString,QString>(modifierRegexp.cap(3),modifierRegexp.cap(4)));
						//qDebug() << "replace >" << options.override.replace.first().first << "< with >"<<options.override.replace.first().second<<"<";
					} else if (!modifierRegexp.cap(5).isEmpty()){
						if (modifierRegexp.cap(6).isEmpty()) {
							removeAllActivated = true; // qDebug() << "remove all";
						} else {
							removePrepended++;
							options.override.remove.prepend(modifierRegexp.cap(6));
							//qDebug() << "remove >" << options.override.remove.first() << "<";
						}
					}
					modifiers.remove(0, modifierRegexp.matchedLength());
				}
			}
			if (removeAllActivated) options.override.removeAll = true;
			if (!parameters.isEmpty()) options.override.append.prepend(parameters);
			//todo /(masterfile,currentfile) modifier ?
			
			//recurse
			ExpandedCommands ecNew = expandCommandLine(cmd, options);
			QList<CommandToRun>& newPart = ecNew.commands;
			
			//clean up modifiers
			if (removeAllActivated) options.override.removeAll = false;
			if (!parameters.isEmpty()) options.override.append.removeFirst();
			for (;replacePrepended>0;replacePrepended--) options.override.replace.removeFirst();
			for (;removePrepended>0;removePrepended--) options.override.remove.removeFirst();
			
			if (newPart.isEmpty()) continue;
			
			if (commands.value(cmdName).rerunCompiler)
				for (int i=0; i<newPart.size(); i++)
					newPart[i].flags |= RCF_RERUN;
			
			for (int i=0; i<newPart.size(); i++)
				if (newPart[i].parentCommand.isEmpty()) {
					newPart[i].parentCommand = cmdName;
					if (user) newPart[i].flags |= RCF_SHOW_STDOUT;
				}
			
			if (splitted.size() == 1)
				res.primaryCommand = cmdName;
			
			res.commands << newPart;
		} else txsWarning(tr("Failed to understand command %1").arg(subcmd));
	}
	options.nestingDeep--;
	return res;
}

RunCommandFlags BuildManager::getSingleCommandFlags(const QString& subcmd) const{
	int result = 0;
	if (latexCommands.contains(subcmd)) result |= RCF_COMPILES_TEX; 
	if (rerunnableCommands.contains(subcmd)) result |= RCF_RERUNNABLE; 
	if (pdfCommands.contains(subcmd)) result |= RCF_CHANGE_PDF;
	if (stdoutCommands.contains(subcmd)) result |= RCF_SHOW_STDOUT;
	if (viewerCommands.contains(subcmd)) result |= RCF_SINGLE_INSTANCE;
	return (RunCommandFlags)(result);
}

bool BuildManager::hasCommandLine(const QString& program){
	for (CommandMapping::const_iterator it = commands.constBegin(), end = commands.constEnd(); it != end; ++it) 
		if (it.value().commandLine == program) return true;
	return false;
}

#ifdef Q_WS_MACX
QString getCommandLineViewDvi(){ return "open %.dvi > /dev/null"; }
QString getCommandLineViewPs(){ return "open %.ps > /dev/null"; }
QString getCommandLineViewPdfExternal(){ return "open %.pdf > /dev/null"; }
QString getCommandLineGhostscript(){ return ""; }
#endif

#ifdef Q_WS_WIN
QString getCommandLineViewDvi(){ 
	const QString yapOptions = " -1 -s @?\"c:ame \"?am.dvi\"";
	QString def=W32_FileAssociation(".dvi");
	if (!def.isEmpty()) {
		if (def.contains("yap.exe")) {
			def=def.trimmed();
			if (def.endsWith("\"?am.dvi\"")){
				def.replace("\"?am.dvi\"",yapOptions);
			} else if (def.endsWith("?am.dvi")) {
				def.replace("?am.dvi",yapOptions);
			} else if (def.endsWith(" /dde")) {
				def.replace(" /dde",yapOptions);
			}
		}
		return def;
	}
	def=searchBaseCommand("yap",yapOptions);//miktex
	if (!def.isEmpty()) return def;
	def=searchBaseCommand("dviout","%.dvi");//texlive
	if (!def.isEmpty()) return def;
	
	if (QFileInfo("C:/texmf/miktex/bin/yap.exe").exists())
		return "C:/texmf/miktex/bin/yap.exe " + yapOptions;
	
	return "";
}
QString getCommandLineViewPs(){ 
	QString def=W32_FileAssociation(".ps");
	if (!def.isEmpty())
		return def;
	
	QString livePath = getTeXLiveBinPath();
	if (!livePath.isEmpty())
		if (QFileInfo(livePath+"psv.exe").exists())
			return "\""+livePath+"psv.exe\"  \"?am.ps\"";
	
	
	QString gsDll = findGhostscriptDLL().replace("/","\\"); //gsview contains gs so x
	int pos;
	while ((pos=gsDll.lastIndexOf("\\"))>-1) {
		gsDll=gsDll.mid(0,pos+1);
		if (QFileInfo(gsDll+"gsview32.exe").exists())
			return "\""+gsDll+"gsview32.exe\" -e \"?am.ps\"";
		if (QFileInfo(gsDll+"gsview.exe").exists())
			return "\""+gsDll+"gsview.exe\" -e \"?am.ps\"";
		gsDll=gsDll.mid(0,pos);
	}
	
	foreach (const QString& p, getProgramFilesPaths())
		if (QFile::exists(p+"Ghostgum/gsview/gsview32.exe"))
			return "\""+p+"Ghostgum/gsview/gsview32.exe\" -e \"?am.ps\"";
	return "";
}
QString getCommandLineViewPdfExternal(){
	QString def=W32_FileAssociation(".pdf");
	if (!def.isEmpty())
		return def;
	
	foreach (const QString& p, getProgramFilesPaths())
		if (QDir(p+"Adobe").exists())
			foreach (const QString& rv, QDir(p+"Adobe").entryList(QStringList() << "Reader*", QDir::Dirs, QDir::Time)){
				QString x = p+"Adobe/"+rv+"/Reader/AcroRd32.exe";
				if (QFile::exists(x)) return "\""+x+"\" \"?am.pdf\"";
			}
	return "";
}
QString getCommandLineGhostscript(){
	QString livePath = getTeXLiveBinPath();
	if (!livePath.isEmpty()){
		if (QFileInfo(livePath+"rungs.exe").exists())
			return "\""+livePath+"rungs.exe\"";
		if (QFileInfo(livePath+"rungs.bat").exists()) //tl 2008 (?)
			return "\""+livePath+"rungs.bat\"";
	}
	QString dll=findGhostscriptDLL().replace("gsdll32.dll","gswin32c.exe",Qt::CaseInsensitive);
	if (dll.endsWith("gswin32c.exe")) return "\""+dll+"\"";
	else if (QFileInfo("C:/Program Files/gs/gs8.64/bin/gswin32c.exe").exists())  //old behaviour
		return "\"C:/Program Files/gs/gs8.64/bin/gswin32c.exe\"";
	else if (QFileInfo("C:/Program Files/gs/gs8.63/bin/gswin32c.exe").exists())  //old behaviour
		return "\"C:/Program Files/gs/gs8.63/bin/gswin32c.exe\"";
	else if (QFileInfo("C:/Program Files/gs/gs8.61/bin/gswin32c.exe").exists())
		return "\"C:/Program Files/gs/gs8.61/bin/gswin32c.exe\"";
	return "";
}
#endif

#ifdef Q_WS_X11
// xdvi %.dvi  -sourceposition @:%.tex
// kdvi "file:%.dvi#src:@ %.tex"
QString getCommandLineViewDvi(){
	switch (x11desktop_env()) {
	case 3:	return "kdvi %.dvi > /dev/null";
	case 4:	return "okular %.dvi > /dev/null";
	default:return "evince %.dvi > /dev/null";
	}
};
QString getCommandLineViewPs(){
	switch (x11desktop_env()) {
	case 3:  return "kghostview %.ps > /dev/null";
	case 4:  return "okular %.ps > /dev/null";
	default: return "evince %.ps > /dev/null";
	};
}
QString getCommandLineViewPdfExternal(){
	switch (x11desktop_env()) {
	case 3:  return "kpdf %.pdf > /dev/null";
	case 4:  return "okular %.pdf > /dev/null";
	default: return "evince %.pdf > /dev/null";
	};
}
QString getCommandLineGhostscript(){ return ""; }
#endif



void BuildManager::registerOptions(ConfigManagerInterface& cmi){
	cmi.registerOption("Tools/Quick Mode",&deprecatedQuickmode,-1);
	cmi.registerOption("Tools/Max Expanding Nesting Deep", &maxExpandingNestingDeep, 10);
	Q_ASSERT(sizeof(dvi2pngMode) == sizeof(int));
	cmi.registerOption("Tools/Dvi2Png Mode",reinterpret_cast<int*>(&dvi2pngMode), -1);
	cmi.registerOption("Files/Save Files Before Compiling", reinterpret_cast<int*>(&saveFilesBeforeCompiling), (int)SFBC_ONLY_NAMED);
	cmi.registerOption("Preview/Remove Beamer Class", &previewRemoveBeamer, true);
	cmi.registerOption("Preview/Precompile Preamble", &previewPrecompilePreamble, true);
	
	cmi.registerOption("Tools/Automatic Rerun Commands", &autoRerunCommands, "compile|latex|pdflatex|lualatex|xelatex");

	cmi.registerOption("User/ToolNames", &deprecatedUserToolNames, QStringList());
	cmi.registerOption("User/Tools", &deprecatedUserToolCommands, QStringList());
	
	cmi.registerOption("Tools/Display Names", &userToolDisplayNames, QStringList());
	cmi.registerOption("Tools/User Order", &userToolOrder, QStringList());
}
void BuildManager::readSettings(QSettings &settings){
	QStringList rerunCommandsUnexpanded = autoRerunCommands.split("|");
	for (int i=0;i<rerunCommandsUnexpanded.size();i++)
		if (rerunCommandsUnexpanded[i].startsWith(TXS_CMD_PREFIX))
			rerunCommandsUnexpanded[i] = rerunCommandsUnexpanded[i].mid(TXS_CMD_PREFIX.size());

	for (int i=0, end = qMin(userToolOrder.size(), userToolDisplayNames.size());i<end;++i)
		registerCommand(userToolOrder[i], "", userToolDisplayNames[i], "", "", 0, true);
	
	settings.beginGroup("Tools");
	settings.beginGroup("Commands");
	QStringList cmds = settings.childKeys();
	foreach (const QString& id, cmds) {
		QString cmd = settings.value(id).toString();
		if (cmd.isEmpty()) continue;
		CommandMapping::iterator it = commands.find(id);
		if (it == commands.end()) registerCommand(id, "", id, "", "", 0, true).commandLine = cmd;
		else {
			it.value().commandLine = cmd;
			it.value().rerunCompiler = rerunCommandsUnexpanded.contains(id);
		}
	}
	settings.endGroup();
	settings.endGroup();
	
	//import old or choose default
	for (CommandMapping::iterator it = commands.begin(), end = commands.end(); it != end; ++it) {
		CommandInfo &cmd = it.value();
		if (!cmd.commandLine.isEmpty()) continue;
		if (!cmd.deprecatedConfigName.isEmpty()) {
			QString import = settings.value(it.value().deprecatedConfigName).toString();
			if (cmd.id == "quick") {
				if (deprecatedQuickmode == 8) 
					cmd.commandLine = import;
			} else if (cmd.id == "view-pdf-external") {
				if (import.startsWith(DEPRECACTED_TMX_INTERNAL_PDF_VIEWER)) {
					import.remove(0, DEPRECACTED_TMX_INTERNAL_PDF_VIEWER.length()+1);
					cmd.commandLine = import;
					commands.find("view-pdf").value().commandLine = CMD_VIEW_PDF_INTERNAL;
				} else {
					cmd.commandLine = import;
					commands.find("view-pdf").value().commandLine = CMD_VIEW_PDF_INTERNAL;
				}
			} else cmd.commandLine = import;
		}
		if (!cmd.commandLine.isEmpty()) continue;
		if (cmd.id == "quick") {
			if (deprecatedQuickmode >= 1 && deprecatedQuickmode < cmd.metaSuggestionList.size() ) 
				cmd.commandLine = cmd.metaSuggestionList[deprecatedQuickmode];
			continue;
		}
		cmd.commandLine = cmd.guessCommandLine();
	}
	
	if (commands.value("quick").commandLine.isEmpty()) {
		//Choose suggestion that actually exists
		CommandInfo &quick = commands.find("quick").value();
		for (int i=0;i<quick.metaSuggestionList.size()-1;i++) {
			QString referenced = quick.metaSuggestionList[i];
			if (referenced.isEmpty()) continue;
			QStringList subCommands = referenced.split("|");
			bool hasAll = true;
			foreach (const QString& s, subCommands){
				QString trimmed = s.trimmed();
				trimmed.remove(0, TXS_CMD_PREFIX.length());
				if (commands.value(trimmed).commandLine.isEmpty()) {
					hasAll = false;
					break;
				}
			}
			if (hasAll) { quick.commandLine = quick.metaSuggestionList[i]; break; }
		}
		deprecatedQuickmode = -2;
	}
	//import old
	for (int i=0;i<qMin(deprecatedUserToolNames.size(),deprecatedUserToolCommands.size());i++)
		if (!deprecatedUserToolNames[i].endsWith("!!!CONVERTED!!!")){
			QString cmd = deprecatedUserToolCommands[i];
			cmd.replace(DEPRECACTED_TMX_INTERNAL_PDF_VIEWER, CMD_VIEW_PDF_INTERNAL);
			CommandInfo & ci = registerCommand(QString("user%1").arg(i), "", deprecatedUserToolNames[i], "", "", 0, true);
			ci.commandLine = cmd;
			userToolOrder << ci.id;
			userToolDisplayNames << ci.displayName;
			deprecatedUserToolNames[i] = deprecatedUserToolNames[i] + "!!!CONVERTED!!!";
		}
	//import very old
	for (int i=1; i<=5; i++) {
		QString temp = settings.value(QString("User/Tool%1").arg(i),"").toString();
		if (!temp.isEmpty()) {
			temp.replace(DEPRECACTED_TMX_INTERNAL_PDF_VIEWER, CMD_VIEW_PDF_INTERNAL);
			CommandInfo & ci = registerCommand(QString("userold%1").arg(i), "", settings.value(QString("User/ToolName%1").arg(i)).toString(), "", "", 0, true);
			ci.commandLine  = temp;
			userToolOrder << ci.id;
			userToolDisplayNames << ci.displayName;
			settings.remove(QString("User/Tool%1").arg(i));
			settings.remove(QString("User/ToolName%1").arg(i));
		}
	}			
	
	if (reinterpret_cast<int&>(dvi2pngMode)<0) {
		if (isCommandDirectlyDefined(CMD_DVIPNG)) dvi2pngMode = DPM_DVIPNG; //best/fastest mode
		else if (isCommandDirectlyDefined(CMD_DVIPS) && isCommandDirectlyDefined(CMD_GS)) dvi2pngMode = DPM_DVIPS_GHOSTSCRIPT; //compatible mode
		else dvi2pngMode = DPM_DVIPNG; //won't work
	}
	
	setAllCommands(commands, userToolOrder);	
}

void BuildManager::saveSettings(QSettings &settings){
	QStringList order = getCommandsOrder();
	userToolOrder.clear();
	userToolDisplayNames.clear();
	settings.beginGroup("Tools");
	settings.beginGroup("Commands");
	settings.remove("");
	QStringList rerunCmds;
	for (int i=0;i<order.size();i++){
		CommandMapping::iterator it = commands.find(order[i]);
		if (it == commands.end()) continue;
		settings.setValue(it->id, it->commandLine);
		if (it->user) {
			userToolDisplayNames << it->displayName;
			userToolOrder << it->id;
		}
		if (it->rerunCompiler) {
			rerunCmds << it->id;
		}
	}
	autoRerunCommands = rerunCmds.join("|");
	settings.endGroup();
	settings.endGroup();
}

bool BuildManager::runCommand(const QString &unparsedCommandLine, const QFileInfo &mainFile, const QFileInfo &currentFile, int currentLine, QString* buffer){
	if (waitingForProcess()) return false;
	if (unparsedCommandLine.isEmpty()) { emit processNotification(tr("Error: No command given")); return false; }
	ExpandingOptions options(mainFile, currentFile, currentLine);
	ExpandedCommands expansion = expandCommandLine(unparsedCommandLine, options);
	if (options.canceled) return false;
	if (expansion.commands.isEmpty()) return true;
	
	bool latexCompiled = false, pdfChanged = false;
	for (int i=0;i<expansion.commands.size();i++){
		latexCompiled |= expansion.commands[i].flags & RCF_COMPILES_TEX;
		pdfChanged |= expansion.commands[i].flags & RCF_CHANGE_PDF;
        if(buffer)
            expansion.commands[i].flags|=RCF_WAITFORFINISHED; // don't let buffer be destroyed before command is finished
	}
	if (latexCompiled) {
		ExpandedCommands temp = expandCommandLine(CMD_INTERNAL_PRE_COMPILE, options);
		for (int i=temp.commands.size()-1;i>=0;i--) expansion.commands.prepend(temp.commands[i]);
	}


	
	emit beginRunningCommands(expansion.primaryCommand, latexCompiled, pdfChanged);
	bool result = runCommandInternal(expansion, mainFile, buffer);
	emit endRunningCommands(expansion.primaryCommand, latexCompiled, pdfChanged);
	return result;
}

bool BuildManager::runCommandInternal(const ExpandedCommands& expandedCommands, const QFileInfo &mainFile, QString* buffer){
	const QList<CommandToRun> & commands = expandedCommands.commands;
	
	int remainingReRunCount = autoRerunLatex;
	for (int i=0;i<commands.size();i++) {
		CommandToRun cur = commands[i];
		if (testAndRunInternalCommand(cur.command, mainFile)) 
			continue;
		
		bool singleInstance = cur.flags & RCF_SINGLE_INSTANCE;
		if (singleInstance && runningCommands.contains(cur.command)) continue;
		bool latexCompiler = cur.flags & RCF_COMPILES_TEX;
		bool lastCommandToRun = i == commands.size()-1;
        bool waitForCommand = latexCompiler || (!lastCommandToRun && !singleInstance) || cur.flags & RCF_WAITFORFINISHED;
		
		ProcessX* p = newProcessInternal(cur.command, mainFile, singleInstance);
		REQUIRE_RET(p, false);
		
		p->setStdoutBuffer(buffer);
		
		emit beginRunningSubCommand(p, expandedCommands.primaryCommand, cur.parentCommand, cur.flags);
		
		if (!waitForCommand) connect(p, SIGNAL(finished(int)), p, SLOT(deleteLater()));
		
		p->startCommand();
		if (!p->waitForStarted(1000)) return false;
		
		if (latexCompiler || (!lastCommandToRun && !singleInstance) ) 
			if (!waitForProcess(p)) {
				p->deleteLater();
				return false;
			}
		
		emit endRunningSubCommand(p, expandedCommands.primaryCommand, cur.parentCommand, cur.flags);
		
        if (waitForCommand) {
            p->waitForFinished();
            p->deleteLater();
        }
		
		bool rerunnable = (cur.flags & RCF_RERUN) && (cur.flags & RCF_RERUNNABLE);
		if (rerunnable || latexCompiler){
			LatexCompileResult result = LCR_NORMAL;
			emit latexCompiled(&result);
			if (result == LCR_NORMAL) continue;
			if (!rerunnable || result == LCR_ERROR) return false;
			if (remainingReRunCount <= 0) return false;
			if (result == LCR_RERUN_WITH_BIBLIOGRAPHY) { runCommand(CMD_BIBLIOGRAPHY, mainFile, mainFile, 0); remainingReRunCount--;}
			REQUIRE_RET(result == LCR_RERUN || result == LCR_RERUN_WITH_BIBLIOGRAPHY, false);
			remainingReRunCount--;
			i--; //rerun
			//qDebug() << "rerun";
		} 
		
	}
	return true;
}

ProcessX* BuildManager::firstProcessOfDirectExpansion(const QString& command, const QFileInfo& mainFile, const QFileInfo& currentFile, int currentLine){
	ExpandingOptions options(mainFile, currentFile, currentLine);
	ExpandedCommands expansion = expandCommandLine(command, options);
	if (options.canceled) return 0;
	
	if (expansion.commands.isEmpty()) return 0;
	
	return newProcessInternal(expansion.commands.first().command, mainFile);
}

//don't use this
ProcessX* BuildManager::newProcessInternal(const QString &cmd, const QFileInfo& mainFile, bool singleInstance){
	if (singleInstance && runningCommands.contains(cmd))
		return 0;
	
	
	ProcessX* proc = new ProcessX(this, cmd, mainFile.absoluteFilePath());
	connect(proc, SIGNAL(processNotification(QString)), SIGNAL(processNotification(QString)));
	if (singleInstance){
		connect(proc, SIGNAL(finished(int)), SLOT(singleInstanceCompleted(int))); //will free proc after the process has ended
		runningCommands.insert(cmd, proc);
	}
	if(!mainFile.fileName().isEmpty())
		proc->setWorkingDirectory(mainFile.absolutePath());
	if (cmd.startsWith(TXS_CMD_PREFIX)) 
		connect(proc, SIGNAL(started()), SLOT(runInternalCommandThroughProcessX()));
	
#ifdef Q_WS_MACX
#if (QT_VERSION >= 0x040600)
	QProcess *myProcess = new QProcess();
	myProcess->start("bash -l -c \"echo $PATH\"");
	myProcess->waitForFinished(3000);
	if(myProcess->exitStatus()==QProcess::NormalExit){
		QByteArray res=myProcess->readAllStandardOutput();
		delete myProcess;
		QString path(res);
		QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
		env.insert("PATH", env.value("PATH") + ":"+path); //apply user path as well
		proc->setProcessEnvironment(env);
	}
#endif
#endif
	
	return proc;
}

bool BuildManager::waitForProcess(ProcessX* p){
	REQUIRE_RET(!processWaitedFor, false);
	processWaitedFor = p;
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	QTime time;
	time.start();
	while (p && p->isRunning()){
		qApp->instance()->processEvents(QEventLoop::ExcludeUserInputEvents);
		if (time.elapsed()>2000)
			qApp->instance()->processEvents(QEventLoop::AllEvents);
	}
	QApplication::restoreOverrideCursor();
	bool result = processWaitedFor;
	processWaitedFor = 0;
	return result;
}

bool BuildManager::waitingForProcess() const{
	return processWaitedFor;
}
void BuildManager::killCurrentProcess(){
	if (!processWaitedFor) return;
	processWaitedFor->kill();
	processWaitedFor = 0;
}

QString BuildManager::createTemporaryFileName(){
	QTemporaryFile *temp=new QTemporaryFile(QDir::tempPath ()+"/texstudio_XXXXXX.tex");
	temp->open();
	temp->setAutoRemove(false);
	QString tempName = temp->fileName();
	delete temp;
	return tempName;
}

void addLaTeXInputPaths(ProcessX* p, const QStringList& paths){
	if (paths.isEmpty()) return;
	static const QString SEP = ON_WIN(";") ON_NIX(":");
	static const QStringList envNames = QStringList() << "TEXINPUTS" << "BIBINPUTS" << "BSTINPUTS" << "MFINPUTS" << "MPINPUTS" << "TFMFONTS";
	QString addPath = paths.join(SEP) + SEP + "." + SEP;
	QStringList env = p->environment();
	env << QProcess::systemEnvironment();
	foreach (const QString& envname, envNames) {
		bool found = false;
		for (int i=0;i<env.size();i++)
			if (env[i].startsWith(envname+"=")) {
				found = true;
				env[i] = env[i] + SEP + addPath;
				break;
			}
		if (!found)
			env.append(envname + "="+addPath);
	}
	p->setOverrideEnvironment(env);
}

//there are 3 ways to generate a preview png:
//1. latex is called => dvipng is called after latex finished and converts the dvi
//2. latex is called and dvipng --follow is called at the same time, and will manage the wait time on its own
//3. latex is called => dvips converts .dvi to .ps => ghostscript is called and created final png
//Then ghostscript to convert it to
void BuildManager::preview(const QString &preamble, const PreviewSource& source, const QString& masterFile, QTextCodec *outputCodec){
	QString tempPath = QDir::tempPath()+QDir::separator()+"."+QDir::separator();
	
	//process preamble
	QString preamble_mod = preamble;
	static const QRegExp beamerClass("^(\\s*%[^\\n]*\\n)*\\s*\\\\documentclass(\\[[^\\]]*\\])?\\{beamer\\}"); //detect the usage of the beamer class
	if (previewRemoveBeamer && preamble_mod.contains(beamerClass)){
		//dvipng is very slow (>14s) and ghostscript is slow (1.4s) when handling beamer documents,
		//after setting the class to article dvipng runs in 77ms
		preamble_mod.remove(beamerClass);
		preamble_mod.insert(0,"\\documentclass{article}\n\\usepackage{beamerarticle}");
	}
	//preamble_mod.remove(QRegExp("\\\\input\\{[^/][^\\]?[^}]*\\}")); //remove all input commands that doesn't use an absolute path from the preamble
	
	QString masterDir = QFileInfo(masterFile).dir().absolutePath();
	QStringList addPaths;
	addPaths << masterDir;
	if (preamble_mod.contains("\\usepackage{import}")) {
		QStringList imports = regExpFindAllMatches(preamble_mod, QRegExp("\\\\subimport\\{([^}\n]*)\\}\\{[^}\n]*\\}"), 1);
		imports.sort();
		for (int i=imports.size()-1;i>0;i--)
			if (imports[i] == imports[i-1]) imports.removeAt(i);
		foreach (const QString& dir, imports)
			addPaths << masterDir+QDir::separator()+dir;
	}
	
	QString preambleFormatFile;
	if (previewPrecompilePreamble) {
		preambleFormatFile = preambleHash.value(preamble_mod, "");
		if (preambleFormatFile != "<failed>") {
			if (!preambleFormatFile.isEmpty())
				if (!QFile::exists(tempPath + preambleFormatFile + ".fmt"))
					preambleFormatFile = "";
			if (preambleFormatFile.isEmpty()) {
				//write preamble
				QTemporaryFile *tf=new QTemporaryFile(tempPath + "hXXXXXX.tex");
				REQUIRE(tf);
				tf->open();
				QTextStream out(tf);
				if (outputCodec) out.setCodec(outputCodec);
				out << preamble_mod;
				tf->setAutoRemove(false);
				tf->close();
				
				//compile
				QFileInfo fi(*tf);
				preambleFormatFile = fi.completeBaseName();
				previewFileNames.append(fi.absoluteFilePath());
				ProcessX *p = newProcessInternal(QString("%1 -interaction=nonstopmode -ini \"&latex %3 \\dump\"").arg(getCommandInfo(CMD_LATEX).getProgramName()).arg(preambleFormatFile), tf->fileName()); //no delete! goes automatically
				addLaTeXInputPaths(p, addPaths);
				p->setProperty("preamble", preamble_mod);
				p->setProperty("preambleFile", preambleFormatFile);
				connect(p,SIGNAL(finished(int)),this,SLOT(preamblePrecompileCompleted(int)));
				connect(p,SIGNAL(finished(int)),p,SLOT(deleteLater()));
				tf->setParent(p); //free file when process is deleted
				REQUIRE(p);
				p->startCommand();
				
				if (p->waitForStarted()) {
					if (p->waitForFinished(800)) {
						if (p->exitStatus() == QProcess::NormalExit && p->exitCode() == 0) {
							preambleHash.insert(preamble_mod, preambleFormatFile);
						} else {
							preambleHash.insert(preamble_mod, "<failed>");
							preambleFormatFile = "";
						}
					} else
						preambleFormatFile = ""; //wait + normal compile while waiting
					
				} else preambleFormatFile = ""; //compiling failed
				//delete tf; // tex file needs to be freed
			}
		} else preambleFormatFile = "";
	}
	
	// write to temp file
	// (place /./ after the temporary directory because it fails otherwise with qt4.3 on win and the tempdir "t:")
	QTemporaryFile *tf=new QTemporaryFile(tempPath + "XXXXXX.tex");
	if (!tf) return;
	tf->open();
	
	QTextStream out(tf);
	if (outputCodec) out.setCodec(outputCodec);
	if (preambleFormatFile.isEmpty()) out << preamble_mod;
	else out << "%&" << preambleFormatFile << "\n";
	out << "\n\\begin{document}\n" << source.text << "\n\\end{document}\n";
	// prepare commands/filenames
	QFileInfo fi(*tf);
	QString ffn=fi.absoluteFilePath();
	previewFileNames.append(ffn);
	previewFileNameToSource.insert(ffn, source);
	tf->setAutoRemove(false);
	tf->close();
	delete tf; // tex file needs to be freed
	// start conversion
	// tex -> dvi
	ProcessX *p1 = firstProcessOfDirectExpansion(CMD_LATEX, QFileInfo(ffn)); //no delete! goes automatically
	addLaTeXInputPaths(p1, addPaths);
	connect(p1,SIGNAL(finished(int)),this,SLOT(latexPreviewCompleted(int)));
	p1->startCommand();
	
	if (dvi2pngMode==DPM_DVIPNG_FOLLOW) {
		p1->waitForStarted();
		// dvi -> png
		//follow mode is a tricky features which allows dvipng to run while tex isn't finished
		ProcessX *p2 = firstProcessOfDirectExpansion("txs:///dvipng/[--follow]", ffn);
		if (!p1->overrideEnvironment().isEmpty()) p2->setOverrideEnvironment(p1->overrideEnvironment());
		connect(p2,SIGNAL(finished(int)),this,SLOT(conversionPreviewCompleted(int)));
		p2->startCommand();
	}
}

void BuildManager::clearPreviewPreambleCache(){
	QHash<QString, QString>::const_iterator it = preambleHash.constBegin();
	while (it != preambleHash.constEnd()) {
		removePreviewFiles(it.value());
		previewFileNames.removeAll(it.value());
		++it;
	}
	preambleHash.clear();
}

bool BuildManager::isCommandDirectlyDefined(const QString& id) const{
	if (id.startsWith(TXS_CMD_PREFIX)) return isCommandDirectlyDefined(id.mid(TXS_CMD_PREFIX.length()));
	if (internalCommands.contains(TXS_CMD_PREFIX + id)) return true;
	return !commands.value(id).commandLine.isEmpty();
}
CommandInfo BuildManager::getCommandInfo(const QString& id) const{
	if (id.startsWith(TXS_CMD_PREFIX)) return getCommandInfo(id.mid(TXS_CMD_PREFIX.length()));
	CommandMapping::const_iterator it = commands.constFind(id);
	if (it == commands.end()) return CommandInfo();
	return *it;
}

QString BuildManager::editCommandList(const QString& list, const QString& excludeId){
	QStringList ids = commandSortingsOrder, names, commands;
	ids << userToolOrder;
	ids.insert(ids.indexOf("view-pdf-external"), CMD_VIEW_PDF_INTERNAL);
	ids << CMD_CONDITIONALLY_RECOMPILE_BIBLIOGRAPHY;
	ids.removeAll(excludeId); ids.removeAll(TXS_CMD_PREFIX + excludeId);
	for (int i=0;i<ids.size();i++) {
		CommandInfo ci = getCommandInfo(ids[i]);
		names << (ci.displayName.isEmpty()?ids[i]:ci.displayName);
		if (names.last() == CMD_VIEW_PDF_INTERNAL) names.last() = tr("Internal Pdf Viewer");
		commands << (ci.commandLine.isEmpty()?ids[i]:ci.commandLine);
		if (!ids[i].startsWith(TXS_CMD_PREFIX)) ids[i] = TXS_CMD_PREFIX + ids[i];
	}
	
	UserQuickDialog uqd(0, ids, names, commands);
	uqd.setCommandList(list);
	if (uqd.exec() == QDialog::Accepted) return uqd.getCommandList();
	else return list;
}

CommandMapping BuildManager::getAllCommands(){
	return commands;
}
QStringList BuildManager::getCommandsOrder(){
	QStringList order = commandSortingsOrder;
	order << userToolOrder;
	foreach (const QString& more, commands.keys())
		if (!order.contains(more)) order << more;
	return order;
}
void BuildManager::setAllCommands(const CommandMapping& cmds, const QStringList& userOrder){
	this->commands = cmds;
	this->userToolOrder = userOrder;
	
	for (CommandMapping::iterator it = commands.begin(), end = commands.end(); it != end; ++it)
		if (it.value().commandLine == tr("<unknown>"))
			it.value().commandLine = "";	
	
	static QStringList latexCommandsUnexpanded, rerunnableCommandsUnexpanded, pdfCommandsUnexpanded, stdoutCommandsUnexpanded, viewerCommandsUnexpanded;
	ConfigManagerInterface::getInstance()->registerOption("Tools/Kind/LaTeX", &latexCommandsUnexpanded, QStringList() << "latex" << "pdflatex" << "xelatex" << "lualatex" << "latexmk" << "compile");
	ConfigManagerInterface::getInstance()->registerOption("Tools/Kind/Rerunnable", &rerunnableCommandsUnexpanded, QStringList() << "latex" << "pdflatex" << "xelatex" << "lualatex");
	ConfigManagerInterface::getInstance()->registerOption("Tools/Kind/Pdf", &pdfCommandsUnexpanded, QStringList() << "pdflatex" << "xelatex" << "lualatex" << "latexmk");
	ConfigManagerInterface::getInstance()->registerOption("Tools/Kind/Stdout", &stdoutCommandsUnexpanded, QStringList() << "bibtex" << "biber" << "bibtex8" << "bibliography");
	ConfigManagerInterface::getInstance()->registerOption("Tools/Kind/Viewer", &viewerCommandsUnexpanded, QStringList() << "view-pdf" << "view-ps" << "view-dvi" << "view-pdf-internal" << "view-pdf-external" << "view");
	
	QList<QStringList*> lists = QList<QStringList*>() << &latexCommands << &rerunnableCommands << &pdfCommands << &stdoutCommands << &viewerCommands;
	QList<QStringList*> listsUnexpanded = QList<QStringList*>() << &latexCommandsUnexpanded << &rerunnableCommandsUnexpanded << &pdfCommandsUnexpanded << &stdoutCommandsUnexpanded << &viewerCommandsUnexpanded;
	Q_ASSERT(lists.size() == listsUnexpanded.size());
	for (int i=0;i<lists.size();i++) {
		QStringList* sl = lists[i];
		*sl = *listsUnexpanded.at(i);
		for (int i=0;i<sl->size();i++) {
			Q_ASSERT(commands.contains((*sl)[i]) || (*sl)[i] == "view-pdf-internal"); 
			(*sl)[i] = getCommandInfo((*sl)[i]).commandLine.trimmed();
		}
	}
}

void BuildManager::singleInstanceCompleted(int status){
	Q_UNUSED(status);
	QObject* s = sender();
	REQUIRE(s);
	for (QMap<QString, ProcessX *>::iterator it = runningCommands.begin(), end = runningCommands.end(); it != end;)
		if (it.value() == s) it = runningCommands.erase(it);
		else ++it;
}

void BuildManager::preamblePrecompileCompleted(int status){
	Q_UNUSED(status);
	QProcess* p = qobject_cast<QProcess*>(sender());
	REQUIRE(p);
	if (p->exitCode() != 0 || p->exitStatus() != QProcess::NormalExit) {
		preambleHash.insert(p->property("preamble").toString(), "<failed>");
	} else
		preambleHash.insert(p->property("preamble").toString(), p->property("preambleFile").toString());
}

//latex has finished the dvi creation
//now either dvips or dvipng is necessary if not already running
void BuildManager::latexPreviewCompleted(int status){
	Q_UNUSED(status);
	if (dvi2pngMode==DPM_DVIPNG) {
		ProcessX* p1=qobject_cast<ProcessX*> (sender());
		if (!p1) return;
		// dvi -> png
		ProcessX *p2 = firstProcessOfDirectExpansion(CMD_DVIPNG,p1->getFile());
		if (!p1->overrideEnvironment().isEmpty()) p2->setOverrideEnvironment(p1->overrideEnvironment());
		connect(p2,SIGNAL(finished(int)),this,SLOT(conversionPreviewCompleted(int)));
		p2->startCommand();
	}
	if (dvi2pngMode==DPM_DVIPS_GHOSTSCRIPT) {
		ProcessX* p1=qobject_cast<ProcessX*> (sender());
		if (!p1) return;
		// dvi -> ps
		ProcessX *p2 = firstProcessOfDirectExpansion("txs:///dvips/[-E]", p1->getFile());
		if (!p1->overrideEnvironment().isEmpty()) p2->setOverrideEnvironment(p1->overrideEnvironment());
		connect(p2,SIGNAL(finished(int)),this,SLOT(dvi2psPreviewCompleted(int)));
		p2->startCommand();
	}
}

//dvi to ps conversion is finished, call ghostscript to make a useable png from it
void BuildManager::dvi2psPreviewCompleted(int status){
	Q_UNUSED(status);
	ProcessX* p2=qobject_cast<ProcessX*> (sender());
	if (!p2) return;
	// ps -> png, ghostscript is quite, safe, will create 24-bit png
	ProcessX *p3 = firstProcessOfDirectExpansion("txs:///gs/[-q][-dSAFER][-dBATCH][-dNOPAUSE][-sDEVICE=png16m][-dEPSCrop][-sOutputFile=\"?am)1.png\"]",p2->getFile());
	if (!p2->overrideEnvironment().isEmpty()) p3->setOverrideEnvironment(p2->overrideEnvironment());
	connect(p3,SIGNAL(finished(int)),this,SLOT(conversionPreviewCompleted(int)));
	p3->startCommand();
}

void BuildManager::conversionPreviewCompleted(int status){
	Q_UNUSED(status);
	ProcessX* p2=qobject_cast<ProcessX*> (sender());
	if (!p2) return;
	// put image in preview
	QString processedFile=p2->getFile();
	QString fn=parseExtendedCommandLine("?am)1.png",processedFile).first();
	if(QFileInfo(fn).exists())
		emit previewAvailable(fn, previewFileNameToSource[processedFile]);
}
void BuildManager::commandLineRequestedDefault(const QString& cmdId, QString* result, bool * user){
	if (user) *user = false;
	if (!result) return;
	int space = cmdId.indexOf(' ');
	if (space == -1) space = cmdId.size();
	if (internalCommands.contains(cmdId.left(space)) || internalCommands.contains(TXS_CMD_PREFIX + cmdId.left(space))) {
		*result = cmdId;
		if (!result->startsWith(TXS_CMD_PREFIX)) *result = TXS_CMD_PREFIX + *result;
		return;
	}
	CommandMapping::iterator it = commands.find(cmdId);
	if (it != commands.end()) {
		*result = it->commandLine; 
		if (user) *user = it->user;
	}
}
void BuildManager::runInternalCommandThroughProcessX(){
	ProcessX *p = qobject_cast<ProcessX*>(sender());
	REQUIRE(p);
	REQUIRE(p->getCommandLine().startsWith(TXS_CMD_PREFIX));
	testAndRunInternalCommand(p->getCommandLine(), p->getFile());
}
bool BuildManager::testAndRunInternalCommand(const QString& cmd, const QFileInfo& mainFile){
	int space = cmd.indexOf(' ');
	QString cmdId, options;
	if (space == -1 ) cmdId = cmd;
	else cmdId = cmd.left(space), options = cmd.mid(space+1);
	if (internalCommands.contains(cmdId)) {
		emit runInternalCommand(cmdId, mainFile, options);
		return true;
	}
	return false;
}

void BuildManager::removePreviewFiles(QString elem){
	QDir currentDir(QFileInfo(elem).absoluteDir());
	elem=QFileInfo(elem).completeBaseName();
	QStringList files;
	files = currentDir.entryList(QStringList(elem+"*"),
	                             QDir::Files | QDir::NoSymLinks);
	foreach(const QString& file,files)
		QFile::remove(currentDir.absolutePath()+"/"+file);
}


//DDE things
#ifdef Q_WS_WIN
#include "windows.h"
bool BuildManager::executeDDE(QString ddePseudoURL) {
	//parse URL
	if (ddePseudoURL.startsWith("dde:///")) ddePseudoURL.remove(0,7);
	else if (ddePseudoURL.startsWith("dde://")) { txsInformation(tr("You have used a dde:// command with two slashes, which is deprecated. Please change it to a triple slash command dde:/// by adding another slash.")); ddePseudoURL.remove(0,6); }
	else return false;
	
	if (ddePseudoURL.length() < 3) return false;
	QString serviceEXEPath;
	if (ddePseudoURL[1] == ':' || (ddePseudoURL[0] == '"' && ddePseudoURL[2] == ':')) { //extended dde of format dde:///<path>:control/commands
		int pathLength = ddePseudoURL.indexOf(':', 3);
		serviceEXEPath = ddePseudoURL.left(pathLength);
		ddePseudoURL.remove(0,pathLength+1);
	}
	
	int slash=ddePseudoURL.indexOf("/");
	if (slash==-1) return false;
	QString service = ddePseudoURL.left(slash);
	ddePseudoURL.remove(0,slash+1);
	slash=ddePseudoURL.indexOf("/");
	if (slash==-1) return false;
	QString topic = ddePseudoURL.left(slash);
	ddePseudoURL.remove(0,slash+1);
	QStringList commands = ddePseudoURL.split("[",QString::SkipEmptyParts);
	if (commands.isEmpty()) return false;
	
	
	//connect to server/topic
	
	if (pidInst==0)
		if (DdeInitializeA(&pidInst, NULL, APPCLASS_STANDARD | APPCMD_CLIENTONLY | CBF_SKIP_ALLNOTIFICATIONS, 0L) != DMLERR_NO_ERROR)
			return false;
	
	QCoreApplication::processEvents();
	
	HSZ hszService = DdeCreateStringHandleA(pidInst, service.toLocal8Bit().data() , CP_WINANSI);
	if (!hszService) return false;
	HSZ hszTopic = DdeCreateStringHandleA(pidInst, topic.toLocal8Bit().data(), CP_WINANSI);
	if (!hszTopic) {
		DdeFreeStringHandle(pidInst, hszService);
		return false;
	}
	HCONV hConv = DdeConnect(pidInst, hszService, hszTopic, NULL);
	if (!hConv && !serviceEXEPath.isEmpty()){
		if (!serviceEXEPath.contains('"') && serviceEXEPath.contains(' ') && QFileInfo(serviceEXEPath).exists())
			serviceEXEPath = "\"" + serviceEXEPath + "\"";
		//connecting failed; start the service if necessary
		QProcess* p = new QProcess(QCoreApplication::instance()); //application is parent, to close the service if txs is closed
		p->start(serviceEXEPath);
		if (p->waitForStarted(5000)) {
			connect(p, SIGNAL(finished(int)), p, SLOT(deleteLater())); //will free proc after the process has ended
			//try again to connect (repeatedly 2s long)
			DWORD startTime = GetTickCount();
			while (!hConv && GetTickCount() - startTime < 1000) {
				hConv = DdeConnect(pidInst, hszService, hszTopic, NULL);
				Sleep(100);
			}
		} else delete p;
	}
	
	QCoreApplication::processEvents();
	
	DdeFreeStringHandle(pidInst, hszService);
	DdeFreeStringHandle(pidInst, hszTopic);
	if (!hConv) return false;
	
	//execute requests
	foreach(const QString s, commands) {
		QString temp=("["+s.trimmed());
		QByteArray ba= temp.toLocal8Bit();
		HDDEDATA req= DdeCreateDataHandle(pidInst, (LPBYTE) ba.data(), ba.size()+1, 0, 0, CF_TEXT, 0);
		if (req) {
			HDDEDATA recData=DdeClientTransaction((BYTE*)req, (DWORD)-1, hConv, 0, 0, XTYP_EXECUTE, 1000, 0);
			DdeFreeDataHandle(req);
			if (recData) DdeFreeDataHandle(recData);
		}
		//else QMessageBox::information(0,"TeXstudio",QObject::tr("DDE command %1 failed").arg("["+s),0); //break; send all commands
	}
	
	QCoreApplication::processEvents();
	
	//disconnect
	DdeDisconnect(hConv);
	
	QCoreApplication::processEvents();
	
	return true;
}
#endif

ProcessX::ProcessX(BuildManager* parent, const QString &assignedCommand, const QString& fileToCompile):
       QProcess(parent), cmd(assignedCommand.trimmed()), file(fileToCompile), isStarted(false), ended(false), stdoutEnabled(true), stdoutEnabledOverrideOn(false), stdoutBuffer(0) {
	QString stdoutRedirection = cmd.mid(cmd.lastIndexOf(">") + 1).trimmed();
	if (stdoutRedirection == "/dev/null" || stdoutRedirection == "txs:///messages"  )  {
		cmd = cmd.left(cmd.lastIndexOf(">")).trimmed();
		if (stdoutRedirection == "/dev/null") stdoutEnabled = false;
		else stdoutEnabledOverrideOn = true;
	} //todo: stderr redirection
	connect(this, SIGNAL(started()), SLOT(onStarted()));
	connect(this, SIGNAL(finished(int)), SLOT(onFinished(int)));
	connect(this, SIGNAL(error(QProcess::ProcessError)), SLOT(onError(QProcess::ProcessError)));
}
void ProcessX::startCommand() {
	ended = false;
	
#ifdef Q_WS_WIN
	if (cmd.startsWith("dde://") || cmd.startsWith("dde:///")) {
		onStarted();
		BuildManager* manager = qobject_cast<BuildManager*>(parent());
		if (!manager) {
			emit finished(1);
			emit finished(1, NormalExit);
			return;
		}
		bool ok = manager->executeDDE(cmd);
		emit finished(ok?0:1);
		emit finished(ok?0:1, NormalExit);
		return;
	}
#endif
	
	if (cmd.startsWith("txs:///")){
		emit started();
		emit finished(0);
		emit finished(0, NormalExit);
		return;
	}
	if (stdoutEnabled || stdoutBuffer) 
		connect(this, SIGNAL(readyReadStandardOutput()),this, SLOT(readFromStandardOutput()));
	if (stderrEnabled) 
		connect(this, SIGNAL(readyReadStandardError()),this, SLOT(readFromStandardError()));
	
	
	QProcess::start(cmd);
	
#ifdef PROFILE_PROCESSES
	connect(this, SIGNAL(finished(int)), SLOT(finished()));
	time.start();
#endif
}
bool ProcessX::waitForStarted(int timeOut){
	if (isStarted) return true;
	return QProcess::waitForStarted(timeOut);
}
const QString& ProcessX::getFile(){
	return file;
}
const QString& ProcessX::getCommandLine(){
	return cmd;
}
bool ProcessX::showStdout() const{
	return stdoutEnabled; 
}
void ProcessX::setShowStdout(bool show){
	if (stdoutEnabledOverrideOn) show = true;
	stdoutEnabled = show; 
}
QString * ProcessX::getStdoutBuffer(){ 
	return stdoutBuffer;
}
void ProcessX::setStdoutBuffer(QString *buffer){
	stdoutBuffer = buffer;
}
bool ProcessX::showStderr() const{
	return stderrEnabled;
}
void ProcessX::setShowStderr(bool show){
	stderrEnabled = show;
}

void ProcessX::setOverrideEnvironment(const QStringList& env) {
	overriddenEnvironment = env;
	setEnvironment(env);
}

const QStringList& ProcessX::overrideEnvironment(){
	return overriddenEnvironment;
}


int ProcessX::exitStatus() const{return QProcess::exitStatus();}
int ProcessX::exitCode() const{return QProcess::exitCode(); }
QString ProcessX::readAllStandardOutputStr(){return QString::fromLocal8Bit(QProcess::readAllStandardOutput());}
QString ProcessX::readAllStandardErrorStr(){return QString::fromLocal8Bit(QProcess::readAllStandardError());}
bool ProcessX::waitForFinished( int msecs ){return QProcess::waitForFinished(msecs);}

bool ProcessX::isRunning() const{
	return isStarted && !ended;
}

void ProcessX::onStarted(){
	if (isStarted) return; //why am I called twice?
	isStarted=true;
	emit processNotification(tr("Process started: %1").arg(cmd));
}

void ProcessX::onError(ProcessError error){
	if (error == FailedToStart)
		emit processNotification(tr("Error: Could not start the command: %1").arg(cmd));
	else if (error == Crashed)
		emit processNotification(tr("Error: Command crashed: %1").arg(cmd));
}

void ProcessX::onFinished(int error){
	if (error){
		emit processNotification(tr("Process exited with error(s)"));
		readFromStandardError(true);
	} else {
		emit processNotification(tr("Process exited normally"));
		readFromStandardOutput();
		readFromStandardError();
	}
	ended = true;
}

#ifdef PROFILE_PROCESSES
void ProcessX::finished(){
	qDebug() << "Process: "<<qPrintable(cmd)<< "  Running time: " << time.elapsed();
}
#endif

void ProcessX::readFromStandardOutput(){
	if (!stdoutEnabled && !stdoutBuffer) return;
	QString t = readAllStandardOutputStr().trimmed();
	if (stdoutBuffer) stdoutBuffer->append(t);
	emit standardOutputRead(t);
}

void ProcessX::readFromStandardError(bool force){
	if (!stderrEnabled && !force) return;
	QString t = readAllStandardErrorStr().simplified();
	emit standardErrorRead(t);
}
