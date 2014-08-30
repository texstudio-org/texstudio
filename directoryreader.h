#ifndef DIRECTORYREADER_H
#define DIRECTORYREADER_H

#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"
#include <QThread>

class directoryReader : public SafeThread
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
