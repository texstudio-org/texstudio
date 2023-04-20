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

	int defaultColCount = 2;
	ui.tableWidget->setColumnCount(defaultColCount);
	ui.tableWidget->setRowCount(2);

	ui.spinBoxRows->setValue(2);
	ui.spinBoxRows->setRange(1, 99);
	connect(ui.spinBoxRows, SIGNAL(valueChanged(int)), this, SLOT(newRows(int)));

	ui.spinBoxColumns->setValue(defaultColCount);
	ui.spinBoxColumns->setRange(1,99);
	connect(ui.spinBoxColumns, SIGNAL(valueChanged(int)), this, SLOT(newColumns(int)));

	setComboEnv();
	ui.comboEnvironment->setCurrentIndex(0);

	ui.comboAlignment->insertItem(0, alignTextList.at(0), 'c');
	ui.comboAlignment->insertItem(1, alignTextList.at(1), 'l');
	ui.comboAlignment->insertItem(2, alignTextList.at(2), 'r');

	int defaultAlignIndex = alignList.indexOf(Qt::AlignHCenter);
	// fill the list with the alignments for array environment
	for (int col = 0; col < defaultColCount; col++) {
		arrayAligns << defaultAlignIndex;
	}

	ui.tableWidget->setCurrentCell(0,0);
	ui.comboAlignment->setCurrentIndex(defaultAlignIndex);
	addEmptyTableItems();
	slotEnvironmentChanged();

	connect(ui.comboEnvironment,SIGNAL(currentIndexChanged(int)),SLOT(slotEnvironmentChanged()));
	connect(ui.comboAlignment,SIGNAL(currentIndexChanged(int)),SLOT(slotAlignmentChanged(int)));
	connect(ui.tableWidget, SIGNAL(currentCellChanged(int, int, int, int)),SLOT(slotCurrentCellChanged(int, int)));
}

ArrayDialog::~ArrayDialog() {
}

QString ArrayDialog::getLatexText() {
	int nrows = ui.spinBoxRows->value();
	int ncols = ui.spinBoxColumns->value();
	QStringList beginEnd = getEnvBeginEndStatements();

	QString text = beginEnd.first() + "\n";
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
	text += QString("\n");
	text += beginEnd.last();
	return text;
}

void ArrayDialog::addEmptyTableItems() {
	int cols = ui.tableWidget->columnCount();
	for (int col = 0; col < cols; col++) {
		addEmptyColumnItems(col);
	}
}

void ArrayDialog::addEmptyColumnItems(int col) {
	int rows = ui.tableWidget->rowCount();
	for (int row = 0; row < rows; row++) {
		QTableWidgetItem *newItem = new QTableWidgetItem();
		ui.tableWidget->setItem(row, col, newItem);
	}
}

void ArrayDialog::setTitle() {
	QString text = tr("Quick Array") + " - ";
	QStringList beginEnd = getEnvBeginEndStatements();
	text += beginEnd.first() + "..." + beginEnd.last();
	setWindowTitle(text);
	setTableHeader();
}

void ArrayDialog::setTableHeader() {
	int ncols = ui.spinBoxColumns->value();
	QStringList headerList;
	for (int i = 0; i < ncols; i++) {
		int ix = currentColAlignIndex(i);
		headerList << ui.comboAlignment->itemData(ix).toChar();
	}
	ui.tableWidget->setHorizontalHeaderLabels(headerList);
}

QStringList ArrayDialog::getEnvBeginEndStatements() {
	int ncols = ui.spinBoxColumns->value();
	QString env = ui.comboEnvironment->currentText();
	QString begin = QString("\\begin{" + env + "}");
	QString end = QString("\\end{") + env + "}";

	if (env == "array") {
		begin += "{" + getArrayAlignments() + "}";
	}
	else if (env == "alignedat") {
		begin += QString("{%1}").arg((ncols + 1) / 2);
	}
	else if (env.endsWith("*")) {   // mathtools
		int idx = ui.comboAlignment->currentIndex();
		begin += "[" + QString(ui.comboAlignment->itemData(idx).toChar()) + "]";
	}
	return {begin, end};
}

QString ArrayDialog::getArrayAlignments() {
	int ncols = ui.spinBoxColumns->value();
	QString text;
	for (int i = 0; i < ncols; i++) {
		text += ui.comboAlignment->itemData(arrayAligns.at(i)).toChar();
	}
	return text;
}

void ArrayDialog::setComboEnv() {
	ui.comboEnvironment->clear();

	for (int i = 0; i < environmentList.count(); i++) {
		QString env = environmentList.at(i);
		if (env == "")
			ui.comboEnvironment->insertSeparator(i);
		else ui.comboEnvironment->insertItem(i, env);
	}
}

void ArrayDialog::slotEnvironmentChanged() {
	QString env = ui.comboEnvironment->currentText();
	if (env == "array") {
		int currentCol = ui.tableWidget->currentColumn();
		ui.comboAlignment->setCurrentIndex(arrayAligns.at(currentCol));
	}
	setColAlignments();
	setTitle();
}

void ArrayDialog::setColAlignments() {
	int cols = ui.tableWidget->columnCount();
	for (int col = 0; col < cols; col++) {
		int ix = currentColAlignIndex(col);
		setColAlignment(col, alignList.at(ix));
	}
}

void ArrayDialog::setColAlignment(int col, Qt::AlignmentFlag align) {
	int rows = ui.tableWidget->rowCount();
	for (int row = 0; row < rows; row++) {
		QTableWidgetItem *item = ui.tableWidget->item(row, col);
		item->setTextAlignment(align);
	}
}

int ArrayDialog::currentColAlignIndex(int col) {
	QString env = ui.comboEnvironment->currentText();
	int ix;
	if (env == "array") {
		ix = arrayAligns.at(col);
	}
	else if (env == "alignedat") {
		int mode = col % 2;
		if (mode == 0) {
			ix = alignList.indexOf(Qt::AlignRight);
		}
		else {
			ix = alignList.indexOf(Qt::AlignLeft);
		}
	}
	else if (env.endsWith("*")) {  // mathtools
		ix = ui.comboAlignment->currentIndex();
	}
	else {  // amsmath
		ix = alignList.indexOf(Qt::AlignHCenter);
	}
	return ix;
}

void ArrayDialog::slotAlignmentChanged(int ix) {
	QString env = ui.comboEnvironment->currentText();
	if (env == "array") {
		int col = ui.tableWidget->currentColumn();
		arrayAligns[ui.tableWidget->currentColumn()] = ix;
		Qt::AlignmentFlag align = alignList[ix];
		setColAlignment(col, align);
	}
	else if (!env.endsWith("*") || env == "alignedat") {}
	else
		setColAlignments();
	setTitle();
}

void ArrayDialog::slotCurrentCellChanged(int row, int col) {
	QString env = ui.comboEnvironment->currentText();
	if (env == "array") {
		ui.comboAlignment->setCurrentIndex(arrayAligns.at(col));
	}
}

void ArrayDialog::newRows(int rows) {
	int rowsOld = ui.tableWidget->rowCount();
	int cols = ui.tableWidget->columnCount();
	ui.tableWidget->setRowCount(rows);
	if (rows > rowsOld) {
		for (int col = 0; col < cols; col++) {
			int ix = currentColAlignIndex(col);
			Qt::AlignmentFlag align = alignList[ix];
			for (int row = rowsOld; row < rows; row++) {
				QTableWidgetItem *newItem = new QTableWidgetItem();
				ui.tableWidget->setItem(row, col, newItem);
				newItem->setTextAlignment(align);
			}
		}
	}
}

void ArrayDialog::newColumns(int cols) {
	int colsOld = ui.tableWidget->columnCount();
	ui.tableWidget->setColumnCount(cols);
	if (colsOld > cols) {
		for (int col = colsOld; col > cols; col--) arrayAligns.removeLast();
	}
	else if (cols > colsOld) {
		int ixArray = ui.comboAlignment->currentIndex();
		Qt::AlignmentFlag alignArray = alignList[ixArray];
		for (int col = colsOld; col < cols; col++) {
			arrayAligns.append(ixArray);
			addEmptyColumnItems(col);
			int ixOther = currentColAlignIndex(col);
			Qt::AlignmentFlag alignOther = alignList[ixOther];
			setColAlignment(col, alignOther);
		}
	}
	setTitle();
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
                ui.spinBoxRows->setValue(ui.spinBoxRows->value() + 1);
            }

            QList<QString> cols = row.split('\t');
            for(const QString &col : cols)
            {
                if (cur_col >= ui.tableWidget->columnCount())
                {
                    ui.spinBoxColumns->setValue(ui.spinBoxColumns->value() + 1);
                }

                QTableWidgetItem *item = ui.tableWidget->item(cur_row, cur_col);
                if (item) // Checks if item is a null pointer (item doesn't exist)
                {
                    item->setText(col);
                    ++cur_col;
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
        for(QTableWidgetItem* i : list)
        {
            i->setText("");
        }
    }
}
