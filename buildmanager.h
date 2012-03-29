#ifndef BUILDMANAGER_H
#define BUILDMANAGER_H

#include "mostQtHeaders.h"

class ProcessX;

struct PreviewSource{
	QString text;
	int fromLine, toLine;
	PreviewSource(){}
	PreviewSource(const QString& text, int fromLine, int toLine):
	       text(text), fromLine(fromLine), toLine(toLine){}
};

enum LatexCompileResult {
	LCR_NORMAL = 0,
	LCR_ERROR,
	LCR_RERUN,
	LCR_RERUN_WITH_BIBLIOGRAPHY
};
Q_DECLARE_METATYPE(LatexCompileResult);

enum RunCommandFlag{
	RCF_SHOW_STDOUT = 1,    //bibliography command (=> show stdout)
	RCF_LATEX_COMPILER = 4, //latex command, show the log and rerun if there are errors
	RCF_CHANGE_PDF = 16,    //pdflatex (=> lock pdf)
	RCF_SINGLE_INSTANCE = 8,//viewer (=> start only once)
};
Q_DECLARE_FLAGS(RunCommandFlags, RunCommandFlag);

struct CommandToRun {
	QString command;
	QString parentCommand;
	RunCommandFlags flags;
	CommandToRun();
	CommandToRun(const QString& cmd);
};

struct ExpandedCommands {
	QString primaryCommand;
	QList<CommandToRun> commands;
};

typedef QString (*GuessCommandLineFunc) ();
struct CommandInfo {
	CommandInfo();
	QString id;
	QString commandLine;
	
	QString defaultArgs;
	QString displayName;
	
	QStringList metaSuggestionList;
	
	QString guessCommandLine() const; 
	//sets a command (accepts tr("<unknown>"))
	void setCommandLine(const QString& newCmd);
	
	QString getPrettyCommand() const;
private:
	friend class BuildManager;
	QString baseName;
	GuessCommandLineFunc guessFunc;
	QString deprecatedConfigName;
	
	static QString getProgramName(const QString& commandLine);
	QString getProgramName() const;
};

struct ExpandingOptions{
	ExpandingOptions(const QFileInfo &mainFile, const QFileInfo &currentFile = QFileInfo(), const int currentLine = 0);
	const QFileInfo &mainFile;
	const QFileInfo &currentFile;
	const int currentLine;
	int nestingDeep; 
	bool canceled;
	struct ParameterOverride{
		QList<QPair<QString, QString> > replace;
		QStringList append;
		QStringList remove;
		bool removeAll;
	};
	ParameterOverride override;
};

typedef QHash<QString, CommandInfo> CommandMapping;
class ConfigManagerInterface;
class BuildManager: public QObject {
	Q_OBJECT
public:
	BuildManager();
	~BuildManager();

	static const QString TXS_CMD_PREFIX;
	static const QString CMD_LATEX, CMD_PDFLATEX;
	static const QString CMD_VIEW_DVI, CMD_VIEW_PS, CMD_VIEW_PDF;
	static const QString CMD_DVIPNG, CMD_DVIPS, CMD_DVIPDF, CMD_PS2PDF, CMD_GS, CMD_MAKEINDEX, CMD_METAPOST, CMD_ASY, CMD_BIBTEX, CMD_SVN, CMD_SVNADMIN;
	static const QString CMD_COMPILE, CMD_BIBLIOGRAPHY, CMD_QUICK, CMD_RECOMPILE_BIBLIOGRAPHY;
	static const QString CMD_VIEW_PDF_INTERNAL, CMD_CONDITIIONALLY_RECOMPILE_BIBLIOGRAPHY;
	
	static QString chainCommands(const QString& a);
	static QString chainCommands(const QString& a, const QString& b);
	static QString chainCommands(const QString& a, const QString& b, const QString& c);
	static QString chainCommands(const QString& a, const QString& b, const QString& c, const QString& d);
	
	static QString findFileInPath(QString fileName);
	static QStringList parseExtendedCommandLine(QString str, const QFileInfo &mainFile, const QFileInfo &currentFile = QFileInfo(), int currentLine=0);
	ExpandedCommands expandCommandLine(const QString& str, ExpandingOptions& expandingOptions);
	
	void registerOptions(ConfigManagerInterface& cmi);
	void readSettings(QSettings &settings);
	void saveSettings(QSettings &settings);

	bool runCommand(const QString &unparsedCommandLine, const QFileInfo &mainFile, const QFileInfo &currentFile = QFileInfo(), int currentLine = 0, QString* buffer = 0);
	bool runCommand(const ExpandedCommands& expandedCommands, const QFileInfo &mainFile, QString* buffer = 0);
private:
	bool runCommandInternal(const ExpandedCommands& expandedCommands, const QFileInfo &mainFile, QString* buffer = 0);
public:
	//creates a process object with the given command line (after it is changed by an implcit call to parseExtendedCommandLine)
	//ProcessX* newProcess(const QString &unparsedCommandLine, const QString &mainFile, const QString &currentFile, int currentLine=0, bool singleInstance = false);
	//QList<ProcessX*> newProcesses(const QString &unparsedCommandLine, const QString &mainFile, const QString &currentFile, int currentLine=0, bool singleInstance = false);
	ProcessX* firstProcessOfDirectExpansion(const QString& command, const QFileInfo& mainfile, const QFileInfo& currentFile = QFileInfo(), int currentLine = 0);
private:
	ProcessX* newProcessInternal(const QString &fullCommandLine, const QFileInfo& mainFile, bool singleInstance = false);
public:
	bool waitForProcess(ProcessX* p);
	bool waitingForProcess() const;
	void killCurrentProcess(); 
	
	
	static QString createTemporaryFileName(); //don't forget to remove the file!
					
	void preview(const QString &preamble, const PreviewSource& source, const QString& masterFile, QTextCodec *outputCodec=0);
	void clearPreviewPreambleCache();

	bool isCommandDirectlyDefined(const QString& id) const;
	CommandInfo getCommandInfo(const QString& id) const;
	QString editCommandList(const QString& list);
	CommandMapping getAllCommands();
	QStringList getCommandsOrder();
	void setAllCommands(const CommandMapping& commands);
	
	int *autoRerunLatex; //0: never, > 0 count of reruns
	int maxExpandingNestingDeep;
	
	int deprecatedQuickmode;
	enum Dvi2PngMode { DPM_DVIPNG, DPM_DVIPNG_FOLLOW, DPM_DVIPS_GHOSTSCRIPT};
	Dvi2PngMode dvi2pngMode;
	enum SaveFilesBeforeCompiling {SFBC_ALWAYS, SFBC_ONLY_CURRENT_OR_NAMED, SFBC_ONLY_NAMED};
	SaveFilesBeforeCompiling saveFilesBeforeCompiling;
	bool previewRemoveBeamer, previewPrecompilePreamble;
private slots:	
	void singleInstanceCompleted(int status);
	void preamblePrecompileCompleted(int status);
	void latexPreviewCompleted(int status);
	void dvi2psPreviewCompleted(int status);
	void conversionPreviewCompleted(int status); 
	void runInternalCommandThroughProcessX();
signals:
	void processNotification(const QString& message);
	void previewAvailable(const QString& filename, const PreviewSource& source);
	void runInternalCommand(const QString& cmdId, const QFileInfo& mainfile);

		
	void latexCompiled(LatexCompileResult* rerun);
	void beginRunningCommands(const QString& commandMain, bool latex, bool pdf);
	void beginRunningSubCommand(ProcessX* p, const QString& commandMain, const QString& subCommand, const RunCommandFlags& flags);
	void endRunningSubCommand(ProcessX* p, const QString& commandMain, const QString& subCommand, const RunCommandFlags& flags);
	void endRunningCommands(const QString& commandMain, bool latex, bool pdf);
	
private:
	void initDefaultCommandNames();
	CommandInfo& registerCommand(const QString& id, const QString& basename, const QString& displayName, const QString& args, const QString& oldConfig = "", GuessCommandLineFunc guessFunc = 0);
	CommandInfo& registerCommand(const QString& id, const QString& displayname, const QStringList& alternatives, const QString& oldConfig = "");
	QString getCommandLine(const QString& id);
	friend class ProcessX;
	CommandMapping commands;
	QStringList internalCommandIds, commandSortingsOrder;
	QMap<QString, ProcessX*> runningCommands;
	ProcessX* processWaitedFor;

	QStringList latexCommands, pdfCommands, stdoutCommands, viewerCommands;
	
	QStringList previewFileNames;
	QMap<QString, PreviewSource> previewFileNameToSource;
	QHash<QString, QString> preambleHash;
	void removePreviewFiles(QString elemName);
#ifdef Q_WS_WIN
	unsigned long int pidInst;
	bool executeDDE(QString ddePseudoURL);
#endif
};

//#define PROFILE_PROCESSES

//this process can handle dde and normal commands
class ProcessX: public QProcess{
	Q_OBJECT
public:
	ProcessX(BuildManager* parent=0, const QString &assignedCommand="", const QString& fileToCompile="");
	void startCommand();
	bool waitForStarted(int timeOut=30000);
	const QString& getFile();
	const QString& getCommandLine();
	bool showStdout() const;
	void setShowStdout(bool show);
	QString * getStdoutBuffer();
	void setStdoutBuffer(QString *buffer);
	bool showStderr() const;
	void setShowStderr(bool show);
	void setOverrideEnvironment(const QStringList& env);
	const QStringList& overrideEnvironment();	
	
	Q_INVOKABLE int exitStatus() const;
	Q_INVOKABLE int exitCode() const;
	Q_INVOKABLE QString readAllStandardOutputStr();
	Q_INVOKABLE QString readAllStandardErrorStr();
	Q_INVOKABLE bool waitForFinished ( int msecs = 30000 );

	bool isRunning() const;
signals:
	void processNotification(const QString& message);
	void standardOutputRead(const QString& data);
	void standardErrorRead(const QString& data);
private slots:
	void onStarted();
	void onError(QProcess::ProcessError error);
	void onFinished(int error);
#ifdef PROFILE_PROCESSES
	void finished();
#endif
	void readFromStandardOutput();
	void readFromStandardError();
private:
	QString cmd;
	QString file;
	bool isStarted, ended, stderrEnabled, stdoutEnabled, stdoutEnabledOverrideOn;
	QString *stdoutBuffer;
	QStringList overriddenEnvironment;
#ifdef PROFILE_PROCESSES
	QTime time;
#endif
};


#endif // BUILDMANAGER_H
