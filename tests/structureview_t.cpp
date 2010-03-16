
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "structureview_t.h"
#include "scriptengine.h"
#include "latexeditorview.h"
#include "qdocumentcursor.h"
#include "qdocument.h"
#include "qeditor.h"
#include "testutil.h"
#include <QtTest/QtTest>
StructureViewTest::StructureViewTest(QEditor* editor,LatexDocument *doc): ed(editor),document(doc){}

void StructureViewTest::script_data(){
	QTest::addColumn<QString>("script");
	
	//-------------cursor without selection--------------
	QTest::newRow("Setup Text")
		<< "editor.setText(\"Hallo\")";

	QTest::newRow("add Label")
		<< "cursor.movePosition(1,cursorEnums.End);cursor.insertText(\"\\n \\\\label{test}\\n\")";

	QTest::newRow("add Label2")
		<< "cursor.insertText(\"\\n \\\\label{test2}\\n\")";

	QTest::newRow("add Label3")
		<< "cursor.insertText(\"\\n \\\\label{test3}\\n\");cursor.insertText(\"\\n \\\\label{test4}\\n\");cursor.insertText(\"\\n \\\\label{test5}\\n\");cursor.insertText(\"\\n \\\\label{test6}\\n\")";

	QTest::newRow("change Label")
		<< "cursor.movePosition(1,cursorEnums.Up);cursor.movePosition(9,cursorEnums.Right);cursor.insertText(\"a\");cursor.insertText(\"b\");cursor.insertText(\"c\")";

	QTest::newRow("change Label2")
		<< "cursor.movePosition(1,cursorEnums.StartOfLine);cursor.movePosition(3,cursorEnums.Up);cursor.movePosition(9,cursorEnums.Right);cursor.insertText(\"a\");cursor.insertText(\"b\");cursor.insertText(\"c\")";

	QTest::newRow("change Label3")
		<< "cursor.deleteChar()";

	QTest::newRow("remove line")
		<< "cursor.eraseLine()";

	QTest::newRow("remove lines")
		<< "cursor.movePosition(1,cursorEnums.EndOfLine);cursor.movePosition(1,cursorEnums.StartOfLine,cursorEnums.keepAnchor);cursor.movePosition(2,cursorEnums.Up,cursorEnums.keepAnchor);cursor.deleteChar()";

}
void StructureViewTest::script(){
	QFETCH(QString, script);
	
	scriptengine eng(this);
	eng.setEditor(ed);
	eng.setScript(script);
	eng.run();

	QStringList res1=unrollStructure(document->baseStructure);
	document->updateStructure();
	QStringList res2=unrollStructure(document->baseStructure);
	QCOMPARE(res1,res2);
	
}
QStringList StructureViewTest::unrollStructure(StructureEntry *baseStructure){
    QStringList result;
    StructureEntryIterator iter(baseStructure);
    while (iter.hasNext()) {
	StructureEntry *se=iter.next();
	QString line=se->title;
	line+=QString(" LVL:%1").arg(se->level);
	result << line;
	qDebug(qPrintable(line));
    }
    return result;
}

#endif

