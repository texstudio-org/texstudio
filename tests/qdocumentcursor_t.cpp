
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "qdocumentcursor_t.h"
#include "qdocumentcursor.h"
#include "qdocument.h"
#include "qdocumentline.h"
#include "testutil.h"
#include <QtTest/QtTest>
void QDocumentCursorTest::initTestCase(){
	doc=new QDocument();
	doc->setText("test: line 1\n"
	             "test: line 2, hello world! abcdefghijklmnopqrstuvwxyzABCDE...XYZ\n"
				 "test: line 3\n");
}
QDocumentCursor QDocumentCursorTest::str2cur(const QString &s){
	QStringList sl=s.split("|");
	if (sl.size()==2) return doc->cursor(sl[0].toInt(),sl[1].toInt());
	else if (sl.size()==4) return doc->cursor(sl[0].toInt(),sl[1].toInt(),sl[2].toInt(),sl[3].toInt());
	else return QDocumentCursor();
	
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
	QTest::addColumn<bool>("c1withinc2");
	QTest::addColumn<QString>("intersection");
	
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
	QDocumentCursor intersect = str2cur(intersection);
	QVERIFY(intersect == c1.intersect(c2));
	
}
void QDocumentCursorTest::cleanupTestCase(){
	delete doc;
}
#endif

