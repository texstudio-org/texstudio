#ifndef QT_NO_DEBUG
#include "qdocumentline_t.h"

//Actually this is a qdocumentlinehandle test, but they are almost the same

//----
//force full access to qdocument things
#define private public
#include "qdocument_p.h"
#include "qdocumentline_p.h"
#undef private
//----

#include "qeditor.h"
#include "qdocumentline.h"
#include "qdocumentline_p.h"
#include "testutil.h"
#include "smallUsefulFunctions.h"
#include <QtTest/QtTest>

QDocumentLineTest::QDocumentLineTest():savedFixedPitch(false),savedSpaceWidth(0), savedLeftPadding(0),savedWorkAroundFPM(false), savedWorkAroundFSCD(false), savedWorkAroundFQTL(false)
{
	doc=new QDocument(this);

}
QDocumentLineTest::~QDocumentLineTest(){
}

void QDocumentLineTest::initTestCase(){
	savedFixedPitch = QDocumentPrivate::m_fixedPitch;
	savedSpaceWidth = QDocumentPrivate::m_spaceWidth;
	savedLeftPadding = QDocumentPrivate::m_leftPadding;

	savedWorkAroundFPM = doc->hasWorkAround(QDocument::DisableFixedPitchMode);
	savedWorkAroundFSCD = doc->hasWorkAround(QDocument::ForceSingleCharacterDrawing);
	savedWorkAroundFQTL = doc->hasWorkAround(QDocument::ForceQTextLayout);
	
	doc->impl()->setHardLineWrap(false);
	doc->setWorkAround(QDocument::DisableFixedPitchMode, false);
	doc->setWorkAround(QDocument::ForceSingleCharacterDrawing, false);
	doc->setWorkAround(QDocument::ForceQTextLayout, false);
	QDocumentPrivate::m_fixedPitch = true;
	QDocumentPrivate::m_leftPadding = 0;
	QDocumentPrivate::m_spaceWidth = 5;
}

void QDocumentLineTest::cleanupTestCase(){
	QDocumentPrivate::m_fixedPitch = savedFixedPitch;
	QDocumentPrivate::m_spaceWidth = savedSpaceWidth;
	QDocumentPrivate::m_leftPadding = savedLeftPadding;
	doc->setWorkAround(QDocument::DisableFixedPitchMode, savedWorkAroundFPM);
	doc->setWorkAround(QDocument::ForceSingleCharacterDrawing, savedWorkAroundFSCD);
	doc->setWorkAround(QDocument::ForceQTextLayout, savedWorkAroundFQTL);
}

typedef QPair<int, int> IntPair;

void QDocumentLineTest::updateWrap_data(){
	QTest::addColumn<QString>("line");
	QTest::addColumn<int>("width");

	//every letter = 5px

	QTest::newRow("no wrap") << "abc" << 20;
	QTest::newRow("no wrap - exact hit") << "abcd" << 20;
	QTest::newRow("one pixel off") << "abc|d" << 19;
	QTest::newRow("3 lines force-break") << "abcd|efgh|ijkl" << 20;
	QTest::newRow("3 lines force-break - 2px waste") << "abcd|efgh|ijkl" << 22;
	QTest::newRow("3 lines force-break - 3px waste") << "abcd|efgh|ijkl" << 23;
	QTest::newRow("4 lines force-break - 2px off") << "abc|def|ghi|jkl" << 18;
	QTest::newRow("word break") << "ab |cde" << 20;
	QTest::newRow("word break - 2 spaces") << "ab  |cde" << 20;//??
	QTest::newRow("word break - 3 spaces nowhere to go") << "ab  | cde" << 20;
	QTest::newRow("word break - 4 spaces nowhere to go") << "ab  |  cd" << 20;
	QTest::newRow("word break - 4 spaces nowhere to go") << "ab  |  |cde" << 20;
	QTest::newRow("word break - space bug") << "a |a  x" << 20;
	QTest::newRow("space break") << "x   |    |    |   " << 20;
	QTest::newRow("space break - 1px off") << "x  |   |   |   " << 19;
	QTest::newRow("indentation break 1") << " abc|def|ghi" << 20;
	QTest::newRow("indentation break 2") << "  ab|cd|ef" << 20;
	QTest::newRow("indentation break 2 - word") << "  ax |bcd" << 30;
	QTest::newRow("indentation breaking") << "    |    |    |   " << 20;
	QTest::newRow("indentation breaking cat") << "    |    |    |   |miau" << 20;
	QTest::newRow("indentation breaking cat in 3d") << "    |    |    |   |miau|xyz" << 20;
}

void QDocumentLineTest::updateWrap(){
	QFETCH(QString, line);
	QFETCH(int, width);

	QString temp=line; temp.replace("|","");
	doc->setText(temp+"\n\n\n",false);
	doc->setWidthConstraint(width);

	QString fExp, fGot;
	QList<int> frontiers;
	for (int i=0;i<line.size();i++)
		if (line.at(i)=='|')
			frontiers << (i - frontiers.size());
	foreach(const int p, frontiers) fExp += QString("<%1:%2>").arg(p).arg(p*5);
	foreach(const IntPair& p, doc->line(0).handle()->m_frontiers) fGot += QString("<%1:%2>").arg(p.first).arg(p.second);
		
	QEQUAL(fGot, fExp);

	
	//-------test hard line wrap----
	QList<QDocumentLineHandle*> handles;
	for (int i=0;i<doc->lines();i++)
		handles << doc->line(i).handle();
	doc->applyHardLineWrap(handles);
	
	QStringList hlw = line.split('|');
	QString indent; 
	for (int i=0;i<hlw.first().length();i++) 
		if (hlw.first()[i].isSpace()) indent += hlw.first()[i];
		else break;
	if (indent == hlw.first()) indent = "";
	for (int i=1;i<hlw.size();i++)
		hlw[i] = indent + hlw[i];
	hlw << "" << "" << "";
	
	QEQUAL(doc->text(), hlw.join("\n"));
	
}

#endif
