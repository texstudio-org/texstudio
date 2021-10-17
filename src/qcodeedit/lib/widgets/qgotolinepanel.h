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

#ifndef Header_QGoto_Line_Panel
#define Header_QGoto_Line_Panel

#include "mostQtHeaders.h"

#include "qpanel.h"

/*!
	\file qgotolinepanel.h
	\brief Definition of the QGotoLinePanel class.
	
	\see QGotoLinePanel
*/

#include "ui_gotoline.h"

class QCE_EXPORT QGotoLinePanel : public QPanel, private Ui::GotoLine
{
	Q_OBJECT
	
	public:
		Q_Panel(QGotoLinePanel, "Goto Line Panel")
		
		QGotoLinePanel(QWidget *p = 0);
		virtual ~QGotoLinePanel();
		
		virtual QString type() const;
		
	public slots:
		
		
	protected:
		virtual bool forward(QMouseEvent *e);
		virtual void editorChange(QEditor *e);
		virtual void showEvent(QShowEvent *e);
		virtual void keyPressEvent(QKeyEvent *e);
		
	private slots:
		void on_bClose_clicked();
		
		void on_bGo_clicked();
		
		void on_spLine_valueChanged(int v);
		void on_slLine_valueChanged(int v);
		
		void lineCountChanged(int n);
		void cursorPositionChanged();
};

#endif // _QGOTO_LINE_PANEL_H_
