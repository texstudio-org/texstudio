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

#include "qdocumentline.h"

/*!
	\file qdocumentline.cpp
	\brief Implementation of the QDocumentLine class.
*/

#include "qdocument_p.h"

/*!
	\ingroup document
	@{
*/

/*!
       \class QDocumentLine

       \brief A reference to line objects

       In QCodeEdit, documents are stored as a list of lines. A QDocumentLine holds
       a pointer to the data of one line and gives access to its content.

       It is not meant to be used to iterate over the document, though it is possible
       for conveneience and compatibility reasons. Indeed, QDocumentLine does not now
	   where in the document it is located. It can obtain that information but this is
	   a O(n) operation. Navigation within the document is one of the task devoted to
       QDocumentCursor which can move around in O(1) (or amortized O(1) in some rare
	   cases).

       Lines can be given formatting in various way : "regular" formatting used for
       highlighting, overlays used mainly to display search matches and similar informations
       and marks.
*/

QDocumentLine::QDocumentLine(QDocument *doc)
 : m_handle(doc ? doc->impl()->at(0) : nullptr)
{
	//m_lines_backing_store << this;
	
	if ( m_handle )
		m_handle->ref();
	
}

QDocumentLine::QDocumentLine(const QDocumentLine& line)
 : m_handle(line.m_handle)
{
	//m_lines_backing_store << this;
	if ( m_handle )
		m_handle->ref();
	
}

QDocumentLine::QDocumentLine(QDocumentLineHandle* handle)
 : m_handle(handle)
{
	//m_lines_backing_store << this;
	if ( m_handle )
		m_handle->ref();
	
}

QDocumentLine::~QDocumentLine()
{
	if ( m_handle )
		m_handle->deref();
	
	//m_lines_backing_store.removeAll(this);
}

/*!
	\brief Comparison operator
*/
bool QDocumentLine::operator == (const QDocumentLine& l) const
{
	return m_handle == l.m_handle;
	//return lineNumber() == l.lineNumber();
}

/*!
	\brief Comparison operator
*/
bool QDocumentLine::operator != (const QDocumentLine& l) const
{
	return m_handle != l.m_handle;
	//return lineNumber() != l.lineNumber();
}

/*!
	\brief copy operator
	
	QDocumentLine objects are just wrappers around the "real" line data.
	Copies of a QDocumentLine all points to the same underlying data and
	modifying one affect them all (no implicit sharing).
*/
QDocumentLine& QDocumentLine::operator = (const QDocumentLine& l)
{
	if ( m_handle )
		m_handle->deref();
	
	m_handle = l.m_handle;
	
	if ( m_handle )
		m_handle->ref();
	
	return *this;
}

/*!
	\return the document to which that line belongs
*/
QDocument* QDocumentLine::document() const
{
    return m_handle ? m_handle->document() : nullptr;
}

/*!
	\brief Check whether a given flag is set to the line
*/
bool QDocumentLine::hasFlag(State s) const
{
	return m_handle ? m_handle->hasFlag(s) : false;
}

/*!
	\brief Check whether any of the flags in a given combination is set to the line
*/
bool QDocumentLine::hasAnyFlag(int s) const
{
	return m_handle ? m_handle->hasFlag(s) : false;
}

/*!
	\brief Set a flag of the line
	
	\warning Do not mess with flags unless you know what you are doing
*/
void QDocumentLine::setFlag(State s, bool y)
{
	if ( m_handle )
		m_handle->setFlag(s, y);
	
}

/*!
	\return whether the line object is null (i.e invalid)
*/
bool QDocumentLine::isNull() const
{
	return m_handle ? !m_handle->document() : true;
}

/*!
	\return whether the line object is valid
*/
bool QDocumentLine::isValid() const
{
    return m_handle ? m_handle->document()!=nullptr : false;
}

/*!
	\return the text of the line
*/
QString QDocumentLine::text() const
{
	return m_handle ? m_handle->text() : QString();
}

/*!
	\return The length of the line, in characters
*/
int QDocumentLine::length() const
{
	return m_handle ? m_handle->text().length() : 0;
}

/*!
	\return the number of visual lines occupied by the line
	
	This is NOT set to zero when the line is hidden (e.g due to folding).
*/
int QDocumentLine::lineSpan() const
{
	return m_handle && m_handle->document() ? m_handle->m_frontiers.count() + 1 : 0;
}

/*!
	\brief Returns the position of the first non-whitespace character
	\return position of first non-whitespace char or -1 if there is none
*/
int QDocumentLine::firstChar() const
{
	return nextNonSpaceChar(0);
}

/*!
	\brief Returns the position of the last non-whitespace character
	\return position of last non-whitespace char or -1 if there is none
*/
int QDocumentLine::lastChar() const
{
	return previousNonSpaceChar(length() - 1);
}

/*!
	\return true if the line starts with txt, neglecting spaces
*/
bool QDocumentLine::startsWith(const QString &txt)
{
	int pos = firstChar();
	return pos >= 0 && pos == text().indexOf(txt);
}

int QDocumentLine::indent() const
{
	return m_handle ? m_handle->indent() : 0;
}

/*!
	Find the position of the next char that is not a space.
	\param pos Column of the character which is examined first.
	\return True if the specified or a following character is not a space
	Otherwise false.
*/
int QDocumentLine::nextNonSpaceChar(int pos) const
{
	return m_handle ? m_handle->nextNonSpaceChar(pos) : -1;
}

/*!
	\brief Find the position of the previous char that is not a space.
	\param pos Column of the character which is examined first.
	\return The position of the first non-whitespace character preceding pos,
   or -1 if none is found.
*/
int QDocumentLine::previousNonSpaceChar(int pos) const
{
	return m_handle ? m_handle->previousNonSpaceChar(pos) : -1;
}

/*!
	\brief Converts a cursor position (column) to a document position (unconstrained viewport)
	
	\deprecated Use cursorToDocumentOffset() instead
	
	This function is kept for compatribility only. It dates back to the time before line wrapping
	was implemented. Due to the limitation of its design (i.e signature) it works in a somewhat
	awkard way : the x position returned is that the cursor would have in an unconstrained viewport,
	even when the line is wrapped so it does not map to an actual viewport coordinate, unless of
	course no wrapping is used.
*/
int QDocumentLine::cursorToX(int cpos) const
{
	return m_handle ? m_handle->cursorToX(cpos) : -1;
}

/*!
	\brief Converts a document position (unconstrained viewport) to a cursor position (column)
	
	\deprecated Use cursorToDocumentOffset() instead
	
	\see cursorToX() for more informations about this function
*/
int QDocumentLine::xToCursor(int xpos) const
{
	return m_handle ? m_handle->xToCursor(xpos) : -1;
}

/*!
	\return The wrapped line (i.e "subline") to which a given cursor position resides
	\param cpos cursor position, as a text column
*/
int QDocumentLine::wrappedLineForCursor(int cpos) const
{
	return m_handle ? m_handle->wrappedLineForCursor(cpos) : -1;
}

/*!
	\brief Converts a document offset (viewport) to a cursor position (character / text column)
	
	The (x, y) coordinates given by this function are relative to the absolute
	position of the line, which can be obtained from the document.
*/
int QDocumentLine::documentOffsetToCursor(int x, int y) const
{
	return m_handle ? m_handle->documentOffsetToCursor(x, y) : -1;
}

/*!
	\brief Converts a cursor position (character / text column) to a document offset (viewport)
	
	The (x, y) coordinates given by this function are relative to the absolute
	position of the line, which can be obtained from the document.
*/
void QDocumentLine::cursorToDocumentOffset(int cpos, int& x, int& y) const
{
	if ( m_handle )
		m_handle->cursorToDocumentOffset(cpos, x, y);
}

/*!
	\overload
*/
QPoint QDocumentLine::cursorToDocumentOffset(int cpos) const
{
	return m_handle ? m_handle->cursorToDocumentOffset(cpos) : QPoint();
}

/*!
	\brief Toggle a mark on the line
*/
void QDocumentLine::addMark(int id)
{
	if ( !document() )
		return;
	
	document()->impl()->addMark(m_handle, id);
	setFlag(QDocumentLine::LayoutDirty,true);
}

/*!
	\brief Toggle a mark on the line
*/
void QDocumentLine::toggleMark(int id)
{
	if ( !document() )
		return;
	
	document()->impl()->toggleMark(m_handle, id);
	setFlag(QDocumentLine::LayoutDirty,true);
}

/*!
	\brief Remove a mark from the line
*/
void QDocumentLine::removeMark(int id)
{
	if ( !document() )
		return;
	
	document()->impl()->removeMark(m_handle, id);
	setFlag(QDocumentLine::LayoutDirty,true);
}

/*!
	\return the list of marks set on this line
*/
QList<int> QDocumentLine::marks() const
{
	return document() ? document()->impl()->marks(m_handle) : QList<int>();
}

/*!
	\return Whether a given mark has been set on the line
*/
bool QDocumentLine::hasMark(int id) const
{
	return marks().contains(id);
}

/*!
	\brief Set the formatting of the line
	
	\note this method is made available for syntax engine use.
	If you want to apply extra formatting on a line use overlays
	instead
	
	\see addOverlay()
*/
void QDocumentLine::setFormats(const QVector<int>& formats)
{
	if ( !m_handle )
		return;
	
	m_handle->setFormats(formats);
}

QVector<int> QDocumentLine::compose(){
    if(!m_handle) return QVector<int> ();
    m_handle->lockForRead();
    QVector<int> result=m_handle->compose();
    m_handle->unlock();
    return result;
}

QVector<int> QDocumentLine::getFormats(){
    if(!m_handle) return QVector<int> ();
    return m_handle->getFormats();
}

int QDocumentLine::getFormatAt(int pos){
	if( !m_handle ) return -1;
	if (pos < 0 ) return -1;
	const QVector<int>& formats = m_handle->getFormats();
	if( pos >= formats.size() ) return -1;
	return formats.at(pos);
}

QVariant QDocumentLine::getCookie(int type){
    if(!m_handle) return QVariant();
    m_handle->lockForRead();
    QVariant result=m_handle->getCookie(type);
    m_handle->unlock();
    return result;
}

void QDocumentLine::setCookie(int type,QVariant data){
	if(!m_handle) return;
    m_handle->lockForWrite();
	m_handle->setCookie(type,data);
    m_handle->unlock();
}

void QDocumentLine::removeCookie(int type){
	if (!m_handle) return;
    m_handle->lockForWrite();
	m_handle->removeCookie(type);
    m_handle->unlock();
}

bool QDocumentLine::isRTLByLayout() const{
    if (!m_handle) return false;
     return m_handle->isRTLByLayout();
}

bool QDocumentLine::isRTLByText() const{
    if (!m_handle) return false;
     return m_handle->isRTLByText();
}

QTextLayout* QDocumentLine::getLayout() const{
    return m_handle ? m_handle->m_layout : nullptr;
}

int QDocumentLine::leftCursorPosition(int oldPos) const{
	if (!m_handle) return 0;
#if QT_VERSION >= 0x040800
	if (m_handle->m_layout) {
		QReadLocker locker(&m_handle->mLock); //no idea if this is needed
		try {
			return m_handle->m_layout->leftCursorPosition(oldPos);
		} catch (std::bad_alloc){

		}
	}
#endif
	return qBound(0, oldPos - 1, length());
}
int QDocumentLine::rightCursorPosition(int oldPos) const{
	if (!m_handle) return 0;
#if QT_VERSION >= 0x040800
	if (m_handle->m_layout) {
		QReadLocker locker(&m_handle->mLock); //no idea if this is needed
		try {
			return m_handle->m_layout->rightCursorPosition(oldPos);
		} catch (std::bad_alloc){ //this is sometimes thrown on qt4.8.7 with 7*hex:(d8ba d8b1) 2478 5e32 2409

		}
	}
#endif
	return qBound(0, oldPos + 1, length());
}

/*!
	\return whether the line has at least one overlay of a given format id
*/
bool QDocumentLine::hasOverlay(int fid) const
{
	if ( !m_handle )
		return false;
	
	foreach ( const QFormatRange& r, m_handle->m_overlays )
		if ( r.format == fid )
			return true;
	
	return false;
}

/*!
	\brief Clear all overlays applied to the line
*/
QList<QFormatRange> QDocumentLine::overlays() const
{
	if ( !m_handle )
		return QList<QFormatRange>();
	
	return m_handle->m_overlays;
}

/*!
	\brief Clear all overlays applied to the line
*/
void QDocumentLine::clearOverlays()
{
	if ( !m_handle )
		return;
	
	m_handle->clearOverlays();
}

void QDocumentLine::clearOverlays(int formatToClear){
	if ( !m_handle )
		return;

    m_handle->clearOverlays(formatToClear);
}

void QDocumentLine::clearOverlays(QList<int> formatsToClear){
    if ( !m_handle )
        return;

    m_handle->clearOverlays(formatsToClear);
}

/*!
	\brief Add an overlay to the line
	
	Overlays are format range that get applied on top of regular formatting.
	
	They are typically used to display search matches, matching braces, ...
*/
void QDocumentLine::addOverlay(const QFormatRange& over)
{
	if ( !m_handle )
		return;
	
	m_handle->addOverlay(over);
}

/*!
	\brief Remove an overlay from the line
*/
void QDocumentLine::removeOverlay(const QFormatRange& over)
{
	if ( !m_handle )
		return;
	
	m_handle->removeOverlay(over);
}

bool QDocumentLine::hasOverlay(int id){
    if ( !m_handle ) return false;
    return m_handle->hasOverlay(id);
}

/*!
 * \brief Returns all QFormatRanges of the given \a preferredFormat.
 * Any format will match for \a preferredFormat == -1.
 */
QList<QFormatRange> QDocumentLine::getOverlays(int preferredFormat) const {
	if ( !m_handle )
		return QList<QFormatRange>();
	
	return m_handle->getOverlays(preferredFormat);
}

/*!
 * \brief Returns the QFormatRange for the given \a preferredFormat at the given column number (\a index).
 * Any format will match for \a preferredFormat == -1.
 */
QFormatRange QDocumentLine::getOverlayAt(int index, int preferredFormat) const {
	if ( !m_handle )
		return QFormatRange();
	
	return m_handle->getOverlayAt(index,preferredFormat);
}

/*!
 * \brief Returns the first QFormatRange between columns \a start and \a end for the given \a preferredFormat.
 * Any format will match for \a preferredFormat == -1.
 */
QFormatRange QDocumentLine::getFirstOverlay(int start, int end, int preferredFormat) const {
	if ( !m_handle )
		return QFormatRange();
	
	return m_handle->getFirstOverlay(start,end,preferredFormat);
}

/*!
 * \brief Returns the last QFormatRange between columns \a start and \a end for the given \a preferredFormat.
 * Any format will match for \a preferredFormat == -1.
 */
QFormatRange QDocumentLine::getLastOverlay(int start, int end, int preferredFormat) const {
	if ( !m_handle )
		return QFormatRange();
	
	return m_handle->getLastOverlay(start,end,preferredFormat);
}


/*!
	\return the list of parentheses present on the line
	
	\note This is language dependent.
*/
const QVector<QParenthesis>& QDocumentLine::parentheses() const
{
	Q_CHECK_PTR(m_handle);
	
	return m_handle->m_parens;
}

/*!
	\brief Set the parentheses present on that line
	
	\note this should only be used by syntax engines
*/
void QDocumentLine::setParentheses(const QVector<QParenthesis>& parentheses)
{
	if ( !m_handle )
		return;
	
	m_handle->m_parens = parentheses;
}

/*!
	Reserved to syntax engines. do not mess with this unless you know what you are doing.
*/
QNFAMatchContext* QDocumentLine::matchContext()
{
    return m_handle ? &m_handle->m_context : nullptr;
}

/*! @} */

