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

#include <QHeaderView>
#include <QScrollBar>
#include <QDebug>

#include "userquickdialog.h"

UserQuickDialog::UserQuickDialog(QWidget *parent, const QStringList& usualNames, const QStringList& usualCommands)
	:QDialog( parent)
{
	ui.setupUi(this);

	connect(ui.addButton, SIGNAL( clicked() ), this, SLOT( actionAddCommand() ) );
	connect(ui.upButton, SIGNAL( clicked() ), this, SLOT( actionUp() ) );
	connect(ui.downButton, SIGNAL( clicked() ), this, SLOT( actionDown() ) );
	connect(ui.deleteButton, SIGNAL( clicked() ), this, SLOT( actionDelete() ) );

	ui.listWidget->clear();
	ui.listWidget->setAlternatingRowColors(true);

	//ui.commandWidget->setSelectionMode (QAbstractItemView::ExtendedSelection);
	ui.commandWidget->setViewMode(QListView::ListMode);
	ui.commandWidget->addItems(usualNames);
	ui.commandWidget->addItem(tr("User"));
	nameToCommand.insert(tr("User"), "");

	for(int i=0; i<usualNames.count(); i++ ) nameToCommand.insert(usualNames.at(i),usualCommands.at(i));
	for(int i=0; i<usualNames.count(); i++ ) commandToName.insert(usualCommands.at(i),usualNames.at(i));
}

UserQuickDialog::~UserQuickDialog(){
}

void UserQuickDialog::addItem(QString name)
{
	QString cmd = nameToCommand.value(name,name);
	ui.listWidget->addItem(name);
	QListWidgetItem* item = ui.listWidget->item(ui.listWidget->count()-1);
	if (cmd == "") item->setFlags(item->flags() | Qt::ItemIsEditable);
	if (ui.listWidget->count()>0)
	{
		ui.listWidget->setCurrentItem(item);
		ui.listWidget->setItemSelected(ui.listWidget->currentItem(), true);
	}
}

void UserQuickDialog::actionUp()
{
	int current=ui.listWidget->currentRow();
	if (current<=0) return;
	QListWidgetItem *item=ui.listWidget->item(current)->clone();
	delete ui.listWidget->item(current);
	ui.listWidget->insertItem(current-1,item);
	ui.listWidget->setCurrentItem(ui.listWidget->item(current-1));
	ui.listWidget->setItemSelected(ui.listWidget->item(current-1),true);
}

void UserQuickDialog::actionDown()
{
	int current=ui.listWidget->currentRow();
	if (current>=ui.listWidget->count()-1 || current<0) return;
	QListWidgetItem *item=ui.listWidget->item(current)->clone();
	delete ui.listWidget->item(current);
	ui.listWidget->insertItem(current+1,item);
	ui.listWidget->setCurrentItem(ui.listWidget->item(current+1));
	ui.listWidget->setItemSelected(ui.listWidget->item(current+1),true);
}

void UserQuickDialog::actionDelete()
{
	int current=ui.listWidget->currentRow();
	if (current<0) return;
	delete ui.listWidget->currentItem();

	if (current==ui.listWidget->count())
	{
		ui.listWidget->setCurrentItem(ui.listWidget->item(current-1));
		ui.listWidget->setItemSelected(ui.listWidget->item(current-1),true);
	}
	else
	{
		ui.listWidget->setCurrentItem(ui.listWidget->item(current));
		ui.listWidget->setItemSelected(ui.listWidget->item(current),true);
	}
}

void UserQuickDialog::actionAddCommand()
{
	QString fn;
	QList<QListWidgetItem *> items;
	items = ui.commandWidget->selectedItems();
	for (int i = 0; i < items.count(); ++i)
	{
		fn=items[i]->text();
		addItem(fn);
	}
}


void UserQuickDialog::setCommandList(const QString& list){
	if (list.isEmpty()) return;
	QStringList split = list.split("|");
	foreach (const QString &s, split){
		QString c = s.trimmed();
		QString name = commandToName.value(c,c);
		ui.listWidget->addItem(name);
		if (name == c || c == "") {
			QListWidgetItem * item = ui.listWidget->item(ui.listWidget->count()-1);
			item->setFlags(item->flags() | Qt::ItemIsEditable);
		}
	}
}

QString UserQuickDialog::getCommandList(){
	QStringList userlist;
	for (int i=0;i<ui.listWidget->count();i++)
		userlist << nameToCommand.value(ui.listWidget->item(i)->text(),ui.listWidget->item(i)->text());
	QString userQuickCommand=userlist.join(" | ");
	return userQuickCommand;
}


