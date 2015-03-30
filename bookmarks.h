#ifndef BOOKMARKS_H
#define BOOKMARKS_H

#include "mostQtHeaders.h"

class LatexEditorView;
class LatexDocuments;
class QDocumentLineHandle;

class Bookmarks : public QObject
{
	Q_OBJECT
public:
	Bookmarks(const LatexDocuments *docs, QObject *parent = 0);

	void setBookmarks(const QList<QVariant> &bookmarkList);
	QList<QVariant> getBookmarks();

	QListWidget *widget() {return bookmarksWidget;}
	
signals:
	void loadFileRequest(const QString &fileName);
	void gotoLineRequest(int lineNr, int col, LatexEditorView *edView);

public slots:
	void bookmarkDeleted(QDocumentLineHandle* dlh);
	void bookmarkAdded(QDocumentLineHandle* dlh,int nr);
	void updateLineWithBookmark(int lineNr);

	void restoreBookmarks(LatexEditorView *edView);
	void updateBookmarks(LatexEditorView *edView);

protected slots:
	void clickedOnBookmark(QListWidgetItem *item);
	void moveBookmarkUp();
	void moveBookmarkDown();
	void removeBookmark();
	void removeAllBookmarks();

private:
	enum DataRole {FileName = Qt::UserRole, LineNr, DocLineHandle, BookmarkNr};

	void initializeWidget();
	void createContextMenu();
	QListWidget *bookmarksWidget;
	const LatexDocuments *documents;
};

#endif // BOOKMARKS_H
