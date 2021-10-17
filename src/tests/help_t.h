#ifndef Header_Help_T
#define Header_Help_T
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"
#include "help.h"
#include "testutil.h"
#include "buildmanager.h"
#include <QtTest/QtTest>

class HelpTest: public QObject{
	Q_OBJECT
public:
    HelpTest(BuildManager *bm) : bm(bm) {
        connect(&help, SIGNAL(runCommand(QString,QString*)), this, SLOT(runCommand(QString,QString*)));
    }

public slots:
    bool runCommand(QString commandline,QString *buffer)
    {
        commandline.replace('@', "@@");
        commandline.replace('%', "%%");
        commandline.replace('?', "??");
        // path is used to force changing into the tmp dir (otherwise git status does not work properly)
        return bm->runCommand(commandline,QFileInfo() , QFileInfo(), 0, buffer, nullptr,buffer);
    }

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
        QString texdocPathname = help.packageDocFile(package, true);
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
    Help help;
    BuildManager *bm;
};

#endif
#endif // HELP_T_H
