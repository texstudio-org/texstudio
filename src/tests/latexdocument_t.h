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
        QString unrollStructure(StructureEntry *baseStructure);
        StructureEntry* generateFromCoded(const QString &code);

        LatexEditorView *m_edView;
        LatexDocument *m_doc;
	private slots:
        void splitStructure_data();
        void splitStructure();
        void appendStructure_data();
        void appendStructure();
};

#endif
#endif
