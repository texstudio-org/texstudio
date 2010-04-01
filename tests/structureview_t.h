#ifndef STRUCTUREVIEW_T_H
#define STRUCTUREVIEW_T_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "latexdocument.h"

class scriptengine;
class QEditor;
class StructureViewTest: public QObject{
	Q_OBJECT
	public:
		StructureViewTest(QEditor* editor,LatexDocument *doc);
		QStringList unrollStructure(StructureEntry *baseStructure);
	private:
		QEditor *ed;
		LatexDocument *document;
	private slots:
		void script_data();
		void script();
		void benchmark_data();
		void benchmark();
};

#endif
#endif
