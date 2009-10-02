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
	setShowGrid(true);
	verticalHeader()->hide();
	horizontalHeader()->hide();
	setIconSize(QSize(32,32));
	setSelectionMode(QAbstractItemView::SingleSelection);

	QStringList files;
	if(!SymbolList.isEmpty() && !SymbolList.startsWith("!")) 
		files=findResourceFiles("symbols/"+SymbolList, "img*.png");

	QStringList fullNames;
	foreach (const QString& partName, files) fullNames << SymbolList+"/"+partName;

	loadSymbols(fullNames,Map);
}
QString SymbolGridWidget::getCurrentSymbol(){
	QTableWidgetItem * cur=currentItem();
	if (!cur) return QString();
	return cur->data(Qt::UserRole+2).toString();
}
void SymbolGridWidget::loadSymbols(const QStringList& fileNames, QVariantMap *Map){	
	foreach(QTableWidgetItem* elem,listOfItems){
		takeItem(row(elem),column(elem));
		delete(elem);
	}
	listOfItems.clear();
	setColumnCount(4);
	int rows=fileNames.isEmpty()?3:(fileNames.size()/4+1);
	setRowCount(rows);
	for (int j = 0; j < rows; ++j) setRowHeight(j,36);
	for(int j=0;j < 4;++j) setColumnWidth(j,36);
	int cols=columnCount();
	
	countOfItems=fileNames.size();
	
	for (int i = 0; i < fileNames.size(); ++i) {
		QString iconName=fileNames.at(i);
		QString fileName=findResourceFile("symbols/"+iconName);
		QTableWidgetItem* item= new QTableWidgetItem();
		QImage img=QImage(fileName);
		item->setIcon(QIcon(fileName));
		item->setText(img.text("Command"));
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		if(Map) {
			item->setData(Qt::UserRole,Map->value(img.text("Command"),0).toInt());
			Map->insert(img.text("Command"),0);
		} else item->setData(Qt::UserRole,0);
		item->setData(Qt::UserRole+2,iconName);
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

			for( int j = 0; j < pkgs.count() ; j++ )
			{
				if(j>0) label += "\n";
				if( j < args.count() && !args[j].isEmpty())
					label = label + "[" + args[j] + "]" + pkgs[j];
				else
					label = label + pkgs[j] ;
			}
		}
		item->setToolTip(label);
		setItem(i/cols,i%cols,item);
		listOfItems << item;
	}
}


void SymbolGridWidget::resizeEvent ( QResizeEvent * event )
{
	//qDebug("%d",event->size());
	QTableWidget::resizeEvent(event);
	// remove remaining old items
	//	qDebug("1");
	int numberOfColumns=columnCount();
	for(int i=0;i<rowCount()*columnCount();i++){
		//delete(item(i/numberOfColumns,i%numberOfColumns));
		takeItem(i/numberOfColumns,i%numberOfColumns);
	}
	// add items with adapted number of columns
	numberOfColumns=event->size().width()/36;
	//	qDebug("1.5");
	setColumnCount(numberOfColumns);
	setRowCount(countOfItems/numberOfColumns+1);
	for(int j = 0; j < countOfItems/numberOfColumns+1; ++j) setRowHeight(j,36);
	for(int j=0;j < numberOfColumns;++j) setColumnWidth(j,36);

	//	qDebug(qPrintable(QString("2:%1").arg((int)this)));
	for (int i = 0; i < listOfItems.size(); ++i) {
		//	qDebug(qPrintable(QString("%1:%2 %3").arg(listOfItems[i]->text()).arg(listOfItems[i]->column()).arg((int)listOfItems[i]->tableWidget())));
		if (!listOfItems[i]->tableWidget()) //the items aren't properly removed if the number of rows changes or the number of cols decrease (latter only if the resizeEvent is propagated to the super class) TODO: fix this correctly
			setItem(i/numberOfColumns,i%numberOfColumns,listOfItems[i]);
	}
		//qDebug("3");
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
	countOfItems=listOfItems.count();
}
