#ifndef Header_Encoding_T
#define Header_Encoding_T
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"
#include "encoding.h"
#include "testutil.h"
#include <QtTest/QtTest>

class EncodingTest : public QObject
{
	Q_OBJECT
private slots:
	void test_lineStart_data();
	void test_lineStart();
	void test_lineEnd_data();
	void test_lineEnd();

	void test_getEncodingFromPackage_data();
	void test_getEncodingFromPackage();
	void test_guessEncoding_data();
	void test_guessEncoding();

	void test_encodingEnum();
};

#endif // QT_NO_DEBUG
#endif // ENCODING_T_H
