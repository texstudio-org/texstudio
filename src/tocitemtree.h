#ifndef TOCITEMTREE_H
#define TOCITEMTREE_H

#include "mostQtHeaders.h"
#include "tocitemstruct.h"

class QTocItemData;

class QTocItemTree : public QAbstractItemModel
{
	Q_OBJECT
public:
	explicit QTocItemTree(QList<TocItem> data, QObject* parent = 0);
	~QTocItemTree();

	QVariant data(const QModelIndex& index, int role) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex& index) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QModelIndex indexFromItem(QTocItemData* item);

private:
	QTocItemData* rootItem;
};

#endif // TOCITEMTREE_H
