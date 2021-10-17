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

#ifndef Header_QStatus_Panel
#define Header_QStatus_Panel

#include "mostQtHeaders.h"

#include "qpanel.h"

/*!
	\file qstatuspanel.h
	\brief Definition of the QStatusPanel class.
	
	\see QStatusPanel
*/

class QLabel;

class QDocumentLine;

class QCE_EXPORT QStatusPanel : public QPanel
{
	Q_OBJECT
	
	public:
		Q_Panel(QStatusPanel, "Status Panel")
		
        QStatusPanel(QWidget *p = nullptr);
		virtual ~QStatusPanel();
		
		virtual QString type() const;
		
	protected:
		virtual void editorChange(QEditor *e);
		virtual bool paint(QPainter *p, QEditor *e);
		
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);
		
	private:
		int m_conflictSpot;
		QTimer *timer;
};

#endif // _QSTATUS_PANEL_H_
