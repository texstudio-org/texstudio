#ifndef QT_NO_DEBUG
#include "testutil.h"
#include "qcetestutil.h"

#include "qdocumentcursor.h"
QString cur2str(const QDocumentCursor &c){
	if (c.hasSelection()) return QString("%1|%2|%3|%4").arg(c.anchorLineNumber()).arg(c.anchorColumnNumber()).arg(c.lineNumber()).arg(c.columnNumber());
	return QString("%1|%2").arg(c.lineNumber()).arg(c.columnNumber());
}
void QCEEQUAL(const QDocumentCursor& c, const QDocumentCursor& expected){
	QEQUAL2(c.hasSelection(),expected.hasSelection(), " got-total: "+cur2str(c)+" expected-total: "+cur2str(expected));
	QEQUAL2(c.anchorLineNumber(),expected.anchorLineNumber(), " got-total: "+cur2str(c)+" expected-total: "+cur2str(expected));
	QEQUAL2(c.anchorColumnNumber(),expected.anchorColumnNumber(), " got-total: "+cur2str(c)+" expected-total: "+cur2str(expected));
	QEQUAL2(c.lineNumber(),expected.lineNumber(), " got-total: "+cur2str(c)+" expected-total: "+cur2str(expected));
	QEQUAL2(c.columnNumber(),expected.columnNumber(), " got-total: "+cur2str(c)+" expected-total: "+cur2str(expected));
}
void QCEEQUAL(const QDocumentCursor& c, const QDocumentCursor& d, const QDocumentCursor& expected){
	QCEEQUAL(c,expected);
	QCEEQUAL(d,expected);
}
#endif
