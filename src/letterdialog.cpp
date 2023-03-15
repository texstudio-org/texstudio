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

#include "letterdialog.h"
#include "utilsUI.h"

LetterDialog::LetterDialog(QWidget *parent, const char *name)
	: QDialog(parent)
{
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);
	UtilsUi::resizeInFontHeight(this, 24, 7);

	ui.comboBoxPt->insertItem(0, "10pt");
	ui.comboBoxPt->insertItem(1, "11pt");
	ui.comboBoxPt->insertItem(2, "12pt");

	ui.comboBoxPaper->insertItem(0, "a4paper");
	ui.comboBoxPaper->insertItem(1, "a5paper");
	ui.comboBoxPaper->insertItem(2, "b5paper");
	ui.comboBoxPaper->insertItem(3, "letterpaper");
	ui.comboBoxPaper->insertItem(4, "legalpaper");
	ui.comboBoxPaper->insertItem(5, "executivepaper");

	ui.comboBoxEncoding->insertItem(1, "latin1");
	ui.comboBoxEncoding->insertItem(2, "latin2");
	ui.comboBoxEncoding->insertItem(3, "latin3");
	ui.comboBoxEncoding->insertItem(4, "latin5");
	ui.comboBoxEncoding->insertItem(5, "utf8");
	ui.comboBoxEncoding->insertItem(6, "utf8x");
	ui.comboBoxEncoding->insertItem(7, "ascii");
	ui.comboBoxEncoding->insertItem(8, "decmulti");
	ui.comboBoxEncoding->insertItem(9, "cp850");
	ui.comboBoxEncoding->insertItem(10, "cp852");
	ui.comboBoxEncoding->insertItem(11, "cp437");
	ui.comboBoxEncoding->insertItem(12, "cp437de");
	ui.comboBoxEncoding->insertItem(13, "cp865");
	ui.comboBoxEncoding->insertItem(14, "applemac");
	ui.comboBoxEncoding->insertItem(15, "next");
	ui.comboBoxEncoding->insertItem(16, "ansinew");
	ui.comboBoxEncoding->insertItem(17, "cp1252");
	ui.comboBoxEncoding->insertItem(18, "cp1250");
	ui.comboBoxEncoding->insertItem(19, "NONE");
	ui.comboBoxEncoding->setCurrentIndex(4);

	ui.checkBox->setChecked(true);
	setWindowTitle(tr("Quick Letter"));
}

LetterDialog::~LetterDialog()
{
}
