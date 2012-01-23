#ifndef LATEXEDITORVIEW_BM_H
#define LATEXEDITORVIEW_BM_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include <QtTest/QtTest>

class LatexEditorView;
class LatexEditorViewBenchmark: public QObject{
	Q_OBJECT
	public:
		LatexEditorViewBenchmark(LatexEditorView* view, bool all);
	private:
		LatexEditorView *edView;
		bool all;
	private slots:
		void documentChange_data();
		void documentChange();
		void linePaint_data();
		void linePaint();
		void paintEvent_data();
		void paintEvent();
};

#endif
#endif
