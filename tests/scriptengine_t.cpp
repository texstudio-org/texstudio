
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "scriptengine_t.h"
#include "scriptengine.h"
#include "latexeditorview.h"
#include "qdocumentcursor.h"
#include "qdocument.h"
#include "qeditor.h"
#include "testutil.h"
#include <QtTest/QtTest>
ScriptEngineTest::ScriptEngineTest(QEditor* editor): ed(editor){}

void ScriptEngineTest::script_data(){
	QTest::addColumn<QString>("script");
	QTest::addColumn<QString>("newText");
	
	//-------------cursor without selection--------------
	QTest::newRow("Setup Text")
		<< "editor.setText(\"Hallo\")"
		<< "Hallo";

	QTest::newRow("Insert Text")
		<< "cursor.insertText(\"a\");"
		<< "aHallo";

	QTest::newRow("Move Cursor")
		<< "cursor.moveTo(0,0);cursor.insertText(\"b\");"
		<< "baHallo";

	QTest::newRow("Delete Chars")
		<< "cursor.deletePreviousChar();cursor.deleteChar();"
		<< "Hallo";

	QTest::newRow("Undo")
		<< "editor.undo()"
		<< "baHallo";

	QTest::newRow("Redo")
		<< "editor.redo()"
		<< "Hallo";

	QTest::newRow("Select All/copy/paste")
		<< "editor.selectAll();editor.copy();editor.selectNothing();editor.paste()"
		<< "HalloHallo";

	QTest::newRow("Move Cursor")
		<< "cursor.movePosition(1,cursorEnums.Start);cursor.movePosition(1,cursorEnums.End,cursorEnums.KeepAnchor)"
		<< "HalloHallo";

}
void ScriptEngineTest::script(){
	QFETCH(QString, script);
	QFETCH(QString, newText);
	if (!newText.endsWith("\n")) newText+="\n";
	
	scriptengine eng(this);
	eng.setEditor(ed);
	eng.setScript(script);
	eng.run();

	QEQUAL(ed->document()->text(), newText);
	
}
#endif

