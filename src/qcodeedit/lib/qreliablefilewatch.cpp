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

#include "qreliablefilewatch.h"

/*!
	\file qreliablefilewatch.cpp
	\brief Implementation of the QReliableFileWatch class.
*/

/*!
	\class QReliableFileWatch
	\brief A specialized file monitor that works around some issues in QFileSystemWatcher
*/

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
		if (!it->recipients.contains(recipient))
			it->recipients << recipient;
	} else {
		QFile f(file);
		QFileInfo info(file);

		Watch w;
		w.state = Clean;
		w.size = f.size();
		w.lastModified=info.lastModified();
		w.recipients << recipient;
		m_targets[file] = w;

		addPath(file);
	}
}

void QReliableFileWatch::removeWatch(QObject *recipient)
{
	removeWatch(QString(), recipient);
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
			removePath(it.key());
			m_targets.erase(it);
		}
	}
}

void QReliableFileWatch::timerEvent(QTimerEvent *e)
{
	if ( e->timerId() != m_timer.timerId() )
		return QFileSystemWatcher::timerEvent(e);

	int postponedEmissions = 0;
	QHash<QString, Watch> targets=m_targets; //copy targets, so m_targets can be modified from the invoken functions without crashing
	QHash<QString, Watch>::iterator it = targets.begin();

	while ( it != targets.end() )
	{
		if ( it->state & Duplicate )
		{
			// postpone signal emission...
			++postponedEmissions;
		} else if ( it->state & Recent ) {
//			// send signal
//			it->state = Clean;
/*
			QFile f(it.key());

			if ( f.size() == (unsigned int)(it->size) )
			{
				// TODO : avoid signal emission if checksum match
				// DO this in editor or here?
			}*/

			//qDebug("%s emission.", qPrintable(it.key()));

            it->recipients.removeAll(nullptr);

			QFileInfo fi(it.key());
			qint64 size = fi.size();
			QDateTime lastModified = fi.lastModified();
			foreach ( QObject *r, it->recipients )
				QMetaObject::invokeMethod(r, "fileChanged", Q_ARG(QString, it.key()));
			fi.refresh();
			if (fi.size() != size || fi.lastModified() != lastModified) {
				QHash<QString, Watch>::iterator it2 = m_targets.find(it.key());
				if (it2 != m_targets.end()) {
					it2->state = Recent | Duplicate;
					it2->size = size;
					it2->lastModified = lastModified;
				}
				++ postponedEmissions;
			}
			//it = m_state.erase(it);
		}

		++it;
	}

	m_timer.stop();
	if ( postponedEmissions )
	{
		//remove duplicates from the real hash
		it = m_targets.begin();
		while (it != m_targets.end()) {
			if ( it->state & Duplicate ) 
				it->state = Recent;
			++it;
		}
		//qDebug("%i postponed emissions", postponedEmissions);
		m_timer.start(20, this);
	} else {
		//remove changes from the real hash
		it = m_targets.begin();
		while (it != m_targets.end()) {
			if ( it->state & Recent ) 
				it->state = Clean;
			++it;
		}
	} 
}

void QReliableFileWatch::sourceChanged(const QString& filepath)
{
	m_timer.stop();

	QHash<QString, Watch>::iterator it = m_targets.find(filepath);
	if ( it == m_targets.end() )
		return;

	qDebug("%s modified.", qPrintable(filepath));
	QFileInfo info(filepath);
	if(it->lastModified==info.lastModified() && it->size==info.size()){
		qDebug("filtered");
		return;
	}

	if ( it->state )
	{
		it->state = Recent | Duplicate;
	} else {
		it->state = Recent;
	}

	m_timer.start(20, this);
}
