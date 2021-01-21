#include "toctreeview.h"
#include "latexstructure.h"
#include "latexdocument.h"
#include "configmanager.h"
#include "utilsUI.h"
#include "utilsSystem.h"
#include "editors.h"
#include "latexeditorview.h"
#include "tocitemtree.h"
#include "tocitemdata.h"
#include "tocitemstruct.h"

bool operator==(const struct TocItem& lh, const struct TocItem& rh) {
	return lh.title == rh.title && lh.file == rh.file && lh.line == rh.line && lh.level == rh.level;
}

TocTreeView::TocTreeView(const ConfigManager& config, LatexDocuments* docs, QWidget* parent) :
	QTreeView(parent),
	documents(docs)
{
	header()->hide();
	setObjectName("TocTree");
	UtilsUi::enableTouchScrolling(this);

	if (config.indentationInStructure > 0)
		setIndentation(config.indentationInStructure);

	updateTOC();
}

void TocTreeView::updateTOC()
{
	closedDocs.clear();
	updateData();
	expandAll();
}

QList<TocItem> parseStruct(QString file, StructureEntry* str) {
	QList<TocItem> result;
	for (int i = 0; i < str->children.count(); i++) {
		if (str->children[i]->type != StructureEntry::SE_SECTION && str->children[i]->type != StructureEntry::SE_INCLUDE) continue;
		TocItem item;
		item.file = file;
		item.title = str->children[i]->title;
		item.level = str->children[i]->level;
		item.line = str->children[i]->getRealLineNumber();
		if (str->children[i]->type == StructureEntry::SE_INCLUDE) {
			if (!item.title.endsWith(".tex", Qt::CaseInsensitive)) item.title.append(".tex");
			item.title = QFileInfo(file).dir().filePath(item.title);
			item.level = -1;
		}
		if (!result.contains(item)) result.push_back(item);
		if (str->children[i]->type == StructureEntry::SE_SECTION) result.append(parseStruct(file, str->children[i]));
	}
	return result;
}

struct QDataComparer
{
	bool operator()(const QList<QVariant>& a, const QList<QVariant>& b) const
	{
		return a[1].toInt() < b[1].toInt();
	}
};

QList<TocItem> parseFile(QString filePath)
{
	QList<TocItem> result;
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
		TocItem item;
		item.file = filePath;
		item.title = text.mid(pos + 1, text.indexOf("}", pos) - pos - 1).trimmed();
		item.line = 0;
		for (int j = 0; j < il[i][1].toInt(); j++) {
			if (text[j] == '\n') item.line++;
		}
		if (il[i][0].toString() == "input") {
			if (!item.title.endsWith(".tex", Qt::CaseInsensitive)) item.title.append(".tex");
			item.title = sd.filePath(item.title);
			item.level = -1;
		}
		else {
			item.level = 2;
			for (int j = 1; j < sf.count(); j++) {
				if (il[i][0].toString() == sf[j]) {
					item.level = j + 1;
					break;
				}
			}
		}
		if (!result.contains(item)) result.push_back(item);
	}
	return result;
}

void TocTreeView::updateData()
{
	if (documents == nullptr) return;
	foreach(QString key, openDocs.keys()) {
		closedDocs.remove(key);
		closedDocs.insert(key, openDocs[key]);
	}
	openDocs.clear();
	QList<QString> inc;
	for (int i = 0; i < documents->documents.size(); i++) {
		closedDocs.remove(documents->documents[i]->getFileName());
		QList<TocItem> ftoc = parseStruct(documents->documents[i]->getFileName(), documents->documents[i]->baseStructure);
		for (int j = 0; j < ftoc.count(); j++) {
			if (ftoc[j].level == -1) inc.push_back(ftoc[j].title);
		}
		openDocs.insert(documents->documents[i]->getFileName(), ftoc);
	}
	for (int i = 0; i < inc.count(); i++) {
		if (openDocs.contains(inc[i])) continue;
		if (closedDocs.contains(inc[i])) continue;
		if (!QFileInfo::exists(inc[i])) continue;
		QList<TocItem> tmp = parseFile(inc[i]);
		for (int j = 0; j < tmp.count(); j++)
		{
			if (tmp[j].level == -1) inc.push_back(tmp[j].title);
		}
		closedDocs.insert(inc[i], tmp);
	}
	LatexDocument* master = documents->masterDocument;
	if (master == nullptr) master = documents->currentDocument;
	if (master == nullptr && documents->documents.size() > 0) master = documents->documents[0];
	if (master != nullptr) setModel(new QTocItemTree(buildToc(master->getFileName()), this));
}

QList<TocItem> TocTreeView::buildToc(QString file)
{
	QList<TocItem> result;
	if (openDocs.contains(file)) {
		foreach(TocItem item, openDocs[file]) {
			if (item.level < 0)
				result.append(buildToc(item.title));
			else
				result.append(item);
		}
	}
	else if (closedDocs.contains(file)) {
		foreach(TocItem item, closedDocs[file]) {
			if (item.level < 0)
				result.append(buildToc(item.title));
			else
				result.append(item);
		}
	}
	else {}
	return result;
}

void TocTreeView::mouseDoubleClickEvent(QMouseEvent* event)
{
	QTocItemData* item = static_cast<QTocItemData*>(this->currentIndex().internalPointer());
	emit gotoFileLine(item->getText(), item->getFile(), item->getLine());
}

void TocTreeView::parentDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles)
{
	updateData();
	expandAll();
}
