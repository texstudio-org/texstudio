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

#include "ui_quickdocumentdialog.h"
#include "addoptiondialog.h"



class QuickDocumentDialog : public QDialog  {
	Q_OBJECT
public:
	QuickDocumentDialog(QWidget *parent=0, const char *name=0);
	~QuickDocumentDialog();
	Ui::QuickDocumentDialog ui;

public:

	QStringList otherClassList, otherPaperList, otherEncodingList, otherOptionsList;

public slots:
	void Init();
private slots:
	void addUserClass();
	void addUserPaper();
	void addUserEncoding();
	void addUserOptions();
private :
	AddOptionDialog *dlg;
};


#endif
