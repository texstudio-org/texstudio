#ifndef TESTUTIL_H
#define TESTUTIL_H
#include <QtTest/QtTest>
#define QSVERIFY(a,b) QVERIFY(a)
#define QSVERIFY2(a,b) QVERIFY2(a, (b).toLatin1().constData())
#define QEQUAL(a,b) QSVERIFY2(a==b, QString("equal failed: got \"%1\" !=expected \"%2\" ").arg(a).arg(b))

#endif
