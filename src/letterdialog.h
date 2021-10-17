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

#ifndef Header_Letter_Dialog
#define Header_Letter_Dialog

#include "mostQtHeaders.h"

#include "ui_letterdialog.h"

class LetterDialog : public QDialog
{
	Q_OBJECT

public:
	LetterDialog(QWidget *parent = 0, const char *name = 0);
	~LetterDialog();
	Ui::LetterDialog ui;
};


#endif

