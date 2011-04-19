/*
	This is part of TeXworks, an environment for working with TeX documents
	Copyright (C) 2007-2010  Jonathan Kew

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	For links to further information, or to contact the author,
	see <http://texworks.org/>.
*/

#ifndef NO_POPPLER_PREVIEW

// Based on code by Pino Toscano from Poppler / qt4 / Demos, released under GPL 2 or later

#include "PDFDocks.h"
#include "PDFDocument.h"
#include "math.h"

#include <QTreeWidget>
#include <QHeaderView>
#include <QListWidget>
#include <QTableWidget>

PDFDock::PDFDock(PDFDocument *doc)
	: QDockWidget("", doc), document(doc), filled(false)
{
	connect(this, SIGNAL(visibilityChanged(bool)), SLOT(myVisibilityChanged(bool)));
	//TODO:	connect(TWApp::instance(), SIGNAL(updatedTranslators()), this, SLOT(changeLanguage()));
}

PDFDock::~PDFDock()
{
}

void PDFDock::documentLoaded()
{
	if (!isHidden()) {
		fillInfo();
		filled = true;
	}
}

void PDFDock::documentClosed()
{
	filled = false;
}

void PDFDock::pageChanged(int page)
{
	Q_UNUSED(page)
}

void PDFDock::myVisibilityChanged(bool visible)
{
	setWindowTitle(getTitle());
	if (visible && document && !filled) {
		fillInfo();
		filled = true;
	}
}

void PDFDock::changeLanguage()
{
	setWindowTitle(getTitle());
}

//////////////// OUTLINE ////////////////

static void fillToc(const QDomNode &parent, QTreeWidget *tree, QTreeWidgetItem *parentItem)
{
	QTreeWidgetItem *newitem = 0;
	for (QDomNode node = parent.firstChild(); !node.isNull(); node = node.nextSibling()) {
		QDomElement e = node.toElement();

		if (!parentItem)
			newitem = new QTreeWidgetItem(tree, newitem);
		else
			newitem = new QTreeWidgetItem(parentItem, newitem);
		newitem->setText(0, e.tagName());

		bool isOpen = false;
		if (e.hasAttribute("Open"))
			isOpen = QVariant(e.attribute("Open")).toBool();
		if (isOpen)
			tree->expandItem(newitem);

		if (e.hasAttribute("DestinationName"))
			newitem->setText(1, e.attribute("DestinationName"));

		if (e.hasChildNodes())
			fillToc(node, tree, newitem);
	}
}

PDFOutlineDock::PDFOutlineDock(PDFDocument *doc)
	: PDFDock(doc)
{
	setObjectName("outline");
	tree = new PDFDockTreeWidget(this);
	tree->setAlternatingRowColors(true);
	tree->header()->hide();
	tree->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	setWidget(tree);
	setWindowTitle(getTitle());
}

PDFOutlineDock::~PDFOutlineDock()
{
}

void PDFOutlineDock::changeLanguage()
{
	PDFDock::changeLanguage();
	if (filled)
		fillInfo();
}

void PDFOutlineDock::fillInfo()
{
	tree->clear();
	if (!document || !document->popplerDoc()) return;
	const QDomDocument *toc = document->popplerDoc()->toc();
	if (toc) {
		fillToc(*toc, tree, 0);
		connect(tree, SIGNAL(itemSelectionChanged()), this, SLOT(followTocSelection()));
		delete toc;
	} else {
		QTreeWidgetItem *item = new QTreeWidgetItem();
		item->setText(0, tr("No TOC"));
		item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
		tree->addTopLevelItem(item);
	}
}

void PDFOutlineDock::documentClosed()
{
	tree->clear();
	PDFDock::documentClosed();
}

void PDFOutlineDock::followTocSelection()
{
	QList<QTreeWidgetItem*> items = tree->selectedItems();
	if (items.count() > 0) {
		QTreeWidgetItem* item = items.first();
		QString dest = item->text(1);
		if (!dest.isEmpty())
			document->goToDestination(dest);
	}
}

PDFDockTreeWidget::PDFDockTreeWidget(QWidget* parent)
	: QTreeWidget(parent)
{
}

PDFDockTreeWidget::~PDFDockTreeWidget()
{
}

QSize PDFDockTreeWidget::sizeHint() const
{
	return QSize(120, 300);
}

//////////////// PDF INFO ////////////////

PDFInfoDock::PDFInfoDock(PDFDocument *doc)
	: PDFDock(doc)
{
	setObjectName("pdfinfo");
	setWindowTitle(getTitle());
	list = new PDFDockListWidget(this);
	list->setAlternatingRowColors(true);
	setWidget(list);
}

PDFInfoDock::~PDFInfoDock()
{
}

void PDFInfoDock::fillInfo()
{
	list->clear();
	if (!document || !document->popplerDoc()) return;
	Poppler::Document *doc = document->popplerDoc();
	QStringList keys = doc->infoKeys();
	QStringList dateKeys;
	dateKeys << "CreationDate";
	dateKeys << "ModDate";
	int i = 0;
	foreach (const QString &date, dateKeys) {
		const int id = keys.indexOf(date);
		if (id != -1) {
			list->addItem(date + ":");
			list->addItem(doc->date(date).toString(Qt::SystemLocaleDate));
			++i;
			keys.removeAt(id);
		}
	}
	foreach (const QString &key, keys) {
		list->addItem(key + ":");
		list->addItem(doc->info(key));
		++i;
	}
}

void PDFInfoDock::documentClosed()
{
	list->clear();
	PDFDock::documentClosed();
}

PDFDockListWidget::PDFDockListWidget(QWidget *parent)
	: QListWidget(parent)
{
}

PDFDockListWidget::~PDFDockListWidget()
{
}

QSize PDFDockListWidget::sizeHint() const
{
	return QSize(200, 300);
}

//////////////// FONT LIST ////////////////

PDFFontsDock::PDFFontsDock(PDFDocument *doc)
	: PDFDock(doc)
	, scannedFonts(false)
{
	setObjectName("fonts");
	setWindowTitle(getTitle());
	table = new QTableWidget(this);
#ifdef Q_WS_MAC /* don't do this on windows, as the font ends up too small */
	QFont f(table->font());
	f.setPointSize(f.pointSize() - 2);
	table->setFont(f);
#endif
	table->setColumnCount(4);
	setHorizontalHeaderLabels();
	table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setAlternatingRowColors(true);
	table->setShowGrid(false);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->verticalHeader()->hide();
	table->horizontalHeader()->setStretchLastSection(true);
	table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	setWidget(table);
}

PDFFontsDock::~PDFFontsDock()
{
}

void PDFFontsDock::changeLanguage()
{
	PDFDock::changeLanguage();
	setHorizontalHeaderLabels();
	if (filled)
		fillInfo();
}

void PDFFontsDock::setHorizontalHeaderLabels()
{
	if (table)
		table->setHorizontalHeaderLabels(QStringList() << tr("Name") << tr("Type") << tr("Subset") << tr("File"));
}

void PDFFontsDock::fillInfo()
{
	if (!document || !document->popplerDoc()) return;
	if (!scannedFonts) {
		fonts = document->popplerDoc()->fonts();
		scannedFonts = true;
	}
	table->clearContents();
	table->setRowCount(0);
	table->setRowCount(fonts.count());
	int i = 0;
	foreach (const Poppler::FontInfo &font, fonts) {
		if (font.name().isNull()) {
			table->setItem(i, 0, new QTableWidgetItem(tr("[none]")));
		} else {
			table->setItem(i, 0, new QTableWidgetItem(font.name()));
		}
		table->setItem(i, 1, new QTableWidgetItem(font.typeName()));
		table->setItem(i, 2, new QTableWidgetItem(font.isSubset() ? tr("yes") : tr("no")));
		table->setItem(i, 3, new QTableWidgetItem(font.isEmbedded() ? tr("[embedded]") : font.file()));
		++i;
	}
	table->resizeColumnsToContents();
	table->resizeRowsToContents();
}

void PDFFontsDock::documentLoaded()
{
	scannedFonts = false;
	fonts.clear();
	PDFDock::documentLoaded();
}

void PDFFontsDock::documentClosed()
{
	scannedFonts = false;
	fonts.clear();
	table->clear();
	table->setRowCount(0);
	PDFDock::documentClosed();
}

//////////////// SEARCH DOCK ////////////////

PDFBaseSearchDock::PDFBaseSearchDock(PDFDocument* doc): QDockWidget(doc), document(doc){
	// do it completely programatic
	setObjectName("Search");
	setWindowTitle(tr("Search"));
	//this->resize(801, 31);
	QWidget* tempWidget = new QWidget(this);
	setWidget(tempWidget);
	QGridLayout *gridLayout = new QGridLayout(tempWidget);
	gridLayout->setContentsMargins(-1, 4, -1, 4);
	QFrame* frame_2 = new QFrame(this);
	frame_2->setObjectName(("frame_2"));
	QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
	frame_2->setSizePolicy(sizePolicy1);
	frame_2->setMinimumSize(QSize(0, 22));
	frame_2->setFrameShape(QFrame::NoFrame);
	frame_2->setLineWidth(0);
	QHBoxLayout* hboxLayout = new QHBoxLayout(frame_2);
	hboxLayout->setObjectName(("hboxLayout"));
	hboxLayout->setContentsMargins(-1, 0, -1, 0);

	QSize buttonSize(22,22);
	/*
	bClose = new QToolButton(frame_2);
	bClose->setObjectName(("bClose"));
	bClose->setMinimumSize(buttonSize);
	bClose->setMaximumSize(buttonSize);
	bClose->setIcon(QIcon(":/closeall.png"));

	hboxLayout->addWidget(bClose);
	*/
	QLabel* label = new QLabel(frame_2);
	label->setObjectName(("label"));
	QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
	sizePolicy3.setHorizontalStretch(0);
	sizePolicy3.setVerticalStretch(0);
	sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
	label->setSizePolicy(sizePolicy3);
	label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

	hboxLayout->addWidget(label);


	gridLayout->addWidget(frame_2, 0, 0, 1, 1);

	leFind = new QLineEdit(this);
	leFind->setObjectName(("leFind"));
	QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
	sizePolicy4.setHorizontalStretch(2);
	leFind->setSizePolicy(sizePolicy4);
	leFind->setMinimumSize(QSize(120, 22));

	gridLayout->addWidget(leFind, 0, 1, 1, 1);

	bNext = new QToolButton(this);
	bNext->setObjectName(("bNext"));
	bNext->setMinimumSize(buttonSize);
	bNext->setMaximumSize(buttonSize);
	bNext->setIcon(QIcon(":/down.png"));

	gridLayout->addWidget(bNext, 0, 3, 1, 1);

	bPrevious = new QToolButton(this);
	bPrevious->setObjectName(("bPrevious"));
	bPrevious->setMinimumSize(buttonSize);
	bPrevious->setMaximumSize(buttonSize);
	bPrevious->setIcon(QIcon(":/up.png"));

	gridLayout->addWidget(bPrevious, 0, 4, 1, 1);
/*
	bCount = new QToolButton(this);
	bCount->setObjectName(("bCount"));
	bCount->setMinimumSize(buttonSize);
	bCount->setMaximumSize(buttonSize);
	bCount->setIcon(QIcon(":/images/qcodeedit/count.png"));

	gridLayout->addWidget(bCount, 0, 5, 1, 1);
*/
	QFrame* frame_6 = new QFrame(this);
	sizePolicy1.setHeightForWidth(frame_6->sizePolicy().hasHeightForWidth());
	frame_6->setSizePolicy(sizePolicy1);
	frame_6->setFrameShape(QFrame::NoFrame);
	gridLayout1 = new QGridLayout(frame_6);
	gridLayout1->setContentsMargins(0, 0, 0, 0);
	cbCase = new QCheckBox(frame_6);
	cbCase->setObjectName(("cbCase"));
	cbCase->setToolTip(tr("Enables case sensitive search."));
	cbCase->setChecked(true);

	gridLayout1->addWidget(cbCase, 0, 0, 1, 1);
/*
	cbWords = new QCheckBox(frame_6);
	cbWords->setToolTip(tr("Only searches for whole words."));
	cbWords->setObjectName(("cbWords"));

	gridLayout1->addWidget(cbWords, 0, 1, 1, 1);

	cbRegExp = new QCheckBox(frame_6);
	cbRegExp->setToolTip(tr("This interprets the search text as a regular expression.\nSome common regexps:\n r* will find any amount of r, r+ is equal to rr*, a? will matches a or nothing,\n () groups expressions together, [xyz] will find x,y, or z, . matches everything, \\. matches .\nYou can use \\1 to \\9 in the replace text to insert a submatch."));
	cbRegExp->setObjectName(("cbRegExp"));

	gridLayout1->addWidget(cbRegExp, 0, 2, 1, 1);
*/
/*	cbHighlight = new QCheckBox(frame_6);
	cbHighlight->setObjectName(("cbHighlight"));
	cbHighlight->setChecked(true);
	cbHighlight->setToolTip(tr("Highlights search matches and replaced text."));
	sizePolicy3.setHeightForWidth(cbHighlight->sizePolicy().hasHeightForWidth());
	cbHighlight->setSizePolicy(sizePolicy3);

	gridLayout1->addWidget(cbHighlight, 0, 3, 1, 1);

	cbCursor = new QCheckBox(frame_6);
	cbCursor->setToolTip(tr("Starts the search from the current cursor position."));
	cbCursor->setObjectName(("cbCursor"));
	cbCursor->setChecked(true);

	gridLayout1->addWidget(cbCursor, 0, 4, 1, 1);

	cbSelection = new QCheckBox(frame_6);
	cbSelection->setToolTip(tr("Only searches in the selected text."));
	cbSelection->setObjectName(("cbSelection"));

	gridLayout1->addWidget(cbSelection, 0, 5, 1, 1);
*/

	gridLayout->addWidget(frame_6, 0, 6, 2, 2,Qt::AlignTop);


	//retranslateUi(this);
	//QObject::connect(bClose, SIGNAL(clicked()), this, SLOT(close()));

	// connect by name
	QMetaObject::connectSlotsByName(this);

	// set texts
	//bClose->setToolTip(QApplication::translate("SearchReplace", "Close search/replace panel", 0, QApplication::UnicodeUTF8));
	leFind->setToolTip(QApplication::translate("SearchReplace", "Text or pattern to search for", 0, QApplication::UnicodeUTF8));
	bNext->setToolTip(QApplication::translate("SearchReplace", "Find next occurence", 0, QApplication::UnicodeUTF8));
	bPrevious->setToolTip(QApplication::translate("SearchReplace", "Find previous occurence", 0, QApplication::UnicodeUTF8));
//	bCount->setToolTip(QApplication::translate("SearchReplace", "Count occurences", 0, QApplication::UnicodeUTF8));

	label->setText(QApplication::translate("SearchReplace", " Find :", 0, QApplication::UnicodeUTF8));
	label->setMinimumWidth(label->sizeHint().width());
	cbCase->setText(QApplication::translate("SearchReplace", "Case", 0, QApplication::UnicodeUTF8));
	cbCase->setMinimumWidth(cbCase->sizeHint().width());
/*	cbWords->setText(QApplication::translate("SearchReplace", "Words", 0, QApplication::UnicodeUTF8));
	cbWords->setMinimumWidth(cbWords->sizeHint().width());
	cbRegExp->setText(QApplication::translate("SearchReplace", "Regexp", 0, QApplication::UnicodeUTF8));
	cbRegExp->setMinimumWidth(cbRegExp->sizeHint().width());*/
/*	cbHighlight->setText(QApplication::translate("SearchReplace", "Highlight all", 0, QApplication::UnicodeUTF8));
	cbHighlight->setMinimumWidth(cbHighlight->sizeHint().width());
	cbCursor->setText(QApplication::translate("SearchReplace", "Cursor", 0, QApplication::UnicodeUTF8));
	cbCursor->setMinimumWidth(cbCursor->sizeHint().width());
	cbSelection->setText(QApplication::translate("SearchReplace", "Selection", 0, QApplication::UnicodeUTF8));
	cbSelection->setMinimumWidth(cbSelection->sizeHint().width());*/
	//bReplaceAll->setText(QApplication::translate("SearchReplace", "all", 0, QApplication::UnicodeUTF8));

	minimum_width=frame_2->sizeHint().width()+leFind->sizeHint().width()+2*bNext->sizeHint().width()+5*hboxLayout->spacing();
	//;

	cbCase->setChecked(false);

	leFind->installEventFilter(this);

	listOfWidget << cbCase;// << cbWords << cbRegExp/* << cbHighlight << cbCursor << cbSelection*/;
}

QString PDFBaseSearchDock::getSearchText() const{
	return leFind->text();
}
bool PDFBaseSearchDock::hasFlagCaseSensitive() const{
	return cbCase->isChecked();
}
void PDFBaseSearchDock::setFocus(){
	leFind->setFocus();
}

void PDFBaseSearchDock::resizeEvent(QResizeEvent *e){
	int w=e->size().width();
	w=w-minimum_width; // remaining space
	int row=0;
	int col=0;
	int remaining_space=w;
	foreach(QWidget *wdg,listOfWidget){
		remaining_space=remaining_space-wdg->minimumWidth();
		if(remaining_space>0){
			gridLayout1->addWidget(wdg, row, col, 1, 1);
			col++;
		}else{
			col=0;
			row++;
			gridLayout1->addWidget(wdg, row, col, 1, 1);
			col++;
			remaining_space=w-wdg->minimumWidth();
		}
	}
	QDockWidget::resizeEvent(e);
}

bool PDFBaseSearchDock::eventFilter(QObject *o, QEvent *e)
{
	int kc;

	if ( o == leFind)
	{
		switch ( e->type() )
		{
			case QEvent::KeyPress :

				kc = static_cast<QKeyEvent*>(e)->key();

				if ( (kc == Qt::Key_Enter) || (kc == Qt::Key_Return) )
					emit search(Qt::ShiftModifier & static_cast<QKeyEvent*>(e)->modifiers(), false);
				else if ( kc == Qt::Key_Escape)
					close();
				break;

			default:
				break;
		}
	}

	return QWidget::eventFilter(o, e);
}

void PDFBaseSearchDock::on_leFind_textEdited(const QString&){
	emit search(false, true);
}

void PDFBaseSearchDock::on_bNext_clicked(){
	emit search(false, false);
}

void PDFBaseSearchDock::on_bPrevious_clicked(){
	emit search(true, false);
}




PDFSearchDock::PDFSearchDock(PDFDocument *doc): PDFBaseSearchDock(doc){
	cbSync = new QCheckBox(this);
	cbSync->setObjectName("cbSync");
	cbSync->setText(tr("Sync"));
	cbSync->setChecked(true);

	gridLayout1->addWidget(cbSync, 0, 3, 1, 1);

	listOfWidget << cbSync;
}

bool PDFSearchDock::hasFlagSync() const {
	return cbSync->isChecked();
}


//////////////// SCROLL AREA ////////////////

PDFScrollArea::PDFScrollArea(QWidget *parent)
	: QAbstractScrollArea(parent),continuous(true),pdf(0)
{
	viewport()->setBackgroundRole(QPalette::NoRole);
	verticalScrollBar()->setSingleStep(20);
	horizontalScrollBar()->setSingleStep(20);
}

void PDFScrollArea::setPDFWidget(PDFWidget* widget){
	//from qt
	if (pdf == widget) return;
	if (pdf) delete pdf;
	pdf = 0;
	horizontalScrollBar()->setValue(0);
	verticalScrollBar()->setValue(0);
	if (widget->parentWidget() != viewport())
		widget->setParent(viewport());
	if (!widget->testAttribute(Qt::WA_Resized))
	    widget->resize(widget->sizeHint());
	pdf = widget;
	pdf->setAutoFillBackground(true);
	pdf->installEventFilter(this);
	updateScrollBars();
	pdf->show();

}

void PDFScrollArea::ensureVisible(int x, int y, int xmargin, int ymargin){
	int logicalX = QStyle::visualPos(layoutDirection(), viewport()->rect(), QPoint(x, y)).x();

	if (logicalX - xmargin < horizontalScrollBar()->value()) {
	    horizontalScrollBar()->setValue(qMax(0, logicalX - xmargin));
	} else if (logicalX > horizontalScrollBar()->value() + viewport()->width() - xmargin) {
	    horizontalScrollBar()->setValue(qMin(logicalX - viewport()->width() + xmargin, horizontalScrollBar()->maximum()));
	}

	if (y - ymargin < verticalScrollBar()->value()) {
	    verticalScrollBar()->setValue(qMax(0, y - ymargin));
	} else if (y > verticalScrollBar()->value() + viewport()->height() - ymargin) {
	    verticalScrollBar()->setValue(qMin(y - viewport()->height() + ymargin, verticalScrollBar()->maximum()));
	}
}

PDFScrollArea::~PDFScrollArea()
{

}

void PDFScrollArea::setContinuous(bool cont){
	Q_ASSERT(pdf);
	if (cont == continuous) return;
	continuous = cont;
	if (!cont) pdf->setGridSize(pdf->gridCols(), 1);
	else resizeEvent(0);
}

bool PDFScrollArea::event(QEvent * e){
	if (e->type() == QEvent::StyleChange || e->type() == QEvent::LayoutRequest) {
		updateScrollBars();
	}
/*   #ifdef QT_KEYPAD_NAVIGATION
	else if (QApplication::keypadNavigationEnabled()) {
	    if (e->type() == QEvent::Show)
		 QApplication::instance()->installEventFilter(this);
	    else if (e->type() == QEvent::Hide)
		 QApplication::instance()->removeEventFilter(this);
	}
   #endif*/
	return QAbstractScrollArea::event(e);
}

bool PDFScrollArea::eventFilter(QObject * o, QEvent * e){
	if (o == pdf && e->type() == QEvent::Resize) {
		if (continuous)
			pdf->setGridSize(pdf->gridCols(), height() / pdf->gridRowHeight() + 2);
		updateScrollBars();
	}

	return false;
}

void
PDFScrollArea::resizeEvent(QResizeEvent *event)
{
	Q_ASSERT(pdf);
	if (continuous)
		pdf->setGridSize(pdf->gridCols(), height() / pdf->gridRowHeight() + 2);
	emit resized();
	updateScrollBars();
}

void PDFScrollArea::scrollContentsBy(int dx, int dy)
{
	Q_ASSERT(pdf);
	updateWidgetPosition();
}

void PDFScrollArea::updateWidgetPosition(){
	Q_ASSERT(pdf);
	Qt::LayoutDirection dir = layoutDirection();
	QScrollBar* hbar = horizontalScrollBar(), *vbar = verticalScrollBar();
	if (!continuous) {
		//from qt
		QRect scrolled = QStyle::visualRect(dir, viewport()->rect(), QRect(QPoint(-hbar->value(), -vbar->value()), pdf->size()));
		QRect aligned = QStyle::alignedRect(dir, Qt::AlignCenter, pdf->size(), viewport()->rect());
		pdf->move(pdf->width() < viewport()->width() ? aligned.x() : scrolled.x(),
			      pdf->height() < viewport()->height() ? aligned.y() : scrolled.y());
	} else {
		int rowHeight = pdf->gridRowHeight();
		QRect scrolled = QStyle::visualRect(dir, viewport()->rect(), QRect(QPoint(-hbar->value(), -(vbar->value() % rowHeight)), pdf->size()));
		QRect aligned = QStyle::alignedRect(dir, Qt::AlignCenter, pdf->size(), viewport()->rect());
		pdf->move(pdf->width() < viewport()->width() ? aligned.x() : scrolled.x(),
			      pdf->height() < viewport()->height() ? aligned.y() : scrolled.y());
		pdf->goToPage((vbar->value() / rowHeight)*pdf->gridCols() ,true);
	}
}

void PDFScrollArea::updateScrollBars(){
	Q_ASSERT(pdf);
	QScrollBar* hbar = horizontalScrollBar(), *vbar = verticalScrollBar();

	QSize p = viewport()->size();
	QSize m = maximumViewportSize();

	if (m.expandedTo(pdf->size()) == m)
	    p = m; // no scroll bars needed

	QSize v = pdf->size();

	hbar->setRange(0, v.width() - p.width());
	hbar->setPageStep(p.width());
	if (!continuous) {
		vbar->setRange(0, v.height() - p.height());
	} else {
		vbar->setRange(0,((pdf->numPages() + pdf->gridCols() - 1)/ pdf->gridCols() - 1) * pdf->gridRowHeight() );
	}
	vbar->setPageStep(p.height());
	updateWidgetPosition();

}


//////////////// Overview ////////////////
struct renderInfo{
    Poppler::Page *page;
    PDFWidget *widget;
};


PDFOverviewDock::PDFOverviewDock(PDFDocument *doc)
	: PDFDock(doc)
{
	setObjectName("outline");
	setWindowTitle(getTitle());
	list = new PDFDockListWidget(this);
	list->setViewMode(QListView::IconMode);
	list->setIconSize(QSize(128, 128));
	list->setMovement(QListView::Static);
	list->setSpacing(12);
	list->setBackgroundRole(QPalette::Mid);
	setWidget(list);
	renderEngine.start();
	connect(&renderEngine,SIGNAL(sendImage(QImage,int)),this,SLOT(insertImage(QImage,int)));
}

PDFOverviewDock::~PDFOverviewDock()
{
    renderEngine.stop();
    renderEngine.wait();
}

void PDFOverviewDock::changeLanguage()
{
	PDFDock::changeLanguage();
	if (filled)
		fillInfo();
}

void PDFOverviewDock::fillInfo()
{
    list->clear();
    toGenerate=0;
    if (!document || !document->popplerDoc()) return;
    Poppler::Document *dc=Poppler::Document::load(document->fileName());
    renderEngine.setDocument(dc);
    Poppler::Document *doc = document->popplerDoc();
    int sx=128;
    int sy=128;
    if(doc->numPages()>0){
	Poppler::Page* page=doc->page(0);
	QSize  sz=page->pageSize();
	if(sz.width()>sz.height()){
	    sy=floor(1.0*sz.height()/sz.width()*sx+0.5);
	}else{
	    sx=floor(1.0*sz.width()/sz.height()*sy+0.5);
	}
	delete page;
    }
    QPixmap pxMap(sx,sy);
    pxMap.fill();
    for(int i=0;i<doc->numPages();i++){
	    QListWidgetItem *lw = new QListWidgetItem(list);

	    lw->setIcon(QIcon(pxMap));
	    lw->setBackgroundColor(Qt::gray);
	    lw->setText(QString("%1").arg(i+1));
	    connect(list, SIGNAL(itemSelectionChanged()), this, SLOT(followTocSelection()));
    }

    list->setCurrentRow(0);
    showImage();
}

void PDFOverviewDock::documentClosed()
{
    list->clear();
    PDFDock::documentClosed();
}

void PDFOverviewDock::followTocSelection()
{
    QList<QListWidgetItem* >lst=list->selectedItems();
    if(lst.isEmpty())
	return;
    int page=lst.first()->text().toInt();
    document->goToPage(page-1);
}

void PDFOverviewDock::pageChanged(int page)
{
    list->setCurrentRow(page);
}

void PDFOverviewDock::showImage(){
    Poppler::Document *doc = document->popplerDoc();
    for(int i=0;i<doc->numPages();i++){
	Poppler::Page* page=doc->page(i);
	QImage image=page->thumbnail();
	if(image.isNull()){
	    RenderCommand cmd(i);
	    renderEngine.enqueue(cmd);
	}else{
	    insertImage(image,i);
	}
	delete page;
    }
}

void PDFOverviewDock::insertImage(QImage image,int page){
    QPixmap pxMap=QPixmap::fromImage(image.scaled(128,128,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    QListWidgetItem *lw = list->item(page);
    lw->setIcon(QIcon(pxMap));
}



PDFClockDock::PDFClockDock(PDFDocument *parent):PDFDock(parent){
	setObjectName("clock");
	setWindowTitle(getTitle());
	start = QDateTime::currentDateTime();
	end = QDateTime::currentDateTime() .addSecs(60*60);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), SLOT(onTimer()));
	timer->start(2000);

	setContextMenuPolicy(Qt::ActionsContextMenu);
	QAction* act = new QAction(tr("Set interval"),this);
	connect(act, SIGNAL(triggered()), SLOT(setInterval()));
	addAction(act);
	act = new QAction(tr("Restart"),this);
	connect(act, SIGNAL(triggered()), SLOT(restart()));
	addAction(act);
}

PDFClockDock::~PDFClockDock(){

}

void PDFClockDock::fillInfo(){

}

QString PDFClockDock::getTitle(){
	return "Clock";
}

void PDFClockDock::onTimer(){
	if (isHidden()) return;
	update();
}

void PDFClockDock::restart(){
	int delta = start.secsTo(end);
	start = QDateTime::currentDateTime();
	end = start.addSecs(delta);
	update();
}

void PDFClockDock::setInterval(){
	bool ok;
	int inter = QInputDialog::getInt(0, "TexMakerX", "New clock interval (in minutes)", 60, 1, 9999, 5, &ok);
	if (!ok) return;
	start = QDateTime::currentDateTime();
	end = start.addSecs(inter * 60);
	update();
}


void PDFClockDock::paintEvent(QPaintEvent * event){
	if (!document || !document->popplerDoc() || !document->widget()) {
		PDFDock::paintEvent(event);
		return;
	}
	QPainter p(this);
	QRect r = rect();
	p.fillRect(r, QColor::fromRgb(0,0,0));
	p.fillRect(0, 0, r.width() * (start.secsTo(QDateTime::currentDateTime())) / qMax(start.secsTo(end), 1),  r.height() * 3 / 4,  QColor::fromRgb(255,0,0));
	p.fillRect(0, r.height() * 3 / 4, r.width() * document->widget()->getCurrentPageIndex() / qMax(1, document->popplerDoc()->numPages()-1),  r.height()/4, QColor::fromRgb(0,0,255));
	QFont f = p.font();
	f.setPixelSize(r.height());
	QFontMetrics met(f);
	QString rem = tr("%1min").arg(qMax(0,QDateTime::currentDateTime().secsTo(end)/60));
	p.setFont(f);
	p.setPen(QColor::fromRgb(255,255,255));
	p.drawText(r, Qt::AlignRight | Qt::AlignVCenter, rem);
}


#endif
