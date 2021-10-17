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

#ifndef Header_QReliable_FileWatch
#define Header_QReliable_FileWatch

#include "mostQtHeaders.h"

#include "qce-config.h"

/*!
	\file qreliablefilewatch.h
	\brief Definition of the QReliableFileWatch class
*/

class QCE_EXPORT QReliableFileWatch : protected QFileSystemWatcher
{
	friend class QPointer<QReliableFileWatch>;
	
	Q_OBJECT
	
	public:
		QReliableFileWatch(QObject *p = 0);
		virtual ~QReliableFileWatch();
		
	public slots:
		void addWatch(const QString& file, QObject *recipient);
		
		void removeWatch(QObject *recipient);
		void removeWatch(const QString& file, QObject *recipient);
		
	protected:
		virtual void timerEvent(QTimerEvent *e);
		
	private slots:
		void sourceChanged(const QString& filepath);
		
	private:
		enum State
		{
			Clean		= 0,
			Recent		= 1,
			Duplicate	= 2
		};
		
		struct Watch
		{
			char state;
			qint64 size;
			QList< QPointer<QObject> > recipients;
			QDateTime lastModified;
		};
		
		QBasicTimer m_timer;
		
		QHash<QString, Watch> m_targets;
};

#endif // !_QRELIABLE_FILE_WATCH_H_
