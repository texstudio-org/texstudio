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

#ifndef Header_QLine_Change_Panel
#define Header_QLine_Change_Panel

#include "mostQtHeaders.h"

/*!
	\file qlinechangepanel.h
	\brief Definition of the QLineChangePanel class.
	
	\see QLineChangePanel
*/

#include "qpanel.h"

class QDocumentLine;

class QCE_EXPORT QLineChangePanel : public QPanel
{
	Q_OBJECT
	
	public:
		Q_Panel(QLineChangePanel, "Line Change Panel")
		
		QLineChangePanel(QWidget *p = 0);
		virtual ~QLineChangePanel();
		
		virtual QString type() const;
		
	protected:
		virtual bool paint(QPainter *p, QEditor *e);
		
	private:
		
};

#endif // _QLINE_CHANGE_PANEL_H_

