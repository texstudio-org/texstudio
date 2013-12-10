#include "testjlcompress.h"

#include "qztest.h"

#include <QDir>
#include <QFileInfo>

#include <QtTest/QtTest>

#include <quazip/JlCompress.h>

void TestJlCompress::compressFile_data()
{
    QTest::addColumn<QString>("zipName");
    QTest::addColumn<QString>("fileName");
    QTest::newRow("simple") << "jlsimplefile.zip" << "test0.txt";
}

void TestJlCompress::compressFile()
{
    QFETCH(QString, zipName);
    QFETCH(QString, fileName);
    QDir curDir;
    if (curDir.exists(zipName)) {
        if (!curDir.remove(zipName))
            QFAIL("Can't remove zip file");
    }
    if (!createTestFiles(QStringList() << fileName)) {
        QFAIL("Can't create test file");
    }
    QVERIFY(JlCompress::compressFile(zipName, "tmp/" + fileName));
    // get the file list and check it
    QStringList fileList = JlCompress::getFileList(zipName);
    QCOMPARE(fileList.count(), 1);
    QVERIFY(fileList[0] == fileName);
    removeTestFiles(QStringList() << fileName);
    curDir.remove(zipName);
}

void TestJlCompress::compressFiles_data()
{
    QTest::addColumn<QString>("zipName");
    QTest::addColumn<QStringList>("fileNames");
    QTest::newRow("simple") << "jlsimplefiles.zip" <<
        (QStringList() << "test0.txt" << "test00.txt");
    QTest::newRow("different subdirs") << "jlsubdirfiles.zip" <<
        (QStringList() << "subdir1/test1.txt" << "subdir2/test2.txt");
}

void TestJlCompress::compressFiles()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QDir curDir;
    if (curDir.exists(zipName)) {
        if (!curDir.remove(zipName))
            QFAIL("Can't remove zip file");
    }
    if (!createTestFiles(fileNames)) {
        QFAIL("Can't create test files");
    }
    QStringList realNamesList, shortNamesList;
    foreach (QString fileName, fileNames) {
        QString realName = "tmp/" + fileName;
        realNamesList += realName;
        shortNamesList += QFileInfo(realName).fileName();
    }
    QVERIFY(JlCompress::compressFiles(zipName, realNamesList));
    // get the file list and check it
    QStringList fileList = JlCompress::getFileList(zipName);
    QCOMPARE(fileList, shortNamesList);
    removeTestFiles(fileNames);
    curDir.remove(zipName);
}

void TestJlCompress::compressDir_data()
{
    QTest::addColumn<QString>("zipName");
    QTest::addColumn<QStringList>("fileNames");
    QTest::addColumn<QStringList>("expected");
    QTest::newRow("simple") << "jldir.zip"
        << (QStringList() << "test0.txt" << "testdir1/test1.txt"
            << "testdir2/test2.txt" << "testdir2/subdir/test2sub.txt")
		<< (QStringList() << "test0.txt"
			<< "testdir1/" << "testdir1/test1.txt"
            << "testdir2/" << "testdir2/test2.txt"
			<< "testdir2/subdir/" << "testdir2/subdir/test2sub.txt");
    QTest::newRow("empty dirs") << "jldir_empty.zip"
		<< (QStringList() << "testdir1/" << "testdir2/testdir3/")
		<< (QStringList() << "testdir1/" << "testdir2/"
            << "testdir2/testdir3/");
}

void TestJlCompress::compressDir()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QFETCH(QStringList, expected);
    QDir curDir;
    if (curDir.exists(zipName)) {
        if (!curDir.remove(zipName))
            QFAIL("Can't remove zip file");
    }
    if (!createTestFiles(fileNames, "compressDir_tmp")) {
        QFAIL("Can't create test files");
    }
    QVERIFY(JlCompress::compressDir(zipName, "compressDir_tmp"));
    // get the file list and check it
    QStringList fileList = JlCompress::getFileList(zipName);
    qSort(fileList);
    qSort(expected);
    QCOMPARE(fileList, expected);
    removeTestFiles(fileNames, "compressDir_tmp");
    curDir.remove(zipName);
}

void TestJlCompress::extractFile_data()
{
    QTest::addColumn<QString>("zipName");
    QTest::addColumn<QStringList>("fileNames");
    QTest::addColumn<QString>("fileToExtract");
    QTest::addColumn<QString>("destName");
    QTest::newRow("simple") << "jlextfile.zip" << (
            QStringList() << "test0.txt" << "testdir1/test1.txt"
            << "testdir2/test2.txt" << "testdir2/subdir/test2sub.txt")
        << "testdir2/test2.txt" << "test2.txt";
}

void TestJlCompress::extractFile()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QFETCH(QString, fileToExtract);
    QFETCH(QString, destName);
    QDir curDir;
    if (!curDir.mkpath("jlext/jlfile")) {
        QFAIL("Couldn't mkpath jlext/jlfile");
    }
    if (!createTestFiles(fileNames)) {
        QFAIL("Couldn't create test files");
    }
    if (!JlCompress::compressDir(zipName, "tmp")) {
        QFAIL("Couldn't create test archive");
    }
    QVERIFY(!JlCompress::extractFile(zipName, fileToExtract,
                "jlext/jlfile/" + destName).isEmpty());
    QFileInfo destInfo("jlext/jlfile/" + destName), srcInfo("tmp/" +
            fileToExtract);
    QCOMPARE(destInfo.size(), srcInfo.size());
    QCOMPARE(destInfo.permissions(), srcInfo.permissions());
    curDir.remove("jlext/jlfile/" + destName);
    curDir.mkdir("jlext/jlfile/" + destName);
    QVERIFY(JlCompress::extractFile(zipName, fileToExtract,
                "jlext/jlfile/" + destName).isEmpty());
    curDir.rmpath("jlext/jlfile/" + destName);
    removeTestFiles(fileNames);
    curDir.remove(zipName);
}

void TestJlCompress::extractFiles_data()
{
    QTest::addColumn<QString>("zipName");
    QTest::addColumn<QStringList>("fileNames");
    QTest::addColumn<QStringList>("filesToExtract");
    QTest::newRow("simple") << "jlextfiles.zip" << (
            QStringList() << "test0.txt" << "testdir1/test1.txt"
            << "testdir2/test2.txt" << "testdir2/subdir/test2sub.txt")
        << (QStringList() << "testdir2/test2.txt" << "testdir1/test1.txt");
}

void TestJlCompress::extractFiles()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QFETCH(QStringList, filesToExtract);
    QDir curDir;
    if (!curDir.mkpath("jlext/jlfiles")) {
        QFAIL("Couldn't mkpath jlext/jlfiles");
    }
    if (!createTestFiles(fileNames)) {
        QFAIL("Couldn't create test files");
    }
    if (!JlCompress::compressDir(zipName, "tmp")) {
        QFAIL("Couldn't create test archive");
    }
    QVERIFY(!JlCompress::extractFiles(zipName, filesToExtract,
                "jlext/jlfiles").isEmpty());
    foreach (QString fileName, filesToExtract) {
        QFileInfo fileInfo("jlext/jlfiles/" + fileName);
        QFileInfo extInfo("tmp/" + fileName);
        QCOMPARE(fileInfo.size(), extInfo.size());
        QCOMPARE(fileInfo.permissions(), extInfo.permissions());
        curDir.remove("jlext/jlfiles/" + fileName);
        curDir.rmpath(fileInfo.dir().path());
    }
    curDir.rmpath("jlext/jlfiles");
    removeTestFiles(fileNames);
    curDir.remove(zipName);
}

void TestJlCompress::extractDir_data()
{
    QTest::addColumn<QString>("zipName");
    QTest::addColumn<QStringList>("fileNames");
    QTest::newRow("simple") << "jlextdir.zip" << (
            QStringList() << "test0.txt" << "testdir1/test1.txt"
            << "testdir2/test2.txt" << "testdir2/subdir/test2sub.txt");
    QTest::newRow("separate dir") << "sepdir.zip" << (
            QStringList() << "laj/" << "laj/lajfile.txt");
}

void TestJlCompress::extractDir()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QDir curDir;
    if (!curDir.mkpath("jlext/jldir")) {
        QFAIL("Couldn't mkpath jlext/jldir");
    }
    if (!createTestFiles(fileNames)) {
        QFAIL("Couldn't create test files");
    }
    if (!createTestArchive(zipName, fileNames)) {
        QFAIL("Couldn't create test archive");
    }
    QStringList extracted;
    QCOMPARE((extracted = JlCompress::extractDir(zipName, "jlext/jldir"))
        .count(), fileNames.count());
    foreach (QString fileName, fileNames) {
        QString fullName = "jlext/jldir/" + fileName;
        QFileInfo fileInfo(fullName);
        QFileInfo extInfo("tmp/" + fileName);
        if (!fileInfo.isDir())
            QCOMPARE(fileInfo.size(), extInfo.size());
        QCOMPARE(fileInfo.permissions(), extInfo.permissions());
        curDir.remove(fullName);
        curDir.rmpath(fileInfo.dir().path());
        QString absolutePath = fileInfo.absoluteFilePath();
        if (fileInfo.isDir() && !absolutePath.endsWith('/'))
	    absolutePath += '/';
        QVERIFY(extracted.contains(absolutePath));
    }
    curDir.rmpath("jlext/jldir");
    removeTestFiles(fileNames);
    curDir.remove(zipName);
}
