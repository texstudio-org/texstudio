#ifndef QT_NO_DEBUG
#include "testmanager.h"

#include "smallUsefulFunctions_t.h"

#include <QtTest/QtTest>

const QRegExp TestToken::simpleTextRegExp ("[A-Z'a-z0-9]+");
const QRegExp TestToken::commandRegExp ("\\\\[A-Za-z]+");
const QRegExp TestToken::ignoredTextRegExp ("[$\t *!{}.\\][]+");


QString TestManager::execute(){
	char* argv[4];
	argv[0]="texmakerx";
	argv[1]="-o";
	argv[2]="results.txt";
	argv[3]="-vs";
	SmallUsefulFunctionsTest test;
	QTest::qExec(&test,4,argv);
	return "results.txt";
}
#endif
