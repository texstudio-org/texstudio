#ifndef SEARCHRESULTMODEL_H
#define SEARCHRESULTMODEL_H

#include "mostQtHeaders.h"
#include <QAbstractItemModel>
#include "qdocumentsearch.h"

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
	
	void addSearch(QList<QDocumentLineHandle *> newSearch,QString name="");
	void removeSearch(QString name);
	void clear();
	QString getFilename(const QModelIndex &index);
	int getLineNumber(const QModelIndex &index);
	void setSearchExpression(const QString &exp,const bool isCaseSensitive,const bool isWord,const bool isRegExp);
	int getNextSearchResultColumn(QString text,int col);
private:
	QList<QPair<int,int> > getSearchResults(const QString &text) const;
	QString prepareResulText(QString text) const;
	
	QList< QList<QDocumentLineHandle *> > m_searches;
	QStringList m_files;
	QString mExpression;
	bool mIsWord,mIsCaseSensitive,mIsRegExp;
};

#endif // SEARCHRESULTMODEL_H
