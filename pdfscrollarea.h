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

#ifndef PDFSCROLLAREA_H
#define PDFSCROLLAREA_H

#include <QScrollArea>

class PdfScrollArea : public QScrollArea
{
Q_OBJECT

public:
    PdfScrollArea( QWidget *parent);
    ~PdfScrollArea();

signals:
  void pageup();
  void pagedown();
protected:
  void wheelEvent( QWheelEvent* );
public slots:
  void scrolltoMin();
  void scrolltoMax();
};

#endif

