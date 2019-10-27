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

		QTest::newRow("fancyhdr") << "fancyhdr" << "fancyhdr.dvi;fancyhdr.pdf";
		QTest::newRow("ifthen") << "ifthen" << "ifthen.pdf";
		QTest::newRow("graphicx") << "graphicx" << "graphicx.pdf;grfguide.pdf";
		QTest::newRow("fancyref") << "fancyref" << "freftest.dvi;fancyref.pdf";
	}

	void packageDocFile() {
		QFETCH(QString, package);
		QFETCH(QString, fileWithoutPath);
		if (!globalExecuteAllTests) {
			qDebug("skip");
			return;
		}
		QStringList checkList=fileWithoutPath.split(";");
		QString texdocPathname = Help::packageDocFile(package, true);
		if (texdocPathname == "") {
			QVERIFY2(false, QString("texdoc command was not found in the search path or package \"%1\" is not installed").arg(package).toLatin1().constData());
		}
		QString texdocFilename = QFileInfo(texdocPathname).fileName();
		bool found=false;
		for(int i=0, n=checkList.count(); i<n; ++i) {
			QString checkFilename=checkList.at(i);
			if(checkFilename==texdocFilename) {
				found=true;
				break;
			}
		}
		QVERIFY2(found, QString("Could not find documentation file for package \"%1\"").arg(package).toLatin1().constData());
	}

private:
	bool allTests;
};

#endif
#endif // HELP_T_H
