#ifndef QUAZIP_TEST_QUAZIODEVICE_H
#define QUAZIP_TEST_QUAZIODEVICE_H

#include <QObject>

class TestQuaZIODevice: public QObject {
    Q_OBJECT
private slots:
    void read();
    void write();
};

#endif // QUAZIP_TEST_QUAZIODEVICE_H
