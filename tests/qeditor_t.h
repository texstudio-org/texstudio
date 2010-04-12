#ifndef QEDITORTEST_H
#define QEDITORTEST_H
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"

class QEditor;
class QEditorTest : public QObject
{
	Q_OBJECT
public:
	QEditorTest(QEditor* ed, bool executeAllTests);
	~QEditorTest();
private:
	bool allTests;
	QEditor* editor;
private slots:
	void loadSave_data();
	void loadSave();
	void foldedText_data();
	void foldedText();
	void passiveFolding_data();
	void passiveFolding();
	void activeFolding_data();
	void activeFolding();
	void indentation_data();
	void indentation();
};
#endif
#endif // QEDITORTEST_H
