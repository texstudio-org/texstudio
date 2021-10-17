/***************************************************************************
 *   copyright       : (C) 2003-2010 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef Header_UserQuick_Dialog
#define Header_UserQuick_Dialog

#include "ui_userquickdialog.h"

#include <QListWidgetItem>
#include <QList>
#include <QStringList>
#include <QCloseEvent>

class UserQuickDialog : public QDialog
{
	Q_OBJECT

public:
	UserQuickDialog(QWidget *parent = 0, const QStringList &ids = QStringList(), const QStringList &usualNames = QStringList(""), const QStringList &usualCommands = QStringList(""));
	~UserQuickDialog();
	Ui::UserQuickDialog ui;
	void setCommandList(const QString &list);
	QString getCommandList();

private:
	QMap<QString, QString> idToCommand, commandToId, idToName, nameToId;

private slots:
	void addItem(QString name);
	void actionUp();
	void actionDown();
	void actionDelete();
	void actionAddCommand();
};


#endif
