#include "testquazip.h"

#include "qztest.h"

#include <QDir>
#include <QFileInfo>
#include <QHash>

#include <QtTest/QtTest>

#include <quazip/quazip.h>
#include <quazip/JlCompress.h>

void TestQuaZip::getFileList_data()
{
    QTest::addColumn<QString>("zipName");
    QTest::addColumn<QStringList>("fileNames");
    QTest::newRow("simple") << "qzfilelist.zip" << (
            QStringList() << "test0.txt" << "testdir1/test1.txt"
            << "testdir2/test2.txt" << "testdir2/subdir/test2sub.txt");
    QTest::newRow("russian") << QString::fromUtf8("файл.zip") << (
        QStringList() << QString::fromUtf8("test0.txt") << QString::fromUtf8("test1/test1.txt")
            << "testdir2/test2.txt" << "testdir2/subdir/test2sub.txt");
    QTest::newRow("japanese") << QString::fromUtf8("テスト.zip") << (
        QStringList() << QString::fromUtf8("test.txt"));
    QTest::newRow("hebrew") << QString::fromUtf8("פתח תקווה.zip") << (
        QStringList() << QString::fromUtf8("test.txt"));
}

void TestQuaZip::getFileList()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    qSort(fileNames);
    QDir curDir;
    if (curDir.exists(zipName)) {
        if (!curDir.remove(zipName))
            QFAIL("Can't remove zip file");
    }
    if (!createTestFiles(fileNames)) {
        QFAIL("Can't create test file");
    }
    if (!createTestArchive(zipName, fileNames)) {
        QFAIL("Can't create test archive");
    }
    QuaZip testZip(zipName);
    QVERIFY(testZip.open(QuaZip::mdUnzip));
    QVERIFY(testZip.goToFirstFile());
    QString firstFile = testZip.getCurrentFileName();
    QStringList fileList = testZip.getFileNameList();
    qSort(fileList);
    QCOMPARE(fileList, fileNames);
    QHash<QString, QFileInfo> srcInfo;
    foreach (QString fileName, fileNames) {
        srcInfo[fileName] = QFileInfo("tmp/" + fileName);
    }
    QList<QuaZipFileInfo> destList = testZip.getFileInfoList();
    QCOMPARE(destList.size(), srcInfo.size());
    for (int i = 0; i < destList.size(); i++) {
        QCOMPARE(static_cast<qint64>(destList[i].uncompressedSize),
                srcInfo[destList[i].name].size());
    }
    // test that we didn't mess up the current file
    QCOMPARE(testZip.getCurrentFileName(), firstFile);
    testZip.close();
    // clean up
    removeTestFiles(fileNames);
    curDir.remove(zipName);
}

void TestQuaZip::add_data()
{
    QTest::addColumn<QString>("zipName");
    QTest::addColumn<QStringList>("fileNames");
    QTest::addColumn<QStringList>("fileNamesToAdd");
    QTest::newRow("simple") << "qzadd.zip" << (
            QStringList() << "test0.txt" << "testdir1/test1.txt"
            << "testdir2/test2.txt" << "testdir2/subdir/test2sub.txt")
            << (QStringList() << "testAdd.txt");
}

void TestQuaZip::add()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QFETCH(QStringList, fileNamesToAdd);
    QDir curDir;
    if (curDir.exists(zipName)) {
        if (!curDir.remove(zipName))
            QFAIL("Can't remove zip file");
    }
    if (!createTestFiles(fileNames)) {
        QFAIL("Can't create test file");
    }
    if (!createTestArchive(zipName, fileNames)) {
        QFAIL("Can't create test archive");
    }
    if (!createTestFiles(fileNamesToAdd)) {
        QFAIL("Can't create test files to add");
    }
    QuaZip testZip(zipName);
    QVERIFY(testZip.open(QuaZip::mdUnzip));
    // according to the bug #3485459 the global is lost, so we test it
    QString globalComment = testZip.getComment();
    testZip.close();
    QVERIFY(testZip.open(QuaZip::mdAdd));
    foreach (QString fileName, fileNamesToAdd) {
        QuaZipFile testFile(&testZip);
        QVERIFY(testFile.open(QIODevice::WriteOnly, 
            QuaZipNewInfo(fileName, "tmp/" + fileName)));
        QFile inFile("tmp/" + fileName);
        QVERIFY(inFile.open(QIODevice::ReadOnly));
        testFile.write(inFile.readAll());
        inFile.close();
        testFile.close();
    }
    testZip.close();
    QVERIFY(testZip.open(QuaZip::mdUnzip));
    QCOMPARE(testZip.getFileNameList(), fileNames + fileNamesToAdd);
    QCOMPARE(testZip.getComment(), globalComment);
    testZip.close();
    removeTestFiles(fileNames);
    removeTestFiles(fileNamesToAdd);
    curDir.remove(zipName);
}
