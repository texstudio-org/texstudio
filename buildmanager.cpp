#include "buildmanager.h"
#include <QChar>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QProcess>
#include <QTemporaryFile>

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
		default: return QString("_unknown_cmd_%1").arg((int)cmd);
	}
}

QString BuildManager::parseExtendedCommandLine(QString str, const QFileInfo &mainFile,int currentline) {
	str=str+" ";
	QString result;
	result.reserve(2*str.length());
	for (int i=0; i<str.size(); i++) {
		if (str.at(i)==QChar('%')) {
			if (str.at(++i)==QChar('%')) result+="%";
			else result+="\""+mainFile.completeBaseName()+"\"";
		} else if (str.at(i)==QChar('@')) {
			if (str.at(++i)==QChar('@')) result+="@";
			else result+=QString::number(currentline);
		}
		if (str.at(i)==QChar('?')) {
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
				//check only sane commands
				if (command=="ame") command=QDir::toNativeSeparators(mainFile.absoluteFilePath());
				else if (command=="am") {
					command=QDir::toNativeSeparators(mainFile.absoluteFilePath());
					if (mainFile.suffix()!="") command.chop(1+mainFile.suffix().length());
				} else if (command=="a") {
					command=QDir::toNativeSeparators(mainFile.absolutePath());
					if (!command.endsWith(QDir::separator())) command+=QDir::separator();
				} else if (command=="me") command=mainFile.fileName();
				else if (command=="m") command=mainFile.completeBaseName();
				else if (command=="e") command=mainFile.suffix();
				else continue; //invalid command
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
	return result;
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
QString findFileInPath(QString fileName) {
	QStringList env= QProcess::systemEnvironment();    //QMessageBox::information(0,env.join("  \n"),env.join("  \n"),0);
	int i=env.indexOf(QRegExp("^PATH=.*", Qt::CaseInsensitive));
	if (i==-1) return "";
	QString path=env[i].mid(5); //skip path=
	QStringList paths=path.split(";"); //windows
	foreach(QString p, paths)
	if (p.endsWith("/") && QFileInfo(p+fileName).exists()) return (p+fileName);
	else if (p.endsWith("\\") && QFileInfo(p+fileName).exists()) return (p+fileName);
	else if (QFileInfo(p+"\\"+fileName).exists()) return (p+"\\"+fileName);
	return "";
}
QString getMiKTeXBinPath() {
	QSettings reg("HKEY_CURRENT_USER\\Software", QSettings::NativeFormat);
	QString mikPath = reg.value("MiK/MikTeX/CurrentVersion/MiKTeX/Install Root", "").toString();
	if (mikPath.isEmpty()) return "";
	if (!mikPath.endsWith("\\") && !mikPath.endsWith("/"))
		mikPath+="\\"; //windows
	return mikPath+"miktex\\bin\\";
}
QString searchBaseCommand(QString cmd, QString options, bool mustExist=false) {
	QString fileName=cmd+".exe";
	if (findFileInPath(fileName).isEmpty()) {
		QString mikPath=getMiKTeXBinPath();
		//QMessageBox::information(0,mikPath,mikPath,0);
		if (!mikPath.isEmpty() && QFileInfo(mikPath+fileName).exists())
			return mikPath+fileName+options;
	} else return cmd+options;
	if (mustExist) return "";
	return cmd+options;
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

QString BuildManager::guessCommandName(LatexCommand cmd) {
#ifdef Q_WS_MACX
	// /usr/local/teTeX/bin/i386-apple-darwin-current
	// /usr/local/teTeX/bin/powerpc-apple-darwin-current
	// /usr/texbin MACTEX/TEXLIVE2007
	switch (cmd) {
	case CMD_LATEX:
		return "\"/usr/texbin/latex\" -interaction=nonstopmode %.tex";
	case CMD_DVIPS:
		return "\"/usr/texbin/dvips\" -o %.ps %.dvi";
	case CMD_DVIPNG:
		return "\"/usr/texbin/dvipng\" -T tight -x 12000 %.dvi";
	case CMD_PS2PDF:
		return "\"/usr/local/bin/ps2pdf\" %.ps";
	case CMD_MAKEINDEX:
		return "\"/usr/texbin/makeindex\" %.idx";
	case CMD_BIBTEX:
		return "\"/usr/texbin/bibtex\" %.aux";
	case CMD_PDFLATEX:
		return "\"/usr/texbin/pdflatex\" -interaction=nonstopmode %.tex";
	case CMD_DVIPDF:
		return "\"/usr/texbin/dvipdfm\" %.dvi";
	case CMD_METAPOST:
		return "\"/usr/texbin/mpost\" --interaction nonstopmode ?me)";
	case CMD_VIEWDVI:
		return "open %.dvi";
	case CMD_VIEWPS:
		return "open %.ps";
	case CMD_VIEWPDF:
		return "open %.pdf";
	case CMD_GHOSTSCRIPT:
		return "/usr/local/bin/gs";
	case CMD_USER_QUICK: return "latex -interaction=nonstopmode %.tex|bibtex %.aux|latex -interaction=nonstopmode %.tex|latex -interaction=nonstopmode %.tex|xdvi %.dvi";
	case CMD_USER_PRECOMPILE: return "";
	case CMD_MAXIMUM_COMMAND_VALUE: return "";
	}
#endif
#ifdef Q_WS_WIN
	switch (cmd) {
	case CMD_LATEX:
		return searchBaseCommand("latex"," -interaction=nonstopmode %.tex");
	case CMD_DVIPS:
		return searchBaseCommand("dvips"," -o %.ps %.dvi");
	case CMD_DVIPNG:
		return searchBaseCommand("dvipng"," -T tight -x 12000 %.dvi");
	case CMD_PS2PDF:
		return searchBaseCommand("ps2pdf"," %.ps");
	case CMD_MAKEINDEX:
		return searchBaseCommand("makeindex"," %.idx");
	case CMD_BIBTEX:
		return searchBaseCommand("bibtex"," %");
	case CMD_PDFLATEX:
		return searchBaseCommand("pdflatex"," -interaction=nonstopmode %.tex");
	case CMD_DVIPDF:
		return searchBaseCommand("dvipdfm"," %.dvi");
	case CMD_METAPOST:
		return searchBaseCommand("mpost"," --interaction nonstopmode ?me)");
	case CMD_VIEWDVI: {
		const QString yapOptions = " -1 -s @?ame \"?am.dvi\"";
		QString def=W32_FileAssociation(".dvi");
		if (!def.isEmpty()) {
			if (def.contains("yap.exe")) {
				def=def.trimmed();
				if (def.endsWith("\"?am.dvi\"")) def.replace("\"?am.dvi\"",yapOptions);
				else if (def.endsWith("?am.dvi")) def.replace("?am.dvi",yapOptions);
			}
			return def;
		}
		def=searchBaseCommand("yap",yapOptions,true);
		if (!def.isEmpty()) return def;
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
		else if (QFileInfo("\"C:/Program Files/Ghostgum/gsview/gsview32.exe\"").exists())
			return "\"C:/Program Files/Ghostgum/gsview/gsview32.exe\" \"?am.ps\"";
		else break;
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
		if (dll.endsWith("gswin32c.exe")) return dll;
		else if (QFileInfo("C:/Program Files/gs/gs8.63/bin/gswin32c.exe").exists())  //old behaviour
			return "\"C:/Program Files/gs/gs8.63/bin/gswin32c.exe\"";
		else if (QFileInfo("C:/Program Files/gs/gs8.61/bin/gswin32c.exe").exists())
			return "\"C:/Program Files/gs/gs8.61/bin/gswin32c.exe\"";
		else break;
	}
	case CMD_USER_QUICK: return "latex -interaction=nonstopmode %.tex|bibtex %.aux|latex -interaction=nonstopmode %.tex|latex -interaction=nonstopmode %.tex|xdvi %.dvi";
	case CMD_USER_PRECOMPILE: return "";
	case CMD_MAXIMUM_COMMAND_VALUE: return "";
	}
#endif
#ifdef Q_WS_X11
// xdvi %.dvi  -sourceposition @:%.tex
// kdvi "file:%.dvi#src:@ %.tex"
	switch (cmd) {
	case CMD_LATEX:
		return "latex -interaction=nonstopmode %.tex";
	case CMD_DVIPS:
		return "dvips -o %.ps %.dvi";
	case CMD_DVIPNG:
		return "dvipng -T tight -x 12000 %.dvi";
	case CMD_PS2PDF:
		return "ps2pdf %.ps";
	case CMD_MAKEINDEX:
		return "makeindex %.idx";
	case CMD_BIBTEX:
		return "bibtex %.aux";
	case CMD_PDFLATEX:
		return "pdflatex -interaction=nonstopmode %.tex";
	case CMD_DVIPDF:
		return "dvipdfm %.dvi";
	case CMD_METAPOST:
		return "mpost --interaction nonstopmode ?me)";
	case CMD_VIEWDVI:
		switch (x11desktop_env()) {
		case 3:
			return "kdvi %.dvi";
		case 4:
			return "okular %.dvi";
		default:
			return "evince %.dvi";
		};
	case CMD_VIEWPS:
		switch (x11desktop_env()) {
		case 3:
			return "kghostview %.ps";
		case 4:
			return "okular %.ps";
		default:
			return "evince %.ps";
		};
	case CMD_VIEWPDF:
		switch (x11desktop_env()) {
		case 3:
			return "kpdf %.pdf";
		case 4:
			return "okular %.pdf";
		default:
			return "evince %.pdf";
		};
	case CMD_GHOSTSCRIPT:
		return "gs";
	case CMD_USER_QUICK: return "latex -interaction=nonstopmode %.tex|bibtex %.aux|latex -interaction=nonstopmode %.tex|latex -interaction=nonstopmode %.tex|xdvi %.dvi";
	case CMD_USER_PRECOMPILE: return "";
	case CMD_MAXIMUM_COMMAND_VALUE: return "";
	}
#endif
	return "";
}

#ifdef Q_WS_WIN
#include "windows.h"

void BuildManager::readSettings(const QSettings &settings){
	for (LatexCommand i=CMD_LATEX; i < CMD_MAXIMUM_COMMAND_VALUE;++i)
		setLatexCommand(i,settings.value(cmdToConfigString(i), "<default>").toString());
}
void BuildManager::saveSettings(QSettings &settings){
	for (LatexCommand i=CMD_LATEX; i < CMD_MAXIMUM_COMMAND_VALUE;++i)
		settings.setValue(cmdToConfigString(i),commands[i]);
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

ProcessX* BuildManager::newProcess(LatexCommand cmd, const QString &fileToCompile, int currentLine){
	return newProcess(getLatexCommand(cmd), fileToCompile, currentLine);
}
ProcessX* BuildManager::newProcess(const QString &unparsedCommandLine, const QString &fileToCompile, int currentLine){
	QFileInfo fi(fileToCompile);
	QString cmd=BuildManager::parseExtendedCommandLine(unparsedCommandLine,fi,currentLine);	
	ProcessX* proc = new ProcessX(this, cmd, fileToCompile);
	connect(proc, SIGNAL(finished(int)),proc, SLOT(deleteLater())); //will free proc after the process has ended
	proc->setWorkingDirectory(fi.absolutePath());
	return proc;
}

QTemporaryFile* BuildManager::temporaryTexFile(){
	QTemporaryFile *temp=new QTemporaryFile(QDir::tempPath ()+"/texmakerx_XXXXXX.tex");
	temp->open();
	temp->setAutoRemove(false);
	return temp;
}

//the preview works in 3 steps.
//First latex is called
//Then dvips to convert it to ps
//Then ghostscript to convert it to 
void BuildManager::preview(const QString &preamble, const QString &text){
	if (getLatexCommand(CMD_LATEX)=="" || getLatexCommand(CMD_GHOSTSCRIPT)=="") 
		return;  //they are needed for preview
	QTemporaryFile *file = temporaryTexFile();
	//file.
	ProcessX * proc = newProcess(CMD_LATEX,file->fileName());
	delete file; //don't deletes the file
	connect(proc,SIGNAL(finished(int)),this, SLOT(latexPreviewCompleted(int)));
	proc->startCommand();
	
}

void BuildManager::latexPreviewCompleted(int status){
//	ProcessX* proc=qobject_cast<ProcessX*>(sender());
	
}
void BuildManager::conversionPreviewCompleted(int status){
}


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
		QProcess(parent), cmd(assignedCommand), file(fileToCompile), started(false) {
}
void ProcessX::startCommand() {
	#ifdef Q_WS_WIN
	if (cmd.startsWith("dde://")) {
		started=true;
		BuildManager* manager = qobject_cast<BuildManager*>(parent());
		if (!manager) return;
		bool ok = manager->executeDDE(cmd);
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
