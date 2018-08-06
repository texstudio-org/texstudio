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

#include "qlinemarksinfocenter.h"

/*!
	\file qlinemarksinfocenter.cpp
	\brief Implementation of QLineMarksInfoCenter
	
	\see QLineMarksInfoCenter
*/

/*!
	\ingroup language
	@{
	
	\class QLineMarksInfoCenter
	\brief A class managing line marks accross all managed editors
	
	QLineMarksInfoCenter provides mean to read/write line marks on managed editors
	but also to serialize and deserialize that data.
*/

#include "qeditor.h"
#include "qcodeedit.h"

#include "qdocument.h"
#include "qdocument_p.h"

#include <QDomDocument>

#define QLINE_MARKS_DUMP_VERSION		1
#define QLINE_MARKS_DUMP_VERSION_MIN	1

QLineMarksInfoCenter* QLineMarksInfoCenter::m_instance = nullptr;

QLineMarksInfoCenter* QLineMarksInfoCenter::instance()
{
	if ( !m_instance )
		m_instance = new QLineMarksInfoCenter;
	
	return m_instance;
}

void QLineMarksInfoCenter::destroy()
{
    delete m_instance;
	
    m_instance = nullptr;
}

QLineMarkTypeList &QLineMarksInfoCenter::markTypes(){
	return m_lineMarkTypes;
}


QLineMarksInfoCenter::QLineMarksInfoCenter()
 : QObject(nullptr)
{
	qRegisterMetaType<QLineMark>("QLineMark");
}

QLineMarksInfoCenter::~QLineMarksInfoCenter()
{
	
}

/*!
	\return the list of line marks set on a given file
*/
QLineMarkList QLineMarksInfoCenter::marks(const QString& file) const
{
	QLineMarkList l;
	bool check = file.count();
	
	foreach ( QLineMarkHandle m, m_lineMarks )
	{
		if ( !check || (m.file == file) )
			l << QLineMark(file, m.line->document()->indexOf(m.line) + 1, m.mark);
	}
	
	return l;
}

/*!
	\brief Remove all line marks on all files
*/
void QLineMarksInfoCenter::clear()
{
	foreach ( QLineMarkHandle m, m_lineMarks )
	{
		removeLineMark(m);
	}
}

/*!
	\brief Remove all line marks on a given file
*/
void QLineMarksInfoCenter::removeMarks(const QString& file)
{
	foreach ( QLineMarkHandle m, m_lineMarks )
		if ( m.file == file )
			removeLineMark(m);
	
}

/*!
	\brief Add a line mark
	
	If the target file is not found the toggling will be delayed.
*/
void QLineMarksInfoCenter::addLineMark(const QLineMark& mark)
{
	QEditor *e = QCodeEdit::managed(mark.file);
	
	if ( !e )
	{
		m_delayed << mark;
		return;
	}
	
	QDocumentLine l = e->document()->line(mark.line - 1);
	
	if ( !l.isValid() )
		return;
	
	e->setCursor(QDocumentCursor(e->document(), mark.line - 1));
	l.addMark(mark.mark);
}

/*!
	\brief Remove a line mark
	
	If the target file is not found the addition will be delayed.
*/
void QLineMarksInfoCenter::toggleLineMark(const QLineMark& mark)
{
	QEditor *e = QCodeEdit::managed(mark.file);
	
	if ( !e )
	{
		m_delayed << mark;
		return;
	}
	
	QDocumentLine l = e->document()->line(mark.line - 1);
	
	if ( !l.isValid() )
		return;
	
	e->setCursor(QDocumentCursor(e->document(), mark.line - 1));
	l.toggleMark(mark.mark);
}

/*!
	\brief Toggle a line mark
	
	If the target file is not found the removal will be delayed.
*/
void QLineMarksInfoCenter::removeLineMark(const QLineMark& mark)
{
	QEditor *e = QCodeEdit::managed(mark.file);
	
	if ( !e )
		return;
	
	QDocumentLine l = e->document()->line(mark.line - 1);
	
	if ( !l.isValid() )
		return;
	
	l.removeMark(mark.mark);
	
	//e->setCursor(QDocumentCursor(l));
}

/*!
	\brief Add a line mark
*/
void QLineMarksInfoCenter::addLineMark(const QLineMarkHandle& mark)
{
	QDocumentLine l(mark.line);
	
	if ( l.isValid() )
		l.addMark(mark.mark);
	
}

/*!
	\brief Toggle a line mark
*/
void QLineMarksInfoCenter::toggleLineMark(const QLineMarkHandle& mark)
{
	QDocumentLine l(mark.line);
	
	if ( l.isValid() )
		l.toggleMark(mark.mark);
	
}

/*!
	\brief Remove a line mark
*/
void QLineMarksInfoCenter::removeLineMark(const QLineMarkHandle& mark)
{
	QDocumentLine l(mark.line);
	
	if ( l.isValid() )
		l.removeMark(mark.mark);
	
}

/*!
	\brief Flush all delayed line marks addition/removal/toggling for a given file
*/
void QLineMarksInfoCenter::flush(const QString& file)
{
	QLineMarkList::iterator i = m_delayed.begin();
	
	while ( i != m_delayed.end() )
	{
		if ( i->file == file )
		{
			addLineMark(*i);
			i = m_delayed.erase(i);
		} else {
			++i;
		}
	}
}

/*!
	\brief Load serialized line marks data from a file
*/
void QLineMarksInfoCenter::loadMarks(const QString& f)
{
	QFile file(f);
	
	if ( !file.open(QFile::ReadOnly) )
		return;
	
	QDataStream stream(&file);
	
	int version;
	
	stream >> version;
	
	if ( version < QLINE_MARKS_DUMP_VERSION_MIN )
	{
		qWarning("QLineMarksInfoCenter : dump file version mismatch");
		return;
	} else if ( version > QLINE_MARKS_DUMP_VERSION ) {
		qWarning("QLineMarksInfoCenter : dump file version mismatch");
		return;
	}
	
	QLineMark mark;
	
	while ( !stream.atEnd() )
	{
		stream >> mark;
		
		addLineMark(mark);
	}
}

/*!
	\brief Write serialized line marks data to a file
*/
void QLineMarksInfoCenter::saveMarks(const QString& f)
{
	QFile file(f);
	
	if ( !file.open(QFile::WriteOnly) )
		return;
	
	QDataStream stream(&file);
	
	stream << QLINE_MARKS_DUMP_VERSION;
	
	foreach ( QLineMarkHandle mark, m_lineMarks )
	{
		stream << mark.line->document()->indexOf(mark.line) + 1;
		stream << mark.file;
		stream << QLineMarksInfoCenter::instance()->markTypeId(mark.mark);
		//stream << mark;
	}
}

QDataStream& operator >> (QDataStream& d, QLineMark& m)
{
	int line;
	QString file, mark;
	
	d >> line;
	d >> file;
	d >> mark;
	
	m.line = line;
	m.file = file;
	m.mark = QLineMarksInfoCenter::instance()->markTypeId(mark);
	
	return d;
}

QDataStream& operator << (QDataStream& d, const QLineMark& m)
{
	int line = m.line;
	QString file = m.file,
			mark = QLineMarksInfoCenter::instance()->markTypeId(m.mark);
	
	d << line;
	d << file;
	d << mark;
	
	return d;
}

/*!
	\brief Load line marks definition from a file
*/
void QLineMarksInfoCenter::loadMarkTypes(const QString& f)
{
	QFile file(f);
	
	if ( !file.open(QFile::ReadOnly | QFile::Text) )
		return;
	
	// TODO : prefer QXmlStreamReader when building against Qt 4.3.0
	
	QDomDocument doc;
	doc.setContent(&file);
	
	QDomNodeList l = doc.documentElement().childNodes();
	
	for ( int i = 0; i < l.count(); i++ )
	{
		QDomElement e = l.at(i).toElement();
		
		if ( e.isNull() || (e.tagName() != "mark") )
			continue;
		
		QLineMarkType t;
		QDomNodeList c = e.childNodes();
		
		//qDebug("mark {");
		
		for ( int j = 0; j < c.count(); j++ )
		{
			QDomElement attr = c.at(j).toElement();
			
			if ( attr.isNull() )
				continue;
			
			const QString field = attr.tagName();
			const QString value = attr.firstChild().toText().data();
			
			//qDebug("\t%s = %s;", qPrintable(field), qPrintable(value));
			
			const bool flag = (value == "true") || value.toUInt();
			
			if ( field == "id" )
			{
				t.id = value;
			} else if ( field == "user" ) {
				t.user = flag;
			} else if ( field == "focus" ) {
				t.focus = flag;
			} else if ( field == "icon" ) {
                t.icon = QIcon(value);
			} else if ( field == "color" ) {
				//t.color = QColor(value);
				
				/*
					color value MUST be a valid value for QColor::setNamedColor()
					with one exception though : an alpha channel indication (unsupported
					by QColor::setNamedColor()) can be prepended using '@' followed by a
					sequence of hex digits (preferabily two of them...)
					
					examples :
						#ff0c80
						#ff0c80@80
						blue
						blue@10
				*/
				
				if ( value.contains('@') )
				{
					t.color = QColor(value.section('@', 0, 0, QString::SectionSkipEmpty));
					t.color.setAlpha(value.section('@', 1, 1, QString::SectionSkipEmpty).toUInt(0, 16));
				} else {
					t.color = QColor(value);
				}
				t.defaultColor = t.color; //remember color, so it can be restored if color is modified
			} else if ( field == "priority" ) {
				t.priority = value.toUInt();
			} else if ( field == "persistency" ) {
				t.persistency = value.toUInt();
			} else if ( field == "rule" ) {
				t.rules << value;
			}
			
		}
		
		m_lineMarkTypes << t;
		
		//qDebug("};");
	}
}

/*!
	\brief int -> string mark type identifier conversion
*/
QString QLineMarksInfoCenter::markTypeId(int id) const
{
	return ((id >= 0) && (id < m_lineMarkTypes.count())) ? m_lineMarkTypes.at(id).id : QString();
}

/*!
	\brief string -> int mark type identifier conversion
*/
int QLineMarksInfoCenter::markTypeId(const QString& id) const
{
	for ( int idx = 0; idx < m_lineMarkTypes.count(); ++idx )
		if ( m_lineMarkTypes.at(idx).id == id )
			return idx;
	
	return -1;
}

/*!
	\return The mark type definition associated with a given id
*/
QLineMarkType QLineMarksInfoCenter::markType(int id) const
{
	return ((id >= 0) && (id < m_lineMarkTypes.count())) ? m_lineMarkTypes.at(id) : QLineMarkType();
}

/*!
	\return the mark type definition associated with a given id
*/
QLineMarkType QLineMarksInfoCenter::markType(const QString& id) const
{
	foreach ( QLineMarkType t, m_lineMarkTypes )
		if ( t.id == id )
			return t;
	
	return QLineMarkType();
}

/*!
	\return A list of available mark types
	\param context context filter (no filtering is performed if empty)
*/
QStringList QLineMarksInfoCenter::availableMarkTypes(const QString& context) const
{
	QStringList l;
	
	foreach ( QLineMarkType t, m_lineMarkTypes )
	{
		if (
				context.count()
			&&
				(
					!t.user
				||
					(
						t.rules.contains("#out")
					&&
						!t.rules.contains(context)
					)
				||
					(
						t.rules.contains("#in")
					&&
						t.rules.contains("!" + context)
					)
				)
			)
		{
			//qDebug("mark[%s] mismatched", qPrintable(t.id));
		} else {
			l << t.id;
		}
	}
	
	return l;
}

int QLineMarksInfoCenter::priority(int id) const{
    return id>=0 &&  id<m_lineMarkTypes.size()?m_lineMarkTypes[id].priority : 0;
}

/*!
	\return the mark that has the highest priority among a list of marks
*/
int QLineMarksInfoCenter::priority(const QList<int>& marks) const
{
	int higher = -1;
	int mark = marks.isEmpty() ? -1 : marks.at(0);
	
	for ( int i = 0; i < m_lineMarkTypes.count(); ++i )
	{
		if ( marks.contains(i) && (m_lineMarkTypes.at(i).priority > higher) )
		{
			mark = i;
			higher = m_lineMarkTypes.at(i).priority;
		}
	}
	
	return mark;
}

/*!
	\return the mark that has the highest priority among a list of marks
*/
QString QLineMarksInfoCenter::priority(const QStringList& marks) const
{
	QString mark;
	int higher = -1;
	
	foreach ( QLineMarkType t, m_lineMarkTypes )
	{
		if ( marks.contains(t.id) && (t.priority > higher) )
		{
			mark = t.id;
			higher = t.priority;
		}
	}
	
	return (mark.count() || !marks.count()) ? mark : marks.at(0);
}

/*!
	\brief Useless for now
*/
QList<QStringList> QLineMarksInfoCenter::marksLayout(const QString& context) const
{
	QList<QStringList> l;
	
	
	foreach ( QString id, availableMarkTypes(context) )
	{
		l << QStringList(id);
	}
	
	/*
	foreach ( QLineMarkType t, availableMarks(context) )
	{
		
	}
	*/
	
	return l;
}

/*!
	\internal
*/
void QLineMarksInfoCenter::cursorMoved(QEditor *e)
{
	foreach ( const QLineMarkHandle& lmh, m_lineMarks )
	{
		QLineMarkType t = markType(lmh.mark);
		
		if (
				(e->fileName() != lmh.file)
			||
				(e->document() != lmh.line->document())
			||
				(t.persistency == 2)
			)
			continue;
		
		if ( !t.persistency || (lmh.line != e->cursor().line().handle()) )
		{
			removeLineMark(lmh);
			cursorMoved(e);
			break;
		}
	}
}

/*!
	\internal
*/
void QLineMarksInfoCenter::lineDeleted(QDocumentLineHandle *h)
{
	QLineMarkHandleList::iterator i = m_lineMarks.begin();
	
	while ( i != m_lineMarks.end() )
	{
		if ( h==i->line )
		{
			QLineMark mrk(i->file, i->line->document()->indexOf(i->line) + 1, i->mark);
			
			i = m_lineMarks.erase(i);
			
			emit lineMarkRemoved(mrk);
		} else {
			++i;
		}
	}
}

/*!
	\brief Entry point for changes in documents
	
	Every document notify through this function a change in its line marks...
*/
void QLineMarksInfoCenter::markChanged(const QString& f, QDocumentLineHandle *line, int mark, bool on)
{
	QLineMarkHandle m(f, line, mark);
	bool in = m_lineMarks.contains(m);
	QLineMark mrk(f, line->document()->indexOf(line) + 1, mark);
	
	if ( !on && in )
	{
		m_lineMarks.removeAll(m);
		
		emit lineMarkRemoved(mrk);
	} else if ( on && !in ) {
		m_lineMarks << m;
		
		emit lineMarkAdded(mrk);
	}
	
	/*
	foreach ( const QLineMarkHandle& h, m_lineMarks )
	{
		qDebug("\t%s:%i [%i]", qPrintable(h.file), h.line->line() + 1, h.mark);
	}
	*/
}

/*! @} */

