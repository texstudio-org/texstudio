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

#ifndef REFDIALOG_H
#define REFDIALOG_H

#include "ui_refdialog.h"

class RefDialog : public QDialog  {
	Q_OBJECT
public:
	RefDialog(QWidget *parent=0, const char *name=0);
	~RefDialog();
	Ui::RefDialog ui;
};


#endif
