#ifndef DIRECTORYREADER_H
#define DIRECTORYREADER_H

#include "mostQtHeaders.h"
#include <QThread>

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
