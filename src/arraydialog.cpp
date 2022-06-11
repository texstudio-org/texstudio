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

#include "arraydialog.h"
#include "utilsUI.h"

ArrayDialog::ArrayDialog(QWidget *parent, const char *name)
		:QDialog(parent) {
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);
	UtilsUi::resizeInFontHeight(this, 36, 30);

	ui.tableWidget->setRowCount(2);
	ui.tableWidget->setColumnCount(2);

	ui.spinBoxRows->setValue(2);
	ui.spinBoxRows->setRange(1, 99);
	connect(ui.spinBoxRows, SIGNAL(valueChanged(int)), this, SLOT(newRows(int)));

	ui.spinBoxColumns->setValue(2);
	ui.spinBoxColumns->setRange(1,99);
	connect(ui.spinBoxColumns, SIGNAL(valueChanged(int)), this, SLOT(newColumns(int)));

	ui.comboAlignment->insertItem(0, tr("Center"), 'c');
	ui.comboAlignment->insertItem(1, tr("Left"), 'l');
	ui.comboAlignment->insertItem(2, tr("Right"), 'r');

	ui.comboEnvironment->insertItem(0, "array");
	ui.comboEnvironment->insertItem(1, "matrix");
	ui.comboEnvironment->insertItem(2, "pmatrix");
	ui.comboEnvironment->insertItem(3, "bmatrix");
	ui.comboEnvironment->insertItem(4, "Bmatrix");
	ui.comboEnvironment->insertItem(5, "vmatrix");
	ui.comboEnvironment->insertItem(6, "Vmatrix");
	setWindowTitle(tr("Quick Array"));
}

ArrayDialog::~ArrayDialog() {
}

QString ArrayDialog::getLatexText()
{
	int nrows = ui.spinBoxRows->value();
	int ncols = ui.spinBoxColumns->value();
	QString env = ui.comboEnvironment->currentText();
	QString text = QString("\\begin{") + env + "}";
	if (env == "array") {
		QChar alignChar = ui.comboAlignment->itemData(ui.comboAlignment->currentIndex()).toChar();
		text += "{" + QString(ncols, alignChar) + "}";
	}
	text += QString("\n");
	for (int i = 0; i < nrows - 1; i++) {
		for (int j = 0; j < ncols - 1; j++) {
			QTableWidgetItem *item = ui.tableWidget->item(i, j);
			if (item)
				text += item->text();
			text += QString(" & ");
		}
		QTableWidgetItem *item = ui.tableWidget->item(i, ncols - 1);
		if (item)
			text += item->text();
		text += QString(" \\\\\n");
	}
	for (int j = 0; j < ncols - 1; j++) {
		QTableWidgetItem *item = ui.tableWidget->item(nrows - 1, j);
		if (item)
			text += item->text();
		text += QString(" & ");
	}
	QTableWidgetItem *item = ui.tableWidget->item(nrows - 1, ncols - 1);
	if (item)
		text += item->text();
	text += QString("\n\\end{") + env + "}";
	return text;
}

void ArrayDialog::newRows(int num) {
	ui.tableWidget->setRowCount(num);
}

void ArrayDialog::newColumns(int num) {
	ui.tableWidget->setColumnCount(num);
}

void ArrayDialog::keyPressEvent(QKeyEvent *event)
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
        for (QTableWidgetItem *item : list)
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

        for (int row=start_row; row <= end_row; ++row)
        {
            for (int col=start_col; col <= end_col; ++col)
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
        for (QTableWidgetItem *item : list)
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

        for (int row=start_row; row <= end_row; ++row)
        {
            for (int col=start_col; col <= end_col; ++col)
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
        QList<QString> rows = pasted_text.split('\n');

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
        for (QString row : rows)
        {
            if (cur_row >= ui.tableWidget->rowCount())
            {
                ui.tableWidget->setRowCount(ui.tableWidget->rowCount() + 1);
                ui.spinBoxRows->setValue(ui.spinBoxRows->value() + 1);
            }

            QList<QString> cols = row.split('\t');
            for (QString col : cols)
            {
                if (cur_col >= ui.tableWidget->columnCount())
                {
                    ui.tableWidget->setColumnCount(ui.tableWidget->columnCount() + 1);
                    ui.spinBoxColumns->setValue(ui.spinBoxColumns->value() + 1);
                }

                // Adds new item if copied size is larger than table size.
                QTableWidgetItem *new_item = new QTableWidgetItem();
                ui.tableWidget->setItem(cur_row, cur_col, new_item);

                QTableWidgetItem *item = ui.tableWidget->item(cur_row, cur_col);
                if (item) // Checks if item is a null pointer (item doesn't exist)
                {
                    item->setText(col);
                    ++cur_col;
                }
                else
                {
                    QTableWidgetItem *newItem = new QTableWidgetItem();
                    newItem->setText(col);
                }
            }
            ++cur_row;
            cur_col = starting_col;
        }
    }

    // Table Delete Cells
    // This feature allows cells to be deleted by selecting and clicking the delete key.
    if (event->key() == Qt::Key_Delete)
    {
        QList<QTableWidgetItem *> list = ui.tableWidget->selectedItems();
        for (QTableWidgetItem* i : list)
        {
            i->setText("");
        }
    }
}
