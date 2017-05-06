#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "qdocumentcursor.h"
#include "qdocument.h"
#include "qdocumentline.h"
#include "qdocumentline_p.h"
#include "smallUsefulFunctions.h"
#include "smallUsefulFunctions_t.h"
#include "latexparser/latexparser.h"
#include "testutil.h"
#include <QtTest/QtTest>

// shortcuts and semantic types
typedef Token T;
typedef QList<int> TTypes;
typedef QList<int> STypes;
typedef QList<int> Length;
typedef QList<int> Starts;
typedef QList<int> Levels;

typedef QList<int> ATypes;

void SmallUsefulFunctionsTest::test_simpleLexing_data() {
    QTest::addColumn<QString>("line");
    QTest::addColumn<TTypes>("types");
    QTest::addColumn<Starts>("starts");
    QTest::addColumn<Length>("lengths");

    QTest::newRow("simple") << "bummerang"
                            << (TTypes() << T::word)
							<< (Starts() << 0)
							<< (Length() << 9);
    QTest::newRow("command") << "\\bummerang"
							 << (TTypes() << T::command)
							 << (Starts() << 0)
							 << (Length() << 10);
    QTest::newRow("command with symbol") << "\\_"
										 << (TTypes() << T::command)
										 << (Starts() << 0)
										 << (Length() << 2);
    QTest::newRow("command with symbol2") << "\\&"
										  << (TTypes() << T::command)
										  << (Starts() << 0)
										  << (Length() << 2);
    QTest::newRow("command with symbol3") << "\\__"
										  << (TTypes() << T::command << T::punctuation)
										  << (Starts() << 0 << 2)
										  << (Length() << 2 << 1);
    QTest::newRow("command with at") << "\\bummer@ng"
									 << (TTypes() << T::command)
									 << (Starts() << 0)
									 << (Length() << 10);
    QTest::newRow("command with arg") << "\\bummerang{abc}"
									  << (TTypes() << T::command << T::openBrace << T::word << T::closeBrace)
									  << (Starts() << 0 << 10 << 11 << 14)
									  << (Length() << 10 << 1 << 3 << 1);
    QTest::newRow("command with optional arg") << " \\bummerang  [abc  ]"
											   << (TTypes() << Token::command << 8 << 1 << 11)
											   << (Starts() << 1 << 13 << 14 << 19)
											   << (Length() << 10 << 1 << 3 << 1);
    QTest::newRow("punctation") << "bummerang."
								<< (TTypes() << T::word << T::punctuation)
								<< (Starts() << 0 << 9)
								<< (Length() << 9 << 1);
    QTest::newRow("symbol") << " a = b "
							<< (TTypes() << T::word << T::symbol << T::word)
							<< (Starts() << 1 << 3 << 5)
							<< (Length() << 1 << 1 << 1);
    QTest::newRow("umlaut") << "\"uber"
							<< (TTypes() << T::punctuation << T::word)
							<< (Starts() << 0 << 1)
							<< (Length() << 1 << 4);
    QTest::newRow("numbers") << "1.2"
							 << (TTypes() << T::number << T::punctuation << T::number)
							 << (Starts() << 0 << 1 << 2)
							 << (Length() << 1 << 1 << 1);
    QTest::newRow("numbers1") << "1em"
							  << (TTypes() << T::number << T::word)
							  << (Starts() << 0 << 1)
							  << (Length() << 1 << 2);
    QTest::newRow("numbers2") << "em2a"
							  << (TTypes() << T::word << T::number << T::word)
							  << (Starts() << 0 << 2 << 3)
							  << (Length() << 2 << 1 << 1);
    QTest::newRow("numbers3") << "\\text1"
							  << (TTypes() << T::command << T::number)
							  << (Starts() << 0 << 5)
							  << (Length() << 5 << 1);
    QTest::newRow("numbers4") << "45\\text4em"
							  << (TTypes() << T::number << T::command << T::number << T::word)
							  << (Starts() << 0 << 2 << 7 << 8)
							  << (Length() << 2 << 5 << 1 << 2);
    QTest::newRow("command with brackets") << "\\bummerang (abc,fgew)"
										   << (TTypes() << T::command << T::openBracket << T::word << T::punctuation << T::word << T::closeBracket)
										   << (Starts() << 0 << 11 << 12 << 15 << 16 << 20)
										   << (Length() << 10 << 1 << 3 << 1 << 4 << 1);
    QTest::newRow("comments") << "abc % \\text"
                              << (TTypes() << T::word << T::comment << T::command )
                              << (Starts() << 0 << 4 << 6 )
                              << (Length() << 3 << 1 << 5 );
}

void SmallUsefulFunctionsTest::test_simpleLexing() {
    QFETCH(QString, line);
    QFETCH(TTypes, types);
    QFETCH(Starts, starts);
    QFETCH(Length, lengths);
    QDocument *doc = new QDocument();
    QDocumentLineHandle *dlh = new QDocumentLineHandle(line, doc);
    simpleLexLatexLine(dlh);
    TokenList tl = dlh->getCookie(QDocumentLine::LEXER_RAW_COOKIE).value<TokenList>();
    for(int i=0; i<tl.length(); i++) {
        Token tk = tl.at(i);
        int type = types.value(i, 0);
        int start = starts.value(i, 0);
        int length = lengths.value(i, 0);
        QVERIFY2(int(tk.type) == type, QString("incorrect type %1 != %2").arg(int(tk.type)).arg(type).toLatin1().constData());
        QVERIFY2(tk.start == start, "incorrect start");
        QVERIFY2(tk.length == length, "incorrect length");
    }
    dlh->deref();
    delete doc;
}

void SmallUsefulFunctionsTest::test_latexLexing_data() {
    QTest::addColumn<QString>("lines");
    QTest::addColumn<TTypes>("types");
    QTest::addColumn<STypes>("subtypes");
    QTest::addColumn<Starts>("starts");
    QTest::addColumn<Length>("lengths");
    QTest::addColumn<Levels>("levels");

    QTest::newRow("simple") << "bummerang"
                            << (TTypes() << T::word)
                            << (STypes() << T::none)
                            << (Starts() << 0)
                            << (Length() << 9)
                            << (Levels() << 0);
    QTest::newRow("simple2") << "bummerang test"
                             << (TTypes() << T::word << T::word)
                             << (STypes() << T::none << T::none)
                             << (Starts() << 0 << 10)
                             << (Length() << 9 << 4)
                             << (Levels() << 0 << 0);
    QTest::newRow("simple3") << "bummerang\ntest"
                             << (TTypes() << T::word << T::word)
                             << (STypes() << T::none << T::none)
                             << (Starts() << 0 << 0)
                             << (Length() << 9 << 4)
                             << (Levels() << 0 << 0);
    QTest::newRow("text command") << "\\textbf{text}"
                                  << (TTypes() << T::command << T::braces << T::word)
                                  << (STypes() << T::none << T::text << T::text)
                                  << (Starts() << 0 << 7 << 8)
                                  << (Length() << 7 << 6 << 4)
                                  << (Levels() << 0 << 0 << 1);
    QTest::newRow("section command") << "\\section{text}"
                                     << (TTypes() << T::command << T::braces << T::word)
                                     << (STypes() << T::none << T::title << T::title)
                                     << (Starts() << 0 << 8 << 9)
                                     << (Length() << 8 << 6 << 4)
                                     << (Levels() << 0 << 0 << 1);
    QTest::newRow("section command, multi-line") << "\\section{text\ntest}"
                                     << (TTypes() << T::command << T::openBrace << T::word<< T::word<<T::closeBrace)
                                     << (STypes() << T::none << T::title << T::title<<T::title<<T::none)
                                     << (Starts() << 0 << 8 << 9<< 0 << 4)
                                     << (Length() << 8 << 5 << 4<< 4 << 1)
                                     << (Levels() << 0 << 0 << 1<< 1 << 0);
    QTest::newRow("section command, multi-line optional") << "\\section[ab\ncd]{text\ntest}"
                                     << (TTypes() << T::command << T::openSquare << T::word<< T::word<<T::closeSquareBracket<< T::openBrace << T::word<< T::word<<T::closeBrace)
                                     << (STypes() << T::none <<T::title << T::title<<T::title<<T::none << T::title << T::title<<T::title<<T::none)
                                     << (Starts() << 0 << 8 << 9 << 0 << 2 << 3 << 4 << 0 << 4)
                                     << (Length() << 8 << 3 << 2 << 2 << 1 << 5 << 4 << 4 << 1)
                                     << (Levels() << 0 << 0 << 1 << 1 << 0 << 0 << 1 << 1 << 0);
    QTest::newRow("usepackage command") << "\\usepackage{text}"
                                        << (TTypes() << T::command << T::braces << T::package)
                                        << (STypes() << T::none << T::package << T::none)
                                        << (Starts() << 0 << 11 << 12)
                                        << (Length() << 11 << 6 << 4)
                                        << (Levels() << 0 << 0 << 1);
    QTest::newRow("usepackage command2") << "\\usepackage{text,text}"
                                         << (TTypes() << T::command << T::braces << T::package << T::package)
                                         << (STypes() << T::none << T::package << T::none << T::none)
                                         << (Starts() << 0 << 11 << 12 << 17)
                                         << (Length() << 11 << 11 << 4 << 4)
                                         << (Levels() << 0 << 0 << 1 << 1);
    QTest::newRow("usepackage command3") << "\\usepackage{text,\ntext}"
                                         << (TTypes() << T::command << T::openBrace << T::package << T::package << T::closeBrace)
                                         << (STypes() << T::none << T::package << T::none << T::none << T::none)
                                         << (Starts() << 0 << 11 << 12 << 0 << 4)
                                         << (Length() << 11 << 6 << 4 << 4 << 1)
                                         << (Levels() << 0 << 0 << 1 << 1 << 0);
    QTest::newRow("newcommand command") << "\\newcommand{text}{test}"
                                        << (TTypes() << T::command << T::braces << T::def << T::braces << T::word)
                                        << (STypes() << T::none << T::def << T::none << T::definition << T::definition)
                                        << (Starts() << 0 << 11 << 12 << 17 << 18)
                                        << (Length() << 11 << 6 << 4 << 6 << 4)
                                        << (Levels() << 0 << 0 << 1 << 0 << 1);
    QTest::newRow("newcommand command2") << "\\newcommand{\\ext}{test}"
                                         << (TTypes() << T::command << T::braces << T::def << T::braces << T::word)
                                         << (STypes() << T::none << T::def << T::none << T::definition << T::definition)
                                         << (Starts() << 0 << 11 << 12 << 17 << 18)
                                         << (Length() << 11 << 6 << 4 << 6 << 4)
                                         << (Levels() << 0 << 0 << 1 << 0 << 1);
    QTest::newRow("newcommand command3") << "\\newcommand{\\paragraph}{test}"
                                         << (TTypes() << T::command << T::braces << T::def << T::braces << T::word)
                                         << (STypes() << T::none << T::def << T::none << T::definition << T::definition)
                                         << (Starts() << 0 << 11 << 12 << 23 << 24)
                                         << (Length() << 11 << 12 << 10 << 6 << 4)
                                         << (Levels() << 0 << 0 << 1 << 0 << 1);
    QTest::newRow("documentclass command") << "\\documentclass{text}"
                                           << (TTypes() << T::command << T::braces << T::documentclass)
                                           << (STypes() << T::none << T::documentclass << T::none)
                                           << (Starts() << 0 << 14 << 15)
                                           << (Length() << 14 << 6 << 4)
                                           << (Levels() << 0 << 0 << 1);
    QTest::newRow("text command, embedded") << "\\textbf{te\\textit{xt} bg}"
                                            << (TTypes() << T::command << T::braces << T::word << T::command << T::braces << T::word << T::word)
                                            << (STypes() << T::none << T::text << T::text << T::text << T::text << T::text << T::text)
                                            << (Starts() << 0 << 7 << 8 << 10 << 17 << 18 << 22)
                                            << (Length() << 7 << 18 << 2 << 7 << 4 << 2 << 2)
                                            << (Levels() << 0 << 0 << 1 << 1 << 1 << 2 << 1);
    QTest::newRow("text command with comment") << "\\textbf{te % bg}"
                                            << (TTypes() << T::command << T::openBrace << T::word )
                                            << (STypes() << T::none << T::text << T::text )
                                            << (Starts() << 0 << 7 << 8 )
                                            << (Length() << 7 << 4 << 2 )
                                            << (Levels() << 0 << 0 << 1 );
    QTest::newRow("graphics command") << "\\includegraphics{file}"
                                      << (TTypes() << T::command << T::braces << T::imagefile)
                                      << (STypes() << T::none << T::imagefile << T::none)
                                      << (Starts() << 0 << 16 << 17)
                                      << (Length() << 16 << 6 << 4)
                                      << (Levels() << 0 << 0 << 1);
    QTest::newRow("graphics command with option") << "\\includegraphics[opt]{file}"
                                                  << (TTypes() << T::command << T::squareBracket << 21 << T::braces << T::imagefile)
                                                  << (STypes() << T::none << T::keyValArg << T::none << T::imagefile << T::none)
                                                  << (Starts() << 0 << 16 << 17 << 21 << 22)
                                                  << (Length() << 16 << 5 << 3 << 6 << 4)
                                                  << (Levels() << 0 << 0 << 1 << 0 << 1);
    QTest::newRow("graphics command with keyval") << "\\includegraphics[opt,opt=text]{file}"
                                                  << (TTypes() << T::command << T::squareBracket << T::keyVal_key << T::keyVal_key << T::word << T::braces << T::imagefile)
                                                  << (STypes() << T::none << T::keyValArg << T::none << T::none << T::keyVal_val << T::imagefile << T::none)
                                                  << (Starts() << 0 << 16 << 17 << 21 << 25 << 30 << 31)
                                                  << (Length() << 16 << 14 << 3 << 3 << 4 << 6 << 4)
                                                  << (Levels() << 0 << 0 << 1 << 1 << 2 << 0 << 1);
    QTest::newRow("include command") << "\\include{text dsf}"
                                     << (TTypes() << T::command << T::braces << T::file)
                                     << (STypes() << T::none << T::file << T::none)
                                     << (Starts() << 0 << 8 << 9)
                                     << (Length() << 8 << 10 << 8)
                                     << (Levels() << 0 << 0 << 1);
    QTest::newRow("include command2") << "\\include{text/dsf}"
                                      << (TTypes() << T::command << T::braces << T::file)
                                      << (STypes() << T::none << T::file << T::none)
                                      << (Starts() << 0 << 8 << 9)
                                      << (Length() << 8 << 10 << 8)
                                      << (Levels() << 0 << 0 << 1);
    QTest::newRow("include command3") << "\\include{text\\dsf}"
                                      << (TTypes() << T::command << T::braces << T::file)
                                      << (STypes() << T::none << T::file << T::none)
                                      << (Starts() << 0 << 8 << 9)
                                      << (Length() << 8 << 10 << 8)
                                      << (Levels() << 0 << 0 << 1);
}

void SmallUsefulFunctionsTest::test_latexLexing() {
    LatexParser lp = LatexParser::getInstance();
    LatexPackage pkg_graphics = loadCwlFile("graphicx.cwl");
    lp.commandDefs.unite(pkg_graphics.commandDescriptions);
    QFETCH(QString,lines);
    QFETCH(TTypes, types);
    QFETCH(STypes, subtypes);
    QFETCH(Starts, starts);
    QFETCH(Length, lengths);
    QFETCH(Levels, levels);

    QDocument *doc = new QDocument();
    doc->setText(lines, false);
    for(int i=0; i<doc->lines(); i++){
        QDocumentLineHandle *dlh = doc->line(i).handle();
        simpleLexLatexLine(dlh);
    }
    TokenStack stack;
    CommandStack commandStack;
    for(int i=0; i<doc->lines(); i++){
            QDocumentLineHandle *dlh = doc->line(i).handle();
            latexDetermineContexts2(dlh, stack, commandStack, lp);
    }
    TokenList tl;
    for(int i=0; i<doc->lines(); i++){
        QDocumentLineHandle *dlh = doc->line(i).handle();
        tl.append(dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>());
    }
    for(int i=0; i<tl.length(); i++){
        Token tk = tl.at(i);
        int type = types.value(i, 0);
        int subtype = subtypes.value(i, 0);
        int start = starts.value(i, 0);
        int length = lengths.value(i, 0);
        int level = levels.value(i, 0);
        QVERIFY2(int(tk.type) == type, QString("incorrect type %1 != %2").arg(int(tk.type)).arg(type).toLatin1().constData());
        QVERIFY2(int(tk.subtype) == subtype, QString("incorrect subtype %1 != %2").arg(int(tk.subtype)).arg(subtype).toLatin1().constData());
        QVERIFY2(tk.start == start, QString("incorrect start (%1)").arg(i).toLatin1().constData());
        QVERIFY2(tk.length == length, QString("incorrect length (%1)").arg(i).toLatin1().constData());
        QVERIFY2(tk.level == level, QString("incorrect level  (%1)").arg(i).toLatin1().constData());
    }
    QVERIFY2(tl.length() == types.length(), "missing tokens");
    delete doc;
}

void SmallUsefulFunctionsTest::test_findCommandWithArgsFromTL_data() {
    QTest::addColumn<QString>("lines");
    QTest::addColumn<TTypes>("types");
    QTest::addColumn<STypes>("subtypes");
    QTest::addColumn<Starts>("starts");
    QTest::addColumn<Length>("lengths");
    QTest::addColumn<Levels>("levels");


    QTest::newRow("newcommand command") << "\\newcommand{text}{test}"
                                        << (TTypes() << T::braces << T::braces)
                                        << (STypes() <<  T::def <<  T::definition )
                                        << (Starts() <<  11 <<  17 )
                                        << (Length() <<  6 << 6 )
                                        << (Levels() << 0 << 0 );
    QTest::newRow("newcommand command2") << "\\newcommand{\\ext}{test}"
                                         << (TTypes() << T::braces << T::braces)
                                         << (STypes() <<  T::def <<  T::definition )
                                         << (Starts() <<  11 <<  17 )
                                         << (Length() <<  6 << 6 )
                                         << (Levels() << 0 << 0 );
    QTest::newRow("newcommand command3") << "\\newcommand{\\paragraph}{test}"
                                         << (TTypes() << T::braces << T::braces)
                                         << (STypes() <<  T::def <<  T::definition )
                                         << (Starts() <<  11 <<  23 )
                                         << (Length() <<  12 << 6 )
                                         << (Levels() << 0 << 0 );
    QTest::newRow("newcommand command, no braces") << "\\newcommand text {test}"
                                        << (TTypes() << T::word << T::braces)
                                        << (STypes() <<  T::def <<  T::definition )
                                        << (Starts() <<  12 <<  17 )
                                        << (Length() <<  4 << 6 )
                                        << (Levels() << 0 << 0 );
    QTest::newRow("newcommand command, no braces2") << "\\newcommand text test"
                                        << (TTypes() << T::word << T::word)
                                        << (STypes() <<  T::def <<  T::definition )
                                        << (Starts() <<  12 <<  17 )
                                        << (Length() <<  4 << 4 )
                                        << (Levels() << 0 << 0 );
    QTest::newRow("documentclass command") << "\\documentclass{text}"
                                           << (TTypes() << T::braces )
                                           << (STypes() <<  T::documentclass )
                                           << (Starts() <<  14 )
                                           << (Length() <<  6 )
                                           << (Levels() << 0 );
    QTest::newRow("text command, embedded") << "\\textbf{te\\textit{xt} bg}"
                                            << (TTypes() << T::braces )
                                            << (STypes() <<  T::text )
                                            << (Starts() <<  7 )
                                            << (Length() <<  18 )
                                            << (Levels() << 0 );
    QTest::newRow("text command, embedded ,open") << "\\textbf{te\\textit{xt} bg"
                                            << (TTypes() << T::openBrace )
                                            << (STypes() <<  T::text )
                                            << (Starts() <<  7 )
                                            << (Length() <<  17 )
                                            << (Levels() << 0 );

}

void SmallUsefulFunctionsTest::test_findCommandWithArgsFromTL() {
    LatexParser lp = LatexParser::getInstance();
    LatexPackage pkg_graphics = loadCwlFile("graphicx.cwl");
    lp.commandDefs.unite(pkg_graphics.commandDescriptions);
    QFETCH(QString,lines);
    QFETCH(TTypes, types);
    QFETCH(STypes, subtypes);
    QFETCH(Starts, starts);
    QFETCH(Length, lengths);
    QFETCH(Levels, levels);

    QDocument *doc = new QDocument();
    doc->setText(lines, false);
    for(int i=0; i<doc->lines(); i++){
        QDocumentLineHandle *dlh = doc->line(i).handle();
        simpleLexLatexLine(dlh);
    }
    TokenStack stack;
    CommandStack commandStack;
    for(int i=0; i<doc->lines(); i++){
            QDocumentLineHandle *dlh = doc->line(i).handle();
            latexDetermineContexts2(dlh, stack, commandStack, lp);
    }
    QDocumentLineHandle *dlh = doc->line(0).handle();
    TokenList tl= dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList >();
    // first token is command
    Token tkCmd;
    TokenList args;
    int cmdStart = findCommandWithArgsFromTL(tl, tkCmd, args, 0, false);
    QVERIFY(cmdStart==0);
    for(int i=0; i<args.length(); i++){
        Token tk = args.at(i);
        int type = types.value(i, 0);
        int subtype = subtypes.value(i, 0);
        int start = starts.value(i, 0);
        int length = lengths.value(i, 0);
        int level = levels.value(i, 0);
        QVERIFY2(int(tk.type) == type, QString("incorrect type %1 != %2").arg(int(tk.type)).arg(type).toLatin1().constData());
        QVERIFY2(int(tk.subtype) == subtype, QString("incorrect subtype %1 != %2").arg(int(tk.subtype)).arg(subtype).toLatin1().constData());
        QVERIFY2(tk.start == start, QString("incorrect start (%1)").arg(i).toLatin1().constData());
        QVERIFY2(tk.length == length, QString("incorrect length (%1)").arg(i).toLatin1().constData());
        QVERIFY2(tk.level == level, QString("incorrect level  (%1)").arg(i).toLatin1().constData());
    }
    QVERIFY2(args.length() == types.length(), "missing tokens");
    delete doc;
}

void SmallUsefulFunctionsTest::test_getArg_data() {
    QTest::addColumn<QString>("lines");
    QTest::addColumn<STypes>("types");
    QTest::addColumn<QStringList>("desiredResults");


    QTest::newRow("newcommand command") << "\\newcommand{text}{test}"
                                        << (STypes() <<T::def << T::definition)
                                        << (QStringList() <<"text" <<"test");
    QTest::newRow("newcommand command2") << "\\newcommand{\\ext}{test}"
                                         <<  (STypes() <<T::def << T::definition)
                                         << (QStringList() <<"\\ext"<<"test");
    QTest::newRow("newcommand command, no braces") << "\\newcommand text {test}"
                                        <<  (STypes() <<T::def<< T::definition)
                                        << (QStringList() <<"text"<<"test");
    QTest::newRow("newcommand command, no braces2") << "\\newcommand text test"
                                        <<  (STypes() <<T::def<< T::definition) << (QStringList() <<"text"<< "test");
    QTest::newRow("documentclass command") << "\\documentclass{text}"
                                           <<  (STypes() << T::documentclass )<< (QStringList() <<"text");
    QTest::newRow("text command, embedded") << "\\textbf{te\\textit{xt} bg}"
                                            << (STypes() <<T::text) << (QStringList() <<"te\\textit{xt} bg");
    QTest::newRow("text command, embedded ,open") << "\\textbf{  te\\textit{xt} bg"
                                            <<   (STypes() <<T::text) << (QStringList() <<"  te\\textit{xt} bg");

}

void SmallUsefulFunctionsTest::test_getArg() {
    LatexParser lp = LatexParser::getInstance();
    LatexPackage pkg_graphics = loadCwlFile("graphicx.cwl");
    lp.commandDefs.unite(pkg_graphics.commandDescriptions);
    QFETCH(QString,lines);
    QFETCH(STypes, types);
    QFETCH(QStringList, desiredResults);

    QDocument *doc = new QDocument();
    doc->setText(lines, false);
    for(int i=0; i<doc->lines(); i++){
        QDocumentLineHandle *dlh = doc->line(i).handle();
        simpleLexLatexLine(dlh);
    }
    TokenStack stack;
    CommandStack commandStack;
    for(int i=0; i<doc->lines(); i++){
            QDocumentLineHandle *dlh = doc->line(i).handle();
            latexDetermineContexts2(dlh, stack, commandStack, lp);
    }
    QDocumentLineHandle *dlh = doc->line(0).handle();
    TokenList tl= dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList >();
    // first token is command
    Token tkCmd;
    TokenList args;
    findCommandWithArgsFromTL(tl, tkCmd, args, 0, false);
    for(int i=0;i<types.length();i++){
        T::TokenType type=T::TokenType(types.at(i));
        QString result=getArg(args,type);
        QVERIFY(desiredResults.at(i)==result);
    }
    delete doc;
}

void SmallUsefulFunctionsTest::test_getArg2_data() {
    QTest::addColumn<QString>("lines");
    QTest::addColumn<ATypes>("types");
    QTest::addColumn<QList<int> >("nr");
    QTest::addColumn<QStringList>("desiredResults");


    QTest::newRow("newcommand command") << "\\newcommand{text}{test}"
                                        << (ATypes() <<ArgumentList::Mandatory << ArgumentList::Mandatory<<ArgumentList::MandatoryWithBraces<<ArgumentList::MandatoryWithBraces)
                                        << (QList<int>()<<0<<1<<0<<1)
                                        << (QStringList() <<"text" <<"test"<<"text"<<"test");
    QTest::newRow("newcommand command2") << "\\newcommand{\\ext}{test}"
                                         <<  (ATypes() <<ArgumentList::Mandatory << ArgumentList::Mandatory)
                                         << (QList<int>()<<0<<1)
                                         << (QStringList() <<"\\ext"<<"test");
    QTest::newRow("newcommand command, no braces") << "\\newcommand text {test}"
                                        <<  (ATypes() <<ArgumentList::Mandatory<< ArgumentList::Mandatory<<ArgumentList::MandatoryWithBraces<< ArgumentList::MandatoryWithBraces)
                                        << (QList<int>()<<0<<1<<0<<1)
                                        << (QStringList() <<"text"<<"test"<<""<<"");
    QTest::newRow("newcommand command, no braces2") << "\\newcommand text test"
                                        <<  (ATypes() <<ArgumentList::Mandatory<< ArgumentList::Mandatory)
                                        << (QList<int>()<<0<<1)
                                        << (QStringList() <<"text"<< "test");
    QTest::newRow("newcommand command, no braces3") << "\\newcommand{text} test"
                                        <<  (ATypes() <<ArgumentList::Mandatory<< ArgumentList::Mandatory<<ArgumentList::MandatoryWithBraces<< ArgumentList::MandatoryWithBraces)
                                        << (QList<int>()<<0<<1<<0<<1)
                                        << (QStringList() <<"text"<< "test"<<"text"<< "");
    QTest::newRow("documentclass command") << "\\documentclass{text}"
                                           <<  (ATypes() << ArgumentList::Mandatory )
                                           << (QList<int>()<<0)
                                           << (QStringList() <<"text");
    QTest::newRow("text command, embedded") << "\\textbf{te\\textit{xt} bg}"
                                            << (ATypes() <<ArgumentList::Mandatory)
                                            << (QList<int>()<<0)
                                            << (QStringList() <<"te\\textit{xt} bg");
    QTest::newRow("text command, embedded ,open") << "\\textbf{  te\\textit{xt} bg"
                                            << (ATypes() <<ArgumentList::Mandatory)
                                            << (QList<int>()<<0)
                                            << (QStringList() <<"  te\\textit{xt} bg ");
    QTest::newRow("text command, multi-line") << "\\textbf{  te\nasdasd}"
                                            << (ATypes() <<ArgumentList::Mandatory)
                                            << (QList<int>()<<0)
                                            << (QStringList() <<"  te asdasd");
    QTest::newRow("text command, multi-line2") << "\\textbf{  te\nasdasd"
                                            << (ATypes() <<ArgumentList::Mandatory)
                                            << (QList<int>()<<0)
                                            << (QStringList() <<"  te asdasd ");
    QTest::newRow("text command, multi-line3") << "\\textbf{  te\nasdasd\n op\n\n}"
                                            << (ATypes() <<ArgumentList::Mandatory)
                                            << (QList<int>()<<0)
                                            << (QStringList() <<"  te asdasd  op ");
    QTest::newRow("text command, multi-line4") << "\\textbf{  te\nasdasd\n op\n\ndd}"
                                            << (ATypes() <<ArgumentList::Mandatory)
                                            << (QList<int>()<<0)
                                            << (QStringList() <<"  te asdasd  op dd");
    QTest::newRow("text command, multi-line5") << "\\textbf{  te\nasdasd\n op\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\ndd}"
                                            << (ATypes() <<ArgumentList::Mandatory)
                                            << (QList<int>()<<0)
                                            << (QStringList() <<"  te asdasd  op dd");
    QTest::newRow("text command, multi-line6") << "\\textbf{  te\nasdasd\n op\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\ndd}"
                                            << (ATypes() <<ArgumentList::Mandatory)
                                            << (QList<int>()<<0)
                                            << (QStringList() <<"  te asdasd  op ");
    QTest::newRow("text command, multi-line7") << "\\textbf{  te\nasdasd\n op\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\ndd}" // runawaylimit=30 assumed
                                            << (ATypes() <<ArgumentList::Mandatory)
                                            << (QList<int>()<<0)
                                            << (QStringList() <<"  te asdasd  op ");
    QTest::newRow("text command, multi-line,runaway") << "\\textbf{  te\nasdasd\n op\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\ndd}" // runawaylimit=30 assumed
                                            << (ATypes() <<ArgumentList::Mandatory)
                                            << (QList<int>()<<0)
                                            << (QStringList() <<"  te asdasd  op ");
    QTest::newRow("optional argument") << "\\section[ab]{text}"
                                            << (ATypes() <<ArgumentList::Mandatory<<ArgumentList::Optional<<ArgumentList::MandatoryWithBraces)
                                            << (QList<int>()<<0<<0<<0)
                                            << (QStringList() <<"text"<<"ab"<<"text");
    QTest::newRow("optional argument2") << "\\section[ab\ncd]{text}"
                                            << (ATypes() <<ArgumentList::Mandatory<<ArgumentList::Optional)
                                            << (QList<int>()<<0<<0)
                                            << (QStringList() <<"text"<<"ab cd");
    QTest::newRow("optional argument, with comment") << "\\section[ab% sdfg\ncd]{text}"
                                            << (ATypes() <<ArgumentList::Mandatory<<ArgumentList::Optional)
                                            << (QList<int>()<<0<<0)
                                            << (QStringList() <<"text"<<"abcd");
    QTest::newRow("optional argument3") << "\\section[]{text}"
                                            << (ATypes() <<ArgumentList::Mandatory<<ArgumentList::Optional)
                                            << (QList<int>()<<0<<0)
                                            << (QStringList() <<"text"<<"[]");
    QTest::newRow("optional argument4") << "\\section{text}"
                                            << (ATypes() <<ArgumentList::Mandatory<<ArgumentList::Optional)
                                            << (QList<int>()<<0<<0)
                                            << (QStringList() <<"text"<<"");
    QTest::newRow("multi-line") << "\\textbf\n\n{  te\nasdasd}"
                                            << (ATypes() <<ArgumentList::Mandatory)
                                            << (QList<int>()<<0)
                                            << (QStringList() <<"  te asdasd");
    QTest::newRow("text command, multi-line with comment") << "\\textbf{  te % Hello\nasdasd}"
                                            << (ATypes() <<ArgumentList::Mandatory)
                                            << (QList<int>()<<0)
                                            << (QStringList() <<"  te asdasd");
    QTest::newRow("text command, multi-line with comment2") << "\\textbf{  te % Hello\nasda% sdfsdf\nsd}"
                                            << (ATypes() <<ArgumentList::Mandatory)
                                            << (QList<int>()<<0)
                                            << (QStringList() <<"  te asdasd");

}

void SmallUsefulFunctionsTest::test_getArg2() {
    LatexParser lp = LatexParser::getInstance();
    LatexPackage pkg_graphics = loadCwlFile("graphicx.cwl");
    lp.commandDefs.unite(pkg_graphics.commandDescriptions);
    QFETCH(QString,lines);
    QFETCH(ATypes, types);
    QFETCH(QList<int>, nr);
    QFETCH(QStringList, desiredResults);

    QDocument *doc = new QDocument();
    doc->setText(lines, false);
    for(int i=0; i<doc->lines(); i++){
        QDocumentLineHandle *dlh = doc->line(i).handle();
        simpleLexLatexLine(dlh);
    }
    TokenStack stack;
    CommandStack commandStack;
    for(int i=0; i<doc->lines(); i++){
            QDocumentLineHandle *dlh = doc->line(i).handle();
            latexDetermineContexts2(dlh, stack, commandStack, lp);
    }
    QDocumentLineHandle *dlh = doc->line(0).handle();
    TokenList tl= dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList >();
    // first token is command
    Token tkCmd;
    TokenList args;
    findCommandWithArgsFromTL(tl, tkCmd, args, 0, false);
    for(int i=0;i<types.length();i++){
        ArgumentList::ArgType type=ArgumentList::ArgType(types.at(i));
        QString result=getArg(args,dlh,nr.at(i),type);
        QVERIFY(desiredResults.at(i)==result);
    }
    delete doc;
}

void SmallUsefulFunctionsTest::test_getTokenAtCol_data() {
    QTest::addColumn<QString>("lines");
    QTest::addColumn<QList<int> >("nr");
    QTest::addColumn<TTypes>("desiredResults");
    QTest::addColumn<TTypes>("desiredResults2"); // with option first=true


    QTest::newRow("simple") << "bummerang  \\test"
                            << (QList<int>()<<0<<4<<9<<10<<11<<12<<16)
                            << (TTypes() << T::word << T::word << T::word << T::none << T::commandUnknown << T::commandUnknown << T::commandUnknown)
                            << (TTypes() << T::word << T::word << T::word << T::none << T::commandUnknown << T::commandUnknown << T::commandUnknown)
                            ;

    QTest::newRow("simple2") << "abc\\test"
                            << (QList<int>()<<3)
                            << (TTypes() << T::commandUnknown )
                            << (TTypes() << T::word )
                            ;
    QTest::newRow("nested1") << "\\textbf{abc}"
                            << (QList<int>()<<3<<7<<8<<11<<12)
                            << (TTypes() << T::command << T::braces  << T::word   << T::word   << T::braces )
                            << (TTypes() << T::command << T::command << T::braces << T::braces << T::braces )
                            ;
    QTest::newRow("nested2") << "\\section[abc\\textbf{abc}]{abc}"
                            << (QList<int>()<<3<<8<<14<<20<<21)
                            << (TTypes() << T::command << T::squareBracket  << T::command       << T::word          << T::word )
                            << (TTypes() << T::command << T::command        << T::squareBracket << T::squareBracket << T::squareBracket )
                            ;

}

void SmallUsefulFunctionsTest::test_getTokenAtCol() {
    LatexParser lp = LatexParser::getInstance();
    LatexPackage pkg_graphics = loadCwlFile("graphicx.cwl");
    lp.commandDefs.unite(pkg_graphics.commandDescriptions);
    QFETCH(QString,lines);
    QFETCH(QList<int>, nr);
    QFETCH(TTypes, desiredResults);
    QFETCH(TTypes, desiredResults2); // with option first=true

    QDocument *doc = new QDocument();
    doc->setText(lines, false);
    for(int i=0; i<doc->lines(); i++){
        QDocumentLineHandle *dlh = doc->line(i).handle();
        simpleLexLatexLine(dlh);
    }
    TokenStack stack;
    CommandStack commandStack;
    for(int i=0; i<doc->lines(); i++){
            QDocumentLineHandle *dlh = doc->line(i).handle();
            latexDetermineContexts2(dlh, stack, commandStack, lp);
    }
    QDocumentLineHandle *dlh = doc->line(0).handle();
    TokenList tl= dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList >();

    for(int i=0;i<nr.length();i++){
        int p=getTokenAtCol(tl,nr.at(i));
        Token tk=getTokenAtCol(dlh,nr.at(i));
        QVERIFY(tl.value(p)==tk); // cross check the two almost identical functions
        QVERIFY(desiredResults.at(i)==tk.type);
        p=getTokenAtCol(tl,nr.at(i),true);
        tk=getTokenAtCol(dlh,nr.at(i),true);
        QVERIFY(tl.value(p)==tk); // cross check the two almost identical functions
        QVERIFY(desiredResults2.at(i)==tk.type);
    }
    delete doc;
}

void SmallUsefulFunctionsTest::test_getCommandFromToken_data() {
    QTest::addColumn<QString>("lines");
    QTest::addColumn<int >("nr");
    QTest::addColumn<QString>("desiredResult");


    QTest::newRow("simple") << "bummerang  \\test"
                            << 0
                            << "";

    QTest::newRow("simple2") << "bummerang  \\section{abc}"
                            << 3
                            << "\\section";

    QTest::newRow("simple3") << "bummerang  \\section{abc cde}"
                            << 4
                            << "\\section";

    QTest::newRow("simple4") << "bummerang  \\section{abc cde}"
                            << 2
                            << "\\section";
    QTest::newRow("optonal") << "bummerang  \\section[ab ab]{abc cde}"
                            << 2
                            << "\\section";
    QTest::newRow("optonal2") << "bummerang  \\section[ab ab]{abc cde}"
                            << 3
                            << "\\section";
    QTest::newRow("optonal3") << "bummerang  \\section[ab ab]{abc cde}"
                            << 4
                            << "\\section";
    QTest::newRow("optonal4") << "bummerang  \\section[ab ab]{abc cde}"
                            << 5
                            << "\\section";
    QTest::newRow("optonal5") << "bummerang  \\section[ab ab]{abc cde}"
                            << 6
                            << "\\section";
    QTest::newRow("nested") << "bummerang  \\section{abc \\textbf{cde}}"
                            << 3
                            << "\\section";
    QTest::newRow("nested1") << "bummerang  \\section{abc \\textbf{cde}}"
                            << 4
                            << "\\section";
    QTest::newRow("nested2") << "bummerang  \\section{abc \\textbf{cde}}"
                            << 5
                            << "\\textbf";
    QTest::newRow("nested3") << "bummerang  \\section{abc \\textbf{cde}}"
                            << 6
                            << "\\textbf";


}

void SmallUsefulFunctionsTest::test_getCommandFromToken() {
    LatexParser lp = LatexParser::getInstance();
    LatexPackage pkg_graphics = loadCwlFile("graphicx.cwl");
    lp.commandDefs.unite(pkg_graphics.commandDescriptions);
    QFETCH(QString,lines);
    QFETCH(int, nr);
    QFETCH(QString, desiredResult);

    QDocument *doc = new QDocument();
    doc->setText(lines, false);
    for(int i=0; i<doc->lines(); i++){
        QDocumentLineHandle *dlh = doc->line(i).handle();
        simpleLexLatexLine(dlh);
    }
    TokenStack stack;
    CommandStack commandStack;
    for(int i=0; i<doc->lines(); i++){
            QDocumentLineHandle *dlh = doc->line(i).handle();
            latexDetermineContexts2(dlh, stack, commandStack, lp);
    }
    QDocumentLineHandle *dlh = doc->line(0).handle();
    TokenList tl= dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList >();

    QString result=getCommandFromToken(tl.at(nr));

    QVERIFY(result==desiredResult);

    delete doc;
}

#endif


