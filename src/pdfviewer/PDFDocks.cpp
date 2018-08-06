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

#include "mostQtHeaders.h"

// Based on code by Pino Toscano from Poppler / qt4 / Demos, released under GPL 2 or later
/*! \class PDFDock
 *  \file PDFDocks.cpp
 *  \brief docking panel for PDF viewer
 *
 *  This class provides the base functions for dockable side-panel.
 * It is used for additional information like table of contents, preview images, etc.
 *
 * \see PDFDocument
  */

#include "PDFDocks.h"
#include "PDFDocument.h"

/*!
 * \brief constructor
 * \param doc actual pdf document which is displayed
 */
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
    QTreeWidgetItem *newitem = nullptr;
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
/*! \class PDFOutlineDock
 *
 * \brief sidepanel for preview
 *
 * show page preview in the sidepanel
 *
 * the actual rendering is done in extra threads
 */
/*!
 * \brief constructor
 * \param doc
 */
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
	if (!document || document->popplerDoc().isNull()) return;
	const QDomDocument *toc = document->popplerDoc()->toc();
	if (toc) {
        fillToc(*toc, tree, nullptr);
		connect(tree, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(followTocSelection()));
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
	QList<QTreeWidgetItem *> items = tree->selectedItems();
	if (items.count() > 0) {
		QTreeWidgetItem *item = items.first();
		QString dest = item->text(1);
		if (!dest.isEmpty())
			document->goToDestination(dest);
	}
}

PDFDockTreeWidget::PDFDockTreeWidget(QWidget *parent)
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
	if (!document) return;
	QSharedPointer<Poppler::Document> spDoc(document->popplerDoc());
	if (spDoc.isNull()) return;

	const Poppler::Document *doc = spDoc.data();
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

PDFDockListView::PDFDockListView(QWidget *parent)
	: QListView(parent)
{
}

QSize PDFDockListView::sizeHint() const
{
	return QSize(200, 300);
}

PDFDockListWidget::PDFDockListWidget(QWidget *parent)
	: QListWidget(parent)
{
}


QSize PDFDockListWidget::sizeHint() const
{
	return QSize(200, 300);
}

PDFOverviewModel::PDFOverviewModel(QObject *parent)
	: QAbstractListModel(parent)
{
    document = nullptr;
	cache.clear();
}

int PDFOverviewModel::rowCount ( const QModelIndex &parent ) const
{
	if (!document || document->popplerDoc().isNull()) return 0;
	if (parent.isValid()) return 0;
	if (!document->widget()) return 0;
	return document->widget()->realNumPages();
}

QVariant PDFOverviewModel::data ( const QModelIndex &index, int role) const
{
	if (!index.isValid() || index.column() != 0 || index.row() < 0 || index.row() >= document->widget()->realNumPages()) return QVariant();
	switch (role) {
	case Qt::DisplayRole:
		return QString::number(index.row() + 1);
	case Qt::DecorationRole:
		while (index.row() >= cache.size()) cache << QPixmap();
		if (cache[index.row()].isNull()) {
			const QObject *o = this; //TODO: get rid of const_cast
			cache[index.row()] = document->renderManager->renderToImage(index.row(), const_cast<QObject *>(o), "updateImage", -1, -1, -1, -1, -1, -1, false).scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		}
		return cache[index.row()];
	case Qt::BackgroundColorRole:
		return QColor(Qt::gray);
	}
	return QVariant();
}

void PDFOverviewModel::setDocument(PDFDocument *doc)
{
	beginResetModel();
	document = doc;
	if (!doc) {
		endResetModel();
		return;
	}
    if (!doc->widget() || document->popplerDoc().isNull()) document = nullptr;
	cache.clear();
	endResetModel();
}

void PDFOverviewModel::updateImage(const QPixmap &pm, int page)
{
	if (!document || page < 0 || page >= cache.size()) return;
	cache[page] = pm.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	emit dataChanged(index(page), index(page));
}

//////////////// FONT LIST ////////////////

PDFFontsDock::PDFFontsDock(PDFDocument *doc)
	: PDFDock(doc)
	, scannedFonts(false)
{
	setObjectName("fonts");
	setWindowTitle(getTitle());
	table = new QTableWidget(this);
#ifdef Q_OS_MAC /* don't do this on windows, as the font ends up too small */
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
	if (!document) return;
	QSharedPointer<Poppler::Document> spDoc(document->popplerDoc());
	if (!scannedFonts) {
		fonts = spDoc->fonts();
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

PDFBaseSearchDock::PDFBaseSearchDock(PDFDocument *doc): QDockWidget(doc), document(doc)
{
	// do it completely programatic
	setObjectName("search");
	setWindowTitle(tr("Search"));
	//this->resize(801, 31);
	QWidget *tempWidget = new QWidget(this);
	setWidget(tempWidget);
	QGridLayout *gridLayout = new QGridLayout(tempWidget);
	gridLayout->setContentsMargins(-1, 4, -1, 4);
	QFrame *frame_2 = new QFrame(this);
	frame_2->setObjectName(("frame_2"));
	QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
	frame_2->setSizePolicy(sizePolicy1);
	frame_2->setMinimumSize(QSize(0, 22));
	frame_2->setFrameShape(QFrame::NoFrame);
	frame_2->setLineWidth(0);
	QHBoxLayout *hboxLayout = new QHBoxLayout(frame_2);
	hboxLayout->setObjectName(("hboxLayout"));
	hboxLayout->setContentsMargins(-1, 0, -1, 0);

	QSize buttonSize(22, 22);

	QLabel *label = new QLabel(frame_2);
	label->setObjectName(("label"));
	QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
	sizePolicy3.setHorizontalStretch(0);
	sizePolicy3.setVerticalStretch(0);
	sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
	label->setSizePolicy(sizePolicy3);
	label->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

	hboxLayout->addWidget(label);


	gridLayout->addWidget(frame_2, 0, 0, 1, 1);

	leFind = new QLineEdit(this);
#if QT_VERSION >= 0x050200
	leFind->setClearButtonEnabled(true);
#endif
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
	bNext->setIcon(getRealIcon("down"));

	gridLayout->addWidget(bNext, 0, 3, 1, 1);

	bPrevious = new QToolButton(this);
	bPrevious->setObjectName(("bPrevious"));
	bPrevious->setMinimumSize(buttonSize);
	bPrevious->setMaximumSize(buttonSize);
	bPrevious->setIcon(getRealIcon("up"));

	gridLayout->addWidget(bPrevious, 0, 4, 1, 1);

	QFrame *frame_6 = new QFrame(this);
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

	gridLayout->addWidget(frame_6, 0, 6, 2, 2, Qt::AlignTop);

	// connect by name
	QMetaObject::connectSlotsByName(this);

	// set texts
	leFind->setToolTip(tr("Text or pattern to search for"));
	bNext->setToolTip(tr("Find next occurence"));
	bPrevious->setToolTip(tr("Find previous occurence"));

	label->setText(tr(" Find :"));
	label->setMinimumWidth(label->sizeHint().width());
	cbCase->setText(tr("Case"));
	cbCase->setMinimumWidth(cbCase->sizeHint().width());

	minimum_width = frame_2->sizeHint().width() + leFind->sizeHint().width() + 2 * bNext->sizeHint().width() + 5 * hboxLayout->spacing();
	//;

	cbCase->setChecked(false);

	leFind->installEventFilter(this);

	listOfWidget << cbCase;
}

QString PDFBaseSearchDock::getSearchText() const
{
	return leFind->text();
}

void PDFBaseSearchDock::setSearchText(QString text)
{
	leFind->setText(text);
}

bool PDFBaseSearchDock::hasFlagCaseSensitive() const
{
	return cbCase->isChecked();
}

void PDFBaseSearchDock::setFocus()
{
	leFind->setFocus();
	leFind->selectAll();
}

void PDFBaseSearchDock::resizeEvent(QResizeEvent *e)
{
	int w = e->size().width();
	w = w - minimum_width; // remaining space
	int row = 0;
	int col = 0;
	int remaining_space = w;
	foreach (QWidget *wdg, listOfWidget) {
		remaining_space = remaining_space - wdg->minimumWidth();
		if (remaining_space > 0) {
			gridLayout1->addWidget(wdg, row, col, 1, 1);
			col++;
		} else {
			col = 0;
			row++;
			gridLayout1->addWidget(wdg, row, col, 1, 1);
			col++;
			remaining_space = w - wdg->minimumWidth();
		}
	}
	QDockWidget::resizeEvent(e);
}

bool PDFBaseSearchDock::eventFilter(QObject *o, QEvent *e)
{
	if ( o == leFind) {
		int kc;
		switch ( e->type() ) {
		case QEvent::KeyPress :

			kc = static_cast<QKeyEvent *>(e)->key();

			if ( (kc == Qt::Key_Enter) || (kc == Qt::Key_Return) )
				emit search(Qt::ShiftModifier & static_cast<QKeyEvent *>(e)->modifiers(), false);
			else if ( kc == Qt::Key_Escape)
				close();
			break;

		default:
			break;
		}
	}

	return QWidget::eventFilter(o, e);
}

void PDFBaseSearchDock::on_leFind_textEdited(const QString &)
{
	emit search(false, true);
}

void PDFBaseSearchDock::on_bNext_clicked()
{
	emit search(false, false);
}

void PDFBaseSearchDock::on_bPrevious_clicked()
{
	emit search(true, false);
}


PDFSearchDock::PDFSearchDock(PDFDocument *doc): PDFBaseSearchDock(doc)
{
	cbWords = new QCheckBox(this);
	cbWords->setObjectName("cbWords");
	cbWords->setText(tr("Words"));
    cbWords->setToolTip(tr("Only searches for whole words."));

	gridLayout1->addWidget(cbWords, 0, 2, 1, 1);

	cbSync = new QCheckBox(this);
	cbSync->setObjectName("cbSync");
	cbSync->setText(tr("Sync"));
	cbSync->setToolTip(tr("Synchronize editor when jumping to search results."));
	cbSync->setChecked(true);

	gridLayout1->addWidget(cbSync, 0, 3, 1, 1);

	listOfWidget << cbWords << cbSync;
}

bool PDFSearchDock::hasFlagWholeWords() const
{
	return cbWords->isChecked();
}

bool PDFSearchDock::hasFlagSync() const
{
	return cbSync->isChecked();
}


//////////////// SCROLL AREA ////////////////

PDFScrollArea::PDFScrollArea(QWidget *parent)
    : QAbstractScrollArea(parent), continuous(true), pdf(nullptr), updateWidgetPositionStackWatch(0), onResizeStackWatch(0)
{
	viewport()->setBackgroundRole(QPalette::NoRole);
	viewport()->setAttribute(Qt::WA_AcceptTouchEvents, true);
	verticalScrollBar()->setSingleStep(20);
	horizontalScrollBar()->setSingleStep(20);
	setFocusPolicy(Qt::StrongFocus);
}

void PDFScrollArea::setPDFWidget(PDFWidget *widget)
{
	//from qt
	if (pdf == widget) return;
    delete pdf;
    pdf = nullptr;
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

void PDFScrollArea::ensureVisible(int x, int y, int xmargin, int ymargin)
{
	int logicalX = QStyle::visualPos(layoutDirection(), viewport()->rect(), QPoint(x, y)).x();

	if (logicalX - xmargin < horizontalScrollBar()->value()) {
		horizontalScrollBar()->setValue(qMax(0, logicalX - xmargin));
	} else if (logicalX > horizontalScrollBar()->value() + viewport()->width() - xmargin) {
		horizontalScrollBar()->setValue(qMin(logicalX - viewport()->width() + xmargin, horizontalScrollBar()->maximum()));
	}

	if (continuous) y += pdf->gridRowHeight() * ((pdf->getPageIndex() + pdf->getPageOffset()) / pdf->gridCols());

	if (y - ymargin < verticalScrollBar()->value()) {
		verticalScrollBar()->setValue(qMax(0, y - ymargin));
	} else if (y > verticalScrollBar()->value() + viewport()->height() - ymargin) {
		verticalScrollBar()->setValue(qMin(y - viewport()->height() + ymargin, verticalScrollBar()->maximum()));
	}
}

void PDFScrollArea::setVerticalScrollBarPolicy(Qt::ScrollBarPolicy policy)
{
	if (continuous) QAbstractScrollArea::setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	else QAbstractScrollArea::setVerticalScrollBarPolicy(policy);
}

PDFScrollArea::~PDFScrollArea()
{
}

void PDFScrollArea::setContinuous(bool cont)
{
	Q_ASSERT(pdf);
	if (cont == continuous) return;
	continuous = cont;
	if (!cont) pdf->setGridSize(pdf->gridCols(), 1);
	else {
		int page = pdf->getPageIndex();
        resizeEvent(nullptr);
		goToPage(page, false);
	}
}

void PDFScrollArea::goToPage(int page, bool sync)
{
	if (continuous) {
		int rowHeight = pdf->gridRowHeight();
		verticalScrollBar()->setValue((page / pdf->gridCols())  * rowHeight);
	} else pdf->goToPageDirect(page, sync);
}

void PDFScrollArea::ensureVisiblePageAbsolutePos(int page, const QPointF &pos, int xmargin, int ymargin)
{
	Q_ASSERT(pdf);
	if (!pdf || page < 0 || page >= pdf->realNumPages()) return;
	if (pdf->pageRect(page).isNull()) goToPage(page);  // pageRect is null if the page is not displayed.
	QPoint scaled = (pdf->totalScaleFactor() * pos).toPoint() + pdf->pageRect(page).topLeft();
	ensureVisible(scaled.x(), scaled.y(), xmargin, ymargin);
}

bool PDFScrollArea::event(QEvent *e)
{
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

bool PDFScrollArea::eventFilter(QObject *o, QEvent *e)
{
	if (onResizeStackWatch < 3 && o == pdf && e->type() == QEvent::Resize) {
		onResizeStackWatch++;
		if (continuous)
			pdf->setGridSize(pdf->gridCols(), height() / pdf->gridRowHeight() + 2);
		updateScrollBars();
		onResizeStackWatch--;
	}

	return false;
}

void PDFScrollArea::wheelEvent(QWheelEvent *e)
{
	if (pdf && !getContinuous()) {
		pdf->wheelEvent(e);
		return;
	}
	QAbstractScrollArea::wheelEvent(e);
}

void
PDFScrollArea::resizeEvent(QResizeEvent *)
{
	Q_ASSERT(pdf);
	if (continuous) {
		pdf->setGridSize(pdf->gridCols(), height() / pdf->gridRowHeight() + 2, true);
		pdf->reloadPage(false);
	}
	emit resized();
	updateScrollBars();
}

void PDFScrollArea::scrollContentsBy(int, int)
{
	Q_ASSERT(pdf);
	updateWidgetPosition();
}

void PDFScrollArea::updateWidgetPosition()
{
	Q_ASSERT(pdf);
	if (updateWidgetPositionStackWatch >= 3) return;
	updateWidgetPositionStackWatch++;
	Qt::LayoutDirection dir = layoutDirection();
	QScrollBar *hbar = horizontalScrollBar(), *vbar = verticalScrollBar();
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
		int pos = vbar->value();
		pdf->goToPageDirect((pos / rowHeight)*pdf->gridCols() , true);
	}
	updateWidgetPositionStackWatch--;
	pdf->updateStatusBar(); //need to update page count when a new page is scrolled in visible area
}

void PDFScrollArea::updateScrollBars()
{
	Q_ASSERT(pdf);
	QScrollBar *hbar = horizontalScrollBar(), *vbar = verticalScrollBar();

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
		int totalRows = ((pdf->pseudoNumPages() + pdf->gridCols() - 1) / pdf->gridCols());
		vbar->setRange(0, totalRows * pdf->gridRowHeight() - pdf->gridBorder() - p.height() - 1); // -1 is heuristic to prevent activation of the scrollbar in case of fit-page and one-page documents (might be this should be corrected in another place)
	}

	if (pdf->getScaleOption() == kFitWindow) {
		vbar->setPageStep(pdf->gridRowHeight()); // use grid height instead of viewport height here to move exactly one page
	} else {
		vbar->setPageStep(p.height());
	}
	updateWidgetPosition();
}


//////////////// Overview ////////////////
struct renderInfo {
	Poppler::Page *page;
	PDFWidget *widget;
};


PDFOverviewDock::PDFOverviewDock(PDFDocument *doc)
	: PDFDock(doc), toGenerate(0)
{
	setObjectName("overview");
	setWindowTitle(getTitle());
	list = new PDFDockListView(this);
	list->setViewMode(QListView::IconMode);
	list->setIconSize(QSize(128, 128));
	list->setMovement(QListView::Static);
	list->setSpacing(12);
	list->setBackgroundRole(QPalette::Mid);
	list->setLayoutMode(QListView::Batched);
	list->setBatchSize(10);
	list->setUniformItemSizes(true); //necessary to prevent it from rendering all pages
	list->setModel(new PDFOverviewModel());
	setWidget(list);
	dontFollow = false;
}

PDFOverviewDock::~PDFOverviewDock()
{
}

void PDFOverviewDock::changeLanguage()
{
	PDFDock::changeLanguage();
	if (filled)
		fillInfo();
}

void PDFOverviewDock::fillInfo()
{
	qobject_cast<PDFOverviewModel *>(list->model())->setDocument(document);
	connect(list->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(followTocSelection()));
}

void PDFOverviewDock::documentClosed()
{
    qobject_cast<PDFOverviewModel *>(list->model())->setDocument(nullptr);
	PDFDock::documentClosed();
}

void PDFOverviewDock::followTocSelection()
{
	if (dontFollow) return;

	QModelIndex mi = list->currentIndex();
	if (mi.isValid()) {
		document->goToPage(mi.row());
	}
}

void PDFOverviewDock::pageChanged(int page)
{
	dontFollow = true;
	list->setCurrentIndex(list->model()->index(page, 0));
	list->scrollTo(list->currentIndex());
	dontFollow = false;
}


PDFClockDock::PDFClockDock(PDFDocument *parent): PDFDock(parent)
{
	setObjectName("clock");
	setWindowTitle(getTitle());
	start = QDateTime::currentDateTime();
	end = QDateTime::currentDateTime() .addSecs(60 * 60);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), SLOT(onTimer()));
	timer->start(2000);

	setContextMenuPolicy(Qt::ActionsContextMenu);
	QAction *act = new QAction(tr("Set Interval..."), this);
	connect(act, SIGNAL(triggered()), SLOT(setInterval()));
	addAction(act);
	act = new QAction(tr("Restart"), this);
	connect(act, SIGNAL(triggered()), SLOT(restart()));
	addAction(act);
}

PDFClockDock::~PDFClockDock()
{

}

void PDFClockDock::fillInfo()
{

}

QString PDFClockDock::getTitle()
{
	return tr("Clock");
}

void PDFClockDock::onTimer()
{
	if (isHidden()) return;
	update();
}

void PDFClockDock::restart()
{
    qint64 delta = start.secsTo(end);
	start = QDateTime::currentDateTime();
	end = start.addSecs(delta);
	update();
}

void PDFClockDock::setInterval()
{
	bool ok;
    int interval = QInputDialog::getInt(nullptr, "TeXstudio", tr("New clock interval (in minutes)"), 60, 1, 9999, 5, &ok);
	if (!ok) return;
	setInterval(interval);
}

void PDFClockDock::setInterval(int interval)
{
	start = QDateTime::currentDateTime();
	end = start.addSecs(interval * 60);
	update();
}

void PDFClockDock::paintEvent(QPaintEvent *event)
{
	if (!document || document->popplerDoc().isNull() || !document->widget()) {
		PDFDock::paintEvent(event);
		return;
	}
	QBrush backgroundBrush = palette().window();  //QColor::fromRgb(96, 96, 96));
	QColor textColor = palette().text().color();
	if (style()->property("manhattanstyle").toBool()) {
		backgroundBrush = QBrush(QColor::fromRgb(96, 96, 96));
		textColor = QColor(Qt::white);
	}
	QColor timeBarColor = QColor::fromRgb(175, 0, 175);
	QColor pagesBarColor = QColor::fromRgb(0, 122, 217);

	QPainter p(this);
	QRect r = rect();
	p.fillRect(r, backgroundBrush);

	// text
	qint64 remainingSeconds = QDateTime::currentDateTime().secsTo(end);
	QString text;
	if (remainingSeconds <= 60)
		text = tr("%1 sec").arg(qMax(qint64(0), remainingSeconds));
	else
		text = tr("%1 min").arg(remainingSeconds / 60);
	QFont f = p.font();
	f.setPixelSize(r.height());
	p.setFont(f);
	p.setPen(textColor);
	int labelWidth = p.fontMetrics().width("9999 min");
	QRect textRect = rect();
	textRect.setWidth(labelWidth);
	p.drawText(textRect, Qt::AlignHCenter | Qt::AlignVCenter, text);

	// progress bar
	r.adjust(labelWidth, 0, 0, 0);
	p.fillRect(r.x(), 0, r.width() * start.secsTo(QDateTime::currentDateTime()) / qMax(qint64(start.secsTo(end)), qint64(1)), r.height() * 3 / 4, timeBarColor);
	p.fillRect(r.x(), r.height() * 3 / 4, r.width() * document->widget()->getPageIndex() / qMax(1, document->widget()->realNumPages() - 1),  r.height() / 4, pagesBarColor);
}


MessageFrame::MessageFrame(QWidget *parent) : QFrame(parent), label(nullptr)
{
	QHBoxLayout *layout = new QHBoxLayout();
	setLayout(layout);
	label = new QLabel("test");
	label->setWordWrap(true);
	layout->addWidget(label);
	layout->setContentsMargins(2, 2, 2, 2);

	setStyleSheet("background: #FFFBBF;");
	setVisible(false);
}

/*
 * Displays the message frame with the given text.
 *
 * actions: For each action, a button with the text of the action is inserted into the message panel.
 *          The action is triggered when the button is pressed.
 *          The button takes ownership of the action.
 */
void MessageFrame::showText(const QString &text, QList<QAction *> actions)
{
	label->setText(text);

	foreach (QPushButton *bt, buttons)
		delete bt;
	buttons.clear();

	foreach (QAction *act, actions) {
		QPushButton *bt = new QPushButton(act->text());
		act->setParent(bt);
		bt->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		buttons.append(bt);
		connect(bt, SIGNAL(clicked()), act, SIGNAL(triggered()));
		layout()->addWidget(bt);
	}
	show();
}

#endif
