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

#include "replacedialog.h"
#include <QMessageBox>

ReplaceDialog::ReplaceDialog(QWidget* parent,  const char* name, Qt::WFlags fl )
    : QDialog( parent, fl )
{
setWindowTitle(name);
setModal(true);
ui.setupUi(this);
connect( ui.findButton, SIGNAL( clicked() ), this, SLOT( doReplace() ) );
connect( ui.replaceallButton, SIGNAL( clicked() ), this, SLOT( doReplaceAll() ) );
connect( ui.closeButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
ui.findButton->setShortcut(Qt::Key_Return);
}


ReplaceDialog::~ReplaceDialog()
{
}

void ReplaceDialog::doReplace()
{
reject();
if ( !editor ) 	return;
bool go=true;
while (go && editor->search( ui.comboFind->currentText(), ui.checkCase->isChecked(),
	ui.checkWords->isChecked(), ui.radioForward->isChecked(), !ui.checkBegin->isChecked()) )
       {
       switch(  QMessageBox::warning(this, "Texmaker",tr("Replace this occurence ? "),tr("Yes"), tr("No"), tr("Cancel"), 0,2 ) )
         {
         case 0:
         editor->replace(ui.comboReplace->currentText() );
         ui.checkBegin->setChecked( FALSE );
    	   break;
         case 1:
         ui.checkBegin->setChecked( FALSE );
    	   break;
         case 2:
         go=false;
    	   break;
         }
       }
if (go) ui.checkBegin->setChecked( TRUE );
}

void ReplaceDialog::doReplaceAll()
{
if ( !editor ) return;
while ( editor->search( ui.comboFind->currentText(), ui.checkCase->isChecked(),
ui.checkWords->isChecked(), ui.radioForward->isChecked(), !ui.checkBegin->isChecked()) )
    {
    editor->replace(ui.comboReplace->currentText() );
    ui.checkBegin->setChecked( FALSE );
    }
ui.checkBegin->setChecked( TRUE );
}

void ReplaceDialog::SetEditor(LatexEditor *ed)
{
editor=ed;
}



