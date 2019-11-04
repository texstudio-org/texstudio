
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

void LatexCompleterTest::initTestCase(){
	edView->editor->emitNeedUpdatedCompleter();
    CodeSnippetList helper;
    helper << CodeSnippet("\\a{") << CodeSnippet("\\b") << CodeSnippet("\\begin{align*}\n\n\\end{align*}") << CodeSnippet("\\begin{alignat}{n}\n\\end{alignat}") << CodeSnippet("\\only<abc>{def}") << CodeSnippet("\\only{abc}<def>");
	edView->getCompleter()->setAdditionalWords(helper); //extra words needed for test
    QSet<QString> labels;
    labels<<"abc"<<"bcd";
    edView->getCompleter()->setAdditionalWords(labels,CT_LABELS);
    labels.clear();
    labels<<"abcq"<<"bcdq";
    edView->getCompleter()->setAdditionalWords(labels,CT_CITATIONS);
    labels.clear();
    labels<<"abc1"<<"bcd1";
    edView->getCompleter()->setKeyValWords("key%\\test",labels);
    labels.clear();
    labels<<"abc2"<<"bcd2";
    edView->getCompleter()->setKeyValWords("key%\\test/abc",labels);
    labels.clear();
    labels<<"abc3"<<"bcd3";
    edView->getCompleter()->setKeyValWords("%abc",labels);
    labels.clear();
    labels<<"abc4"<<"bcd4";
    edView->getCompleter()->setContextWords(labels,"%abca");
    labels.clear();
    labels<<"%abca"<<"bcd3";
    edView->getCompleter()->setKeyValWords("%abcd",labels);
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

	if (globalExecuteAllTests) {
		QTest::newRow("simple") << ">><<" << true << false << 0 << 2
					<< "" << ""
					<< (QStringList()
					    << "\\:>>\\<<"
					    << "a:>>\\a<<"
					    << "b:>>\\ab<<"
					    << "s:>>\\abs<<"
                        << "*:>>\\abstractname*<<");

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
	} else qDebug("skipped some tests");

	QTest::newRow("smill cmd") << ">><<" << false << false << 0 << 2
				<< "" << ""
				<< (QStringList()
				    << "\\:>>\\<<"
				    << "i:>>\\i<<"
				    << "{:>>\\i{<<"
				    );
	QTest::newRow("smill cmd +pc") << ">><<" << false << true << 0 << 2
			<< "" << ""
				<< (QStringList()
				<< "\\:>>\\<<"
				<< "i:>>\\i<<"
				<< "{:>>\\i{}<<"
				<< "-:>>\\i{-}<<"
				);
	QTest::newRow("smill cmd +ec") << ">><<" << true << false << 0 << 2
			<< "" << ""
			<< (QStringList()
				    << "\\:>>\\<<"
				    << "i:>>\\i<<"
				    << "{:>>\\i{<<"
				    );
	QTest::newRow("smill cmd +ec+pc") << ">><<" << true << true << 0 << 2
			<< "" << ""
				<< (QStringList()
				<< "\\:>>\\<<"
				<< "i:>>\\i<<"
				<< "{:>>\\i{}<<"
				<< "-:>>\\i{-}<<"
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

    QTest::newRow("no pc restore +ec+pc") << ">><<" << true << true << 0 << 2
				<< "\\{" << ">>\\{\\}<<"
				<< (QStringList()
                << "\\:>>\\{\\\\}<<"
                << "x:>>\\{\\x\\}<<"
                << "y:>>\\{\\xy\\}<<"
                << "z:>>\\{\\xyz\\}<<"
                << "+:>>\\{\\xyz+\\}<<"
				<< "{:>>\\{\\xyz+{}\\}<<"
				);

    QTest::newRow("no pc restore 2  +ec+pc") << ">><<" << true << true << 0 << 2
				<< "\\{" << ">>\\{\\}<<"
				<< (QStringList()
                << "\\:>>\\{\\\\}<<"
                << "x:>>\\{\\x\\}<<"
                << "y:>>\\{\\xy\\}<<"
                << "z:>>\\{\\xyz\\}<<"
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

void LatexCompleterTest::keyval_data(){
    const QString trEnvironmentName = QObject::tr("*environment-name*");
    const QString trContent = QObject::tr("content...");

    QTest::addColumn<QString>("text");
    QTest::addColumn<QString>("workingDir");
    QTest::addColumn<int>("line");
    QTest::addColumn<int>("offset");
    QTest::addColumn<int>("completerFlag");
    QTest::addColumn<QString>("preinsert");
    QTest::addColumn<QString>("preres");
    QTest::addColumn<QStringList>("log");

    QTest::newRow("simple") << ">><<" << "" <<  0 << 2 << 0
                            << "" << ""
                            << (QStringList()
                                << "\\:>>\\<<"
                                << "b:>>\\b<<"
                                << "e:>>\\be<<"
                                << "g:>>\\beg<<"
                                << "\n:>>\\begin{" + trEnvironmentName + "}\n\t" + trContent + "\n\\end{" + trEnvironmentName + "}<<");

    QTest::newRow("ref") << ">>{}<<" << "" <<  0 << 3 << 5
                            << "" << ""
                            << (QStringList()
                                << "a:>>{a}<<"
                                << "\n:>>{abc}<<"
                                );
    QTest::newRow("ref-replace") << ">>{hj}<<" << "" <<  0 << 3 << 5
                            << "" << ""
                            << (QStringList()
                                << "a:>>{ahj}<<"
                                << "\n:>>{abc}<<"
                                );

    QTest::newRow("key") << ">>{}<<" << "key%\\test" <<  0 << 3 << 129
                            << "" << ""
                            << (QStringList()
                                << "a:>>{a}<<"
                                << "\n:>>{abc1}<<"
                                );
    QTest::newRow("key2") << ">>{a,}<<" << "key%\\test" <<  0 << 5 << 129
                            << "" << ""
                            << (QStringList()
                                << "a:>>{a,a}<<"
                                << "\n:>>{a,abc1}<<"
                                );
    QTest::newRow("key-replace") << ">>{gh}<<" << "key%\\test" <<  0 << 3 << 129
                            << "" << ""
                            << (QStringList()
                                << "a:>>{agh}<<"
                                << "\n:>>{abc1}<<"
                                );
    QTest::newRow("key-replace2") << ">>{gh,}<<" << "key%\\test" <<  0 << 3 << 129
                            << "" << ""
                            << (QStringList()
                                << "a:>>{agh,}<<"
                                << "\n:>>{abc1,}<<"
                                );
    QTest::newRow("keyval") << ">>{}<<" << "key%\\test/abc" <<  0 << 3 << 129
                            << "" << ""
                            << (QStringList()
                                << "a:>>{a}<<"
                                << "\n:>>{abc2}<<"
                                );
    QTest::newRow("keyval2") << ">>{a=}<<" << "key%\\test/abc" <<  0 << 5 << 129
                            << "" << ""
                            << (QStringList()
                                << "a:>>{a=a}<<"
                                << "\n:>>{a=abc2}<<"
                                );
    QTest::newRow("keyval-replace") << ">>{a=f,bbb}<<" << "key%\\test/abc" <<  0 << 5 << 129
                            << "" << ""
                            << (QStringList()
                                << "a:>>{a=af,bbb}<<"
                                << "\n:>>{a=abc2,bbb}<<"
                                );
    QTest::newRow("special") << ">>{}<<" << "%abc" <<  0 << 3 << 129
                            << "" << ""
                            << (QStringList()
                                << "a:>>{a}<<"
                                << "\n:>>{abc3}<<"
                                );
    QTest::newRow("special2") << ">>{}<<" << "%abca" <<  0 << 3 << 257 // maybe unite keyval with context list ??? context does not replace old content ...
                            << "" << ""
                            << (QStringList()
                                << "a:>>{a}<<"
                                << "\n:>>{abc4}<<"
                                );
    QTest::newRow("special-replacement") << ">>{gh}<<" << "%abca" <<  0 << 3 << 257 // maybe unite keyval with context list ??? context does not replace old content ...
                            << "" << ""
                            << (QStringList()
                                << "a:>>{agh}<<"
                                << "\n:>>{abc4gh}<<"
                                );
    QTest::newRow("special3") << ">>{}<<" << "%abcd" <<  0 << 3 << 129 // keyvals refer to special
                            << "" << ""
                            << (QStringList()
                                << "a:>>{a}<<"
                                << "\n:>>{abc4}<<"
                                );
    QTest::newRow("cite") << ">>\\cit<<" << "" <<  0 << 6 << 0
                            << "" << ""
                            << (QStringList()
                                << "\n:>>\\cite{bibid}<<"
                                );
    QTest::newRow("cite2") << ">>{a}<<" << "" <<  0 << 4 << 32
                            << "" << ""
                            << (QStringList()
                                << "#:>>{a}<<"
                                );
    QTest::newRow("cite2") << ">>{ag,}<<" << "" <<  0 << 6 << 32
                            << "" << ""
                            << (QStringList()
                                << "a:>>{ag,a}<<"
                                << "\n:>>{ag,abcq}<<"
                                );
    QTest::newRow("cite-replace") << ">>{ag}<<" << "" <<  0 << 3 << 32
                            << "" << ""
                            << (QStringList()
                                << "a:>>{aag}<<"
                                << "\n:>>{abcq}<<"
                                );

}
void LatexCompleterTest::keyval(){
    QFETCH(QString, text);
    QFETCH(QString, workingDir);
    QFETCH(QString, preinsert);
    QFETCH(QString, preres);
    QFETCH(int, completerFlag);
    QFETCH(int, line);
    QFETCH(int, offset);
    QFETCH(QStringList, log);

    config->eowCompletes = false;

    edView->editor->cutBuffer = "";

    edView->editor->setFlag(QEditor::AutoCloseChars, false);
    edView->editor->setText(text, false);
    edView->editor->setCursor(edView->editor->document()->cursor(line,offset));

    if (!preinsert.isEmpty()) {
        edView->editor->insertText(preinsert);
        QEQUAL(edView->editor->text(), preres);
    }
    edView->getCompleter()->setWorkPath(workingDir);
    edView->complete(completerFlag);
    foreach (const QString& s, log){
        char key = s.at(0).toLatin1();
        if(key=='\n'){
            QTest::keyClick(edView->editor, Qt::Key_Return);
        }else{
            if(key!='#'){ // # means no input
                QTest::keyClick(edView->editor, key);
            }
        }
        QString text = s.mid(2);
        edView->editor->document()->setLineEndingDirect(QDocument::Unix,true);
        QString ist=edView->editor->text();
        QEQUAL(ist, text);
    }

    edView->editor->clearPlaceHolders();
    edView->editor->clearCursorMirrors();
}

#endif

