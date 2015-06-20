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

class BuildManager;
class UserToolDialog : public QDialog  {
	Q_OBJECT
public:
	UserToolDialog(QWidget *parent=0, QString name="", BuildManager* bm = 0);
	~UserToolDialog();
	Ui::UserToolDialog ui;

	QStringList Name,Tool;
	BuildManager* buildManager;
private:
	enum ToolRoles{
		CommandRole = Qt::UserRole + 1,
	};

public slots:
	void init();

private slots:
	void change(QListWidgetItem *current, QListWidgetItem *previous);
	void itemTextChanged(const QString &text);
	void commandChanged(const QString &command);
	void slotOk();
	void slotAdd();
	void slotRemove();
	void slotMoveUp();
	void slotMoveDown();
	void openWizard();
};

#endif
