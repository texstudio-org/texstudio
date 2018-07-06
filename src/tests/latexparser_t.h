#ifndef LATEXPARSER_T_H
#define LATEXPARSER_T_H
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"
#include "latexparser/latexparser.h"
#include "latexparser/latexreader.h"
#include "testutil.h"
#include <QtTest/QtTest>


const int NW_IGNORED_TOKEN = -2; //token that are not words,  { and }
const int NW_OPTION = -3; //option text like in \include
const int NW_OPTION_PUNCTATION = -4; //option punctation like in \include

class TestToken: public QString
{
	static const QRegExp simpleTextRegExp; //defined in testmanager.cpp
	static const QRegExp commandRegExp;
	static const QRegExp ignoredTextRegExp;
	static const QRegExp specialCharTextRegExp;
	static const QRegExp punctationRegExp;
	void guessType()
	{
		if (simpleTextRegExp.exactMatch(*this)) type = LatexReader::NW_TEXT;
		else if (commandRegExp.exactMatch(*this)) type = LatexReader::NW_COMMAND;
		else if (punctationRegExp.exactMatch(*this)) type = LatexReader::NW_PUNCTATION;
		else if (ignoredTextRegExp.exactMatch(*this)) type = NW_IGNORED_TOKEN;
		else if (*this == "%") type = LatexReader::NW_COMMENT;
		else if (specialCharTextRegExp.exactMatch(*this)) type = LatexReader::NW_TEXT;
		else QVERIFY2(false, QString("invalid test data: \"%1\"").arg(*this).toLatin1().constData());
	}
public:
	int type, position;
    TestToken(): QString(), type(NW_IGNORED_TOKEN), position(-1), soll(QString()) { }
	TestToken(const TestToken &token): QString(token), type(token.type), position(token.position), soll(token.soll) { }
    TestToken(const QString &str): QString(str), position(-1), soll(str) { guessType(); }
    TestToken(const char *cstr): QString(cstr), position(-1), soll(QString(cstr)) { guessType(); }
    TestToken(const QString &str, int atype): QString(str), type(atype), position(-1), soll(str) {}
    TestToken(const QString &str, const QString result, int atype): QString(str), type(atype), position(-1), soll(result) {}
	bool operator ==(const QString &other)
	{
		return soll.compare(other) == 0;
	}
private:
	QString soll;
};

Q_DECLARE_METATYPE(TestToken);
Q_DECLARE_METATYPE(QList<TestToken>);


class LatexParserTest : public QObject
{
	Q_OBJECT
	enum TokenFilter {FILTER_NEXTTOKEN, FILTER_NEXTWORD_WITH_COMMANDS, FILTER_NEXTWORD, FILTER_NEXTTEXTWORD};
	TestToken env(const QString &str);
	TestToken option(const QString &str);
	void addRow(const char *name, TokenFilter filter, QList<TestToken> tokens);
	void addComplexData(TokenFilter filter);
	void nextWord_complex_test(bool commands);
private slots:
	void nextToken_complex_data();
	void nextToken_complex();
	void nextWordWithCommands_complex_data();
	void nextWordWithCommands_complex();
	void nextWord_complex_data();
	void nextWord_complex();
	void nextTextWord_complex_data();
	void nextTextWord_complex();
	void nextWord_simple_data();
	void nextWord_simple();
	void cutComment_simple_data();
	void cutComment_simple();
	void test_findContext_data();
	void test_findContext();
	void test_findContext2_data();
	void test_findContext2();
	void test_resolveCommandOptions_data();
	void test_resolveCommandOptions();
	void test_findClosingBracket_data();
	void test_findClosingBracket();
}; // LatexParserTest


#endif // QT_NO_DEBUG
#endif // LATEXPARSER_T_H
