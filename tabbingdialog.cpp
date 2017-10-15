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

#include "tabbingdialog.h"
#include "utilsUI.h"

TabbingDialog::TabbingDialog(QWidget *parent, const char *name)
	: QDialog(parent)
{
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);
	UtilsUi::resizeInFontHeight(this, 23, 12);

	ui.spinBoxColumns->setValue(2);
	ui.spinBoxColumns->setRange(2, 99);

	ui.spinBoxRows->setValue(1);
	ui.spinBoxRows->setRange(1, 99);
	setWindowTitle(tr("Quick Tabbing"));
}

TabbingDialog::~TabbingDialog()
{
}
