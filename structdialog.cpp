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

#include "structdialog.h"

StructDialog::StructDialog(QWidget *parent, QString name)
		: QDialog(parent) {
	setModal(true);
	ui.setupUi(this);
	setWindowTitle(name);
}

StructDialog::~StructDialog() {
}


