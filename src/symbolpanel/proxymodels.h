#ifndef Header_Proxy_Model
#define Header_Proxy_Model

#include <QSortFilterProxyModel>


class MostUsedProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
    MostUsedProxyModel(QObject *parent = nullptr);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};


class BooleanFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
    BooleanFilterProxyModel(QObject *parent = nullptr);
	using QSortFilterProxyModel::invalidateFilter;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};


#endif // PROXYMODELS_H
