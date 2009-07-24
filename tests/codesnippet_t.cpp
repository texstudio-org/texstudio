
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "codesnippet_t.h"
#include "codesnippet.h"
#include "qdocumentline.h"
#include "qeditor.h"
#include "testutil.h"
#include <QtTest/QtTest>
//placeholder position
class CP{
public:
	CP(): ay(-1){}
	CP(int line, int cursor):ay(line), ax(cursor), cy(line), cx(cursor){}
	CP(int line, int anchor, int cursor):ay(line), ax(anchor), cy(line), cx(cursor){}
	CP(int lineA, int anchor, int lineC, int cursor):ay(lineA), ax(anchor), cy(lineC), cx(cursor){}
	CP(int line, int anchor, int cursor, QList<CP> mir):ay(line), ax(anchor), cy(line), cx(cursor), mirrors(mir){}
	CP(int lineA, int anchor, int lineC, int cursor, QList<CP> mir):ay(lineA), ax(anchor), cy(lineC), cx(cursor), mirrors(mir){}
	int ay, ax, cy, cx;
	QList<CP> mirrors;
};
Q_DECLARE_METATYPE(CP);
Q_DECLARE_METATYPE(QList<CP>);


CodeSnippetTest::CodeSnippetTest(QEditor* editor): QObject(0), 	ed(editor){
	ed->document()->setLineEnding(QDocument::Unix); //necessary to compare with "\n" separated lines
}

void CodeSnippetTest::insert_data(){
	QTest::addColumn<QString>("editorText");
	QTest::addColumn<int>("cy");
	QTest::addColumn<int>("cx");
	QTest::addColumn<QString>("snippetText");
	QTest::addColumn<QString>("newText");
	QTest::addColumn<CP>("npos");
	QTest::addColumn<QList<CP> >("placeholder");
	
	QTest::newRow("trivial") 
		<< "abcd\nefgh"
		<< 0 << 2
		<< "trivial" 
		<< "abtrivialcd\nefgh"
		<< CP(0,9) 
		<< QList<CP>();
	QTest::newRow("multirow") 
		<< "abcd\nefgh"
		<< 0 << 2
		<< "1%n2%n3" 
		<< "ab1\n2\n3cd\nefgh"
		<< CP(2,1) 
		<< QList<CP>();
	QTest::newRow("cursor") 
		<< "abcd\nefgh"
		<< 0 << 2
		<< "tri%|vial" 
		<< "abtrivialcd\nefgh"
		<< CP(0,5) 
		<< QList<CP>();
	QTest::newRow("selection") 
		<< "abcd\nefgh"
		<< 0 << 2
		<< "tri%|via%|l" 
		<< "abtrivialcd\nefgh"
		<< CP(0,5,8) 
		<< QList<CP>();
	QTest::newRow("multirow") 
		<< "abcd\nefgh"
		<< 0 << 2
		<< "1%n2%n3" 
		<< "ab1\n2\n3cd\nefgh"
		<< CP(2,1) 
		<< QList<CP>();
	QTest::newRow("multirow cursor 0") 
		<< "abcd\nefgh"
		<< 0 << 2
		<< "%|1%n2%n3" 
		<< "ab1\n2\n3cd\nefgh"
		<< CP(0,2) 
		<< QList<CP>();
	QTest::newRow("multirow cursor 1") 
		<< "abcd\nefgh"
		<< 0 << 2
		<< "1%n2%|%n3x" 
		<< "ab1\n2\n3xcd\nefgh"
		<< CP(1,1) 
		<< QList<CP>();
	QTest::newRow("multirow cursor 2") 
		<< "abcd\nefgh"
		<< 0 << 2
		<< "1%n2%n3y%|" 
		<< "ab1\n2\n3ycd\nefgh"
		<< CP(2,2) 
		<< QList<CP>();
	/*QTest::newRow("multirow selection") 
		<< "abcd\nefgh"
		<< 0 << 2
		<< "1%|%n2%n3%|y" 
		<< "ab1\n2\n3ycd\nefgh"
		<< CP(0,1,2,1) 
		<< QList<CP>();*/
	//TODO: more tests 
}
void CodeSnippetTest::insert(){
	QFETCH(QString, editorText);
	QFETCH(QString, newText);
	if (!newText.endsWith("\n")) newText+="\n";
	QFETCH(int, cy);
	QFETCH(int, cx);
	QFETCH(QString, snippetText);
	QFETCH(CP, npos);
	QFETCH(QList<CP>, placeholder);
	
	ed->document()->setText(editorText);
	QDocumentCursor c = ed->document()->cursor(cy,cx);
	CodeSnippet(snippetText).insertAt(ed, &c);
	QEQUAL(ed->document()->text(),newText);
	QEQUAL(ed->cursor().anchorLineNumber(), npos.ay);
	QEQUAL(ed->cursor().anchorColumnNumber(), npos.ax);
	QEQUAL(ed->cursor().lineNumber(), npos.cy);
	QEQUAL(ed->cursor().columnNumber(), npos.cx);
}
#endif


