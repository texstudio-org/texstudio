#ifndef TESTMANAGER_H
#define TESTMANAGER_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include <QAbstractNativeEventFilter>
//the only reason for this file is to separate the test headers from the remaining program
class LatexEditorView;
class QCodeEdit;
class QEditor;
class BuildManager;
class TestManager : public QObject, public QAbstractNativeEventFilter {
	Q_OBJECT
public:
	enum TestLevel {TL_ALL, TL_FAST,TL_AUTO/*, TL_NONE*/};
	QString execute(TestLevel level, LatexEditorView *edView, QCodeEdit* codeedit, QEditor* editor, BuildManager* buildManager);
signals:
	void newMessage(const QString &m);
private:
	QString performTest(QObject* obj);
	bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);
};

#endif
#endif
