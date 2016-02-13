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
    QTest::newRow("command with symbol") << "\\_" << (QList<int>()<<2) << (QList<int>()<<0)  << (QList<int>()<<2);
    QTest::newRow("command with symbol2") << "\\&" << (QList<int>()<<2) << (QList<int>()<<0)  << (QList<int>()<<2);
    QTest::newRow("command with symbol3") << "\\__" << (QList<int>()<<2<<43) << (QList<int>()<<0<<2)  << (QList<int>()<<2<<1);
    QTest::newRow("command with at") << "\\bummer@ng" << (QList<int>()<<2) << (QList<int>()<<0)  << (QList<int>()<<10);
    QTest::newRow("command with arg") << "\\bummerang{abc}" << (QList<int>()<<2<<6<<1<<9) << (QList<int>()<<0<<10<<11<<14)  << (QList<int>()<<10<<1<<3<<1);
    QTest::newRow("command with optional arg") << " \\bummerang  [abc  ]" << (QList<int>()<<2<<8<<1<<11) << (QList<int>()<<1<<13<<14<<19)  << (QList<int>()<<10<<1<<3<<1);
    QTest::newRow("punctation") << "bummerang." << (QList<int>()<<1<<43) << (QList<int>()<<0<<9)  << (QList<int>()<<9<<1);
    QTest::newRow("symbol") << " a = b " << (QList<int>()<<1<<42<<1) << (QList<int>()<<1<<3<<5)  << (QList<int>()<<1<<1<<1);
    QTest::newRow("umlaut") << "\"uber" << (QList<int>()<<43<<1) << (QList<int>()<<0<<1)  << (QList<int>()<<1<<4);
    QTest::newRow("numbers") << "1.2" << (QList<int>()<<44<<43<<44) << (QList<int>()<<0<<1<<2)  << (QList<int>()<<1<<1<<1);
    QTest::newRow("numbers1") << "1em" << (QList<int>()<<44<<1) << (QList<int>()<<0<<1)  << (QList<int>()<<1<<2);
    QTest::newRow("numbers2") << "em2a" << (QList<int>()<<1<<44<<1) << (QList<int>()<<0<<2<<3)  << (QList<int>()<<2<<1<<1);
    QTest::newRow("numbers3") << "\\text1" << (QList<int>()<<2<<44) << (QList<int>()<<0<<5)  << (QList<int>()<<5<<1);
    QTest::newRow("numbers4") << "45\\text4em" << (QList<int>()<<44<<2<<44<<1) << (QList<int>()<<0<<2<<7<<8)  << (QList<int>()<<2<<5<<1<<2);
    QTest::newRow("command with brackets") << "\\bummerang (abc,fgew)" << (QList<int>()<<2<<7<<1<<43<<1<<10) << (QList<int>()<<0<<11<<12<<15<<16<<20)  << (QList<int>()<<10<<1<<3<<1<<4<<1);
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
    dlh->deref();
    delete doc;
}

void SmallUsefulFunctionsTest::test_latexLexing_data() {
    QTest::addColumn<QString>("lines");
    QTest::addColumn<QList<int> >("types");
    QTest::addColumn<QList<int> >("subtypes");
    QTest::addColumn<QList<int> >("starts");
    QTest::addColumn<QList<int> >("lengths");
    QTest::addColumn<QList<int> >("levels");

    QTest::newRow("simple") << "bummerang" << (QList<int>()<<1)<< (QList<int>()<<0) << (QList<int>()<<0)  << (QList<int>()<<9) << (QList<int>()<<0);
    QTest::newRow("simple2") << "bummerang test" << (QList<int>()<<1<<1)<< (QList<int>()<<0<<0) << (QList<int>()<<0<<10)  << (QList<int>()<<9<<4) << (QList<int>()<<0<<0);
    QTest::newRow("simple3") << "bummerang\ntest" << (QList<int>()<<1<<1)<< (QList<int>()<<0<<0) << (QList<int>()<<0<<0)  << (QList<int>()<<9<<4) << (QList<int>()<<0<<0);
    QTest::newRow("text command") << "\\textbf{text}" << (QList<int>()<<2<<3<<1)<< (QList<int>()<<0<<24<<24) << (QList<int>()<<0<<7<<8)  << (QList<int>()<<7<<6<<4) << (QList<int>()<<0<<0<<1);
    QTest::newRow("section command") << "\\section{text}" << (QList<int>()<<2<<3<<1)<< (QList<int>()<<0<<33<<33) << (QList<int>()<<0<<8<<9)  << (QList<int>()<<8<<6<<4) << (QList<int>()<<0<<0<<1);
    QTest::newRow("usepackage command") << "\\usepackage{text}" << (QList<int>()<<2<<3<<29)<< (QList<int>()<<0<<29<<0) << (QList<int>()<<0<<11<<12)  << (QList<int>()<<11<<6<<4) << (QList<int>()<<0<<0<<1);
    QTest::newRow("usepackage command2") << "\\usepackage{text,text}" << (QList<int>()<<2<<3<<29<<29)<< (QList<int>()<<0<<29<<0<<0) << (QList<int>()<<0<<11<<12<<17)  << (QList<int>()<<11<<11<<4<<4) << (QList<int>()<<0<<0<<1<<1);
    QTest::newRow("usepackage command3") << "\\usepackage{text,\ntext}" << (QList<int>()<<2<<6<<29<<29<<9)<< (QList<int>()<<0<<29<<0<<0<<0) << (QList<int>()<<0<<11<<12<<0<<4)  << (QList<int>()<<11<<6<<4<<4<<1) << (QList<int>()<<0<<0<<1<<1<<0);
    QTest::newRow("newcommand command") << "\\newcommand{text}{test}" << (QList<int>()<<2<<3<<27<<3<<1)<< (QList<int>()<<0<<27<<0<<48<<48) << (QList<int>()<<0<<11<<12<<17<<18)  << (QList<int>()<<11<<6<<4<<6<<4) << (QList<int>()<<0<<0<<1<<0<<1);
    QTest::newRow("newcommand command2") << "\\newcommand{\\ext}{test}" << (QList<int>()<<2<<3<<27<<3<<1)<< (QList<int>()<<0<<27<<0<<48<<48) << (QList<int>()<<0<<11<<12<<17<<18)  << (QList<int>()<<11<<6<<4<<6<<4) << (QList<int>()<<0<<0<<1<<0<<1);
    QTest::newRow("newcommand command3") << "\\newcommand{\\paragraph}{test}" << (QList<int>()<<2<<3<<27<<3<<1)<< (QList<int>()<<0<<27<<0<<48<<48) << (QList<int>()<<0<<11<<12<<23<<24)  << (QList<int>()<<11<<12<<10<<6<<4) << (QList<int>()<<0<<0<<1<<0<<1);
    QTest::newRow("documentclass command") << "\\documentclass{text}" << (QList<int>()<<2<<3<<35)<< (QList<int>()<<0<<35<<0) << (QList<int>()<<0<<14<<15)  << (QList<int>()<<14<<6<<4) << (QList<int>()<<0<<0<<1);
    QTest::newRow("text command, embedded") << "\\textbf{te\\textit{xt} bg}" << (QList<int>()<<2<<3<<1<<2<<3<<1<<1)<< (QList<int>()<<0<<24<<24<<24<<24<<24<<24) << (QList<int>()<<0<<7<<8<<10<<17<<18<<22)  << (QList<int>()<<7<<18<<2<<7<<4<<2<<2) << (QList<int>()<<0<<0<<1<<1<<1<<2<<1);
    QTest::newRow("graphics command") << "\\includegraphics{file}" << (QList<int>()<<2<<3<<18)<< (QList<int>()<<0<<18<<0) << (QList<int>()<<0<<16<<17)  << (QList<int>()<<16<<6<<4) << (QList<int>()<<0<<0<<1);
    QTest::newRow("graphics command with option") << "\\includegraphics[opt]{file}" << (QList<int>()<<2<<5<<21<<3<<18)<< (QList<int>()<<0<<20<<0<<18<<0) << (QList<int>()<<0<<16<<17<<21<<22)  << (QList<int>()<<16<<5<<3<<6<<4) << (QList<int>()<<0<<0<<1<<0<<1);
    QTest::newRow("graphics command with keyval") << "\\includegraphics[opt,opt=text]{file}" << (QList<int>()<<2<<5<<21<<21<<1<<3<<18)<< (QList<int>()<<0<<20<<0<<0<<22<<18<<0) << (QList<int>()<<0<<16<<17<<21<<25<<30<<31)  << (QList<int>()<<16<<14<<3<<3<<4<<6<<4) << (QList<int>()<<0<<0<<1<<1<<2<<0<<1);
    QTest::newRow("include command") << "\\include{text dsf}" << (QList<int>()<<2<<3<<17)<< (QList<int>()<<0<<17<<0) << (QList<int>()<<0<<8<<9)  << (QList<int>()<<8<<10<<8) << (QList<int>()<<0<<0<<1);
    QTest::newRow("include command2") << "\\include{text/dsf}" << (QList<int>()<<2<<3<<17)<< (QList<int>()<<0<<17<<0) << (QList<int>()<<0<<8<<9)  << (QList<int>()<<8<<10<<8) << (QList<int>()<<0<<0<<1);
    QTest::newRow("include command3") << "\\include{text\\dsf}" << (QList<int>()<<2<<3<<17)<< (QList<int>()<<0<<17<<0) << (QList<int>()<<0<<8<<9)  << (QList<int>()<<8<<10<<8) << (QList<int>()<<0<<0<<1);
}

void SmallUsefulFunctionsTest::test_latexLexing() {
    LatexParser lp=LatexParser::getInstance();
    LatexPackage pkg_graphics=loadCwlFile("graphicx.cwl");
    lp.commandDefs.unite(pkg_graphics.commandDescriptions);
    QFETCH(QString,lines);
    QFETCH(QList<int>, types);
    QFETCH(QList<int>, subtypes);
    QFETCH(QList<int>, starts);
    QFETCH(QList<int>, lengths);
    QFETCH(QList<int>, levels);

    QDocument *doc=new QDocument();
    doc->setText(lines,false);
    for(int i=0;i<doc->lines();i++){
        QDocumentLineHandle *dlh=doc->line(i).handle();
        simpleLexLatexLine(dlh);
    }
    TokenStack stack;
    CommandStack commandStack;
    for(int i=0;i<doc->lines();i++){
            QDocumentLineHandle *dlh=doc->line(i).handle();
            latexDetermineContexts2(dlh,stack,commandStack,lp);
    }
    TokenList tl;
    for(int i=0;i<doc->lines();i++){
        QDocumentLineHandle *dlh=doc->line(i).handle();
        tl.append(dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>());
    }
    for(int i=0;i<tl.length();i++){
        Tokens tk=tl.at(i);
        int type=types.value(i,0);
        int subtype=subtypes.value(i,0);
        int start=starts.value(i,0);
        int length=lengths.value(i,0);
        int level=levels.value(i,0);
        QVERIFY2(int(tk.type)==type,QString("incorrect type %1 != %2").arg(int(tk.type)).arg(type).toLatin1().constData());
        QVERIFY2(int(tk.subtype)==subtype,QString("incorrect subtype %1 != %2").arg(int(tk.subtype)).arg(subtype).toLatin1().constData());
        QVERIFY2(tk.start==start,QString("incorrect start (%1)").arg(i).toLatin1().constData());
        QVERIFY2(tk.length==length,QString("incorrect length (%1)").arg(i).toLatin1().constData());
        QVERIFY2(tk.level==level,QString("incorrect level  (%1)").arg(i).toLatin1().constData());
    }
    QVERIFY2(tl.length()==types.length(),"missing tokens");
    delete doc;

}

#endif


