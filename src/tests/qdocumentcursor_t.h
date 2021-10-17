#ifndef Header_QDocument_Cursor_T
#define Header_QDocument_Cursor_T
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include <QtTest/QtTest>

class QEditor;
class QDocument;
class QDocumentCursor;
class QDocumentCursorTest: public QObject{
	Q_OBJECT
public:
        QDocumentCursorTest(bool autoTests):doc(NULL),m_autoTests(autoTests){}
	private:
		QDocument *doc;
		bool m_autoTests;
		QDocumentCursor str2cur(const QString &s);
	private slots:
		void initTestCase();
		void constMethods_data();
		void constMethods();
		void const2Methods_data();
		void const2Methods();
		void subtractBoundaries_data();
		void subtractBoundaries();
		void movePosition_data();
		void movePosition();
		void bidiMoving_data();
		void bidiMoving();
		void isForwardSelection_data();
		void isForwardSelection();
		void columnMemory_data();
		void columnMemory();
		void cleanupTestCase();
};

#endif
#endif
