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

#ifndef Header_Array_Dialog
#define Header_Array_Dialog

#include "mostQtHeaders.h"
#include "ui_arraydialog.h"

class ArrayDialog : public QDialog
{
	Q_OBJECT

public:
    ArrayDialog(QWidget *parent = nullptr, const char *name = 0);
	~ArrayDialog();
	Ui::ArrayDialog ui;
	QString getLatexText();

protected slots:
	void newRows(int num);
	void newColumns(int num);
};

#endif
