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

class QCodeEdit;
class QLanguageFactory;
class QSearchReplacePanel;
class UserMenuDialog : public QDialog {
	Q_OBJECT

public:
	UserMenuDialog(QWidget* parent = 0, QString name="", QLanguageFactory* languageFactory=0);
	~UserMenuDialog();
	Ui::UserMenuDialog ui;

	QStringList Name,Tag,Abbrev;

private:
	int previous_index;
	QCodeEdit* codeedit;
	QLanguageFactory* languages;
	QSearchReplacePanel* searchReplacePanel;
public slots:
	void init();


private slots:
	void change(int index);
	void slotOk();
	void slotAdd();
	void slotRemove();
	void textChanged();
	void changeTypeToNormal();
	void changeTypeToEnvironment();
	void changeTypeToScript();
};

#endif // USERMENUDIALOG_H
