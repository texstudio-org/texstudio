#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "qdocumentcursor_t.h"
#include "qdocumentcursor.h"
#include "qdocumentcursor_p.h"
#include "qdocument.h"
#include "qdocument_p.h"
#include "qdocumentline.h"
#include "qdocumentline_p.h"
#include "testutil.h"
#include "qcetestutil.h"
#include <QtTest/QtTest>

void QDocumentCursorTest::initTestCase(){
	doc=new QDocument();
	doc->setText("test: line 1\n"
	             "test: line 2, hello world! abcdefghijklmnopqrstuvwxyzABCDE...XYZ\n"
				 "test: line 3\n", false);
	doc->setLineEnding(QDocument::Unix);
}

QDocumentCursor QDocumentCursorTest::str2cur(const QString &s){
	QStringList sl=s.split("|");
	if (sl.size()==2) return doc->cursor(sl[0].toInt(),sl[1].toInt());
	else if (sl.size()==4) return doc->cursor(sl[0].toInt(),sl[1].toInt(),sl[2].toInt(),sl[3].toInt());
	else return QDocumentCursor();

}
void QDocumentCursorTest::constMethods_data(){
	QTest::addColumn<QString>("cursor");
	QTest::addColumn<bool>("atStart");
	QTest::addColumn<bool>("atEnd");
	QTest::addColumn<bool>("atLineStart");
	QTest::addColumn<bool>("atLineEnd");
	QTest::addColumn<int>("position");
	QTest::addColumn<int>("anchorLineNumber");
	QTest::addColumn<int>("anchorColumnNumber");
	QTest::addColumn<int>("lineNumber");
	QTest::addColumn<int>("columnNumber");
	QTest::addColumn<QString>("selectionStart");
	QTest::addColumn<QString>("selectionEnd");
	QTest::addColumn<bool>("hasSelection");
	QTest::addColumn<QString>("selectedText");
	QTest::addColumn<char>("previousChar");
	QTest::addColumn<char>("nextChar");

	//-------------cursor without selection--------------
	QTest::newRow("simple cursor mid in a line")
		<< "1|12"
		<< false << false << false << false
		<< 13+12
		<< 1 << 12 << 1 << 12
		<< "1|12" << "1|12" //TODO: qce documentation says << "" << ""
		<< false << ""
		<< '2' << ',';
	QTest::newRow("simple cursor at line start")
		<< "1|0"
		<< false << false << true << false
		<< 13+0
		<< 1 << 0 << 1 << 0
		<< "1|0" << "1|0" //TODO: qce documentation says << "" << ""
		<< false << ""
		<< '\n' << 't';
	QTest::newRow("simple cursor at line end")
		<< "1|64"
		<< false << false << false << true
		<< 13+64
		<< 1 << 64 << 1 << 64
		<< "1|64" << "1|64" //TODO: qce documentation says << "" << ""
		<< false << ""
		<< 'Z' << '\n';
	QTest::newRow("simple cursor at doc start")
		<< "0|0"
		<< true << false << true << false
		<< 0
		<< 0 << 0 << 0 << 0
		<< "0|0" << "0|0" //TODO: qce documentation says << "" << ""
		<< false << ""
		<< '\0' << 't';
	QTest::newRow("simple cursor at doc end")  //TODO: check if this is right
		<< "3|0"
		<< false << true << true << true
		<< 13+65+13
		<< 3 << 0 << 3 << 0
		<< "3|0" << "3|0" //TODO: qce documentation says << "" << ""
		<< false << ""
		<< '\n' << '\0';
		//<< '3' << '\n';

	//--------------cursor with selection-------------
	QTest::newRow("selection mid in a line")
		<< "1|12|1|18"
		<< false << false << false << false
		<< 13+18
		<< 1 << 12 << 1 << 18
		<< "1|12" << "1|18"
		<< true << ", hell"
		<< 'l' << 'o';
	QTest::newRow("selection mid in a line reverted")
		<< "1|18|1|12"
		<< false << false << false << false
		<< 13+12
		<< 1 << 18 << 1 << 12
		<< "1|12" << "1|18"
		<< true << ", hell"
		<< '2' << ',';
	QTest::newRow("selection from line start to mid")
		<< "1|0|1|18"
		<< false << false << false << false
		<< 13+18
		<< 1 << 0 << 1 << 18
		<< "1|0" << "1|18"
		<< true << "test: line 2, hell"
		<< 'l' << 'o';
	QTest::newRow("selection from line start to mid reverted")
		<< "1|18|1|0"
		<< false << false << true << false
		<< 13+0
		<< 1 << 18 << 1 << 0
		<< "1|0" << "1|18"
		<< true << "test: line 2, hell"
		<< '\n' << 't';
	QTest::newRow("selection from line mid to end")
		<< "1|4|1|64"
		<< false << false << false << true
		<< 13+64
		<< 1 << 4 << 1 << 64
		<< "1|4" << "1|64"
		<< true << ": line 2, hello world! abcdefghijklmnopqrstuvwxyzABCDE...XYZ"
		<< 'Z' << '\n';
	QTest::newRow("selection from line mid to end reversed")
		<< "1|64|1|4"
		<< false << false << false << false
		<< 13+4
		<< 1 << 64 << 1 << 4
		<< "1|4" << "1|64"
		<< true << ": line 2, hello world! abcdefghijklmnopqrstuvwxyzABCDE...XYZ"
		<< 't' << ':';
	QTest::newRow("selection from document start to line mid")
		<< "0|0|0|4"
		<< false << false << false << false
		<< 4
		<< 0 << 0 << 0 << 4
		<< "0|0" << "0|4"
		<< true << "test"
		<< 't' << ':';
	QTest::newRow("selection from document start to line mid reversed")
		<< "0|4|0|0"
		<< true << false << true << false
		<< 0
		<< 0 << 4 << 0 << 0
		<< "0|0" << "0|4"
		<< true << "test"
		<< '\0' << 't';
	QTest::newRow("selection from line mid to document end")
		<< "2|6|3|0"
		<< false << true << true << true
		<< 13+65+13
		<< 2 << 6 << 3 << 0
		<< "2|6" << "3|0"
		<< true << "line 3\n"
		<< '\n' << '\0';
	QTest::newRow("selection from line mid to document end reversed") //TODO: is 2|12 really the document end?
		<< "2|12|2|6"
		<< false << false << false << false
		<< 13+65+6
		<< 2 << 12 << 2 << 6
		<< "2|6" << "2|12"
		<< true << "line 3"
		<< ' ' << 'l';
	QTest::newRow("selection from line start to line end")
		<< "1|0|1|64"
		<< false << false << false << true
		<< 13+64
		<< 1 << 0 << 1 << 64
		<< "1|0" << "1|64"
		<< true << "test: line 2, hello world! abcdefghijklmnopqrstuvwxyzABCDE...XYZ"
		<< 'Z' << '\n';
	QTest::newRow("selection from line start to line end reversed")
		<< "1|64|1|0"
		<< false << false << true << false
		<< 13+0
		<< 1 << 64 << 1 << 0
		<< "1|0" << "1|64"
		<< true << "test: line 2, hello world! abcdefghijklmnopqrstuvwxyzABCDE...XYZ"
		<< '\n' << 't';
	QTest::newRow("multi line selection from document start to document end") //TODO: is 2|12 really the document end?
		<< "0|0|3|0"
		<< false << true << true << true
		<< 13+65+13
		<< 0 << 0 << 3 << 0
		<< "0|0" << "3|0"
		<< true << "test: line 1\ntest: line 2, hello world! abcdefghijklmnopqrstuvwxyzABCDE...XYZ\ntest: line 3\n"
		<< '\n' << '\0';
	QTest::newRow("multi line selection from document start to document end reversed") //TODO: is 2|12 really the document end?
		<< "2|12|0|0"
		<< true << false << true << false
		<< 0
		<< 2 << 12 <<  0 << 0
		<< "0|0" << "2|12"
		<< true << "test: line 1\ntest: line 2, hello world! abcdefghijklmnopqrstuvwxyzABCDE...XYZ\ntest: line 3" //no \n at end?
		<< '\0' << 't';
	QTest::newRow("multi line selection from line mid to next line")
		<< "0|4|1|2"
		<< false << false << false << false
		<< 13+2
		<< 0 << 4 << 1 << 2
		<< "0|4" << "1|2"
		<< true << ": line 1\nte"
		<< 'e' << 's';
	QTest::newRow("multi line selection from line mid to next line reversed")
		<< "1|2|0|4"
		<< false << false << false << false
		<< 4
		<< 1 << 2 << 0 << 4
		<< "0|4" << "1|2"
		<< true << ": line 1\nte"
		<< 't' << ':';
	QTest::newRow("multi line selection from line mid to second next line")
		<< "0|4|2|10"
		<< false << false << false << false
		<< 13+65+10
		<< 0 << 4 << 2 << 10
		<< "0|4" << "2|10"
		<< true << ": line 1\ntest: line 2, hello world! abcdefghijklmnopqrstuvwxyzABCDE...XYZ\ntest: line"
		<< 'e' << ' ';
	QTest::newRow("multi line selection from line mid to second next line reversed")
		<< "2|10|0|4"
		<< false << false << false << false
		<< 4
		<< 2 << 10 << 0 << 4
		<< "0|4" << "2|10"
		<< true << ": line 1\ntest: line 2, hello world! abcdefghijklmnopqrstuvwxyzABCDE...XYZ\ntest: line"
		<< 't' << ':';

	//there are more cases (e.g. multi line starting at line start/end) but they probably aren't independent of those tested above
}
void QDocumentCursorTest::constMethods(){
	QFETCH(QString, cursor);
	QFETCH(bool, atStart);
	QFETCH(bool, atEnd);
	QFETCH(bool, atLineStart);
	QFETCH(bool, atLineEnd);
	QFETCH(int, position);
	QFETCH(int, anchorLineNumber);
	QFETCH(int, anchorColumnNumber);
	QFETCH(int, lineNumber);
	QFETCH(int, columnNumber);
	QFETCH(QString, selectionStart);
	QFETCH(QString, selectionEnd);
	QFETCH(bool, hasSelection);
	QFETCH(QString, selectedText);
	QFETCH(char, previousChar);
	QFETCH(char, nextChar);

	Q_UNUSED(position)

	QDocumentCursor c=str2cur(cursor);
	QVERIFY(c.isValid()); QVERIFY(!c.isNull());
	QVERIFY(c==c); QVERIFY(!(c!=c));
	QVERIFY(c<=c); QVERIFY(c>=c);
	QVERIFY(!(c<c)); QVERIFY(!(c>c));
	QEQUAL(c.atStart(), atStart);
	QEQUAL(c.atEnd(), atEnd);
	QEQUAL(c.atLineStart(), atLineStart);
	QEQUAL(c.atLineEnd(), atLineEnd);
	//QEQUAL(c.position(), position);
	QEQUAL(c.anchorLineNumber(), anchorLineNumber);
	QEQUAL(c.anchorColumnNumber(), anchorColumnNumber);
	QEQUAL(c.lineNumber(), lineNumber);
	QEQUAL(c.columnNumber(), columnNumber);
	QVERIFY(c.line()==doc->line(lineNumber));
	QVERIFY(c.anchorLine()==doc->line(anchorLineNumber));
	if (selectionStart == "") QVERIFY(c.selectionStart().isNull());
	else QSVERIFY2(c.selectionStart() == str2cur(selectionStart),QString("%1:%2").arg(c.selectionStart().lineNumber()).arg(c.selectionStart().columnNumber()));
	if (selectionEnd == "") QVERIFY(c.selectionEnd().isNull());
	else QSVERIFY2(c.selectionEnd() == str2cur(selectionEnd),QString("%1:%2").arg(c.selectionEnd().lineNumber()).arg(c.selectionEnd().columnNumber()));
	QEQUAL(c.hasSelection(), hasSelection);
	QEQUAL(c.selectedText(), selectedText);
	QEQUAL(c.previousChar(), previousChar);
	QEQUAL(c.nextChar(), nextChar);

}
void QDocumentCursorTest::const2Methods_data(){
	QTest::addColumn<QString>("tc1");
	QTest::addColumn<QString>("tc2");
	QTest::addColumn<bool>("eq");
	QTest::addColumn<bool>("neq");
	QTest::addColumn<bool>("lt");
	QTest::addColumn<bool>("gt");
	QTest::addColumn<bool>("lteq");
	QTest::addColumn<bool>("gteq");
	QTest::addColumn<bool>("c1withinc2"); //c1.isWithInSelection(c2) === is c2 within c1
	QTest::addColumn<QString>("intersection");

	//----------------identical cursor------------------
	QTest::newRow("identical cursors single line")
		<< "1|4|1|10" << "1|4|1|10"
		<< true << false
		<< false << false
		<< true << true
		<< true
		<< "1|4|1|10";
	QTest::newRow("identical cursors multi lines")
		<< "0|4|2|7" << "0|4|2|7"
		<< true << false
		<< false << false
		<< true << true
		<< true
		<< "0|4|2|7";


	//---------------identical right side-----------------
	//if the right side is identical the cursor are considered to be identical
	QTest::newRow("identical right side, c1 before c2 on same line, single line")
		<< "1|4|1|17" << "1|10|1|17"
		<< true << false//<< false << true
		<< false << false // << true << false
		<< true << true//<< true << false
		<< true
		<< "1|10|1|17";
	QTest::newRow("identical right side, c1 before c2 on same line, multi line")
		<< "1|4|2|7" << "1|10|2|7"
		<< true << false //<< false << true
		<< false << false  //<< true << false
		<< true << true //<< true << false
		<< true
		<< "1|10|2|7";

	QTest::newRow("identical right side, c1 after c2 on same line, single line")
		<< "1|8|1|17" << "1|3|1|17"
		<< true << false //<< false << true
		<< false << false  //<< false << true
		<< true << true//<< false << true
		<< true //false
		<< "1|8|1|17";
	QTest::newRow("identical right side, c1 after c2 on same line, multi line")
		<< "1|9|2|7" << "1|3|2|7"
		<< true << false//<< false << true
		<< false << false  //<< false << true
		<< true << true//<< false << true
		<< true //false
		<< "1|9|2|7";


	QTest::newRow("identical right side, c1 before c2 on different lines")
		<< "0|8|2|7" << "1|4|2|7"
		<< true << false //<< false << true
		<< false << false  //<< true << false
		<< true << true //<< true << false
		<< true
		<< "1|4|2|7";
	QTest::newRow("identical right side, c1 after c2 on different lines")
		<< "1|0|2|7" << "0|3|2|7"
		<< true << false//<< false << true
		<< false << false  //<< false << true
		<< true << true//<< false << true
		<< true //false
		<< "1|0|2|7";


	//----------------identical left side-------------------
	QTest::newRow("identical left side, c1 before c2 on same line, single line")
		<< "1|4|1|10" << "1|4|1|17"
		<< false << true
		<< true << false
		<< true << false
		<< false
		<< "1|4|1|10";
	QTest::newRow("identical left side, c1 before c2 on same line, multi line")
		<< "0|7|2|4" << "0|7|2|7"
		<< false << true
		<< true << false
		<< true << false
		<< false
		<< "0|7|2|4";

	QTest::newRow("identical left side, c1 after c2 on same line, single line")
		<< "1|3|1|17" << "1|3|1|7"
		<< false << true
		<< false << true
		<< false << true
		<< true
		<< "1|3|1|7";
	QTest::newRow("identical left side, c1 after c2 on same line, multi line")
		<< "1|3|2|7" << "1|3|2|3"
		<< false << true
		<< false << true
		<< false << true
		<< true //false
		<< "1|3|2|3";

	QTest::newRow("identical left side, c1 before c2 on different lines")
		<< "0|5|1|10" << "0|5|2|7"
		<< false << true
		<< true << false
		<< true << false
		<< false
		<< "0|5|1|10";
	QTest::newRow("identical left side, c1 after c2 on different lines")
		<< "1|0|2|7" << "1|0|1|3"
		<< false << true
		<< false << true
		<< false << true
		<< true
		<< "1|0|1|3";


	//-------------c1 left side before c2--------------
	QTest::newRow("c1 left side before c2, no intersection, start on same line")
		<< "0|1|0|5" << "0|7|2|10"
		<< false << true
		<< true << false
		<< true << false
		<< false
		<< "";

	QTest::newRow("c1 left side before c2, no intersection, start on different lines")
		<< "0|1|1|5" << "1|7|2|10"
		<< false << true
		<< true << false
		<< true << false
		<< false
		<< "";

	QTest::newRow("c1 left side before c2, no intersection, start on same line, c1 inverted")
		<< "0|5|0|1" << "0|7|2|10"
		<< false << true
		<< true << false
		<< true << false
		<< false
		<< "";

	QTest::newRow("c1 left side before c2, no intersection, start on different lines, c1 inverted")
		<< "1|5|0|5" << "1|7|2|10"
		<< false << true
		<< true << false
		<< true << false
		<< false
		<< "";


	QTest::newRow("c1 left side before c2, touching ends, start on same line")
		<< "0|1|0|7" << "0|7|2|10"
		<< false << true
		<< true << false
		<< true << false
		<< false
		<< "0|7";

	QTest::newRow("c1 left side before c2, touching ends, start on same line, inverted")
		<< "0|1|0|7" << "2|10|0|7"
		<< true << false
		<< false << false
		<< true << true
		<< true
		<< "0|7";

	QTest::newRow("c1 left side before c2, touching ends on next line")
		<< "0|0|1|0" << "1|0|2|10"
		<< false << true
		<< true << false
		<< true << false
		<< false
		<< "1|0";

	QTest::newRow("c1 left side before c2, touching ends on next line, inverted")
		<< "0|1|1|0" << "2|10|1|0"
		<< true << false
		<< false << false
		<< true << true
		<< true
		<< "1|0";
	//...

	//-------------c1 left side after c2--------------
	//...
}
void QDocumentCursorTest::const2Methods(){
	QFETCH(QString, tc1);
	QFETCH(QString, tc2);
	QFETCH(bool,eq);
	QFETCH(bool,neq);
	QFETCH(bool,lt);
	QFETCH(bool,gt);
	QFETCH(bool,lteq);
	QFETCH(bool,gteq);
	QFETCH(bool,c1withinc2);
	QFETCH(QString,intersection);

	QDocumentCursor c1=str2cur(tc1);
	QDocumentCursor c2=str2cur(tc2);

	QVERIFY(!c1.isNull());	QVERIFY(c1.isValid());
	QVERIFY(!c2.isNull());	QVERIFY(c2.isValid());
	QVERIFY(c1==c1); QVERIFY(c2==c2);
	QVERIFY(c1<=c1); QVERIFY(c2<=c2);
	QVERIFY(c1>=c1); QVERIFY(c2>=c2);

	QEQUAL(c1==c2, eq);
	QEQUAL(c1!=c2, neq);
	QEQUAL(c1<c2, lt);
	QEQUAL(c1>c2, gt);
	QEQUAL(c1<=c2, lteq);
	QEQUAL(c1>=c2, gteq);

	QEQUAL(c1.isWithinSelection(c2), c1withinc2);
	QCEEQUAL(c1.intersect(c2),str2cur(intersection));

}
void QDocumentCursorTest::subtractBoundaries_data(){
	QTest::addColumn<QString>("cursor");
	QTest::addColumn<QString>("subtract");
	QTest::addColumn<QString>("result");

/*aaaXXXXXbbbb*/
	QTest::newRow("cutting left, one char") << "0|4|0|9" << "0|4|0|5" << "0|4|0|8";
	QTest::newRow("cutting left, multiple chars") << "0|4|0|9" << "0|4|0|7" << "0|4|0|6";
	QTest::newRow("cutting left, whole selection") << "0|4|0|9" << "0|4|0|9" << "0|4|0|4";

	QTest::newRow("beyond left, one intersecting char") << "0|4|0|9" << "0|2|0|5" << "0|2|0|6";
	QTest::newRow("beyond left, multiple char") << "0|4|0|9" << "0|2|0|6" << "0|2|0|5";
	QTest::newRow("beyond left, whole selection") << "0|4|0|9" << "0|2|0|9" << "0|2|0|2";
	QTest::newRow("beyond left, more than selection") << "0|4|0|9" << "0|2|0|13" << "0|2|0|2";

	QTest::newRow("cutting mid, chars") << "0|4|0|9" << "0|5|0|8" << "0|4|0|6";
	QTest::newRow("cutting mid, remaining") << "0|4|0|9" << "0|5|0|9" << "0|4|0|5";
	QTest::newRow("cutting mid, more than selection") << "0|4|0|9" << "0|5|0|12" << "0|4|0|5";

/*aaaaXXXXXX
ZZZZZZZZZZbbbbbbbbbbbb*/

	QTest::newRow("cutting left, one char") << "0|4|1|10" << "0|4|0|5" << "0|4|1|10";
	QTest::newRow("cutting left, multiple char") << "0|4|1|10" << "0|4|0|10" << "0|4|1|10";
	QTest::newRow("cutting left, whole line") << "0|4|1|10" << "0|4|1|0" << "0|4|0|14";
	QTest::newRow("cutting left, whole line + chars on last line") << "0|4|1|10" << "0|4|1|3" << "0|4|0|11";
	QTest::newRow("cutting left, whole selection") << "0|4|1|10" << "0|4|1|10" << "0|4|0|4";
	QTest::newRow("cutting left, more than selection") << "0|4|1|10" << "0|4|1|20" << "0|4|0|4";

	QTest::newRow("cutting mid, in first line") << "0|4|1|10" << "0|6|0|10" << "0|4|1|10";
	QTest::newRow("cutting mid, first line") << "0|4|1|10" << "0|6|1|0" << "0|4|0|16";
	QTest::newRow("cutting mid, first line + part of second") << "0|4|1|10" << "0|6|1|4" << "0|4|0|12";
	QTest::newRow("cutting mid, remaining") << "0|4|1|10" << "0|6|1|10" << "0|4|0|6";
	QTest::newRow("cutting mid, more than selection") << "0|4|1|10" << "0|6|1|12" << "0|4|0|6";
	QTest::newRow("cutting mid, in second line") << "0|4|1|10" << "1|3|1|5" << "0|4|1|8";

/*aaaaXXXXXX
YYYYYYYYYY
ZZZZZZZZbbbbbbbbbbbb*/

	QTest::newRow("cutting left, single char") << "0|4|2|10" << "0|4|0|5" << "0|4|2|10"; //(no change, only line length in the selection differs)
	QTest::newRow("cutting left, multiple chars") << "0|4|2|10" << "0|4|0|10" << "0|4|2|10"; // "
	QTest::newRow("cutting left, whole line of selection") << "0|4|2|10" << "0|4|1|0" << "0|4|1|10"; //(removing first line of selection, everything moves one line up)
	QTest::newRow("cutting left, whole line + chars on next line") << "0|4|2|10" << "0|4|1|5" << "0|4|1|10";//"
	QTest::newRow("cutting left, two whole lines") << "0|4|2|10" << "0|4|2|0" << "0|4|0|14";
	QTest::newRow("cutting left, two whole lines + chars on last line") << "0|4|2|10" << "0|4|2|8" << "0|4|0|6";

	//QTest::newRow("beyond left, no intersection") << "0|4|2|10" << "0|1|0|3" << "0|4|2|10"; //should move left, but substractb.. handles only intersections
	QTest::newRow("beyond left, intersection in first line") << "0|4|2|10" << "0|1|0|10" << "0|1|2|10"; //moves to the left because characters before selection are removed
	QTest::newRow("beyond left, removing complete previous line") << "1|0|2|10" << "0|0|1|0" << "0|0|1|10"; //line moves up
	QTest::newRow("beyond left, removing partly previous line") << "1|0|2|10" << "0|5|1|0" << "0|5|1|10"; //line moves up, column moves left

	QTest::newRow("cutting mid, chars in first line") << "0|4|2|10" << "0|6|0|10" << "0|4|2|10";
	QTest::newRow("cutting mid, chars in second line") << "0|4|2|10" << "1|6|1|10" << "0|4|2|10";
	QTest::newRow("cutting mid, chars in third line") << "0|4|2|10" << "2|4|2|6" << "0|4|2|8";
	QTest::newRow("cutting mid, whole second line") << "0|4|2|10" << "1|0|2|0" << "0|4|1|10";
	QTest::newRow("cutting mid, second line + chars in third") << "0|4|2|10" << "1|0|2|4" << "0|4|1|6";
	QTest::newRow("cutting mid, remaining") << "0|4|2|10" << "1|0|2|10" << "0|4|1|0";
	QTest::newRow("cutting mid, more than selection") << "0|4|2|10" << "1|0|2|15" << "0|4|1|0";

}
void QDocumentCursorTest::subtractBoundaries(){
	QFETCH(QString, cursor);
	QFETCH(QString, subtract);
	QFETCH(QString, result);
	QDocumentCursor c=str2cur(cursor),
	                s=str2cur(subtract),
	                r=str2cur(result);
	int bl, bc, el, ec;
	s.boundaries(bl,bc,el,ec);
	c.handle()->substractBoundaries(bl,bc,el,ec);
	QCEEQUAL(c,r);

	//check swapped cursor
	c = str2cur(cursor);
	c = doc->cursor(c.lineNumber(),c.columnNumber(),c.anchorLineNumber(),c.anchorColumnNumber());
	c.handle()->substractBoundaries(bl,bc,el,ec);
	r = doc->cursor(r.lineNumber(),r.columnNumber(),r.anchorLineNumber(),r.anchorColumnNumber());
	QCEEQUAL2(c,r, "swapped");
}
void QDocumentCursorTest::movePosition_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("line");
	QTest::addColumn<int>("column");
	QTest::addColumn<int>("moveCount");
	QTest::addColumn<int>("operation");
	QTest::addColumn<int>("newLine");
	QTest::addColumn<int>("newColumn");
	QTest::addColumn<bool>("expectedReturnValue");

	QString text = "0123 5678\n0123 5678\n0123 5678";
	QTest::newRow("left") << text << 1 << 1 << 1 << (int)QDocumentCursor::Left << 1 << 0 << true;
	QTest::newRow("left5") << text << 1 << 6 << 5 << (int)QDocumentCursor::Left << 1 << 1 << true;
	QTest::newRow("left to start") << text << 0 << 2 << 2 << (int)QDocumentCursor::Left << 0 << 0 << true;
	QTest::newRow("left beyond start") << text << 0 << 2 << 3 << (int)QDocumentCursor::Left << 0 << 2 << false;
	QTest::newRow("left across line") << text << 2 << 1 << 3 << (int)QDocumentCursor::Left << 1 << 8 << true;
	QTest::newRow("left across multi line") << text << 2 << 1 << 13 << (int)QDocumentCursor::Left << 0 << 8 << true;
	QTest::newRow("left across empty line") << "0123 5678\n\n0123 5678" << 2 << 1 << 4 << (int)QDocumentCursor::Left << 0 << 8 << true;

	QTest::newRow("right") << text << 0 << 1 << 1 << (int)QDocumentCursor::Right << 0 << 2 << true;
	QTest::newRow("right5") << text << 0 << 1 << 5 << (int)QDocumentCursor::Right << 0 << 6 << true;
	QTest::newRow("right to line end") << text << 0 << 1 << 8 << (int)QDocumentCursor::Right << 0 << 9 << true;
	QTest::newRow("right to end") << text << 2 << 2 << 7 << (int)QDocumentCursor::Right << 2 << 9 << true;
	QTest::newRow("right beyond end") << text << 2 << 2 << 20 << (int)QDocumentCursor::Right << 2 << 2 << false;
	QTest::newRow("right across line") << text << 0 << 8 << 3 << (int)QDocumentCursor::Right << 1 << 1 << true;
	QTest::newRow("right across multi line") << text << 0 << 8 << 13 << (int)QDocumentCursor::Right << 2 << 1 << true;
	QTest::newRow("right across empty line") << "0123 5678\n\n0123 5678" << 0 << 8 << 4 << (int)QDocumentCursor::Right << 2 << 1 << true;

	QTest::newRow("StartOfParenthesis no parens") << "012 456" << 0 << 4 << 1 << (int)QDocumentCursor::StartOfParenthesis << 0 << 4 << false;
	QTest::newRow("StartOfParenthesis4") << "012 {567} 0" << 0 << 4 << 1 << (int)QDocumentCursor::StartOfParenthesis << 0 << 4 << true;
	QTest::newRow("StartOfParenthesis5") << "012 {567} 0" << 0 << 5 << 1 << (int)QDocumentCursor::StartOfParenthesis << 0 << 4 << true;
	QTest::newRow("StartOfParenthesis6") << "012 {567} 0" << 0 << 6 << 1 << (int)QDocumentCursor::StartOfParenthesis << 0 << 4 << true;
	QTest::newRow("StartOfParenthesis7") << "012 {567} 0" << 0 << 7 << 1 << (int)QDocumentCursor::StartOfParenthesis << 0 << 4 << true;
	QTest::newRow("StartOfParenthesis8") << "012 {567} 0" << 0 << 8 << 1 << (int)QDocumentCursor::StartOfParenthesis << 0 << 4 << true;
	QTest::newRow("StartOfParenthesis9") << "012 {567} 0" << 0 << 9 << 1 << (int)QDocumentCursor::StartOfParenthesis << 0 << 4 << true;
	QTest::newRow("StartOfParenthesis10") << "012 {567} 0" << 0 << 10 << 1 << (int)QDocumentCursor::StartOfParenthesis << 0 << 10 << false;

	QTest::newRow("StartOfParenthesis nested same") << "012 {456 {901} 456}" << 0 << 15 << 1 << (int)QDocumentCursor::StartOfParenthesis << 0 << 4 << true;
	QTest::newRow("StartOfParenthesis nested other") << "012 {456 [901] 456}" << 0 << 15 << 1 << (int)QDocumentCursor::StartOfParenthesis << 0 << 4 << true;
}
void QDocumentCursorTest::movePosition(){
	QFETCH(QString, text);
	QFETCH(int, line);
	QFETCH(int, column);
	QFETCH(int, moveCount);
	QFETCH(int, operation);
	QFETCH(int, newLine);
	QFETCH(int, newColumn);
	QFETCH(bool, expectedReturnValue);

	doc->setText(text, false);
	for (int i=0;i<doc->lineCount();i++)
		doc->line(i).handle()->layout(i);

	QDocumentCursor c(doc, line, column);
	bool b = c.movePosition(moveCount, (QDocumentCursor::MoveOperation) operation);
	QEQUAL2(c.lineNumber(), newLine, "line" );
	QEQUAL2(c.columnNumber(), newColumn, "column" );
	QEQUAL2(b, expectedReturnValue, "return value" );
}
void QDocumentCursorTest::bidiMoving_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("line");
	QTest::addColumn<int>("column");
	QTest::addColumn<int>("movement");
	QTest::addColumn<int>("dir");
	QTest::addColumn<int>("newLine");
	QTest::addColumn<int>("newColumn");

	const int L = (int)QDocumentCursor::Left;
	const int R = (int)QDocumentCursor::Right;

	QString withMarkers = QString::fromUtf8("\n" "ه‎\\glqq{}‎‎" "\n"); //rendered as \glqq{}o
    if (globalExecuteAllTests) {
        QTest::newRow("with all markers 1")  << withMarkers << 1<<0  << 1 << R << 2<<0; // failing test on ubuntu
    }
	QTest::newRow("with all markers 2")  << withMarkers << 1<<0  << 1 << L << 1<<11; //????? that is not the same position as if run manually (there it skips 11 and goes to 10)
	QTest::newRow("with all markers 2b") << withMarkers << 1<<11 << 1 << L << 1<<10;
	QTest::newRow("with all markers 2r") << withMarkers << 1<<11 << 1 << R << 1<<0;
	QTest::newRow("with all markers 3")  << withMarkers << 1<<10 << 1 << L << 1<<9;
	QTest::newRow("with all markers 3r") << withMarkers << 1<<10 << 1 << R << 1<<11; //again, skips 11 if run interactively
	QTest::newRow("with all markers 4")  << withMarkers << 1<<9 << 1 << L << 1<<8;
	QTest::newRow("with all markers 5")  << withMarkers << 1<<8 << 1 << L << 1<<7;
	QTest::newRow("with all markers 6")  << withMarkers << 1<<7 << 1 << L << 1<<6;
	QTest::newRow("with all markers 7")  << withMarkers << 1<<1 << 1 << L << 0<<0; //jump over invisible marker

	QString withSomeMarkers = QString::fromUtf8("\n" "ه‎\\test{}" "\n"); //rendered as {}\testo
    if (globalExecuteAllTests) {
        QTest::newRow("with some markers 1")  << withSomeMarkers << 1<<0  << 1 << R << 2<<0; // failing test on ubuntu
    }
	QTest::newRow("with some markers 2")  << withSomeMarkers << 1<<0  << 1 << L << 1<<6;
	QTest::newRow("with some markers 2r") << withSomeMarkers << 1<<6  << 1 << R << 1<<0;
	QTest::newRow("with some markers 3")  << withSomeMarkers << 1<<2  << 1 << L << 1<<1;
	QTest::newRow("with some markers 4")  << withSomeMarkers << 1<<1  << 1 << L << 1<<7;
	QTest::newRow("with some markers 5")  << withSomeMarkers << 1<<7  << 1 << L << 1<<8;
	QTest::newRow("with some markers 5r") << withSomeMarkers << 1<<7  << 1 << R << 1<<1;
	QTest::newRow("with some markers 6")  << withSomeMarkers << 1<<8  << 1 << L << 1<<9;
	QTest::newRow("with some markers 6r") << withSomeMarkers << 1<<8  << 1 << R << 1<<7;
	QTest::newRow("with some markers 6")  << withSomeMarkers << 1<<9  << 1 << L << 0<<0;

	QString withOtherMarkers = QString::fromUtf8("\n" "ه\\glqq{}‎" "\n"); //rendered as glqq{}\o
    if (globalExecuteAllTests) {
        QTest::newRow("with other markers 1")  << withOtherMarkers << 1<<0  << 1 << R << 2<<0; // failing test on ubuntu
    }
	QTest::newRow("with other markers 2")  << withOtherMarkers << 1<<0  << 1 << L << 1<<1;
	QTest::newRow("with other markers 3")  << withOtherMarkers << 1<<1  << 1 << L << 1<<9; //this is 8 if run manually (9 is invisible control character?)
	QTest::newRow("with other markers 3r") << withOtherMarkers << 1<<9  << 1 << R << 1<<1;
	QTest::newRow("with other markers 4")  << withOtherMarkers << 1<<9  << 1 << L << 1<<8;
	QTest::newRow("with other markers 5")  << withOtherMarkers << 1<<8  << 1 << L << 1<<7;
	QTest::newRow("with other markers 6")  << withOtherMarkers << 1<<2  << 1 << L << 0<<0;

	QString full = QString::fromUtf8("\n" "دددددددد" "\n");
	QTest::newRow("start of line")  << full << 1<<4  << 1 << (int)QDocumentCursor::StartOfLine << 1<<0; //that's actually just like in ltr in this case
	QTest::newRow("end of line")    << full << 1<<4  << 1 << (int)QDocumentCursor::EndOfLine   << 1<<8;

	QString combined = QString::fromUtf8("\n" "دددددtest" "\n");
	QTest::newRow("start of line")  << combined << 1<<4  << 1 << (int)QDocumentCursor::StartOfLine << 1<<0;
    if (globalExecuteAllTests) {
        QTest::newRow("end of line")    << combined << 1<<4  << 1 << (int)QDocumentCursor::EndOfLine   << 1<<5; //appended ltr text does not count , failing test on ubuntu
    }

}

void QDocumentCursorTest::bidiMoving(){
	QFETCH(QString, text);
	QFETCH(int, line);
	QFETCH(int, column);
	QFETCH(int, dir);
	QFETCH(int, movement);
	QFETCH(int, newLine);
	QFETCH(int, newColumn);

	if (m_autoTests){
		qDebug("skipped bidi tests");
		return;
	}


	doc->setText(text,false);
	for (int i=0;i<doc->lineCount();i++)
		doc->line(i).handle()->layout(i);

	QDocumentCursor c(doc, line, column);
	c.movePosition(movement, (QDocumentCursor::MoveOperation)dir);
	QEQUAL2(c.lineNumber(), newLine, "line" );
	QEQUAL2(c.columnNumber(), newColumn, "column" );

}

void QDocumentCursorTest::isForwardSelection_data()
{
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("line");
	QTest::addColumn<int>("column");
	QTest::addColumn<int>("anchorLine");
	QTest::addColumn<int>("anchorColumn");
	QTest::addColumn<bool>("expectedResult");
	QTest::newRow("no selection") << "foo" << 0 << 1 << -1 << -1 << false;
	QTest::newRow("forward single line") << "foo" << 0 << 1 << 0 << 2 << true;
	QTest::newRow("backward single line") << "foo" << 0 << 2 << 0 << 1 << false;
	QTest::newRow("forward multi line") << "foo\nbar" << 0 << 1 << 1 << 0 << true;
	QTest::newRow("backward multi line") << "foo\nbar" << 1 << 2 << 0 << 1 << false;
}

void QDocumentCursorTest::isForwardSelection()
{
	QFETCH(QString, text);
	QFETCH(int, line);
	QFETCH(int, column);
	QFETCH(int, anchorLine);
	QFETCH(int, anchorColumn);
	QFETCH(bool, expectedResult);
	doc->setText(text, false);
	QDocumentCursor c(doc, line, column, anchorLine, anchorColumn);
	QEQUAL(c.isForwardSelection(), expectedResult);
}

void QDocumentCursorTest::columnMemory_data()
{
	// Enable soft line breaks
	doc->impl()->setHardLineWrap(false);
	doc->impl()->setLineWidthConstraint(true);
	// The code that calculates wrap width is taken from QEditor::setWrapAfterNumChars
	int wrapAfterNumChars = 50;
	int wrapWidth=QFontMetrics(QDocument::font()).averageCharWidth()*(wrapAfterNumChars+0.5) + 5; // +5 fixed width on left side, 0.5: 1/2 a char margin on right side
	doc->setWidthConstraint(wrapWidth);
	doc->setText(
		(
			"abcdefghij\n"
			"\t\tabcdef ghijabcde fghijab cdefghi jabcdef ghij abcdef ghij abcd efghija\n"
			"qqqqqqqqqqqqqq"
		),
		false
	);

	QTest::addColumn<int>("column");
	QTest::addColumn<bool>("downwards");
	QTest::addColumn<int>("numOps");

	QTest::newRow("at column 0, downwards") << 0 << true << 3;
	QTest::newRow("at column 0, upwards") << 0 << false << 3;
	QTest::newRow("at column 1, downwards") << 1 << true << 3;
	QTest::newRow("at column 1, upwards") << 1 << false << 3;
}

void QDocumentCursorTest::columnMemory()
{
	QFETCH(int, column);
	QFETCH(bool, downwards);
	QFETCH(int, numOps);
	int lastLineNumber, i;

	lastLineNumber = doc->lines() - 1;
	QDocumentCursor cursor(doc, downwards ? 0 : lastLineNumber, column);
	cursor.setColumnMemory(true);
	for (i = 0; i < numOps; ++i) {
		qDebug() << QString("Before move. Index %1, line %2, column %3").arg(i).arg(cursor.lineNumber()).arg(cursor.columnNumber());
		cursor.movePosition(
			1,
			static_cast<QDocumentCursor::MoveOperation> (downwards ? QDocumentCursor::Down : QDocumentCursor::Up),
			QDocumentCursor::ThroughWrap
		);
		qDebug() << QString("After move. Index %1, line %2, column %3").arg(i).arg(cursor.lineNumber()).arg(cursor.columnNumber());
	}
	QEQUAL(cursor.lineNumber(), downwards ? lastLineNumber : 0);
	QEQUAL(cursor.columnNumber(), column);
}

void QDocumentCursorTest::cleanupTestCase(){
	delete doc;
}
#endif
