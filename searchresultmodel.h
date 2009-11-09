#ifndef SEARCHRESULTMODEL_H
#define SEARCHRESULTMODEL_H

#include <QAbstractItemModel>
#include "mostQtHeaders.h"
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

	void addSearch(QDocumentSearch *newSearch,QString name="");
	void removeSearch(QDocumentSearch *search);
	void clear();
	QString getFilename(const QModelIndex &index);
	int getLineNumber(const QModelIndex &index);
private:
	QList<QDocumentSearch *> m_searches;
	QStringList m_files;
};

#endif // SEARCHRESULTMODEL_H
