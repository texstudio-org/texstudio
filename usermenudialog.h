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

#ifndef USERMENUDIALOG_H
#define USERMENUDIALOG_H

#include "mostQtHeaders.h"

#include "ui_usermenudialog.h"

typedef QStringList userlist;

class UserMenuDialog : public QDialog {
	Q_OBJECT

public:
	UserMenuDialog(QWidget* parent = 0, QString name="");
	~UserMenuDialog();
	Ui::UserMenuDialog ui;

	userlist Name,Tag,Abbrev;

private:
	int previous_index;

public slots:
	void init();


private slots:
	void change(int index);
	void slotOk();
	void textChanged();
	void changeTypeToNormal();
	void changeTypeToEnvironment();
	void changeTypeToScript();
};

#endif // USERMENUDIALOG_H
