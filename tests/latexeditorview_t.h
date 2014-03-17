#ifndef LATEXEDITORVIEW_T_H
#define LATEXEDITORVIEW_T_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include <QtTest/QtTest>

class LatexEditorView;
class LatexEditorViewTest: public QObject{
	Q_OBJECT
	public:
		LatexEditorViewTest(LatexEditorView* view);
	private:
		LatexEditorView *edView;
	private slots:
		void insertHardLineBreaks_data();
		void insertHardLineBreaks();
};

#endif
#endif
