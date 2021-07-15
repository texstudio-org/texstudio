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

#include "filechooser.h"
#include "filedialog.h"

#include "smallUsefulFunctions.h"

FileChooser::FileChooser(QWidget *parent, QString name)
	: QDialog(parent)
{
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);
	UtilsUi::resizeInFontHeight(this, 31, 8);

    connect(ui.lineEdit, SIGNAL(textChanged(const QString&)), this, SIGNAL(fileNameChanged(const QString&)));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(chooseFile()));
	ui.pushButton->setIcon(getRealIcon("document-open"));
	setWindowTitle(name);
}

void FileChooser::setDir(const QString &di)
{
	dir = di;
}

void FileChooser::setFilter(const QString &fil)
{
	filter = fil;
}

QString FileChooser::fileName() const
{
	return ui.lineEdit->text();
}

void FileChooser::chooseFile()
{
	QString fn;
	fn = FileDialog::getOpenFileName(this, tr("Select a File"), dir, filter);
	if (!fn.isEmpty()) {
		ui.lineEdit->setText(fn);
		emit fileNameChanged(fn);
	}
}

