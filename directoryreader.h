#ifndef DIRECTORYREADER_H
#define DIRECTORYREADER_H

#include "mostQtHeaders.h"
#include <QThread>
#if QT_VERSION >= 0x040400
#include <QFileSystemModel>
#endif

class directoryReader : public QThread
{
    Q_OBJECT
public:
    explicit directoryReader(QObject *parent = 0);

signals:
    void directoryLoaded(QString path,QSet<QString> content);

public slots:
    void readDirectory(QString path);

private:

};

#endif // DIRECTORYREADER_H
