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

#ifndef Header_QSimple_ColorPicker
#define Header_QSimple_ColorPicker

#include "mostQtHeaders.h"

#include "qce-config.h"

/*!
	\file qsimplecolorpicker.h
	\brief Definition of the QSimpleColorPicker class
*/

#include <QToolButton>

class QCE_EXPORT QSimpleColorPicker : public QToolButton
{
	Q_OBJECT
	
	Q_PROPERTY(QColor color READ color WRITE setColor)
	
	public:
		QSimpleColorPicker(QWidget *w = 0);
		QSimpleColorPicker(const QColor& c, QWidget *w = 0);
		
		const QColor& color() const;
		
	protected:
		void resizeEvent(QResizeEvent *e);
		void contextMenuEvent(QContextMenuEvent *e);
		
	public slots:
		void setColor(const QColor& c);
		
		void updateIcon(const QSize& sz);
		
	private slots:
		void clicked();
		
	private:
		QColor m_color;
};

#endif
