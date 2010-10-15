/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                         2008-2009 by Benito van der Zander              *
 *   http://texmakerx.sourceforge.net
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
#include "scriptengine.h"
#include "tmxtabwidget.h"
#include "tablemanipulation.h"
#include "PDFDocument.h"

#include "qformatfactory.h"
#include "qlanguagefactory.h"
#include "qlinemarksinfocenter.h"

typedef QHash<QString,int> SymbolList;


class Texmaker : public QMainWindow {
	Q_OBJECT

public:
	Texmaker(QWidget *parent = 0, Qt::WFlags flags = 0);

	QString getCurrentFileName(); //returns the absolute file name of the current file or "" if none is opene
	QString getAbsoluteFilePath(const QString & relName, const QString &extension=""); //treats the path relative to the compiled .tex file
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
	inline QAction* newManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName=0, const QKeySequence &shortCut=0, const QString & iconFile="");
	inline QAction* newManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QList<QKeySequence> &shortCuts, const QString & iconFile="");
	inline QAction* newManagedAction(QWidget* menu, const QString &id, QAction* act);
	inline QAction* getManagedAction(QString id);
	
	SymbolGridWidget* addSymbolGrid(const QString& SymbolList,  const QString& iconName, const QString& text);
	void addTagList(const QString& id, const QString& iconName, const QString& text, const QString& tagFile);

	QVariantMap *MapForSymbols;

	void setupDockWidgets();
	void setupMenus();
	void setupToolBars();
	void createStatusBar();
	bool FileAlreadyOpen(QString f, bool checkTemporaryNames = false);
	bool closeAllFilesAsking(); //asks the user and close all files
	bool canCloseNow(); //asks the user and close all files, and prepares to exit tmx
	void closeEvent(QCloseEvent *e);
	
	QFormatFactory *m_formats;
	QLanguageFactory* m_languages;
	LatexCompleter* completer;

//gui
	TmxTabWidget *EditorView;
	QToolBar* centralToolBar;
	CustomWidgetList *leftPanel;
	SymbolGridWidget *MostUsedSymbolWidget, *FavoriteSymbolWidget;
	QString hiddenLeftPanelWidgets;
	
	QTreeView *structureTreeView;
	LatexDocuments documents;

	OutputViewWidget *outputView; //contains output widgets (over OutputLayout)
	
	QPointer<PDFDocument> pdfviewerWindow;
//toolbars
//
	QToolBar *spellToolBar;
	QAction *ToggleAct, *ToggleRememberAct;

	QLabel *stat1, *stat2, *stat3;
	
	QToolButton *combo1,*combo2,*combo3,*comboSpell;

//settings
	ConfigManager configManager;
	BuildManager buildManager;
	int split1_right, split1_left, split2_top, split2_bottom;
	QString spell_ignored_words;
	QStringList struct_level;
	QStringList labelitem;
	QStringList UserMenuName, UserMenuTag, UserMenuAbbrev;
	QStringList UserToolName, UserToolCommand;

	QStringList userTemplatesList;

	int spellcheckErrorFormat;
	SpellerUtility *mainSpeller;

//dialogs
	TextAnalysisDialog *textAnalysisDlg;
	SpellerDialog *spellDlg;
	templateselector *templateSelectorDialog;

//tools
	bool FINPROCESS, ERRPROCESS, KILLPROCESS, PROCESSRUNNING;

	SymbolList symbolScore;
	usercodelist symbolMostused;
	QStringList symbolFavorites;
	
	LatexEditorView *currentEditorView() const;
	QEditor* currentEditor() const;
	void configureNewEditorView(LatexEditorView *edit);
	void configureNewEditorViewEnd(LatexEditorView *edit);
	LatexEditorView* getEditorViewFromFileName(const QString &fileName, bool checkTemporaryNames = false);
	
	QAction* outputViewAction, *fullscreenModeAction;
private slots:

	void fileNew(QString fileName="");
	void fileNewFromTemplate();
	void fileMakeTemplate();
	void fileOpen();
	void fileRestoreSession();
	void fileSave();
	void fileSaveAll();
	void fileSaveAll(bool alsoUnnamedFiles, bool alwaysCurrentFile);
	void fileSaveAs(QString fileName = "");
	void fileClose();
	void fileCloseAll();
	void fileExit();
	void fileOpenRecent();
	void fileOpenAllRecent();
	void fileOpenRecentProject();
	void MarkCurrentFileAsRecent();
	void filePrint();
	void fileCheckin(QString filename="");
	void checkin(QString fn,QString text="tmx auto checkin",bool blocking=false);
	bool svnadd(QString fn,int stage=0);
	void svncreateRep(QString fn);
	void svnUndo(bool redo=false);
	void svnPatch(QEditor *ed,QString diff);
	void showOldRevisions();
	QStringList svnLog();
	void changeToRevision(QString rev,QString old_rev="");
	void svnDialogClosed();
        void openExternalFile(const QString name); // signaled by latexViewer to open specific file


	void editUndo();
	void editRedo();
	void editCut();
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
	void editSelectAll();
	void editEraseLine();
	void editEraseWordCmdEnv();
	void editFind();
	void editFindNext();
	void editReplace();
	void editGotoLine();
	void editJumpToLastChange();
	void editJumpToLastChangeForward();
	void editGotoDefinition();
	void editComment();
	void editUncomment();
	void editIndent();
	void editUnindent();
	void editSpell();
	void editThesaurus();
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

	void ReadSettings();
	void SaveSettings();

	void showMarkTooltipForLogMessage(int error);
	void NewDocumentStatus(bool m);
	void UpdateCaption();
	void CloseEditorTab(int tab);
        void EditorTabMoved(int from,int to);

	void updateStructure();
	void ShowStructure();
	void clickedOnStructureEntry(const QModelIndex & index);
	void editRemovePlaceHolders();
	
	void NormalCompletion();
	void InsertEnvironmentCompletion();
	void InsertTextCompletion();
	void InsertTag(QString Entity, int dx, int dy);
	void InsertSymbol(QTableWidgetItem *item);
	void InsertSymbolPressed(QTableWidgetItem *item);
	void InsertXmlTag(QListWidgetItem *item);	
	void insertXmlTagFromToolButtonAction();
	void insertFromActionFromToolButtonAction();
	void InsertFromAction();
	void InsertBib();
	void InsertStruct();

	void InsertBibEntryFromAction();
	void CleanBib();
	void InsertBibEntry();
	void InsertBibEntry(const QString& id);
	
	void InsertUserTag();
	void EditUserMenu();

	void InsertRef();
	void InsertPageRef();

	void SpellingLanguageChanged();

	void QuickTabular();
	void QuickArray();
	void QuickTabbing();
	void QuickLetter();
	void QuickDocument();
	void QuickGraphics();

	void runCommand(BuildManager::LatexCommand cmd,bool waitendprocess,bool showStdout);
	void runCommand(QString comd,bool waitendprocess,bool showStdout, bool compileLatex=false, QString *buffer=0, bool singleInstance = false);
	void RunPreCompileCommand();
	void readFromStderr();
	void readFromStdoutput();
	void SlotEndProcess(int err);
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
	void ViewAndHighlightError();
	void DisplayLatexError();
	void NextMark();
	void PreviousMark();
	bool gotoNearLogEntry(LogType lt, bool backward, QString notFoundMessage);
	bool NextError();
	bool PreviousError();
	void NextWarning();
	void PreviousWarning();
	void NextBadBox();
	void PreviousBadBox();
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
	
	
	void viewToggleOutputView();
	void viewCloseSomething();
	void setFullScreenMode();
	
	void viewCollapseEverything();
	void viewCollapseLevel();
	void viewCollapseBlock();
	void viewExpandEverything();
	void viewExpandLevel();
	void viewExpandBlock();

        void masterDocumentChanged(LatexDocument * doc);

	void gotoBookmark();
	void toggleBookmark();

	void SetMostUsedSymbols(QTableWidgetItem* item);

	void updateCompleter();
	void completerNeedsUpdate();

	void tabChanged(int i);

	void gotoLine(int line);  //0 based
	void gotoLocation(int line, const QString &fileName);  //0 based, absolute file name
	void gotoLogEntryEditorOnly(int logEntryNumber);
	bool gotoLogEntryAt(int newLineNumber);
	bool gotoMark(bool backward, int id);
	void syncFromViewer(const QString &fileName, int line, bool activate);  //0 based, absolute file name, raise window
	
	void previewLatex();
	void previewAvailable(const QString& imageFile, const QString& text);
	void showPreview(const QString text);

	void templateRemove();
	void templateEdit();

	void fileReloaded();
	void fileAutoReloading(QString fname);

	void jumpToSearch(QString filename,int lineNumber);

	void cursorPositionChanged();
//	void treeWidgetChanged();

	bool generateMirror(bool setCur=false);
	void cursorHovered();
	void loadProfile();

	void addRowCB();
	void addColumnCB();
	void removeColumnCB();
	void removeRowCB();
	void cutColumnCB();
	void pasteColumnCB();
	void addHLineCB();
	void remHLineCB();


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
	QComboBox *cmbLog;

	QStringList m_columnCutBuffer;

        QTimer autosaveTimer;
};



#endif
