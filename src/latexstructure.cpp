#include "latexstructure.h"
#include "latexdocument.h"


StructureEntry::StructureEntry(LatexDocument *doc, Type newType): type(newType), level(0), valid(false), parent(nullptr), document(doc), columnNumber(0), parentRow(-1), lineHandle(nullptr), lineNumber(-1), m_contexts(nullptr)
{
#ifndef QT_NO_DEBUG
	Q_ASSERT(document);
	document->StructureContent.insert(this);
#endif
}

StructureEntry::~StructureEntry()
{
	level = -1; //invalidate entry
	foreach (StructureEntry *se, children)
		delete se;
#ifndef QT_NO_DEBUG
	Q_ASSERT(document);
	bool removed = document->StructureContent.remove(this);
	Q_ASSERT(removed); //prevent double deletion
#endif
}

void StructureEntry::add(StructureEntry *child)
{
    Q_ASSERT(child != nullptr);
	children.append(child);
	child->parent = this;
}

void StructureEntry::insert(int pos, StructureEntry *child)
{
    Q_ASSERT(child != nullptr);
	children.insert(pos, child);
	child->parent = this;
}

void StructureEntry::setLine(QDocumentLineHandle *handle, int lineNr)
{
	lineHandle = handle;
	lineNumber = lineNr;
}

QDocumentLineHandle *StructureEntry::getLineHandle() const
{
	return lineHandle;
}

int StructureEntry::getCachedLineNumber() const
{
	return lineNumber;
}

int StructureEntry::getRealLineNumber() const
{
	lineNumber = document->indexOf(lineHandle, lineNumber);
	Q_ASSERT(lineNumber == -1 || document->line(lineNumber).handle() == lineHandle);
	return lineNumber;
}

template <typename T> inline int hintedIndexOf (const QList<T *> &list, const T *elem, int hint)
{
	if (hint < 2) return list.indexOf(const_cast<T *>(elem));
	int backward = hint, forward = hint + 1;
	for (; backward >= 0 && forward < list.size();
	        backward--, forward++) {
		if (list[backward] == elem) return backward;
		if (list[forward] == elem) return forward;
	}
	if (backward >= list.size()) backward = list.size() - 1;
	for (; backward >= 0; backward--)
		if (list[backward] == elem) return backward;
	if (forward < 0) forward = 0;
	for (; forward < list.size(); forward++)
		if (list[forward] == elem) return forward;
	return -1;
}

int StructureEntry::getRealParentRow() const
{
	REQUIRE_RET(parent, -1);
	parentRow = hintedIndexOf<StructureEntry>(parent->children, this, parentRow);
	return parentRow;
}

void StructureEntry::debugPrint(const char *message) const
{
	qDebug("%s %p", message, this);
	qDebug("   level: %i", level);
    qDebug("   type: %i", static_cast<int>(type));
	qDebug("   line nr: %i", lineNumber);
	qDebug("   title: %s", qPrintable(title));
}

StructureEntryIterator::StructureEntryIterator(StructureEntry *entry)
{
	if (!entry) return;
	while (entry->parent) {
		entryHierarchy.prepend(entry);
		indexHierarchy.prepend(entry->getRealParentRow());
		entry = entry->parent;
	}
	entryHierarchy.prepend(entry);
	indexHierarchy.prepend(0);
}

bool StructureEntryIterator::hasNext()
{
	return !entryHierarchy.isEmpty();
}

StructureEntry *StructureEntryIterator::next()
{
    if (!hasNext()) return nullptr;
	StructureEntry *result = entryHierarchy.last();
	if (!result->children.isEmpty()) { //first child is next element, go a level deeper
		entryHierarchy.append(result->children.at(0));
		indexHierarchy.append(0);
	} else { //no child, go to next on same level
		entryHierarchy.removeLast();
		indexHierarchy.last()++;
		while (!entryHierarchy.isEmpty() && indexHierarchy.last() >= entryHierarchy.last()->children.size()) {
			//doesn't exists, proceed to travel upwards
			entryHierarchy.removeLast();
			indexHierarchy.removeLast();
			indexHierarchy.last()++;
		}
		if (!entryHierarchy.isEmpty())
			entryHierarchy.append(entryHierarchy.last()->children.at(indexHierarchy.last()));
	}
	return result;
}



LatexDocumentsModel::LatexDocumentsModel(LatexDocuments &docs): documents(docs),
	iconDocument(":/images/doc.png"), iconMasterDocument(":/images/masterdoc.png"), iconBibTeX(":/images/bibtex.png"), iconInclude(":/images/include.png"),
	iconWarning(getRealIconCached("warning")), m_singleMode(false)
{
	mHighlightIndex = QModelIndex();

	QStringList structureIconNames = QStringList() << "part" << "chapter" << "section" << "subsection" << "subsubsection" << "paragraph" << "subparagraph";
	iconSection.resize(structureIconNames.length());
	for (int i = 0; i < structureIconNames.length(); i++)
		iconSection[i] = getRealIconCached(structureIconNames[i]);
}

Qt::ItemFlags LatexDocumentsModel::flags ( const QModelIndex &index ) const
{
	if (index.isValid()) return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    else return nullptr;
}

QVariant LatexDocumentsModel::data ( const QModelIndex &index, int role) const
{
	static const QColor beyondEndColor(255, 170, 0);
	static const QColor inAppendixColor(200, 230, 200);
	static const QColor missingFileColor(Qt::red);
	static const QColor activeItemColor(UtilsUi::mediumLightColor(QPalette().color(QPalette::Highlight), 75));

	if (!index.isValid()) return QVariant();
    StructureEntry *entry = static_cast<StructureEntry *>(index.internalPointer());
	if (!entry) return QVariant();
	QString result;
	switch (role) {
	case Qt::DisplayRole:
		if (entry->type == StructureEntry::SE_DOCUMENT_ROOT) { //show only base file name
			QString title = entry->title.mid(1 + qMax(entry->title.lastIndexOf("/"), entry->title.lastIndexOf(QDir::separator())));
			if (title.isEmpty()) title = tr("untitled");
			return QVariant(title);
		}
		//show full title in other cases
		if (documents.showLineNumbersInStructure && entry->getCachedLineNumber() > -1) {
			result = entry->title + QString(tr(" (Line %1)").arg(entry->getRealLineNumber() + 1));
		} else {
			result = entry->title;
		}
		return QVariant(result);
	case Qt::ToolTipRole:
		if (!entry->tooltip.isNull()) {
			return QVariant(entry->tooltip);
		}
		if (entry->type == StructureEntry::SE_DOCUMENT_ROOT) {
			return QVariant(QDir::toNativeSeparators(entry->document->getFileName()));
		}
		if (entry->type == StructureEntry::SE_SECTION) {
#if QT_VERSION < 0x050000
			QString htmlTitle = entry->title;
#else
			QString htmlTitle = entry->title.toHtmlEscaped();
#endif
			htmlTitle.replace(' ', "&nbsp;");  // repleacement: prevent line break
			QString tooltip("<html><b>" + htmlTitle + "</b>");
			if (entry->getCachedLineNumber() > -1)
				tooltip.append("<br><i>" + tr("Line") + QString("</i>: %1").arg(entry->getRealLineNumber() + 1));
			StructureEntry *se = LatexDocumentsModel::labelForStructureEntry(entry);
			if (se)
				tooltip.append("<br><i>" + tr("Label") + "</i>: " + se->title);
			if (documents.markStructureElementsBeyondEnd && entry->hasContext(StructureEntry::BeyondEnd))
				tooltip.append(QString("<br><font color=\"%1\">%2</font>").arg(beyondEndColor.darker(120).name(), tr("Beyond end of document.")));
			if (documents.markStructureElementsInAppendix && entry->hasContext(StructureEntry::InAppendix))
				tooltip.append(QString("<br><font color=\"%1\">%2</font>").arg(inAppendixColor.darker(120).name(), tr("In Appendix.")));
            // show preview if file is loaded
            if(LatexDocument *doc=entry->document){
                int l=entry->getRealLineNumber();
                tooltip += doc->exportAsHtml(doc->cursor(qMax(0, l - 2), 0, l + 2), true, true, 60);
            }
			tooltip.append("</html>");
			return QVariant(tooltip);
		}
		if (entry->type == StructureEntry::SE_INCLUDE) {
#if QT_VERSION < 0x050000
			QString htmlTitle = entry->title;
#else
			QString htmlTitle = entry->title.toHtmlEscaped();
#endif
			htmlTitle.replace(' ', "&nbsp;").replace('-', "&#8209;");  // repleacement: prevent line break
			QString tooltip("<html><b>" + htmlTitle + "</b>");
			if (entry->getCachedLineNumber() > -1)
				tooltip.append("<br><i>" + tr("Line") + QString("</i>: %1").arg(entry->getRealLineNumber() + 1));
            if (!entry->valid){
				tooltip.append(QString("<br><font color=\"%1\">%2</font>").arg(missingFileColor.name(), tr("File not found.")));
            }else{
                // show preview if file is loaded
                if(LatexDocument *doc=entry->document){
                    QString fileName=entry->title;
                    fileName=doc->getAbsoluteFilePath(fileName,".tex");
                    LatexDocument *incDoc = documents.findDocument(fileName);
                    if(incDoc){
                        tooltip += incDoc->exportAsHtml(incDoc->cursor(0, 0,qMin(5,incDoc->lines()-1)), true, true, 60);
                    }
                }
            }
			return QVariant(tooltip);
		}
		if (entry->getCachedLineNumber() > -1)
			return QVariant(entry->title + QString(tr(" (Line %1)").arg(entry->getRealLineNumber() + 1)));
		else
			return QVariant();
	case Qt::DecorationRole:
		switch (entry->type) {
		case StructureEntry::SE_BIBTEX:
			return iconBibTeX;
		case StructureEntry::SE_INCLUDE:
			return iconInclude;
		case StructureEntry::SE_MAGICCOMMENT:
			if (entry->valid)
				return QVariant();
			else
				return iconWarning;
		case StructureEntry::SE_SECTION:
			if (entry->level >= 0 && entry->level < iconSection.count())
				return iconSection[entry->level];
			else
				return QVariant();
		case StructureEntry::SE_DOCUMENT_ROOT:
			if (documents.masterDocument == entry->document)
				return iconMasterDocument;
			else
				return iconDocument;
		default:
			return QVariant();
		}
	case Qt::BackgroundRole:
		if (index == mHighlightIndex) return QVariant(activeItemColor);
		if (documents.markStructureElementsBeyondEnd && entry->hasContext(StructureEntry::BeyondEnd)) return QVariant(beyondEndColor);
		if (documents.markStructureElementsInAppendix && entry->hasContext(StructureEntry::InAppendix)) return QVariant(inAppendixColor);
		return QVariant();
	case Qt::ForegroundRole:
		if (entry->type == StructureEntry::SE_INCLUDE) {
			return entry->valid ? QVariant() : QVariant(missingFileColor); // not found files marked red, else black (green is not easily readable)
		} else return QVariant();
	case Qt::FontRole:
		if (entry->type == StructureEntry::SE_DOCUMENT_ROOT) {
			QFont f = QApplication::font();
			if (entry->document == documents.currentDocument) f.setBold(true);
			if (entry->title.isEmpty() || (entry->document && !entry->document->isClean())) f.setItalic(true);
			return QVariant(f);
		}
		return QVariant();
	default:
		return QVariant();
	}
}

QVariant LatexDocumentsModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
	Q_UNUSED(orientation);
	if (section != 0) return QVariant();
	if (role != Qt::DisplayRole) return QVariant();
	return QVariant("Structure");
}

int LatexDocumentsModel::rowCount ( const QModelIndex &parent ) const
{
	if (!parent.isValid()) return documents.documents.count();
	else {
        StructureEntry *entry = static_cast<StructureEntry *>(parent.internalPointer());
		if (!entry) return 0;
		return entry->children.size();
	}
}

int LatexDocumentsModel::columnCount ( const QModelIndex &parent ) const
{
	Q_UNUSED(parent);
	return 1;
}

QModelIndex LatexDocumentsModel::index ( int row, int column, const QModelIndex &parent ) const
{
	if (column != 0) return QModelIndex(); //one column
	if (row < 0) return QModelIndex(); //shouldn't happen
	if (parent.isValid()) {
        const StructureEntry *entry = static_cast<StructureEntry *>(parent.internalPointer());
		if (!entry) return QModelIndex(); //should never happen
		if (row >= entry->children.size()) return QModelIndex(); //shouldn't happen in a correct view
		return createIndex(row, column, entry->children.at(row));
	} else {
		if (row >= documents.documents.size()) return QModelIndex();
		if (m_singleMode) {
			if (row != 0 || !documents.currentDocument )
				return QModelIndex();
			else
				return createIndex(row, column, documents.currentDocument->baseStructure);
		} else {
			return createIndex(row, column, documents.documents.at(row)->baseStructure);
		}
	}
}

QModelIndex LatexDocumentsModel::index ( StructureEntry *entry ) const
{
	if (!entry) return QModelIndex();
    if (entry->parent == nullptr && entry->type == StructureEntry::SE_DOCUMENT_ROOT) {
		int row = documents.documents.indexOf(entry->document);
		if (m_singleMode) {
			row = 0;
		}
		if (row < 0) return QModelIndex();
		return createIndex(row, 0, entry);
    } else if (entry->parent != nullptr && entry->type != StructureEntry::SE_DOCUMENT_ROOT) {
		int row = entry->getRealParentRow();
		if (row < 0) return QModelIndex(); //shouldn't happen
		return createIndex(row, 0, entry);
	} else return QModelIndex(); //shouldn't happen
}

QModelIndex LatexDocumentsModel::parent ( const QModelIndex &index ) const
{
	if (!index.isValid()) return QModelIndex();
    const StructureEntry *entry = static_cast<StructureEntry *>(index.internalPointer());
#ifndef QT_NO_DEBUG
    const LatexDocument *found = nullptr;
	foreach (const LatexDocument *ld, documents.documents)
		if (ld->StructureContent.contains(const_cast<StructureEntry *>(entry))) {
			found = ld;
			break;
		}
	if (!found) entry->debugPrint("No document for entry:");
	//Q_ASSERT(found);
	//Q_ASSERT(entry->document == found);
#endif
	if (!entry) return QModelIndex();
	if (!entry->parent) return QModelIndex();

	if (entry->level > LatexParser::getInstance().structureDepth() || entry->level < 0) {
		entry->debugPrint("Structure broken!");
		//qDebug("Title %s",qPrintable(entry->title));
		return QModelIndex();
	}
	if (entry->parent->level > LatexParser::getInstance().structureDepth() || entry->parent->level < 0) {
		entry->debugPrint("Structure broken (b)!");
		//qDebug("Title %s",qPrintable(entry->title));
		return QModelIndex();
	}
	if (entry->parent->parent)
		return createIndex(entry->parent->getRealParentRow(), 0, entry->parent);
	else {
		if (m_singleMode)
			return createIndex(0, 0, entry->parent);
		for (int i = 0; i < documents.documents.count(); i++)
			if (documents.documents.at(i)->baseStructure == entry->parent)
				return createIndex(i, 0, entry->parent);
		return QModelIndex();
	}
}

StructureEntry *LatexDocumentsModel::indexToStructureEntry(const QModelIndex &index )
{
    if (!index.isValid()) return nullptr;
    StructureEntry *result = static_cast<StructureEntry *>(index.internalPointer());
    if (!result || !result->document) return nullptr;
	return result;
}

LatexDocument *LatexDocumentsModel::indexToDocument(const QModelIndex &index )
{
	StructureEntry *se = indexToStructureEntry(index);
    return se ? se->document : nullptr;
}

/*!
 Returns an associated SE_LABEL entry for a structure element if one exists, otherwise 0.
 TODO: currently association is checked, by checking, if the label is on the same line or on the next.
 This is not necessarily correct. It fails if:
  - there are multiple labels on one line (always the first label is chosen)
  - the label is more than one line after the entry (label not detected)
*/
StructureEntry *LatexDocumentsModel::labelForStructureEntry(const StructureEntry *entry)
{
    REQUIRE_RET(entry && entry->document, nullptr );
	QDocumentLineHandle *dlh = entry->getLineHandle();
    if (!dlh) return nullptr;
	QDocumentLineHandle *nextDlh = entry->document->line(entry->getRealLineNumber() + 1).handle();
	StructureEntryIterator iter(entry->document->baseStructure);

	while (iter.hasNext()) {
		StructureEntry *se = iter.next();
		if (se->type == StructureEntry::SE_LABEL) {
			QDocumentLineHandle *labelDlh = se->getLineHandle();
			if (labelDlh == dlh || labelDlh == nextDlh) {
				return se;
			}
		}
	}
    return nullptr;
}

QModelIndex LatexDocumentsModel::highlightedEntry()
{
	return mHighlightIndex;
}

void LatexDocumentsModel::setHighlightedEntry(StructureEntry *entry)
{

	QModelIndex i1 = mHighlightIndex;
	QModelIndex i2 = index(entry);
	if (i1 == i2) return;
	emit dataChanged(i1, i1);
	mHighlightIndex = i2;
	emit dataChanged(i2, i2);
}

void LatexDocumentsModel::resetAll()
{
#if QT_VERSION<0x050000
#else
	beginResetModel();
#endif

	mHighlightIndex = QModelIndex();

#if QT_VERSION<0x050000
	reset();
#else
	endResetModel();
#endif
}

void LatexDocumentsModel::resetHighlight()
{
	mHighlightIndex = QModelIndex();
}

void LatexDocumentsModel::structureUpdated(LatexDocument *document, StructureEntry *highlight)
{
	Q_UNUSED(document);
    if (highlight) {
        mHighlightIndex = index(highlight);
    } else {
        mHighlightIndex = QModelIndex();
    }
    emit layoutChanged();
}
void LatexDocumentsModel::structureLost(LatexDocument *document)
{
	Q_UNUSED(document);
	resetAll();
}

void LatexDocumentsModel::removeElement(StructureEntry *se, int row)
{
	REQUIRE(se);
	if (!se->parent)
		beginRemoveRows(QModelIndex(), row, row); // remove from root (documents)
	else {
		if (row < 0) row = se->getRealParentRow();
		else {
			Q_ASSERT(row < se->parent->children.size());
			Q_ASSERT(se->parent->children[row] == se);
		}
		beginRemoveRows(index(se->parent), row, row);
	}
}

void LatexDocumentsModel::removeElementFinished()
{
	endRemoveRows();
}

void LatexDocumentsModel::addElement(StructureEntry *se, int row)
{
	beginInsertRows(index(se), row, row);
}

void LatexDocumentsModel::addElementFinished()
{
	endInsertRows();
}

void LatexDocumentsModel::updateElement(StructureEntry *se)
{
	emit dataChanged(index(se), index(se));
}

void LatexDocumentsModel::setSingleDocMode(bool singleMode)
{
	if (m_singleMode != singleMode) {
		//resetAll();
		if (singleMode) {
			foreach (LatexDocument *doc, documents.documents) {
				changePersistentIndex(index(doc->baseStructure), createIndex(0, 0, doc->baseStructure));
			}
		} else {
			for (int i = 0; i < documents.documents.count(); i++) {
				StructureEntry *se = documents.documents.at(i)->baseStructure;
				changePersistentIndex(index(se), createIndex(i, 0, se));
			}
		}
		m_singleMode = singleMode;
	}
    structureUpdated(documents.currentDocument, nullptr);
}

void LatexDocumentsModel::moveDocs(int from, int to)
{
	REQUIRE(from >= 0 && to >= 0
	        && from < documents.documents.length()
	        && to < documents.documents.length() );
	QModelIndexList fl, tl;
	int d = from < to ? 1 : -1;
	for (int i = from; i != to + d ; i += d )
		fl.append(createIndex(i, 0, documents.documents.at(i)->baseStructure));
	tl.append(createIndex(to, 0, documents.documents.at(from)->baseStructure));
	for (int i = from + d; i != to + d; i += d )
		tl.append(createIndex(i - d, 0, documents.documents.at(i)->baseStructure));
	changePersistentIndexList(fl, tl);
}

bool LatexDocumentsModel::getSingleDocMode()
{
	return m_singleMode;
}
