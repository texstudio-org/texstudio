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

#include "qcodeedit.h"

#include "qpanel.h"
#include "qeditor.h"
#include "qpanellayout.h"

#include <QDir>
#include <QMenu>
#include <QEvent>
#include <QAction>
#include <QFileInfo>
#include <QStringList>
#include <QMetaObject>

class QPanelWatcher : public QObject
{
	public:
		QPanelWatcher(QCodeEdit *e)
		 : qce(e)
		{
		
		}
		
		bool eventFilter(QObject *o, QEvent *e)
		{
			QPanel *p = qobject_cast<QPanel*>(o);
			QAction *a = qce->toggleViewAction(p);
			
			if ( a )
			{
				bool sig = a->signalsBlocked();
				a->blockSignals(true);
				
				if ( a->isChecked() && e->type() == QEvent::Hide )
					a->setChecked(false);
				else if ( !a->isChecked() && e->type() == QEvent::Show )
					a->setChecked(true);
				
				a->blockSignals(sig);
			}
			
			return QObject::eventFilter(o, e);
		}
		
	private:
		QCodeEdit *qce;
};

QStringList __qce_data_path;

QString QCE::fetchDataFile(const QString& file)
{
	if ( QFileInfo(file).isAbsolute() )
		return file;
	
	foreach ( QString dp, __qce_data_path )
	{
		QDir d(dp);
		
		if ( d.exists(file) )
			return d.absoluteFilePath(file);
	}
	
	return file;
}

QStringList QCE::dataPathes()
{
	return __qce_data_path;
}

void QCE::addDataPath(const QString& path)
{
	if ( !__qce_data_path.contains(path) )
		__qce_data_path << path;
}

QList<QCodeEdit*> QCodeEdit::m_instances;

QCodeEdit::QCodeEdit(QWidget *p)
 : m_panelsMenu(0)
{
	m_editor = new QEditor(p);
	m_watcher = new QPanelWatcher(this);
	m_layout = new QPanelLayout(m_editor);
	
	m_instances << this;
}

QCodeEdit::QCodeEdit(bool actions, QWidget *p)
 : m_panelsMenu(0)
{
	m_editor = new QEditor(actions, p);
	m_watcher = new QPanelWatcher(this);
	m_layout = new QPanelLayout(m_editor);
	
	m_instances << this;
}

QCodeEdit::QCodeEdit(const QString& layout, QWidget *p)
 : m_panelsMenu(0)
{
	m_editor = new QEditor(p);
	m_watcher = new QPanelWatcher(this);
	m_layout = new QPanelLayout(layout, m_editor);
	
	m_instances << this;
}

QCodeEdit::QCodeEdit(const QString& layout, bool actions, QWidget *p)
 : m_panelsMenu(0)
{
	m_editor = new QEditor(actions, p);
	m_watcher = new QPanelWatcher(this);
	m_layout = new QPanelLayout(layout, m_editor);
	
	m_instances << this;
}

QCodeEdit::QCodeEdit(QEditor *e, QPanelLayout *p)
 : m_panelsMenu(0)
{
	m_editor = e;
	m_watcher = new QPanelWatcher(this);
	m_layout = p ? p : new QPanelLayout(m_editor);
	
	m_instances << this;
}

QCodeEdit::QCodeEdit(QEditor *e, const QString& l)
 : m_panelsMenu(0)
{
	m_editor = e;
	m_watcher = new QPanelWatcher(this);
	m_layout = new QPanelLayout(l, m_editor);
	
	m_instances << this;
}

QCodeEdit::~QCodeEdit()
{
	m_instances.removeAll(this);
	
	delete m_watcher;
	delete m_editor;
	delete m_layout;
}

QEditor* QCodeEdit::editor() const
{
	return m_editor;
}

QPanelLayout* QCodeEdit::panelLayout() const
{
	return m_layout;
}

QAction* QCodeEdit::addPanel(QPanel *panel, Position pos, bool _add)
{
	panel->attach(m_editor);
	
	QAction *a = new QAction(panel->type(), m_editor);
	a->setCheckable(true);
	a->setChecked(panel->defaultVisibility());
	
	QObject::connect(a		, SIGNAL( toggled(bool) ),
					panel	, SLOT  ( setVisible(bool) ) );
	
	m_layout->addWidget(panel, QPanelLayout::Position(pos));
	m_layout->update();
	
	m_actions << a;
	
	panel->installEventFilter(m_watcher);
	
	if ( _add )
	{
		if ( !m_panelsMenu )
		{
			m_panelsMenu = new QMenu(QEditor::tr("Panels"), m_editor);
			m_panelsMenu->menuAction()->setObjectName("panels");
			m_editor->addAction(m_panelsMenu->menuAction(), QEditor::tr("&View"), QString());
		}
		
		m_panelsMenu->addAction(a);
	}

	return a;
}

QList<QPanel*> QCodeEdit::panels(const QString& type) const
{
	if ( !m_layout )
		return QList<QPanel*>();
	
	QList<QPanel*> l = m_layout->panels();
	
	if ( type.isEmpty() )
		return l;
	
	int i = 0;
	
	while ( i < l.count() )
	{
		if ( l.at(i)->type() == type )
		{
			++i;
		} else {
			l.removeAt(i);
		}
	}
	
	return l;
}

QAction* QCodeEdit::toggleViewAction(QPanel *p) const
{
	int idx = panels().indexOf(p);
	return idx == -1 ? 0 : m_actions.at(idx);
}

void QCodeEdit::sendPanelCommand(	const QString& type,
									const char *signature,
									const QList<QGenericArgument>& args)
{
	QList<QPanel*> lp = panels();
	
	//qDebug("looking for panel of type %s", qPrintable(type));
	
	foreach ( QPanel *p, lp )
	{
		if ( p && (p->type() == type) )
		{
			//qDebug("found.");
			
			// TODO : ask trolltech to provide an overloaded invokeMetaMethod()
			// taking a QList<> instead of nine defaulted args...
			
			if ( args.isEmpty() )
				QMetaObject::invokeMethod(p, signature);
			else if ( args.count() == 1 )
				QMetaObject::invokeMethod(	p, signature,
												args.at(0));
			else if ( args.count() == 2 )
				QMetaObject::invokeMethod(	p, signature,
												args.at(0),
												args.at(1));
			else if ( args.count() == 3 )
				QMetaObject::invokeMethod(	p, signature,
												args.at(0),
												args.at(1),
												args.at(2));
			else if ( args.count() == 4 )
				QMetaObject::invokeMethod(	p, signature,
												args.at(0),
												args.at(1),
												args.at(2),
												args.at(3));
			else if ( args.count() == 5 )
				QMetaObject::invokeMethod(	p, signature,
												args.at(0),
												args.at(1),
												args.at(2),
												args.at(3),
												args.at(4));
			else if ( args.count() == 6 )
				QMetaObject::invokeMethod(	p, signature,
												args.at(0),
												args.at(1),
												args.at(2),
												args.at(3),
												args.at(4),
												args.at(5));
			else if ( args.count() == 7 )
				QMetaObject::invokeMethod(	p, signature,
												args.at(0),
												args.at(1),
												args.at(2),
												args.at(3),
												args.at(4),
												args.at(5),
												args.at(6));
			else if ( args.count() == 7 )
				QMetaObject::invokeMethod(	p, signature,
												args.at(0),
												args.at(1),
												args.at(2),
												args.at(3),
												args.at(4),
												args.at(5),
												args.at(6));
			else if ( args.count() == 8 )
				QMetaObject::invokeMethod(	p, signature,
												args.at(0),
												args.at(1),
												args.at(2),
												args.at(3),
												args.at(4),
												args.at(5),
												args.at(6),
												args.at(7));
			else if ( args.count() == 9 )
				QMetaObject::invokeMethod(	p, signature,
												args.at(0),
												args.at(1),
												args.at(2),
												args.at(3),
												args.at(4),
												args.at(5),
												args.at(7),
												args.at(8));
			else if ( args.count() == 10 )
				QMetaObject::invokeMethod(	p, signature,
												args.at(0),
												args.at(1),
												args.at(2),
												args.at(3),
												args.at(4),
												args.at(5),
												args.at(7),
												args.at(8),
												args.at(9));
			
		}
	}
}

QCodeEdit* QCodeEdit::manager(QEditor *e)
{
	foreach ( QCodeEdit *m, m_instances )
		if ( m->m_editor == e )
			return m;
	
	return 0;
}

QEditor* QCodeEdit::managed(const QString& f)
{
	foreach ( QCodeEdit *m, m_instances )
		if ( m && m->m_editor && (m->m_editor->fileName() == f) )
			return m->m_editor;
	
	return 0;
}
