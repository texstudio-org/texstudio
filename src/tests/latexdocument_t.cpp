
#ifndef QT_NO_DEBUG
#include "latexeditorview.h"
#include "latexdocument_t.h"
#include "testutil.h"
#include <QtTest/QtTest>

LatexDocumentTest::LatexDocumentTest(LatexEditorView* view): m_edView(view){
    m_doc=m_edView->getDocument();
}

#endif

