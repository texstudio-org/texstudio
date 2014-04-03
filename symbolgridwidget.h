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

#ifndef SYMBOLGRIDWIDGET_H
#define SYMBOLGRIDWIDGET_H

#include "mostQtHeaders.h"
#include <QTableWidgetItem>

typedef QList<QTableWidgetItem*> usercodelist;

Q_DECLARE_METATYPE(QTableWidgetItem*)

class SymbolGridWidget : public QTableWidget {
	Q_OBJECT

public:
	SymbolGridWidget(QWidget *parent, QString SymbolList, QVariantMap *Map=0);
	~SymbolGridWidget();
	QString getCurrentSymbol(); //returns category/fileName.png
public slots:
	void SetUserPage(usercodelist ulist);
	void loadSymbols(const QStringList& fileNames, QVariantMap *Map=0);
protected:
	void resizeEvent ( QResizeEvent * event );

private:
	QList<QTableWidgetItem*>listOfItems;
	int countOfItems; //not necessary equal to listOfItems.size() while the symbols are added

	bool mLoadedSymbols;
	QVariantMap *mMap;
	QString mSymbolList;
};

#endif
