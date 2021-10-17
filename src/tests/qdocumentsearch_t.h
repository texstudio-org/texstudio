#ifndef Header_QDocument_Search_T
#define Header_QDocument_Search_T
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include <QtTest/QtTest>

class QEditor;
class QDocumentSearch;
class QDocumentSearchTest: public QObject{
	Q_OBJECT
	public:
		QDocumentSearchTest(QEditor* editor, bool all);
	private:
		QDocumentSearch *ds;
		QEditor *ed;
		bool all;
	private slots:
		void initTestCase();
		void next_sameText_data();
		void next_sameText();
		void replaceAll_data();
		void replaceAll();
		void searchAndFolding_data();
		void searchAndFolding();
		void cleanupTestCase();
};

#endif
#endif
