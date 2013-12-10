#include "testquaziodevice.h"
#include <quazip/quaziodevice.h>
#include <QBuffer>
#include <QByteArray>
#include <QtTest/QtTest>

void TestQuaZIODevice::read()
{
    QByteArray buf(256, 0);
    z_stream zouts;
    zouts.zalloc = (alloc_func) NULL;
    zouts.zfree = (free_func) NULL;
    zouts.opaque = NULL;
    deflateInit(&zouts, Z_DEFAULT_COMPRESSION);
    zouts.next_in = reinterpret_cast<Bytef*>(const_cast<char*>("test"));
    zouts.avail_in = 4;
    zouts.next_out = reinterpret_cast<Bytef*>(buf.data());
    zouts.avail_out = buf.size();
    deflate(&zouts, Z_FINISH);
    deflateEnd(&zouts);
    QBuffer testBuffer(&buf);
    testBuffer.open(QIODevice::ReadOnly);
    QuaZIODevice testDevice(&testBuffer);
    QVERIFY(testDevice.open(QIODevice::ReadOnly));
    char outBuf[5];
    QCOMPARE(testDevice.read(outBuf, 5), static_cast<qint64>(4));
    testDevice.close();
    QVERIFY(!testDevice.isOpen());
}

void TestQuaZIODevice::write()
{
    QByteArray buf(256, 0);
    QBuffer testBuffer(&buf);
    testBuffer.open(QIODevice::WriteOnly);
    QuaZIODevice testDevice(&testBuffer);
    QVERIFY(testDevice.open(QIODevice::WriteOnly));
    QCOMPARE(testDevice.write("test", 4), static_cast<qint64>(4));
    testDevice.close();
    QVERIFY(!testDevice.isOpen());
    z_stream zins;
    zins.zalloc = (alloc_func) NULL;
    zins.zfree = (free_func) NULL;
    zins.opaque = NULL;
    inflateInit(&zins);
    zins.next_in = reinterpret_cast<Bytef*>(buf.data());
    zins.avail_in = testBuffer.pos();
    char outBuf[5];
    zins.next_out = reinterpret_cast<Bytef*>(outBuf);
    zins.avail_out = 5;
    inflate(&zins, Z_FINISH);
    inflateEnd(&zins);
    int size = 5 - zins.avail_out;
    QCOMPARE(size, 4);
    outBuf[4] = '\0';
    QCOMPARE(static_cast<const char*>(outBuf), "test");
}
