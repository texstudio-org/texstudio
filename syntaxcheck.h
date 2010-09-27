#ifndef SYNTAXCHECK_H
#define SYNTAXCHECK_H

#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"
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

    explicit SyntaxCheck(QObject *parent = 0);

    QList<QPair<int,int> > getResult();
    void putLine(QString line,Environment previous=ENV_normal);
    bool isEmpty();

protected:
     void run();

private:
     QQueue<Ranges *> mResults;
     QQueue<QString> mLines;
     QQueue<Environment> mPreviousEnvs,mDetectedEnvs;
     QSemaphore mLinesAvailable;
     QMutex mLinesLock;
     QMutex mResultLock;
};

#endif // SYNTAXCHECK_H
