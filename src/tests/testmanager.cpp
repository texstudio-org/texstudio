#ifndef QT_NO_DEBUG
#include "testmanager.h"
//hel 
#include "smallUsefulFunctions_t.h"
#include "latexparser_t.h"
#include "latexparsing_t.h"
#include "encoding_t.h"
#include "buildmanager_t.h"
#include "codesnippet_t.h"
#include "qdocumentcursor_t.h"
#include "qdocumentline_t.h"
#include "qdocumentsearch_t.h"
#include "qsearchreplacepanel_t.h"
#include "qeditor_t.h"
#include "latexcompleter_t.h"
#include "latexeditorview_t.h"
#include "latexeditorview_bm.h"
#include "latexstyleparser_t.h"
#include "scriptengine_t.h"
#include "structureview_t.h"
#include "tablemanipulation_t.h"
#include "syntaxcheck_t.h"
#include "updatechecker_t.h"
#include "utilsui_t.h"
#include "utilsversion_t.h"
#include "help_t.h"
#include "latexoutputfilter_t.h"
#include <QtTest/QtTest>

const QRegExp TestToken::simpleTextRegExp ("[A-Z'a-z0-9]+.?");
const QRegExp TestToken::commandRegExp ("\\\\([A-Za-z]+|.)");
const QRegExp TestToken::ignoredTextRegExp ("[$\t *!{}.\\][]+");
const QRegExp TestToken::specialCharTextRegExp ("[A-Z'\"\\\\\\{\\}a-z0-9ö]+");
const QRegExp TestToken::punctationRegExp("[!():\"?,.;-]");

int totalTestTime;
char* tempResult;
bool globalExecuteAllTests;


QString TestManager::performTest(QObject* obj){
	char* argv[3];
	argv[0]=(char*)"texstudio";
	argv[1]=(char*)"-o";
	argv[2]=tempResult;
	QTime timing; timing.start();
	QTest::qExec(obj,3,argv);
	delete obj;
	int time = timing.elapsed();
	totalTestTime += time;
	QString testTime = QString("Time: %1 ms\n\n" ).arg(time);
	QFile f(QFile::decodeName(tempResult));
	if (!f.open(QIODevice::ReadOnly)) 
		return "\n\n!!!!!!!!!!! Couldn't find test result !!!!!!!!!!!! \n\n";
	return f.readAll()+testTime;
}

QString TestManager::execute(TestLevel level, LatexEditorView* edView, QCodeEdit* codeedit, QEditor* editor, BuildManager* buildManager){
	QTemporaryFile tf;
	tf.setAutoRemove(false);
	tf.open();
	QByteArray tfn = QFile::encodeName(tf.fileName());
	tf.close();
	tempResult = tfn.data();
	
	globalExecuteAllTests = level == TL_ALL;
	
	//codeedit, editor are passed as extra parameters and not extracted from edView, so we don't have
	//to include latexeditorview.h here
	totalTestTime = 0;
	QString tr;
	QList<QObject*> tests=QList<QObject*>()
        << new SmallUsefulFunctionsTest()
        << new LatexParserTest()
        << new LatexParsingTest()
        << new EncodingTest()
        << new LatexOutputFilterTest()
		<< new BuildManagerTest(buildManager)
		<< new CodeSnippetTest(editor)
		<< new QDocumentLineTest()
        << new QDocumentCursorTest(level==TL_AUTO)
		<< new QDocumentSearchTest(editor,level==TL_ALL)
		<< new QSearchReplacePanelTest(codeedit,level==TL_ALL)
		<< new QEditorTest(editor,level==TL_ALL)
		<< new LatexEditorViewTest(edView)
		<< new LatexCompleterTest(edView)
		<< new LatexStyleParserTest(level==TL_ALL)
		<< new ScriptEngineTest(edView,level==TL_ALL)
		<< new LatexEditorViewBenchmark(edView,level==TL_ALL)
		<< new StructureViewTest(edView,edView->document,level==TL_ALL)
		<< new TableManipulationTest(editor)
		<< new SyntaxCheckTest(edView)
		<< new UpdateCheckerTest(level==TL_ALL)
		<< new UtilsUITest(level==TL_ALL)
        << new VersionTest(level==TL_ALL)
        << new HelpTest();
	bool allPassed=true;
	if (level!=TL_ALL)
		tr="There are skipped tests. Please rerun with --execute-all-tests\n\n";
	for (int i=0; i <tests.size();i++){
		emit newMessage(tests[i]->metaObject()->className());
        qDebug()<<tests[i]->metaObject()->className();
		QString res=performTest(tests[i]);
		tr+=res;
		if (!res.contains(", 0 failed, 0 skipped")) allPassed=false;
	}	
	
	tr+=QString("\nTotal testing time: %1 ms\n").arg(totalTestTime);
	
	if (!allPassed)
		tr="*** THERE SEEM TO BE FAILED TESTS! ***\n\n\n\n"+tr;
	
	QFile(QFile::decodeName(tempResult)).remove();
	
	return tr;
}
#endif
