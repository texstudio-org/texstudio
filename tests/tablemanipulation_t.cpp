
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

void TableManipulationTest::addRow_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("row");
	QTest::addColumn<int>("col");
	QTest::addColumn<QString>("newText");

	//-------------cursor without selection--------------
	QTest::newRow("add row")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 0
		<< "\\begin{tabular}{ll}\na&b\\\\\n & \\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n";

	QTest::newRow("add row, cursor at end of line")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 5
		<< "\\begin{tabular}{ll}\na&b\\\\\n & \\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n";

	QTest::newRow("add row")
		<< "\\begin{tabular}{ll}\na&b\\\\c&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 0
		<< "\\begin{tabular}{ll}\na&b\\\\\n & \\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n";

	QTest::newRow("add row")
		<< "\\begin{tabular}{ll}\na&b\\\\c&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 6
		<< "\\begin{tabular}{ll}\na&b\\\\c&d\\\\\n & \\\\\ne&f\\\\\n\\end{tabular}\n";

}
void TableManipulationTest::addRow(){
	QFETCH(QString, text);
	QFETCH(int, row);
	QFETCH(int, col);
	QFETCH(QString, newText);

	ed->document()->setText(text);
	ed->setCursorPosition(row,col);
	QDocumentCursor c(ed->cursor());
	LatexTables::addRow(c,2);

	QEQUAL(ed->document()->text(), newText);

}

void TableManipulationTest::remCol_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("row");
	QTest::addColumn<int>("col");
	QTest::addColumn<QString>("newText");

	//-------------cursor without selection--------------
	QTest::newRow("rem col 0")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 0
		<< "\\begin{tabular}{ll}\nb\\\\\nd\\\\\nf\\\\\n\\end{tabular}\n";

	QTest::newRow("rem col 1")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 1
		<< "\\begin{tabular}{ll}\na\\\\\nc\\\\\ne\\\\\n\\end{tabular}\n";

	QTest::newRow("rem col 0, multicolumn")
		<< "\\begin{tabular}{ll}\na&b\\\\\n\\multicolumn{2}{c}\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 0
		<< "\\begin{tabular}{ll}\nb\\\\\n\\multicolumn{1}{c}\\\\\nf\\\\\n\\end{tabular}\n";

	QTest::newRow("rem col 1, multicolumn")
		<< "\\begin{tabular}{ll}\na&b\\\\\n\\multicolumn{2}{c}\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 1
		<< "\\begin{tabular}{ll}\na\\\\\n\\multicolumn{1}{c}\\\\\ne\\\\\n\\end{tabular}\n";

	QTest::newRow("rem col 1, multicolumn plus col")
		<< "\\begin{tabular}{ll}\na&b\\\\\n\\multicolumn{2}{c}&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 1
		<< "\\begin{tabular}{ll}\na\\\\\n\\multicolumn{1}{c}&d\\\\\ne\\\\\n\\end{tabular}\n";

	QTest::newRow("rem col 1, multicolumn")
		<< "\\begin{tabular}{ll}\na&b\\\\\n\\multicolumn{2}{c}&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 2
		<< "\\begin{tabular}{ll}\na&b\\\\\n\\multicolumn{2}{c}\\\\\ne&f\\\\\n\\end{tabular}\n";

	QTest::newRow("rem col 0, row over multiple lines")
		<< "\\begin{tabular}{ll}\na&\nb\\\\\nc\n&\nd\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 0
		<< "\\begin{tabular}{ll}\n\nb\\\\\n\nd\\\\\nf\\\\\n\\end{tabular}\n";

	QTest::newRow("rem col 1, row over multiple lines")
		<< "\\begin{tabular}{ll}\na&\nb\\\\\nc\n&\nd\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 1
		<< "\\begin{tabular}{ll}\na\\\\\nc\n\\\\\ne\\\\\n\\end{tabular}\n";

}
void TableManipulationTest::remCol(){
	QFETCH(QString, text);
	QFETCH(int, row);
	QFETCH(int, col);
	QFETCH(QString, newText);

	ed->document()->setText(text);
	LatexTables::removeColumn(ed->document(),row,col);

	QEQUAL(ed->document()->text(), newText);

}

void TableManipulationTest::remRow_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("row");
	QTest::addColumn<int>("col");
	QTest::addColumn<QString>("newText");

	//-------------cursor without selection--------------
	QTest::newRow("rem row")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 0
		<< "\\begin{tabular}{ll}\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n";

	QTest::newRow("rem row, cursor at end of line")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 5
		<< "\\begin{tabular}{ll}\na&b\\\\\ne&f\\\\\n\\end{tabular}\n";

	QTest::newRow("rem row, second row")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 2 << 0
		<< "\\begin{tabular}{ll}\na&b\\\\\ne&f\\\\\n\\end{tabular}\n";

	QTest::newRow("rem row, third row")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 3 << 0
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\n\\end{tabular}\n";

	QTest::newRow("rem row, multi rows in one line 1")
		<< "\\begin{tabular}{ll}\na&b\\\\c&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 0
		<< "\\begin{tabular}{ll}\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n";

	QTest::newRow("rem row, multi rows in one line 2")
		<< "\\begin{tabular}{ll}\na&b\\\\c&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 6
		<< "\\begin{tabular}{ll}\na&b\\\\\ne&f\\\\\n\\end{tabular}\n";

	QTest::newRow("rem row, multi rows in one line 3")
		<< "\\begin{tabular}{ll}\na&b\\\\c&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 2 << 6
		<< "\\begin{tabular}{ll}\na&b\\\\c&d\\\\\n\\end{tabular}\n";

	QTest::newRow("rem row, multi rows in one line 4")
		<< "\\begin{tabular}{ll}\na&b\\\\c&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 3 << 6
		<< "\\begin{tabular}{ll}\na&b\\\\c&d\\\\\ne&f\\\\\n\\end{tabular}\n";


}
void TableManipulationTest::remRow(){
	QFETCH(QString, text);
	QFETCH(int, row);
	QFETCH(int, col);
	QFETCH(QString, newText);

	ed->document()->setText(text);
	ed->setCursorPosition(row,col);
	QDocumentCursor c(ed->cursor());
	LatexTables::removeRow(c);

	QEQUAL(ed->document()->text(), newText);

}

void TableManipulationTest::getCol_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("row");
	QTest::addColumn<int>("col");
	QTest::addColumn<int>("colFound");

	//-------------cursor without selection--------------
	QTest::newRow("col 0")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 0
		<< 0;

	QTest::newRow("col 0")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 1
		<< 0;

	QTest::newRow("col 1")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 2
		<< 1;

	QTest::newRow("col 1")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 3
		<< 1;

	QTest::newRow("col 1")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 4
		<< 1;

	QTest::newRow("col -1")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 1 << 5
		<< -1;

	QTest::newRow("row 2,col 1")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 2 << 0
		<< 0;

	QTest::newRow("row 3,col 1")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 3 << 0
		<< 0;

	QTest::newRow("row 2,col 2")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 3 << 2
		<< 1;

	QTest::newRow("row 2,col -1")
		<< "\\begin{tabular}{ll}\na&b\\\\\nc&d\\\\\ne&f\\\\\n\\end{tabular}\n"
		<< 3 << 5
		<< -1;

}
void TableManipulationTest::getCol(){
	QFETCH(QString, text);
	QFETCH(int, row);
	QFETCH(int, col);
	QFETCH(int, colFound);

	ed->document()->setText(text);
	ed->setCursorPosition(row,col);
	QDocumentCursor c(ed->cursor());
	int nc=LatexTables::getColumn(c);

	QEQUAL(nc,colFound);

}

#endif

