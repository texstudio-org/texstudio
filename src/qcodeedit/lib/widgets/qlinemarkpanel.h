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

#ifndef Header_QLine_Mark_Panel
#define Header_QLine_Mark_Panel

/*!
	\file qlinemarkpanel.h
	\brief Definition of the QLineMarkPanel class.
	
	\see QLineMarkPanel
*/

#include "mostQtHeaders.h"

#include "qpanel.h"

class QDocumentLine;

class QCE_EXPORT QLineMarkPanel : public QPanel
{
	Q_OBJECT
	
	public:
		Q_Panel(QLineMarkPanel, "Line Mark Panel")
		
		QLineMarkPanel(QWidget *p = 0);
		virtual ~QLineMarkPanel();
		
		virtual QString type() const;
		void setToolTipForTouchedMark(QString text);
signals:
		void toolTipRequested(int line, int markID);
		void lineClicked(int line);
		void contextMenuRequested(int line, QPoint globalPos);
		
protected:
		virtual bool event(QEvent *e);
		virtual bool paint(QPainter *p, QEditor *e);
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);
		virtual void contextMenuEvent(QContextMenuEvent *e);
		
	private:
        QList<QRectF> m_rects;
		QList<int> m_lines;
		int minMarksPerLine;
		int maxMarksPerLine;
		QString markToolTip;
};

#endif // _QLINE_MARK_PANEL_H_

