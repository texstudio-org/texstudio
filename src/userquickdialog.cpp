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
#include "utilsUI.h"

UserQuickDialog::UserQuickDialog(QWidget *parent, const QStringList &ids , const QStringList &usualNames, const QStringList &usualCommands)
	: QDialog( parent)
{
	ui.setupUi(this);
	UtilsUi::resizeInFontHeight(this, 48, 22);

	connect(ui.addButton, SIGNAL( clicked() ), this, SLOT( actionAddCommand() ) );
	connect(ui.upButton, SIGNAL( clicked() ), this, SLOT( actionUp() ) );
	connect(ui.downButton, SIGNAL( clicked() ), this, SLOT( actionDown() ) );
	connect(ui.deleteButton, SIGNAL( clicked() ), this, SLOT( actionDelete() ) );

	ui.listWidget->clear();
	ui.listWidget->setAlternatingRowColors(true);

	//ui.commandWidget->setSelectionMode (QAbstractItemView::ExtendedSelection);
	int len = usualNames.count();
	for (int i = 0; i < len; i++) idToCommand.insert(ids.at(i), usualCommands.at(i));
	for (int i = 0; i < len; i++) commandToId.insert(usualCommands.at(i), ids.at(i));
	for (int i = 0; i < len; i++) idToName.insert(ids.at(i), usualNames.at(i));
	for (int i = 0; i < len; i++) nameToId.insert(usualNames.at(i), ids.at(i));
	nameToId.insert(tr("User"), "");

	ui.commandWidget->setViewMode(QListView::ListMode);
	for (int i = 0; i < ids.count(); i++) ui.commandWidget->addItem(idToName.value(ids[i]));
	ui.commandWidget->addItem(tr("User"));

	for (int i = 0; i < ids.count(); i++) commandToId.insert(ids[i], ids[i]);
}

UserQuickDialog::~UserQuickDialog()
{
}

void UserQuickDialog::addItem(QString name)
{
	QString cmd = idToCommand.value(nameToId.value(name, name), name);
	ui.listWidget->addItem(name);
	QListWidgetItem *item = ui.listWidget->item(ui.listWidget->count() - 1);
	if (cmd == "" || name == tr("User")) item->setFlags(item->flags() | Qt::ItemIsEditable);
	if (ui.listWidget->count() > 0) {
		ui.listWidget->setCurrentItem(item);
		ui.listWidget->currentItem()->setSelected (true);
	}
}

void UserQuickDialog::actionUp()
{
	int current = ui.listWidget->currentRow();
	if (current <= 0) return;
	QListWidgetItem *item = ui.listWidget->item(current)->clone();
	delete ui.listWidget->item(current);
	ui.listWidget->insertItem(current - 1, item);
	ui.listWidget->setCurrentItem(ui.listWidget->item(current - 1));
	ui.listWidget->item(current - 1)->setSelected(true);
}

void UserQuickDialog::actionDown()
{
	int current = ui.listWidget->currentRow();
	if (current >= ui.listWidget->count() - 1 || current < 0) return;
	QListWidgetItem *item = ui.listWidget->item(current)->clone();
	delete ui.listWidget->item(current);
	ui.listWidget->insertItem(current + 1, item);
	ui.listWidget->setCurrentItem(ui.listWidget->item(current + 1));
	ui.listWidget->item(current + 1)->setSelected(true);
}

void UserQuickDialog::actionDelete()
{
	int current = ui.listWidget->currentRow();
	if (current < 0) return;
	delete ui.listWidget->currentItem();

    if(ui.listWidget->count()==0) return; //empty, no item left for selection

	if (current == ui.listWidget->count()) {
		ui.listWidget->setCurrentItem(ui.listWidget->item(current - 1));
		ui.listWidget->item(current - 1)->setSelected(true);
	} else {
		ui.listWidget->setCurrentItem(ui.listWidget->item(current));
		ui.listWidget->item(current)->setSelected(true);
	}
}

void UserQuickDialog::actionAddCommand()
{
	QString fn;
	QList<QListWidgetItem *> items;
	items = ui.commandWidget->selectedItems();
	for (int i = 0; i < items.count(); ++i) {
		fn = items[i]->text();
		addItem(fn);
	}
}

void UserQuickDialog::setCommandList(const QString &list)
{
	if (list.isEmpty()) return;
	QStringList split = list.split("|");
	foreach (const QString &s, split) {
		QString c = s.trimmed();
		QString name = idToName.value(commandToId.value(c, c), c);
		ui.listWidget->addItem(name);
		if (name == c || c == "") {
			QListWidgetItem *item = ui.listWidget->item(ui.listWidget->count() - 1);
			item->setFlags(item->flags() | Qt::ItemIsEditable);
		}
	}
}

QString UserQuickDialog::getCommandList()
{
	QStringList userlist;
	for (int i = 0; i < ui.listWidget->count(); i++)
		userlist << nameToId.value(ui.listWidget->item(i)->text(), ui.listWidget->item(i)->text());
	QString userQuickCommand = userlist.join(" | ");
	return userQuickCommand;
}
