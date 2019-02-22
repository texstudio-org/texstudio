
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "qdocumentsearch_t.h"
#include "qdocumentsearch.h"
#include "qdocumentline.h"
#include "qeditor.h"
#include "testutil.h"
#include <QtTest/QtTest>
QDocumentSearchTest::QDocumentSearchTest(QEditor* editor, bool all): QObject(nullptr), ds(nullptr), ed(editor), all(all){
	ed->setFlag(QEditor::HardLineWrap, false);
}
void QDocumentSearchTest::initTestCase(){
    ds=new QDocumentSearch(ed,"",nullptr);
	ed->document()->setLineEnding(QDocument::Unix); //necessary to compare with "\n" separated lines
}
//cursor movement
class CM{
public:
    CM(): dir(false),rep(false),l(-1),ax(-1),cx(-1){}
	CM(bool adir, int line, int anchorOffset, int cursorOffset,const QString &replaceText,const QString& newText):
		dir(adir),rep(replaceText!="\1"),l(line),ax(anchorOffset),cx(cursorOffset),rt(replaceText),nt(newText){
	}
	bool dir, rep;
	int l,ax,cx;
	QString rt, nt;
};
//search previous
CM SP(int line, int anchorOffset, int cursorOffset,const QString &replaceText="\1",const QString &newText=""){
	return CM(true,line,anchorOffset,cursorOffset,replaceText,newText);
}
CM SN(int line, int anchorOffset, int cursorOffset,const QString &replaceText="\1",const QString& newText=""){
	return CM(false,line,anchorOffset,cursorOffset,replaceText,newText);
}
	
Q_DECLARE_METATYPE(CM);
Q_DECLARE_METATYPE(QList<CM>);


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
			<< SN(0,7,9) << SP(0, 5, 3) << SN(0, 7, 9) 
			<< SN(1, 6, 8) << SN (3, 0, 2) << SN(0, 0,2));
	if (!all) {
		qDebug("skipped tests");
		return;
	}
	QTest::newRow("forward-backward-case sensitive")
		<< "aaAaaAaaA\naAaAa\naaaaaaaa" 
		<< "aa" << (int)QDocumentSearch::CaseSensitive
		<< 0 << 2
		<< (QList<CM>() 
			<< SN(0, 3, 5) << SN(0, 6, 8) << SN(2, 0, 2) << SP(0, 8, 6)
			<< SN(2, 0, 2) << SN(2, 2, 4) << SN(2, 4, 6) << SN(2, 6, 8) 
			<< SP(2, 6, 4) << SP(2, 4, 2) << SP(2, 2, 0) << SP(0, 8, 6) 
			<< SP(0, 5, 3) << SP(0, 2, 0) << SP(2, 8, 6));
	QTest::newRow("forward-backward-case whole words")
		<< "aaAaaAaaA\naA aAa\naaa aa aaa\n" 
		<< "aA" << (int)QDocumentSearch::WholeWords
		<< 0 << 0
		<< (QList<CM>() 
			<< SN(1, 0, 2) << SN(2, 4, 6) << SP(1, 2, 0) << SN (2, 4, 6) << SN(1,0,2));
	QTest::newRow("forward-backward-case whole words case sensitive ")
		<< "aa Aaa Aaa A\naA aAa\naa  aA aa a\n" 
		<< "aA" << (int)(QDocumentSearch::WholeWords | QDocumentSearch::CaseSensitive)
		<< 0 << 0
		<< (QList<CM>() 
			<< SN(1, 0, 2) << SN(2, 4, 6) << SP(1, 2, 0) << SN (2, 4, 6) << SN(1,0,2));
	QTest::newRow("forward reg exp")
		<< "Hello42World" 
		<< "[0-9]+" << (int)QDocumentSearch::RegExp
		<< 0 << 0
		<< (QList<CM>() 
			<< SN(0, 5, 7) << SN(0,5,7));
	QTest::newRow("reg exp with 0 match")
		<< "Hello423World" 
		<< "[0-9]*" << (int)QDocumentSearch::RegExp
		<< 0 << 0
		<< (QList<CM>() 
			<< SN(0, 5, 8) << SN(0, 5, 8) << SN(0, 5, 8) << SN(0, 5, 8) );
	QTest::newRow("replace forward")
		<< "Hello42World17XXXX2358YYY" 
		<< "[0-9]+" << (int)QDocumentSearch::RegExp
		<< 0 << 0
		<< (QList<CM>() 
			<< SN(0, 5, 7) 
			<< SN(0, 15, 17, "mouse","HellomouseWorld17XXXX2358YYY") 
			<< SN(0, 24, 28, "mouse","HellomouseWorldmouseXXXX2358YYY") 
			<< SN(-1, -1, -1, "house!","HellomouseWorldmouseXXXXhouse!YYY"));
	QTest::newRow("replace forward-backward")
		<< "aa aa aa\naa aaa XXXX aa\naa YYYY aa aa YYYY" 
		<< "aa" << (int)QDocumentSearch::WholeWords
		<< 2 << 0
		<< (QList<CM>() 
			<< SN(2, 0, 2, "***","aa aa aa\naa aaa XXXX aa\naa YYYY aa aa YYYY") 
			<< SN(2, 9, 11, "***","aa aa aa\naa aaa XXXX aa\n*** YYYY aa aa YYYY") 
			<< SN(3, 2, 4, "\n!","aa aa aa\naa aaa XXXX aa\n*** YYYY \n! aa YYYY") 
			<< SP(1, 14, 12, "ups", "aa aa aa\naa aaa XXXX aa\n*** YYYY \n! ups YYYY") 
			<< SP(1, 2, 0, "first","aa aa aa\naa aaa XXXX first\n*** YYYY \n! ups YYYY") 
			<< SP(0, 8, 6, "sec","aa aa aa\nsec aaa XXXX first\n*** YYYY \n! ups YYYY") 
			<< SP(0, 5, 3, "\xE4","aa aa \xE4\nsec aaa XXXX first\n*** YYYY \n! ups YYYY") 
			<< SP(0, 2, 0, "miau","aa miau \xE4\nsec aaa XXXX first\n*** YYYY \n! ups YYYY") 
			<< SP(-1, -1, -1, "^^^^","^^^^ miau \xE4\nsec aaa XXXX first\n*** YYYY \n! ups YYYY") );
			//<< SP(1, 0, 0, "first","aa aa \nfirst aaa XXXX ups\n*** YYYY \n! aa YYYY") 
			//<< SN(3, 2, 2, "","^^^^ \xE4 \nfirst aaa XXXX ups\n*** YYYY \n!  YYYY") 
			//<< SP(-1,-1,-1));
	QTest::newRow("replace regexp backreferences")
		<< "\\begin{abc} \n content \n ... \n \\end{abc}"
		<< "\\\\(begin|end)\\{([a-zA-Z]*)\\}" << (int)QDocumentSearch::RegExp
		<< 0 << 0
		<< (QList<CM>() 
			<< SN(0, 0, 11, "\\\\1{left-\\2-right}","\\begin{abc} \n content \n ... \n \\end{abc}") 
			<< SN(3, 1, 10, "\\\\1{left-\\2-right}","\\begin{left-abc-right} \n content \n ... \n \\end{abc}") 
			<< SN(-1, -1, -1, "\\\\1{left-\\2-right}","\\begin{left-abc-right} \n content \n ... \n \\end{left-abc-right}")); 
	QTest::newRow("replace escape seq")
		<< "hello world! hello!"
		<< "l" << (int)QDocumentSearch::EscapeSeq
		<< 0 << 0
		<< (QList<CM>() 
			<< SN(0, 2, 3, "????", "hello world! hello!") 
			<< SN(1, 0, 1, "\\n","he\nlo world! hello!") 
			<< SN(1, 6, 7, "\\\\","he\n\\o world! hello!") 
			<< SN(1, 12, 13, "\\t","he\n\\o wor\td! hello!") 
			<< SN(2, 0, 1, "\\r","he\n\\o wor\td! he\nlo!")) ;
//			<< SN(-1, -1, -1, "\\0",QString("he\n\\o wor\td! he\n*o!").replace(QChar('*'),QChar('\0')))); 
	QTest::newRow("touching block replace")
		<< "xxxxxxxxxxxx"
		<< "xx" << 0
		<< 0 << 4
		<< (QList<CM>() 
			 << SN(0, 4,6, "abc",  "xxxxxxxxxxxx")
			 << SN(0, 6,8, "**",   "xxxx**xxxxxx")
			 << SN(0, 8,10, "!!",  "xxxx**!!xxxx")
			 << SN(0, 10,12, "==", "xxxx**!!==xx")
			 << SN(0, 0,2, "--",   "xxxx**!!==--")
			 << SN(0, 4,6, "++++", "++++xx**!!==--")
			 << SN(-1, -1,-1, "//", "++++//**!!==--") );
	QTest::newRow("loop around replace")
		<< "aaaaaa\nggaagg\nbbaabb\n"
		<< "aa" << 0
		<< 1 << 0
		<< (QList<CM>() 
			 << SN(1, 2,4, "**", "aaaaaa\nggaagg\nbbaabb\n")
			 << SN(2, 2,4, "xy", "aaaaaa\nggxygg\nbbaabb\n")
			 << SN(0, 0,2, "tz", "aaaaaa\nggxygg\nbbtzbb\n")
			 << SN(0, 2,4, "12", "12aaaa\nggxygg\nbbtzbb\n")
			 << SN(0, 4,6, "34", "1234aa\nggxygg\nbbtzbb\n")
			 << SN(-1, -1,-1, "56", "123456\nggxygg\nbbtzbb\n"));
	QTest::newRow("loop around backward replace")
		<< "aaaaaa\nggaagg\nbbaabb\n"
		<< "aa" << 0
		<< 1 << 4
		<< (QList<CM>() 
			<< SP(1, 4, 2, "tsara", "aaaaaa\nggaagg\nbbaabb\n")
			<< SP(0, 6, 4, "---", "aaaaaa\ngg---gg\nbbaabb\n")
			<< SP(0, 4, 2, "!!!!", "aaaa!!!!\ngg---gg\nbbaabb\n")
			<< SP(0, 2, 0, ">>", "aa>>!!!!\ngg---gg\nbbaabb\n")
			<< SP(2, 4, 2, "<<", "<<>>!!!!\ngg---gg\nbbaabb\n")
			<< SP(-1, -1, -1, "%", "<<>>!!!!\ngg---gg\nbb%bb\n"));
	
	QTest::newRow("replacing leading to new find occurences")
		<< "abc\nabc\nabc"
		<< "abc" << 0
		<< 0 << 0
		<< (QList<CM>() 
			<< SN(0,0,3) << SN(1,0,3) 
			<< SN(2, 0,3, "abc abc", "abc\nabc abc\nabc")
			<< SN(0,0,3) << SN(1,0,3) << SN(1, 4, 7) << SN(2,0,3) 
			<< SP(1,7,4) << SP(1,3,0) << SP(0,3,0)
			<< SN(1, 0,3, "abc+++abc", "abc+++abc\nabc abc\nabc")
			<< SN(1, 4,7) << SP (1,3,0) << SP(0,9,6) << SP(0,3,0) << SP(2,3,0));

	QTest::newRow("replacing leading to new find occurences empty lines")
		<< "abc\n\n\nabc\n\n\nabc"
		<< "abc" << 0
		<< 0 << 0
		<< (QList<CM>() 
			<< SN(0,0,3) << SN(3,0,3) 
			<< SN(6, 0,3, "abc abc", "abc\n\n\nabc abc\n\n\nabc")
			<< SN(0,0,3) << SN(3,0,3) << SN(3, 4, 7) << SN(6,0,3) 
			<< SP(3,7,4) << SP(3,3,0) << SP(0,3,0)
			<< SN(3, 0,3, "abc+++abc", "abc+++abc\n\n\nabc abc\n\n\nabc")
			<< SN(3, 4,7) << SP (3,3,0) << SP(0,9,6) << SP(0,3,0) << SP(6,3,0));
}
void QDocumentSearchTest::next_sameText(){
	QFETCH(QString, editorText);
	QFETCH(QString, searchText);
	QFETCH(int, options);
	options |= QDocumentSearch::Silent ;
	
	QFETCH(int, sy);
	QFETCH(int, sx);
	
	QFETCH(QList<CM>, cms);
	
	QDocumentSearch* ds=this->ds;
	
	for (int loop=0; loop<4; loop++){
		//QWARN(qPrintable(QString("%1").arg(loop)));
		ed->setText(editorText, false);
		if (loop<2) {
			ds->setSearchText(searchText);
			if (loop) 
				options|=QDocumentSearch::HighlightAll; //highlighting shouldn't change anything
			ds->setOptions((QDocumentSearch::Options)options);
		} else if (loop==2)//creating a new search shouldn't change anything
			ds=new QDocumentSearch(ed,searchText,(QDocumentSearch::Options)options); 
		else
			ds=new QDocumentSearch(ed,searchText,(QDocumentSearch::Options)options|QDocumentSearch::HighlightAll); 
		ds->setCursor(ed->document()->cursor(sy,sx));
		for (int i=0;i< cms.size();i++){
			QString sel;
			if (cms[i].l>=0) {
				if (cms[i].rep) {
					QStringList temp=cms[i].nt.split("\n");
					QVERIFY(temp.size()>cms[i].l);
					sel=temp[cms[i].l];
				} else sel=ed->document()->line(cms[i].l).text();
				if (cms[i].ax<cms[i].cx) sel = sel.mid(cms[i].ax,cms[i].cx-cms[i].ax);
				else sel =sel.mid(cms[i].cx,cms[i].ax-cms[i].cx);
			}
			if (!cms[i].rep)
				ds->setOptions((QDocumentSearch::Options)options & (~QDocumentSearch::Replace));
			else {
				ds->setOptions((QDocumentSearch::Options)options | QDocumentSearch::Replace);
				ds->setReplaceText(cms[i].rt);
			}
			int foundCount = ds->next(cms[i].dir,false,cms[i].rep);
			QByteArray emba=QString("%1: %2 %3 %4  \"%5\" \"%6\" expected %7 %8 %9 %10 %11  %12").arg(i).arg(ds->cursor().lineNumber()).arg(ds->cursor().anchorColumnNumber()).arg(ds->cursor().columnNumber()).arg(ds->cursor().selectedText()).arg(ed->document()->text()).arg(cms[i].l).arg(cms[i].ax).arg(cms[i].cx).arg(sel).arg(cms[i].nt).arg(loop?"(highlight-run)":"").toLatin1();//make sure the message stays in memory for the next few lines
			const char* errorMessage=emba.constData();
			QVERIFY2(ds->cursor().selectedText()== sel,errorMessage);
			QVERIFY2(ds->cursor().lineNumber()== cms[i].l,errorMessage);
			QVERIFY2(ds->cursor().columnNumber()== cms[i].cx,errorMessage);
			QVERIFY2(ds->cursor().anchorLineNumber()== cms[i].l,errorMessage);
			QVERIFY2(ds->cursor().anchorColumnNumber()== cms[i].ax,errorMessage);
			if (cms[i].rep){
				QVERIFY2(ed->document()->text()== cms[i].nt,errorMessage);
			}
			if (cms[i].l==-1) QEQUAL(foundCount, 0);
			else QEQUAL(foundCount, 1);
			/*if (options & QDocumentSearch::Replace)
				QVERIFY(ed->document()->text()== newText[i]);*/
		}
		if (loop>=2) delete ds;
	}

}
void QDocumentSearchTest::replaceAll_data(){
	QTest::addColumn<QString >("editorText");
	QTest::addColumn<QString >("searchText");
	QTest::addColumn<QString >("replaceText");
	QTest::addColumn<int>("options");
	QTest::addColumn<bool>("dir");
	QTest::addColumn<bool>("wrapAround");
	QTest::addColumn<int>("scopey");
	QTest::addColumn<int >("scopex");
	QTest::addColumn<int>("scopey2");
	QTest::addColumn<int>("scopex2");
	QTest::addColumn<int>("sy");
	QTest::addColumn<int>("sx");
	QTest::addColumn<QString >("newtext");
	QTest::addColumn<int>("foundCount");
	
	QTest::newRow("simple")
		<< "hell!\nes ist hell, die Sonne scheint\nHello World\nHello!!!\nhell!"
		<< "hell"
		<< "Heaven"
		<< 0 << false << true
		<< 1 << 7
		<< 3 << 4
		<< 0 << 0
		<< "hell!\nes ist Heaven, die Sonne scheint\nHeaveno World\nHeaveno!!!\nhell!"
		<< 3;
	QTest::newRow("simple backward")
		<< "hell!\nes ist hell, die Sonne scheint\nHello World\nxxHello!!!\nhell!"
		<< "hell"
		<< "Heaven"
		<< 0 << true << true
		<< 1 << 7
		<< 3 << 6
		<< 99 << 99
		<< "hell!\nes ist Heaven, die Sonne scheint\nHeaveno World\nxxHeaveno!!!\nhell!"
		<< 3;
	QTest::newRow("whole words backward")
		<< "abc abc \nabc abc abc \nabc abcabcabcabc \nabc\nabc abc abc\nabc"
		<< "abc"
		<< "uvxyz"
		<< (int)QDocumentSearch::WholeWords << true << false
		<< 0 << 5
		<< 5 << 3
		<< 5 << 0
		<< "abc abc \nuvxyz uvxyz uvxyz \nuvxyz abcabcabcabc \nuvxyz\nuvxyz uvxyz uvxyz\nabc"
		<< 8;
	QTest::newRow("whole words backward")
		<< "abc abc \nabc abc abc \nabc abcabcabcabc \nabc\nabc abc abc\nabc"
		<< "abc"
		<< "uvxyz"
		<< (int)QDocumentSearch::WholeWords << true << true
		<< 0 << 5
		<< 5 << 3
		<< 5 << 0
		<< "abc abc \nuvxyz uvxyz uvxyz \nuvxyz abcabcabcabc \nuvxyz\nuvxyz uvxyz uvxyz\nuvxyz"
		<< 9;
	QTest::newRow("whole words backward")
		<< "abc abc \nabc abc abc \nabc abcabcabcabc \nabc\nabc abc abc\nabc"
		<< "abc"
		<< "uvxyz"
		<< (int)QDocumentSearch::WholeWords << true << true
		<< 0 << 5
		<< 5 << 0
		<< 5 << 0
		<< "abc abc \nuvxyz uvxyz uvxyz \nuvxyz abcabcabcabc \nuvxyz\nuvxyz uvxyz uvxyz\nabc"
		<< 8;

	QTest::newRow("replaces leading to new search result")
		<< "abc abc abc"
		<< "a"
		<< "aj"
		<< 0 << false << true
		<< -1 << -1
		<< -1 << -1
		<< 0 << 0
		<< "ajbc ajbc ajbc"
		<< 3;
		
	QTest::newRow("replaces leading to new search result ending with o")
		<< "abc abc abc"
		<< "a"
		<< "ao"
		<< 0 << false << true
		<< -1 << -1
		<< -1 << -1
		<< 0 << 0
		<< "aobc aobc aobc"
		<< 3;
		
	QTest::newRow("replaces leading to new search result ending with o backward, in scope")
		<< "abc abc abc"
		<< "a"
		<< "ao"
		<< 0 << true << true
		<< 0 << 0
		<< 0 << 8
		<< 0 << 8
		<< "aobc aobc abc"
		<< 2;

	QTest::newRow("replaces leading to new search result ending with o backward, after scope")
		<< "abc abc abc"
		<< "a"
		<< "ao"
		<< 0 << true << true
		<< 0 << 0
		<< 0 << 5
		<< 0 << 8
		<< "aobc aobc abc"
		<< 2;

	QTest::newRow("replaces leading to new search result ending with o backward wrap around")
		<< "abc abc abc"
		<< "a"
		<< "ao"
		<< 0 << true << true
		<< -1 << -1
		<< -1 << -1
		<< 0 << 8
		<< "aobc aobc aobc"
		<< 3;

	QTest::newRow("replaces all matching regexp")
		<< "abc a12b34c abc"
		<< "[0-9]*"
		<< "x"
		<< (int)QDocumentSearch::RegExp << false << true
		<< -1 << -1
		<< -1 << -1
		<< 0 << 0
		<< "abc axbxc abc"
		<< 2;

	QTest::newRow("replaces all matching regexp backward") //correct? no greedy replace with backward search
		<< "abc a12b34c abc"
		<< "[0-9]*"
		<< "!"
		<< (int)QDocumentSearch::RegExp << true << true
		<< -1 << -1
		<< -1 << -1
		<< 0 << 8
		<< "abc a12b34c abc"
		<< 0;
	QTest::newRow("replaces number matching regexp backward, in scope")
		<< "abc a12b34c abc"
		<< "[0-9]+"
		<< "!"
		<< (int)QDocumentSearch::RegExp << true << true
		<< 0 << 0
		<< 0 << 8
		<< 0 << 8
		<< "abc a!!b34c abc"
		<< 2;
	QTest::newRow("replaces number matching regexp backward, out scope")
		<< "abc a12b34c abc"
		<< "[0-9]+"
		<< "!"
		<< (int)QDocumentSearch::RegExp << true << true
		<< 0 << 0
		<< 0 << 8
		<< 0 << 16
		<< "abc a!!b34c abc"
		<< 2;
	QTest::newRow("replaces number matching regexp backward, all/wrap around")
		<< "abc a12b34c abc"
		<< "[0-9]+"
		<< "!"
		<< (int)QDocumentSearch::RegExp << true << true
		<< -1 << -1
		<< -1 << -1
		<< 0 << 8
		<< "abc a!!b!!c abc"
		<< 4;

	QTest::newRow("replaces all wrap around")
		<< "abc\nabc\nabc\nabc"
		<< "abc"
		<< "abcabc"
		<< 0 << false << true
		<< -1 << -1
		<< -1 << -1
		<< 1 << 0
		<< "abcabc\nabcabc\nabcabc\nabcabc"
		<< 4;
	QTest::newRow("replaces all, no wrap around")
		<< "abc\nabc\nabc\nabc"
		<< "abc"
		<< "abcabc"
		<< 0 << false << false
		<< -1 << -1
		<< -1 << -1
		<< 1 << 0
		<< "abc\nabcabc\nabcabc\nabcabc"
		<< 3;
	QTest::newRow("replaces all 2, wrap around")
		<< "abc\nabc\nabc\nabc"
		<< "abc"
		<< "abcabc"
		<< 0 << false << true
		<< -1 << -1
		<< -1 << -1
		<< 1 << 1
		<< "abcabc\nabcabc\nabcabc\nabcabc"
		<< 4;
	QTest::newRow("replaces all 2, no wrap around")
		<< "abc\nabc\nabc\nabc"
		<< "abc"
		<< "abcabc"
		<< 0 << false << false
		<< -1 << -1
		<< -1 << -1
		<< 1 << 1
		<< "abc\nabc\nabcabc\nabcabc"
		<< 2;
}
void QDocumentSearchTest::replaceAll(){
	QFETCH(QString, editorText);
	QFETCH(QString, searchText);
	QFETCH(QString, replaceText);
	QFETCH(int, options);
	options |= QDocumentSearch::Silent ;
	options |= QDocumentSearch::Replace;
	QFETCH(bool, dir);
	QFETCH(bool, wrapAround);

	QFETCH(int, scopey);
	QFETCH(int, scopex);
	QFETCH(int, scopey2);
	QFETCH(int, scopex2);
	QFETCH(int, sy);
	QFETCH(int, sx);
	
	QFETCH(QString, newtext);
	QFETCH(int, foundCount);

	for (int loop=0; loop<2; loop++){
		ed->setText(editorText, false);
		ds->setSearchText(searchText);
		ds->setReplaceText(replaceText);
		if (loop) 
			options|=QDocumentSearch::HighlightAll; //highlighting shouldn't change anything
		ds->setOptions((QDocumentSearch::Options)options);
		ds->setCursor(ed->document()->cursor(sy,sx));
		ds->setScope(ed->document()->cursor(scopey,scopex,scopey2,scopex2));
		int count=ds->next(dir, true, false, wrapAround);
		QVERIFY2(ed->document()->text()== newtext,qPrintable(QString("%1 != %2 loop: %3, dir: %4").arg(ed->document()->text()).arg(newtext).arg(loop).arg(dir)));
		QEQUAL(count, foundCount);
	}
}
void QDocumentSearchTest::searchAndFolding_data(){
	QTest::addColumn<QString>("editorText");
	QTest::addColumn<QList<int> >("foldAt");
	QTest::addColumn<QList<int> >("hiddenLines");
	QTest::addColumn<int>("searchFrom");
	QTest::addColumn<QString>("searchText");
	QTest::addColumn<int>("options");
	QTest::addColumn<CM>("movement");
	QTest::addColumn<QList<int> >("hiddenLinesAfterwards");
	QTest::newRow("before fold")
			<< "0\nabc\n{\nabc\n}\n"
			<< (QList<int>() << 2)
			<< (QList<int>() << 3 << 4)
			<< 0
			<< "abc"
			<< 0
			<< SN(1,0,3)
			<< (QList<int>() << 3 << 4);
	QTest::newRow("simple fold")
			<< "0\nabc\n{\nabc\n}\n"
			<< (QList<int>() << 2)
			<< (QList<int>() << 3 << 4)
			<< 2
			<< "abc"
			<< 0
			<< SN(3,0,3)
			<< (QList<int>());
	QTest::newRow("after fold")
			<< "0\n1abc\n2{\n3abc\n4}\n5\n6abc"
			<< (QList<int>() << 2)
			<< (QList<int>() << 3 << 4)
			<< 4
			<< "abc"
			<< 0
			<< SN(6,1,4)
			<< (QList<int>() << 3 << 4);
	QTest::newRow("double fold")
			<< "0\n{\n{\nabc\n}\n}"
			<< (QList<int>() << 1 << 2)
			<< (QList<int>() << 2 << 3 << 4 << 5)
			<< 0
			<< "abc"
			<< 0
			<< SN(3,0,3)
			<< (QList<int>());
	QTest::newRow("silent double fold") //don't unfold if silent
			<< "0\n{\n{\nabc\n}\n}"
			<< (QList<int>() << 1 << 2)
			<< (QList<int>() << 2 << 3 << 4 << 5)
			<< 0
			<< "abc"
			<< (int)QDocumentSearch::Silent
			<< SN(3,0,3)
			<< (QList<int>() << 2 << 3 << 4 << 5);
	QTest::newRow("triple fold, only outer")
			<< "0\n1{\n2{\n3abx\n4}\n5{abc\n6}\n}"
			<< (QList<int>() << 1 << 2 << 5)
			<< (QList<int>() << 2 << 3 << 4 << 5 << 6 << 7)
			<< 0
			<< "abc"
			<< 0
			<< SN(5,2,5)
			<< (QList<int>() << 3 << 4 << 6);
	QTest::newRow("triple fold, keep first")
			<< "0\n1{\n2{\n3abx\n4}\n5{\nabc\n7}\n}"
			<< (QList<int>() << 1 << 2 << 5)
			<< (QList<int>() << 2 << 3 << 4 << 5 << 6 << 7 << 8)
			<< 0
			<< "abc"
			<< 0
			<< SN(6,0,3)
			<< (QList<int>() << 3 << 4);

	//backward
	QTest::newRow("simple fold (backward)")
			<< "0\nabc\n{\nabc\n}\n"
			<< (QList<int>() << 2)
			<< (QList<int>() << 3 << 4)
			<< 4
			<< "abc"
			<< 0
			<< SP(3,3,0)
			<< (QList<int>());
	QTest::newRow("double fold (backward)")
			<< "0\n{\n{\nabc\n}\n}"
			<< (QList<int>() << 1 << 2)
			<< (QList<int>() << 2 << 3 << 4 << 5)
			<< 5
			<< "abc"
			<< 0
			<< SP(3,3,0)
			<< (QList<int>());
	QTest::newRow("silent double fold (backward)") //don't unfold if silent
			<< "0\n{\n{\nabc\n}\n}"
			<< (QList<int>() << 1 << 2)
			<< (QList<int>() << 2 << 3 << 4 << 5)
			<< 6
			<< "abc"
			<< (int)QDocumentSearch::Silent
			<< SP(3,3,0)
			<< (QList<int>() << 2 << 3 << 4 << 5);
	QTest::newRow("triple fold, only outer (backward)")
			<< "0\n1{\n2{\n3abx\n4}\n5{abc\n6}\n}"
			<< (QList<int>() << 1 << 2 << 5)
			<< (QList<int>() << 2 << 3 << 4 << 5 << 6 << 7)
			<< 8
			<< "abc"
			<< 0
			<< SP(5,5,2)
			<< (QList<int>() << 3 << 4 << 6);
	QTest::newRow("triple fold, keep first (backward)")
			<< "0\n1{\n2{\n3abx\n4}\n5{\nabc\n7}\n}"
			<< (QList<int>() << 1 << 2 << 5)
			<< (QList<int>() << 2 << 3 << 4 << 5 << 6 << 7 << 8)
			<< 9
			<< "abc"
			<< 0
			<< SP(6,3,0)
			<< (QList<int>() << 3 << 4);

}

void QDocumentSearchTest::searchAndFolding(){
	QFETCH(QString, editorText);
	QFETCH(QList<int>, foldAt);
	QFETCH(QList<int>, hiddenLines);
	QFETCH(int, searchFrom);
	QFETCH(QString, searchText);
	QFETCH(int, options);
	QFETCH(CM, movement);
	QFETCH(QList<int>, hiddenLinesAfterwards);
	for (int loop=0;loop<2;loop++){
		ed->setText(editorText, false);
		foreach (const int i, foldAt)
			ed->document()->collapse(i);
		for (int i=0;i<ed->document()->lines();i++)
			QVERIFY(ed->document()->line(i).isHidden()==hiddenLines.contains(i));
		ds->setCursor(ed->document()->cursor(searchFrom));
		ds->setOptions((QDocumentSearch::Options)(options|(loop?QDocumentSearch::HighlightAll:0))); //highlighting shouldn't change anything
		ds->setSearchText(searchText);
		int foundCount=ds->next(movement.dir);

		QEQUAL(ds->cursor().lineNumber(),movement.l);
		QEQUAL(ds->cursor().columnNumber(),movement.cx);
		QEQUAL(ds->cursor().anchorColumnNumber(),movement.ax);
		for (int i=0;i<ed->document()->lines();i++)
			QVERIFY2(ed->document()->line(i).isHidden()==hiddenLinesAfterwards.contains(i),qPrintable(QString::number(i)));
		QEQUAL(foundCount, 1);
	}
}

void QDocumentSearchTest::cleanupTestCase(){
	delete ds;
}
#endif

