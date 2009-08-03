
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
	ed->document()->setLineEnding(QDocument::Unix); //necessary to compare with "\n" separated lines
}
//cursor movement
class CM{
public:
	CM(): l(-1){}
	CM(bool adir, int line, int anchorOffset, int cursorOffset,const QString &replaceText,const QString& newText):
		dir(adir),rep(replaceText!="\1"),l(line),ax(anchorOffset),cx(cursorOffset),rt(replaceText),nt(newText){
		if (!nt.endsWith("\n")) nt.append("\n");
	}
	bool dir, rep;
	int l,ax,cx;
	QString rt, nt;
};
class SP:public CM{//search previous
public:	
	SP(int line, int anchorOffset, int cursorOffset,const QString &replaceText="\1",const QString 
&newText=""):
		CM(true,line,anchorOffset,cursorOffset,replaceText,newText){}
};
class SN:public CM{//search next
public:
	SN(int line, int anchorOffset, int cursorOffset,const QString &replaceText="\1",const QString& newText=""):
		CM(false,line,anchorOffset,cursorOffset,replaceText,newText){}
};
	
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
			<< SN(2, 0, 1, "\\r","he\n\\o wor\td! he\nlo!") 
			<< SN(-1, -1, -1, "\\0",QString("he\n\\o wor\td! he\n*o!").replace(QChar('*'),QChar('\0')))); 
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
	
}
void QDocumentSearchTest::next_sameText(){
	QFETCH(QString, editorText);
	QFETCH(QString, searchText);
	QFETCH(int, options);
	options |= QDocumentSearch::Silent ;
	
	QFETCH(int, sy);
	QFETCH(int, sx);
	
	QFETCH(QList<CM>, cms);
	
	
	for (int loop=0; loop<2; loop++){
		ed->document()->setText(editorText);
		ds->setSearchText(searchText);
		if (loop) 
			options|=QDocumentSearch::HighlightAll; //highlighting shouldn't change anything
		ds->setOptions((QDocumentSearch::Options)options);
		ds->setOrigin(ed->document()->cursor(sy,sx));
		
		for (int i=0;i< cms.size();i++){
			QString sel;
			if (cms[i].l>=0) {
				if (cms[i].rep) sel=cms[i].nt.split("\n")[cms[i].l];
				else sel=ed->document()->line(cms[i].l).text();
				if (cms[i].ax<cms[i].cx) sel = sel.mid(cms[i].ax,cms[i].cx-cms[i].ax);
				else sel =sel.mid(cms[i].cx,cms[i].ax-cms[i].cx);
			}
			if (!cms[i].rep)
				ds->setOptions((QDocumentSearch::Options)options & (~QDocumentSearch::Replace));
			else {
				ds->setOptions((QDocumentSearch::Options)options | QDocumentSearch::Replace);
				ds->setReplaceText(cms[i].rt);
			}
			ds->next(cms[i].dir,false,cms[i].rep);
			const char* errorMessage=QString("%1: %2 %3 %4  \"%5\" \"%6\" expected %7 %8 %9 %10 %11  %12").arg(i).arg(ds->cursor().lineNumber()).arg(ds->cursor().anchorColumnNumber()).arg(ds->cursor().columnNumber()).arg(ds->cursor().selectedText()).arg(ed->document()->text()).arg(cms[i].l).arg(cms[i].ax).arg(cms[i].cx).arg(sel).arg(cms[i].nt).arg(loop?"(highlight-run)":"").toLatin1().constData();
			QVERIFY2(ds->cursor().selectedText()== sel,errorMessage);
			QVERIFY2(ds->cursor().lineNumber()== cms[i].l,errorMessage);
			QVERIFY2(ds->cursor().columnNumber()== cms[i].cx,errorMessage);
			QVERIFY2(ds->cursor().anchorLineNumber()== cms[i].l,errorMessage);
			QVERIFY2(ds->cursor().anchorColumnNumber()== cms[i].ax,errorMessage);
			if (cms[i].rep){
				QVERIFY2(ed->document()->text()== cms[i].nt,errorMessage);
			}
			/*if (options & QDocumentSearch::Replace)
				QVERIFY(ed->document()->text()== newText[i]);*/
		}
	}

}
void QDocumentSearchTest::cleanupTestCase(){
	delete ds;
}
#endif

