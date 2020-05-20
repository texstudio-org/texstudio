#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"

#include "execprogram.h"
#include "execprogram_t.h"
#include "testutil.h"
#include <QtTest/QtTest>

void ExecProgramTest::commandLineParser_data(void)
{
	QTest::addColumn<QString>("commandLine");
	QTest::addColumn<QString>("program");
	QTest::addColumn<QStringList>("arguments");

	QTest::newRow("empty") << "" << "" << QStringList();
	QTest::newRow("only program") << "myprogram" << "myprogram" << QStringList();
	QTest::newRow("single-quoted program with space") << "'my program'" << "my program" << QStringList();
	QTest::newRow("double-quoted program with space") << "\"my program\"" << "my program" << QStringList();
	QTest::newRow("program with internal single-quotes") << "/path/to/m'y prog'ram" << "/path/to/my program" << QStringList();
	QTest::newRow("program with internal double-quotes") << "/path/to/m\"y prog\"ram" << "/path/to/my program" << QStringList();
	QTest::newRow("multiple arguments") << "myprogram arg1 arg2 arg3" << "myprogram" << (QStringList() << "arg1" << "arg2" << "arg3");
	QTest::newRow("argument with single-quoted whitespace") << "myprogram 'abc def' ghi" << "myprogram" << (QStringList() << "abc def" << "ghi");
	QTest::newRow("argument with double-quoted whitespace") << "myprogram \"abc def\" ghi" << "myprogram" << (QStringList() << "abc def" << "ghi");
	QTest::newRow("argument with adjacent quotes 1") << "myprogram ab\"cd\"\"ef\"ghi" << "myprogram" << (QStringList() << "abcdefghi");
	QTest::newRow("argument with adjacent quotes 2") << "myprogram ab\"cd\"'ef'ghi" << "myprogram" << (QStringList() << "abcdefghi");
	QTest::newRow("argument with adjacent quotes 3") << "myprogram ab'cd'\"ef\"ghi" << "myprogram" << (QStringList() << "abcdefghi");
	QTest::newRow("argument with adjacent quotes 4") << "myprogram ab'cd''ef'ghi" << "myprogram" << (QStringList() << "abcdefghi");
	QTest::newRow("double quote inside single quotes") << "myprogram a'b\"cde'f" << "myprogram" << (QStringList() << "abcdef");
	QTest::newRow("single quote inside double quotes") << "myprogram a\"b'cde\"f" << "myprogram" << (QStringList() << "abcdef");
	QTest::newRow("unbalanced single quote") << "myprogram abc de'f ghi" << "myprogram" << (QStringList() << "abc" << "def" << "ghi");
	QTest::newRow("unbalanced double quote") << "myprogram abc de\"f ghi" << "myprogram" << (QStringList() << "abc" << "def" << "ghi");
}

void ExecProgramTest::commandLineParser(void)
{
	QFETCH(QString, commandLine);
	QFETCH(QString, program);
	QFETCH(QStringList, arguments);

	ExecProgram execProgram(commandLine, "");

	QEQUAL(execProgram.m_program, program);
	QEQUALLIST(execProgram.m_arguments, arguments);
}

#endif // QT_NO_DEBUG
