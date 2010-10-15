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

// Based on code by Pino Toscano from Poppler / qt4 / Demos, released under GPL 2 or later

#include "PDFDocks.h"
#include "PDFDocument.h"

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

//////////////// SCROLL AREA ////////////////

PDFScrollArea::PDFScrollArea(QWidget *parent)
	: QScrollArea(parent)
{
}

PDFScrollArea::~PDFScrollArea()
{
}

void
PDFScrollArea::resizeEvent(QResizeEvent *event)
{
	QScrollArea::resizeEvent(event);
	emit resized();
}
