#ifndef SCRIPTENGINE_T_H
#define SCRIPTENGINE_T_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "qeditor.h"
#include <QtTest/QtTest>

class scriptengine;
class ScriptEngineTest: public QObject{
	Q_OBJECT
	public:
		ScriptEngineTest(QEditor* editor);
	private:
		QEditor *ed;
	private slots:
		void script_data();
		void script();
};

#endif
#endif
