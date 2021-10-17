/***************************************************************************
 *   copyright       : (C) 2003-2013 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef Header_QuickBeamer_Dialog
#define Header_QuickBeamer_Dialog

#include "ui_quickbeamerdialog.h"
#include <QLabel>

class ConfigManagerInterface;
class QuickBeamerDialog : public QDialog
{
	Q_OBJECT

public:
	QuickBeamerDialog(QWidget *parent = 0, const QString &name = 0);
	~QuickBeamerDialog();
	Ui::QuickBeamerDialog ui;
	QLabel *labelImage;

	QString getNewDocumentText();

	static QString document_encoding;
private:
	static ConfigManagerInterface *configManagerInterface;
public:
	static void registerOptions(ConfigManagerInterface &configManager);
public slots:
	void Init();
private slots:
	void updatePreview(const QString &theme);
};


#endif
