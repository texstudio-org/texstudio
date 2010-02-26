#include "buildmanager.h"

#include "smallUsefulFunctions.h"

#ifdef Q_WS_WIN
#include "windows.h"
#endif

BuildManager::BuildManager()
#ifdef Q_WS_WIN
		:
		pidInst(0)
#endif
{
}
BuildManager::~BuildManager() {
	//remove preview file names
	foreach(QString elem,previewFileNames){
		QDir currentDir(QFileInfo(elem).absoluteDir());
		elem=QFileInfo(elem).completeBaseName();
		QStringList files;
		files = currentDir.entryList(QStringList(elem+"*"),
								  QDir::Files | QDir::NoSymLinks);
		foreach(QString file,files) QFile::remove(currentDir.absolutePath()+"/"+file);
	}
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
		default: return QString("_unknown_cmd_%1").arg((int)cmd);
	}
}

QString BuildManager::parseExtendedCommandLine(QString str, const QFileInfo &mainFile, const QFileInfo &currentFile, int currentline) {
	str=str+" "; //end character  so str[i++] is always defined 
	QString result;
	result.reserve(2*str.length());
	for (int i=0; i<str.size(); i++) {
		if (str.at(i)==QChar('%')) {
			if (str.at(i+1)==QChar('%')) result+=str.at(++i);
			else result+="\""+mainFile.completeBaseName()+"\"";
		} else if (str.at(i)==QChar('@')) {
			if (str.at(i+1)==QChar('@')) result+=str.at(++i);
			else result+=QString::number(currentline);
		} else if (str.at(i)==QChar('?')) {
			if (str.at(++i)==QChar('?')) result+="?";
			else {
				QString command;
				int endMode=0;
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
					} else if (str.at(i)==QChar('.')) {
						endMode=4;
						break;
					}
					command+=str.at(i);
					i++;
				}
				bool useCurrentFile=command.startsWith("c:");
				const QFileInfo& selectedFile=useCurrentFile?currentFile:mainFile;
				if (useCurrentFile) command=command.mid(2);
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
				result+=command;
			}
		} else result+=str.at(i);
	}
	//  QMessageBox::information(0,"",str+"->"+result,0);
	if (result.endsWith(" ")) result.chop(1); //remove additional end character
	return result;
}

QString BuildManager::parseExtendedCommandLine(QString str, const QFileInfo &mainFile, int currentLine) {
		return parseExtendedCommandLine(str, mainFile, mainFile, currentLine);
}


QString BuildManager::findFileInPath(QString fileName) {
	QStringList env= QProcess::systemEnvironment();    //QMessageBox::information(0,env.join("  \n"),env.join("  \n"),0);
	int i=env.indexOf(QRegExp("^PATH=.*", Qt::CaseInsensitive));
	if (i==-1) return "";
	QString path=env[i].mid(5); //skip path=
	#ifdef Q_WS_WIN
	if (!fileName.contains('.')) fileName+=".exe"; 
	QStringList paths=path.split(";"); //windows
	#else
	QStringList paths=path.split(":"); //linux
	#endif
	foreach(QString p, paths)
		if (p.endsWith("/") && QFileInfo(p+fileName).exists()) return (p+fileName);
		else if (p.endsWith("\\") && QFileInfo(p+fileName).exists()) return (p+fileName);
		else if (QFileInfo(p+"/"+fileName).exists()) return (p+"\\"+fileName);
	return "";
}

#ifdef Q_WS_WIN
typedef BOOL (* AssocQueryStringAFunc)(DWORD, DWORD, char*, char*, char*, DWORD*);
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
QString getMiKTeXBinPath() {
	QSettings reg("HKEY_CURRENT_USER\\Software", QSettings::NativeFormat);
	QString mikPath = reg.value("MiK/MikTeX/CurrentVersion/MiKTeX/Install Root", "").toString();
	if (mikPath.isEmpty()) return "";
	if (!mikPath.endsWith("\\") && !mikPath.endsWith("/"))
		mikPath+="\\"; //windows
	return mikPath+"miktex\\bin\\";
}
QString findGhostscriptDLL() {
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
	if (i==-1) return ""; //not found
	QString dll=env[i].mid(7); //skip gs_dll=
	return dll;
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
			return mikPath+fileName+options; //found
#endif
#ifdef Q_WS_MACX
		// comments from texmaker: /usr/local/teTeX/bin/i386-apple-darwin-current
		// /usr/local/teTeX/bin/powerpc-apple-darwin-current
		// /usr/texbin MACTEX/TEXLIVE2007
		if (QFileInfo("/usr/bin/texbin/"+fileName).exists())
			return "/usr/bin/texbin/"+fileName+options;
		if (QFileInfo("/usr/local/bin/"+fileName).exists())
			return "/usr/local/bin/"+fileName+options;
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
		case CMD_VIEWDVI: return "open %.dvi";
		case CMD_VIEWPS: return "open %.ps";
		case CMD_VIEWPDF: return "open %.pdf";
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
				if (def.endsWith("\"?am.dvi\"")) def.replace("\"?am.dvi\"",yapOptions);
				else if (def.endsWith("?am.dvi")) def.replace("?am.dvi",yapOptions);
			}
			return def;
		}
		def=searchBaseCommand("yap",yapOptions);//,true);
		if (!def.isEmpty()) return def;
		else if (QFileInfo("C:/Program Files/MiKTeX 2.8/miktex/bin/yap.exe").exists())
			return "\"C:/Program Files/MiKTeX 2.8/miktex/bin/yap.exe\" " + yapOptions;
		else if (QFileInfo("C:/Program Files/MiKTeX 2.7/miktex/bin/yap.exe").exists())
			return "\"C:/Program Files/MiKTeX 2.7/miktex/bin/yap.exe\" " + yapOptions;
		else if (QFileInfo("C:/Program Files/MiKTeX 2.5/miktex/bin/yap.exe").exists())
			return "\"C:/Program Files/MiKTeX 2.5/miktex/bin/yap.exe\" " + yapOptions;
		else if (QFileInfo("C:/texmf/miktex/bin/yap.exe").exists())
			return "C:/texmf/miktex/bin/yap.exe " + yapOptions;
		else break;
	}
	case CMD_VIEWPS: {
		QString def=W32_FileAssociation(".ps");
		if (!def.isEmpty())
			return def;
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
		if (QFileInfo("\"C:/Program Files/Ghostgum/gsview/gsview32.exe\"").exists())
			return "\"C:/Program Files/Ghostgum/gsview/gsview32.exe\" -e \"?am.ps\"";
		break;
	}
	case CMD_VIEWPDF: {
		QString def=W32_FileAssociation(".pdf");
		if (!def.isEmpty())
			return def;
		else if (QFileInfo("C:/Program Files/Adobe/Reader 9.0/Reader/AcroRd32.exe").exists())
			return "\"C:/Program Files/Adobe/Reader 9.0/Reader/AcroRd32.exe\" \"?am.pdf\"";
		else if (QFileInfo("C:/Program Files/Adobe/Reader 8.0/Reader/AcroRd32.exe").exists())
			return "\"C:/Program Files/Adobe/Reader 8.0/Reader/AcroRd32.exe\" \"?am.pdf\"";
		else break;
	}
	case CMD_GHOSTSCRIPT: {
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
		case 3:	return "kdvi %.dvi";
		case 4:	return "okular %.dvi";
		default:return "evince %.dvi";
		};
	case CMD_VIEWPS:
		switch (x11desktop_env()) {
		case 3: return "kghostview %.ps";
		case 4:	return "okular %.ps";
		default:return "evince %.ps";
		};
	case CMD_VIEWPDF:
		switch (x11desktop_env()) {
		case 3: return "kpdf %.pdf";
		case 4:	return "okular %.pdf";
		default:return "evince %.pdf";
		};
	default:;
	}
#endif
	return "";
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
		/*case CMD_VIEWDVI: case CMD_VIEWPS:  case CMD_VIEWPDF: 
			viewer are platform dependent*/
		case CMD_GHOSTSCRIPT: return "gs";
		default: return "";
	}
} 
QString BuildManager::defaultCommandOptions(LatexCommand cmd){
	switch (cmd){
		case CMD_LATEX: return "-interaction=nonstopmode %.tex";
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
		case CMD_PDFLATEX: return "-interaction=nonstopmode %.tex";
		case CMD_DVIPDF: return "%.dvi";
		case CMD_METAPOST: return "--interaction nonstopmode ?me)";
		case CMD_VIEWDVI: return "%.dvi";
		case CMD_VIEWPS: return "%.ps";
		case CMD_VIEWPDF: return "%.pdf";
		case CMD_SVN: return "";
		case CMD_SVNADMIN: return "";
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
		case CMD_BIBTEX: return "Bibtex";
		case CMD_PDFLATEX: return "PdfLaTeX";
		case CMD_DVIPDF: return "DviPdf";
		case CMD_METAPOST: return "Metapost";
		case CMD_VIEWDVI: return tr("Dvi Viewer");
		case CMD_VIEWPS: return tr("Ps Viewer");
		case CMD_VIEWPDF: return tr("Pdf Viewer");
		case CMD_GHOSTSCRIPT: return "Ghostscript";
		case CMD_SVN: return "SVN";
		case CMD_SVNADMIN: return "SVNADMIN";
		default: return "";
	}
}
void BuildManager::readSettings(const QSettings &settings){
	for (LatexCommand i=CMD_LATEX; i < CMD_MAXIMUM_COMMAND_VALUE;++i)
		setLatexCommand(i,settings.value(cmdToConfigString(i), "<default>").toString());
	if (settings.contains("Tools/Quick Mode")) 
		quickmode=settings.value("Tools/Quick Mode",1).toInt(); //load stored value
	else {
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
		else quickmode=1; //texmaker default
	}	
	if (settings.contains("Tools/Dvi2Png Mode")) 
		dvi2pngMode=(Dvi2PngMode) settings.value("Tools/Dvi2Png Mode",1).toInt(); //load stored value
	else {
		if (hasLatexCommand(CMD_DVIPNG)) dvi2pngMode = DPM_DVIPNG_FOLLOW; //best/fastest mode
		else if (hasLatexCommand(CMD_DVIPS) && hasLatexCommand(CMD_GHOSTSCRIPT)) dvi2pngMode = DPM_DVIPS_GHOSTSCRIPT; //compatible mode
		else dvi2pngMode = DPM_DVIPNG_FOLLOW; //won't work
	}
}
void BuildManager::saveSettings(QSettings &settings){
	for (LatexCommand i=CMD_LATEX; i < CMD_MAXIMUM_COMMAND_VALUE;++i)
		settings.setValue(cmdToConfigString(i),commands[i]);
	settings.setValue("Tools/Quick Mode",quickmode);
	settings.setValue("Tools/Dvi2Png Mode",dvi2pngMode);
}

void BuildManager::setLatexCommand(LatexCommand cmd, const QString &cmdString){
	if (cmdString=="<default>") commands[cmd]=guessCommandName(cmd);
	else if (cmdString==tr("<unknown>")) commands[cmd]="";
	else commands[cmd] = cmdString;
}

QString BuildManager::getLatexCommand(LatexCommand cmd){
	return commands[cmd];
}
QString BuildManager::getLatexCommandForDisplay(LatexCommand cmd){
	if (commands[cmd] == "") return tr("<unknown>");
	else return commands[cmd];
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

ProcessX* BuildManager::newProcess(const QString &unparsedCommandLine, const QString &mainFile, const QString &currentFile, int currentLine){
	QFileInfo mfi(mainFile);
	QFileInfo cfi;
	if (mainFile==currentFile) cfi=mfi;
	else cfi=QFileInfo(currentFile);
	QString cmd=BuildManager::parseExtendedCommandLine(unparsedCommandLine,mfi,cfi,currentLine);	
	ProcessX* proc = new ProcessX(this, cmd, mainFile);
	connect(proc, SIGNAL(finished(int)),proc, SLOT(deleteLater())); //will free proc after the process has ended
	proc->setWorkingDirectory(mfi.absolutePath());
/* this was added in texmaker 1.9.9, not sure if it is useful
+#ifdef Q_WS_MACX
+#if (QT_VERSION >= 0x0406)
+QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
+env.insert("PATH", env.value("PATH") + ":/usr/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/texbin:/sw/bin");
+proc->setProcessEnvironment(env);
+#endif
+#endif
+*/
	return proc;
}
ProcessX* BuildManager::newProcess(const QString &unparsedCommandLine, const QString &mainFile, int currentLine){
	return newProcess(unparsedCommandLine, mainFile, mainFile, currentLine);
}

QTemporaryFile* BuildManager::temporaryTexFile(){
	QTemporaryFile *temp=new QTemporaryFile(QDir::tempPath ()+"/texmakerx_XXXXXX.tex");
	temp->open();
	temp->setAutoRemove(false);
	return temp;
}

//there are 3 ways to generate a preview png:
//1. latex is called => dvipng is called after latex finished and converts the dvi
//2. latex is called and dvipng --follow is called at the same time, and will manage the wait time on its own
//3. latex is called => dvips converts .dvi to .ps => ghostscript is called and created final png
//Then ghostscript to convert it to 
void BuildManager::preview(const QString &preamble, const QString &text, QTextCodec *outputCodec){
    // write to temp file
	QTemporaryFile *tf=new QTemporaryFile(QDir::tempPath()+"/XXXXXX.tex");
	tf->open();
	QTextStream out(tf);
	if (outputCodec) out.setCodec(outputCodec);
	out << preamble 
		<< "\n\\begin{document}\n" 
		<< text
		<< "\n\\end{document}\n";
	tf->close();
	// prepare commands/filenames
	QString ffn=QFileInfo(*tf).absoluteFilePath();
	previewFileNames.append(ffn);
	previewFileNameToText.insert(ffn,text);
	tf->setAutoRemove(false);
	delete tf; // tex file needs to be freed
	// start conversion
	// preliminary code
	// tex -> dvi
	ProcessX *p1 = newProcess(CMD_LATEX,ffn); //no delete! goes automatically
	connect(p1,SIGNAL(finished(int)),this,SLOT(latexPreviewCompleted(int)));
	p1->startCommand();
	
	if (dvi2pngMode==DPM_DVIPNG_FOLLOW) {
		p1->waitForStarted();
		// dvi -> png
		//follow mode is a tricky features which allows dvipng to run while tex isn't finished
		ProcessX *p2 = newProcess(CMD_DVIPNG,"--follow", ffn);
		connect(p2,SIGNAL(finished(int)),this,SLOT(conversionPreviewCompleted(int)));
		p2->startCommand();
	}
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
		connect(p2,SIGNAL(finished(int)),this,SLOT(conversionPreviewCompleted(int)));
		p2->startCommand();	
	}
	if (dvi2pngMode==DPM_DVIPS_GHOSTSCRIPT) {
		ProcessX* p1=qobject_cast<ProcessX*> (sender());
		if (!p1) return;
		// dvi -> ps
		ProcessX *p2 = newProcess(CMD_DVIPS,"-E",p1->getFile());
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
	ProcessX *p3 = newProcess(CMD_GHOSTSCRIPT,"-q -dSAFER -dBATCH -dNOPAUSE -sDEVICE=png16m -dEPSCrop -sOutputFile=\"?am)1.png\"  \"?am.ps\"",p2->getFile());
	connect(p3,SIGNAL(finished(int)),this,SLOT(conversionPreviewCompleted(int)));
	p3->startCommand();	
}

void BuildManager::conversionPreviewCompleted(int status){
	Q_UNUSED(status);
	ProcessX* p2=qobject_cast<ProcessX*> (sender());
	if (!p2) return;
	// put image in preview
	QString processedFile=p2->getFile();
	QString fn=parseExtendedCommandLine("?am)1.png",processedFile);
	if(QFileInfo(fn).exists()) 
		emit previewAvailable(fn,previewFileNameToText[processedFile]);
}


//DDE things
#ifdef Q_WS_WIN
#include "windows.h"
bool BuildManager::executeDDE(QString ddePseudoURL) {
	//parse URL
	if (!ddePseudoURL.startsWith("dde://")) return false;
	ddePseudoURL.remove(0,6);
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

	QCoreApplication::processEvents();

	DdeFreeStringHandle(pidInst, hszService);
	DdeFreeStringHandle(pidInst, hszTopic);
	if (!hConv) return false;

	//execute requests
	foreach(QString s, commands) {
		QString temp=("["+s.trimmed());
		QByteArray ba= temp.toLocal8Bit();
		HDDEDATA req= DdeCreateDataHandle(pidInst, (LPBYTE) ba.data(), ba.size()+1, 0, 0, CF_TEXT, 0);
		if (req) {
			HDDEDATA recData=DdeClientTransaction((BYTE*)req, (DWORD)-1, hConv, 0, 0, XTYP_EXECUTE, 1000, 0);
			DdeFreeDataHandle(req);
			if (recData) DdeFreeDataHandle(recData);
		}
		//else QMessageBox::information(0,"TexMakerX",QObject::tr("DDE command %1 failed").arg("["+s),0); //break; send all commands
	}

	QCoreApplication::processEvents();

	//disconnect
	DdeDisconnect(hConv);

	QCoreApplication::processEvents();

	return true;
}
#endif

ProcessX::ProcessX(BuildManager* parent, const QString &assignedCommand, const QString& fileToCompile):
		QProcess(parent), cmd(assignedCommand), file(fileToCompile), started(false), mBuffer(0) {
}
void ProcessX::startCommand() {
	#ifdef Q_WS_WIN
	if (cmd.startsWith("dde://")) {
		started=true;
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
