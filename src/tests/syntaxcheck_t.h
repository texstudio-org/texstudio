#ifndef Header_SyntaxCheck_T
#define Header_SyntaxCheck_T
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
        void checkkeyval_data();
        void checkkeyval();
        void checkArguments_data();
        void checkArguments();
        void checkMathHighlight_data();
        void checkMathHighlight();
        void checkAllowedMath_data();
        void checkAllowedMath();
};

#endif
#endif
