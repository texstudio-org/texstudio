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

#include "qreliablefilewatch.h"

#include <QFile>
#include <QTimerEvent>

QReliableFileWatch::QReliableFileWatch(QObject *p)
 : QFileSystemWatcher(p)
{
	connect(this, SIGNAL( fileChanged(QString) ),
			this, SLOT  ( sourceChanged(QString) ) );
	
}

QReliableFileWatch::~QReliableFileWatch()
{
	
}

void QReliableFileWatch::addWatch(const QString& file, QObject *recipient)
{
	QHash<QString, Watch>::iterator it = m_targets.find(file);
	
	if ( it != m_targets.end() )
	{
		it->recipients << recipient;
	} else {
		QFile f(file);
		
		Watch w;
		w.state = Clean;
		w.checksum = -1;
		w.size = f.size();
		w.recipients << recipient;
		m_targets[file] = w;
		
		addPath(file);
	}
}

void QReliableFileWatch::removeWatch(const QString& file, QObject *recipient)
{
	QHash<QString, Watch>::iterator it = m_targets.find(file);
	
	if ( it == m_targets.end() )
	{
		if ( !recipient )
			return;
		
		// given recipient stop watching any file
		
		it = m_targets.begin();
		
		while ( it != m_targets.end() )
		{
			int n = it->recipients.removeAll(recipient);
			
			if ( n && it->recipients.isEmpty() )
			{
				// no more recipients watching this file
				removePath(it.key());
				it = m_targets.erase(it);
			} else {
				++it;
			}
		}
	} else {
		if ( recipient )
		{
			// given recipient stops watching given file
			it->recipients.removeAll(recipient);
			
			if ( it->recipients.isEmpty() )
			{
				// no more recipients watching this file
				removePath(it.key());
				m_targets.erase(it);
			}
		} else {
			// stop watching given file at all
			m_targets.erase(it);
		}
	} 
}

void QReliableFileWatch::timerEvent(QTimerEvent *e)
{
	if ( e->timerId() != m_timer.timerId() )
		return QFileSystemWatcher::timerEvent(e);
	
	int postponedEmissions = 0;
	QHash<QString, Watch>::iterator it = m_targets.begin();
	
	while ( it != m_targets.end() )
	{
		if ( it->state & Duplicate )
		{
			// postpone signal emission...
			++postponedEmissions;
			it->state = Recent;
		} else if ( it->state & Recent ) {
			// send signal
			it->state = Clean;
			
			QFile f(it.key());
			
			if ( f.size() == it->size )
			{
				// TODO : avoid signal emission if checksum match
				// DO this in editor or here?
			}
			
			//qDebug("%s emission.", qPrintable(it.key()));
			
			foreach ( QObject *r, it->recipients )
				QMetaObject::invokeMethod(r, "fileChanged", Q_ARG(QString, it.key()));
			
			//it = m_state.erase(it);
		}
		
		++it;
	}
	
	if ( postponedEmissions )
	{
		//qDebug("%i postponed emissions", postponedEmissions);
		m_timer.start(20, this);
	}
}

void QReliableFileWatch::sourceChanged(const QString& filepath)
{
	m_timer.stop();
	
	QHash<QString, Watch>::iterator it = m_targets.find(filepath);
	
	if ( it == m_targets.end() )
		return;
	
	//qDebug("%s modified.", qPrintable(filepath));
	
	if ( it->state )
	{
		it->state = Recent | Duplicate;
	} else {
		it->state = Recent;
	}
	
	m_timer.start(20, this);
}
