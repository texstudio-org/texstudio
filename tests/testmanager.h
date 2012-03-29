#ifndef TESTMANAGER_H
#define TESTMANAGER_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
//the only reason for this file is to separate the test headers from the remaining program
class LatexEditorView;
class QCodeEdit;
class QEditor;
class BuildManager;
class TestManager{
private:
	static QString performTest(QObject* obj);
public:
	enum TestLevel {TL_ALL, TL_FAST/*, TL_NONE*/};
	static QString execute(TestLevel level, LatexEditorView *edView, QCodeEdit* codeedit, QEditor* editor, BuildManager* buildManager);
};

#endif
#endif
