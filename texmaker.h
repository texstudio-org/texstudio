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


#include "buildmanager.h"
#include "codesnippet.h"
#include "configmanager.h"
#include "latexlog.h"
#include "latexeditorview.h"
#include "latexcompleter.h"
#include "templateselector.h"
//#include "symbollistwidget.h"
#include "symbolgridwidget.h"
#include "xmltagslistwidget.h"
#include "spellerdialog.h"
#include "textanalysis.h"
#include "toolwidgets.h"
#include "thesaurusdialog.h"


#include "qformatfactory.h"
#include "qlanguagefactory.h"
#include "qlinemarksinfocenter.h"

typedef  QStringList Userlist;
typedef  QString UserCd[5];
typedef QHash<QString,int> SymbolList;

struct BibTeXFileInfo{
	QDateTime lastModified;
	QStringList ids;
	QString linksTo;
};

class Texmaker : public QMainWindow {
	Q_OBJECT

public:
	Texmaker(QWidget *parent = 0, Qt::WFlags flags = 0);

	QString getCurrentFileName(); //returns the absolute file name of the current file or "" if none is opened
	QString getCompileFileName(); //returns the absolute file name of the file to be compiled (master or current)  
	QString getCompilePath(); //returns the absolute file path of the file to be compiled (master or current) 
	QString getPreferredPath(); //returns getCompilePath() if not empty or QDir::homePath (for dialogs)
	QString getAbsoluteFilePath(const QString & relName, const QString &extension=""); //treats the path relative to the compiled .tex file
	QString getRelativeBaseName(const QString & file);//get completebasename with path relative to the compiled file for a given file 
	QByteArray windowstate;
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
	bool FileAlreadyOpen(QString f);
	bool canCloseNow(); //asks the user and close all files
	void closeEvent(QCloseEvent *e);

	QMap<QString, BibTeXFileInfo> bibTeXFiles; //bibtex files loaded by tmx
	QStringList mentionedBibTeXFiles; //bibtex files imported in the tex file (absolute after updateBibFiles)
	QSet<QString> allBibTeXIds;
	
	QFormatFactory *m_formats;
	QLanguageFactory* m_languages;
	LatexCompleter* completer;

//gui
	QTabWidget *EditorView;
	CustomWidgetList* leftPanel;
	
	//XmlTagsListWidget *MpListWidget, *PsListWidget, *leftrightWidget, *tikzWidget, *asyWidget;
	//SymbolListWidget *RelationListWidget, *ArrowListWidget, *MiscellaneousListWidget, *DelimitersListWidget, *GreekListWidget ;
	//SymbolGridWidget *RelationGridWidget,*ArrowGridWidget,*GreekGridWidget,*CyrillicGridWidget,*MiscellaneousMathGridWidget,*MiscellaneousTextGridWidget,*MiscellaneousWasyGridWidget,*DelimitersGridWidget,*SpecialGridWidget,*OperatorGridWidget;
	SymbolGridWidget* MostUsedListWidget;
	qlonglong SymbolListVisible;

	QTreeWidget *StructureTreeWidget;

	OutputViewWidget *outputView; //contains output widgets (over OutputLayout)
	

//toolbars
//
	QToolBar *fileToolBar, *editToolBar, *runToolBar, *formatToolBar, *mathToolBar;
	QAction *ToggleAct, *ToggleRememberAct;

	QLabel *stat1, *stat2, *stat3;
	QString MasterName,persistentMasterFile;
	
	QToolButton *combo1,*combo2,*combo3,*combo4,*combo5;

//settings
	ConfigManager configManager;
	BuildManager buildManager;
	int split1_right, split1_left, split2_top, split2_bottom;
	bool singlemode,  showoutputview, showstructview, ams_packages, makeidx_package;
	QString document_class, typeface_size, paper_size, document_encoding, author;
	QString spell_dic, spell_ignored_words;
	QStringList struct_level;
	QString thesaurus_database;
	QStringList userClassList, userPaperList, userEncodingList, userOptionsList;
	QStringList labelitem;
        Userlist UserMenuName, UserMenuTag, UserMenuAbbrev;
	UserCd UserToolName, UserToolCommand;

	QStringList userCommandList;
	QStringList userTemplatesList;

	int spellcheckErrorFormat;
	SpellerUtility *mainSpeller;

//dialogs
	ThesaurusDialog *thesaurusDialog;
	TextAnalysisDialog *textAnalysisDlg;
	SpellerDialog *spellDlg;
	templateselector *templateSelectorDialog;



//tools
	bool FINPROCESS, ERRPROCESS;

	SymbolList symbolScore;
	usercodelist symbolMostused;

	LatexEditorView *currentEditorView() const;
	QEditor* currentEditor() const;
	void configureNewEditorView(LatexEditorView *edit);
	LatexEditorView* getEditorViewFromFileName(const QString &fileName);
	
	QAction* outputViewAction;
private slots:

	void fileNew(QString fileName="untitled");
	void fileNewFromTemplate();
	void fileMakeTemplate();
	void fileOpen();
	void fileSave();
	void fileSaveAll();
	void fileSaveAs(QString fileName = "");
	void fileClose();
	void fileCloseAll();
	void fileExit();
	void fileOpenRecent();
	void fileOpenRecentProject();
	void MarkCurrentFileAsRecent();
	void filePrint();

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
	void editSelectAll();
	void editEraseLine();
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
	void editInsertRefToNextLabel(bool backward=false);
	void editInsertRefToPrevLabel();

	void StructureContextMenu(QPoint point);
	void StructureToolBoxContextMenu(QPoint point);
	void MostUsedSymbolsTriggered(bool direct=false);

	void ReadSettings();
	void SaveSettings();

	void showMarkTooltipForLogMessage(int error);
	void NewDocumentStatus(bool m);
	void UpdateCaption();
	void CloseEditorTab(int tab);

	void updateStructure();
	void updateStructureForFile(const QString& fileName);
	void ShowStructure();
	void ClickedOnStructure(QTreeWidgetItem *item,int);

	void NormalCompletion();
	void InsertEnvironmentCompletion();
	void InsertTextCompletion();
	void InsertTag(QString Entity, int dx, int dy);
	void InsertSymbol(QTableWidgetItem *item);
	void InsertSymbolPressed(QTableWidgetItem *item);
	void InsertXmlTag(QListWidgetItem *item);	
	void InsertFromAction();
	void InsertWithSelectionFromString(const QString& text);
	void InsertFromString(const QString& text);
	void InsertBib();
	void InsertStruct();
	void InsertStructFromString(const QString& text);
	void InsertImage();
	void InsertInclude();
	void InsertInput();

	void InsertBibEntryFromAction();
	void CleanBib();
	void InsertBibEntry();
	void InsertBibEntry(const QString& id);
	
	void InsertUserTag();
	void EditUserMenu();

	void SectionCommand();
	void OtherCommand();
	void InsertRef();
	void InsertPageRef();
	void SizeCommand();
	void LeftDelimiter();
	void RightDelimiter();

	void QuickTabular();
	void QuickArray();
	void QuickTabbing();
	void QuickLetter();
	void QuickDocument();

	void runCommand(BuildManager::LatexCommand cmd,bool waitendprocess,bool showStdout,QString fn="");
	void runCommand(QString comd,bool waitendprocess,bool showStdout,QString fn="", bool compileLatex=false);
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
	void AnalyseText();
	void AnalyseTextFormDestroyed();
	void GenerateRandomText();
	
	void RealViewLog(bool noTabChange=false);
	void ViewLog(bool noTabChange=false);
	void ViewAndHighlightError();
	void DisplayLatexError();
	void NextMark();
	void PreviousMark();
	void gotoNearLogEntry(LogType lt, bool backward, QString notFoundMessage);
	void NextError();
	void PreviousError();
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
	
	void viewCollapseEverything();
	void viewCollapseLevel();
	void viewCollapseBlock();
	void viewExpandEverything();
	void viewExpandLevel();
	void viewExpandBlock();

//void ToggleMode();

	void gotoBookmark();
	void toggleBookmark();

	void SetMostUsedSymbols(QTableWidgetItem* item);

	void updateBibFiles();
	void updateCompleter();

	void tabChanged(int i);

	void gotoLine(int line);  //0 based
	void gotoLocation(int line, const QString &fileName);  //0 based, absolute file name
	void gotoLogEntryEditorOnly(int logEntryNumber);
	void gotoLogEntryAt(int newLineNumber);
	void gotoMark(bool backward, int id);

	void lineHandleDeleted(QDocumentLineHandle* l);
	
	void previewLatex();
	void previewAvailable(const QString& imageFile, const QString& text);


	void StructureToolBoxToggle(bool checked);

	void templateRemove();
	void templateEdit();

	void fileReloaded();
protected:
	LatexEditorView* getEditorFromStructureItem(QTreeWidgetItem* m_item);
	QPoint sectionSelection(QTreeWidgetItem* m_item);
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
	virtual void changeEvent(QEvent *e);

	Qt::MouseButtons mb;
public:
	static const int structureTreeLineColumn;
};



#endif
