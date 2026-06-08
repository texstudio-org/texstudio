
#ifndef QT_NO_DEBUG
#include "latexeditorview.h"
#include "latexdocument_t.h"
#include "testutil.h"
#include <QtTest/QtTest>

LatexDocumentTest::LatexDocumentTest(LatexEditorView* view): m_edView(view){
    m_doc=m_edView->getDocument();
}

/*!
 * Regression test for the use-after-free crash in LatexDocument::getListOfDocs()
 * (SIGABRT in getListOfDocs while rescanning a multi-file project).
 */
void LatexDocumentTest::getListOfDocsCacheInvalidation(){
    LatexDocuments docs;
    LatexDocument *master = new LatexDocument();
    LatexDocument *child = new LatexDocument();
    master->setFileName("/tmp/texstudio_test_master.tex");
    child->setFileName("/tmp/texstudio_test_child.tex");
    docs.addDocument(master, false); // visible master
    docs.addDocument(child, true);   // hidden included document

    // register child as an included document of master
    master->addChild(child);

    // first call builds and caches the project document list
    QList<LatexDocument *> before = master->getListOfDocs();
    QVERIFY2(before.contains(master), "master document missing from list");
    QVERIFY2(before.contains(child), "child document missing from list");

    // break the relationship: the cache must be invalidated so the stale
    // (potentially freed) child pointer is not returned again
    master->removeChild(child);
    QList<LatexDocument *> after = master->getListOfDocs();
    QVERIFY2(after.contains(master), "master document missing after removeChild");
    QVERIFY2(!after.contains(child), "stale child returned from cached project document list (cache not invalidated)");

    // docs has no destructor that deletes its documents, so free them here.
    // master->childDocs no longer references child and neither document holds
    // a masterDocument pointer, so deletion order is irrelevant.
    delete master;
    delete child;
}

#endif
