#ifndef QEDITORTEST_H
#define QEDITORTEST_H
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"

class QEditor;
class QEditorTest : public QObject
{
	Q_OBJECT
public:
	QEditorTest(bool executeAllTests);
	~QEditorTest();
private:
	bool allTests;
	QEditor* editor;
private slots:
	void loadSave_data();
	void loadSave();
};
#endif
#endif // QEDITORTEST_H
