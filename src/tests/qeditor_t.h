#ifndef Header_QEditor_Test
#define Header_QEditor_Test
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"
#include "qdocument.h"

class QEditor;
class QEditorTest : public QObject
{
	Q_OBJECT
public:
	QEditorTest(QEditor* ed, bool executeAllTests);
	~QEditorTest();
private:
	bool checkIsOpen(QDocument *doc, int lineNr);

	bool allTests;
	QEditor* editor;
	QTextCodec* defaultCodec;
private slots:
	void setText_data();
	void setText();
	void loadSave_data();
	void loadSave();
	void foldedText_data();
	void foldedText();
	void passiveFolding_data();
	void passiveFolding();
	void activeFolding_data();
	void activeFolding();
	void insertTab_data();
	void insertTab();
	void indentation_data();
	void indentation();
	void autoClosing_data();
	void autoClosing();
};
#endif
#endif // QEDITORTEST_H
