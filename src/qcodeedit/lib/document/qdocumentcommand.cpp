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

#include "qdocumentcommand.h"

/*!
	\file qdocumentcommand.cpp
	\brief Implementation of the QDocumentCommand class and its basic heirs.
*/

#include "qdocument_p.h"

#include "stdint.h"

/*!
	\ingroup document
	@{
*/

/*!
	\class QDocumentCommand
	\brief The base class for document editing command
*/


/*!
	\brief ctor
*/
QDocumentCommand::QDocumentCommand(Command c, QDocument *d, QDocumentCommand *p)
 : QUndoCommand(p),
	m_state(false), m_first(true), m_doc(d),
	m_redoOffset(0), m_undoOffset(0),
    m_silent(false), m_keepAnchor(false), m_command(c), m_cursor(nullptr)
{

}

QStringList QDocumentCommand::debugRepresentation() const {
	return QStringList() << "UNKNOWN COMMAND";
}

/*!
	\brief dtor
*/
QDocumentCommand::~QDocumentCommand()
{
	if ( m_cursor )
	{
		// release the handle
		m_cursor->deref();
	}
}

/*!
	\return command identifier
*/
int QDocumentCommand::id() const
{
	return m_command;
}

/*!
	\brief Attempts to merge with another command

	Command merging is not implemented.
*/
bool QDocumentCommand::mergeWith(const QUndoCommand */*command*/)
{
	return false;
}

/*!
	\brief Redo the command
*/
void QDocumentCommand::redo()
{
	QUndoCommand::redo();
}

/*!
	\brief Undo the command
*/
void QDocumentCommand::undo()
{
	QUndoCommand::undo();
}

/*!
	\return whether the command is silent

	Silent command do not update the editing cursor of the host document.
*/
bool QDocumentCommand::isSilent() const
{
	return m_silent;
}

/*!
	\brief Set whether the command is silent
*/
void QDocumentCommand::setSilent(bool y)
{
	m_silent = y;
}

/*!
	\return whether the command preserve selection of the target cursor
	
	When this property is true, cursor adjustement upon command execution
	will preserve the anchor of target cursor and only alter its position
	thus keeping a selection.
	
	\note This is disabled by default
*/
bool QDocumentCommand::keepAnchor() const
{
	return m_keepAnchor;
}

/*!
	\brief Set whether the command preserve selection of the target cursor
	
	\note This is disabled by default
*/
void QDocumentCommand::setKeepAnchor(bool y)
{
	m_keepAnchor = y;
}

/*!
	\brief Set the target cursor

	The position of the target cursor is update upon undo() and redo()
*/
void QDocumentCommand::setTargetCursor(QDocumentCursorHandle *h)
{
	if ( m_cursor )
	{
		// release the handle
		m_cursor->deref();
	}

	m_cursor = h;

	if ( m_cursor )
	{
		// make sure the handle does not get deleted while the command knows it
		m_cursor->ref();
	}
}

/*!
	\brief ?
*/
void QDocumentCommand::setRedoOffset(int off)
{
	m_redoOffset = off;
}

/*!
	\brief ?
*/
void QDocumentCommand::setUndoOffset(int off)
{
	m_undoOffset = off;
}

/*!
	\brief Insert some text
	\param line target line
	\param pos target text position within line
	\param s text to insert

	This helper method is provided so that subclasses may actually
	modify the document contents without using private API.
*/
void QDocumentCommand::insertText(int line, int pos, const QString& s)
{
	if ( !m_doc )
		return;

	QDocumentPrivate *pd = m_doc->impl();
	QDocumentLineHandle *h = pd->m_lines.at(line);

	if ( !h )
		return;
	
	h->lockForWriteText();
	h->textBuffer().insert(pos, s);
	h->shiftOverlays(pos, s.length());
	h->unlock();
}

/*!
	\brief Remove some text
	\param line target line
	\param pos target text position within line
	\param length length of the text to remove

	This helper method is provided so that subclasses may actually
	modify the document contents without using private API.
*/
void QDocumentCommand::removeText(int line, int pos, int length)
{
	if ( !m_doc )
		return;

	QDocumentPrivate *pd = m_doc->impl();
	QDocumentLineHandle *h = pd->m_lines.at(line);

	if ( !h || !length )
		return;

	h->lockForWriteText();
	h->textBuffer().remove(pos, length);
	h->shiftOverlays(pos, -length);
	h->unlock();
}

/*!
	\brief Insert some lines in the host document
	\param after where to insert lines (line number)
	\param l list of lines to insert

	This helper method is provided so that subclasses may actually
	modify the document contents without using too much private API
	(QDocumentLineHandle is part of the private API...)
*/
void QDocumentCommand::insertLines(int after, const QList<QDocumentLineHandle*>& l)
{
	if ( l.isEmpty() || !m_doc->impl()->at(after) )
		return;

	m_doc->impl()->insertLines(after, l);
}

inline void growPosOnInsertion(int *moveLine, int *moveOffset, int line, int column, int prefixLength, int numLines, int suffixLength){
	if ( numLines )
	{
		if ( *moveLine == line )
			*moveOffset -= column;
		*moveLine += numLines;
		*moveOffset += suffixLength;
	} else if ( *moveLine == line ) {
		*moveOffset += prefixLength;
	}
}

inline void movePosOnInsertion(int *moveLine, int *moveOffset, int line, int column, int prefixLength, int numLines, int suffixLength){
	if ( *moveLine > line )
	{
		*moveLine += numLines;
	} else if ( *moveLine == line && *moveOffset >= column ) {
		if ( numLines )
		{
			*moveLine += numLines;
			*moveOffset -= column;
			*moveOffset += suffixLength;
		} else {
			*moveOffset += prefixLength;
		}
	}
}

void QDocumentCommand::updateCursorsOnInsertion(int line, int column, int prefixLength, int numLines, int suffixLength)
{
	//qDebug("inserting %i lines at (%i, %i) with (%i : %i) bounds", numLines, line, column, prefixLength, suffixLength);
	foreach ( QDocumentCursorHandle *ch, m_doc->impl()->m_autoUpdatedCursorList )
	{
		if ( ch == m_cursor || ch->document() != m_doc )
			continue;

		//printf("[[watch:0x%x(%i, %i)]]", ch, ch->m_begLine, ch->m_begOffset);

		// TODO : better selection handling
		if ( ch->hasSelection() )
		{
			if (ch->hasFlag(QDocumentCursorHandle::AutoUpdateKeepBegin) &&
			    line == ch->m_begLine && column == ch->m_begOffset) {
				//movePosOnInsertion(&ch->m_begLine, &ch->m_begOffset, line, column, prefixLength, numLines, suffixLength);
				//movePosOnInsertion(&ch->m_endLine, &ch->m_endOffset, line, column, prefixLength, numLines, suffixLength);
				continue;
			}
			if (ch->hasFlag(QDocumentCursorHandle::AutoUpdateKeepEnd) &&
			    line == ch->m_endLine && column == ch->m_endOffset) {
				movePosOnInsertion(&ch->m_begLine, &ch->m_begOffset, line, column, prefixLength, numLines, suffixLength);
				movePosOnInsertion(&ch->m_endLine, &ch->m_endOffset, line, column, prefixLength, numLines, suffixLength);
				continue;
			}
			int lbeg = line, cbeg = column, lend = line, cend = column;

			ch->intersectBoundaries(lbeg, cbeg, lend, cend);

			if ( lbeg == line && cbeg == column )
			{
				//qDebug("expand (%i, %i : %i, %i)", ch->m_begLine, ch->m_begOffset, ch->m_endLine, ch->m_endOffset);
				if ( (ch->m_begLine > ch->m_endLine) || (ch->m_begLine == ch->m_endLine && ch->m_begOffset >= ch->m_endOffset) )
					growPosOnInsertion(&ch->m_begLine, &ch->m_begOffset, line, column, prefixLength, numLines, suffixLength);
                else
					growPosOnInsertion(&ch->m_endLine, &ch->m_endOffset, line, column, prefixLength, numLines, suffixLength);
				//qDebug("into (%i, %i : %i, %i)", ch->m_begLine, ch->m_begOffset, ch->m_endLine, ch->m_endOffset);
				continue;
			}
		}

		// move
		movePosOnInsertion(&ch->m_begLine, &ch->m_begOffset, line, column, prefixLength, numLines, suffixLength);
		movePosOnInsertion(&ch->m_endLine, &ch->m_endOffset, line, column, prefixLength, numLines, suffixLength);
	}
}

void QDocumentCommand::updateCursorsOnDeletion(int line, int column, int prefixLength, int numLines, int suffixLength)
{
//	qDebug("removing %i lines at (%i, %i) with (%i : %i) bounds", numLines, line, column, prefixLength, suffixLength);
//erstes zeichen einer zeile: warning: removing 0 lines at (12, 0) with (1 : -1) bounds
//zeile mit 10 textzeichen: warning: removing 1 lines at (13, 0) with (10 : 0) bounds
	foreach ( QDocumentCursorHandle *ch, m_doc->impl()->m_autoUpdatedCursorList )
	{
		if ( ch == m_cursor || ch->document() != m_doc)
			continue;

	//	qDebug("[[watch:0x%x(%i, %i)]]", ch, ch->m_begLine, ch->m_begOffset);
		int columnEnd = (numLines >= 1) ? suffixLength : column + prefixLength;
		// TODO : better selection handling
		if ( ch->hasSelection() )
		{
			int lbeg = line;
			int cbeg = column;
			int lend = line + numLines;
			int cend = columnEnd;

			
			ch->intersectBoundaries(lbeg, cbeg, lend, cend);
			//qDebug("intersection (%i, %i : %i, %i)", lbeg, cbeg, lend, cend);
			if ( lbeg != -1 && cbeg != -1 && lend != -1 && cend != -1 )
			{
				//qDebug("shrink (%i, %i : %i, %i)", ch->m_begLine, ch->m_begOffset, ch->m_endLine, ch->m_endOffset);
				//qDebug("of intersection (%i, %i : %i, %i)", lbeg, cbeg, lend, cend);
				if (ch->isAutoErasable() && 
				    (lbeg > line || (lbeg == line && cbeg > column)) &&
					(lend < line+numLines || (lend == line+numLines && cend < columnEnd))) 
				{	
					//intersection is complete within the removed range without touching the bordes
					//=> cursor is completely removed and thus invalid
					ch->m_begLine = ch->m_endLine = -1;
					ch->m_begOffset = ch->m_endOffset = -1;
				} else {				
					ch->substractBoundaries(line, column, line+numLines,columnEnd);
					//lbeg, cbeg, lend, cend);
				}
				//qDebug("into (%i, %i : %i, %i)", ch->m_begLine, ch->m_begOffset, ch->m_endLine, ch->m_endOffset);
				continue;
			}
		}
		
		int cend = columnEnd;
		// move
		if ( ch->m_begLine > line + numLines )
		{
			ch->m_begLine -= numLines;
		} else if ( ch->m_begLine == line + numLines && ch->m_begOffset >= cend ) {
			if ( numLines )
			{
				ch->m_begLine -= numLines;
				ch->m_begOffset -= suffixLength;
				ch->m_begOffset += column;
			} else {
				ch->m_begOffset -= prefixLength;
			}
		} else if ( ch->m_begLine > line || (ch->m_begLine == line && ch->m_begOffset > column) ) {
			// cursor will become invalid in an unrecoverable way...

		}

		if ( ch->m_endLine > line + numLines )
		{
			ch->m_endLine -= numLines;
		} else if ( ch->m_endLine == line + numLines && ch->m_endOffset >= cend ) {
			if ( numLines )
			{
				ch->m_endLine -= numLines;
				ch->m_endOffset -= suffixLength;
				ch->m_endOffset += column;
			} else {
				ch->m_endOffset -= prefixLength;
			}
		} else if ( ch->m_endLine > line || (ch->m_endLine == line && ch->m_endOffset > column) ) {
			// cursor will become invalid in an unrecoverable way...
			// except that it should have intersected in the first place...
		}
	}
}


/*!
	\brief Remove some lines from the host document
	\param after where to remove lines (line number)
	\param n number of lines to remove

	This helper method is provided so that subclasses may actually
	modify the document contents without using the private API.
*/
void QDocumentCommand::removeLines(int after, int n)
{
	if ( n <= 0 || !m_doc->impl()->at(after) || !m_doc->impl()->at(after + n) )
		return;

	m_doc->impl()->removeLines(after, n);
}

/*!
	\brief Update the target cursor
	\param l target line
	\param offset target text position within target line
*/
void QDocumentCommand::updateTarget(int l, int offset)
{
	//QDocumentLineHandle *h = m_doc->impl()->at(l);
	
	// update command sender if any
	if ( m_cursor )
	{
//		qDebug("moving cursor [0x%x:beg] from (%i, %i) to line (%i, %i) as updating",
//					m_cursor,
//					m_cursor->m_begLine,
//					m_cursor->m_begOffset,
//					l,
//					offset
//					);
//
		while ( l && (offset < 0) )
		{
			--l;
			offset += m_doc->line(l).length() + 1;
		}

		while ( (l + 1) < m_doc->lines() && m_doc->line(l).length() < offset )
		{
			offset -= m_doc->line(l).length() + 1;
			++l;
		}

		if ( !m_keepAnchor )
		{
		m_cursor->m_endLine = -1;
		m_cursor->m_endOffset = -1;
		} else if ( m_cursor->m_endLine == -1 ) {
			m_cursor->m_endLine = m_cursor->m_begLine;
			m_cursor->m_endOffset = m_cursor->m_begOffset;
		}

		m_cursor->m_begLine = qMax(0, l);
		m_cursor->m_begOffset = qMax(0, offset);
		
		m_cursor->refreshColumnMemory();
	}
}


/*!
	\brief Change the modification status of a line
*/
void QDocumentCommand::markRedone(QDocumentLineHandle *h, bool firstTime)
{
	QHash<QDocumentLineHandle*, QPair<int, int> >::iterator it = m_doc->impl()->m_status.find(h);

	if ( it != m_doc->impl()->m_status.end() )
	{
		if ( firstTime && it->first < it->second )
			it->second = -1;

		++it->first;
	} else {
		m_doc->impl()->m_status[h] = qMakePair(1, 0);
	}
}

/*!
	\brief Change the modifiaction status of a line
*/
void QDocumentCommand::markUndone(QDocumentLineHandle *h)
{
	QHash<QDocumentLineHandle*, QPair<int, int> >::iterator it = m_doc->impl()->m_status.find(h);

	if ( it != m_doc->impl()->m_status.end() )
	{
		--it->first;
	} else {
        qDebug()<<"warning: status data and/or undo stack corrupted...";
		m_doc->impl()->m_status[h] = qMakePair(-1, 0);
	}
}

////////////////////////////

/*!
	\class QDocumentInsertCommand
	\brief A specialized command to insert text
*/

/*!
	\brief ctor
	\param l target line
	\param offset target text position within target line
	\param text text to insert (can contain line feeds, "\n", which will result in the creation of new lines)
	\param doc host document
	\param p parent command
*/
QDocumentInsertCommand::QDocumentInsertCommand(	int l, int offset,
												const QString& text,
												QDocument *doc,
												QDocumentCommand *p)
 : QDocumentCommand(Insert, doc, p)
{
    QStringList lines;
    if (!text.contains("\n") && text.contains("\r"))  //mac line ending
      lines = text.split(QLatin1Char('\r'), QString::KeepEmptyParts);
    else
      lines = text.split(QLatin1Char('\n'), QString::KeepEmptyParts);

	if ( !m_doc || text.isEmpty() )
		qFatal("Invalid insert command");

	m_data.lineNumber = l;
	m_data.startOffset = offset;

	m_data.begin = lines.takeAt(0);
	m_data.endOffset = lines.count() ? lines.last().length() : -1;

	foreach ( const QString& s, lines )
		m_data.handles << new QDocumentLineHandle(s, m_doc);

	QDocumentLine bl = m_doc->line(l);

	if ( m_data.handles.count() && (bl.length() > offset) )
	{
		m_data.end = bl.text().mid(offset);
		m_data.handles.last()->lockForWriteText();
		m_data.handles.last()->textBuffer().append(m_data.end);
		m_data.handles.last()->unlock();
	}

	/*
	if ( (text == "\n") && m_data.handles.isEmpty() )
		qWarning("Go fix it by hand...");
	*/
}

/*!
	\brief dtor
*/
QDocumentInsertCommand::~QDocumentInsertCommand()
{
	if ( m_state )
		return;

	foreach ( QDocumentLineHandle *h, m_data.handles )
		h->deref();

}

bool QDocumentInsertCommand::mergeWith(const QUndoCommand *command)
{
	const QDocumentInsertCommand* cmd = static_cast<const QDocumentInsertCommand*>(command);
	int new_line=cmd->m_data.lineNumber;
	int new_startOffset=cmd->m_data.startOffset;
	int myLenght=m_data.begin.length();
	if(new_line==m_data.lineNumber && new_startOffset==m_data.startOffset+myLenght && 
	   cmd->m_data.handles.count()==0 && m_data.handles.count()==0) //don't know exactly why this line is needed but otherwise undo after insertion with several lines with autoindent doesn't work
	{
		m_data.begin+=cmd->m_data.begin;
		return true;
	}
	return false;
}

void QDocumentInsertCommand::redo()
{
	// state : handles used by doc
	m_state = true;

	//QDocumentIterator it = m_doc->impl()->index(m_data.lineNumber);

	//qDebug("inserting %i lines after %i", m_data.handles.count(), m_data.lineNumber);

	bool commandAffectsFolding = m_doc->linesPartiallyFolded(m_data.lineNumber, m_data.lineNumber);

	QDocumentLineHandle *hl = m_doc->impl()->at(m_data.lineNumber);

	if ( m_data.handles.count() )
	{
		removeText(m_data.lineNumber, m_data.startOffset, m_data.end.count());
	}

	insertText(m_data.lineNumber, m_data.startOffset, m_data.begin);

	insertLines(m_data.lineNumber, m_data.handles);

	if ( m_data.handles.count() )
	{
		QDocumentLineHandle *h = m_data.handles.last();

		//updateTarget(h, h->text().length() - m_data.end.length());
		updateTarget(m_data.lineNumber + m_data.handles.count(), h->text().length() - m_data.end.length() + m_redoOffset);
	} else {
		updateTarget(m_data.lineNumber, m_data.startOffset + m_data.begin.length() + m_redoOffset);
	}

	updateCursorsOnInsertion(m_data.lineNumber, m_data.startOffset, m_data.begin.length(), m_data.handles.count(), m_data.endOffset);

	m_doc->impl()->emitContentsChange(m_data.lineNumber, m_data.handles.count() + 1);
    m_doc->setProposedPosition(QDocumentCursor(m_doc,m_data.lineNumber+m_data.handles.size(),m_data.endOffset));

	markRedone(hl, m_first);

	foreach ( QDocumentLineHandle *h, m_data.handles )
		markRedone(h, m_first);

	if (commandAffectsFolding)
		m_doc->correctFolding(m_data.lineNumber, m_data.lineNumber+m_data.handles.count());

	//m_doc->impl()->emitContentsChanged();
	m_first = false;
}

void QDocumentInsertCommand::undo()
{
	// state : handles !used by doc
	m_state = false;

	bool commandAffectsFolding = m_doc->linesPartiallyFolded(m_data.lineNumber, m_data.lineNumber+m_data.handles.count());

	//QDocumentIterator it = m_doc->impl()->index(m_data.line);

	QDocumentLineHandle *hl = m_doc->impl()->at(m_data.lineNumber);

	removeLines(m_data.lineNumber, m_data.handles.count());
	removeText(m_data.lineNumber, m_data.startOffset, m_data.begin.count());

	if ( m_data.handles.count() )
	{
		insertText(m_data.lineNumber, m_data.startOffset, m_data.end);
	}

	updateTarget(m_data.lineNumber, m_data.startOffset + m_undoOffset);

	updateCursorsOnDeletion(m_data.lineNumber, m_data.startOffset, m_data.begin.length(), m_data.handles.count(), m_data.endOffset);

	m_doc->impl()->emitContentsChange(m_data.lineNumber, m_data.handles.count() + 1);
    m_doc->setProposedPosition(QDocumentCursor(m_doc,m_data.lineNumber,m_data.startOffset));

	markUndone(hl);

	foreach ( QDocumentLineHandle *h, m_data.handles )
		markUndone(h);

	if (commandAffectsFolding)
		m_doc->correctFolding(m_data.lineNumber, m_data.lineNumber+m_data.handles.count());
	//m_doc->impl()->emitContentsChanged();
}

///////////////////////////

/*!
	\class QDocumentEraseCommand
	\brief A specialized command to erase text
*/

/*!
	\brief ctor
	\param bl begin line of the target area
	\param bo begin text position of the target area
	\param el end line of the target area
	\param eo end text position of the target area
	\param doc host document
	\param p parent command
*/
QDocumentEraseCommand::QDocumentEraseCommand(	int bl, int bo,
												int el, int eo,
												QDocument *doc,
												QDocumentCommand *p)
 : QDocumentCommand(Erase, doc, p)
{
	if (el>m_doc->lines()-1) {
		el=m_doc->lines()-1;
		eo=m_doc->impl()->at(el)->text().length();
	}
	QDocumentLineHandle *start = m_doc->impl()->at(bl),
						*end = m_doc->impl()->at(el);

	QDocumentConstIterator it = m_doc->impl()->begin() + bl; //index(start);

	m_data.lineNumber = bl;
	m_data.startOffset = bo;

	if ( start == end )
	{
		m_data.begin = start->text().mid(bo, eo - bo);

		m_data.end = QString();
		m_data.endOffset = -1;

	} else {
		m_data.begin = start->text().mid(bo);

		m_data.endOffset = eo;
		m_data.end = end->text().mid(eo);

		do
		{
			m_data.handles << *(++it);
		} while ( *it != end );
	}

	m_state = true;
    m_mergedLines=false;
}

QStringList QDocumentInsertCommand::debugRepresentation() const{
	QStringList result;
	result << QString("INSERT COMMAND: %1:%2").arg(m_data.lineNumber).arg(m_data.startOffset).arg(m_data.lineNumber+m_data.handles.size()).arg(m_data.endOffset);
	result << QString("     Inserted text: \"%1\"").arg(m_data.begin);
	if (m_data.handles.size()) {
		result << ("     Inserted lines:");
		for (int i=0; i < m_data.handles.size(); i++)
			result << (QString("     %1").arg((intptr_t)(m_data.handles[i]),8,16) + (m_doc->indexOf(m_data.handles[i]) >= 0?"\""+m_data.handles[i]->text()+"\"":"<ERASED>") );
	}
	return result;
}


/*!
	\brief dtor
*/
QDocumentEraseCommand::~QDocumentEraseCommand()
{
	if ( m_state )
		return;

	foreach ( QDocumentLineHandle *h, m_data.handles )
		h->deref();
	//qDeleteAll(m_data.handles);
}

bool QDocumentEraseCommand::mergeWith(const QUndoCommand *command)
{
    const QDocumentEraseCommand *eraseCommand=dynamic_cast<const QDocumentEraseCommand*>(command);
    if(eraseCommand==nullptr)
        return false;
    int new_line=eraseCommand->m_data.lineNumber;
    int new_startOffset=eraseCommand->m_data.startOffset;
    int myLenght=eraseCommand->m_data.begin.length();
    if(eraseCommand->m_data.endOffset!=-1) return false;
	if(m_data.endOffset!=-1) return false;
	if(new_line==m_data.lineNumber && new_startOffset+myLenght==m_data.startOffset){ //backspace
        m_data.begin=eraseCommand->m_data.begin+m_data.begin;
		m_data.startOffset=new_startOffset;
        m_undoOffset+=eraseCommand->m_undoOffset;
		return true;
	}
	if(new_line==m_data.lineNumber && new_startOffset==m_data.startOffset){ //delete char
        m_data.begin+=eraseCommand->m_data.begin;
        m_undoOffset+=eraseCommand->m_undoOffset;
		//m_data.startOffset=new_startOffset;
		return true;
	}
	return false;
}

void QDocumentEraseCommand::redo()
{
	// state : handles !used by doc
	m_state = false;

	bool commandAffectsFolding = m_doc->linesPartiallyFolded(m_data.lineNumber, m_data.lineNumber+m_data.handles.count());
	bool foldStart = false;
	if (commandAffectsFolding) 
		for (int i=m_data.lineNumber; i<=m_data.lineNumber+m_data.handles.count();i++)
			if (m_doc->line(i).hasFlag(QDocumentLine::CollapsedBlockStart)) {
				foldStart = true;
				break;
			}
	
	//QDocumentIterator it = m_doc->impl()->index(m_data.line);

	QDocumentLineHandle *hl = m_doc->impl()->at(m_data.lineNumber);

	if ( m_data.handles.isEmpty() )
	{
		removeText(m_data.lineNumber, m_data.startOffset, m_data.begin.count());
	} else {
		removeText(m_data.lineNumber, m_data.startOffset, m_data.begin.count());

        if ( m_data.endOffset != -1 ){
			insertText(m_data.lineNumber, m_data.startOffset, m_data.end);
            m_mergedLines=m_doc->linesMerged(hl,m_data.startOffset,m_data.handles.last());
        }

		removeLines(m_data.lineNumber, m_data.handles.count());
	}


	updateTarget(m_data.lineNumber, m_data.startOffset + m_redoOffset);

	updateCursorsOnDeletion(m_data.lineNumber, m_data.startOffset, m_data.begin.length(), m_data.handles.count(), m_data.endOffset);

	m_doc->impl()->emitContentsChange(m_data.lineNumber, m_data.handles.count() + 1);

	markRedone(hl, m_first);

	foreach ( QDocumentLineHandle *h, m_data.handles )
		markRedone(h, m_first);

	if (commandAffectsFolding)
		m_doc->correctFolding(m_data.lineNumber, m_data.lineNumber+m_data.handles.count(), foldStart);

	//m_doc->impl()->emitContentsChanged();
	m_first = false;
}

void QDocumentEraseCommand::undo()
{
	// state : handles used by doc
	m_state = true;

	bool commandAffectsFolding = m_doc->linesPartiallyFolded(m_data.lineNumber, m_data.lineNumber);

	//QDocumentIterator it = m_doc->impl()->index(m_data.line);

	QDocumentLineHandle *hl = m_doc->impl()->at(m_data.lineNumber);

	if ( m_data.handles.count() )
	{
		insertLines(m_data.lineNumber, m_data.handles);

		if ( m_data.endOffset != -1 )
			removeText(m_data.lineNumber, m_data.startOffset, m_data.end.count());

		insertText(m_data.lineNumber, m_data.startOffset, m_data.begin);

        if(m_mergedLines){
            m_doc->linesUnMerged(hl,m_data.handles.last());
        }

		m_doc->impl()->emitContentsChange(m_data.lineNumber, m_data.handles.count() + 1);
	} else {

		insertText(m_data.lineNumber, m_data.startOffset, m_data.begin);

		m_doc->impl()->emitContentsChange(m_data.lineNumber, 1);
	}

	if ( m_data.handles.count() )
	{
		QDocumentLineHandle *h = m_data.handles.last();

		//updateTarget(h, h->text().length() - m_data.end.length());
		updateTarget(m_data.lineNumber + m_data.handles.count(), h->text().length() - m_data.end.length() + m_undoOffset);
	} else {
		updateTarget(m_data.lineNumber, m_data.startOffset + m_data.begin.length() + m_undoOffset);
	}

	updateCursorsOnInsertion(m_data.lineNumber, m_data.startOffset, m_data.begin.length(), m_data.handles.count(), m_data.endOffset);
    m_doc->setProposedPosition(QDocumentCursor());

	markUndone(hl);

	foreach ( QDocumentLineHandle *h, m_data.handles )
		markUndone(h);

	if (commandAffectsFolding)
		m_doc->correctFolding(m_data.lineNumber,m_data.lineNumber+m_data.handles.count());

	//m_doc->impl()->emitContentsChanged();
}

QStringList QDocumentEraseCommand::debugRepresentation() const{
	QStringList result;
	result << QString("ERASE COMMAND: %1:%2 to %3:%4").arg(m_data.lineNumber).arg(m_data.startOffset).arg(m_data.lineNumber+m_data.handles.size()).arg(m_data.endOffset);
	result << QString("     Erased text: \"%1\", \"%2\"").arg(m_data.begin).arg(m_data.end);
    if (!m_data.handles.empty()) {
		result << ("     Erased lines:");
		for (int i=0; i < m_data.handles.size(); i++)
			result << (QString("     %1").arg((intptr_t)(m_data.handles[i]),8,16) + (m_doc->indexOf(m_data.handles[i]) >= 0?"\""+m_data.handles[i]->text()+"\"":"<ERASED>") );
	}
	return result;
}


///////////////////////////
/*
QDocumentReplaceCommand::QDocumentReplaceCommand(const QDocumentLine& l, int, int, const QString&)
 : QDocumentCommand(Replace, l.document())
{

}

QDocumentReplaceCommand::~QDocumentReplaceCommand()
{

}

bool QDocumentReplaceCommand::mergeWith(const QUndoCommand *)
{
	return false;
}

void QDocumentReplaceCommand::redo()
{

}

void QDocumentReplaceCommand::undo()
{

}
*/

//////////////////////


/*!
	\class QDocumentCommandBlock
	\brief A meta command used for command grouping
*/

/*!
	\brief ctor
	\param d host document
*/
QDocumentCommandBlock::QDocumentCommandBlock(QDocument *d)
 : QDocumentCommand(Custom, d), m_weakLocked(false)
{

}

/*!
	\brief dtor
*/
QDocumentCommandBlock::~QDocumentCommandBlock()
{
	qDeleteAll(m_commands);
}

void QDocumentCommandBlock::redo()
{
	if ( isWeakLocked() )
	{
		setWeakLock(false);
		return;
	}

	//foreach ( QDocumentCommand *c, m_commands )
	//	c->redo();

	for ( int i = 0; i < m_commands.count(); ++i )
		m_commands.at(i)->redo();

}

void QDocumentCommandBlock::undo()
{
	//foreach ( QDocumentCommand *c, m_commands )
	//	c->undo();

	for ( int i = m_commands.count() - 1; i >= 0; --i )
		m_commands.at(i)->undo();

}

/*!
	\brief Set whether the block is weakly locked
*/
void QDocumentCommandBlock::setWeakLock(bool l)
{
	m_weakLocked = l;
}

/*!
	\return whether the block is weakly locked

	Weak locking of command block is an obscure internal feature
	which prevents the first redo() call from actually redo'ing
	the grouped commands
*/
bool QDocumentCommandBlock::isWeakLocked() const
{
	return m_weakLocked;
}

/*!
	\brief Add a command to the group

	\warning Doing that after having pushed the command on the undo/redo stack
	is likely to result in corruption of the undo/redo stack
*/
void QDocumentCommandBlock::addCommand(QDocumentCommand *c)
{
	m_commands << c;
}

/*!
	\brief Remove a command from the block

	\warning Doing that after having pushed the command on the undo/redo stack
	is likely to result in corruption of the undo/redo stack
*/
void QDocumentCommandBlock::removeCommand(QDocumentCommand *c)
{
	m_commands.removeAll(c);
}

QStringList QDocumentCommandBlock::debugRepresentation() const{
	QStringList result;
	result << "BLOCK:";
	for (int i=0;i<m_commands.size();i++) {
		QStringList child = m_commands[i]->debugRepresentation();
		foreach (const QString& s, child)
			result << "    " + s;
	}
	return result;
}


QDocumentChangeMetaDataCommand::QDocumentChangeMetaDataCommand(QDocument *d, QTextCodec* newCodec)
	:QDocumentCommand(Custom, d){
	init(newCodec, d->lineEnding());
}
QDocumentChangeMetaDataCommand::QDocumentChangeMetaDataCommand(QDocument *d, QDocument::LineEnding newLineEnding)
       :QDocumentCommand(Custom, d){
	init(d->codec(), newLineEnding);
}

void QDocumentChangeMetaDataCommand::redo(){
	m_doc->setCodecDirect(newCodec);
	m_doc->setLineEndingDirect(newLineEnding);
}

void QDocumentChangeMetaDataCommand::undo(){
	m_doc->setLineEndingDirect(oldLineEnding);	
	m_doc->setCodecDirect(oldCodec);
}

void QDocumentChangeMetaDataCommand::init(QTextCodec* newCodec, QDocument::LineEnding newLineEnding){
	this->oldCodec = m_doc->codec();
	this->newCodec = newCodec;
	this->oldLineEnding = m_doc->lineEnding();
	this->newLineEnding = newLineEnding;
}

QStringList QDocumentChangeMetaDataCommand::debugRepresentation() const{
	return QStringList() << QString("META DATA CHANGE: Encoding: %1=>%2; Line-Ending: %3=>%4").arg(oldCodec?oldCodec->name().data():"0").arg(newCodec?newCodec->name().data():"0").arg(oldLineEnding).arg(newLineEnding);
}

/*! @} */

