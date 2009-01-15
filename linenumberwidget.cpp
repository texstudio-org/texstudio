/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "linenumberwidget.h"
#include <QTextDocument>
#include <QTextCursor>
#include <QTextEdit>
#include <QTextBlock>

LineNumberWidget::LineNumberWidget(LatexEditor* editor, QWidget* parent)
	: QWidget( parent) ,
	  m_editor( editor )
{
setAutoFillBackground( true );
QPalette p( palette() );
p.setColor( backgroundRole(), QColor( "#ecffec" ) );
setPalette( p );
setToolTip(tr("Click to add or remove a bookmark"));
connect( m_editor->verticalScrollBar(), SIGNAL( valueChanged( int ) ), this, SLOT( update() ) );
connect( m_editor, SIGNAL( textChanged() ), this, SLOT( update() ) );
}

LineNumberWidget::~LineNumberWidget()
{
}

void LineNumberWidget::paintEvent( QPaintEvent* /*e*/ )
{
int max=0;
int l=0;
QPainter painter( this );
painter.setFont(numfont);
const QFontMetrics fm(numfont);
int yOffset = m_editor->verticalScrollBar()->value();
QTextDocument *doc = m_editor->document();
int i = 1;
QTextBlock p = doc->begin();
QString numtext;
const QBrush oldbrush=painter.brush();
QPen oldpen(QColor("#136872"));
oldpen.setStyle(Qt::SolidLine);
painter.setPen(oldpen);
painter.drawLine(width()-2,0,width()-2,height());
while ( p.isValid() ) 
	{
	QPointF point = p.layout()->position();
	if ( point.y() + 20 - yOffset < 0 ) 
		{
		i++;
		p = p.next();
		continue;
		}		
	if ( (int)(point.y()) - yOffset > height() ) break;
	for (int j = 0; j < 3; ++j)
		{
		if (m_editor->UserBookmark[j]==i) 
 			{
			const QBrush brush(QColor("#1B8EA6"));
			painter.fillRect(2, (int)(point.y()) - yOffset,fm.width("0")+6,fm.lineSpacing(), brush);
			const QPen pen(QColor("#FFFFFF"));
			painter.setPen(pen);
			painter.drawText(4, (int)(point.y()) - yOffset,width()-4,fm.lineSpacing(),Qt::AlignLeft | Qt::AlignTop,QString::number(j+1));
 			}
		}
	painter.setPen(oldpen);
	numtext=QString::number(i);
	painter.drawText(0, (int)(point.y()) - yOffset,width()-4,fm.lineSpacing(),Qt::AlignRight | Qt::AlignTop,numtext);
	l= fm.width(numtext)+18+fm.width("0");
	if (l>max) max=l;
	i++;
	p = p.next();
	}
	if (i>=10000) setFixedWidth(max);	
painter.end();
}

void LineNumberWidget::mousePressEvent(QMouseEvent *e)
{
e->accept();
QPoint p = m_editor->viewport()->mapFromGlobal(e->globalPos());
QTextCursor cur( m_editor->cursorForPosition(p) );
int i = m_editor->linefromblock(cur.block());	
if ( i==-1 ) return;
for (int j = 0; j < 3; ++j)
	{
	if (m_editor->UserBookmark[j]==i) 
		{
		m_editor->UserBookmark[j]=0;
		update();
		return;
		}
	}
for (int j = 0; j < 3; ++j)
	{
	if (m_editor->UserBookmark[j]==0) 
		{
		m_editor->UserBookmark[j]=i;
		update();
		return;
		}
	}
}

void LineNumberWidget::setFont(QFont efont)
{
numfont=efont;
}

