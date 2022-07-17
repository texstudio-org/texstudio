#ifndef Header_Latex_Style_Parser_T
#define Header_Latex_Style_Parser_T
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"
#include "latexstyleparser.h"
#include "testutil.h"
#include <QtTest/QtTest>

class LatexStyleParserTest: public QObject{
	Q_OBJECT
public:
	LatexStyleParserTest(bool executeAllTests) : allTests(executeAllTests) {}
private slots:
    void parseLine_basic_data();
    void parseLine_basic();
    void parseLineRequire_data();
    void parseLineRequire();
private:
	bool allTests;
};

#endif // QT_NO_DEBUG
#endif // LATEXSTYLEPARSER_T_H
