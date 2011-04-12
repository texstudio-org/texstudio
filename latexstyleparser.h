#ifndef LATEXSTYLEPARSER_H
#define LATEXSTYLEPARSER_H
#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"
#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QQueue>

class LatexStyleParser : public QThread
{
    Q_OBJECT
public:
    explicit LatexStyleParser(QObject *parent = 0,QString baseDirName="");
    void stop();
    void addFile(QString filename);

protected:
    void run();

signals:
    void scanCompleted(QString package);

public slots:

private:
    QQueue<QString> mFiles;
    QSemaphore mFilesAvailable;
    QMutex mFilesLock;

    bool stopped;

    QString baseDir;

};

#endif // LATEXSTYLEPARSER_H
