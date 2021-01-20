#include "tocitemdata.h"

struct QDataComparer
{
	bool operator()(const QList<QVariant>& a, const QList<QVariant>& b) const
	{
		return a[1].toInt() < b[1].toInt();
	}
};

QList<QList<QVariant>> parseFileToc(QString filePath)
{
	QList<QList<QVariant>> result;
	QFile file(filePath);
	QString text;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		stream.setCodec("UTF-8");
		while (!stream.atEnd())
			text.append(stream.readLine() + "\n");
	}
	file.close();
	QList<QString> sf; sf << "input"; sf << "section"; sf << "subsection"; sf << "subsubsection";
	QList<QList<QVariant>> il;
	for (int i = 0; i < sf.count(); i++) {
		int pos = text.indexOf("\\" + sf[i]);
		while (pos >= 0) {
			QList<QVariant> item;
			item.push_back(sf[i]);
			item.push_back(pos);
			il.push_back(item);
			pos = text.indexOf("\\" + sf[i], pos + sf[i].length() + 1);
		}
	}
	std::sort(il.begin(), il.end(), QDataComparer());
	QDir sd = QFileInfo(filePath).dir();
	for (int i = 0; i < il.size(); i++) {
		int pos = text.indexOf("{", il[i][1].toInt());
		QString content = text.mid(pos + 1, text.indexOf("}", pos) - pos - 1).trimmed();
		if (il[i][0].toString() == "input") {
			if (!content.endsWith(".tex", Qt::CaseInsensitive))content.append(".tex");
			content = sd.filePath(content);
			if (QFileInfo::exists(content)) result.append(parseFileToc(content));
		}
		else {
			int l = 0;
			for (int j = 0; j < il[i][1].toInt(); j++) {
				if (text[j] == '\n') l++;
			}
			QList<QVariant> item;
			item.push_back(content);
			item.push_back(filePath);
			item.push_back(il[i][0].toString());
			item.push_back(l);
			result.push_back(item);
		}
	}
	
	return result;
}

QTocItemData::QTocItemData(const QString& head, const QString& file)
	: m_parentItem(0)
	, m_text(head)
	, m_file(file)
	, m_type("tableofcontent")
	, m_line(0)
{
	m_itemData.push_back(m_text);
}

QTocItemData::QTocItemData(const QList<QVariant>& data, QTocItemData* parentItem)
	: m_parentItem(parentItem)
	, m_line(0)
{
	m_text = data[0].toString();
	m_file = data[1].toString();
	m_type = data[2].toString();
	m_line = data[3].toUInt();
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

QString QTocItemData::getType()
{
	return m_type;
}

int QTocItemData::getLine()
{
	return m_line;
}
