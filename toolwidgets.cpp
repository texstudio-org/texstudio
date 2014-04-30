#include "toolwidgets.h"
#include "math.h"
#include "smallUsefulFunctions.h"
#include "qdocument.h"
#include "latexdocument.h"
#include "utilsSystem.h"

void adjustScrollBar(QScrollBar *scrollBar, double factor)
{
	scrollBar->setValue(int(factor * scrollBar->value()
							+ ((factor - 1) * scrollBar->pageStep()/2)));
}


PreviewWidget::PreviewWidget(QWidget * parent): QScrollArea(parent){
	setBackgroundRole(QPalette::Base);

	mCenter=false;

	preViewer = new QLabel(this);
	preViewer->setBackgroundRole(QPalette::Base);
	preViewer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	preViewer->setScaledContents(true);
	preViewer->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(preViewer,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenu(QPoint)));
	connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenu(QPoint)));
	setContextMenuPolicy(Qt::CustomContextMenu);

	setWidget(preViewer);
}

void PreviewWidget::scaleImage(double factor)
{
	REQUIRE(preViewer->pixmap());
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
	REQUIRE(preViewer->pixmap());
	// needs to be improved
	QSize m_size=size()-QSize(2,2);
	QSize m_labelSize=preViewer->size();
	qreal ratio=1.0*m_labelSize.height()/m_labelSize.width();
	qreal ratioPreviewer=1.0*m_size.height()/m_size.width();
	int h,w;
	if(ratioPreviewer>ratio){
		h=qRound(ratio*m_size.width());
		w=m_size.width();
		pvscaleFactor=1.0*w/preViewer->pixmap()->size().width();
	} else {
		h=m_size.height();
		w=qRound(m_size.height()/ratio);
		pvscaleFactor=1.0*h/preViewer->pixmap()->size().height();;
	}
	preViewer->resize(w,h);
	//setWidgetResizable(true);
}
void PreviewWidget::centerImage(){
	mCenter=!mCenter;
	if(mCenter) setAlignment(Qt::AlignCenter);
	else setAlignment(Qt::AlignLeft|Qt::AlignTop);
	scaleImage(1.0);
}

void PreviewWidget::zoomOut(){
	scaleImage(1/1.4);
}

void PreviewWidget::zoomIn(){
	scaleImage(1.4);
}

void PreviewWidget::resetZoom(){
	pvscaleFactor=1.0;
	scaleImage(1.0);
}

void PreviewWidget::wheelEvent(QWheelEvent *event){
	if (!preViewer->pixmap()) return;
	if(event->modifiers()==Qt::ControlModifier){
		float numDegrees = event->delta() / 8.0f;
		float numSteps = numDegrees / 15.0f;
		scaleImage(pow(1.4,numSteps));
		event->accept();
	} else QScrollArea::wheelEvent(event);
}

void PreviewWidget::contextMenu(QPoint point) {
	if (!preViewer->pixmap()) return;
	QMenu menu;
	menu.addAction(tr("zoom in "),this, SLOT(zoomIn()));
	menu.addAction(tr("zoom out"),this, SLOT(zoomOut()));
	menu.addAction(tr("reset zoom"),this, SLOT(resetZoom()));
	menu.addAction(tr("fit"),this, SLOT(fitImage()));
	if(mCenter) menu.addAction(tr("left-align image"),this, SLOT(centerImage()));
	else menu.addAction(tr("center image"),this, SLOT(centerImage()));
	QWidget* menuParent = qobject_cast<QWidget*>(sender());
	Q_ASSERT(menuParent);
	if (!menuParent) menuParent = preViewer;
	menu.exec(menuParent->mapToGlobal(point));
}

OutputViewWidget::OutputViewWidget(QWidget * parent) :
	TitledPanel(parent),
	MESSAGES_PAGE("messages"),
	LOG_PAGE("log"),
	PREVIEW_PAGE("preview"),
	SEARCH_RESULT_PAGE("search")
{
	setSelectorStyle(TabSelector);
	mToggleViewAction->setText(tr("Messages / Log File"));
	mToggleViewAction->setIcon(getRealIcon("logpanel"));


	// messages
	QFontMetrics fm(QApplication::font());
	OutputMessages = new LogEditor(this);
	OutputMessages->setFocusPolicy(Qt::ClickFocus);
	OutputMessages->setMinimumHeight(3*(fm.lineSpacing()+4));
	OutputMessages->setReadOnly(true);

	appendPage(new TitledPanelPage(OutputMessages, MESSAGES_PAGE, tr("Messages")), false);

	// log / errors
	logWidget = new LatexLogWidget(this);

	TitledPanelPage *page = new TitledPanelPage(logWidget, LOG_PAGE, tr("Log"));
	page->addToolbarActions(logWidget->displayActions());
	appendPage(page, false);

	// previewer
	previewWidget = new PreviewWidget(this);
	appendPage(new TitledPanelPage(previewWidget, PREVIEW_PAGE, tr("Preview")), false);

	// global search results
	searchResultModel = new SearchResultModel(this);

	SearchTreeDelegate *searchDelegate=new SearchTreeDelegate(this);

    QHBoxLayout *horz=new QHBoxLayout;
    QLabel *lbl=new QLabel;
    lbl->setText(tr("Search text:"));
    searchTextEdit=new QLineEdit;
    //searchTextEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    QPushButton *btn=new QPushButton(tr("Search again"));
    connect(btn,SIGNAL(clicked()),this,SLOT(updateSearch()));
    QLabel *lbl2=new QLabel;
    lbl2->setText(tr("Replace by:"));
    replaceTextEdit=new QLineEdit;
    connect(replaceTextEdit,SIGNAL(textChanged(QString)),this,SLOT(replaceTextChanged(QString)));
    //replaceTextEdit->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Fixed);
    QPushButton *btn2=new QPushButton(tr("Replace all"));
    connect(btn2,SIGNAL(clicked()),this,SLOT(replaceAll()));

    horz->addWidget(lbl);
    horz->addWidget(searchTextEdit,1);
    horz->addWidget(btn);
    horz->addWidget(lbl2);
    horz->addWidget(replaceTextEdit,1);
    horz->addWidget(btn2);

	OutputSearchTree= new QTreeView(this);
    OutputSearchTree->header()->hide();
	OutputSearchTree->setUniformRowHeights(true);
	OutputSearchTree->setModel(searchResultModel);
    OutputSearchTree->setItemDelegate(searchDelegate);

    QVBoxLayout *vert=new QVBoxLayout;

    vert->addLayout(horz);
    vert->addWidget(OutputSearchTree,1);

    QWidget *wgt=new QWidget;
    wgt->setLayout(vert);

	connect(OutputSearchTree,SIGNAL(clicked(QModelIndex)),this,SLOT(clickedSearchResult(QModelIndex)));

    //appendPage(new TitledPanelPage(OutputSearchTree, SEARCH_RESULT_PAGE, tr("Search Results")));
    appendPage(new TitledPanelPage(wgt, SEARCH_RESULT_PAGE, tr("Search Results")));
}
void OutputViewWidget::previewLatex(const QPixmap& pixmap){
	previewWidget->previewLatex(pixmap);
	//showPreview();	
}

void OutputViewWidget::replaceTextChanged(QString text){
    searchResultModel->setReplacementText(text);
}

void OutputViewWidget::updateSearch(){
    bool isWord,isCase,isReg;
    searchResultModel->getSearchConditions(isCase,isWord,isReg);
    emit updateTheSearch(mDocs,searchTextEdit->text(),replaceTextEdit->text(),isCase,isWord,isReg);
}

void OutputViewWidget::replaceAll(){
    QList<SearchInfo> searches=searchResultModel->getSearches();
    QString replaceText=replaceTextEdit->text();
    bool isWord,isCase,isReg;
    searchResultModel->getSearchConditions(isCase,isWord,isReg);
    foreach(SearchInfo search,searches){
        LatexDocument *doc=qobject_cast<LatexDocument*>(search.doc.data());
        if(!doc)
            continue;
        QDocumentCursor *cur=new QDocumentCursor(doc);
        for(int i=0;i<search.checked.size();i++){
            if(search.checked.value(i,false)){
                QDocumentLineHandle *dlh=search.lines.value(i,0);
                if(dlh){
                    QList<QPair<int,int> > results=searchResultModel->getSearchResults(dlh->text());
                    if(!results.isEmpty()){
                        QPair<int,int> elem;
                        int offset=0;
                        foreach(elem,results){
                            if(isReg){
                                QRegExp rx(searchResultModel->searchExpression(),isCase ? Qt::CaseSensitive : Qt::CaseInsensitive);
                                QString txt=dlh->text();
                                QString newText=txt.replace(rx,replaceText);
                                int lineNr=doc->indexOf(dlh,search.lineNumberHints.value(i,-1));
                                cur->select(lineNr,elem.first+offset,lineNr,elem.second+offset);
                                newText=newText.mid(elem.first);
                                newText.chop(txt.length()-elem.second-1);
                                cur->replaceSelectedText(newText);
                                offset+=newText.length()-elem.second+elem.first;
                            }else{
                                // simple replacement
                                int lineNr=doc->indexOf(dlh,search.lineNumberHints.value(i,-1));
                                cur->select(lineNr,elem.first+offset,lineNr,elem.second+offset);
                                cur->replaceSelectedText(replaceText);
                                offset+=replaceText.length()-elem.second+elem.first;
                            }
                        }
                    }
                }
            }
        }
        delete cur;
    }
}

void OutputViewWidget::clickedSearchResult(const QModelIndex& index){
	QDocument* doc = searchResultModel->getDocument(index);
    if(!searchResultModel->parent(index).isValid())
        return;
	if (!doc) return;
	emit jumpToSearch(doc,searchResultModel->getLineNumber(index));
}

void OutputViewWidget::copySearchResult() {
	QApplication::clipboard()->setText(OutputSearchTree->currentIndex().data(Qt::DisplayRole).toString());
}

//copied and modified from qbytearray.cpp
//should be an optimization for qtextstream, but doesn't really improve anything
QByteArray simplifyLineConserving(const QByteArray& ba)
{
	if (ba.size() == 0)
		return QByteArray();
	QByteArray result(ba.size(), Qt::Uninitialized);
	const char *from = ba.constData();
	const char *fromend = from + ba.size();
	int outc=0;
	char *to = result.data();
	for (;;) {
		while (from!=fromend && isspace(uchar(*from)))
			from++;
		while (from!=fromend && !isspace(uchar(*from)))
			to[outc++] = *from++;
		if (from!=fromend) {
			if (uchar(*from) == '\n' || uchar(*from) == '\r') to[outc++] = '\n';
			else to[outc++] = ' ';
		} else
			break;
	}
	if (outc > 0 && to[outc-1] == ' ')
		outc--;
	result.resize(outc);
	return result;
}

bool OutputViewWidget::isPreviewPanelVisible(){
	if (!isVisible()) return false;
	return currentPageId() == PREVIEW_PAGE;
}

void OutputViewWidget::setMessage(const QString &message){
	setCurrentPage(MESSAGES_PAGE);
	OutputMessages->setText(message);
}

void OutputViewWidget::insertMessageLine(const QString &message){
	OutputMessages->insertLine(message);
}

void OutputViewWidget::copy() {
	QString pageId = currentPageId();

	if (pageId == LOG_PAGE) {
		logWidget->copy();
	} else if (pageId == SEARCH_RESULT_PAGE) {
		copySearchResult();
	}
}

void OutputViewWidget::resetMessages(bool noTabChange){
	OutputMessages->clear();
	if(!noTabChange) setCurrentPage(MESSAGES_PAGE);
}
void OutputViewWidget::resetMessagesAndLog(bool noTabChange){
	resetMessages(noTabChange);
	logWidget->resetLog();
}
void OutputViewWidget::selectLogEntry(int logEntryNumber, bool makeVisible){
	if (!logWidget->logEntryNumberValid(logEntryNumber)) return;
	if (makeVisible) showPage(LOG_PAGE);
	logWidget->selectLogEntry(logEntryNumber);
}

void OutputViewWidget::retranslateUi() {
	mToggleViewAction->setText(tr("Messages / Log File"));
	pageFromId(MESSAGES_PAGE)->setTitle(tr("Messages"));
	pageFromId(LOG_PAGE)->setTitle(tr("Log"));
	pageFromId(PREVIEW_PAGE)->setTitle(tr("Preview"));
	pageFromId(SEARCH_RESULT_PAGE)->setTitle(tr("Search Results"));
	updateTopbar();
}

/*
void OutputViewWidget::gotoLogLine(int logLine){
	logWidget->gotoLogEntry(logModel->logLineNumberToLogEntryNumber(logLine));
}*/


void OutputViewWidget::addSearch(QList<QDocumentLineHandle *> lines, QDocument* doc){
	SearchInfo search;
	search.doc = doc;
	search.lines = lines;
    for(int i=0;i<lines.count();i++){
        search.checked << true;
    }
	searchResultModel->addSearch(search);
}
void OutputViewWidget::clearSearch(){
	searchResultModel->clear();
}
void OutputViewWidget::setSearchExpression(QString exp,QString replaceText,bool isCase,bool isWord,bool isRegExp){
    replaceTextEdit->setText(replaceText);
    searchTextEdit->setText(exp);
    searchResultModel->setSearchExpression(exp,replaceText,isCase,isWord,isRegExp);
}

void OutputViewWidget::setSearchExpression(QString exp,bool isCase,bool isWord,bool isRegExp){
    searchTextEdit->setText(exp);
    searchResultModel->setSearchExpression(exp,isCase,isWord,isRegExp);
}
QString OutputViewWidget::searchExpression() const {
	return searchResultModel->searchExpression();
}
int OutputViewWidget::getNextSearchResultColumn(QString text,int col){
	return searchResultModel->getNextSearchResultColumn(text,col);
}
bool OutputViewWidget::childHasFocus(){
	return logWidget->childHasFocus()
			|| OutputMessages->hasFocus()
			|| OutputSearchTree->hasFocus();
}

void OutputViewWidget::changeEvent(QEvent *event){
	switch (event->type()) {
	case QEvent::LanguageChange:
		retranslateUi();
		break;
	default:
		break;
	}	
}

//====================================================================
// CustomDelegate for search results
//====================================================================
SearchTreeDelegate::SearchTreeDelegate(QObject *parent):QItemDelegate(parent)
{
    ;
}

void SearchTreeDelegate::paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QPalette::ColorGroup    cg  = option.state & QStyle::State_Enabled ? QPalette::Normal : QPalette::Disabled;

    /*if( cg == QPalette::Normal && !(option.state & QStyle::State_Active) )
        cg = QPalette::Inactive;*/

    if( option.state & QStyle::State_Selected )
    {
        painter->fillRect( option.rect, option.palette.brush(cg, QPalette::Highlight) );
        painter->setPen( option.palette.color(cg, QPalette::HighlightedText) );
    }
    else
    {
        painter->setPen( option.palette.color(cg, QPalette::Text) );
    }

    QSize size;
    if(index.data(Qt::CheckStateRole).isValid()){
#if QT_VERSION >= 0x050201  /* QItemDelegate::check is an internal function which has been renamed (maybe already in Qt5.2?) */
		size = doCheck(option, option.rect, Qt::Checked).size();
#else
        size = check(option, option.rect, Qt::Checked).size();
#endif
        QRect checkboxRect(option.rect.x(),option.rect.y(),size.width(),size.height());
        QItemDelegate::drawCheck(painter, option, checkboxRect, (Qt::CheckState) index.data(Qt::CheckStateRole).toInt());
    }

    if( index.data().toString().isEmpty() )
        return;
    painter->save();
    QString text=index.data().toString();
    QRect r=option.rect;
    r.adjust(size.width(),0,0,0);
    QStringList textList=text.split("|");
    for(int i=0;i<textList.size();i++){
        QString temp=textList.at(i);
        int w=option.fontMetrics.width(temp);
        if(i%2) {
            painter->fillRect( QRect(r.left(),r.top(),w,r.height()), QBrush(Qt::yellow) );
        }
        painter->drawText(r,Qt::AlignLeft || Qt::AlignTop || Qt::TextSingleLine, temp);
        r.setLeft(r.left()+w+1);
    }
    painter->restore();
}

QSize SearchTreeDelegate::sizeHint(const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
 {
       QFontMetrics fontMetrics = option.fontMetrics;
       QRect rect = fontMetrics.boundingRect(index.data().toString());
       return QSize(rect.width(), rect.height());
}

//====================================================================
// CustomWidgetList (for left panel)
//====================================================================

Q_DECLARE_METATYPE(QAction*)

CustomWidgetList::CustomWidgetList(QWidget* p):
	QDockWidget(p), toolbox(0), frame(0),stack(0), toolbar(0)
{
    toggleViewAction()->setIcon(getRealIcon("sidebar"));
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
void CustomWidgetList::setWidgetText(QWidget* widget, const QString& text){
	int pos=widgets.indexOf(widget);
	if (pos<0) return;
	widget->setProperty("Name",text);
	if (newStyle) actions()[pos]->setToolTip(text);
	else toolbox->setItemText(pos,text);
}
void CustomWidgetList::setWidgetIcon(const QString& id, const QString& icon){
	setWidgetIcon(widget(id), icon);
}

void CustomWidgetList::setWidgetIcon(QWidget* widget, const QString& icon){
	int pos=widgets.indexOf(widget);
	if (pos<0) return;
	widget->setProperty("iconName",icon);
}

void CustomWidgetList::showPageFromAction(){
	QAction* act=qobject_cast<QAction*>(sender());
	if (!act) return;
	QWidget* wid=widget(act->data().toString());
	stack->setCurrentWidget(wid);
	setWindowTitle(act->toolTip());
	foreach (QAction* a, toolbar->actions())
		a->setChecked(a==act);
}
void CustomWidgetList::currentWidgetChanged(int i){
	Q_ASSERT(newStyle==false);
	setWindowTitle(toolbox->itemText(i));
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
				act->setCheckable(true);
				if (i==0) act->setChecked(true);
				act->setData(widgetId(widgets[i]));
				connect(act,SIGNAL(triggered()),this,SLOT(showPageFromAction()));
				widgets[i]->setProperty("associatedAction", QVariant::fromValue<QAction*>(act));
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
		connect(toolbox,SIGNAL(currentChanged(int)),SLOT(currentWidgetChanged(int)));
		setWidget(toolbox);

	}
	if (!widgets.empty()) //name after active (first) widget
		setWindowTitle(widgets.first()->property("Name").toString());
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
		QAction* act = widget->property("associatedAction").value<QAction*>();
		foreach (QAction* a, toolbar->actions())
			a->setChecked(a==act);
	} else {
		toolbox->setCurrentWidget(widget);
	}
}
QWidget* CustomWidgetList::currentWidget() const{
	if (newStyle) return stack->currentWidget();
	else return toolbox->currentWidget();
}
bool CustomWidgetList::isNewLayoutStyleEnabled() const{
	return newStyle;
}
QString CustomWidgetList::widgetId(QWidget* widget) const{
	if (!widget) return "";
	return widget->property("id").toString();
}
