#ifndef LATEXSTRUCTURE_H
#define LATEXSTRUCTURE_H

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
		InAppendix = 0x0001,
		BeyondEnd = 0x0010
	};
	Q_DECLARE_FLAGS(Contexts, Context)
	Type type;
	QString title; ///< actual text to be displayed
	QString tooltip; ///< optional because most tooltips are automatically generated.
	int level; ///< only used for section types!
	bool valid; ///< currently only used for includes and magic comments
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



/*!
 * \brief model to interpret structure view information for treeview
 * The actual structure is stored in StructureEntry. This model extracts the necessary information for treeview.
 */
class LatexDocumentsModel: public QAbstractItemModel
{
	Q_OBJECT

private:
	LatexDocuments &documents;
	QIcon iconDocument, iconMasterDocument, iconBibTeX, iconInclude, iconWarning;
	QVector<QIcon> iconSection;
	QModelIndex mHighlightIndex;
	bool m_singleMode;

public:
	LatexDocumentsModel(LatexDocuments &docs);
	Qt::ItemFlags flags ( const QModelIndex &index ) const;
	QVariant data ( const QModelIndex &index, int role = Qt::DisplayRole ) const;
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	int rowCount ( const QModelIndex &parent = QModelIndex() ) const;
	int columnCount ( const QModelIndex &parent = QModelIndex() ) const;
	QModelIndex index ( int row, int column, const QModelIndex &parent = QModelIndex() ) const;
	QModelIndex index ( StructureEntry *entry ) const;
	QModelIndex parent ( const QModelIndex &index ) const;

	static StructureEntry *indexToStructureEntry(const QModelIndex &index );
	static LatexDocument *indexToDocument(const QModelIndex &index );
	static StructureEntry *labelForStructureEntry(const StructureEntry *entry);
	QModelIndex highlightedEntry();

	void resetAll();
	void resetHighlight();
	void setSingleDocMode(bool singleMode);
	bool getSingleDocMode();
	void moveDocs(int from, int to);

    void setHighlightedEntry(StructureEntry *entry);

private slots:
    void structureUpdated(LatexDocument *document, StructureEntry *highlight = nullptr);
	void structureLost(LatexDocument *document);
	void removeElement(StructureEntry *se, int row);
	void removeElementFinished();
	void addElement(StructureEntry *se, int row);
	void addElementFinished();
	void updateElement(StructureEntry *se);

	friend class LatexDocuments;
};

#endif // LATEXSTRUCTURE_H
