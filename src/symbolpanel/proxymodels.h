#ifndef PROXYMODELS_H
#define PROXYMODELS_H

#include <QSortFilterProxyModel>


class MostUsedProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	MostUsedProxyModel(QObject *parent = 0);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};


class BooleanFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	BooleanFilterProxyModel(QObject *parent = 0);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};


#endif // PROXYMODELS_H
