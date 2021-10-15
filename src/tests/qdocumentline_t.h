#ifndef Header_QDocument_LineTest
#define Header_QDocument_LineTest
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"

class QDocument;
class QDocumentLine;
class QDocumentLineHandle;
class QDocumentLineTest : public QObject
{
	Q_OBJECT
public:
	QDocumentLineTest();
	~QDocumentLineTest();
private:
	QDocument* doc;

	bool savedFixedPitch;
	int savedSpaceWidth, savedLeftPadding;
	bool savedWorkAroundFPM, savedWorkAroundFSCD, savedWorkAroundFQTL;
private slots:
	void initTestCase();
	void cleanupTestCase();

	void updateWrap_data();
	void updateWrap();
};
#endif
#endif // QEDITORTEST_H
