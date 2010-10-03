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

#ifndef USERTOOLDIALOG_H
#define USERTOOLDIALOG_H

#include "mostQtHeaders.h"

#include "ui_usertooldialog.h"

typedef QString userCd[5];

class BuildManager;
class UserToolDialog : public QDialog  {
	Q_OBJECT
public:
	UserToolDialog(QWidget *parent=0, QString name="", BuildManager* bm = 0);
	~UserToolDialog();
	Ui::UserToolDialog ui;

	userCd Name,Tool;
	BuildManager* buildManager;
private:
	int previous_index;

public slots:
	void init();

private slots:
	void change(int index);
	void slotOk();
	void openWizard();
};

#endif
