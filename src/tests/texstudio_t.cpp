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
        <<QStringList{"/home/sdm/Dokumente/tex/testcases_structure/simple_document.tex"};

}

void TexStudioTest::checkIncludes(){
    QFETCH(QStringList, files);
    Texstudio *txs=txsInstance;

    LatexEditorView *edView;
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
    txs->fileClose();
}
