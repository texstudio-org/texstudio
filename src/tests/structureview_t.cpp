
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
StructureViewTest::StructureViewTest(LatexEditorView* editor,LatexDocument *doc, bool all): edView(editor),document(doc), all(all){}

void StructureViewTest::script_data(){
	const QString trLabels = LatexDocument::tr("LABELS");
	QTest::addColumn<QString>("script");
	QTest::addColumn<QString>("expectedStructure");

	//-------------cursor without selection--------------
    QTest::newRow("Setup Text")
		<< "editor.setText(\"Hallo\")"
        <<"" ;


	QTest::newRow("add Label")
		<< "cursor.movePosition(1,cursorEnums.End);cursor.insertText(\"\\n \\\\label{test}\\n\")"
        << "Label:test LVL:0"
		;

	QTest::newRow("add Label2")
		<< "cursor.insertText(\" \\\\label{test2}\\n\")"
        << "Label:test LVL:0##Label:test2 LVL:0" ;

	QTest::newRow("add Label3")
		<< "cursor.insertText(\" \\\\label{test3}\\n\");cursor.insertText(\" \\\\label{test4}\\n\");cursor.insertText(\" \\\\label{test5}\\n\");cursor.insertText(\" \\\\label{test6}\\n\")"
        << "Label:test LVL:0##Label:test2 LVL:0##Label:test3 LVL:0##Label:test4 LVL:0##Label:test5 LVL:0##Label:test6 LVL:0" ;

	QTest::newRow("change Label")
		<< "cursor.movePosition(1,cursorEnums.Up);cursor.movePosition(9,cursorEnums.Right);cursor.insertText(\"a\");cursor.insertText(\"b\");cursor.insertText(\"c\")"
        << "Label:test LVL:0##Label:test2 LVL:0##Label:test3 LVL:0##Label:test4 LVL:0##Label:test5 LVL:0##Label:tabcest6 LVL:0" ;

	QTest::newRow("change Label2")
		<< "cursor.movePosition(1,cursorEnums.StartOfLine);cursor.movePosition(3,cursorEnums.Up);cursor.movePosition(9,cursorEnums.Right);cursor.insertText(\"a\");cursor.insertText(\"b\");cursor.insertText(\"c\")"
        << "Label:test LVL:0##Label:test2 LVL:0##Label:tabcest3 LVL:0##Label:test4 LVL:0##Label:test5 LVL:0##Label:tabcest6 LVL:0";


	QTest::newRow("change Label3")
		<< "cursor.deleteChar()"
        << "Label:test LVL:0##Label:test2 LVL:0##Label:tabcst3 LVL:0##Label:test4 LVL:0##Label:test5 LVL:0##Label:tabcest6 LVL:0" ;

	QTest::newRow("remove line")
		<< "cursor.eraseLine()"
        << "Label:test LVL:0##Label:test2 LVL:0##Label:test4 LVL:0##Label:test5 LVL:0##Label:tabcest6 LVL:0" ;

	QTest::newRow("remove lines2")
		<< "cursor.movePosition(1,cursorEnums.EndOfLine);cursor.movePosition(1,cursorEnums.StartOfLine,cursorEnums.KeepAnchor);cursor.movePosition(1,cursorEnums.Up,cursorEnums.KeepAnchor);cursor.removeSelectedText()"
        << "Label:test LVL:0##Label:test5 LVL:0##Label:tabcest6 LVL:0" ;

	QTest::newRow("add section")
		<< "cursor.movePosition(1,cursorEnums.End);cursor.insertText(\" \\\\section{sec:test}\\n\")"
        << "Label:test LVL:0##Label:test5 LVL:0##Label:tabcest6 LVL:0##Section:sec:test LVL:2" ;

	QTest::newRow("add section2")
		<< "cursor.movePosition(1,cursorEnums.End);cursor.insertText(\" \\\\section{sec:test}\\n\")"
        << "Label:test LVL:0##Label:test5 LVL:0##Label:tabcest6 LVL:0##Section:sec:test LVL:2##Section:sec:test LVL:2" ;

	QTest::newRow("change section")
		<< "cursor.movePosition(1,cursorEnums.Up);cursor.movePosition(11,cursorEnums.Right);cursor.insertText(\"a\");cursor.insertText(\"b\");cursor.insertText(\"c\")"
        << "Label:test LVL:0##Label:test5 LVL:0##Label:tabcest6 LVL:0##Section:sec:test LVL:2##Section:sabcec:test LVL:2" ;

	QTest::newRow("change section2")
		<< "cursor.movePosition(1,cursorEnums.StartOfLine);cursor.movePosition(2,cursorEnums.Right);cursor.insertText(\"sub\")"
        << "Label:test LVL:0##Label:test5 LVL:0##Label:tabcest6 LVL:0##Section:sec:test LVL:2##Section:sabcec:test LVL:3" ;

	QTest::newRow("change section3")
		<< "cursor.movePosition(1,cursorEnums.StartOfLine);cursor.movePosition(2,cursorEnums.Right);cursor.insertText(\"sub\")"
        << "Label:test LVL:0##Label:test5 LVL:0##Label:tabcest6 LVL:0##Section:sec:test LVL:2##Section:sabcec:test LVL:4" ;

	if (!globalExecuteAllTests)
		qDebug("skipped some tests");
	else {
        QTest::newRow("change section4")
			<< "cursor.movePosition(1,cursorEnums.StartOfLine);cursor.movePosition(2,cursorEnums.Right);cursor.movePosition(6,cursorEnums.Right,cursorEnums.KeepAnchor);cursor.removeSelectedText()"
            << "Label:test LVL:0##Label:test5 LVL:0##Label:tabcest6 LVL:0##Section:sec:test LVL:2##Section:sabcec:test LVL:2" ;

		QTest::newRow("set sequence of headings")
                << "editor.setText(\"\\\\documentclass{book}\\n\\\\section{a}\\n\\\\section{b}\\n\\\\section{c}\\n\")"
                << "Section:a LVL:2##Section:b LVL:2##Section:c LVL:2" ;

		QTest::newRow("change heading in line 1 up")
                << "cursor.moveTo(1,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\chapter{a}\")"
                << "Section:a LVL:1##Section:b LVL:2##Section:c LVL:2" ;

		QTest::newRow("change heading in line 1 up")
                << "cursor.moveTo(1,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\subsection{a}\")"
                << "Section:a LVL:3##Section:b LVL:2##Section:c LVL:2" ;

		QTest::newRow("change heading in line 1 back")
                << "cursor.moveTo(1,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\section{a}\")"
                << "Section:a LVL:2##Section:b LVL:2##Section:c LVL:2" ;

		QTest::newRow("change heading in line 2 up")
                << "cursor.moveTo(2,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\chapter{b}\")"
                << "Section:a LVL:2##Section:b LVL:1##Section:c LVL:2" ;

		QTest::newRow("change heading in line 1 (remove)")
                << "cursor.moveTo(1,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\ssection{a}\")"
                << "Section:b LVL:1##Section:c LVL:2" ;

		QTest::newRow("change heading in line 1 (add)")
                << "cursor.moveTo(1,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\section{a}\")"
                << "Section:a LVL:2##Section:b LVL:1##Section:c LVL:2" ;

		QTest::newRow("change heading in line 2 down")
                << "cursor.moveTo(2,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\subsection{b}\")"
                << "Section:a LVL:2##Section:b LVL:3##Section:c LVL:2" ;

		QTest::newRow("change heading in line 2 back")
                << "cursor.moveTo(2,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\section{b}\")"
                << "Section:a LVL:2##Section:b LVL:2##Section:c LVL:2" ;

		QTest::newRow("change heading in line 3 up")
                << "cursor.moveTo(3,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\chapter{c}\")"
                << "Section:a LVL:2##Section:b LVL:2##Section:c LVL:1" ;

		QTest::newRow("change heading in line 3 down")
                << "cursor.moveTo(3,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\subsection{c}\")"
                << "Section:a LVL:2##Section:b LVL:2##Section:c LVL:3" ;

		QTest::newRow("change heading in line 3 back")
                << "cursor.moveTo(3,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\section{c}\")"
                << "Section:a LVL:2##Section:b LVL:2##Section:c LVL:2" ;

		QTest::newRow("set sequence of sections/subsection")
				<< "editor.setText(\"\\\\section{a}\\n\\\\subsection{sdfgsdfgsdfgsfgb}\\n\\\\subsection{c}\\n\")"
                << "Section:a LVL:2##Section:sdfgsdfgsdfgsfgb LVL:3##Section:c LVL:3" ;

		QTest::newRow("change heading in line 2 down")
				<< "cursor.moveTo(1,0);cursor.movePosition(1,cursorEnums.EndOfLine);cursor.movePosition(3,cursorEnums.Left);cursor.insertText(\"df\")"
                << "Section:a LVL:2##Section:sdfgsdfgsdfgsfdfgb LVL:3##Section:c LVL:3" ;

		QTest::newRow("set sequence of sections/chapter")
                << "editor.setText(\"\\\\documentclass{book}\\n\\\\section{a}\\n\\\\section{b}\\n\\\\chapter{c}\\n\")"
                << "Section:a LVL:2##Section:b LVL:2##Section:c LVL:1" ;

		QTest::newRow("change heading in line 2 up")
                << "cursor.moveTo(2,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\chapter{b}\")"
                << "Section:a LVL:2##Section:b LVL:1##Section:c LVL:1" ;

		QTest::newRow("set sequence of sections/subsec")
                << "editor.setText(\"\\\\documentclass{book}\\n\\\\section{a}\\n\\\\subsection{b}\\n\")"
                << "Section:a LVL:2##Section:b LVL:3" ;

		QTest::newRow("change heading in line 2 up")
                << "cursor.moveTo(1,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\chapter{a}\")"
                << "Section:a LVL:1##Section:b LVL:3" ;

		QTest::newRow("set sequence of subsection/section")
				<< "editor.setText(\"\\\\subsection{a}\\n\\\\subsection{b}\\n\\\\section{c}\\n\")"
                << "Section:a LVL:3##Section:b LVL:3##Section:c LVL:2" ;

		QTest::newRow("change first subsection to section")
				<< "cursor.moveTo(0,0);cursor.movePosition(1,cursorEnums.EndOfLine,cursorEnums.KeepAnchor);cursor.replaceSelectedText(\"\\\\section{a}\")"
                << "Section:a LVL:2##Section:b LVL:3##Section:c LVL:2" ;

		QTest::newRow("Nested structure on one line")
                << "editor.setText(\"\\\\documentclass{book}\\n123\\\\chapter{abc}...\\\\section{def},,,\\\\chapter{xyz}\")"
                << "Section:abc LVL:1##Section:def LVL:2##Section:xyz LVL:1";

		QTest::newRow("Structure/include")
                    << "editor.setText('\\\\documentclass{book}\\n'); cursor.moveTo(1,0); cursor.insertText('\\\\chapter{c}\\n'); cursor.insertText('\\\\include{incl}\\n'); cursor.insertText('\\\\section{s}\\n');cursor.insertText('\\\\subsection{ss}\\n');"
                << "Section:c LVL:1##Include:incl LVL:0##Section:s LVL:2##Section:ss LVL:3";

		QTest::newRow("Structure/include 2")
                    << "editor.setText('\\\\documentclass{book}\\n'); cursor.moveTo(1,0); cursor.insertText('\\\\chapter{c}\\n'); cursor.insertText('\\\\section{s}\\n');cursor.insertText('\\\\subsection{ss}\\n'); cursor.moveTo(2,0); cursor.insertText('\\\\include{incl}\\n'); "
                << "Section:c LVL:1##Include:incl LVL:0##Section:s LVL:2##Section:ss LVL:3";

		QTest::newRow("Structure/include 3")
                    << "editor.setText('\\\\documentclass{book}\\n'); cursor.moveTo(1,0); cursor.insertText('\\\\chapter{c}\\n'); cursor.insertText('\\\\section{s}\\n');cursor.insertText('\\\\subsection{ss}\\n'); cursor.moveTo(2,0); cursor.insertText('\\\\include{incl}'); cursor.insertText('\\n');"
                << "Section:c LVL:1##Include:incl LVL:0##Section:s LVL:2##Section:ss LVL:3";

		QTest::newRow("Structure/include 4")
                    << "editor.setText('\\\\documentclass{book}\\n'); cursor.moveTo(1,0); cursor.insertText('\\\\chapter{c}\\n'); cursor.insertText('\\\\subsection{ss}\\n'); cursor.moveTo(2,0); cursor.insertText('\\\\include{incl}\\n\\\\section{s}\\n');"
                << "Section:c LVL:1##Include:incl LVL:0##Section:s LVL:2##Section:ss LVL:3";

		QTest::newRow("Move section")
                    << "editor.setText('\\\\documentclass{book}\\n'); cursor.moveTo(1,0); cursor.insertText('\\\\chapter{c}\\n'); cursor.insertText('\\\\section{s}\\n');  cursor.insertText('\\\\subsection{ss}\\n');  cursor.moveTo(2,0); cursor.insertLine();"
                    << "Section:c LVL:1##Section:s LVL:2##Section:ss LVL:3";

		QTest::newRow("Delete empty line")
				    << "editor.setText(''); cursor.moveTo(0,0); editor.insertText('\\\\section{s}\\n\\n\\\\subsection{ss}'); cursor.moveTo(1,0); cursor.deletePreviousChar();"
                    << "Section:s LVL:2##Section:ss LVL:3";

		QTest::newRow("Section before chapter,include,section")
                    << "editor.setText('\\\\documentclass{book}\\n'); cursor.moveTo(1,0); editor.insertText('\\n\\n\\\\chapter{title}\\\\include{file}\\\\section{s}'); cursor.moveTo(1,0); cursor.insertText('\\\\section{s}');"
                    << "Section:s LVL:2##Section:title LVL:1##Include:file LVL:0##Section:s LVL:2";

		QTest::newRow("chapter/section/include/section")
                    << "editor.setText('\\\\documentclass{book}\\n\\\\chapter{title}\\\\section{s1}\\\\section{s2}\\\\section{s3}\\\\section{s4}\\\\include{in}\\\\section{end}'); cursor.moveTo(1,2); cursor.deleteChar();"
                    << "Section:s1 LVL:2##Section:s2 LVL:2##Section:s3 LVL:2##Section:s4 LVL:2##Include:in LVL:0##Section:end LVL:2";

		QTest::newRow("inserting several before")
                    << "editor.setText('\\\\documentclass{book}\\n\\\\chapter{Yc}\\\\section{Ys1}\\\\section{Ys2}\\\\section{Ys3}\\\\chapter{Yc2}\\\\section{Ys4}\\\\section{Ys5}\\n\\\\chapter{Zc}\\\\section{Zs1}\\\\section{Zs2}'); cursor.moveTo(1,0); cursor.insertText('\\n');"
                    << "Section:Yc LVL:1##Section:Ys1 LVL:2##Section:Ys2 LVL:2##Section:Ys3 LVL:2##Section:Yc2 LVL:1##Section:Ys4 LVL:2##Section:Ys5 LVL:2##Section:Zc LVL:1##Section:Zs1 LVL:2##Section:Zs2 LVL:2";

	}
}

void StructureViewTest::script(){
	QFETCH(QString, script);
	QFETCH(QString, expectedStructure);

    scriptengine eng(nullptr);
	eng.setEditorView(edView);
	eng.setScript(script);
	eng.run();

    QStringList res1=unrollStructure(document->docStructure);
	QCOMPARE(res1.join("##"), expectedStructure);
//	qDebug() << "Unrolled Structure: " << res1.join("##");
	document->updateStructure();
    QStringList res2=unrollStructure(document->docStructure);
	QCOMPARE(res1,res2);
}

QString structureTypeToString(StructureEntry::Type type) {
	switch (type) {
	case StructureEntry::SE_DOCUMENT_ROOT: return "Root";
	case StructureEntry::SE_OVERVIEW: return "Overview";
	case StructureEntry::SE_SECTION: return "Section";
	case StructureEntry::SE_BIBTEX: return "BibTeX";
	case StructureEntry::SE_TODO: return "Todo";
	case StructureEntry::SE_INCLUDE: return "Include";
	case StructureEntry::SE_LABEL: return "Label";
//	case StructureEntry::SE_BLOCK: return "Block";
	default: Q_ASSERT(false);
	}
	return "Error";
}

QStringList StructureViewTest::unrollStructure(std::list<StructureEntry *> docStructure){
	QStringList result;
    for(auto it=docStructure.cbegin();it!=docStructure.cend();++it){
        StructureEntry *se=*it;
		QString line=QString("%1:%2 LVL:%3").arg(structureTypeToString(se->type)).arg(se->title).arg(se->level);
		result << line;
    }
	return result;
}

void StructureViewTest::benchmark_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("start");
	QTest::addColumn<int>("count");

	//-------------cursor without selection--------------
	QTest::newRow("single line text")
		<< "abcdefg\nhallo welt\nabcdefg"
		<< 0 << 1;

	if (!all) {
		qDebug("skipped benchmark data");
		return;
	}

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
}

void StructureViewTest::benchmark(){
	QFETCH(QString, text);
	QFETCH(int, start);
	QFETCH(int, count);

	if (!all) {
		qDebug() << "skipped benchmark";
		return;
	}

	edView->editor->setText(text, false);
	QBENCHMARK {
		document->patchStructure(start,count);
	}
}

#endif

