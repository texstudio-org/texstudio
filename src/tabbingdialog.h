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

#ifndef Header_Tabbing_Dialog
#define Header_Tabbing_Dialog

#include "mostQtHeaders.h"

#include "ui_tabbingdialog.h"

class TabbingDialog : public QDialog
{
	Q_OBJECT

public:
	TabbingDialog(QWidget *parent = 0, const char *name = 0);
	~TabbingDialog();
	Ui::TabbingDialog ui;
};

#endif
