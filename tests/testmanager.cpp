#ifndef QT_NO_DEBUG
#include "testmanager.h"

#include "smallUsefulFunctions_t.h"
#include "buildmanager_t.h"
#include <QtTest/QtTest>

const QRegExp TestToken::simpleTextRegExp ("[A-Z'a-z0-9]+");
const QRegExp TestToken::commandRegExp ("\\\\[A-Za-z]+");
const QRegExp TestToken::ignoredTextRegExp ("[$\t *!{}.\\][]+");

QString TestManager::performTest(QObject* obj){
	char* argv[3];
	argv[0]="texmakerx";
	argv[1]="-o";
	argv[2]="tempResult.txt";
	QTest::qExec(obj,3,argv);
	delete obj;
	QFile f("tempResult.txt");
	if (!f.open(QIODevice::ReadOnly)) 
		return "\n\n!!!!!!!!!!! Couldn't find test result !!!!!!!!!!!! \n\n";
	return f.readAll();
}

QString TestManager::execute(){
	QString tr;
	tr+=performTest(new SmallUsefulFunctionsTest());
	tr+=performTest(new BuildManagerTest());
	return tr;
}
#endif
