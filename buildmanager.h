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
	RCF_COMPILES_TEX = 4, //latex command, show the log 
	RCF_RERUNNABLE = 8,   //rerun if there are errors (usually RCF_RERUNNABLE is set iff RCF_COMPILES_TEX is set, except for latexmk)
	RCF_RERUN = 16,
	RCF_CHANGE_PDF = 32,    //pdflatex (=> lock pdf)
	RCF_SINGLE_INSTANCE = 64,//viewer (=> start only once)
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
	bool user;
	bool meta;
	
	QStringList metaSuggestionList;
	QStringList simpleDescriptionList;
	
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
	const QFileInfo mainFile;
	const QFileInfo currentFile;
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
	static const QString CMD_LATEX, CMD_PDFLATEX, CMD_XELATEX, CMD_LUALATEX,CMD_LATEXMK;
	static const QString CMD_VIEW_DVI, CMD_VIEW_PS, CMD_VIEW_PDF, CMD_VIEW_LOG;
	static const QString CMD_DVIPNG, CMD_DVIPS, CMD_DVIPDF, CMD_PS2PDF, CMD_GS, CMD_MAKEINDEX, CMD_TEXINDY, CMD_METAPOST, CMD_ASY, CMD_BIBTEX, CMD_SVN, CMD_SVNADMIN;
	static const QString CMD_COMPILE, CMD_VIEW, CMD_BIBLIOGRAPHY, CMD_INDEX, CMD_QUICK, CMD_RECOMPILE_BIBLIOGRAPHY;
	static const QString CMD_VIEW_PDF_INTERNAL, CMD_INTERNAL_PRE_COMPILE, CMD_CONDITIONALLY_RECOMPILE_BIBLIOGRAPHY;
	
	static QString chainCommands(const QString& a);
	static QString chainCommands(const QString& a, const QString& b);
	static QString chainCommands(const QString& a, const QString& b, const QString& c);
	static QString chainCommands(const QString& a, const QString& b, const QString& c, const QString& d);
	
	static QString findFileInPath(QString fileName);
	static QStringList parseExtendedCommandLine(QString str, const QFileInfo &mainFile, const QFileInfo &currentFile = QFileInfo(), int currentLine=0);
	ExpandedCommands expandCommandLine(const QString& str, ExpandingOptions& expandingOptions);
	RunCommandFlags getSingleCommandFlags(const QString& command) const;
	bool hasCommandLine(const QString& program);
	
	void registerOptions(ConfigManagerInterface& cmi);
	void readSettings(QSettings &settings);
	void saveSettings(QSettings &settings);
	
public slots:
	bool runCommand(const QString &unparsedCommandLine, const QFileInfo &mainFile, const QFileInfo &currentFile = QFileInfo(), int currentLine = 0, QString* buffer = 0);
private:
	bool runCommandInternal(const ExpandedCommands& expandedCommands, const QFileInfo &mainFile, QString* buffer = 0);
public:
	//creates a process object with the given command line (after it is changed by an implcit call to parseExtendedCommandLine)
	//ProcessX* newProcess(const QString &unparsedCommandLine, const QString &mainFile, const QString &currentFile, int currentLine=0, bool singleInstance = false);
	//QList<ProcessX*> newProcesses(const QString &unparsedCommandLine, const QString &mainFile, const QString &currentFile, int currentLine=0, bool singleInstance = false);
	Q_INVOKABLE ProcessX* firstProcessOfDirectExpansion(const QString& command, const QFileInfo& mainfile, const QFileInfo& currentFile = QFileInfo(), int currentLine = 0);
	
	Q_INVOKABLE ProcessX* newProcessInternal(const QString &fullCommandLine, const QFileInfo& mainFile, bool singleInstance = false);
public:
	Q_INVOKABLE bool waitForProcess(ProcessX* p);
	Q_INVOKABLE bool waitingForProcess() const;
	Q_INVOKABLE void killCurrentProcess(); 
	
	static QString createTemporaryFileName(); //don't forget to remove the file!
	
	void preview(const QString &preamble, const PreviewSource& source, const QString& masterFile, QTextCodec *outputCodec=0);
	void clearPreviewPreambleCache();
	
	Q_INVOKABLE bool isCommandDirectlyDefined(const QString& id) const;
	CommandInfo getCommandInfo(const QString& id) const;
	QString editCommandList(const QString& list, const QString& excludeId = "");
	CommandMapping getAllCommands();
	QStringList getCommandsOrder();
	void setAllCommands(const CommandMapping& commands, const QStringList& userOrder);
	
	int maxExpandingNestingDeep;
	
	int deprecatedQuickmode;
	QStringList deprecatedUserToolCommands, deprecatedUserToolNames;
	QStringList userToolOrder, userToolDisplayNames;
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
	void commandLineRequestedDefault(const QString& cmdId, QString* result, bool * user);
	void runInternalCommandThroughProcessX();
private:
	bool testAndRunInternalCommand(const QString& cmd, const QFileInfo& mainFile);
signals:
	void processNotification(const QString& message);
	void previewAvailable(const QString& filename, const PreviewSource& source);
	
	void commandLineRequested(const QString& cmdId, QString* result, bool * user = 0);
	void runInternalCommand(const QString& cmdId, const QFileInfo& mainfile, const QString& options);
	
	void latexCompiled(LatexCompileResult* rerun);
	void beginRunningCommands(const QString& commandMain, bool latex, bool pdf);
	void beginRunningSubCommand(ProcessX* p, const QString& commandMain, const QString& subCommand, const RunCommandFlags& flags);
	void endRunningSubCommand(ProcessX* p, const QString& commandMain, const QString& subCommand, const RunCommandFlags& flags);
	void endRunningCommands(const QString& commandMain, bool latex, bool pdf);
	
private:
	void initDefaultCommandNames();
	CommandInfo& registerCommand(const QString& id, const QString& basename, const QString& displayName, const QString& args, const QString& oldConfig = "", GuessCommandLineFunc guessFunc = 0, bool user = false);
	CommandInfo& registerCommand(const QString& id, const QString& displayname, const QStringList& alternatives, const QString& oldConfig = "",const bool metaCommand=true, const QStringList simpleDescriptions = QStringList());
	Q_INVOKABLE QString getCommandLine(const QString& id, bool* user);
	friend class ProcessX;
	CommandMapping commands;
	QStringList internalCommands, commandSortingsOrder;
	QMap<QString, ProcessX*> runningCommands;
	QPointer<ProcessX> processWaitedFor;
	
	QStringList latexCommands, rerunnableCommands, pdfCommands, stdoutCommands, viewerCommands;
	QStringList rerunCommandsUnexpanded;
public:
	static int autoRerunLatex;
	static QString autoRerunCommands;
private:
	QStringList previewFileNames;
	QMap<QString, PreviewSource> previewFileNameToSource;
	QHash<QString, QString> preambleHash;
	void removePreviewFiles(QString elemName);
#ifdef Q_WS_WIN
	unsigned long int pidInst;
	Q_INVOKABLE bool executeDDE(QString ddePseudoURL);
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
	void readFromStandardError(bool force=false);
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
