#include "tocitemtree.h"
#include "tocitemdata.h"
#include "tocitemstruct.h"

QTocItemTree::QTocItemTree(QList<TocItem> data, QObject* parent) :
	QAbstractItemModel(parent)
{
	rootItem = new QTocItemData(tr("Table of content"));
	QTocItemData* pSection = rootItem;
	QTocItemData* pSubSection = rootItem;
	QTocItemData* pSubSubSection = rootItem;
	for (int i = 0; i < data.size(); i++) {
		if (data[i].level == 2)
		{
			pSection = new QTocItemData(data[i], rootItem);
			rootItem->appendChild(pSection);
			pSubSection = pSection;
		}
		else if (data[i].level == 3)
		{
			pSubSection = new QTocItemData(data[i], pSection);
			pSection->appendChild(pSubSection);
		}
		else if (data[i].level == 4)
		{
			pSubSubSection = new QTocItemData(data[i], pSubSection);
			pSubSection->appendChild(pSubSubSection);
		}
	}
}

QTocItemTree::~QTocItemTree() { delete rootItem; }

QVariant QTocItemTree::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	QTocItemData* item = static_cast<QTocItemData*>(index.internalPointer());

	return item->data(index.column());
}

Qt::ItemFlags QTocItemTree::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return 0;

	return QAbstractItemModel::flags(index);
}

QVariant QTocItemTree::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return rootItem->data(section);

	return QVariant();
}

QModelIndex QTocItemTree::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	QTocItemData* parentItem;

	if (!parent.isValid())
		parentItem = rootItem;
	else
		parentItem = static_cast<QTocItemData*>(parent.internalPointer());

	QTocItemData* childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

QModelIndex QTocItemTree::parent(const QModelIndex& index) const
{
	if (!index.isValid())
		return QModelIndex();

	QTocItemData* childItem = static_cast<QTocItemData*>(index.internalPointer());
	QTocItemData* parentItem = childItem->parentItem();

	if (parentItem == rootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

int QTocItemTree::rowCount(const QModelIndex& parent) const
{
	QTocItemData* parentItem;
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
		parentItem = rootItem;
	else
		parentItem = static_cast<QTocItemData*>(parent.internalPointer());

	return parentItem->childCount();
}

int QTocItemTree::columnCount(const QModelIndex& parent) const
{
	if (parent.isValid())
		return static_cast<QTocItemData*>(parent.internalPointer())->columnCount();
	else
		return rootItem->columnCount();
}

QModelIndex QTocItemTree::indexFromItem(QTocItemData* item)
{
	if (item == rootItem || item == NULL)
		return QModelIndex();
	QTocItemData* parent = item->parentItem();

	QList<QTocItemData*> parents;

	while (parent && parent != rootItem) {
		parents << parent;
		parent = parent->parentItem();
	}
	QModelIndex ix;
	parent = rootItem;

	for (int i = 0; i < parents.count(); i++) {
		ix = index(parents[i]->row(), 0, ix);
	}
	ix = index(ix.row(), 0, ix);
	return ix;
}
