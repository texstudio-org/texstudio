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

SymbolGridWidget :: SymbolGridWidget(QWidget *parent, QString SymbolList) : QTableWidget(parent) {
	listOfItems.clear();
	setItemDelegate(new IconDelegate(this));
	QString icon_name;
	setShowGrid(true);
	verticalHeader()->hide();
	horizontalHeader()->hide();
	setIconSize(QSize(32,32));
	setSelectionMode(QAbstractItemView::SingleSelection);
	QStringList files=findResourceFiles("symbols/"+SymbolList, "img*.png");
	setColumnCount(4);
	setRowCount(files.length()/4+1);
	for (int j = 0; j < (files.length()/4+1); ++j) setRowHeight(j,36);
	for(int j=0;j < 4;++j) setColumnWidth(j,36);
	for (int i = 0; i < files.length(); ++i) {
		icon_name=files.at(i);
		QTableWidgetItem* item= new QTableWidgetItem();
		QImage img=QImage(findResourceFile("symbols/"+SymbolList+"/"+icon_name));
		item->setIcon(QIcon(findResourceFile("symbols/"+SymbolList+"/"+icon_name)));
		item->setText(img.text("Command")+";"+QString::number(i));
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
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
	setRowCount(listOfItems.length()/numberOfColumns+1);
	for(int j = 0; j < listOfItems.length()/numberOfColumns+1; ++j) setRowHeight(j,36);
	for(int j=0;j < numberOfColumns;++j) setColumnWidth(j,36);

	for (int i = 0; i < listOfItems.length(); ++i) {
		setItem(i/numberOfColumns,i%numberOfColumns,listOfItems[i]);
	}

}
