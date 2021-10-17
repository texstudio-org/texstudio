#ifndef Header_StructureView_T
#define Header_StructureView_T
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "latexdocument.h"

class scriptengine;
class QEditor;
class LatexEditorView;
class StructureViewTest: public QObject{
	Q_OBJECT
	public:
		StructureViewTest(LatexEditorView* editor,LatexDocument *doc, bool all);
		QStringList unrollStructure(StructureEntry *baseStructure);
	private:
		LatexEditorView *edView;
		LatexDocument *document;
		bool all;
	private slots:
		void script_data();
		void script();
		void benchmark_data();
		void benchmark();
};

#endif
#endif
