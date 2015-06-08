#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "qdocumentcursor.h"
#include "qdocument.h"
#include "qdocumentline.h"
#include "qdocumentline_p.h"
#include "smallUsefulFunctions.h"
#include "smallUsefulFunctions_t.h"
#include "testutil.h"
#include <QtTest/QtTest>

void SmallUsefulFunctionsTest::test_simpleLexing_data() {
    QTest::addColumn<QString>("line");
    QTest::addColumn<QList<int> >("types");
    QTest::addColumn<QList<int> >("starts");
    QTest::addColumn<QList<int> >("lengths");

    QTest::newRow("simple") << "bummerang" << (QList<int>()<<1) << (QList<int>()<<0)  << (QList<int>()<<9);
    QTest::newRow("command") << "\\bummerang" << (QList<int>()<<2) << (QList<int>()<<0)  << (QList<int>()<<10);
    QTest::newRow("command with arg") << "\\bummerang{abc}" << (QList<int>()<<2<<6<<1<<9) << (QList<int>()<<0<<10<<11<<14)  << (QList<int>()<<10<<1<<3<<1);
}

void SmallUsefulFunctionsTest::test_simpleLexing() {
    QFETCH(QString,line);
    QFETCH(QList<int>, types);
    QFETCH(QList<int>, starts);
    QFETCH(QList<int>, lengths);
    QDocument *doc=new QDocument();
    QDocumentLineHandle *dlh=new QDocumentLineHandle(line,doc);
    simpleLexLatexLine(dlh);
    TokenList tl=dlh->getCookie(QDocumentLine::LEXER_RAW_COOKIE).value<TokenList>();
    for(int i=0;i<tl.length();i++){
        Tokens tk=tl.at(i);
        int type=types.value(i,0);
        int start=starts.value(i,0);
        int length=lengths.value(i,0);
        QVERIFY2(int(tk.type)==type,QString("incorrect type %1 != %2").arg(int(tk.type)).arg(type).toLatin1().constData());
        QVERIFY2(tk.start==start,"incorrect start");
        QVERIFY2(tk.length==length,"incorrect length");
    }
    delete doc;
}

#endif

