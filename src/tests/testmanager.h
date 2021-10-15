#ifndef Header_Test_Manager
#define Header_Test_Manager
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include <QAbstractNativeEventFilter>
//the only reason for this file is to separate the test headers from the remaining program
class LatexEditorView;
class QCodeEdit;
class QEditor;
class BuildManager;
class TestmanagerEventFilter : public QAbstractNativeEventFilter
{
public:
#if (QT_VERSION>=QT_VERSION_CHECK(6,0,0))
     virtual bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *) override;
#else
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *) override;
#endif
};

class TestManager : public QObject /*, public QAbstractNativeEventFilter*/ {
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
