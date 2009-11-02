#ifndef QCETESTUTIL_H
#define QCETESTUTIL_H
#ifndef QT_NO_DEBUG
class QDocumentCursor;
QString cur2str(const QDocumentCursor &c);
void QCEEQUAL(const QDocumentCursor& c, const QDocumentCursor& expected);
void QCEEQUAL(const QDocumentCursor& c, const QDocumentCursor& d, const QDocumentCursor& expected); //triple comparison, all three should be equal
#endif
#endif
