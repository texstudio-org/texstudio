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

#ifndef Header_FileChooser
#define Header_FileChooser

#include "ui_filechooser.h"

class FileChooser : public QDialog
{
	Q_OBJECT

public:
	FileChooser(QWidget *parent = 0, QString name = "");
	Ui::FileChooser ui;
	Q_INVOKABLE QString fileName() const;
	QString filter, dir;

public slots:
	void setDir(const QString &di);
	void setFilter(const QString &fil);

signals:
	void fileNameChanged(const QString &);

private slots:
	void chooseFile();

};

#endif
