#ifndef Header_QCE_TestUtil
#define Header_QCE_TestUtil
#ifndef QT_NO_DEBUG
class QDocumentCursor;
QString cur2str(const QDocumentCursor &c);

//defines can determine the current position
#define QCEEQUAL(c, expected) qceEqual(c, expected, Q__POSITION__)
#define QCEMULTIEQUAL(c, d, expected) qceEqual(c, d, expected, Q__POSITION__)
#define QCEEQUAL2(c, expected, message) qceEqual(c, expected, QString("%1 at %2").arg(message).arg(Q__POSITION__))

void qceEqual(const QDocumentCursor& c, const QDocumentCursor& expected, const QString& message);
//triple comparison, all three should be equal:
void qceEqual(const QDocumentCursor& c, const QDocumentCursor& d, const QDocumentCursor& expected, const QString& message); 
#endif
#endif
