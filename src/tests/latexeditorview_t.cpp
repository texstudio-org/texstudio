
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "latexeditorview_t.h"
#include "latexeditorview.h"
#include "latexdocument.h"
#include "qdocumentcursor.h"
#include "qdocument.h"
#include "qeditor.h"
#include "testutil.h"
#include <QtTest/QtTest>
LatexEditorViewTest::LatexEditorViewTest(LatexEditorView* view): edView(view){}

void LatexEditorViewTest::insertHardLineBreaks_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("start");
	QTest::addColumn<int>("end");
	QTest::addColumn<int>("length");
	QTest::addColumn<QString>("newText");

	//-------------cursor without selection--------------
	QTest::newRow("one break in single line")
		<< "a\nhallo welt\nb"
		<< 1 << 1
		<< 5
		<< "a\nhallo\nwelt\nb";
	QTest::newRow("multiple breaks in single line")
		<< "a\nhallo welt miau x y z ping pong thing\nb"
		<< 1 << 1
		<< 5
		<< "a\nhallo\nwelt\nmiau\nx y z\nping\npong\nthing\nb";
	QTest::newRow("one break in multi lines")
		<< "a\nhallo welt\nb\nxyz\nc"
		<< 0 << 3
		<< 5
		<< "a\nhallo\nwelt\nb\nxyz\nc";
	QTest::newRow("multiple breaks in multiple lines")
		<< "hallo welt ilias ting ping 12 34\ntest test test 7 test test\nend"
		<< 0 << 1
		<< 5
		<< "hallo\nwelt\nilias\nting\nping\n12 34\ntest\ntest\ntest\n7\ntest\ntest\nend";
	QTest::newRow("long words")
		<< "hello world yipyip yeah\nabc def ghi ijk\nend"
		<< 0 << 1
		<< 5
		<< "hello\nworld\nyipyip\nyeah\nabc\ndef\nghi\nijk\nend";
	QTest::newRow("comments")
		<< "hello %world yipyip yeah\n%abc def ghi ijk\nend"
		<< 0 << 1
		<< 5
		<< "hello\n%world\n%yipyip\n%yeah\n%abc\n%def\n%ghi\n%ijk\nend";
	QTest::newRow("comments too long") //"x y z" is ok, "%x y z" not
		<< "hello x y z %x y z world a b c yipyip yeah\n%abc def ghi ijk\nend"
		<< 0 << 1
		<< 5
		<< "hello\nx y z\n%x y\n%z\n%world\n%a b\n%c\n%yipyip\n%yeah\n%abc\n%def\n%ghi\n%ijk\nend";
	QTest::newRow("comments and percent")
		<< "mui muo\\% mua muip abc %def ghi ijk\nend"
		<< 0 << 0
		<< 5
		<< "mui\nmuo\\%\nmua\nmuip\nabc\n%def\n%ghi\n%ijk\nend";

}
void LatexEditorViewTest::insertHardLineBreaks(){
	QFETCH(QString, text);
	QFETCH(int, start);
	QFETCH(int, end);
	QFETCH(int, length);
	QFETCH(QString, newText);

	edView->editor->setText(text, false);
	if (start==end)
		edView->editor->setCursor(edView->editor->document()->cursor(start,0,start,1));
	else
		edView->editor->setCursor(edView->editor->document()->cursor(start,0,end+1,0));
	edView->insertHardLineBreaks(length,false,false);
    edView->editor->document()->setLineEndingDirect(QDocument::Unix,true);
	QEQUAL(edView->editor->document()->text(), newText);

	if (start!=end) { //repeat with different cursor position
		edView->editor->setText(text, false);
		edView->editor->setCursor(edView->editor->document()->cursor(start,1,end,1));
		edView->insertHardLineBreaks(length, false, false);
        edView->editor->document()->setLineEndingDirect(QDocument::Unix,true);
		QEQUAL(edView->editor->document()->text(), newText);
	}
}
void LatexEditorViewTest::inMathEnvironment_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<QString>("inmath");

	QTest::newRow("closed")
			<<  "a$bc$de\\[f\\]g"
            << "fftttffffttfff";

	QTest::newRow("open")
			<<  "xy$z"
			<< "ffftt";
}
void LatexEditorViewTest::inMathEnvironment(){
	QFETCH(QString, text);
	QFETCH(QString, inmath);
	edView->editor->setText(text);

        edView->document->SynChecker.waitForQueueProcess(); // wait for syntax checker to finish (as it runs in a parallel thread)

	QDocumentCursor c = edView->editor->document()->cursor(0,0);
	for (int i=0;i<inmath.size();i++) {
		c.setColumnNumber(i);
		bool posinmath = inmath.at(i) == 't';
		QEQUAL(edView->isInMathHighlighting(c), posinmath );
	}

}

#endif

