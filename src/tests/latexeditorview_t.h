#ifndef Header_Latex_Editor_View_T
#define Header_Latex_Editor_View_T
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
		void inMathEnvironment_data();
		void inMathEnvironment();
};

#endif
#endif
