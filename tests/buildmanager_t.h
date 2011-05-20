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
		QTest::addColumn<QString >("fileName2");
		QTest::addColumn<int >("line");
		QTest::addColumn<QString >("expected");
		
		QTest::newRow("basic meta") << "@-@@ %% ?? @" << "" << "!none" << 17 << "17-@ % ? 17";
		QTest::newRow("relative file") << "%#?m)#?me)#?m.pdf:42!" << "pseudo.tex" << "!none" << 42  
				<< "\"pseudo\"#pseudo#pseudo.tex#pseudo.pdf:42!";
		//use resource path so no drive letter will be inserted on windows 
		QTest::newRow("absolute file") << "?a)~?am)~?ame)~" << ":/somewhere/something/test.tex" << "!none" << 0 
				<< QString(":/somewhere/something/~:/somewhere/something/test~:/somewhere/something/test.tex~").replace("/",QDir::separator());;
		QTest::newRow("placeholder end") << "?m.newExt##?m)##?m\"##?m ##?e)" << "rel.tex" << "!none" << 0 
				<< "rel.newExt##rel##\"rel\"##rel ##tex";
		QTest::newRow("truncated placeholder") << "?m" << "inserted.here" << "!none" << 0 << "inserted";
		
		QTest::newRow("relative current file") << "?me)-?c:me)-?c:e)-?e)+?m.tex+?c:m.tex" << "main.mfile" << "current.cfile" << 0 
				<< "main.mfile-current.cfile-cfile-mfile+main.tex+current.tex";
		QTest::newRow("absolute current file") << "?ame)?c:ame)?c:a)?c:am.tex?c:a" << ":/somewhere/mainfile.m" << ":/elsewhere/include/current.c" << 0
				<< QString(":/somewhere/mainfile.m:/elsewhere/include/current.c:/elsewhere/include/:/elsewhere/include/current.tex:/elsewhere/include/").replace("/",QDir::separator());;		
	}
	void parseExtendedCommandLine(){ 
		QFETCH(QString, str);
		QFETCH(QString, fileName);
		QFileInfo file(fileName);
		QFETCH(QString, fileName2);		
		QFileInfo file2;
		if (fileName2!="!none") 
			file2=QFileInfo(fileName2);
		QFETCH(int, line);
		QFETCH(QString, expected);
		QString real;
		if (fileName2!="!none") 
			real=BuildManager::parseExtendedCommandLine(str,file,file2,line).first();
		else
			real=BuildManager::parseExtendedCommandLine(str,file,line).first();
		QVERIFY2(real==expected, QString("result wrong: got %1 expected %2").arg(real).arg(expected).toLatin1().constData());
	}
};
#endif
#endif
