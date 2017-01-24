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

#include "mostQtHeaders.h"

#include "qce-config.h"

/*!
	\file qeditsession.h
	\brief Definition of the QEditSession class.
*/

class QEditor;

class QDocument;
class QDocumentCursor;
class QDocumentCommand;

class QDataStream;

class QCE_EXPORT QEditSession : public QObject
{
	Q_OBJECT
	
	public:
		enum SessionFormat
		{
			QCESession0,
			QCESession1,
			
			FormatCount
		};
		
		QEditSession(QObject *p = 0);
		QEditSession(const QString& f, QObject *p = 0);
		virtual ~QEditSession();
		
		int autoUpdateInterval() const;
		
		int format() const;
		
		QString fileName() const;
		
	public slots:
		virtual void addEditor(QEditor *e);
		virtual void removeEditor(QEditor *e);
		
		virtual void updateData();
		
		virtual void setAutoUpdateInterval(int ms);
		
		virtual void setFormat(int fmt);
		
		virtual void setFileName(const QString& filename, bool restore = false);
		
		virtual void clear(bool cleanup = false);
		
		virtual void save();
		virtual void restore();
		
		virtual void save(QDataStream& s);
		virtual void restore(QDataStream& s);
		
	signals:
		void restored(QEditor *e);
		
	protected slots:
		virtual void destroyed(QObject *o);
		
		virtual void saved(QEditor *e, const QString& fn);
		virtual void loaded(QEditor *e, const QString& fn);
		
	protected:
		virtual void timerEvent(QTimerEvent *e);
		
		virtual QEditor* createEditor();
		
	public:
		struct Cursor
		{
			Cursor()
			 : beginLine(-1), beginColumn(-1), endLine(-1), endColumn(-1) {}
			
			Cursor(int line, int column)
			 : beginLine(line), beginColumn(column), endLine(-1), endColumn(-1) {}
			
			Cursor(const Cursor& c)
			 : beginLine(c.beginLine), beginColumn(c.beginColumn), endLine(c.endLine), endColumn(c.endColumn) {}
			
			Cursor(const QDocumentCursor& c);
			
			QDocumentCursor toDocumentCursor(QDocument *d) const;
			
			int beginLine;
			int beginColumn;
			int endLine;
			int endColumn;
		};
		
		struct Document
		{
			quint8 flags;
			QString fileName;
			QDateTime timeStamp;
			
			int scrollX, scrollY;
			
			QList<Cursor> cursors;
			QHash<int, QList<int> > marks;
		};
		
	protected:
		virtual void update(QEditor *e, Document *d);
		
		int m_id;
		int m_delay;
		int m_format;
		QString m_fileName;
		
		QList<QEditor*> m_editors;
		QList<Document*> m_sessionData;
};

#endif // ! _QEDIT_SESSION_H_
