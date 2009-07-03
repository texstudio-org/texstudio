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

#ifndef TABDIALOG_H
#define TABDIALOG_H

#include "mostQtHeaders.h"

#include "ui_tabdialog.h"

class TabDialog : public QDialog  {
	Q_OBJECT
public:
	TabDialog(QWidget *parent=0, const char *name=0);
	~TabDialog();
	Ui::TabDialog ui;

protected slots:
	void NewRows(int num);
	void NewColumns(int num);
};


#endif


