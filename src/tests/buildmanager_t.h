#ifndef Header_Build_Manager_T
#define Header_Build_Manager_T
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
	void replaceEnvironmentVariables_data() {
		QTest::addColumn<QString>("command");
		QTest::addColumn<QString>("result");
		QTest::newRow("no variables") << "foo bar baz" << "foo bar baz";
		QTest::newRow("TXSpercent1") << "foo %" << "foo %";
		QTest::newRow("TXSpercent2") << "foo % to %" << "foo % to %";
#ifdef Q_OS_WIN
		QTest::newRow("caseinsens1") << "foo %lowercase% bar" << "foo result/lower bar";
		QTest::newRow("caseinsens2") << "foo %loweRCase% bar" << "foo result/lower bar";
		QTest::newRow("caseinsene3") << "foo %mIXEdcase% bar" << "foo result/mixed bar";
		QTest::newRow("underscore") << "foo %with_underscore% bar" << "foo result/underscore bar";
		QTest::newRow("number") << "foo %number99%" << "foo 99 bars";
		QTest::newRow("nonexistentVariable") << "foo %bar% baz" << "foo  baz";
		QTest::newRow("multiple") << "%lowercase%%mixedcase% %with_underscore%" << "result/lowerresult/mixed result/underscore";
#endif
	}
	void replaceEnvironmentVariables() {
		QFETCH(QString, command);
		QFETCH(QString, result);
		QHash<QString, QString> variables;
		variables.insert("lowercase", "result/lower");
		variables.insert("miXedCase", "result/mixed");
		variables.insert("with_underscore", "result/underscore");
		variables.insert("number99", "99 bars");
#ifdef Q_OS_WIN
		QHash<QString, QString> upperVariables;
		foreach (const QString &name, variables.keys()) {
			upperVariables.insert(name.toUpper(), variables.value(name));
		}
		QEQUAL(BuildManager::replaceEnvironmentVariables(command, upperVariables, true), result);
#else
		QEQUAL(BuildManager::replaceEnvironmentVariables(command, variables, false), result);
#endif
	}

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
				<< QString(":/somewhere/something/~:/somewhere/something/test~:/somewhere/something/test.tex~").replace("/",QDir::separator());
		QTest::newRow("placeholder end") << "?m.newExt##?m)##?m\"##?m ##?e)" << "rel.tex" << "!none" << 0
				<< "rel.newExt##rel##\"rel\"##rel ##tex";
		QTest::newRow("truncated placeholder") << "?m" << "inserted.here" << "!none" << 0 << "inserted";

		QTest::newRow("relative current file") << "?me)-?c:me)-?c:e)-?e)+?m.tex+?c:m.tex" << "main.mfile" << "current.cfile" << 0
				<< "main.mfile-current.cfile-cfile-mfile+main.tex+current.tex";
		QTest::newRow("absolute current file") << "?ame)?c:ame)?c:a)?c:am.tex?c:a" << ":/somewhere/mainfile.m" << ":/elsewhere/include/current.c" << 0
				<< QString(":/somewhere/mainfile.m:/elsewhere/include/current.c:/elsewhere/include/:/elsewhere/include/current.tex:/elsewhere/include/").replace("/",QDir::separator());

		QTest::newRow("search for non-existent output files") << "?p{dvi}:ame ?p{abc}:me ?p{def}:a" << "/somewhere/mainfile.m" << "/elsewhere/include/current.c" << 0
				<< QString("/somewhere/mainfile.dvi mainfile.abc /somewhere/").replace("/",QDir::separator());
		// TODO: Add search for existing output files
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
        QFileInfo fi{file};
        ExpandingOptions options(fi,fi,42);
		ExpandedCommands result = bm->expandCommandLine(commandLine, options);
		QEQUAL(result.commands.size(), expectedcommands.size());
		for (int i=0;i<expectedcommands.size();i++)
			QEQUAL(result.commands[i].command, expectedcommands[i]);
	}
	void splitOptions_data() {
		QTest::addColumn<QString>("line");
		QTest::addColumn<QStringList>("expectedOptions");

		QTest::newRow("empty") << "" << QStringList();
		QTest::newRow("spaces") << " " << QStringList();
		QTest::newRow("simple") << "cmd" << (QStringList() << "cmd");
		QTest::newRow("simple2") << " cmd" << (QStringList() << "cmd");
		QTest::newRow("simple3") << "cmd " << (QStringList() << "cmd");
		QTest::newRow("option") << "cmd --arg" << (QStringList() << "cmd" << "--arg");
		QTest::newRow("option2") << "cmd   --arg" << (QStringList() << "cmd" << "--arg");
		QTest::newRow("option3") << "cmd --arg " << (QStringList() << "cmd" << "--arg");
		QTest::newRow("quoted") << "cmd \"arg with space\"" << (QStringList() << "cmd" << "arg with space");
		QTest::newRow("quoted2")<< "cmd \"arg with space\" --other" << (QStringList() << "cmd" << "arg with space" << "--other");
		QTest::newRow("quotedQuote")<< "cmd \"arg \\\"with space\" --other" << (QStringList() << "cmd" << "arg \"with space" << "--other");
	}
	void splitOptions() {
		QFETCH(QString, line);
		QFETCH(QStringList, expectedOptions);
		QEQUAL(BuildManager::splitOptions(line).join("|"), expectedOptions.join("|"));
	}
	void extractOutputRedirection_data() {
		QTest::addColumn<QString>("commandLine");
		QTest::addColumn<QString>("expectedRemainder");
		QTest::addColumn<QString>("expectedStdOut");
		QTest::addColumn<QString>("expectedStdErr");

		QTest::newRow("pure")               << "pdflatex foo"                      << "pdflatex foo" << "" << "";
		QTest::newRow("redirStdOut")        << "pdflatex foo > foo.txt"            << "pdflatex foo" << "foo.txt" << "";
		QTest::newRow("redirStdOutNoSpace") << "pdflatex foo>foo.txt"              << "pdflatex foo" << "foo.txt" << "";
		QTest::newRow("redirStdErr")        << "pdflatex foo 2> foo.txt"           << "pdflatex foo" << "" << "foo.txt";
		QTest::newRow("redirStdErrNoSpace") << "pdflatex foo >foo.txt"             << "pdflatex foo" << "foo.txt" << "";
		QTest::newRow("redirStdOutStdErr")  << "pdflatex foo 2>&1 >/dev/null"      << "pdflatex foo" << "/dev/null" << "&1";
		QTest::newRow("ignoreExtra1")       << "pdflatex foo >/dev/null bar"       << "pdflatex foo" << "/dev/null" << "";
		QTest::newRow("ignoreExtra2")       << "pdflatex foo 2>/dev/null bar"      << "pdflatex foo" << "" << "/dev/null";
		QTest::newRow("ignoreExtra3")       << "pdflatex foo > /dev/null 2>&1 bar" << "pdflatex foo" << "/dev/null" << "&1";
	}
	void extractOutputRedirection() {
		QFETCH(QString, commandLine);
		QFETCH(QString, expectedRemainder);
		QFETCH(QString, expectedStdOut);
		QFETCH(QString, expectedStdErr);
		QString stdOut, stdErr;
		QString remainder = BuildManager::extractOutputRedirection(commandLine, stdOut, stdErr);
		QEQUAL(remainder, expectedRemainder);
		QEQUAL(stdOut, expectedStdOut);
		QEQUAL(stdErr, expectedStdErr);
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
