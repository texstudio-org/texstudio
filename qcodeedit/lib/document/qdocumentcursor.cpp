 /****************************************************************************
**
** Copyright (C) 2006-2008 fullmetalcoder <fullmetalcoder@hotmail.fr>
**
** This file is part of the Edyuk project <http://edyuk.org>
** 
** This file may be used under the terms of the GNU General Public License
** version 3 as published by the Free Software Foundation and appearing in the
** file GPL.txt included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "qdocumentcursor.h"

#include "qdocument_p.h"

/*!
	\file qdocumentcursor.cpp
	\brief Implementation of the QDocumentCursor class
*/

#include "qdocumentline.h"

/*!
	\class QDocumentCursor
	
	\brief A cursor to navigate within documents and edit them
	
	QDocumentCursor is a central class of the public API.
	
	It is the best (as in fastest and easiest) way to iterate over
	the content of a document.
	
	It is also the only class that allows to perform editing operations.
	
	A cursor position is defined by a line number and a text position
	within the line.
	
	Every cursor can have one or two cursor positions. In the later
	case, they delimit a selection. The first position set (before
	selecting) is referred to as the "anchor" and the other (if it
	is different from the anchor) is the actual cursor position.
*/

QDocumentCursor::QDocumentCursor(QDocument *doc)
 : m_handle(new QDocumentCursorHandle(doc))
{
	m_handle->ref();
}

QDocumentCursor::QDocumentCursor(const QDocumentCursor& cursor)
 : m_handle(0)
{
	if ( cursor.m_handle )
	{
		m_handle = cursor.m_handle->clone();
		m_handle->ref();
	}
}

QDocumentCursor::QDocumentCursor(QDocument *doc, int line, int column)
 : m_handle(new QDocumentCursorHandle(doc, line))
{
	m_handle->ref();
	
	m_handle->setColumnNumber(column);
}

/*
QDocumentCursor::QDocumentCursor(const QDocumentLine& line, int column)
 : m_handle(new QDocumentCursorHandle(line.document(), line.lineNumber()))
{
	m_handle->ref();
	
	m_handle->setColumnNumber(column);
	//movePosition(qMin(column, line.length()));
}
*/

QDocumentCursor::QDocumentCursor(QDocumentCursorHandle *handle)
 : m_handle(handle)
{
	if ( m_handle )
		m_handle->ref();
}

QDocumentCursor::~QDocumentCursor()
{
	if ( m_handle )
		m_handle->deref();
}

QDocumentCursor QDocumentCursor::clone() const
{
	return m_handle ? QDocumentCursor(m_handle->clone()) : QDocumentCursor();
}

QDocumentCursor& QDocumentCursor::operator = (const QDocumentCursor& c)
{
	#if 0
	if ( m_handle )
		m_handle->deref();
	
	m_handle = c.m_handle ? c.m_handle->clone() : 0;
	//m_handle = c.m_handle;
	
	if ( m_handle )
		m_handle->ref();
	#endif
	
	if ( c.m_handle )
	{
		if ( m_handle )
		{
			m_handle->copy(c.m_handle);
		} else {
			m_handle = c.m_handle->clone();
			m_handle->ref();
		}
	} else if ( m_handle ) {
		
		//qWarning("Setting a cursor to null");
		
		m_handle->deref();
		m_handle = 0;
	}
	
	return *this;
}

/*!
	\brief comparision operator
	
	\note If any of the operand is an invalid cursor, false is returned
*/
bool QDocumentCursor::operator == (const QDocumentCursor& c) const
{
	if ( !m_handle || !c.m_handle )
		return false;
	
	return m_handle->eq(c.m_handle);
}

/*!
	\brief comparision operator
	
	\note If any of the operand is an invalid cursor, true is returned (to preserve logical consistency with == )
*/
bool QDocumentCursor::operator != (const QDocumentCursor& c) const
{
	if ( !m_handle || !c.m_handle )
		return true;
	
	return !m_handle->eq(c.m_handle);
}

/*!
	\brief comparision operator
	
	\note If any of the operand is an invalid cursor, false is returned
*/
bool QDocumentCursor::operator < (const QDocumentCursor& c) const
{
	if ( !m_handle || !c.m_handle )
		return false;
	
	return m_handle->lt(c.m_handle);
}

/*!
	\brief comparision operator
	
	\note If any of the operand is an invalid cursor, false is returned
*/
bool QDocumentCursor::operator > (const QDocumentCursor& c) const
{
	if ( !m_handle || !c.m_handle )
		return false;
	
	return m_handle->gt(c.m_handle);
}

/*!
	\brief comparision operator
	
	\note If any of the operand is an invalid cursor, false is returned
*/
bool QDocumentCursor::operator <= (const QDocumentCursor& c) const
{
	if ( !m_handle || !c.m_handle )
		return false;
	
	return m_handle->gt(c.m_handle) || m_handle->eq(c.m_handle);
}

/*!
	\brief comparision operator
	
	\note If any of the operand is an invalid cursor, false is returned
*/
bool QDocumentCursor::operator >= (const QDocumentCursor& c) const
{
	if ( !m_handle || !c.m_handle )
		return false;
	
	return m_handle->lt(c.m_handle) || m_handle->eq(c.m_handle);
}

/*!
	\brief comparision operator
*/
bool QDocumentCursor::isNull() const
{
	return !m_handle || !m_handle->document();
}

/*!
	\brief comparision operator
*/
bool QDocumentCursor::isValid() const
{
	return m_handle && m_handle->document();
}

/*!
	\return whether the cursor is at the end of the document
*/
bool QDocumentCursor::atEnd() const
{
	return m_handle ? m_handle->atEnd() : false;
}

/*!
	\return whether the cursor is at the begining of the document
*/
bool QDocumentCursor::atStart() const
{
	return m_handle ? m_handle->atStart() : false;
}

/*!
	\return whether the cursor is at the end of a block
*/
bool QDocumentCursor::atBlockEnd() const
{
	return m_handle ? m_handle->atBlockEnd() : false;
}

/*!
	\return whether the cursor is at the start of a block
*/
bool QDocumentCursor::atBlockStart() const
{
	return m_handle ? m_handle->atBlockStart() : false;
}

/*!
	\return whether the cursor is at the end of a line
	
	\note this may only differ from atBlockEnd() on wrapped lines
*/
bool QDocumentCursor::atLineEnd() const
{
	return m_handle ? m_handle->atLineEnd() : false;
}

/*!
	\return whether the cursor is at the start of a line
	
	\note this may only differ from atBlockStart() on wrapped lines
*/
bool QDocumentCursor::atLineStart() const
{
	return m_handle ? m_handle->atLineStart() : false;
}

/*!
	\return the document on which this cursor operates
*/
QDocument* QDocumentCursor::document() const
{
	return m_handle ? m_handle->document() : 0;
}

/*!
	\return the text position (within the whole document) at which this cursor is
	
	\note available for compat with QTextCursor and ridiculously slow : avoid whenever possible
*/
int QDocumentCursor::position() const
{
	return m_handle ? m_handle->position() : -1;
}

/*!
	\return the text column of the anchor
*/
int QDocumentCursor::anchorColumn() const
{
	return m_handle ? m_handle->anchorColumn() : -1;
}

/*!
	\return the "visual" text column of the cursor
	
	\note this may only differ from columnNumber() when there are tabs on the line
*/
int QDocumentCursor::visualColumn() const
{
	return m_handle ? m_handle->visualColumn() : -1;
}

/*!
	\return the text column of the cursor
*/
int QDocumentCursor::columnNumber() const
{
	return m_handle ? m_handle->columnNumber() : -1;
}

/*!
	\brief Set the text column of the cursor
	\param c text column to set
	\param m move mode (determines whether text will be selected)
*/
void QDocumentCursor::setColumnNumber(int c, MoveMode m)
{
	if ( m_handle )
		m_handle->setColumnNumber(c, m);
}

/*!
	\return The line number to which the cursor points
*/
int QDocumentCursor::lineNumber() const
{
	return m_handle ? m_handle->lineNumber() : -1;
}

/*!
	\return the document position at which the cursor is
	
	Document position and viewport position are two terms used interchangeably.
	The only difference is the former refers to model perception (QDocument)
	whereas the later refers to view perception (QEditor)
*/
QPoint QDocumentCursor::documentPosition() const
{
	return m_handle ? m_handle->documentPosition() : QPoint();
}

/*!
	\return The line object at which this cursor points
*/
QDocumentLine QDocumentCursor::line() const
{
	return m_handle ? m_handle->line() : QDocumentLine();
}

/*!
	\brief Shift cursor position (text column) by a number of columns (characters)
*/
void QDocumentCursor::shift(int offset)
{
	if ( m_handle )
		m_handle->shift(offset);
}

/*!
	\brief Set the text position of the cursor (within the whole document)
	
	Remark made about position() applies.
*/
void QDocumentCursor::setPosition(int pos, MoveMode m)
{
	if ( m_handle )
		m_handle->setPosition(pos, m);
}

/*!
	\brief Moves the cursor position
	\param offset number of times the selected move will be done
	\param op movement type
	\param m movement mode (whether to select)
	\return true on succes
*/
bool QDocumentCursor::movePosition(int offset, MoveOperation op, MoveMode m)
{
	return m_handle ? m_handle->movePosition(offset, op, m) : false;
}

/*!
	\brief Jump to another cursor position
	\param line target line number
	\param colum target text column
*/
void QDocumentCursor::moveTo(int line, int column)
{
	if ( m_handle )
		m_handle->moveTo(line, column);
}

/*!
	\brief Jump to the position of another cursor
	\param c target cursor
*/
void QDocumentCursor::moveTo(const QDocumentCursor &c)
{
	if ( m_handle )
		m_handle->moveTo(c);
}

/*!
	\brief Jump to another cursor position
	\param l target line
	\param column target text column
	
	\note Calls QDocumentLine::lineNumber() => SLOW : avoid whenever possible
*/
void QDocumentCursor::moveTo(const QDocumentLine &l, int column)
{
	if ( m_handle )
		m_handle->moveTo(l.lineNumber(), column);
}

void QDocumentCursor::deleteChar()
{
	if ( m_handle )
		m_handle->deleteChar();
}

void QDocumentCursor::deletePreviousChar()
{
	if ( m_handle )
		m_handle->deletePreviousChar();
}


QChar QDocumentCursor::getPreviousChar() const
{
    return m_handle ? m_handle->getPreviousChar() : QChar(0);

}


void QDocumentCursor::eraseLine()
{
	if ( m_handle )
		m_handle->eraseLine();
}

void QDocumentCursor::insertLine()
{
	if ( m_handle )
		m_handle->insertText("\n");
}

void QDocumentCursor::insertText(const QString& s)
{
	if ( m_handle )
		m_handle->insertText(s);
}

QDocumentCursor QDocumentCursor::selectionStart() const
{
	return m_handle ? m_handle->selectionStart() : QDocumentCursor();
}

QDocumentCursor QDocumentCursor::selectionEnd() const
{
	return m_handle ? m_handle->selectionEnd() : QDocumentCursor();
}

QString QDocumentCursor::selectedText() const
{
	return m_handle ? m_handle->selectedText() : QString();
}

void QDocumentCursor::removeSelectedText()
{
	if ( m_handle )
		m_handle->removeSelectedText();
}

void QDocumentCursor::beginEditBlock()
{
	if ( m_handle )
		m_handle->beginEditBlock();
}

void QDocumentCursor::endEditBlock()
{
	if ( m_handle )
		m_handle->endEditBlock();
}

bool QDocumentCursor::isSilent() const
{
	return m_handle ? m_handle->isSilent() : true;
}

void QDocumentCursor::setSilent(bool y)
{
	if ( m_handle )
		m_handle->setSilent(y);
	
}

bool QDocumentCursor::isAutoUpdated() const
{
	return m_handle ? m_handle->isAutoUpdated() : true;
}

void QDocumentCursor::setAutoUpdated(bool y)
{
	if ( m_handle )
		m_handle->setAutoUpdated(y);
	
}

void QDocumentCursor::refreshColumnMemory()
{
	if ( m_handle )
		m_handle->refreshColumnMemory();
	
}

bool QDocumentCursor::hasColumnMemory() const
{
	return m_handle ? m_handle->hasColumnMemory() : false;
}

void QDocumentCursor::setColumnMemory(bool y)
{
	if ( m_handle )
		m_handle->setColumnMemory(y);
	
}

bool QDocumentCursor::hasSelection() const
{
	return m_handle ? m_handle->hasSelection() : false;
}

void QDocumentCursor::clearSelection()
{
	if ( m_handle )
		m_handle->clearSelection();
	
}

void QDocumentCursor::select(SelectionType t)
{
	if ( m_handle )
		m_handle->select(t);
	
}

void QDocumentCursor::setSelectionBoundary(const QDocumentCursor& c)
{
	if ( m_handle )
		m_handle->setSelectionBoundary(c);
	
}

bool QDocumentCursor::isWithinSelection(const QDocumentCursor& c) const
{
	return m_handle ? m_handle->isWithinSelection(c) : false;
}

QDocumentSelection QDocumentCursor::selection() const
{
	QDocumentSelection s;
	
	if ( isNull() || !hasSelection() )
	{
		qDebug("NULL selection");
		
		s.startLine = -1;
		s.endLine = -1;
		
		s.start = -1;
		s.end = -1;
	} else if ( m_handle->m_begLine == m_handle->m_endLine ) {
		
		s.startLine = m_handle->m_begLine;
		s.endLine = m_handle->m_begLine;
		
		s.start = qMin(m_handle->m_begOffset, m_handle->m_endOffset);
		s.end = qMax(m_handle->m_begOffset, m_handle->m_endOffset);
		
	} else if ( m_handle->m_begLine > m_handle->m_endLine ) {
		
		s.startLine = m_handle->m_endLine;
		s.endLine = m_handle->m_begLine;
		
		s.start = m_handle->m_endOffset;
		s.end = m_handle->m_begOffset;
		
		//qDebug("[(%i,%i);(%i,%i)]", s.startLine.lineNumber(), s.start, s.endLine.lineNumber(), s.end);
	} else {
		s.startLine = m_handle->m_begLine;
		s.endLine = m_handle->m_endLine;
		
		s.start = m_handle->m_begOffset;
		s.end = m_handle->m_endOffset;
		
		//qDebug("[(%i,%i);(%i,%i)]", s.startLine.lineNumber(), s.start, s.endLine.lineNumber(), s.end);
	}
	
	return s;
}
