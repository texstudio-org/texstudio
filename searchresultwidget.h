#ifndef SEARCHRESULTWIDGET_H
#define SEARCHRESULTWIDGET_H

#include "mostQtHeaders.h"

#include "searchresultmodel.h"
#include "qdocumentsearch.h"
#include "latexdocument.h"

class SearchResultWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SearchResultWidget(QWidget *parent = 0);
	~SearchResultWidget();
	
	void setSearchExpression(QString exp,bool isCase,bool isWord,bool isRegExp);
    void setSearchExpression(QString exp,QString replaceText,bool isCase,bool isWord,bool isRegExp);
	QString searchExpression() const;
    int getSearchScope() const;
	int getNextSearchResultColumn(QString text,int col);
	
signals:
	void jumpToSearch(QDocument* doc,int lineNumber);
	void updateTheSearch(int);
	
public slots:
	void addSearch(QList<QDocumentLineHandle *> search, QDocument* doc);
	void clearSearch();
    void setSearchEditors(QList<LatexDocument *> docs){
        mDocs=docs;
    }

private slots:
	void clickedSearchResult(const QModelIndex& index);
    void updateSearch();
    void replaceAll();
    void replaceTextChanged(QString text);

private:
	QLabel *searchTextLabel;
    QLineEdit *replaceTextEdit;
    QComboBox *searchScopeBox;
	SearchResultModel *searchResultModel;
	QTreeView *searchTree;
	QList<LatexDocument*> mDocs;
	
	void retranslateUi();
};

class SearchTreeDelegate: public QItemDelegate {
	Q_OBJECT
public:
	SearchTreeDelegate(QObject * parent = 0 );
protected:
	void paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
	//void drawDisplay( QPainter* painter, const QStyleOptionViewItem& option, const QRect& rect, const QString& text ) const;
	QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const;
};


#endif // SEARCHRESULTWIDGET_H
