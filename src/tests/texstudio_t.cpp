#include "texstudio_t.h"

#include "testutil.h"
#include <QtTest/QtTest>

TexStudioTest::TexStudioTest()
{
    qDebug()<<"test";
}

void TexStudioTest::checkIncludes_data(){
    QTest::addColumn<QStringList>("files");

    QTest::newRow("simple")
        <<QStringList{"simple_document"};

}

void TexStudioTest::checkIncludes(){
    QFETCH(QStringList, files);
    /*

    bool inlineSyntaxChecking = edView->getConfig()->inlineSyntaxChecking;
    bool realtimeChecking = edView->getConfig()->realtimeChecking;

    edView->getConfig()->inlineSyntaxChecking = true;
    edView->getConfig()->realtimeChecking = true;

    for(const QString &fn:files){
        load(fn)
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
    QEQUAL(synError,error);

    edView->getConfig()->inlineSyntaxChecking = inlineSyntaxChecking;
    edView->getConfig()->realtimeChecking = realtimeChecking;*/
}
