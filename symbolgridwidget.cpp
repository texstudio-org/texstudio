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

#include "symbolgridwidget.h"
#include "icondelegate.h"
#include "smallUsefulFunctions.h"

SymbolGridWidget :: SymbolGridWidget(QWidget *parent, QString SymbolList, QVariantMap *Map) : QTableWidget(parent) {
	listOfItems.clear();
	setItemDelegate(new IconDelegate(this));
	QString icon_name;
	setShowGrid(true);
	verticalHeader()->hide();
	horizontalHeader()->hide();
	setIconSize(QSize(32,32));
	setSelectionMode(QAbstractItemView::SingleSelection);
	setColumnCount(4);
	int rows;
	QStringList files;
	if(SymbolList.isEmpty()) rows=3;
	else {
		files=findResourceFiles("symbols/"+SymbolList, "img*.png");
		rows=files.size()/4+1;
	}
	setRowCount(rows);
	for (int j = 0; j < rows; ++j) setRowHeight(j,36);
	for(int j=0;j < 4;++j) setColumnWidth(j,36);
	if(SymbolList.isEmpty()) return;
	for (int i = 0; i < files.size(); ++i) {
		icon_name=files.at(i);
		QTableWidgetItem* item= new QTableWidgetItem();
		QImage img=QImage(findResourceFile("symbols/"+SymbolList+"/"+icon_name));
		item->setIcon(QIcon(findResourceFile("symbols/"+SymbolList+"/"+icon_name)));
		item->setText(img.text("Command"));
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		if(Map) {
			item->setData(Qt::UserRole,Map->value(img.text("Command"),0).toInt());
			Map->insert(img.text("Command"),0);
		} else item->setData(Qt::UserRole,0);
		QString label;
		QStringList args,pkgs;

		label = tr("Command: ") + img.text("Command");



		QRegExp rePkgs("(?:\\[(.*)\\])?\\{(.*)\\}");

		args.clear();
		pkgs.clear();

		QString text = img.text("Packages");

		if( rePkgs.indexIn(text) != -1 )
		{
			args = rePkgs.cap(1).split(",");
			pkgs = rePkgs.cap(2).split(",");
		}
		if( pkgs.count() > 0 )
		{
			if(pkgs.count() == 1)
				label += "\n" + tr("Package: ");
			else
				label += "\n" + tr("Packages: ");

			for( int i = 0; i < pkgs.count() ; i++ )
			{
				if(i>0) label += "\n";
				if( i < args.count() && !args[i].isEmpty())
					label = label + "[" + args[i] + "]" + pkgs[i];
				else
					label = label + pkgs[i] ;
			}
		}
		item->setToolTip(label);
		setItem(i/4,i%4,item);
		listOfItems << item;
	}
}


void SymbolGridWidget::resizeEvent ( QResizeEvent * event )
{
	//qDebug("%d",event->size());
	QTableWidget::resizeEvent(event);
	// remove remaining old items
	int numberOfColumns=columnCount();
	for(int i=0;i<rowCount()*columnCount();i++){
		//delete(item(i/numberOfColumns,i%numberOfColumns));
		takeItem(i/numberOfColumns,i%numberOfColumns);
	}
	// add items with adapted number of columns
	numberOfColumns=event->size().width()/36;
	setColumnCount(numberOfColumns);
	setRowCount(listOfItems.size()/numberOfColumns+1);
	for(int j = 0; j < listOfItems.size()/numberOfColumns+1; ++j) setRowHeight(j,36);
	for(int j=0;j < numberOfColumns;++j) setColumnWidth(j,36);

	for (int i = 0; i < listOfItems.size(); ++i) {
		setItem(i/numberOfColumns,i%numberOfColumns,listOfItems[i]);
	}

}

void SymbolGridWidget::SetUserPage(usercodelist ulist) {
	foreach(QTableWidgetItem* elem,listOfItems){
		takeItem(row(elem),column(elem));
		delete(elem);
	}
	listOfItems.clear();
	int numberOfColumns=columnCount();
	//setColumnCount(numberOfColumns);
	setRowCount(12/numberOfColumns);
	int i=0;
	foreach(QTableWidgetItem* elem,ulist){
		QTableWidgetItem* item= elem->clone();
		item->setData(Qt::UserRole,-1);
		item->setData(Qt::UserRole+1,QVariant::fromValue(elem));
		setItem(i/numberOfColumns,i%numberOfColumns,item);
		listOfItems << item;
		i++;
	}

}
