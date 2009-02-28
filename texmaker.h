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
#include <QTableWidgetItem>
#include <QPointer>
#include <QProcess>
#include <QPushButton>
#include <QColor>
#include <QTextTable>
#include <QVBoxLayout>
#include <QTableWidget>

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
typedef  QMap<QString,QString> KeysMap;
typedef  QString Userlist[10];
typedef  QString UserCd[5];
typedef int SymbolList[412];

class Texmaker : public QMainWindow
{
    Q_OBJECT

public:
    Texmaker(QWidget *parent = 0, Qt::WFlags flags = 0);

QString getName();
QFont EditorFont;
QByteArray windowstate;
public slots:
void load( const QString &f );
void gotoLine( int line );//0 based
void executeCommandLine( const QStringList& args, bool realCmdLine);
void onOtherInstanceMessage(const QString &);  // For messages for the single instance

private:
void setupMenus();
void setupToolBars();
void createStatusBar();
bool FileAlreadyOpen(QString f);
void closeEvent(QCloseEvent *e);

FilesMap filenames;
KeysMap shortcuts, actionstext;

QString configFileName,configFileNameBase;
QFormatFactory *m_formats;
QLanguageFactory* m_languages;
LatexCompleter* completer;

//gui
QDockWidget *OutputView, *StructureView;
QTabWidget *EditorView;
LogEditor* OutputTextEdit;
QToolBox *StructureToolbox;
MetapostListWidget *MpListWidget;
PstricksListWidget *PsListWidget;
SymbolListWidget *RelationListWidget, *ArrowListWidget, *MiscellaneousListWidget, *DelimitersListWidget, *GreekListWidget, *MostUsedListWidget;
QTreeWidget *StructureTreeWidget;
QVBoxLayout *OutputLayout;
QTableWidget *OutputTableWidget;


//menu-toolbar
QMenu *fileMenu, *recentMenu, *editMenu, *toolMenu;
QMenu *latex1Menu, *latex11Menu, *latex12Menu, *latex13Menu, *latex14Menu, *latex15Menu, *latex16Menu, *latex17Menu ;
QMenu *math1Menu, *math11Menu, *math12Menu, *math13Menu, *math14Menu;
QMenu *wizardMenu;
QMenu *bibMenu;
QMenu *user1Menu, *user11Menu, *user12Menu;
QMenu *viewMenu;
QMenu *optionsMenu;
QMenu *helpMenu;

QToolBar *fileToolBar, *editToolBar, *runToolBar, *formatToolBar, *mathToolBar;
QAction *recentFileActs[5], *ToggleAct, *ToggleRememberAct;

QLabel *stat1, *stat2, *stat3;
QPushButton *pb1, *pb2, *pb3;
QString MasterName,persistentMasterFile;
bool logpresent;
QStringList recentFilesList;
//settings
int split1_right, split1_left, split2_top, split2_bottom, quickmode;
bool singlemode, wordwrap, parenmatch, showoutputview, showstructview, ams_packages, makeidx_package, completion, autoindent;
int showlinemultiples;
bool folding, showlinestate, showcursorstate, realtimespellchecking;
QString document_class, typeface_size, paper_size, document_encoding, author;
QString latex_command, viewdvi_command, dvips_command, dvipdf_command, metapost_command;
QString viewps_command, ps2pdf_command, makeindex_command, bibtex_command, pdflatex_command, viewpdf_command, userquick_command, ghostscript_command;
QString spell_dic, spell_ignored_words;
QString lastDocument;
QTextCodec* newfile_encoding;
bool autodetectLoadedFile;
QString struct_level1, struct_level2, struct_level3, struct_level4, struct_level5;
QStringList userClassList, userPaperList, userEncodingList, userOptionsList;
QStringList structlist, labelitem, structitem;
Userlist UserMenuName, UserMenuTag;
UserCd UserToolName, UserToolCommand;
QVector<QString> UserKeyReplace, UserKeyReplaceAfterWord, UserKeyReplaceBeforeWord;

int spellcheckErrorFormat;
SpellerUtility *mainSpeller;
//dialogs
TextAnalysisDialog *textAnalysisDlg;
SpellerDialog *spellDlg;


//tools
QProcess *proc;
bool FINPROCESS, ERRPROCESS;
//latex errors
QStringList errorFileList, errorTypeList, errorLineList, errorMessageList, errorLogList;
QList<int> onlyErrorList;
int errorIndex;

//X11
#if defined( Q_WS_X11 )
QString x11style;
QString x11fontfamily;
int x11fontsize;
#endif
SymbolList symbolScore;
usercodelist symbolMostused;


LatexEditorView *currentEditorView() const;
void configureNewEditorView(LatexEditorView *edit);
void updateEditorSetting(LatexEditorView *edit);
private slots:

void fileNew();
void fileOpen();
void fileSave();
void fileSaveAll();
void fileSaveAs();
void fileClose();
void fileCloseAll();
void fileExit();
void fileOpenRecent();
void AddRecentFile(const QString &f);
void UpdateRecentFile();
void filePrint();

void editUndo();
void editRedo();
void editCut();
void editCopy();
void editPaste();
void editSelectAll();
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

void ReadSettings();
void SaveSettings();

void NewDocumentStatus(bool m);
void UpdateCaption();

void UpdateStructure();
void ShowStructure();
void ClickedOnStructure(QTreeWidgetItem *item,int);

void InsertTag(QString Entity, int dx, int dy);
void InsertSymbol(QTableWidgetItem *item);
void InsertMetaPost(QListWidgetItem *item);
void InsertPstricks(QListWidgetItem *item);
void InsertFromAction();
void InsertWithSelectionFromAction();
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

void InsertUserTag1();
void InsertUserTag2();
void InsertUserTag3();
void InsertUserTag4();
void InsertUserTag5();
void InsertUserTag6();
void InsertUserTag7();
void InsertUserTag8();
void InsertUserTag9();
void InsertUserTag10();
void EditUserMenu();

void SectionCommand(const QString& text);
void OtherCommand(const QString& text);
void InsertRef();
void InsertPageRef();
void SizeCommand(const QString& text);
void LeftDelimiter(const QString& text);
void RightDelimiter(const QString& text);

void QuickTabular();
void QuickArray();
void QuickTabbing();
void QuickLetter();
void QuickDocument();

void RunCommand(QString comd,bool waitendprocess,bool showStdout);
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
void UserTool1();
void UserTool2();
void UserTool3();
void UserTool4();
void UserTool5();
void EditUserTool();
void EditUserKeyReplacements();

void WebPublish();
void AnalyseText();
void AnalyseTextFormDestroyed();


void ViewLog();
void ClickedOnLogLine(QTableWidgetItem *item);
void OutputViewVisibilityChanged(bool visible);
void LatexError();
void DisplayLatexError();
void NextError();
void PreviousError();
bool NoLatexErrors();
bool LogExists();

/////
void LatexHelp();
void UserManualHelp();
void HelpAbout();

void GeneralOptions();
void ToggleMode();
void ToggleMasterRememberMode();

void gotoNextDocument();
void gotoPrevDocument();
//void ToggleMode();

void SetInterfaceFont();
void SetInterfaceType();

void gotoBookmark(int id);
void gotoBookmark0(){gotoBookmark(0);}
void gotoBookmark1(){gotoBookmark(1);}
void gotoBookmark2(){gotoBookmark(2);}
void gotoBookmark3(){gotoBookmark(3);}
void gotoBookmark4(){gotoBookmark(4);}
void gotoBookmark5(){gotoBookmark(5);}
void gotoBookmark6(){gotoBookmark(6);}
void gotoBookmark7(){gotoBookmark(7);}
void gotoBookmark8(){gotoBookmark(8);}
void gotoBookmark9(){gotoBookmark(9);}

void toggleBookmark(int id);
void toggleBookmark0(){toggleBookmark(0);}
void toggleBookmark1(){toggleBookmark(1);}
void toggleBookmark2(){toggleBookmark(2);}
void toggleBookmark3(){toggleBookmark(3);}
void toggleBookmark4(){toggleBookmark(4);}
void toggleBookmark5(){toggleBookmark(5);}
void toggleBookmark6(){toggleBookmark(6);}
void toggleBookmark7(){toggleBookmark(7);}
void toggleBookmark8(){toggleBookmark(8);}
void toggleBookmark9(){toggleBookmark(9);}

void SetMostUsedSymbols();

void ModifyShortcuts();

void updateCompleter();

protected:
void dragEnterEvent(QDragEnterEvent *event);
void dropEvent(QDropEvent *event);
};

#endif
