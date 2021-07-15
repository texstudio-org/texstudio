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

#include "qcalltip.h"
#include "utilsUI.h"

/*!
	\file qcalltip.cpp
	\brief Implementation of the QCallTip class
*/

/*!
	\class QCallTip
	\brief A widget dedicated to calltips display
*/

QCallTip::QCallTip(QWidget *p)
 : QWidget(p), m_index(0)
{
	setCursor(Qt::ArrowCursor);
	setFocusPolicy(Qt::StrongFocus);
	setAttribute(Qt::WA_DeleteOnClose);
}

QCallTip::~QCallTip()
{

}

QStringList QCallTip::tips() const
{
	return m_tips;
}

void QCallTip::setTips(const QStringList& l)
{
	m_tips = l;
	m_index = 0;
}

static int arrowWidth = 14;

void QCallTip::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e)

	QPainter p(this);
	QFontMetrics fm = fontMetrics();

	m_up = m_down = QRect();

	bool bPrev = m_index, bNext = (m_index + 1) < m_tips.count();
	int offset = 3, whalf = arrowWidth / 2 - 3; //, hhalf = height() / 2;

	QRect bg(0, 0, UtilsUi::getFmWidth(fm, m_tips.at(m_index)) + 6, fm.height());

	if ( bPrev )
	{
		bg.setWidth(bg.width() + arrowWidth);
	}

	if ( bNext )
	{
		bg.setWidth(bg.width() + arrowWidth);
	}

	p.fillRect(bg, QColor(0xca, 0xff, 0x70));
	//p.drawRect(bg);

	p.save();

	p.setPen(QColor(0x00, 0x00, 0x00));
	p.drawLine(0, height() - 1, bg.width() - 1, height() - 1);
	p.drawLine(bg.width() - 1, height() - 1, bg.width() - 1, 0);

	p.setPen(QColor(0xc0, 0xc0, 0xc0));
	p.drawLine(0, height() - 1, 0, 0);
	p.drawLine(0, 0, bg.width() - 1, 0);

	p.restore();

	int top = height() / 3, bottom = height() - height() / 3;

	if ( bPrev )
	{
		int x = offset + arrowWidth / 2 - 1;

		QPoint pts[] = {
			QPoint(x - whalf, bottom),
			QPoint(x + whalf, bottom),
			QPoint(x, top)
		};

		p.drawPolygon(pts, sizeof(pts) / sizeof(QPoint), Qt::WindingFill);

		m_up = QRect(offset, 0, offset + arrowWidth, height());
		offset += arrowWidth;
	}

	if ( bNext )
	{
		int x = offset + arrowWidth / 2 - 1;

		QPoint pts[] = {
			QPoint(x - whalf, top),
			QPoint(x + whalf, top),
			QPoint(x, bottom)
		};

		p.drawPolygon(pts, sizeof(pts) / sizeof(QPoint), Qt::WindingFill);

		m_down = QRect(offset, 0, offset + arrowWidth, height());
		offset += arrowWidth;
	}

	p.drawText(offset, fm.ascent() + 2, m_tips.at(m_index));

	setFixedSize(bg.size() + QSize(1, 1));
}

void QCallTip::keyPressEvent(QKeyEvent *e)
{
	if ( e->modifiers() & (Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier) )
	{
		close();

		if ( parentWidget() )
			parentWidget()->setFocus();

		e->ignore();
		return;
	}

    QString text = e->text();

	switch ( e->key() )
	{
		case Qt::Key_Escape :
			close();

			if ( parentWidget() )
				parentWidget()->setFocus();

			e->accept();
			break;

		case Qt::Key_Enter :
		case Qt::Key_Return :
		case Qt::Key_Tab :
			//hide();

			close();

			if ( parentWidget() )
				parentWidget()->setFocus();

			e->ignore();

			break;

		case Qt::Key_Up :

			if ( m_index )
				--m_index;

			e->accept();
			update();
			break;

		case Qt::Key_Down :

			if ( (m_index + 1) < m_tips.count() )
				++m_index;

			e->accept();
			update();
			break;

		case Qt::Key_Backspace :

			close();

			if ( parentWidget() )
				parentWidget()->setFocus();

			e->ignore();
			break;

		case Qt::Key_Shift :
		case Qt::Key_Alt :
		case Qt::Key_Control :
			e->ignore();
			break;

		default:

			if ( text.count() && text.at(0).isPrint() )
			{

			} else {
				close();

				if ( parentWidget() )
					parentWidget()->setFocus();

			}

			e->ignore();

			break;
	}
}

void QCallTip::focusInEvent(QFocusEvent *e)
{
	QWidget::focusInEvent(e);
}

void QCallTip::focusOutEvent(QFocusEvent *e)
{
	QWidget::focusOutEvent(e);

	close();

	if ( parentWidget() )
		parentWidget()->setFocus();

}

void QCallTip::mousePressEvent(QMouseEvent *e)
{
	if ( m_index && m_up.isValid() && m_up.contains(e->pos()) )
	{
		--m_index;
	} else if (
			((m_index + 1) < m_tips.count())
		&&
			m_down.isValid()
		&&
			m_down.contains(e->pos())
		)
	{
		++m_index;
	} else {
		close();

		if ( parentWidget() )
			parentWidget()->setFocus();

	}

	e->accept();

	update();
}

void QCallTip::mouseReleaseEvent(QMouseEvent *e)
{
	e->accept();
}
