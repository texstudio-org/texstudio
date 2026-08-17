#include "texstudio_t.h"

#include "testutil.h"
#include "texstudio.h"
#include <QtTest/QtTest>

extern Texstudio *txsInstance;

void TexStudioTest::checkIncludes_data(){
    if (!allTests){
        qDebug("skipped includes tests");
        return;
    }

    QTest::addColumn<QStringList>("files");
    QTest::addColumn<bool>("refPresent");

    QTest::newRow("simple")
        <<QStringList{QString(TESTDATADIR)+"/simple_document.tex"}<<false;
    QTest::newRow("top_with_two_level_include")
        <<QStringList{QString(TESTDATADIR)+"/top_with_two_level_include.tex"}<<true;
    QTest::newRow("top_with_two_level_include_as_second_file")
        <<QStringList{QString(TESTDATADIR)+"/included_level1.tex",QString(TESTDATADIR)+"/top_with_two_level_include.tex"}<<true;
    QTest::newRow("top_with_two_level_include_as_first_file")
        <<QStringList{QString(TESTDATADIR)+"/top_with_two_level_include.tex",QString(TESTDATADIR)+"/included_level1.tex"}<<true;
    QTest::newRow("top_with_subfile")
        <<QStringList{QString(TESTDATADIR)+"/top_with_subfile.tex"}<<false;
    QTest::newRow("subfile")
        <<QStringList{QString(TESTDATADIR)+"/subfile_level1.tex"}<<false;
    QTest::newRow("eqref")
        <<QStringList{QString(TESTDATADIR)+"/test_eqref.tex"}<<true;
    QTest::newRow("eqref via include")
        <<QStringList{QString(TESTDATADIR)+"/test_eqref_top.tex"}<<true;
    QTest::newRow("2 level include")
        <<QStringList{QString(TESTDATADIR)+"/top.tex",QString(TESTDATADIR)+"/a1.tex",QString(TESTDATADIR)+"/a2.tex"}<<false;
    QTest::newRow("2 level include, out of order")
        <<QStringList{QString(TESTDATADIR)+"/top.tex",QString(TESTDATADIR)+"/a2.tex",QString(TESTDATADIR)+"/a1.tex"}<<false;
    QTest::newRow("2 level include, buried package")
        <<QStringList{QString(TESTDATADIR)+"/included_level1a.tex",QString(TESTDATADIR)+"/included_level2a.tex",QString(TESTDATADIR)+"/top_buried_package.tex"}<<true;
    QTest::newRow("usercommands")
        <<QStringList{QString(TESTDATADIR)+"/usercommands.tex"}<<false;
}

void TexStudioTest::checkIncludes(){
    if (!allTests){
        qDebug("skipped includes tests");
        return;
    }
    QFETCH(QStringList, files);
    QFETCH(bool, refPresent);

    Texstudio *txs=txsInstance;

    // deactivate caching
    auto *conf=dynamic_cast<ConfigManager *>(ConfigManagerInterface::getInstance());
    bool cacheDocs=conf->cacheDocuments;
    conf->cacheDocuments=false;

    QList<LatexEditorView *> edViews;
    for(const QString &fn:files){
        LatexEditorView *edView=txs->load(fn);
        if(!edView){
            qDebug()<<"test file not found ! Skip !";
            return;
        }
        edViews<<edView;
    }
    for(const LatexEditorView* edView:edViews){
        LatexDocument *doc=edView->getDocument();
        doc->synChecker.waitForQueueProcess(); // wait for syntax checker to finish (as it runs in a parallel thread)
    }

    LatexDocument *doc=edViews.last()->getDocument();
    bool synError=false;
    bool refFound=false;
    for(int i=0;i<doc->lineCount();i++){
        QDocumentLineHandle *dlh=doc->line(i).handle();
        QList<QFormatRange> formats=dlh->getOverlays(LatexEditorView::syntaxErrorFormat);
        if(!formats.isEmpty())
            synError=true;
        formats=dlh->getOverlays(LatexEditorView::referencePresentFormat);
        if(!formats.isEmpty())
            refFound=true;
    }
    // cache information
    conf->cacheDocuments=true;

    for(int i=0;i<files.size();++i){
        txs->fileClose();
    }
    // restore previous cache setting
    conf->cacheDocuments=cacheDocs;

    QEQUAL(synError,false);
    QEQUAL(refFound,refPresent);
}

void TexStudioTest::checkIncludesCached_data(){
    if (!allTests){
        qDebug("skipped includes tests");
        return;
    }

    QTest::addColumn<QStringList>("files");
    QTest::addColumn<bool>("refPresent");

    QTest::newRow("simple")
        <<QStringList{QString(TESTDATADIR)+"/simple_document.tex"}<<false;
    QTest::newRow("top_with_two_level_include")
        <<QStringList{QString(TESTDATADIR)+"/top_with_two_level_include.tex"}<<true;
    QTest::newRow("top_with_two_level_include_as_second_file")
        <<QStringList{QString(TESTDATADIR)+"/included_level1.tex",QString(TESTDATADIR)+"/top_with_two_level_include.tex"}<<true;
    QTest::newRow("top_with_two_level_include_as_first_file")
        <<QStringList{QString(TESTDATADIR)+"/top_with_two_level_include.tex",QString(TESTDATADIR)+"/included_level1.tex"}<<true;
    QTest::newRow("top_with_subfile")
        <<QStringList{QString(TESTDATADIR)+"/top_with_subfile.tex"}<<false;
    QTest::newRow("subfile")
        <<QStringList{QString(TESTDATADIR)+"/subfile_level1.tex"}<<false;
    QTest::newRow("eqref")
        <<QStringList{QString(TESTDATADIR)+"/test_eqref.tex"}<<true;
    QTest::newRow("eqref via include")
        <<QStringList{QString(TESTDATADIR)+"/test_eqref_top.tex"}<<true;
    QTest::newRow("2 level include")
        <<QStringList{QString(TESTDATADIR)+"/top.tex",QString(TESTDATADIR)+"/a1.tex",QString(TESTDATADIR)+"/a2.tex"}<<false;
    QTest::newRow("2 level include, out of order")
        <<QStringList{QString(TESTDATADIR)+"/top.tex",QString(TESTDATADIR)+"/a2.tex",QString(TESTDATADIR)+"/a1.tex"}<<false;
    QTest::newRow("2 level include, buried package")
        <<QStringList{QString(TESTDATADIR)+"/included_level1a.tex",QString(TESTDATADIR)+"/included_level2a.tex",QString(TESTDATADIR)+"/top_buried_package.tex"}<<true;
}

void TexStudioTest::checkIncludesCached(){
    if (!allTests){
        qDebug("skipped includes tests");
        return;
    }
    QFETCH(QStringList, files);
    QFETCH(bool, refPresent);

    Texstudio *txs=txsInstance;
    // used cached docs
    auto *conf=dynamic_cast<ConfigManager *>(ConfigManagerInterface::getInstance());
    bool cacheDocs=conf->cacheDocuments;
    conf->cacheDocuments=true;

    LatexEditorView *edView=nullptr;
    for(const QString &fn:files){
        edView=txs->load(fn);
    }
    if(!edView){
        qDebug()<<"test file not found ! Skip !";
        return;
    }
    LatexDocument *doc=edView->getDocument();
    doc->synChecker.waitForQueueProcess(); // wait for syntax checker to finish (as it runs in a parallel thread)

    bool synError=false;
    bool refFound=false;
    for(int i=0;i<doc->lineCount();i++){
        QDocumentLineHandle *dlh=doc->line(i).handle();
        QList<QFormatRange> formats=dlh->getOverlays(LatexEditorView::syntaxErrorFormat);
        if(!formats.isEmpty())
            synError=true;
        formats=dlh->getOverlays(LatexEditorView::referencePresentFormat);
        if(!formats.isEmpty())
            refFound=true;
    }
    for(int i=0;i<files.size();++i){
        txs->fileClose();
    }
    // restore previous cache setting
    conf->cacheDocuments=cacheDocs;

    QEQUAL(synError,false);
    QEQUAL(refFound,refPresent);
}

void TexStudioTest::normalCompletion_data(){
    QTest::addColumn<QString>("text");
    QTest::addColumn<int>("line");
    QTest::addColumn<int>("column");
    QTest::addColumn<LatexCompleter::CompletionFlags>("flags");

    QTest::newRow("command") << QStringLiteral("\\be") << 0 << 3 << LatexCompleter::CompletionFlags();
    QTest::newRow("environment") << QStringLiteral("\\begin{doc") << 0 << 11 << LatexCompleter::CompletionFlags();
    QTest::newRow("ref") << QStringLiteral("\\label{test}\\ref{t") << 0 << 18 << LatexCompleter::CompletionFlags(LatexCompleter::CF_FORCE_REF);
    QTest::newRow("cite") << QStringLiteral("\\bibitem{test}\\cite{t") << 0 << int(QStringLiteral("\\bibitem{test}\\cite{t").size()) << LatexCompleter::CompletionFlags(LatexCompleter::CF_FORCE_CITE);
    //QTest::newRow("package") << QStringLiteral("\\usepackage{a") << 0 << int(QStringLiteral("\\usepackage{a").size()) << LatexCompleter::CompletionFlags(LatexCompleter::CF_FORCE_PACKAGE);
    //QTest::newRow("graphic") << QStringLiteral("\\usepackage{graphicx}\\includegraphics{f") << 0 << int(QStringLiteral("\\usepackage{graphicx}\\includegraphics{f").size()) << LatexCompleter::CompletionFlags(LatexCompleter::CF_FORCE_GRAPHIC);
    QTest::newRow("keyval_key") << QStringLiteral("\\usepackage{fancyvrb}\\fvset{f") << 0 << int(QStringLiteral("\\usepackage{fancyvrb}\\fvset{f").size()) << LatexCompleter::CompletionFlags(LatexCompleter::CF_FORCE_KEYVAL);
    QTest::newRow("keyval_valAfterEqual") << QStringLiteral("\\usepackage{fancyvrb}\\fvset{frame=") << 0 << int(QStringLiteral("\\usepackage{fancyvrb}\\fvset{frame=").size()) << LatexCompleter::CompletionFlags(LatexCompleter::CF_FORCE_KEYVAL);
    QTest::newRow("keyval_val") << QStringLiteral("\\usepackage{fancyvrb}\\fvset{frame=s") << 0 << int(QStringLiteral("\\usepackage{fancyvrb}\\fvset{frame=s").size()) << LatexCompleter::CompletionFlags(LatexCompleter::CF_FORCE_KEYVAL);
    QTest::newRow("keyval_keyAfterComma") << QStringLiteral("\\usepackage{fancyvrb}\\fvset{frame=s,") << 0 << int(QStringLiteral("\\usepackage{fancyvrb}\\fvset{frame=s,").size()) << LatexCompleter::CompletionFlags(LatexCompleter::CF_FORCE_KEYVAL);
}

void TexStudioTest::normalCompletion(){
    QFETCH(QString, text);
    QFETCH(int, line);
    QFETCH(int, column);
    QFETCH(LatexCompleter::CompletionFlags, flags);

    Texstudio *txs = txsInstance;
    QVERIFY2(txs, "The Texstudio instance must exist for completion tests");

    LatexEditorView *edView = txs->currentEditorView();
    if (!edView) {
        QVERIFY2(QMetaObject::invokeMethod(txs, "fileNewInternal", Qt::DirectConnection), "A new document should be created for completion tests");
        edView = txs->currentEditorView();
    }
    QVERIFY2(edView, "A LatexEditorView must be available for completion tests");
    QVERIFY2(edView->editor, "The editor should be created before invoking completion");

    edView->editor->setText(text, false);
    edView->editor->setCursor(edView->editor->document()->cursor(line, column));
    LatexEditorView::getCompleter()->close();
    QCoreApplication::processEvents();

    QVERIFY2(!LatexEditorView::getCompleter()->isVisible(), "The completer should start closed before invoking normal completion");
    QVERIFY2(QMetaObject::invokeMethod(txs, "normalCompletion", Qt::DirectConnection), "normalCompletion should be invokable");
    QCoreApplication::processEvents();
    QVERIFY2(LatexEditorView::getCompleter()->isVisible(), "normalCompletion should open the completion popup");
    QVERIFY2(LatexEditorView::getCompleter()->countWords() > 0, "normalCompletion should produce completion entries");
    QVERIFY2(gatherCompletionFlags() == flags, "normalCompletion should set the correct completion flags");
    LatexEditorView::getCompleter()->close();
}
/*!
 * \brief recreate the completion flags from the current configuration
 * Converts the current configuration into a set of completion flags that can be used to control the behavior of the completion engine.
 * \return
 */
LatexCompleter::CompletionFlags TexStudioTest::gatherCompletionFlags()
{
    LatexCompleter *completer = LatexEditorView::getCompleter();
    LatexCompleter::CompletionFlags flags;
    if(completer){
        if(completer->forcedCite)
            flags |= LatexCompleter::CF_FORCE_CITE;
        if(completer->forcedRef)
            flags |= LatexCompleter::CF_FORCE_REF;
        if(completer->forcedPackage)
            flags |= LatexCompleter::CF_FORCE_PACKAGE;
        if(completer->forcedGraphic)
            flags |= LatexCompleter::CF_FORCE_GRAPHIC;
        if(completer->forcedKeyval)
            flags |= LatexCompleter::CF_FORCE_KEYVAL;
        if(completer->forcedSpecialOption)
            flags |= LatexCompleter::CF_FORCE_SPECIALOPTION;
        if(completer->forcedLength)
            flags |= LatexCompleter::CF_FORCE_LENGTH;
    }
    return flags;
}
