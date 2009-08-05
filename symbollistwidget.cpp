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

#include "symbollistwidget.h"
#include "icondelegate.h"

SymbolListWidget :: SymbolListWidget(QWidget *parent, int page) : QTableWidget(parent) {
	setItemDelegate(new IconDelegate(this));
	listOfItems.clear();
	QString icon_name;
	setShowGrid(true);
	verticalHeader()->hide();
	horizontalHeader()->hide();
	setIconSize(QSize(32,32));
	setSelectionMode(QAbstractItemView::SingleSelection);
	switch (page) {
	case 0: {
		setColumnCount(4);
		setRowCount(57);
		for (uint j = 0; j < 57; ++j) setRowHeight(j,36);
		setColumnWidth(0,36);
		setColumnWidth(1,36);
		setColumnWidth(2,36);
		setColumnWidth(3,36);
		for (uint i = 0; i <= 225; ++i) {
			icon_name=":/symbols/img"+QString::number(i+1)+".png";
			QTableWidgetItem* item= new QTableWidgetItem();
			item->setIcon(QIcon(icon_name));
			item->setText(code[i]);
			item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			item->setData(Qt::UserRole,0);
			setItem(i/4,i%4,item);
			listOfItems << item;
		}
	}
	break;
	case 1: {
		setColumnCount(4);
		setRowCount(17);
		for (uint j = 0; j < 17; ++j) setRowHeight(j,36);
		setColumnWidth(0,36);
		setColumnWidth(1,36);
		setColumnWidth(2,36);
		setColumnWidth(3,36);
		for (uint i = 247; i <= 313; ++i) {
			icon_name=":/symbols/img"+QString::number(i+1)+".png";
			QTableWidgetItem* item= new QTableWidgetItem();
			item->setIcon(QIcon(icon_name));
			item->setText(code[i]);
			item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			item->setData(Qt::UserRole,0);
			setItem((i-247)/4,(i-247)%4,item);
			listOfItems << item;
		}
	}
	break;
	case 2: {
		setColumnCount(4);
		setRowCount(15);
		for (uint j = 0; j < 15; ++j) setRowHeight(j,36);
		setColumnWidth(0,36);
		setColumnWidth(1,36);
		setColumnWidth(2,36);
		setColumnWidth(3,36);
		for (uint i = 314; i <= 371; ++i) {
			icon_name=":/symbols/img"+QString::number(i+1)+".png";
			QTableWidgetItem* item= new QTableWidgetItem();
			item->setIcon(QIcon(icon_name));
			item->setText(code[i]);
			item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			item->setData(Qt::UserRole,0);
			setItem((i-314)/4,(i-314)%4,item);
			listOfItems << item;
		}
	}
	break;
	case 3: {
		setColumnCount(4);
		setRowCount(6);
		for (uint j = 0; j < 6; ++j) setRowHeight(j,36);
		setColumnWidth(0,36);
		setColumnWidth(1,36);
		setColumnWidth(2,36);
		setColumnWidth(3,36);
		for (uint i = 226; i <= 246; ++i) {
			icon_name=":/symbols/img"+QString::number(i+1)+".png";
			QTableWidgetItem* item= new QTableWidgetItem();
			item->setIcon(QIcon(icon_name));
			item->setText(code[i]);
			item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			item->setData(Qt::UserRole,0);
			setItem((i-226)/4,(i-226)%4,item);
			listOfItems << item;
		}
	}
	break;
	case 4: {
		setColumnCount(4);
		setRowCount(10);
		for (uint j = 0; j < 10; ++j) setRowHeight(j,36);
		setColumnWidth(0,36);
		setColumnWidth(1,36);
		setColumnWidth(2,36);
		setColumnWidth(3,36);
		for (uint i = 0; i <= 39; ++i) {
			icon_name=":/symbols/img"+QString::number(i+1)+"greek.png";
			QTableWidgetItem* item= new QTableWidgetItem();
			item->setIcon(QIcon(icon_name));
			item->setText(code[i+372]);
			item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			item->setData(Qt::UserRole,0);
			setItem(i/4,i%4,item);
			listOfItems << item;
		}
	}
	break;
	case 5: {
		setColumnCount(4);
		setRowCount(3);
		for (uint j = 0; j < 3; ++j) setRowHeight(j,36);
		setColumnWidth(0,36);
		setColumnWidth(1,36);
		setColumnWidth(2,36);
		setColumnWidth(3,36);
	}
	break;
	}

}
void SymbolListWidget::SetUserPage(usercodelist ulist) {
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

void SymbolListWidget::resizeEvent ( QResizeEvent * event )
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

