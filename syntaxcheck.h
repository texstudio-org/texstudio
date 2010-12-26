#ifndef SYNTAXCHECK_H
#define SYNTAXCHECK_H

#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"
#include "qdocumentline_p.h"
#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QQueue>

class SyntaxCheck : public QThread
{
    Q_OBJECT

public:
    enum Environment {
        ENV_normal,
        ENV_math,
	ENV_tabular,
	ENV_matrix,
	ENV_tabbing
    };

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
	QString text;
	Environment prevEnv;
	int ticket;
	int cols;
	bool clearOverlay;
	QDocumentLineHandle* dlh;
    };

    struct Error {
	QPair<int,int> range;
	ErrorType type;
    };

    typedef QList<Error > Ranges;

    explicit SyntaxCheck(QObject *parent = 0);

    void putLine(QString text,QDocumentLineHandle *dlh,Environment previous=ENV_normal,bool clearOverlay=false,int cols=-1);
    void stop();
    void setErrFormat(int errFormat);
    QString getErrorAt(QString &text,int pos,Environment previous,int cols);

protected:
     void run();
     void checkLine(QString &line,Ranges &newRanges,QStack<Environment> &activeEnv,int cols,int &excessCols);

private:
     QQueue<SyntaxLine> mLines;
     QSemaphore mLinesAvailable;
     QMutex mLinesLock;
     bool stopped;
     int syntaxErrorFormat;
};

#endif // SYNTAXCHECK_H
