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

#ifndef _QEDIT_SESSION_H_
#define _QEDIT_SESSION_H_

#include "qce-config.h"

/*!
	\file qeditsession.h
	\brief Definition of the QEditSession class.
*/

#include <QObject>
#include <QPointer>
#include <QStringList>

class QEditor;

class QDocument;
class QDocumentCommand;

class QDataStream;

class QCE_EXPORT QEditSession : public QObject
{
	Q_OBJECT
	
	public:
		QEditSession(QObject *p = 0);
		virtual ~QEditSession();
		
		int autoUpdateInterval() const;
		
		QString fileName() const;
		
	public slots:
		virtual void addEditor(QEditor *e);
		virtual void removeEditor(QEditor *e);
		
		virtual void updateData();
		
		virtual void setAutoUpdateInterval(int ms);
		
		virtual void setFileName(const QString& filename);
		
		virtual void save(QDataStream& s);
		virtual void restore(const QDataStream& s);
		
	protected:
		virtual void saved(QEditor *e);
		virtual void timerEvent(QTimerEvent *e);
		
		virtual QEditor* createEditor();
		
		struct Cursor
		{
			Cursor()
			 : beginLine(-1), beginColumn(-1), endLine(-1), endColumn(-1) {}
			
			Cursor(int line, int column)
			 : beginLine(line), beginColumn(column), endLine(-1), endColumn(-1) {}
			
			Cursor(const Cursor& c)
			 : beginLine(c.beginLine), beginColumn(c.beginColumn), endLine(c.endLine), endColumn(c.endColumn) {}
			
			Cursor(const QDocumentCursor& c);
			
			int beginLine;
			int beginColumn;
			int endLine;
			int endColumn;
		};
		
		struct Command
		{
			enum Type
			{
				Nop,
				Insert,
				Remove
			};
			
			int type;
			Cursor cursor;
			QVariant data;
		};
		
		struct Document
		{
			QString fileName;
			QDateTime timeStamp;
			
			QList<Cursor> cursors;
			QHash<int, QList<int> > marks;
			
			int commandIndex;
			QStack<Command> commands;
		};
		
		int m_id;
		int m_delay;
		QString m_fileName;
		
		QList< QPointer<QEditor*> > m_editors;
		QList<Document*> m_sessionData;
};

#endif // ! _QEDIT_SESSION_H_
