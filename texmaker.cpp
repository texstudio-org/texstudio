/***************************************************************************
 *   copyright       : (C) 2003-2008 by Pascal Brachet                     *
 *   addons by Luis Silvestre                                              *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation  either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
//#include <stdlib.h>

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QSettings>
#include <QApplication>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QFileInfo>
#include <QLabel>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QHeaderView>
#include <QLineEdit>
#include <QProcess>
#include <QComboBox>
#include <QSpinBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QCheckBox>
#include <QLocale>
#include <QTabWidget>
#include <QStyleFactory>
#include <QStyle>
#include <QFontDatabase>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextEdit>
#include <QTextBlock>
#include <QDebug>
#include <QDesktopServices>
#include <QAbstractItemModel>
#include <QTextCharFormat>
#include <QTextTableFormat>
#include <QTextLength>
#include <QFrame>
#include <QFontMetrics>
#include <QCloseEvent>
#include <QPrinter>
#include <QPrintDialog>

#include "texmaker.h"
#include "latexeditorview.h"

#include "structdialog.h"
#include "filechooser.h"
#include "tabdialog.h"
#include "arraydialog.h"
#include "tabbingdialog.h"
#include "letterdialog.h"
#include "quickdocumentdialog.h"
#include "usermenudialog.h"
#include "userkeyreplacementsdialog.h"
#include "usertooldialog.h"
#include "refdialog.h"
#include "configdialog.h"
#include "aboutdialog.h"
#include "webpublishdialog.h"

#include "qdocument.h"
#include "qdocumentline.h"
#include "qcodecompletionengine.h"

#if defined( Q_WS_X11 )
#include "x11fontdialog.h"
#endif

Texmaker::Texmaker(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
ReadSettings();
setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

#ifdef Q_WS_MACX
setWindowIcon(QIcon(":/images/logo128.png"));
#else
setWindowIcon(QIcon(":/images/appicon.png"));
#endif

setIconSize(QSize(22,22 ));


// PANNEAU STRUCTURE
StructureView = new QDockWidget(this);
StructureView->setObjectName("StructureView");
StructureView->setAllowedAreas(Qt::AllDockWidgetAreas);
StructureView->setFeatures(QDockWidget::DockWidgetClosable);
StructureView->setWindowTitle(tr("Structure"));
addDockWidget(Qt::LeftDockWidgetArea, StructureView);
StructureToolbox=new QToolBox(StructureView);
StructureView->setWidget(StructureToolbox);

StructureTreeWidget=new QTreeWidget(StructureToolbox);
StructureTreeWidget->setColumnCount(1);
StructureTreeWidget->header()->hide();
StructureTreeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//StructureTreeWidget->setToolTip(tr("Click to jump to the line"));
connect( StructureTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem *,int )), SLOT(ClickedOnStructure(QTreeWidgetItem *,int)));
// connect( StructureTreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *,int )), SLOT(DoubleClickedOnStructure(QTreeWidgetItem *,int))); // qt4 bugs - don't use it
StructureToolbox->addItem(StructureTreeWidget,QIcon(":/images/structure.png"),tr("Structure"));

RelationListWidget=new SymbolListWidget(StructureToolbox,0);
connect(RelationListWidget, SIGNAL(itemClicked ( QTableWidgetItem*)), this, SLOT(InsertSymbol(QTableWidgetItem*)));
StructureToolbox->addItem(RelationListWidget,QIcon(":/images/math1.png"),tr("Relation symbols"));

ArrowListWidget=new SymbolListWidget(StructureToolbox,1);
connect(ArrowListWidget, SIGNAL(itemClicked ( QTableWidgetItem*)), this, SLOT(InsertSymbol(QTableWidgetItem*)));
StructureToolbox->addItem(ArrowListWidget,QIcon(":/images/math2.png"),tr("Arrow symbols"));

MiscellaneousListWidget=new SymbolListWidget(StructureToolbox,2);
connect(MiscellaneousListWidget, SIGNAL(itemClicked ( QTableWidgetItem*)), this, SLOT(InsertSymbol(QTableWidgetItem*)));
StructureToolbox->addItem(MiscellaneousListWidget,QIcon(":/images/math3.png"),tr("Miscellaneous symbols"));

DelimitersListWidget=new SymbolListWidget(StructureToolbox,3);
connect(DelimitersListWidget, SIGNAL(itemClicked ( QTableWidgetItem*)), this, SLOT(InsertSymbol(QTableWidgetItem*)));
StructureToolbox->addItem(DelimitersListWidget,QIcon(":/images/math4.png"),tr("Delimiters"));

GreekListWidget=new SymbolListWidget(StructureToolbox,4);
connect(GreekListWidget, SIGNAL(itemClicked ( QTableWidgetItem*)), this, SLOT(InsertSymbol(QTableWidgetItem*)));
StructureToolbox->addItem(GreekListWidget,QIcon(":/images/math5.png"),tr("Greek letters"));

MostUsedListWidget=new SymbolListWidget(StructureToolbox,5);
connect(MostUsedListWidget, SIGNAL(itemClicked ( QTableWidgetItem*)), this, SLOT(InsertSymbol(QTableWidgetItem*)));
StructureToolbox->addItem(MostUsedListWidget,QIcon(":/images/math6.png"),tr("Most used symbols"));
SetMostUsedSymbols();

PsListWidget=new PstricksListWidget(StructureToolbox);
connect(PsListWidget, SIGNAL(itemClicked ( QListWidgetItem*)), this, SLOT(InsertPstricks(QListWidgetItem*)));
StructureToolbox->addItem(PsListWidget,QIcon(":/images/pstricks.png"),tr("Pstricks Commands"));

MpListWidget=new MetapostListWidget(StructureToolbox);
connect(MpListWidget, SIGNAL(itemClicked ( QListWidgetItem*)), this, SLOT(InsertMetaPost(QListWidgetItem*)));
StructureToolbox->addItem(MpListWidget,QIcon(":/images/metapost.png"),tr("MetaPost Commands"));

// OUTPUT WIDGETS
OutputView = new QDockWidget(this);
OutputView->setObjectName("OutputView");
OutputView->setAllowedAreas(Qt::AllDockWidgetAreas);
OutputView->setFeatures(QDockWidget::DockWidgetClosable);
OutputView->setWindowTitle(tr("Messages / Log File"));
addDockWidget(Qt::BottomDockWidgetArea,OutputView);
connect(OutputView,SIGNAL(visibilityChanged ( bool )),this,SLOT(OutputViewVisibilityChanged(bool)));


QFrame *Outputframe=new QFrame(OutputView);
Outputframe->setLineWidth(1);
Outputframe->setFrameShape(QFrame::StyledPanel);
Outputframe->setFrameShadow(QFrame::Sunken);

OutputLayout= new QVBoxLayout(Outputframe);
OutputLayout->setSpacing(0);
OutputLayout->setMargin(0);

OutputTableWidget= new QTableWidget (1,5,Outputframe);
QTableWidgetItem *HeaderItem = new QTableWidgetItem(" ");
HeaderItem->setTextAlignment(Qt::AlignLeft);
OutputTableWidget->setHorizontalHeaderItem(0,HeaderItem);
HeaderItem = new QTableWidgetItem("File");
HeaderItem->setTextAlignment(Qt::AlignLeft);
OutputTableWidget->setHorizontalHeaderItem(1,HeaderItem);
HeaderItem = new QTableWidgetItem("Type");
HeaderItem->setTextAlignment(Qt::AlignLeft);
OutputTableWidget->setHorizontalHeaderItem(2,HeaderItem);
HeaderItem = new QTableWidgetItem("Line");
HeaderItem->setTextAlignment(Qt::AlignLeft);
OutputTableWidget->setHorizontalHeaderItem(3,HeaderItem);
HeaderItem = new QTableWidgetItem("Message");
HeaderItem->setTextAlignment(Qt::AlignLeft);
OutputTableWidget->setHorizontalHeaderItem(4,HeaderItem);

//OutputTableWidget->setWordWrap(true);
OutputTableWidget->setSelectionMode (QAbstractItemView::SingleSelection);
QFontMetrics fm(qApp->font());
OutputTableWidget->setColumnWidth(0,fm.width("> "));
OutputTableWidget->setColumnWidth(1,20*fm.width("w"));
OutputTableWidget->setColumnWidth(2,fm.width("WarningW"));
OutputTableWidget->setColumnWidth(3,fm.width("Line WWWWW"));
OutputTableWidget->setColumnWidth(4,20*fm.width("w"));
connect(OutputTableWidget, SIGNAL(itemClicked ( QTableWidgetItem*)), this, SLOT(ClickedOnLogLine(QTableWidgetItem*)));
OutputLayout->addWidget(OutputTableWidget);
OutputTableWidget->setMinimumHeight(5*(fm.lineSpacing()+4));


OutputTextEdit = new LogEditor(Outputframe);
OutputTextEdit->setFocusPolicy(Qt::ClickFocus);
OutputTextEdit->setMinimumHeight(3*(fm.lineSpacing()+4));
OutputTextEdit->setReadOnly(true);
connect(OutputTextEdit, SIGNAL(clickonline(int )),this,SLOT(ClickedOnOutput(int )));

OutputLayout->addWidget(OutputTextEdit);

OutputView->setWidget(Outputframe);
OutputTableWidget->hide();


logpresent=false;

//
errorFileList.clear();
errorTypeList.clear();
errorLineList.clear();
errorMessageList.clear();
errorLogList.clear();
onlyErrorList.clear();
errorIndex=-1;


// TAB WIDGET EDITEUR
EditorView=new QTabWidget(this);
EditorView->setFocusPolicy(Qt::ClickFocus);
EditorView->setFocus();
connect(EditorView, SIGNAL( currentChanged( QWidget * ) ), this, SLOT(UpdateCaption()) );
setCentralWidget(EditorView);
setupMenus();
setupToolBars();

restoreState(windowstate, 0);


UpdateRecentFile();
createStatusBar();
UpdateCaption();
singlemode=true;
MasterName=getName();

show();

stat1->setText(QString(" %1 ").arg(tr("Normal Mode")));
stat2->setText(QString(" %1 ").arg(tr("Ready")));
//connect(stat3, SIGNAL(itemClicked ( QTableWidgetItem*)), this, SLOT(InsertSymbol(QTableWidgetItem*)));


setAcceptDrops(true);

    mainSpeller=new SpellerUtility();;
    mainSpeller->loadDictionary(spell_dic,configFileNameBase);
    mainSpeller->setActive(realtimespellchecking);
    
    LatexEditorView::setSpeller(mainSpeller);

    if (QFileInfo(QCoreApplication::applicationDirPath()+"/texmakerFormats.qxf").exists() && QFileInfo(QCoreApplication::applicationDirPath()+"/texmakerFormats.qxf").isWritable()) 
        m_formats = new QFormatFactory(QCoreApplication::applicationDirPath()+"/texmakerFormats.qxf", this);
    else {
        QString formatFileName=configFileNameBase+"Formats.qxf";
        
        if (!QFileInfo(formatFileName).exists()) 
            QFile::copy(findResourceFile("defaultFormats.qxf"), formatFileName);
        m_formats = new QFormatFactory(formatFileName, this);
    } 

        
    QDocument::setFormatFactory(m_formats);
    mainSpeller->spellcheckErrorFormat=m_formats->id("spellingMistake");

    QDocument::setShowSpaces(QDocument::ShowTrailing | QDocument::ShowLeading | QDocument::ShowTabs);


    QString qxsPath=QFileInfo(findResourceFile("qxs/tex.qnfa")).path();   
    m_languages = new QLanguageFactory(m_formats, this);
    m_languages->addDefinitionPath(qxsPath);
    QLineMarksInfoCenter::instance()->loadMarkTypes(qxsPath+"/marks.qxm");

    completer=new LatexCompleter(this);
    
    
    updateCompleter();
    m_languages->addCompletionEngine(completer);

}

QString Texmaker::findResourceFile(QString fileName){
    QStringList searchFiles;
    #if defined( Q_WS_X11 )
    searchFiles<<PREFIX"/share/texmakerx/"+fileName; //X_11
    #endif
    searchFiles<<QCoreApplication::applicationDirPath() + "/../Resources/"+fileName; //macx
    searchFiles<<QCoreApplication::applicationDirPath() + "/"+fileName; //windows old 
    searchFiles<<QCoreApplication::applicationDirPath() + "/help/"+fileName; //windows new
    searchFiles<<QCoreApplication::applicationDirPath() + "/data/"+fileName; //windows new
    searchFiles<<QCoreApplication::applicationDirPath() + "/qxs/"+fileName; //windows new
    searchFiles<<QCoreApplication::applicationDirPath() + "/dictionaries/"+fileName; //windows new
    searchFiles<<QCoreApplication::applicationDirPath() + "/translation/"+fileName; //windows new
    
    foreach (QString fn, searchFiles) {
        QFileInfo fic(fn);
        if (fic.exists() && fic.isReadable() ) 
        {
            return fn;
            break;
        }
    }
    return "";
}
void Texmaker::setupMenus()
{
QAction *Act;
//file
fileMenu = menuBar()->addMenu(tr("&File"));
Act = new QAction(QIcon(":/images/filenew.png"), tr("New"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_N);
connect(Act, SIGNAL(triggered()), this, SLOT(fileNew()));
fileMenu->addAction(Act);

Act = new QAction(QIcon(":/images/fileopen.png"), tr("Open"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_O);
connect(Act, SIGNAL(triggered()), this, SLOT(fileOpen()));
fileMenu->addAction(Act);

recentMenu=fileMenu->addMenu(tr("Open Recent"));
for (int i = 0; i < 5; ++i)
	{
	recentFileActs[i] = new QAction(this);
	recentFileActs[i]->setVisible(false);
	connect(recentFileActs[i], SIGNAL(triggered()),this, SLOT(fileOpenRecent()));
	recentMenu->addAction(recentFileActs[i]);
	}

Act = new QAction(QIcon(":/images/filesave.png"), tr("Save"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_S);
connect(Act, SIGNAL(triggered()), this, SLOT(fileSave()));
fileMenu->addSeparator();
fileMenu->addAction(Act);

Act = new QAction(tr("Save As"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
fileMenu->addAction(Act);

Act = new QAction(tr("Save All"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(fileSaveAll()));
fileMenu->addAction(Act);

Act = new QAction(QIcon(":/images/fileclose.png"), tr("Close"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_W);
connect(Act, SIGNAL(triggered()), this, SLOT(fileClose()));
fileMenu->addSeparator();
fileMenu->addAction(Act);

Act = new QAction(tr("Close All"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(fileCloseAll()));
fileMenu->addAction(Act);

Act = new QAction(tr("Print"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_P);
connect(Act, SIGNAL(triggered()), this, SLOT(filePrint()));
fileMenu->addSeparator();
fileMenu->addAction(Act);

Act = new QAction(QIcon(":/images/exit.png"), tr("Exit"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_Q);
connect(Act, SIGNAL(triggered()), this, SLOT(fileExit()));
fileMenu->addSeparator();
fileMenu->addAction(Act);

editMenu = menuBar()->addMenu(tr("&Edit"));
Act = new QAction(QIcon(":/images/undo.png"), tr("Undo"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_Z);
connect(Act, SIGNAL(triggered()), this, SLOT(editUndo()));
editMenu->addAction(Act);

Act = new QAction(QIcon(":/images/redo.png"), tr("Redo"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_Y);
connect(Act, SIGNAL(triggered()), this, SLOT(editRedo()));
editMenu->addAction(Act);
editMenu->addSeparator();

Act = new QAction(QIcon(":/images/editcopy.png"), tr("Copy"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_C);
connect(Act, SIGNAL(triggered()), this, SLOT(editCopy()));
editMenu->addAction(Act);


Act = new QAction(QIcon(":/images/editcut.png"), tr("Cut"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_X);
connect(Act, SIGNAL(triggered()), this, SLOT(editCut()));
editMenu->addAction(Act);

Act = new QAction(QIcon(":/images/editpaste.png"), tr("Paste"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_V);
connect(Act, SIGNAL(triggered()), this, SLOT(editPaste()));
editMenu->addAction(Act);

Act = new QAction( tr("Select All"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_A);
connect(Act, SIGNAL(triggered()), this, SLOT(editSelectAll()));
editMenu->addAction(Act);
editMenu->addSeparator();

LatexEditorView::setBaseActions(editMenu->actions());


Act = new QAction( tr("Comment"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_T);
connect(Act, SIGNAL(triggered()), this, SLOT(editComment()));
editMenu->addAction(Act);

Act = new QAction( tr("Uncomment"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_U);
connect(Act, SIGNAL(triggered()), this, SLOT(editUncomment()));
editMenu->addAction(Act);

Act = new QAction( tr("Indent"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(editIndent()));
editMenu->addAction(Act);

Act = new QAction( tr("Unindent"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(editUnindent()));
editMenu->addAction(Act);
editMenu->addSeparator();

Act = new QAction( tr("Find"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_F);
connect(Act, SIGNAL(triggered()), this, SLOT(editFind()));
editMenu->addAction(Act);

Act = new QAction( tr("FindNext"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_M);
connect(Act, SIGNAL(triggered()), this, SLOT(editFindNext()));
editMenu->addAction(Act);

Act = new QAction( tr("Replace"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_R);
connect(Act, SIGNAL(triggered()), this, SLOT(editReplace()));
editMenu->addAction(Act);

editMenu->addSeparator();

Act = new QAction(QIcon(":/images/goto.png"), tr("Goto Line"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_G);
connect(Act, SIGNAL(triggered()), this, SLOT(editGotoLine()));
editMenu->addAction(Act);

Act = new QAction(tr("Jump to last change"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_H);
connect(Act, SIGNAL(triggered()), this, SLOT(editJumpToLastChange()));
editMenu->addAction(Act);

Act = new QAction(tr("Jump forward"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_H);
connect(Act, SIGNAL(triggered()), this, SLOT(editJumpToLastChangeForward()));
editMenu->addAction(Act);

  //bookmarks menus
    //toggle
QMenu *subMenu=new QMenu("Toggle Bookmark",this);
editMenu->addMenu(subMenu);
Act = new QAction(tr("Bookmark 0"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_0);
connect(Act, SIGNAL(triggered()), this, SLOT(toggleBookmark0()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 1"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_1);
connect(Act, SIGNAL(triggered()), this, SLOT(toggleBookmark1()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 2"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_2);
connect(Act, SIGNAL(triggered()), this, SLOT(toggleBookmark2()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 3"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_3);
connect(Act, SIGNAL(triggered()), this, SLOT(toggleBookmark3()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 4"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_4);
connect(Act, SIGNAL(triggered()), this, SLOT(toggleBookmark4()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 5"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_5);
connect(Act, SIGNAL(triggered()), this, SLOT(toggleBookmark5()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 6"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_6);
connect(Act, SIGNAL(triggered()), this, SLOT(toggleBookmark6()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 7"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_7);
connect(Act, SIGNAL(triggered()), this, SLOT(toggleBookmark7()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 8"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_8);
connect(Act, SIGNAL(triggered()), this, SLOT(toggleBookmark8()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 9"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_9);
connect(Act, SIGNAL(triggered()), this, SLOT(toggleBookmark9()));
subMenu->addAction(Act);

    //goto
subMenu=new QMenu("Goto Bookmark",this);
editMenu->addMenu(subMenu);
Act = new QAction(tr("Bookmark 0"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_0);
connect(Act, SIGNAL(triggered()), this, SLOT(gotoBookmark0()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 1"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_1);
connect(Act, SIGNAL(triggered()), this, SLOT(gotoBookmark1()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 2"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_2);
connect(Act, SIGNAL(triggered()), this, SLOT(gotoBookmark2()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 3"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_3);
connect(Act, SIGNAL(triggered()), this, SLOT(gotoBookmark3()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 4"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_4);
connect(Act, SIGNAL(triggered()), this, SLOT(gotoBookmark4()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 5"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_5);
connect(Act, SIGNAL(triggered()), this, SLOT(gotoBookmark5()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 6"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_6);
connect(Act, SIGNAL(triggered()), this, SLOT(gotoBookmark6()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 7"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_7);
connect(Act, SIGNAL(triggered()), this, SLOT(gotoBookmark7()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 8"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_8);
connect(Act, SIGNAL(triggered()), this, SLOT(gotoBookmark8()));
subMenu->addAction(Act);
Act = new QAction(tr("Bookmark 9"), this);
Act->setShortcut(Qt::CTRL+Qt::Key_9);
connect(Act, SIGNAL(triggered()), this, SLOT(gotoBookmark9()));
subMenu->addAction(Act);

editMenu->addSeparator();

Act = new QAction(tr("Check Spelling"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_F7);
connect(Act, SIGNAL(triggered()), this, SLOT(editSpell()));
editMenu->addAction(Act);
editMenu->addSeparator();

Act = new QAction(tr("Refresh Structure"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(UpdateStructure()));
editMenu->addAction(Act);

toolMenu = menuBar()->addMenu(tr("&Tools"));
Act = new QAction(QIcon(":/images/quick.png"),tr("Quick Build"), this);
Act->setShortcut(Qt::Key_F1);
connect(Act, SIGNAL(triggered()), this, SLOT(QuickBuild()));
toolMenu->addAction(Act);
toolMenu->addSeparator();
Act = new QAction(QIcon(":/images/latex.png"),"LaTeX", this);
Act->setShortcut(Qt::Key_F2);
connect(Act, SIGNAL(triggered()), this, SLOT(Latex()));
toolMenu->addAction(Act);
Act = new QAction(QIcon(":/images/viewdvi.png"),tr("View Dvi"), this);
Act->setShortcut(Qt::Key_F3);
connect(Act, SIGNAL(triggered()), this, SLOT(ViewDvi()));
toolMenu->addAction(Act);
Act = new QAction(QIcon(":/images/dvips.png"),"Dvi->PS", this);
Act->setShortcut(Qt::Key_F4);
connect(Act, SIGNAL(triggered()), this, SLOT(DviToPS()));
toolMenu->addAction(Act);
Act = new QAction(QIcon(":/images/viewps.png"),tr("View PS"), this);
Act->setShortcut(Qt::Key_F5);
connect(Act, SIGNAL(triggered()), this, SLOT(ViewPS()));
toolMenu->addAction(Act);
Act = new QAction(QIcon(":/images/pdflatex.png"),"PDFLaTeX", this);
Act->setShortcut(Qt::Key_F6);
connect(Act, SIGNAL(triggered()), this, SLOT(PDFLatex()));
toolMenu->addAction(Act);
Act = new QAction(QIcon(":/images/viewpdf.png"),tr("View PDF"), this);
Act->setShortcut(Qt::Key_F7);
connect(Act, SIGNAL(triggered()), this, SLOT(ViewPDF()));
toolMenu->addAction(Act);
Act = new QAction(QIcon(":/images/ps2pdf.png"),"PS->PDF", this);
Act->setShortcut(Qt::Key_F8);
connect(Act, SIGNAL(triggered()), this, SLOT(PStoPDF()));
toolMenu->addAction(Act);
Act = new QAction(QIcon(":/images/dvipdf.png"),"DVI->PDF", this);
Act->setShortcut(Qt::Key_F9);
connect(Act, SIGNAL(triggered()), this, SLOT(DVItoPDF()));
toolMenu->addAction(Act);
Act = new QAction(QIcon(":/images/viewlog.png"),tr("View Log"), this);
Act->setShortcut(Qt::Key_F10);
connect(Act, SIGNAL(triggered()), this, SLOT(ViewLog()));
toolMenu->addAction(Act);
Act = new QAction("BibTeX", this);
Act->setShortcut(Qt::Key_F11);
connect(Act, SIGNAL(triggered()), this, SLOT(MakeBib()));
toolMenu->addAction(Act);
Act = new QAction("MakeIndex", this);
Act->setShortcut(Qt::Key_F12);
connect(Act, SIGNAL(triggered()), this, SLOT(MakeIndex()));
toolMenu->addAction(Act);
toolMenu->addSeparator();
Act = new QAction("MPost", this);
connect(Act, SIGNAL(triggered()), this, SLOT(MetaPost()));
toolMenu->addAction(Act);
toolMenu->addSeparator();
Act = new QAction(tr("Clean"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(CleanAll()));
toolMenu->addAction(Act);

toolMenu->addSeparator();
Act = new QAction(tr("Convert to Html"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(WebPublish()));
toolMenu->addAction(Act);

toolMenu->addSeparator();
Act = new QAction(tr("Text Analysis"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(AnalyseText()));
toolMenu->addAction(Act);


Act = new QAction(QIcon(":/images/errorprev.png"),tr("Previous LaTeX Error"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(PreviousError()));
Act = new QAction(QIcon(":/images/errornext.png"),tr("Next LaTeX Error"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(NextError()));

latex1Menu = menuBar()->addMenu(tr("&LaTeX"));
Act = new QAction("\\documentclass", this);
Act->setData("\\documentclass[10pt]{}/21/0/\\documentclass[options]{class}");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex1Menu->addAction(Act);
Act = new QAction("\\usepackage{}", this);
Act->setData("\\usepackage{} /12/0/\\usepackage[options]{pkg}");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex1Menu->addAction(Act);
Act = new QAction("AMS packages", this);
Act->setData("\\usepackage{amsmath}\n\\usepackage{amsfonts}\n\\usepackage{amssymb}\n/0/3/The main American Mathematical Society packages");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex1Menu->addAction(Act);
Act = new QAction("\\begin{document}", this);
Act->setData("\\begin{document}\n\n\\end{document}/0/1/Text is allowed only between \\begin{document} and \\end{document}.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex1Menu->addAction(Act);
Act = new QAction("\\author{}", this);
Act->setData("\\author{}/8/0/\\author{names}\nThe \\author command declares the author(s), where names is a list of authors separated by \\and commands.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex1Menu->addAction(Act);
Act = new QAction("\\title{}", this);
Act->setData("\\title{}/7/0/\\title{text}\nThe \\title command declares text to be the title.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex1Menu->addAction(Act);
Act = new QAction("\\maketitle", this);
Act->setData("\\maketitle/10/0/This command generates a title on a separate title page\n- except in the article class, where the title normally goes at the top of the first page.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex1Menu->addAction(Act);
Act = new QAction("\\tableofcontents", this);
Act->setData("\\tableofcontents/16/0/Put this command where you want the table of contents to go");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex1Menu->addAction(Act);

latex11Menu=latex1Menu->addMenu(tr("&Sectioning"));
Act = new QAction("\\part", this);
Act->setData("\\part");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertStruct()));
latex11Menu->addAction(Act);
Act = new QAction("\\chapter", this);
Act->setData("\\chapter");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertStruct()));
latex11Menu->addAction(Act);
Act = new QAction("\\section", this);
Act->setData("\\section");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertStruct()));
latex11Menu->addAction(Act);
Act = new QAction("\\subsection", this);
Act->setData("\\subsection");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertStruct()));
latex11Menu->addAction(Act);
Act = new QAction("\\subsubsection", this);
Act->setData("\\subsubsection");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertStruct()));
latex11Menu->addAction(Act);
Act = new QAction("\\paragraph", this);
Act->setData("\\paragraph");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertStruct()));
latex11Menu->addAction(Act);
Act = new QAction("\\subparagraph", this);
Act->setData("\\subparagraph");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertStruct()));
latex11Menu->addAction(Act);

latex12Menu=latex1Menu->addMenu(tr("&Environment"));
Act = new QAction(QIcon(":/images/text_center.png"),"\\begin{center} [selection]", this);
Act->setData("\\begin{center}\n/\n\\end{center}/0/1");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex12Menu->addAction(Act);
Act = new QAction(QIcon(":/images/text_left.png"),"\\begin{flushleft} [selection]", this);
Act->setData("\\begin{flushleft}\n/\n\\end{flushleft}/0/1");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex12Menu->addAction(Act);
Act = new QAction(QIcon(":/images/text_right.png"),"\\begin{flushright}  [selection]", this);
Act->setData("\\begin{flushright}\n/\n\\end{flushright}/0/1");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex12Menu->addAction(Act);
Act = new QAction("\\begin{quote}  [selection]", this);
Act->setData("\\begin{quote}\n/\n\\end{quote}/0/1");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex12Menu->addAction(Act);
Act = new QAction("\\begin{quotation}  [selection]", this);
Act->setData("\\begin{quotation}\n/\n\\end{quotation}/0/1");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex12Menu->addAction(Act);
Act = new QAction("\\begin{verse}  [selection]", this);
Act->setData("\\begin{verse}\n/\n\\end{verse}/0/1");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex12Menu->addAction(Act);
Act = new QAction("\\begin{verbatim}  [selection]", this);
Act->setData("\\begin{verbatim}\n/\n\\end{verbatim}/0/1");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex12Menu->addAction(Act);
Act = new QAction("\\begin{table}  [selection]", this);
Act->setData("\\begin{table}\n/\n\\caption{}\n\\end{table}/0/1");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex12Menu->addAction(Act);
Act = new QAction("\\begin{figure}  [selection]", this);
Act->setData("\\begin{figure}\n/\n\\caption{}\n\\end{figure}/0/1");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex12Menu->addAction(Act);
Act = new QAction("\\begin{titlepage}  [selection]", this);
Act->setData("\\begin{titlepage}\n/\n\\end{titlepage}/0/1");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex12Menu->addAction(Act);

latex13Menu=latex1Menu->addMenu(tr("&List Environment"));
Act = new QAction(QIcon(":/images/itemize.png"),"\\begin{itemize}", this);
Act->setData("\\begin{itemize}\n\\item \n\\end{itemize}/6/1/The itemize environment produces a 'bulleted' list.\nEach item of an itemized list begins with an \\item command.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex13Menu->addAction(Act);
Act = new QAction(QIcon(":/images/enumerate.png"),"\\begin{enumerate}", this);
Act->setData("\\begin{enumerate}\n\\item \n\\end{enumerate}/6/1/The enumerate environment produces a numbered list.\nEach item of an enumerated list begins with an \\item command.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex13Menu->addAction(Act);
Act = new QAction("\\begin{description}", this);
Act->setData("\\begin{description}\n\\item[]\n\\end{description}/6/1/The description environment is used to make labelled lists.\nEach item of the list begins with an \\item[label] command.\n");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex13Menu->addAction(Act);
Act = new QAction("\\begin{list}", this);
Act->setData("\\begin{list}{}{}\n\\item \n\\end{list}/13/0/\\begin{list}{label}{spacing}\nThe {label} argument is a piece of text that is inserted in a box to form the label.\nThe {spacing} argument contains commands to change the spacing parameters for the list.\nEach item of the list begins with an \\item command.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex13Menu->addAction(Act);

Act = new QAction(QIcon(":/images/item.png"),"\\item", this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_I);
Act->setData("\\item/5/0/\\item[label] Hello");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex13Menu->addAction(Act);

latex14Menu=latex1Menu->addMenu(tr("Font St&yles"));
Act = new QAction(QIcon(":/images/text_italic.png"),"\\textit - Italics  [selection]", this);
Act->setShortcut(Qt::CTRL+Qt::Key_I);
Act->setData("\\textit{/}/8/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex14Menu->addAction(Act);
Act = new QAction("\\textsl - Slanted  [selection]", this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_S);
Act->setData("\\textsl{/}/8/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex14Menu->addAction(Act);
Act = new QAction(QIcon(":/images/text_bold.png"),"\\textbf - Boldface  [selection]", this);
Act->setShortcut(Qt::CTRL+Qt::Key_B);
Act->setData("\\textbf{/}/8/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex14Menu->addAction(Act);
Act = new QAction("\\texttt - Typewriter  [selection]", this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_T);
Act->setData("\\texttt{/}/8/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex14Menu->addAction(Act);
Act = new QAction("\\textsc - Small caps  [selection]", this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_C);
Act->setData("\\textsc{/}/8/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex14Menu->addAction(Act);
Act = new QAction("\\emph - Emphasis  [selection]", this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_E);
Act->setData("\\emph{/}/6/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
latex14Menu->addAction(Act);

latex15Menu=latex1Menu->addMenu(tr("&Tabular Environment"));
Act = new QAction("\\begin{tabbing}", this);
Act->setData("\\begin{tabbing}\n\n\\end{tabbing}/0/1/\\begin{tabbing}\ntext \\= more text \\= still more text \\= last text \\\\\nsecond row \\>  \\> more \\\\\n\\end{tabbing}");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex15Menu->addAction(Act);
Act = new QAction("\\begin{tabular}", this);
Act->setData("\\begin{tabular}{}\n\n\\end{tabular}/16/0/\\begin{tabular}[pos]{cols}\ncolumn 1 entry & column 2 entry ... & column n entry \\\\\n...\n\\end{tabular}");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex15Menu->addAction(Act);
Act = new QAction("\\multicolumn", this);
Act->setData("\\multicolumn{}{}{} /13/0/\\multicolumn{cols}{pos}{text}\ncol, specifies the number of columns to span.\npos specifies the formatting of the entry: c for centred, l for flushleft, r for flushright.\ntext specifies what text is to make up the entry.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex15Menu->addAction(Act);
Act = new QAction("\\hline", this);
Act->setData("\\hline /7/0/The \\hline command draws a horizontal line the width of the table.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex15Menu->addAction(Act);
Act = new QAction("\\vline", this);
Act->setData("\\vline /7/0/The \\vline command draws a vertical line extending the full height and depth of its row.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex15Menu->addAction(Act);
Act = new QAction("\\cline", this);
Act->setData("\\cline{-} /7/0/The \\cline{i-j} command draws horizontal lines across the columns specified, beginning in column i and ending in column j");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex15Menu->addAction(Act);

latex16Menu=latex1Menu->addMenu(tr("S&pacing"));
Act = new QAction("\\newpage", this);
Act->setData("\\newpage /9/0/The \\newpage command ends the current page");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex16Menu->addAction(Act);
Act = new QAction("\\linebreak", this);
Act->setData("\\linebreak /11/0/The \\linebreak command tells LaTeX to break the current line at the point of the command.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex16Menu->addAction(Act);
Act = new QAction("\\pagebreak", this);
Act->setData("\\pagebreak /11/0/The \\pagebreak command tells LaTeX to break the current page at the point of the command.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex16Menu->addAction(Act);
Act = new QAction("\\bigskip", this);
Act->setData("\\bigskip /9/0/The \\bigskip command adds a 'big' vertical space.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex16Menu->addAction(Act);
Act = new QAction("\\medskip", this);
Act->setData("\\medskip /9/0/The \\medskip command adds a 'medium' vertical space.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex16Menu->addAction(Act);
Act = new QAction(QIcon(":/images/newline.png"),"New line", this);
Act->setData("\\\\\n/0/1/The \\newline command breaks the line right where it is.");
Act->setShortcut(Qt::CTRL+Qt::Key_Return);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex16Menu->addAction(Act);

latex17Menu=latex1Menu->addMenu(tr("International &Accents"));
Act = new QAction(QIcon(":/images/accent1.png"),"\\'{}", this);
Act->setData("\\'{}/3/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex17Menu->addAction(Act);
Act = new QAction(QIcon(":/images/accent2.png"),"\\`{}", this);
Act->setData("\\`{}/3/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex17Menu->addAction(Act);
Act = new QAction(QIcon(":/images/accent3.png"),"\\^{}", this);
Act->setData("\\^{}/3/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex17Menu->addAction(Act);
Act = new QAction(QIcon(":/images/accent4.png"),"\\\"{}", this);
Act->setData("\\\"{}/3/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex17Menu->addAction(Act);
Act = new QAction(QIcon(":/images/accent5.png"),"\\~{}", this);
Act->setData("\\~{}/3/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex17Menu->addAction(Act);
Act = new QAction(QIcon(":/images/accent6.png"),"\\={}", this);
Act->setData("\\={}/3/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex17Menu->addAction(Act);
Act = new QAction(QIcon(":/images/accent7.png"),"\\.{}", this);
Act->setData("\\.{}/3/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex17Menu->addAction(Act);
Act = new QAction(QIcon(":/images/accent8.png"),"\\v{}", this);
Act->setData("\\v{}/3/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex17Menu->addAction(Act);
Act = new QAction(QIcon(":/images/accent9.png"),"\\u{}", this);
Act->setData("\\u{}/3/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex17Menu->addAction(Act);
Act = new QAction(QIcon(":/images/accent10.png"),"\\H{}", this);
Act->setData("\\H{}/3/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex17Menu->addAction(Act);

Act = new QAction("\\includegraphics{file}", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertImage()));
latex1Menu->addAction(Act);
Act = new QAction("\\include{file}", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertInclude()));
latex1Menu->addAction(Act);
Act = new QAction("\\input{file}", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertInput()));
latex1Menu->addAction(Act);
latex1Menu->addSeparator();

Act = new QAction("\\label{}", this);
Act->setData("\\label{} /7/0/\\label{key}");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex1Menu->addAction(Act);
Act = new QAction("\\cite{}", this);
Act->setData("\\cite{} /6/0/\\cite{ref} :\nThis command generates an in-text citation to the reference associated with the ref entry in the bib file");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex1Menu->addAction(Act);
Act = new QAction("\\footnote{}", this);
Act->setData("\\footnote{} /10/0/\\footnote[number]{text}\nThe \\footnote command places the numbered footnote text at the bottom of the current page.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex1Menu->addAction(Act);
Act = new QAction("\\bibliographystyle{}", this);
Act->setData("\\bibliographystyle{} /19/0/The argument to \\bibliographystyle refers to a file style.bst, which defines how your citations will look");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
latex1Menu->addAction(Act);
Act = new QAction("\\bibliography{}", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib()));
latex1Menu->addAction(Act);

math1Menu = menuBar()->addMenu(tr("&Math"));
Act = new QAction(QIcon(":/images/mathmode.png"),tr("Inline math mode $...$"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_M);
Act->setData("$  $/2/0/The math environment can be used in both paragraph and LR mode");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math1Menu->addAction(Act);
Act = new QAction(tr("Display math mode \\[...\\]"), this);
Act->setShortcut(Qt::ALT+Qt::SHIFT+Qt::Key_M);
Act->setData("\\[  \\]/3/0/The displaymath environment can be used only in paragraph mode");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math1Menu->addAction(Act);
Act = new QAction(tr("Numbered equations \\begin{equation}"), this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_N);
Act->setData("\\begin{equation}\n\n\\end{equation}/0/1/The equation environment centres your equation on the page and places the equation number in the right margin.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math1Menu->addAction(Act);
Act = new QAction("\\begin{eqnarray}", this);
Act->setData("\\begin{eqnarray}\n\n\\end{eqnarray}/0/1/\\begin{eqnarray}\nmath formula 1 \\\\\n\\end{eqnarray}\nThe eqnarray environment is used to display a sequence of equations or inequalities.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math1Menu->addAction(Act);
Act = new QAction(QIcon(":/images/indice.png"),"_{} - subscript", this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_D);
Act->setData("_{}/2/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math1Menu->addAction(Act);
Act = new QAction(QIcon(":/images/puissance.png"),"^{} - superscript", this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_U);
Act->setData("^{}/2/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math1Menu->addAction(Act);
Act = new QAction(QIcon(":/images/smallfrac.png"),"\\frac{}{}", this);
Act->setShortcut(Qt::ALT+Qt::SHIFT+Qt::Key_F);
Act->setData("\\frac{}{}/6/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math1Menu->addAction(Act);
Act = new QAction(QIcon(":/images/dfrac.png"),"\\dfrac{}{}", this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_F);
Act->setData("\\dfrac{}{}/7/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math1Menu->addAction(Act);
Act = new QAction(QIcon(":/images/racine.png"),"\\sqrt{}", this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_Q); //setShortcut(Qt::CTRL+Qt::ALT+Qt::Key_Q);
Act->setData("\\sqrt{}/6/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math1Menu->addAction(Act);
Act = new QAction("\\left", this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_L);
Act->setData("\\left /6/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math1Menu->addAction(Act);
Act = new QAction("\\right", this);
Act->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_R);
Act->setData("\\right /7/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math1Menu->addAction(Act);
Act = new QAction("\\begin{array}", this);
Act->setData("\\begin{array}{}\n\n\\end{array}/14/0/\\begin{array}{col1col2...coln}\ncolumn 1 entry & column 2 entry ... & column n entry \\\\\n...\n\\end{array}");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math1Menu->addAction(Act);

math14Menu=math1Menu->addMenu(tr("Math &Functions"));
Act = new QAction("\\arccos", this);
Act->setData("\\arccos /8/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\arcsin", this);
Act->setData("\\arcsin /8/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\arctan", this);
Act->setData("\\arctan /8/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\cos", this);
Act->setData("\\cos /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\cosh", this);
Act->setData("\\cosh /6/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\cot", this);
Act->setData("\\cot /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\coth", this);
Act->setData("\\coth /6/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\csc", this);
Act->setData("\\csc /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\deg", this);
Act->setData("\\deg /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\det", this);
Act->setData("\\det /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\dim", this);
Act->setData("\\dim /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\exp", this);
Act->setData("\\exp /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\gcd", this);
Act->setData("\\gcd /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\hom", this);
Act->setData("\\hom /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\inf", this);
Act->setData("\\inf /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\ker", this);
Act->setData("\\ker /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\lg", this);
Act->setData("\\lg /4/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\lim", this);
Act->setData("\\lim /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\liminf", this);
Act->setData("\\liminf /8/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\limsup", this);
Act->setData("\\limsup /8/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\ln", this);
Act->setData("\\ln /4/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\log", this);
Act->setData("\\log /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\max", this);
Act->setData("\\max /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\min", this);
Act->setData("\\min /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\sec", this);
Act->setData("\\sec /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\sin", this);
Act->setData("\\sin /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\sinh", this);
Act->setData("\\sinh /6/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\sup", this);
Act->setData("\\sup /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\tan", this);
Act->setData("\\tan /5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);
Act = new QAction("\\tanh", this);
Act->setData("\\tanh /6/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math14Menu->addAction(Act);

math11Menu=math1Menu->addMenu(tr("Math Font St&yles"));
Act = new QAction("\\mathrm{}  [selection]", this);
Act->setData("\\mathrm{/}/8/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
math11Menu->addAction(Act);
Act = new QAction("\\mathit{}  [selection]", this);
Act->setData("\\mathit{/}/8/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
math11Menu->addAction(Act);
Act = new QAction("\\mathbf{}  [selection]", this);
Act->setData("\\mathbf{/}/8/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
math11Menu->addAction(Act);
Act = new QAction("\\mathsf{}  [selection]", this);
Act->setData("\\mathsf{/}/8/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
math11Menu->addAction(Act);
Act = new QAction("\\mathtt{}  [selection]", this);
Act->setData("\\mathtt{/}/8/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
math11Menu->addAction(Act);
Act = new QAction("\\mathcal{}  [selection]", this);
Act->setData("\\mathcal{/}/9/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
math11Menu->addAction(Act);
Act = new QAction("\\mathbb{}  [selection]", this);
Act->setData("\\mathbb{/}/8/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
math11Menu->addAction(Act);
Act = new QAction("\\mathfrak{}  [selection]", this);
Act->setData("\\mathfrak{/}/10/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
math11Menu->addAction(Act);

math12Menu=math1Menu->addMenu(tr("Math &Accents"));
Act = new QAction(QIcon(":/images/acute.png"),"\\acute{}", this);
Act->setData("\\acute{}/7/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math12Menu->addAction(Act);
Act = new QAction(QIcon(":/images/grave.png"),"\\grave{}", this);
Act->setData("\\grave{}/7/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math12Menu->addAction(Act);
Act = new QAction(QIcon(":/images/tilde.png"),"\\tilde{}", this);
Act->setData("\\tilde{}/7/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math12Menu->addAction(Act);
Act = new QAction(QIcon(":/images/bar.png"),"\\bar{}", this);
Act->setData("\\bar{}/5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math12Menu->addAction(Act);
Act = new QAction(QIcon(":/images/vec.png"),"\\vec{}", this);
Act->setData("\\vec{}/5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math12Menu->addAction(Act);
Act = new QAction(QIcon(":/images/hat.png"),"\\hat{}", this);
Act->setData("\\hat{}/5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math12Menu->addAction(Act);
Act = new QAction(QIcon(":/images/check.png"),"\\check{}", this);
Act->setData("\\check{}/7/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math12Menu->addAction(Act);
Act = new QAction(QIcon(":/images/breve.png"),"\\breve{}", this);
Act->setData("\\breve{}/7/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math12Menu->addAction(Act);
Act = new QAction(QIcon(":/images/dot.png"),"\\dot{}", this);
Act->setData("\\dot{}/5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math12Menu->addAction(Act);
Act = new QAction(QIcon(":/images/ddtot.png"),"\\ddot{}", this);
Act->setData("\\ddot{}/6/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math12Menu->addAction(Act);

math13Menu=math1Menu->addMenu(tr("Math S&paces"));
Act = new QAction("small", this);
Act->setData("\\,/2/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math13Menu->addAction(Act);
Act = new QAction("medium", this);
Act->setData("\\:/2/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math13Menu->addAction(Act);
Act = new QAction("large", this);
Act->setData("\\;/2/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math13Menu->addAction(Act);
Act = new QAction("\\quad", this);
Act->setData("\\quad/5/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math13Menu->addAction(Act);
Act = new QAction("\\qquad", this);
Act->setData("\\qquad/6/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
math13Menu->addAction(Act);

wizardMenu = menuBar()->addMenu(tr("&Wizard"));
Act = new QAction(tr("Quick Start"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(QuickDocument()));
wizardMenu->addAction(Act);
Act = new QAction(tr("Quick Letter"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(QuickLetter()));
wizardMenu->addAction(Act);
wizardMenu->addSeparator();
Act = new QAction(tr("Quick Tabular"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(QuickTabular()));
wizardMenu->addAction(Act);
Act = new QAction(tr("Quick Tabbing"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(QuickTabbing()));
wizardMenu->addAction(Act);
Act = new QAction(tr("Quick Array"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(QuickArray()));
wizardMenu->addAction(Act);

bibMenu = menuBar()->addMenu(tr("&Bibliography"));
Act = new QAction("Article in Journal", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib1()));
bibMenu->addAction(Act);
Act = new QAction("Article in Conference Proceedings", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib2()));
bibMenu->addAction(Act);
Act = new QAction("Article in a collection", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib3()));
bibMenu->addAction(Act);
Act = new QAction("Chapter or Pages in a Book", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib4()));
bibMenu->addAction(Act);
Act = new QAction("Conference Proceedings", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib5()));
bibMenu->addAction(Act);
Act = new QAction("Book", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib6()));
bibMenu->addAction(Act);
Act = new QAction("Booklet", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib7()));
bibMenu->addAction(Act);
Act = new QAction("PhD. Thesis", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib8()));
bibMenu->addAction(Act);
Act = new QAction("Master's Thesis", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib9()));
bibMenu->addAction(Act);
Act = new QAction("Technical Report", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib10()));
bibMenu->addAction(Act);
Act = new QAction("Technical Manual", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib11()));
bibMenu->addAction(Act);
Act = new QAction("Unpublished", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib12()));
bibMenu->addAction(Act);
Act = new QAction("Miscellaneous", this);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertBib13()));
bibMenu->addAction(Act);
bibMenu->addSeparator();
Act = new QAction(tr("Clean"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(CleanBib()));
bibMenu->addAction(Act);

user1Menu = menuBar()->addMenu(tr("&User"));
user11Menu=user1Menu->addMenu(tr("User &Tags"));
Act = new QAction("1: "+UserMenuName[0], this);
Act->setShortcut(Qt::SHIFT+Qt::Key_F1);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag1()));
user11Menu->addAction(Act);
Act = new QAction("2: "+UserMenuName[1], this);
Act->setShortcut(Qt::SHIFT+Qt::Key_F2);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag2()));
user11Menu->addAction(Act);
Act = new QAction("3: "+UserMenuName[2], this);
Act->setShortcut(Qt::SHIFT+Qt::Key_F3);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag3()));
user11Menu->addAction(Act);
Act = new QAction("4: "+UserMenuName[3], this);
Act->setShortcut(Qt::SHIFT+Qt::Key_F4);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag4()));
user11Menu->addAction(Act);
Act = new QAction("5: "+UserMenuName[4], this);
Act->setShortcut(Qt::SHIFT+Qt::Key_F5);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag5()));
user11Menu->addAction(Act);
Act = new QAction("6: "+UserMenuName[5], this);
Act->setShortcut(Qt::SHIFT+Qt::Key_F6);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag6()));
user11Menu->addAction(Act);
Act = new QAction("7: "+UserMenuName[6], this);
Act->setShortcut(Qt::SHIFT+Qt::Key_F7);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag7()));
user11Menu->addAction(Act);
Act = new QAction("8: "+UserMenuName[7], this);
Act->setShortcut(Qt::SHIFT+Qt::Key_F8);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag8()));
user11Menu->addAction(Act);
Act = new QAction("9: "+UserMenuName[8], this);
Act->setShortcut(Qt::SHIFT+Qt::Key_F9);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag9()));
user11Menu->addAction(Act);
Act = new QAction("10: "+UserMenuName[9], this);
Act->setShortcut(Qt::SHIFT+Qt::Key_F10);
connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag10()));
user11Menu->addAction(Act);
user11Menu->addSeparator();
Act = new QAction(tr("Edit User &Tags"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(EditUserMenu()));
user11Menu->addAction(Act);
user12Menu=user1Menu->addMenu(tr("User &Commands"));
Act = new QAction("1: "+UserToolName[0], this);
Act->setShortcut(Qt::SHIFT+Qt::ALT+Qt::Key_F1);
connect(Act, SIGNAL(triggered()), this, SLOT(UserTool1()));
user12Menu->addAction(Act);
Act = new QAction("2: "+UserToolName[1], this);
Act->setShortcut(Qt::SHIFT+Qt::ALT+Qt::Key_F2);
connect(Act, SIGNAL(triggered()), this, SLOT(UserTool2()));
user12Menu->addAction(Act);
Act = new QAction("3: "+UserToolName[2], this);
Act->setShortcut(Qt::SHIFT+Qt::ALT+Qt::Key_F3);
connect(Act, SIGNAL(triggered()), this, SLOT(UserTool3()));
user12Menu->addAction(Act);
Act = new QAction("4: "+UserToolName[3], this);
Act->setShortcut(Qt::SHIFT+Qt::ALT+Qt::Key_F4);
connect(Act, SIGNAL(triggered()), this, SLOT(UserTool4()));
user12Menu->addAction(Act);
Act = new QAction("5: "+UserToolName[4], this);
Act->setShortcut(Qt::SHIFT+Qt::ALT+Qt::Key_F5);
connect(Act, SIGNAL(triggered()), this, SLOT(UserTool5()));
user12Menu->addAction(Act);
user12Menu->addSeparator();
Act = new QAction(tr("Edit User &Commands"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(EditUserTool()));
user12Menu->addAction(Act);
Act = new QAction(tr("Edit User &Key Replacements..."), this);
connect(Act, SIGNAL(triggered()), this, SLOT(EditUserKeyReplacements()));
user1Menu->addAction(Act);


viewMenu = menuBar()->addMenu(tr("&View"));
Act = new QAction(tr("Next Document"), this);
Act->setShortcut(Qt::ALT+Qt::Key_PageUp);
connect(Act, SIGNAL(triggered()), this, SLOT(gotoNextDocument()));
viewMenu->addAction(Act);
Act = new QAction(tr("Previous Document"), this);
Act->setShortcut(Qt::ALT+Qt::Key_PageDown);
connect(Act, SIGNAL(triggered()), this, SLOT(gotoPrevDocument()));
viewMenu->addAction(Act);
viewMenu->addSeparator();
viewMenu->addAction(StructureView->toggleViewAction());
viewMenu->addAction(OutputView->toggleViewAction());

optionsMenu = menuBar()->addMenu(tr("&Options"));
Act = new QAction(QIcon(":/images/configure.png"), tr("Configure TexMakerX"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(GeneralOptions()));
optionsMenu->addAction(Act);
optionsMenu->addSeparator();
#if defined( Q_WS_X11 )
Act = new QAction(QIcon(":/images/configure.png"), tr("Change Interface Font"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(SetInterfaceFont()));
optionsMenu->addAction(Act);
Act = new QAction(QIcon(":/images/configure.png"), tr("Change Interface Type"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(SetInterfaceType()));
optionsMenu->addAction(Act);
optionsMenu->addSeparator();
#endif
ToggleAct = new QAction(tr("Define Current Document as 'Master Document'"), this);
connect(ToggleAct, SIGNAL(triggered()), this, SLOT(ToggleMode()));
optionsMenu->addAction(ToggleAct);

helpMenu = menuBar()->addMenu(tr("&Help"));
Act = new QAction(QIcon(":/images/help.png"), tr("LaTeX Reference"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(LatexHelp()));
helpMenu->addAction(Act);
Act = new QAction(QIcon(":/images/help.png"), tr("User Manual"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(UserManualHelp()));
helpMenu->addAction(Act);
helpMenu->addSeparator();
Act = new QAction(QIcon(":/images/appicon.png"), tr("About TexMakerX"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(HelpAbout()));
helpMenu->addAction(Act);

QList<QAction *> listaction;
if (shortcuts.isEmpty())
	{
	actionstext.clear();
	listaction << latex11Menu->actions();
	listaction << latex12Menu->actions();
	listaction << latex13Menu->actions();
	listaction << latex14Menu->actions();
	listaction << latex15Menu->actions();
	listaction << latex16Menu->actions();
	listaction << latex17Menu->actions();
	listaction << math1Menu->actions();
	listaction << math11Menu->actions();
	listaction << math12Menu->actions();
	listaction << math13Menu->actions();
	listaction << math14Menu->actions();
	QListIterator<QAction*> iterator(listaction);
	while ( iterator.hasNext() )
		{
		QAction *action = iterator.next();
		if (action && (!action->menu()) && (!action->data().toString().isEmpty()))
			{
			if (action->shortcut().isEmpty()) shortcuts.insert(action->data().toString(),"none");
			else shortcuts.insert(action->data().toString(),action->shortcut());
			actionstext.insert(action->data().toString(),action->text());
			}
		}
	}
else ModifyShortcuts();
}

void Texmaker::setupToolBars()
{
QAction *Act;
QStringList list;
//file
fileToolBar = addToolBar("File");
fileToolBar->setObjectName("File");

Act = new QAction(QIcon(":/images/filenew.png"), tr("New"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(fileNew()));
fileToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/fileopen.png"), tr("Open"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(fileOpen()));
fileToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/filesave.png"), tr("Save"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(fileSave()));
fileToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/fileclose.png"), tr("Close"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(fileClose()));
fileToolBar->addAction(Act);

//edit
editToolBar = addToolBar("Edit");
editToolBar->setObjectName("Edit");

Act = new QAction(QIcon(":/images/undo.png"), tr("Undo"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(editUndo()));
editToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/redo.png"), tr("Redo"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(editRedo()));
editToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/editcopy.png"), tr("Copy"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(editCopy()));
editToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/editcut.png"), tr("Cut"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(editCut()));
editToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/editpaste.png"), tr("Paste"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(editPaste()));
editToolBar->addAction(Act);

//tools
runToolBar = addToolBar("Tools");
runToolBar->setObjectName("Tools");

Act = new QAction(QIcon(":/images/viewlog.png"),tr("View Log"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(ViewLog()));
runToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/errorprev.png"),tr("Previous LaTeX Error"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(PreviousError()));
runToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/errornext.png"),tr("Next LaTeX Error"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(NextError()));
runToolBar->addAction(Act);
runToolBar->addSeparator();

Act = new QAction(QIcon(":/images/quick.png"),tr("Quick Build"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(QuickBuild()));
runToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/latex.png"),"LaTeX", this);
connect(Act, SIGNAL(triggered()), this, SLOT(Latex()));
runToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/viewdvi.png"),tr("View Dvi"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(ViewDvi()));
runToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/dvips.png"),"Dvi->PS", this);
connect(Act, SIGNAL(triggered()), this, SLOT(DviToPS()));
runToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/viewps.png"),tr("View PS"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(ViewPS()));
runToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/pdflatex.png"),"PDFLaTeX", this);
connect(Act, SIGNAL(triggered()), this, SLOT(PDFLatex()));
runToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/viewpdf.png"),tr("View PDF"), this);
connect(Act, SIGNAL(triggered()), this, SLOT(ViewPDF()));
runToolBar->addAction(Act);

//format
formatToolBar = addToolBar("Format");
formatToolBar->setObjectName("Format");
insertToolBarBreak(formatToolBar);

list.clear();
list.append("part");
list.append("chapter");
list.append("section");
list.append("subsection");
list.append("subsubsection");
list.append("paragraph");
list.append("subparagraph");
QComboBox* combo1 = new QComboBox(formatToolBar);
combo1->addItems(list);
connect(combo1, SIGNAL(activated(const QString&)),this,SLOT(SectionCommand(const QString&)));
formatToolBar->addWidget(combo1);
formatToolBar->addSeparator();

list.clear();
list.append("label");
list.append("ref");
list.append("pageref");
list.append("index");
list.append("cite");
list.append("footnote");
QComboBox* combo2 = new QComboBox(formatToolBar);
combo2->addItems(list);
connect(combo2, SIGNAL(activated(const QString&)),this,SLOT(OtherCommand(const QString&)));
formatToolBar->addWidget(combo2);
formatToolBar->addSeparator();

list.clear();
list.append("tiny");
list.append("scriptsize");
list.append("footnotesize");
list.append("small");
list.append("normalsize");
list.append("large");
list.append("Large");
list.append("LARGE");
list.append("huge");
list.append("Huge");
QComboBox* combo3 = new QComboBox(formatToolBar);
combo3->addItems(list);
connect(combo3, SIGNAL(activated(const QString&)),this,SLOT(SizeCommand(const QString&)));
formatToolBar->addWidget(combo3);
formatToolBar->addSeparator();

Act = new QAction(QIcon(":/images/text_bold.png"),tr("Bold"), this);
Act->setData("\\textbf{/}/8/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
formatToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/text_italic.png"),tr("Italic"), this);
Act->setData("\\textit{/}/8/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
formatToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/text_under.png"),tr("Underline"), this);
Act->setData("\\underline{/}/11/0");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
formatToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/text_left.png"),tr("Left"), this);
Act->setData("\\begin{flushleft}\n/\n\\end{flushleft}/0/1");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
formatToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/text_center.png"),tr("Center"), this);
Act->setData("\\begin{center}\n/\n\\end{center}/0/1");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
formatToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/text_right.png"),tr("Right"), this);
Act->setData("\\begin{flushright}\n/\n\\end{flushright}/0/1");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertWithSelectionFromAction()));
formatToolBar->addAction(Act);
formatToolBar->addSeparator();

Act = new QAction(QIcon(":/images/newline.png"),tr("New line"), this);
Act->setData("\\\\\n/0/1/The \\newline command breaks the line right where it is. It can only be used in paragraph mode.");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
formatToolBar->addAction(Act);

//math
mathToolBar = addToolBar("Math");
mathToolBar->setObjectName("Math");

Act = new QAction(QIcon(":/images/mathmode.png"),"$...$", this);
Act->setData("$  $/2/0/The math environment can be used in both paragraph and LR mode");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
mathToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/indice.png"),"_{} - subscript", this);
Act->setData("_{}/2/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
mathToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/puissance.png"),"^{} - superscript", this);
Act->setData("^{}/2/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
mathToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/smallfrac.png"),"\\frac{}{}", this);
Act->setData("\\frac{}{}/6/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
mathToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/dfrac.png"),"\\dfrac{}{}", this);
Act->setData("\\dfrac{}{}/7/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
mathToolBar->addAction(Act);

Act = new QAction(QIcon(":/images/racine.png"),"\\sqrt{}", this);
Act->setData("\\sqrt{}/6/0/ ");
connect(Act, SIGNAL(triggered()), this, SLOT(InsertFromAction()));
mathToolBar->addAction(Act);
mathToolBar->addSeparator();

list.clear();
list.append("left (");
list.append("left [");
list.append("left {");
list.append("left <");
list.append("left )");
list.append("left ]");
list.append("left }");
list.append("left >");
list.append("left.");
QComboBox* combo4 = new QComboBox(mathToolBar);
combo4->addItems(list);
connect(combo4, SIGNAL(activated(const QString&)),this,SLOT(LeftDelimiter(const QString&)));
mathToolBar->addWidget(combo4);
mathToolBar->addSeparator();

list.clear();
list.append("right )");
list.append("right ]");
list.append("right }");
list.append("right >");
list.append("right (");
list.append("right [");
list.append("right {");
list.append("right <");
list.append("right.");
QComboBox* combo5 = new QComboBox(mathToolBar);
combo5->addItems(list);
connect(combo5, SIGNAL(activated(const QString&)),this,SLOT(RightDelimiter(const QString&)));
mathToolBar->addWidget(combo5);

}


void Texmaker::createStatusBar()
{
QStatusBar * status=statusBar();
stat1=new QLabel(status);
stat2=new QLabel( status );
stat3=new QLabel( status );
pb1=new QPushButton(QIcon(":/images/bookmark1.png"),"",status);
pb2=new QPushButton(QIcon(":/images/bookmark2.png"),"",status);
pb3=new QPushButton(QIcon(":/images/bookmark3.png"),"",status);
pb1->setToolTip(tr("Click to jump to the bookmark"));
pb2->setToolTip(tr("Click to jump to the bookmark"));
pb3->setToolTip(tr("Click to jump to the bookmark"));
connect (pb1,SIGNAL(clicked()),this,SLOT(gotoBookmark1()));
connect (pb2,SIGNAL(clicked()),this,SLOT(gotoBookmark2()));
connect (pb3,SIGNAL(clicked()),this,SLOT(gotoBookmark3()));
pb1->setMaximumSize(20,20);
pb2->setMaximumSize(20,20);
pb3->setMaximumSize(20,20);
pb1->setFlat(true);
pb2->setFlat(true);
pb3->setFlat(true);
status->addPermanentWidget(stat3,0);
status->addPermanentWidget(stat2,0);
status->addPermanentWidget(stat1,0);
status->addPermanentWidget(pb1,0);
status->addPermanentWidget(pb2,0);
status->addPermanentWidget(pb3,0);
}

void Texmaker::UpdateCaption()
{
QString title;
if   ( !currentEditorView() )	{title="TexMakerX";}
else
	{
	title="Document : "+getName();
	if (currentEditorView()->editor && currentEditorView()->editor->getFileEncoding()) stat3->setText(currentEditorView()->editor->getFileEncoding()->name());
	else stat3->setText("unknown");
	//input_encoding=currentEditorView()->editor->getEncoding();
	}
setWindowTitle(title);
UpdateStructure();
if (singlemode)
	{
	OutputTextEdit->clear();
	OutputTableWidget->hide();
	logpresent=false;
	}
QString finame=getName();
if (finame!="untitled" && finame!="") lastDocument=finame;
}

void Texmaker::NewDocumentStatus(bool m)
{
if ( !currentEditorView() )	return;
if (m)
	{
	EditorView->setTabIcon(EditorView->indexOf(currentEditorView()),QIcon(":/images/modified.png"));
	EditorView->setTabText(EditorView->indexOf(currentEditorView()),QFileInfo( getName() ).fileName());
	}
else
	{
	EditorView->setTabIcon(EditorView->indexOf(currentEditorView()),QIcon(":/images/empty.png"));
	EditorView->setTabText(EditorView->indexOf(currentEditorView()),QFileInfo( getName() ).fileName());
	}
}

LatexEditorView *Texmaker::currentEditorView() const
{
if ( EditorView->currentWidget() && EditorView->currentWidget()->inherits( "LatexEditorView" ) ) return (LatexEditorView*)EditorView->currentWidget();
return 0;
}

void Texmaker::configureNewEditorView(LatexEditorView *edit){
  m_languages->setLanguage(edit->codeeditor->editor(), ".tex");
  edit->editor->setCompletionEngine(completer->clone());
  EditorView->setCurrentIndex(EditorView->indexOf(edit));
  edit->changeSettings(EditorFont,showlinemultiples,folding,showlinestate,showcursorstate, wordwrap,completion);
  
  connect(edit->editor, SIGNAL(contentModified(bool)), this, SLOT(NewDocumentStatus(bool)));
    
//connect(edit->editor, SIGNAL(spellme()), this, SLOT(editSpell())); todo:benibela
}

QString Texmaker::getName()
{
QString title;
if ( !currentEditorView() )	{title="";}
else {title=filenames[currentEditorView()];}
return title;
}

bool Texmaker::FileAlreadyOpen(QString f)
{
bool rep=false;
FilesMap::Iterator it;
QString fw32,funix,forig;
for( it = filenames.begin(); it != filenames.end(); ++it )
	{
	forig=filenames[it.key()];
	fw32=filenames[it.key()];
	funix=filenames[it.key()];
	fw32.replace(QString("\\"),QString("/"));
	funix.replace(QString("/"),QString("\\"));
	if ( (forig==f) || (fw32==f) || (funix==f)) 
		{
		EditorView->setCurrentIndex(EditorView->indexOf(it.key()));
		rep=true;
		}
	}
return rep;
}
///////////////////FILE//////////////////////////////////////


void Texmaker::load( const QString &f )
{
raise();
if (FileAlreadyOpen(f) || !QFile::exists( f )) return;
LatexEditorView *edit = new LatexEditorView(0);
EditorView->addTab( edit, QFileInfo( f ).fileName() );
configureNewEditorView(edit);

QFile file( f );
if ( !file.open( QIODevice::ReadOnly ) )
	{
	QMessageBox::warning( this,tr("Error"), tr("You do not have read permission to this file."));
	return;
	}

if (autodetectLoadedFile) edit->editor->load(f,0);
else edit->editor->load(f,newfile_encoding);

//filenames.replace( edit, f );
filenames.remove( edit);
filenames.insert( edit, f );
edit->editor->setFocus();
UpdateCaption();
NewDocumentStatus(false);
AddRecentFile(f);
ShowStructure();
}

void Texmaker::setLine( const QString &line )
{
bool ok;
int l=line.toInt(&ok,10);
if (currentEditorView() && ok)
	{
	    currentEditorView()->editor->setCursorPosition(l,1);
	    currentEditorView()->editor->ensureCursorVisible();
	    currentEditorView()->editor->setFocus();
	}
}


void Texmaker::fileNew()
{
LatexEditorView *edit = new LatexEditorView(0);
if (newfile_encoding) edit->editor->setFileEncoding(newfile_encoding);
else edit->editor->setFileEncoding(QTextCodec::codecForName("utf-8"));
EditorView->addTab( edit, "untitled");
configureNewEditorView(edit);
//filenames.replace( edit, "untitled" );
filenames.remove( edit);
filenames.insert( edit, "untitled" );
UpdateCaption();
NewDocumentStatus(false);
edit->editor->setFocus();
}

void Texmaker::fileOpen()
{
QString currentDir=QDir::homePath();
if (!lastDocument.isEmpty())
	{
	QFileInfo fi(lastDocument);
	if (fi.exists() && fi.isReadable()) currentDir=fi.absolutePath();
	}
QString fn = QFileDialog::getOpenFileName(this,tr("Open File"),currentDir,"TeX files (*.tex *.bib *.sty *.cls *.mp);;All files (*.*)");
if ( !fn.isEmpty() ) load( fn );
}

void Texmaker::fileSave()
{
if ( !currentEditorView() )	return;
QString fn;
if ( getName()=="untitled" ) {fileSaveAs();}
else
	{
	QFile file( *filenames.find( currentEditorView() ) );
	if ( !file.open( QIODevice::WriteOnly ) )
		{
		QMessageBox::warning( this,tr("Error"),tr("The file could not be saved. Please check if you have write permission."));
		return;
		}
    currentEditorView()->editor->save();
	//currentEditorView()->editor->setModified(false);
	fn=getName();
	AddRecentFile(fn);
	}
UpdateCaption();
}

void Texmaker::fileSaveAs()
{
if ( !currentEditorView() ) 	return;
QString currentDir=QDir::homePath();
if (!lastDocument.isEmpty())
	{
	QFileInfo fi(lastDocument);
	if (fi.exists() && fi.isReadable()) currentDir=fi.absolutePath();
	}
QString fn = QFileDialog::getSaveFileName(this,tr("Save As"),currentDir,"TeX files (*.tex *.bib *.sty *.cls *.mp);;All files (*.*)");
if ( !fn.isEmpty() )
	{
	QFileInfo fic(fn);
	currentEditorView()->editor->setFileName(fn);
	filenames.remove(currentEditorView());
	filenames.insert(currentEditorView(), fn );
	//filenames.replace( currentEditorView(), fn );
	fileSave();
	EditorView->setTabText(EditorView->indexOf(currentEditorView()),fic.fileName());
	}
UpdateCaption();
}

void Texmaker::fileSaveAll()
{
//LatexEditorView *temp = new LatexEditorView(EditorView,colorMath,colorCommand,colorKeyword);
//temp=currentEditorView();
int currentIndex=EditorView->indexOf(currentEditorView());
FilesMap::Iterator it;
for( it = filenames.begin(); it != filenames.end(); ++it )
	{
	EditorView->setCurrentIndex(EditorView->indexOf(it.key()));
	fileSave();
	}
EditorView->setCurrentIndex(currentIndex);
UpdateCaption();
}

void Texmaker::fileClose()
{
if ( !currentEditorView() )	return;
if (currentEditorView()->editor->isContentModified())
	{
	switch(  QMessageBox::warning(this, "TexMakerX",
					tr("The document contains unsaved work. "
					"Do you want to save it before closing?"),
					tr("Save and Close"), tr("Don't Save and Close"), tr("Cancel"),
					0,
					2 ) )
		{
		case 0:
			fileSave();
		filenames.remove(currentEditorView());
			delete currentEditorView();
			break;
		case 1:
		filenames.remove(currentEditorView());
			delete currentEditorView();
			break;
		case 2:
		default:
			return;
			break;
		}
	}
else
{
filenames.remove(currentEditorView());
delete currentEditorView();
}
UpdateCaption();
}

void Texmaker::fileCloseAll()
{
bool go=true;
while (currentEditorView() && go)
	{
	if (currentEditorView()->editor->isContentModified())
		{
		switch(  QMessageBox::warning(this, "TexMakerX",
						tr("The document contains unsaved work. "
						"Do you want to save it before exiting?"),
						tr("Save and Close"), tr("Don't Save and Close"), tr("Cancel"),
						0,
						2 ) )
			{
			case 0:
			fileSave();
			filenames.remove(currentEditorView());
			delete currentEditorView();
			break;
			case 1:
			filenames.remove(currentEditorView());
			delete currentEditorView();
			break;
			case 2:
			default:
			go=false;
			return;
			break;
			}
		}
	else
		{
		filenames.remove(currentEditorView());
		delete currentEditorView();
		}
	}
UpdateCaption();
}

void Texmaker::fileExit()
{
SaveSettings();
bool accept=true;
while (currentEditorView() && accept)
	{
	if (currentEditorView()->editor->isContentModified())
		{
		switch(  QMessageBox::warning(this, "TexMakerX",
						tr("The document contains unsaved work. "
						"Do you want to save it before exiting?"),
						tr("Save and Close"), tr("Don't Save and Close"),tr( "Cancel"),
						0,
						2 ) )
			{
			case 0:
				fileSave();
			filenames.remove(currentEditorView());
				delete currentEditorView();
				break;
			case 1:
			filenames.remove(currentEditorView());
				delete currentEditorView();
				break;
			case 2:
			default:
				accept=false;
				break;
			}

		}
	else
		{
		filenames.remove(currentEditorView());
		delete currentEditorView();
		}
	}
if (accept) qApp->quit();
}

void Texmaker::closeEvent(QCloseEvent *e)
{
SaveSettings();
bool accept=true;
while (currentEditorView() && accept)
	{
	if (currentEditorView()->editor->isContentModified())
		{
		switch(  QMessageBox::warning(this, "TexMakerX",
						tr("The document contains unsaved work. "
						"Do you want to save it before exiting?"),
						tr("Save and Close"), tr("Don't Save and Close"), tr("Cancel"),
						0,
						2 ) )
			{
			case 0:
				fileSave();
			filenames.remove(currentEditorView());
				delete currentEditorView();
				break;
			case 1:
			filenames.remove(currentEditorView());
				delete currentEditorView();
				break;
			case 2:
			default:
				accept=false;
				break;
			}
		}
	else
		{
		filenames.remove(currentEditorView());
		delete currentEditorView();
		}
	}
if (accept)  {
    e->accept();
    delete mainSpeller; //this saves the ignore list
} else e->ignore();
}


void Texmaker::fileOpenRecent()
{
QAction *action = qobject_cast<QAction *>(sender());
if (action) load(action->data().toString());
}

void Texmaker::AddRecentFile(const QString &f)
{
if (recentFilesList.contains(f)) return;

if (recentFilesList.count() < 5) recentFilesList.prepend(f);
else
	{
	recentFilesList.removeLast();
	recentFilesList.prepend(f);
	}
UpdateRecentFile();
}

void Texmaker::UpdateRecentFile()
{
for (int i=0; i < recentFilesList.count(); i++)
	{
        recentFileActs[i]->setText(recentFilesList.at(i));
        recentFileActs[i]->setData(recentFilesList.at(i));
        recentFileActs[i]->setVisible(true);
	}
for (int j = recentFilesList.count(); j < 5; ++j) recentFileActs[j]->setVisible(false);
}

void Texmaker::filePrint()
{
if ( !currentEditorView() ) return;
QTextDocument *document = new QTextDocument(currentEditorView()->editor->text());
QPrinter printer;
QPrintDialog *dlg = new QPrintDialog(&printer, this);
if (dlg->exec() != QDialog::Accepted) return;
document->print(&printer);
}
//////////////////////////// EDIT ///////////////////////
void Texmaker::editUndo()
{
if ( !currentEditorView() ) return;
currentEditorView()->editor->undo();
}

void Texmaker::editRedo()
{
if ( !currentEditorView() ) return;
currentEditorView()->editor->redo();
}

void Texmaker::editCut()
{
if ( !currentEditorView() ) return;
currentEditorView()->editor->cut();
}

void Texmaker::editCopy()
{
if ( !currentEditorView() ) return;
currentEditorView()->editor->copy();
}

void Texmaker::editPaste()
{
if ( !currentEditorView() ) return;
currentEditorView()->editor->paste();
}

void Texmaker::editSelectAll()
{
if ( !currentEditorView() ) return;
currentEditorView()->editor->selectAll();
}

void Texmaker::editFind()
{
if ( !currentEditorView() )	return;
currentEditorView()->editor->find();
}

void Texmaker::editFindNext()
{
if ( !currentEditorView() )	return;
currentEditorView()->editor->findNext();
}


void Texmaker::editReplace()
{
if ( !currentEditorView() )	return;
currentEditorView()->editor->replace();
}

void Texmaker::editGotoLine()
{
if ( !currentEditorView() )	return;
currentEditorView()->editor->gotoLine();
}

void Texmaker::editJumpToLastChange(){
    if ( !currentEditorView() )	return;
    currentEditorView()->jumpChangePositionBackward();
}
void Texmaker::editJumpToLastChangeForward(){
    if ( !currentEditorView() )	return;
    currentEditorView()->jumpChangePositionForward();
}

void Texmaker::editComment()
{
if ( !currentEditorView() )	return;
currentEditorView()->editor->commentSelection();
}

void Texmaker::editUncomment()
{
if ( !currentEditorView() )	return;
currentEditorView()->editor->uncommentSelection();
}

void Texmaker::editIndent()
{
if ( !currentEditorView() )	return;
currentEditorView()->editor->indentSelection();
}

void Texmaker::editUnindent()
{
if ( !currentEditorView() )	return;
currentEditorView()->editor->unindentSelection();
}

void Texmaker::editSpell()
{
    if (!currentEditorView()) return;
    if (!spellDlg) {
        spellDlg=new SpellerDialog(this,mainSpeller);
        spellDlg->setEditorView(currentEditorView());
    }
    spellDlg->startSpelling();
}

/////////////// CONFIG ////////////////////
void Texmaker::ReadSettings()
{
    bool usbMode = QFileInfo(QCoreApplication::applicationDirPath()+"/texmakerx.ini").exists() && QFileInfo(QCoreApplication::applicationDirPath()+"/texmakerx.ini").isWritable();
    if (!usbMode) 
        if (QFileInfo(QCoreApplication::applicationDirPath()+"/texmaker.ini").exists() && QFileInfo(QCoreApplication::applicationDirPath()+"/texmaker.ini").isWritable()) {
            //import texmaker usb settings
            usbMode=(QFile(QCoreApplication::applicationDirPath()+"/texmaker.ini")).copy(QCoreApplication::applicationDirPath()+"/texmakerx.ini");
        }
    QSettings *config;
    if (usbMode) {
        config=new QSettings(QCoreApplication::applicationDirPath()+"/texmakerx.ini",QSettings::IniFormat);
    } else {
        config=new QSettings(QSettings::IniFormat,QSettings::UserScope,"benibela","texmakerx");
        if (config->childGroups().empty()) {
            //import texmaker global settings
            QSettings oldconfig (QSettings::IniFormat,QSettings::UserScope,"xm1","texmaker");
            QStringList keys=oldconfig.allKeys();
            foreach (QString key, keys) config->setValue(key,oldconfig.value(key,""));
        }
    }
    configFileName=config->fileName();
    configFileNameBase=configFileName;
    if (configFileNameBase.endsWith(".ini")) configFileNameBase=configFileNameBase.replace(QString(".ini"),"");
    


config->beginGroup( "texmaker" );
singlemode=true;

QFontDatabase fdb;
QStringList xf = fdb.families();
QString deft;
// #ifdef Q_WS_X11
// x11style=config->value( "X11/Style","plastique").toString();
// if (xf.contains("DejaVu Sans",Qt::CaseInsensitive)) deft="DejaVu Sans";
// else if (xf.contains("Bitstream Vera Sans",Qt::CaseInsensitive)) deft="Bitstream Vera Sans";
// else if (xf.contains("Luxi Sans",Qt::CaseInsensitive)) deft="Luxi Sans";
// else deft=qApp->font().family();
// x11fontfamily=config->value("X11/Font Family",deft).toString();
// x11fontsize=config->value( "X11/Font Size","10").toInt();
//
// QStringList styles = QStyleFactory::keys();
// if (styles.contains("oxygen")) QApplication::setStyle(QStyleFactory::create("oxygen"));
// else QApplication::setStyle(QStyleFactory::create(x11style));
// // QApplication::setPalette(QApplication::style()->standardPalette());
// QFont x11Font (x11fontfamily,x11fontsize);
// QApplication::setFont(x11Font);
// #endif

QRect screen = QApplication::desktop()->screenGeometry();
int w= config->value( "Geometries/MainwindowWidth",screen.width()-100).toInt();
int h= config->value( "Geometries/MainwindowHeight",screen.height()-100).toInt() ;
int x= config->value( "Geometries/MainwindowX",10).toInt();
int y= config->value( "Geometries/MainwindowY",10).toInt() ;
resize(w,h);
move(x,y);
windowstate=config->value("MainWindowState").toByteArray();
#ifdef Q_WS_WIN
if (xf.contains("Courier New",Qt::CaseInsensitive)) deft="Courier New";
else deft=qApp->font().family();
QString fam=config->value("Editor/Font Family",deft).toString();
int si=config->value( "Editor/Font Size",10).toInt();
#else
if (xf.contains("DejaVu Sans Mono",Qt::CaseInsensitive)) deft="DejaVu Sans Mono";
else if (xf.contains("Lucida Sans Typewriter",Qt::CaseInsensitive)) deft="Lucida Sans Typewriter";
else deft=qApp->font().family();
QString fam=config->value("Editor/Font Family",deft).toString();
int si=config->value( "Editor/Font Size",qApp->font().pointSize()).toInt();
#endif
QFont F(fam,si);
EditorFont=F;

wordwrap=config->value( "Editor/WordWrap",true).toBool();
parenmatch=config->value( "Editor/Parentheses Matching",true).toBool();
showlinemultiples=config->value( "Editor/Line Number Multiples",-1).toInt();
if (showlinemultiples==-1) 
  if (config->value( "Editor/Line Numbers",true).toBool()) showlinemultiples=1; //texmaker import
  else showlinemultiples=0;

completion=config->value( "Editor/Completion",true).toBool();
folding=config->value( "Editor/Folding",true).toBool();
showlinestate=config->value( "Editor/Show Line State",true).toBool();
showcursorstate=config->value( "Editor/Show Cursor State",true).toBool();
realtimespellchecking=config->value( "Editor/Real-Time Spellchecking",true).toBool();

shortcuts.clear();
QStringList data,shortcut;
data=config->value("Shortcuts/data").toStringList();
shortcut=config->value("Shortcuts/shortcut").toStringList();
QStringListIterator dataiterator(data);
QStringListIterator shortcutiterator(shortcut);
while ( dataiterator.hasNext() && shortcutiterator.hasNext())
	{
	QString d=dataiterator.next();
	if (!d.isEmpty()) shortcuts.insert(d,shortcutiterator.next());
	}

showoutputview=config->value("Show/OutputView",true).toBool();
showstructview=config->value( "Show/Structureview",true).toBool();

quickmode=config->value( "Tools/Quick Mode",1).toInt();
#ifdef Q_WS_MACX
// /usr/local/teTeX/bin/i386-apple-darwin-current
// /usr/local/teTeX/bin/powerpc-apple-darwin-current
// /usr/texbin MACTEX/TEXLIVE2007
latex_command=config->value("Tools/Latex","\"/usr/texbin/latex\" -interaction=nonstopmode %.tex").toString();
dvips_command=config->value("Tools/Dvips","\"/usr/texbin/dvips\" -o %.ps %.dvi").toString();
ps2pdf_command=config->value("Tools/Ps2pdf","\"/usr/local/bin/ps2pdf\" %.ps").toString();
makeindex_command=config->value("Tools/Makeindex","\"/usr/texbin/makeindex\" %.idx").toString();
bibtex_command=config->value("Tools/Bibtex","\"/usr/texbin/bibtex\" %.aux").toString();
pdflatex_command=config->value("Tools/Pdflatex","\"/usr/texbin/pdflatex\" -interaction=nonstopmode %.tex").toString();
dvipdf_command=config->value("Tools/Dvipdf","\"/usr/texbin/dvipdfm\" %.dvi").toString();
metapost_command=config->value("Tools/Metapost","\"/usr/texbin/mpost\" --interaction nonstopmode ").toString();
viewdvi_command=config->value("Tools/Dvi","open %.dvi").toString();
viewps_command=config->value("Tools/Ps","open %.ps").toString();
viewpdf_command=config->value("Tools/Pdf","open %.pdf").toString();
ghostscript_command=config->value("Tools/Ghostscript","/usr/local/bin/gs").toString();
#endif
#ifdef Q_WS_WIN
latex_command=config->value("Tools/Latex","latex -interaction=nonstopmode %.tex").toString();
dvips_command=config->value("Tools/Dvips","dvips -o %.ps %.dvi").toString();
ps2pdf_command=config->value("Tools/Ps2pdf","ps2pdf %.ps").toString();
makeindex_command=config->value("Tools/Makeindex","makeindex %.idx").toString();
bibtex_command=config->value("Tools/Bibtex","bibtex %").toString();
//bibtex %.aux
pdflatex_command=config->value("Tools/Pdflatex","pdflatex -interaction=nonstopmode %.tex").toString();
dvipdf_command=config->value("Tools/Dvipdf","dvipdfm %.dvi").toString();
metapost_command=config->value("Tools/Metapost","mpost --interaction nonstopmode ").toString();
viewdvi_command=config->value("Tools/Dvi","\"C:/Program Files/MiKTeX 2.7/miktex/bin/yap.exe\" %.dvi").toString();
//C:/texmf/miktex/bin/yap.exe
//\"C:/Program Files/MiKTeX 2.5/miktex/bin/yap.exe\" -1 -s @%.tex %.dvi
viewps_command=config->value("Tools/Ps","\"C:/Program Files/Ghostgum/gsview/gsview32.exe\" %.ps").toString();
viewpdf_command=config->value("Tools/Pdf","\"C:/Program Files/Adobe/Reader 9.0/Reader/AcroRd32.exe\" %.pdf").toString();
//viewpdf_command=config->value("Tools/Pdf","\"C:/Program Files/Adobe/Reader 8.0/Reader/AcroRd32.exe\" %.pdf").toString();
ghostscript_command=config->value("Tools/Ghostscript","\"C:/Program Files/gs/gs8.63/bin/gswin32c.exe\"").toString();
//ghostscript_command=config->value("Tools/Ghostscript","\"C:/Program Files/gs/gs8.61/bin/gswin32c.exe\"").toString();
#endif
#ifdef Q_WS_X11
int desktop_env=1; // 1 : no kde ; 2: kde ; 3 : kde4 ;
QStringList styles = QStyleFactory::keys();
QString kdesession= ::getenv("KDE_FULL_SESSION");
QString kdeversion= ::getenv("KDE_SESSION_VERSION");
if (!kdesession.isEmpty()) desktop_env=2;
if (!kdeversion.isEmpty()) desktop_env=3;

latex_command=config->value("Tools/Latex","latex -interaction=nonstopmode %.tex").toString();
dvips_command=config->value("Tools/Dvips","dvips -o %.ps %.dvi").toString();
ps2pdf_command=config->value("Tools/Ps2pdf","ps2pdf %.ps").toString();
makeindex_command=config->value("Tools/Makeindex","makeindex %.idx").toString();
bibtex_command=config->value("Tools/Bibtex","bibtex %.aux").toString();
pdflatex_command=config->value("Tools/Pdflatex","pdflatex -interaction=nonstopmode %.tex").toString();
dvipdf_command=config->value("Tools/Dvipdf","dvipdfm %.dvi").toString();
metapost_command=config->value("Tools/Metapost","mpost --interaction nonstopmode ").toString();
// xdvi %.dvi  -sourceposition @:%.tex
// kdvi "file:%.dvi#src:@ %.tex"
switch (desktop_env)
	{
	case 1:
		{
		viewdvi_command=config->value("Tools/Dvi","evince %.dvi").toString();
		viewps_command=config->value("Tools/Ps","evince %.ps").toString();
		viewpdf_command=config->value("Tools/Pdf","evince %.pdf").toString();
		}break;
	case 2:
		{
		viewdvi_command=config->value("Tools/Dvi","kdvi %.dvi").toString();
		viewps_command=config->value("Tools/Ps","kghostview %.ps").toString();
		viewpdf_command=config->value("Tools/Pdf","kpdf %.pdf").toString();
		}break;
	case 3:
		{
		viewdvi_command=config->value("Tools/Dvi","okular %.dvi").toString();
		viewps_command=config->value("Tools/Ps","okular %.ps").toString();
		viewpdf_command=config->value("Tools/Pdf","okular %.pdf").toString();
		}break;
	}



ghostscript_command=config->value("Tools/Ghostscript","gs").toString();

x11style=config->value( "X11/Style","Plastique").toString();
if (xf.contains("DejaVu Sans",Qt::CaseInsensitive)) deft="DejaVu Sans";
else if (xf.contains("DejaVu Sans LGC",Qt::CaseInsensitive)) deft="DejaVu Sans LGC";
else if (xf.contains("Bitstream Vera Sans",Qt::CaseInsensitive)) deft="Bitstream Vera Sans";
else if (xf.contains("Luxi Sans",Qt::CaseInsensitive)) deft="Luxi Sans";
else deft=qApp->font().family();
x11fontfamily=config->value("X11/Font Family",deft).toString();
x11fontsize=config->value( "X11/Font Size","10").toInt();
if (x11style!="default")
    if ((desktop_env !=3) || (!styles.contains("Oxygen"))) QApplication::setStyle(x11style); //plastique style if not kde4
//if (desktop_env !=3) QApplication::setStyle(QStyleFactory::create(x11style));
// QApplication::setPalette(QApplication::style()->standardPalette());
QFont x11Font (x11fontfamily,x11fontsize);
QApplication::setFont(x11Font);
QPalette pal = QApplication::palette();
pal.setColor( QPalette::Active, QPalette::Highlight, QColor("#4490d8") );
pal.setColor( QPalette::Inactive, QPalette::Highlight, QColor("#4490d8") );
pal.setColor( QPalette::Disabled, QPalette::Highlight, QColor("#4490d8") );

//pal.setColor( QPalette::Active, QPalette::Highlight, QColor("#5689be") );
//pal.setColor( QPalette::Inactive, QPalette::Highlight, QColor("#5689be") );
//pal.setColor( QPalette::Disabled, QPalette::Highlight, QColor("#5689be") );

pal.setColor( QPalette::Active, QPalette::HighlightedText, QColor("#ffffff") );
pal.setColor( QPalette::Inactive, QPalette::HighlightedText, QColor("#ffffff") );
pal.setColor( QPalette::Disabled, QPalette::HighlightedText, QColor("#ffffff") );

pal.setColor( QPalette::Active, QPalette::Base, QColor("#ffffff") );
pal.setColor( QPalette::Inactive, QPalette::Base, QColor("#ffffff") );
pal.setColor( QPalette::Disabled, QPalette::Base, QColor("#ffffff") );

pal.setColor( QPalette::Active, QPalette::WindowText, QColor("#000000") );
pal.setColor( QPalette::Inactive, QPalette::WindowText, QColor("#000000") );
pal.setColor( QPalette::Disabled, QPalette::WindowText, QColor("#000000") );

pal.setColor( QPalette::Active, QPalette::ButtonText, QColor("#000000") );
pal.setColor( QPalette::Inactive, QPalette::ButtonText, QColor("#000000") );
pal.setColor( QPalette::Disabled, QPalette::ButtonText, QColor("#000000") );

if (desktop_env ==3)
	{
	pal.setColor( QPalette::Active, QPalette::Window, QColor("#eae9e9") );
	pal.setColor( QPalette::Inactive, QPalette::Window, QColor("#eae9e9") );
	pal.setColor( QPalette::Disabled, QPalette::Window, QColor("#eae9e9") );

	pal.setColor( QPalette::Active, QPalette::Button, QColor("#eae9e9") );
	pal.setColor( QPalette::Inactive, QPalette::Button, QColor("#eae9e9") );
	pal.setColor( QPalette::Disabled, QPalette::Button, QColor("#eae9e9") );
	}
else
	{
/*
	pal.setColor( QPalette::Active, QPalette::Window, QColor("#f1f1f1") );
	pal.setColor( QPalette::Inactive, QPalette::Window, QColor("#f1f1f1") );
	pal.setColor( QPalette::Disabled, QPalette::Window, QColor("#f1f1f1") );

	pal.setColor( QPalette::Active, QPalette::Button, QColor("#f1f1f1") );
	pal.setColor( QPalette::Inactive, QPalette::Button, QColor("#f1f1f1") );
	pal.setColor( QPalette::Disabled, QPalette::Button, QColor("#f1f1f1") );
*/
	pal.setColor( QPalette::Active, QPalette::Window, QColor("#fbf8f1") );
	pal.setColor( QPalette::Inactive, QPalette::Window, QColor("#fbf8f1") );
	pal.setColor( QPalette::Disabled, QPalette::Window, QColor("#fbf8f1") );

	pal.setColor( QPalette::Active, QPalette::Button, QColor("#fbf8f1") );
	pal.setColor( QPalette::Inactive, QPalette::Button, QColor("#fbf8f1") );
	pal.setColor( QPalette::Disabled, QPalette::Button, QColor("#fbf8f1") );
	}

QApplication::setPalette(pal);
#endif
userquick_command=config->value("Tools/Userquick","latex -interaction=nonstopmode %.tex|bibtex %.aux|latex -interaction=nonstopmode %.tex|latex -interaction=nonstopmode %.tex|xdvi %.dvi").toString();
userClassList=config->value("Tools/User Class").toStringList();
userPaperList=config->value("Tools/User Paper").toStringList();
userEncodingList=config->value("Tools/User Encoding").toStringList();
userOptionsList=config->value("Tools/User Options").toStringList();

lastDocument=config->value("Files/Last Document","").toString();
recentFilesList=config->value("Files/Recent Files").toStringList();
newfile_encoding=QTextCodec::codecForName(config->value("Files/New File Encoding", "utf-8").toString().toAscii().data());
autodetectLoadedFile=config->value("Files/Auto Detect Encoding Of Loaded Files", "true").toBool();

UserMenuName[0]=config->value("User/Menu1","").toString();
UserMenuTag[0]=config->value("User/Tag1","").toString();
UserMenuName[1]=config->value("User/Menu2","").toString();
UserMenuTag[1]=config->value("User/Tag2","").toString();
UserMenuName[2]=config->value("User/Menu3","").toString();
UserMenuTag[2]=config->value("User/Tag3","").toString();
UserMenuName[3]=config->value("User/Menu4","").toString();
UserMenuTag[3]=config->value("User/Tag4","").toString();
UserMenuName[4]=config->value("User/Menu5","").toString();
UserMenuTag[4]=config->value("User/Tag5","").toString();
UserMenuName[5]=config->value("User/Menu6","").toString();
UserMenuTag[5]=config->value("User/Tag6","").toString();
UserMenuName[6]=config->value("User/Menu7","").toString();
UserMenuTag[6]=config->value("User/Tag7","").toString();
UserMenuName[7]=config->value("User/Menu8","").toString();
UserMenuTag[7]=config->value("User/Tag8","").toString();
UserMenuName[8]=config->value("User/Menu9","").toString();
UserMenuTag[8]=config->value("User/Tag9","").toString();
UserMenuName[9]=config->value("User/Menu10","").toString();
UserMenuTag[9]=config->value("User/Tag10","").toString();
UserToolName[0]=config->value("User/ToolName1","").toString();
UserToolCommand[0]=config->value("User/Tool1","").toString();
UserToolName[1]=config->value("User/ToolName2","").toString();
UserToolCommand[1]=config->value("User/Tool2","").toString();
UserToolName[2]=config->value("User/ToolName3","").toString();
UserToolCommand[2]=config->value("User/Tool3","").toString();
UserToolName[3]=config->value("User/ToolName4","").toString();
UserToolCommand[3]=config->value("User/Tool4","").toString();
UserToolName[4]=config->value("User/ToolName5","").toString();
UserToolCommand[4]=config->value("User/Tool5","").toString();

int UserKeyReplaceCount = config->value("User/KeyReplaceCount",2).toInt();
UserKeyReplace.clear();
UserKeyReplaceAfterWord.clear();
UserKeyReplaceBeforeWord.clear();
for (int i=0;i<UserKeyReplaceCount;i++) {
  UserKeyReplace.append(config->value("User/KeyReplace"+QVariant(i).toString(),i!=0?"'":"\"").toString());
  UserKeyReplaceAfterWord.append(config->value("User/KeyReplaceAfterWord"+QVariant(i).toString(),i!=0?"''":"\"<").toString());
  UserKeyReplaceBeforeWord.append(config->value("User/KeyReplaceBeforeWord"+QVariant(i).toString(),i!=0?"``":"\">").toString());
}
LatexEditorView::setKeyReplacements(&UserKeyReplace,&UserKeyReplaceAfterWord,&UserKeyReplaceBeforeWord);

struct_level1=config->value("Structure/Structure Level 1","part").toString();
struct_level2=config->value("Structure/Structure Level 2","chapter").toString();
struct_level3=config->value("Structure/Structure Level 3","section").toString();
struct_level4=config->value("Structure/Structure Level 4","subsection").toString();
struct_level5=config->value("Structure/Structure Level 5","subsubsection").toString();


document_class=config->value("Quick/Class","article").toString();
typeface_size=config->value("Quick/Typeface","10pt").toString();
paper_size=config->value("Quick/Papersize","a4paper").toString();
document_encoding=config->value("Quick/Encoding","latin1").toString();
ams_packages=config->value( "Quick/AMS",true).toBool();
makeidx_package=config->value( "Quick/MakeIndex",false).toBool();
author=config->value("Quick/Author","").toString();


spell_dic=config->value("Spell/Dic","<dic not found>").toString();
if (spell_dic=="<dic not found>"){
    spell_dic=findResourceFile(QString(QLocale::system().name())+".dic");
    if (spell_dic=="") spell_dic=findResourceFile("en_US.dic");
    if (spell_dic=="") spell_dic=findResourceFile("en_GB.dic");
    if (spell_dic=="") spell_dic=findResourceFile("fr_FR.dic");
    if (spell_dic=="") spell_dic=findResourceFile("de_DE.dic");
}

for (int i=0; i <412 ; i++)
	symbolScore[i]=config->value( "Symbols/symbol"+QString::number(i),0).toInt();


config->endGroup();
}

void Texmaker::SaveSettings()
{
    QSettings *config=new QSettings (configFileName, QSettings::IniFormat);   

config->setValue( "IniMode",true);
config->beginGroup( "texmaker" );
QList<int> sizes;
QList<int>::Iterator it;

#if defined( Q_WS_X11 )
config->setValue( "X11/Style",x11style);
config->setValue("X11/Font Family",x11fontfamily);

config->setValue( "X11/Font Size",x11fontsize);
#endif

config->setValue("MainWindowState",saveState(0));
config->setValue("Geometries/MainwindowWidth", width() );

config->setValue("Geometries/MainwindowHeight", height() );
config->setValue("Geometries/MainwindowX", x() );
config->setValue("Geometries/MainwindowY", y() );



config->setValue("Editor/Font Family",EditorFont.family());
config->setValue( "Editor/Font Size",EditorFont.pointSize());
config->setValue( "Editor/WordWrap",wordwrap);

config->setValue( "Editor/Parentheses Matching",parenmatch);
config->setValue( "Editor/Line Number Multiples",showlinemultiples);
config->setValue( "Editor/Completion",completion);

config->setValue( "Editor/Folding",folding);
config->setValue( "Editor/Show Line State",showlinestate);
config->setValue( "Editor/Show Cursor State",showcursorstate);
config->setValue( "Editor/Real-Time Spellchecking",realtimespellchecking);


QStringList data,shortcut;
// data.clear();
// shortcut.clear();
KeysMap::Iterator its;
for( its = shortcuts.begin(); its != shortcuts.end(); ++its )
	{
	data.append(its.key());
	shortcut.append(its.value());
	}
config->setValue("Shortcuts/data",data);

config->setValue("Shortcuts/shortcut",shortcut);

config->setValue("Show/OutputView",showoutputview);

config->setValue( "Show/Structureview",showstructview);

config->setValue("Tools/Quick Mode",quickmode);

config->setValue("Tools/Latex",latex_command);
config->setValue("Tools/Dvi",viewdvi_command);
config->setValue("Tools/Dvips",dvips_command);
config->setValue("Tools/Ps",viewps_command);


config->setValue("Tools/Ps2pdf",ps2pdf_command);

config->setValue("Tools/Makeindex",makeindex_command);

config->setValue("Tools/Bibtex",bibtex_command);
config->setValue("Tools/Pdflatex",pdflatex_command);
config->setValue("Tools/Pdf",viewpdf_command);

config->setValue("Tools/Dvipdf",dvipdf_command);
config->setValue("Tools/Metapost",metapost_command);

config->setValue("Tools/Ghostscript",ghostscript_command);
config->setValue("Tools/Userquick",userquick_command);
if (userClassList.count()>0) 
config->setValue("Tools/User Class",userClassList);
if (userPaperList.count()>0) config->setValue("Tools/User Paper",userPaperList);
if (userEncodingList.count()>0) config->setValue("Tools/User Encoding",userEncodingList);
if (userOptionsList.count()>0) config->setValue("Tools/User Options",userOptionsList);


config->setValue("Files/Last Document",lastDocument);
if (recentFilesList.count()>0) config->setValue("Files/Recent Files",recentFilesList);

config->setValue("Files/New File Encoding", newfile_encoding?newfile_encoding->name():"??");
config->setValue("Files/Auto Detect Encoding Of Loaded Files", autodetectLoadedFile);



config->setValue("User/Menu1",UserMenuName[0]);
config->setValue("User/Tag1",UserMenuTag[0]);
config->setValue("User/Menu2",UserMenuName[1]);
config->setValue("User/Tag2",UserMenuTag[1]);
config->setValue("User/Menu3",UserMenuName[2]);



config->setValue("User/Tag3",UserMenuTag[2]);
config->setValue("User/Menu4",UserMenuName[3]);

config->setValue("User/Tag4",UserMenuTag[3]);
config->setValue("User/Menu5",UserMenuName[4]);
config->setValue("User/Tag5",UserMenuTag[4]);
config->setValue("User/Menu6",UserMenuName[5]);

config->setValue("User/Tag6",UserMenuTag[5]);
config->setValue("User/Menu7",UserMenuName[6]);
config->setValue("User/Tag7",UserMenuTag[6]);

config->setValue("User/Menu8",UserMenuName[7]);
config->setValue("User/Tag8",UserMenuTag[7]);
config->setValue("User/Menu9",UserMenuName[8]);

config->setValue("User/Tag9",UserMenuTag[8]);
config->setValue("User/Menu10",UserMenuName[9]);

config->setValue("User/Tag10",UserMenuTag[9]);
config->setValue("User/ToolName1",UserToolName[0]);

config->setValue("User/Tool1",UserToolCommand[0]);
config->setValue("User/ToolName2",UserToolName[1]);
config->setValue("User/Tool2",UserToolCommand[1]);

config->setValue("User/ToolName3",UserToolName[2]);
config->setValue("User/Tool3",UserToolCommand[2]);

config->setValue("User/ToolName4",UserToolName[3]);
config->setValue("User/Tool4",UserToolCommand[3]);
config->setValue("User/ToolName5",UserToolName[4]);
config->setValue("User/Tool5",UserToolCommand[4]);

int UserKeyReplaceCount = UserKeyReplace.count();

config->setValue("User/KeyReplaceCount",UserKeyReplaceCount);
for (int i=0;i<UserKeyReplaceCount;i++) {
  
  
  
  
  config->setValue("User/KeyReplace"+QVariant(i).toString(),UserKeyReplace[i]);
  config->setValue("User/KeyReplaceAfterWord"+QVariant(i).toString(),UserKeyReplaceAfterWord[i]);
  
  config->setValue("User/KeyReplaceBeforeWord"+QVariant(i).toString(),UserKeyReplaceBeforeWord[i]);
}


config->setValue("Structure/Structure Level 1",struct_level1);
config->setValue("Structure/Structure Level 2",struct_level2);
config->setValue("Structure/Structure Level 3",struct_level3);



config->setValue("Structure/Structure Level 4",struct_level4);
config->setValue("Structure/Structure Level 5",struct_level5);

config->setValue( "Quick/Class",document_class);

config->setValue( "Quick/Typeface",typeface_size);
config->setValue( "Quick/Papersize",paper_size);
config->setValue( "Quick/Encoding",document_encoding);
config->setValue( "Quick/AMS",ams_packages);

config->setValue( "Quick/MakeIndex",makeidx_package);
config->setValue( "Quick/Author",author);


config->setValue( "Spell/Dic",spell_dic);

for (int i=0; i <412 ; i++)
	{
	config->setValue( "Symbols/symbol"+QString::number(i),symbolScore[i]);
	}


config->endGroup();
delete config;
}

////////////////// STRUCTURE ///////////////////
void Texmaker::ShowStructure()
{
//StructureToolbox->setCurrentItem(StructureTreeWidget);
StructureToolbox->setCurrentIndex(StructureToolbox->indexOf(StructureTreeWidget));
}

void Texmaker::UpdateStructure()
{
QTreeWidgetItem *Child,*parent_level[5], *theitem;
QString current;
if (StructureTreeWidget->currentItem()) current=StructureTreeWidget->currentItem()->text(0);
StructureTreeWidget->clear();
if ( !currentEditorView() ) return;
QString shortName = getName();
if ((shortName.right(4)!=".tex") && (shortName!="untitled"))  return;
int pos;
while ( (pos = (int)shortName.indexOf('/')) != -1 )
shortName.remove(0,pos+1);
QTreeWidgetItem *top = new QTreeWidgetItem(StructureTreeWidget);
top->setIcon(0,QIcon(":/images/doc.png"));
top->setText(0,shortName);
Child=parent_level[0]=parent_level[1]=parent_level[2]=parent_level[3]=parent_level[4]=top;
structlist.clear();
structitem.clear();
labelitem.clear();
structlist.append(QString::number(0));
structitem.append(shortName);
QTreeWidgetItem *toplabel = new QTreeWidgetItem(top);
toplabel->setText(0,"LABELS");
structlist.append(QString::number(0));
structitem.append("LABELS");
QString s;
for (int i=0;i<currentEditorView()->editor->document()->lines();i++)
	{
	int tagStart, tagEnd;
	//// label ////
	tagStart=tagEnd=0;
	s=currentEditorView()->editor->text(i);
	tagStart=s.indexOf("\\label{", tagEnd);
	if (tagStart!=-1)
		{
		s=s.mid(tagStart+7,s.length());
		tagStart=s.indexOf("}", tagEnd);
		if (tagStart!=-1)
			{
			s=s.mid(0,tagStart);
			labelitem.append(s);
			structlist.append(QString::number(i));
			s=s+" (line "+QString::number(i+1)+")";
			structitem.append(s);
			Child = new QTreeWidgetItem(toplabel);
			Child->setText(0,s);
			}
		};

	//// include ////
	tagStart=tagEnd=0;
	s=currentEditorView()->editor->text(i);
	tagStart=s.indexOf("\\include{", tagEnd);
	if (tagStart!=-1)
		{
		s=s.mid(tagStart+8,s.length());
		tagStart=s.indexOf("}", tagEnd);
		if (tagStart!=-1)
			{
			s=s.mid(0,tagStart+1);
			structlist.append("include");
			structitem.append(s);
			Child = new QTreeWidgetItem(top);
			Child->setText(0,s);
			Child->setIcon(0,QIcon(":/images/include.png"));
			}
		};
	//// input ////
	tagStart=tagEnd=0;
	s=currentEditorView()->editor->text(i);
	tagStart=s.indexOf("\\input{", tagEnd);
		if (tagStart!=-1)
		{
		s=s.mid(tagStart+6,s.length());
		tagStart=s.indexOf("}", tagEnd);
		if (tagStart!=-1)
			{
			s=s.mid(0,tagStart+1);
			structlist.append("input");
			structitem.append(s);
			Child = new QTreeWidgetItem(top);
			Child->setText(0,s);
			Child->setIcon(0,QIcon(":/images/include.png"));
			}
		};
	//// part ////
	tagStart=tagEnd=0;
	s=currentEditorView()->editor->text(i);
	tagStart=s.indexOf(QRegExp("\\\\"+struct_level1+"\\*?[\\{\\[]"), tagEnd);
	if (tagStart!=-1)
		{
		structlist.append(QString::number(i));
		tagStart=s.indexOf(struct_level1, tagEnd);
		s=s.mid(tagStart+struct_level1.length(),s.length());
		s=s+" (line "+QString::number(i+1)+")";
		structitem.append(s);
		parent_level[0] = new QTreeWidgetItem(top);
		parent_level[0]->setText(0,s);
		parent_level[0]->setIcon(0,QIcon(":/images/part.png"));
		parent_level[1]=parent_level[2]=parent_level[3]=parent_level[4]=parent_level[0];
		};
	//// chapter ////
	tagStart=tagEnd=0;
	s=currentEditorView()->editor->text(i);
	tagStart=s.indexOf(QRegExp("\\\\"+struct_level2+"\\*?[\\{\\[]"), tagEnd);
	if (tagStart!=-1)
		{
		structlist.append(QString::number(i));
		tagStart=s.indexOf(struct_level2, tagEnd);
		s=s.mid(tagStart+struct_level2.length(),s.length());
		s=s+" (line "+QString::number(i+1)+")";
		structitem.append(s);
		parent_level[1] = new QTreeWidgetItem(parent_level[0]);
		parent_level[1]->setText(0,s);
		parent_level[1]->setIcon(0,QIcon(":/images/chapter.png"));
		parent_level[1]->setText(1,"chapter"); //this is intern (at least from textanalyse) needed to recognize chapter items!
		parent_level[1]->setText(3,QString::number(i+1)); //this is intern (at least from textanalyse) needed to recognize chapter items! (2 would be name)
		parent_level[2]=parent_level[3]=parent_level[4]=parent_level[1];
		};
	//// section ////
	tagStart=tagEnd=0;
	s=currentEditorView()->editor->text(i);
	tagStart=s.indexOf(QRegExp("\\\\"+struct_level3+"\\*?[\\{\\[]"), tagEnd);
		if (tagStart!=-1)
		{
		structlist.append(QString::number(i));
		tagStart=s.indexOf(struct_level3, tagEnd);
		s=s.mid(tagStart+struct_level3.length(),s.length());
		s=s+" (line "+QString::number(i+1)+")";
		structitem.append(s);
		parent_level[2] = new QTreeWidgetItem(parent_level[1]);
		parent_level[2]->setText(0,s);
		parent_level[2]->setIcon(0,QIcon(":/images/section.png"));
		parent_level[3]=parent_level[4]=parent_level[2];
		};
	//// subsection ////
	tagStart=tagEnd=0;
	s=currentEditorView()->editor->text(i);
	tagStart=s.indexOf(QRegExp("\\\\"+struct_level4+"\\*?[\\{\\[]"), tagEnd);
	if (tagStart!=-1)
		{
		structlist.append(QString::number(i));
		tagStart=s.indexOf(struct_level4, tagEnd);
		s=s.mid(tagStart+struct_level4.length(),s.length());
		s=s+" (line "+QString::number(i+1)+")";
		structitem.append(s);
		parent_level[3] = new QTreeWidgetItem(parent_level[2]);
		parent_level[3]->setText(0,s);
		parent_level[3]->setIcon(0,QIcon(":/images/subsection.png"));
		parent_level[4]=parent_level[3];
		};
	//// subsubsection ////
	tagStart=tagEnd=0;
	s=currentEditorView()->editor->text(i);
	tagStart=s.indexOf(QRegExp("\\\\"+struct_level5+"\\*?[\\{\\[]"), tagEnd);
	if (tagStart!=-1)
		{
		structlist.append(QString::number(i));
		tagStart=s.indexOf(struct_level5, tagEnd);
		s=s.mid(tagStart+struct_level5.length(),s.length());
		s=s+" (line "+QString::number(i+1)+")";
		structitem.append(s);
		parent_level[4] = new QTreeWidgetItem(parent_level[3]);
		parent_level[4]->setText(0,s);
		parent_level[4]->setIcon(0,QIcon(":/images/subsubsection.png"));
		};
	}
if (!current.isEmpty())
	{
	QList<QTreeWidgetItem *> fItems=StructureTreeWidget->findItems (current,Qt::MatchRecursive,0);
	if ((fItems.size()>0 ) && (fItems.at(0)))
		{
		StructureTreeWidget->setCurrentItem(fItems.at(0));
		theitem=fItems.at(0)->parent();
		while ((theitem) && (theitem!=top))
			{
			StructureTreeWidget->setItemExpanded (theitem,true);
			theitem=theitem->parent();
			}
		}
	}
StructureTreeWidget->setItemExpanded (top,true);
updateCompleter();
}

void Texmaker::ClickedOnStructure(QTreeWidgetItem *item,int col)
{
QString finame;
if (singlemode) {finame=getName();}
else {finame=MasterName;}
if ((singlemode && !currentEditorView()) || finame=="untitled" || finame=="")
{
return;
}
QFileInfo fi(finame);
QString name=fi.absoluteFilePath();
QString flname=fi.fileName();
QString basename=name.left(name.length()-flname.length());
if ((item) && (!structlist.isEmpty()))
	{
	QStringList::ConstIterator it1 = structitem.begin();
	QStringList::ConstIterator it2 = structlist.begin();
	for ( ; it1 !=structitem.end(); ++it1 )
		{
		if (*it1==item->text(col)) break;
		++it2;
		}
	QString s=*it2;
	if (s=="include")
		{
		QString fname=*it1;
		if (fname.right(5)==".tex}") fname=basename+fname.mid(1,fname.length()-2);
		else fname=basename+fname.mid(1,fname.length()-2)+".tex";
		QFileInfo fi(fname);
		if (fi.exists() && fi.isReadable()) load(fname);
		}
	else if (s=="input")
		{
		QString fname=*it1;
		if (fname.right(5)==".tex}") fname=basename+fname.mid(1,fname.length()-2);
		else fname=basename+fname.mid(1,fname.length()-2)+".tex";
		QFileInfo fi(fname);
		if (fi.exists() && fi.isReadable()) load(fname);
		}
	else
		{
		bool ok;
		int l=s.toInt(&ok,10);
		if (ok)
			{
			currentEditorView()->editor->setCursorPosition(l,1);
			currentEditorView()->editor->setFocus();
			}
		}
	}
}

//////////TAGS////////////////
void Texmaker::InsertTag(QString Entity, int dx, int dy)
{
    if ( !currentEditorView() )	return;
    int curline,curindex;
    currentEditorView()->editor->getCursorPosition(curline,curindex);
    currentEditorView()->editor->cursor().insertText(Entity);
    if (dy==0) currentEditorView()->editor->setCursorPosition(curline,curindex+dx);
    else if (dx==0) currentEditorView()->editor->setCursorPosition(curline+dy,0);
    else currentEditorView()->editor->setCursorPosition(curline+dy,curindex+dx);
    currentEditorView()->editor->setFocus();
    OutputTextEdit->clear();
    OutputTableWidget->hide();
    logpresent=false;
}

void Texmaker::InsertSymbol(QTableWidgetItem *item)
{
QString code_symbol;
QRegExp rxnumber(";([0-9]+)");
int number=-1;
if (item)
	{
	if ( rxnumber.indexIn(item->text()) != -1) number=rxnumber.cap(1).toInt();
	if ((number>-1) && (number<412)) symbolScore[number]=symbolScore[number]+1;
	code_symbol=item->text().remove(rxnumber);
	InsertTag(code_symbol,code_symbol.length(),0);
	SetMostUsedSymbols();
	}
}

void Texmaker::InsertMetaPost(QListWidgetItem *item)
{
QString mpcode;
if (item)
	{
	mpcode=item->text();
	if (mpcode!="----------") InsertTag(mpcode,mpcode.length(),0);
	}
}

void Texmaker::InsertPstricks(QListWidgetItem *item)
{
QString pstcode;
if (item  && !item->font().bold())
	{
	pstcode=item->text();
	pstcode.remove(QRegExp("\\[(.*)\\]"));
	InsertTag(pstcode,pstcode.length(),0);
	}
}

void Texmaker::InsertFromAction()
{
bool ok;
QString actData;
QStringList tagList;
QAction *action = qobject_cast<QAction *>(sender());
if ( !currentEditorView() )	return;
if (action)
	{
	actData=action->data().toString();
	tagList= actData.split("/");
	InsertTag(tagList.at(0),tagList.at(1).toInt(&ok, 10),tagList.at(2).toInt(&ok, 10));
	OutputTextEdit->insertLine(tagList.at(3));
	}
}

void Texmaker::InsertWithSelectionFromAction()
{
bool ok;
QString actData;
QStringList tagList;
QAction *action = qobject_cast<QAction *>(sender());
if ( !currentEditorView() )	return;
if (action)
	{
	actData=action->data().toString();
	tagList= actData.split("/");
	if (!currentEditorView()->editor->cursor().hasSelection())
		{
		OutputTextEdit->insertLine("You can select a text before using this environment.");
		InsertTag(tagList.at(0)+tagList.at(1),tagList.at(2).toInt(&ok, 10),tagList.at(3).toInt(&ok, 10));
		}
	else
		{
		currentEditorView()->editor->cut();
		InsertTag(tagList.at(0),tagList.at(2).toInt(&ok, 10),tagList.at(3).toInt(&ok, 10));
		currentEditorView()->editor->paste();
		InsertTag(tagList.at(1),0,0);
		}
	}
}

void Texmaker::InsertWithSelectionFromString(const QString& text)
{
bool ok;
QStringList tagList;
if ( !currentEditorView() )	return;
tagList= text.split("/");
if (!currentEditorView()->editor->cursor().hasSelection())
	{
	InsertTag(tagList.at(0)+tagList.at(1),tagList.at(2).toInt(&ok, 10),tagList.at(3).toInt(&ok, 10));
	}
else
	{
	currentEditorView()->editor->cut();
	InsertTag(tagList.at(0),tagList.at(2).toInt(&ok, 10),tagList.at(3).toInt(&ok, 10));
	currentEditorView()->editor->paste();
	InsertTag(tagList.at(1),0,0);
	}
}

void Texmaker::InsertFromString(const QString& text)
{
bool ok;
QStringList tagList;
if ( !currentEditorView() ) return;
tagList= text.split("/");
InsertTag(tagList.at(0),tagList.at(1).toInt(&ok, 10),tagList.at(2).toInt(&ok, 10));
}

void Texmaker::InsertBib()
{
if ( !currentEditorView() )	return;
//currentEditorView()->editor->viewport()->setFocus();
QString tag;
QFileInfo fi(getName());
tag=QString("\\bibliography{");
tag +=fi.completeBaseName();
tag +=QString("}\n");
InsertTag(tag,0,1);
OutputTextEdit->clear();
OutputTableWidget->hide();
OutputTextEdit->insertLine("The argument to \\bibliography refers to the bib file (without extension)");
OutputTextEdit->insertLine("which should contain your database in BibTeX format.");
OutputTextEdit->insertLine("Texmaker inserts automatically the base name of the TeX file");
}

void Texmaker::InsertStruct()
{
QString actData, tag;
if ( !currentEditorView() )	return;
//currentEditorView()->editor->viewport()->setFocus();
QAction *action = qobject_cast<QAction *>(sender());
if (action)
	{
	actData=action->data().toString();
	StructDialog *stDlg = new StructDialog(this,actData);
	if ( stDlg->exec() )
		{
		if (stDlg->ui.checkBox->isChecked())
		{tag=actData+"{";}
		else
		{tag=actData+"*{";}
		tag +=stDlg->ui.TitlelineEdit->text();
		tag +=QString("}\n");
		InsertTag(tag,0,1);
		UpdateStructure();
		}
	}
}

void Texmaker::InsertStructFromString(const QString& text)
{
QString tag;
if ( !currentEditorView() )	return;
//currentEditorView()->editor->viewport()->setFocus();
StructDialog *stDlg = new StructDialog(this,text);
if ( stDlg->exec() )
	{
	if (stDlg->ui.checkBox->isChecked())
	{tag=text+"{";}
	else
	{tag=text+"*{";}
	tag +=stDlg->ui.TitlelineEdit->text();
	tag +=QString("}\n");
	InsertTag(tag,0,1);
	UpdateStructure();
	}
}

void Texmaker::InsertImage()
{
if ( !currentEditorView() )	return;
QString currentDir=QDir::homePath();
QString finame;
if (singlemode) {finame=getName();}
else {finame=MasterName;}
QFileInfo fi(finame);
if (finame!="untitled") currentDir=fi.absolutePath();
FileChooser *sfDlg = new FileChooser(this,tr("Select an image File"));
sfDlg->setFilter("Graphic files (*.eps *.pdf *.png);;All files (*.*)");
sfDlg->setDir(currentDir);
if (sfDlg->exec() )
	{
	QString fn=sfDlg->fileName();
	QFileInfo fi(fn);
	InsertTag("\\includegraphics[scale=1]{"+fi.completeBaseName()+"."+fi.suffix()+"} ",26,0);
	}
}

void Texmaker::InsertInclude()
{
if ( !currentEditorView() )	return;
QString currentDir=QDir::homePath();
QString finame;
if (singlemode) {finame=getName();}
else {finame=MasterName;}
QFileInfo fi(finame);
if (finame!="untitled") currentDir=fi.absolutePath();
FileChooser *sfDlg = new FileChooser(this,tr("Select a File"));
sfDlg->setFilter("TeX files (*.tex);;All files (*.*)");
sfDlg->setDir(currentDir);
if (sfDlg->exec() )
	{
	QString fn=sfDlg->fileName();
	QFileInfo fi(fn);
	InsertTag("\\include{"+fi.completeBaseName()+"}",9,0);
	}
UpdateStructure();
}

void Texmaker::InsertInput()
{
if ( !currentEditorView() )	return;
QString currentDir=QDir::homePath();
QString finame;
if (singlemode) {finame=getName();}
else {finame=MasterName;}
QFileInfo fi(finame);
if (finame!="untitled") currentDir=fi.absolutePath();
FileChooser *sfDlg = new FileChooser(this,tr("Select a File"));
sfDlg->setFilter("TeX files (*.tex);;All files (*.*)");
sfDlg->setDir(currentDir);
if (sfDlg->exec() )
	{
	QString fn=sfDlg->fileName();
	QFileInfo fi(fn);
	InsertTag("\\input{"+fi.completeBaseName()+"}",7,0);
	}
UpdateStructure();
}

void Texmaker::QuickTabular()
{
if ( !currentEditorView() )	return;
QString al="";
QString vs="";
QString hs="";
QString tag;
TabDialog *quickDlg = new TabDialog(this,"Tabular");
QTableWidgetItem *item=new QTableWidgetItem();
if ( quickDlg->exec() )
	{
	int y = quickDlg->ui.spinBoxRows->value();
	int x = quickDlg->ui.spinBoxColumns->value();
	if  ((quickDlg->ui.comboSeparator->currentIndex())==0) vs=QString("|");
	if  ((quickDlg->ui.comboSeparator->currentIndex())==1) vs=QString("||");
	if  ((quickDlg->ui.comboSeparator->currentIndex())==2) vs=QString("");
	if  ((quickDlg->ui.comboSeparator->currentIndex())==3) vs=QString("@{}");
	tag = QString("\\begin{tabular}{")+vs;
	if  ((quickDlg->ui.comboAlignment->currentIndex())==0) al=QString("c")+vs;
	if  ((quickDlg->ui.comboAlignment->currentIndex())==1) al=QString("l")+vs;
	if  ((quickDlg->ui.comboAlignment->currentIndex())==2) al=QString("r")+vs;
	if  ((quickDlg->ui.comboAlignment->currentIndex())==3) al=QString("p{}")+vs;
	if (quickDlg->ui.checkBox->isChecked()) hs=QString("\\hline ");
	for ( int j=0;j<x;j++) {tag +=al;}
	tag +=QString("}\n");
	for ( int i=0;i<y;i++)
		{
		tag +=hs;
		for ( int j=0;j<x-1;j++)
			{
			item =quickDlg->ui.tableWidget->item(i,j);
			if (item) tag +=item->text()+ QString(" & ");
			else tag +=QString(" & ");
			}
		item =quickDlg->ui.tableWidget->item(i,x-1);
		if (item) tag +=item->text()+ QString(" \\\\ \n");
		else tag +=QString(" \\\\ \n");
		}
	if (quickDlg->ui.checkBox->isChecked()) tag +=hs+QString("\n\\end{tabular} ");
	else tag +=QString("\\end{tabular} ");
	InsertTag(tag,0,0);
	}

}

void Texmaker::QuickArray()
{
if ( !currentEditorView() )	return;
QString al;
ArrayDialog *arrayDlg = new ArrayDialog(this,"Array");
QTableWidgetItem *item=new QTableWidgetItem();
if ( arrayDlg->exec() )
	{
	int y = arrayDlg->ui.spinBoxRows->value();
	int x = arrayDlg->ui.spinBoxColumns->value();
	QString env=arrayDlg->ui.comboEnvironment->currentText();
	QString tag = QString("\\begin{")+env+"}";
	if (env=="array")
		{
		tag+="{";
		if  ((arrayDlg->ui.comboAlignment->currentIndex())==0) al=QString("c");
		if  ((arrayDlg->ui.comboAlignment->currentIndex())==1) al=QString("l");
		if  ((arrayDlg->ui.comboAlignment->currentIndex())==2) al=QString("r");
		for ( int j=0;j<x;j++) {tag +=al;} tag+="}";
		}
	tag +=QString("\n");
	for ( int i=0;i<y-1;i++)
		{
		for ( int j=0;j<x-1;j++)
			{
			item =arrayDlg->ui.tableWidget->item(i,j);
			if (item) tag +=item->text()+ QString(" & ");
			else tag +=QString(" & ");
			}
		item =arrayDlg->ui.tableWidget->item(i,x-1);
		if (item) tag +=item->text()+ QString(" \\\\ \n");
		else tag +=QString(" \\\\ \n");
		}
	for ( int j=0;j<x-1;j++)
		{
		item =arrayDlg->ui.tableWidget->item(y-1,j);
		if (item) tag +=item->text()+ QString(" & ");
		else tag +=QString(" & ");
		}
	item =arrayDlg->ui.tableWidget->item(y-1,x-1);
	if (item) tag +=item->text()+ QString("\n\\end{")+env+"} ";
	else tag +=QString("\n\\end{")+env+"} ";
	InsertTag(tag,0,0);
	}
}

void Texmaker::QuickTabbing()
{
if ( !currentEditorView() ) return;
TabbingDialog *tabDlg = new TabbingDialog(this,"Tabbing");
if ( tabDlg->exec() )
	{
	int	x = tabDlg->ui.spinBoxColumns->value();
	int	y = tabDlg->ui.spinBoxRows->value();
	QString s=tabDlg->ui.lineEdit->text();
	QString tag = QString("\\begin{tabbing}\n");
	for ( int j=1;j<x;j++) {tag +="\\hspace{"+s+"}\\=";}
	tag+="\\kill\n";
	for ( int i=0;i<y-1;i++)
		{
		for ( int j=1;j<x;j++) {tag +=" \\> ";}
		tag+="\\\\ \n";
		}
	for ( int j=1;j<x;j++) {tag +=" \\> ";}
	tag += QString("\n\\end{tabbing} ");
	InsertTag(tag,0,2);
	}
}

void Texmaker::QuickLetter()
{
if ( !currentEditorView() )	return;
QString tag=QString("\\documentclass[");
LetterDialog *ltDlg = new LetterDialog(this,"Letter");
if ( ltDlg->exec() )
	{
	tag+=ltDlg->ui.comboBoxPt->currentText()+QString(",");
	tag+=ltDlg->ui.comboBoxPaper->currentText()+QString("]{letter}");
	tag+=QString("\n");
	if (ltDlg->ui.comboBoxEncoding->currentText()!="NONE") tag+=QString("\\usepackage[")+ltDlg->ui.comboBoxEncoding->currentText()+QString("]{inputenc}");
	if (ltDlg->ui.comboBoxEncoding->currentText().startsWith("utf8")) tag+=QString(" \\usepackage{ucs}");
	tag+=QString("\n");
	if (ltDlg->ui.checkBox->isChecked()) tag+=QString("\\usepackage{amsmath}\n\\usepackage{amsfonts}\n\\usepackage{amssymb}\n");
	tag+="\\address{your name and address} \n";
	tag+="\\signature{your signature} \n";
	tag+="\\begin{document} \n";
	tag+="\\begin{letter}{name and address of the recipient} \n";
	tag+="\\opening{saying hello} \n \n";
	tag+="write your letter here \n \n";
	tag+="\\closing{saying goodbye} \n";
	tag+="%\\cc{Cclist} \n";
	tag+="%\\ps{adding a postscript} \n";
	tag+="%\\encl{list of enclosed material} \n";
	tag+="\\end{letter} \n";
	tag+="\\end{document}";
	if (ltDlg->ui.checkBox->isChecked()) {InsertTag(tag,9,5);}
	else {InsertTag(tag,9,2);}
	}
}

void Texmaker::QuickDocument()
{
QString opt="";
int li=3;
int f;
if ( !currentEditorView() ) return;
QString tag=QString("\\documentclass[");
QuickDocumentDialog *startDlg = new QuickDocumentDialog(this,"Quick Start");
startDlg->otherClassList=userClassList;
startDlg->otherPaperList=userPaperList;
startDlg->otherEncodingList=userEncodingList;
startDlg->otherOptionsList=userOptionsList;
startDlg->Init();
f=startDlg->ui.comboBoxClass->findText(document_class,Qt::MatchExactly | Qt::MatchCaseSensitive);
startDlg->ui.comboBoxClass->setCurrentIndex(f);
f=startDlg->ui.comboBoxSize->findText(typeface_size,Qt::MatchExactly | Qt::MatchCaseSensitive);
startDlg->ui.comboBoxSize->setCurrentIndex(f);
f=startDlg->ui.comboBoxPaper->findText(paper_size,Qt::MatchExactly | Qt::MatchCaseSensitive);
startDlg->ui.comboBoxPaper->setCurrentIndex(f);
f=startDlg->ui.comboBoxEncoding->findText(document_encoding,Qt::MatchExactly | Qt::MatchCaseSensitive);
startDlg->ui.comboBoxEncoding->setCurrentIndex(f);
startDlg->ui.checkBoxAMS->setChecked(ams_packages);
startDlg->ui.checkBoxIDX->setChecked(makeidx_package);
startDlg->ui.lineEditAuthor->setText(author);
if ( startDlg->exec() )
	{
	tag+=startDlg->ui.comboBoxSize->currentText()+QString(",");
	tag+=startDlg->ui.comboBoxPaper->currentText();
	QList<QListWidgetItem *> selectedItems=startDlg->ui.listWidgetOptions->selectedItems();
	for (int i = 0; i < selectedItems.size(); ++i)
		{
		if ( selectedItems.at(i)) opt+=QString(",")+selectedItems.at(i)->text();
		}
	tag+=opt+QString("]{");
	tag+=startDlg->ui.comboBoxClass->currentText()+QString("}");
	tag+=QString("\n");
	if (startDlg->ui.comboBoxEncoding->currentText()!="NONE") tag+=QString("\\usepackage[")+startDlg->ui.comboBoxEncoding->currentText()+QString("]{inputenc}");
	tag+=QString("\n");
	if (startDlg->ui.comboBoxEncoding->currentText().startsWith("utf8"))
		{
		tag+=QString("\\usepackage{ucs}\n");
		li=li+1;
		}
	if (startDlg->ui.checkBoxAMS->isChecked())
		{
		tag+=QString("\\usepackage{amsmath}\n\\usepackage{amsfonts}\n\\usepackage{amssymb}\n");
		li=li+3;
		}
	if (startDlg->ui.checkBoxIDX->isChecked())
		{
		tag+=QString("\\usepackage{makeidx}\n");
		li=li+1;
		}
	if (startDlg->ui.lineEditAuthor->text()!="")
		{
		tag+="\\author{"+startDlg->ui.lineEditAuthor->text()+"}\n";
		li=li+1;
		}
	if (startDlg->ui.lineEditTitle->text()!="")
		{
		tag+="\\title{"+startDlg->ui.lineEditTitle->text()+"}\n";
		li=li+1;
		}
	tag+=QString("\\begin{document}\n\n\\end{document}");
	InsertTag(tag,0,li);
	document_class=startDlg->ui.comboBoxClass->currentText();
	typeface_size=startDlg->ui.comboBoxSize->currentText();
	paper_size=startDlg->ui.comboBoxPaper->currentText();
	document_encoding=startDlg->ui.comboBoxEncoding->currentText();
	ams_packages=startDlg->ui.checkBoxAMS->isChecked();
	makeidx_package=startDlg->ui.checkBoxIDX->isChecked();
	author=startDlg->ui.lineEditAuthor->text();
	userClassList=startDlg->otherClassList;
	userPaperList=startDlg->otherPaperList;
	userEncodingList=startDlg->otherEncodingList;
	userOptionsList=startDlg->otherOptionsList;
	}
}

void Texmaker::InsertBib1()
{
QString tag = QString("@Article{,\n");
tag+="author = {},\n";
tag+="title = {},\n";
tag+="journal = {},\n";
tag+="year = {},\n";
tag+="OPTkey = {},\n";
tag+="OPTvolume = {},\n";
tag+="OPTnumber = {},\n";
tag+="OPTpages = {},\n";
tag+="OPTmonth = {},\n";
tag+="OPTnote = {},\n";
tag+="OPTannote = {}\n";
tag+="}\n";
InsertTag(tag,9,0);
OutputTextEdit->insertLine("Bib fields - Article in Journal");
OutputTextEdit->insertLine( "OPT.... : optionnal fields (use the 'Clean' command to remove them)");
}
void Texmaker::InsertBib2()
{
QString tag = QString("@InProceedings{,\n");
tag+="author = {},\n";
tag+="title = {},\n";
tag+="booktitle = {},\n";
tag+="OPTcrossref = {},\n";
tag+="OPTkey = {},\n";
tag+="OPTpages = {},\n";
tag+="OPTyear = {},\n";
tag+="OPTeditor = {},\n";
tag+="OPTvolume = {},\n";
tag+="OPTnumber = {},\n";
tag+="OPTseries = {},\n";
tag+="OPTaddress = {},\n";
tag+="OPTmonth = {},\n";
tag+="OPTorganization = {},\n";
tag+="OPTpublisher = {},\n";
tag+="OPTnote = {},\n";
tag+="OPTannote = {}\n";
tag+="}\n";
InsertTag(tag,15,0);
OutputTextEdit->insertLine("Bib fields - Article in Conference Proceedings");
OutputTextEdit->insertLine( "OPT.... : optionnal fields (use the 'Clean' command to remove them)");
}
void Texmaker::InsertBib3()
{
QString tag = QString("@InCollection{,\n");
tag+="author = {},\n";
tag+="title = {},\n";
tag+="booktitle = {},\n";
tag+="OPTcrossref = {},\n";
tag+="OPTkey = {},\n";
tag+="OPTpages = {},\n";
tag+="OPTpublisher = {},\n";
tag+="OPTyear = {},\n";
tag+="OPTeditor = {},\n";
tag+="OPTvolume = {},\n";
tag+="OPTnumber = {},\n";
tag+="OPTseries = {},\n";
tag+="OPTtype = {},\n";
tag+="OPTchapter = {},\n";
tag+="OPTaddress = {},\n";
tag+="OPTedition = {},\n";
tag+="OPTmonth = {},\n";
tag+="OPTnote = {},\n";
tag+="OPTannote = {}\n";
tag+="}\n";
InsertTag(tag,14,0);
OutputTextEdit->insertLine("Bib fields - Article in a Collection");
OutputTextEdit->insertLine( "OPT.... : optionnal fields (use the 'Clean' command to remove them)");
}
void Texmaker::InsertBib4()
{
QString tag = QString("@InBook{,\n");
tag+="ALTauthor = {},\n";
tag+="ALTeditor = {},\n";
tag+="title = {},\n";
tag+="chapter = {},\n";
tag+="publisher = {},\n";
tag+="year = {},\n";
tag+="OPTkey = {},\n";
tag+="OPTvolume = {},\n";
tag+="OPTnumber = {},\n";
tag+="OPTseries = {},\n";
tag+="OPTtype = {},\n";
tag+="OPTaddress = {},\n";
tag+="OPTedition = {},\n";
tag+="OPTmonth = {},\n";
tag+="OPTpages = {},\n";
tag+="OPTnote = {},\n";
tag+="OPTannote = {}\n";
tag+="}\n";
InsertTag(tag,8,0);
OutputTextEdit->insertLine("Bib fields - Chapter or Pages in a Book");
OutputTextEdit->insertLine( "ALT.... : you have the choice between these two fields");
OutputTextEdit->insertLine( "OPT.... : optionnal fields (use the 'Clean' command to remove them)");
}
void Texmaker::InsertBib5()
{
QString tag = QString("@Proceedings{,\n");
tag+="title = {},\n";
tag+="year = {},\n";
tag+="OPTkey = {},\n";
tag+="OPTeditor = {},\n";
tag+="OPTvolume = {},\n";
tag+="OPTnumber = {},\n";
tag+="OPTseries = {},\n";
tag+="OPTaddress = {},\n";
tag+="OPTmonth = {},\n";
tag+="OPTorganization = {},\n";
tag+="OPTpublisher = {},\n";
tag+="OPTnote = {},\n";
tag+="OPTannote = {}\n";
tag+="}\n";
InsertTag(tag,13,0);
OutputTextEdit->insertLine("Bib fields - Conference Proceedings");
OutputTextEdit->insertLine( "OPT.... : optionnal fields (use the 'Clean' command to remove them)");
}
void Texmaker::InsertBib6()
{
QString tag = QString("@Book{,\n");
tag+="ALTauthor = {},\n";
tag+="ALTeditor = {},\n";
tag+="title = {},\n";
tag+="publisher = {},\n";
tag+="year = {},\n";
tag+="OPTkey = {},\n";
tag+="OPTvolume = {},\n";
tag+="OPTnumber = {},\n";
tag+="OPTseries = {},\n";
tag+="OPTaddress = {},\n";
tag+="OPTedition = {},\n";
tag+="OPTmonth = {},\n";
tag+="OPTnote = {},\n";
tag+="OPTannote = {}\n";
tag+="}\n";
InsertTag(tag,6,0);
OutputTextEdit->insertLine("Bib fields - Book");
OutputTextEdit->insertLine( "ALT.... : you have the choice between these two fields");
OutputTextEdit->insertLine( "OPT.... : optionnal fields (use the 'Clean' command to remove them)");
}
void Texmaker::InsertBib7()
{
QString tag = QString("@Booklet{,\n");
tag+="title = {},\n";
tag+="OPTkey = {},\n";
tag+="OPTauthor = {},\n";
tag+="OPThowpublished = {},\n";
tag+="OPTaddress = {},\n";
tag+="OPTmonth = {},\n";
tag+="OPTyear = {},\n";
tag+="OPTnote = {},\n";
tag+="OPTannote = {}\n";
tag+="}\n";
InsertTag(tag,9,0);
OutputTextEdit->insertLine("Bib fields - Booklet");
OutputTextEdit->insertLine( "OPT.... : optionnal fields (use the 'Clean' command to remove them)");
}
void Texmaker::InsertBib8()
{
QString tag = QString("@PhdThesis{,\n");
tag+="author = {},\n";
tag+="title = {},\n";
tag+="school = {},\n";
tag+="year = {},\n";
tag+="OPTkey = {},\n";
tag+="OPTtype = {},\n";
tag+="OPTaddress = {},\n";
tag+="OPTmonth = {},\n";
tag+="OPTnote = {},\n";
tag+="OPTannote = {}\n";
tag+="}\n";
InsertTag(tag,11,0);
OutputTextEdit->insertLine("Bib fields - PhD. Thesis");
OutputTextEdit->insertLine( "OPT.... : optionnal fields (use the 'Clean' command to remove them)");
}
void Texmaker::InsertBib9()
{
QString tag = QString("@MastersThesis{,\n");
tag+="author = {},\n";
tag+="title = {},\n";
tag+="school = {},\n";
tag+="year = {},\n";
tag+="OPTkey = {},\n";
tag+="OPTtype = {},\n";
tag+="OPTaddress = {},\n";
tag+="OPTmonth = {},\n";
tag+="OPTnote = {},\n";
tag+="OPTannote = {}\n";
tag+="}\n";
InsertTag(tag,15,0);
OutputTextEdit->insertLine("Bib fields - Master's Thesis");
OutputTextEdit->insertLine( "OPT.... : optionnal fields (use the 'Clean' command to remove them)");
}
void Texmaker::InsertBib10()
{
QString tag = QString("@TechReport{,\n");
tag+="author = {},\n";
tag+="title = {},\n";
tag+="institution = {},\n";
tag+="year = {},\n";
tag+="OPTkey = {},\n";
tag+="OPTtype = {},\n";
tag+="OPTnumber = {},\n";
tag+="OPTaddress = {},\n";
tag+="OPTmonth = {},\n";
tag+="OPTnote = {},\n";
tag+="OPTannote = {}\n";
tag+="}\n";
InsertTag(tag,12,0);
OutputTextEdit->insertLine("Bib fields - Technical Report");
OutputTextEdit->insertLine( "OPT.... : optionnal fields (use the 'Clean' command to remove them)");
}
void Texmaker::InsertBib11()
{
QString tag = QString("@Manual{,\n");
tag+="title = {},\n";
tag+="OPTkey = {},\n";
tag+="OPTauthor = {},\n";
tag+="OPTorganization = {},\n";
tag+="OPTaddress = {},\n";
tag+="OPTedition = {},\n";
tag+="OPTmonth = {},\n";
tag+="OPTyear = {},\n";
tag+="OPTnote = {},\n";
tag+="OPTannote = {}\n";
tag+="}\n";
InsertTag(tag,8,0);
OutputTextEdit->insertLine("Bib fields - Technical Manual");
OutputTextEdit->insertLine( "OPT.... : optionnal fields (use the 'Clean' command to remove them)");
}
void Texmaker::InsertBib12()
{
QString tag = QString("@Unpublished{,\n");
tag+="author = {},\n";
tag+="title = {},\n";
tag+="note = {},\n";
tag+="OPTkey = {},\n";
tag+="OPTmonth = {},\n";
tag+="OPTyear = {},\n";
tag+="OPTannote = {}\n";
tag+="}\n";
InsertTag(tag,13,0);
OutputTextEdit->insertLine("Bib fields - Unpublished");
OutputTextEdit->insertLine( "OPT.... : optionnal fields (use the 'Clean' command to remove them)");
}
void Texmaker::InsertBib13()
{
QString tag = QString("@Misc{,\n");
tag+="OPTkey = {},\n";
tag+="OPTauthor = {},\n";
tag+="OPTtitle = {},\n";
tag+="OPThowpublished = {},\n";
tag+="OPTmonth = {},\n";
tag+="OPTyear = {},\n";
tag+="OPTnote = {},\n";
tag+="OPTannote = {}\n";
tag+="}\n";
InsertTag(tag,6,0);
OutputTextEdit->insertLine("Bib fields - Miscellaneous");
OutputTextEdit->insertLine( "OPT.... : optionnal fields (use the 'Clean' command to remove them)");
}

void Texmaker::CleanBib()
{
    if ( !currentEditorView() ) return;
    currentEditorView()->cleanBib();
}

void Texmaker::InsertUserTag1()
{
if (UserMenuTag[0].left(1)=="%")
	{
	QString t=UserMenuTag[0];
	t=t.remove(0,1);
	QString s="\\begin{"+t+"}\n\n\\end{"+t+"}\n";
	InsertTag(s,0,1);
	}
else
	{
	if (!UserMenuTag[0].contains(QRegExp("\n"))) InsertTag(UserMenuTag[0]+" ",UserMenuTag[0].length()+1,0);
	else InsertTag(UserMenuTag[0],0,0);
	}
}

void Texmaker::InsertUserTag2()
{
if (UserMenuTag[1].left(1)=="%")
	{
	QString t=UserMenuTag[1];
	t=t.remove(0,1);
	QString s="\\begin{"+t+"}\n\n\\end{"+t+"}\n";
	InsertTag(s,0,1);
	}
else
	{
	if (!UserMenuTag[1].contains(QRegExp("\n"))) InsertTag(UserMenuTag[1]+" ",UserMenuTag[1].length()+1,0);
	else InsertTag(UserMenuTag[1],0,0);
	}
}

void Texmaker::InsertUserTag3()
{
if (UserMenuTag[2].left(1)=="%")
	{
	QString t=UserMenuTag[2];
	t=t.remove(0,1);
	QString s="\\begin{"+t+"}\n\n\\end{"+t+"}\n";
	InsertTag(s,0,1);
	}
else
	{
	if (!UserMenuTag[2].contains(QRegExp("\n"))) InsertTag(UserMenuTag[2]+" ",UserMenuTag[2].length()+1,0);
	else InsertTag(UserMenuTag[2],0,0);
	}
}

void Texmaker::InsertUserTag4()
{
if (UserMenuTag[3].left(1)=="%")
	{
	QString t=UserMenuTag[3];
	t=t.remove(0,1);
	QString s="\\begin{"+t+"}\n\n\\end{"+t+"}\n";
	InsertTag(s,0,1);
	}
else
	{
	if (!UserMenuTag[3].contains(QRegExp("\n"))) InsertTag(UserMenuTag[3]+" ",UserMenuTag[3].length()+1,0);
	else InsertTag(UserMenuTag[3],0,0);
	}
}

void Texmaker::InsertUserTag5()
{
if (UserMenuTag[4].left(1)=="%")
	{
	QString t=UserMenuTag[4];
	t=t.remove(0,1);
	QString s="\\begin{"+t+"}\n\n\\end{"+t+"}\n";
	InsertTag(s,0,1);
	}
else
	{
	if (!UserMenuTag[4].contains(QRegExp("\n"))) InsertTag(UserMenuTag[4]+" ",UserMenuTag[4].length()+1,0);
	else InsertTag(UserMenuTag[4],0,0);
	}
}

void Texmaker::InsertUserTag6()
{
if (UserMenuTag[5].left(1)=="%")
	{
	QString t=UserMenuTag[5];
	t=t.remove(0,1);
	QString s="\\begin{"+t+"}\n\n\\end{"+t+"}\n";
	InsertTag(s,0,1);
	}
else
	{
	if (!UserMenuTag[5].contains(QRegExp("\n"))) InsertTag(UserMenuTag[5]+" ",UserMenuTag[5].length()+1,0);
	else InsertTag(UserMenuTag[5],0,0);
	}
}

void Texmaker::InsertUserTag7()
{
if (UserMenuTag[6].left(1)=="%")
	{
	QString t=UserMenuTag[6];
	t=t.remove(0,1);
	QString s="\\begin{"+t+"}\n\n\\end{"+t+"}\n";
	InsertTag(s,0,1);
	}
else
	{
	if (!UserMenuTag[6].contains(QRegExp("\n"))) InsertTag(UserMenuTag[6]+" ",UserMenuTag[6].length()+1,0);
	else InsertTag(UserMenuTag[6],0,0);
	}
}

void Texmaker::InsertUserTag8()
{
if (UserMenuTag[7].left(1)=="%")
	{
	QString t=UserMenuTag[7];
	t=t.remove(0,1);
	QString s="\\begin{"+t+"}\n\n\\end{"+t+"}\n";
	InsertTag(s,0,1);
	}
else
	{
	if (!UserMenuTag[7].contains(QRegExp("\n"))) InsertTag(UserMenuTag[7]+" ",UserMenuTag[7].length()+1,0);
	else InsertTag(UserMenuTag[7],0,0);
	}
}

void Texmaker::InsertUserTag9()
{
if (UserMenuTag[8].left(1)=="%")
	{
	QString t=UserMenuTag[8];
	t=t.remove(0,1);
	QString s="\\begin{"+t+"}\n\n\\end{"+t+"}\n";
	InsertTag(s,0,1);
	}
else
	{
	if (!UserMenuTag[8].contains(QRegExp("\n"))) InsertTag(UserMenuTag[8]+" ",UserMenuTag[8].length()+1,0);
	else InsertTag(UserMenuTag[8],0,0);
	}
}

void Texmaker::InsertUserTag10()
{
if (UserMenuTag[9].left(1)=="%")
	{
	QString t=UserMenuTag[9];
	t=t.remove(0,1);
	QString s="\\begin{"+t+"}\n\n\\end{"+t+"}\n";
	InsertTag(s,0,1);
	}
else
	{
	if (!UserMenuTag[9].contains(QRegExp("\n"))) InsertTag(UserMenuTag[9]+" ",UserMenuTag[9].length()+1,0);
	else InsertTag(UserMenuTag[9],0,0);
	}
}

void Texmaker::EditUserMenu()
{
QAction *Act;
UserMenuDialog *umDlg = new UserMenuDialog(this,tr("Edit User &Tags"));
for ( int i = 0; i <= 9; i++ )
    {
    umDlg->Name[i]=UserMenuName[i];
    umDlg->Tag[i]=UserMenuTag[i];
    umDlg->init();
    }
if ( umDlg->exec() )
	{
	for ( int i = 0; i <= 9; i++ )
		{
		UserMenuName[i]=umDlg->Name[i];
		UserMenuTag[i]=umDlg->Tag[i];
		}
	user11Menu->clear();
	Act = new QAction("1: "+UserMenuName[0], this);
	Act->setShortcut(Qt::SHIFT+Qt::Key_F1);
	connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag1()));
	user11Menu->addAction(Act);
	Act = new QAction("2: "+UserMenuName[1], this);
	Act->setShortcut(Qt::SHIFT+Qt::Key_F2);
	connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag2()));
	user11Menu->addAction(Act);
	Act = new QAction("3: "+UserMenuName[2], this);
	Act->setShortcut(Qt::SHIFT+Qt::Key_F3);
	connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag3()));
	user11Menu->addAction(Act);
	Act = new QAction("4: "+UserMenuName[3], this);
	Act->setShortcut(Qt::SHIFT+Qt::Key_F4);
	connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag4()));
	user11Menu->addAction(Act);
	Act = new QAction("5: "+UserMenuName[4], this);
	Act->setShortcut(Qt::SHIFT+Qt::Key_F5);
	connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag5()));
	user11Menu->addAction(Act);
	Act = new QAction("6: "+UserMenuName[5], this);
	Act->setShortcut(Qt::SHIFT+Qt::Key_F6);
	connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag6()));
	user11Menu->addAction(Act);
	Act = new QAction("7: "+UserMenuName[6], this);
	Act->setShortcut(Qt::SHIFT+Qt::Key_F7);
	connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag7()));
	user11Menu->addAction(Act);
	Act = new QAction("8: "+UserMenuName[7], this);
	Act->setShortcut(Qt::SHIFT+Qt::Key_F8);
	connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag8()));
	user11Menu->addAction(Act);
	Act = new QAction("9: "+UserMenuName[8], this);
	Act->setShortcut(Qt::SHIFT+Qt::Key_F9);
	connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag9()));
	user11Menu->addAction(Act);
	Act = new QAction("10: "+UserMenuName[9], this);
	Act->setShortcut(Qt::SHIFT+Qt::Key_F10);
	connect(Act, SIGNAL(triggered()), this, SLOT(InsertUserTag10()));
	user11Menu->addAction(Act);
	user11Menu->addSeparator();
	Act = new QAction(tr("Edit User &Tags"), this);
	connect(Act, SIGNAL(triggered()), this, SLOT(EditUserMenu()));
	user11Menu->addAction(Act);
	}
}

void Texmaker::SectionCommand(const QString& text)
{
if ( !currentEditorView() ) return;
InsertStructFromString("\\"+text);
}

void Texmaker::OtherCommand(const QString& text)
{
if ( !currentEditorView() ) return;
if (text=="label")
	{
	InsertFromString("\\label{} /7/0");
	return;
	}
if (text=="ref")
	{
	InsertRef();
	return;
	}
if (text=="pageref")
	{
	InsertPageRef();
	return;
	}
if (text=="index")
	{
	InsertFromString("\\index{}/7/0");
	return;
	}
if (text=="cite")
	{
	InsertFromString("\\cite{}/6/0");
	return;
	}
if (text=="footnote")
	{
	InsertFromString("\\footnote{}/10/0");
	return;
	}
}

void Texmaker::InsertRef()
{
UpdateStructure();
QString tag="";
RefDialog *refDlg = new RefDialog(this,"Labels");
refDlg->ui.comboBox->addItems(labelitem);
if (!labelitem.isEmpty() && refDlg->exec() )
	{
	tag="\\ref{"+refDlg->ui.comboBox->currentText()+"}";
	InsertTag(tag,tag.length(),0);
	}
else InsertTag("\\ref{}",5,0);
OutputTextEdit->insertLine( "\\ref{key}");
}

void Texmaker::InsertPageRef()
{
UpdateStructure();
QString tag="";
RefDialog *refDlg = new RefDialog(this,"Labels");
refDlg->ui.comboBox->addItems(labelitem);
if (!labelitem.isEmpty() && refDlg->exec() )
	{
	tag="\\pageref{"+refDlg->ui.comboBox->currentText()+"}";
	InsertTag(tag,tag.length(),0);
	}
else InsertTag("\\pageref{}",9,0);
OutputTextEdit->insertLine( "\\pageref{key}");
}

void Texmaker::SizeCommand(const QString& text)
{
if ( !currentEditorView() ) return;
if (text=="tiny")
	{
	InsertWithSelectionFromString("\\begin{tiny}/\\end{tiny}/12/0");
	return;
	}
if (text=="scriptsize")
	{
	InsertWithSelectionFromString("\\begin{scriptsize}/\\end{scriptsize}/18/0");
	return;
	}
if (text=="footnotesize")
	{
	InsertWithSelectionFromString("\\begin{footnotesize}/\\end{footnotesize}/20/0");
	return;
	}
if (text=="small")
	{
	InsertWithSelectionFromString("\\begin{small}/\\end{small}/13/0");
	return;
	}
if (text=="normalsize")
	{
	InsertWithSelectionFromString("\\begin{normalsize}/\\end{normalsize}/18/0");
	return;
	}
if (text=="large")
	{
	InsertWithSelectionFromString("\\begin{large}/\\end{large}/13/0");
	return;
	}
if (text=="Large")
	{
	InsertWithSelectionFromString("\\begin{Large}/\\end{Large}/13/0");
	return;
	}
if (text=="LARGE")
	{
	InsertWithSelectionFromString("\\begin{LARGE}/\\end{LARGE}/13/0");
	return;
	}
if (text=="huge")
	{
	InsertWithSelectionFromString("\\begin{huge}/\\end{huge}/12/0");
	return;
	}
if (text=="Huge")
	{
	InsertWithSelectionFromString("\\begin{Huge}/\\end{Huge}/12/0");
	return;
	}
}

void Texmaker::LeftDelimiter(const QString& text)
{
if (text=="left (") InsertTag("\\left( ",7,0);
if (text=="left [") InsertTag("\\left[ ",7,0);
if (text=="left {") InsertTag("\\left\\lbrace ",13,0);
if (text=="left <") InsertTag("\\left\\langle ",13,0);
if (text=="left )") InsertTag("\\left) ",7,0);
if (text=="left ]") InsertTag("\\left] ",7,0);
if (text=="left }") InsertTag("\\left\\rbrace ",13,0);
if (text=="left >") InsertTag("\\left\\rangle ",13,0);
if (text=="left.") InsertTag("\\left. ",7,0);
}

void Texmaker::RightDelimiter(const QString& text)
{
if (text=="right (") InsertTag("\\right( ",8,0);
if (text=="right [") InsertTag("\\right[ ",8,0);
if (text=="right {") InsertTag("\\right\\lbrace ",14,0);
if (text=="right <") InsertTag("\\right\\langle ",14,0);
if (text=="right )") InsertTag("\\right) ",8,0);
if (text=="right ]") InsertTag("\\right] ",8,0);
if (text=="right }") InsertTag("\\right\\rbrace ",14,0);
if (text=="right >") InsertTag("\\right\\rangle ",14,0);
if (text=="right.") InsertTag("\\right. ",8,0);
}

///////////////TOOLS////////////////////
void Texmaker::RunCommand(QString comd,bool waitendprocess)
{

QString finame;
QString commandline=comd;
QByteArray result;
if (singlemode) {finame=getName();}
else {finame=MasterName;}
if ((singlemode && !currentEditorView()) || finame=="untitled" || finame=="")
	{
	QMessageBox::warning( this,tr("Error"),tr("Can't detect the file name"));
	return;
	}
fileSave();
QFileInfo fi(finame);
QString basename=fi.completeBaseName();
commandline.replace("%","\""+basename+"\"");
//commandline.replace("%",basename);
int temp;int currentline;
currentEditorView()->editor->getCursorPosition(currentline,temp);
commandline.replace("@",QString::number(currentline));
proc = new QProcess( this );
proc->setWorkingDirectory(fi.absolutePath());

connect(proc, SIGNAL(readyReadStandardError()),this, SLOT(readFromStderr()));
//connect(proc, SIGNAL(readyReadStandardOutput()),this, SLOT(readFromStdoutput()));
connect(proc, SIGNAL(finished(int)),this, SLOT(SlotEndProcess(int)));
OutputTextEdit->clear();
OutputTableWidget->hide();
//OutputTextEdit->insertLine(commandline+"\n");
proc->start(commandline);
if (!proc->waitForStarted(1000))
	{
	ERRPROCESS=true;
	OutputTextEdit->insertLine("Error : could not start the command\n");
	return;
	}
else OutputTextEdit->insertLine("Process started\n");
FINPROCESS=false;
if (waitendprocess)
	{
	while (!FINPROCESS)
		{
		qApp->instance()->processEvents(QEventLoop::ExcludeUserInputEvents);
		}
	}
}

void Texmaker::readFromStderr()
{
QByteArray result=proc->readAllStandardError();
QString t=QString(result);
t=t.simplified();
if (!t.isEmpty()) OutputTextEdit->insertLine(t+"\n");
}

// void Texmaker::readFromStdoutput()
// {
// QByteArray result=proc->readAllStandardOutput ();
// OutputTextEdit->insertLine(QString(result)+"\n");
// }

void Texmaker::SlotEndProcess(int err)
{
FINPROCESS=true;
QString result=((err) ? "Process exited with error(s)" : "Process exited normally");
if (err) ERRPROCESS=true;
OutputTextEdit->insertLine(result);
stat2->setText(QString(" %1 ").arg(tr("Ready")));
}

void Texmaker::QuickBuild()
{
stat2->setText(QString(" %1 ").arg(tr("Quick Build")));
ERRPROCESS=false;
switch (quickmode)
 {
  case 1:
    {
    stat2->setText(QString(" %1 ").arg("Latex"));
    RunCommand(latex_command,true);
    if (ERRPROCESS && !LogExists())
        {
	QMessageBox::warning( this,tr("Error"),tr("Could not start the command."));
	return;
	}
    ViewLog();
    if (NoLatexErrors())
    	{
	stat2->setText(QString(" %1 ").arg("Dvips"));
    	if (!ERRPROCESS) RunCommand(dvips_command,true);
        else return;
	if (!ERRPROCESS) ViewPS();
        else return;
	}
    else {NextError();}
    }break;
  case 2:
    {
    stat2->setText(QString(" %1 ").arg("Latex"));
    RunCommand(latex_command,true);
    if (ERRPROCESS && !LogExists())
        {
	QMessageBox::warning( this,tr("Error"),tr("Could not start the command."));
	return;
	}
    ViewLog();
    if (NoLatexErrors())
    	{
	if (!ERRPROCESS) ViewDvi();
        else return;
	}
    else {NextError();}
    }break;
 case 3:
    {
    stat2->setText(QString(" %1 ").arg("Pdf Latex"));
    RunCommand(pdflatex_command,true);
    if (ERRPROCESS && !LogExists())
        {
	QMessageBox::warning( this,tr("Error"),tr("Could not start the command."));
	return;
	}
    ViewLog();
    if (NoLatexErrors())
    	{
	if (!ERRPROCESS) ViewPDF();
        else return;
	}
    else {NextError();}
    }break;
 case 4:
    {
    stat2->setText(QString(" %1 ").arg("Latex"));
    RunCommand(latex_command,true);
    if (ERRPROCESS && !LogExists())
        {
	QMessageBox::warning( this,tr("Error"),tr("Could not start the command."));
	return;
	}
    ViewLog();
    if (NoLatexErrors())
    	{
	stat2->setText(QString(" %1 ").arg("Dvi to Pdf"));
	if (!ERRPROCESS) RunCommand(dvipdf_command,true);
        else return;
	if (!ERRPROCESS) ViewPDF();
        else return;
	}
    else {NextError();}
    }break;
 case 5:
    {
    stat2->setText(QString(" %1 ").arg("Latex"));
    RunCommand(latex_command,true);
    if (ERRPROCESS && !LogExists())
        {
	QMessageBox::warning( this,tr("Error"),tr("Could not start the command."));
	return;
	}
    ViewLog();
    if (NoLatexErrors())
    	{
	stat2->setText(QString(" %1 ").arg("Dvips"));
	if (!ERRPROCESS) RunCommand(dvips_command,true);
        else return;
	stat2->setText(QString(" %1 ").arg("Ps to Pdf"));
	if (!ERRPROCESS) RunCommand(ps2pdf_command,true);
        else return;
	if (!ERRPROCESS) ViewPDF();
	}
    else {NextError();}
    }break;
 case 6:
    {
    QStringList commandList=userquick_command.split("|");
    for (int i = 0; i < commandList.size(); ++i)
	{
	if ((!ERRPROCESS)&&(!commandList.at(i).isEmpty())) RunCommand(commandList.at(i),true);
        else return;
	}
    }break;
 }
if (NoLatexErrors()) ViewLog();
//ViewLog();
//DisplayLatexError();
}

void Texmaker::Latex()
{
stat2->setText(QString(" %1 ").arg("Latex"));
RunCommand(latex_command,false);
}

void Texmaker::ViewDvi()
{
stat2->setText(QString(" %1 ").arg(tr("View Dvi file")));
RunCommand(viewdvi_command,false);
}

void Texmaker::DviToPS()
{
stat2->setText(QString(" %1 ").arg("Dvips"));
RunCommand(dvips_command,false);
}

void Texmaker::ViewPS()
{
stat2->setText(QString(" %1 ").arg(tr("View PS file")));
RunCommand(viewps_command,false);
}

void Texmaker::PDFLatex()
{
stat2->setText(QString(" %1 ").arg("Pdf Latex"));
RunCommand(pdflatex_command,false);
}

void Texmaker::ViewPDF()
{
stat2->setText(QString(" %1 ").arg(tr("View Pdf file")));
RunCommand(viewpdf_command,false);
}

void Texmaker::MakeBib()
{
stat2->setText(QString(" %1 ").arg("Bibtex"));
RunCommand(bibtex_command,false);
}

void Texmaker::MakeIndex()
{
stat2->setText(QString(" %1 ").arg("Make index"));
RunCommand(makeindex_command,false);
}

void Texmaker::PStoPDF()
{
stat2->setText(QString(" %1 ").arg("Ps -> Pdf"));
RunCommand(ps2pdf_command,false);
}

void Texmaker::DVItoPDF()
{
stat2->setText(QString(" %1 ").arg("Dvi -> Pdf"));
RunCommand(dvipdf_command,false);
}

void Texmaker::MetaPost()
{
stat2->setText(QString(" %1 ").arg("Mpost"));
QString finame=getName();
QFileInfo fi(finame);
RunCommand(metapost_command+fi.completeBaseName()+"."+fi.suffix(),false);
}

void Texmaker::CleanAll()
{
QString finame,f;
if (singlemode) {finame=getName();}
else {finame=MasterName;}
if ((singlemode && !currentEditorView()) || finame=="untitled" || finame=="")
	{
	QMessageBox::warning( this,tr("Error"),tr("Can't detect the file name"));
	return;
	}
fileSave();
QFileInfo fi(finame);
QString name=fi.absoluteFilePath();
QString ext=fi.suffix();
QString basename=name.left(name.length()-ext.length()-1);
QStringList extension=QString(".log,.aux,.dvi,.lof,.lot,.bit,.idx,.glo,.bbl,.ilg,.toc,.ind").split(",");
int query =QMessageBox::warning(this, "TexMakerX", tr("Delete the output files generated by LaTeX ?\n(.log,.aux,.dvi,.lof,.lot,.bit,.idx,.glo,.bbl,.ilg,.toc,.ind)"),tr("Delete Files"), tr("Cancel") );
if (query==0)
	{
	stat2->setText(QString(" %1 ").arg(tr("Clean")));
	for ( QStringList::Iterator it = extension.begin(); it != extension.end(); ++it )
		{
		f=basename+*it;
		if (QFile::exists(f))
			{
			QFile file(f);
			file.open( QIODevice::ReadOnly );
			file.remove();
			}
		}

	}
}

void Texmaker::UserTool1()
{
QStringList commandList=UserToolCommand[0].split("|");
ERRPROCESS=false;
for (int i = 0; i < commandList.size(); ++i)
	{
	if ((!ERRPROCESS)&&(!commandList.at(i).isEmpty())) RunCommand(commandList.at(i),true);
        else return;
	}
}

void Texmaker::UserTool2()
{
QStringList commandList=UserToolCommand[1].split("|");
ERRPROCESS=false;
for (int i = 0; i < commandList.size(); ++i)
	{
	if ((!ERRPROCESS)&&(!commandList.at(i).isEmpty())) RunCommand(commandList.at(i),true);
        else return;
	}
}

void Texmaker::UserTool3()
{
QStringList commandList=UserToolCommand[2].split("|");
ERRPROCESS=false;
for (int i = 0; i < commandList.size(); ++i)
	{
	if ((!ERRPROCESS)&&(!commandList.at(i).isEmpty())) RunCommand(commandList.at(i),true);
        else return;
	}
}

void Texmaker::UserTool4()
{
QStringList commandList=UserToolCommand[3].split("|");
ERRPROCESS=false;
for (int i = 0; i < commandList.size(); ++i)
	{
	if ((!ERRPROCESS)&&(!commandList.at(i).isEmpty())) RunCommand(commandList.at(i),true);
        else return;
	}
}

void Texmaker::UserTool5()
{
QStringList commandList=UserToolCommand[4].split("|");
ERRPROCESS=false;
for (int i = 0; i < commandList.size(); ++i)
	{
	if ((!ERRPROCESS)&&(!commandList.at(i).isEmpty())) RunCommand(commandList.at(i),true);
        else return;
	}
}

void Texmaker::EditUserTool()
{
QAction *Act;
UserToolDialog *utDlg = new UserToolDialog(this,tr("Edit User &Commands"));
for ( int i = 0; i <= 4; i++ )
	{
	utDlg->Name[i]=UserToolName[i];
	utDlg->Tool[i]=UserToolCommand[i];
	utDlg->init();
	}
if ( utDlg->exec() )
	{
	for ( int i = 0; i <= 4; i++ )
		{
		UserToolName[i]=utDlg->Name[i];
		UserToolCommand[i]=utDlg->Tool[i];
		}
	user12Menu->clear();
	Act = new QAction("1: "+UserToolName[0], this);
	Act->setShortcut(Qt::SHIFT+Qt::ALT+Qt::Key_F1);
	connect(Act, SIGNAL(triggered()), this, SLOT(UserTool1()));
	user12Menu->addAction(Act);
	Act = new QAction("2: "+UserToolName[1], this);
	Act->setShortcut(Qt::SHIFT+Qt::ALT+Qt::Key_F2);
	connect(Act, SIGNAL(triggered()), this, SLOT(UserTool2()));
	user12Menu->addAction(Act);
	Act = new QAction("3: "+UserToolName[2], this);
	Act->setShortcut(Qt::SHIFT+Qt::ALT+Qt::Key_F3);
	connect(Act, SIGNAL(triggered()), this, SLOT(UserTool3()));
	user12Menu->addAction(Act);
	Act = new QAction("4: "+UserToolName[3], this);
	Act->setShortcut(Qt::SHIFT+Qt::ALT+Qt::Key_F4);
	connect(Act, SIGNAL(triggered()), this, SLOT(UserTool4()));
	user12Menu->addAction(Act);
	Act = new QAction("5: "+UserToolName[4], this);
	Act->setShortcut(Qt::SHIFT+Qt::ALT+Qt::Key_F5);
	connect(Act, SIGNAL(triggered()), this, SLOT(UserTool5()));
	user12Menu->addAction(Act);
	user12Menu->addSeparator();
	Act = new QAction(tr("Edit User &Commands"), this);
	connect(Act, SIGNAL(triggered()), this, SLOT(EditUserTool()));
	user12Menu->addAction(Act);
	}
}

void Texmaker::EditUserKeyReplacements()
{
UserKeyReplacementsDialog *utDlg = new UserKeyReplacementsDialog(this,tr("Edit &Key Replacements"));
utDlg->UserKeyReplace=UserKeyReplace;
utDlg->UserKeyReplaceAfterWord=UserKeyReplaceAfterWord;
utDlg->UserKeyReplaceBeforeWord=UserKeyReplaceBeforeWord;
utDlg->init();
if ( utDlg->exec() ) {
    UserKeyReplace=utDlg->UserKeyReplace;
    UserKeyReplaceAfterWord=utDlg->UserKeyReplaceAfterWord;
    UserKeyReplaceBeforeWord=utDlg->UserKeyReplaceBeforeWord;
}
}


void Texmaker::WebPublish()
{
    if (!currentEditorView()) return;
    if (!currentEditorView()->editor->getFileEncoding()) return;
QString finame;
fileSave();
if (singlemode) {finame=getName();}
else {finame=MasterName;}
if (finame=="untitled") finame="";
WebPublishDialog *ttwpDlg = new WebPublishDialog(this,tr("Convert to Html"),ghostscript_command,latex_command,dvips_command,
                                                currentEditorView()->editor->getFileEncoding());
ttwpDlg->ui.inputfileEdit->setText(finame);
ttwpDlg->exec();
delete ttwpDlg;
}


void Texmaker::AnalyseText(){
    if (!currentEditorView()) return;
  TextAnalysisDialog *utDlg = new TextAnalysisDialog(this,tr("Text Analysis"));
  utDlg->data=currentEditorView()->editor->text();
  int temp;
  utDlg->selectionStart=currentEditorView()->editor->cursor().selectionStart().position();
  utDlg->selectionEnd=currentEditorView()->editor->cursor().selectionEnd().position();
  utDlg->init();
  for (int i=0;i<StructureTreeWidget->topLevelItemCount ();i++)
      //if (StructureTreeWidget->topLevelItem(i)->text(0)==MasterName)
        utDlg->interpretStructureTree(StructureTreeWidget->topLevelItem(i));

  utDlg->exec();
  delete utDlg;
}
//////////////// MESSAGES - LOG FILE///////////////////////
bool Texmaker::LogExists()
{
QString finame;
if (singlemode) {finame=getName();}
else {finame=MasterName;}
if ((singlemode && !currentEditorView()) ||finame=="untitled" || finame=="")
	{
	return false;
	}
QFileInfo fi(finame);
QString name=fi.absoluteFilePath();
QString ext=fi.suffix();
QString basename=name.left(name.length()-ext.length()-1);
QString logname=basename+".log";
QFileInfo fic(logname);
if (fic.exists() && fic.isReadable()) return true;
else return false;
}

void Texmaker::ViewLog()
{
OutputTextEdit->clear();
logpresent=false;
QString finame;
if (singlemode) {finame=getName();}
else {finame=MasterName;}
if ((singlemode && !currentEditorView()) ||finame=="untitled" || finame=="")
	{
	QMessageBox::warning( this,tr("Error"),tr("Could not start the command."));
	ERRPROCESS=true;
	return;
	}
QFileInfo fi(finame);
QString name=fi.absoluteFilePath();
QString ext=fi.suffix();
QString basename=name.left(name.length()-ext.length()-1);
QString logname=basename+".log";
QString line;
QFileInfo fic(logname);
if (fic.exists() && fic.isReadable() )
	{
	OutputTextEdit->insertLine("LOG FILE :");
	QFile f(logname);
	if ( f.open(QIODevice::ReadOnly) )
		{
		QTextStream t( &f );
//		OutputTextEdit->setPlainText( t.readAll() );
		while ( !t.atEnd() )
			{
			line=t.readLine();
			line=line.simplified();
			if (!line.isEmpty()) OutputTextEdit->append(line);
			}
		}
		f.close();
	LatexError();
	logpresent=true;
	}
else {QMessageBox::warning( this,tr("Error"),tr("Log File not found !"));}
}

void Texmaker::ClickedOnOutput(int l)
{
if ( !currentEditorView() ) return;
currentEditorView()->editor->setCursorPosition(l-1,0);
currentEditorView()->editor->setFocus();
}

void Texmaker::ClickedOnLogLine(QTableWidgetItem *item)
{
if ( !currentEditorView() ) return;
QTableWidget *container=item->tableWidget();
item=container->item(item->row(),3);
QString content=item->text();
int Start, End;
bool ok;
QString s;
QString line="";
//// l. ///
s = content;
Start=End=0;
Start=s.indexOf(QRegExp("l.[0-9]"), End);
if (Start!=-1)
	{
	Start=Start+2;
	s=s.mid(Start,s.length());
	End=s.indexOf(QRegExp("[ a-zA-Z.\\-]"),0);
	if (End!=-1)
	line=s.mid(0,End);
	else
	line=s.mid(0,s.length());
	};
//// line ///
s = content;
Start=End=0;
Start=s.indexOf(QRegExp("line [0-9]"), End);
if (Start!=-1)
	{
	Start=Start+5;
	s=s.mid(Start,s.length());
	End=s.indexOf(QRegExp("[ a-zA-Z.\\-]"),0);
	if (End!=-1)
	line=s.mid(0,End);
	else
	line=s.mid(0,s.length());
	};
//// lines ///
s = content;
Start=End=0;
Start=s.indexOf(QRegExp("lines [0-9]"), End);
if (Start!=-1)
	{
	Start=Start+6;
	s=s.mid(Start,s.length());
	End=s.indexOf(QRegExp("[ a-zA-Z.\\-]"),0);
	if (End!=-1)
	line=s.mid(0,End);
	else
	line=s.mid(0,s.length());
	};
	
int l=line.toInt(&ok,10)-1;
if (ok)
	{
	currentEditorView()->editor->setCursorPosition(l,0);
	currentEditorView()->editor->setFocus();
	}
QString ll=item->data(Qt::UserRole).toString();
int logline=ll.toInt(&ok,10)-1;
OutputTextEdit->setCursorPosition(logline , 0);

}
void Texmaker::OutputViewVisibilityChanged(bool visible){
    if (visible) OutputView->toggleViewAction()->setShortcut(Qt::Key_Escape);
    else OutputView->toggleViewAction()->setShortcut(QKeySequence ());
}

////////////////////////// ERRORS /////////////////////////////
void Texmaker::LatexError()
{
errorFileList.clear();
errorTypeList.clear();
errorLineList.clear();
errorMessageList.clear();
errorLogList.clear();
onlyErrorList.clear();
errorIndex=-1;

QString mot,suivant,lettre,expression,warning,latexerror,badbox;
QStringList pile,filestack;
filestack.clear();
pile.clear();

int j;

int ligne=0;
int par=1;
int errorpar=1;

QRegExp rxWarning1("Warning: (.*) on.*line *(\\d+)");
QRegExp rxWarning2("Warning: (.*)");
QRegExp rxLatexError("(! )*(LaTeX Error:)* *(.*)\\.l\\.(\\d+) *(.*)");
QRegExp rxLineError("l\\.(\\d+)");
QRegExp rxBadBox("at (line|lines) ([0-9]+)");


QTextBlock tb = OutputTextEdit->document()->begin();
while (tb.isValid())
 	{
	errorpar=par;
	expression=tb.text();
	j=0;
	pile.clear();
	while (j<expression.length())
		{
		lettre=expression.mid(j,1);
		if (lettre=="(" || lettre==")")
			{
			pile.prepend(lettre);
			j+=1;
			}
		else
			{
			mot="";
			while (j<expression.length() && (expression.mid(j,1)!="(" && expression.mid(j,1)!=")"))
				{
				mot+=expression.mid(j,1);
				j+=1;
				}
			pile.prepend(mot);
			}
		}
	while (pile.count()>0)
		{
		mot=pile.last();
		pile.removeLast();
		if (mot=="(" && pile.count()>0)
			{
			suivant=pile.last();
			pile.removeLast();
			filestack.append(suivant.remove("./"));
			}
		else if (mot==")" && filestack.count()>0) filestack.removeLast();
		}
	if (expression.contains("Warning"))
		{
		warning=expression.trimmed();
		while (tb.isValid() && !expression.contains(QRegExp("\\.$")))
			{
			par++;
			tb=tb.next();
			if (tb.isValid())
				{
				expression=tb.text();
				warning+=expression.trimmed();
				}
			}
		if ( rxWarning1.indexIn(warning) != -1 )
			{
			if (!filestack.isEmpty()) errorFileList.append(filestack.last());
			else errorFileList.append("");
			errorTypeList.append("Warning");
			errorLineList.append(rxWarning1.cap(2));
			errorMessageList.append(rxWarning1.cap(1).replace("*",""));
			errorLogList.append(QString::number(errorpar));
			}
		else if ( rxWarning2.indexIn(warning) != -1 )
			{
			if (!filestack.isEmpty()) errorFileList.append(filestack.last());
			else errorFileList.append("");
			errorTypeList.append("Warning");
			errorLineList.append("1");
			errorMessageList.append(rxWarning2.cap(1).replace("*",""));
			errorLogList.append(QString::number(errorpar));
			}
		else
			{
			if (!filestack.isEmpty()) errorFileList.append(filestack.last());
			else errorFileList.append("");
			errorTypeList.append("Warning");
			errorLineList.append("1");
			errorMessageList.append(warning.replace("*",""));
			errorLogList.append(QString::number(errorpar));
 			}
		errorpar=par;
		}
	else if (expression.contains(QRegExp("^!")))
		{
		latexerror=expression.trimmed();
		while (tb.isValid() && !expression.contains(rxLineError))
			{
			par++;
			tb=tb.next();
			if (tb.isValid())
				{
				expression=tb.text();
				latexerror+=expression.trimmed();
				}
			}
		//qDebug() << latexerror;
// 		if ( rxLatexError.indexIn(latexerror) != -1 )
// 			{
// 			qDebug() << rxLatexError.cap(1);
// 			qDebug() << rxLatexError.cap(2);
// 			qDebug() << rxLatexError.cap(3);
// 			qDebug() << rxLatexError.cap(4);
// 			qDebug() << rxLatexError.cap(5);
// 			errorFileList.append(filestack.last());
// 			errorTypeList.append("Error");
// 			errorLineList.append(rxLatexError.cap(1));
// 			errorMessageList.append(rxLatexError.cap(3)+" :"+rxLatexError.cap(5));
// 			}
		if ( rxLineError.indexIn(latexerror) != -1 )
			{
			//qDebug() << "Error";
			if (!filestack.isEmpty()) errorFileList.append(filestack.last());
			else errorFileList.append("");
			errorTypeList.append("Error");
			errorLineList.append(rxLineError.cap(1));
			errorMessageList.append(latexerror.remove(rxLineError).replace("*",""));
			errorLogList.append(QString::number(errorpar));
			}
		else 
			{
			//qDebug() << "Error";
			if (!filestack.isEmpty()) errorFileList.append(filestack.last());
			else errorFileList.append("");
			errorTypeList.append("Error");
			errorLineList.append("1");
			errorMessageList.append(latexerror.replace("*",""));
			errorLogList.append(QString::number(errorpar));
			}
		errorpar=par;
		}
	else if (expression.contains(QRegExp("^(Over|Under)(full \\\\[hv]box .*)")))
		{
		badbox=expression.trimmed();
		while (tb.isValid() && !expression.contains(QRegExp("(.*) at line")))
			{
			par++;
			tb=tb.next();
			if (tb.isValid())
				{
				expression=tb.text();
				badbox+=expression.trimmed();
				}
			}
		if ( rxBadBox.indexIn(badbox) != -1 )
			{
			if (!filestack.isEmpty()) errorFileList.append(filestack.last());
			else errorFileList.append("");
			errorTypeList.append("Badbox");
			errorLineList.append(rxBadBox.cap(2));
			errorMessageList.append(badbox.replace("*",""));
			errorLogList.append(QString::number(errorpar));
			}
		errorpar=par;
		}
	if (tb.isValid())
		{
		par++;
		tb = tb.next();
		}
	}
DisplayLatexError();
}

void Texmaker::DisplayLatexError()
{
OutputTableWidget->clearContents();
QFontMetrics fm(qApp->font());
int rowheight=fm.lineSpacing()+4;
int maxwidth=0;
int row=0;
if (errorFileList.count()>0)
	{
	OutputTableWidget->setRowCount(errorFileList.count());
	for ( int i = 0; i <errorFileList.count(); i++ )
		{
		if (errorTypeList.at(i)=="Error")
			{
			QTableWidgetItem *ItemFile = new QTableWidgetItem(errorFileList.at(i));
			ItemFile->setData(Qt::UserRole,errorLogList.at(i));
			ItemFile->setForeground(QBrush(QColor(Qt::red)));
			ItemFile->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			OutputTableWidget->setItem(row,1, ItemFile);
			QTableWidgetItem *ItemType = new QTableWidgetItem(errorTypeList.at(i));
			ItemType->setData(Qt::UserRole,errorLogList.at(i));
			ItemType->setForeground(QBrush(QColor(Qt::red)));
			ItemType->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			OutputTableWidget->setItem(row,2, ItemType);
			QTableWidgetItem *ItemLine = new QTableWidgetItem("line "+errorLineList.at(i));
			ItemLine->setData(Qt::UserRole,errorLogList.at(i));
			ItemLine->setForeground(QBrush(QColor(Qt::red)));
			ItemLine->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			ItemLine->setToolTip(tr("Click to jump to the line"));
			OutputTableWidget->setItem(row,3, ItemLine);
			QTableWidgetItem *ItemMessage = new QTableWidgetItem(errorMessageList.at(i));
			if (fm.width(errorMessageList.at(i))>maxwidth) maxwidth=fm.width(errorMessageList.at(i));
			ItemMessage->setData(Qt::UserRole,errorLogList.at(i));
			ItemMessage->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			ItemMessage->setForeground(QBrush(QColor(Qt::red)));
			OutputTableWidget->setItem(row,4, ItemMessage);

			onlyErrorList.append(i);
			row++;
			}
		}
	for ( int i = 0; i <errorFileList.count(); i++ )
		{
		if (errorTypeList.at(i)!="Error")
			{
			QTableWidgetItem *ItemFile = new QTableWidgetItem(errorFileList.at(i));
			ItemFile->setData(Qt::UserRole,errorLogList.at(i));
			ItemFile->setForeground(QBrush(QColor(Qt::blue)));
			ItemFile->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			OutputTableWidget->setItem(row,1, ItemFile);
			QTableWidgetItem *ItemType = new QTableWidgetItem(errorTypeList.at(i));
			ItemType->setData(Qt::UserRole,errorLogList.at(i));
			ItemType->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			ItemType->setForeground(QBrush(QColor(Qt::blue)));
			OutputTableWidget->setItem(row,2, ItemType);
			QTableWidgetItem *ItemLine = new QTableWidgetItem("line "+errorLineList.at(i));
			ItemLine->setData(Qt::UserRole,errorLogList.at(i));
			ItemLine->setForeground(QBrush(QColor(Qt::blue)));
			ItemLine->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			ItemLine->setToolTip(tr("Click to jump to the line"));
			OutputTableWidget->setItem(row,3, ItemLine);
			QTableWidgetItem *ItemMessage = new QTableWidgetItem(errorMessageList.at(i));
			if (fm.width(errorMessageList.at(i))>maxwidth) maxwidth=fm.width(errorMessageList.at(i));
			ItemMessage->setData(Qt::UserRole,errorLogList.at(i));
			ItemMessage->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			ItemMessage->setForeground(QBrush(QColor(Qt::blue)));
			OutputTableWidget->setItem(row,4, ItemMessage);
			row++;
			}
		}
	OutputTableWidget->setColumnWidth(4,maxwidth);
	for ( int i = 0; i<OutputTableWidget->rowCount(); ++i )
		{
		OutputTableWidget->setRowHeight(i,rowheight);
		}
	}
else
	{
	OutputTableWidget->setRowCount(1);
	OutputTableWidget->setRowHeight(0,rowheight);
	OutputTableWidget->clearContents();
	}
OutputTableWidget->show();
OutputTextEdit->setCursorPosition(0 , 0);
if (errorTypeList.contains("Error")) {
     OutputView->show();    //show log when error
     OutputTableWidget->setFocus();
}
}

bool Texmaker::NoLatexErrors()
{
return onlyErrorList.isEmpty();
}

void Texmaker::NextError()
{
int line=0;
QTableWidgetItem *Item;
if (!logpresent) {ViewLog();}
if (logpresent && !onlyErrorList.isEmpty())
  	{
	if (errorIndex<onlyErrorList.size()-1) errorIndex=errorIndex+1;
	if (errorIndex<0) errorIndex=0;
	if (errorIndex>=onlyErrorList.count()) errorIndex=onlyErrorList.count()-1;
	if (singlemode)// && onlyErrorList.at(errorIndex)!=0)
		{
		line=errorLineList.at(onlyErrorList.at(errorIndex)).toInt();
		for ( int i = 0; i <errorFileList.count(); i++ )
			{
			Item = new QTableWidgetItem(" ");
			OutputTableWidget->setItem(i,0, Item);
			}
		Item = new QTableWidgetItem(">");
		OutputTableWidget->setItem(errorIndex,0, Item);
		OutputTableWidget->scrollToItem(Item,QAbstractItemView::PositionAtCenter);
		ClickedOnOutput(line-1);
		int logline=errorLogList.at(onlyErrorList.at(errorIndex)).toInt()-1;
		OutputTextEdit->setCursorPosition(logline , 0);
		}
  	}
if (logpresent && onlyErrorList.isEmpty())
	{
	QMessageBox::information( this,"TexMakerX",tr("No LaTeX errors detected !"));
	OutputTextEdit->setCursorPosition(0 , 0);
	}
}

void Texmaker::PreviousError()
{
int line=0;
QTableWidgetItem *Item;
if (!logpresent) {ViewLog();}

if (logpresent && !onlyErrorList.isEmpty())
  	{
	if (errorIndex>0) errorIndex=errorIndex-1;
	if (errorIndex<0) errorIndex=0;
	if (errorIndex>=onlyErrorList.count()) errorIndex=onlyErrorList.count()-1;
	if (singlemode)// && onlyErrorList.at(errorIndex)!=0)
		{
		line=errorLineList.at(onlyErrorList.at(errorIndex)).toInt();
		for ( int i = 0; i <errorFileList.count(); i++ )
			{
			Item = new QTableWidgetItem(" ");
			OutputTableWidget->setItem(i,0, Item);
			}
		Item = new QTableWidgetItem(">");
		OutputTableWidget->setItem(errorIndex,0, Item);
		OutputTableWidget->scrollToItem(Item,QAbstractItemView::PositionAtCenter);
		ClickedOnOutput(line-1);
		int logline=errorLogList.at(onlyErrorList.at(errorIndex)).toInt()-1;
		OutputTextEdit->setCursorPosition(logline , 0);
		}
  	}
if (logpresent && onlyErrorList.isEmpty())
	{
	QMessageBox::information( this,"TexMakerX",tr("No LaTeX errors detected !"));
	OutputTextEdit->setCursorPosition(0 , 0);
	}
}

//////////////// HELP /////////////////
void Texmaker::LatexHelp()
{
    QString latexHelp=findResourceFile("latexhelp.html");
    if (latexHelp!="") QDesktopServices::openUrl("file:///"+latexHelp);
    else QMessageBox::warning( this,tr("Error"),tr("File not found"));
}

void Texmaker::UserManualHelp()
{
    QString locale = QString(QLocale::system().name()).left(2);
    if ( locale.length() < 2 || locale!="fr" ) locale = "en";
    QString latexHelp=findResourceFile("usermanual_"+locale+".html");
    if (latexHelp!="") QDesktopServices::openUrl("file:///"+latexHelp);
    else QMessageBox::warning( this,tr("Error"),tr("File not found"));
}

void Texmaker::HelpAbout()
{
AboutDialog *abDlg = new AboutDialog(this);
abDlg->exec();
}
////////////// OPTIONS //////////////////////////////////////
void Texmaker::GeneralOptions()
{
ConfigDialog *confDlg = new ConfigDialog(this);

confDlg->ui.lineEditLatex->setText(latex_command);
confDlg->ui.lineEditPdflatex->setText(pdflatex_command);
confDlg->ui.lineEditDvips->setText(dvips_command);
confDlg->ui.lineEditDviviewer->setText(viewdvi_command);
confDlg->ui.lineEditPsviewer->setText(viewps_command);
confDlg->ui.lineEditDvipdfm->setText(dvipdf_command);
confDlg->ui.lineEditPs2pdf->setText(ps2pdf_command);
confDlg->ui.lineEditBibtex->setText(bibtex_command);
confDlg->ui.lineEditMakeindex->setText(makeindex_command);
confDlg->ui.lineEditPdfviewer->setText(viewpdf_command);
confDlg->ui.lineEditMetapost->setText(metapost_command);
confDlg->ui.lineEditGhostscript->setText(ghostscript_command);

foreach (QString formatName, m_formats->formats()){
    confDlg->editorFormats.insert(formatName,m_formats->format(formatName));
    confDlg->ui.comboBoxStyles->addItem(formatName);
}
confDlg->ui.comboBoxFont->lineEdit()->setText(EditorFont.family() );
if (newfile_encoding)
  confDlg->ui.comboBoxEncoding->setCurrentIndex(confDlg->ui.comboBoxEncoding->findText(newfile_encoding->name(), Qt::MatchExactly));
confDlg->ui.checkBoxAutoDetectOnLoad->setChecked(autodetectLoadedFile);

confDlg->ui.spinBoxSize->setValue(EditorFont.pointSize() );
confDlg->ui.checkBoxWordwrap->setChecked(wordwrap);
switch (showlinemultiples) {
    case 0: confDlg->ui.comboboxLineNumbers->setCurrentIndex(0); break;
    case 10: confDlg->ui.comboboxLineNumbers->setCurrentIndex(2); break;
    default: confDlg->ui.comboboxLineNumbers->setCurrentIndex(1);
}
confDlg->ui.checkBoxCompletion->setChecked(completion);
confDlg->ui.checkBoxFolding->setChecked(folding);
confDlg->ui.checkBoxLineState->setChecked(showlinestate);
confDlg->ui.checkBoxState->setChecked(showcursorstate);
confDlg->ui.checkBoxRealTimeCheck->setChecked(realtimespellchecking);

confDlg->ui.lineEditAspellCommand->setText(spell_dic);


confDlg->ui.pushButtonColorDecoration->setAutoFillBackground(true);
confDlg->ui.pushButtonColorText->setAutoFillBackground(true);

if (quickmode==1) {confDlg->ui.radioButton1->setChecked(true); confDlg->ui.lineEditUserquick->setEnabled(false);}
if (quickmode==2) {confDlg->ui.radioButton2->setChecked(true); confDlg->ui.lineEditUserquick->setEnabled(false);}
if (quickmode==3) {confDlg->ui.radioButton3->setChecked(true); confDlg->ui.lineEditUserquick->setEnabled(false);}
if (quickmode==4)  {confDlg->ui.radioButton4->setChecked(true); confDlg->ui.lineEditUserquick->setEnabled(false);}
if (quickmode==5)  {confDlg->ui.radioButton5->setChecked(true); confDlg->ui.lineEditUserquick->setEnabled(false);}
if (quickmode==6)  {confDlg->ui.radioButton6->setChecked(true); confDlg->ui.lineEditUserquick->setEnabled(true);}
confDlg->ui.lineEditUserquick->setText(userquick_command);

int row=0;
KeysMap::Iterator its, iter;
QString d,f;
for( its = shortcuts.begin(); its != shortcuts.end(); ++its )
	{
	d=its.key().section("/",0,0);
	for( iter = actionstext.begin(); iter != actionstext.end(); ++iter )
		{
		f=iter.key().section("/",0,0);
		if (d==f)
			{
			QTableWidgetItem *newItem = new QTableWidgetItem(iter.value());
			//QTableWidgetItem *newItem = new QTableWidgetItem(*actionstext.find(its.key()));
			newItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
			newItem->setData(Qt::UserRole, its.key());
			confDlg->ui.shorttableWidget->setRowCount(row+1);
			confDlg->ui.shorttableWidget->setItem(row, 0, newItem);
			newItem = new QTableWidgetItem(its.value());
			newItem->setData(Qt::UserRole,its.value());//to revert the shortcut
			confDlg->ui.shorttableWidget->setItem(row, 1, newItem);
			row++;
			}
		}
	}
confDlg->ui.shorttableWidget->horizontalHeader()->resizeSection( 0, 250 );
confDlg->ui.shorttableWidget->verticalHeader()->hide();

if (confDlg->exec())
	{
	for(int row=0; row<confDlg->ui.shorttableWidget->rowCount(); row++ )
	{
		QString itemtext = confDlg->ui.shorttableWidget->item(row, 0)->text();
		QString itemshortcut = confDlg->ui.shorttableWidget->item(row, 1)->text();
		QString itemdata=confDlg->ui.shorttableWidget->item(row, 0)->data(Qt::UserRole).toString();
		shortcuts.remove(itemdata);
		shortcuts.insert(itemdata,itemshortcut);
	}
	ModifyShortcuts();

	if (confDlg->ui.radioButton1->isChecked()) quickmode=1;
	if (confDlg->ui.radioButton2->isChecked()) quickmode=2;
	if (confDlg->ui.radioButton3->isChecked()) quickmode=3;
	if (confDlg->ui.radioButton4->isChecked()) quickmode=4;
	if (confDlg->ui.radioButton5->isChecked()) quickmode=5;
	if (confDlg->ui.radioButton6->isChecked()) quickmode=6;
	userquick_command=confDlg->ui.lineEditUserquick->text();

	latex_command=confDlg->ui.lineEditLatex->text();
	pdflatex_command=confDlg->ui.lineEditPdflatex->text();
	dvips_command=confDlg->ui.lineEditDvips->text();
	viewdvi_command=confDlg->ui.lineEditDviviewer->text();
	viewps_command=confDlg->ui.lineEditPsviewer->text();
	dvipdf_command=confDlg->ui.lineEditDvipdfm->text();
	ps2pdf_command=confDlg->ui.lineEditPs2pdf->text();
	bibtex_command=confDlg->ui.lineEditBibtex->text();
	makeindex_command=confDlg->ui.lineEditMakeindex->text();
	viewpdf_command=confDlg->ui.lineEditPdfviewer->text();
	metapost_command=confDlg->ui.lineEditMetapost->text();
	ghostscript_command=confDlg->ui.lineEditGhostscript->text();

	QString fam=confDlg->ui.comboBoxFont->lineEdit()->text();
	int si=confDlg->ui.spinBoxSize->value();
	QFont F(fam,si);
	EditorFont=F;

    newfile_encoding=QTextCodec::codecForName(confDlg->ui.comboBoxEncoding->currentText().toAscii().data());
    autodetectLoadedFile=confDlg->ui.checkBoxAutoDetectOnLoad;

	wordwrap=confDlg->ui.checkBoxWordwrap->isChecked();
	completion=confDlg->ui.checkBoxCompletion->isChecked();
    switch (confDlg->ui.comboboxLineNumbers->currentIndex()) {
        case 0: showlinemultiples=0; break;
        case 2: showlinemultiples=10; break;
        default: showlinemultiples=1; break;
    }
	spell_dic=confDlg->ui.lineEditAspellCommand->text();
    folding=confDlg->ui.checkBoxFolding->isChecked();
    showlinestate=confDlg->ui.checkBoxLineState->isChecked();
    showcursorstate=confDlg->ui.checkBoxState->isChecked();
    realtimespellchecking=confDlg->ui.checkBoxRealTimeCheck->isChecked();
    mainSpeller->setActive(realtimespellchecking);
    mainSpeller->loadDictionary(spell_dic,configFileNameBase);

    QMap<QString, QFormat>::const_iterator it = confDlg->editorFormats.constBegin();
    while (it != confDlg->editorFormats.constEnd()) {
        m_formats->setFormat(it.key(),it.value());
        ++it;
    }    
    QDocument::setFormatFactory(m_formats);

	if (currentEditorView())
		{
            FilesMap::Iterator it;
            for( it = filenames.begin(); it != filenames.end(); ++it )
                it.key()->changeSettings(EditorFont,showlinemultiples,folding,showlinestate,showcursorstate, wordwrap,completion);
            UpdateCaption();
            OutputTextEdit->clear();
            OutputTableWidget->hide();
            //OutputTextEdit->insertLine("Editor settings apply only to new loaded document.");
		}
	}
}

void Texmaker::ToggleMode()
{
//QAction *action = qobject_cast<QAction *>(sender());
if (!singlemode)
	{
	ToggleAct->setText(tr("Define Current Document as 'Master Document'"));
	OutputTextEdit->clear();
	OutputTableWidget->hide();
	logpresent=false;
	singlemode=true;
	stat1->setText(QString(" %1 ").arg(tr("Normal Mode")));
	return;
	}
if (singlemode && currentEditorView())
	{
	MasterName=getName();
	if (MasterName=="untitled" || MasterName=="")
		{
		QMessageBox::warning( this,tr("Error"),tr("Could not start the command."));
		return;
		}
	QString shortName = MasterName;
	int pos;
	while ( (pos = (int)shortName.indexOf('/')) != -1 ) shortName.remove(0,pos+1);
	ToggleAct->setText(tr("Normal Mode (current master document :")+shortName+")");
	singlemode=false;
	stat1->setText(QString(" %1 ").arg(tr("Master Document :")+shortName));
	return;
	}
}

void Texmaker::onOtherInstanceMessage(const QString &msg)  // Added slot for messages to the single instance
{
QStringList argv = msg.split("#!#");
int argc = argv.size();
for ( int i = 1; i < argc; ++i )
	{
	QString arg = argv[ i ];
	if ( arg[0] != '-' )    load( arg );
	if ( arg == "-master" ) ToggleMode();
	if (( arg == "-line" ) && (i<argc-1))  setLine( argv[ ++i ] );
	}
}
////////////////// VIEW ////////////////

void Texmaker::gotoNextDocument()
{
if ( EditorView->count() < 2 ) return;
int cPage = EditorView->currentIndex() + 1;
if ( cPage >= EditorView->count() ) EditorView->setCurrentIndex( 0 );
else EditorView->setCurrentIndex( cPage );
}

void Texmaker::gotoPrevDocument()
{
if ( EditorView->count() < 2 ) return;
int cPage = EditorView->currentIndex() - 1;
if ( cPage < 0 ) EditorView->setCurrentIndex( EditorView->count() - 1 );
else EditorView->setCurrentIndex( cPage );
}

void Texmaker::SetInterfaceFont()
{
#if defined( Q_WS_X11 )
X11FontDialog *xfdlg = new X11FontDialog(this);
int ft=xfdlg->ui.comboBoxFont->findText (x11fontfamily , Qt::MatchExactly);
xfdlg->ui.comboBoxFont->setCurrentIndex(ft);
xfdlg->ui.spinBoxSize->setValue(x11fontsize);
if (xfdlg->exec())
	{
	x11fontfamily=xfdlg->ui.comboBoxFont->currentText();
	x11fontsize=xfdlg->ui.spinBoxSize->value();
	QFont x11Font (x11fontfamily,x11fontsize);
	QApplication::setFont(x11Font);
	}
#endif
}
void Texmaker::SetInterfaceType()
{
#if defined( Q_WS_X11 )
QStringList styles=QStyleFactory::keys()<<"default";
x11style = QInputDialog::getItem(this,"TexMakerX",tr("Select interface style"),styles,styles.indexOf(x11style));
if (x11style=="default") QMessageBox::information(this,"TexMakerX",tr("Please restart TexMakerX to apply the changes"),0);
else {
    QPalette pal = QApplication::palette();
    QApplication::setStyle(x11style);
    QApplication::setPalette(pal);
	}
#endif
}

void Texmaker::gotoBookmark(int id){
    if ( !currentEditorView() ) return;
    currentEditorView()->jumpToBookmark(id);
}
void Texmaker::toggleBookmark(int id){
    if ( !currentEditorView() ) return;
    currentEditorView()->toggleBookmark(id);
}

//*********************************
void Texmaker::dragEnterEvent(QDragEnterEvent *event)
{
if (event->mimeData()->hasFormat("text/uri-list")) event->acceptProposedAction();
}

void Texmaker::dropEvent(QDropEvent *event)
{
QRegExp rx("file://(.*\\.(?:tex|bib|sty|cls|mp))");
QList<QUrl> uris=event->mimeData()->urls();
QString uri;
for (int i = 0; i < uris.size(); ++i)
	{
	uri=uris.at(i).toString();
	if (rx.exactMatch(uri)) load(rx.cap(1));
	}
event->acceptProposedAction();
}

//***********************************
void Texmaker::SetMostUsedSymbols()
{
for ( int i = 0; i <=11; ++i ) symbolMostused[i]=-1;
QList<int> list_num, list_score;
list_num.clear();
list_score.clear();
for (int i=0; i <412 ; i++)
	{
	list_num.append(i);
	list_score.append(symbolScore[i]);
	}
int max;
for (int i = 0; i < 412; i++)
	{
	max=i;
	for (int j = i+1; j < 412; j++)
		{
		if (list_score.at(j)>list_score.at(max)) max=j;
		}
	if (max!=i)
		{
		list_num.swap(i,max);
		list_score.swap(i,max);
		}
	}
for ( int i = 0; i <=11; ++i )
	{
	if (list_score.at(i)>0) symbolMostused[i]=list_num.at(i);
	}
MostUsedListWidget->SetUserPage(symbolMostused);
}

void Texmaker::ModifyShortcuts()
{
KeysMap::Iterator its;
QString d,f,s;
QList<QAction *> listaction;
listaction << latex11Menu->actions();
listaction << latex12Menu->actions();
listaction << latex13Menu->actions();
listaction << latex14Menu->actions();
listaction << latex15Menu->actions();
listaction << latex16Menu->actions();
listaction << latex17Menu->actions();
listaction << math1Menu->actions();
listaction << math11Menu->actions();
listaction << math12Menu->actions();
listaction << math13Menu->actions();
listaction << math14Menu->actions();
QListIterator<QAction*> iterator(listaction);
actionstext.clear();
while ( iterator.hasNext() )
	{
	QAction *action=iterator.next();
        if (action && (!action->menu())  && (!action->data().toString().isEmpty()))
		{
		actionstext.insert(action->data().toString(),action->text());
		d=action->data().toString().section("/",0,0);
		for( its = shortcuts.begin(); its != shortcuts.end(); ++its )
			{
			f=its.key().section("/",0,0);
			s=its.value();
			if (f==d && s!="none" && !s.isEmpty()) action->setShortcut(s);
			}
// 		its=shortcuts.find(action->data().toString());
// 		if (its!=shortcuts.end())
// 			{
// 			s=*its;
// 			if (s!="none" && !s.isEmpty()) action->setShortcut(s);
// 			}
		//QString s=*shortcuts.find(action->data().toString());
		//if (s!="none" && !s.isEmpty()) action->setShortcut(s);
		}
	}
}

void Texmaker::updateCompleter()
{
    QStringList words;
    QFile tagsfile(":/completion/completion.txt");
    if (tagsfile.open(QFile::ReadOnly)) {
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        QString line;
        while (!tagsfile.atEnd())
        {
            line = tagsfile.readLine();
            if (!line.isEmpty()) words.append(line.trimmed());
        }
        QApplication::restoreOverrideCursor();
    }
    for (int i=0; i<labelitem.count();++i)
    {
        words.append("\\ref{"+labelitem.at(i)+"}");
        words.append("\\pageref{"+labelitem.at(i)+"}");
	}
    
    QMultiMap<QString, QString> sortMap;
    foreach (QString str, words)
        sortMap.insert(str.toLower(), str);
    completer->setWords(sortMap.values());
}

