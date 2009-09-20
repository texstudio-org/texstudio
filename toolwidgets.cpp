#include "toolwidgets.h"

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
void OutputViewWidget::resetMessages(bool noTabChange){
	OutputTextEdit->clear();
	if(!noTabChange) logViewerTabBar->setCurrentIndex(0);
}
void OutputViewWidget::resetMessagesAndLog(bool noTabChange){
	resetMessages(noTabChange);
	resetLog(noTabChange);
}
void OutputViewWidget::resetLog(bool noTabChange){
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
void OutputViewWidget::showLogOrErrorList(bool noTabChange){
	if (!isVisible()) show();
	if (OutputLayout->currentIndex()!=LAYOUT_PAGE_LOG && OutputLayout->currentIndex()!=LAYOUT_PAGE_ERRORS &&!noTabChange)
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



//====================================================================
// CustomWidgetList (for left panel)
//====================================================================
CustomWidgetList::CustomWidgetList(QWidget* p): 
	QDockWidget(p), toolbox(0), frame(0),stack(0), toolbar(0)
{
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this,SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customContextMenuRequested(QPoint)));
}
void CustomWidgetList::addWidget(QWidget* widget, const QString& id, const QString& text, const QString& iconName){
	widgets << widget;
	widget->setProperty("id",id);
	widget->setProperty("Name",text);
	widget->setProperty("iconName",iconName);
	widget->setProperty("StructPos",widgets.size());

	QAction *Act = new QAction(text, this);
	Act->setCheckable(true);
	Act->setChecked(!hiddenWidgetsIds.contains(id));
	Act->setData(id);
	connect(Act, SIGNAL(toggled(bool)), this, SLOT(toggleWidgetFromAction(bool)));
	addAction(Act);
}
void CustomWidgetList::setWidgetText(const QString& id, const QString& text){
	setWidgetText(widget(id),text);
}
void CustomWidgetList::setWidgetText(const QWidget* widget, const QString& text){
	if (!widget) return;
}
void CustomWidgetList::showPageFromAction(){
	QAction* act=qobject_cast<QAction*>(sender());
	if (!act) return;
	QWidget* wid=widget(act->data().toString());
	stack->setCurrentWidget(wid);
}
void CustomWidgetList::toggleWidgetFromAction(bool on){
	QAction* act=qobject_cast<QAction*>(sender());
	if (!act || act->data().toString()=="") return;
	if (on) 
		hiddenWidgetsIds.removeAll(act->data().toString());
	else if (!hiddenWidgetsIds.contains(act->data().toString())) 
		hiddenWidgetsIds.append(act->data().toString());
	showWidgets(newStyle);
}
void CustomWidgetList::customContextMenuRequested(const QPoint& localPosition){
	QWidget *widget=currentWidget();
	if(widget && widget->underMouse()) //todo?: use a more reliable function than underMouse (see qt bug 260000)
		emit widgetContextMenuRequested(widget, mapToGlobal(localPosition));
	else{
		QMenu menu;
		menu.addActions(actions());
		menu.exec(mapToGlobal(localPosition));
	}
}
void CustomWidgetList::showWidgets(bool newLayoutStyle){
	if (toolbox) {
		for (int i=0;i<widgets.count();i++){
			toolbox->removeItem(toolbox->indexOf(widgets[i]));
			widgets[i]->setParent(this);//otherwise it will be deleted
		}
		delete toolbox;
	}
	if (stack) {
		for (int i=0;i<widgets.count();i++){
			stack->removeWidget(widgets[i]);
			widgets[i]->setParent(this);//otherwise it will be deleted
		}
		delete stack;
	}
	if (toolbar) delete toolbar;
	if (frame) delete frame; 
	newStyle=newLayoutStyle;
	if (newLayoutStyle) {
		toolbox=0;
		frame=new QFrame(this);
		frame->setLineWidth(0);
		frame->setFrameShape(QFrame::Box);
		frame->setFrameShadow(QFrame::Plain);

		toolbar=new QToolBar("LogToolBar",this);
		toolbar->setFloatable(false);
		toolbar->setOrientation(Qt::Vertical);
		toolbar->setMovable(false);
		toolbar->setIconSize(QSize(16,16 ));

		stack=new QStackedWidget(this);

		for (int i=0;i<widgets.size();i++)
			if (!hiddenWidgetsIds.contains(widgetId(widgets[i]))) {
				stack->addWidget(widgets[i]);
				QAction* act=toolbar->addAction(QIcon(widgets[i]->property("iconName").toString()),widgets[i]->property("Name").toString());
				act->setData(widgetId(widgets[i]));
				connect(act,SIGNAL(triggered()),this,SLOT(showPageFromAction()));
			} else widgets[i]->hide();
		
		QHBoxLayout* hlayout= new QHBoxLayout(frame);
		hlayout->setSpacing(0);
		hlayout->setMargin(0);
		hlayout->addWidget(toolbar);
		hlayout->addWidget(stack);
			
		setWidget(frame);
	} else {
		frame=0;
		toolbar=0;
		stack=0;
		toolbox = new QToolBox(this);
		for (int i=0;i<widgets.size();i++)
			if (!hiddenWidgetsIds.contains(widgetId(widgets[i]))) {
				toolbox->addItem(widgets[i],QIcon(widgets[i]->property("iconName").toString()),widgets[i]->property("Name").toString());
			} else widgets[i]->hide();
		setWidget(toolbox);
	}
}
int CustomWidgetList::widgetCount() const{
	return widgets.count();
}
void CustomWidgetList::setHiddenWidgets(const QString& hidden){
	hiddenWidgetsIds=hidden.split("|");
}
QString CustomWidgetList::hiddenWidgets() const{
	return hiddenWidgetsIds.join("|");
}

/*'void CustomWidgetList::addWidgetOld(QWidget* widget, const QString& text, const QIcon& icon){
}
void CustomWidgetList::addWidgetNew(QWidget* widget, const QString& text, const QIcon& icon){
	stack->addWidget(*list);
	toolbar->addAction(icon,text);
}*/

QWidget* CustomWidgetList::widget(int i) const{
	return widgets[i];
}
QWidget* CustomWidgetList::widget(const QString& id) const{
	for (int i=0;i<widgets.size();i++)
		if (widgetId(widgets[i])==id) 
			return widgets[i];
	return 0;
}
void CustomWidgetList::setCurrentWidget(QWidget* widget){
	if (newStyle) {
		stack->setCurrentWidget(widget);
	} else {
		toolbox->setCurrentWidget(widget);
	}
}
QWidget* CustomWidgetList::currentWidget() const{
	if (newStyle) return stack->currentWidget();
	else return toolbox->currentWidget();
}
QString CustomWidgetList::widgetId(QWidget* widget) const{
	if (!widget) return "";
	return widget->property("id").toString();
}
