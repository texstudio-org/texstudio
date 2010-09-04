
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "tablemanipulation_t.h"
#include "tablemanipulation.h"
#include "qdocumentcursor.h"
#include "qdocument.h"
#include "qeditor.h"
#include "testutil.h"
#include <QtTest/QtTest>
TableManipulationTest::TableManipulationTest(QEditor* editor): ed(editor){}

void TableManipulationTest::addCol_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("row");
	QTest::addColumn<int>("col");
	QTest::addColumn<QString>("newText");
	
	//-------------cursor without selection--------------
	QTest::newRow("add first col")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 0
		<< "\\begin{tabular}{ll}\n &a&b\\\\\n &c&d\\\\\n &e&f\\\\\n\\end{tabular}\n";

	QTest::newRow("add second col")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 1
		<< "\\begin{tabular}{ll}\na& &b\\\\\nc& &d\\\\\ne& &f\\\\\n\\end{tabular}\n";

	QTest::newRow("add third col")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 2
		<< "\\begin{tabular}{ll}\na&b& \\\\\nc&d& \\\\\ne&f& \\\\\n\\end{tabular}\n";

	QTest::newRow("add 4th col")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 3
		<< "\\begin{tabular}{ll}\na&b& \\\\\nc&d& \\\\\ne&f& \\\\\n\\end{tabular}\n";


}
void TableManipulationTest::addCol(){
	QFETCH(QString, text);
	QFETCH(int, row);
	QFETCH(int, col);
	QFETCH(QString, newText);
	
	ed->document()->setText(text);
	LatexTables::addColumn(ed->document(),row,col,0);

	QEQUAL(ed->document()->text(), newText);
	
}
#endif

