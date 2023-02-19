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
#include "utilsUI.h"
//#include <QDebug>

#include "smallUsefulFunctions.h"


TabDialog::TabDialog(QWidget *parent, const char *name)
	:QDialog( parent)
{
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);
	UtilsUi::resizeInFontHeight(this, 53, 44);

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
	ui.comboBoxColAl->insertSeparator(3);
	ui.comboBoxColAl->insertItem(4, tr("p{} (fixed width - top / justified)", "tabular alignment"));
	ui.comboBoxColAl->insertItem(5, tr("p{} (fixed width - top / left)", "tabular alignment"));
	ui.comboBoxColAl->insertItem(6, tr("p{} (fixed width - top / center)", "tabular alignment"));
	ui.comboBoxColAl->insertItem(7, tr("p{} (fixed width - top / right)", "tabular alignment"));
	ui.comboBoxColAl->insertSeparator(8);
	ui.comboBoxColAl->insertItem(9, tr("m{} (fixed width - center / justified)", "tabular alignment"));
	ui.comboBoxColAl->insertItem(10, tr("m{} (fixed width - center / left)", "tabular alignment"));
	ui.comboBoxColAl->insertItem(11, tr("m{} (fixed width - center / center)", "tabular alignment"));
	ui.comboBoxColAl->insertItem(12, tr("m{} (fixed width - center / right)", "tabular alignment"));
	ui.comboBoxColAl->insertSeparator(13);
	ui.comboBoxColAl->insertItem(14, tr("b{} (fixed width - bottom / justified)", "tabular alignment"));
	ui.comboBoxColAl->insertItem(15, tr("b{} (fixed width - bottom / left)", "tabular alignment"));
	ui.comboBoxColAl->insertItem(16, tr("b{} (fixed width - bottom / center)", "tabular alignment"));
	ui.comboBoxColAl->insertItem(17, tr("b{} (fixed width - bottom / right)", "tabular alignment"));
	ui.comboBoxColAl->setCurrentIndex(0);
	ui.comboBoxColAl->setMaxVisibleItems(18);

	// alignList must match the entires in ui.comboBoxColAl
	alignlist << "c" << "l" << "r"
			  << QString("<SEP>")  << "p{3cm}" << ">{\\raggedright\\arraybackslash}p{3cm}" << ">{\\centering\\arraybackslash}p{3cm}" << ">{\\raggedleft\\arraybackslash}p{3cm}"
			  << QString("<SEP>")  << "m{3cm}" << ">{\\raggedright\\arraybackslash}m{3cm}" << ">{\\centering\\arraybackslash}m{3cm}" << ">{\\raggedleft\\arraybackslash}m{3cm}"
			  << QString("<SEP>")  << "b{3cm}" << ">{\\raggedright\\arraybackslash}p{3cm}" << ">{\\centering\\arraybackslash}b{3cm}" << ">{\\raggedleft\\arraybackslash}b{3cm}";

	alignlistLabels << QString("c") << QString("l") << QString("r")
			  << QString("<SEP>") << QString("j p{}") << QString("l p{}") << QString("c p{}") << QString("r p{}")
			  << QString("<SEP>")  << QString("j m{}") << QString("l m{}") << QString("c m{}") << QString("r m{}")
			  << QString("<SEP>")  << QString("j b{}") << QString("l b{}") << QString("c b{}") << QString("r b{}");

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

	// borderlist must match the entires in ui.comboLeftBorder and ui.comboBoxEndBorder
	borderlist << QString("|") << QString("||") << QString("") << QString("@{}");

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

/*!
 * Return the LaTeX formatted text describing the table.
 */
QString TabDialog::getLatexText()
{
	QString placeholder;//(0x2022);

	int nrows = ui.spinBoxRows->value();
	int ncols = ui.spinBoxColumns->value();
	QString text = "\\begin{tabular}{";
	for ( int j = 0; j < ncols; j++) {
		text += borderlist.at(colDataList.at(j).leftborder);
		text += alignlist.at(colDataList.at(j).alignment);
	}
	text += borderlist.at(ui.comboBoxEndBorder->currentIndex());
	text += "}\n";
	QTableWidgetItem *item = nullptr;
	for ( int i = 0; i < nrows; i++) {
		if (liDataList.at(i).topborder) text += "\\hline\n";
		if (ui.checkBoxMargin->isChecked()) text += "\\rule[-1ex]{0pt}{2.5ex} ";
		if (liDataList.at(i).merge && (liDataList.at(i).mergeto > liDataList.at(i).mergefrom)) {
			QString el = "";
			for ( int j = 0; j < ncols; j++) {
				item = ui.tableWidget->item(i, j);
				QString itemText = (item) ? textToLatex(item->text()) : "";
				if (j == liDataList.at(i).mergefrom - 1) {
					el += itemText;
					text += "\\multicolumn{";
					text += QString::number(liDataList.at(i).mergeto - liDataList.at(i).mergefrom + 1);
					text += "}{";
					if ((j == 0) && (colDataList.at(j).leftborder < 2)) text += borderlist.at(colDataList.at(j).leftborder);
					if (colDataList.at(j).alignment < 3) text += alignlist.at(colDataList.at(j).alignment);
					else text += "c";
					if (liDataList.at(i).mergeto == ncols) text += borderlist.at(ui.comboBoxEndBorder->currentIndex());
					else text += borderlist.at(colDataList.at(liDataList.at(i).mergeto).leftborder);
					text += "}{";
				} else if (j == liDataList.at(i).mergeto - 1) {
					el += itemText;
					if (el.isEmpty()) el = placeholder;
					text += el + "}";
					if (j < ncols - 1) text += " & ";
					else text += " \\\\\n";
				} else if ((j > liDataList.at(i).mergefrom - 1) && (j < liDataList.at(i).mergeto - 1)) {
					el += itemText;
				} else {
					if (itemText.isEmpty()) {
						itemText = placeholder;
					}
					text += itemText;
					if (j < ncols - 1) text += " & ";
					else text += " \\\\\n";
				}

			}
		} else {
			for ( int j = 0; j < ncols - 1; j++) {
				item = ui.tableWidget->item(i, j);
				QString itemText = (item) ? textToLatex(item->text()) : "";
				if (itemText.isEmpty()) {
					itemText = placeholder;
				}
				text += itemText + " & ";
			}
			item = ui.tableWidget->item(i, ncols - 1);
			QString itemText = (item) ? textToLatex(item->text()) : "";
			if (itemText.isEmpty()) {
				itemText = placeholder;
			}
			text += itemText + " \\\\\n";
		}
	}
	if (ui.checkBoxBorderBottom->isChecked())
		text += "\\hline\n\\end{tabular}";
	else
		text += "\\end{tabular}";
	return text;
}

/*!
 * Return a list of packages the given latex table code depends upon.
 */
QStringList TabDialog::getRequiredPackages(const QString &text)
{
	QStringList requiredPackages;
	if (text.contains("arraybackslash")) {
		requiredPackages << "array";
	}
    return requiredPackages;
}
/*!
 * \brief split instered text from spreadsheet into table wizard
 * "\n" row separator
 * "\t" col delimiter
 * \param pasted_text
 */
void TabDialog::insertTextIntoTable(QString pasted_text)
{
#if (QT_VERSION>=QT_VERSION_CHECK(5,14,0))
        QList<QString> rows = pasted_text.split('\n', Qt::SkipEmptyParts);
#else
        QList<QString> rows = pasted_text.split('\n', QString::SkipEmptyParts);
#endif

        // Get indexes of currently selected cells.
        int starting_row = 0;
        int starting_col = 0;
        QItemSelectionModel *selection_model = ui.tableWidget->selectionModel();
        if (selection_model)
        {
            QModelIndexList indexList = selection_model->selectedIndexes();
            if (indexList.count() > 0)
            {
                starting_row = selection_model->selectedIndexes().begin()->row();
                starting_col = selection_model->selectedIndexes().begin()->column();
            }
        }

        int cur_row = starting_row;
        int cur_col = starting_col;
        for(const QString &row : rows)
        {
            if (cur_row >= ui.tableWidget->rowCount())
            {
                ui.tableWidget->setRowCount(ui.tableWidget->rowCount() + 1);
                ui.spinBoxRows->setValue(ui.spinBoxRows->value() + 1);
            }

            QList<QString> cols = row.split('\t');
            for(const QString &col : cols)
            {
                if (cur_col >= ui.tableWidget->columnCount())
                {
                    ui.tableWidget->setColumnCount(ui.tableWidget->columnCount() + 1);
                    ui.spinBoxColumns->setValue(ui.spinBoxColumns->value() + 1);
                }

                QTableWidgetItem *item = ui.tableWidget->item(cur_row, cur_col);
                if (item) // Checks if item is a null pointer (item doesn't exist)
                {
                    item->setText(col);
                    ++cur_col;
                }
                else
                {
                    // Adds new item if copied size is larger than table size.
                    QTableWidgetItem *newItem = new QTableWidgetItem();
                    newItem->setText(col);
                    ui.tableWidget->setItem(cur_row, cur_col, newItem);
                }
            }
            ++cur_row;
            cur_col = starting_col;
        }
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
	int nrows = ui.spinBoxRows->value();
	int ncols = ui.spinBoxColumns->value();
	QStringList headerList;
	QString tag="";
	for ( int j=0;j<ncols;j++)
	{
		tag=borderlist.at(colDataList.at(j).leftborder);
		tag+=alignlistLabels.at(colDataList.at(j).alignment);
		if (j<ncols-1) headerList.append(tag);
	}
	tag+=borderlist.at(ui.comboBoxEndBorder->currentIndex());
	headerList.append(tag);
	ui.tableWidget->setHorizontalHeaderLabels(headerList);
	/*QColor selBlendColor=QColor("#0000FF");
QColor spancolor = selBlendColor.dark( 140 );
spancolor.setAlphaF( 0.2 );*/
	QTableWidgetItem *item, *new_item;
	QString content;
	for ( int i=0;i<nrows;i++)
	{
		for ( int j=0;j<ncols;j++)
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

void TabDialog::keyPressEvent(QKeyEvent *event)
{
    // Table Copy
    // This code captures the cells text values and puts them to clipboard.
    // Data is tab spaced for pasting into spreadsheet applications such as LibreOffice Calc.
    if ((event->modifiers() == Qt::CTRL) && (event->key() == Qt::Key_C))
    {
        // Check to ensure selection exists.
        QItemSelectionModel *selection_model = ui.tableWidget->selectionModel();
        if (selection_model)
        {
            QModelIndexList indexList = selection_model->selectedIndexes();
            if (indexList.count() <= 0)
            {
                return;
            }
        }
        else
        {
            return;
        }

        QString copied_text = "";
        QList<QTableWidgetItem *> list = ui.tableWidget->selectedItems();

        int start_row = list[0]->row();
        int end_row = list[0]->row();
        int start_col = list[0]->column();
        int end_col = list[0]->column();
        for(QTableWidgetItem *item : list)
        {
            if (item->row() < start_row)
            {
                start_row = item->row();
            }
            if (item->row() > end_row)
            {
                end_row = item->row();
            }
            if (item->column() < start_col)
            {
                start_col = item->column();
            }
            if (item->column() > end_col)
            {
                end_col = item->column();
            }
        }

        for(int row=start_row; row <= end_row; ++row)
        {
            for(int col=start_col; col <= end_col; ++col)
            {
                QTableWidgetItem *item = ui.tableWidget->item(row, col);
                copied_text += item->text();
                if (col < ui.tableWidget->columnCount() - 1)
                {
                    copied_text += "\t";
                }
            }
            copied_text += "\n";
        }
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(copied_text);
    }

    // Cut
    if ((event->modifiers() == Qt::CTRL) && (event->key() == Qt::Key_X))
    {
        // Check to ensure selection exists.
        QItemSelectionModel *selection_model = ui.tableWidget->selectionModel();
        if (selection_model)
        {
            QModelIndexList indexList = selection_model->selectedIndexes();
            if (indexList.count() <= 0)
            {
                return;
            }
        }
        else
        {
            return;
        }

        QString copied_text = "";
        QList<QTableWidgetItem *> list = ui.tableWidget->selectedItems();

        int start_row = list[0]->row();
        int end_row = list[0]->row();
        int start_col = list[0]->column();
        int end_col = list[0]->column();
        for(QTableWidgetItem *item : list)
        {
            if (item->row() < start_row)
            {
                start_row = item->row();
            }
            if (item->row() > end_row)
            {
                end_row = item->row();
            }
            if (item->column() < start_col)
            {
                start_col = item->column();
            }
            if (item->column() > end_col)
            {
                end_col = item->column();
            }
        }

        for(int row=start_row; row <= end_row; ++row)
        {
            for(int col=start_col; col <= end_col; ++col)
            {
                QTableWidgetItem *item = ui.tableWidget->item(row, col);
                copied_text += item->text();
                item->setText("");
                if (col < ui.tableWidget->columnCount() - 1)
                {
                    copied_text += "\t";
                }
            }
            copied_text += "\n";
        }
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(copied_text);
    }

    // Table Paste
    // Allows pasting of cell data from spreadsheet applications such as LibreOffice Calc.
    if ((event->modifiers() == Qt::CTRL) && (event->key() == Qt::Key_V))
    {
        QClipboard *clipboard = QGuiApplication::clipboard();
        QString pasted_text = clipboard->text();
        insertTextIntoTable(pasted_text);
    }

    // Table Delete Cells
    // This feature allows cells to be deleted by selecting and clicking the delete key.
    if (event->key() == Qt::Key_Delete)
    {
        QList<QTableWidgetItem *> list = ui.tableWidget->selectedItems();
        for(QTableWidgetItem* i : list)
        {
            i->setText("");
        }
    }
}
