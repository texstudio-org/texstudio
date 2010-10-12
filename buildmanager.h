#ifndef BUILDMANAGER_H
#define BUILDMANAGER_H

#include "mostQtHeaders.h"

class ProcessX;

//all the build things in texmaker.cpp are going to be moved to this place, but it doesn't have high priority
class ConfigManagerInterface;
class BuildManager: public QObject {
	Q_OBJECT
public:
	
	BuildManager();
	~BuildManager();
	enum LatexCommand {
		CMD_LATEX=1,
		CMD_DVIPS,
		CMD_PS2PDF,
		CMD_MAKEINDEX,
		CMD_BIBTEX,
		CMD_PDFLATEX,
		CMD_DVIPDF,
		CMD_DVIPNG,
		CMD_METAPOST,
		CMD_VIEWDVI,
		CMD_VIEWPS,
		CMD_VIEWPDF,
		CMD_GHOSTSCRIPT,
		CMD_ASY,
		CMD_USER_QUICK,
		CMD_USER_PRECOMPILE,
		CMD_SVN,
		CMD_SVNADMIN,
		CMD_MAXIMUM_COMMAND_VALUE
	};
	static QString findFileInPath(QString fileName);
	static QString cmdToConfigString(LatexCommand cmd);
	static QString parseExtendedCommandLine(QString str, const QFileInfo &mainFile, const QFileInfo &currentFile, int currentLine=0);
	static QString parseExtendedCommandLine(QString str, const QFileInfo &mainFile, int currentLine=0);	
	static QString guessCommandName(LatexCommand cmd);
	static QString baseCommandName(LatexCommand cmd); //returns a platform independent base name if it exists
	static QString defaultCommandOptions(LatexCommand cmd);
	static QString commandDisplayName(LatexCommand cmd);
	static QString TMX_INTERNAL_PDF_VIEWER;

	void registerOptions(ConfigManagerInterface& cmi);
	void readSettings(const QSettings &settings);

	void setLatexCommand(LatexCommand cmd, const QString &cmdString);//sets a command (accepts tr("<unknown>"))
	QString getLatexCommand(LatexCommand cmd); //returns the program+args for the command
	QString getLatexCommandForDisplay(LatexCommand cmd); //returns program or tr("<unknown>") if no command exists
	bool hasLatexCommand(LatexCommand cmd); //returns if the command can be called
	
	//creates a process object for a predefined command, which will operate on the given file and line number
	ProcessX* newProcess(LatexCommand cmd, const QString &fileToCompile, int currentLine=0);
	//like above, but will add (TODO: override) the given parameters (they will be parsed, e.g % will replaced by the file name) 
	ProcessX* newProcess(LatexCommand cmd, const QString &additionalParameters, const QString &fileToCompile, int currentLine=0);
	//creates a process object with the given command line (after it is changed by an implcit call to parseExtendedCommandLine)
	ProcessX* newProcess(const QString &unparsedCommandLine, const QString &mainFile, const QString &currentFile, int currentLine=0, bool singleInstance = false);
	ProcessX* newProcess(const QString &unparsedCommandLine, const QString &mainFile, int currentLine=0);
	
	static QString createTemporaryFileName(); //don't forget to remove the file!
					
	void preview(const QString &preamble, const QString &text, QTextCodec *outputCodec=0);

	QString editCommandList(const QString& list);

	int quickmode;
	enum Dvi2PngMode { DPM_DVIPNG, DPM_DVIPNG_FOLLOW, DPM_DVIPS_GHOSTSCRIPT};
	Dvi2PngMode dvi2pngMode;
	enum SaveFilesBeforeCompiling {SFBC_ALWAYS, SFBC_ONLY_CURRENT_OR_NAMED, SFBC_ONLY_NAMED};
	SaveFilesBeforeCompiling saveFilesBeforeCompiling;
private slots:	
	void singleInstanceCompleted(int status);
	void latexPreviewCompleted(int status);
	void dvi2psPreviewCompleted(int status);
	void conversionPreviewCompleted(int status); 
	
signals:
	void previewAvailable(const QString& filename, const QString& text);
private:
	friend class ProcessX;
	QStringList previewFileNames;
	QMap<QString, ProcessX*> runningCommands;
	QMap<QString, QString> previewFileNameToText;
	QHash<LatexCommand, QString> commands;
#ifdef Q_WS_WIN
	unsigned long int pidInst;
	bool executeDDE(QString ddePseudoURL);
#endif
};

inline void operator++(BuildManager::LatexCommand& cmd){
	cmd = (BuildManager::LatexCommand)((int)cmd + 1);
}

//this process can handle dde and normal commands
class ProcessX: public QProcess{
	Q_OBJECT
public:
	ProcessX(BuildManager* parent=0, const QString &assignedCommand="", const QString& fileToCompile="");
	void startCommand();
	bool waitForStarted(int timeOut=30000);
	const QString& getFile();
	const QString& getCommandLine();
	QString *getBuffer(){
		return mBuffer;
	}
	void setBuffer(QString *buffer) {
		mBuffer=buffer;
	}

private:
	QString cmd;
	QString file;
	bool started;
	QString *mBuffer;
};


#endif // BUILDMANAGER_H
