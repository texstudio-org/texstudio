#ifndef QDOCUMENTCURSOR_T_H
#define QDOCUMENTCURSOR_T_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include <QtTest/QtTest>

class QEditor;
class QDocument;
class QDocumentCursor;
class QDocumentCursorTest: public QObject{
	Q_OBJECT
	private:
		QDocument *doc;
		QDocumentCursor str2cur(const QString &s);
	private slots:
		void initTestCase();
		void constMethods_data();
		void constMethods();
		void const2Methods_data();
		void const2Methods();
		void subtractBoundaries_data();
		void subtractBoundaries();
		void bidiMoving_data();
		void bidiMoving();
		void cleanupTestCase();
};

#endif
#endif
