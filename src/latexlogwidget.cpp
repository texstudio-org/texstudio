#include "latexlogwidget.h"
#include "encoding.h"
#include "configmanager.h"
#include "minisplitter.h"

/*
 * row heights of tables are quite large by default. Experimentally detect the
 * optimal row height in a portable way by resizing to contents and getting
 * the resulting row height
 */
int getOptimalRowHeight(QTableView *tableView)
{
	QAbstractItemModel *model = tableView->model();
	QStandardItemModel testModel;
	QStandardItem item("Test");
	testModel.appendRow(&item);
	tableView->setModel(&testModel);
	tableView->resizeRowsToContents();
	int height = tableView->rowHeight(0);
	tableView->setModel(model);
	return height;
}

LatexLogWidget::LatexLogWidget(QWidget *parent) :
    QWidget(parent), logModel(nullptr), proxyModel(nullptr), logpresent(false), filterErrorAction(nullptr), filterWarningAction(nullptr), filterBadBoxAction(nullptr)
{
	logModel = new LatexLogModel(this);//needs loaded line marks

	errorTable = new QTableView(this);
	int rowHeight = getOptimalRowHeight(errorTable);
	errorTable->verticalHeader()->setDefaultSectionSize(rowHeight);
	QFontMetrics fm(QApplication::font());
	errorTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	errorTable->setSelectionMode(QAbstractItemView::SingleSelection);
	errorTable->setColumnWidth(0, fm.width("> "));
	errorTable->setColumnWidth(1, 20 * fm.width("w"));
	errorTable->setColumnWidth(2, fm.width("WarningW"));
	errorTable->setColumnWidth(3, fm.width("Line WWWWW"));
	errorTable->setColumnWidth(4, 20 * fm.width("w"));
	connect(errorTable, SIGNAL(clicked(const QModelIndex &)), this, SLOT(clickedOnLogModelIndex(const QModelIndex &)));

	errorTable->horizontalHeader()->setStretchLastSection(true);
	errorTable->setMinimumHeight(5 * rowHeight);
	errorTable->setFrameShape(QFrame::NoFrame);
	errorTable->setSortingEnabled(true);

	proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(logModel);
	errorTable->setModel(proxyModel);

	QAction *act = new QAction(tr("&Copy"), errorTable);
	connect(act, SIGNAL(triggered()), SLOT(copyMessage()));
	errorTable->addAction(act);
	act = new QAction(tr("&Copy All"), errorTable);
	connect(act, SIGNAL(triggered()), SLOT(copyAllMessages()));
	errorTable->addAction(act);
	act = new QAction(tr("&Copy All With Line Numbers"), errorTable);
	connect(act, SIGNAL(triggered()), SLOT(copyAllMessagesWithLineNumbers()));
	errorTable->addAction(act);
	errorTable->setContextMenuPolicy(Qt::ActionsContextMenu);

	log = new LogEditor(this);
	log->setFocusPolicy(Qt::ClickFocus);
	log->setMinimumHeight(3 * (fm.lineSpacing() + 4));
	log->setReadOnly(true);
	log->setFrameShape(QFrame::NoFrame);
	connect(log, SIGNAL(clickOnLogLine(int)), this, SLOT(gotoLogLine(int)));

	QSplitter *splitter = new MiniSplitter(Qt::Vertical, this);
	splitter->setChildrenCollapsible(false);
	splitter->addWidget(errorTable);
	splitter->addWidget(log);

	infoLabel = new QLabel(tr("No log file available"), this);
	infoLabel->setStyleSheet("background: #FFFBBF;");
	infoLabel->setMargin(2);

	QVBoxLayout *vLayout = new QVBoxLayout(); //contains the widgets for the normal mode (OutputTable + OutputLogTextEdit)
	vLayout->setSpacing(0);
	vLayout->setMargin(0);
	vLayout->addWidget(infoLabel);
	vLayout->addWidget(splitter);
	setLayout(vLayout);

	displayTableAction = new QAction(tr("Issues"), this);
	displayTableAction->setCheckable(true);
	connect(displayTableAction, SIGNAL(triggered(bool)), this, SLOT(setWidgetVisibleFromAction(bool)));
	displayLogAction = new QAction(tr("Log File"), this);
	displayLogAction->setCheckable(true);
	connect(displayLogAction, SIGNAL(triggered(bool)), this, SLOT(setWidgetVisibleFromAction(bool)));
	filterErrorAction = new QAction(QIcon(":/images-ng/error.svgz"), tr("Show Error"), this);
	filterErrorAction->setCheckable(true);
	filterErrorAction->setChecked(true);
	connect(filterErrorAction, SIGNAL(toggled(bool)), this, SLOT(filterChanged(bool)));
	filterWarningAction = new QAction(QIcon(":/images-ng/warning.svgz"), tr("Show Warning"), this);
	filterWarningAction->setCheckable(true);
	filterWarningAction->setChecked(true);
	connect(filterWarningAction, SIGNAL(toggled(bool)), this, SLOT(filterChanged(bool)));
	filterBadBoxAction = new QAction(QIcon(":/images-ng/badbox.svg"), tr("Show BadBox"), this);
	filterBadBoxAction->setCheckable(true);
	filterBadBoxAction->setChecked(true);
	connect(filterBadBoxAction, SIGNAL(toggled(bool)), this, SLOT(filterChanged(bool)));

	// initialize visibility
	displayTableAction->setChecked(true);
	errorTable->setVisible(true);
	displayLogAction->setChecked(false);
	log->setVisible(false);
}


bool LatexLogWidget::loadLogFile(const QString &logname, const QString &compiledFileName, QTextCodec* fallbackCodec)
{
	resetLog();
	QFileInfo fi(logname);
	if (logname.isEmpty() || !fi.exists()) {
		setInfo(tr("Log file not found."));
		return false;
	}
	if (!fi.isReadable()) {
		setInfo(tr("Log file not readable."));
		return false;
	}

	QFile f(logname);
	if (f.open(QIODevice::ReadOnly)) {
		double fileSizeLimitMB = ConfigManagerInterface::getInstance()->getOption("LogView/WarnIfFileSizeLargerMB").toDouble();
		if (f.size() > fileSizeLimitMB * 1024 * 1024 &&
		        !UtilsUi::txsConfirmWarning(tr("The logfile is very large (%1 MB) are you sure you want to load it?").arg(double(f.size()) / 1024 / 1024, 0, 'f', 2)))
			return false;

		QByteArray fullLog = f.readAll();
		f.close();

		int sure;
		QTextCodec *codec = Encoding::guessEncodingBasic(fullLog, &sure);
		if (sure < 2 || !codec) codec = fallbackCodec ? fallbackCodec : QTextCodec::codecForLocale();

		log->setPlainText(codec->toUnicode(fullLog));

		logModel->parseLogDocument(log->document(), compiledFileName);

		logpresent = true;

		// workaround to https://sourceforge.net/p/texstudio/feature-requests/622/
		// There seems to be a bug in Qt (4.8.4) that resizeRowsToContents() does not work correctly if
		// horizontalHeader()->setStretchLastSection(true) and the tableView has not yet been shown
		// when iterating through the columns to determine the maximal height, everything is fine
		// until the last column. There the calculated height is too large.
		// As a workaround we will temporarily deactivate column stretching.
		// Note: To reproduce, you can call the viewer via The ViewLog button. When showing the viewer
		// by clicking the ViewTab, the widget is shown before loading (so there the bug did not appear.)
		bool visible = errorTable->isVisible();
		if (!visible) errorTable->horizontalHeader()->setStretchLastSection(false);
		errorTable->resizeColumnsToContents();
		errorTable->resizeRowsToContents();
		if (!visible) errorTable->horizontalHeader()->setStretchLastSection(true);

		selectLogEntry(0);
		emit logLoaded();
		return true;
	}

	setInfo(tr("Log file not readable."));
	return false;
}

bool LatexLogWidget::logPresent()
{
	return logpresent;
}

void LatexLogWidget::resetLog()
{
	log->clear();
	logModel->clear();
	logpresent = false;
	setInfo("");
	emit logResetted();
}

bool LatexLogWidget::logEntryNumberValid(int logEntryNumber)
{
	return logEntryNumber >= 0 && logEntryNumber < logModel->count();
}

void LatexLogWidget::selectLogEntry(int logEntryNumber)
{
	if (!logEntryNumberValid(logEntryNumber)) return;
	QModelIndex index = proxyModel->mapFromSource(logModel->index(logEntryNumber, 1));
	errorTable->scrollTo(index, QAbstractItemView::PositionAtCenter);
	//errorTable->selectRow(logEntryNumber);
	errorTable->selectRow(index.row());
	log->setCursorPosition(logModel->at(logEntryNumber).logline, 0);
}

void LatexLogWidget::copy()
{
	if (log->isVisible())
		log->copy();
	else
		copyMessage();
}

// TODO what is this for?
void LatexLogWidget::gotoLogEntry(int logEntryNumber)
{
	if (!logEntryNumberValid(logEntryNumber)) return;
	//select entry in table view/log
	//OutputTable->scrollTo(logModel->index(logEntryNumber,1),QAbstractItemView::PositionAtCenter);
	//OutputLogTextEdit->setCursorPosition(logModel->at(logEntryNumber).logline, 0);
	selectLogEntry(logEntryNumber);
	//notify editor
	emit logEntryActivated(logEntryNumber);
}

void LatexLogWidget::clickedOnLogModelIndex(const QModelIndex &index)
{
	QModelIndex idx = proxyModel->mapToSource(index);
	gotoLogEntry(idx.row());
}

void LatexLogWidget::gotoLogLine(int logLine)
{
	gotoLogEntry(logModel->logLineNumberToLogEntryNumber(logLine));
}

void LatexLogWidget::copyMessage()
{
	QModelIndex curMessage = proxyModel->mapToSource(errorTable->currentIndex());
	if (!curMessage.isValid()) return;
	curMessage = logModel->index(curMessage.row(), 3);
	REQUIRE(QApplication::clipboard());
	QApplication::clipboard()->setText(logModel->data(curMessage, Qt::DisplayRole).toString());
}

void LatexLogWidget::copyAllMessages()
{
	QStringList result;
	for (int i = 0; i < logModel->count(); i++)
		result << logModel->data(logModel->index(i, 3), Qt::DisplayRole).toString();
	REQUIRE(QApplication::clipboard());
	QApplication::clipboard()->setText(result.join("\n"));
}

void LatexLogWidget::copyAllMessagesWithLineNumbers()
{
	QStringList result;
	for (int i = 0; i < logModel->count(); i++)
		result << logModel->data(logModel->index(i, 2), Qt::DisplayRole).toString() + ": " + logModel->data(logModel->index(i, 3), Qt::DisplayRole).toString();
	REQUIRE(QApplication::clipboard());
	QApplication::clipboard()->setText(result.join("\n"));
}

void LatexLogWidget::setWidgetVisibleFromAction(bool visible)
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (act == displayTableAction) {
		errorTable->setVisible(visible);
		if (!visible && !log->isVisible()) {
			displayLogAction->setChecked(true); // fallback, one widget should always be visible
			log->setVisible(true);
		}
	} else if (act == displayLogAction) {
		log->setVisible(visible);
		if (!visible && !errorTable->isVisible()) {
			displayTableAction->setChecked(true);  // fallback, one widget should always be visible
			errorTable->setVisible(true);
		}
	}
}

void LatexLogWidget::setInfo(const QString &message)
{
	infoLabel->setText(message);
	infoLabel->setVisible(!message.isEmpty());
}

QList<QAction *> LatexLogWidget::displayActions()
{
	QList<QAction *> result;
	QAction *sep1 = new QAction(this);
	sep1->setSeparator(true);
	QAction *sep2 = new QAction(this);
	sep2->setSeparator(true);
	result << displayLogAction << displayTableAction << sep1 << filterErrorAction << filterWarningAction << filterBadBoxAction << sep2;
	return result;
}

void LatexLogWidget::filterChanged(bool )
{
	QStringList lst;
	if (filterErrorAction && filterErrorAction->isChecked())
		lst << logModel->returnString(LT_ERROR);
	if (filterWarningAction && filterWarningAction->isChecked())
		lst << logModel->returnString(LT_WARNING);
	if (filterBadBoxAction && filterBadBoxAction->isChecked())
		lst << logModel->returnString(LT_BADBOX);
	QString rg = lst.join("|");
	proxyModel->setFilterRegExp(rg);
	proxyModel->setFilterKeyColumn(1);
}
