#ifndef Header_Latex_Parsing_T
#define Header_Latex_Parsing_T

#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"
#include "latexparsing.h"
#include "testutil.h"
#include <QtTest/QtTest>


class LatexParsingTest: public QObject
{
	Q_OBJECT
private slots:
	void test_simpleLexing_data();
	void test_simpleLexing();
	void test_latexLexing_data();
	void test_latexLexing();
	void test_findCommandWithArgsFromTL_data();
	void test_findCommandWithArgsFromTL();
	void test_getArg_data();
	void test_getArg();
	void test_getArg2_data();
	void test_getArg2();
	void test_getTokenAtCol_data();
	void test_getTokenAtCol();
	void test_getCommandFromToken_data();
	void test_getCommandFromToken();
	void test_getContext_data();
	void test_getContext();
	void test_getCompleterContext_data();
	void test_getCompleterContext();
};

#endif  // QT_NO_DEBUG
#endif  // LATEXPARSING_T_H
