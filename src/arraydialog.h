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

#ifndef Header_Array_Dialog
#define Header_Array_Dialog

#include "mostQtHeaders.h"
#include "ui_arraydialog.h"

class ArrayDialog : public QDialog
{
	Q_OBJECT

public:
    ArrayDialog(QWidget *parent = nullptr, const char *name = 0);
	~ArrayDialog();
	Ui::ArrayDialog ui;
	QString getLatexText();

private:
	QStringList packageList = {"latex", "amsmath", "mathtools"};
	QStringList environmentList = {"array", "alignedat", "matrix", "pmatrix", "bmatrix", "Bmatrix", "vmatrix", "Vmatrix"};
	QList<Qt::AlignmentFlag> alignList = {Qt::AlignHCenter, Qt::AlignLeft, Qt::AlignRight};
	QStringList alignTextList = {tr("Center"), tr("Left"), tr("Right")};
	QList<int> arrayAligns;
	void addEmptyTableItems();
	void addEmptyColumnItems(int col);
	void setComboEnv(QString package);
	void setColAlignments();
	void setColAlignment(int col, Qt::AlignmentFlag align);
	int currentColAlignIndex(int col);
	QStringList getEnvBeginEndStatements();
	QString getFactoredAlignments();
	QString squash(QString part, QString align);

protected slots:
	void newRows(int num);
	void newColumns(int num);
    void keyPressEvent(QKeyEvent *event);
	void setTitle();
	void slotEnvironmentChanged();
	void slotCurrentCellChanged(int row, int col);
	void slotAlignmentChanged(int ix);
	void slotPackageChanged();
};

#endif
