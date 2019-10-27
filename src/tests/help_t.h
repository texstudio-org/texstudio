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
		QString texdocFilename = QFileInfo(texdocPathname).fileName();
		bool found=false;
		for(int i=(checkList.count()-1);i>0;i--) {
			QString checkFilename=checkList.at(i);
			if(checkFilename==texdocFilename) {
				QEQUAL(texdocFilename, checkFilename);
				found=true;
				break;
			}
		}
		if(!found) {
			QEQUAL(texdocFilename, checkList.value(0,""));
		}
	}

private:
	bool allTests;
};

#endif
#endif // HELP_T_H
