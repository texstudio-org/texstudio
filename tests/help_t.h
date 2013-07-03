#ifndef HELP_T_H
#define HELP_T_H
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"
#include "help.h"
#include "testutil.h"
#include <QtTest/QtTest>

class HelpTest: public QObject{
	Q_OBJECT
public:
	HelpTest(bool executeAllTests=true) : allTests(executeAllTests) {}
private slots:
	void packageDocFile_data() {
		QTest::addColumn<QString>("package");
		QTest::addColumn<QString>("fileWithoutPath");

		QTest::newRow("fancyhdr") << "fancyhdr" << "fancyhdr.dvi";
		QTest::newRow("xcolor") << "xcolor" << "xcolor.pdf";
		QTest::newRow("graphicx") << "graphicx" << "graphicx.pdf";
		QTest::newRow("fancyref") << "fancyref" << "freftest.dvi";
	}

	void packageDocFile() {
		QFETCH(QString, package);
		QFETCH(QString, fileWithoutPath);

		QString file = Help::packageDocFile(package);
		QEQUAL(QFileInfo(file).fileName(), fileWithoutPath);
	}

private:
	bool allTests;
};

#endif
#endif // HELP_T_H
