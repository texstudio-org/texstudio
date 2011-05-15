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
    QString name;
    int id;

    bool operator ==(const Environment& env){
	return (name==env.name)&&(id==env.id);
    }
    bool operator !=(const Environment& env){
	return (name!=env.name)||(id!=env.id);
    }

};

typedef QStack<Environment> StackEnvironment;

Q_DECLARE_METATYPE(StackEnvironment);

class SyntaxCheck : public QThread
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
	ERR_missingEndOfLine
    };

    struct SyntaxLine{
	StackEnvironment prevEnv;
	int ticket;
	bool clearOverlay;
	QDocumentLineHandle *dlh;
	int excessCols;
    };

    struct Error {
	QPair<int,int> range;
	ErrorType type;
    };

    typedef QList<Error > Ranges;

    explicit SyntaxCheck(QObject *parent = 0);

    void putLine(QDocumentLineHandle *dlh, StackEnvironment previous,bool clearOverlay=false, int excessCols=0);
    void stop();
    void setErrFormat(int errFormat);
    QString getErrorAt(QDocumentLineHandle *dlh,int pos,StackEnvironment previous);
    int verbatimFormat;
    void setLtxCommands(LatexParser cmds);
    void waitForQueueProcess();
    static int containsEnv(const QString& name,const StackEnvironment& envs,const int id=-1);
    bool checkCommand(const QString &cmd,const StackEnvironment &envs);
    static bool equalEnvStack(StackEnvironment env1,StackEnvironment env2);
    bool queuedLines();

signals:
    void checkNextLine(QDocumentLineHandle *dlh,bool clearOverlay,int excessCols, int ticket);
protected:
    void run();
    void checkLine(QString &line,Ranges &newRanges,StackEnvironment &activeEnv,int &excessCols);

private:
    QQueue<SyntaxLine> mLines;
    QSemaphore mLinesAvailable;
    QMutex mLinesLock;
    QMutex mLtxCommandLock;
    bool stopped;
    int syntaxErrorFormat;
    LatexParser ltxCommands;
};

#endif // SYNTAXCHECK_H
