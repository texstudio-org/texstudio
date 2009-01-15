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

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include "ui_configdialog.h"

#include <QListWidgetItem>

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigDialog(QWidget* parent = 0);
	~ConfigDialog();
Ui::ConfigDialog ui;

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private slots:
void createIcons();
void browseAspell();
void configureColorMath();
void configureColorCommand();
void configureColorKeyword();
void browseLatex();
void browseDvips();
void browseBibtex();
void browseMakeindex();
void browseDviviewer();
void browsePsviewer();
void browsePdflatex();
void browseDvipdfm();
void browsePs2pdf();
void browsePdfviewer();
void browseMetapost();
void browseGhostscript();
};

#endif
