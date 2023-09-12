#include "latexstructure.h"
#include "latexdocument.h"


StructureEntry::StructureEntry(LatexDocument *doc, Type newType): type(newType), level(0), valid(false), expanded(false), document(doc), columnNumber(0), lineHandle(nullptr), lineNumber(-1), m_contexts(Unknown)
{
#ifndef QT_NO_DEBUG
	Q_ASSERT(document);
	document->StructureContent.insert(this);
#endif
}

StructureEntry::~StructureEntry()
{
	level = -1; //invalidate entry

#ifndef QT_NO_DEBUG
	Q_ASSERT(document);
	bool removed = document->StructureContent.remove(this);
	Q_ASSERT(removed); //prevent double deletion
#endif
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

void StructureEntry::debugPrint(const char *message) const
{
	qDebug("%s %p", message, this);
    qDebug()<<"   level: "<< level;
    qDebug()<<"   type: "<< static_cast<int>(type);
    qDebug()<<"   line nr: "<< lineNumber;
    qDebug()<<"   title: " << title;
}
