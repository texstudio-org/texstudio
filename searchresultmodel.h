#ifndef SEARCHRESULTMODEL_H
#define SEARCHRESULTMODEL_H

#include "mostQtHeaders.h"

class QDocument;
class QDocumentLineHandle;
struct SearchInfo{
	QPointer<QDocument> doc;
	QList<QDocumentLineHandle *> lines;
    QList<bool> checked;
	mutable QList<int> lineNumberHints;
};

class SearchResultModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	SearchResultModel(QObject *parent=0);
	~SearchResultModel();
	
	QVariant data(const QModelIndex &index, int role) const;
	QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
	
	void addSearch(const SearchInfo& search);
	void removeSearch(const QDocument* doc);
    QList<SearchInfo> getSearches();
	void clear();
	QDocument* getDocument(const QModelIndex &index);
	int getLineNumber(const QModelIndex &index);
    void setSearchExpression(const QString &exp,const bool isCaseSensitive,const bool isWord,const bool isRegExp);
    void setSearchExpression(const QString &exp,const QString &repl,const bool isCaseSensitive,const bool isWord,const bool isRegExp);
	QString searchExpression() { return mExpression; }
	int getNextSearchResultColumn(const QString& text,int col);
    void getSearchConditions(bool &isCaseSensitive,bool &isWord,bool &isRegExp){
        isWord=mIsWord;
        isCaseSensitive=mIsCaseSensitive;
        isRegExp=mIsRegExp;
    }
    void setReplacementText(QString text){
        mReplacementText=text;
    }

    QList<QPair<int,int> > getSearchResults(const QString &text) const;

private:
	QString prepareResultText(const QString& text) const;
    QString prepareReplacedText(const QString& text) const;
	
	QList< SearchInfo > m_searches;
    QString mExpression,mReplacementText;
	bool mIsWord,mIsCaseSensitive,mIsRegExp;
};

#endif // SEARCHRESULTMODEL_H
