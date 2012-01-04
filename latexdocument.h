#ifndef LATEXDOCUMENT_H
#define LATEXDOCUMENT_H
//#undef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "bibtexparser.h"
#include "latexeditorview.h"

class QDocumentLineHandle;
class LatexEditorView;
class LatexDocument;
class LatexDocuments;
class QDocument;
class QDocumentCursor;
struct QDocumentSelection;

struct StructureEntry{
	enum Type {SE_DOCUMENT_ROOT,SE_OVERVIEW,SE_SECTION,SE_BIBTEX,SE_TODO,SE_MAGICCOMMENT,SE_INCLUDE,SE_LABEL,SE_BLOCK=SE_LABEL};
	Type type;
	QString title;
	QString tooltip; // optional because most tooltips are automatically generated.
	int level; //only used for section types
	bool valid; //currently only used for magic comments
	int lineNumber;
	QDocumentLineHandle* lineHandle;
	QList<StructureEntry*> children;
	StructureEntry* parent;
	LatexDocument* document;
	bool appendix;
	
	StructureEntry(LatexDocument* doc, Type newType);
	~StructureEntry();
	void add(StructureEntry* child);
	void insert(int pos, StructureEntry* child);
	
	int getRealLineNumber();
};

//iterator for fast traversal of a structure entry tree
class StructureEntryIterator{
public:
	StructureEntryIterator(StructureEntry* entry);
	bool hasNext();
	StructureEntry* next();
private:
	QList<StructureEntry*> entryHierarchy; //hierarchy of next element (all parents and element itself)
	QList<int> indexHierarchy; //for every element in entryHierarchy the index of this element in its parent children
};

struct FileNamePair{
	QString relative, absolute;
	FileNamePair(const QString& rel);
};

struct ReferencePair{
	QString name;
	int start;
};

class LatexDocument: public QDocument
{
	Q_OBJECT
public:
	LatexDocument(QObject *parent=0);
	~LatexDocument();
	
	enum CookieType{
		CK_COLS=0
	};
	void setFileName(const QString& fileName);
	void setEditorView(LatexEditorView* edView);
	LatexEditorView *getEditorView() const;
	QString getFileName() const;
	QFileInfo getFileInfo() const;
	//QSet<QString> texFiles; //absolute file names, also contains fileName
	
	//	References containedLabels,containedReferences;
	QMultiHash<QDocumentLineHandle*,FileNamePair>& mentionedBibTeXFiles();
	const QMultiHash<QDocumentLineHandle*,FileNamePair>& mentionedBibTeXFiles() const;
	
	//	QMap<QString,DocumentLine> mentionedBibTeXFiles; //bibtex files imported in the tex file (absolute after updateBibFiles)
	//	QSet<QString> allBibTeXIds;
	
	QStringList labelItem()const {
		QList<ReferencePair> lst=mLabelItem.values();
		QStringList result;
		foreach(const ReferencePair& elem,lst){
			result << elem.name;
		}
		
		return result;
	}
	QStringList labelItemAt(QDocumentLineHandle *dlh){
		QList<ReferencePair> lst=mLabelItem.values(dlh);
		QStringList result;
		foreach(const ReferencePair& elem,lst){
			result << elem.name;
		}
		return result;
	}
	QStringList refItem() const{
		QList<ReferencePair> lst=mRefItem.values();
		QStringList result;
		foreach(const ReferencePair& elem,lst){
			result << elem.name;
		}
		return result;
	}
	QStringList refItemAt(QDocumentLineHandle *dlh){
		QList<ReferencePair> lst=mRefItem.values(dlh);
		QStringList result;
		foreach(const ReferencePair& elem,lst){
			result << elem.name;
		}
		return result;
	}
	const QSet<QString> userCommandList() const{
		return mUserCommandList.values().toSet();
	}
	const QSet<QString> additionalCommandsList() const{
		return mCompleterWords;
	}
	void updateRefsLabels(const QString& ref);
	void recheckRefsLabels();
	int countLabels(const QString& name);
	int countRefs(const QString& name);
	QMultiHash<QDocumentLineHandle*,int> getLabels(QString name);
	QMultiHash<QDocumentLineHandle*,int> getRefs(QString name);
	
	//void includeDocument(LatexDocument* includedDocument);
	
	//QString getAbsoluteFilePath(const QString& relativePath); //returns the absolute file path for an included file
	
	StructureEntry* baseStructure;
	
	QDocumentSelection sectionSelection(StructureEntry* section);
	void clearAppendix(){
		mAppendixLine=0;
	}
	StructureEntry * findSectionForLine(int currentLine);
	
	LatexDocuments *parent;
	
	void setTemporaryFileName(const QString& fileName);
	QString getTemporaryFileName();
	QString getAbsoluteFilePath(const QString & relName, const QString &extension);
	
	void setMasterDocument(LatexDocument* doc);
	LatexDocument* getMasterDocument() const{
		return masterDocument;
	}
	LatexDocument* getTopMasterDocument(QSet<LatexDocument*> *visitedDocs=0);
	
	QStringList includedFiles();
	QList<LatexDocument *> getListOfDocs(QSet<LatexDocument*> *visitedDocs=0);
	
	LatexParser ltxCommands;
	
	bool containsPackage(const QString& name);
	void updateCompletionFiles(QStringList &added,QStringList &removed,bool forceUpdate);
	void updateCompletionFiles(QStringList &files,bool forceUpdate);
	
	QLocale spellingLanguage() {
		return mSpellingLanguage;
	}
	QString getMagicComment(const QString& name);
	QDocumentLineHandle* getMagicCommentLineHandle(const QString &name);
	void updateMagicComment(const QString &name, const QString &val, bool createIfNonExisting=false);
	
private:
	QString fileName; //absolute
	QString temporaryFileName; //absolute, temporary
	QFileInfo fileInfo;
	
	LatexEditorView* edView;
	
	LatexDocument* masterDocument;
	
	StructureEntry* magicCommentList;
	StructureEntry* labelList;
	StructureEntry* todoList;
	StructureEntry* bibTeXList;
	StructureEntry* blockList;
	
	QMultiHash<QDocumentLineHandle*,ReferencePair> mLabelItem;
	QMultiHash<QDocumentLineHandle*,ReferencePair> mRefItem;
	QMultiHash<QDocumentLineHandle*,FileNamePair> mMentionedBibTeXFiles;
	QMultiHash<QDocumentLineHandle*,QString> mUserCommandList;
	QMultiHash<QDocumentLineHandle*,QString> mUsepackageList;
	
	QSet<QString> mCompleterWords; // local list of completer words
	
	QLocale mSpellingLanguage; // default/not specified: QLocale::c()
	
	QDocumentLineHandle *mAppendixLine;
	
	void updateAppendix(QDocumentLineHandle *oldLine,QDocumentLineHandle *newLine);
	void setAppendix(StructureEntry *se,int startLine,int endLine,bool state);
	bool fileExits(QString fname);
	QString findFileName(QString fname);
	void findStructureEntryBefore(QMutableListIterator<StructureEntry*> &iter,QMultiHash<QDocumentLineHandle*,StructureEntry*> &MapOfElemnts,int linenr,int count);
	void splitStructure(StructureEntry* se,QVector<StructureEntry*> &parent_level,QVector<QList<StructureEntry*> > &remainingChildren,QMap<StructureEntry*,int> &toBeDeleted,QMultiHash<QDocumentLineHandle*,StructureEntry*> &MapOfElements,int linenr,int count,int lvl=0,bool front=true,bool back=true);
	
	void removeAndDeleteElement(StructureEntry* se, int row);
	
	bool splitMagicComment(const QString &comment, QString &name, QString &val);
	void parseMagicComment(const QString &name, const QString &val, StructureEntry* se);
	
	void gatherCompletionFiles(QStringList &files,QStringList &loadedFiles,LatexPackage &pck);
	
#ifndef QT_NO_DEBUG
public:
	QSet<StructureEntry*> StructureContent;
	void checkForLeak();
#endif
	
public slots:
	void updateStructure();
	void patchStructure(int linenr, int count);
	void patchStructureRemoval(QDocumentLineHandle* dlh);
	void clearStructure();
	void initStructure();
	
signals:
	void hasBeenIncluded(const LatexDocument& newMasterDocument);
	void structureUpdated(LatexDocument* document,StructureEntry *highlight=0);
	void structureLost(LatexDocument* document);
	void removeElement(StructureEntry *se,int row);
	void removeElementFinished();
	void addElement(StructureEntry *se,int row);
	void addElementFinished();
	void updateElement(StructureEntry *se);
	void updateCompleter();
	void updateBibTeXFiles();
	void toBeChanged();
	void importPackage(QString name);
	void spellingLanguageChanged(const QLocale &lang);
};

class LatexDocumentsModel: public QAbstractItemModel{
	Q_OBJECT
private:
	LatexDocuments& documents;
	QIcon iconDocument, iconMasterDocument, iconBibTeX, iconInclude, iconWarning;
	QVector<QIcon> iconSection;
	QModelIndex mHighlightIndex;
	bool m_singleMode;
	
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
	QModelIndex highlightedEntry();
	void setHighlightedEntry(StructureEntry* entry);
	
	void resetAll();
	void resetHighlight();
	void setSingleDocMode(bool singleMode);
	bool getSingleDocMode();
private slots:
	void structureUpdated(LatexDocument* document,StructureEntry *highlight=0);
	void structureLost(LatexDocument* document);
	void removeElement(StructureEntry *se,int row);
	void removeElementFinished();
	void addElement(StructureEntry *se,int row);
	void addElementFinished();
	void updateElement(StructureEntry *se);
	
	friend class LatexDocuments;
};

class LatexDocuments: public QObject
{
	Q_OBJECT
public:
	LatexDocumentsModel* model;
	LatexDocument* masterDocument;
	LatexDocument* currentDocument;
	QList<LatexDocument*> documents;
	
	LatexDocuments();
	~LatexDocuments();
	void addDocument(LatexDocument* document);
	void deleteDocument(LatexDocument* document);
	void setMasterDocument(LatexDocument* document);
	
	LatexDocument *getMasterDocumentForDoc(LatexDocument *doc=0); // no argument means current doc ...
	
	QString getCurrentFileName(); //returns the absolute file name of the current file or "" if none is opened
	QString getCompileFileName(); //returns the absolute file name of the file to be compiled (master or current)
	QString getTemporaryCompileFileName(); //returns the absolute file name of the file to be compiled (master or current)
	QString getAbsoluteFilePath(const QString & relName, const QString &extension="");
	
	LatexDocument* findDocument(const QString& fileName, bool checkTemporaryNames = false);
	LatexDocument* findDocument(const QDocument *qDoc);
	LatexDocument* findDocumentFromName(const QString& fileName);
	
	void settingsRead();
	
	bool singleMode();
	
	//support for included BibTeX-files
	QMap<QString, BibTeXFileInfo> bibTeXFiles; //bibtex files loaded by txs
	bool bibTeXFilesModified; //true iff the BibTeX files were changed after the last compilation
	QStringList mentionedBibTeXFiles; //bibtex files imported in the tex file (absolute after updateBibFiles)
	QSet<QString> allBibTeXIds;
	void updateBibFiles();
	
	
	void updateStructure();
	void updateLayout();
	void updateMasterSlaveRelations(LatexDocument *doc);
	
	LatexParser ltxCommands;
	bool showLineNumbersInStructure;
	int indentationInStructure;
signals:
	void masterDocumentChanged(LatexDocument *masterDocument);
private slots:
	void bibTeXFilesNeedUpdate();
private:
};

#endif // LATEXDOCUMENT_H
