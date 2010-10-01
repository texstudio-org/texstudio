
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "latexcompleter_t.h"
#include "latexcompleter_config.h"
#include "latexcompleter.h"
#include "latexeditorview.h"
#include "qdocumentcursor.h"
#include "qdocument.h"
#include "qeditor.h"
#include "testutil.h"

#include <QtTest/QtTest>
LatexCompleterTest::LatexCompleterTest(LatexEditorView* view): edView(view){
	Q_ASSERT(edView->getCompleter());
	Q_ASSERT(edView->getCompleter()->getConfig());
	config = const_cast<LatexCompleterConfig*>(edView->getCompleter()->getConfig());
	Q_ASSERT(config);
	oldEowCompletes = config->eowCompletes;
}
LatexCompleterTest::~LatexCompleterTest(){
	edView->editor->setCursorPosition(0,0);
	config->eowCompletes = oldEowCompletes;
}

void LatexCompleterTest::simple_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<bool>("eowCompletes");
	QTest::addColumn<int>("line");
	QTest::addColumn<int>("offset");
	QTest::addColumn<QStringList>("log");

	QTest::newRow("simple") << ">><<" << true << 0 << 2
				<< (QStringList()
				    << "\\:>>\\<<"
				    << "a:>>\\a<<"
				    << "b:>>\\ab<<"
				    << "s:>>\\abs<<"
				    << "*:>>\\abstractname{*}<<");

	QTest::newRow("simple no eow comp") << ">><<" << false << 0 << 2
				<< (QStringList()
				    << "\\:>>\\<<"
				    << "a:>>\\a<<"
				    << "b:>>\\ab<<"
				    << "s:>>\\abs<<"
				    << "*:>>\\abs*<<");


	QTest::newRow("begin") << ">><<" << true << 0 << 2
			<< (QStringList()
			    << "\\:>>\\<<"
			    << "b:>>\\b<<"
			    << "e:>>\\be<<"
			    << "g:>>\\beg<<"
			    << "{:>>\\begin{<<"
			    << "*:>>\\begin{align*<<");

}
void LatexCompleterTest::simple(){
	QFETCH(QString, text);
	QFETCH(bool, eowCompletes);
	QFETCH(int, line);
	QFETCH(int, offset);
	QFETCH(QStringList, log);

	config->eowCompletes = eowCompletes;

	edView->editor->document()->setText(text);
	edView->editor->setCursor(edView->editor->document()->cursor(line,offset));
	edView->complete(false);
	foreach (const QString& s, log){
		char key = s.at(0).toAscii();
		QTest::keyClick(edView->editor, key);
		QString text = s.mid(2);
		QEQUAL(edView->editor->text(), text);
	}

	edView->editor->clearPlaceHolders();
	edView->editor->clearCursorMirrors();
}

#endif

