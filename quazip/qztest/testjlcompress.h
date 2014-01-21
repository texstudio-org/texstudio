#ifndef QUAZIP_TEST_JLCOMPRESS_H
#define QUAZIP_TEST_JLCOMPRESS_H

#include <QObject>

class TestJlCompress: public QObject {
    Q_OBJECT
private slots:
    void compressFile_data();
    void compressFile();
    void compressFiles_data();
    void compressFiles();
    void compressDir_data();
    void compressDir();
    void extractFile_data();
    void extractFile();
    void extractFiles_data();
    void extractFiles();
    void extractDir_data();
    void extractDir();
};

#endif // QUAZIP_TEST_JLCOMPRESS_H
