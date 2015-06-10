#ifndef SEARCHRESULTWIDGET_H
#define SEARCHRESULTWIDGET_H

#include "mostQtHeaders.h"

#include "searchquery.h"
#include "qdocumentsearch.h"
#include "qdocument.h"

class SearchResultWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SearchResultWidget(QWidget *parent = 0);
	
	void setQuery(SearchQuery *sq);
	int getSearchScope() const;

signals:
	void jumpToSearchResult(QDocument *doc, int lineNumber, const SearchQuery *query);
	void updateTheSearch(int);

public slots:
	void clearSearch();

private slots:
	void clickedSearchResult(const QModelIndex &index);
	void updateSearch();
	void replaceAll();

private:
	QLabel *searchTypeLabel;
	QLabel *searchTextLabel;
	QPushButton *searchAgainButton;
	QLineEdit *replaceTextEdit;
	QPushButton *replaceButton;
	QComboBox *searchScopeBox;
	QTreeView *searchTree;

	SearchQuery *query;

	void retranslateUi();
};


class SearchTreeDelegate: public QItemDelegate {
	Q_OBJECT
public:
	SearchTreeDelegate(QObject *parent = 0);
protected:
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};


#endif // SEARCHRESULTWIDGET_H
