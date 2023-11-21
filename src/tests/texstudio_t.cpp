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
