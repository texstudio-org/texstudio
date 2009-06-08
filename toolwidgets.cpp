#include "toolwidgets.h"

#include <QApplication>
#include <QFile>
#include <QFontMetrics>
#include <QHeaderView>
#include <QMenu>
#include <QScrollBar>
#include <QTextStream>
#include <QVBoxLayout>

void adjustScrollBar(QScrollBar *scrollBar, double factor)
{
	scrollBar->setValue(int(factor * scrollBar->value()
							+ ((factor - 1) * scrollBar->pageStep()/2)));
}


PreviewWidget::PreviewWidget(QWidget * parent): QScrollArea(parent){
	setBackgroundRole(QPalette::Base);

	preViewer = new QLabel(this);
	preViewer->setBackgroundRole(QPalette::Base);
	preViewer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	preViewer->setScaledContents(true);
	preViewer->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(preViewer,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenu(QPoint)));

	setWidget(preViewer);
}

void PreviewWidget::scaleImage(double factor)
{
	Q_ASSERT(preViewer->pixmap());
	pvscaleFactor *= factor;
	preViewer->resize(pvscaleFactor * preViewer->pixmap()->size());

	adjustScrollBar(horizontalScrollBar(), factor);
	adjustScrollBar(verticalScrollBar(), factor);

}

void PreviewWidget::previewLatex(const QPixmap& previewImage){
	preViewer->setPixmap(previewImage);
	preViewer->adjustSize();
	pvscaleFactor=1.0;
}

void PreviewWidget::fitImage(){
	// needs to be improved
	QSize m_size=size()-QSize(2,2);
	QSize m_labelSize=preViewer->size();
	qreal ratio=1.0*m_labelSize.height()/m_labelSize.width();
	qreal ratioPreviewer=1.0*m_size.height()/m_size.width();
	int h,w;
	if(ratioPreviewer>ratio){
		h=qRound(ratio*m_size.width());
		w=m_size.width();
	} else {
		h=m_size.height();
		w=qRound(m_size.height()/ratio);
	}
	preViewer->resize(w,h);
	//setWidgetResizable(true);
}

void PreviewWidget::zoomOut(){
	scaleImage(0.8);
}

void PreviewWidget::zoomIn(){
	scaleImage(1.2);
}

void PreviewWidget::contextMenu(QPoint point) {
	QMenu menu;
	menu.addAction(tr("zoom in "),this, SLOT(zoomIn()));
	menu.addAction(tr("zoom out"),this, SLOT(zoomOut()));
	menu.addAction(tr("fit"),this, SLOT(fitImage()));
	menu.exec(preViewer->mapToGlobal(point));
}




const int LAYOUT_PAGE_MESSAGES=0;
const int LAYOUT_PAGE_LOG=1;
const int LAYOUT_PAGE_ERRORS=2;
const int LAYOUT_PAGE_PREVIEW=3;
	
OutputViewWidget::OutputViewWidget(QWidget * parent): QDockWidget(parent), logModel(0), logpresent(false), tabbedLogView(false){
	logModel = new LatexLogModel(this);//needs loaded line marks

	OutputTable= new QTableView(this);
	OutputTable2= new QTableView(this); // second table view for tab log view
	QFontMetrics fm(QApplication::font());
	for (int i=0;i<2;i++){ //setup tables
		QTableView* table=(i==0)?OutputTable:OutputTable2;
		table->setModel(logModel);

		table->setSelectionBehavior(QAbstractItemView::SelectRows);
		table->setSelectionMode(QAbstractItemView::SingleSelection);
		table->setColumnWidth(0,fm.width("> "));
		table->setColumnWidth(1,20*fm.width("w"));
		table->setColumnWidth(2,fm.width("WarningW"));
		table->setColumnWidth(3,fm.width("Line WWWWW"));
		table->setColumnWidth(4,20*fm.width("w"));
		connect(table, SIGNAL(clicked(const QModelIndex &)), this, SLOT(clickedOnLogModelIndex(const QModelIndex &)));
	
		table->horizontalHeader()->setStretchLastSection(true);
		table->setMinimumHeight(5*(fm.lineSpacing()+4));
	}

	OutputTextEdit = new LogEditor(this);
	OutputTextEdit->setFocusPolicy(Qt::ClickFocus);
	OutputTextEdit->setMinimumHeight(3*(fm.lineSpacing()+4));
	OutputTextEdit->setReadOnly(true);
	connect(OutputTextEdit, SIGNAL(clickOnLogLine(int)),this,SLOT(gotoLogLine(int)));

	OutputLogTextEdit = new LogEditor(this);
	OutputLogTextEdit->setFocusPolicy(Qt::ClickFocus);
	OutputLogTextEdit->setMinimumHeight(3*(fm.lineSpacing()+4));
	OutputLogTextEdit->setReadOnly(true);
	connect(OutputLogTextEdit, SIGNAL(clickOnLogLine(int)),this,SLOT(gotoLogLine(int)));

	OutputLayout= new QStackedWidget(this);

	QVBoxLayout* OutputVLayout= new QVBoxLayout(); //contains the widgets for the normal mode (OutputTable + OutputLogTextEdit)
	OutputVLayout->setSpacing(0);
	OutputVLayout->setMargin(0);

	// add widget to log view
	OutputLayout->addWidget(OutputTextEdit);

	OutputVLayout->addWidget(OutputTable);
	OutputVLayout->addWidget(OutputLogTextEdit);
	QWidget* tempWidget=new QWidget (this);
	tempWidget->setLayout(OutputVLayout);
	OutputLayout->addWidget(tempWidget);

	OutputLayout->addWidget(OutputTable2);

	// previewer
	previewWidget = new PreviewWidget(this);
	OutputLayout->addWidget(previewWidget);

	// order for tabbar
	logViewerTabBar=new QTabBar(this);
	logViewerTabBar->addTab(tr("messages"));
	logViewerTabBar->addTab(tr("log file"));
	logViewerTabBar->addTab(tr("errors"));
	logViewerTabBar->addTab(tr("preview"));
	logViewerTabBar->hide(); //internal default is non tabbed mode

	this->setWidget(OutputLayout);

	connect(logViewerTabBar, SIGNAL(currentChanged(int)),
	        OutputLayout, SLOT(setCurrentIndex(int)));

	connect(logViewerTabBar, SIGNAL(currentChanged(int)),
	        this, SIGNAL(tabChanged(int)));

}
void OutputViewWidget::setTabbedLogView(bool tabbed){
	tabbedLogView=tabbed;
	if (tabbed) {
		this->setTitleBarWidget(logViewerTabBar);
		OutputTable->hide();
	} else {
		this->setTitleBarWidget(0);
		OutputTable->show();
	}
}
void OutputViewWidget::previewLatex(const QPixmap& pixmap){
	previewWidget->previewLatex(pixmap);
	//showPreview();	
}
LatexLogModel* OutputViewWidget::getLogModel(){
	return logModel;
}
void OutputViewWidget::loadLogFile(const QString &logname, const QString & compiledFileName, const QString & overrideFileName){
	OutputLogTextEdit->clear();
	QFile f(logname);
	if (f.open(QIODevice::ReadOnly)) {
		QTextStream t(&f);
		QString line;
//		OutputTextEdit->setPlainText( t.readAll() );
		while (!t.atEnd()) {
			line=t.readLine();
			line=line.simplified();
			if (!line.isEmpty()) OutputLogTextEdit->append(line);
		}
		f.close();

		logModel->parseLogDocument(OutputLogTextEdit->document(), compiledFileName, overrideFileName);
		logpresent=true;		
		//update table size
		OutputTable->resizeColumnsToContents();
		OutputTable->resizeRowsToContents();
		OutputTable2->resizeColumnsToContents();
		OutputTable2->resizeRowsToContents();	
		
		selectLogEntry(0,false);
	}
}
bool OutputViewWidget::logPresent(){
	return logpresent;
}
bool OutputViewWidget::isPreviewPanelVisible(){
	if (!isVisible()) return false;
	return !tabbedLogView || logViewerTabBar->currentIndex()==LAYOUT_PAGE_PREVIEW;
}
void OutputViewWidget::setMessage(const QString &message){
	logViewerTabBar->setCurrentIndex(0);
	OutputTextEdit->setText(message);
}
void OutputViewWidget::insertMessageLine(const QString &message){
	OutputTextEdit->insertLine(message);
}
void OutputViewWidget::resetMessages(){
	OutputTextEdit->clear();
	logViewerTabBar->setCurrentIndex(0);
}
void OutputViewWidget::resetMessagesAndLog(){
	resetMessages();
	logpresent=false;
}
void OutputViewWidget::selectLogEntry(int logEntryNumber, bool makeVisible){
	if (logEntryNumber<0 || logEntryNumber>=logModel->count()) return;
	if (makeVisible) showErrorListOrLog();
	OutputTable->scrollTo(logModel->index(logEntryNumber,1),QAbstractItemView::PositionAtCenter);
	OutputTable->selectRow(logEntryNumber);
	OutputTable2->scrollTo(logModel->index(logEntryNumber,1),QAbstractItemView::PositionAtCenter);
	OutputTable2->selectRow(logEntryNumber);
	OutputLogTextEdit->setCursorPosition(logModel->at(logEntryNumber).logline, 0);
}
void OutputViewWidget::showLogOrErrorList(){
	if (!isVisible()) show();
	if (OutputLayout->currentIndex()!=LAYOUT_PAGE_LOG && OutputLayout->currentIndex()!=LAYOUT_PAGE_MESSAGES) 
		logViewerTabBar->setCurrentIndex(LAYOUT_PAGE_LOG);
}
void OutputViewWidget::showErrorListOrLog(){
	if (!isVisible()) show();
	if (tabbedLogView) {
		if (OutputLayout->currentIndex()!=LAYOUT_PAGE_LOG) 
			logViewerTabBar->setCurrentIndex(LAYOUT_PAGE_ERRORS);
	} else logViewerTabBar->setCurrentIndex(LAYOUT_PAGE_LOG);
}
void OutputViewWidget::showPreview(){
	if (!isVisible()) show();
	logViewerTabBar->setCurrentIndex(LAYOUT_PAGE_PREVIEW);
}
void OutputViewWidget::gotoLogEntry(int logEntryNumber) {
	if (logEntryNumber<0 || logEntryNumber>=logModel->count()) return;
	//select entry in table view/log
	//OutputTable->scrollTo(logModel->index(logEntryNumber,1),QAbstractItemView::PositionAtCenter);
	//OutputLogTextEdit->setCursorPosition(logModel->at(logEntryNumber).logline, 0);
	selectLogEntry(logEntryNumber);
	//notify editor	
	emit logEntryActivated(logEntryNumber);
}

void OutputViewWidget::clickedOnLogModelIndex(const QModelIndex& index){
	gotoLogEntry(index.row());
}
void OutputViewWidget::gotoLogLine(int logLine){
	gotoLogEntry(logModel->logLineNumberToLogEntryNumber(logLine));
}
