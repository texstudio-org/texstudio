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

#include "qstatuspanel.h"

/*!
	\file qstatuspanel.cpp
	\brief Implementation of the QStatusPanel class.

	\see QStatusPanel
*/

#include "qeditor.h"

#include "qdocument.h"
#include "qdocumentline.h"
#include "qdocumentcursor.h"

/*!
	\ingroup widgets
	@{
*/

/*!
	\class QStatusPanel
	\brief A panel that display some status informations
*/

QCE_AUTO_REGISTER(QStatusPanel)

/*!
	\brief Constructor
*/
QStatusPanel::QStatusPanel(QWidget *p)
 : QPanel(p)
{
	setFixedHeight(fontMetrics().lineSpacing() + 4);
}

/*!
	\brief Empty destructor
*/
QStatusPanel::~QStatusPanel()
{

}

/*!

*/
QString QStatusPanel::type() const
{
	return "Status";
}

/*!

*/
void QStatusPanel::editorChange(QEditor *e)
{
	if ( editor() )
	{
		disconnect(	editor(), SIGNAL( cursorPositionChanged() ),
					this	, SLOT  ( update() ) );

	}

	if ( e )
	{
		connect(e	, SIGNAL( cursorPositionChanged() ),
				this, SLOT  ( update() ) );

	}
}

/*!

*/
bool QStatusPanel::paint(QPainter *p, QEditor *e)
{
	//qDebug("drawing status panel... [%i, %i, %i, %i]",
	//		geometry().x(),
	//		geometry().y(),
	//		geometry().width(),
	//		geometry().height());
	static QPixmap _warn(":/warning.png"), _mod(":/save.png");

	QString s;
	int xpos = 10;
	QDocumentCursor c = e->cursor();
	const QFontMetrics fm(fontMetrics());

	const int ls = fm.lineSpacing();
	const int ascent = fm.ascent() + 3;

	s = tr("Line : %1 Visual column : %2 Text column : %3")
			.arg(c.lineNumber() + 1)
			.arg(c.visualColumnNumber())
			.arg(c.columnNumber());

	p->drawText(xpos, ascent, s);
	xpos += fm.width(s) + 10;

	int sz = qMin(height(), _mod.height());
	QString timeDiff;
	if(e->displayModifyTime() && e->document()){
		int lastMod = e->document()->lastModified().secsTo(QDateTime::currentDateTime());
		timeDiff = tr("(%1 min %2 s ago)").arg(lastMod / 60).arg(lastMod % 60);
	}

	xpos += 10;
	if ( e->isContentModified() )
	{
		p->drawPixmap(xpos, (height() - sz) / 2, sz, sz, _mod);
		xpos += sz;
		xpos += 10;
                if(e->displayModifyTime()) p->drawText(xpos, ascent, timeDiff);
	} else {
		xpos += sz + 10;
	}
	xpos += fm.width(timeDiff);
	xpos += 20;
	
	s = editor()->flag(QEditor::Overwrite) ? tr("OVERWRITE") : tr("INSERT");
	p->drawText(xpos, ascent, s);
	xpos += fm.width(s) + 10;

	m_conflictSpot = 0;

	if ( editor()->isInConflict() )
	{
		s =  tr("Conflict");
		int w = fm.width(s) + 30;

		if ( xpos + w + _warn.width() < width() )
		{
			m_conflictSpot = width() - (w + _warn.width());
			p->drawText(width() - w + 15, ascent, s);
			p->drawPixmap(m_conflictSpot, (ls - _warn.height()) / 2 + 2, _warn);
		} else if ( xpos + _warn.width() < width() ) {
			m_conflictSpot = width() - _warn.width();
			p->drawPixmap(m_conflictSpot, (ls - _warn.height()) / 2 + 2, _warn);
		}
	}

	setFixedHeight(ls + 4);
	
	QTimer::singleShot(1000, this, SLOT( update() ) );
	
	return true;
}

/*!

*/
void QStatusPanel::mousePressEvent(QMouseEvent *e)
{
	if ( !editor() || (e->button() != Qt::LeftButton) || !m_conflictSpot || e->x() < m_conflictSpot )
	{
		editor()->setFocus();
		return;
	}

	editor()->save();
}

/*!

*/
void QStatusPanel::mouseReleaseEvent(QMouseEvent *e)
{
	Q_UNUSED(e)
	
	editor()->setFocus();
}

/*! @} */
