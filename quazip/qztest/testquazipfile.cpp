#include "testquazipfile.h"

#include "qztest.h"

#include <quazip/JlCompress.h>
#include <quazip/quazipfile.h>
#include <quazip/quazip.h>

#include <QFile>
#include <QString>
#include <QStringList>

#include <QtTest/QtTest>

void TestQuaZipFile::zipUnzip_data()
{
    QTest::addColumn<QString>("zipName");
    QTest::addColumn<QStringList>("fileNames");
    QTest::addColumn<QByteArray>("fileNameCodec");
    QTest::addColumn<QByteArray>("password");
    QTest::newRow("simple") << "simple.zip" << (
            QStringList() << "test0.txt" << "testdir1/test1.txt"
            << "testdir2/test2.txt" << "testdir2/subdir/test2sub.txt")
        << QByteArray() << QByteArray();
    QTest::newRow("Cyrillic") << "cyrillic.zip" << (
            QStringList()
            << QString::fromUtf8("русское имя файла с пробелами.txt"))
        << QByteArray("IBM866") << QByteArray();
    QTest::newRow("password") << "password.zip" << (
            QStringList() << "test.txt")
        << QByteArray() << QByteArray("PassPass");
}

void TestQuaZipFile::zipUnzip()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QFETCH(QByteArray, fileNameCodec);
    QFETCH(QByteArray, password);
    QFile testFile(zipName);
    if (testFile.exists()) {
        if (!testFile.remove()) {
            QFAIL("Couldn't remove existing archive to create a new one");
        }
    }
    if (!createTestFiles(fileNames)) {
        QFAIL("Couldn't create test files for zipping");
    }
    QuaZip testZip(&testFile);
    if (!fileNameCodec.isEmpty())
        testZip.setFileNameCodec(fileNameCodec);
    QVERIFY(testZip.open(QuaZip::mdCreate));
    QString comment = "Test comment";
    testZip.setComment(comment);
    foreach (QString fileName, fileNames) {
        QFile inFile("tmp/" + fileName);
        if (!inFile.open(QIODevice::ReadOnly)) {
            qDebug("File name: %s", fileName.toUtf8().constData());
            QFAIL("Couldn't open input file");
        }
        QuaZipFile outFile(&testZip);
        QVERIFY(outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(fileName,
                        inFile.fileName()),
                password.isEmpty() ? NULL : password.constData()));
        for (qint64 pos = 0, len = inFile.size(); pos < len; ) {
            char buf[4096];
            qint64 readSize = qMin(static_cast<qint64>(4096), len - pos);
            qint64 l;
            if ((l = inFile.read(buf, readSize)) != readSize) {
                qDebug("Reading %ld bytes from %s at %ld returned %ld",
                        static_cast<long>(readSize),
                        fileName.toUtf8().constData(),
                        static_cast<long>(pos),
                        static_cast<long>(l));
                QFAIL("Read failure");
            }
            QVERIFY(outFile.write(buf, readSize));
            pos += readSize;
        }
        inFile.close();
        outFile.close();
        QCOMPARE(outFile.getZipError(), ZIP_OK);
    }
    testZip.close();
    QCOMPARE(testZip.getZipError(), ZIP_OK);
    // now test unzip
    QuaZip testUnzip(&testFile);
    if (!fileNameCodec.isEmpty())
        testUnzip.setFileNameCodec(fileNameCodec);
    QVERIFY(testUnzip.open(QuaZip::mdUnzip));
    QCOMPARE(testUnzip.getComment(), comment);
    QVERIFY(testUnzip.goToFirstFile());
    foreach (QString fileName, fileNames) {
        QCOMPARE(testUnzip.getCurrentFileName(), fileName);
        QFile original("tmp/" + fileName);
        QVERIFY(original.open(QIODevice::ReadOnly));
        QuaZipFile archived(&testUnzip);
        QVERIFY(archived.open(QIODevice::ReadOnly,
                         password.isEmpty() ? NULL : password.constData()));
        QByteArray originalData = original.readAll();
        QByteArray archivedData = archived.readAll();
        QCOMPARE(archivedData, originalData);
        testUnzip.goToNextFile();
    }
    testUnzip.close();
    QCOMPARE(testUnzip.getZipError(), UNZ_OK);
    // clean up
    removeTestFiles(fileNames);
    testFile.remove();
}

void TestQuaZipFile::bytesAvailable_data()
{
    QTest::addColumn<QString>("zipName");
    QTest::addColumn<QStringList>("fileNames");
    QTest::newRow("simple") << "test.zip" << (
            QStringList() << "test0.txt" << "testdir1/test1.txt"
            << "testdir2/test2.txt" << "testdir2/subdir/test2sub.txt");
}

void TestQuaZipFile::bytesAvailable()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QDir curDir;
    if (!createTestFiles(fileNames)) {
        QFAIL("Couldn't create test files");
    }
    if (!JlCompress::compressDir(zipName, "tmp")) {
        QFAIL("Couldn't create test archive");
    }
    QuaZip testZip(zipName);
    QVERIFY(testZip.open(QuaZip::mdUnzip));
    foreach (QString fileName, fileNames) {
        QFileInfo fileInfo("tmp/" + fileName);
        QVERIFY(testZip.setCurrentFile(fileName));
        QuaZipFile zipFile(&testZip);
        QVERIFY(zipFile.open(QIODevice::ReadOnly));
        QCOMPARE(zipFile.bytesAvailable(), fileInfo.size());
        QCOMPARE(zipFile.read(1).size(), 1);
        QCOMPARE(zipFile.bytesAvailable(), fileInfo.size() - 1);
        QCOMPARE(zipFile.read(fileInfo.size() - 1).size(),
                static_cast<int>(fileInfo.size() - 1));
        QCOMPARE(zipFile.bytesAvailable(), (qint64) 0);
    }
    removeTestFiles(fileNames);
    testZip.close();
    curDir.remove(zipName);
}

void TestQuaZipFile::atEnd_data()
{
    bytesAvailable_data();
}

void TestQuaZipFile::atEnd()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QDir curDir;
    if (!createTestFiles(fileNames)) {
        QFAIL("Couldn't create test files");
    }
    if (!JlCompress::compressDir(zipName, "tmp")) {
        QFAIL("Couldn't create test archive");
    }
    QuaZip testZip(zipName);
    QVERIFY(testZip.open(QuaZip::mdUnzip));
    foreach (QString fileName, fileNames) {
        QFileInfo fileInfo("tmp/" + fileName);
        QVERIFY(testZip.setCurrentFile(fileName));
        QuaZipFile zipFile(&testZip);
        QVERIFY(zipFile.open(QIODevice::ReadOnly));
        QCOMPARE(zipFile.atEnd(), false);
        QCOMPARE(zipFile.read(1).size(), 1);
        QCOMPARE(zipFile.atEnd(), false);
        QCOMPARE(zipFile.read(fileInfo.size() - 1).size(),
                static_cast<int>(fileInfo.size() - 1));
        QCOMPARE(zipFile.atEnd(), true);
    }
    removeTestFiles(fileNames);
    testZip.close();
    curDir.remove(zipName);
}

void TestQuaZipFile::pos_data()
{
    bytesAvailable_data();
}

void TestQuaZipFile::pos()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QDir curDir;
    if (!createTestFiles(fileNames)) {
        QFAIL("Couldn't create test files");
    }
    if (!JlCompress::compressDir(zipName, "tmp")) {
        QFAIL("Couldn't create test archive");
    }
    QuaZip testZip(zipName);
    QVERIFY(testZip.open(QuaZip::mdUnzip));
    foreach (QString fileName, fileNames) {
        QFileInfo fileInfo("tmp/" + fileName);
        QVERIFY(testZip.setCurrentFile(fileName));
        QuaZipFile zipFile(&testZip);
        QVERIFY(zipFile.open(QIODevice::ReadOnly));
        QCOMPARE(zipFile.pos(), (qint64) 0);
        QCOMPARE(zipFile.read(1).size(), 1);
        QCOMPARE(zipFile.pos(), (qint64) 1);
        QCOMPARE(zipFile.read(fileInfo.size() - 1).size(),
                static_cast<int>(fileInfo.size() - 1));
        QCOMPARE(zipFile.pos(), fileInfo.size());
    }
    removeTestFiles(fileNames);
    testZip.close();
    curDir.remove(zipName);
}

void TestQuaZipFile::getZip()
{
    QuaZip testZip;
    QuaZipFile f1(&testZip);
    QCOMPARE(f1.getZip(), &testZip);
    QuaZipFile f2("doesntexist.zip", "someFile");
    QCOMPARE(f2.getZip(), static_cast<QuaZip*>(NULL));
}
