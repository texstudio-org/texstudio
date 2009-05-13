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

UserToolDialog::UserToolDialog(QWidget *parent, QString name) : QDialog(parent) {
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);

	previous_index=0;

	ui.comboBox->insertItem(0, "Command 1");
	ui.comboBox->insertItem(1, "Command 2");
	ui.comboBox->insertItem(2, "Command 3");
	ui.comboBox->insertItem(3, "Command 4");
	ui.comboBox->insertItem(4, "Command 5");
	connect(ui.comboBox, SIGNAL(activated(int)),this,SLOT(change(int)));

	connect(ui.okButton, SIGNAL(clicked()), SLOT(slotOk()));
}

UserToolDialog::~UserToolDialog() {
}

void UserToolDialog::init() {
	ui.toolEdit->setText(Tool[0]);
	ui.itemEdit->setText(Name[0]);
	ui.comboBox->setCurrentIndex(0);
}

void UserToolDialog::change(int index) {
	Tool[previous_index]=ui.toolEdit->text();
	Name[previous_index]=ui.itemEdit->text();
	ui.toolEdit->setText(Tool[index]);
	ui.itemEdit->setText(Name[index]);
	previous_index=index;
}

void UserToolDialog::slotOk() {
	Tool[previous_index]=ui.toolEdit->text();
	Name[previous_index]=ui.itemEdit->text();
	accept();
}
