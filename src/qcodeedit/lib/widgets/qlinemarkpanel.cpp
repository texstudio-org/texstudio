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

#include "qlinemarkpanel.h"

/*!
	\file qlinemarkpanel.cpp
	\brief Implementation of the QLineMarkPanel class.
*/

#include "qeditor.h"

#include "qdocument.h"
#include "qdocumentline.h"

#include "qlanguagedefinition.h"
#include "qlinemarksinfocenter.h"

/*!
	\ingroup widgets
	@{
*/

/*!
	\class QLineMarkPanel
	\brief A specific panel in charge of drawing line marks of an editor
*/

QCE_AUTO_REGISTER(QLineMarkPanel)

/*!
	\brief Constructor
*/
QLineMarkPanel::QLineMarkPanel(QWidget *p)
 : QPanel(p)
{
	setObjectName("lineMarkPanel");
	minMarksPerLine=1;
	maxMarksPerLine=1;
	setFixedWidth(minMarksPerLine*16+2);
}

/*!
	\brief Empty destructor
*/
QLineMarkPanel::~QLineMarkPanel()
{

}

/*!

*/
QString QLineMarkPanel::type() const
{
	return "Line marks";
}

void QLineMarkPanel::setToolTipForTouchedMark(QString text){
    markToolTip=text;
}

/*!
	\internal
*/
bool QLineMarkPanel::event(QEvent *e) {
     if (e->type() == QEvent::ToolTip) {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(e);
        int linen=editor()->document()->lineNumber(editor()->verticalOffset()+helpEvent->y());
        markToolTip="";
        if (linen>-1 && linen<editor()->document()->lines()) {
            QDocumentLine line = editor()->document()->line(linen);
			QList<int> lm = line.marks();
			int count = 1;
			int bestMark = -1;
			QLineMarksInfoCenter *mic = QLineMarksInfoCenter::instance();
			foreach ( int id, lm )
			{
			    if (mic->markType(id).icon.isNull())
                    continue;
                if (helpEvent->x()>count && helpEvent->x()<count+16)
                    bestMark = id; //no break do to overdraw
				if (count < 16*(maxMarksPerLine-1)) {
                    count += 16;
                    if (bestMark!=-1) break;
				}
			}
			if (bestMark!=-1)
                emit toolTipRequested(linen,bestMark);
        }
        if (markToolTip.isEmpty()) QToolTip::hideText();
        else QToolTip::showText(helpEvent->globalPos(), markToolTip);
		e->setAccepted(true);
    }
    return QWidget::event(e);
}
bool QLineMarkPanel::paint(QPainter *p, QEditor *e)
{
	if ( !e || !e->document() )
		return true;

	m_rects.clear();
	m_lines.clear();
	QDocument *d = e->document();

	int realMarksPerLine = d->maxMarksPerLine();
	int marksPerLine = realMarksPerLine;
	if (marksPerLine<minMarksPerLine) marksPerLine=minMarksPerLine;
	if (marksPerLine>maxMarksPerLine) marksPerLine=maxMarksPerLine;
	setFixedWidth(marksPerLine ? marksPerLine * 16 + 2 : 18);

    int n;
    qreal posY,
        as = QFontMetricsF(d->font()).ascent(),
		ls = d->getLineSpacing(),
		pageBottom = e->viewport()->height(),
		contentsY = e->verticalOffset();

	QLineMarksInfoCenter *mic = QLineMarksInfoCenter::instance();

	n = d->lineNumber(contentsY);
	posY = 2 + d->y(n) - contentsY;

	//qDebug("first = %i; last = %i", first, last);
	//qDebug("beg pos : %i", posY);
	//qDebug("<session>");
	for ( ; ; ++n )
	{
		//qDebug("n = %i; pos = %i", n, posY);
		QDocumentLine line = d->line(n);

		if ( line.isNull() || ((posY - as) > pageBottom) )
			break;

		if ( line.isHidden() )
			continue;

		m_lines << n;
        m_rects << QRectF(0, posY, width(), ls);

		if ( realMarksPerLine )
		{
			int count = 1;
			QList<int> lm = line.marks();

			foreach ( int id, lm )
			{
				const QIcon & icon = mic->markType(id).icon;

				if ( icon.isNull() )
					continue;

                int size = qMin(16., ls-4); // (maxWidth, maxHeight) assuming square icons


                qreal x = count,
                    y = posY + ( (ls - size) /2  );
#ifdef Q_OS_MAC
                QPixmap pix=icon.pixmap(2*size); // oversampling on mac !!!!
#else
                QPixmap pix=icon.pixmap(size);
#endif

                p->drawPixmap(QRectF(x, y, size,size),pix,pix.rect());

				if (count < 16*(maxMarksPerLine-1))
                    count += 16;
			}
		}

		posY += ls * line.lineSpan();
	}
	//qDebug("</session>");

	return true;
}

/*!
	\internal
*/
void QLineMarkPanel::mousePressEvent(QMouseEvent *e)
{
// 	if ( !editor() || !editor()->document() || !editor()->marker() )
// 	{
// 		return QPanel::mousePressEvent(e);
// 	}
//
	QPanel::mousePressEvent(e);
 	e->accept();
}

/*!
	\internal
*/
void QLineMarkPanel::mouseReleaseEvent(QMouseEvent *e)
{
	if ( !editor() || !editor()->document() || !editor()->languageDefinition() || e->button()!= Qt::LeftButton)
	{
		QPanel::mouseReleaseEvent(e);
		return;
	}

	int line=editor()->document()->lineNumber(editor()->verticalOffset()+e->y());
	if (editor()->document()->line(line).isValid())
		emit lineClicked(line);

	//QMessageBox::warning(0, 0, "clik.");

	QDocumentLine l;
	QLanguageDefinition *d = editor()->languageDefinition();
	const int id = QLineMarksInfoCenter::instance()->markTypeId(d->defaultLineMark());
	if ( id < 0 )
		return;

	e->accept();


	for ( int i = 0; i < m_rects.count(); ++i )
	{
		if ( m_rects.at(i).contains(e->pos()) )
		{
			l = editor()->document()->line(m_lines.at(i));
			l.toggleMark(id);
			//m->toggleDefaultMark(l, -1);

			break;
		}
	}

	QPanel::mouseReleaseEvent(e);
}

/*!
	\internal
*/
void QLineMarkPanel::contextMenuEvent(QContextMenuEvent *e)
{
	if ( !editor() || !editor()->document() )
	{
		e->ignore();
		return;
	}

	int line=editor()->document()->lineNumber(editor()->verticalOffset()+e->y());
	if (editor()->document()->line(line).isValid())
		emit contextMenuRequested(line, e->globalPos());

	/*
	QTextBlock b;
	QMarker *m = editor()->marker();
	QTextDocument *d = editor()->document();

	e->accept();

	QHash<int, QRect>::iterator i;

	for ( i = rects.begin(); i != rects.end(); i++ )
	{
		b = d->findBlock(i.key());

		if ( i->contains( e->pos() ) )
			return m->menu(b, e->globalPos());
	}
	*/
}

/*! @} */
