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

#include "qeditsession.h"

/*!
	\file qeditsession.cpp
	\brief Implementation of the QEditSession class.
*/

#include "qeditor.h"
#include "qdocument.h"
#include "qdocument_p.h"
#include "qdocumentline.h"
#include "qdocumentcursor.h"

#include "qlinemarksinfocenter.h"

#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QScrollBar>

/*!
	\class QEditSession
	
	\brief A session recording class
	
	The purpose of this class is to collect session data from several QEditor object,
	to serialize it and to re-create the same session by deserializing the stored data.
*/

/*!
	\brief ctor
*/
QEditSession::QEditSession(QObject *p)
 : QObject(p), m_id(-1), m_delay(0)
{
	setFormat(FormatCount - 1);
}

/*!
	\brief ctor
*/
QEditSession::QEditSession(const QString& f, QObject *p)
 : QObject(p), m_id(-1), m_delay(0)
{
	setFileName(f);
	setFormat(FormatCount - 1);
}

/*!
	\brief dtor
*/
QEditSession::~QEditSession()
{
	
}

/*!
	\return The update interval, in milliseconds
	
	A value of zero means the data is NOT automatically updated.
	
	\see updateData()
*/
int QEditSession::autoUpdateInterval() const
{
	return m_delay;
}

/*!
	\brief Set the update interval
	
	If \a ms is strictly positive then the data will be
	updated every \a ms milliseconds
	
	If the session has been given a valid filename, the updated
	data will automatically be saved to that file.
*/
void QEditSession::setAutoUpdateInterval(int ms)
{
	if ( m_delay )
	{
		killTimer(m_id);
		m_id = -1;
	}
	
	m_delay = ms;
	
	if ( m_delay )
	{
		m_id = startTimer(m_delay);
	}
}

/*!
	\return The format used to save session data
*/
int QEditSession::format() const
{
	return m_format;
}

/*!
	\brief Set the session save format
	
	QEditSession maintains full backward compatibility for session
	loading, automatically determining the session format and using
	proper loader. However it will automatically convert session
	files when saving (to the latest format by default). If you want
	to enforce backward compat of session files with older releases
	you may want to manually set the session save format.
*/
void QEditSession::setFormat(int fmt)
{
	m_format = fmt;
}

/*!
	\return The file name used as storage
	
	If it is empty then no auto-save is performed.
*/
QString QEditSession::fileName() const
{
	return m_fileName;
}

/*!
	\brief Set the storage destination
	
	Every time the data is updated, either when the autoupdate timer
	ticks or when updateData() is called programmatically, it will be
	written to that file, provided the filename is valid and points
	to a writeable location.
	
	\see updateData()
	\see autoUpdateInterval()
*/
void QEditSession::setFileName(const QString& filename, bool r)
{
	m_fileName = filename;
	
	if ( r )
		restore();
	
}

/*!
	\brief Add an editor to the session
*/
void QEditSession::addEditor(QEditor *e)
{
	if ( m_editors.contains(e) )
		return;
	
	//qDebug("+ 0x%x", e);
	
	Document *d = new Document;
	d->flags = 0;
	
	m_editors << e;
	m_sessionData << d;
	
	connect(e	, SIGNAL( destroyed(QObject*) ),
			this, SLOT  ( destroyed(QObject*) ) );
	
	connect(e	, SIGNAL( saved(QEditor*, QString) ),
			this, SLOT  ( saved(QEditor*, QString) ) );
	
	connect(e	, SIGNAL( loaded(QEditor*, QString) ),
			this, SLOT  ( loaded(QEditor*, QString) ) );
	
	update(e, d);
}

/*!
	\brief Remove an editor from the session
*/
void QEditSession::removeEditor(QEditor *e)
{
	int idx = m_editors.indexOf(e);
	
	if ( idx == -1 )
		return;
	
	//qDebug("- 0x%x", e);
	
	disconnect(	e	, SIGNAL( destroyed(QObject*) ),
				this, SLOT  ( destroyed(QObject*) ) );
	
	disconnect(	e	, SIGNAL( saved(QEditor*, QString) ),
				this, SLOT  ( saved(QEditor*, QString) ) );
	
	disconnect(	e	, SIGNAL( loaded(QEditor*, QString) ),
				this, SLOT  ( loaded(QEditor*, QString) ) );
	
	m_editors.removeAt(idx);
	delete m_sessionData.takeAt(idx);
}

/*!
	
*/
void QEditSession::clear(bool cleanup)
{
	if ( cleanup )
		qDeleteAll(m_editors);
	
	qDeleteAll(m_sessionData);
	
	m_editors.clear();
	m_sessionData.clear();
}

/*!
	\brief Serialize session data
*/
void QEditSession::save()
{
	QFile f(m_fileName);
	
	if ( f.open(QFile::WriteOnly) )
	{
		QDataStream s(&f);
		
		save(s);
	}
}

/*!
	\brief Serialize session data
*/
void QEditSession::restore()
{
	QFile f(m_fileName);
	
	if ( f.open(QFile::ReadOnly) )
	{
		QDataStream s(&f);
		
		restore(s);
	}
}

typedef void (*save_func)(QDataStream&, const QList<QEditSession::Document*>&);
typedef QList<QEditSession::Document*> (*restore_func)(QDataStream&);

QList<QEditSession::Document*> restore_qes(QDataStream&);
void save_qes(QDataStream&, const QList<QEditSession::Document*>&);

QList<QEditSession::Document*> restore_qes1(QDataStream&);
void save_qes1(QDataStream&, const QList<QEditSession::Document*>&);

// magic numbers (4 letters, 4 bytes, 32bit integer...)
/*
	
*/
static QList<const char*> _magic = QList<const char*>()
	<< "QES "
	<< "QES1";

static QList<save_func> _save = QList<save_func>()
	<< save_qes
	<< save_qes1;

static QList<restore_func> _restore = QList<restore_func>()
	<< restore_qes
	<< restore_qes1;

///////////////////////////////////////////////////////////////////////////////

/*!
	\brief Serialize session data
*/
void QEditSession::save(QDataStream& s)
{
	int format = qBound(0, m_format, FormatCount - 1);
	
	s.writeRawData(_magic.at(format), 4);
	
	//qDebug("saving session [fmt:%i]", format);
	_save.at(format)(s, m_sessionData);
}

/*!
	\brief Deserialize session data
*/
void QEditSession::restore(QDataStream& s)
{
	//qDebug("restoring");
	
	char magic[4];
	
	s.readRawData(magic, 4);
	
	for ( int i = 0; i < _magic.count(); ++i )
	{
		const char *mi = _magic.at(i);
		bool matchMagic, normal = true, wicked = true;
		
		for ( int j = 0; j < 4; ++j )
		{
			normal &= magic[j] == mi[j];
			wicked &= magic[j] == mi[3 - j];
		}
		
		matchMagic = i ? normal : normal | wicked;
		
		if ( matchMagic )
		{
			//qDebug("loading session [fmt:%i]", i);
			
			QList<Document*> docs = _restore.at(i)(s);
			
			foreach ( Document *d, docs )
			{
				if ( QFile::exists(d->fileName) )
				{
					QEditor *e = createEditor();
					
					e->load(d->fileName);
					
					QDocumentCursor c = d->cursors.first().toDocumentCursor(e->document());
					
					if ( d->cursors.count() )
					{
						e->setCursor(c);
						
						for ( int j = 1; j < d->cursors.count(); ++j )
							e->addCursorMirror(d->cursors.at(j).toDocumentCursor(e->document()));
					}
					
					QHash<int, QList<int> >::const_iterator it = d->marks.constBegin();
					
					while ( it != d->marks.constEnd() )
					{
						QList<int> marks = *it;
						
						foreach ( int mark, marks )
							e->document()->line(it.key()).addMark(mark);
					}
					
					// TODO : defer. it does not seem to work properly that way
					// TODO : view size independency (store the first visible line number)
					e->verticalScrollBar()->setValue(d->scrollY);
					e->horizontalScrollBar()->setValue(d->scrollX);
					
					connect(e	, SIGNAL( destroyed(QObject*) ),
							this, SLOT  ( destroyed(QObject*) ) );
					
					connect(e	, SIGNAL( saved(QEditor*, QString) ),
							this, SLOT  ( saved(QEditor*, QString) ) );
					
					connect(e	, SIGNAL( loaded(QEditor*, QString) ),
							this, SLOT  ( loaded(QEditor*, QString) ) );
					
					m_editors << e;
					m_sessionData << d;
					
					emit restored(e);
				} else {
					delete d;
				}
			}
			
			return;
		}
	}
	
	qWarning("Unsupported session format");
}

/*!
	\brief Updates the data
	
	Fetches up-to-date session data from the attached editors.
	
	If the session has been given a valid filename the data will
	automatically be saved.
	
	\note This will NOT affect the automatic updates timing
*/
void QEditSession::updateData()
{
	for ( int i = 0; i < m_editors.count(); ++i )
	{
		QEditor *e = m_editors.at(i);
		Document *d = m_sessionData.at(i);
		
		update(e, d);
	}
	
	save();
}

void QEditSession::destroyed(QObject *o)
{
	//qDebug("~ 0x%x", o);
	
	for ( int i = 0; i < m_editors.count(); ++i )
	{
		QEditor *e = m_editors.at(i);
		
		if ( !e || ((QObject*)e == o) )
		{
			delete m_sessionData.takeAt(i);
			m_editors.removeAt(i);
			break;
		}
	}
}

/*!
	\brief Called whenever an editor is saved
	
	This handler is responsible for updating file names and time stamps
	which is needed to avoid data loss upon session restoration
*/
void QEditSession::saved(QEditor *e, const QString& fn)
{
	int idx = m_editors.indexOf(e);
	
	if ( idx == -1 )
		return;
	
	//qDebug("saved : %s", qPrintable(fn));
	
	Document *d = m_sessionData.at(idx);
	
	//d->timeStamp = QDateTime::currentDateTime();
	
	update(e, d);
}

/*!
	\brief Called whenever an editor is loaded with new content
	
	This handler is responsible for updating file names and time stamps
	which is needed to avoid data loss upon session restoration
*/
void QEditSession::loaded(QEditor *e, const QString& fn)
{
	int idx = m_editors.indexOf(e);
	
	if ( idx == -1 )
		return;
	
	//qDebug("loaded : %s", qPrintable(fn));
	
	Document *d = m_sessionData.at(idx);
	
	//d->timeStamp = QDateTime::currentDateTime();
	
	update(e, d);
}

void QEditSession::update(QEditor *e, Document *d)
{
	if ( !e || !d )
		return;
	
	//qDebug(">>%s", qPrintable(e->fileName()));
	
	d->fileName = e->fileName();
	d->timeStamp = QFileInfo(d->fileName).lastModified();
	
	d->cursors.clear();
	d->cursors << Cursor(e->cursor());
	
	for ( int i = 0; i < e->cursorMirrorCount(); ++i )
		d->cursors << Cursor(e->cursorMirror(i));
	
	d->marks.clear();
	
	QLineMarkList marks = QLineMarksInfoCenter::instance()->marks(d->fileName);
	
	foreach ( const QLineMark& mark, marks )
	{
		d->marks[mark.line] << mark.mark;
	}
	
	d->scrollX = e->verticalScrollBar()->value();
	d->scrollY = e->horizontalScrollBar()->value();
}

/*!
	\internal
*/
void QEditSession::timerEvent(QTimerEvent *e)
{
	if ( e->timerId() == m_id )
	{
		updateData();
	}
}

QEditor* QEditSession::createEditor()
{
	return new QEditor;
}

QEditSession::Cursor::Cursor(const QDocumentCursor& c)
{
	beginLine = c.lineNumber();
	beginColumn = c.columnNumber();
	endLine = c.hasSelection() ? c.anchorLineNumber() : -1;
	endColumn = c.hasSelection() ? c.anchorColumnNumber() : -1;
	
	//qDebug("((%i, %i), (%i, %i))", beginLine, beginColumn, endLine, endColumn);
}

QDocumentCursor QEditSession::Cursor::toDocumentCursor(QDocument *d) const
{
	//qDebug("((%i, %i), (%i, %i))", beginLine, beginColumn, endLine, endColumn);
	
	QDocumentCursor beg(d, beginLine, beginColumn);
	QDocumentCursor end(d, endLine, endColumn);
	
	if ( endLine != -1 )
	{
		end.setSelectionBoundary(beg);
		return end;
	}
	
	return beg;
}

///////////////////////////////////////////////////////////////////////////////

QList<QEditSession::Document*> restore_qes(QDataStream& s)
{
	QList<QEditSession::Document*> l;
	int documentCount = 0;
	
	s >> documentCount;
	
	for ( int i = 0; i < documentCount; ++i )
	{
		QEditSession::Document *d = new QEditSession::Document;
		d->flags = 0;
		
		s >> d->fileName;
		s >> d->timeStamp;
		
		//qDebug("> %s", qPrintable(d->fileName));
		
		int cursorCount = 0;
		
		s >> cursorCount;
		
		for ( int j = 0; j < cursorCount; ++j )
		{
			QEditSession::Cursor c;
			
			s >> c.beginLine;
			s >> c.beginColumn;
			s >> c.endLine;
			s >> c.endColumn;
			
			d->cursors << c;
		}
		
		int markCount = 0;
		s >> markCount;
		
		for ( int j = 0; j < markCount; ++j )
		{
			int line = 0;
			QList<int> marks;
			
			s >> line;
			s >> marks;
			
			d->marks[line] = marks;
			
		}
		
		s >> d->scrollX;
		s >> d->scrollY;
		
		l << d;
	}
	
	return l;
}

void save_qes(QDataStream& s, const QList<QEditSession::Document*>& m_sessionData)
{
	s << m_sessionData.count();
	
	foreach ( QEditSession::Document *d, m_sessionData )
	{
		//qDebug("> %s", qPrintable(d->fileName));
		
		s << d->fileName;
		s << d->timeStamp;
		
		s << d->cursors.count();
		
		foreach ( const QEditSession::Cursor& c, d->cursors )
			s << c.beginLine << c.beginColumn << c.endLine << c.endColumn;
		
		s << d->marks.count();
		
		QHash<int, QList<int> >::const_iterator it = d->marks.constBegin();
		const QHash<int, QList<int> >::const_iterator end = d->marks.constEnd();
		
		while ( it != end )
		{
			s << it.key() << *it;
			++it;
		}
		
		s << d->scrollX;
		s << d->scrollY;
	}
}

///////////////////////////////////////////////////////////////////////////////

QList<QEditSession::Document*> restore_qes1(QDataStream& s)
{
	QList<QEditSession::Document*> l;
	
	quint32 version = 0;
	s >> version;
	
	if ( version )
	{
		qWarning("Unsupported version of session format (QCESession1) : possible data loss");
	}
	
	quint32 documentCount = 0;
	s >> documentCount;
	
	for ( quint32 i = 0; i < documentCount; ++i )
	{
		QEditSession::Document *d = new QEditSession::Document;
		
		s >> d->flags;
		s >> d->fileName;
		s >> d->timeStamp;
		
		//qDebug("> %s", qPrintable(d->fileName));
		
		quint32 cursorCount = 0;
		
		s >> cursorCount;
		
		for ( quint32 j = 0; j < cursorCount; ++j )
		{
			QEditSession::Cursor c;
			
			s >> c.beginLine;
			s >> c.beginColumn;
			s >> c.endLine;
			s >> c.endColumn;
			
			d->cursors << c;
		}
		
		quint32 markCount = 0;
		s >> markCount;
		
		for ( quint32 j = 0; j < markCount; ++j )
		{
			int line = 0;
			QList<int> marks;
			
			s >> line;
			s >> marks;
			
			d->marks[line] = marks;
		}
		
		s >> d->scrollX;
		s >> d->scrollY;
		
		// handle extra (version-specific) fields here
		
		qint32 extra_sz;
		s >> extra_sz;
		
		// make sure we do not mistake extra fields as data for another document
		s.skipRawData(extra_sz);
		
		
		l << d;
	}
	
	return l;
}

void save_qes1(QDataStream& s, const QList<QEditSession::Document*>& m_sessionData)
{
	bool supportExtra = !s.device()->isSequential();
	
	s << quint32(0);
	
	s << m_sessionData.count();
	
	foreach ( QEditSession::Document *d, m_sessionData )
	{
		//qDebug("> %s", qPrintable(d->fileName));
		
		s << d->flags;
		s << d->fileName;
		s << d->timeStamp;
		
		s << d->cursors.count();
		
		foreach ( const QEditSession::Cursor& c, d->cursors )
			s << c.beginLine << c.beginColumn << c.endLine << c.endColumn;
		
		s << d->marks.count();
		
		QHash<int, QList<int> >::const_iterator it = d->marks.constBegin();
		const QHash<int, QList<int> >::const_iterator end = d->marks.constEnd();
		
		while ( it != end )
		{
			s << it.key() << *it;
			++it;
		}
		
		s << d->scrollX;
		s << d->scrollY;
		
		// extra data
		if ( supportExtra )
		{
			// make room for size field and record position
			qint64 sz_pos = s.device()->pos();
			s << qint32(0);
			qint64 post_sz_pos = s.device()->pos();
			
			
			// write extra fields here
			
			//s << "some crap to test extra fields.";
			
			
			
			// update the value of the size field based on what was written
			qint64 extra_end = s.device()->pos();
			s.device()->seek(sz_pos);
			s << qint32(extra_end - post_sz_pos);
			s.device()->seek(extra_end);
			
			//qDebug("%i, %i, %i", qint32(sz_pos), qint32(post_sz_pos), qint32(extra_end));
		} else {
			// no extra fields
			s << qint32(0);
			
			
		}
	}
}
