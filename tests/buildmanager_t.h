#ifndef BUILDMANAGER_T_H
#define BUILDMANAGER_T_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "buildmanager.h"
#include <QtTest/QtTest>
#include "testutil.h"

class BuildManagerTest: public QObject{
	Q_OBJECT
public:
	BuildManagerTest(BuildManager* bm): bm(bm){
		connect(bm, SIGNAL(commandLineRequested(QString,QString*)), SLOT(commandLineRequested(QString,QString*)));
	}
private slots:
	void parseExtendedCommandLine_data(){ 
		QTest::addColumn<QString >("str");
		QTest::addColumn<QString >("fileName");
		QTest::addColumn<QString >("fileName2");
		QTest::addColumn<int >("line");
		QTest::addColumn<QString >("expected");
		
		QTest::newRow("basic meta") << "@-@@ %% ?? @" << "" << "!none" << 17 << "17-@ % ? 17";
		QTest::newRow("relative file") << "%#?m)#?me)#?m.pdf:42!" << "pseudo.tex" << "!none" << 42  
				<< "\"pseudo\"#pseudo#pseudo.tex#pseudo.pdf:42!";
		//use resource path so no drive letter will be inserted on windows 
		QTest::newRow("absolute file") << "?a)~?am)~?ame)~" << ":/somewhere/something/test.tex" << "!none" << 0 
				<< QString(":/somewhere/something/~:/somewhere/something/test~:/somewhere/something/test.tex~").replace("/",QDir::separator());;
		QTest::newRow("placeholder end") << "?m.newExt##?m)##?m\"##?m ##?e)" << "rel.tex" << "!none" << 0 
				<< "rel.newExt##rel##\"rel\"##rel ##tex";
		QTest::newRow("truncated placeholder") << "?m" << "inserted.here" << "!none" << 0 << "inserted";
		
		QTest::newRow("relative current file") << "?me)-?c:me)-?c:e)-?e)+?m.tex+?c:m.tex" << "main.mfile" << "current.cfile" << 0 
				<< "main.mfile-current.cfile-cfile-mfile+main.tex+current.tex";
		QTest::newRow("absolute current file") << "?ame)?c:ame)?c:a)?c:am.tex?c:a" << ":/somewhere/mainfile.m" << ":/elsewhere/include/current.c" << 0
				<< QString(":/somewhere/mainfile.m:/elsewhere/include/current.c:/elsewhere/include/:/elsewhere/include/current.tex:/elsewhere/include/").replace("/",QDir::separator());;		
	}
	void parseExtendedCommandLine(){ 
		QFETCH(QString, str);
		QFETCH(QString, fileName);
		QFileInfo file(fileName);
		QFETCH(QString, fileName2);		
		QFileInfo file2;
		if (fileName2!="!none") 
			file2=QFileInfo(fileName2);
		QFETCH(int, line);
		QFETCH(QString, expected);
		QString real;
		real=BuildManager::parseExtendedCommandLine(str,file,file2,line).first();
		QVERIFY2(real==expected, QString("result wrong: got %1 expected %2").arg(real).arg(expected).toLatin1().constData());
	}
	void expandCommandLine_data(){
		QTest::addColumn<QString >("commandLine");
		QTest::addColumn<QString >("file");
		QTest::addColumn<QString >("expected");

		QTest::newRow("simple") << "txs:///mocka" << "" << "coffee";
		QTest::newRow("append options 1") << "txs:///mocka -abc" << "" << "coffee  -abc";
		QTest::newRow("append options 2") << "txs:///mocka   -abc" << "" << "coffee    -abc";
		QTest::newRow("append options 3") << "txs:///mocka   -abc  -def" << "" << "coffee    -abc  -def";
		QTest::newRow("expand 1") << "txs:///mockab" << "" << "coffee|foobar -test -xyz -maus=haus --maus=laus -abc -maus=\"test test test\" end";
		QTest::newRow("expand 2") << "txs:///mockac" << "" << "coffee|test -xyz -quadrat .abc";
		QTest::newRow("expand 3") << "txs:///mockac" << "/tmp/testfile.tex" << "coffee|test -xyz -quadrat testfile.abc";
		QTest::newRow("expand 4") << "txs:///mockabc" << "/tmp/testfile.tex" << "coffee|foobar -test -xyz -maus=haus --maus=laus -abc -maus=\"test test test\" end|test -xyz -quadrat testfile.abc";
		QTest::newRow("expand 5") << "txs:///mockab-c" << "/tmp/testfile.tex" << "coffee|foobar -test -xyz -maus=haus --maus=laus -abc -maus=\"test test test\" end|test -xyz -quadrat testfile.abc";
		QTest::newRow("cmd insert 1") << "txs:///mocka/[-abc][-def][-ghi]" << "" << "coffee -abc -def -ghi";
		QTest::newRow("cmd insert existing") << "txs:///mockc/[-xyz][-abc]" << "" << "test -abc -xyz -quadrat .abc";
		QTest::newRow("cmd insert replacing") << "txs:///mockb/[-maus=zimzim][-abc]" << "" << "foobar -test -xyz -maus=zimzim  -abc  end";
		QTest::newRow("cmd remove all") << "txs:///mockb/{}" << "" << "foobar";
		QTest::newRow("cmd remove abc") << "txs:///mockb/{-abc}" << "" << "foobar -test -xyz -maus=haus --maus=laus  -maus=\"test test test\" end";
		QTest::newRow("cmd remove abcmaus") << "txs:///mockb/{-abc}{-maus}" << "" << "foobar -test -xyz     end";
		QTest::newRow("cmd remove insert abcmaus") << "txs:///mockb/{-abc}{-maus}[-triple]" << "" << "foobar -triple -test -xyz     end";
		QTest::newRow("realworld pdf1") << "txs:///mock-pdflatex/[-synctex=0]{-shell-escape}" << "" << "pdflatex -interaction=nonstopmode -src -synctex=0  --src-specials   \"\".tex";
		QTest::newRow("realworld pdf2") << "txs:///mock-pdflatex/{-synctex}" << "" << "pdflatex -interaction=nonstopmode -src   --src-specials -shell-escape  \"\".tex";
		QTest::newRow("cmd remove all") << "txs:///mockabc/{}" << "" << "coffee|foobar|test";
		QTest::newRow("cmd remove all 2") << "txs:///mockab-c/{}" << "" << "coffee|foobar|test";
		QTest::newRow("cmd remove most") << "txs:///mockab-c/{-xyz}{-maus}" << "" << "coffee|foobar -test    -abc  end|test  -quadrat .abc";
		QTest::newRow("cmd remove insert most") << "txs:///mockab-c/{-xyz}[-maus=SUAM]{-abc}" << "" << "coffee -maus=SUAM|foobar -test  -maus=SUAM    end|test -maus=SUAM  -quadrat .abc";
	}
	void expandCommandLine(){
		QFETCH(QString, commandLine);
		QFETCH(QString, file);
		QFETCH(QString, expected);
		QStringList expectedcommands = expected.split("|");
		ExpandingOptions options(file,file,42);
		ExpandedCommands result = bm->expandCommandLine(commandLine, options);
		QEQUAL(result.commands.size(), expectedcommands.size());
		for (int i=0;i<expectedcommands.size();i++)
			QEQUAL(result.commands[i].command, expectedcommands[i]);
	}
public slots:
	void commandLineRequested(const QString& cmdId, QString* result){
		if (cmdId == "mocka") *result = "coffee";
		else if (cmdId == "mockb") *result = "foobar -test -xyz -maus=haus --maus=laus -abc -maus=\"test test test\" end";
		else if (cmdId == "mockc") *result = "test -xyz -quadrat ?m.abc";
		else if (cmdId == "mockab") *result = "txs:///mocka | txs:///mockb";
		else if (cmdId == "mockac") *result = "txs:///mocka | txs:///mockc";
		else if (cmdId == "mockbc") *result = "txs:///mockb | txs:///mockc";
		else if (cmdId == "mockabc") *result = "txs:///mocka | txs:///mockb | txs:///mockc";
		else if (cmdId == "mockab-c") *result = "txs:///mockab | txs:///mockc";
		else if (cmdId == "mock-pdflatex") *result = "pdflatex -interaction=nonstopmode -src -synctex=1  --src-specials -shell-escape  %.tex ";
	}

private:
	BuildManager *bm;
};
#endif
#endif
