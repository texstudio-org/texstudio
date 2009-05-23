#ifndef BUILDMANAGER_H
#define BUILDMANAGER_H

#include <QString>
#include <QFileInfo>
#include <QPixmap>
#include <QProcess>
#include <QSettings>
#include <QTemporaryFile>

class ProcessX;

//all the build things in texmaker.cpp are going to be moved to this place, but it doesn't have high priority
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
		CMD_USER_QUICK,
		CMD_USER_PRECOMPILE,
		CMD_MAXIMUM_COMMAND_VALUE
	};
	static QString cmdToConfigString(LatexCommand cmd);
	static QString parseExtendedCommandLine(QString str, const QFileInfo &mainFile,int currentline);
	static QString guessCommandName(LatexCommand cmd);

	void readSettings(const QSettings &settings);
	void saveSettings(QSettings &settings);
	
	void setLatexCommand(LatexCommand cmd, const QString &cmdString);
	QString getLatexCommand(LatexCommand cmd);
	QString getLatexCommandForDisplay(LatexCommand cmd);
	
	ProcessX* newProcess(LatexCommand cmd, const QString &fileToCompile, int currentLine=0);
	ProcessX* newProcess(const QString &unparsedCommandLine, const QString &fileToCompile, int currentLine=0);
	
	static QTemporaryFile* temporaryTexFile(); //don't forget to remove the file!
					
	void preview(const QString &preamble, const QString &text);

private slots:	
	void latexPreviewCompleted(int status);
	void conversionPreviewCompleted(int status);
	
private:
	friend class ProcessX;
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
private:
	QString cmd;
	QString file;
	bool started;
};


#endif // BUILDMANAGER_H
