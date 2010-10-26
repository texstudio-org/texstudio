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

#include "mostQtHeaders.h"
 
#include "insertgraphics.h"


InsertGraphics::InsertGraphics(QWidget *parent, QString name)
		: QDialog(parent) {
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);
	connect(ui.lineEdit, SIGNAL(textChanged(const QString &)), this, SIGNAL(fileNameChanged(const QString &)));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(chooseFile()));
	connect(ui.cbFloat, SIGNAL(stateChanged(int)), this, SLOT(floatStateChanged(int)));
	setWindowTitle(tr("Insert Graphics","Wizard"));
}

void InsertGraphics::setDir(const QString &di) {
	dir=di;
}

void InsertGraphics::setFilter(const QString &fil) {
	filter=fil;
}
QString InsertGraphics::fileName() const {
	return ui.lineEdit->text();
}

void InsertGraphics::chooseFile() {
	QString fn;
	fn =QFileDialog::getOpenFileName(this,tr("Select a File","Wizard"),dir,filter);
	if (!fn.isEmpty()) {
		ui.lineEdit->setText(fn);
		emit fileNameChanged(fn);
	}
}

void InsertGraphics::floatStateChanged(int state){
    if(state==Qt::Checked){
	ui.cbBottom->setEnabled(true);
	ui.cbTop->setEnabled(true);
	ui.cbPage->setEnabled(true);
	ui.cbHere->setEnabled(true);
    }else{
	ui.cbBottom->setEnabled(false);
	ui.cbTop->setEnabled(false);
	ui.cbPage->setEnabled(false);
	ui.cbHere->setEnabled(false);
    }
}

