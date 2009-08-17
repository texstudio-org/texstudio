#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "qsearchreplacepanel_t.h"
#include "qsearchreplacepanel.h"
#include "qdocumentsearch.h"
#include "ui_searchreplace.h"
#include "qdocumentline.h"
#include "qeditor.h"
#include "qcodeedit.h"
#include "testutil.h"
#include <QtTest/QtTest>
//#include "windows.h"
QSearchReplacePanelTest::QSearchReplacePanelTest(QCodeEdit* codeedit): 
		QObject(0), ed(codeedit->editor()), panel(0){
	if (!codeedit->hasPanel("Search")) return;
	panel=qobject_cast<QSearchReplacePanel*>(codeedit->panels("Search")[0]);
}

void QSearchReplacePanelTest::initTestCase(){
	QVERIFY(panel);
	widget=(Ui::SearchReplace*)(panel);
	//QVERIFY(widget);
}

void QSearchReplacePanelTest::incrementalsearch_data(){
	//movement-form: "search text", "cursorLine|cursorColumn|searchText" or , "cursorLine|cursorColumn|searchText|foundText" 
	QTest::addColumn<QString >("editorText");
	QTest::addColumn<int>("options");
	QTest::addColumn<bool>("cursor");
	QTest::addColumn<int>("sy");
	QTest::addColumn<int>("sx");
	QTest::addColumn<QStringList>("moves");
	QTest::addColumn<int>("scopey1");
	QTest::addColumn<int>("scopex1");
	QTest::addColumn<int>("scopey2");
	QTest::addColumn<int>("scopex2");

	QTest::newRow("simple")
			<< "hello world!\nhello world!\nyeah!"
			<< 0 << true
			<< 1 << 0
			<< (QStringList() << "1|0|h" << "he" << "hel" << "hell" << "hello" << "1|6|world!")
			<< -1 << -1 << -1 << -1;
	QTest::newRow("whole words")
			<< "hello world!\nhello hell hel he h!\nyeah!"
			<< (int)QDocumentSearch::WholeWords << true
			<< 1 << 0
			<< (QStringList() << "1|18|h" << "1|15|he" << "1|11|hel" << "1|6|hell" << "0|0|hello" << "0|6|world")
			<< -1 << -1 << -1 << -1;
	QTest::newRow("regexp scoped")
			<< "seven dwarfs go around\nlooking for the worthful treasure\nthey are digging at the beach"
			<< (int)QDocumentSearch::RegExp << true
			<< 0 << 0
			<< (QStringList() << "0|14|[aeiou]|o" << "0|14|[aeiou]|o" << "0|14|[aeiou]|o" << "1|1|o{2,}|oo" << "1|1|[aeiou]|o" << "1|22|u" << "1|22|u.|ul" << "1|23|l " << "1|23|l t" << "1|25|tr[aeoiu]*|trea" << "2|1|h.y|hey" << "1|26|re")
			<< 0 << 9 << 2 << 7;
}
void QSearchReplacePanelTest::incrementalsearch(){
	QFETCH(QString, editorText);
	QFETCH(int, options);
	QFETCH(bool, cursor);
	
	QFETCH(int, sy);
	QFETCH(int, sx);
	
	QFETCH(QStringList, moves);

	QFETCH(int, scopey1);
	QFETCH(int, scopex1);
	QFETCH(int, scopey2);
	QFETCH(int, scopex2);
	
	
	for (int loop=0; loop<2; loop++) {
		panel->display(1,loop==1);
		ed->document()->setText(editorText);
		if (scopey1!=-1) {
			widget->cbSelection->setChecked(true);
			ed->setCursor(ed->document()->cursor(scopey1,scopex1,scopey2,scopex2));
		}
		panel->setOptions((QDocumentSearch::Options)options, cursor, scopey1!=-1);
		ed->setCursorPosition(sy,sx);
		
		int cx=-1;
		int cy=-1;
		foreach (const QString& s, moves){
			QString search=s;
			QStringList sl = s.split("|");
			QVERIFY(sl.count()==1||sl.count()==3||sl.count()==4);
			if (sl.count()>=3){
				cy=sl[0].toInt();
				cx=sl[1].toInt();
				search=sl[2];
			} 
			QString res=search;
			if (sl.count()==4) res=sl[3];
			
			//it doesn't react to setText
			if (search.isEmpty()) {
				widget->leFind->setText("a");
				widget->leFind->cursorForward(false);	
				QTest::keyClick(widget->leFind,Qt::Key_Backspace);
			} else {
				widget->leFind->setText(search.left(search.length()-1));
				widget->leFind->cursorForward(false,search.length());	
				QTest::keyClick(widget->leFind,search[search.length()-1].toLatin1());
			}
			QDocumentCursor s=ed->cursor().selectionStart();
			QEQUAL2(s.lineNumber(), cy, search+" "+ed->cursor().selectedText());
			QEQUAL2(s.columnNumber(), cx, search+" "+ed->cursor().selectedText());
			QEQUAL2(ed->cursor().selectedText(), res, search+" "+ed->cursor().selectedText());
		}
	}
}
void QSearchReplacePanelTest::findNext_data(){
	QTest::addColumn<QString >("editorText");
	QTest::addColumn<int>("options");
	QTest::addColumn<int>("sy");
	QTest::addColumn<int>("sx");
	QTest::addColumn<QString >("search");
	QTest::addColumn<QStringList>("positions"); //y|x
	
	QTest::newRow("simple") 
		<< "Hello World\nHello!!heLlO!!\nHello World!"
		<< 0 << 0 << 0
		<< "hello"
		<< (QStringList() << "0|0|Hello" << "1|0|Hello" << "1|7|heLlO" << "2|0|Hello");
}
void QSearchReplacePanelTest::findNext(){
	QFETCH(QString, editorText);
	QFETCH(int, options);
	QFETCH(int, sy);
	QFETCH(int, sx);
	QFETCH(QString, search);
	QFETCH(QStringList, positions);

	for (int highlightRun=0; highlightRun<2; highlightRun++) {
		ed->document()->setText(editorText);
		panel->setOptions(options,true,false);
		ed->setCursorPosition(sy,sx);
		ed->find(search,highlightRun!=0,false);
		panel->display(0,false);
		for (int i=0;i<positions.size();i++){
			QStringList pos=positions[i].split('|');
			QEQUAL(pos.size(),3);			
			QEQUAL2(ed->cursor().selectionStart().lineNumber(),pos[0].toInt(),QString("%1 highlight-run: %2").arg(positions[i]).arg(highlightRun));
			QEQUAL2(ed->cursor().selectionStart().columnNumber(),pos[1].toInt(),QString("%1 highlight-run: %2").arg(positions[i]).arg(highlightRun));
			QEQUAL2(ed->cursor().selectedText(),pos[2],QString("%1 highlight-run: %2").arg(positions[i]).arg(highlightRun));
			if (i!=positions.size()-1) 
				panel->findNext();
		}
	}
}
void QSearchReplacePanelTest::findReplace_data(){
	QTest::addColumn<QString >("editorText");
	QTest::addColumn<int>("options");
	QTest::addColumn<int>("sy");
	QTest::addColumn<int>("sx");
	QTest::addColumn<QStringList>("movements"); //search|y|x or search|y|x|replace|new text
	
	QTest::newRow("simple find")
		<< "hello\nhello\nhello!!!"
		<< 0
		<< 0 << 0
		<< (QStringList() << "llo|0|2" << "hello|1|0" << "hello!!!|2|0");
	QTest::newRow("simple replace")
		<< "hello\nhello\nhello!!!"
		<< 0
		<< 0 << 0
		<< (QStringList() 
			<< "hello|0|0"
			<< "hello|1|0|mouse|mouse\nhello\nhello!!!" 
			<< "hello|2|0|mouse|mouse\nmouse\nhello!!!");
	QTest::newRow("replace new occurences")
		<< "abc\nabc\nabc"
		<< 0
		<< 0 << 0
		<<(QStringList() 
		 	<< "abc|0|0"
			<< "abc|1|0"
			<< "abc|2|0|abc abc|abc\nabc abc\nabc" 
			<< "abc|0|0|1"
			<< "abc|1|0"
			<< "abc|1|4"
			<< "abc|2|0");
	QTest::newRow("replace new occurences with empty lines")
		<< "abc\n\n\nabc\n\n\nabc"
		<< 0
		<< 0 << 0
		<< (QStringList() 
			<<  "abc|0|0"
			<< "abc|3|0"
			<< "abc|6|0|abc abc|abc\n\n\nabc abc\n\n\nabc" 
			<< "abc|0|0|1"
			<< "abc|3|0"
			<< "abc|3|4"
			<< "abc|6|0");
	
}
void QSearchReplacePanelTest::findReplace(){
	QFETCH(QString, editorText);
	QFETCH(int, options);
	QFETCH(int, sy);
	QFETCH(int, sx);
	QFETCH(QStringList, movements);
	panel->display(1,true);
	for (int highlightRun=0; highlightRun<2; highlightRun++) {
		ed->document()->setText(editorText);
		panel->setOptions(options | (highlightRun?QDocumentSearch::HighlightAll:0), true, false);
		ed->setCursorPosition(sy,sx);
		
		for (int i=0;i<movements.size();i++){
			QStringList move=movements[i].split('|');
			QVERIFY(move.size()>=3);
			widget->leFind->setText(move[0]);
			if (move.size()==5) {
				widget->leReplace->setText(move[3]);
				widget->bReplaceNext->click();
				QString newText=move[4];
				if (!newText.endsWith("\n")) newText+="\n";
				QEQUAL2(ed->document()->text(),newText,QString("%1 highlight-run: %2").arg(movements[i]).arg(highlightRun));
			} else {
				bool mes=false;
				if (move.size()==4) mes=true;
				else QVERIFY(move.size()==3);
				if (mes) QTest::closeMessageBoxLater(true,QMessageBox::Yes);
				widget->bNext->click();
				if (mes) QTest::messageBoxShouldBeClose();
				QApplication::processEvents();
			}
			//QApplication::processEvents();
			//Sleep(1000);
			QEQUAL2(ed->cursor().selectionStart().lineNumber(),move[1].toInt(),QString("%1 highlight-run: %2").arg(movements[i]).arg(highlightRun));			QEQUAL2(ed->cursor().selectionStart().columnNumber(),move[2].toInt(),QString("%1 highlight-run: %2").arg(movements[i]).arg(highlightRun));
			QEQUAL2(ed->cursor().selectedText(),move[0],QString("%1 highlight-run: %2").arg(movements[i]).arg(highlightRun));
		}
	}	
}
void QSearchReplacePanelTest::findReplaceSpecialCase(){
	//test for a strange special case
	ed->document()->setText("abc\n\n\nabc\n\n\nabc");
	widget->leFind->setText("abc");
	ed->setCursorPosition(0,0);
	panel->setOptions(QDocumentSearch::HighlightAll, true, false);
	
	widget->bNext->click();
	QEQUAL2(ed->cursor().lineNumber(),0,"a"); QEQUAL(ed->cursor().selectionStart().columnNumber(),0);
	
	widget->bNext->click();
	QEQUAL2(ed->cursor().lineNumber(),3,"b"); QEQUAL(ed->cursor().selectionStart().columnNumber(),0);
	
	widget->leReplace->setText("abc abc");
	widget->bReplaceNext->click();
	QEQUAL2(ed->cursor().lineNumber(),6,"c"); QEQUAL(ed->cursor().selectionStart().columnNumber(),0);

	widget->bPrevious->click();
	QEQUAL2(ed->cursor().lineNumber(),3,"d"); QEQUAL(ed->cursor().selectionStart().columnNumber(),4);

	widget->bPrevious->click();
	QEQUAL2(ed->cursor().lineNumber(),3,"e"); QEQUAL(ed->cursor().selectionStart().columnNumber(),0);

	widget->bPrevious->click();
	QEQUAL2(ed->cursor().lineNumber(),0,"f"); QEQUAL(ed->cursor().selectionStart().columnNumber(),0);
}
void QSearchReplacePanelTest::cleanupTestCase(){
}
#endif

