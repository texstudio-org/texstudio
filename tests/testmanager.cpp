#ifndef QT_NO_DEBUG
#include "testmanager.h"
//hel 
#include "smallUsefulFunctions_t.h"
#include "buildmanager_t.h"
#include "codesnippet_t.h"
#include "qdocumentcursor_t.h"
#include "qdocumentsearch_t.h"
#include "qsearchreplacepanel_t.h"
#include "qeditor_t.h"
#include "latexeditorview_t.h"
#include "scriptengine_t.h"
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

QString TestManager::execute(TestLevel level, LatexEditorView* edView, QCodeEdit* codeedit, QEditor* editor){
	//codeedit, editor are passed as extra parameters and not extracted from edView, so we don't have
	//to include latexeditorview.h here

	QString tr;
	QList<QObject*> tests=QList<QObject*>()
		<< new SmallUsefulFunctionsTest()
		<< new BuildManagerTest()
		<< new CodeSnippetTest(editor)
		<< new QDocumentCursorTest()
		<< new QDocumentSearchTest(editor)
		<< new QSearchReplacePanelTest(codeedit,level==TL_ALL)
		<< new QEditorTest(level==TL_ALL)
		<< new LatexEditorViewTest(edView)
		<< new ScriptEngineTest(editor);
	bool allPassed=true;
	if (level!=TL_ALL)
		tr="There are skipped tests. Please rerun with --execute-all-tests\n\n";
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
