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
#include "utilsUI.h"

ArrayDialog::ArrayDialog(QWidget *parent, const char *name)
		:QDialog(parent) {
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);
	UtilsUi::resizeInFontHeight(this, 36, 30);

	ui.tableWidget->setRowCount(2);
	ui.tableWidget->setColumnCount(2);

	ui.spinBoxRows->setValue(2);
	ui.spinBoxRows->setRange(1, 99);
	connect(ui.spinBoxRows, SIGNAL(valueChanged(int)), this, SLOT(newRows(int)));

	ui.spinBoxColumns->setValue(2);
	ui.spinBoxColumns->setRange(1,99);
	connect(ui.spinBoxColumns, SIGNAL(valueChanged(int)), this, SLOT(newColumns(int)));

	ui.comboAlignment->insertItem(0, tr("Center"), 'c');
	ui.comboAlignment->insertItem(1, tr("Left"), 'l');
	ui.comboAlignment->insertItem(2, tr("Right"), 'r');

	ui.comboEnvironment->insertItem(0, "array");
	ui.comboEnvironment->insertItem(1, "matrix");
	ui.comboEnvironment->insertItem(2, "pmatrix");
	ui.comboEnvironment->insertItem(3, "bmatrix");
	ui.comboEnvironment->insertItem(4, "Bmatrix");
	ui.comboEnvironment->insertItem(5, "vmatrix");
	ui.comboEnvironment->insertItem(6, "Vmatrix");
	setWindowTitle(tr("Quick Array"));
}

ArrayDialog::~ArrayDialog() {
}

QString ArrayDialog::getLatexText()
{
	int nrows = ui.spinBoxRows->value();
	int ncols = ui.spinBoxColumns->value();
	QString env = ui.comboEnvironment->currentText();
	QString text = QString("\\begin{") + env + "}";
	if (env == "array") {
		QChar alignChar = ui.comboAlignment->itemData(ui.comboAlignment->currentIndex()).toChar();
		text += "{" + QString(ncols, alignChar) + "}";
	}
	text += QString("\n");
	for (int i = 0; i < nrows - 1; i++) {
		for (int j = 0; j < ncols - 1; j++) {
			QTableWidgetItem *item = ui.tableWidget->item(i, j);
			if (item)
				text += item->text();
			text += QString(" & ");
		}
		QTableWidgetItem *item = ui.tableWidget->item(i, ncols - 1);
		if (item)
			text += item->text();
		text += QString(" \\\\\n");
	}
	for (int j = 0; j < ncols - 1; j++) {
		QTableWidgetItem *item = ui.tableWidget->item(nrows - 1, j);
		if (item)
			text += item->text();
		text += QString(" & ");
	}
	QTableWidgetItem *item = ui.tableWidget->item(nrows - 1, ncols - 1);
	if (item)
		text += item->text();
	text += QString("\n\\end{") + env + "}";
	return text;
}

void ArrayDialog::newRows(int num) {
	ui.tableWidget->setRowCount(num);
}

void ArrayDialog::newColumns(int num) {
	ui.tableWidget->setColumnCount(num);
}
