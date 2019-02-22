#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "qsearchreplacepanel_t.h"
#include "qsearchreplacepanel.h"
#include "qdocumentcursor.h"
#include "qdocumentsearch.h"
#include "qformatscheme.h"
#include "qdocumentline.h"
#include "qeditor.h"
#include "qcodeedit.h"
#include "qcetestutil.h"
#include "testutil.h"
#include <QtTest/QtTest>

class QSearchReplacePanelProtectedBreaker: public QSearchReplacePanel{
	friend class QSearchReplacePanelTest;
};


//must return void to be able to use QEQUAL,...
void getHighlightedSelectionIntern(QEditor* ed, int &minLine, int& minCol, int& maxLine, int& maxCol, const QString& message){
	Q_ASSERT (ed && ed->document());
	if (!(ed && ed->document())) return;
	int f = ed->document()->getFormatId("selection");
	minLine=-1;
	maxLine=-1;
	int minRight = -1;
	for (int i=0;i<ed->document()->lines();i++){
		QList<QFormatRange> overlays= ed->document()->line(i).getOverlays(f);
		if (overlays.size()==0) continue;
		QEQUAL2(overlays.size(),1,"multiple selection highlighted on the same line"+message);
		minLine=i;
		minCol=ed->document()->line(i).length();
		int frLength=0;
		foreach (const QFormatRange& fr, overlays)
			if (fr.offset<minCol) {
				minCol=fr.offset;
				frLength=fr.length;
			}
		minRight=minCol+frLength;
		break;
	}
	if (minLine==-1) return;

	int maxLeft=-1;
	for (int i=ed->document()->lines()-1;i>=0;i--){
		QList<QFormatRange> overlays= ed->document()->line(i).getOverlays(f);
		if (overlays.size()==0) continue;
		QEQUAL2(overlays.size(),1,"multiple selection highlighted on the same line"+message);
		maxLine=i;
		maxCol=0;
		int frOffset=0;
		foreach (const QFormatRange& fr, overlays)
			if (fr.offset+fr.length>maxCol) {
				maxCol=fr.offset+fr.length;
				frOffset=fr.offset;
			}
		maxLeft=frOffset;
		break;
	}
	if (maxLine==-1) return;
	if (minLine!=maxLine) {
		QEQUAL2(maxLeft,0,"highlighted selection starts too late in last line"+message);
		QEQUAL2(minRight,ed->document()->line(minLine).length(),"highlighted selection too short in first line"+message);
	}
	for (int i = minLine+1;i<maxLine;i++){
		QList<QFormatRange> overlays= ed->document()->line(i).getOverlays(f);
		QSVERIFY2(overlays.size()<=1,"multiple selection highlighted on the same line"+message);
		QEQUAL2(overlays.size(),1,QString("no selection highlighted in line %1: %2").arg(i).arg(message));
		QEQUAL2(overlays[0].offset,0,"selection highlighting start not at offset 0: "+message);
		QEQUAL2(overlays[0].length, ed->document()->line(i).length(),"selection highlighting hasn't line length "+message);
	}
	
}
QDocumentCursor getHighlightedSelectionIntern(QEditor* ed, const QString& str){
	int minLine, minCol, maxLine, maxCol;
	getHighlightedSelectionIntern(ed,minLine, minCol, maxLine, maxCol, str);
	if (minLine==-1 || maxLine==-1) return QDocumentCursor();
	return ed->document()->cursor(minLine, minCol, maxLine, maxCol);
}

#define getHighlightedSelection(ed) getHighlightedSelectionIntern(ed, Q__POSITION__)

//#include "windows.h"
QSearchReplacePanelTest::QSearchReplacePanelTest(QCodeEdit* codeedit, bool executeAllTests):
        QObject(nullptr), ed(codeedit->editor()), panel(nullptr),widget(nullptr), allTests(executeAllTests){
	if (!codeedit->hasPanel("Search")) return;
	ed->setFlag(QEditor::HardLineWrap, false);
	panel=qobject_cast<QSearchReplacePanel*>(codeedit->panels("Search")[0]);
	Q_ASSERT(panel);
	oldFindHistory = static_cast<QSearchReplacePanelProtectedBreaker*>(panel)->getHistory();
	oldReplaceHistory = static_cast<QSearchReplacePanelProtectedBreaker*>(panel)->getHistory(false);
	panel->setSearchOnlyInSelection(true);
}

QSearchReplacePanelTest::~QSearchReplacePanelTest(){
	static_cast<QSearchReplacePanelProtectedBreaker*>(panel)->setHistory(oldFindHistory);
	static_cast<QSearchReplacePanelProtectedBreaker*>(panel)->setHistory(oldReplaceHistory, false);
}

void QSearchReplacePanelTest::initTestCase(){
	QVERIFY(panel);
	widget=static_cast<QSearchReplacePanelProtectedBreaker*>(panel);
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
	if (!allTests){
		qDebug("skipped some incremental search tests");
		return;
	}
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

	QTest::newRow("simple, cursor off")
			<< "hello world!\nhello world!\nyeah!"
			<< 0 << false
			<< 1 << 0
			<< (QStringList() << "0|0|h" << "he" << "hel" << "hell" << "hello" << "0|6|world!")
			<< -1 << -1 << -1 << -1;
	QTest::newRow("whole words, cursor off")
			<< "hello world!\nhello hell hel he h!\nyeah!"
			<< (int)QDocumentSearch::WholeWords << false
			<< 1 << 0
			<< (QStringList() << "1|18|h" << "1|15|he" << "1|11|hel" << "1|6|hell" << "0|0|hello" << "0|6|world")
			<< -1 << -1 << -1 << -1;
	QTest::newRow("regexp scoped, cursor off")
			<< "seven dwarfs go around\nlooking for the worthful treasure\nthey are digging at the beach"
			<< (int)QDocumentSearch::RegExp << false
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
		ed->setText(editorText, false);
		if (scopey1!=-1) {
			widget->cbSelection->setChecked(true);
			ed->setCursor(ed->document()->cursor(scopey1,scopex1,scopey2,scopex2));
			//test if the set search scope is correctly highlighted
			QCEMULTIEQUAL(getHighlightedSelection(ed), panel->getSearchScope(), ed->document()->cursor(scopey1,scopex1,scopey2,scopex2));
		}
		if (!cursor && loop!=0){ //reset, so it won't continue previous search
			panel->setOptions((QDocumentSearch::Options)options, true, scopey1!=-1);
			ed->setCursorPosition(0,0);
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
				widget->cFind->setEditText("a");
				widget->cFind->lineEdit()->cursorForward(false);	
				QTest::keyClick(widget->cFind->lineEdit(),Qt::Key_Backspace);
			} else {
				widget->cFind->setEditText(search.left(search.length()-1));
				widget->cFind->lineEdit()->cursorForward(false,search.length());	
				QTest::keyClick(widget->cFind->lineEdit(),search[search.length()-1].toLatin1());
			}
			QDocumentCursor c=ed->cursor().selectionStart();
			QEQUAL2(c.lineNumber(), cy, search+" "+ed->cursor().selectedText()+"  "+QString::number(loop));
			QEQUAL2(c.columnNumber(), cx, search+" "+ed->cursor().selectedText());
			QEQUAL2(ed->cursor().selectedText(), res, search+" "+ed->cursor().selectedText());
			//searching shouldn't change highlighted selection
			QCEMULTIEQUAL(getHighlightedSelection(ed), panel->getSearchScope(), ed->document()->cursor(scopey1,scopex1,scopey2,scopex2));			
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
		ed->setText(editorText, false);
		panel->setOptions(options,true,false);
		ed->setCursorPosition(sy,sx);
		//ed->find(search,highlightRun!=0,false);
		panel->find(search, false, highlightRun!=0, false, false, false);//init search
		panel->display(0,false);
		for (int i=0;i<positions.size();i++){
			QStringList pos=positions[i].split('|');
			QEQUAL(pos.size(),3);			
			QCEEQUAL2(ed->cursor(),ed->document()->cursor(pos[0].toInt(),pos[1].toInt(),pos[0].toInt(),pos[1].toInt()+pos[2].length()),QString("%1: %2 highlight-run: %3").arg(i).arg(positions[i]).arg(highlightRun));
			//QMessageBox::information(0,"abc","def",0);
			//QEQUAL2(ed->cursor().selectionStart().lineNumber(),pos[0].toInt(),QString("%1 highlight-run: %2").arg(positions[i]).arg(highlightRun));
			//QEQUAL2(ed->cursor().selectionStart().columnNumber(),pos[1].toInt(),.arg(highlightRun));
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
	if (!allTests){
		qDebug("skipped some findReplace tests");
		return;
	}
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
	ed->document()->setLineEnding(QDocument::Unix);
	for (int highlightRun=0; highlightRun<2; highlightRun++) {
		ed->setText(editorText, false);
		panel->setOptions(options | (highlightRun?QDocumentSearch::HighlightAll:0), true, false);
		ed->setCursorPosition(sy,sx);
		
		for (int i=0;i<movements.size();i++){
			QStringList move=movements[i].split('|');
			QVERIFY(move.size()>=3);
			widget->cFind->setEditText(move[0]);
			if (move.size()==5) {
				widget->cReplace->setEditText(move[3]);
				widget->bReplaceNext->click();
				QString newText=move[4];
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
			QEQUAL2(ed->cursor().selectionStart().lineNumber(),move[1].toInt(),QString("%1 highlight-run: %2").arg(movements[i]).arg(highlightRun));			
			QEQUAL2(ed->cursor().selectionStart().columnNumber(),move[2].toInt(),QString("%1 highlight-run: %2").arg(movements[i]).arg(highlightRun));
			QEQUAL2(ed->cursor().selectedText(),move[0],QString("%1 highlight-run: %2").arg(movements[i]).arg(highlightRun));
		}
	}	
}
void QSearchReplacePanelTest::findReplaceSpecialCase(){
	//test for a strange special case
	ed->setText("abc\n\n\nabc\n\n\nabc", false);
	widget->cFind->setEditText("abc");
	ed->setCursorPosition(0,0);
	panel->setOptions(QDocumentSearch::HighlightAll, true, false);
	
	widget->bNext->click();
	QEQUAL2(ed->cursor().lineNumber(),0,"a"); QEQUAL(ed->cursor().selectionStart().columnNumber(),0);
	
	widget->bNext->click();
	QEQUAL2(ed->cursor().lineNumber(),3,"b"); QEQUAL(ed->cursor().selectionStart().columnNumber(),0);
	
	widget->cReplace->setEditText("abc abc");
	widget->bReplaceNext->click();
	QEQUAL2(ed->cursor().lineNumber(),6,"c"); QEQUAL(ed->cursor().selectionStart().columnNumber(),0);

	widget->bPrevious->click();
	QEQUAL2(ed->cursor().lineNumber(),3,"d"); QEQUAL(ed->cursor().selectionStart().columnNumber(),4);

	widget->bPrevious->click();
	QEQUAL2(ed->cursor().lineNumber(),3,"e"); QEQUAL(ed->cursor().selectionStart().columnNumber(),0);

	widget->bPrevious->click();
	QEQUAL2(ed->cursor().lineNumber(),0,"f"); QEQUAL(ed->cursor().selectionStart().columnNumber(),0);
}

//this tests how the search panel reacts to an already existing selection
void QSearchReplacePanelTest::findSpecialCase2(){
    if (!allTests){
        qDebug("skipped failing test on travis-ci");
        return;
    }
	ed->setText("sela\nseli\nselo\nSSSSSSSSSSNAKE\nsnape", false);
	for (int useCursor=1; useCursor<2; useCursor++) {
		widget->cbCursor->setChecked(useCursor!=0); //doesn't depend on cursor (old, now it does depend, TODO: think about it)
		widget->cbSelection->setChecked(false);
		//init (necessary because find does changes the cursor if search text is changed)
		panel->find("el", false, false, false, false, false);
		for (int highlightRun=0; highlightRun<2; highlightRun++) {
			//goto next match if searched text is already selected
			ed->setCursor(ed->document()->cursor(0,1,0,3)); //select searched text
			panel->find("el", false, highlightRun!=0, false, false, false);
			QCEEQUAL2(ed->cursor(), ed->document()->cursor(1,1,1,3), highlightRun);
			
			//find first match if it is not selected, but touched
			ed->setCursor(ed->document()->cursor(0,1)); 
			panel->find("el", false, highlightRun!=0, false, false, false);
			QCEEQUAL(ed->cursor(), ed->document()->cursor(0,1,0,3));

			//find next match
			panel->find("el", false, highlightRun!=0, false, false, false);
			QCEEQUAL(ed->cursor(), ed->document()->cursor(1,1,1,3));

			//find second match if first is selected
			ed->setCursor(ed->document()->cursor(0,1,0,3)); 
			panel->find("el", false, highlightRun!=0, false, false, false);
			QCEEQUAL(ed->cursor(), ed->document()->cursor(1,1,1,3));

			//find first if backward searching
			panel->find("el", true, highlightRun!=0, false, false, false);
			QCEEQUAL(ed->cursor(), ed->document()->cursor(0,3,0,1));

			//find first if backward searching and second is selected
			ed->setCursor(ed->document()->cursor(1,1,1,3)); 
			panel->find("el", true, highlightRun!=0, false, false, false);
			QCEEQUAL(ed->cursor(), ed->document()->cursor(0,3,0,1));
		}
	}
	

	//test if the current selection is used as search scope
	for (int oldSel=0;oldSel<2;oldSel++){
		//multiline
		widget->cbSelection->setChecked(oldSel);
		panel->display(0,false);
		QDocumentCursor sel=ed->document()->cursor(0,2,2,3);
		ed->setCursor(sel);
		panel->display(1,false);
        QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);
        QEQUAL(widget->cbSelection->isChecked(),true);
		
		//single line
		panel->setUseLineForSearch(false);
		widget->cbSelection->setChecked(oldSel);
		panel->display(0,false);
		sel=ed->document()->cursor(0,2,0,3);
		ed->setCursor(sel);
		panel->display(1,false);
		QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);
		QEQUAL(widget->cbSelection->isChecked(),true);

		//not single line (=single line with disabled take selection)
		panel->setUseLineForSearch(true);
		widget->cbSelection->setChecked(oldSel);
		panel->display(0,false);
		ed->setCursor(sel);
		panel->display(1,false);
		QEQUAL(widget->cFind->currentText(),"l");
        QEQUAL(widget->cbSelection->isChecked(),false); // is automatically set to false for convinience

	}

	//test if first match in newly selected text is matched
	panel->display(0,false);
	QDocumentCursor sel=ed->document()->cursor(0,1,2,3);
	ed->setCursor(sel);
	panel->display(1,false);
	widget->cFind->setEditText("el");
	panel->findReplace(false);
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);
	QCEEQUAL(ed->cursor(),ed->document()->cursor(0,1,0,3));
	
	//test if first match is selected if text is searched from above the current scope
	ed->setCursorPosition(0,0);
	panel->findReplace(false);
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);
	QCEEQUAL(ed->cursor(),ed->document()->cursor(0,1,0,3));

	//test if last match is selected if text is searched from below the current scope
	ed->setCursorPosition(3,3);
	panel->findReplace(true);
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);
	QCEEQUAL(ed->cursor(),ed->document()->cursor(2,3,2,1));

	//test if last match is found in newly selected text
	panel->display(0,false);
	sel=ed->document()->cursor(0,1,1,3);
	ed->setCursor(sel);
	panel->display(1,false);
	widget->cFind->setEditText("el");
	panel->findReplace(true);
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);
	QCEEQUAL(ed->cursor(),ed->document()->cursor(1,3,1,1));
}


//test if the panel use the correct highlighting of the current selection 
void QSearchReplacePanelTest::selectionHighlighting(){
	ed->setText("hallo welt\nhello world\nsalve mundus\nbounjoure ???\n", false);
	panel->display(1, false);
	widget->cbSelection->setChecked(true);
	QDocumentCursor sel=ed->document()->cursor(0,7,2,10);

//test if nothing is highlighted if the panel is hidden
	ed->setCursor(sel);
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel); //should now highlighted
	panel->display(0, false);
	QCEEQUAL2(getHighlightedSelection(ed),QDocumentCursor(), "highlight not removed"); //highlighting should be removed

//test if cursor changes with invisible panel modify are (correctly not) highlighted
	ed->setCursor(sel);
	QCEEQUAL2(getHighlightedSelection(ed),QDocumentCursor(), "sel. highlighting was wrongly restored");
	ed->setCursor(ed->document()->cursor(1,3,1,8));
	QCEEQUAL2(getHighlightedSelection(ed),QDocumentCursor(), "sel. highlighting was wrongly restored");

//test how selection reacts to document modifications
	panel->display(1, false);
    widget->cbSelection->setChecked(true); // was deactivated automatically because of previous single line selection
	sel=ed->document()->cursor(0,5,2,10);	
	ed->setCursor(sel);
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);

	//modify mid line of selection
	QDocumentCursor c=ed->document()->cursor(1,10);
	c.deletePreviousChar();
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);
	c.insertText("m");
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);
	c.movePosition(1, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
	c.insertText(" doomination!!!! panically!");
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);
	
	//modify last line, after selection
	c=ed->document()->cursor(2,11);
	c.insertText("holla!holla!holla!");
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);
	
	//modify first line, before selection, keeping length
	c=ed->document()->cursor(0,1);
	c.deletePreviousChar();
	c.insertText("e");
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);

	//modify first line, in selection, changing text, but not selection
	c=ed->document()->cursor(0,7);
	c.deletePreviousChar();
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);
	c.insertText("okay!dokay!decay!");
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), sel);
	
	//modify last line, in selection
	c=ed->document()->cursor(2,1);
	c.insertText("holla!");
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), ed->document()->cursor(0,5,2,16));
	c.deletePreviousChar();
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), ed->document()->cursor(0,5,2,15));

	//modify first line, before selection
	c=ed->document()->cursor(0,1);
	c.insertText("holland!");
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), ed->document()->cursor(0,13,2,15));
	c.deletePreviousChar();
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), ed->document()->cursor(0,12,2,15));
	
	//removing line in selection
	c=ed->document()->cursor(1,1);
	c.eraseLine();
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), ed->document()->cursor(0,12,1,15));
	
	//adding new lines
	c=ed->document()->cursor(0,15);
	c.insertText("abc\ndef\n");
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), ed->document()->cursor(0,12,3,15));
	c=ed->document()->cursor(0,5);
	c.insertText("abc\ndef\n");
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), ed->document()->cursor(2,7,5,15));

	//removing lines
	c=ed->document()->cursor(0,5);
	c.eraseLine();
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), ed->document()->cursor(1,7,4,15));
	c.eraseLine();
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), ed->document()->cursor(0,7,3,15));
	c.eraseLine();
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), ed->document()->cursor(0,0,2,15));
	c.eraseLine();
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), ed->document()->cursor(0,0,1,15));
	c.eraseLine();
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), ed->document()->cursor(0,0,0,15));
	c.eraseLine();
	QCEMULTIEQUAL(getHighlightedSelection(ed),panel->getSearchScope(), QDocumentCursor());
}
void QSearchReplacePanelTest::cleanupTestCase(){
	widget->cbSelection->setChecked(false); //this gets annoying later
}
#endif

