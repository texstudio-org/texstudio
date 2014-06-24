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

#include "arraydialog.h"

ArrayDialog::ArrayDialog(QWidget *parent, const char *name)
		:QDialog(parent) {
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);

	ui.tableWidget->setRowCount(2);
	ui.tableWidget->setColumnCount(2);

	ui.spinBoxRows->setValue(2);
	ui.spinBoxRows->setRange(1,99);
	connect(ui.spinBoxRows, SIGNAL(valueChanged(int)),this, SLOT(NewRows(int)));

	ui.spinBoxColumns->setValue(2);
	ui.spinBoxColumns->setRange(1,99);
	connect(ui.spinBoxColumns, SIGNAL(valueChanged(int)),this, SLOT(NewColumns(int)));

	ui.comboAlignment->insertItem(0,tr("Center"));
	ui.comboAlignment->insertItem(1,tr("Left"));
	ui.comboAlignment->insertItem(2,tr("Right"));

	ui.comboEnvironment->insertItem(0,"array");
	ui.comboEnvironment->insertItem(1,"matrix");
	ui.comboEnvironment->insertItem(2,"pmatrix");
	ui.comboEnvironment->insertItem(3,"bmatrix");
	ui.comboEnvironment->insertItem(4,"vmatrix");
	ui.comboEnvironment->insertItem(5,"Vmatrix");
	setWindowTitle(tr("Quick Array"));
}

ArrayDialog::~ArrayDialog() {
}
void ArrayDialog::NewRows(int num) {
	ui.tableWidget->setRowCount(num);
}
void ArrayDialog::NewColumns(int num) {
	ui.tableWidget->setColumnCount(num);
}

