#ifndef KPATHSEAPARSER_H
#define KPATHSEAPARSER_H
#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"
#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QQueue>

class KpathSeaParser : public SafeThread
{
    Q_OBJECT
public:
    explicit KpathSeaParser(QObject *parent = 0,QString kpsecmd="");
    void stop();

protected:
    void run();

    QString kpsewhich();
    QString mpm(QString arg);

signals:
    void scanCompleted(QStringList packages);

public slots:

private:

    QString kpseWhichCmd;


};

#endif // LATEXSTYLEPARSER_H
