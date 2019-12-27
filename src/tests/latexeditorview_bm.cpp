
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "latexeditorview_bm.h"
#include "latexeditorview.h"
#include "qdocumentcursor.h"
#include "qdocument.h"
#include "qdocumentline.h"
#include "qdocumentline_p.h"
#include "latexdocument.h"
#include "qeditor.h"
#include "testutil.h"
#include <QtTest/QtTest>
LatexEditorViewBenchmark::LatexEditorViewBenchmark(LatexEditorView* view, bool all): edView(view), all(all){}

void LatexEditorViewBenchmark::documentChange_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("start");
	QTest::addColumn<int>("count");
	
	
	//-------------cursor without selection--------------
	QTest::newRow("one line update")
		<< "abcdefg\nhallo welt\nabcdefg"
		<< 0 << 1;

	if (!all) {
		qDebug() << "skipped benchmark data";
		return;
	}
	QTest::newRow("multi line update")
		<< "abcdefga\nabcdefg\nabcdefg\nxyz\nc"
		<< 0 << 3;
	QTest::newRow("long line update")
		<< "abcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefga\nabcdefg\nabcdefg\nxyz\nc"
		<< 0 << 3;
	QTest::newRow("labels")
			<< "\\label{ab} \\label{cd}\nhallo welt\nabcdefg"
		<< 0 << 1;
	QTest::newRow("refs")
			<< "\\ref{ab} \\ref{cd}\nhallo welt\nabcdefg"
		<< 0 << 1;
	QTest::newRow("no spellcheck in command")
			<< "\\usepackage{graphicx} \\usepackage{graphicx}\nhallo welt\nabcdefg"
		<< 0 << 1;
	QTest::newRow("spellcheck in command")
			<< "\\textbf{graphicx} \\textbf{graphicx}\nhallo welt\nabcdefg"
		<< 0 << 1;
}
void LatexEditorViewBenchmark::documentChange(){
	QFETCH(QString, text);
	QFETCH(int, start);
	QFETCH(int, count);
	
	if (!all) {
		qDebug() << "skipped benchmark";
		return;
	}

	edView->editor->setText(text, false);
	QBENCHMARK {
		edView->documentContentChanged(start,count);
	}
}

void LatexEditorViewBenchmark::patch_data(){
    QTest::addColumn<QString>("text");
    QTest::addColumn<int>("start");
    QTest::addColumn<int>("count");


    //-------------cursor without selection--------------
    QTest::newRow("one line update")
        << "abcdefg\nhallo welt\nabcdefg"
        << 0 << 1;

    if (!all) {
        qDebug() << "skipped benchmark data";
        return;
    }
    QTest::newRow("multi line update")
        << "abcdefga\nabcdefg\nabcdefg\nxyz\nc"
        << 0 << 3;
    QTest::newRow("long line update")
        << "abcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefga\nabcdefg\nabcdefg\nxyz\nc"
        << 0 << 3;
    QTest::newRow("labels")
            << "\\label{ab} \\label{cd}\nhallo welt\nabcdefg"
        << 0 << 1;
    QTest::newRow("refs")
            << "\\ref{ab} \\ref{cd}\nhallo welt\nabcdefg"
        << 0 << 1;
    QTest::newRow("no spellcheck in command") // does a complete recheck as package is concerned
            << "\\usepackage{graphicx} \\usepackage{graphicx}\nhallo welt\nabcdefg"
        << 0 << 1;
    QTest::newRow("no spellcheck in command2")
            << "\\begin{document} \\includegraphics{test}\nhallo welt\nabcdefg"
        << 0 << 1;
    QTest::newRow("spellcheck in command")
            << "\\textbf{graphicx} \\textbf{graphicx}\nhallo welt\nabcdefg"
        << 0 << 1;
    QTest::newRow("multi-line command")
            << "\\textbf{graphicx} \\textbf{graphicx}\nhallo welt\nabcdefg"
        << 0 << 4;
    QTest::newRow("many lines")
            << QString("\\documentclass{article}\n%\\usepackage{babel} \n%opening\n\n\n\\usepackage{german,color,textcomp,titlesec}\n\n\\usepackage{graphicx,\n	url,\n")
               +QString("tabu,cleveref,\n	tabularx} \n\\usepackage[utf8]{inputenc}\n\\title{sdfg}\n\\author{sdfg}\n\\usepackage{tabulary}\n\\pagestyle{empty}\n\n\\makeatletter\n")
               +QString("\\renewcommand{\\paragraph}{\\@startsection{paragraph}{4}{\\z@}%\n  {-3.25ex\\@plus -1ex \\@minus -.2ex}%\n  {1.5ex \\@plus .2ex}%\n  {\\ifnum \\scr@compatibility>\\@nameuse{scr@v@2.96}\\relax\n")
               +QString("\\setlength{\\parfillskip}{\\z@ plus 1fil}\\fi\n    \\raggedsection\\normalfont\\sectfont\\nobreak\\size@subsubsection\n  }%\n}\n\\makeatother\n\n\\begin{document}\n%\\ertet\n\\newcommand{\\testa}[2][efault]{def}\n")
               +QString("\n\\let\\oldsection\\section\\renewcommand{\\section}{\\clearpage\\oldsection}\n%\\ref{sec:asdas}\n\\cref{sdfsdf,sec:asdas}\n\\testa{as}\n\\begin{enumerate}\n\\item asda\n\\item asd\n\\end{enumerate}\n\\vspace{\\linewidth}\n")
               +QString("\\textcolor{blue}{text}\n%\\includegraphics[height=]{imagefile}\n\\maketitle\n\\ref{sdfsdf}\n\\begin{abstract}\nsdfgsdfg\\item \n\\end{abstract}\n\\ref{sec:asdas}\ndas bla \n\\section{fgsdfg}\n\\label{sdfsdf}\nals \\url{etwas}\n")
               +QString("\\begin{description}\n\\item[desc] text\n\\label{sec:asdas}\n\\item[desc] text\n\\item[desc] text\n\\item[desc] text\n\\end{description}\nsdfgsdfgsdfgsdfgsdfgsdfgsdfgsdfgsdgfgsdfgsdgfsdfgsdfgsdfgsdfgsdfgsdfgsdfgsdfgsdfgsdfgsdfg\n")
               +QString("Hallo Hallo Hallo\n\"Arger\n%\\fgdfg\nozy\n$\\textbf{sd}$\n%\\include{\"test abc\"}\n\\titleformat{\\section}[hang]{\\normalfont\\bfseries}{\\thesection}{0.7em}{}[]\n\\titlespacing*{\\section}{0em}{1.5em}{1.5em} \nfig\n\"And Änd \n")
               +QString("%#sdfsdf\n\\newcommand{\\rel}{./}\n \\include{test2}\n\\url{http://en.wikipedia.org/wiki/Internal_control}\n\\section[asd]{sdfgsdfg(sdfd}\nsdfsdfg\n\\includegraphics[width=.3\\linewidth,hiresbb=false,angle=12,]{appicon.pdf} \nJadsdfsdf\n")
               +QString("\\include{included} \n%\\includegraphics[graphicx keys]{}\nMal sehen.\n% %\\include{included2} \n% %\\include{test_mi2}\n% %\\include{circDesc_TOP}\n\nNämlich ist das blöd, das das \\verb|asdas dasdasd| asd sd assd asd nämlich \n")
               +QString("\\begin{equation}\nerdf\n\\end{equation}\n\n\\textmu m\n\n$\\mu\\quad\\theta$\n\n\\begin{verbatim}\ndas dassdf asdasdf asdf \nasdfasdfa asdf asdf asdf  fad txssdsdsd\n\\end{verbatim}\n\n\\begin{tabular}	{l|*{3}{c}}\n\\hline 1 & 2 & 3 & 4 \\\\ \n")
               +QString("\\hline a & b & c & d \\\\\n\\hline\n\\end{tabular}\n\n\\end{document}\n\n%\\section{dfgdfg}\n\n")
        << 0 << 111;
}
void LatexEditorViewBenchmark::patch(){
    QFETCH(QString, text);
    QFETCH(int, start);
    QFETCH(int, count);

    if (!all) {
        qDebug() << "skipped benchmark";
        return;
    }

    edView->editor->setText(text, false);
    QBENCHMARK {
        edView->document->patchStructure(start,count);
    }
}

void LatexEditorViewBenchmark::linePaint_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("start");
	QTest::addColumn<int>("count");

	//-------------cursor without selection--------------
	QTest::newRow("one line update")
		<< "abcdefg\nhallo welt\nabcdefg"
		<< 0 << 1;

	if (!all) {
		qDebug() << "skipped benchmark data"; 
		return;
	}

	QTest::newRow("correct german")
		<< "Haus\nAuto\nKind\nxyz\nc"
		<< 0 << 3;
	QTest::newRow("long line update")
		<< "abcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefga\nabcdefg\nabcdefg\nxyz\nc"
		<< 0 << 3;
	QTest::newRow("labels")
			<< "\\label{ab} \\label{cd}\nhallo welt\nabcdefg"
		<< 0 << 1;
	QTest::newRow("refs")
			<< "\\ref{ab} \\ref{cd}\nhallo welt\nabcdefg"
		<< 0 << 1;
	QTest::newRow("no spellcheck in command")
			<< "\\usepackage{graphicx} \\usepackage{graphicx}\nhallo welt\nabcdefg"
		<< 0 << 1;
	QTest::newRow("spellcheck in command")
			<< "\\textbf{graphicx} \\textbf{graphicx}\nhallo welt\nabcdefg"
		<< 0 << 1;
}
void LatexEditorViewBenchmark::linePaint(){
	QFETCH(QString, text);
	QFETCH(int, start);
	QFETCH(int, count);
	Q_UNUSED(start)
	Q_UNUSED(count)

	if (!all) {
		qDebug() << "skipped benchmark";
		return;
	}

	edView->editor->setText(text, false);
	LatexDocument *doc=edView->document;
	QDocument::PaintContext cxt;
	cxt.xoffset = 0;
	cxt.yoffset = 0;
	cxt.width = 1000;
	cxt.height = 700;
	cxt.palette = QApplication::palette();
	cxt.fillCursorRect = false;
	cxt.blinkingCursor = false;

	QVector<int> m_cursorLines(0), m_selectionBoundaries(0);

	QBrush bg = cxt.palette.base();

	QDocumentLineHandle *dlh=doc->line(0).handle();
	bool fullSel=false;
	QPixmap *px=new QPixmap(cxt.width,12);
	//px->fill(base.color());//fullSel ? selbg.color() : bg.color());
	px->fill(bg.color());
	QPainter pnt(px);
	pnt.setFont(QApplication::font());
	pnt.translate(-cxt.xoffset,0);
	/*pnt.fillRect(0, 0,
							m_leftMargin, m_lineSpacing*(wrap+1),
							base); // fillrect executed twice, to be optimized

	*/
	QBENCHMARK {
		dlh->draw(0, &pnt, cxt.xoffset, cxt.width, m_selectionBoundaries, cxt.palette, fullSel);
	}
	pnt.end();
	delete px;
}


void LatexEditorViewBenchmark::paintEvent_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("start");
	QTest::addColumn<int>("count");

	//-------------cursor without selection--------------
	QTest::newRow("one line update")
		<< "abcdefg\nhallo welt\nabcdefg"
		<< 0 << 1;

	if (!all) {
		qDebug() << "skipped benchmark data";
		return;
	}

	QTest::newRow("correct german")
		<< "Haus\nAuto\nKind\nxyz\nc"
		<< 0 << 3;
	QTest::newRow("long line update")
		<< "abcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefgaabcdefga\nabcdefg\nabcdefg\nxyz\nc"
		<< 0 << 3;
	QTest::newRow("labels")
			<< "\\label{ab} \\label{cd}\nhallo welt\nabcdefg"
		<< 0 << 1;
	QTest::newRow("refs")
			<< "\\ref{ab} \\ref{cd}\nhallo welt\nabcdefg"
		<< 0 << 1;
	QTest::newRow("no spellcheck in command")
			<< "\\usepackage{graphicx} \\usepackage{graphicx}\nhallo welt\nabcdefg"
		<< 0 << 1;
	QTest::newRow("spellcheck in command")
			<< "\\textbf{graphicx} \\textbf{graphicx}\nhallo welt\nabcdefg"
		<< 0 << 1;
}
void LatexEditorViewBenchmark::paintEvent(){
	QFETCH(QString, text);
	QFETCH(int, start);
	QFETCH(int, count);
	Q_UNUSED(start)
	Q_UNUSED(count)

	if (!all) {
		qDebug() << "skipped benchmark";
		return;
	}
	
	edView->editor->setText(text, false);
	edView->editor->setCursorPosition(0,0);
	QBENCHMARK {
		edView->editor->repaint(edView->rect());
	}
}
#endif

