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

/*!
	\ingroup document
	@{
*/

/*!
	\class QDocumentCommand
	\brief The base class for document editing command
*/

QList<QDocumentCursorHandle*> QDocumentCommand::m_autoUpdated;

/*!
	\brief ctor
*/
QDocumentCommand::QDocumentCommand(Command c, QDocument *d, QDocumentCommand *p)
 : QUndoCommand(p),
	m_state(false), m_first(true), m_doc(d),
	m_redoOffset(0), m_undoOffset(0),
	m_silent(false), m_command(c), m_cursor(0)
{
	
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
bool QDocumentCommand::mergeWith(const QUndoCommand *)
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
	
	h->textBuffer().insert(pos, s);
	h->shiftOverlays(pos, s.length());
	
	foreach ( QDocumentCursorHandle *ch, m_autoUpdated )
	{
		if ( (pd->at(ch->m_begLine) == h) && (ch->m_begOffset >= pos) )
		{
			ch->m_begOffset += s.length();
		}
		
		if ( (pd->at(ch->m_endLine) == h) && (ch->m_endOffset >= pos) )
		{
			ch->m_endOffset += s.length();
		}
	}
	
	pd->adjustWidth(line);
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
	
	if ( !h )
		return;
	
	h->textBuffer().remove(pos, length);
	h->shiftOverlays(pos, -length);
	
	QList<QDocumentCursorHandle*> m_del;
	
	foreach ( QDocumentCursorHandle *ch, m_autoUpdated )
	{
		if ( pd->at(ch->m_begLine) == h )
		{
			if ( ch->m_begOffset < pos )
				continue;
			
			if ( ch->m_begOffset >= (pos + length) )
			{
				ch->m_begOffset -= length;
			} else {
				// TODO : what if only part of a selection disappeared???
				// cursor caught in a deleted text..
				ch->moveTo(QDocumentCursor());
				m_del << ch;
			}
		}
		
		if ( pd->at(ch->m_endLine) == h )
		{
			if ( ch->m_endOffset < pos )
				continue;
			
			if ( ch->m_endOffset >= (pos + length) )
			{
				ch->m_endOffset -= length;
			} else {
				// TODO : what if only part of a selection disappeared???
				// cursor caught in a deleted text..
				ch->moveTo(QDocumentCursor());
				m_del << ch;
			}
		}
	}
	
	foreach ( QDocumentCursorHandle *ch, m_del )
	{
		//qDebug("hard-no-up(0x%x)", h);
		//m_autoUpdated.removeAll(ch);
	}
	
	pd->adjustWidth(line);
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
	if ( l.isEmpty() )
		return;
	
	//printf("[processing %i watches]\n", m_autoUpdated.count());
	//fflush(stdout);
	
	foreach ( QDocumentCursorHandle *ch, m_autoUpdated )
	{
		//printf("[[watch:0x%x(%i, %i)]]", ch, ch->m_begLine, ch->m_begOffset);
		
		if ( ch->m_begLine > after )
		{
//			qDebug("moving cursor [0x%x:beg] from line %i to %i upon insertion of %i lines",
//					ch,
//					ch->m_begLine,
//					ch->m_begLine + l.count(),
//					l.count()
//					);
//			
			//printf(" moved.\n");
			ch->m_begLine += l.count();
		} else {
//			qDebug("skipped cursor [0x%x:beg] at line %i upon insertion of %i lines",
//					ch,
//					ch->m_begLine,
//					l.count()
//					);
//			
			//printf("\n");
		}
		
		if ( ch->m_endLine > after )
		{
//			qDebug("moving cursor [0x%x:end] from line %i to %i upon insertion of %i lines",
//					ch,
//					ch->m_endLine,
//					ch->m_endLine + l.count(),
//					l.count()
//					);
//			
			ch->m_endLine += l.count();
		}
		
		//fflush(stdout);
	}
	
	m_doc->impl()->insertLines(after, l);
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
	if ( n <= 0 )
		return;
	
	foreach ( QDocumentCursorHandle *ch, m_autoUpdated )
	{
		if ( ch->m_begLine > after )
		{
//			qDebug("moving cursor [0x%x:beg] from line %i to %i upon deletion of %i lines",
//					ch,
//					ch->m_begLine,
//					ch->m_begLine - n,
//					n
//					);
//			
			ch->m_begLine -= n;
		}
		
		if ( ch->m_endLine > after )
		{
//			qDebug("moving cursor [0x%x:end] from line %i to %i upon deletion of %i lines",
//					ch,
//					ch->m_endLine,
//					ch->m_endLine - n,
//					n
//					);
//			
			ch->m_endLine -= n;
		}
	}
	
	m_doc->impl()->removeLines(after, n);
}

/*!
	\brief Update the target cursor
	\param l target line
	\param offset target text position within target line
*/
void QDocumentCommand::updateTarget(int l, int offset)
{
	QDocumentLineHandle *h = m_doc->impl()->at(l);
	
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
		
		m_cursor->m_begLine = l;
		m_cursor->m_begOffset = qMax(0, offset);
		m_cursor->m_endLine = -1;
		m_cursor->m_endOffset = -1;
		
		m_cursor->refreshColumnMemory();
	}
}

/*!
	\return whether a given cursor is auto updated
*/
bool QDocumentCommand::isAutoUpdated(const QDocumentCursorHandle *h)
{
	return m_autoUpdated.contains(const_cast<QDocumentCursorHandle*>(h));
}

/*!
	\brief Enable auto update for a given cursor
*/
void QDocumentCommand::enableAutoUpdate(QDocumentCursorHandle *h)
{
	//qDebug("up(0x%x)", h);
	
	if ( !m_autoUpdated.contains(h) )
		m_autoUpdated << h;
}

/*!
	\brief Disable auto update for a given cursor
*/
void QDocumentCommand::disableAutoUpdate(QDocumentCursorHandle *h)
{
	//qDebug("no-up(0x%x)", h);
	m_autoUpdated.removeAll(h);
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
		qDebug("warning: status data and/or undo stack corrupted...");
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
	QStringList lines = text.split(QLatin1Char('\n'), QString::KeepEmptyParts);
	
	if ( !m_doc || text.isEmpty() )
		qFatal("Invalid insert command");
	
	m_data.lineNumber = l;
	m_data.startOffset = offset;
	
	m_data.begin = lines.takeAt(0);
	
	foreach ( const QString& s, lines )
		m_data.handles << new QDocumentLineHandle(s, m_doc);
	
	QDocumentLine bl = m_doc->line(l);
	
	if ( m_data.handles.count() && (bl.length() > offset) )
	{
		m_data.end = bl.text().mid(m_data.startOffset);
		
		m_data.handles.last()->textBuffer().append(m_data.end);
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
	
	//foreach ( QDocumentLineHandle *h, m_data.handles )
	//	h->deref();
	
}

bool QDocumentInsertCommand::mergeWith(const QUndoCommand *)
{
	return false;
}

void QDocumentInsertCommand::redo()
{
	// state : handles used by doc
	m_state = true;
	
	//QDocumentIterator it = m_doc->impl()->index(m_data.lineNumber);
	
	//qDebug("inserting %i lines after %i", m_data.handles.count(), m_data.lineNumber);
	
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
	
	m_doc->impl()->emitContentsChange(m_data.lineNumber, m_data.handles.count() + 1);
	
	markRedone(hl, m_first);
	
	foreach ( QDocumentLineHandle *h, m_data.handles )
		markRedone(h, m_first);
	
	//m_doc->impl()->emitContentsChanged();
	m_first = false;
}

void QDocumentInsertCommand::undo()
{
	// state : handles !used by doc
	m_state = false;
	
	//QDocumentIterator it = m_doc->impl()->index(m_data.line);
	
	QDocumentLineHandle *hl = m_doc->impl()->at(m_data.lineNumber);
	
	removeLines(m_data.lineNumber, m_data.handles.count());
	removeText(m_data.lineNumber, m_data.startOffset, m_data.begin.count());
	
	if ( m_data.handles.count() )
	{
		insertText(m_data.lineNumber, m_data.startOffset, m_data.end);
	}
	
	updateTarget(m_data.lineNumber, m_data.startOffset + m_undoOffset);
	
	m_doc->impl()->emitContentsChange(m_data.lineNumber, m_data.handles.count() + 1);
	
	markUndone(hl);
	
	foreach ( QDocumentLineHandle *h, m_data.handles )
		markUndone(h);
	
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
}

/*!
	\brief dtor
*/
QDocumentEraseCommand::~QDocumentEraseCommand()
{
	if ( m_state )
		return;
	
	//qDeleteAll(m_data.handles);
}

bool QDocumentEraseCommand::mergeWith(const QUndoCommand *)
{
	return false;
}

void QDocumentEraseCommand::redo()
{
	// state : handles !used by doc
	m_state = false;
	
	//QDocumentIterator it = m_doc->impl()->index(m_data.line);
	
	QDocumentLineHandle *hl = m_doc->impl()->at(m_data.lineNumber);
	
	if ( m_data.handles.isEmpty() )
	{
		removeText(m_data.lineNumber, m_data.startOffset, m_data.begin.count());
		
		m_doc->impl()->emitContentsChange(m_data.lineNumber, 1);
		
	} else {
		removeText(m_data.lineNumber, m_data.startOffset, m_data.begin.count());
		
		if ( m_data.endOffset != -1 )
			insertText(m_data.lineNumber, m_data.startOffset, m_data.end);
		
		removeLines(m_data.lineNumber, m_data.handles.count());
		
		m_doc->impl()->emitContentsChange(m_data.lineNumber, m_data.handles.count() + 1);
	}
	
	updateTarget(m_data.lineNumber, m_data.startOffset + m_redoOffset);
	
	markRedone(hl, m_first);
	
	foreach ( QDocumentLineHandle *h, m_data.handles )
		markRedone(h, m_first);
	
	//m_doc->impl()->emitContentsChanged();
	m_first = false;
}

void QDocumentEraseCommand::undo()
{
	// state : handles used by doc
	m_state = true;
	
	//QDocumentIterator it = m_doc->impl()->index(m_data.line);
	
	QDocumentLineHandle *hl = m_doc->impl()->at(m_data.lineNumber);
	
	if ( m_data.handles.count() )
	{
		insertLines(m_data.lineNumber, m_data.handles);
		
		if ( m_data.endOffset != -1 )
			removeText(m_data.lineNumber, m_data.startOffset, m_data.end.count());
		
		insertText(m_data.lineNumber, m_data.startOffset, m_data.begin);
		
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
	
	markUndone(hl);
	
	foreach ( QDocumentLineHandle *h, m_data.handles )
		markUndone(h);
	
	//m_doc->impl()->emitContentsChanged();
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

/*! @} */

