#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "scriptengine_t.h"
#include "scriptengine.h"
#include "latexdocument.h"
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
		<< "cursor.movePosition(2,cursorEnums.Left);cursor.movePosition(20,cursorEnums.Right);cursor.deleteChar();cursor.deletePreviousChar()"
		<< "ballo";  // a movement out of range is canceled completely

	QTest::newRow("check cursor movement out of range2")
		<< "cursor.moveTo(20,10);cursor.deleteChar();cursor.deletePreviousChar();cursor.eraseLine();cursor.insertText(\"as\")"
		<< "ballo";  // invalid cursors are not executed


	QTest::newRow("Search/Replace Test 1")
		<< "editor.setText(\"Hallo1\\nHallo2\\nHallo3\", false); editor.replace(\"a\", \"b\"); "
		<< "Hbllo1\nHallo2\nHallo3";
    //QTest::newRow("Search/Replace Test 2")
    //    << "editor.replace(\"ll\", \"tt\", editor.document().cursor(1,0,1,6)); "
    //	<< "Hbllo1\nHatto2\nHallo3";
    //QTest::newRow("Search/Replace Test 2")
    //        << "editor.replace(\"ll\", \"tt\", QDocumentCursor(editor.document(),1,0,1,6)); "
    //        << "Hbllo1\nHatto2\nHallo3";
    QTest::newRow("Search/Replace Test 2a")
        << "var c2=new QDocumentCursor(editor.document(),1,0,1,6); editor.replace(\"ll\", \"tt\", c2); "
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

    QTest::newRow("Search/Replace Test 1g")
            << "editor.setText(\"Hallo1\\nHallo2\\nHallo3\", false); editor.replace(\"a\", \"g\", \"b\"); "
            << "Hbllo1\nHbllo2\nHbllo3";

    QTest::newRow("Search/Replace Test 2g")
            << "var c2=new QDocumentCursor(editor.document(),1,0,1,6); editor.replace(\"ll\", \"g\", \"tt\", c2); "
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
#if (QT_VERSION>=QT_VERSION_CHECK(5,14,0))
    QTest::newRow("replaceSelectedText 1")
		<< "editor.setText(\"Hallo1\\nHallo2\\nHallo3\", false); editor.setCursor(editor.document().cursor(1,2,1,4)); editor.addCursorMirror(editor.document().cursor(2,2,2,4));  editor.replaceSelectedText('xYz'); "
		<< "Hallo1\nHaxYzo2\nHaxYzo3";

	QTest::newRow("replaceSelectedText 2")
		<< "editor.setText(\"Hallo1\\nHallo2\\nHalso3\", false); editor.setCursor(editor.document().cursor(1,2,1,4)); editor.addCursorMirror(editor.document().cursor(2,2,2,4));  editor.replaceSelectedText(function(s){return s.toUpperCase();}); "
		<< "Hallo1\nHaLLo2\nHaLSo3";

	QTest::newRow("replaceSelectedText 3")
		<< "editor.setText(\"Hallo1\\nHallo2\\nHallo3\", false); editor.setCursor(editor.document().cursor(1,2,1,4)); editor.addCursorMirror(editor.document().cursor(2,2,2,4));  editor.replaceSelectedText('x%<Y%>z', {'macro': true}); "
		<< "Hallo1\nHaxllzo2\nHaxllzo3";
#endif
}
void ScriptEngineTest::script(){
	QFETCH(QString, script);
	QFETCH(QString, newText);
	scriptengine eng(nullptr);
	eng.setEditorView(edView);
	eng.setScript(script);
    eng.run(true);

	QEQUAL(edView->editor->document()->text(), newText);
}

void ScriptEngineTest::scriptApp_data(){
    QTest::addColumn<QString>("script");
    QTest::addColumn<QString>("newText");

    QTest::newRow("app.version")
        << "var a=app.getVersion();editor.setText(a, false)"
        << QString::number(Version::parseVersionNumberToInt(TXSVERSION));
    QTest::newRow("app.currentFileName")
        << "var a=app.getCurrentFileName();editor.setText(a, false)"
        << "";
    QTest::newRow("fileChooser")
        << "fileChooser.setDir(\"/\"); fileChooser.setFilter(\"*.etx\") "
        << "";

}
void ScriptEngineTest::scriptApp(){
    QFETCH(QString, script);
    QFETCH(QString, newText);
    scriptengine eng(nullptr);
    eng.setEditorView(edView);
    eng.setScript(script);
    eng.run(true);

    QEQUAL(edView->editor->document()->text(), newText);
}

void ScriptEngineTest::getLineTokens_data(void)
{
	QTest::addColumn<QString>("documentText");
	QTest::addColumn<int>("lineNr");
	QTest::addColumn<QString>("jsonExpected");

	QTest::newRow("negative line number")
		<< (
			"\\documentclass{amsart}\n"
			"\\begin{document}\n"
			"some text\n"
			"\\end{document}"

		)
		<< -1
		<< "false";
	QTest::newRow("line 0")
		<< QString ()
		<< 0
		<< getLineTokensText(
			3,
			Token::command, Token::none, 0, 0, "\\documentclass",
			Token::braces, Token::documentclass, 14, 1, "{amsart}",
			Token::documentclass, Token::none, 15, 1, "amsart"
		);
	QTest::newRow("line 1")
		<< QString ()
		<< 1
		<< getLineTokensText(
			3,
			Token::command, Token::none, 0, 0, "\\begin",
			Token::braces, Token::beginEnv, 6, 1, "{document}",
			Token::beginEnv, Token::none, 7, 1, "document"
		);
	QTest::newRow("line 2")
		<< QString ()
		<< 2
		<< getLineTokensText(
			2,
			Token::word, Token::none, 0, 0, "some",
			Token::word, Token::none, 5, 0, "text"
		);
	QTest::newRow("line 3")
		<< QString ()
		<< 3
		<< getLineTokensText(
			3,
			Token::command, Token::none, 0, 0, "\\end",
			Token::braces, Token::env, 4, 1, "{document}",
			Token::env, Token::none, 5, 1, "document"
		);
	QTest::newRow("too big line number")
		<< QString ()
		<< 4
		<< "false";
}

void ScriptEngineTest::getLineTokens(void)
{
	QFETCH(QString, documentText);
	QFETCH(int, lineNr);
	QFETCH(QString, jsonExpected);

	if (!documentText.isEmpty()) {
		edView->editor->setText(documentText, false);
		edView->document->SynChecker.waitForQueueProcess(); // wait for syntax checker to finish (as it runs in a parallel thread)
	}
	scriptengine eng(nullptr);
	eng.setEditorView(edView);
	// Our JS script relies on JSON.stringify() not reordering the object properties in the resulting JSON string
	eng.setScript(
		QString(
			"tlExpected = JSON.stringify(%2);"
			"tlActual = JSON.stringify(editor.document().getLineTokens(%1));"
			"if (tlExpected !== tlActual) {"
				"throw ('Wrong tokens list. Expected ' + tlExpected + ', got ' + tlActual);"
			"}"
		)
		.arg(lineNr)
		.arg(jsonExpected)
	);
    eng.run(true);
}

/*!
 * \brief Converts the specified token list into a JSON string
 * \details Converts the specified token list into a JSON string. The numTokens parameter is followed by numTokens groups
 * of arguments, each group consisting of type, subtype, start column, level, text.
 * \param[in] numTokens The number of token groups
 * \returns Returns the JSON string for the token list.
 */
QString ScriptEngineTest::getLineTokensText(int numTokens, ...)
{
    QRegularExpression rxEscape("([\"\\\\])");

	va_list vaList;
	// We don't use QJsonDocument because it reorders the properties in the resulting JSON string.
	QString result("[");
	va_start(vaList, numTokens);
	for (int i = 0; i < numTokens; ++i) {
		if (i) {
			result += ",";
		}
		int type = va_arg(vaList, int);
		int subtype = va_arg(vaList, int);
		int startColumn = va_arg(vaList, int);
		int level = va_arg(vaList, int);
		QString text(va_arg(vaList, const char *));
		text.replace(rxEscape, "\\\\1");
		result +=
			QString ("{type:%1,subtype:%2,startColumn:%3,level:%4,text:\"%5\"}")
			.arg(type)
			.arg(subtype)
			.arg(startColumn)
			.arg(level)
			.arg(text);
	}
	va_end(vaList);
	result += "]";
	return result;
}

#endif
