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
	QTest::newRow("program with arguments") << "\"my program\" arg1 arg2" << "my program" << (QStringList() << "arg1" << "arg2");
	QTest::newRow("argument with multiple pieces") << "\"my program\" argname='piece1'\"piece2\"" << "my program" << (QStringList() << "argname=piece1piece2");
	QTest::newRow("argument with multiple pieces and whitespace") << "\"my program\" 'piece 1'\"pi ece2\"piece3" << "my program" << (QStringList() << "piece 1pi ece2piece3");
	QTest::newRow("single-quoted argument with double-quote") << "myprogram 'a\"rg1'" << "myprogram" << (QStringList() << "a\"rg1");
	QTest::newRow("double-quoted argument with single-quote") << "myprogram \"a'rg1\"" << "myprogram" << (QStringList() << "a'rg1");
	QTest::newRow("single-quoted argument with escaped single-quote") << "myprogram 'a\\'rg1'" << "myprogram" << (QStringList() << "a'rg1");
	QTest::newRow("double-quoted argument with escaped double-quote") << "myprogram \"a\\\"rg1\"" << "myprogram" << (QStringList() << "a\"rg1");
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
