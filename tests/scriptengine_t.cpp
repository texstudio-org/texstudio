
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

	QTest::newRow("remove Selection")
		<< "cursor.movePosition(1,cursorEnums.Start);cursor.movePosition(5,cursorEnums.Right,cursorEnums.KeepAnchor);cursor.removeSelectedText()"
		<< "Hallo";

	QTest::newRow("get selected Text")
		<< "cursor.movePosition(1,cursorEnums.Start);cursor.movePosition(2,cursorEnums.Right,cursorEnums.KeepAnchor);a=cursor.selectedText();cursor.replaceSelectedText(\"be\");cursor.clearSelection();cursor.insertText(a)"
		<< "beHallo";

	QTest::newRow("check cursor movement out of range")
		<< "cursor.movePosition(20,cursorEnums.Right);cursor.deleteChar();cursor.deletePreviousChar()"
		<< "bello";  // a movement out of range is canceled completely

	QTest::newRow("check cursor movement out of range")
		<< "cursor.moveTo(20,10);cursor.deleteChar();cursor.deletePreviousChar();cursor.eraseLine();cursor.insertText(\"as\")"
		<< "bello";  // invalid cursors are not executed
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

