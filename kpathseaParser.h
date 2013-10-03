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

	static void savePackageList(QSet<QString> packages, const QString &filename);
	static QSet<QString> readPackageList(const QString &filename);

protected:
    void run();

    QString kpsewhich();
    QString mpm(QString arg);

signals:
    void scanCompleted(QSet<QString> packages);

public slots:

private:

    QString kpseWhichCmd;
    bool stopped;

};

#endif // LATEXSTYLEPARSER_H
