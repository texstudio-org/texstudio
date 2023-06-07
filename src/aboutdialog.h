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

#ifndef Header_About_Dialog
#define Header_About_Dialog

#include "mostQtHeaders.h"

#include "ui_aboutdialog.h"

class AboutDialog : public QDialog
{
	Q_OBJECT

public:
    AboutDialog(QWidget *parent = nullptr); ///< set-up about dialog
	~AboutDialog();
	Ui::AboutDialog ui;
private slots:
	void setText(QString latestVersion = "");
	void largeLogo(); ///< show enlarged logo, triggered via context menu on image in about-dialog
};


#endif
