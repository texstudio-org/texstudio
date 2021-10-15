#ifndef Header_Latex_Completer_T
#define Header_Latex_Completer_T
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include <QtTest/QtTest>

class LatexEditorView;
class LatexCompleterConfig;
class LatexCompleterTest: public QObject{
	Q_OBJECT
	public:
		LatexCompleterTest(LatexEditorView* view);
		~LatexCompleterTest();
	private:
		LatexEditorView *edView;
		LatexCompleterConfig *config;
		bool oldEowCompletes;
		int oldPrefered;
	private slots:
		void initTestCase();
		void simple_data();
		void simple();
        void keyval_data();
        void keyval();
};

#endif
#endif
