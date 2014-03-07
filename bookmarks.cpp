#include "bookmarks.h"
#include "latexdocument.h"

Bookmarks::Bookmarks(const LatexDocuments *docs, QObject *parent) :
	QObject(parent)
{
	documents = docs;
	initializeWidget();
}

void Bookmarks::initializeWidget() {
	bookmarksWidget = new QListWidget();
	bookmarksWidget->setAlternatingRowColors(true);
	bookmarksWidget->setStyleSheet(
				"QListWidget::item {"
				"padding: 4px;"
				"border-bottom: 1px solid palette(dark); }"
				"QListWidget::item:selected {"
				"color: palette(highlighted-text);"
				"background-color: palette(highlight); }");
	connect(bookmarksWidget, SIGNAL(itemPressed(QListWidgetItem*)), SLOT(clickedOnBookmark(QListWidgetItem *))); //single click
	createContextMenu();
}

void Bookmarks::createContextMenu() {
	bookmarksWidget->setContextMenuPolicy(Qt::ActionsContextMenu);

	QAction *act = new QAction(tr("Move Up"), bookmarksWidget);
	connect(act, SIGNAL(triggered()), SLOT(moveBookmarkUp()));
	bookmarksWidget->addAction(act);
	act = new QAction(tr("Move Down"), bookmarksWidget);
	connect(act, SIGNAL(triggered()), SLOT(moveBookmarkDown()));
	bookmarksWidget->addAction(act);
	act = new QAction(tr("Remove"), bookmarksWidget);
	connect(act, SIGNAL(triggered()), SLOT(removeBookmark()));
	bookmarksWidget->addAction(act);
	act = new QAction(tr("Remove All"), bookmarksWidget);
	connect(act, SIGNAL(triggered()), SLOT(removeAllBookmarks()));
	bookmarksWidget->addAction(act);
}

void Bookmarks::setBookmarks(const QList<QVariant> &bookmarkList) {
	QStringList bookmark;
	bookmarksWidget->clear();
	for(int i=0; i<bookmarkList.count(); i++){
		bookmark = bookmarkList.at(i).toStringList();
		QString fn;
		if (!bookmark.isEmpty())
			fn = bookmark.takeFirst();
		int lineNr = 0;
		if (!bookmark.isEmpty())
			lineNr = bookmark.takeFirst().toInt();
		int bookmarkNumber = -1;
		if (!bookmark.isEmpty()){
			bool ok;
			bookmarkNumber = bookmark.first().toInt(&ok);
			if(!ok)
				bookmarkNumber = -1;
			else
				bookmark.removeFirst();
		}
		QString text;
		if (!bookmark.isEmpty())
			text = bookmark.takeFirst();
		QListWidgetItem *item = new QListWidgetItem(text,bookmarksWidget);
		item->setData(FileName, fn);
		item->setData(LineNr, lineNr);
		item->setData(BookmarkNr, bookmarkNumber);
		LatexDocument *doc=documents->findDocumentFromName(fn);
		if(doc && lineNr<doc->lineCount() && lineNr>=0) {
			QDocumentLineHandle *dlh=doc->line(lineNr).handle();
			item->setData(DocLineHandle,qVariantFromValue(dlh));
		}else{
			item->setData(DocLineHandle,0);
		}
	}
}

QList<QVariant> Bookmarks::getBookmarks() {
	QStringList bookmark;
	QList<QVariant> bookmarkList;
	for(int i=0; i<bookmarksWidget->count(); i++) {
		bookmark.clear();
		QListWidgetItem *item = bookmarksWidget->item(i);
		QString fn = item->data(FileName).toString();
		int lineNr = item->data(LineNr).toInt();
		int bookmarkNumber = item->data(BookmarkNr).toInt();
		QDocumentLineHandle *dlh = qvariant_cast<QDocumentLineHandle*>(item->data(DocLineHandle));
		LatexDocument *doc = documents->findDocumentFromName(fn);
		if(doc) {
			int temp = doc->indexOf(dlh);
			if (temp >= 0) lineNr = temp;
		}
		bookmark << fn;
		bookmark << QString::number(lineNr);
		bookmark << QString::number(bookmarkNumber);
		bookmark << item->text();
		bookmarkList << bookmark;
	}
	return bookmarkList;
}

void Bookmarks::bookmarkDeleted(QDocumentLineHandle* dlh){
	QString text=dlh->document()->getFileInfo().fileName();
	QList<QListWidgetItem*> lst = bookmarksWidget->findItems(text,Qt::MatchStartsWith);
	foreach (QListWidgetItem *item, lst){
		//QString fn=item->data(FileName).toString();
		//int lineNr=item->data(LineNr).toInt();
		QDocumentLineHandle *dlh_item = qvariant_cast<QDocumentLineHandle*>(item->data(DocLineHandle));
		if (dlh_item == dlh){
			int row = bookmarksWidget->row(item);
			bookmarksWidget->takeItem(row);
			return;
		}
	}
}

void Bookmarks::bookmarkAdded(QDocumentLineHandle* dlh,int nr){
	QDocument *doc = dlh->document();

	QString text = doc->getFileInfo().fileName();
	text+="\n"+dlh->text().trimmed();
	QListWidgetItem *item=new QListWidgetItem(text,bookmarksWidget);
	item->setData(FileName, doc->getFileName());
	item->setData(LineNr, doc->indexOf(dlh));
	item->setData(DocLineHandle, qVariantFromValue(dlh));
	item->setData(BookmarkNr, nr);
	int lineNr=doc->indexOf(dlh);
	lineNr = lineNr>1 ? lineNr-2 : 0;
	item->setToolTip(doc->exportAsHtml(doc->cursor(lineNr, 0, lineNr+4), true, true, 60));
}

void Bookmarks::updateLineWithBookmark(int lineNr){
	LatexDocument *doc=qobject_cast<LatexDocument*> (sender());
	if(!doc)
		return;
	QString text = doc->getFileInfo().fileName();
	QDocumentLineHandle *dlh = doc->line(lineNr).handle();
	QList<QListWidgetItem*> lst = bookmarksWidget->findItems(text,Qt::MatchStartsWith);
	foreach (QListWidgetItem *item, lst){
		QDocumentLineHandle *dlh_item = qvariant_cast<QDocumentLineHandle*>(item->data(DocLineHandle));
		if(dlh_item == dlh){
			QString text = doc->getFileInfo().fileName();
			text += "\n" + dlh->text().trimmed();
			item->setText(text);
			lineNr = lineNr>1 ? lineNr-2 : 0;
			item->setToolTip(doc->exportAsHtml(doc->cursor(lineNr, 0, lineNr+4), true, true, 60));
			return;
		}
	}
  // no bookmark found, add one (why)
  /*
	 text=doc->getFileInfo().fileName();
	 text+="\n"+dlh->text().trimmed();
	 QListWidgetItem *item=new QListWidgetItem(text,bookmarksWidget);
	 item->setData(FileName,documents.currentDocument->getFileName());
	 item->setData(LineNr,lineNr);
	 item->setData(DocLineHandle,qVariantFromValue(dlh));
	 lineNr = lineNr>1 ? lineNr-2 : 0;
	 text.clear();
	 for(int i=lineNr;(i<lineNr+4)&&(i<doc->lineCount());i++){
		 QString ln=doc->line(i).text().trimmed();
		 if(ln.length()>40)
			 ln=ln.left(40)+"...";
		 text+=ln+"\n";
	 }
	 item->setToolTip(text);
	 */
}

void Bookmarks::restoreBookmarks(LatexEditorView *edView) {
	Q_ASSERT(edView);
	LatexDocument *doc = edView->document;
	if(!doc)
		return;
	// go trough bookmarks
	for (int i=0; i<bookmarksWidget->count(); i++){
		QListWidgetItem *item = bookmarksWidget->item(i);
		QString fn = item->data(FileName).toString();
		if (doc->getFileName() != fn)
			continue;
		int lineNr = item->data(LineNr).toInt();
		int bookmarkNumber = item->data(BookmarkNr).toInt();
		edView->addBookmark(lineNr, bookmarkNumber);
		QDocumentLineHandle *dlh=doc->line(lineNr).handle();
		if(!dlh)
			continue;
		item->setData(DocLineHandle, qVariantFromValue(dlh));
		item->text() = dlh->text();
		item->setToolTip(doc->exportAsHtml(doc->cursor(lineNr, 0, lineNr+4), true, true, 60));
	}
}

void Bookmarks::updateBookmarks(LatexEditorView *edView){
	if(!edView)
		return;
	LatexDocument *doc = edView->document;
	  QString text = doc->getFileInfo().fileName();
	  QList<QListWidgetItem*> lst = bookmarksWidget->findItems(text,Qt::MatchStartsWith);
	  foreach (QListWidgetItem *item, lst){
		QDocumentLineHandle *dlh = qvariant_cast<QDocumentLineHandle*>(item->data(DocLineHandle));
		int lineNr = doc->indexOf(dlh);
		item->setData(LineNr, lineNr);
		item->setData(DocLineHandle, 0);
	  }
}


/*** context menu ***/

void Bookmarks::clickedOnBookmark(QListWidgetItem *item) {
	if (QApplication::mouseButtons() == Qt::RightButton) return; // avoid jumping to line if contextmenu is called
	QString fn = item->data(FileName).toString();
	int lineNr = item->data(LineNr).toInt();
	QDocumentLineHandle *dlh = qvariant_cast<QDocumentLineHandle*>(item->data(DocLineHandle));

	LatexDocument *doc = documents->findDocumentFromName(fn);
	if (!doc) {
		emit loadFileRequest(fn);
		doc = documents->findDocumentFromName(fn);
		if (!doc) return;
	}

	if (doc->indexOf(dlh)<0) {
		dlh=doc->line(lineNr).handle();
		item->setData(DocLineHandle, qVariantFromValue(dlh));
	}

	emit gotoLineRequest(lineNr, 0, doc->getEditorView());
}


void Bookmarks::moveBookmarkUp() {
	QListWidgetItem *item=bookmarksWidget->currentItem();
	if(!item) return;
	int row=bookmarksWidget->row(item);
	if(row<=0) return;
	bookmarksWidget->takeItem(row);
	bookmarksWidget->insertItem(row-1,item);
	bookmarksWidget->setCurrentRow(row-1);
}

void Bookmarks::moveBookmarkDown() {
	QListWidgetItem *item=bookmarksWidget->currentItem();
	if(!item) return;
	int row = bookmarksWidget->row(item);
	if(row<0) return;
	if(row == bookmarksWidget->count()-1) return;
	bookmarksWidget->takeItem(row);
	bookmarksWidget->insertItem(row+1, item);
	bookmarksWidget->setCurrentRow(row+1);
}

void Bookmarks::removeBookmark() {
	int row = bookmarksWidget->currentRow();
	if(row<0) return;
	QListWidgetItem *item = bookmarksWidget->takeItem(row);
	QString fn = item->data(FileName).toString();
	int lineNr = item->data(LineNr).toInt();
	int bookmarkNumber = item->data(BookmarkNr).toInt();
	QDocumentLineHandle *dlh = qvariant_cast<QDocumentLineHandle*>(item->data(DocLineHandle));

	LatexDocument *doc = documents->findDocumentFromName(fn);
	if (!doc) return;
	LatexEditorView* edView = doc->getEditorView();
	if (dlh) {
		edView->removeBookmark(dlh, bookmarkNumber);
	} else {
		edView->removeBookmark(lineNr, bookmarkNumber);
	}
}

void Bookmarks::removeAllBookmarks() {
	while(bookmarksWidget->count()>0) {
		QListWidgetItem *item = bookmarksWidget->takeItem(0);
		QString fn = item->data(FileName).toString();
		int lineNr = item->data(LineNr).toInt();
		int bookmarkNumber = item->data(BookmarkNr).toInt();
		QDocumentLineHandle *dlh = qvariant_cast<QDocumentLineHandle*>(item->data(DocLineHandle));

		LatexDocument *doc = documents->findDocumentFromName(fn);
		if (!doc) return;
		LatexEditorView* edView = doc->getEditorView();
		if (dlh) {
			edView->removeBookmark(dlh, bookmarkNumber);
		} else {
			edView->removeBookmark(lineNr, bookmarkNumber);
		}
	}
}

