
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "latexeditorview_bm.h"
#include "latexeditorview.h"
#include "qdocumentcursor.h"
#include "qdocument.h"
#include "qeditor.h"
#include "testutil.h"
#include <QtTest/QtTest>
LatexEditorViewBenchmark::LatexEditorViewBenchmark(LatexEditorView* view): edView(view){}

void LatexEditorViewBenchmark::documentChange_data(){
#if QT_VERSION >= 0x040500	
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("start");
	QTest::addColumn<int>("count");
	
	//-------------cursor without selection--------------
	QTest::newRow("one line update")
		<< "abcdefg\nhallo welt\nabcdefg"
		<< 0 << 1;
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
			<< "\\usepackage{abcdsdfsdfds} \\usepackage{abcdsdfsdfds}\nhallo welt\nabcdefg"
		<< 0 << 1;
	QTest::newRow("spellcheck in command")
			<< "\\textbf{abcdsdfsdfds} \\textbf{abcdsdfsdfds}\nhallo welt\nabcdefg"
		<< 0 << 1;
#endif
}
void LatexEditorViewBenchmark::documentChange(){
#if QT_VERSION >= 0x040500	
	QFETCH(QString, text);
	QFETCH(int, start);
	QFETCH(int, count);
	
	edView->editor->document()->setText(text);
	QBENCHMARK {
		edView->documentContentChanged(start,count);
	}
#endif
}
#endif

