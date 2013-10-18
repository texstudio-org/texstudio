#ifndef LATEXSTYLEPARSER_H
#define LATEXSTYLEPARSER_H
#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"
#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QQueue>

class LatexStyleParser : public SafeThread
{
    Q_OBJECT
public:
    explicit LatexStyleParser(QObject *parent = 0,QString baseDirName="",QString kpsecmd="");
    void stop();
    void addFile(QString filename);

protected:
    void run();

    QStringList readPackage(QString fn,QStringList& parsedPackages);
    QStringList readPackageTexDef(QString fn);
    QStringList readPackageTracing(QString fn);
    QString kpsewhich(QString name);

signals:
    void scanCompleted(QString package);

public slots:

private:
    QQueue<QString> mFiles;
    QSemaphore mFilesAvailable;
    QMutex mFilesLock;

    bool stopped;

    QString baseDir;
    QString kpseWhichCmd;
    QString texdefDir;

    bool texdefMode;

};

#endif // LATEXSTYLEPARSER_H
