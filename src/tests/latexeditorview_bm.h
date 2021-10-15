#ifndef Header_Latex_Editor_View_Benchmark
#define Header_Latex_Editor_View_Benchmark
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
        void patch_data();
        void patch();
		void linePaint_data();
		void linePaint();
		void paintEvent_data();
		void paintEvent();
};

#endif
#endif
