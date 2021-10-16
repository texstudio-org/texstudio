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

#ifndef Header_QFold_Panel
#define Header_QFold_Panel

#include "mostQtHeaders.h"

#include <QPainterPath>

#include "qpanel.h"

/*!
	\file qfoldpanel.h
	\brief Definition of the QFoldPanel class.
	
	\see QFoldPanel
*/

class QDocumentLine;

class QCE_EXPORT QFoldPanel : public QPanel
{
	Q_OBJECT
	
	public:
        Q_Panel(QFoldPanel, "Fold Panel")
		
		QFoldPanel(QWidget *p = 0);
		virtual ~QFoldPanel();
		
		virtual QString type() const;

	signals:
		void contextMenuRequested(int line, QPoint globalPos);

	protected:
		void setWidth(int w);
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseMoveEvent(QMouseEvent *e);
		virtual void leaveEvent(QEvent *);
		virtual void contextMenuEvent(QContextMenuEvent *e);
		virtual bool paint(QPainter *p, QEditor *e);
		bool event(QEvent *e);

        int mapRectPosToLine(const QPointF& p);

		QRectF drawIcon(QPainter *p, QEditor *e,
						qreal x, qreal y, int iconSize, bool expand, bool highlight);

		virtual void editorChange(QEditor *e);

	protected slots:
		void setFont_slot(const QFont &font);

	private:
        QList<QRectF> m_rects;
		QList<int> m_lines;
		int m_width;
		int m_lastMouseLine;
};

#endif // _QFOLD_PANEL_H_
