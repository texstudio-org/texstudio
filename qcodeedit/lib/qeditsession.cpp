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
void QEditSession::setFileName(const QString& filename)
{
	m_fileName = filename;
}

/*!
	\brief Add an editor to the session
*/
void QEditSession::addEditor(QEditor *e)
{
	if ( m_editors.contains(e) )
		return;
	
	Document *d = new Document;
	d->fileName = e->fileName();
	d->timeStamp = QFile(d->fileName).lastModified();
	d->cursors << Cursor(e->cursor());
	
	m_editors << e;
	m_sessionData << d;
}

/*!
	\brief Remove an editor from the session
*/
void QEditSession::removeEditor(QEditor *e)
{
	int idx = m_editors.indexOf(e);
	
	if ( idx == -1 )
		return;
	
	m_editors.removeAt(e);
	delete m_sessionData.takeAt(idx);
}

/*!
	\brief Serialize session data
*/
void QEditSession::save(QDataStream& s)
{
	
}

/*!
	\brief Deserialize session data
*/
void QEditSession::restore(const QDataStream& s)
{
	
}

/*!
	\brief Updates the data
	
	Fetches up-to-date session data from the attached editors.
	
	If the session has been given a valid filename the data will
	automatically be saved.
	
	\note This will NOT affect the automatic updates
*/
void QEditSession::updateData()
{
	foreach ( QEditor *e, m_editors )
	{
		if ( !e )
			continue;
		
	}
}

/*!
	\brief Called whenever an editor is saved
	
	This handler is responsible for updating file names and time stamps
	which is needed to avoid data loss upon session restoration
*/
void QEditSession::saved(QEditor *e)
{
	int idx = m_editors.indexOf(e);
	
	if ( idx == -1 )
		return;
	
	
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
