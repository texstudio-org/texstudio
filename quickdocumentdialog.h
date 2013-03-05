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

#ifndef QUICKDOCUMENTDIALOG_H
#define QUICKDOCUMENTDIALOG_H

#include "mostQtHeaders.h"

#include "ui_quickdocumentdialog.h"

class ConfigManagerInterface;
struct GeometryOption;
class QuickDocumentDialog : public QDialog  {
	Q_OBJECT
public:
	QuickDocumentDialog(QWidget *parent=0, const QString& name=0);
	~QuickDocumentDialog();
	Ui::QuickDocumentDialog ui;


	QString getNewDocumentText();


	static QString document_encoding;
private:
	static QStringList otherClassList, otherPaperList, otherEncodingList, otherOptionsList;
	static QString document_class, typeface_size, paper_size, author;
	static bool ams_packages, makeidx_package, graphicx_package;
	static ConfigManagerInterface* configManagerInterface;
public:
	static void registerOptions(ConfigManagerInterface& configManager);
public slots:
	void Init();
	virtual void accept();

	void geometryUnitsChanged();
	void geometryValuesChanged();
private slots:
	void addUserClass();
	void addUserPaper();
	void addUserEncoding();
	void addUserOptions();
};


#endif
