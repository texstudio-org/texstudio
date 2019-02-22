#ifndef QT_NO_DEBUG
#include "encoding_t.h"


void EncodingTest::test_lineStart_data()
{
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("pos");
	QTest::addColumn<int>("start");

	QTest::newRow("empty") << "" << 0 << 0;
	QTest::newRow("start") << "foo bar" << 0 << 0;
	QTest::newRow("text") << "foo bar" << 6 << 0;
	QTest::newRow("newline") << "foo\nbar" << 6 << 4;
	QTest::newRow("cr") << "foo\rbar" << 6 << 4;
	QTest::newRow("cr_newline") << "foo\r\nbar" << 6 << 5;
	QTest::newRow("start_newline") << "foo\nbar" << 4 << 4;
}

void EncodingTest::test_lineStart()
{
	QFETCH(QString, text);
	QFETCH(int, pos);
	QFETCH(int, start);
	QEQUAL(Encoding::Internal::lineStart(text.toLatin1(), pos), start);
}

void EncodingTest::test_lineEnd_data()
{
	QTest::addColumn<QString>("text");
	QTest::addColumn<int>("pos");
	QTest::addColumn<int>("end");

	QTest::newRow("empty") << "" << 0 << 0;
	QTest::newRow("end") << "foo bar" << 7 << 7;
	QTest::newRow("text") << "foo bar" << 1 << 7;
	QTest::newRow("newline") << "foo\nbar" << 1 << 3;
	QTest::newRow("cr") << "foo\rbar" << 1 << 3;
	QTest::newRow("cr_newline") << "foo\r\nbar" << 1 << 3;
	QTest::newRow("end_newline") << "foo\nbar" << 3 << 3;
	QTest::newRow("end_newline") << "foo\r\nbar\x20\x29more" << 2 << 3;
}

void EncodingTest::test_lineEnd()
{
	QFETCH(QString, text);
	QFETCH(int, pos);
	QFETCH(int, end);
	QEQUAL(Encoding::Internal::lineEnd(text.toLatin1(), pos), end);
}

void EncodingTest::test_getEncodingFromPackage_data()
{
	QTest::addColumn<QString>("text");
	QTest::addColumn<QString>("encodingName");

	QTest::newRow("empty") << "" << "";
	QTest::newRow("no info") << "foo bar\nbaz" << "";
	QTest::newRow("simple") << "\\usepackage[latin1]{inputenc}" << "latin1";
	QTest::newRow("simple2") << "foo bar\nbaz\n\\usepackage[latin1]{inputenc}" << "latin1";
	QTest::newRow("spaces") << "  \\usepackage[utf8]{inputenc}  " << "utf8";
	QTest::newRow("multiple") << "\\usepackage[latin1]{inputenc}\n\\usepackage[utf8]{inputenc}" << "latin1";
	QTest::newRow("commented") << "  %\\usepackage[latin1]{inputenc}" << "";
	QTest::newRow("commented2") << "% \\usepackage[latin1]{inputenc}\n\\usepackage[utf8]{inputenc}" << "utf8";
}

void EncodingTest::test_getEncodingFromPackage()
{
	QFETCH(QString, text);
	QFETCH(QString, encodingName);
	QEQUAL(encodingName, Encoding::Internal::getEncodingFromPackage(text.toLatin1(), text.length(), "inputenc"));
}

void EncodingTest::test_guessEncoding_data()
{
	QTest::addColumn<QString>("text");
	QTest::addColumn<QString>("encodingName");
	QTest::newRow("empty") << "" << "";
	QTest::newRow("no info") << "foo bar\nbaz" << "";
	QTest::newRow("inputenc") << "\\usepackage[latin1]{inputenc}" << "ISO-8859-1";
	QTest::newRow("inputenx") << "\\usepackage[utf8]{inputenx}" << "UTF-8";
}

void EncodingTest::test_guessEncoding()
{
	QFETCH(QString, text);
	QFETCH(QString, encodingName);

    QTextCodec *encoding = nullptr;
	int sure = 0;
	Encoding::guessEncoding(text.toLatin1(), encoding, sure);
	if (encodingName.isEmpty()) {
        int b = (encoding == nullptr) ? 0 : 1 ;
		QEQUAL(0, b);
	} else {
		QEQUAL(encodingName, QString(encoding->name()));
	}
}

void EncodingTest::test_encodingEnum()
{
	using namespace Encoding;
	Q_ASSERT(QTextCodec::codecForName("UTF-8") == QTextCodec::codecForMib(MIB_UTF8));
	Q_ASSERT(QTextCodec::codecForName("UTF-16LE") == QTextCodec::codecForMib(MIB_UTF16LE));
	Q_ASSERT(QTextCodec::codecForName("UTF-16BE") == QTextCodec::codecForMib(MIB_UTF16BE));
	Q_ASSERT(QTextCodec::codecForName("ISO-8859-1") == QTextCodec::codecForMib(MIB_LATIN1));

	Q_ASSERT(QTextCodec::codecForMib(MIB_UTF8)->mibEnum() == MIB_UTF8);
	Q_ASSERT(QTextCodec::codecForMib(MIB_UTF16LE)->mibEnum() == MIB_UTF16LE);
	Q_ASSERT(QTextCodec::codecForMib(MIB_UTF16BE)->mibEnum() == MIB_UTF16BE);
	Q_ASSERT(QTextCodec::codecForMib(MIB_LATIN1)->mibEnum() == MIB_LATIN1);
}

#endif // QT_NO_DEBUG
