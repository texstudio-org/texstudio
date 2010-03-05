#ifndef QT_NO_DEBUG
#include "qeditor_t.h"
#include "qeditor.h"
#include "qdocumentline.h"
#include "tests/testutil.h"
#include <QtTest/QtTest>
Q_DECLARE_METATYPE(QList<int>);

QEditorTest::QEditorTest(QEditor* ed, bool executeAllTests):allTests(executeAllTests)
{
	editor=ed;
}
QEditorTest::~QEditorTest(){
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

void QEditorTest::foldedText_data(){
	QTest::addColumn<QString>("editorText");
	QTest::addColumn<QList<int> >("foldAt");
	QTest::addColumn<QList<int> >("hiddenLines");
	QTest::addColumn<int>("froml");
	QTest::addColumn<int>("fromc");
	QTest::addColumn<int>("tol");
	QTest::addColumn<int>("toc");
	QTest::addColumn<QString>("operation");
	QTest::addColumn<QString>("newEditorText");
	QTest::addColumn<QList<int> >("newHiddenLines");

	QTest::newRow("simple folded comment")
		<< "0\n1{\n2abc\n3}\n4\n"
		<<  (QList<int>() << 1)
		<<  (QList<int>() << 2 << 3)
		<< 0 << 1 << 4 << 1
		<< "comment"
		<< "%0\n%1{\n%2abc\n%3}\n%4\n"
		<< (QList<int>());

	QTest::newRow("simple folded uncomment")
		<< "0\n1{\n%2abc\n3}\n4\n"
		<<  (QList<int>() << 1)
		<<  (QList<int>() << 2 << 3)
		<< 0 << 1 << 4 << 1
		<< "uncomment"
		<< "0\n1{\n2abc\n3}\n4\n"
		<< (QList<int>() << 2 << 3);

	QTest::newRow("simple folded indent")
		<< "0\n1{\n2abc\n3}\n4\n"
		<<  (QList<int>() << 1)
		<<  (QList<int>() << 2 << 3)
		<< 0 << 1 << 4 << 1
		<< "indent"
		<< "\t0\n\t1{\n\t2abc\n\t3}\n\t4\n"
		<< (QList<int>() << 2 << 3);

	QTest::newRow("simple folded unindent")
		<< "\t0\n\t1{\n\t2abc\n\t3}\n\t4\n"
		<<  (QList<int>() << 1)
		<<  (QList<int>() << 2 << 3)
		<< 0 << 1 << 4 << 1
		<< "unindent"
		<< "0\n1{\n2abc\n3}\n4\n"
		<< (QList<int>() << 2 << 3);

	QTest::newRow("inner folded uncomment")
		<< "{\n1{\n%2abc\n3}\n4\n5}\n6\n"
		<<  (QList<int>() << 1)
		<<  (QList<int>() << 2 << 3)
		<< 0 << 1 << 5 << 1
		<< "uncomment"
		<< "{\n1{\n2abc\n3}\n4\n5}\n6\n"
		<< (QList<int>() << 2 << 3);

	QTest::newRow("fold block shorting uncomment")
		<< "0\n1{\n%2}\n3}\n4\n"
		<<  (QList<int>() << 1)
		<<  (QList<int>() << 2 << 3)
		<< 0 << 1 << 4 << 1
		<< "uncomment"
		<< "0\n1{\n2}\n3}\n4\n"
		<< (QList<int>() << 2);

	QTest::newRow("fold block larging uncomment")
		<< "0\n1{\n%2{\n3\n4}\n5\n6}\n"
		<<  (QList<int>() << 1)
		<<  (QList<int>() << 2 << 3 << 4)
		<< 0 << 1 << 6 << 1
		<< "uncomment"
		<< "0\n1{\n2{\n3\n4}\n5\n6}\n"
		<< (QList<int>() << 2 << 3 << 4 << 5 << 6);

	QTest::newRow("uncomment single line")
		<< "0\n1{\n%2}\n3}\n4\n"
		<<  (QList<int>() << 1)
		<<  (QList<int>() << 2 << 3)
		<< 0 << 1 << 0 << 1
		<< "uncomment"
		<< "0\n1{\n%2}\n3}\n4\n"
		<< (QList<int>() << 2 << 3);
}
void QEditorTest::foldedText(){
	QFETCH(QString, editorText);
	QFETCH(QList<int>, foldAt);
	QFETCH(QList<int>, hiddenLines);
	QFETCH(int, froml);
	QFETCH(int, fromc);
	QFETCH(int, tol);
	QFETCH(int, toc);
	QFETCH(QString, operation);
	QFETCH(QString, newEditorText);
	QFETCH(QList<int>, newHiddenLines);

	editor->setText(editorText);
	foreach(const int &i, foldAt)
		editor->document()->collapse(i);
	for (int i=0;i<editor->document()->lines();i++)
		QVERIFY2(editor->document()->line(i).isHidden() == hiddenLines.contains(i),qPrintable(QString::number(i)));
	editor->setCursor(editor->document()->cursor(froml,fromc,tol,toc));
	if (operation=="indent") editor->indentSelection();
	else if (operation=="unindent") editor->unindentSelection();
	else if (operation=="comment") editor->commentSelection();
	else if (operation=="uncomment") editor->uncommentSelection();
	else qFatal("invalid operation");
	QEQUAL(editor->document()->text(), newEditorText);
	for (int i=0;i<editor->document()->lines();i++)
		QVERIFY2(editor->document()->line(i).isHidden() == newHiddenLines.contains(i),qPrintable(QString::number(i)));
}

#endif
