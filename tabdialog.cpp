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

#include "tabdialog.h"

TabDialog::TabDialog(QWidget *parent, const char *name)
    :QDialog( parent)
{
setWindowTitle(name);
setModal(true);
ui.setupUi(this);

ui.tableWidget->setRowCount( 2 );
ui.tableWidget->setColumnCount( 2 );

ui.spinBoxRows->setValue(2);
ui.spinBoxRows->setRange(1,99);
connect( ui.spinBoxRows, SIGNAL(valueChanged(int)),this, SLOT(NewRows(int)));

ui.spinBoxColumns->setValue(2);
ui.spinBoxColumns->setRange(1,99);
connect( ui.spinBoxColumns, SIGNAL(valueChanged(int)),this, SLOT(NewColumns(int)));

ui.comboAlignment->insertItem(0,"Center" );
ui.comboAlignment->insertItem(1,"Left" );
ui.comboAlignment->insertItem(2,"Right" );
ui.comboAlignment->insertItem(3, "p{}");

ui.comboSeparator->insertItem(0,"|");
ui.comboSeparator->insertItem(1,"||");
ui.comboSeparator->insertItem(2,"none");
ui.comboSeparator->insertItem(3, "@{text}" );
setWindowTitle(tr("Quick Tabular"));
}

TabDialog::~TabDialog(){
}
void TabDialog::NewRows(int num)
{
  ui.tableWidget->setRowCount( num );
}
void TabDialog::NewColumns(int num)
{
  ui.tableWidget->setColumnCount( num );
}
