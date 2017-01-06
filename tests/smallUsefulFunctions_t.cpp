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

#endif


