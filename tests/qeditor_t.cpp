#ifndef QT_NO_DEBUG
#include "qeditor_t.h"
#include "qeditor.h"
#include "tests/testutil.h"
#include <QtTest/QtTest>

QEditorTest::QEditorTest(bool executeAllTests):allTests(executeAllTests)
{
	editor=new QEditor((QWidget*)0);
}
QEditorTest::~QEditorTest(){
	delete editor;
}
void QEditorTest::loadSave_data(){
	QTest::addColumn<QString>("outCodecName");
	QTest::addColumn<QString>("outLineEnding");
	QTest::addColumn<bool>("autodetect");
	
	QStringList codings = QStringList() << "latin1" << "utf-8" << "utf-16le" << "utf-16be" << "latin2";
	QStringList endings = QStringList() << "\n" << "\r" << "\r\n";
	for (int i=0;i<codings.size();i++)
		for (int j=0;j<endings.size();j++){
			if (i!=codings.size()-1) //auto detect all except last one
				QTest::newRow(qPrintable(QString("load with encoding %1 endings %2").arg(codings[i]).arg(j)))
						<< codings[i]
						<< endings[j]
						<< true;
			QTest::newRow(qPrintable(QString("load with encoding %1 endings %2").arg(codings[i]).arg(j)))
					<< codings[i]
					<< endings[j]
					<< false;
		}

}
//checks if load/saving preserves encoding and line endings
void QEditorTest::loadSave(){
	QFETCH(QString, outCodecName);
	QFETCH(QString, outLineEnding);
	QFETCH(bool, autodetect);
	QTextCodec* outCodec=QTextCodec::codecForName(qPrintable(outCodecName));

	if (!allTests) {
		qDebug("skipped load save test");
		return;
	}

	const QString testText = "hallo\n\xE4\xF6\xFC\n";
	QString testTextWithLineEndings=testText;
	testTextWithLineEndings.replace("\n",outLineEnding);
	QTemporaryFile tf;//uncomment if you need to look at the files &tf=*(new QTemporaryFile);
	tf.open();
	QString tfn=tf.fileName();
	tf.write(outCodec->fromUnicode(testTextWithLineEndings));
	tf.close();

	//Load
	editor->setFileCodec(QTextCodec::codecForName("iso-8859-5"));
	editor->load(tfn,autodetect?0:outCodec);
	QEQUAL2(editor->document()->text(),testTextWithLineEndings,"File: "+tfn);
	QVERIFY2(editor->getFileCodec()==outCodec,qPrintable(QString("wrong encoding: got %1 wanted %2 by the sheriff %3").arg(QString::fromAscii(editor->getFileCodec()->name())).arg(QString::fromAscii(outCodec->name())).arg(autodetect)));
	QEQUAL(editor->document()->lineEndingString(),outLineEnding);

	//Save
	editor->document()->setText(editor->document()->text()+"Save test");
	editor->save();
	tf.open();
	QString writtenText=outCodec->toUnicode( tf.readAll());
	tf.close();

	QEQUAL2(writtenText, testTextWithLineEndings+"Save test"+outLineEnding, "file text check, file:"+tfn);
	QVERIFY2(writtenText.contains(outLineEnding), qPrintable("file don't contain right line ending, file"+tfn));
}
#endif
