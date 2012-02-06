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

#ifndef TEXMAKER_H
#define TEXMAKER_H

#include "mostQtHeaders.h"

#include "bibtexparser.h"
#include "buildmanager.h"
#include "codesnippet.h"
#include "configmanager.h"
#include "latexlog.h"
#include "latexdocument.h"
#include "latexeditorview.h"
#include "latexcompleter.h"
#include "templateselector.h"
//#include "symbollistwidget.h"
#include "symbolgridwidget.h"
#include "xmltagslistwidget.h"
#include "spellerdialog.h"
#include "textanalysis.h"
#include "toolwidgets.h"
#include "tmxtabwidget.h"
#include "unicodeinsertion.h"
#include "tablemanipulation.h"
#include "PDFDocument.h"

#include "qformatfactory.h"
#include "qlanguagefactory.h"
#include "qlinemarksinfocenter.h"
#include "latexstyleparser.h"
#include "diffoperations.h"

typedef QHash<QString,int> SymbolList;

enum SVNSTATUS {
	Unknown=0,
	Unmanaged,
	Modified,
	Locked,
	CheckedIn,
	InConflict
};

enum RunCommandFlag{
	RCF_SHOW_STDOUT = 1,//low priority, overriden by configmanager always, both overriden by /dev/null redirection
	RCF_WAIT_FOR_FINISHED = 2,
	RCF_VIEW_LOG = 4, //show the log (only use if the command changes the log i.e. is latex), also enable reruns
	RCF_SINGLE_INSTANCE = 8, //single viewer only
	RCF_CHANGE_PDF = 16,
	RCF_NO_DOCUMENT = 32, // don't check if document is saved as it is not used
	RCF_IS_RERUN_CALL = 64 // call is an automatically rerun (internal)
};
Q_DECLARE_FLAGS(RunCommandFlags, RunCommandFlag);





class UserMenuDialog;
class Texmaker : public QMainWindow {
	Q_OBJECT
	
public:
	Texmaker(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Texmaker();
	
	Q_INVOKABLE QString getCurrentFileName(); //returns the absolute file name of the current file or "" if none is opene
	Q_INVOKABLE QString getAbsoluteFilePath(const QString & relName, const QString &extension=""); //treats the path relative to the compiled .tex file
	QByteArray windowstate;
	bool tobemaximized,tobefullscreen;
	
public slots:
	LatexEditorView* load(const QString &f , bool asProject = false);
	void executeCommandLine(const QStringList& args, bool realCmdLine);
	void onOtherInstanceMessage(const QString &);  // For messages for the single instance
	
private:
	//these are just wrappers around configManager so we don't have to type so much (todo??? move them to configmanager.h and use a singleton design???)
	inline QMenu* newManagedMenu(const QString &id,const QString &text);
	inline QMenu* newManagedMenu(QMenu* menu, const QString &id,const QString &text);
	inline QAction* newManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName=0, const QKeySequence &shortCut=0, const QString & iconFile="", const QList<QVariant>& args = QList<QVariant>());
	inline QAction* newManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QList<QKeySequence> &shortCuts, const QString & iconFile="", const QList<QVariant>& args = QList<QVariant>());
	inline QAction* newManagedEditorAction(QWidget* menu, const QString &id,const QString &text, const char* slotName=0, const QKeySequence &shortCut=0, const QString & iconFile="", const QList<QVariant>& args = QList<QVariant>());
	inline QAction* newManagedEditorAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QList<QKeySequence> &shortCuts, const QString & iconFile="", const QList<QVariant>& args = QList<QVariant>());
	inline QAction* newManagedAction(QWidget* menu, const QString &id, QAction* act);
	inline QAction* getManagedAction(QString id);
	QAction* insertManagedAction(QAction* before, const QString &id,const QString &text, const char* slotName=0, const QKeySequence &shortCut=0, const QString & iconFile="");
	
	SymbolGridWidget* addSymbolGrid(const QString& SymbolList,  const QString& iconName, const QString& text);
	void addTagList(const QString& id, const QString& iconName, const QString& text, const QString& tagFile);
	
	QVariantMap *MapForSymbols;
	
private slots:
	void updateToolBarMenu(const QString& menuName);
private:
	void setupMenus();
	void setupDockWidgets();
	void setupToolBars();
	void createStatusBar();
	bool FileAlreadyOpen(QString f, bool checkTemporaryNames = false);
	bool closeAllFilesAsking(); //asks the user and close all files
	bool canCloseNow(); //asks the user and close all files, and prepares to exit txs
	void closeEvent(QCloseEvent *e);
	
	QFormatFactory *m_formats;
	QLanguageFactory* m_languages;
	LatexCompleter* completer;
	
	QPointer<UnicodeInsertion> unicodeInsertionDialog;
	
	//gui
	TmxTabWidget *EditorView;
	QToolBar* centralToolBar;
	CustomWidgetList *leftPanel;
	SymbolGridWidget *MostUsedSymbolWidget, *FavoriteSymbolWidget;
	QString hiddenLeftPanelWidgets;
	
	QTreeView *structureTreeView;
    QListWidget *bookmarksWidget;
	LatexParser latexParser;
	LatexDocuments documents;
	
	OutputViewWidget *outputView; //contains output widgets (over OutputLayout)
	
	//toolbars
	//
	QAction *ToggleAct, *ToggleRememberAct;
	QAction *actSave, *actUndo, *actRedo;
	
	QLabel *statusLabelMode, *statusLabelProcess, *statusLabelEncoding;
	QToolButton *statusTbLanguage;
	QActionGroup *spellLanguageActions;
	
	QToolButton *combo1,*combo2,*combo;
	
	//settings
	ConfigManager configManager;
	BuildManager buildManager;
	int split1_right, split1_left, split2_top, split2_bottom;
	QString spell_ignored_words;
	QStringList struct_level;
	QStringList labelitem;
	
	QStringList userTemplatesList;
	
	SpellerManager spellerManager;
	
	//dialogs
	TextAnalysisDialog *textAnalysisDlg;
	SpellerDialog *spellDlg;
	templateselector *templateSelectorDialog;
	
	//tools
	bool FINPROCESS, ERRPROCESS, KILLPROCESS, PROCESSRUNNING;
	
	SymbolList symbolScore;
	usercodelist symbolMostused;
	QStringList symbolFavorites;
	
	Q_INVOKABLE LatexEditorView *currentEditorView() const;
	Q_INVOKABLE QEditor* currentEditor() const;
	void configureNewEditorView(LatexEditorView *edit);
	void configureNewEditorViewEnd(LatexEditorView *edit,bool asMaster=false);
	LatexEditorView* getEditorViewFromFileName(const QString &fileName, bool checkTemporaryNames = false);
	
	QAction* outputViewAction, *fullscreenModeAction;
	
	void linkToEditorSlot(QAction* act, const char* slot, const QList<QVariant>& args);
private slots:
	void relayToEditorSlot();
	void relayToOwnSlot();
	
protected slots:
	void fileNew(QString fileName="");
	void fileNewFromTemplate();
	void fileMakeTemplate();
	void fileOpen();
	void fileRestoreSession();
	void fileSave();
	void fileSaveAll();
	void fileSaveAll(bool alsoUnnamedFiles, bool alwaysCurrentFile);
private slots:
	void fileSaveAs(const QString& fileName = "");
protected slots:	
	void fileClose();
	void fileCloseAll();
	void fileExit();
	void fileOpenRecent();
	void fileOpenAllRecent();
	void fileOpenFirstNonOpen();
	void fileOpenRecentProject();
	void MarkCurrentFileAsRecent();
private slots:
	void fileCheckin(QString filename="");
	void fileLockPdf(QString filename="");
	void fileCheckinPdf(QString filename="");
	void fileUpdate(QString filename="");
	void fileUpdateCWD(QString filename="");
	void checkin(QString fn,QString text="txs auto checkin",bool blocking=false);
	bool svnadd(QString fn,int stage=0);
	void svncreateRep(QString fn);
	void svnUndo(bool redo=false);
	void svnPatch(QEditor *ed,QString diff);
	void svnLock(QString fn);
	SVNSTATUS svnStatus(QString filename);
	void showOldRevisions();
	QStringList svnLog();
	void changeToRevision(QString rev,QString old_rev="");
	void svnDialogClosed();
	void fileDiff();
	void fileDiff3();
	bool checkSVNConflicted(bool substituteContents=true);
	void removeDiffMarkers(bool theirs=false);
	void editChangeDiff(QPoint pt);
	void jumpNextDiff();
	void jumpPrevDiff();
	void fileDiffMerge();
	void declareConflictResolved();
protected slots:	
	void openExternalFile(const QString& name,const QString& defaultExt="tex",LatexDocument *doc=0); // signaled by latexViewer to open specific file
	
	void editUndo();
	void editRedo();
	void editDebugUndoStack();
	void editCopy();
	void editPaste();
	void editSectionCopy();
	void editSectionCopy(int startingLine, int endLine);
	void editSectionCut();
	void editSectionCut(int startingLine, int endLine);
	void editSectionPasteAfter();
	void editSectionPasteAfter(int line);
	void editSectionPasteBefore();
	void editSectionPasteBefore(int line);
	void editPasteLatex();
	void convertToLatex();
	void editPasteRef();
	void editIndentSection();
	void editUnIndentSection();
	void editHardLineBreak();
	void editHardLineBreakRepeat();
	void editEraseLine();
	void editEraseWordCmdEnv();
	void editGotoDefinition();
	void editSpell();
	void editThesaurus(int line=-1,int col=-1);
	void editChangeLineEnding();
	void editSetupEncoding();
	void editInsertUnicode();
	void editInsertRefToNextLabel(bool backward=false);
	void editInsertRefToPrevLabel();
	void editFindGlobal();
	
	void findWordRepetions();
	void findNextWordRepetion();
	
	void StructureContextMenu(const QPoint& point);
	void structureContextMenuCloseDocument();
	void structureContextMenuSwitchMasterDocument();
	void SymbolGridContextMenu(QWidget* widget, const QPoint& point);
	void MostUsedSymbolsTriggered(bool direct=false);
	void symbolAddFavorite();
	void symbolRemoveFavorite();
	void symbolRemoveAllFavorites();
	
private slots:	
	void ReadSettings();
	void SaveSettings(const QString& configName="");
	
protected slots:	
	void showMarkTooltipForLogMessage(int error);
	void NewDocumentStatus();
	void NewDocumentLineEnding();
	void UpdateCaption();
	void updateMasterDocumentCaption();
	void updateUndoRedoStatus();
	void editorTabChanged(int index);
	void CloseEditorTab(int tab);
	void EditorTabMoved(int from,int to);
	
	void updateStructure(bool initial=false);
	void ShowStructure();
	void clickedOnStructureEntry(const QModelIndex & index);
    void clickedOnBookmark(QListWidgetItem *item);
	void editRemovePlaceHolders();
    void toggleBookmark();
    void moveBookmarkUp();
    void moveBookmarkDown();
    void removeBookmark();
    void removeAllBookmarks();
    void lineWithBookmarkRemoved(int lineNr);
    void updateBookmarks(LatexEditorView *edView);
	
	void NormalCompletion();
	void InsertEnvironmentCompletion();
	void InsertTextCompletion();
	void InsertTag(QString Entity, int dx, int dy);
	void InsertSymbol(QTableWidgetItem *item);
	void InsertSymbolPressed(QTableWidgetItem *item);
	void InsertXmlTag(QListWidgetItem *item);	
	void insertXmlTagFromToolButtonAction();
	void callToolButtonAction();
	void InsertFromAction();
	void InsertBib();
	void InsertStruct();
	
	void InsertBibEntryFromAction();
	void InsertBibEntry(const QString& id="");
	
	void insertUserTag(const QString& macro);
	void insertUserTag();
	void EditUserMenu();
	void userMacroDialogAccepted();
	
	void InsertRef();
	void InsertPageRef();
	
	void UpdateAvailableLanguages();
	void EditorSpellerChanged(const QString &name);
	void ChangeEditorSpeller();
	void InsertSpellcheckMagicComment();
	
	void QuickTabular();
	void QuickArray();
	void QuickTabbing();
	void QuickLetter();
	void QuickDocument();
	void QuickGraphics(const QString &graphicsFile = QString());
	
private slots:	
	void runCommand(BuildManager::LatexCommand cmd, RunCommandFlags flags);
	void runCommand(const QString& commandline, RunCommandFlags flags = 0, QString *buffer = 0); //default flags == 0 is necessary for pdf viewer
	void RunPreCompileCommand();
	void readFromStderr();
	void readFromStdoutput();
	void SlotEndProcess(int err);
	void runCommandList(const QStringList& commandList, const RunCommandFlags& additionalFlags);
protected slots:	
	void processNotification(const QString& message);
	void QuickBuild();
	void CleanAll();
	void commandFromAction();  //calls a command given by sender.data, doesn't wait
	void UserTool();
	void EditUserTool();
	
	void WebPublish();
	void WebPublishSource();
	void AnalyseText();
	void AnalyseTextFormDestroyed();
	void GenerateRandomText();
	
	void RealViewLog(bool noTabChange=false);
	void ViewLog(bool noTabChange=false);
	void ViewLogOrReRun();
	void DisplayLatexError();
	bool gotoNearLogEntry(int lt, bool backward, QString notFoundMessage);
	bool NoLatexErrors();
	bool LogExists();
	void ClearMarkers();
	/////
	void LatexHelp();
	void UserManualHelp();
	void HelpAbout();
	
	void GeneralOptions();
	void ToggleMode();
	
	void gotoNextDocument();
	void gotoPrevDocument();
	void gotoOpenDocument();
	void updateOpenDocumentMenu(bool localChange=false);
	
	void viewToggleOutputView();
	void viewCloseSomething();
	void setFullScreenMode();
	void viewSetHighlighting();
	
	void viewCollapseBlock();
	void viewExpandBlock();
	
	void newPdfPreviewer();
	
	void masterDocumentChanged(LatexDocument * doc);
	
	void SetMostUsedSymbols(QTableWidgetItem* item);
	
	void updateCompleter();
	void completerNeedsUpdate();
	void needUpdatedCompleter();
	
	void tabChanged(int i);
	
	void gotoLine(int line);  //0 based
	void gotoLocation(int line, const QString &fileName);  //0 based, absolute file name
	void gotoLogEntryEditorOnly(int logEntryNumber);
	bool gotoLogEntryAt(int newLineNumber);
	bool gotoMark(bool backward, int id=-1);
	void syncFromViewer(const QString &fileName, int line, bool activate, const QString& guessedWord);  //0 based, absolute file name, raise window
	
	void previewLatex();
	void previewAvailable(const QString& imageFile, const QString& text, int line);
	void clearPreview();
	void showPreview(const QString& text);
	void showPreview(const QDocumentCursor& c);
	void showPreview(const QDocumentCursor& c, bool addToList);
	void showPreviewQueue();
	
	void templateRemove();
	void templateEdit();
	
	void fileReloaded();
	void fileInConflict();
	void fileAutoReloading(QString fname);
	
	void jumpToSearch(QString filename,int lineNumber);
	
	void cursorPositionChanged();
	//	void treeWidgetChanged();
	
	bool generateMirror(bool setCur=false);
	void generateBracketInverterMirror();
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
	
	void latexModelViewMode();
	void moveDocumentToFront();
	void moveDocumentToEnd();
	void moveDocumentToDest(int dest);
	
	void updateHighlighting();
	
private slots:
	void importPackage(QString name);
	void packageScanCompleted(QString name);
	void stopPackageParser();
	void packageParserFinished();
protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
	virtual void changeEvent(QEvent *e);
	
	Qt::MouseButtons mb;
	
	bool mCompleterNeedsUpdate;
	
	bool previewEquation;
	int currentLine;
	QBrush oldBackground;
	bool mDontScrollToItem;
	
	QByteArray stateFullScreen;
	
	QDialog *svndlg;
	UserMenuDialog *userMacroDialog;
	QComboBox *cmbLog;
	
	QStringList m_columnCutBuffer;
	
	QTimer autosaveTimer;
	
	bool completionBaseCommandsUpdated;
	
	QSet<int> previewQueue;
	LatexEditorView* previewQueueOwner;
	
	QString fileFilters;
	QString selectedFileFilter;
	
	
	LatexStyleParser *latexStyleParser;
	
	int remainingReRunCount;
	bool lastReRunWasBibTeX;
	QString rerunCommand;
	RunCommandFlags rerunFlags;
	
	QMap<QString,QString> detectedEnvironmentsForHighlighting;
	
	LatexDocument* diffLoadDocHidden(QString f);
	void showDiff3(const QString file1,const QString file2);

    void restoreBookmarks(LatexEditorView *edView);
	
	
	
public:
	Q_PROPERTY(QString clipboard READ clipboardText WRITE setClipboardText);
	Q_INVOKABLE QString clipboardText(const QClipboard::Mode& mode = QClipboard::Clipboard) const;
	Q_INVOKABLE void setClipboardText(const QString& text, const QClipboard::Mode& mode = QClipboard::Clipboard);
	Q_INVOKABLE int getVersion() const;
};

Q_DECLARE_METATYPE(Texmaker*)

#endif
