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

#ifndef Header_QCall_Tip
#define Header_QCall_Tip

#include "mostQtHeaders.h"

#include "qce-config.h"

/*!
	\file qcalltip.h
	\brief Definition of the QCallTip class
*/

class QCE_EXPORT QCallTip : public QWidget
{
	public:
		QCallTip(QWidget *p = 0);
		virtual ~QCallTip();
		
		QStringList tips() const;
		void setTips(const QStringList& l);
		
	protected:
		virtual void paintEvent(QPaintEvent *e);
		virtual void keyPressEvent(QKeyEvent *e);
		virtual void focusInEvent(QFocusEvent *e);
		virtual void focusOutEvent(QFocusEvent *e);
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);
		
	private:
		int m_index;
		QStringList m_tips;
		QRect m_up, m_down;
};

#endif
