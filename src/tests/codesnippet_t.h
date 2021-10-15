#ifndef Header_CodeSnippet_T
#define Header_CodeSnippet_T
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include <QtTest/QtTest>

class QEditor;
class CodeSnippetTest: public QObject{
	Q_OBJECT
	public:
		CodeSnippetTest(QEditor* editor);
	private:
		QEditor *ed;
	private slots:
		void initTestCase();
		void insert_data();
		void insert();
		void nestedInsert_data();
		void nestedInsert();
		void insertPlaceholderModes_data();
		void insertPlaceholderModes();
		void undoRedo_data();
		void undoRedo();
};

#endif
#endif
