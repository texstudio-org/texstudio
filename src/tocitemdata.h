#ifndef TOCITEMDATA_H
#define TOCITEMDATA_H

#include "mostQtHeaders.h"

QList<QList<QVariant>> parseFileToc(QString filePath);

class QTocItemData
{
public:
	explicit QTocItemData(const QString& head, const QString& file);
	explicit QTocItemData(const QList<QVariant>& data, QTocItemData* parentItem = 0);
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
	QString getType();
	int getLine();

private:
	QList<QTocItemData*> m_childItems;
	QList<QVariant> m_itemData;
	QTocItemData* m_parentItem;

	QString m_text;
	QString m_file;
	QString m_type;
	int m_line;
};

#endif // TOCITEMDATA_H
