#ifndef TOCITEMDATA_H
#define TOCITEMDATA_H

#include "mostQtHeaders.h"

struct TocItem;

class QTocItemData
{
public:
	explicit QTocItemData(const QString& head);
	explicit QTocItemData(const TocItem& data, QTocItemData* parentItem = 0);
	~QTocItemData();

	void appendChild(QTocItemData* child);
	QTocItemData* child(int row);
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	int row() const;
	QTocItemData* parentItem();
	QString getText();
	QString getFile();
	int getLine();
	int getLevel();

private:
	QList<QTocItemData*> m_childItems;
	QList<QVariant> m_itemData;
	QTocItemData* m_parentItem;

	QString m_text;
	QString m_file;
	int m_line;
	int m_level;
};

#endif // TOCITEMDATA_H
