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
		QTest::newRow("xcolor") << "xcolor" << "xcolor.pdf";
        QTest::newRow("graphicx") << "graphicx" << "graphicx.pdf;grfguide.pdf";
        QTest::newRow("fancyref") << "fancyref" << "freftest.dvi;fancyref.pdf";
	}

	void packageDocFile() {
		QFETCH(QString, package);
		QFETCH(QString, fileWithoutPath);
        QStringList lst=fileWithoutPath.split(";");
		QString file = Help::packageDocFile(package);
        bool found=false;
        for(int i=(lst.count()-1);i>0;i--){
            QString fileName=lst.at(i);
            if(fileName==QFileInfo(file).fileName()){
                QEQUAL(QFileInfo(file).fileName(), fileName);
                found=true;
                break;
            }
        }
        if(!found)
            QEQUAL(QFileInfo(file).fileName(), lst.value(0,""));
	}

private:
	bool allTests;
};

#endif
#endif // HELP_T_H
