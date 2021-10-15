#ifndef Header_SmallUsefulFunctions_T
#define Header_SmallUsefulFunctions_T
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"
#include "smallUsefulFunctions.h"
#include "testutil.h"
#include <QtTest/QtTest>

class SmallUsefulFunctionsTest: public QObject
{
	Q_OBJECT
private slots:
	void test_getCommand_data();
	void test_getCommand();
	void test_trimLeft_data();
	void test_trimLeft();
	void test_trimRight_data();
	void test_trimRight();
	void test_latexToText_data();
	void test_latexToText();
	void test_joinLinesExceptCommentsAndEmptyLines_data();
	void test_joinLinesExceptCommentsAndEmptyLines();
	void test_splitLines_data();
	void test_splitLines();
	void test_tokenizeCommandLine_data();
	void test_tokenizeCommandLine();
	void test_extractOutputRedirection_data();
	void test_extractOutputRedirection();
	void test_enquoteDequoteString_data();
	void test_enquoteDequoteString();
	void test_joinUnicodeSurrogate_data();
	void test_joinUnicodeSurrogate();
	void test_replaceFileExtension_data();
	void test_replaceFileExtension();
	void test_getParamItem_data();
	void test_getParamItem();
	void test_addMostRecent_data();
	void test_addMostRecent();
	void test_indicesOf_data();
	void test_indicesOf();
	void test_indicesOf_RegExp_data();
	void test_indicesOf_RegExp();
	void test_indexMin_data();
	void test_indexMin();
    void test_textToLatex_data();
    void test_textToLatex();
};

#endif  // QT_NO_DEBUG
#endif  // SMALLUSEFULFUNCTIONS_T_H

