#ifndef Header_LatexDocumentTest_T
#define Header_LatexDocumentTest_T
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "latexdocument.h"
#include <QtTest/QtTest>

class LatexEditorView;
class LatexDocumentTest: public QObject{
	Q_OBJECT
	public:
        LatexDocumentTest(LatexEditorView* view);
	private:
        LatexEditorView *m_edView;
        LatexDocument *m_doc;
	private slots:
};

#endif
#endif
