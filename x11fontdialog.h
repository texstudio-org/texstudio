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

#ifndef X11FONTDIALOG_H
#define X11FONTDIALOG_H

#include "ui_x11fontdialog.h"

class X11FontDialog : public QDialog  {
   Q_OBJECT
public:
	X11FontDialog(QWidget *parent=0);
	~X11FontDialog();
	Ui::X11FontDialog ui;
};


#endif
