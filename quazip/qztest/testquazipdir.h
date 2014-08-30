#ifndef QUAZIP_TEST_QUAZIPDIR_H
#define QUAZIP_TEST_QUAZIPDIR_H

#include <QObject>

class TestQuaZipDir: public QObject {
    Q_OBJECT
private slots:
    void entryList_data();
    void entryList();
    void cd_data();
    void cd();
};

#endif // QUAZIP_TEST_QUAZIPDIR_H
