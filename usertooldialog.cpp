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

#include "usertooldialog.h"
#include "buildmanager.h"
#include "smallUsefulFunctions.h"
UserToolDialog::UserToolDialog(QWidget *parent, QString name, BuildManager* bm) : QDialog(parent), buildManager(bm) {
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);

	connect(ui.commandList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), SLOT(change(QListWidgetItem*,QListWidgetItem*)));

	connect(ui.itemEdit, SIGNAL(textChanged(QString)), SLOT(itemTextChanged(QString)));
	connect(ui.toolEdit, SIGNAL(textChanged(QString)), SLOT(commandChanged(QString)));

	connect(ui.pushButtonWizard, SIGNAL(clicked()), SLOT(openWizard()));

	connect(ui.okButton, SIGNAL(clicked()), SLOT(slotOk()));
	connect(ui.pushButtonRemove, SIGNAL(clicked()), SLOT(slotRemove()));
	connect(ui.pushButtonAdd, SIGNAL(clicked()), SLOT(slotAdd()));
	connect(ui.pushButtonUp, SIGNAL(clicked()), SLOT(slotMoveUp()));
	connect(ui.pushButtonDown, SIGNAL(clicked()), SLOT(slotMoveDown()));
}

UserToolDialog::~UserToolDialog() {
}

void UserToolDialog::init() {
	for (int i=0;i<Tool.size();i++) {
		QListWidgetItem *item = new QListWidgetItem(Name.at(i));
		item->setData(UserToolDialog::CommandRole, Tool.at(i));
		ui.commandList->addItem(item);
	}
	if (Tool.size() == 0) {
		change(0,0); // disable controls as a side effect
	} else {
		ui.commandList->setCurrentRow(0);
	}
}

void UserToolDialog::change(QListWidgetItem *current, QListWidgetItem *previous) {
	Q_UNUSED(previous);
	ui.toolEdit->setEnabled(current);
	ui.itemEdit->setEnabled(current);
	if (!current) {
		ui.toolEdit->setText("");
		ui.itemEdit->setText("");
		return;
	}

	ui.toolEdit->setText(current->data(UserToolDialog::CommandRole).toString());
	ui.itemEdit->setText(current->data(Qt::DisplayRole).toString());
}

void UserToolDialog::itemTextChanged(const QString &text) {
	QListWidgetItem *item = ui.commandList->currentItem();
	if (!item) return;
	item->setData(Qt::DisplayRole, text);
}

void UserToolDialog::commandChanged(const QString &command) {
	QListWidgetItem *item = ui.commandList->currentItem();
	if (!item) return;
	item->setData(UserToolDialog::CommandRole, command);
}

void UserToolDialog::slotOk() {
	Tool.clear();
	Name.clear();
	for (int i=0; i<ui.commandList->count(); i++) {
		Tool << ui.commandList->item(i)->data(UserToolDialog::CommandRole).toString();
		Name << ui.commandList->item(i)->data(Qt::DisplayRole).toString();
	}
	accept();
}

void UserToolDialog::slotAdd() {
	QString newName(tr("User Command"));
	for (int i=0; i<=ui.commandList->count(); i++) {
		if (i>0) newName = tr("User Command").append(QString(" %1").arg(i));
		if (ui.commandList->findItems(newName, Qt::MatchExactly).count() == 0) break;
	}
	QListWidgetItem *item = new QListWidgetItem(newName, ui.commandList);
	ui.commandList->setCurrentItem(item);
}

void UserToolDialog::slotRemove() {
	QListWidgetItem *item = ui.commandList->takeItem(ui.commandList->currentRow());
	if (item) delete item;
}

void UserToolDialog::slotMoveUp() {
	int row = ui.commandList->currentRow();
	if (row <= 0) return;
	QListWidgetItem *item = ui.commandList->takeItem(row);
	ui.commandList->insertItem(row-1, item);
	ui.commandList->setCurrentItem(item);
}

void UserToolDialog::slotMoveDown() {
	int row = ui.commandList->currentRow();
	if (row < 0 || row >= ui.commandList->count()-1) return;
	QListWidgetItem *item = ui.commandList->takeItem(row);
	ui.commandList->insertItem(row+1, item);
	ui.commandList->setCurrentItem(item);
}

void UserToolDialog::openWizard() {
	if (!buildManager) return;
	ui.toolEdit->setText(buildManager->editCommandList(ui.toolEdit->text()));
}
