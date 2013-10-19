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

#include "qsimplecolorpicker.h"

/*!
	\file qsimplecolorpicker.cpp
	\brief Implementation of the QSimpleColorPicker class
*/

QSimpleColorPicker::QSimpleColorPicker(QWidget *w)
 : QToolButton(w)
{
	setColor(QColor());
	
	connect(this, SIGNAL( clicked() ), this, SLOT( clicked() ) );
}

QSimpleColorPicker::QSimpleColorPicker(const QColor& c, QWidget *w)
 : QToolButton(w)
{
	setColor(c);
	
	connect(this, SIGNAL( clicked() ), this, SLOT( clicked() ) );
}

const QColor& QSimpleColorPicker::color() const
{
	return m_color;
}

void QSimpleColorPicker::setColor(const QColor& c)
{
	m_color = c;
	
	updateIcon(size());
}

void QSimpleColorPicker::resizeEvent(QResizeEvent *e)
{
	updateIcon(e->size());
	
	QToolButton::resizeEvent(e);
}

void QSimpleColorPicker::contextMenuEvent(QContextMenuEvent *e)
{
	setColor(QColor());
	
	e->accept();
	
	QToolButton::contextMenuEvent(e);
}

void QSimpleColorPicker::updateIcon(const QSize& sz)
{
	QPixmap px(sz.width() - 3, sz.height() - 3);
	QPainter p(&px);
	
	if ( m_color.isValid() )
	{
		p.fillRect(0, 0, px.width(), px.height(), m_color);
		setIcon(QIcon(px));
	} else {
		//p.fillRect(0, 0, px.width(), px.height(), palette().window());
		setIcon(QIcon());
	}
}

void QSimpleColorPicker::clicked()
{
	QColor c = QColorDialog::getColor(m_color);
	
	if ( c.isValid() )
	{
		setColor(c);
	}
}
