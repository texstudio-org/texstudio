#ifndef QT_NO_DEBUG
#include "testmanager.h"

#include "latexeditorview.h"

#include "smallUsefulFunctions_t.h"
#include "buildmanager_t.h"
#include "codesnippet_t.h"
#include "qdocumentcursor_t.h"
#include "qdocumentsearch_t.h"
#include "qsearchreplacepanel_t.h"
#include <QtTest/QtTest>

const QRegExp TestToken::simpleTextRegExp ("[A-Z'a-z0-9]+");
const QRegExp TestToken::commandRegExp ("\\\\([A-Za-z]+|.)");
const QRegExp TestToken::ignoredTextRegExp ("[$\t *!{}.\\][]+");
const QRegExp TestToken::specialCharTextRegExp ("[A-Z'\"\\\\\\{\\}a-z0-9ö]+");

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

QString TestManager::execute(LatexEditorView* edView, QCodeEdit* codeedit, QEditor* editor){
	QString tr;
	QList<QObject*> tests=QList<QObject*>()
		<< new SmallUsefulFunctionsTest()
		<< new BuildManagerTest()
		<< new CodeSnippetTest(editor)
		<< new QDocumentCursorTest()
		<< new QDocumentSearchTest(editor)
		<< new QSearchReplacePanelTest(codeedit);
	bool allPassed=true;
	for (int i=0; i <tests.size();i++){
		QString res=performTest(tests[i]);
		tr+=res;
		if (!res.contains(", 0 failed, 0 skipped")) allPassed=false;
	}	
	
	if (!allPassed) 
		tr="THERE SEEMS TO BE FAILED TESTS! \n\n\n\n\n\n\n"+tr;
	return tr;
}
#endif
