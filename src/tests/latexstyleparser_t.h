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
	void parseLine_basic_data() {
		QTest::addColumn<QString>("line");
		QTest::addColumn<QStringList>("expectedResult");

		QTest::newRow("def") << "\\def \\cmd {foo}" << (QStringList() << "\\cmd#S");
		QTest::newRow("def1") << "\\def \\cmd#1{foo}" << (QStringList() << "\\cmd{arg1}#S");
		QTest::newRow("def3") << "\\def\\cmd #1 #2 #3 #4 #5 {foo}" << (QStringList() << "\\cmd{arg1}{arg2}{arg3}{arg4}{arg5}#S");
		QTest::newRow("let") << "\\let \\cmd" << (QStringList() << "\\cmd#S");

		QTest::newRow("newcommand") << "\\newcommand{\\cmd}" << (QStringList() << "\\cmd#S");
		QTest::newRow("newcommand1") << "\\newcommand{\\cmd}[1]" << (QStringList() << "\\cmd{arg1}#S");
		QTest::newRow("newcommand2") << "\\newcommand{\\cmd}[2]" << (QStringList() << "\\cmd{arg1}{arg2}#S");
		QTest::newRow("newcommand9") << "\\newcommand{\\cmd}[9]" << (QStringList() << "\\cmd{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}{arg9}#S");
		QTest::newRow("newcommand-star") << "\\newcommand*{\\cmd}" << (QStringList() << "\\cmd#S");
		QTest::newRow("newcommand-nobrace1") << "\\newcommand\\cmd[1]" << (QStringList() << "\\cmd{arg1}#S");
		QTest::newRow("newcommand-spaces") << "bla foo \\newcommand  {\\cmd}   [1]" << (QStringList() << "\\cmd{arg1}#S");
		QTest::newRow("newcommand-optional") << "\\newcommand{\\cmd}[1][default]" << (QStringList() << "\\cmd[opt]#S" << "\\cmd#S");
		QTest::newRow("newcommand-optional2") << "\\newcommand{\\cmd}[2][default]" << (QStringList() << "\\cmd[opt]{arg1}#S" << "\\cmd{arg1}#S");
		QTest::newRow("newcommand-nobrace-optional") << "\\newcommand \\cmd[1][a \\default value]" << (QStringList() << "\\cmd[opt]#S" << "\\cmd#S");
		QTest::newRow("newcommand-nobrace-optional2") << "\\newcommand\\cmd[2][a \\default value]" << (QStringList() << "\\cmd[opt]{arg1}#S" << "\\cmd{arg1}#S");

		QTest::newRow("providecommand1") << "\\providecommand{\\cmd}[1]" << (QStringList() << "\\cmd{arg1}#S");
		QTest::newRow("declareRobustCommand1") << "\\DeclareRobustCommand{\\cmd}[1]" << (QStringList() << "\\cmd{arg1}#S");
		QTest::newRow("newenvironment") << "\\newenvironment{myenv}" << (QStringList() << "\\begin{myenv}#S" << "\\end{myenv}#S");

		QTest::newRow("mathSymbol") << "\\DeclareMathSymbol{\\myop}" << (QStringList() << "\\myop#Sm");
		QTest::newRow("newLength") << "\\newlength{\\mylen}" << (QStringList() << "\\mylen");
		QTest::newRow("newCounter") << "\\newcounter{duke}" << (QStringList() << "\\theduke");
		QTest::newRow("loadClass") << "\\LoadClass{myclass}" << (QStringList() << "#include:myclass");
	}

	void parseLine_basic() {
		// basic parseLine test: no context (inRequirePackage, parsedPackages)
		QFETCH(QString, line);
		QFETCH(QStringList, expectedResult);
		bool inRequirePackage = false;
		QStringList parsedPackages;
		QStringList result = LatexStyleParser().parseLine(line, inRequirePackage, parsedPackages, "mypackage.sty");
		QEQUALLIST(result, expectedResult);
	}

private:
	bool allTests;
};

#endif // QT_NO_DEBUG
#endif // LATEXSTYLEPARSER_T_H
