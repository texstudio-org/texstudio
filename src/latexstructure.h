#ifndef Header_Latex_Structure
#define Header_Latex_Structure

#include "mostQtHeaders.h"

class QDocumentLineHandle;
class LatexDocument;
class LatexDocuments;

/*!
 * \brief leaf of structure reqresentation of document structure
 *
 * The structure is organized as a tree with SE_DOCUMENT_ROOT as root
 * Section are organized hierarchical depending on the section level, MAGIC comments, label are below a root-marker below root
 */
struct StructureEntry {
	enum Type {SE_DOCUMENT_ROOT, SE_OVERVIEW, SE_SECTION, SE_BIBTEX, SE_TODO, SE_MAGICCOMMENT, SE_INCLUDE, SE_LABEL, SE_BLOCK = SE_LABEL};
	enum Context { ///< mark if entry is located beyond appendix/end document commands
        Unknown = 0x0000,
		InAppendix = 0x0001,
        BeyondEnd = 0x0010,
        Import = 0x0100
	};
	Q_DECLARE_FLAGS(Contexts, Context)
	Type type;
	QString title; ///< actual text to be displayed
	QString tooltip; ///< optional because most tooltips are automatically generated.
	int level; ///< only used for section types!
	bool valid; ///< currently only used for includes and magic comments
    bool expanded; ///< remember collapsed/expanded for toplevel TOC
	QList<StructureEntry *> children; ///< children
	StructureEntry *parent; ///< parent for easier tree structure parsing
	LatexDocument *document;

	StructureEntry(LatexDocument *doc, Type newType); ///< constructor
	~StructureEntry();
	void add(StructureEntry *child); ///< add child element
	void insert(int pos, StructureEntry *child); ///< insert child elemet at pos

	int columnNumber; //position of the entry in the line, only used for correct sorting of structure update (TODO: use a local variable for it)
	void setLine(QDocumentLineHandle *handle, int lineNr = -1); ///< set linehandle for automatic update of line number
	QDocumentLineHandle *getLineHandle() const; ///< get linehandle for entry
	int getCachedLineNumber() const; ///< get cached line number
	int getRealLineNumber() const; ///< get line number from given linehandle. More time consuming than from cached line number.
	int getRealParentRow() const; ///< determine position of this element in parent

	bool hasContext(Context c) const
	{
		return m_contexts & c;    ///< get context
	}
	void setContext(Context c, bool b = true)
	{
		if (b) m_contexts |= c;    ///< change context
		else m_contexts &= ~c;
	}

	void debugPrint(const char *message) const;

private:
	mutable int parentRow;
	QDocumentLineHandle *lineHandle;
	mutable int lineNumber;
	Contexts m_contexts;
};
Q_DECLARE_METATYPE(StructureEntry *)


/// iterator for fast traversal of a structure entry tree
class StructureEntryIterator
{
public:
	StructureEntryIterator(StructureEntry *entry);
	bool hasNext();
	StructureEntry *next();

private:
	QList<StructureEntry *> entryHierarchy; ///< hierarchy of next element (all parents and element itself)
	QList<int> indexHierarchy; ///< for every element in entryHierarchy the index of this element in its parent children
};


#endif // LATEXSTRUCTURE_H
