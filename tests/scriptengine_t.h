#ifndef SCRIPTENGINE_T_H
#define SCRIPTENGINE_T_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"

class scriptengine;
class QEditor;
class ScriptEngineTest: public QObject{
	Q_OBJECT
	public:
		ScriptEngineTest(QEditor* editor, bool all);
	private:
		QEditor *ed;
		bool all;
	private slots:
		void script_data();
		void script();
};

#endif
#endif
