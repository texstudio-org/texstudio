#ifndef QT_NO_DEBUG
#include "qeditor_t.h"
#include "qeditor.h"
#include "qdocumentline.h"
#include "testutil.h"
#include "smallUsefulFunctions.h"
#include "qdocument_p.h"
#include <QtTest/QtTest>
Q_DECLARE_METATYPE(QList<int>);

QEditorTest::QEditorTest(QEditor* ed, bool executeAllTests):allTests(executeAllTests)
{
	editor=ed;
	if (editor->getFileCodec()!=0) defaultCodec = editor->getFileCodec();
	else defaultCodec = QTextCodec::codecForName("latin1");
	ed->setFlag(QEditor::HardLineWrap, false);
	ed->setFlag(QEditor::AutoCloseChars, true);
}
QEditorTest::~QEditorTest(){
}

void QEditorTest::setText_data(){
	//reason is to test if the last new line ending is preserved
	QTest::addColumn<QString>("text");
	QTest::newRow("empty") << "";
	QTest::newRow("single word") << "hallo";
	QTest::newRow("single line") << "hallo welt\n";
	QTest::newRow("two lines") << "hallo welt\njipjipiu";
	QTest::newRow("three lines") << "hallo welt\njipjipiu\n";
	QTest::newRow("many lines a") << "hallo welt\njipjipiu\n\n\n\n";
	QTest::newRow("many lines b") << "hallo welt\njipjipiu\n\n\n\nb";
}

void QEditorTest::setText(){
	Q_ASSERT(editor);
	QFETCH(QString, text);
	editor->setText(text, false);
	QString restext = editor->text();
	QEQUAL(restext,text);
}


void QEditorTest::loadSave_data(){
	QTest::addColumn<QString>("outCodecName");
	QTest::addColumn<QString>("outLineEnding");
	QTest::addColumn<bool>("autodetect");
	
	QStringList codings = QStringList() << "latin1" << "utf-8" << "utf-16le" << "utf-16be" << "latin2"; //latin1 is not used
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
	Q_ASSERT(QTextCodec::codecForName("UTF-8")==QTextCodec::codecForMib(MIB_UTF8));
	Q_ASSERT(QTextCodec::codecForName("UTF-16LE")==QTextCodec::codecForMib(MIB_UTF16LE));
	Q_ASSERT(QTextCodec::codecForName("UTF-16BE")==QTextCodec::codecForMib(MIB_UTF16BE));
	Q_ASSERT(QTextCodec::codecForName("ISO-8859-1")==QTextCodec::codecForMib(MIB_LATIN1));

	Q_ASSERT(QTextCodec::codecForMib(MIB_UTF8)->mibEnum() == MIB_UTF8);
	Q_ASSERT(QTextCodec::codecForMib(MIB_UTF16LE)->mibEnum() == MIB_UTF16LE);
	Q_ASSERT(QTextCodec::codecForMib(MIB_UTF16BE)->mibEnum() == MIB_UTF16BE);
	Q_ASSERT(QTextCodec::codecForMib(MIB_LATIN1)->mibEnum() == MIB_LATIN1);
}
//checks if load/saving preserves encoding and line endings
void QEditorTest::loadSave(){
	QFETCH(QString, outCodecName);
	QFETCH(QString, outLineEnding);
	QFETCH(bool, autodetect);
	QTextCodec* outCodec=QTextCodec::codecForName(qPrintable(outCodecName));
	if (outCodecName=="latin1") outCodec = defaultCodec;

	if (!allTests) {
		qDebug("skipped load save test");
		return;
	}

	const QString testText = QString::fromLatin1("hallo\n\xE4\xF6\xFC\n");
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
	editor->document()->setLineEnding(editor->document()->originalLineEnding()); //TODO: find out why this line is only needed iff the editor passed by the testmanager is used and not if a new QEditor(0) is created
    QEQUAL2(editor->document()->text(),testTextWithLineEndings,QString("File: %1  Got file codec: %2 ").arg(tfn).arg(editor->getFileCodec()?QString::fromLatin1(editor->getFileCodec()->name()):"<null>"));
    QVERIFY2(editor->getFileCodec()==outCodec,qPrintable(QString("wrong encoding: got %1 wanted %2 by the sheriff %3").arg(QString::fromLatin1(editor->getFileCodec()->name())).arg(QString::fromLatin1(outCodec->name())).arg(autodetect)));
	QEQUAL(editor->document()->lineEndingString(),outLineEnding);

	//Save
	editor->setText(editor->document()->text()+"Save test", false);
	editor->save();
	tf.open();
	QString writtenText=outCodec->toUnicode( tf.readAll());
	tf.close();

	QEQUAL2(writtenText, testTextWithLineEndings+"Save test", "file text check, file:"+tfn);
	QVERIFY2(writtenText.contains(outLineEnding), qPrintable("file don't contain right line ending, file"+tfn));
	
	editor->setFileName(""); //reset filename so it won't get panically if the file is deleted
	editor->document()->setLineEnding(QDocument::Conservative); //reset line ending so we won't screw up the other tests
}

void compareLists(const QList<int> actual, const QList<int> exp){
	if (actual.length() != exp.length()) {
		QFAIL(qPrintable(QString("length %1 != %2 ").arg(actual.length()).arg(exp.length())));
		return;
	}
	for (int i=0;i<actual.length();i++)
		QEQUAL(actual[i],exp[i]);
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

	QTest::newRow("last section folded commenting")
		<< "\\section{1}\n1\n\\section{2}\n2\n\\section{3}\n3\n\\section{4}\n4\n"
		<< (QList<int>() << 0 << 2 << 4 << 6)
		<< (QList<int>() << 1 << 3 << 5 << 7 << 8)
		<< 6 << 0 << 7 << 1
		<< "comment"
		<< "\\section{1}\n1\n\\section{2}\n2\n\\section{3}\n3\n%\\section{4}\n%4\n"
		<< (QList<int>() << 1 << 3 << 5 << 6 << 7 << 8);

	QTest::newRow("last section folded indent")
		<< "\\section{1}\n1\n\\section{2}\n2\n\\section{3}\n3\n\\section{4}\n4\n"
		<< (QList<int>() << 0 << 2 << 4 << 6)
		<< (QList<int>() << 1 << 3 << 5 << 7 << 8)
		<< 6 << 0 << 7 << 1
		<< "indent"
		<< "\\section{1}\n1\n\\section{2}\n2\n\\section{3}\n3\n\t\\section{4}\n\t4\n"
		<< (QList<int>() << 1 << 3 << 5 << 7 << 8);

	QTest::newRow("last section folded unindent")
		<< "\\section{1}\n1\n\\section{2}\n2\n\\section{3}\n3\n\t\\section{4}\n\t4\n"
		<< (QList<int>() << 0 << 2 << 4 << 6)
		<< (QList<int>() << 1 << 3 << 5 << 7 << 8)
		<< 6 << 0 << 7 << 1
		<< "unindent"
		<< "\\section{1}\n1\n\\section{2}\n2\n\\section{3}\n3\n\\section{4}\n4\n"
		<< (QList<int>() << 1 << 3 << 5 << 7 << 8);
}
//checks if block-commands (e.g indent, comment) work with folded text
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

	editor->setText(editorText, false);
	foreach(const int &i, foldAt)
		editor->document()->collapse(i);
	for (int i=0;i<editor->document()->lines();i++)
		QVERIFY2(editor->document()->line(i).isHidden() == hiddenLines.contains(i),qPrintable(QString::number(i)));
	compareLists(editor->document()->impl()->testGetHiddenLines(), hiddenLines);
	editor->setCursor(editor->document()->cursor(froml,fromc,tol,toc));
	if (operation=="indent") editor->indentSelection();
	else if (operation=="unindent") editor->unindentSelection();
	else if (operation=="comment") editor->commentSelection();
	else if (operation=="uncomment") editor->uncommentSelection();
	else qFatal("invalid operation");
	QEQUAL(editor->document()->text(), newEditorText);
	for (int i=0;i<editor->document()->lines();i++)
		QVERIFY2(editor->document()->line(i).isHidden() == newHiddenLines.contains(i),qPrintable(QString::number(i)));
	compareLists(editor->document()->impl()->testGetHiddenLines(), newHiddenLines);
}


void QEditorTest::passiveFolding_data(){
	QTest::addColumn<QString>("editorText");
	QTest::addColumn<QList<int> >("foldAt");
	QTest::addColumn<QList<int> >("hiddenLines1");
	QTest::addColumn<QList<int> >("unFoldAt");
	QTest::addColumn<QList<int> >("hiddenLines2");
	QTest::addColumn<QList<int> >("foldAtAgain");
	QTest::addColumn<QList<int> >("hiddenLines3");

	QTest::newRow("trivial")
		<< "0\n1{\n2\n3\n4}\n5"
		<< (QList<int>() << 1)
		<< (QList<int>() << 2 << 3 << 4)
		<< (QList<int>() << 1)
		<< (QList<int>())
		<< (QList<int>() << 1)
		<< (QList<int>() << 2 << 3 << 4);

	QTest::newRow("trivial mixed brackets")
		<< "0\n1${[](\n2\n3\n4)\\{\\}}$\n5"
		<< (QList<int>() << 1)
		<< (QList<int>() << 2 << 3 << 4)
		<< (QList<int>() << 1)
		<< (QList<int>())
		<< (QList<int>() << 1)
		<< (QList<int>() << 2 << 3 << 4);

	QTest::newRow("trivial open/close block")
		<< "0\n1{\n2\n3\n4} {\n5\n6}\n"
		<< (QList<int>() << 1 << 4)
		<< (QList<int>() << 2 << 3 << 5 << 6)
		<< (QList<int>() << 4)
		<< (QList<int>() << 2 << 3)
		<< (QList<int>() << 4)
		<< (QList<int>() << 2 << 3 << 5 << 6);

	QTest::newRow("open/close block with weight override")
		<< "0\n1{\n2\n3\n4(} {)\n5\n6}\n"
		<< (QList<int>() << 1 << 4)
		<< (QList<int>() << 2 << 3 << 5 << 6)
		<< (QList<int>() << 4)
		<< (QList<int>() << 2 << 3)
		<< (QList<int>() << 4)
		<< (QList<int>() << 2 << 3 << 5 << 6);

	QTest::newRow("trivial unclosed block")
		<< "0\n1{\n2\n3\n4\n"
		<< (QList<int>() << 1)
		<< (QList<int>() << 2 << 3 << 4 << 5)
		<< (QList<int>() << 1)
		<< (QList<int>())
		<< (QList<int>() << 1)
		<< (QList<int>() << 2 << 3 << 4 << 5);

	QTest::newRow("\\chapter overrides \\section")
		<< "0\n1\\chapter\n2\n3\\section\n4\n5\\section\n6\n7\\chapter\n8\n9\n10\n"
		<< (QList<int>() << 1 << 3)
		<< (QList<int>() << 2 << 3 << 4 << 5 << 6)
		<< (QList<int>() << 1)
		<< (QList<int>() << 4)
		<< (QList<int>() << 7)
		<< (QList<int>() << 4 << 8 << 9 << 10 << 11);

	QTest::newRow("\\section folds until \\chapter")
		<< "0\n1\\chapter\n2\n3\\section\n4\n5\\section\n6\n7\\chapter\n8\n9\n10\n"
		<< (QList<int>() << 5)
		<< (QList<int>() << 6)
		<< (QList<int>())
		<< (QList<int>() << 6)
		<< (QList<int>() << 1)
		<< (QList<int>() << 2 << 3 << 4 << 5 << 6);
}
//checks if collapsing/expanding works
void QEditorTest::passiveFolding(){
	QFETCH(QString, editorText);
	QFETCH(QList<int>, foldAt);
	QFETCH(QList<int>, hiddenLines1);
	QFETCH(QList<int>, unFoldAt);
	QFETCH(QList<int>, hiddenLines2);
	QFETCH(QList<int>, foldAtAgain);
	QFETCH(QList<int>, hiddenLines3);

	editor->setText(editorText, false);

	foreach(const int &i, foldAt)
		editor->document()->collapse(i);
	
	for (int i=0;i<editor->document()->lines();i++)
		QVERIFY2(editor->document()->line(i).isHidden() == hiddenLines1.contains(i),qPrintable(QString::number(i)));

	compareLists(editor->document()->impl()->testGetHiddenLines(), hiddenLines1);
	
	foreach(const int &i, unFoldAt)
		editor->document()->expand(i);
	for (int i=0;i<editor->document()->lines();i++)
		QVERIFY2(editor->document()->line(i).isHidden() == hiddenLines2.contains(i),qPrintable(QString::number(i)));

	compareLists(editor->document()->impl()->testGetHiddenLines(), hiddenLines2);

	foreach(const int &i, foldAtAgain)
		editor->document()->collapse(i);
	for (int i=0;i<editor->document()->lines();i++)
		QVERIFY2(editor->document()->line(i).isHidden() == hiddenLines3.contains(i),qPrintable(QString::number(i)));

	compareLists(editor->document()->impl()->testGetHiddenLines(), hiddenLines3);
}


void QEditorTest::activeFolding_data(){
	QTest::addColumn<QString>("editorText");
	QTest::addColumn<QList<int> >("foldAt");
	QTest::addColumn<QList<int> >("hiddenLines");
	QTest::addColumn<int>("cursorAL");
	QTest::addColumn<int>("cursorAC");
	QTest::addColumn<int>("cursorL");
	QTest::addColumn<int>("cursorC");
	QTest::addColumn<QString>("textToInsert");
	QTest::addColumn<QString>("newEditorText");
	QTest::addColumn<QList<int> >("newHiddenLines");

	QTest::newRow("trivial insertion: shift down")
		<< "0\n1\n2{\n3\n4}\n5\n"
		<< (QList<int> () << 2)
		<< (QList<int> () << 3 << 4)
		<< 1 << 1 << 1 << 1
		<< "insert\nnew line"
		<< "0\n1insert\nnew line\n2{\n3\n4}\n5\n"
		<< (QList<int> () << 4 << 5);

	QTest::newRow("trivial insertion: shift up")
		<< "0\n1\n2{\n3\n4}\n5\n"
		<< (QList<int> () << 2)
		<< (QList<int> () << 3 << 4)
		<< 0 << 0 << 1 << 1
		<< "remove line"
		<< "remove line\n2{\n3\n4}\n5\n"
		<< (QList<int> () << 2 << 3);

	QTest::newRow("comment opened folding")
		<< "0\n1\n2{\n3\n4}\n5\n"
		<< (QList<int> () << 2)
		<< (QList<int> () << 3 << 4)
		<< 2 << 1 << 2 << 1
		<< "%"
		<< "0\n1\n2%{\n3\n4}\n5\n"
		<< (QList<int> ());

	QTest::newRow("comment opened folding partially")
		<< "0\n1\n2{{{()}\n3\n4{\n5}\n6}\n7}\n"
		<< (QList<int> () << 2 << 4)
		<< (QList<int> () << 3 << 4 << 5 << 6 << 7)
		<< 2 << 1 << 2 << 1
		<< "%"
		<< "0\n1\n2%{{{()}\n3\n4{\n5}\n6}\n7}\n"
		<< (QList<int> () << 5);

	QTest::newRow("comment merges blocks")
		<< "0\n1\n2{\n3\n4} {\n5\n6}\n"
		<< (QList<int> () << 2 << 4)
		<< (QList<int> () << 3 << 5 << 6)
		<< 4 << 1 << 4 << 1
		<< "%"
		<< "0\n1\n2{\n3\n4%} {\n5\n6}\n"
		<< (QList<int> () << 3 << 4 << 5 << 6);

	QTest::newRow("comment enlarge block")
		<< "0\n1\n2{\n3\n4}\n5\n"
		<< (QList<int> () << 2)
		<< (QList<int> () << 3 << 4)
		<< 4 << 1 << 4 << 1
		<< "%"
		<< "0\n1\n2{\n3\n4%}\n5\n"
		<< (QList<int> () << 3 << 4 << 5 << 6);

	QTest::newRow("line removing block merging")
		<< "0\n1\n2{\n3\n4}\n5\n6{\n7\n8}\n"
		<< (QList<int> () << 2 << 6)
		<< (QList<int> () << 3 << 4 << 7 << 8)
		<< 4 << 2 << 5 << 1
		<< " "
		<< "0\n1\n2{\n3\n4} \n6{\n7\n8}\n"
		<< (QList<int> () << 3 << 4 << 6 << 7);

	QTest::newRow("block override")
		<< "0\n1$\n2{\n3\n4\n5}\n6\n"
		<< (QList<int> () << 2 )
		<< (QList<int> () << 3 << 4 << 5)
		<< 4 << 1 << 4 << 1
		<< "$"
		<< "0\n1$\n2{\n3\n4$\n5}\n6\n"
		<< (QList<int> () << 3);
	
	QTest::newRow("multi line deletion")
	              << "0\n1{\n2abc\n3}\n4\n"
	              << (QList<int>() << 1)
	              << (QList<int>() << 2 << 3)
	              << 1 << 0 << 4 << 0
	              << "x"
	              << "0\nx4\n"
	              << (QList<int>());

	
	QTest::newRow("latex test") 
	       << "\\begin{document}\n\n\\subsection{Bilder}\n\n\\subsection{end}\n\n\\end{document}"
	       << (QList<int>() << 2)
	       << (QList<int>() << 3)
	       << 1 << 0 << 5 << 0
	       << "x"
	       << "\\begin{document}\nx\n\\end{document}"
	       << (QList<int>());
		
}
//tests if folded text can be edited
void QEditorTest::activeFolding(){
	QFETCH(QString, editorText);
	QFETCH(QList<int>, foldAt);
	QFETCH(QList<int>, hiddenLines);
	QFETCH(int, cursorAL);
	QFETCH(int, cursorAC);
	QFETCH(int, cursorL);
	QFETCH(int, cursorC);
	QFETCH(QString, textToInsert);
	QFETCH(QString, newEditorText);
	QFETCH(QList<int>, newHiddenLines);

	editor->setText(editorText, false);

	foreach(const int &i, foldAt)
		editor->document()->collapse(i);
	for (int i=0;i<editor->document()->lines();i++)
		QVERIFY2(editor->document()->line(i).isHidden() == hiddenLines.contains(i),qPrintable(QString::number(i)));
	compareLists(editor->document()->impl()->testGetHiddenLines(), hiddenLines);

	QDocumentCursor editCursor = editor->document()->cursor(cursorAL,cursorAC,cursorL,cursorC);
	editCursor.insertText(textToInsert);

	QEQUAL(editor->document()->text(), newEditorText);
	for (int i=0;i<editor->document()->lines();i++)
		QVERIFY2(editor->document()->line(i).isHidden() == newHiddenLines.contains(i),qPrintable(QString::number(i)));

	compareLists(editor->document()->impl()->testGetHiddenLines(), newHiddenLines);
}

void QEditorTest::indentation_data(){
	editor->setFlag(QEditor::AutoIndent,true);
	editor->setFlag(QEditor::ReplaceTabs,false);

	QTest::addColumn<QString>("baseText");
	QTest::addColumn<bool>("weak");
	QTest::addColumn<int>("line");
	QTest::addColumn<int>("col");
	QTest::addColumn<int>("anchorLine");
	QTest::addColumn<int>("anchorCol");
	QTest::addColumn<QString>("insert");
	QTest::addColumn<QString>("result");

	QTest::newRow("trivial")
		<< "hello\nworld\n"
		<< false << 0 << 5 << -1 << -1
		<< "{\na\n}"
		<< "hello{\n\ta\n}\nworld\n";

	QTest::newRow("trivial weak")
		<< "hello\nworld\n"
		<< true << 0 << 5 << -1 << -1
		<< "{\na\n}"
		<< "hello{\na\n}\nworld\n";

	QTest::newRow("trivial + \\t indentation")
		<< "\thello\nworld\n"
		<< false << 0 << 6 << -1 << -1
		<< "{\na\n}"
		<< "\thello{\n\t\ta\n\t}\nworld\n";

	QTest::newRow("trivial + \\t indentation weak")
		<< "\thello\nworld\n"
		<< true << 0 << 6 << -1 << -1
		<< "{\na\n}"
		<< "\thello{\n\ta\n\t}\nworld\n";

	QTest::newRow("trivial + space indentation")
		<< "   hello\nworld\n"
		<< false << 0 << 8 << -1 << -1
		<< "{\na\n}"
		<< "   hello{\n   \ta\n   }\nworld\n";

	QTest::newRow("trivial + space indentation weak")
		<< "   hello\nworld\n"
		<< true << 0 << 8 << -1 << -1
		<< "{\na\n}"
		<< "   hello{\n   a\n   }\nworld\n";

	QTest::newRow("trivial + \\t indentation")
		<< "\thello\nworld\n"
		<< false << 0 << 6 << -1 << -1
		<< "{\na\n}"
		<< "\thello{\n\t\ta\n\t}\nworld\n";

	QTest::newRow("space test")
		<< "   \nworld\n"
		<< false << 0 << 2 << -1 << -1
		<< "\n"
		<< "  \n   \nworld\n";

	QTest::newRow("space test + weak")
		<< "   \nworld\n"
		<< true << 0 << 2 << -1 << -1
		<< "\n"
		<< "  \n   \nworld\n";

	QTest::newRow("space test + weak")
		<< "   \nworld\n"
		<< true << 0 << 2 << -1 << -1
		<< "\n"
		<< "  \n   \nworld\n";

	QTest::newRow("block indentation")
		<< "   hello\nworld\n"
		<< true << 0 << 6 << -1 << -1
		<< "  x\n y\n  z"
		<< "   hel  x\n    y\n     zlo\nworld\n";

	QTest::newRow("block indentation")
		<< "   hello\nworld\n"
		<< true << 0 << 6 << -1 << -1
		<< "  \\begin{abc}\n    abcdef\n  \\end{abc}"
		<< "   hel  \\begin{abc}\n       abcdef\n     \\end{abc}lo\nworld\n";

	QTest::newRow("block indentation + 3 space")
		<< "   hello\nworld\n"
		<< false << 0 << 6 << -1 << -1
		<< "  \\begin{abc}\n             abcdef\n  \\end{abc}"
		<< "   hel  \\begin{abc}\n   \tabcdef\n   \\end{abc}lo\nworld\n";

	QTest::newRow("block indentation + 4 space")
		<< "    hello\nworld\n"
		<< false << 0 << 7 << -1 << -1
		<< " \\begin{abc}\n             abcdef\n               \\end{abc}"
		<< "    hel \\begin{abc}\n    \tabcdef\n    \\end{abc}lo\nworld\n";

	QTest::newRow("block indentation + tabs")
		<< "\thello\nworld\n"
		<< true << 0 << 4 << -1 << -1
		<< "\t\\begin{abc}\n\t\tabcdef\n\t\\end{abc}"
		<< "\thel\t\\begin{abc}\n\t\t\tabcdef\n\t\t\\end{abc}lo\nworld\n";

	QTest::newRow("block indentation + tabs simple")
		<< "hello\nworld\n"
		<< true << 0 << 3 << -1 << -1
		<< "\t\\begin{abc}\n\t\tabcdef\n\t\\end{abc}"
		<< "hel\t\\begin{abc}\n\t\tabcdef\n\t\\end{abc}lo\nworld\n";

	QTest::newRow("multi unindent with closing brackets after text")
		<< "hello\nworld\n"
		<< false << 0 << 5 << -1 << -1
		<< "{{\na\nxx}}\nabc"
		<< "hello{{\n\t\ta\n\t\txx}}\nabc\nworld\n"; //only unindent the next line

	QTest::newRow("multi unindent with closing brackets after text with pre indentation")
		<< " hello\n world\n"
		<< false << 0 << 6 << -1 << -1
		<< "{{\na\nxx}}\nabc"
		<< " hello{{\n \t\ta\n \t\txx}}\n abc\n world\n"; 

	QTest::newRow("no immediate unindent with closing bracket after text")
		<< "\t\thello\n\t\tworld\n"
		<< false << 0 << 7 << -1 << -1
		<< "}}"
		<< "\t\thello}}\n\t\tworld\n"; //no prapagation yet

	QTest::newRow("selection block self replacement (line start) weak")
			<< "\tAA\n\tBB\n\tCC\n"
			<< true << 2 << 0 << 1 << 0
			<< "\tBB\n"
			<< "\tAA\n\tBB\n\tCC\n";
	QTest::newRow("selection block self replacement (line start)")
			<< "\tAA\n\tBB\n\tCC\n"
			<< false << 2 << 0 << 1 << 0
			<< "\tBB\n"
			<< "\tAA\n\tBB\n\tCC\n";
	QTest::newRow("reversed selection block self replacement (line start) weak")
			<< "\tAA\n\tBB\n\tCC\n"
			<< true << 1 << 0 << 2 << 0
			<< "\tBB\n"
			<< "\tAA\n\tBB\n\tCC\n";
	QTest::newRow("reversed selection block self replacement (line start)")
			<< "\tAA\n\tBB\n\tCC\n"
			<< false << 1 << 0 << 2 << 0
			<< "\tBB\n"
			<< "\tAA\n\tBB\n\tCC\n";
	QTest::newRow("selection block self replacement (text start) weak")
			<< "\tAA\n\tBB\n\tCC\n"
			<< true << 2 << 1 << 1 << 1
			<< "\tBB\n"
			<< "\tAA\n\tBB\n\tCC\n";
	QTest::newRow("selection block self replacement (text start)")
			<< "\tAA\n\tBB\n\tCC\n"
			<< false << 2 << 1 << 1 << 1
			<< "\tBB\n"
			<< "\tAA\n\tBB\n\tCC\n";
	QTest::newRow("reversed selection block self replacement (text start) weak")
			<< "\tAA\n\tBB\n\tCC\n"
			<< true << 1 << 1 << 2 << 1
			<< "\tBB\n"
			<< "\tAA\n\tBB\n\tCC\n";
	QTest::newRow("reversed selection block self replacement (text start)")
			<< "\tAA\n\tBB\n\tCC\n"
			<< false << 1 << 1 << 2 << 1
			<< "\tBB\n"
			<< "\tAA\n\tBB\n\tCC\n";

	/*
  this is broken:
	QTest::newRow("trivial 2")
		<< "hello\nworld\n"
		<< false << 0 << 5
		<< "{{\na\n}}"
		<< "hello{{\n\t\ta\n}}\nworld\n";
*/

}
void QEditorTest::indentation(){
	QFETCH(QString, baseText);
	QFETCH(bool, weak);
	QFETCH(int, line);
	QFETCH(int, col);
	QFETCH(int, anchorLine);
	QFETCH(int, anchorCol);
	QFETCH(QString, insert);
	QFETCH(QString,	result);

	editor->setFlag(QEditor::WeakIndent, weak);

	editor->setText(baseText, false);
	QDocumentCursor c=editor->document()->cursor(line,col,anchorLine,anchorCol);
	editor->insertText(c, insert);
	QEQUAL(editor->document()->text(), result);
}

void QEditorTest::autoClosing_data(){
	editor->setFlag(QEditor::AutoIndent,true);
	//editor->setFlag(QEditor::WeakIndent,false);
	editor->setFlag(QEditor::ReplaceTabs,false);

	QTest::addColumn<QString>("baseText");
	QTest::addColumn<int>("line");
	QTest::addColumn<int>("col");
	QTest::addColumn<QString>("insert");
	QTest::addColumn<QString>("result");

	QTest::newRow("-(-") << "><" << 0 << 1 << "(" << ">()<";
	QTest::newRow("-)-") << "><" << 0 << 1 << ")" << ">)<";
	QTest::newRow("-{-") << "><" << 0 << 1 << "{" << ">{}<";
	QTest::newRow("-$-") << "><" << 0 << 1 << "$" << ">$<"; //this tests the absence of a feature
	QTest::newRow("-\\begin{verbatim}-") << "><" << 0 << 1 << "\\begin{verbatim}" << ">\\begin{verbatim}<"; //too
	QTest::newRow("existing )") << ">)<" << 0 << 1 << "(" << ">()<";
	QTest::newRow("existing 2-)") << ">))<" << 0 << 1 << "(" << ">())<";
	//QTest::newRow("only last") << "><" << 0 << 1 << "((" << ">(()<"; disabled to prevent clipboard completion
	QTest::newRow("only last") << "><" << 0 << 1 << "((" << ">((<"; //disabled to prevent clipboard completion
	QTest::newRow("counting 1") << ">())<" << 0 << 1 << "(" << ">(())<";
	QTest::newRow("counting 2") << ">((())))<" << 0 << 1 << "(" << ">(((())))<";
	QTest::newRow("counting 3") << ">((()()))())<" << 0 << 1 << "(" << ">(((()()))())<";
	QTest::newRow("multi line search") << ">\n\n\\]<" << 0 << 1 << "\\[" << ">\\[\n\n\\]<";
	QTest::newRow("mixed") << ">[{}])<" << 0 << 1 << "(" << ">([{}])<";
//	QTest::newRow("mixed") << ">([{}]))<" << 0 << 2 << "(" << ">(([{}]))<";
	QTest::newRow("mixed") << ">([{}]))<" << 0 << 2 << "(" << ">(()[{}]))<"; //TODO: THIS IS A BUG!
	QTest::newRow("mixed") << ">({[]}))<" << 0 << 2 << "(" << ">((){[]}))<";//TODO: THIS IS A BUG!
	QTest::newRow("many") << "(((((())))))" << 0 << 1 << "(" << "((((((())))))";
}

void QEditorTest::autoClosing(){
	QFETCH(QString, baseText);
	QFETCH(int, line);
	QFETCH(int, col);
	QFETCH(QString, insert);
	QFETCH(QString, result);

	editor->cutBuffer.clear(); // need to start from a clean state (other tests may have put something there)
	editor->setText(baseText, false);
	QDocumentCursor c=editor->document()->cursor(line,col);
	editor->insertText(c, insert);
	QEQUAL(editor->document()->text(), result);
}

#endif

