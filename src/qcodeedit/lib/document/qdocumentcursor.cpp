 /****************************************************************************
**
** Copyright (C) 2006-2009 fullmetalcoder <fullmetalcoder@hotmail.fr>
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

/*!
	\file qdocumentcursor.cpp
	\brief Implementation of the QDocumentCursor class
*/

#include "qdocumentcursor.h"

/*!
	\ingroup document
	@{
*/

#include "qdocument_p.h"

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
	
	When the cursor does not have a selection, querying informations about
	the anchor has the same result as querying informations about the cursor
	position.
	
	Informations you can get about both the anchor and the posiotion :
	<ul>
	<li>the line number : the logical line to which the cursor position points inside the document
	<li>the column number : the logical text column to which the cursor position points to, inside the pointed line.
	<li>the wrapped line offset : when a cursor resides on a wrapped line, this indicates in which part of
	the wrapped line it does
	<li>the document position : document (x, y) coordinates corresponding to the place the cursor is drawn
	</ul>
	
	The visual line to which a given cursor resides can be obtained as follows :
	
	\code
	int visual_line = cursor.document()->visualLine(cursor.lineNumber()) + cursor.wrappedLineOffset();
	\endcode
	
	\note The line and column numbers passed to/returned by a cursor method
	always start at zero.

	\note Quick overview of the various coordinate systems :
	<ul>
		<li>document coordinates aka viewport coordinates : (x, y) coords, in pixels, origin at the top left corner of
		the rectangle occupied by the very first line of the document
		<li>text coordinates : (line, column) in logical units (number of lines, number of characters)
		<li>visual text coordinates : (line, column) in logical units but with a different mapping
	</ul>
*/

QDocumentCursor::QDocumentCursor(QDocument *doc)
 : QObject(nullptr),m_handle(new QDocumentCursorHandle(doc))
{
	m_handle->ref();
}

QDocumentCursor::QDocumentCursor(const QDocumentCursor& from, const QDocumentCursor& to): QObject(nullptr){
	Q_ASSERT(from.document() == to.document());
	Q_ASSERT(from.handle());
	Q_ASSERT(to.handle());
	Q_ASSERT(from.hasSelection() == false);
	Q_ASSERT(to.hasSelection() == false);

	m_handle = new QDocumentCursorHandle(from.document());
	m_handle->m_endLine = from.lineNumber();
	m_handle->m_endOffset = from.columnNumber();
	m_handle->m_begLine = to.lineNumber();
	m_handle->m_begOffset = to.columnNumber();
}

QDocumentCursor::QDocumentCursor(const QDocumentCursor& cursor)
 : QObject(nullptr),m_handle(nullptr)
{
	if ( cursor.m_handle )
	{
		m_handle = cursor.m_handle->clone(true);
		m_handle->ref();
	}
}

QDocumentCursor::QDocumentCursor(const QDocumentCursor& cursor, const bool cloneAutoUpdateFlag)
 : QObject(nullptr),m_handle(nullptr)
{
	if ( cursor.m_handle )
	{
		m_handle = cursor.m_handle->clone(cloneAutoUpdateFlag);
		m_handle->ref();
	}
}



QDocumentCursor::QDocumentCursor(QDocument *doc, int line, int column, int lineTo, int columnTo)
 : QObject(nullptr),m_handle(new QDocumentCursorHandle(doc, line, column, lineTo, columnTo))
{
	m_handle->ref();
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
 : QObject(nullptr),m_handle(handle)
{
	if ( m_handle )
		m_handle->ref();
}

QDocumentCursor::~QDocumentCursor()
{
	if ( m_handle )
		m_handle->deref();
}

QDocumentCursor QDocumentCursor::clone(bool cloneAutoUpdatedFlag) const
{
	return m_handle ? QDocumentCursor(m_handle->clone(cloneAutoUpdatedFlag)) : QDocumentCursor();
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
			m_handle->copy(c.m_handle); //warning: this is inconsistent, a copied cursor is never auto updated,
		} else {                            //but the clones is. (there was however a reason for this behaviour)
			m_handle = c.m_handle->clone(true);
			m_handle->ref();
		}
	} else if ( m_handle ) {
		
		//qWarning("Setting a cursor to null");
		
		m_handle->deref();
        m_handle = nullptr;
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
	
	return m_handle->lt(c.m_handle) || m_handle->eq(c.m_handle);
}

/*!
	\brief comparision operator
	
	\note If any of the operand is an invalid cursor, false is returned
*/
bool QDocumentCursor::operator >= (const QDocumentCursor& c) const
{
	if ( !m_handle || !c.m_handle )
		return false;
	
	return m_handle->gt(c.m_handle) || m_handle->eq(c.m_handle);
}

/*!
	\brief comparision operator
*/
bool QDocumentCursor::isNull() const
{
	return !m_handle || !m_handle->document() || !line().isValid();
}

bool QDocumentCursor::beginBoundaryLarger (const QDocumentCursor& c) const{
	if (!m_handle || !c.m_handle) return false;
	int line1, col1;
	m_handle->beginBoundary(line1,col1);
	int line2, col2;
	c.m_handle->beginBoundary(line2,col2);
	if (line1==line2)
		return col1>col2;
	else 
		return line1>line2;	
}

bool QDocumentCursor::equalBoundaries(const QDocumentCursor& c) const{
	if (!m_handle) return false;
	if (m_handle == c.m_handle) return true;
	return m_handle->equalBoundaries(c.m_handle);
}

bool QDocumentCursor::equal(const QDocumentCursor& c) const{
	if (!m_handle) return false;
	if (m_handle == c.m_handle) return true;
	return m_handle->equal(c.m_handle);
}


/*!
  Returns if my right boundary is larger (line/offset) than c
*/
bool QDocumentCursor::endBoundaryLarger (const QDocumentCursor& c) const{
	if (!m_handle || !c.m_handle) return false;
	int line1, col1;
	m_handle->endBoundary(line1,col1);
	int line2, col2;
	c.m_handle->endBoundary(line2,col2);
	if (line1==line2)
		return col1>col2;
	else 
		return line1>line2;	
}

void QDocumentCursor::beginBoundary(int& begline, int& begcol) const{
	if (!m_handle) {
		begline=-1;
		begcol=-1;
		return;
	}
	m_handle->beginBoundary(begline, begcol);
}
void QDocumentCursor::endBoundary(int& endline, int& endcol) const{
	if (!m_handle) {
		endline=-1;
		endcol=-1;
		return;
	}
	m_handle->endBoundary(endline, endcol);
}
void QDocumentCursor::boundaries(int& begline, int& begcol, int& endline, int& endcol) const{
	if (!m_handle) {
		begline=begcol=endline=endcol=-1;
		return;
	}
	m_handle->boundaries(begline,begcol,endline,endcol);
}


/*!
	\brief comparision operator
*/
bool QDocumentCursor::isValid() const
{
	return m_handle && m_handle->document() && line().isValid();
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
    return m_handle ? m_handle->document() : nullptr;
}

/*!
	\return the text column of the anchor
*/
int QDocumentCursor::anchorColumnNumber() const
{
	return m_handle ? m_handle->anchorColumnNumber() : -1;
}

int QDocumentCursor::startLineNumber() const{
	return m_handle ? m_handle->startLineNumber() : -1;
}
int QDocumentCursor::startColumnNumber() const{
	return m_handle ? m_handle->startColumnNumber() : -1;
}

int QDocumentCursor::endLineNumber() const{
	return m_handle ? m_handle->endLineNumber() : -1;
}
int QDocumentCursor::endColumnNumber() const{
	return m_handle ? m_handle->endColumnNumber() : -1;
}


/*!
	\return the "visual" text column of the cursor
	
	\note this may only differ from columnNumber() when there are tabs on the line
*/
int QDocumentCursor::visualColumnNumber() const
{
	return m_handle ? m_handle->visualColumnNumber() : -1;
}

/*!
	\return the text column of the cursor
*/
int QDocumentCursor::columnNumber() const
{
	return m_handle ? m_handle->columnNumber() : -1;
}


void QDocumentCursor::setLineNumber(int l, MoveMode m)
{
	if ( m_handle )
		m_handle->setLineNumber(l, m);
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

void QDocumentCursor::setAnchorLineNumber(int c) const{
	if ( m_handle )
		m_handle->setAnchorLineNumber(c);
}

void QDocumentCursor::setAnchorColumnNumber(int c) const{
	if ( m_handle )
		m_handle->setAnchorColumnNumber(c);
}


/*!
	\return The line number to which the cursor points
*/
int QDocumentCursor::lineNumber() const
{
	return m_handle ? m_handle->lineNumber() : -1;
}

/*!
	\return The line number to which the cursor points
*/
int QDocumentCursor::anchorLineNumber() const
{
	return m_handle ? m_handle->anchorLineNumber() : -1;
}

/*!
	\return The wrapped line on which the cursor resides
	
	Wrapped line are "sublines" of logical lines.
*/
int QDocumentCursor::wrappedLineOffset() const
{
	return line().wrappedLineForCursor(columnNumber());
}

/*!
	\return The line number on which the anchor resides
*/
int QDocumentCursor::anchorWrappedLineOffset() const
{
	return anchorLine().wrappedLineForCursor(anchorColumnNumber());
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
	\return the document position of the anchor
*/
QPoint QDocumentCursor::anchorDocumentPosition() const
{
	return m_handle ? m_handle->anchorDocumentPosition() : QPoint();
}

QPolygon QDocumentCursor::documentRegion() const
{
	return m_handle ? m_handle->documentRegion() : QPolygon();
}

/*!
	\return The line object on which the cursor resides
*/
QDocumentLine QDocumentCursor::line() const
{
	return m_handle ? m_handle->line() : QDocumentLine();
}

/*!
	\return The line object on which the anchor resides
*/
QDocumentLine QDocumentCursor::anchorLine() const
{
	return m_handle ? m_handle->anchorLine() : QDocumentLine();
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
void QDocumentCursor::moveTo(int line, int column, MoveMode m)
{
	if ( m_handle )
		m_handle->moveTo(line, column,m);
}


/*!
	\brief Jump to the position of another cursor
	\param c target cursor
*/
void QDocumentCursor::moveTo(const QDocumentCursor &c, MoveMode m)
{
	if ( m_handle )
		m_handle->moveTo(c,m);
}

/*!
	\brief Jump to another cursor position
	\param l target line
	\param column target text column
	
	\note Calls QDocumentLine::lineNumber() => SLOW : avoid whenever possible
*/
/*void QDocumentCursor::moveTo(const QDocumentLine &l, int column, MoveMode m)
{
	if ( m_handle )
		m_handle->moveTo(l.lineNumber(), column, m);
}*/

/*!
	\return the character at the position immediately after the cursor
*/
QChar QDocumentCursor::nextChar() const
{
	return m_handle ? m_handle->nextChar() : QChar();
}

/*!
	\return the character at the position immediately before the cursor
*/
QChar QDocumentCursor::previousChar() const
{
	return m_handle ? m_handle->previousChar() : QChar();
}

/*!
	\brief Delete the character at the position immediately after the cursor
*/
void QDocumentCursor::deleteChar()
{
	if ( m_handle )
		m_handle->deleteChar();
}

/*!
	\brief Delete the character at the position immediately before the cursor
*/
void QDocumentCursor::deletePreviousChar()
{
	if ( m_handle )
		m_handle->deletePreviousChar();
}

/*!
	\brief erase the whole line the cursor is on, newline included
*/
void QDocumentCursor::eraseLine()
{
	if ( m_handle )
		m_handle->eraseLine();
}

/*!
	\brief insert a new line at the cursor position
*/
void QDocumentCursor::insertLine(bool keepAnchor)
{
	if ( m_handle )
		m_handle->insertText("\n", keepAnchor);
}

/*!
	\brief insert some text at the cursor position
	
	Selected text will be removed before insertion happens.
	
	\note Nothing happens if \a s is empty
*/
void QDocumentCursor::insertText(const QString& s, bool keepAnchor)
{
	if ( m_handle )
		m_handle->insertText(s, keepAnchor);
}

/*!
	\return A cursor pointing at the position of the selection start.
	
	Selection start is the position of the selection that is nearest to document start.
	
	\note an invalid cursor is returned when the cursor does not have a selection
*/
QDocumentCursor QDocumentCursor::selectionStart() const
{
	return m_handle ? m_handle->selectionStart() : QDocumentCursor();
}

/*!
	\return A cursor pointing at the position of the selection end.
	
	Selection end is the position of the selection that is nearest to document end.
	
	\note an invalid cursor is returned when the cursor does not have a selection
*/
QDocumentCursor QDocumentCursor::selectionEnd() const
{
	return m_handle ? m_handle->selectionEnd() : QDocumentCursor();
}

/*!
	\return A cursor pointing at the position of the anchor.
*/
QDocumentCursor QDocumentCursor::anchorCursor() const
{
	return m_handle ? m_handle->anchorCursor() : QDocumentCursor();
}

/*!
	\return The selected text
*/
QString QDocumentCursor::selectedText() const
{
	return m_handle ? m_handle->selectedText() : QString();
}


/*!
	\brief Remove the selected text
*/
void QDocumentCursor::removeSelectedText()
{
	if ( m_handle )
		m_handle->removeSelectedText();
}

/*!
	\brief Replace the selected text
	
	This method differs from insertText() in two ways :
	<ul>
		<li>if \a text is empty the selection WILL be removed
		<li>after the replacement happens this command will
		cause the cursor to select the new text (note that this
		information is NOT preserved by the undo/redo stack
		however).
	</ul>
*/
void QDocumentCursor::replaceSelectedText(const QString& text)
{
	if ( m_handle )
		m_handle->replaceSelectedText(text);
}

/*!
	\brief Begin an edit block
	
	Edit blocks are command groups. All the commands in an edit block
	are executed in a row when the edit block is ended with endEditBlock().
	
	Edit blocks are considered as a single command as far as the undo/redo
	stack is concerned.
	
	Edit blocks can be nested but that isn't of much use
*/
void QDocumentCursor::beginEditBlock()
{
	if ( m_handle )
		m_handle->beginEditBlock();
}

/*!
	\brief End an edit block
*/
void QDocumentCursor::endEditBlock()
{
	if ( m_handle )
		m_handle->endEditBlock();
}

/*!
	\return Whether the cursor is silent
*/
bool QDocumentCursor::isSilent() const
{
	return m_handle ? m_handle->isSilent() : true;
}

/*!
	\brief Set whether the cursor is silent
*/
void QDocumentCursor::setSilent(bool y)
{
	if ( m_handle )
		m_handle->setSilent(y);
	
}

/*!
	\return whether the cursor is auto updated
	
	An auto updated cursor will remain on the actual line it points
	to when the document is modified.
	
	\code
	QDocumentCursor c1(10, 0, document), c2(10, 0, document), c(5, 0, document);
	
	c1.setAutoUpdated(true);
	
	c.insertLine();
	
	// at this point c2 still points to line 10 whereas c1 points to line 11
	\endcode
*/
bool QDocumentCursor::isAutoUpdated() const
{
	return m_handle ? m_handle->isAutoUpdated() : true;
}

/*!
	\brief Set whether the cursor is aut updated
*/
void QDocumentCursor::setAutoUpdated(bool y)
{
	if ( m_handle )
		m_handle->setAutoUpdated(y);
}

bool QDocumentCursor::isAutoErasable() const{
	return m_handle ? m_handle->isAutoErasable() : true;
}
void QDocumentCursor::setAutoErasable(bool y){
	if ( m_handle )
		m_handle->setAutoErasable(y);
}


/*!
	\brief Refresh the column memory of the cursor
	
	This set the current column memory to the current column position.
	
	\note It is not recommended to call that yourself. The various
	movement method should do that perfectly fine.
*/
void QDocumentCursor::refreshColumnMemory()
{
	if ( m_handle )
		m_handle->refreshColumnMemory();
	
}

/*!
	\return Whether the cursor has column memory
	
	The column memory is a feature that allow a cursor
	to remember its biggest column number so that moving
	back and forth (with movePosition()) on lines of
	different width does not result in the column to change.
	
*/
bool QDocumentCursor::hasColumnMemory() const
{
	return m_handle ? m_handle->hasColumnMemory() : false;
}

/*!
	\brief Set whether the cursor use column memory
*/
void QDocumentCursor::setColumnMemory(bool y)
{
	if ( m_handle )
		m_handle->setColumnMemory(y);
	
}

/*!
	\return whether the cursor has a selection
*/
bool QDocumentCursor::hasSelection() const
{
	return m_handle ? m_handle->hasSelection() : false;
}

/*!
 * \return true if there is an selection and the anchor is before the cursor
 */
bool QDocumentCursor::isForwardSelection() const
{
	return m_handle ? m_handle->isForwardSelection() : false;
}

/*!
	\brief clear the selection
*/
void QDocumentCursor::clearSelection()
{
	if ( m_handle )
		m_handle->clearSelection();
	
}

/*!
 * \brief exchanges cursor and anchor positions
 */
void QDocumentCursor::flipSelection() {
	if ( m_handle )
		m_handle->flipSelection();
}

/*!
	\brief Select something
*/
void QDocumentCursor::select(SelectionType t)
{
	if ( m_handle )
		m_handle->select(t);
	
}

/*!
	\brief Expand a current selection
*/
void QDocumentCursor::expandSelect(QDocumentCursor::SelectionType t)
{
	if ( m_handle )
		m_handle->expandSelect(t);
}

/*!
	\brief Set the selection boundary
	
	Select text between the current cursor anchor and the one
	of \a c.
	
	\note We mean ANCHOR. If the cursor already has a selection the
	anchor will not change, but the position will be set to that of
	\a c.
*/
void QDocumentCursor::setSelectionBoundary(const QDocumentCursor& c)
{
	if ( m_handle )
		m_handle->setSelectionBoundary(c);	
}

void QDocumentCursor::select(int line, int column, int lineTo, int columnTo){
	if ( m_handle )
		m_handle->select(line, column, lineTo, columnTo);
}

void QDocumentCursor::selectColumns(int column, int columnTo){
	if ( m_handle )
		m_handle->select(lineNumber(), column, lineNumber(), columnTo);
}

/*!
	\return whether the given cursor c is within the selection of this (ignores selection of c)
*/
bool QDocumentCursor::isWithinSelection(const QDocumentCursor& c) const
{
	return m_handle ? m_handle->isWithinSelection(c) : false;
}

/*!
  Creates a new cursor whose selection is the largest region which is contained in the selection of both
  (returns c if c has no selection but is within the selection of c and returns an invalid cursor if
  this has no selection)
*/
QDocumentCursor QDocumentCursor::intersect(const QDocumentCursor& c) const{
	return m_handle ? m_handle->intersect(c) : QDocumentCursor();
}

/*!
  Sets the selection given by lbeg/cbeg/lend/cend to the largest selection which is contained in
  the selection of this cursor and the passed boundaries
  (it sets all to -1 if such a selection doesn't exists)
*/
void QDocumentCursor::intersectBoundaries(int& lbeg, int& cbeg, int& lend, int& cend) const{
	if (m_handle)
		m_handle->intersectBoundaries(lbeg, cbeg, lend, cend);
}



void QDocumentCursor::getMatchingPair(QDocumentCursor& from, QDocumentCursor& to, bool maximal) const{
	if (m_handle)
		m_handle->getMatchingPair(from, to, maximal);
	else
		from = to = QDocumentCursor();

}

/*!
	\return selection information
	
	\note The QDocumentSelection object is not updated if the selection
	changes later on : use it right away and do not store it.
*/
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

bool QDocumentCursor::isRTL() const{
	return m_handle && m_handle->isRTL();
}

void QDocumentCursor::sort(QDocumentCursor& from, QDocumentCursor& to){
	if (from < to) return;
	QDocumentCursorHandle* temp = to.m_handle;
	to.m_handle = from.m_handle;
	from.m_handle = temp;
}

/*! @} */

