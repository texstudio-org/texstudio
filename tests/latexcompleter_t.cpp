
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
#include "latexdocument.h"

#include <QtTest/QtTest>
LatexCompleterTest::LatexCompleterTest(LatexEditorView* view): edView(view){
	Q_ASSERT(edView->getCompleter());
	Q_ASSERT(edView->getCompleter()->getConfig());
	config = const_cast<LatexCompleterConfig*>(edView->getCompleter()->getConfig());
	Q_ASSERT(config);
	oldEowCompletes = config->eowCompletes;
	oldPrefered = config->preferedCompletionTab;
	config->preferedCompletionTab=LatexCompleterConfig::CPC_ALL;
}
LatexCompleterTest::~LatexCompleterTest(){
	edView->editor->setCursorPosition(0,0);
	config->eowCompletes = oldEowCompletes;
	config->preferedCompletionTab=LatexCompleterConfig::PreferedCompletionTab(oldPrefered);
}

void LatexCompleterTest::simple_data(){
	QTest::addColumn<QString>("text");
	QTest::addColumn<bool>("eowCompletes");
	QTest::addColumn<bool>("autoParenComplete");
	QTest::addColumn<int>("line");
	QTest::addColumn<int>("offset");
	QTest::addColumn<QString>("preinsert");
	QTest::addColumn<QString>("preres");
	QTest::addColumn<QStringList>("log");

	QTest::newRow("simple") << ">><<" << true << false << 0 << 2
				<< "" << ""
				<< (QStringList()
				    << "\\:>>\\<<"
				    << "a:>>\\a<<"
				    << "b:>>\\ab<<"
				    << "s:>>\\abs<<"
				    << "*:>>\\abstractname{*}<<");

	QTest::newRow("simple no eow comp") << ">><<" << false << false << 0 << 2
				<< "" << ""
				<< (QStringList()
				    << "\\:>>\\<<"
				    << "a:>>\\a<<"
				    << "b:>>\\ab<<"
				    << "s:>>\\abs<<"
				    << "*:>>\\abs*<<");



	QTest::newRow("begin") << ">><<" << true << false << 0 << 2
			<< "" << ""
			<< (QStringList()
			    << "\\:>>\\<<"
			    << "b:>>\\b<<"
			    << "e:>>\\be<<"
			    << "g:>>\\beg<<"
			    << "{:>>\\begin{<<"
			    << "a:>>\\begin{a<<"
			    << "*:>>\\begin{align*<<");

	QTest::newRow("begin +pc") << ">><<" << true << true << 0 << 2
			<< "" << ""
			<< (QStringList()
			    << "\\:>>\\<<"
			    << "b:>>\\b<<"
			    << "e:>>\\be<<"
			    << "g:>>\\beg<<"
			    << "{:>>\\begin{<<"
			    << "a:>>\\begin{a<<"
			    << "*:>>\\begin{align*<<");

	QTest::newRow("begin no eowc") << ">><<" << false << false << 0 << 2
			<< "" << ""
			<< (QStringList()
			    << "\\:>>\\<<"
			    << "b:>>\\b<<"
			    << "e:>>\\be<<"
			    << "g:>>\\beg<<"
			    << "{:>>\\beg{<<"
			    << "*:>>\\beg{*<<");

	QTest::newRow("begin -eowc+pc") << ">><<" << false << true << 0 << 2
			<< "" << ""
			<< (QStringList()
			    << "\\:>>\\<<"
			    << "b:>>\\b<<"
			    << "e:>>\\be<<"
			    << "g:>>\\beg<<"
			    << "{:>>\\beg{}<<"
			    << "*:>>\\beg{*}<<");

	QTest::newRow("begin multiple {{%1") << ">><<" << false << false << 0 << 2
			<< "" << ""
			<< (QStringList()
			    << "\\:>>\\<<"
			    << "b:>>\\b<<"
			    << "e:>>\\be<<"
			    << "g:>>\\beg<<"
			    << "{:>>\\beg{<<"
			    << "{:>>\\beg{{<<");

	QTest::newRow("begin multiple {{%1") << ">><<" << false << true << 0 << 2
			<< "" << ""
			<< (QStringList()
			    << "\\:>>\\<<"
			    << "b:>>\\b<<"
			    << "e:>>\\be<<"
			    << "g:>>\\beg<<"
			    << "{:>>\\beg{}<<"
			    << "{:>>\\beg{{}}<<");

	for (int a=0;a<2;a++)
	QTest::newRow(qPrintable(QString("begin multiple {{ +ec%1").arg(a))) << ">><<" << true << !!a << 0 << 2
			<< "" << ""
			<< (QStringList()
			    << "\\:>>\\<<"
			    << "b:>>\\b<<"
			    << "e:>>\\be<<"
			    << "g:>>\\beg<<"
			    << "{:>>\\begin{<<"
			    << "{:>>\\begin{alignat}{<<");
	{	}


	QTest::newRow("small cmd") << ">><<" << false << false << 0 << 2
				<< "" << ""
				<< (QStringList()
				    << "\\:>>\\<<"
				    << "a:>>\\a<<"
				    << "{:>>\\a{<<"
				    );
	QTest::newRow("small cmd +pc") << ">><<" << false << true << 0 << 2
				<< "" << ""
				<< (QStringList()
				<< "\\:>>\\<<"
				<< "a:>>\\a<<"
				<< "{:>>\\a{<<" // pc does not work, as the defined command is \a{
				<< "-:>>\\a{-<<"
				);
	QTest::newRow("small cmd +ec") << ">><<" << true << false << 0 << 2
				<< "" << ""
				<< (QStringList()
				    << "\\:>>\\<<"
				    << "a:>>\\a<<"
				    << "{:>>\\a{<<"
				    );
	QTest::newRow("small cmd +ec+pc") << ">><<" << true << true << 0 << 2
				<< "" << ""
				<< (QStringList()
				<< "\\:>>\\<<"
				<< "a:>>\\a<<"
				<< "{:>>\\a{<<"
				<< "-:>>\\a{-<<"
				);


	QTest::newRow("smbll cmd") << ">><<" << false << false << 0 << 2
				<< "" << ""
				<< (QStringList()
				    << "\\:>>\\<<"
				    << "b:>>\\b<<"
				    << "{:>>\\b{<<"
				    );
	QTest::newRow("smbll cmd +pc") << ">><<" << false << true << 0 << 2
			<< "" << ""
				<< (QStringList()
				<< "\\:>>\\<<"
				<< "b:>>\\b<<"
				<< "{:>>\\b{}<<"
				<< "-:>>\\b{-}<<"
				);
	QTest::newRow("smbll cmd +ec") << ">><<" << true << false << 0 << 2
			<< "" << ""
			<< (QStringList()
				    << "\\:>>\\<<"
				    << "b:>>\\b<<"
				    << "{:>>\\b{<<"
				    );
	QTest::newRow("smbll cmd +ec+pc") << ">><<" << true << true << 0 << 2
			<< "" << ""
				<< (QStringList()
				<< "\\:>>\\<<"
				<< "b:>>\\b<<"
				<< "{:>>\\b{}<<"
				<< "-:>>\\b{-}<<"
				);

	QTest::newRow("nearest eow +ec") << ">><<" << true << false << 0 << 2
			<< "" << ""
				<< (QStringList()
				<< "\\:>>\\<<"
				<< "o:>>\\o<<"
				<< "n:>>\\on<<"
				<< "l:>>\\onl<<"
				<< "<:>>\\only<<<"
				);
	QTest::newRow("nearest eow +ec") << ">><<" << true << false << 0 << 2
			<< "" << ""
				<< (QStringList()
				<< "\\:>>\\<<"
				<< "o:>>\\o<<"
				<< "n:>>\\on<<"
				<< "l:>>\\onl<<"
				<< "{:>>\\only{<<"
				);

	QTest::newRow("nearest eow +ec") << ">><<" << true << false << 0 << 2
			<< "" << ""
				<< (QStringList()
				<< "\\:>>\\<<"
				<< "o:>>\\o<<"
				<< "n:>>\\on<<"
				<< "l:>>\\onl<<"
				<< "{:>>\\only{<<"
				);

	for (int a=0;a<2;a++) for (int b=0;b<2;b++)
	QTest::newRow(qPrintable(QString("accent \\\" %1%2").arg(a).arg(b))) << ">><<" << !!a << !!b << 0 << 2
			<< "" << ""
				<< (QStringList()
				<< "\\:>>\\<<"
				<< "\":>>\\\"<<"
				);

	QTest::newRow("pc restore +ec+pc") << ">><<" << true << true << 0 << 2
				<< "\\{" << ">>\\{\\}<<"
				<< (QStringList()
				<< "\\:>>\\{\\}<<"
				<< "x:>>\\{\\x}<<"
				<< "y:>>\\{\\xy}<<"
				<< "z:>>\\{\\xyz}<<"
				<< "+:>>\\{\\xyz+\\}<<"
				<< "{:>>\\{\\xyz+{}\\}<<"
				);

	QTest::newRow("pc restore 2  +ec+pc") << ">><<" << true << true << 0 << 2
				<< "\\{" << ">>\\{\\}<<"
				<< (QStringList()
				<< "\\:>>\\{\\}<<"
				<< "x:>>\\{\\x}<<"
				<< "y:>>\\{\\xy}<<"
				<< "z:>>\\{\\xyz}<<"
				<< "{:>>\\{\\xyz{}\\}<<"
				);
}
void LatexCompleterTest::simple(){
	QFETCH(QString, text);
	QFETCH(QString, preinsert);
	QFETCH(QString, preres);
	QFETCH(bool, eowCompletes);
	QFETCH(bool, autoParenComplete);
	QFETCH(int, line);
	QFETCH(int, offset);
	QFETCH(QStringList, log);

	config->eowCompletes = eowCompletes;

	edView->editor->cutBuffer = "";
	
	edView->editor->setFlag(QEditor::AutoCloseChars, autoParenComplete);
	edView->editor->setText(text, false);
	edView->editor->setCursor(edView->editor->document()->cursor(line,offset));
	QSet<QString> helper;
	helper << "\\a{" << "\\b" << "\\begin{align*}\n\n\\end{align*}" << "\\begin{alignat}{n}\n\\end{alignat}" << "\\only<abc>{def}" << "\\only{abc}<def>";
	edView->getCompleter()->setAdditionalWords(helper); //extra words needed for test
	if (!preinsert.isEmpty()) {
		edView->editor->insertText(preinsert);
		QEQUAL(edView->editor->text(), preres);
	}
	edView->complete(0);
	foreach (const QString& s, log){
		char key = s.at(0).toLatin1();
		QTest::keyClick(edView->editor, key);
		QString text = s.mid(2);
		QString ist=edView->editor->text();
		QEQUAL(ist, text);
	}
 
	edView->editor->clearPlaceHolders();
	edView->editor->clearCursorMirrors();
}

#endif

