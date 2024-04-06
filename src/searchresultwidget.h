#ifndef Header_SearchResult_Widget
#define Header_SearchResult_Widget

#include "mostQtHeaders.h"

#include "searchquery.h"
#include "qdocumentsearch.h"
#include "qdocument.h"

class SearchResultWidget : public QWidget
{
	Q_OBJECT

public:
    explicit SearchResultWidget(QWidget *parent = nullptr);

	void setQuery(SearchQuery *sq);
	SearchQuery::Scope searchScope() const;
	void updateSearchExpr(QString searchText);

	void saveConfig();

signals:
    void jumpToSearchResult(LatexDocument *doc, int lineNumber, const SearchQuery *query);
    void jumpToFileSearchResult(QString fn, int lineNumber, const SearchQuery *query);
	void runSearch(SearchQuery *query);

public slots:
	void clearSearch();

private slots:
	void clickedSearchResult(const QModelIndex &index);
    void replaceButtonClicked();
    void replaceTextEditChanged(const QString &text);
	void updateSearch();
    void changeScope(int mode);
    void changeFileFilter(int mode);
	void searchCompleted();

private:
	QLabel *searchTypeLabel;
	QLabel *searchTextLabel;
    QLabel *m_replaceByLabel;
	QPushButton *searchAgainButton;
	QLineEdit *replaceTextEdit;
	QPushButton *replaceButton;
	QComboBox *searchScopeBox;
    QComboBox *m_fileFilterBox;
	QTreeView *searchTree;

	SearchQuery *query;

	void retranslateUi();
	void updateSearchScopeBox(SearchQuery::Scope sc);
    void adaptGUItoScope();
};


class SearchTreeDelegate: public QItemDelegate
{
	Q_OBJECT

public:
    SearchTreeDelegate(QString editorFontFamily, QObject *parent = nullptr);

protected:
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
	QString m_editorFontFamily;
};


#endif // SEARCHRESULTWIDGET_H
