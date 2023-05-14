#include "latexstructure.h"
#include "latexdocument.h"


StructureEntry::StructureEntry(LatexDocument *doc, Type newType): type(newType), level(0), valid(false), expanded(false), parent(nullptr), document(doc), columnNumber(0), parentRow(-1), lineHandle(nullptr), lineNumber(-1), m_contexts(Unknown)
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
    if(lineHandle==nullptr) return lineNumber;
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
    qDebug()<<"   level: "<< level;
    qDebug()<<"   type: "<< static_cast<int>(type);
    qDebug()<<"   line nr: "<< lineNumber;
    qDebug()<<"   title: " << title;
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




