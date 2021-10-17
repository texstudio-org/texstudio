#ifndef Header_SymbolList_Model
#define Header_SymbolList_Model

#include "mostQtHeaders.h"


/*! a container for symbol information */
struct SymbolItem {
	QString id;
	QString command;
	QString category;
	QString unicode;
	QString packages;
	QString iconFile;
	QIcon icon;
};


class SymbolListModel : public QAbstractListModel
{
	Q_OBJECT
public:
	enum AdditionalDataRoles {
		IdRole=Qt::UserRole,
		CommandRole,
		UnicodeRole,
		CategoryRole,
		UsageCountRole,
		FavoriteRole,
	};

	SymbolListModel(QVariantMap usageCountMap, QStringList favoriteList);
	void load(QString category);

	int rowCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;

	void incrementUsage(const QString &id);

	QVariantMap usageCountAsQVariantMap() const;
	QStringList favorites() const;
    void setDarkmode(bool active);

public slots:
	void addFavorite(const QString &id);
	void removeFavorite(const QString &id);

signals:
	void favoritesChanged();

protected:
	void loadSymbols(const QString &category, const QStringList &fileNames);
	QIcon getIcon(const SymbolItem &item) const;
	QString getTooltip(const SymbolItem &item) const;

private:
	QList<SymbolItem> symbols;
	QHash<QString, int> usageCount;
	QStringList favoriteIds;
    bool m_darkMode;
};

#endif // SYMBOLLISTMODEL_H
