#ifndef Header_QCE_TestUtil
#define Header_QCE_TestUtil
#ifndef QT_NO_DEBUG

#include "testutil.h"

class QDocumentCursor;
class QString;

QString cur2str(const QDocumentCursor &c);


void qceEqual(const QDocumentCursor& c, const QDocumentCursor& expected, const QString& message);
//triple comparison, all three should be equal:
void qceEqual(const QDocumentCursor& c, const QDocumentCursor& d, const QDocumentCursor& expected, const QString& message);


inline void QCEEQUAL(const QDocumentCursor & cursor,const QDocumentCursor & expected){
    qceEqual(cursor,expected,Q__POSITION__);
}

inline void QCEMULTIEQUAL(const QDocumentCursor & cursorA,const QDocumentCursor & cursorB,const QDocumentCursor & expected){
    qceEqual(cursorA,cursorB,expected,Q__POSITION__);
}

template <typename Type> inline void QCEEQUAL2(const QDocumentCursor & cursor,const QDocumentCursor & expected,Type message){
    qceEqual(cursor,expected,QString("%1 at %2").arg(message).arg(Q__POSITION__));
}

#endif
#endif
