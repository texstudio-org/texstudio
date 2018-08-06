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

#include "qcodeedit.h"

/*!
	\file qcodeedit.cpp
	\brief Implementation of the QCodeEdit class
*/

#include "qpanel.h"
#include "qeditor.h"
#include "qpanellayout.h"
#include "qmetautils.h"

/*!
	\class QCodeEdit
	\brief A thin layer over QEditor
	
	The QCodeEdit class provides simple means to associate panels with editors and manage them.
*/

/*!
	\internal
	\class QPanelWatcher
	
	A class designed to work around some limitations of the hide/show event system and allow
	proper setting and conservation of default visibility for panels.
*/
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

/*!
	\brief Centralized access point to data fetching
*/
QString QCE::fetchDataFile(const QString& file)
{
	if ( QFileInfo(file).isAbsolute() )
		return file;
	
	foreach ( const QString& dp, __qce_data_path )
	{
		QDir d(dp);
		
		if ( d.exists(file) )
			return d.absoluteFilePath(file);
	}
	
	return file;
}

/*!
	\return The list of pathes used by QCE to fetch data
*/
QStringList QCE::dataPathes()
{
	return __qce_data_path;
}

/*!
	\brief Add a path to the list of pathes used to fetch data
*/
void QCE::addDataPath(const QString& path)
{
	if ( !__qce_data_path.contains(path) )
		__qce_data_path << path;
}

QList<QCodeEdit*> QCodeEdit::m_instances;

/*!
	\brief ctor
	
	The created editor object comes with builtin actions.
*/
QCodeEdit::QCodeEdit(QWidget *p)
 : m_panelsMenu(nullptr)
{
	m_editor = new QEditor(p);
	m_watcher = new QPanelWatcher(this);
	m_layout = new QPanelLayout(m_editor);
	
	m_instances << this;
}

/*!
	\brief ctor
	\param actions whether the QEditor object should create builtin actions
*/
QCodeEdit::QCodeEdit(bool actions, QWidget *p, QDocument *doc)
 : m_panelsMenu(nullptr)
{
	m_editor = new QEditor(actions, p,doc);
	m_watcher = new QPanelWatcher(this);
	m_layout = new QPanelLayout(m_editor);
	
	m_instances << this;
}

/*!
	\brief ctor
	\param layout structure of the panel layout
	
	The created editor object comes with builtin actions.
*/
QCodeEdit::QCodeEdit(const QString& layout, QWidget *p)
 : m_panelsMenu(nullptr)
{
	m_editor = new QEditor(p);
	m_watcher = new QPanelWatcher(this);
	m_layout = new QPanelLayout(layout, m_editor);
	
	m_instances << this;
}

/*!
	\brief ctor
	\param layout structure of the panel layout
	\param actions whether the QEditor object should create builtin actions
*/
QCodeEdit::QCodeEdit(const QString& layout, bool actions, QWidget *p)
 : m_panelsMenu(nullptr)
{
	m_editor = new QEditor(actions, p);
	m_watcher = new QPanelWatcher(this);
	m_layout = new QPanelLayout(layout, m_editor);
	
	m_instances << this;
}

/*!
	\brief ctor
	\param e editor to manage
	\param p panel layout to associate with the editor
*/
QCodeEdit::QCodeEdit(QEditor *e, QPanelLayout *p)
 : m_panelsMenu(nullptr)
{
	m_editor = e;
	m_watcher = new QPanelWatcher(this);
	m_layout = p ? p : new QPanelLayout(m_editor);
	
	m_instances << this;
}

/*!
	\brief ctor
	\param e editor to manage
	\param l structure of the panel layout
*/
QCodeEdit::QCodeEdit(QEditor *e, const QString& l)
 : m_panelsMenu(nullptr)
{
	m_editor = e;
	m_watcher = new QPanelWatcher(this);
	m_layout = new QPanelLayout(l, m_editor);
	
	m_instances << this;
}

/*!
	\brief dtor
	
	\warning Destroyes the editor and the panel layout it manages
*/
QCodeEdit::~QCodeEdit()
{
	m_instances.removeAll(this);
	
	delete m_watcher;
	delete m_editor;
	delete m_layout;
}

/*!
	\return the managed editor
*/
QEditor* QCodeEdit::editor() const
{
	return m_editor;
}

/*!
	\return the panel layout associated with the managed editor
*/
QPanelLayout* QCodeEdit::panelLayout() const
{
	return m_layout;
}

/*!
	\brief Add a panel
	\return Toggle view action for the added panel
	\param panel panel to add
	\param pos position of the panel in the layout
	\param _add whether to add the show action of the panel to the menu of the editor
*/
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

/*!
	\overload
	\return Toggle view action for the added panel
	\param name name of panel to add
	\param pos position of the panel in the layout
	\param _add whether to add the show action of the panel to the menu of the editor
*/
QAction* QCodeEdit::addPanel(const QString& name, Position pos, bool _add)
{
	return addPanel(QPanel::panel(name, m_editor), pos, _add);
}

/*!
	\return whether the editor has a panel of the given \a type
*/
bool QCodeEdit::hasPanel(const QString& type) const
{
	if ( !m_layout )
		return false;
	
	QList<QPanel*> l = m_layout->panels();
	
	foreach ( QPanel *p, l )
		if ( p->type() == type )
			return true;
	
	return false;
}

/*!
	\return a list of panels added to the editor
	\param type Type of panel to look for (no filtering is performed if empty)
*/
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

/*!
	\return the toggle view action of a given panel
*/
QAction* QCodeEdit::toggleViewAction(QPanel *p) const
{
	int idx = panels().indexOf(p);
	return idx == -1 ? 0 : m_actions.at(idx);
}

/*!
	\brief Send a command to every panel of a given type
	\param signature method name suitable for QMetaObject::invokeMethod()
	\param args list of arguments suitable for QMetaObject::invokeMethod()
	
	Example use :
	\code
	sendPanelCommand("Status", "setVisible" Q_COMMAND << Q_ARG(bool, false));
	\endcode
*/
void QCodeEdit::sendPanelCommand(	const QString& type,
									const char *signature,
									const QList<QGenericArgument>& args)
{
	QList<QPanel*> lp = panels();
	
	//qDebug("looking for panel of type %s", qPrintable(type));
	
	foreach ( QPanel *p, lp )
	{
		if ( p && (p->type() == type) )
			QMetaObjectInvokeMethod(p, signature, args);
	}
}

void QCodeEdit::sendPanelCommand(	const QString& type,
						const char *signature,
						const QList<QVariant>& args){

	QList<QPanel*> lp = panels();

	//qDebug("looking for panel of type %s", qPrintable(type));

	foreach ( QPanel *p, lp )
	{
		if ( p && (p->type() == type) )
			QMetaObjectInvokeMethod(p, signature, args);
	}
}


/*!
	\return The QCodeEdit object managing a given editor or a null point if the given editor is unmanaged
*/
QCodeEdit* QCodeEdit::manager(QEditor *e)
{
	foreach ( QCodeEdit *m, m_instances )
		if ( m->m_editor == e )
			return m;
	
    return nullptr;
}

/*!
	\brief The (first) managed editor editing a given file or a null pointer if none found
*/
QEditor* QCodeEdit::managed(const QString& f)
{
	foreach ( QCodeEdit *m, m_instances )
		if ( m && m->m_editor && (m->m_editor->fileName() == f) )
			return m->m_editor;
	
    return nullptr;
}

