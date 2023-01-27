/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                         2008-2009 by Benito van der Zander              *
 *   http://texstudio.sourceforge.net
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef Header_TexStudio
#define Header_TexStudio

#include "mostQtHeaders.h"

#include "bibtexparser.h"
#include "buildmanager.h"
#include "bookmarks.h"
#include "codesnippet.h"
#include "configmanager.h"
#include "cursorhistory.h"
#include "latexlog.h"
#include "latexdocument.h"
#include "latexeditorview.h"
#include "latexcompleter.h"
#include "usermacro.h"
#include "xmltagslistwidget.h"
#include "spellerdialog.h"
#include "textanalysis.h"
#include "toolwidgets.h"
#include "txstabwidget.h"
#include "editors.h"
#include "searchresultwidget.h"
#include "unicodeinsertion.h"
#include "tablemanipulation.h"
//#include "PDFDocument.h"
#include <QSplashScreen>
#include "session.h"
#include "sessionlist.h"
#include "qformatfactory.h"
#include "qlanguagefactory.h"
#include "qlinemarksinfocenter.h"
#include "latexstyleparser.h"
#include "kpathseaParser.h"
#include "diffoperations.h"
#include "svn.h"
#include "git.h"
#include "help.h"

#include <QProgressDialog>

/*!
 * \file texstudio.h
 * \brief Definition for Mainwindow
 */

class UserMenuDialog;
class GrammarCheck;
class FileSelector;
class LatexReference;
class SymbolListModel;
class SymbolWidget;
class StructureTreeView;

//Q_DECLARE_METATYPE(QSet<QString>)
#if QT_VERSION_MAJOR<6
Q_DECLARE_METATYPE(std::set<QString>)
#endif

class Texstudio : public QMainWindow
{
	Q_OBJECT

public:
    Texstudio(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(), QSplashScreen *splash = nullptr);
	~Texstudio();

	Q_INVOKABLE QString getCurrentFileName(); ///< returns the absolute file name of the current file or "" if none is opene
	Q_INVOKABLE QString getAbsoluteFilePath(const QString &relName, const QString &extension = ""); ///< treats the path relative to the compiled .tex file
	Q_INVOKABLE QString getRelativeFileName(const QString &file, QString basepath, bool keepSuffix = false); ///< provide function for scripts
    Q_INVOKABLE bool fileExists(const QString &file); ///< provide function for scripts
	QByteArray windowstate; ///< qt window state, used for state-restoring
	bool tobemaximized, tobefullscreen;

    Q_INVOKABLE void runInternalCommand(const QString &cmd, const QString &master, const QString &options);

public slots:
	LatexEditorView *load(const QString &f , bool asProject = false, bool hidden = false, bool recheck = true, bool dontAsk = false);
    void executeCommandLine(const QStringList &args, bool realCmdLine);
	void hideSplash(); ///< hide splash screen
	void startupCompleted();
	void onOtherInstanceMessage(const QString &);  ///< For messages for the single instance
	void fuzzCursorHistory();
	void fuzzBackForward();
    void setBuildButtonsDisabled(bool c);


protected:
	//these are just wrappers around configManager so we don't have to type so much (todo??? move them to configmanager.h and use a singleton design???)
	Q_INVOKABLE inline QMenu *newManagedMenu(const QString &id, const QString &text) { return configManager.newManagedMenu(id, text); }
	Q_INVOKABLE inline QMenu *newManagedMenu(QMenu *menu, const QString &id, const QString &text) { return configManager.newManagedMenu(menu, id, text); }
    Q_INVOKABLE QAction *newManagedAction(QWidget *menu, const QString &id, const QString &text, const char *slotName = nullptr, const QKeySequence &shortCut = 0, const QString &iconFile = "", const QList<QVariant> &args = QList<QVariant>());
	Q_INVOKABLE QAction *newManagedAction(QWidget *menu, const QString &id, const QString &text, const char *slotName, const QList<QKeySequence> &shortCuts, const QString &iconFile = "", const QList<QVariant> &args = QList<QVariant>());
    Q_INVOKABLE QAction *newManagedEditorAction(QWidget *menu, const QString &id, const QString &text, const char *slotName = nullptr, const QKeySequence &shortCut = 0, const QString &iconFile = "", const QList<QVariant> &args = QList<QVariant>());
	Q_INVOKABLE QAction *newManagedEditorAction(QWidget *menu, const QString &id, const QString &text, const char *slotName, const QList<QKeySequence> &shortCuts, const QString &iconFile = "", const QList<QVariant> &args = QList<QVariant>());
	Q_INVOKABLE inline QAction *newManagedAction(QWidget *menu, const QString &id, QAction *act) { return configManager.newManagedAction(menu, id, act); }
	Q_INVOKABLE inline QMenu *getManagedMenu(const QString &id) { return configManager.getManagedMenu(id); }
	Q_INVOKABLE inline QAction *getManagedAction(const QString &id) { return configManager.getManagedAction(id); }
	Q_INVOKABLE inline QList<QAction *> getManagedActions(const QStringList &ids, const QString &commonPrefix = "") { return configManager.getManagedActions(ids, commonPrefix); }
    Q_INVOKABLE QAction *insertManagedAction(QAction *before, const QString &id, const QString &text, const char *slotName = nullptr, const QKeySequence &shortCut = 0, const QString &iconFile = "");
    Q_INVOKABLE void loadManagedMenu(const QString &fn);

    Q_INVOKABLE void setupToolBars();

	void addTagList(const QString &id, const QString &iconName, const QString &text, const QString &tagFile);
    void addMacrosAsTagList();

private slots:
	void updateToolBarMenu(const QString &menuName);
	void showTestProgress(const QString &message);
    void leftPanelChanged(QWidget* widget);
private:
    bool executeTests(const QStringList &args); ///< execute self-tests. Only works for debug-builds.
	void generateAddtionalTranslations();
	void setupMenus();
	void setupDockWidgets();
	void createStatusBar();
	bool activateEditorForFile(QString f, bool checkTemporaryNames = false, bool setFocus = true);
	bool saveAllFilesForClosing(); ///< checks for unsaved files and asks the user if they should be saved
    bool saveFilesForClosing(const QList<LatexDocument *> &documentList); ///< checks for unsaved files and asks the user if they should be saved
	void closeAllFiles();
	bool canCloseNow(bool saveSettings = true); ///< asks the user and close all files, and prepares to exit txs
	void closeEvent(QCloseEvent *e);

	void updateUserMacros(bool updateMenu = true);

	void updateEmphasizedRegion(QDocumentCursor c, int sid);

	QSplashScreen *splashscreen;  ///< only used during startup
	QFormatScheme *m_formats, *m_formatsOldDefault;
	QLanguageFactory *m_languages;
	LatexCompleter *completer;
	LatexReference *latexReference;

	QPointer<UnicodeInsertion> unicodeInsertionDialog;

	//gui
	Editors *editors;
	QSplitter *sidePanelSplitter;
	QSplitter *mainHSplitter;
	QSplitter *centralVSplitter;
	QFrame *centralFrame;
	QToolBar *centralToolBar;
	CustomWidgetList *leftPanel;
	TitledPanel *sidePanel;
	SymbolListModel *symbolListModel;
	SymbolWidget *symbolWidget;
	QString hiddenLeftPanelWidgets;

    //StructureTreeView *structureTreeView;
    QTreeWidget *structureTreeWidget;
    QTreeWidget *topTOCTreeWidget;
	LatexParser latexParser;

    QVector<QIcon> iconSection;
public:
	LatexDocuments documents;

    Q_INVOKABLE bool completerIsVisible();
private:
	OutputViewWidget *outputView; ///< contains output widgets (over OutputLayout)

	//menu
	QActionGroup *bibtexEntryActions;
	QActionGroup *biblatexEntryActions;
	QActionGroup *bibTypeActions;
	QActionGroup *highlightLanguageActions;
	QActionGroup *actgroupRootDocMode;
	QAction *actRootDocAutomatic;
	QAction *actRootDocExplicit;
	QAction *actRootDocSetExplicit;

	//toolbars
	QAction *actSave, *actUndo, *actRedo;

	QLabel *statusLabelMode, *statusLabelProcess, *statusLabelLanguageTool;
	QToolButton *statusTbLanguage;
	QToolButton *statusTbEncoding;
	QActionGroup *spellLanguageActions;

	CursorHistory *cursorHistory;

	//settings
	ConfigManager configManager;
public:
	BuildManager buildManager;
private:
	QStringList struct_level;

	qreal pdfSplitterRel;

	SpellerManager spellerManager;
	SVN svn;
    GIT git;
    Help help;
	SafeThread grammarCheckThread;
	GrammarCheck *grammarCheck;
	Bookmarks *bookmarks;
	SessionList *recentSessionList;

	//dialogs
	TextAnalysisDialog *textAnalysisDlg;
	SpellerDialog *spellDlg;

	Q_INVOKABLE LatexEditorView *currentEditorView() const;
	Q_INVOKABLE QEditor *currentEditor() const;
	void configureNewEditorView(LatexEditorView *edit);
	void configureNewEditorViewEnd(LatexEditorView *edit, bool asMaster = false, bool hidden = false);
	LatexEditorView *getEditorViewFromFileName(const QString &fileName, bool checkTemporaryNames = false);
	LatexEditorView *getEditorViewFromHandle(const QDocumentLineHandle *dlh);

	QAction *fullscreenModeAction;

	int runningPDFCommands, runningPDFAsyncCommands;
	QEditor *previewEditorPending; bool previewIsAutoCompiling;

	void updateUserToolMenu();
	void linkToEditorSlot(QAction *act, const char *slot, const QList<QVariant> &args);

    bool parseStruct(StructureEntry* se, QVector<QTreeWidgetItem *> &rootVector, QSet<LatexDocument*> *visited=nullptr, QList<QTreeWidgetItem *> *todoList=nullptr, int currentColor=0);
    void parseStructLocally(StructureEntry* se, QVector<QTreeWidgetItem *> &rootVector, QList<QTreeWidgetItem *> *todoList=nullptr, QList<QTreeWidgetItem *> *labelList=nullptr, QList<QTreeWidgetItem *> *magicList=nullptr, QList<QTreeWidgetItem *> *biblioList=nullptr);
#ifndef QT_NO_DEBUG
    void checkForShortcutDuplicate();
#endif
private slots:
    void updateTOCs();

    void updateTOC();
    void updateCurrentPosInTOC(QTreeWidgetItem *root=nullptr,StructureEntry *old=nullptr,StructureEntry *selected=nullptr);
    void syncExpanded(QTreeWidgetItem *item);
    void syncCollapsed(QTreeWidgetItem *item);
    void editSectionCopy();
    void editSectionCut();
    void editSectionPasteAfter();
    void editSectionPasteBefore();
    void editIndentSection();
    void editUnIndentSection();
    void gotoLineFromAction();
    void openAllRelatedDocuments();
    void closeAllRelatedDocuments();
    void toggleMasterDocument();
    void closeDocument();
    void copyFileName();
    void copyFilePath();
    void showInGraphicalShell_();
    void toggleSingleDocMode();
    void expandSubitems();
    void collapseSubitems();
    StructureEntry *labelForStructureEntry(const StructureEntry *entry);

    void updateStructureLocally();
    void customMenuStructure(const QPoint &pos);
    void createLabelFromAction();

	void relayToEditorSlot();
	void relayToOwnSlot();
	void autoRunScripts();
	void runScripts(int trigger);
	void runScriptsInList(int trigger, const QList<Macro> &scripts);

protected slots:
	void fileNew(QString fileName = "");
	void fileNewFromTemplate();
	void fileMakeTemplate();
	void fileOpen();
	void fileRestoreSession(bool showProgress = true, bool warnMissing = true);
    void fileSave(const bool saveSilently = false,QEditor *editor=nullptr);
	void fileSaveAll();
    void fileSaveAllFromTimer();
	void fileSaveAll(bool alsoUnnamedFiles, bool alwaysCurrentFile);
	void fileSaveAs(const QString &fileName = "") { fileSaveAs(fileName, false); }
private slots:
	void fileSaveAs(const QString &fileName, const bool saveSilently);
	void fileNewInternal(QString fileName = "");
protected slots:
	void fileUtilCopyMove(bool move); ///< call dialog to copy/move files
	void fileUtilDelete(); ///< call dialog to remove file
	void fileUtilRevert(); ///< reload file from disc, undoing all changes in memory
	void fileUtilPermissions(); ///< call dialog to set file permissions
	void fileUtilCopyFileName(); ///< copy file name into clipboard
	void fileUtilCopyMasterFileName(); ///< copy file name of master file into clipboard
	void fileClose(); ///< close current editor
	void fileCloseAll(); ///< close all open editors
	void fileExit(); ///< exit application
	void fileExitWithError(); ///< exit application with error code, used for auto-tests
protected slots:
	void fileOpenRecent();
	void fileOpenAllRecent(); ///< open all files in recent file list
	void fileRecentList();
    void fileClearRecentList();
	void viewDocumentListHidden(); ///< show names of all hidden document (for debug)
	void fileDocumentOpenFromChoosen(const QString &doc, int duplicate, int lineNr, int column);
	void viewDocumentList();
	void viewDocumentOpenFromChoosen(const QString &doc, int duplicate, int lineNr, int column);
	void fileOpenFirstNonOpen();
	void fileOpenRecentProject();
	void fileLoadSession();
	void loadSession(const QString &fileName);
	void fileSaveSession();
private slots:
	void restoreSession(const Session &s, bool showProgress = true, bool warnMissing = true);
	Session getCurrentSession();
protected slots:
	void MarkCurrentFileAsRecent();
private slots:
	void fileCheckin(QString filename = "");
	void fileLockPdf(QString filename = "");
	void fileCheckinPdf(QString filename = "");
	void fileUpdate(QString filename = "");
	void fileUpdateCWD(QString filename = "");
	void checkinAfterSave(QString filename, int checkIn = 0);
	void checkin(QString fn, QString text = "txs auto checkin", bool blocking = false);
	bool svnadd(QString fn, int stage = 0);
	void svnUndo(bool redo = false);
	void svnPatch(QEditor *ed, QString diff);
	void showOldRevisions();
	void changeToRevision(QString rev, QString old_rev = "");
    void svnDialogClosed(int);
	void fileDiff();
	void fileDiff3();
	bool checkSVNConflicted(bool substituteContents = true);
	void removeDiffMarkers(bool theirs = false);
	void editChangeDiff(QPoint pt);
	void jumpNextDiff();
	void jumpPrevDiff();
	void fileDiffMerge();
	void declareConflictResolved();
protected slots:
    void openExternalFile(QString name, const QString &defaultExt = "tex", LatexDocument *doc = nullptr,bool relativeToCurrentDoc=false); // signaled by latexViewer to open specific file
    void openExternalFileFromAction();

	void editUndo(); ///< undo changes in text editor
	void editRedo(); ///< redo changes in text editor
	void editDebugUndoStack(); ///< print undo-stack content into a new text editor window
	void editCopy(); ///< copy text
	void editPaste(); ///< paste text
	void editPasteImage(QImage image);
	void editTextToLowercase();
	void editTextToUppercase();
	void editTextToTitlecase(bool smart = false);
	void editTextToTitlecaseSmart();
	void editFind(); ///< open search panel
	void editPasteLatex();
	void convertToLatex();
	void editHardLineBreak();
	void editHardLineBreakRepeat();
	void editDeleteLine(); ///< delete current line in current text editor
    void editCutLine(); ///< cut current line in current text editor
	void editDeleteToEndOfLine();
	void editDeleteFromStartOfLine();
	void editMoveLineUp();
	void editMoveLineDown();
	void editDuplicateLine();
	void editSortLines();
	void editAlignMirrors();
	void editEraseWordCmdEnv();
	void editGotoDefinition(QDocumentCursor c = QDocumentCursor());
	void editSpell();
	void editThesaurus(int line = -1, int col = -1);
	void editChangeLineEnding();
	void setPreviewMode();
	void setCheckedPreviewModeAction();
	void editSetupEncoding();
	void editInsertUnicode(); ///< open dialog to insert a unicode character
	void editInsertRefToNextLabel(const QString &refCmd = "\\ref", bool backward = false);
	void editInsertRefToPrevLabel(const QString &refCmd = "\\ref");
	void runSearch(SearchQuery *query);
	void findLabelUsages(LatexDocument *doc, const QString &labelText);
    void findLabelUsagesFromAction();
	SearchResultWidget *searchResultWidget();

	void findWordRepetions();
	void findNextWordRepetion();

	void addDocToLoad(QString filename);

	void LTErrorMessage(QString message);

    void paletteChanged(const QPalette &palette);

private slots:
	void readSettings(bool reread = false); ///< read configured/default settings from ini
	void saveSettings(const QString &configName = ""); ///< save all setting to ini
	void restoreDefaultSettings(); ///< restore default settings, removing all changed values

protected slots:
	void showMarkTooltipForLogMessage(QList<int> errors);
	void newDocumentLineEnding();
	void updateCaption();
	void updateMasterDocumentCaption();
	void updateUndoRedoStatus();
	void currentEditorChanged();
	void editorTabMoved(int from, int to);
	void editorAboutToChangeByTabClick(LatexEditorView *edFrom, LatexEditorView *edTo);

    void updateStructure(bool initial = false, LatexDocument *doc = nullptr, bool hidden = false);
	void structureContextMenuToggleMasterDocument(LatexDocument *document);

	void editRemovePlaceHolders();
	void editRemoveCurrentPlaceHolder();

	void normalCompletion(); ///< activate normal completion
	void insertEnvironmentCompletion(); ///< activate environment completion
	void insertTextCompletion(); ///< activate normal text completion
	void insertText(const QString &text);
	void insertTag(const QString &Entity, int dx = 0, int dy = 0);
	void insertCitation(const QString &text);
	void insertFormula(const QString &formula);
	void insertSymbol(const QString &text);
	void insertXmlTag(QListWidgetItem *item);
	void insertXmlTagFromToolButtonAction();
	void callToolButtonAction();
	void insertFromAction();
    void insertTextFromAction();
    void insertFromTagList(QListWidgetItem *item);
	void insertBib();
	void closeEnvironment();

	void insertBibEntryFromAction();
	void insertBibEntry(const QString &id = "");
	void setBibTypeFromAction();

	void insertUserTag();
	void execMacro(const Macro &m, const MacroExecContext &context = MacroExecContext(), bool allowWrite = false);
	void runScript(const QString &script, const MacroExecContext &context = MacroExecContext(), bool allowWrite = false);

	void editMacros(); ///< open edit macros dialog
	void macroDialogAccepted(); ///< macro dialog was closed with ok
	void macroDialogRejected(); ///< macro dialog was closed with cancel

	void insertRef(const QString &refCmd);
	void insertRef();
	void insertEqRef();
	void insertPageRef();

	void changeTextCodec();
	void updateAvailableLanguages();
	void updateLanguageToolStatus();
	void editorSpellerChanged(const QString &name);
	void changeEditorSpeller();
    void showMoreDictionaries();
	void insertSpellcheckMagicComment();
	void updateStatusBarEncoding();
	void addMagicRoot();
	void addMagicCoding();
    void addMagicBibliography();
    void addMagicProgram();

	void quickTabular(); ///< start quick tabular wizard
	void quickArray(); ///< start quick array wizard
	void quickTabbing(); ///< start quick tabbing wizard
	void quickLetter(); ///< start quick leter wizard
	void quickDocument(); ///< start quick document wizard
	void quickBeamer(); ///< start quick beamer wizard
	void quickGraphics(const QString &graphicsFile = QString()); ///< start quick graphics wizard
	void quickMath(); ///< start quick math wizard

	bool checkProgramPermission(const QString &program, const QString &cmdId, LatexDocument *master);
	void runInternalPdfViewer(const QFileInfo &master, const QString &options);
	void runBibliographyIfNecessary(const QFileInfo &cmd);
	QDateTime GetBblLastModified(void);

	void showExtendedSearch();

	void changeIconSize(int value);
	void changeSecondaryIconSize(int value);
    void changePDFIconSize(int value);
	void changeSymbolGridIconSize(int value, bool changePanel = true);

public slots:
	void connectSubCommand(ProcessX *p, bool showStdoutLocallyDefault);
private slots:
    void runInternalCommand(const QString &cmd, const QFileInfo &master, const QString &options);
	void commandLineRequested(const QString &cmdId, QString *result, bool *);
	void beginRunningCommand(const QString &commandMain, bool latex, bool pdf, bool async);
	void beginRunningSubCommand(ProcessX *p, const QString &commandMain, const QString &subCommand, const RunCommandFlags &flags);
	void endRunningSubCommand(ProcessX *p, const QString &commandMain, const QString &subCommand, const RunCommandFlags &flags);
	void endRunningCommand(const QString &commandMain, bool latex, bool pdf, bool async);


    bool runCommand(const QString &commandline, QString *buffer = nullptr, QTextCodec *codecForBuffer = nullptr, bool saveAll=true);
    bool runCommandNoSpecialChars(QString commandline, QString *buffer = nullptr, QTextCodec *codecForBuffer = nullptr);
	void setStatusMessageProcess(const QString &message);
    bool runCommandAsync(const QString &commandline, const char *returnCMD);
protected slots:
	void processNotification(const QString &message);
    void clearLogs();
	void openExternalTerminal(void); ///< open external terminal
	void cleanAll();
	void commandFromAction();  ///< calls a command given by sender.data, doesn't wait

	void webPublish();
	void webPublishSource();
	void convertToPlainText();
	void analyseText();
	void analyseTextFormDestroyed();
	void generateRandomText();

	bool loadLog();
	void onCompileError();
	void setLogMarksVisible(bool visible);
	void clearLogEntriesInEditors();
	void updateLogEntriesInEditors();
	void showLog(); ///< show log viewer in bottom panel
	void viewLog();
	void viewLogOrReRun(LatexCompileResult *result);
	bool gotoNearLogEntry(int lt, bool backward, QString notFoundMessage);
	bool hasLatexErrors();
	bool logExists();
	void clearMarkers();
	/////
	void latexHelp(); ///< open latex help document
	void userManualHelp(); ///< open txs user manual
	void texdocHelp();
	void helpAbout(); ///< open about dialog

	void generalOptions(); ///< open config dialog
	void setAutomaticRootDetection();
	void setExplicitRootDocument(LatexDocument *doc);
	void setCurrentDocAsExplicitRoot();

	void gotoNextDocument();
	void gotoPrevDocument();
	void gotoOpenDocument();
	void updateOpenDocumentMenu(bool localChange = false);
	void onEditorsReordered();

	void focusEditor();
	void focusViewer();
	void enlargeEmbeddedPDFViewer();
	void shrinkEmbeddedPDFViewer(bool preserveConfig = false);

	void showStatusbar();
	void viewCloseElement();
	void setFullScreenMode();
	void viewSetHighlighting(QAction *act);
	void showHighlightingMenu();

	void viewCollapseBlock();
	void viewExpandBlock();

#ifndef NO_POPPLER_PREVIEW
	QObject *newPdfPreviewer(bool embedded = false);
#endif
	void pdfClosed();

	void masterDocumentChanged(LatexDocument *doc);
	void aboutToDeleteDocument(LatexDocument *doc);

    void updateCompleter(LatexEditorView *edView = nullptr);
	void completerNeedsUpdate();
    void completerCommandsNeedsUpdate();
	void needUpdatedCompleter();

	void outputPageChanged(const QString &id);

    void gotoLine(int line, int col = 0, LatexEditorView *edView = nullptr, QEditor::MoveFlags mflags = QEditor::Navigation, bool setFocus = true); // line is 0 based
	bool gotoLine(int line, const QString &fileName);  // line is 0 based, absolute file name
	void gotoLine(LatexDocument *doc, int line, int col=0);
    void gotoLine(QTreeWidgetItem * item,int col);
	void gotoLogEntryEditorOnly(int logEntryNumber);
	QDocumentCursor getLogEntryContextCursor(const QDocumentLineHandle *dlh, const LatexLogEntry &entry);
	bool gotoLogEntryAt(int newLineNumber);
	bool gotoMark(bool backward, int id = -1);
	QList<int> findOccurencesApproximate(QString checkLine, const QString &guessedWord);
	void syncFromViewer(const QString &fileName, int lineNr, bool activate, const QString &guessedWord);  //0 based, absolute file name, raise window

	void goBack();
	void goForward();
	void setGlobalCursor(const QDocumentCursor &c);
	void saveCurrentCursorToHistory();
	void saveEditorCursorToHistory(LatexEditorView *edView);

	void previewLatex();
	void previewAvailable(const QString &imageFile, const PreviewSource &source);
	void clearPreview();
	void showPreview(const QString &text);
	void showPreview(const QDocumentCursor &c);
	void showPreview(const QDocumentCursor &c, bool addToList);
	QStringList makePreviewHeader(const LatexDocument *rootDoc);
	void showPreviewQueue();
	void showImgPreview(const QString &fname);
	void showImgPreviewFinished(const QPixmap &pm, int page);
	void recompileForPreview();
	void recompileForPreviewNow();

	void templateEdit(const QString &fname);

	void fileReloaded();
	void fileInConflictShowDiff();
	void fileAutoReloading(QString fname);

	void jumpToSearchResult(QDocument *doc, int lineNumber, const SearchQuery *query);

	void cursorPositionChanged();
	void syncPDFViewer(QDocumentCursor cur, bool inForeground = true);
	//	void treeWidgetChanged();

	bool generateMirror(bool setCur = false);
	void generateBracketInverterMirror();
	void jumpToBracket();
	void selectBracket();
	void findMissingBracket();
	void cursorHovered();
	void loadProfile();
	void saveProfile();

	void addRowCB();
	void addColumnCB();
	void removeColumnCB();
	void removeRowCB();
	void cutColumnCB();
	void pasteColumnCB();
	void addHLineCB();
	void remHLineCB();
	void insertTableTemplate();
	void alignTableCols();

	void updateTexQNFA();
	void updateTexLikeQNFA(QString languageName, QString filename);

	void toggleGrammar(int type);

	void openInternalDocViewer(QString package, const QString command = "");

private slots:
	void importPackage(QString name);
	void packageScanCompleted(QString name);
	void stopPackageParser();
	void packageParserFinished();
	void readinAllPackageNames();
    void packageListReadCompleted(std::set<QString> packages);
protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
	virtual void changeEvent(QEvent *e);

    bool eventFilter(QObject *obj, QEvent *event);

	bool mCompleterNeedsUpdate;
    bool mCompleterCommandsNeedsUpdate=false;
    CodeSnippetList mCompleterWords;

	int currentLine;
	QBrush oldBackground;
	bool mDontScrollToItem;

	QByteArray stateFullScreen;

	QDialog *svndlg;
	UserMenuDialog *userMacroDialog;
	QComboBox *cmbLog;

	QStringList m_columnCutBuffer;

	QTimer autosaveTimer,previewDelayTimer,previewFullCompileDelayTimer;

	QSet<int> previewQueue;
	LatexEditorView *previewQueueOwner;

	QString fileFilters;
	QString selectedFileFilter;

	QPointer<FileSelector> fileSelector;

	bool runBibliographyIfNecessaryEntered;

	LatexStyleParser *latexStyleParser;
	PackageScanner *packageListReader;

	QMap<QString, QString> detectedEnvironmentsForHighlighting;

	LatexDocument *diffLoadDocHidden(QString f);
	void showDiff3(const QString file1, const QString file2);

	void restoreBookmarks(LatexEditorView *edView);

	bool completerPreview;
    QPixmapCache previewCache;

	bool recheckLabels;

    bool rememberFollowFromScroll,enlargedViewer;

    std::set<QString> latexPackageList, currentPackageList;

	QMap<QString, QString> *mReplacementList;

    StructureEntry *currentSection;

public:
    Q_PROPERTY(QString clipboard READ clipboardText WRITE setClipboardText)
	Q_INVOKABLE QString clipboardText(const QClipboard::Mode &mode = QClipboard::Clipboard) const;
	Q_INVOKABLE void setClipboardText(const QString &text, const QClipboard::Mode &mode = QClipboard::Clipboard);
	Q_INVOKABLE int getVersion() const; ///< return current version number of txs (coded in hex,32 bit)
	Q_INVOKABLE void simulateKeyPress(const QString &shortcut);

	static void recoverFromCrash();

public slots:
	void threadCrashed();
	void iamalive();
	void checkLatexInstall();
	void checkCWLs();
    void checkLanguageTool();

	void slowOperationStarted();
	void slowOperationEnded();

	void openBugsAndFeatures();

signals:
	void infoNewFile(); ///< signal that a new file has been generated. Used for scritps as trigger.
	void infoNewFromTemplate(); ///< signal that a new file from template has been generated. Used for scritps as trigger.
	void infoLoadFile(const QString &filename); ///< signal that a file has been loaded. Used for scritps as trigger.
	void infoFileSaved(const QString &filename,const int checkin = 0); ///< signal that a file has been saved. Used for scritps as trigger.
	void infoFileClosed(); ///< signal that a file has been closed. Used for scritps as trigger.
	void infoAfterTypeset(); ///< signal that a file has been compiled. Used for scritps as trigger.
	void imgPreview(const QString &fn);
};

//Q_DECLARE_METATYPE(Texstudio *)

#endif

