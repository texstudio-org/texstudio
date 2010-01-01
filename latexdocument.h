#ifndef LATEXDOCUMENT_H
#define LATEXDOCUMENT_H
#include "mostQtHeaders.h"
#include "bibtexparser.h"

class QDocumentLineHandle;
class LatexEditorView;
class LatexDocument;
class QDocument;
class QDocumentCursor;
struct QDocumentSelection;

/*class References {
public:
	References() {}
	References(QString pattern) : mPattern(pattern) {}
	void insert(QString key,QDocumentLineHandle* handle) {mReferences.insert(key,handle);}
	QList<QDocumentLineHandle*> values(QString key) {return mReferences.values(key);}
	bool contains(QString key) {return mReferences.contains(key);}
	int count(QString key) {return mReferences.count(key);}
	QStringList removeByHandle(QDocumentLineHandle* handle);
	void removeUpdateByHandle(QDocumentLineHandle* handle,References* altRefs=0);
	void updateByKeys(QStringList refs,References* altRefs=0);
	void setPattern(QString pattern) {mPattern=pattern;}
	QString pattern() {return mPattern;}
	void setFormats(int multiple,int single,int none) {
		referenceMultipleFormat=multiple;
		referencePresentFormat=single;
		referenceMissingFormat=none;
	}
	void unite(References others){
		//TODO:
	}
protected:
	QMultiHash<QString,QDocumentLineHandle*> mReferences;
	int referenceMultipleFormat,referencePresentFormat,referenceMissingFormat;
	QString mPattern;
};*/


struct StructureEntry{
	enum Type {SE_DOCUMENT_ROOT,SE_OVERVIEW,SE_SECTION,SE_BIBTEX,SE_TODO,SE_INCLUDE,SE_LABEL};
	Type type;
	QString title;
	int level; //only used for section types
	int lineNumber;
	QDocumentLineHandle* lineHandle;
	QList<StructureEntry*> children;
	StructureEntry* parent;
	LatexDocument* document;

	StructureEntry(LatexDocument* doc, Type newType);
	StructureEntry(LatexDocument* doc, StructureEntry* parent, Type newType);
	~StructureEntry();
	void add(StructureEntry* child);
	void insert(int pos, StructureEntry* child);

	int getRealLineNumber() const;
};

class LatexDocument: public QObject
{
	Q_OBJECT
public:
	LatexDocument();
	~LatexDocument();
	LatexEditorView* edView;
	QDocument* text;

	//QString fileName; //Masterfile, absolute
	QSet<QString> texFiles; //absolute file names, also contains fileName

//	References containedLabels,containedReferences;
//	QMap<QString,DocumentLine> mentionedBibTeXFiles; //bibtex files imported in the tex file (absolute after updateBibFiles)
//	QSet<QString> allBibTeXIds;

	QStringList labelItem;
	QStringList userCommandList;

	//void includeDocument(LatexDocument* includedDocument);

	//QString getAbsoluteFilePath(const QString& relativePath); //returns the absolute file path for an included file

	StructureEntry* baseStructure;
	StructureEntry* labelList;
	StructureEntry* todoList;
	StructureEntry* bibTeXList;


	QDocumentSelection sectionSelection(StructureEntry* section);

public slots:
	void updateStructure();

signals:
	void hasBeenIncluded(const LatexDocument& newMasterDocument);
	void structureUpdated(LatexDocument* document);
	void structureLost(LatexDocument* document);
};

class LatexDocuments;
class LatexDocumentsModel: public QAbstractItemModel{
	Q_OBJECT
private:
	LatexDocuments& documents;
	QIcon iconDocument, iconBibTeX, iconInclude;
	QVector<QIcon> iconSection;
	StructureEntry* mHighlightedEntry;

public:
	LatexDocumentsModel(LatexDocuments& docs);
	Qt::ItemFlags flags ( const QModelIndex & index ) const;
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
	QModelIndex index ( StructureEntry* entry ) const;
	QModelIndex parent ( const QModelIndex & index ) const;

	static StructureEntry* indexToStructureEntry(const QModelIndex & index );
	StructureEntry* highlightedEntry();
	void setHighlightedEntry(StructureEntry* entry);

private slots:
	void structureUpdated(LatexDocument* document);
	void structureLost(LatexDocument* document);

	friend class LatexDocuments;
};

class LatexDocuments
{
public:
	LatexDocumentsModel* model;
	QList<LatexDocument*> documents;
	QMap<QString, BibTeXFileInfo> bibTeXFiles; //bibtex files loaded by tmx
	bool bibTeXFilesModified; //true iff the BibTeX files were changed after the last compilation

	LatexDocuments();
	~LatexDocuments();
	void addDocument(LatexDocument* document);
	void deleteDocument(LatexDocument* document);
};

#endif // LATEXDOCUMENT_H
