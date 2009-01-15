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

#include "gotolinedialog.h"


GotoLineDialog::GotoLineDialog(QWidget* parent,  const char* name, Qt::WFlags fl )
    : QDialog( parent, fl )
{
setWindowTitle(name);
setModal(true);
ui.setupUi(this);
connect( ui.closeButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
connect( ui.gotoButton, SIGNAL( clicked() ), this, SLOT( gotoLine() ) );
}

GotoLineDialog::~GotoLineDialog()
{

}
void GotoLineDialog::gotoLine()
{
    if ( editor )
    {
    editor->gotoLine( ui.spinLine->value() - 1 );
    editor->setFocus();
    }
    accept();
}
void GotoLineDialog::SetEditor(LatexEditor *ed)
{
editor=ed;
}

