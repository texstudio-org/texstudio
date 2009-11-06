#ifndef QT_NO_DEBUG
#include "testutil.h"
#include "qcetestutil.h"

#include "qdocumentcursor.h"
QString cur2str(const QDocumentCursor &c){
	if (c.hasSelection()) return QString("%1|%2|%3|%4").arg(c.anchorLineNumber()).arg(c.anchorColumnNumber()).arg(c.lineNumber()).arg(c.columnNumber());
	return QString("%1|%2").arg(c.lineNumber()).arg(c.columnNumber());
}
void QCEEQUAL(const QDocumentCursor& c, const QDocumentCursor& expected){
	QCEEQUAL2(c,expected,QString());
}
void QCEEQUAL(const QDocumentCursor& c, const QDocumentCursor& d, const QDocumentCursor& expected){
	QCEEQUAL2(c,expected,QString());
	QCEEQUAL2(d,expected,QString());
}
void QCEEQUAL2(const QDocumentCursor& c, const QDocumentCursor& expected, const QString& message){
	QEQUAL2(c.hasSelection(),expected.hasSelection(), " got-total: "+cur2str(c)+" expected-total: "+cur2str(expected)+" more: "+message);
	QEQUAL2(c.anchorLineNumber(),expected.anchorLineNumber(), " got-total: "+cur2str(c)+" expected-total: "+cur2str(expected)+" more: "+message);
	QEQUAL2(c.anchorColumnNumber(),expected.anchorColumnNumber(), " got-total: "+cur2str(c)+" expected-total: "+cur2str(expected)+" more: "+message);
	QEQUAL2(c.lineNumber(),expected.lineNumber(), " got-total: "+cur2str(c)+" expected-total: "+cur2str(expected)+" more: "+message);
	QEQUAL2(c.columnNumber(),expected.columnNumber(), " got-total: "+cur2str(c)+" expected-total: "+cur2str(expected)+" more: "+message);
}
#endif
