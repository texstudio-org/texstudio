#ifndef SYNTAXCHECK_T_H
#define SYNTAXCHECK_T_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "latexeditorview.h"

class SyntaxCheckTest: public QObject{
	Q_OBJECT
	public:
		SyntaxCheckTest(LatexEditorView* editor);
	private:
		LatexEditorView *edView;
	private slots:
		void checktabular_data();
		void checktabular();
};

#endif
#endif
