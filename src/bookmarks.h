#ifndef Header_Bookmarks
#define Header_Bookmarks

#include "mostQtHeaders.h"
#include "latexeditorview.h"
#include "latexdocument.h"
//class LatexEditorView;
//class LatexDocuments;
//class LatexDocument;
//class QDocumentLineHandle;


struct Bookmark {
	Bookmark();
	
	static Bookmark fromStringList(QStringList slist);
	QStringList toStringList() const;
	
	QString filename;
	int lineNumber;
	int bookmarkNumber;
	QString text;
};

class Bookmarks : public QObject
{
	Q_OBJECT

public:
    Bookmarks(const LatexDocuments *docs, QObject *parent = nullptr); ///< constructor

	void setBookmarks(const QList<Bookmark> &bookmarkList); ///< set list of bookmarks
	QList<Bookmark> getBookmarks(); ///< get list of bookmarks

	QListWidget *widget() { return bookmarksWidget; } ///< get reference to bookmark list widget

signals:
	void loadFileRequest(const QString &fileName); ///< request loading of file in order to jump to a bookmark position there
	void gotoLineRequest(int lineNr, int col, LatexEditorView *edView); ///< jump to line of bookmark

public slots:
	void bookmarkDeleted(QDocumentLineHandle *dlh);
	void bookmarkAdded(QDocumentLineHandle *dlh, int nr);
	void updateLineWithBookmark(int lineNr);

	void restoreBookmarks(LatexEditorView *edView);
	void updateBookmarks(LatexEditorView *edView);
    void setDarkMode(bool mode);

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

    bool m_darkMode;
};

#endif // BOOKMARKS_H
