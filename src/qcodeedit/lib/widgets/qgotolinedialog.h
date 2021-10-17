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

#ifndef Header_QGoto_Line_Dialog
#define Header_QGoto_Line_Dialog

#include "mostQtHeaders.h"

#include "qce-config.h"

/*!
	\file qgotodialog.h
	\brief Definition of the QGotoLineDialog class
	
	\see QGotoLineDialog
*/

#include "ui_gotolinedialog.h"

class QEditor;

class QCE_EXPORT QGotoLineDialog : public QDialog, private Ui::GotoDialog
{
	Q_OBJECT
	
	public:
		QGotoLineDialog(QWidget *w = 0);
		
	public slots:
		void exec(QEditor *e);
};

#endif // _QGOTO_LINE__DIALOG_H_
