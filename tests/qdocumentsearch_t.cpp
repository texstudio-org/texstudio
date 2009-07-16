
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "qdocumentsearch_t.h"
#include "qdocumentsearch.h"
#include "qdocumentline.h"
#include "qeditor.h"
#include <QtTest/QtTest>
QDocumentSearchTest::QDocumentSearchTest(QEditor* editor): QObject(0), 	ed(editor){
}
void QDocumentSearchTest::initTestCase(){
	ds=new QDocumentSearch(ed,"",0);
}
//cursor movement
struct CM{
public:
	CM(): l(-1){}
	CM(bool adir, int line, int anchorOffset, int cursorOffset):dir(adir),l(line),ax(anchorOffset),cx(cursorOffset){
		
	}
	bool dir;
	int l,ax,cx;
};
Q_DECLARE_METATYPE(CM);
Q_DECLARE_METATYPE(QList<CM>);

//search previous
#define SP(a,b,c) CM(true, a, b, c)
//search next
#define SN(a,b,c) CM(false, a, b, c)

void QDocumentSearchTest::next_sameText_data(){
	QTest::addColumn<QString >("editorText");
	QTest::addColumn<QString >("searchText");
	QTest::addColumn<int>("options");
	QTest::addColumn<int>("sy");
	QTest::addColumn<int>("sx");

	QTest::addColumn<QList<CM> >("cms"); //cursorMovements
	
	
	QTest::newRow("forward-backward-simple")
		<< "wo?wo??wo?\nHello World!\nHello!\nWorld!!!!" 
		<< "wo" << 0
		<< 0 << 6
		<< (QList<CM>() 
			<< SN(0,7,9) << SP(0, 9, 7) << SN(0, 7, 9) 
			<< SN(1, 6, 8) << CM (false, 3, 0, 2) << SN(-1, -1, -1));
	QTest::newRow("forward-backward-case sensitive")
		<< "aaAaaAaaA\naAaAa\naaaaaaaa" 
		<< "aa" << (int)QDocumentSearch::CaseSensitive
		<< 0 << 2
		<< (QList<CM>() 
			<< SN(0, 3, 5) << SN(0, 6, 8) << SN(2, 0, 2) << SP(2, 2, 0)
			<< SP(0, 8, 6) << SN(0, 6, 8) << SN(2, 0, 2) << SN(2, 2, 4) 
			<< SN(2, 4, 6) << SN(2, 6, 8) << SP(2, 8, 6) << SP(2, 6, 4)
			<< SP(2, 4, 2) << SP(2, 2, 0) << SP(0, 8, 6) << SP(0, 5, 3) 
			<< SP(0, 2, 0) << SP(-1, -1, -1));
	QTest::newRow("forward-backward-case whole words")
		<< "aaAaaAaaA\naA aAa\naaa aa aaa\n" 
		<< "aA" << (int)QDocumentSearch::WholeWords
		<< 0 << 0
		<< (QList<CM>() 
			<< SN(1, 0, 2) << SN(2, 4, 6) << SP(2, 6, 4) << SP(1, 2, 0) << SN(1,0,2) << SN (2, 4, 6) << SN(-1,-1,-1));
	QTest::newRow("forward-backward-case whole words case sensitive ")
		<< "aa Aaa Aaa A\naA aAa\naa  aA aa a\n" 
		<< "aA" << (int)(QDocumentSearch::WholeWords | QDocumentSearch::CaseSensitive)
		<< 0 << 0
		<< (QList<CM>() 
			<< SN(1, 0, 2) << SN(2, 4, 6) << SP(2, 6, 4) << SP(1, 2, 0) << SN(1,0,2) << SN (2, 4, 6) << SN(-1,-1,-1));
	QTest::newRow("forward-backward-case reg exp (THIS FAILS DUE TO DESIGN ISSUES AND IS EXPECT TO FAIL IN THE MOMENT)")
		<< "Hello42World" 
		<< "[0-9]*" << (int)QDocumentSearch::RegExp
		<< 0 << 0
		<< (QList<CM>() 
			<< SN(0, 5, 7) << SN(-1,-1,-1));
			
	
}
void QDocumentSearchTest::next_sameText(){
	QFETCH(QString, editorText);
	QFETCH(QString, searchText);
	QFETCH(int, options);
	
	QFETCH(int, sy);
	QFETCH(int, sx);
	
	QFETCH(QList<CM>, cms);
	
	ed->document()->setText(editorText);
	ds->setSearchText(searchText);
	ds->setOptions((QDocumentSearch::Options)options |QDocumentSearch::Silent );
	
	ds->setOrigin(ed->document()->cursor(sy,sx));
	
	for (int i=0;i< cms.size();i++){
		QString sel;
		if (cms[i].l>=0)
			if (cms[i].ax<cms[i].cx) sel = ed->document()->line(cms[i].l).text().mid(cms[i].ax,cms[i].cx-cms[i].ax);
			else sel = ed->document()->line(cms[i].l).text().mid(cms[i].cx,cms[i].ax-cms[i].cx);
		ds->next(cms[i].dir);
		const char* errorMessage=QString("%1: %2 %3 %4  %5 expected %6 %7 %8").arg(i).arg(ds->cursor().lineNumber()).arg(ds->cursor().anchorColumnNumber()).arg(ds->cursor().columnNumber()).arg(ds->cursor().selectedText()).arg(cms[i].l).arg(cms[i].ax).arg(cms[i].cx).toLatin1().constData();
		QVERIFY2(ds->cursor().selectedText()== sel,errorMessage);
		QVERIFY2(ds->cursor().lineNumber()== cms[i].l,errorMessage);
		QVERIFY2(ds->cursor().columnNumber()== cms[i].cx,errorMessage);
		QVERIFY2(ds->cursor().anchorLineNumber()== cms[i].l,errorMessage);
		QVERIFY2(ds->cursor().anchorColumnNumber()== cms[i].ax,errorMessage);
		/*if (options & QDocumentSearch::Replace)
			QVERIFY(ed->document()->text()== newText[i]);*/
	}
	

}
void QDocumentSearchTest::cleanupTestCase(){
	delete ds;
}
#endif


