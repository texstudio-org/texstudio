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

#include "usermenudialog.h"


UserMenuDialog::UserMenuDialog(QWidget* parent,  QString name)
		: QDialog(parent) {
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);

	previous_index=0;

	ui.comboBox->insertItem(0, "Menu 1");
	ui.comboBox->insertItem(1, "Menu 2");
	ui.comboBox->insertItem(2, "Menu 3");
	ui.comboBox->insertItem(3, "Menu 4");
	ui.comboBox->insertItem(4, "Menu 5");
	ui.comboBox->insertItem(5, "Menu 6");
	ui.comboBox->insertItem(6, "Menu 7");
	ui.comboBox->insertItem(7, "Menu 8");
	ui.comboBox->insertItem(8, "Menu 9");
	ui.comboBox->insertItem(9, "Menu 10");
        if(Tag.size()>10) {
            for(int i=10;i<Tag.size();i++)
                   ui.comboBox->insertItem(i, QString("Menu %1").arg(i));
        }
	connect(ui.comboBox, SIGNAL(activated(int)),this,SLOT(change(int)));

	connect(ui.okButton, SIGNAL(clicked()), SLOT(slotOk()));

	connect(ui.tagEdit, SIGNAL(textChanged()), SLOT(textChanged()));
	connect(ui.radioButtonNormal, SIGNAL(clicked()), SLOT(changeTypeToNormal()));
	connect(ui.radioButtonEnvironment, SIGNAL(clicked()), SLOT(changeTypeToEnvironment()));
	connect(ui.radioButtonScript, SIGNAL(clicked()), SLOT(changeTypeToScript()));
}

UserMenuDialog::~UserMenuDialog() {
}

void UserMenuDialog::init() {
	ui.tagEdit->setPlainText(Tag[0]);
	ui.itemEdit->setText(Name[0]);
        ui.abbrevEdit->setText(Abbrev[0]);
	ui.comboBox->setCurrentIndex(0);
}

void UserMenuDialog::change(int index) {
	Tag[previous_index]=ui.tagEdit->toPlainText();
	Name[previous_index]=ui.itemEdit->text();
	ui.tagEdit->setPlainText(Tag[index]);
	ui.itemEdit->setText(Name[index]);
        ui.abbrevEdit->setText(Abbrev[index]);
	previous_index=index;
}

void UserMenuDialog::slotOk() {
	Tag[previous_index]=ui.tagEdit->toPlainText();
	Name[previous_index]=ui.itemEdit->text();
        Abbrev[previous_index]=ui.abbrevEdit->text();
	accept();
}
void UserMenuDialog::changeTypeToNormal(){
	QString cur = ui.tagEdit->document()->toPlainText();
	if (cur.startsWith("%SCRIPT\n")) ui.tagEdit->document()->setPlainText(cur.mid(8));
	else if (cur.startsWith("%")) ui.tagEdit->document()->setPlainText(cur.mid(1));
}
void UserMenuDialog::changeTypeToEnvironment(){
	QString cur = ui.tagEdit->document()->toPlainText();
	if (cur.startsWith("%SCRIPT")) ui.tagEdit->document()->setPlainText("%"+cur.mid(8));
	else {
		if (cur.startsWith("%")) return;
		ui.tagEdit->document()->setPlainText("%"+cur);
	}
}
void UserMenuDialog::changeTypeToScript(){
	QString cur = ui.tagEdit->document()->toPlainText();
	if (cur.startsWith("%SCRIPT\n")) return;
	if (cur.startsWith("%")) cur = cur.mid(1);
	ui.tagEdit->document()->setPlainText("%SCRIPT\n"+cur);
}
void UserMenuDialog::textChanged(){
	QString line = ui.tagEdit->document()->firstBlock().text();
	if (line=="%SCRIPT") ui.radioButtonScript->setChecked(true);
	else if (line.startsWith("%")) ui.radioButtonEnvironment->setChecked(true);
	else ui.radioButtonNormal->setChecked(true);
}
