#include "texstudio_t.h"

#include "testutil.h"
#include "texstudio.h"
#include <QtTest/QtTest>

extern Texstudio *txsInstance;

TexStudioTest::TexStudioTest()
{
}

void TexStudioTest::checkIncludes_data(){
    QTest::addColumn<QStringList>("files");

    QTest::newRow("simple")
        <<QStringList{QString(TESTDATADIR)+"/simple_document.tex"};
    QTest::newRow("top_with_two_level_include")
        <<QStringList{QString(TESTDATADIR)+"/top_with_two_level_include.tex"};
    QTest::newRow("top_with_two_level_include_as_second_file")
        <<QStringList{QString(TESTDATADIR)+"/included_level1.tex",QString(TESTDATADIR)+"/top_with_two_level_include.tex"};
    QTest::newRow("top_with_two_level_include_as_first_file")
        <<QStringList{QString(TESTDATADIR)+"/top_with_two_level_include.tex",QString(TESTDATADIR)+"/included_level1.tex"};
    QTest::newRow("top_with_subfile")
        <<QStringList{QString(TESTDATADIR)+"/top_with_subfile.tex"};
    QTest::newRow("subfile")
        <<QStringList{QString(TESTDATADIR)+"/subfile_level1.tex"};
}

void TexStudioTest::checkIncludes(){
    QFETCH(QStringList, files);
    Texstudio *txs=txsInstance;

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
    for(int i=0;i<doc->lineCount();i++){
        QDocumentLineHandle *dlh=doc->line(i).handle();
        QList<QFormatRange> formats=dlh->getOverlays(LatexEditorView::syntaxErrorFormat);
        if(!formats.isEmpty())
            synError=true;
    }
    QEQUAL(synError,false);
    for(int i=0;i<files.size();++i){
        txs->fileClose();
    }
}
