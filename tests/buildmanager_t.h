#ifndef BUILDMANAGER_T_H
#define BUILDMANAGER_T_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "buildmanager.h"
#include <QtTest/QtTest>

class BuildManagerTest: public QObject{
	Q_OBJECT
private slots:
	void parseExtendedCommandLine_data(){ 
		QTest::addColumn<QString >("str");
		QTest::addColumn<QString >("fileName");
		QTest::addColumn<int >("line");
		QTest::addColumn<QString >("expected");
		
		QTest::newRow("basic meta") << "@-@@ %% ?? @" << "" << 17 << "17-@ % ? 17";
		QTest::newRow("relative file") << "%#?m)#?me)#?m.pdf:42!" << "pseudo.tex" << 42  
				<< "\"pseudo\"#pseudo#pseudo.tex#pseudo.pdf:42!";
		//use resource path so no drive letter will be inserted on windows 
		QTest::newRow("absolute file") << "?a)~?am)~?ame)~" << ":/somewhere/something/test.tex" << 0 
				<< QString(":/somewhere/something/~:/somewhere/something/test~:/somewhere/something/test.tex~").replace("/",QDir::separator());;
		QTest::newRow("placeholder end") << "?m.newExt##?m)##?m\"##?m ##" << "rel.tex" << 0 
				<< "rel.newExt##rel##\"rel\"##rel ##";
		
	}
	void parseExtendedCommandLine(){ 
		QFETCH(QString, str);
		QFETCH(QString, fileName);
		QFileInfo file(fileName);
		QFETCH(int, line);
		QFETCH(QString, expected);
		QString real=BuildManager::parseExtendedCommandLine(str,file,line);
		QVERIFY2(real==expected, QString("result wrong: got %1 expected %2").arg(real).arg(expected).toLatin1().constData());
	}
};
#endif
#endif
