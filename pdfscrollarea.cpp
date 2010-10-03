/***************************************************************************
 *   copyright       : (C) 2003-2010 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
 
#include "pdfscrollarea.h"

#include <QtGui>


PdfScrollArea::PdfScrollArea( QWidget *parent)
    : QScrollArea( parent )
{
setFrameStyle(QFrame::NoFrame);
}

PdfScrollArea::~PdfScrollArea()
{

}

void PdfScrollArea::wheelEvent( QWheelEvent *e )
{
int delta = e->delta();
int vScroll = verticalScrollBar()->value();
e->accept();
if ( delta <= -120 && vScroll == verticalScrollBar()->maximum() )
    {
     emit pagedown();     
     }
else if ( delta >= 120 && vScroll == verticalScrollBar()->minimum() )
    {
    emit pageup();
    }
else
    QAbstractScrollArea::wheelEvent( e );
}

void PdfScrollArea::scrolltoMin()
{
verticalScrollBar()->setValue(verticalScrollBar()->minimum());
}

void PdfScrollArea::scrolltoMax()
{
verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}