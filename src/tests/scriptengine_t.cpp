
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
ScriptEngineTest::ScriptEngineTest(LatexEditorView* editor, bool all): edView(editor), all(all){
	edView->editor->setCursorPosition(0,0);
	edView->editor->document()->clear();
}

void ScriptEngineTest::script_data(){
	QTest::addColumn<QString>("script");
	QTest::addColumn<QString>("newText");
	
	//-------------cursor without selection--------------
	QTest::newRow("Setup Text")
		<< "editor.setText(\"Hallo\", false)"
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
	if (all) {
		QTest::newRow("Select All/copy/paste")
		<< "editor.selectAll();editor.copy();editor.selectNothing();editor.paste()"
		<< "HalloHallo";	
	} else 
		QTest::newRow("SKIP Select All/copy/paste ")
		<< "editor.setText(\"HalloHallo\");"
		<< "HalloHallo";
	
	QTest::newRow("remove Selection")
		<< "cursor.movePosition(1,cursorEnums.Start);cursor.movePosition(5,cursorEnums.Right,cursorEnums.KeepAnchor);cursor.removeSelectedText()"
		<< "Hallo";

	QTest::newRow("get selected Text")
		<< "cursor.movePosition(1,cursorEnums.Start);cursor.movePosition(2,cursorEnums.Right,cursorEnums.KeepAnchor);a=cursor.selectedText();cursor.replaceSelectedText(\"be\");cursor.clearSelection();cursor.insertText(a)"
		<< "beHallo";

	QTest::newRow("check cursor movement out of range")
		<< "cursor.movePosition(2,cursorEnums.Left);cursor.movePosition(20,cursorEnums.Right);cursor.deleteChar();cursor.deletePreviousChar()"
		<< "ballo";  // a movement out of range is canceled completely

	QTest::newRow("check cursor movement out of range2")
		<< "cursor.moveTo(20,10);cursor.deleteChar();cursor.deletePreviousChar();cursor.eraseLine();cursor.insertText(\"as\")"
		<< "ballo";  // invalid cursors are not executed


	QTest::newRow("Search/Replace Test 1")
		<< "editor.setText(\"Hallo1\\nHallo2\\nHallo3\", false); editor.replace(\"a\", \"b\"); "
		<< "Hbllo1\nHallo2\nHallo3";
	QTest::newRow("Search/Replace Test 2")
		<< "editor.replace(\"ll\", \"tt\", editor.document().cursor(1,0,1,6)); "
		<< "Hbllo1\nHatto2\nHallo3";
	QTest::newRow("Search/Replace Test 3")
		<< "editor.replace(/b..o/, function(c){return editor.search(c.selectedText());}); "
		<< "H11\nHatto2\nHallo3";
	QTest::newRow("Search/Replace Test 4 (no conversion)")
		<< "editor.replace(/[0-9]*/, function(c){return 17+c.selectedText();}); "
		<<  "H1711\nHatto2\nHallo3";
	QTest::newRow("Search/Replace Test 5")
		<< "editor.replace(/[0-9]*/, function(c){return 17+1*c.selectedText();}); "
		<< "H1728\nHatto2\nHallo3";

	if (all) {
		QTest::newRow("Search/Replace Test 1g")
			<< "editor.setText(\"Hallo1\\nHallo2\\nHallo3\", false); editor.replace(\"a\", \"g\", \"b\"); "
			<< "Hbllo1\nHbllo2\nHbllo3";
		QTest::newRow("Search/Replace Test 2g")
			<< "editor.replace(\"ll\", \"g\", \"tt\", editor.document().cursor(1,0,1,6)); "
			<< "Hbllo1\nHbtto2\nHbllo3";
		QTest::newRow("Search/Replace Test 3gg")
			<< "editor.replace(/b..o/g, function(c){return editor.search(c.selectedText(),\"g\");}); "
			<< "H21\nH12\nH13";
		QTest::newRow("Search/Replace Test 4g (no conversion)")
			<< "editor.replace(/[0-9]*/g, function(c){return 17+c.selectedText();}); "
			<<  "H1721\nH1712\nH1713";
		QTest::newRow("Search/Replace Test 5g")
			<< "editor.replace(/[0-9]*/g, function(c){return 17+1*c.selectedText();}); "
			<< "H1738\nH1729\nH1730";
		QTest::newRow("Search/Replace Test 6g")
			<< "editor.replace(/h/g, 'test'); "
			<< "H1738\nH1729\nH1730";
		QTest::newRow("Search/Replace Test 7gi")
			<< "editor.replace(/h/gi, 'test'); "
			<< "test1738\ntest1729\ntest1730";
		QTest::newRow("Search/Replace Test function replacing")
			  << "editor.setText(\"Hallo1\\nHallo2\\nHallo3\", false); editor.replace(\"a\", \"g\", function(c){return \">\"+c.selectedText()+\"<\";}); "
			<< "H>a<llo1\nH>a<llo2\nH>a<llo3";
		QTest::newRow("Search/Replace Test function replacing 2")
			  << "editor.setText(\"Hallo1\\nHamlo2\\nHallo3\", false); editor.replace(/a./, \"g\", function(c){return \">\"+c.selectedText()+\"<\";}); "
			<< "H>al<lo1\nH>am<lo2\nH>al<lo3";
	}

	QTest::newRow("replaceSelectedText 1")
		<< "editor.setText(\"Hallo1\\nHallo2\\nHallo3\", false); editor.setCursor(editor.document().cursor(1,2,1,4)); editor.addCursorMirror(editor.document().cursor(2,2,2,4));  editor.replaceSelectedText('xYz'); "
		<< "Hallo1\nHaxYzo2\nHaxYzo3";

	QTest::newRow("replaceSelectedText 2")
		<< "editor.setText(\"Hallo1\\nHallo2\\nHalso3\", false); editor.setCursor(editor.document().cursor(1,2,1,4)); editor.addCursorMirror(editor.document().cursor(2,2,2,4));  editor.replaceSelectedText(function(s){return s.toUpperCase();}); "
		<< "Hallo1\nHaLLo2\nHaLSo3";

	QTest::newRow("replaceSelectedText 3")
		<< "editor.setText(\"Hallo1\\nHallo2\\nHallo3\", false); editor.setCursor(editor.document().cursor(1,2,1,4)); editor.addCursorMirror(editor.document().cursor(2,2,2,4));  editor.replaceSelectedText('x%<Y%>z', {'macro': true}); "
		<< "Hallo1\nHaxllzo2\nHaxllzo3";
}
void ScriptEngineTest::script(){
	QFETCH(QString, script);
	QFETCH(QString, newText);
    scriptengine eng(nullptr);
	eng.setEditorView(edView);
	eng.setScript(script);
	eng.run();

	QEQUAL(edView->editor->document()->text(), newText);	
}
#endif

