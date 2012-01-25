#include "buildmanager.h"

#include "smallUsefulFunctions.h"
#include "configmanagerinterface.h"

#include "userquickdialog.h"

#ifdef Q_WS_WIN
#include "windows.h"
#endif


QString BuildManager::TXS_INTERNAL_PDF_VIEWER = "tmx://internal-pdf-viewer";

BuildManager::BuildManager()
#ifdef Q_WS_WIN
		:
		pidInst(0)
#endif
{
}
BuildManager::~BuildManager() {
	//remove preview file names
	foreach(const QString& elem,previewFileNames)
		removePreviewFiles(elem);
#ifdef Q_WS_WIN
	if (pidInst) DdeUninitialize(pidInst);
#endif
}

QString BuildManager::cmdToConfigString(LatexCommand cmd){
	switch (cmd) {
		case CMD_LATEX: return "Tools/Latex";
		case CMD_DVIPS: return "Tools/Dvips";
		case CMD_PS2PDF: return "Tools/Ps2pdf";
		case CMD_MAKEINDEX: return "Tools/Makeindex";
		case CMD_BIBTEX: return "Tools/Bibtex";
		case CMD_PDFLATEX: return "Tools/Pdflatex";
		case CMD_DVIPDF: return "Tools/Dvipdf";
		case CMD_DVIPNG: return "Tools/Dvipng";
		case CMD_METAPOST: return "Tools/Metapost";
		case CMD_VIEWDVI: return "Tools/Dvi";
		case CMD_VIEWPS: return "Tools/Ps";
		case CMD_VIEWPDF: return "Tools/Pdf";
		case CMD_GHOSTSCRIPT: return "Tools/Ghostscript";
		case CMD_USER_PRECOMPILE: return "Tools/Precompile";
		case CMD_USER_QUICK: return "Tools/Userquick";
		case CMD_SVN: return "Tools/SVN";
		case CMD_SVNADMIN: return "Tools/SVNADMIN";
		case CMD_ASY: return "Tools/Asy";
		default: return QString("_unknown_cmd_%1").arg((int)cmd);
	}
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
				const QFileInfo& selectedFile=useCurrentFile?currentFile:mainFile;
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

QStringList BuildManager::parseExtendedCommandLine(QString str, const QFileInfo &mainFile, int currentLine) {
		return parseExtendedCommandLine(str, mainFile, mainFile, currentLine);
}


QString BuildManager::findFileInPath(QString fileName) {
#ifdef Q_WS_MAC
        QProcess *myProcess = new QProcess();
	myProcess->start("bash -l -c \"echo $PATH\"");
        myProcess->waitForFinished(3000);
	if(myProcess->exitStatus()==QProcess::CrashExit) return "";
	QByteArray res=myProcess->readAllStandardOutput();
	delete myProcess;
	QString path(res);
#else
	QStringList env= QProcess::systemEnvironment();    //QMessageBox::information(0,env.join("  \n"),env.join("  \n"),0);
	int i=env.indexOf(QRegExp("^PATH=.*", Qt::CaseInsensitive));
	if (i==-1) return "";
	QString path=env[i].mid(5); //skip path=
#endif
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
#ifdef Q_WS_WIN
	QString fileName=cmd+".exe";
#else
	QString fileName=cmd;
#endif
	if (!options.startsWith(" ")) options=" "+options;
	if (!BuildManager::findFileInPath(fileName).isEmpty())
		return cmd+options; //found in path
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
	return "";
}


QString BuildManager::guessCommandName(LatexCommand cmd) {
	//todo: remove default options and call defaultCommandOptions instead

//-------------User Commands--------------------
//no need to perform next checks
	switch (cmd) {
		case CMD_USER_QUICK:
			return "latex -interaction=nonstopmode %.tex|bibtex %.aux|latex -interaction=nonstopmode %.tex|latex -interaction=nonstopmode %.tex|xdvi %.dvi";
		case CMD_SVN:
			return "svn ";
		case CMD_SVNADMIN:
			return "svnadmin ";
		case CMD_ASY:
			return "asy ?m*.asy";
		case CMD_USER_PRECOMPILE:
		case CMD_MAXIMUM_COMMAND_VALUE:
			return "";
		default:;
	}


//-------------Latex Base Commands ---------------------
//They're the same on every platform and we will choose the path default if they exists
	QString baseCommand  = baseCommandName(cmd); //platform independent name
	QString defaultOptions= defaultCommandOptions(cmd); //default parameters
	if (!baseCommand.isEmpty()){
		//search it
		QString bestCommand = searchBaseCommand(baseCommand,defaultOptions);
		if (!bestCommand.isEmpty()) return bestCommand;
	}

//-------------Viewer or WinGhostScript----------------------
//Platform dependant
#ifdef Q_WS_MACX
	switch (cmd) {
		case CMD_VIEWDVI: return "open %.dvi > /dev/null";
		case CMD_VIEWPS: return "open %.ps > /dev/null";
		case CMD_VIEWPDF: return "open %.pdf > /dev/null";
		default:;
	}
#endif
#ifdef Q_WS_WIN
	switch (cmd) {
	case CMD_VIEWDVI: {
		const QString yapOptions = " -1 -s @?c:ame \"?am.dvi\"";
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
		else break;
	}
	case CMD_VIEWPS: {
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
		break;
	}
	case CMD_VIEWPDF: {
		QString def=W32_FileAssociation(".pdf");
		if (!def.isEmpty())
			return def;

		foreach (const QString& p, getProgramFilesPaths())
			if (QDir(p+"Adobe").exists())
				foreach (const QString& rv, QDir(p+"Adobe").entryList(QStringList() << "Reader*", QDir::Dirs, QDir::Time)){
					QString x = p+"Adobe/"+rv+"/Reader/AcroRd32.exe";
					if (QFile::exists(x)) return "\""+x+"\" \"?am.pdf\"";
				}
		break;
	}
	case CMD_GHOSTSCRIPT: {
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
		else break;
	}
	default:;
	}
#endif
#ifdef Q_WS_X11
// xdvi %.dvi  -sourceposition @:%.tex
// kdvi "file:%.dvi#src:@ %.tex"
	switch (cmd) {
	case CMD_VIEWDVI:
		switch (x11desktop_env()) {
		case 3:	return "kdvi %.dvi > /dev/null";
		case 4:	return "okular %.dvi > /dev/null";
		default:return "evince %.dvi > /dev/null";
		};
	case CMD_VIEWPS:
		switch (x11desktop_env()) {
		case 3: return "kghostview %.ps > /dev/null";
		case 4:	return "okular %.ps > /dev/null";
		default:return "evince %.ps > /dev/null";
		};
	case CMD_VIEWPDF:
		switch (x11desktop_env()) {
		case 3: return "kpdf %.pdf > /dev/null";
		case 4:	return "okular %.pdf > /dev/null";
		default:return "evince %.pdf > /dev/null";
		};
	default:;
	}
#endif
	return baseCommand+" "+defaultOptions;
}
//returns a platform independent base name if it exists
QString BuildManager::baseCommandName(LatexCommand cmd){
	switch(cmd) {
		case CMD_LATEX: return "latex";
		case CMD_DVIPS: return "dvips";
		case CMD_DVIPNG: return "dvipng";
		case CMD_PS2PDF: return "ps2pdf";
		case CMD_MAKEINDEX: return "makeindex";
		case CMD_BIBTEX: return "bibtex";
		case CMD_PDFLATEX: return "pdflatex";
		case CMD_DVIPDF: return "dvipdf";
		case CMD_METAPOST: return "mpost";
		case CMD_SVN: return "svn";
		case CMD_SVNADMIN: return "svnadmin";
		case CMD_ASY: return "asy";
		/*case CMD_VIEWDVI: case CMD_VIEWPS:  case CMD_VIEWPDF:
			viewer are platform dependent*/
		case CMD_GHOSTSCRIPT: return "gs";
		default: return "";
	}
}
QString BuildManager::defaultCommandOptions(LatexCommand cmd){
	switch (cmd){
		case CMD_LATEX: return "-src -interaction=nonstopmode %.tex";
		case CMD_DVIPS: return "-o %.ps %.dvi";
		case CMD_DVIPNG: return "-T tight -D 120 %.dvi";
		case CMD_PS2PDF: return "%.ps";
		case CMD_MAKEINDEX: return "%.idx";
		case CMD_BIBTEX:
		#ifdef Q_WS_WIN
			return "%"; //miktex bibtex will stop (appears like crash in tmx) if .aux is attached
		#else
			return "%.aux";
		#endif
		case CMD_PDFLATEX: return "-synctex=1 -interaction=nonstopmode %.tex";
		case CMD_DVIPDF: return "%.dvi";
		case CMD_METAPOST: return "-interaction=nonstopmode ?me)";
		case CMD_VIEWDVI: return "%.dvi";
		case CMD_VIEWPS: return "%.ps";
		case CMD_VIEWPDF: return "%.pdf";
		case CMD_SVN: return "";
		case CMD_SVNADMIN: return "";
		case CMD_ASY: return "?m*.asy";
		case CMD_GHOSTSCRIPT: return "\"?am.ps\"";
		default: return "";
	}
}
QString BuildManager::commandDisplayName(LatexCommand cmd){
	switch (cmd){
		case CMD_LATEX: return "LaTeX";
		case CMD_DVIPS: return "DviPs";
		case CMD_DVIPNG: return "DviPng";
		case CMD_PS2PDF: return "Ps2Pdf";
		case CMD_MAKEINDEX: return "Makeindex";
        case CMD_BIBTEX: return "BibTeX";
		case CMD_PDFLATEX: return "PdfLaTeX";
		case CMD_DVIPDF: return "DviPdf";
		case CMD_METAPOST: return "Metapost";
		case CMD_VIEWDVI: return tr("Dvi Viewer");
		case CMD_VIEWPS: return tr("Ps Viewer");
		case CMD_VIEWPDF: return tr("Pdf Viewer");
		case CMD_GHOSTSCRIPT: return "Ghostscript";
		case CMD_SVN: return "SVN";
		case CMD_SVNADMIN: return "SVNADMIN";
		case CMD_ASY: return "Asymptote";
		default: return "";
	}
}
void BuildManager::registerOptions(ConfigManagerInterface& cmi){
	for (LatexCommand i=CMD_LATEX; i < CMD_MAXIMUM_COMMAND_VALUE;++i)
		cmi.registerOption(cmdToConfigString(i),&commands[i],"<default>");
	cmi.registerOption("Tools/Quick Mode",&quickmode,-1);
	Q_ASSERT(sizeof(dvi2pngMode) == sizeof(int));
	cmi.registerOption("Tools/Dvi2Png Mode",reinterpret_cast<int*>(&dvi2pngMode), -1);
	cmi.registerOption("Files/Save Files Before Compiling", reinterpret_cast<int*>(&saveFilesBeforeCompiling), (int)SFBC_ONLY_NAMED);
	cmi.registerOption("Preview/Remove Beamer Class", &previewRemoveBeamer, true);
	cmi.registerOption("Preview/Precompile Preamble", &previewPrecompilePreamble, true);
}
void BuildManager::readSettings(const QSettings &settings){
	Q_UNUSED(settings);
	for (LatexCommand i=CMD_LATEX; i < CMD_MAXIMUM_COMMAND_VALUE;++i)
		setLatexCommand(i,commands[i]);
	if (reinterpret_cast<int&>(quickmode)<0) {
		//choose working default where every necessary command is knownr
		if (hasLatexCommand(CMD_LATEX) && hasLatexCommand(CMD_DVIPS) && hasLatexCommand(CMD_VIEWPS))
			quickmode=1;
		else if (hasLatexCommand(CMD_LATEX) && hasLatexCommand(CMD_VIEWDVI))
			quickmode=2;
		else if (hasLatexCommand(CMD_PDFLATEX) && hasLatexCommand(CMD_VIEWPDF))
			quickmode=3;
		else if (hasLatexCommand(CMD_LATEX) && hasLatexCommand(CMD_DVIPDF) && hasLatexCommand(CMD_VIEWPDF))
			quickmode=4;
		else if (hasLatexCommand(CMD_LATEX) && hasLatexCommand(CMD_DVIPS) &&
					 hasLatexCommand(CMD_PS2PDF) && hasLatexCommand(CMD_VIEWPDF))
			quickmode=5;
		else if (hasLatexCommand(CMD_LATEX) && hasLatexCommand(CMD_ASY) &&
				 hasLatexCommand(CMD_LATEX) && hasLatexCommand(CMD_VIEWDVI))
			quickmode=6;
		else if (hasLatexCommand(CMD_PDFLATEX) && hasLatexCommand(CMD_ASY) &&
				 hasLatexCommand(CMD_PDFLATEX) && hasLatexCommand(CMD_VIEWPDF))
			quickmode=7;
		else quickmode=1; //texmaker default
	}
	if (reinterpret_cast<int&>(dvi2pngMode)<0) {
		if (hasLatexCommand(CMD_DVIPNG)) dvi2pngMode = DPM_DVIPNG; //best/fastest mode
		else if (hasLatexCommand(CMD_DVIPS) && hasLatexCommand(CMD_GHOSTSCRIPT)) dvi2pngMode = DPM_DVIPS_GHOSTSCRIPT; //compatible mode
		else dvi2pngMode = DPM_DVIPNG; //won't work
	}

}

void BuildManager::setLatexCommand(LatexCommand cmd, const QString &cmdString){
	if (cmdString=="<default>") {
	    commands[cmd]=guessCommandName(cmd);
	    if(cmd==CMD_VIEWPDF)
		commands[cmd].prepend(BuildManager::TXS_INTERNAL_PDF_VIEWER+"/");
	}
	else if (cmdString==tr("<unknown>")) commands[cmd]="";
	else {
		//force commands to include options (e.g. file name)
		QString baseName = baseCommandName(cmd);
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
			commands[cmd] = cmdString + " " + defaultCommandOptions(cmd);
		else
			commands[cmd] = cmdString;
	}
}

QString BuildManager::getLatexCommand(LatexCommand cmd){ 
	return commands[cmd];
}
QString BuildManager::getLatexCommandForDisplay(LatexCommand cmd){
	if (commands[cmd] == "") return tr("<unknown>");
        QString res=commands[cmd];
        if(cmd==CMD_VIEWPDF && res.startsWith(BuildManager::TXS_INTERNAL_PDF_VIEWER))
            res=res.mid(BuildManager::TXS_INTERNAL_PDF_VIEWER.length() + 1);
        return res;
}
QString BuildManager::getLatexCommandExecutable(LatexCommand cmd){
	QString cmdStr = getLatexCommand(cmd).trimmed();
	int p=-1;
	if (cmdStr.startsWith('"')) p = cmdStr.indexOf('"',1)+1;
	else if (cmdStr.contains(' ')) p = cmdStr.indexOf(' ')+1;
	if (p==-1) p = cmdStr.length(); //indexOf failed if it returns -1
	return cmdStr.mid(0, p);
}

bool BuildManager::hasLatexCommand(LatexCommand cmd){
	return !commands[cmd].isEmpty();
}
ProcessX* BuildManager::newProcess(LatexCommand cmd, const QString &fileToCompile, int currentLine){
	return newProcess(getLatexCommand(cmd), fileToCompile, currentLine);
}
ProcessX* BuildManager::newProcess(LatexCommand cmd, const QString &additionalParameters, const QString &fileToCompile, int currentLine){
	QString cmdStr = getLatexCommand(cmd).trimmed();
	int p=-1;
	if (cmdStr.startsWith('"')) p = cmdStr.indexOf('"',1)+1;
	else if (cmdStr.contains(' ')) p = cmdStr.indexOf(' ')+1;
	if (p==-1) p = cmdStr.length(); //indexOf failed if it returns -1
	cmdStr.insert(p," "+additionalParameters+" ");
	return newProcess(cmdStr, fileToCompile, currentLine);
}

ProcessX* BuildManager::newProcess(const QString &unparsedCommandLine, const QString &mainFile, const QString &currentFile, int currentLine, bool singleInstance){
	QFileInfo mfi(mainFile);
	QFileInfo cfi;
	if (mainFile==currentFile) cfi=mfi;
	else cfi=QFileInfo(currentFile);
	QString cmd=BuildManager::parseExtendedCommandLine(unparsedCommandLine,mfi,cfi,currentLine).first();

	return newProcessInternal(cmd,mainFile,singleInstance);

}
QList<ProcessX*> BuildManager::newProcesses(const QString &unparsedCommandLine, const QString &mainFile, const QString &currentFile, int currentLine, bool singleInstance){
	QFileInfo mfi(mainFile);
	QFileInfo cfi;
	if (mainFile==currentFile) cfi=mfi;
	else cfi=QFileInfo(currentFile);
	QStringList cmd=BuildManager::parseExtendedCommandLine(unparsedCommandLine,mfi,cfi,currentLine);

	QList<ProcessX*> res;
	foreach (const QString& c, cmd){
		ProcessX * px = newProcessInternal(c,mainFile,singleInstance);
		if (px) res << px;
	}
	return res;

}
ProcessX* BuildManager::newProcess(const QString &unparsedCommandLine, const QString &mainFile, int currentLine){
	return newProcess(unparsedCommandLine, mainFile, mainFile, currentLine);
}
//don't use this
ProcessX* BuildManager::newProcessInternal(const QString &cmd, const QString& mainFile, bool singleInstance){
	if (singleInstance && runningCommands.contains(cmd))
		return 0;

	ProcessX* proc = new ProcessX(this, cmd, mainFile);
	connect(proc, SIGNAL(finished(int)),proc, SLOT(deleteLater())); //will free proc after the process has ended
	connect(proc, SIGNAL(processNotification(QString)), SIGNAL(processNotification(QString)));
	if (singleInstance){
		connect(proc, SIGNAL(finished(int)), SLOT(singleInstanceCompleted(int))); //will free proc after the process has ended
		runningCommands.insert(cmd, proc);
	}
	if(!mainFile.isEmpty())
		proc->setWorkingDirectory(QFileInfo(mainFile).absolutePath());

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
#ifdef Q_WS_WIN
	static const QString SEP = ";";
#else
	static const QString SEP = ":";
#endif
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
void BuildManager::preview(const QString &preamble, const QString &text, int line, const QString& masterFile, QTextCodec *outputCodec){
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
				ProcessX *p = newProcess(QString("%1 -interaction=nonstopmode -ini \"&latex %3 \\dump\"").arg(getLatexCommandExecutable(CMD_LATEX)).arg(preambleFormatFile), tf->fileName()); //no delete! goes automatically
				addLaTeXInputPaths(p, addPaths);
				p->setProperty("preamble", preamble_mod);
				p->setProperty("preambleFile", preambleFormatFile);
				connect(p,SIGNAL(finished(int)),this,SLOT(preamblePrecompileCompleted(int)));
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
	out << "\n\\begin{document}\n" << text << "\n\\end{document}\n";
	// prepare commands/filenames
	QFileInfo fi(*tf);
	QString ffn=fi.absoluteFilePath();
	previewFileNames.append(ffn);
	previewFileNameToText.insert(ffn,QPair<QString,int>(text, line));
	tf->setAutoRemove(false);
	tf->close();
	delete tf; // tex file needs to be freed
	// start conversion
	// tex -> dvi
	ProcessX *p1 = newProcess(CMD_LATEX,ffn); //no delete! goes automatically
	addLaTeXInputPaths(p1, addPaths);
	connect(p1,SIGNAL(finished(int)),this,SLOT(latexPreviewCompleted(int)));
	p1->startCommand();

	if (dvi2pngMode==DPM_DVIPNG_FOLLOW) {
		p1->waitForStarted();
		// dvi -> png
		//follow mode is a tricky features which allows dvipng to run while tex isn't finished
		ProcessX *p2 = newProcess(CMD_DVIPNG,"--follow", ffn);
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

QString BuildManager::editCommandList(const QString& list){
	QStringList names, commands;
	for (int i=CMD_LATEX; i <= CMD_ASY; i++) {
		names.append(commandDisplayName((LatexCommand)(i)));
		commands.append(getLatexCommandForDisplay((LatexCommand)(i)));
	}

	UserQuickDialog uqd(0, names, commands);
	uqd.setCommandList(list);
	if (uqd.exec() == QDialog::Accepted) return uqd.getCommandList();
	else return list;
}

QList<BuildManager::LatexCommand> BuildManager::getQuickBuildCommands(int mode){
	switch (mode) {
	case 1: return QList<LatexCommand>() << BuildManager::CMD_LATEX << BuildManager::CMD_DVIPS << BuildManager::CMD_VIEWPS;
	case 2: return QList<LatexCommand>() << BuildManager::CMD_LATEX << BuildManager::CMD_VIEWDVI;
	case 3: return QList<LatexCommand>() << BuildManager::CMD_PDFLATEX << BuildManager::CMD_VIEWPDF;
	case 4: return QList<LatexCommand>() << BuildManager::CMD_LATEX << BuildManager::CMD_DVIPDF << BuildManager::CMD_VIEWPDF;
	case 5: return QList<LatexCommand>() << BuildManager::CMD_LATEX << BuildManager::CMD_DVIPS << BuildManager::CMD_PS2PDF << BuildManager::CMD_VIEWPDF;
	case 6: return QList<LatexCommand>() << BuildManager::CMD_LATEX << BuildManager::CMD_ASY << BuildManager::CMD_LATEX << BuildManager::CMD_VIEWDVI;
	case 7: return QList<LatexCommand>() << BuildManager::CMD_PDFLATEX << BuildManager::CMD_ASY << BuildManager::CMD_PDFLATEX << BuildManager::CMD_VIEWPDF;
		//case 8/user: below
	}
	Q_ASSERT(false);
	return QList<LatexCommand>();
}

int BuildManager::getQuickBuildCommandCount(){
	return 7;
}

QString BuildManager::getQuickBuildCommandText(int mode){
	if (mode == 8) return tr("User : (% : filename without extension)");
	QList<LatexCommand> commands = getQuickBuildCommands(mode);
	QString result;
	foreach (const LatexCommand cmd, commands) result += (result.isEmpty()?"":" + ") + commandDisplayName(cmd);
	return result;
}

void BuildManager::singleInstanceCompleted(int status){
	Q_UNUSED(status);
	ProcessX* procX = qobject_cast<ProcessX*>(sender());
	REQUIRE(procX);
	runningCommands.remove(procX->getCommandLine());
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
		ProcessX *p2 = newProcess(CMD_DVIPNG,p1->getFile());
		if (!p1->overrideEnvironment().isEmpty()) p2->setOverrideEnvironment(p1->overrideEnvironment());
		connect(p2,SIGNAL(finished(int)),this,SLOT(conversionPreviewCompleted(int)));
		p2->startCommand();
	}
	if (dvi2pngMode==DPM_DVIPS_GHOSTSCRIPT) {
		ProcessX* p1=qobject_cast<ProcessX*> (sender());
		if (!p1) return;
		// dvi -> ps
		ProcessX *p2 = newProcess(CMD_DVIPS,"-E",p1->getFile());
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
	ProcessX *p3 = newProcess(CMD_GHOSTSCRIPT,"-q -dSAFER -dBATCH -dNOPAUSE -sDEVICE=png16m -dEPSCrop -sOutputFile=\"?am)1.png\"",p2->getFile());
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
		emit previewAvailable(fn,previewFileNameToText[processedFile].first,previewFileNameToText[processedFile].second);
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
	if (!ddePseudoURL.startsWith("dde://")) return false;
	ddePseudoURL.remove(0,6);

	if (ddePseudoURL.length() < 3) return false;
	QString serviceEXEPath;
	if (ddePseudoURL[1] == ':' || (ddePseudoURL[0] == '"' && ddePseudoURL[2] == ':')) { //extended dde of format dde://<path>:control/commands
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
		QProcess* p = new QProcess(QCoreApplication::instance()); //application is parent, to close the service if tmx is closed
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
		QProcess(parent), cmd(assignedCommand.trimmed()), file(fileToCompile), started(false), stdoutEnabled(true), mBuffer(0) {
	if (cmd.mid(cmd.lastIndexOf(">") + 1).trimmed() == "/dev/null" )  {
		cmd = cmd.left(cmd.lastIndexOf(">")).trimmed();
		stdoutEnabled = false;
	}
	connect(this, SIGNAL(started()), SLOT(onStarted()));
	connect(this, SIGNAL(finished(int)), SLOT(onFinished(int)));
	connect(this, SIGNAL(error(QProcess::ProcessError)), SLOT(onError(QProcess::ProcessError)));
}
void ProcessX::startCommand() {
	#ifdef Q_WS_WIN
	if (cmd.startsWith("dde://")) {
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

	QProcess::start(cmd);

#ifdef PROFILE_PROCESSES
	connect(this, SIGNAL(finished(int)), SLOT(finished()));
	time.start();
#endif
}
bool ProcessX::waitForStarted(int timeOut){
	if (started) return true;
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
	stdoutEnabled = show;
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
QString ProcessX::readAllStandardOutputStr(){return QString(QProcess::readAllStandardOutput());}
QString ProcessX::readAllStandardErrorStr(){return QString(QProcess::readAllStandardError());}
bool ProcessX::waitForFinished ( int msecs ){return QProcess::waitForFinished(msecs);}


void ProcessX::onStarted(){
	if (started) return; //why am I called twice?
	started=true;
	emit processNotification(tr("Process started: %1").arg(cmd));
}

void ProcessX::onError(ProcessError error){
	if (error == FailedToStart)
		emit processNotification(tr("Error: Could not start the command: %1").arg(cmd));
	else if (error == Crashed)
		emit processNotification(tr("Error: Command crashed: %1").arg(cmd));
}

void ProcessX::onFinished(int error){
	if (error)
                emit processNotification(tr("Process exited with error(s)"));
	else
                emit processNotification(tr("Process exited normally"));
}

#ifdef PROFILE_PROCESSES
void ProcessX::finished(){
	qDebug() << "Process: "<<qPrintable(cmd)<< "  Running time: " << time.elapsed();
}
#endif
