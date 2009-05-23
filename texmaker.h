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

#include <QMainWindow>
#include <QDockWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QListWidget>
#include <QToolBox>
#include <QTabWidget>
#include <QTreeWidget>
#include <QLabel>
#include <QAction>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QPointer>
#include <QProcess>
#include <QPushButton>
#include <QColor>
#include <QTextTable>
#include <QVBoxLayout>
#include <QTableView>

#include "buildmanager.h"
#include "configmanager.h"
#include "latexlog.h"
#include "latexeditorview.h"
#include "latexcompleter.h"
#include "symbollistwidget.h"
#include "metapostlistwidget.h"
#include "pstrickslistwidget.h"
#include "logeditor.h"
#include "textanalysis.h"
#include "spellerdialog.h"


#include "qformatfactory.h"
#include "qlanguagefactory.h"
#include "qlinemarksinfocenter.h"


typedef  QMap<LatexEditorView*, QString> FilesMap;
typedef  QString Userlist[10];
typedef  QString UserCd[5];
typedef int SymbolList[412];

class Texmaker : public QMainWindow {
	Q_OBJECT

public:
	Texmaker(QWidget *parent = 0, Qt::WFlags flags = 0);

	QString getName();
	QString getCurrentFileName(); //returns the absolute file name of the current file or "" if none is opened
	QString getCompileFileName(); //returns the absolute file name of the file to be compiled (master or current)  TODO: test if it is always absolute (it depends on MasterFile and filenames)
	QByteArray windowstate;
public slots:
	LatexEditorView* load(const QString &f , bool asProject = false);
	void gotoLine(int line);  //0 based
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
	
	void setupMenus();
	void setupToolBars();
	void createStatusBar();
	bool FileAlreadyOpen(QString f);
	void closeEvent(QCloseEvent *e);

	FilesMap filenames;


	QFormatFactory *m_formats;
	QLanguageFactory* m_languages;
	LatexCompleter* completer;

//gui
	QDockWidget *StructureView;
	QTabWidget *EditorView;
	QToolBox *StructureToolbox;
	MetapostListWidget *MpListWidget;
	PstricksListWidget *PsListWidget;
	SymbolListWidget *RelationListWidget, *ArrowListWidget, *MiscellaneousListWidget, *DelimitersListWidget, *GreekListWidget, *MostUsedListWidget;
	QTreeWidget *StructureTreeWidget;

	QDockWidget *OutputView; //contains output widgets (over OutputLayout)
	QTabBar *logViewerTabBar; //header to select outp (if tabbedLogView, then it is OutputView's TitleBarWidget)
	QStackedWidget *OutputLayout; //only widget of OutputView, contains the others (OutputTextEdit, OutputVLayout, OutputTable2), only one of them is visible at the same time
	QTableView *OutputTable, *OutputTable2;
	LogEditor *OutputTextEdit,*OutputLogTextEdit;
	QLabel *preViewer;

	bool tabbedLogView;

//toolbars
//
	QToolBar *fileToolBar, *editToolBar, *runToolBar, *formatToolBar, *mathToolBar;
	QAction *ToggleAct, *ToggleRememberAct;

	QLabel *stat1, *stat2, *stat3;
	QString MasterName,persistentMasterFile;
	bool logpresent;

	QToolButton *combo1,*combo2,*combo3,*combo4,*combo5;

//settings
	ConfigManager configManager;
	BuildManager buildManager;
	int split1_right, split1_left, split2_top, split2_bottom, quickmode;
	bool singlemode, wordwrap, parenmatch, showoutputview, showstructview, ams_packages, makeidx_package, completion, autoindent;
	int showlinemultiples;
	bool folding, showlinestate, showcursorstate, realtimespellchecking;
	QString document_class, typeface_size, paper_size, document_encoding, author;
	QString latex_command, viewdvi_command, dvips_command, dvipdf_command, metapost_command;
	QString precompile_command, viewps_command, ps2pdf_command, makeindex_command, bibtex_command, pdflatex_command, viewpdf_command, userquick_command, ghostscript_command;
	QString spell_dic, spell_ignored_words;
        QStringList struct_level;
	QStringList userClassList, userPaperList, userEncodingList, userOptionsList;
	QStringList labelitem;
	Userlist UserMenuName, UserMenuTag;
	UserCd UserToolName, UserToolCommand;

	int spellcheckErrorFormat;
	SpellerUtility *mainSpeller;
//dialogs
	TextAnalysisDialog *textAnalysisDlg;
	SpellerDialog *spellDlg;

	QStringList completerWords;
	QStringList completerFiles;
	QStringList userCommandList;

//tools
	QProcess *proc;
	bool FINPROCESS, ERRPROCESS;
//latex errors
	LatexLogModel * logModel;

	SymbolList symbolScore;
	usercodelist symbolMostused;

	LatexEditorView *currentEditorView() const;
	void configureNewEditorView(LatexEditorView *edit);
	void updateEditorSetting(LatexEditorView *edit);
private slots:

	void fileNew(QString fileName="untitled");
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
	void editSelectAll();
	void editEraseLine();
	void editFind();
	void editFindNext();
	void editReplace();
	void editGotoLine();
	void editJumpToLastChange();
	void editJumpToLastChangeForward();
	void editComment();
	void editUncomment();
	void editIndent();
	void editUnindent();
	void editSpell();
	void editChangeLineEnding();
	void editSetupEncoding();

	void StructureContextMenu(QPoint point);

	void ReadSettings();
	void SaveSettings();

	void lineMarkToolTip(int line, int mark);
	void NewDocumentStatus(bool m);
	void UpdateCaption();
	void CloseEditorTab(int tab);

	void UpdateStructure();
	void ShowStructure();
	void ClickedOnStructure(QTreeWidgetItem *item,int);

	void NormalCompletion();
	void InsertEnvironmentCompletion();
	void InsertTextCompletion();
	void InsertTag(QString Entity, int dx, int dy);
	void InsertSymbol(QTableWidgetItem *item);
	void InsertMetaPost(QListWidgetItem *item);
	void InsertPstricks(QListWidgetItem *item);
	void InsertFromAction();
	void InsertWithSelectionFromString(const QString& text);
	void InsertFromString(const QString& text);
	void InsertBib();
	void InsertStruct();
	void InsertStructFromString(const QString& text);
	void InsertImage();
	void InsertInclude();
	void InsertInput();

	void InsertBib1();
	void InsertBib2();
	void InsertBib3();
	void InsertBib4();
	void InsertBib5();
	void InsertBib6();
	void InsertBib7();
	void InsertBib8();
	void InsertBib9();
	void InsertBib10();
	void InsertBib11();
	void InsertBib12();
	void InsertBib13();
	void CleanBib();

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

	void RunCommand(QString comd,bool waitendprocess,bool showStdout,QString fn="");
	void RunPreCompileCommand();
	void readFromStderr();
	void readFromStdoutput();
	void SlotEndProcess(int err);
	void QuickBuild();
	void Latex();
	void ViewDvi();
	void DviToPS();
	void ViewPS();
	void PDFLatex();
	void ViewPDF();
	void CleanAll();
	void MakeBib();
	void MakeIndex();
	void PStoPDF();
	void DVItoPDF();
	void MetaPost();
	void UserTool();
	void EditUserTool();

	void WebPublish();
	void AnalyseText();
	void AnalyseTextFormDestroyed();

	void SwitchToErrorList();
	void RealViewLog();
	void ViewLog();
	void ClickedOnLogLine(const QModelIndex &);
	void OutputViewVisibilityChanged(bool visible);
	void LatexError();
	void DisplayLatexError();
	void GoToLogEntry(int logEntryNumber);
	void GoToLogEntryAt(int newLineNumber);
	void GoToMark(bool backward, int id);
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

/////
	void LatexHelp();
	void UserManualHelp();
	void HelpAbout();

	void GeneralOptions();
	void ToggleMode();

	void gotoNextDocument();
	void gotoPrevDocument();

	void viewCollapseEverything();
	void viewCollapseLevel();
	void viewCollapseBlock();
	void viewExpandEverything();
	void viewExpandLevel();
	void viewExpandBlock();

//void ToggleMode();

	void gotoBookmark();
	void toggleBookmark();

	void SetMostUsedSymbols();

	void readCompletionList(const QStringList &files);
	void updateCompleter();

	void tabChanged(int i);

	void lineHandleDeleted(QDocumentLineHandle* l);

        void previewLatex();
protected:
	QPoint sectionSelection(QTreeWidgetItem* m_item);
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);


public:
	static const int structureTreeLineColumn;
};

#endif
