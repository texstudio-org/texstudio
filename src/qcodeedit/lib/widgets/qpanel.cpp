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

#include "qpanel.h"

/*!
	\file qpanel.cpp
	\brief Implementation of the QPanel class
	
	\see QPanel
*/

#include "qeditor.h"
#include "qcodeedit.h"
#include "qpanellayout.h"

/*!
	\ingroup widgets
	@{
	
	\class QPanel
	\brief Helper class for panels displayed by QCodeEdit
	
*/

QHash<QString, QPanelCreator*>& QPanel::creators()
{
	static QHash<QString, QPanelCreator*> _c;
	return _c;
}

QPanel* QPanel::panel(const QString& id, QWidget *p)
{
	if ( !creators().contains(id) )
        return nullptr;
	
	return creators().value(id)->panel(p);
}

void QPanel::registerCreator(QPanelCreator *c)
{
	creators()[c->id()] = c;
}

static int _panels = 0;

/*!
	\brief Constructor
	
	If the parent is a text editor, it is automatically connected to the panel
*/
QPanel::QPanel(QWidget *p)
 : QWidget(p), m_defaultVisibility(true), m_shownOnce(false)
{
	setAutoFillBackground(true);
	QEditor *e = qobject_cast<QEditor*>(p);
	
	if ( e )
		attach(e);
	
	++_panels;
}

/*!
	\brief Destructor
*/
QPanel::~QPanel()
{
	--_panels;
	
	//if ( !_panels )
	//	qDebug("Panels cleared.");
	
}

/*!
*/
QEditor* QPanel::editor()
{
	return m_editor;
}

/*!
	\brief Connect the panel to a text editor
*/
void QPanel::attach(QEditor *e)
{
	if ( m_editor )
	{
		disconnect(	m_editor->document(),
					SIGNAL( formatsChanged() ),
					this,
					SLOT  ( update() ) );
		
		disconnect(	m_editor->document(),
					SIGNAL( contentsChanged() ),
					this,
					SLOT  ( update() ) );
		
		disconnect(	m_editor->verticalScrollBar(),
					SIGNAL( valueChanged(int) ),
					this,
					SLOT  ( update() ) );
		
	}
	
	editorChange(e);
	
	m_editor = e;
	setParent(e);
	
	if ( m_editor )
	{
		connect(m_editor->document(),
				SIGNAL( formatsChanged() ),
				this,
				SLOT  ( update() ) );
		
		connect(m_editor->document(),
				SIGNAL( contentsChanged() ),
				this,
				SLOT  ( update() ) );
		
		connect(m_editor->verticalScrollBar(),
				SIGNAL( valueChanged(int) ),
				this,
				SLOT  ( update() ) );
		
	}
}

/*!
	\brief 
*/
bool QPanel::shallShow() const
{
	return m_shownOnce ? isHidden() : m_defaultVisibility;
}

/*!
	\brief 
*/
bool QPanel::defaultVisibility() const
{
	return m_defaultVisibility;
}

/*!
	\brief 
*/
void QPanel::setDefaultVisibility(bool on)
{
	m_defaultVisibility = on;
}

/*!
	\brief Callback
	
	Each time attach() is called, this function is called as well so that
	the panel can fine tune its behaviour according to the editor monitored.
	
	\note the Default implementation does nothing...
*/
void QPanel::editorChange(QEditor *)
{
	
}

bool QPanel::forward(QMouseEvent *e)
{
	QPoint pos, globalPos = e->globalPos(), ref = editor()->viewport()->pos();
	
	if ( editor()->viewport()->parentWidget() )
		ref = editor()->viewport()->parentWidget()->mapToGlobal(ref);
	
	globalPos.setX(qBound(ref.x(), globalPos.x(), ref.x() + editor()->width()));
	globalPos.setY(qBound(ref.y(), globalPos.y(), ref.y() + editor()->height()));
	
	pos = editor()->viewport()->mapFromGlobal(globalPos);
	
	QMouseEvent fw(
					e->type(),
					pos,
					globalPos,
					e->button(),
					e->buttons(),
					e->modifiers()
				);
	
	bool ok = qApp->sendEvent(editor()->viewport(), &fw) && fw.isAccepted();
	
	//qDebug("forwarding mouse event : (%i, %i) => %i", pos.x(), pos.y(), ok);
	
	return ok;
}

/*!
	\internal
*/
void QPanel::mouseMoveEvent(QMouseEvent *e)
{
	if ( !editor() )
		return;
	
	if ( forward(e) )
		e->accept();
	else
		QWidget::mouseMoveEvent(e);
}

/*!
	\internal
*/
void QPanel::mousePressEvent(QMouseEvent *e)
{
	if ( !editor() )
		return;
	
	if ( forward(e) )
		e->accept();
	else
		QWidget::mousePressEvent(e);
}

/*!
	\internal
*/
void QPanel::mouseReleaseEvent(QMouseEvent *e)
{
	if ( !editor() )
		return;
	
	if ( forward(e) )
		e->accept();
	else
        QWidget::mouseReleaseEvent(e);
}

void QPanel::wheelEvent(QWheelEvent *e)
{
    if( !editor()) return;
    m_editor->wheelEvent(e);
}

/*!
	\internal
*/
void QPanel::showEvent(QShowEvent *e)
{
	m_shownOnce = true;
	
	QWidget::showEvent(e);
}

/*!
	\internal
*/
void QPanel::hideEvent(QHideEvent *e)
{
	QCodeEdit *ce = QCodeEdit::manager(editor());
	
	if ( ce )
		ce->panelLayout()->update();
	
	QWidget::hideEvent(e);
}

/*!
	\internal
*/
void QPanel::paintEvent(QPaintEvent *e)
{
	if ( !m_editor || !m_editor->document() )
	{
		e->ignore();
		return;
	}
	
	e->accept();
	
	QPainter p(this);
	
	if ( !paint(&p, m_editor) )
		QWidget::paintEvent(e);
}

/*!
	\internal
*/
bool QPanel::paint(QPainter *, QEditor *)
{
	/*
	qWarning("Bad panel implementation : "
			"QPanel::paint(QPainter*, QEditor*)"
			" is a stub that should not get called."
			"\nCheck out the code of %s", qPrintable(type()));
	*/
	return false;
}

/* @} */
