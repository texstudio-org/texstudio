#ifndef SCRIPTENGINE_T_H
#define SCRIPTENGINE_T_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"

class scriptengine;
class LatexEditorView;
class ScriptEngineTest: public QObject{
	Q_OBJECT
	public:
		ScriptEngineTest(LatexEditorView* editor, bool all);
	private:
		LatexEditorView *edView;
		bool all;
	private slots:
		void script_data();
		void script();
};

#endif
#endif
