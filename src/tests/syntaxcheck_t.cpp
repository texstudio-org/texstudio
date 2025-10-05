
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "syntaxcheck_t.h"
#include "tablemanipulation.h"
#include "qdocumentcursor.h"
#include "qdocument.h"
#include "qeditor.h"
#include "latexdocument.h"
#include "latexeditorview_config.h"

//#include "syntaxcheck.h"
#include "testutil.h"
#include <QtTest/QtTest>
SyntaxCheckTest::SyntaxCheckTest(LatexEditorView* ed): edView(ed){}

void SyntaxCheckTest::checktabular_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("row");
	QTest::addColumn<int>("col");
	QTest::addColumn<QString>("expectedMessage");

	//-------------cursor without selection--------------
    QTest::newRow("all okay")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 0
		<< "no error";

	QTest::newRow("too little cols")
		<< "\\begin{tabular}{ll}\na\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 1
		<< "cols in tabular missing";

	QTest::newRow("too many cols")
		<< "\\begin{tabular}{ll}\na&b&b2\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 6
		<< "more cols in tabular than specified";

    QTest::newRow("too many cols 2")
		<< "\\begin{tabular}{ll}\na&b&b2\\\\c&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 6
		<< "more cols in tabular than specified";

	QTest::newRow("no error second col")
		<< "\\begin{tabular}{ll}\na&b&b2\\\\c&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 11
		<< "no error";

    QTest::newRow("no error second col 2")
		<< "\\begin{tabular}{ll}\na&b&b2\\\\c&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 13
		<< "no error";

	QTest::newRow("too many cols second col")
		<< "\\begin{tabular}{lll}\na&b&b2\\\\c&d&e&f\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 15
		<< "more cols in tabular than specified";

	QTest::newRow("too many cols ")
		<< "\\begin{tabular}{lll}\n&&&\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 3
		<< "more cols in tabular than specified";

	QTest::newRow("no error 3 cols")
		<< "\\begin{tabular}{lll}\na&b&b2\\\\c&d&e&f\\\\\n\\end{tabular}\n"
		<< 1 << 6
		<< "no error";

    QTest::newRow("no error 3 cols 2")
		<< "\\begin{tabular}{lll}\na&b&b2\\\\c&d&e&f\\\\\n\\end{tabular}\n"
		<< 1 << 8
		<< "no error";

	QTest::newRow("no error 3 cols, multicolumn")
		<< "\\begin{tabular}{lll}\n\\multicolumn{2}{c}{Hallo}&b2\\\\c&d&e&f\\\\\n\\end{tabular}\n"
		<< 1 << 29
		<< "no error";

    QTest::newRow("no error 3 cols, multicolumn 2")
		<< "\\begin{tabular}{lll}\n\\multicolumn{2}{c}{Hallo}&b2\\\\c&d&e&f\\\\\n\\end{tabular}\n"
		<< 1 << 27
		<< "no error";

	QTest::newRow("too many cols, 3 cols, multicolumn v1")
			<< "\\begin{tabular}{lll}\n\\multicolumn{2}{c}{Hallo}&b2&b3\\\\c&d&e&f\\\\\n\\end{tabular}\n"
			<< 1 << 31
			<< "more cols in tabular than specified";

	QTest::newRow("too little cols, 3 cols, multicolumn v2")
			<< "\\begin{tabular}{lll}\n\\multicolumn{2}{c}{Hallo}\\\\c&d&e&f\\\\\n\\end{tabular}\n"
			<< 1 << 26
			<< "cols in tabular missing";

    QTest::newRow("tabu")
            << "\\usepackage{tabu}\\begin{tabu}{lll}\n\\multicolumn{2}{c}{Hallo}\\\\c&d&e&f\\\\\n\\end{tabu}\n"
            << 1 << 26
            << "cols in tabular missing";

    QTest::newRow("tabu2")
            << "\\usepackage{tabu}\\begin{tabu}to \\linewidth {lll}\n\\multicolumn{2}{c}{Hallo}\\\\c&d&e&f\\\\\n\\end{tabu}\n"
            << 1 << 26
            << "cols in tabular missing";

    QTest::newRow("tabu3")
            << "\\usepackage{tabu}\\begin{tabu}to \\linewidth {|*{3}{l|}}\n\\multicolumn{2}{c}{Hallo}\\\\c&d&e&f\\\\\n\\end{tabu}\n"
            << 1 << 26
            << "cols in tabular missing";

    QTest::newRow("multiline preamble")
        << "\\begin{tabular}{\nll\n}\na&b&b2\\\\c&d\\\\\ne&f\\\\\n\\end{tabular}\n"
        << 3 << 11
        << "no error";

    QTest::newRow("multiline preamble, error")
        << "\\begin{tabular}{\nl\n}\na&b&b2\\\\c&d\\\\\ne&f\\\\\n\\end{tabular}\n"
        << 3 << 1
        << "more cols in tabular than specified";

    QTest::newRow("no error 3 cols")
           << "\\begin{tabular}{lll}\n&&\\\\c&d&e&f\\\\\n\\end{tabular}\n"
           << 1 << 3
           << "no error";

    QTest::newRow("no error 3 cols")
           << "\\begin{tabular}{lll}\n&&\\\\c&d&e&f\\\\\n\\end{tabular}\n"
           << 1 << 2
           << "no error";

    QTest::newRow("no error 3 cols,multiple lines")
           << "\\begin{tabular}{lll}\na&\n&\\\\c&d&e&f\\\\\n\\end{tabular}\n"
           << 2 << 1
           << "no error";

    QTest::newRow("no error 3 cols,multiple lines 1/1")
           << "\\begin{tabular}{lll}\na&\n&\\\\c&d&e&f\\\\\n\\end{tabular}\n"
           << 2 << 1
           << "no error";

    QTest::newRow("no error 3 cols,multiple lines")
           << "\\begin{tabular}{lll}\na&\n&\\\\c&d&e&f\\\\\n\\end{tabular}\n"
           << 2 << 2
           << "no error";

    QTest::newRow("too little cols, 3 cols,multiple lines 1")
           << "\\begin{tabular}{lll}\na&\n\\\\c&d&e&f\\\\\n\\end{tabular}\n"
           << 2 << 1
           << "cols in tabular missing";

    QTest::newRow("too many cols, 3 cols,multiple lines 2")
           << "\\begin{tabular}{lll}\na&\n&&a\\\\c&d&e&f\\\\\n\\end{tabular}\n"
           << 2 << 3
           << "more cols in tabular than specified";

    QTest::newRow("too many cols, 3 cols,multiple lines 3")
           << "\\begin{tabular}{lll}\na&\n&&\na\\\\c&d&e&f\\\\\n\\end{tabular}\n"
           << 2 << 2
           << "more cols in tabular than specified";

    QTest::newRow("too many cols, 3 cols,multiple lines 4")
           << "\\begin{tabular}{lll}\na&&\\multicolumn{2}{c}{test}\na\\\\c&d&e&f\\\\\n\\end{tabular}\n"
           << 1 << 4
           << "more cols in tabular than specified";

    QTest::newRow("too many cols, 3 cols,multiple lines 5")
           << "\\begin{tabular}{lll}\na\\multicolumn{4}{c}{test}\na\\\\c&d&e&f\\\\\n\\end{tabular}\n"
           << 1 << 4
           << "more cols in tabular than specified";

    QTest::newRow("hline")
           << "\\begin{tabular}{ll}\na&b\\\\\\hline\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
           << 1 << 4
           << "no error";
    QTest::newRow("tblr,multiline cell")
        << "\\usepackage{tabularry}\n\\begin{tblr}{ll}\na&{b\\\\b}\\\\\\hline\nc&d\\\\\ne&f\\\\\n\\end{tblr}\n"
        << 2 << 4
        << "no error";
    QTest::newRow("tblr,multiline cell")
        << "\\usepackage{tabularry}\n\\begin{tblr}{ll}\na&{b\\\\b}\\\\\\hline\nc&d\\\\\ne&f\\\\\n\\end{tblr}\n"
        << 2 << 8
        << "no error";


}
void SyntaxCheckTest::checktabular(){
	QFETCH(QString, text);
	QFETCH(int, row);
	QFETCH(int, col);
	QFETCH(QString, expectedMessage);

	expectedMessage = QApplication::translate("SyntaxCheck", qPrintable(expectedMessage));

	bool inlineSyntaxChecking = edView->getConfig()->inlineSyntaxChecking;
	bool realtimeChecking = edView->getConfig()->realtimeChecking;

    edView->getConfig()->inlineSyntaxChecking = true;
    edView->getConfig()->realtimeChecking = true;

	edView->editor->setText(text, false);
    edView->document->synChecker.waitForQueueProcess(); // wait for syntax checker to finish (as it runs in a parallel thread)
	StackEnvironment env;
    edView->document->getEnv(row,env);
    QDocumentLineHandle *prev=edView->document->line(row-1).handle();
    TokenStack remainder;
    if(prev)
          remainder=prev->getCookieLocked(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
    QString message=edView->document->synChecker.getErrorAt(edView->document->line(row).handle(),col,env,remainder);
	QEQUAL(message, expectedMessage);

	edView->getConfig()->inlineSyntaxChecking = inlineSyntaxChecking;
	edView->getConfig()->realtimeChecking = realtimeChecking;
}

void SyntaxCheckTest::checkkeyval_data(){
    QTest::addColumn<QString>("text");
    QTest::addColumn<bool>("error");

     QTest::newRow("no option")
             <<"\\SI{test}"<<false;
     QTest::newRow("key only")
             <<"\\SI[mode]{test}"<<false;
     QTest::newRow("key only,error")
             <<"\\SI[modea]{test}"<<true;
     QTest::newRow("key/value")
             <<"\\SI[mode=text]{test}"<<false;
     QTest::newRow("key/value, with -")
             <<"\\si[per-mode=power-positive-first]{dfg}"<<false;
     QTest::newRow("key/value,error key")
             <<"\\SI[modea=text]{test}"<<true;
     QTest::newRow("key/value, with -, error key")
             <<"\\si[per-moded=reciprocal-positive-first]{dfg}"<<true;
     QTest::newRow("key/value,error value")
             <<"\\SI[mode=texta]{test}"<<true;
     QTest::newRow("key/value, with -, error val")
             <<"\\si[per-mode=reciprocal-positive-firstd]{dfg}"<<true;
     QTest::newRow("key/math env as value") // issue #2138
             <<"\\SI[mode=$\\sigma$]"<<false;
     QTest::newRow("2 key/value")
             <<"\\SI[color=red,mode=text]{test}"<<false;
     QTest::newRow("2 key/value,error key")
             <<"\\SI[color=red,modea=text]{test}"<<true;
     QTest::newRow("2 key/value,error value")
             <<"\\SI[color=red,mode=texta]{test}"<<true;
     QTest::newRow("key/value,color error")
             <<"\\SI[color=reda]{test}"<<true;
     QTest::newRow("key/value,color in braces")
             <<"\\SI[color={red}]{test}"<<false;
     QTest::newRow("key/value,mixed color in braces")
             <<"\\SI[color={red!20!black}]{test}"<<false;
     QTest::newRow("key/value,mixed color")
             <<"\\SI[color=red!20!black]{test}"<<false;
     QTest::newRow("key/value,defined color")
         <<"\\definecolor{cola}{as}{as}\\SI[color=cola]{test}"<<false;
     QTest::newRow("2 key/value,composite key")
             <<"\\SI[mode=text,number-mode=math]{test}"<<false;
     QTest::newRow("yathesis without options")
             <<"\\documentclass{yathesis}"<<false;
     QTest::newRow("yathesis with valid option")
             <<"\\documentclass[fleqn]{yathesis}"<<false;
     QTest::newRow("yathesis with ilegal option")
             <<"\\documentclass[fleqn2]{yathesis}"<<true;
     QTest::newRow("article")
             <<"\\documentclass[fleqn2]{article}"<<false;
     QTest::newRow("article if yathesis is loaded")
             <<"\\documentclass[fleqn]{yathesis} \\documentclass[fleqn2]{article}"<<false;
     QTest::newRow("hypersetup, key in argument")
             <<"\\usepackage{hyperref} \\hypersetup{pdfauthor}"<<false;
     QTest::newRow("hypersetup, key in argument 2")
             <<"\\usepackage{hyperref} \\hypersetup{pdfauthor2}"<<true;
     QTest::newRow("hypersetup, val in argument")
             <<"\\usepackage{hyperref} \\hypersetup{pdfpagemode=FullScreen}"<<false;
     QTest::newRow("hypersetup, val in argument 2")
             <<"\\usepackage{hyperref} \\hypersetup{pdfpagemode=test}"<<true;
     QTest::newRow("tcolorbox, different values in 2 args")
         <<"\\usepackage{tcolorbox} \\newtcbox[auto counter]{cmd}{after skip balanced=glue}"<<false;
     QTest::newRow("tcolorbox, different values in 2 args, error in 2nd")
         <<"\\usepackage{tcolorbox} \\newtcbox[auto counter]{cmd}{after kip balanced=glue}"<<true;
     QTest::newRow("tcolorbox, different values in 2 args, error in 1st")
         <<"\\usepackage{tcolorbox} \\newtcbox[aut counter]{cmd}{after skip balanced=glue}"<<true;
     QTest::newRow("keyval value with space, valid")
         <<"\\usepackage{ProfLycee} \\begin{CodePiton}[Alignement=flush left]\\end{CodePiton}"<<false;
     QTest::newRow("keyval value with space, invalid")
         <<"\\usepackage{ProfLycee} \\begin{CodePiton}[Alignement=flush leftx]\\end{CodePiton}"<<true;
     QTest::newRow("keyval value with space, first word only")
         <<"\\usepackage{ProfLycee} \\begin{CodePiton}[Alignement=flush]\\end{CodePiton}"<<true;

}

void SyntaxCheckTest::checkkeyval(){
    QFETCH(QString, text);
    QFETCH(bool, error);

    bool inlineSyntaxChecking = edView->getConfig()->inlineSyntaxChecking;
    bool realtimeChecking = edView->getConfig()->realtimeChecking;

    edView->getConfig()->inlineSyntaxChecking = true;
    edView->getConfig()->realtimeChecking = true;

    text="\\usepackage{siunitx,color}\n"+text;

    edView->editor->setText(text, false);
    LatexDocument *doc=edView->getDocument();
    doc->synChecker.waitForQueueProcess(); // wait for syntax checker to finish (as it runs in a parallel thread)

    QDocumentLineHandle *dlh=doc->line(1).handle();
    QList<QFormatRange> formats=dlh->getOverlays(LatexEditorView::syntaxErrorFormat);
    QEQUAL(!formats.isEmpty(),error);

    edView->getConfig()->inlineSyntaxChecking = inlineSyntaxChecking;
    edView->getConfig()->realtimeChecking = realtimeChecking;
}

void SyntaxCheckTest::checkArguments_data(){
    QTest::addColumn<QString>("text");
    QTest::addColumn<bool>("error");

    QTest::newRow("simple")
        <<"\\_"<<false;
    QTest::newRow("at")
        <<"\\@as"<<false;
    QTest::newRow("at2")
        <<"\\sdf@as"<<false;
    QTest::newRow("unknown command")
        <<"\\sdfs"<<true;
    QTest::newRow("newcommand")
        <<"\\newcommand{\\test}{\\abcd}"<<false;
    QTest::newRow("newcommand2")
        <<"\\newcommand{\\test}{\\abcd\n \\abcd}"<<false;
    QTest::newRow("newcommand3")
        <<"\\newcommand{\\test}{\\abcd\n{\n \\abcd}\n}"<<false;
    QTest::newRow("specialDef missing")
        <<"\\DTLrowcount{tes}\n}"<<true;
    QTest::newRow("specialDef present")
        <<"\\DTLnewdb{tes}\n\\DTLrowcount{tes}\n}"<<false;
}

void SyntaxCheckTest::checkArguments(){
    QFETCH(QString, text);
    QFETCH(bool, error);

    bool inlineSyntaxChecking = edView->getConfig()->inlineSyntaxChecking;
    bool realtimeChecking = edView->getConfig()->realtimeChecking;

    edView->getConfig()->inlineSyntaxChecking = true;
    edView->getConfig()->realtimeChecking = true;

    text="\\usepackage{datatool}\n"+text;

    edView->editor->setText(text, false);
    LatexDocument *doc=edView->getDocument();
    doc->synChecker.waitForQueueProcess(); // wait for syntax checker to finish (as it runs in a parallel thread)

    bool synError=false;
    for(int i=0;i<doc->lineCount();i++){
        QDocumentLineHandle *dlh=doc->line(i).handle();
        QList<QFormatRange> formats=dlh->getOverlays(LatexEditorView::syntaxErrorFormat);
        if(!formats.isEmpty())
            synError=true;
    }
    QEQUAL(synError,error);

    edView->getConfig()->inlineSyntaxChecking = inlineSyntaxChecking;
    edView->getConfig()->realtimeChecking = realtimeChecking;
}

void SyntaxCheckTest::checkMathHighlight_data(){
    QTest::addColumn<QString>("text");
    QTest::addColumn<QList<int>>("start");
    QTest::addColumn<QList<int>>("length");
    QTest::addColumn<QList<int>>("textStart");
    QTest::addColumn<QList<int>>("textLength");

     QTest::newRow("simple")
             <<"text"<<QList<int>{}<<QList<int>{}<<QList<int>{}<<QList<int>{};
     QTest::newRow("simple math")
             <<"$abc$"<<QList<int>{1}<<QList<int>{3}<<QList<int>{}<<QList<int>{};
     QTest::newRow("math env")
             <<"\\begin{displaymath}abc\\end{displaymath}"<<QList<int>{19}<<QList<int>{3}<<QList<int>{}<<QList<int>{};
     QTest::newRow("nested text in math")
             <<"$abc \\textbf{text} abc$"<<QList<int>{1}<<QList<int>{21}<<QList<int>{13}<<QList<int>{4};
     QTest::newRow("nested math in text")
             <<"\\textbf{text $abc$}"<<QList<int>{14}<<QList<int>{3}<<QList<int>{}<<QList<int>{};
     QTest::newRow("nested text in math in text")
             <<"\\textbf{text $\\textbf{text}abc$}"<<QList<int>{14}<<QList<int>{16}<<QList<int>{22}<<QList<int>{4};
     QTest::newRow("nested math in text in math in text")
             <<"\\textbf{text $\\textbf{text $abc$}abc$}"<<QList<int>{14,28}<<QList<int>{22,3}<<QList<int>{22}<<QList<int>{4};
}

void SyntaxCheckTest::checkMathHighlight(){
    QFETCH(QString, text);
    QFETCH(QList<int>, start);
    QFETCH(QList<int>, length);
    QFETCH(QList<int>, textStart);
    QFETCH(QList<int>, textLength);

    bool inlineSyntaxChecking = edView->getConfig()->inlineSyntaxChecking;
    bool realtimeChecking = edView->getConfig()->realtimeChecking;

    edView->getConfig()->inlineSyntaxChecking = edView->getConfig()->realtimeChecking = true;

    edView->editor->setText(text, false);
    LatexDocument *doc=edView->getDocument();
    doc->synChecker.waitForQueueProcess(); // wait for syntax checker to finish (as it runs in a parallel thread)

    for(int i=0;i<doc->lineCount();++i){
        QDocumentLineHandle *dlh=doc->line(i).handle();
        QList<QFormatRange> formats=dlh->getOverlays(LatexEditorView::numbersFormat);
        QList<QFormatRange> mathText=dlh->getOverlays(doc->getFormatId("math-text"));
        QEQUAL(formats.length(),start.length());
        QEQUAL(mathText.length(),textStart.length());
        for(int k=0;k<formats.length();++k){
            QEQUAL(formats[k].offset,start.value(k));
            QEQUAL(formats[k].length,length.value(k));
        }
        for(int k=0;k<mathText.length();++k){
            QEQUAL(mathText[k].offset,textStart.value(k));
            QEQUAL(mathText[k].length,textLength.value(k));
        }
    }

    edView->getConfig()->inlineSyntaxChecking = inlineSyntaxChecking;
    edView->getConfig()->realtimeChecking = realtimeChecking;
}

void SyntaxCheckTest::checkAllowedMath_data(){
    QTest::addColumn<QString>("text");
    QTest::addColumn<bool>("error");

     QTest::newRow("simple")
             <<"$\\alpha$"<<false;
     QTest::newRow("simple2")
             <<"\\alpha"<<true;
     QTest::newRow("simple3") // issue #192
             <<"$y \\big($"<<false;
     QTest::newRow("nested text in math")
             <<"$\\textit{\\alpha}$"<<true;
     QTest::newRow("nested text in math with linebreak")
         <<"$\\textit{\n\\alpha}$"<<true;
     QTest::newRow("nested text in math (underscore)")
             <<"$\\textit{a_b}$"<<true;
     QTest::newRow("nested text in math and extra braces")
             <<"$\\textit{ {\\alpha}}$"<<true;
     QTest::newRow("nested text in math amd extra braces(underscore)")
             <<"$\\textit{ {a_b}}$"<<true;
     QTest::newRow("nested math in text in math")
             <<"$\\textit{$\\alpha$}$"<<false;
     QTest::newRow("nested math in text in math (underscore)")
             <<"$\\textit{$a_b$}$"<<false;
     QTest::newRow("nested math in text in math and extra braces")
             <<"$\\textit{$ {\\alpha}$}$"<<false;
     QTest::newRow("nested math in text in math and extra braces (underscore)")
             <<"$\\textit{$ {a_b}$}$"<<false;
     QTest::newRow("handle math aliases correctly")
         <<"\\usepackage{amsmath}\n\\begin{align}\n\\alpha\n\\end{align}"<<false;
     QTest::newRow("handle math aliases correctly, force error")
         <<"\\usepackage{amsmath}\n\\begin{align}\n\\text{\\alpha}\n\\end{align}"<<true;
}

void SyntaxCheckTest::checkAllowedMath(){
    QFETCH(QString, text);
    QFETCH(bool, error);

    bool inlineSyntaxChecking = edView->getConfig()->inlineSyntaxChecking;
    bool realtimeChecking = edView->getConfig()->realtimeChecking;

    edView->getConfig()->inlineSyntaxChecking = true;
    edView->getConfig()->realtimeChecking = true;

    edView->editor->setText(text, false);
    LatexDocument *doc=edView->getDocument();
    doc->synChecker.waitForQueueProcess(); // wait for syntax checker to finish (as it runs in a parallel thread)

    bool errorFlag=false;
    for(int i=0;i<doc->lines();++i){
        QDocumentLineHandle *dlh=doc->line(i).handle();
        QList<QFormatRange> formats=dlh->getOverlays(LatexEditorView::syntaxErrorFormat);
        errorFlag|=!formats.isEmpty();
    }
    QEQUAL(errorFlag,error);

    edView->getConfig()->inlineSyntaxChecking = inlineSyntaxChecking;
    edView->getConfig()->realtimeChecking = realtimeChecking;
}

void SyntaxCheckTest::checkExplHighlight_data(){
    QTest::addColumn<QString>("text");
    QTest::addColumn<QList<int>>("start");
    QTest::addColumn<QList<int>>("length");
    QTest::addColumn<QList<int>>("colonStart");
    QTest::addColumn<QList<int>>("colonLength");

    QTest::newRow("simple")
        <<"text"<<QList<int>{}<<QList<int>{}<<QList<int>{}<<QList<int>{};
    QTest::newRow("simple text")
        <<"\\ExplSyntaxOn text \\ExplSyntaxOff"<<QList<int>{}<<QList<int>{}<<QList<int>{}<<QList<int>{};
    QTest::newRow("simple cmd")
        <<"\\ExplSyntaxOn \\test \\ExplSyntaxOff"<<QList<int>{14}<<QList<int>{5}<<QList<int>{}<<QList<int>{};
    QTest::newRow("simple cmd with _")
        <<"\\ExplSyntaxOn \\test_asd_asd \\ExplSyntaxOff"<<QList<int>{14}<<QList<int>{13}<<QList<int>{}<<QList<int>{};
    QTest::newRow("simple cmd with :")
        <<"\\ExplSyntaxOn \\test_asd_asd:NN \\ExplSyntaxOff"<<QList<int>{14}<<QList<int>{14}<<QList<int>{28}<<QList<int>{2};
    QTest::newRow("two cmds")
        <<"\\ExplSyntaxOn \\test \\test \\ExplSyntaxOff"<<QList<int>{14,20}<<QList<int>{5,5}<<QList<int>{}<<QList<int>{};
}

void SyntaxCheckTest::checkExplHighlight(){
    QFETCH(QString, text);
    QFETCH(QList<int>, start);
    QFETCH(QList<int>, length);
    QFETCH(QList<int>, colonStart);
    QFETCH(QList<int>, colonLength);

    bool inlineSyntaxChecking = edView->getConfig()->inlineSyntaxChecking;
    bool realtimeChecking = edView->getConfig()->realtimeChecking;

    edView->getConfig()->inlineSyntaxChecking = true;
    edView->getConfig()->realtimeChecking = true;

    edView->editor->setText(text, false);
    LatexDocument *doc=edView->getDocument();
    doc->synChecker.waitForQueueProcess(); // wait for syntax checker to finish (as it runs in a parallel thread)

    for(int i=0;i<doc->lineCount();++i){
        QDocumentLineHandle *dlh=doc->line(i).handle();
        QList<QFormatRange> formats=dlh->getOverlays(doc->getFormatId("picture-keyword"));
        QList<QFormatRange> colonTextFormat=dlh->getOverlays(LatexEditorView::numbersFormat);
        QEQUAL(formats.length(),start.length());
        QEQUAL(colonTextFormat.length(),colonStart.length());
        for(int k=0;k<formats.length();++k){
            QEQUAL(formats[k].offset,start.value(k));
            QEQUAL(formats[k].length,length.value(k));
        }
        for(int k=0;k<colonTextFormat.length();++k){
            QEQUAL(colonTextFormat[k].offset,colonStart.value(k));
            QEQUAL(colonTextFormat[k].length,colonLength.value(k));
        }
    }

    edView->getConfig()->inlineSyntaxChecking = inlineSyntaxChecking;
    edView->getConfig()->realtimeChecking = realtimeChecking;
}

#endif

