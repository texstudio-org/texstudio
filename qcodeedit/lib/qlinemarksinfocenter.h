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

#ifndef _QLINE_MARKS_INFO_CENTER_H_
#define _QLINE_MARKS_INFO_CENTER_H_

/*!
	\file qlinemarksinfocenter.h
	\brief Definition of the QLineMarksInfoCenter class.
	
	\see QLineMarksInfoCenter
*/

/*!
	\defgroup language Language framework
*/

#include "qce-config.h"

#include <QColor>
#include <QPixmap>
#include <QObject>
#include <QMetaType>
#include <QStringList>

class QEditor;
class QDataStream;
class QDocumentLineHandle;

struct QLineMark
{
	inline QLineMark() : line(-1) {}
	
	inline QLineMark(const QString& f, int l, int m)
	 : mark(m), line(l), file(f)
	{}
	
	inline bool operator == (const QLineMark& m)
	{ return (line == m.line) && (file == m.file) && (mark == m.mark); }
	
	inline bool operator != (const QLineMark& m)
	{ return (line != m.line) || (file != m.file) || (mark != m.mark); }
	
	int mark;
	int line;
	QString file;
};

Q_DECLARE_METATYPE(QLineMark)

typedef QList<QLineMark> QLineMarkList;

Q_DECLARE_TYPEINFO(QLineMark, Q_MOVABLE_TYPE);

struct QLineMarkHandle
{
	inline QLineMarkHandle() : line(0) {}
	
	inline QLineMarkHandle(const QString& f, QDocumentLineHandle *l, int m)
	 : mark(m), line(l), file(f)
	{}
	
	inline bool operator == (const QLineMarkHandle& m)
	{ return (line == m.line) && (file == m.file) && (mark == m.mark); }
	
	inline bool operator != (const QLineMarkHandle& m)
	{ return (line != m.line) || (file != m.file) || (mark != m.mark); }
	
	int mark;
	QDocumentLineHandle *line;
	QString file;
};

Q_DECLARE_METATYPE(QLineMarkHandle)

typedef QList<QLineMarkHandle> QLineMarkHandleList;

Q_DECLARE_TYPEINFO(QLineMarkHandle, Q_MOVABLE_TYPE);

QCE_EXPORT QDataStream& operator >> (QDataStream& d, QLineMark& m);
QCE_EXPORT QDataStream& operator << (QDataStream& d, const QLineMark& m);

struct QLineMarkType
{
	inline QLineMarkType()
	 : user(false), focus(false), priority(-1), persistency(0)
	{}
	
	bool user;
	bool focus;
	QString id;
	QPixmap icon;
	QColor color;
	int priority;
	int persistency;
	QStringList rules;
};

Q_DECLARE_METATYPE(QLineMarkType)

typedef QList<QLineMarkType> QLineMarkTypeList;

Q_DECLARE_TYPEINFO(QLineMarkType, Q_MOVABLE_TYPE);

class QCE_EXPORT QLineMarksInfoCenter : public QObject
{
	friend class QEditor;
	friend class QCodeEdit;
	
	Q_OBJECT
	
	public:
		static QLineMarksInfoCenter* instance();
		static void destroy();
		
		QLineMarkList marks(const QString& file = QString());
		
		QString markTypeId(int id);
		int markTypeId(const QString& id);
		
		QLineMarkType markType(int id);
		QLineMarkType markType(const QString& id);
		
		int priority(const QList<int>& marks);
		QString priority(const QStringList& marks);
		
		QStringList availableMarkTypes(const QString& context = QString());
		QList<QStringList> marksLayout(const QString& context = QString());
		
	public slots:
		void loadMarks(const QString& f);
		void saveMarks(const QString& f);
		
		void loadMarkTypes(const QString& f);
		
		void clear();
		
		void removeMarks(const QString& file);
		
		void addLineMark(const QLineMark& mark);
		void toggleLineMark(const QLineMark& mark);
		void removeLineMark(const QLineMark& mark);
		
		void addLineMark(const QLineMarkHandle& mark);
		void toggleLineMark(const QLineMarkHandle& mark);
		void removeLineMark(const QLineMarkHandle& mark);
		
		void flush(const QString& file);
		
	signals:
		void lineMarkAdded(const QLineMark& mark);
		void lineMarkRemoved(const QLineMark& mark);
		
	protected:
		QLineMarksInfoCenter();
		virtual ~QLineMarksInfoCenter();
		
	protected slots:
		void cursorMoved(QEditor *e);
		void lineDeleted(QDocumentLineHandle *h);
		void markChanged(const QString& f, QDocumentLineHandle *h, int mark, bool on);
		
	private:
		QLineMarkList m_delayed;
		QLineMarkHandleList m_lineMarks;
		QLineMarkTypeList m_lineMarkTypes;
		
		static QLineMarksInfoCenter *m_instance;
};

#endif // !_QLINE_MARKS_INFO_CENTER_H_
