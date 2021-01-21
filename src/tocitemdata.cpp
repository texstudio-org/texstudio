#include "tocitemdata.h"

QTocItemData::QTocItemData(const QString& head)
	: m_parentItem(0)
	, m_text(head)
	, m_file("")
	, m_line(0)
	, m_level(0)
{
	m_itemData.push_back(m_text);
}

QTocItemData::QTocItemData(const TocItem& data, QTocItemData* parentItem)
	: m_parentItem(parentItem)
	, m_text(data.title)
	, m_file(data.file)
	, m_line(data.line)
	, m_level(data.level)
{
	m_itemData.push_back(m_text);
}

QTocItemData::~QTocItemData()
{
	qDeleteAll(m_childItems);
}

void QTocItemData::appendChild(QTocItemData* child)
{
	m_childItems.append(child);
}

QTocItemData* QTocItemData::child(int row)
{
	return m_childItems.value(row);
}

int QTocItemData::childCount() const
{
	return m_childItems.count();
}

int QTocItemData::columnCount() const
{
	return m_itemData.count();
}

QVariant QTocItemData::data(int column) const
{
	return m_itemData.value(column);
}

int QTocItemData::row() const
{
	if (m_parentItem)
		return m_parentItem->m_childItems.indexOf(const_cast<QTocItemData*>(this));

	return 0;
}

QTocItemData* QTocItemData::parentItem()
{
	return m_parentItem;
}

QString QTocItemData::getText()
{
	return m_text;
}

QString QTocItemData::getFile()
{
	return m_file;
}

int QTocItemData::getLine()
{
	return m_line;
}

int QTocItemData::getLevel()
{
	return m_level;
}