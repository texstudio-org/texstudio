#include "cursorposition.h"
#include "qdocument.h"
#include "qdocumentline.h"
#include "qdocumentcursor.h"

QDocumentLineTrackedHandle::QDocumentLineTrackedHandle(const QDocumentCursor &c):
    m_doc(nullptr), m_dlh(nullptr), m_oldLineNumber(0)
{
	if (c.isValid()) {
		m_doc = qobject_cast<QDocument *>(c.document());
		m_dlh = c.line().handle();
		m_oldLineNumber = c.lineNumber();
	}
}

int QDocumentLineTrackedHandle::lineNumber() const
{
	m_oldLineNumber = m_doc->indexOf(m_dlh);
	return m_oldLineNumber;
}

bool QDocumentLineTrackedHandle::isValid() const
{
	if (!m_doc) return false;
	m_oldLineNumber = m_doc->indexOf(m_dlh, m_oldLineNumber);
	return m_oldLineNumber >= 0;
}


CursorPosition::CursorPosition(const QDocumentCursor &c) :
	QDocumentLineTrackedHandle(c), m_columnNumber(0)
{
	if (m_dlh)
		m_columnNumber = c.columnNumber();
}

QDocumentCursor CursorPosition::toCursor()
{
	if (!m_doc) return QDocumentCursor();
	// update line number
	m_oldLineNumber = m_doc->indexOf(m_dlh, m_oldLineNumber);
	return QDocumentCursor(m_doc, m_oldLineNumber, m_columnNumber);
}

bool CursorPosition::equals(const CursorPosition &pos) const
{
	return (m_doc == pos.m_doc && m_dlh == pos.m_dlh && m_columnNumber == pos.m_columnNumber);
}
