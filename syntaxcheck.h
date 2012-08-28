#ifndef SYNTAXCHECK_H
#define SYNTAXCHECK_H

#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"
#include "qdocumentline_p.h"
#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QQueue>

class LatexDocument;

class Environment{
	
public:
	Environment(): id(-1), excessCol(0), dlh(0), ticket(0) {}
	
	QString name;
	int id;
	int excessCol;
	QDocumentLineHandle *dlh;
	int ticket;
	
	bool operator ==(const Environment& env){
		return (name==env.name)&&(id==env.id)&&(excessCol==env.excessCol);
	}
	bool operator !=(const Environment& env){
		return (name!=env.name)||(id!=env.id)||(excessCol!=env.excessCol);
	}
};

typedef QStack<Environment> StackEnvironment;

Q_DECLARE_METATYPE(StackEnvironment)

class SyntaxCheck : public SafeThread
{
	Q_OBJECT
	
public:
	
	
	enum ErrorType {
		ERR_none,
		ERR_unrecognizedCommand,
		ERR_unrecognizedMathCommand,
		ERR_unrecognizedTabularCommand,
		ERR_TabularCommandOutsideTab,
		ERR_MathCommandOutsideMath,
		ERR_TabbingCommandOutside,
		ERR_tooManyCols,
		ERR_tooLittleCols,
        ERR_missingEndOfLine,
        ERR_closingUnopendEnv,
        ERR_EnvNotClosed
	};
	
	struct SyntaxLine{
		StackEnvironment prevEnv;
		int ticket;
		bool clearOverlay;
		QDocumentLineHandle *dlh;
	};
	
	struct Error {
		QPair<int,int> range;
		ErrorType type;
	};
	
	typedef QList<Error > Ranges;
	
	explicit SyntaxCheck(QObject *parent = 0);
	
	void putLine(QDocumentLineHandle *dlh, StackEnvironment previous,bool clearOverlay=false);
	void stop();
	void setErrFormat(int errFormat);
	QString getErrorAt(QDocumentLineHandle *dlh,int pos,StackEnvironment previous);
	int verbatimFormat;
	void waitForQueueProcess();
	static int containsEnv(const LatexParser& parser, const QString& name,const StackEnvironment& envs,const int id=-1);
	int topEnv(const QString& name,const StackEnvironment& envs,const int id=-1);
	bool checkCommand(const QString &cmd,const StackEnvironment &envs);
	static bool equalEnvStack(StackEnvironment env1,StackEnvironment env2);
	bool queuedLines();
	void setLtxCommands(const LatexParser& cmds);
    void markUnclosedEnv(Environment env);
	
signals:
	void checkNextLine(QDocumentLineHandle *dlh,bool clearOverlay, int ticket);
protected:
	void run();
    void checkLine(const QString &line,Ranges &newRanges,StackEnvironment &activeEnv, QDocumentLineHandle *dlh,int ticket);
	
private:
	QQueue<SyntaxLine> mLines;
	QSemaphore mLinesAvailable;
	QMutex mLinesLock;
	bool stopped;
	int syntaxErrorFormat;
	LatexParser *ltxCommands;

	LatexParser newLtxCommands;
	bool newLtxCommandsAvailable;
	QMutex mLtxCommandLock;
};

#endif // SYNTAXCHECK_H
