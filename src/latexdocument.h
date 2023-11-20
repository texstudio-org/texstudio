#ifndef Header_Latex_Document
#define Header_Latex_Document
//#undef QT_NO_DEBUG
#include "mostQtHeaders.h"
#include "latexstructure.h"
#include "qdocument.h"
#include "codesnippet.h"
#include "bibtexparser.h"
#include "latexparser.h"
//#include "usermacro.h"
#include "syntaxcheck.h"
#include "grammarcheck.h"
#include "latexpackage.h"
//#include "latexeditorview.h"

//class QDocumentLineHandle;
class LatexEditorView;
class QDocumentCursor;
class Macro;


struct FileNamePair {
	QString relative, absolute;
	FileNamePair(const QString &rel, const QString &abs);
};


struct ReferencePair {
	QString name;
	int start;
};

struct ReferencePairEx {
    QDocumentLineHandle *dlh;
    QVector<int> starts,lengths,formats;
    QList<int> formatList;
};


struct UserCommandPair {
	// name of command ("\command") or environment ("environment"),
	// null string for other user definitions (e.g. newcolumntype, definecolor)
	QString name;
	// information for code completion
	CodeSnippet snippet;
	UserCommandPair(const QString &name, const CodeSnippet &snippet);
    UserCommandPair(const QString &name, const QString &snippet);
};


/*! \brief extended QDocument
 *
 * Extended document for handling latex documents
 * Extension encompass filename handling, label,bibliography as well as syntax interpreting (Token system)
 * Also structureview is maintained here
 * The live-update of syntactical information is performed in \method patchStructure
 */
class LatexDocument: public QDocument
{
	Q_OBJECT

public:
    LatexDocument(QObject *parent = nullptr);
	~LatexDocument();

	enum CookieType {
		CK_COLS = 0
	};
	static const QSet<QString> LATEX_LIKE_LANGUAGES;

	void setFileName(const QString &fileName);
	void setEditorView(LatexEditorView *edView);///< set reference to actual GUI element of editor
    Q_INVOKABLE LatexEditorView *getEditorView() const;
	QString getFileName() const;
	QFileInfo getFileInfo() const;
    void setAsImportedFile(bool state);
    bool getStateImportedFile();

    Q_PROPERTY(QString fileName READ getFileName)
    Q_PROPERTY(QFileInfo fileInfo READ getFileInfo)
    Q_PROPERTY(LatexEditorView *editorView READ getEditorView)

	bool isHidden(); ///< true if editor is not displayed

	//	References containedLabels,containedReferences;
	QMultiHash<QDocumentLineHandle *, FileNamePair> &mentionedBibTeXFiles();
	const QMultiHash<QDocumentLineHandle *, FileNamePair> &mentionedBibTeXFiles() const;
	QStringList listOfMentionedBibTeXFiles() const;
	QSet<QString> lastCompiledBibTeXFiles;

	QList<Macro> localMacros;

	friend class SyntaxCheckTest;
    friend class LatexEditorViewTest;
	friend class ScriptEngineTest;
    friend class LatexDocumentTest;
    friend class TexStudioTest;

private:
	static QStringList someItems(const QMultiHash<QDocumentLineHandle *, ReferencePair> &list);
	void setFileNameInternal(const QString& fileName);
	void setFileNameInternal(const QString& fileName, const QFileInfo &pairedFileInfo);

public:
	Q_INVOKABLE QStringList labelItems() const; ///< all labels in this document
	Q_INVOKABLE QStringList refItems() const; ///< all references in this document
	Q_INVOKABLE QStringList bibItems() const; ///< all bibitem defined in this document
	Q_INVOKABLE QList<CodeSnippet> userCommandList() const; ///< all user commands defined in this document, sorted
    Q_INVOKABLE CodeSnippetList additionalCommandsList(QStringList &loadedFiles);
	void updateRefsLabels(const QString &ref);
    void recheckRefsLabels(QList<LatexDocument *> listOfDocs=QList<LatexDocument*>(), QStringList items=QStringList());
    static void updateRefHighlight(ReferencePairEx p);
	Q_INVOKABLE int countLabels(const QString &name);
	Q_INVOKABLE int countRefs(const QString &name);
	Q_INVOKABLE bool bibIdValid(const QString &name);
	Q_INVOKABLE bool isBibItem(const QString &name);
	Q_INVOKABLE QString findFileFromBibId(const QString &name); ///< find bib-file from bibid
	Q_INVOKABLE QMultiHash<QDocumentLineHandle *, int> getLabels(const QString &name); ///< get line/column from label name
	Q_INVOKABLE QMultiHash<QDocumentLineHandle *, int> getRefs(const QString &name); ///< get line/column from reference name
	Q_INVOKABLE QMultiHash<QDocumentLineHandle *, int> getBibItems(const QString &name);
    LatexDocument *getDocumentForLabel(const QString &name); ///< get document from label name
    int countCommandDefintions(const QString &name, const QString word=""); ///< count how many time a certain command is defined, used for checking for duplicates
	Q_INVOKABLE QDocumentLineHandle *findCommandDefinition(const QString &name); ///< get line of definition from command name (may return nullptr)
	Q_INVOKABLE QDocumentLineHandle *findUsePackage(const QString &name); ///< get line of \usepackage from package name (may return nullptr)
	Q_INVOKABLE void replaceItems(QMultiHash<QDocumentLineHandle *, ReferencePair> items, const QString &newName, QDocumentCursor *cursor = nullptr);
    Q_INVOKABLE void replaceLabel(const QString &name, const QString &newName, QDocumentCursor *cursor = nullptr);
    Q_INVOKABLE void replaceRefs(const QString &name, const QString &newName, QDocumentCursor *cursor = nullptr);
	Q_INVOKABLE void replaceLabelsAndRefs(const QString &name, const QString &newName);

	QDocumentSelection sectionSelection(StructureEntry *section);
    void clearAppendix();
	StructureEntry *findSectionForLine(int currentLine);

	LatexDocuments *parent;

	void setTemporaryFileName(const QString &fileName);
	Q_INVOKABLE QString getTemporaryFileName() const;
	Q_INVOKABLE QString getFileNameOrTemporaryFileName() const;
	Q_INVOKABLE QFileInfo getTemporaryFileInfo() const;
	Q_INVOKABLE QString getAbsoluteFilePath(const QString &relName, const QString &extension, const QStringList &additionalSearchPaths = QStringList()) const;

	void setMasterDocument(LatexDocument *doc, bool recheck = true);
	void addChild(LatexDocument *doc);
	void removeChild(LatexDocument *doc);
	bool containsChild(LatexDocument *doc) const;
    Q_INVOKABLE LatexDocument *getMasterDocument() const;
    const LatexDocument *getRootDocument(QSet<const LatexDocument *> *visitedDocs = nullptr, bool breakAtSubfileRoot=false) const;
	Q_INVOKABLE LatexDocument *getRootDocument();
    Q_INVOKABLE LatexDocument *getTopMasterDocument();

    Q_INVOKABLE QStringList includedFiles(bool importsOnly=false);
	Q_INVOKABLE QStringList includedFilesAndParent();
    Q_INVOKABLE QList<LatexDocument *> getListOfDocs(QSet<LatexDocument *> *visitedDocs = nullptr,bool onlyChildDocs=false);

    LatexParser ltxCommands; /// locally defined latex commands
    QSharedPointer<LatexParser> lp;

	Q_INVOKABLE bool containsPackage(const QString &name);
	Q_INVOKABLE QStringList containedPackages();
    Q_INVOKABLE QSet<QString> usedPackages(bool onlyInChildDocs=false);
    bool updateCompletionFiles(const bool updatePackages=true,const bool updateUserCommands=true);
    const QSet<QString> &getCWLFiles() const;

    Q_INVOKABLE QString spellingDictName() const;
	Q_INVOKABLE QString getMagicComment(const QString &name) const;
	Q_INVOKABLE StructureEntry *getMagicCommentEntry(const QString &name) const;
    Q_INVOKABLE void updateMagicComment(const QString &name, const QString &val, bool createIfNonExisting = false, QString prefix="!TeX");

	void updateMagicCommentScripts();
	static bool splitMagicComment(const QString &comment, QString &name, QString &val);

	QString findFileName(QString fname);
	bool fileExits(QString fname);

	void saveLineSnapshot();
	QDocumentLine lineFromLineSnapshot(int lineNumber);
	int lineToLineSnapshotLineNumber(const QDocumentLine &line);

	bool remeberAutoReload; //remember whether doc is auto reloaded while hidden (and auto reload is always activated).

	bool mayHaveDiffMarkers;

	void emitUpdateCompleter();

    static int syntaxErrorFormat,spellErrorFormat;

	bool languageIsLatexLike() const;
	void reCheckSyntax(int lineStart = 0, int lineNum = -1);
	QString getErrorAt(QDocumentLineHandle *dlh, int pos, StackEnvironment previous, TokenStack stack);

	void getEnv(int lineNumber, StackEnvironment &env); // get Environment for syntax checking, number of cols is now part of env
	Q_INVOKABLE QString getLastEnvName(int lineNumber); // special function to use with javascript (insert "\item" from menu)

    void enableSyntaxCheck(bool enable);
    Q_INVOKABLE bool isSubfileRoot();
    bool saveCachingData(const QString &folder);
    bool restoreCachedData(const QString &folder, const QString fileName);
    bool isIncompleteInMemory();
    void startSyntaxChecker();

    struct HandledData {
        QStringList removedUsepackages;
        QStringList addedUsepackages;
        QStringList removedUserCommands;
        QStringList addedUserCommands;
        QStringList lstFilesToLoad;
        QStringList removedIncludes;
        QList<LatexDocument *> addedIncludes;
        QStringList oldBibs;
        bool completerNeedsUpdate = false;
        bool bibItemsChanged = false;
        bool bibTeXFilesNeedsUpdate = false;
        bool updateSyntaxCheck = false;
        int posLabel;
        int posTodo;
        int posBlock;
        int posBibTeX;
    };

    int lexLines(int &lineNr,int &count,bool recheck=false);
    void lexLinesSimple(const int lineNr,const int count);
    void handleComments(QDocumentLineHandle *dlh, int &curLineNr, std::list<StructureEntry*>::iterator &docStructureIter);
    void removeLineElements(QDocumentLineHandle *dlh, HandledData &changedCommands);
    void handleRescanDocuments(HandledData changedCommands);
    void interpretCommandArguments(QDocumentLineHandle *dlh, const int i, HandledData &data, bool recheckLabels, std::list<StructureEntry*>::iterator &docStructureIter);
    void reinterpretCommandArguments(HandledData &changedCommands);
    void replaceOrAdd(std::list<StructureEntry*>::iterator &docStructureIter, QDocumentLineHandle *dlh, StructureEntry *newElement);

    void gatherCompletionFiles(QStringList &files, QStringList &loadedFiles, LatexPackage &pck, bool gatherForCompleter = false);

    std::list<StructureEntry *> docStructure;

private:
	QString fileName; //absolute
	QString temporaryFileName; //absolute, temporary
	QFileInfo fileInfo;
    bool importedFile=false; /// mark if this file was loaded via import/subimport, i.e. inputs relative to this file instead of root !

	LatexEditorView *edView;

	LatexDocument *masterDocument;
	QSet<LatexDocument *> childDocs;

	QMultiHash<QDocumentLineHandle *, ReferencePair> mLabelItem;
	QMultiHash<QDocumentLineHandle *, ReferencePair> mBibItem;
	QMultiHash<QDocumentLineHandle *, ReferencePair> mRefItem;
	QMultiHash<QDocumentLineHandle *, FileNamePair> mMentionedBibTeXFiles;
	QMultiHash<QDocumentLineHandle *, UserCommandPair> mUserCommandList;
	QMultiHash<QDocumentLineHandle *, QString> mUsepackageList;
	QMultiHash<QDocumentLineHandle *, QString> mIncludedFilesList;
    QMultiHash<QDocumentLineHandle *, QString> mImportedFilesList;

	QList<QDocumentLineHandle *> mLineSnapshot;

	QSet<QString> mCompleterWords; // local list of completer words
	QSet<QString> mCWLFiles;

	QString mSpellingDictName;

	QString mClassOptions; // store class options, if they are defined in this doc

	QDocumentLineHandle *mAppendixLine, *mBeyondEnd;

	void updateContext(QDocumentLineHandle *oldLine, QDocumentLineHandle *newLine, StructureEntry::Context context);
    void setContextForLines(int startLine, int endLine, StructureEntry::Context context, bool state);

    void removeRangeFromStructure(int lineNr,int count);

    QStringList unrollStructure();

    void addMagicComment(const QString &text, int lineNr, std::list<StructureEntry*>::iterator &docStructureIter);
	void parseMagicComment(const QString &name, const QString &val, StructureEntry *se);

    SyntaxCheck synChecker;
	Environment unclosedEnv;

	bool syntaxChecking;

    bool m_isSubfileRoot=false;

    bool m_cachedDataOnly=false;

#ifndef QT_NO_DEBUG
public:
	QSet<StructureEntry *> StructureContent;
	void checkForLeak();
#endif

public slots:
	void updateStructure();
    void patchStructure(int linenr, int count, bool recheck = false);
    void patchStructureRemoval(QDocumentLineHandle *dlh,int hint=-1,int count=1);
	void initClearStructure();
    void updateLtxCommands(bool updateAll = false, bool updatePackages=true);
    void addLtxCommands();
    void setLtxCommands(QSharedPointer<LatexParser> cmds);
    void setSpeller(SpellerUtility *speller);
    void setReplacementList(QMap<QString,QString> replacementList);
	void updateSettings();
    void checkNextLine(QDocumentLineHandle *dlh, bool clearOverlay, int ticket, int hint=-1);

signals:
    void structureUpdated();
	void updateCompleter();
    void updateCompleterCommands();
	void updateBibTeXFiles();
	void importPackage(QString name);
	void spellingDictChanged(const QString &name);
	void encodingChanged();
	void bookmarkLineUpdated(int lineNr);
};
//Q_DECLARE_METATYPE(LatexDocument *)



/*! \brief administrate all open documents
 * organizes all open documents
 * handles master/slave or root/child relation between documents
 * documents can be hidden, i.e. they don't have a visible editor
 * hidden documents are used to keep syntax information present in the editor without the necessesity to make an extra storage architecture for closed elements
 * documents which are closed/deleted are hidden if they are child documents of still used documents
 * Furthermore autimatically loaded documents are generally hidden
 */
class LatexDocuments: public QObject
{
	Q_OBJECT

public:
    //LatexDocumentsModel *model; ///< reference to latexmodel which generates the structure information for treeview
	LatexDocument *masterDocument; ///< master/root document if it is set (in automatic mode ==NULL)
	LatexDocument *currentDocument; ///< current edited document
	QList<LatexDocument *> documents; ///< list of open documents
	QList<LatexDocument *> hiddenDocuments; ///< list of open documents with no visible editor

	LatexDocuments();

	void addDocument(LatexDocument *document, bool hidden = false);
	void deleteDocument(LatexDocument *document, bool hidden = false, bool purge = false);
	void move(int from, int to);
	Q_INVOKABLE void setMasterDocument(LatexDocument *document); ///< explicitely set master document
	Q_INVOKABLE LatexDocument *getCurrentDocument() const;
	Q_INVOKABLE LatexDocument *getMasterDocument() const; ///< get explicit master if set
	Q_INVOKABLE QList<LatexDocument *> getDocuments() const; ///< get all documents (visible&hidden)

    Q_PROPERTY(LatexDocument *currentDocument READ getCurrentDocument)
    Q_PROPERTY(LatexDocument *masterDocument READ getMasterDocument)
    Q_PROPERTY(QList<LatexDocument *> documents READ getDocuments); //<- semicolon necessary due to qt bug 22992

    Q_INVOKABLE LatexDocument *getRootDocumentForDoc(LatexDocument *doc = nullptr, bool breakAtSubfileRoot=false) const ; ///< no argument means current doc ...

	Q_INVOKABLE QString getCurrentFileName() const; ///< returns the absolute file name of the current file or "" if none is opened
	Q_INVOKABLE QString getCompileFileName() const; ///< returns the absolute file name of the file to be compiled (master or current)
	Q_INVOKABLE QString getTemporaryCompileFileName() const; ///< returns the absolute file name of the file to be compiled (master or current)
	Q_INVOKABLE QString getLogFileName() const;
	Q_INVOKABLE QString getAbsoluteFilePath(const QString &relName, const QString &extension = "", const QStringList &additionalSearchPaths = QStringList()) const;

	Q_INVOKABLE LatexDocument *findDocument(const QString &fileName, bool checkTemporaryNames = false) const;
	Q_INVOKABLE LatexDocument *findDocument(const QDocument *qDoc) const;
	Q_INVOKABLE LatexDocument *findDocumentFromName(const QString &fileName) const;

	void reorder(const QList<LatexDocument *> &order);

	void settingsRead();
    void setCachingFolder(const QString &folder);
    QString getCachingFolder() const;

	Q_INVOKABLE bool singleMode() const;

	//support for included BibTeX-files
	QMap<QString, BibTeXFileInfo> bibTeXFiles; ///< bibtex files loaded by txs
	bool bibTeXFilesModified; ///< true if the BibTeX files were changed after the last compilation
	QStringList mentionedBibTeXFiles; ///< bibtex files imported in the tex file (absolute after updateBibFiles)
	//QSet<QString> bibItems; // direct defined bibitems
	//QSet<QString> allBibTeXIds;
	void updateBibFiles(bool updateFiles = true);

	void updateMasterSlaveRelations(LatexDocument *doc, bool recheckRefs = true, bool updateCompleterNow = false);

	bool showLineNumbersInStructure;
	int indentationInStructure;
	bool showCommentedElementsInStructure;
	bool markStructureElementsBeyondEnd;
	bool markStructureElementsInAppendix;
	bool indentIncludesInStructure; //pointer! those above should be changed as well


	QHash<QString, LatexPackage> cachedPackages;
    bool addDocsToLoad(QStringList filenames, LatexDocument *parentDocument, bool isHigherLevel=false);
	void removeDocs(QStringList removeIncludes);
	void hideDocInEditor(LatexEditorView *edView);
	QString findPackageByCommand(const QString command);
	void requestQNFAupdate();

signals:
	void masterDocumentChanged(LatexDocument *masterDocument);
	void aboutToDeleteDocument(LatexDocument *document);
    void docsToLoad(QStringList filenames,QSharedPointer<LatexParser> lp);
	void docToHide(LatexEditorView *edView);
	void updateQNFA();

private slots:
	void bibTeXFilesNeedUpdate();

public slots:
    void lineGrammarChecked(LatexDocument *doc, QDocumentLineHandle *line, int lineNr, const QList<GrammarError> &errors);
	void requestedClose();

private:
	bool m_patchEnabled;
    QString m_cachingFolder;
};

#endif // LATEXDOCUMENT_H
