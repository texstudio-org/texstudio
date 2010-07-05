
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
		<< "cursor.insertText(\" \\\\label{test2}\\n\")";

	QTest::newRow("add Label3")
		<< "cursor.insertText(\" \\\\label{test3}\\n\");cursor.insertText(\" \\\\label{test4}\\n\");cursor.insertText(\" \\\\label{test5}\\n\");cursor.insertText(\" \\\\label{test6}\\n\")";

	QTest::newRow("change Label")
		<< "cursor.movePosition(1,cursorEnums.Up);cursor.movePosition(9,cursorEnums.Right);cursor.insertText(\"a\");cursor.insertText(\"b\");cursor.insertText(\"c\")";

	QTest::newRow("change Label2")
		<< "cursor.movePosition(1,cursorEnums.StartOfLine);cursor.movePosition(3,cursorEnums.Up);cursor.movePosition(9,cursorEnums.Right);cursor.insertText(\"a\");cursor.insertText(\"b\");cursor.insertText(\"c\")";

	QTest::newRow("change Label3")
		<< "cursor.deleteChar()";

	QTest::newRow("remove line")
		<< "cursor.eraseLine()";

	QTest::newRow("remove lines2")
		<< "cursor.movePosition(1,cursorEnums.EndOfLine);cursor.movePosition(1,cursorEnums.StartOfLine,cursorEnums.KeepAnchor);cursor.movePosition(1,cursorEnums.Up,cursorEnums.KeepAnchor);cursor.removeSelectedText()";

	QTest::newRow("add section")
			<< "cursor.movePosition(1,cursorEnums.End);cursor.insertText(\" \\\\section{sec:test}\\n\")";

	QTest::newRow("add section2")
			<< "cursor.movePosition(1,cursorEnums.End);cursor.insertText(\" \\\\section{sec:test}\\n\")";

	QTest::newRow("change section")
		<< "cursor.movePosition(1,cursorEnums.Up);cursor.movePosition(11,cursorEnums.Right);cursor.insertText(\"a\");cursor.insertText(\"b\");cursor.insertText(\"c\")";

	QTest::newRow("change section2")
		<< "cursor.movePosition(1,cursorEnums.StartOfLine);cursor.movePosition(2,cursorEnums.Right);cursor.insertText(\"sub\")";

	QTest::newRow("change section3")
		<< "cursor.movePosition(1,cursorEnums.StartOfLine);cursor.movePosition(2,cursorEnums.Right);cursor.insertText(\"sub\")";

	QTest::newRow("change section4")
		<< "cursor.movePosition(1,cursorEnums.StartOfLine);cursor.movePosition(2,cursorEnums.Right);cursor.movePosition(6,cursorEnums.Right,cursorEnums.KeepAnchor);cursor.removeSelectedText()";

	QTest::newRow("set sequence of headings")
			<< "editor.setText(\"\\\\section{a}\\n\\\\section{b}\\n\\\\section{c}\\n\")";

	QTest::newRow("change heading in line 1 up")
			<< "cursor.moveTo(0,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\chapter{a}\")";

	QTest::newRow("change heading in line 1 up")
			<< "cursor.moveTo(0,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\subsection{a}\")";

	QTest::newRow("change heading in line 1 back")
			<< "cursor.moveTo(0,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\section{a}\")";

	QTest::newRow("change heading in line 2 up")
			<< "cursor.moveTo(1,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\chapter{b}\")";

	QTest::newRow("change heading in line 1 (remove)")
			<< "cursor.moveTo(0,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\ssection{a}\")";

	QTest::newRow("change heading in line 1 (add)")
			<< "cursor.moveTo(0,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\section{a}\")";

	QTest::newRow("change heading in line 2 down")
			<< "cursor.moveTo(1,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\subsection{b}\")";

	QTest::newRow("change heading in line 2 back")
			<< "cursor.moveTo(1,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\section{b}\")";

	QTest::newRow("change heading in line 3 up")
			<< "cursor.moveTo(2,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\chapter{c}\")";

	QTest::newRow("change heading in line 3 down")
			<< "cursor.moveTo(2,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\subsection{c}\")";

	QTest::newRow("change heading in line 3 back")
			<< "cursor.moveTo(2,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\section{c}\")";

	QTest::newRow("set sequence of sections/subsection")
			<< "editor.setText(\"\\\\section{a}\\n\\\\subsection{sdfgsdfgsdfgsfgb}\\n\\\\subsection{c}\\n\")";

	QTest::newRow("change heading in line 2 down")
			<< "cursor.moveTo(1,0);cursor.movePosition(1,cursorEnums.EndOfLine);cursor.movePosition(3,cursorEnums.Left);cursor.insertText(\"df\")";

	QTest::newRow("set sequence of sections/chapter")
			<< "editor.setText(\"\\\\section{a}\\n\\\\section{b}\\n\\\\chapter{c}\\n\")";

	QTest::newRow("change heading in line 2 up")
			<< "cursor.moveTo(1,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\chapter{b}\")";

	QTest::newRow("set sequence of sections/subsec")
			<< "editor.setText(\"\\\\section{a}\\n\\\\subsection{b}\\n\")";

	QTest::newRow("change heading in line 2 up")
			<< "cursor.moveTo(0,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\chapter{a}\")";

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
	int i=0;
	StructureEntry *l=se;
	while(l->parent){
		l=l->parent;
		i++;
	}
	line+=QString(" IND:%1").arg(i);
	result << line;
	//qDebug(qPrintable(line));
    }
    return result;
}

void StructureViewTest::benchmark_data(){
#if QT_VERSION >= 0x040500	
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("start");
	QTest::addColumn<int>("count");

	//-------------cursor without selection--------------
	QTest::newRow("single line text")
		<< "abcdefg\nhallo welt\nabcdefg"
		<< 0 << 1;

	QTest::newRow("labels1")
		<< "\\label{a}\nhallo welt\n\\label{b}\nabcdefg\n\\label{c}"
		<< 0 << 1;

	QTest::newRow("labels2")
		<< "\\label{a}\nhallo welt\n\\label{b}\nabcdefg\n\\label{c}"
		<< 2 << 1;

	QTest::newRow("labels3")
		<< "\\label{a}\nhallo welt\n\\label{b}\nabcdefg\n\\label{c}"
		<< 4 << 1;

	QTest::newRow("sections")
		<< "\\section{a}\nhallo welt\n\\section{b}\nabcdefg\n\\section{c}"
		<< 2 << 1;

	QTest::newRow("sections with many children")
		<< "\\section{a}\nhallo welt\n\\section{b}\nabcdefg\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}\n\\subsection{c}"
		<< 2 << 1;
#endif
}

void StructureViewTest::benchmark(){
#if QT_VERSION >= 0x040500	
	QFETCH(QString, text);
	QFETCH(int, start);
	QFETCH(int, count);

	ed->document()->setText(text);
	QBENCHMARK {
		document->patchStructure(start,count);
	}
#endif
}

#endif

