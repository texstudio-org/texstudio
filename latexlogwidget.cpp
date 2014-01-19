#include "latexlogwidget.h"
#include "smallUsefulFunctions.h"
#include "configmanager.h"

LatexLogWidget::LatexLogWidget(QWidget *parent) :
	QWidget(parent), logModel(0), displayPartsActions(0), logpresent(false)
{
	logModel = new LatexLogModel(this);//needs loaded line marks

	errorTable = new QTableView(this);

	errorTable->setModel(logModel);

	QFontMetrics fm(QApplication::font());
	errorTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	errorTable->setSelectionMode(QAbstractItemView::SingleSelection);
	errorTable->setColumnWidth(0,fm.width("> "));
	errorTable->setColumnWidth(1,20*fm.width("w"));
	errorTable->setColumnWidth(2,fm.width("WarningW"));
	errorTable->setColumnWidth(3,fm.width("Line WWWWW"));
	errorTable->setColumnWidth(4,20*fm.width("w"));
	connect(errorTable, SIGNAL(clicked(const QModelIndex &)), this, SLOT(clickedOnLogModelIndex(const QModelIndex &)));

	errorTable->horizontalHeader()->setStretchLastSection(true);
	errorTable->setMinimumHeight(5*(fm.lineSpacing()+4));
	errorTable->setFrameShape(QFrame::NoFrame);

	QAction * act = new QAction(tr("&Copy"),errorTable);
	connect(act, SIGNAL(triggered()), SLOT(copyMessage()));
	errorTable->addAction(act);
	act = new QAction(tr("&Copy All"),errorTable);
	connect(act, SIGNAL(triggered()), SLOT(copyAllMessages()));
	errorTable->addAction(act);
	act = new QAction(tr("&Copy All With Line Numbers"),errorTable);
	connect(act, SIGNAL(triggered()), SLOT(copyAllMessagesWithLineNumbers()));
	errorTable->addAction(act);
	errorTable->setContextMenuPolicy(Qt::ActionsContextMenu);

	log = new LogEditor(this);
	log->setFocusPolicy(Qt::ClickFocus);
	log->setMinimumHeight(3*(fm.lineSpacing()+4));
	log->setReadOnly(true);
	connect(log, SIGNAL(clickOnLogLine(int)),this,SLOT(gotoLogLine(int)));

	QSplitter *splitter = new QSplitter(Qt::Vertical, this);
	splitter->setChildrenCollapsible(false);
	splitter->addWidget(errorTable);
	splitter->addWidget(log);

	infoLabel = new QLabel(tr("No log file available"), this);
	infoLabel->setStyleSheet("background: #FFFBBF;");
	infoLabel->setMargin(2);

	QVBoxLayout* vLayout = new QVBoxLayout(); //contains the widgets for the normal mode (OutputTable + OutputLogTextEdit)
	vLayout->setSpacing(0);
	vLayout->setMargin(0);
	vLayout->addWidget(infoLabel);
	vLayout->addWidget(splitter);
	setLayout(vLayout);

	displayPartsActions = new QActionGroup(this);
	displayPartsActions->setExclusive(true);
	connect(displayPartsActions, SIGNAL(triggered(QAction*)), this, SLOT(changeDisplay(QAction *)));
	displayTableAction = new QAction(tr("Issues"), displayPartsActions);
	displayTableAction->setData(qVariantFromValue(DisplayTable));
	displayTableAction->setCheckable(true);
	displayLogAction = new QAction(tr("Log File"), displayPartsActions);
	displayLogAction->setData(qVariantFromValue(DisplayLog));
	displayLogAction->setCheckable(true);
	displayLogAndTableAction = new QAction(tr("Issues and Log"), displayPartsActions);
	displayLogAndTableAction->setData(qVariantFromValue(DisplayLogAndTable));
	displayLogAndTableAction->setCheckable(true);

	setDisplayParts(DisplayTable);
}

bool LatexLogWidget::loadLogFile(const QString &logname, const QString & compiledFileName){
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
		if (f.size() > fileSizeLimitMB*1024*1024 &&
			!txsConfirmWarning(tr("The logfile is very large (%1 MB) are you sure you want to load it?").arg(double(f.size()) / 1024 / 1024, 0, 'f', 2)))
			return false;

		//QByteArray fullLog = simplifyLineConserving(f.readAll());
		// TODO: if we want to have simplification here it has to be smarter.
		// The above version trims whitespace, which leads to undesired effects due to the 80 char
		// line width of the log. "line\n 1"  would become "\line\n1" and, when rejoining lines for error/warning detection "line1".
		// Do we need this or can we just leave the output as it is?
		QByteArray fullLog = f.readAll();
		f.close();

		int sure;
		QTextCodec * codec = guessEncodingBasic(fullLog, &sure);
		if (!sure || !codec) codec = QTextCodec::codecForLocale();

		log->setPlainText(codec->toUnicode(fullLog));

		logModel->parseLogDocument(log->document(), compiledFileName);

		logpresent=true;

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

bool LatexLogWidget::logPresent(){
	return logpresent;
}

void LatexLogWidget::resetLog() {
	log->clear();
	logModel->clear();
	logpresent=false;
	setInfo("");
	emit logResetted();
}

bool LatexLogWidget::logEntryNumberValid(int logEntryNumber) {
	return logEntryNumber>=0 && logEntryNumber<logModel->count();
}

void LatexLogWidget::selectLogEntry(int logEntryNumber){
	if (!logEntryNumberValid(logEntryNumber)) return;
	errorTable->scrollTo(logModel->index(logEntryNumber,1),QAbstractItemView::PositionAtCenter);
	errorTable->selectRow(logEntryNumber);
	log->setCursorPosition(logModel->at(logEntryNumber).logline, 0);
}

void LatexLogWidget::copy() {
	if (displayLogAction->isChecked() || displayLogAndTableAction->isChecked())
		log->copy();
	else
		copyMessage();
}

void LatexLogWidget::setDisplayParts(DisplayParts parts) {
	errorTable->setVisible( parts == DisplayTable || parts == DisplayLogAndTable);
	log->setVisible( parts == DisplayLog || parts == DisplayLogAndTable);
	switch(parts) {
		case DisplayTable:       displayTableAction->setChecked(true); break;
		case DisplayLog:         displayLogAction->setChecked(true); break;
		case DisplayLogAndTable: displayLogAndTableAction->setChecked(true); break;
	}
}

// TODO what is this for?
void LatexLogWidget::gotoLogEntry(int logEntryNumber) {
	if (!logEntryNumberValid(logEntryNumber)) return;
	//select entry in table view/log
	//OutputTable->scrollTo(logModel->index(logEntryNumber,1),QAbstractItemView::PositionAtCenter);
	//OutputLogTextEdit->setCursorPosition(logModel->at(logEntryNumber).logline, 0);
	selectLogEntry(logEntryNumber);
	//notify editor
	emit logEntryActivated(logEntryNumber);
}

void LatexLogWidget::clickedOnLogModelIndex(const QModelIndex& index){
	gotoLogEntry(index.row());
}

void LatexLogWidget::gotoLogLine(int logLine){
	gotoLogEntry(logModel->logLineNumberToLogEntryNumber(logLine));
}

void LatexLogWidget::copyMessage(){
	QModelIndex curMessage = errorTable->currentIndex();
	if (!curMessage.isValid()) return;
	curMessage = logModel->index(curMessage.row(), 3);
	REQUIRE(QApplication::clipboard());
	QApplication::clipboard()->setText(logModel->data(curMessage, Qt::DisplayRole).toString());
}
void LatexLogWidget::copyAllMessages(){
	QStringList result;
	for (int i=0;i<logModel->count();i++)
		result << logModel->data(logModel->index(i, 3), Qt::DisplayRole).toString();
	REQUIRE(QApplication::clipboard());
	QApplication::clipboard()->setText(result.join("\n"));
}
void LatexLogWidget::copyAllMessagesWithLineNumbers(){
	QStringList result;
	for (int i=0;i<logModel->count();i++)
		result << logModel->data(logModel->index(i, 2), Qt::DisplayRole).toString() +": "+logModel->data(logModel->index(i, 3), Qt::DisplayRole).toString();
	REQUIRE(QApplication::clipboard());
	QApplication::clipboard()->setText(result.join("\n"));
}

void LatexLogWidget::changeDisplay(QAction *act) {
	if(act) {
		setDisplayParts(act->data().value<LatexLogWidget::DisplayParts>());
	}
}

void LatexLogWidget::setInfo(const QString &message) {
	infoLabel->setText(message);
	infoLabel->setVisible(!message.isEmpty());
}

