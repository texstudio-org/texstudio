#include "proxymodels.h"


MostUsedProxyModel::MostUsedProxyModel(QObject *parent)
	: QSortFilterProxyModel(parent)
{
}

bool MostUsedProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
	QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

	int count = sourceModel()->data(index, sortRole()).toInt();
	return count > 0;
}

BooleanFilterProxyModel::BooleanFilterProxyModel(QObject *parent)
	: QSortFilterProxyModel(parent)
{
}

bool BooleanFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
	QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

	return sourceModel()->data(index, filterRole()).toBool();
}
