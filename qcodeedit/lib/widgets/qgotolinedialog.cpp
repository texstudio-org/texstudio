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

#include "qgotolinedialog.h"

/*!
	\file qgotolinedialog.cpp
	\brief Implementation of the QGotoDialog class.
	
	\see QGotoDialog
*/

#include "qeditor.h"

#include "qdocument.h"
#include "qdocumentline.h"
#include "qdocumentcursor.h"

/*!
	\ingroup dialogs
	@{
	
	\class QGotoLineDialog
	\brief A Kate-like generic goto line dialog.
	
*/

QGotoLineDialog::QGotoLineDialog(QWidget *w)
 : QDialog(w)
{
	setupUi(this);
}

void QGotoLineDialog::exec(QEditor *e)
{
	if ( !e )
		return;
	
	int ln = e->cursor().lineNumber() + 1,
		max = e->document()->lines();
	
	spinLine->setValue(ln);
	spinLine->setMaximum(max);
	
	slideLine->setValue(ln);
	slideLine->setMaximum(max);
	
	spinLine->selectAll();
	
	if ( QDialog::exec() != QDialog::Accepted )
		return;
	
	QDocumentCursor c(e->document(), spinLine->value() - 1);
	
	if ( c.isNull() )
		return;
	
	//qDebug("going to line : %i [%i]", c.lineNumber(), spinLine->value());
	
	e->setCursor(c);
}

/*! @} */

