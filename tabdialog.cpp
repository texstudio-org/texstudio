/***************************************************************************
 *   copyright	  : (C) 2003-2011 by Pascal Brachet				 *
 *   http://www.xm1math.net/texmaker/							   *
 *														   *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or	*
 *   (at your option) any later version.							*
 *														   *
 ***************************************************************************/

#include "tabdialog.h"
//#include <QDebug>


TabDialog::TabDialog(QWidget *parent, const char *name)
	:QDialog( parent)
{
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);

	colData col;
	col.alignment=0;
	col.leftborder=0;
	liData li;
	li.topborder=true;
	li.merge=false;
	li.mergefrom=1;
	li.mergeto=1;
	colDataList.clear();
	liDataList.clear();
	for ( int j = 0; j < 99; ++j )
	{
		colDataList.append(col);
		liDataList.append(li);
	}
	ui.tableWidget->setRowCount( 2 );
	ui.tableWidget->setColumnCount( 2 );

	ui.spinBoxRows->setValue(2);
	ui.spinBoxRows->setRange(1,99);
	connect( ui.spinBoxRows, SIGNAL(valueChanged(int)),this, SLOT(NewRows(int)));


	ui.spinBoxColumns->setValue(2);
	ui.spinBoxColumns->setRange(1,99);
	connect( ui.spinBoxColumns, SIGNAL(valueChanged(int)),this, SLOT(NewColumns(int)));

	ui.spinBoxNumCol->setRange(1,2);
	ui.spinBoxNumLi->setRange(1,2);
	ui.spinBoxSpanFrom->setRange(1,1);
	ui.spinBoxSpanTo->setRange(2,2);

	ui.comboBoxColAl->insertItem(0, tr("Center", "tabular alignment"));
	ui.comboBoxColAl->insertItem(1, tr("Left", "tabular alignment"));
	ui.comboBoxColAl->insertItem(2, tr("Right", "tabular alignment"));
	ui.comboBoxColAl->insertItem(3, tr("p{} (fixed width - justified)", "tabular alignment"));
	ui.comboBoxColAl->insertItem(4, tr("p{} (fixed width - left)", "tabular alignment"));
	ui.comboBoxColAl->insertItem(5, tr("p{} (fixed width - center)", "tabular alignment"));
	ui.comboBoxColAl->insertItem(6, tr("p{} (fixed width - right)", "tabular alignment"));
	ui.comboBoxColAl->setCurrentIndex(0);

	ui.comboLeftBorder->insertItem(0, "|");
	ui.comboLeftBorder->insertItem(1, "||");
	ui.comboLeftBorder->insertItem(2, tr("None", "tabular left border"));
	ui.comboLeftBorder->insertItem(3, tr("@{text}", "tabular left border"));
	ui.comboLeftBorder->setCurrentIndex(0);

	ui.comboBoxEndBorder->insertItem(0, "|");
	ui.comboBoxEndBorder->insertItem(1, "||");
	ui.comboBoxEndBorder->insertItem(2, tr("None", "tabular right border"));
	ui.comboBoxEndBorder->insertItem(3, tr("@{text}", "tabular right border"));
	ui.comboLeftBorder->setCurrentIndex(0);

	ui.spinBoxNumCol->setValue(1);
	ui.spinBoxNumLi->setValue(1);

	ui.checkBoxBorderTop->setChecked(true);
	ui.checkBoxSpan->setChecked(false);
	ui.spinBoxSpanFrom->setValue(1);
	ui.spinBoxSpanTo->setValue(1);
	ui.spinBoxSpanFrom->setEnabled(false);
	ui.spinBoxSpanTo->setEnabled(false);
	ui.checkBoxBorderBottom->setChecked(true);
	ui.checkBoxMargin->setChecked(false);

	connect(ui.checkBoxSpan, SIGNAL(toggled(bool)),this, SLOT(updateSpanStatus(bool)));

	connect(ui.pushButtonColumns, SIGNAL(clicked()), this, SLOT(applytoAllColumns()));
	connect(ui.pushButtonLines, SIGNAL(clicked()), this, SLOT(applytoAllLines()));

	connect( ui.spinBoxNumCol, SIGNAL(valueChanged(int)),this, SLOT(showColSettings(int)));
	connect( ui.spinBoxNumLi, SIGNAL(valueChanged(int)),this, SLOT(showRowSettings(int)));

	connect(ui.comboBoxColAl, SIGNAL(currentIndexChanged(int)),this, SLOT(updateColSettings()));
	connect(ui.comboLeftBorder, SIGNAL(currentIndexChanged(int)),this, SLOT(updateColSettings()));

	connect(ui.checkBoxBorderTop, SIGNAL(toggled(bool)),this, SLOT(updateRowSettings()));
	connect(ui.checkBoxSpan, SIGNAL(toggled(bool)),this, SLOT(updateRowSettings()));
	connect(ui.spinBoxSpanFrom, SIGNAL(valueChanged(int)),this, SLOT(updateRowSettings()));
	connect(ui.spinBoxSpanTo, SIGNAL(valueChanged(int)),this, SLOT(updateRowSettings()));

	connect(ui.comboBoxEndBorder, SIGNAL(currentIndexChanged(int)),this, SLOT(updateTableWidget()));

	connect(ui.tableWidget, SIGNAL(cellClicked(int,int)),this, SLOT(showColRowSettings(int,int)));
	connect(ui.tableWidget, SIGNAL(currentCellChanged(int,int,int,int)),this, SLOT(showColRowSettings(int,int)));

	setWindowTitle(tr("Quick Tabular"));
	updateTableWidget();
}

TabDialog::~TabDialog(){
}
void TabDialog::NewRows(int num)
{
	ui.tableWidget->setRowCount( num );
	ui.spinBoxNumLi->setRange(1,num);
	updateTableWidget();
}

void TabDialog::NewColumns(int num)
{
	ui.tableWidget->setColumnCount( num );
	ui.spinBoxNumCol->setRange(1,num);
	if (num>1)
	{
		ui.spinBoxSpanFrom->setRange(1,num-1);
		ui.spinBoxSpanTo->setRange(2,num);
	}
	else
	{
		ui.spinBoxSpanFrom->setRange(1,num-1);
		ui.spinBoxSpanTo->setRange(2,num);
	}
	updateTableWidget();
}

void TabDialog::updateSpanStatus(bool enabled)
{
	ui.spinBoxSpanFrom->setEnabled(enabled);
	ui.spinBoxSpanTo->setEnabled(enabled);
	updateTableWidget();
}

void TabDialog::applytoAllColumns()
{
	colData col;
	col.alignment=ui.comboBoxColAl->currentIndex();
	col.leftborder=ui.comboLeftBorder->currentIndex();
	for ( int i = 0; i < 99; ++i )
	{
		colDataList.replace(i,col);
	}
	updateTableWidget();
}

void TabDialog::applytoAllLines()
{
	liData li;
	li.topborder=ui.checkBoxBorderTop->isChecked();
	li.merge=ui.checkBoxSpan->isChecked();
	li.mergefrom=ui.spinBoxSpanFrom->value();
	li.mergeto=ui.spinBoxSpanTo->value();
	if (li.mergefrom>li.mergeto)
	{
		li.mergefrom=1;
		li.mergeto=1;
	}
	for ( int i = 0; i < 99; ++i )
	{
		liDataList.replace(i,li);
	}
	updateTableWidget();
}

void TabDialog::updateColSettings()
{
	int i=ui.spinBoxNumCol->value()-1;
	colData col;
	col.alignment=ui.comboBoxColAl->currentIndex();
	col.leftborder=ui.comboLeftBorder->currentIndex();
	colDataList.replace(i,col);
	updateTableWidget();
	//qDebug() << "change" << i << colDataList.at(i).alignment << colDataList.at(i).leftborder;
}

void TabDialog::updateRowSettings()
{
	int i=ui.spinBoxNumLi->value()-1;
	liData li;
	li.topborder=ui.checkBoxBorderTop->isChecked();
	li.merge=ui.checkBoxSpan->isChecked();
	li.mergefrom=ui.spinBoxSpanFrom->value();
	li.mergeto=ui.spinBoxSpanTo->value();
	if (li.mergefrom>li.mergeto)
	{
		li.mergefrom=1;
		li.mergeto=1;
	}
	liDataList.replace(i,li);
	updateTableWidget();
}

void TabDialog::showColSettings(int column)
{
	int i=column-1;
	if (i>=99) return;
	disconnect(ui.comboBoxColAl, SIGNAL(currentIndexChanged(int)),this, SLOT(updateColSettings()));
	disconnect(ui.comboLeftBorder, SIGNAL(currentIndexChanged(int)),this, SLOT(updateColSettings()));
	ui.comboBoxColAl->setCurrentIndex(colDataList.at(i).alignment);
	ui.comboLeftBorder->setCurrentIndex(colDataList.at(i).leftborder);
	connect(ui.comboBoxColAl, SIGNAL(currentIndexChanged(int)),this, SLOT(updateColSettings()));
	connect(ui.comboLeftBorder, SIGNAL(currentIndexChanged(int)),this, SLOT(updateColSettings()));
	updateTableWidget();
}

void TabDialog::showRowSettings(int row)
{
	int i=row-1;
	if (i>=99) return;
	disconnect(ui.checkBoxBorderTop, SIGNAL(toggled(bool)),this, SLOT(updateRowSettings()));
	disconnect(ui.checkBoxSpan, SIGNAL(toggled(bool)),this, SLOT(updateRowSettings()));
	disconnect(ui.spinBoxSpanFrom, SIGNAL(valueChanged(int)),this, SLOT(updateRowSettings()));
	disconnect(ui.spinBoxSpanTo, SIGNAL(valueChanged(int)),this, SLOT(updateRowSettings()));
	ui.checkBoxBorderTop->setChecked(liDataList.at(i).topborder);
	ui.checkBoxSpan->setChecked(liDataList.at(i).merge);
	ui.spinBoxSpanFrom->setValue(liDataList.at(i).mergefrom);
	ui.spinBoxSpanTo->setValue(liDataList.at(i).mergeto);
	connect(ui.checkBoxBorderTop, SIGNAL(toggled(bool)),this, SLOT(updateRowSettings()));
	connect(ui.checkBoxSpan, SIGNAL(toggled(bool)),this, SLOT(updateRowSettings()));
	connect(ui.spinBoxSpanFrom, SIGNAL(valueChanged(int)),this, SLOT(updateRowSettings()));
	connect(ui.spinBoxSpanTo, SIGNAL(valueChanged(int)),this, SLOT(updateRowSettings()));
	updateTableWidget();
}

void TabDialog::showColRowSettings(int row,int column)
{
	ui.spinBoxNumLi->setValue(row+1);
	ui.spinBoxNumCol->setValue(column+1);
}

void TabDialog::updateTableWidget()
{
	QStringList borderlist, alignlist;
	borderlist<< QString("|") << QString("||") << QString("") << QString("@{}");
	alignlist << QString("c") << QString("l") << QString("r") << QString("j p{}") << QString("l p{}") << QString("c p{}") << QString("r p{}");
	int y = ui.spinBoxRows->value();
	int x = ui.spinBoxColumns->value();
	QStringList headerList;
	QString tag="";
	for ( int j=0;j<x;j++)
	{
		tag=borderlist.at(colDataList.at(j).leftborder);
		tag+=alignlist.at(colDataList.at(j).alignment);
		if (j<x-1) headerList.append(tag);
	}
	tag+=borderlist.at(ui.comboBoxEndBorder->currentIndex());
	headerList.append(tag);
	ui.tableWidget->setHorizontalHeaderLabels(headerList);
	/*QColor selBlendColor=QColor("#0000FF");
QColor spancolor = selBlendColor.dark( 140 );
spancolor.setAlphaF( 0.2 );*/
	QTableWidgetItem *item, *new_item;
	QString content;
	for ( int i=0;i<y;i++)
	{
		for ( int j=0;j<x;j++)
		{
			item=ui.tableWidget->item(i,j);
			if (item)
			{
				content=item->text();
				new_item=new QTableWidgetItem();
				new_item->setText(content);
			}
			else
			{
				new_item=new QTableWidgetItem();
				new_item->setText("");
			}
			if (alignlist.at(colDataList.at(j).alignment).contains("l")) new_item->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
			else if (alignlist.at(colDataList.at(j).alignment).contains("r")) new_item->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
			else new_item->setTextAlignment(Qt::AlignCenter);
			if (ui.tableWidget->columnSpan(i,j)>1) ui.tableWidget->setSpan(i,j,1,1);
			/*    if ((liDataList.at(i).merge) && (liDataList.at(i).mergeto>liDataList.at(i).mergefrom)&& (j>=liDataList.at(i).mergefrom-1) && (j<=liDataList.at(i).mergeto-1))
	 {
	 new_item->setBackgroundColor(spancolor);
	 }*/
			ui.tableWidget->setItem(i,j,new_item);
		}
		if ((liDataList.at(i).merge) && (liDataList.at(i).mergeto>liDataList.at(i).mergefrom))
		{
			ui.tableWidget->setSpan(i,liDataList.at(i).mergefrom-1,1,liDataList.at(i).mergeto-liDataList.at(i).mergefrom+1);
		}
	}
}
