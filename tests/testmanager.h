#ifndef TESTMANAGER_H
#define TESTMANAGER_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
//the only reason for this file is to separate the test headers from the remaining program
class LatexEditorView;
class QCodeEdit;
class QEditor;
class TestManager{
private:
	static QString performTest(QObject* obj);
public:
	static QString execute(LatexEditorView *edView, QCodeEdit* codeedit, QEditor* editor);
};

#endif
#endif
