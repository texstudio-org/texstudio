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

	QTest::newRow("simple")
			<< "hello world!\nhello world!\nyeah!"
			<< 0 << true
			<< 1 << 0
			<< (QStringList() << "1|0|h" << "he" << "hel" << "hell" << "hello" << "1|6|world!");
	QTest::newRow("whole words")
			<< "hello world!\nhello hell hel he h!\nyeah!"
			<< (int)QDocumentSearch::WholeWords << true
			<< 1 << 0
			<< (QStringList() << "1|18|h" << "1|15|he" << "1|11|hel" << "1|6|hell" << "0|0|hello" << "0|6|world");
}
void QSearchReplacePanelTest::incrementalsearch(){
	QFETCH(QString, editorText);
	QFETCH(int, options);
	QFETCH(bool, cursor);
	
	QFETCH(int, sy);
	QFETCH(int, sx);
	
	QFETCH(QStringList, moves);
	
	ed->document()->setText(editorText);
	panel->setOptions((QDocumentSearch::Options)options, cursor, false);
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
void QSearchReplacePanelTest::cleanupTestCase(){
}
#endif

