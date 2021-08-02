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

#include "qlinechangepanel.h"

/*!
	\file qlinechangepanel.cpp
	\brief Implementation of the QLineChangePanel class.
*/

#include "qeditor.h"

#include "qdocument.h"
#include "qdocumentline.h"

/*!
	\ingroup widgets
	@{
*/

/*!
	\class QLineMarkPanel
	\brief A specific panel in charge of drawing line numbers of an editor

	\see QEditorInterface
*/

QCE_AUTO_REGISTER(QLineChangePanel)

/*!
	\brief Constructor
*/
QLineChangePanel::QLineChangePanel(QWidget *p)
 : QPanel(p)
{
	setFixedWidth(4);
	setObjectName("lineChangePanel");
}

/*!
	\brief Empty destructor
*/
QLineChangePanel::~QLineChangePanel()
{

}

/*!

*/
QString QLineChangePanel::type() const
{
	return "Line changes";
}

/*!
	\internal
*/
bool QLineChangePanel::paint(QPainter *p, QEditor *e)
{
	if ( !e || !e->document() )
		return true;

    int n;
    qreal posY,
        as = QFontMetricsF(e->document()->font()).ascent(),
		ls = e->document()->getLineSpacing(),
		pageBottom = e->viewport()->height(),
		contentsY = e->verticalOffset();

	QDocument *d = e->document();
	n = d->lineNumber(contentsY);
    posY = d->y(n) - contentsY;

	for ( ; ; ++n )
	{
		//qDebug("n = %i; pos = %i", n, posY);
		QDocumentLine line = d->line(n);

		if ( line.isNull() || ((posY - as) > pageBottom) )
			break;

		if ( line.isHidden() )
			continue;

		int span = line.lineSpan();

		if ( d->isLineModified(line) )
		{
            p->fillRect(QRectF(1, posY, 2, ls * span), QColor(255, 216, 0)); // yellow
		} else if ( d->hasLineEverBeenModified(line) ) {
            p->fillRect(QRectF(1, posY, 2, ls * span), QColor(70, 191, 0)); // green
		}

		posY += ls * span;
	}
	
	return true;
}

/*! @} */
