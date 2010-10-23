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
    typedef QList<QPair<int,int> > Ranges;
    enum Environment {
        ENV_normal,
        ENV_math,
        ENV_tabular
    };

    struct SyntaxLine{
	QString text;
	Environment prevEnv;
	int ticket;
	bool clearOverlay;
	QDocumentLineHandle* dlh;
    };

    explicit SyntaxCheck(QObject *parent = 0);

    void putLine(QString text,QDocumentLineHandle *dlh,Environment previous=ENV_normal,bool clearOverlay=false);
    void stop();
    void setErrFormat(int errFormat);

protected:
     void run();

private:
     QQueue<SyntaxLine> mLines;
     QQueue<Environment> mDetectedEnvs;
     QSemaphore mLinesAvailable;
     QMutex mLinesLock;
     bool stopped;
     int syntaxErrorFormat;
};

#endif // SYNTAXCHECK_H
