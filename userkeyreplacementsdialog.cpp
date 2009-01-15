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

#include "userkeyreplacementsdialog.h"


UserKeyReplacementsDialog::UserKeyReplacementsDialog( QWidget* parent,  QString name)
    : QDialog( parent)
{
setWindowTitle(name);
setModal(true);
ui.setupUi(this);


//connect(ui.comboBox, SIGNAL(activated(int)),this,SLOT(change(int)));

  connect(ui.okButton, SIGNAL(clicked()), SLOT(slotOk()) );
  connect(ui.cancelButton, SIGNAL(clicked()), SLOT(slotCancel()) );
  connect(ui.addrowButton, SIGNAL(clicked()), SLOT(slotAddRow()) );
  connect(ui.removeRowButton, SIGNAL(clicked()), SLOT(slotRemoveRow()) );
}

UserKeyReplacementsDialog::~UserKeyReplacementsDialog()
{
}

void UserKeyReplacementsDialog::init()
{
    for (int i=0;i<UserKeyReplace.size();i++) {
        ui.keyList->insertRow(i);
        ui.keyList->setItem(i,0,new QTableWidgetItem(UserKeyReplace[i],0));
        ui.keyList->setItem(i,1,new QTableWidgetItem(UserKeyReplaceBeforeWord[i],0));
        ui.keyList->setItem(i,2,new QTableWidgetItem(UserKeyReplaceAfterWord[i],0));
    }
}
/*
void UserMenuDialog::change(int index)
{
Tag[previous_index]=ui.tagEdit->toPlainText();
Name[previous_index]=ui.itemEdit->text();
ui.tagEdit->setPlainText(Tag[index]);
ui.itemEdit->setText(Name[index]);
previous_index=index;
}
*/
void UserKeyReplacementsDialog::slotOk()
{
    UserKeyReplace.clear();
    UserKeyReplaceBeforeWord.clear();
    UserKeyReplaceAfterWord.clear();
    for (int i=0;i<ui.keyList->rowCount();i++){
        UserKeyReplace.append(ui.keyList->item(i,0)->text());
        UserKeyReplaceBeforeWord.append(ui.keyList->item(i,1)->text());
        UserKeyReplaceAfterWord.append(ui.keyList->item(i,2)->text());
    }
    accept();
}

void UserKeyReplacementsDialog::slotCancel(){
    reject();
}
void UserKeyReplacementsDialog::slotAddRow(){
    ui.keyList->insertRow(ui.keyList->rowCount()-1);
}
void UserKeyReplacementsDialog::slotRemoveRow(){
    ui.keyList->removeRow(ui.keyList->currentItem()->row());
}
