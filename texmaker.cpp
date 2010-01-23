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

#include "texmaker.h"
#include "latexeditorview.h"

#include "smallUsefulFunctions.h"

#include "structdialog.h"
#include "filechooser.h"
#include "tabdialog.h"
#include "arraydialog.h"
#include "bibtexdialog.h"
#include "tabbingdialog.h"
#include "letterdialog.h"
#include "quickdocumentdialog.h"
#include "usermenudialog.h"
#include "usertooldialog.h"
#include "aboutdialog.h"
#include "encodingdialog.h"
#include "randomtextgenerator.h"
#include "webpublishdialog.h"
#include "findGlobalDialog.h"
#include "qsearchreplacepanel.h"
#include "latexcompleter_config.h"
#include "universalinputdialog.h"

#ifndef QT_NO_DEBUG
#include "tests/testmanager.h"
#endif

#include "qdocument.h"
#include "qdocumentcursor.h"
#include "qdocumentline.h"
#include "qdocumentline_p.h"

Texmaker::Texmaker(QWidget *parent, Qt::WFlags flags)
		: QMainWindow(parent, flags), textAnalysisDlg(0), spellDlg(0), mDontScrollToItem(false), PROCESSRUNNING(false) {

	MapForSymbols=0;
	currentLine=-1;
	thesaurusFileName.clear();
	previewEquation=false;
	svndlg=0;

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

	setIconSize(QSize(22,22));

	leftPanel=0;
	structureTreeView=0;

	outputView=0;
	thesaurusDialog=0;
	templateSelectorDialog=0;

	mainSpeller=new SpellerUtility();;
	mainSpeller->loadDictionary(configManager.spell_dic,configManager.configFileNameBase);

	LatexEditorView::setSpeller(mainSpeller);

	QDocument::setFormatFactory(m_formats);
	mainSpeller->spellcheckErrorFormat=m_formats->id("spellingMistake");

	QDocument::setShowSpaces(QDocument::ShowTrailing | QDocument::ShowLeading | QDocument::ShowTabs);

	if (configManager.autodetectLoadedFile) QDocument::setDefaultCodec(0);
	else QDocument::setDefaultCodec(configManager.newfile_encoding);


	QString qxsPath=QFileInfo(findResourceFile("qxs/tex.qnfa")).path();
	m_languages = new QLanguageFactory(m_formats, this);
	m_languages->addDefinitionPath(qxsPath);
	QLineMarksInfoCenter::instance()->loadMarkTypes(qxsPath+"/marks.qxm");


// TAB WIDGET EDITEUR
	EditorView=new QTabWidget(this);
	EditorView->setFocusPolicy(Qt::ClickFocus);
	EditorView->setFocus();
	connect(EditorView, SIGNAL(currentChanged(QWidget *)), this, SLOT(UpdateCaption()));
	if (hasAtLeastQt(4,5)){
		EditorView->setProperty("tabsClosable",true);
		EditorView->setProperty("movable",true);
		connect(EditorView, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseEditorTab(int)));
	}
	setCentralWidget(EditorView);

	symbolMostused.clear();
	setupDockWidgets();
	//SetMostUsedSymbols();
	setupMenus();
	configManager.updateRecentFiles(true);
	setupToolBars();

	restoreState(windowstate, 0);
	if(tobemaximized) showMaximized();
	if(tobefullscreen) {
		showFullScreen();
		restoreState(stateFullScreen,1);
		fullscreenModeAction->setChecked(true);
	}

	createStatusBar();
	UpdateCaption();
	singlemode=true;
	MasterName="";

	show();

	stat1->setText(QString(" %1 ").arg(tr("Normal Mode")));
	stat2->setText(QString(" %1 ").arg(tr("Ready")));
//connect(stat3, SIGNAL(itemClicked ( QTableWidgetItem*)), this, SLOT(InsertSymbol(QTableWidgetItem*)));
	// adapt menu output view visible;
	bool mVis=outputView->isVisible();
	outputViewAction->setChecked(mVis);

	setAcceptDrops(true);
	installEventFilter(this);


	completer=new LatexCompleter(this);
	completer->setConfig(configManager.completerConfig);
	updateCompleter();
	LatexEditorView::setCompleter(completer);
	completer->setAbbreviations(UserMenuAbbrev,UserMenuTag);

	if (configManager.sessionRestore) {
		fileRestoreSession();
		ToggleRememberAct->setChecked(true);
	}
}

QMenu* Texmaker::newManagedMenu(QMenu* menu, const QString &id,const QString &text){
	return configManager.newManagedMenu(menu,id,text);
}
QAction* Texmaker::newManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QKeySequence &shortCut, const QString & iconFile) {
	return configManager.newManagedAction(menu,id,text,slotName,QList<QKeySequence>() << shortCut, iconFile);
}
QAction* Texmaker::newManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QList<QKeySequence> &shortCuts, const QString & iconFile) {
	return configManager.newManagedAction(menu,id,text,slotName,shortCuts, iconFile);
}
QAction* Texmaker::newManagedAction(QWidget* menu, const QString &id, QAction* act){
	return configManager.newManagedAction(menu,id,act);
}
QAction* Texmaker::getManagedAction(QString id) {
	return configManager.getManagedAction(id);
}
QMenu* Texmaker::newManagedMenu(const QString &id,const QString &text){
	return configManager.newManagedMenu(id,text);
}

SymbolGridWidget* Texmaker::addSymbolGrid(const QString& SymbolList,  const QString& iconName, const QString& text){
	SymbolGridWidget* list = qobject_cast<SymbolGridWidget*>(leftPanel->widget(SymbolList));
	if (!list) {
		list=new SymbolGridWidget(this,SymbolList,MapForSymbols);
		list->setProperty("isSymbolGrid",true);
		connect(list, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(InsertSymbol(QTableWidgetItem*)));
		connect(list, SIGNAL(itemPressed(QTableWidgetItem*)), this, SLOT(InsertSymbolPressed(QTableWidgetItem*)));
		leftPanel->addWidget(list, SymbolList, text, iconName);
	} else leftPanel->setWidgetText(list,text);
	return list;
}

void Texmaker::addTagList(const QString& id, const QString& iconName, const QString& text, const QString& tagFile){
	XmlTagsListWidget* list=qobject_cast<XmlTagsListWidget*>(leftPanel->widget(id));
	if (!list) {
		list=new XmlTagsListWidget(0,":/tags/"+tagFile);
		connect(list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(InsertXmlTag(QListWidgetItem*)));
		leftPanel->addWidget(list, id, text, iconName);
		//(*list)->setProperty("mType",2);
	} else leftPanel->setWidgetText(list,text);
}
void Texmaker::setupDockWidgets(){
//to allow retranslate this function must be able to be called multiple times

	//Structure panel
	if (!leftPanel) {
		leftPanel = new CustomWidgetList(this);
		leftPanel->setWindowTitle(tr("Structure"));
		leftPanel->setObjectName("leftPanel");
		leftPanel->setAllowedAreas(Qt::AllDockWidgetAreas);
		leftPanel->setFeatures(QDockWidget::DockWidgetClosable);
		addDockWidget(Qt::LeftDockWidgetArea, leftPanel);
		connect(&configManager,SIGNAL(newLeftPanelLayoutChanged(bool)), leftPanel,  SLOT(showWidgets(bool)));
		if (hiddenLeftPanelWidgets!="") {
			leftPanel->setHiddenWidgets(hiddenLeftPanelWidgets);
			hiddenLeftPanelWidgets=""; //not needed anymore after the first call
		}

		connect(leftPanel,SIGNAL(widgetContextMenuRequested(QWidget*, QPoint)),this,SLOT(SymbolGridContextMenu(QWidget*, QPoint)));
	}

	if (!structureTreeView) {
		structureTreeView=new QTreeView(this);
		structureTreeView->header()->hide();
		structureTreeView->setModel(documents.model);
		//disabled because it also reacts to expand, connect(structureTreeView, SIGNAL(activated(const QModelIndex &)), SLOT(clickedOnStructureEntry(const QModelIndex &))); //enter or double click (+single click on some platforms)
		connect(structureTreeView, SIGNAL(pressed(const QModelIndex &)), SLOT(clickedOnStructureEntry(const QModelIndex &))); //single click
//		connect(structureTreeView, SIGNAL(expanded(const QModelIndex &)), SLOT(treeWidgetChanged()));
//		connect(structureTreeView, SIGNAL(collapsed(const QModelIndex &)), SLOT(treeWidgetChanged()));
//-- connect( StructureTreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *,int )), SLOT(DoubleClickedOnStructure(QTreeWidgetItem *,int))); // qt4 bugs - don't use it ?? also true for view??

		leftPanel->addWidget(structureTreeView, "structureTreeView", tr("Structure"), ":/images/structure.png");
	} else leftPanel->setWidgetText(structureTreeView,tr("Structure"));

	addSymbolGrid("operators", ":/images/math1.png",tr("Operator symbols"));
	addSymbolGrid("relation", ":/images/hi16-action-math1.png",tr("Relation symbols"));
	addSymbolGrid("arrows", ":/images/math2.png",tr("Arrow symbols"));
	addSymbolGrid("delimiters",":/images/math4.png",tr("Delimiters"));
	addSymbolGrid("greek", ":/images/math5.png",tr("Greek letters"));
	addSymbolGrid("cyrillic", ":/images/hi16-action-math10.png",tr("Cyrillic letters"));
	addSymbolGrid("misc-math", ":/images/math3.png",tr("Miscellaneous math symbols"));
	addSymbolGrid("misc-text", ":/images/hi16-action-math5.png",tr("Miscellaneous text symbols"));
	addSymbolGrid("wasysym", ":/images/hi16-action-math5.png",tr("Miscellaneous text symbols (wasysym)"));
	addSymbolGrid("special", ":/images/accent1.png",tr("Accented letters"));

	MostUsedSymbolWidget=addSymbolGrid("!mostused",":/images/math6.png",tr("Most used symbols"));
	FavoriteSymbolWidget=addSymbolGrid("!favorite",":/images/math7.png",tr("Favorites"));
	FavoriteSymbolWidget->loadSymbols(symbolFavorites);

	addTagList("leftright", ":/images/leftright.png", tr("Left/Right Brackets"),"leftright_tags.xml");
	addTagList("pstricks", ":/images/pstricks.png", tr("Pstricks Commands"),"pstricks_tags.xml");
	addTagList("metapost", ":/images/metapost.png", tr("MetaPost Commands"),"metapost_tags.xml");
	addTagList("tikz", ":/images/tikz.png", tr("Tikz Commands"),"tikz_tags.xml");
	addTagList("asymptote", ":/images/asymptote.png", tr("Asymptote Commands"),"asymptote_tags.xml");

	leftPanel->showWidgets(configManager.newLeftPanelLayout);

	// update MostOftenUsed
	MostUsedSymbolsTriggered(true);
	// clean not further used map;
	if (MapForSymbols){
		delete MapForSymbols;
		MapForSymbols = 0;
	}
// OUTPUT WIDGETS
	if (!outputView) {
		outputView = new OutputViewWidget(this);
		outputView->setObjectName("OutputView");
		outputView->setAllowedAreas(Qt::AllDockWidgetAreas);
		outputView->setFeatures(QDockWidget::DockWidgetClosable);
		outputView->setTabbedLogView(configManager.tabbedLogView);
		addDockWidget(Qt::BottomDockWidgetArea,outputView);
		connect(outputView,SIGNAL(locationActivated(int,const QString&)),this,SLOT(gotoLocation(int,const QString&)));
		connect(outputView,SIGNAL(logEntryActivated(int)),this,SLOT(gotoLogEntryEditorOnly(int)));
		connect(outputView,SIGNAL(tabChanged(int)),this,SLOT(tabChanged(int)));
		connect(outputView,SIGNAL(jumpToSearch(QString,int)),this,SLOT(jumpToSearch(QString,int)));
		connect(&configManager,SIGNAL(tabbedLogViewChanged(bool)),outputView,SLOT(setTabbedLogView(bool)));
		connect(&buildManager,SIGNAL(previewAvailable(const QString&, const QString&)),this,SLOT(previewAvailable	(const QString&,const QString&)));
	}
	outputView->setWindowTitle(tr("Messages / Log File"));

}

void Texmaker::setupMenus() {
	//This function is called whenever the menu changes (= start and retranslation)
	//This means if you call it repeatedly with the same language setting it should not change anything
	//Currently this is not true, because it adds additional separator, which are invisible
	//creates new action groups and new context menu, although all invisible, they are a memory leak
	//But not a bad one, because no one is expected to change the language multiple times
	//TODO: correct somewhen

	configManager.menuParent=this;
	configManager.menuParentsBar=menuBar();

//file
	QMenu *menu=newManagedMenu("main/file",tr("&File"));
	newManagedAction(menu, "new",tr("New"), SLOT(fileNew()), Qt::CTRL+Qt::Key_N, ":/images/filenew.png");
	newManagedAction(menu, "newfromtemplate",tr("New from template"), SLOT(fileNewFromTemplate()));
	newManagedAction(menu, "open",tr("Open"), SLOT(fileOpen()), Qt::CTRL+Qt::Key_O, ":/images/fileopen.png");

	QMenu *submenu=newManagedMenu(menu, "openrecent",tr("Open Recent")); //only create the menu here, actions are created by config manager
	newManagedAction(menu, "restoresession",tr("Restore previous session"), SLOT(fileRestoreSession()));

	menu->addSeparator();
	newManagedAction(menu,"save",tr("Save"), SLOT(fileSave()), Qt::CTRL+Qt::Key_S, ":/images/filesave.png");
	newManagedAction(menu,"saveas",tr("Save As"), SLOT(fileSaveAs()), Qt::CTRL+Qt::ALT+Qt::Key_S);
	newManagedAction(menu,"saveall",tr("Save All"), SLOT(fileSaveAll()), Qt::CTRL+Qt::SHIFT+Qt::ALT+Qt::Key_S);
	newManagedAction(menu, "maketemplate",tr("Make Template"), SLOT(fileMakeTemplate()));
	newManagedAction(menu, "checkin",tr("Check in"), SLOT(fileCheckin()));
	newManagedAction(menu, "showrevisions",tr("Show old Revisions"), SLOT(showOldRevisions()));

	menu->addSeparator();
	newManagedAction(menu,"close",tr("Close"), SLOT(fileClose()), Qt::CTRL+Qt::Key_W, ":/images/fileclose.png");
	newManagedAction(menu,"closeall",tr("Close All"), SLOT(fileCloseAll()));

	menu->addSeparator();
	newManagedAction(menu, "print",tr("Print"), SLOT(filePrint()), Qt::CTRL+Qt::Key_P);

	menu->addSeparator();
	newManagedAction(menu,"exit",tr("Exit"), SLOT(fileExit()), Qt::CTRL+Qt::Key_Q);

//edit

	menu=newManagedMenu("main/edit",tr("&Edit"));
	newManagedAction(menu, "undo",tr("Undo"), SLOT(editUndo()), Qt::CTRL+Qt::Key_Z, ":/images/undo.png");
	newManagedAction(menu, "redo",tr("Redo"), SLOT(editRedo()), Qt::CTRL+Qt::Key_Y, ":/images/redo.png");

	menu->addSeparator();
	newManagedAction(menu,"copy",tr("Copy"), SLOT(editCopy()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_C)<<Qt::CTRL+Qt::Key_Insert, ":/images/editcopy.png");
	newManagedAction(menu,"cut",tr("Cut"), SLOT(editCut()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_X)<<Qt::SHIFT+Qt::Key_Delete, ":/images/editcut.png");
	newManagedAction(menu,"paste",tr("Paste"), SLOT(editPaste()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_V)<<Qt::SHIFT+Qt::Key_Insert, ":/images/editpaste.png");
	newManagedAction(menu,"selectall",tr("Select All"), SLOT(editSelectAll()), Qt::CTRL+Qt::Key_A);
	newManagedAction(menu,"eraseLine",tr("Erase Line"), SLOT(editEraseLine()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_K));
	menu->addSeparator();
	newManagedAction(menu,"pasteAsLatex",tr("Paste as Latex"), SLOT(editPasteLatex()), Qt::CTRL+Qt::SHIFT+Qt::Key_V, ":/images/editpaste.png");
	newManagedAction(menu,"convertToLatex",tr("Convert to Latex"), SLOT(convertToLatex()));
	newManagedAction(menu,"previewLatex",tr("Preview Selection/Parantheses"), SLOT(previewLatex()),Qt::ALT+Qt::Key_P);

	if (LatexEditorView::getBaseActions().empty()) //only called at first menu created
		LatexEditorView::setBaseActions(menu->actions());

	menu->addSeparator();
	newManagedAction(menu,"comment", tr("Comment"), SLOT(editComment()));
	newManagedAction(menu,"uncomment",tr("Uncomment"), SLOT(editUncomment()));
	newManagedAction(menu,"indent",tr("Indent"), SLOT(editIndent()));
	newManagedAction(menu,"unindent",tr("Unindent"), SLOT(editUnindent()));
	newManagedAction(menu,"hardbreak",tr("Hard Line Break"), SLOT(editHardLineBreak()));
	newManagedAction(menu,"hardbreakrepeat",tr("Repeat Hard Line Break"), SLOT(editHardLineBreakRepeat()));

	menu->addSeparator();
	newManagedAction(menu,"find", tr("Find"), SLOT(editFind()), Qt::CTRL+Qt::Key_F);
	newManagedAction(menu,"findnext",tr("Find Next"), SLOT(editFindNext()), Qt::CTRL+Qt::Key_M);
	newManagedAction(menu,"findglobal",tr("Find Dialog"), SLOT(editFindGlobal()));
	newManagedAction(menu,"replace",tr("Replace"), SLOT(editReplace()), Qt::CTRL+Qt::Key_R);

	menu->addSeparator();
	submenu=newManagedMenu(menu, "goto",tr("Go to"));
	newManagedAction(submenu,"line", tr("Line"), SLOT(editGotoLine()), Qt::CTRL+Qt::Key_G, ":/images/goto.png");
	newManagedAction(submenu,"lastchange",tr("last change"), SLOT(editJumpToLastChange()), Qt::CTRL+Qt::Key_H);
	newManagedAction(submenu,"nextchange",tr("\"next\" change"), SLOT(editJumpToLastChangeForward()), Qt::CTRL+Qt::SHIFT+Qt::Key_H);
	submenu->addSeparator();
	newManagedAction(submenu,"markprev",tr("Previous mark"),SLOT(PreviousMark()),Qt::CTRL+Qt::Key_Up);//, ":/images/errorprev.png");
	newManagedAction(submenu,"marknext",tr("Next mark"),SLOT(NextMark()),Qt::CTRL+Qt::Key_Down);//, ":/images/errornext.png");
	submenu->addSeparator();
	newManagedAction(submenu,"errorprev",tr("Previous error"),SLOT(PreviousError()),Qt::CTRL+Qt::SHIFT+Qt::Key_Up, ":/images/errorprev.png");
	newManagedAction(submenu,"errornext",tr("Next error"),SLOT(NextError()),Qt::CTRL+Qt::SHIFT+Qt::Key_Down, ":/images/errornext.png");
	newManagedAction(submenu,"warningprev",tr("Previous warning"),SLOT(PreviousWarning()),Qt::CTRL+Qt::ALT+Qt::Key_Up);//, ":/images/errorprev.png");
	newManagedAction(submenu,"warningnext",tr("Next warning"),SLOT(NextWarning()),Qt::CTRL+Qt::ALT+Qt::Key_Down);//, ":/images/errornext.png");
	newManagedAction(submenu,"badboxprev",tr("Previous bad box"),SLOT(PreviousBadBox()),Qt::SHIFT+Qt::ALT+Qt::Key_Up);//, ":/images/errorprev.png");
	newManagedAction(submenu,"badboxnext",tr("Next bad box"),SLOT(NextBadBox()),Qt::SHIFT+Qt::ALT+Qt::Key_Down);//, ":/images/errornext.png");
	submenu->addSeparator();
	newManagedAction(submenu,"definition",tr("Definition"),SLOT(editGotoDefinition()),Qt::CTRL+Qt::ALT+Qt::Key_F);

	submenu=newManagedMenu(menu, "gotoBookmark",tr("Goto Bookmark"));
	for (int i=0; i<=9; i++)
		newManagedAction(submenu,QString("bookmark%1").arg(i),tr("Bookmark %1").arg(i),SLOT(gotoBookmark()),Qt::CTRL+Qt::Key_0+i)
		->setData(i);

	submenu=newManagedMenu(menu, "toggleBookmark",tr("Toggle Bookmark"));
	newManagedAction(submenu,QString("bookmark"),tr("unnamed bookmark"),SLOT(toggleBookmark()),Qt::CTRL+Qt::SHIFT+Qt::Key_B)
	->setData(-1);
	for (int i=0; i<=9; i++)
		newManagedAction(submenu,QString("bookmark%1").arg(i),tr("Bookmark %1").arg(i),SLOT(toggleBookmark()),Qt::CTRL+Qt::SHIFT+Qt::Key_0+i)
		->setData(i);

	submenu=newManagedMenu(menu, "complete",tr("Complete"));
	newManagedAction(submenu, "normal", tr("normal"), SLOT(NormalCompletion()),Qt::CTRL+Qt::Key_Space);
	newManagedAction(submenu, "environment", tr("\\begin{ completion"), SLOT(InsertEnvironmentCompletion()),Qt::CTRL+Qt::ALT+Qt::Key_Space);
	newManagedAction(submenu, "text", tr("normal text"), SLOT(InsertTextCompletion()),Qt::SHIFT+Qt::ALT+Qt::Key_Space);

	menu->addSeparator();
	submenu=newManagedMenu(menu,"lineend",tr("Line Ending"));
	QActionGroup *lineEndingGroup=new QActionGroup(this);
	QAction* act=newManagedAction(submenu, "crlf", tr("DOS/Windows (CR LF)"), SLOT(editChangeLineEnding()));
	act->setData(QDocument::Windows);
	act->setCheckable(true);
	lineEndingGroup->addAction(act);
	act=newManagedAction(submenu, "lf", tr("Unix (LF)"), SLOT(editChangeLineEnding()));
	act->setData(QDocument::Unix);
	act->setCheckable(true);
	lineEndingGroup->addAction(act);
	act=newManagedAction(submenu, "cr", tr("Old Mac (CR)"), SLOT(editChangeLineEnding()));
	act->setData(QDocument::Mac);
	act->setCheckable(true);
	lineEndingGroup->addAction(act);


	newManagedAction(menu,"encoding",tr("Setup Encoding"),SLOT(editSetupEncoding()));


	menu->addSeparator();
	newManagedAction(menu,"spelling",tr("Check Spelling"),SLOT(editSpell()),Qt::CTRL+Qt::SHIFT+Qt::Key_F7);
	newManagedAction(menu,"thesaurus",tr("Thesaurus"),SLOT(editThesaurus()),Qt::CTRL+Qt::SHIFT+Qt::Key_F8);

	menu->addSeparator();
	newManagedAction(menu,"reparse",tr("Refresh Structure"),SLOT(updateStructure()));
	newManagedAction(menu,"removePlaceHolders",tr("Remove Placeholders"),SLOT(editRemovePlaceHolders()),Qt::CTRL+Qt::SHIFT+Qt::Key_K);


//tools

	menu=newManagedMenu("main/tools",tr("&Tools"));
	newManagedAction(menu, "quickbuild",tr("Quick Build"), SLOT(QuickBuild()), Qt::Key_F1, ":/images/quick.png");

	menu->addSeparator();
	newManagedAction(menu, "latex",tr("LaTeX"), SLOT(commandFromAction()), Qt::Key_F2, ":/images/latex.png")->setData(BuildManager::CMD_LATEX);
	newManagedAction(menu, "viewdvi",tr("View Dvi"), SLOT(commandFromAction()), Qt::Key_F3, ":/images/viewdvi.png")->setData(BuildManager::CMD_VIEWDVI);
	newManagedAction(menu, "dvi2ps",tr("Dvi->PS"), SLOT(commandFromAction()), Qt::Key_F4, ":/images/dvips.png")->setData(BuildManager::CMD_DVIPS);
	newManagedAction(menu, "viewps",tr("View PS"), SLOT(commandFromAction()), Qt::Key_F5, ":/images/viewps.png")->setData(BuildManager::CMD_VIEWPS);
	newManagedAction(menu, "pdflatex",tr("PDFLaTeX"), SLOT(commandFromAction()), Qt::Key_F6, ":/images/pdflatex.png")->setData(BuildManager::CMD_PDFLATEX);
	newManagedAction(menu, "viewpdf",tr("View PDF"), SLOT(commandFromAction()), Qt::Key_F7, ":/images/viewpdf.png")->setData(BuildManager::CMD_VIEWPDF);
	newManagedAction(menu, "ps2pdf",tr("PS->PDF"), SLOT(commandFromAction()), Qt::Key_F8, ":/images/ps2pdf.png")->setData(BuildManager::CMD_PS2PDF);
	newManagedAction(menu, "dvipdf",tr("DVI->PDF"), SLOT(commandFromAction()), Qt::Key_F9, ":/images/dvipdf.png")->setData(BuildManager::CMD_DVIPDF);
	newManagedAction(menu, "viewlog",tr("View Log"), SLOT(RealViewLog()), Qt::Key_F10, ":/images/viewlog.png");
	newManagedAction(menu, "bibtex",tr("BibTeX"), SLOT(commandFromAction()), Qt::Key_F11)->setData(BuildManager::CMD_BIBTEX);
	newManagedAction(menu, "makeindex",tr("MakeIndex"), SLOT(commandFromAction()), Qt::Key_F12)->setData(BuildManager::CMD_MAKEINDEX);
	newManagedAction(menu, "clearmarkers",tr("Clear Markers"), SLOT(ClearMarkers()));

	menu->addSeparator();
	newManagedAction(menu, "metapost",tr("MetaPost"), SLOT(commandFromAction()))->setData(BuildManager::CMD_METAPOST);
	menu->addSeparator();
	newManagedAction(menu, "clean",tr("Clean"), SLOT(CleanAll()));
	menu->addSeparator();
	newManagedAction(menu, "htmlexport",tr("Convert to Html"), SLOT(WebPublish()));
	menu->addSeparator();
	newManagedAction(menu, "analysetext",tr("Analyse Text"), SLOT(AnalyseText()));
	newManagedAction(menu, "generaterandomtext",tr("Generate Random Text"), SLOT(GenerateRandomText()));

//  Latex/Math external
	configManager.loadManagedMenus(":/uiconfig.xml");
	// add some additional items
	menu=newManagedMenu("main/latex",tr("&Latex"));
	newManagedAction(menu, "insertrefnextlabel",tr("Insert \\ref to next label"), SLOT(editInsertRefToNextLabel()), Qt::ALT+Qt::CTRL+Qt::Key_R);
	newManagedAction(menu, "insertrefprevlabel",tr("Insert \\ref to previous label"), SLOT(editInsertRefToPrevLabel()));

//wizards

	menu=newManagedMenu("main/wizards",tr("&Wizards"));
	newManagedAction(menu, "start",tr("Quick Start"), SLOT(QuickDocument()));
	newManagedAction(menu, "letter",tr("Quick Letter"), SLOT(QuickLetter()));

	menu->addSeparator();
	newManagedAction(menu, "tabular",tr("Quick Tabular"), SLOT(QuickTabular()));
	newManagedAction(menu, "tabbing",tr("Quick Tabbing"), SLOT(QuickTabbing()));
	newManagedAction(menu, "array",tr("Quick Array"), SLOT(QuickArray()));

	menu=newManagedMenu("main/bibtex",tr("&Bibliography"));
	foreach (const BibTeXType& bt, BibTeXDialog::getPossibleBibTeXTypes())
		newManagedAction(menu,bt.name.mid(1), bt.description, SLOT(InsertBibEntryFromAction()))->setData(bt.name);
	menu->addSeparator();
	newManagedAction(menu, "clean", tr("Clean"), SLOT(CleanBib()));
	menu->addSeparator();
	newManagedAction(menu, "dialog", tr("BibTeX insert dialog"), SLOT(InsertBibEntry()));


//  User
	menu=newManagedMenu("main/user",tr("&User"));
	submenu=newManagedMenu(menu,"tags",tr("User &Tags"));
	for (int i=0; i<10; i++)
		newManagedAction(submenu, QString("tag%1").arg(i),QString("%1: %2").arg(i+1).arg(UserMenuName[i]), SLOT(InsertUserTag()), Qt::SHIFT+Qt::Key_F1+i)
		->setData(i);
	submenu->addSeparator();
	newManagedAction(submenu, QString("manage"),tr("Edit User &Tags"), SLOT(EditUserMenu()));

	submenu=newManagedMenu(menu,"commands",tr("User &Commands"));
	for (int i=0; i<5; i++)
		newManagedAction(submenu, QString("cmd%1").arg(i),QString("%1: %2").arg(i+1).arg(UserToolName[i]), SLOT(UserTool()), Qt::SHIFT+Qt::ALT+Qt::Key_F1+i)
		->setData(i);
	submenu->addSeparator();
	newManagedAction(submenu, QString("manage"),tr("Edit User &Commands"), SLOT(EditUserTool()));

//---view---
	menu=newManagedMenu("main/view",tr("&View"));
	newManagedAction(menu, "nextdocument",tr("Next Document"), SLOT(gotoNextDocument()), Qt::ALT+Qt::Key_PageUp);
	newManagedAction(menu, "prevdocument",tr("Previous Document"), SLOT(gotoPrevDocument()), Qt::ALT+Qt::Key_PageDown);

	menu->addSeparator();
	newManagedAction(menu, "structureview",leftPanel->toggleViewAction());
	outputViewAction=newManagedAction(menu, "outputview",tr("Messages / Log File"), SLOT(viewToggleOutputView()));
	outputViewAction->setCheckable(true);
	newManagedAction(menu, "closesomething",tr("Close Something"), SLOT(viewCloseSomething()), Qt::Key_Escape);

	menu->addSeparator();
	submenu=newManagedMenu(menu, "collapse", tr("Collapse"));
	newManagedAction(submenu, "all", tr("Everything"), SLOT(viewCollapseEverything()));
	newManagedAction(submenu, "block", tr("Nearest block"), SLOT(viewCollapseBlock()));
	for (int i=1; i<=4; i++)
		newManagedAction(submenu, QString::number(i), tr("Level %1").arg(i), SLOT(viewCollapseLevel()))->setData(i);
	submenu=newManagedMenu(menu, "expand", tr("Expand"));
	newManagedAction(submenu, "all", tr("Everything"), SLOT(viewExpandEverything()));
	newManagedAction(submenu, "block", tr("Nearest block"), SLOT(viewExpandBlock()));
	for (int i=1; i<=4; i++)
		newManagedAction(submenu, QString::number(i), tr("Level %1").arg(i), SLOT(viewExpandLevel()))->setData(i);

	menu->addSeparator();
	fullscreenModeAction=newManagedAction(menu, "fullscreenmode",tr("Fullscreen Mode"), SLOT(setFullScreenMode()));
	fullscreenModeAction->setCheckable(true);

//---options---
	menu=newManagedMenu("main/options",tr("&Options"));
	newManagedAction(menu, "config",tr("Configure TexMakerX"), SLOT(GeneralOptions()), 0,":/images/configure.png");

	menu->addSeparator();
	ToggleAct=newManagedAction(menu, "masterdocument",tr("Define Current Document as 'Master Document'"), SLOT(ToggleMode()));
	ToggleRememberAct=newManagedAction(menu, "remembersession",tr("Automatically restore session at next start"));
	ToggleRememberAct->setCheckable(true);

//---help---
	menu=newManagedMenu("main/help",tr("&Help"));
	newManagedAction(menu, "latexreference",tr("LaTeX Reference"), SLOT(LatexHelp()), 0,":/images/help.png");
	newManagedAction(menu, "usermanual",tr("User Manual"), SLOT(UserManualHelp()), 0,":/images/help.png");

	menu->addSeparator();
	newManagedAction(menu, "appinfo",tr("About TexMakerX"), SLOT(HelpAbout()), 0,":/images/appicon.png");

//-----context menus-----
	structureTreeView->setObjectName("StructureTree");
	structureTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
	newManagedAction(structureTreeView,"CopySection",tr("Copy"), SLOT(editSectionCopy()));
	newManagedAction(structureTreeView,"CutSection",tr("Cut"), SLOT(editSectionCut()));
	newManagedAction(structureTreeView,"PasteBefore",tr("Paste before"), SLOT(editSectionPasteBefore()));
	newManagedAction(structureTreeView,"PasteAfter",tr("Paste after"), SLOT(editSectionPasteAfter()));
	QAction* sep = new QAction(structureTreeView);
	sep->setSeparator(true);
	structureTreeView->addAction(sep);
	newManagedAction(structureTreeView,"IndentSection",tr("Indent Section"), SLOT(editIndentSection()));
	newManagedAction(structureTreeView,"UnIndentSection",tr("Unindent Section"), SLOT(editUnIndentSection()));
	connect(structureTreeView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(StructureContextMenu(QPoint)));


	configManager.modifyManagedShortcuts();
}

void Texmaker::setupToolBars() {
	QStringList list;
//file
	fileToolBar = addToolBar("File");
	fileToolBar->setObjectName("File");

	fileToolBar->addAction(getManagedAction("main/file/new"));
	fileToolBar->addAction(getManagedAction("main/file/open"));
	fileToolBar->addAction(getManagedAction("main/file/save"));
	fileToolBar->addAction(getManagedAction("main/file/close"));

//edit
	editToolBar = addToolBar("Edit");
	editToolBar->setObjectName("Edit");

	editToolBar->addAction(getManagedAction("main/edit/undo"));
	editToolBar->addAction(getManagedAction("main/edit/redo"));
	editToolBar->addAction(getManagedAction("main/edit/copy"));
	editToolBar->addAction(getManagedAction("main/edit/cut"));
	editToolBar->addAction(getManagedAction("main/edit/paste"));


//tools
	runToolBar = addToolBar("Tools");
	runToolBar->setObjectName("Tools");

	runToolBar->addAction(getManagedAction("main/tools/viewlog"));
	runToolBar->addAction(getManagedAction("main/edit/goto/errorprev"));
	runToolBar->addAction(getManagedAction("main/edit/goto/errornext"));

	runToolBar->addSeparator();
	runToolBar->addAction(getManagedAction("main/tools/quickbuild"));
	runToolBar->addAction(getManagedAction("main/tools/latex"));
	runToolBar->addAction(getManagedAction("main/tools/viewdvi"));
	runToolBar->addAction(getManagedAction("main/tools/dvi2ps"));
	runToolBar->addAction(getManagedAction("main/tools/viewps"));
	runToolBar->addAction(getManagedAction("main/tools/pdflatex"));
	runToolBar->addAction(getManagedAction("main/tools/viewpdf"));

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
	QFontMetrics fontMetrics(runToolBar->font());
	combo1=createComboToolButton(formatToolBar,list,runToolBar->height()-2,fontMetrics,this,SLOT(SectionCommand()));
	formatToolBar->addWidget(combo1);
	formatToolBar->addSeparator();

	list.clear();
	list.append("label");
	list.append("ref");
	list.append("pageref");
	list.append("index");
	list.append("cite");
	list.append("footnote");
	combo2=createComboToolButton(formatToolBar,list,runToolBar->height()-2,fontMetrics,this,SLOT(OtherCommand()));
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
	combo3=createComboToolButton(formatToolBar,list,runToolBar->height()-2,fontMetrics,this,SLOT(SizeCommand()));
	formatToolBar->addWidget(combo3);
	formatToolBar->addSeparator();

	formatToolBar->addAction(getManagedAction("main/latex/fontstyles/textbf"));
	formatToolBar->addAction(getManagedAction("main/latex/fontstyles/textit"));
	formatToolBar->addAction(getManagedAction("main/latex/fontstyles/underline"));
	formatToolBar->addAction(getManagedAction("main/latex/environment/flushleft"));
	formatToolBar->addAction(getManagedAction("main/latex/environment/center"));
	formatToolBar->addAction(getManagedAction("main/latex/environment/flushright"));
	formatToolBar->addSeparator();
	formatToolBar->addAction(getManagedAction("main/latex/spacing/newline"));

//math
	mathToolBar = addToolBar("Math");
	mathToolBar->setObjectName("Math");

	mathToolBar->addAction(getManagedAction("main/math/mathmode"));
	mathToolBar->addAction(getManagedAction("main/math/subscript"));
	mathToolBar->addAction(getManagedAction("main/math/superscript"));
	mathToolBar->addAction(getManagedAction("main/math/frac"));
	mathToolBar->addAction(getManagedAction("main/math/dfrac"));
	mathToolBar->addAction(getManagedAction("main/math/sqrt"));

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
	combo4=createComboToolButton(mathToolBar,list,runToolBar->height()-2,fontMetrics,this,SLOT(LeftDelimiter()));
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
	combo5=createComboToolButton(mathToolBar,list,runToolBar->height()-2,fontMetrics,this,SLOT(RightDelimiter()));
	mathToolBar->addWidget(combo5);

// spelling language
	spellToolBar = addToolBar("Spelling");
	spellToolBar->setObjectName("Spelling");
	list.clear();
	QDir fic=QFileInfo(configManager.spell_dic).absoluteDir();
	if (fic.exists() && fic.isReadable())
			list << fic.entryList(QStringList("*.dic"),QDir::Files,QDir::Name);


	comboSpell=createComboToolButton(spellToolBar,list,runToolBar->height()-2,fontMetrics,this,SLOT(SpellingLanguageChanged()),QFileInfo(configManager.spell_dic).fileName());
	spellToolBar->addWidget(comboSpell);
//custom toolbar
	//first apply custom icons
	QHash<QString, QVariant>::const_iterator i = configManager.replacedIconsOnMenus.constBegin();
	while (i != configManager.replacedIconsOnMenus.constEnd()) {
	    QString id=i.key();
	    QVariant zw=i.value();
	    QAction * act= getManagedAction(id);
	    if (act) {
		if(zw.canConvert<QString>()) act->setIcon(QIcon(zw.toString()));
	    }
	    i++;
	}
	//setup actual custom toolbar
	customToolBar = addToolBar("Custom");
	customToolBar->setObjectName("Custom");
	int l=configManager.listCustomActions.size();
	if(l>0){
	    for (int i=0; i<l; i++){
		QAction *act=getManagedAction(configManager.listCustomActions.at(i));
		if(act->icon().isNull()){
		    act->setIcon(QIcon(":/images/appicon.png"));
		}
		customToolBar->addAction(act);
	    }
	}
}


void Texmaker::createStatusBar() {
	QStatusBar * status=statusBar();
	stat1=new QLabel(status);
	stat2=new QLabel(status);
	stat3=new QLabel(status);
	status->addPermanentWidget(stat3,0);
	status->addPermanentWidget(stat2,0);
	status->addPermanentWidget(stat1,0);
//statCursor=new QLabel( status );
	for (int i=1; i<=3; i++) {
		QPushButton* pb=new QPushButton(QIcon(QString(":/images/bookmark%1.png").arg(i)),"",status);
		pb->setToolTip(tr("Click to jump to the bookmark"));
		connect(pb,SIGNAL(clicked()),getManagedAction(QString("main/edit/gotoBookmark/bookmark%1").arg(i)),SIGNAL(triggered()));
		pb->setMaximumSize(20,20);
		pb->setFlat(true);
		status->addPermanentWidget(pb,0);
	}
}

void Texmaker::UpdateCaption() {
	if (!currentEditorView()) documents.currentDocument=0;
	else documents.currentDocument=currentEditorView()->document;
	QString title;
	if (!currentEditorView())	{
		title="TexMakerX";
	} else {
		title="Document : "+getCurrentFileName();
		if (currentEditorView()->editor) {
			if (currentEditorView()->editor->getFileCodec()) stat3->setText(currentEditorView()->editor->getFileCodec()->name());
			else stat3->setText("unknown");
			QDocument::LineEnding le = currentEditorView()->editor->document()->lineEnding();
			if (le==QDocument::Conservative) le= currentEditorView()->editor->document()->originalLineEnding();
			switch (le) {
#ifdef Q_WS_WIN
			case QDocument::Local:
#endif
			case QDocument::Windows:
				getManagedAction("main/edit/lineend/crlf")->setChecked(true);
				break;
			case QDocument::Mac:
				getManagedAction("main/edit/lineend/cr")->setChecked(true);
				break;
			default:
				getManagedAction("main/edit/lineend/lf")->setChecked(true);
			}
			//input_encoding=current	EditorView()->editor->getEncoding();
		}
	}
	setWindowTitle(title);
	//updateStructure();
	cursorPositionChanged();
	if (singlemode) {
		outputView->resetMessagesAndLog();
	}
	QString finame=getCurrentFileName();
	if (finame!="") configManager.lastDocument=finame;
}

void Texmaker::CloseEditorTab(int tab) {
	int cur=EditorView->currentIndex();
	int total=EditorView->count();
	EditorView->setCurrentIndex(tab);
	fileClose();
	if (cur>tab) cur--;//removing moves to left
	if (total!=EditorView->count() && cur!=tab)//if user clicks cancel stay in clicked editor
		EditorView->setCurrentIndex(cur);
}
void Texmaker::showMarkTooltipForLogMessage(int error){
	if (!currentEditorView()) return;
	if (error<0 || error >= outputView->getLogModel()->count()) return;
	currentEditorView()->setLineMarkToolTip(outputView->getLogModel()->at(error).niceMessage());

}

void Texmaker::NewDocumentStatus(bool m) {
	LatexEditorView* edView = currentEditorView();
	if (!edView) return;
	int index=EditorView->currentIndex();
	if (qobject_cast<QEditor*>(sender()) && edView->editor!=sender()){
		edView=0;
		for (int i=0;i<EditorView->count();i++)
			if (qobject_cast<LatexEditorView*>(EditorView->widget(i))->editor==sender()){
				edView=	qobject_cast<LatexEditorView*>(EditorView->widget(i));
				index=i;
				break;
			}
		if (!edView) return;
	}
	if (m)
		EditorView->setTabIcon(index,QIcon(":/images/modified.png"));
	else
		EditorView->setTabIcon(index,QIcon(":/images/empty.png"));
	if (edView->editor->fileName().isEmpty())
		EditorView->setTabText(index,tr("untitled"));
	else
		EditorView->setTabText(index,edView->editor->name());
}

LatexEditorView *Texmaker::currentEditorView() const {
	return qobject_cast<LatexEditorView *>(EditorView->currentWidget());
}
QEditor* Texmaker::currentEditor() const{
	LatexEditorView* edView = currentEditorView();
	if (!edView) return 0;
	return edView->editor;
}
void Texmaker::configureNewEditorView(LatexEditorView *edit) {

	m_languages->setLanguage(edit->codeeditor->editor(), ".tex");
	//EditorView->setCurrentWidget(edit);

//edit->setFormats(m_formats->id("environment"),m_formats->id("referenceMultiple"),m_formats->id("referencePresent"),m_formats->id("referenceMissing"));

	connect(edit->editor, SIGNAL(contentModified(bool)), this, SLOT(NewDocumentStatus(bool)));
	connect(edit->editor, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChanged()));
	connect(edit, SIGNAL(showMarkTooltipForLogMessage(int)),this,SLOT(showMarkTooltipForLogMessage(int)));
	connect(edit, SIGNAL(needCitation(const QString&)),this,SLOT(InsertBibEntry(const QString&)));
	connect(edit, SIGNAL(showPreview(QString)),this,SLOT(showPreview(QString)));

	edit->setBibTeXIds(&documents.allBibTeXIds);
}

LatexEditorView* Texmaker::getEditorViewFromFileName(const QString &fileName){
	LatexDocument* document=documents.findDocument(fileName);
	if (!document) return 0;
	return document->getEditorView();
}


QString Texmaker::getCurrentFileName() {
	return documents.getCurrentFileName();
}
QString Texmaker::getCompileFileName(){
	return documents.getCompileFileName();
}
QString Texmaker::getCompilePath(){
	QString compFile=getCompileFileName();
	if (compFile.isEmpty()) return "";
	QString dir=QFileInfo(compFile).absolutePath();
	if (!dir.endsWith("/") && !dir.endsWith(QDir::separator())) dir.append(QDir::separator());
	return dir;
}
QString Texmaker::getPreferredPath(){
	QString dir=getCompilePath();
	if (!dir.isEmpty()) return dir;
	return QDir::homePath();
}
QString Texmaker::getAbsoluteFilePath(const QString & relName, const QString &extension){
	return documents.getAbsoluteFilePath(relName, extension);
}
QString Texmaker::getRelativeBaseName(const QString & file){
	QString basepath=getCompilePath();
	basepath.replace(QDir::separator(),"/");
	if (basepath.endsWith("/")) basepath=basepath.left(basepath.length()-1);

	QFileInfo fi(file);
	QString filename = fi.fileName();
	QString path = fi.path();
	if (path.endsWith("/")) path=path.left(path.length()-1);
	QStringList basedirs = basepath.split("/");
	QStringList dirs = path.split("/");
	//QStringList basedirs = QStringList::split("/", basepath, false);
	//QStringList dirs = QStringList::split("/", path, false);

	int nDirs = dirs.count();

	while (dirs.count() > 0 && basedirs.count() > 0 &&  dirs[0] == basedirs[0]) {
		dirs.pop_front();
		basedirs.pop_front();
	}

	if (nDirs != dirs.count()) {
		path = dirs.join("/");

		if (basedirs.count() > 0) {
			for (int j=0; j < basedirs.count(); ++j) {
				path = "../" + path;
			}
		}

		//if (path.length()>0 && path.right(1) != "/") path = path + "/";
	} else {
		path = fi.path();
	}

	if (path.length()>0 && !path.endsWith("/") && !path.endsWith("\\")) path+="/"; //necessary if basepath isn't given

	return path+fi.completeBaseName();
}

bool Texmaker::FileAlreadyOpen(QString f) {
	LatexEditorView* edView = getEditorViewFromFileName(f);
	if (!edView) return false;
	EditorView->setCurrentWidget(edView);
	return true;
}
///////////////////FILE//////////////////////////////////////


LatexEditorView* Texmaker::load(const QString &f , bool asProject) {
	QString f_real=f;
#ifdef Q_WS_WIN
	QRegExp regcheck("/([a-zA-Z]:[/\\\\].*)");
	if (regcheck.exactMatch(f)) f_real=regcheck.cap(1);
#endif
	raise();

	if (FileAlreadyOpen(f_real)) {
		if (asProject) {
			if (singlemode) ToggleMode();
			else if (!singlemode && MasterName != f_real) {
				ToggleMode();
				ToggleMode();
			}
		}
		return currentEditorView();
	}

	if (!QFile::exists(f_real)) return 0;
	bool bibTeXmodified=documents.bibTeXFilesModified;

	LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig);
	configureNewEditorView(edit);

	edit->document=documents.findDocument(f);
	if (!edit->document) {
		edit->document=new LatexDocument();
		edit->document->setEditorView(edit);
		documents.addDocument(edit->document);
	} else edit->document->setEditorView(edit);
	EditorView->addTab(edit, "[*] "+QFileInfo(f_real).fileName());
	EditorView->setCurrentWidget(edit);
	connect(edit->editor,SIGNAL(fileReloaded()),this,SLOT(fileReloaded()));

	QFile file(f_real);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this,tr("Error"), tr("You do not have read permission to this file."));
		return 0;
	}

	edit->editor->load(f_real,QDocument::defaultCodec());
	edit->editor->document()->setLineEnding(edit->editor->document()->originalLineEnding());

	edit->editor->setFocus();
	edit->document->setEditorView(edit); //update file name (if document didn't exist)
	UpdateCaption();
	NewDocumentStatus(false);
	MarkCurrentFileAsRecent();
	updateStructure();
	ShowStructure();
	if (asProject) {
		if (singlemode) ToggleMode();
		else if (!singlemode && MasterName != f_real) {
			ToggleMode();
			ToggleMode();
		}
	}
	if (outputView->logPresent()) DisplayLatexError(); //show marks
	if (!bibTeXmodified)
		documents.bibTeXFilesModified=false; //loading a file can change the list of included bib files, but we won't consider that as a modification of them, because then they don't have to be recompiled
	return edit;
}

void Texmaker::fileNew(QString fileName) {
	LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig);
	if (configManager.newfile_encoding)
		edit->editor->setFileCodec(configManager.newfile_encoding);
	else
		edit->editor->setFileCodec(QTextCodec::codecForName("utf-8"));

	configureNewEditorView(edit);

	edit->document=new LatexDocument();
	edit->document->setEditorView(edit);
	documents.addDocument(edit->document);

	EditorView->addTab(edit, fileName);
	EditorView->setCurrentWidget(edit);

	UpdateCaption();
	NewDocumentStatus(false);

	connect(edit->editor,SIGNAL(fileReloaded()),this,SLOT(fileReloaded()));

	edit->editor->setFocus();
}


void Texmaker::fileReloaded(){
	QEditor *mEditor = qobject_cast<QEditor *>(sender());
	if(mEditor==currentEditor()){
		updateStructure();
	}
}

void Texmaker::fileMakeTemplate() {
	if (!currentEditorView())
		return;

	// select a directory/filepath
	QString currentDir=configManager.configFileNameBase;

	// get a file name
	QString fn = QFileDialog::getSaveFileName(this,tr("Save As"),currentDir,"TeX files (*.tex)");
	if (!fn.isEmpty()) {
		int lastsep=qMax(fn.lastIndexOf("/"),fn.lastIndexOf("\\"));
		int lastpoint=fn.lastIndexOf(".");
		if (lastpoint <= lastsep) //if both aren't found or point is in directory name
			fn.append(".tex");
		// save file
		QString old_name=currentEditor()->fileName();
		QTextCodec *mCodec=currentEditor()->getFileCodec();
		currentEditor()->setFileCodec(QTextCodec::codecForName("utf-8"));
		currentEditor()->save(fn);
		currentEditor()->setFileName(old_name);
		currentEditor()->setFileCodec(mCodec);
		if(!userTemplatesList.contains(fn)) userTemplatesList.append(fn);
	}
}

void Texmaker::templateRemove(){
	QStringList templates=findResourceFiles("templates/","template_*.tex");
	int len=templates.size();
	if(templateSelectorDialog->ui.listWidget->currentRow()>=len){
		if(QMessageBox::question(this,tr("Please Confirm"), tr("Are you sure to remove that template permanently ?"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes){
			QString f_real=userTemplatesList.at(templateSelectorDialog->ui.listWidget->currentRow()-len);
			userTemplatesList.removeAt(templateSelectorDialog->ui.listWidget->currentRow()-len);
			templateSelectorDialog->ui.listWidget->takeItem(templateSelectorDialog->ui.listWidget->currentRow());
			QFile file(f_real);
			if(!file.remove()) QMessageBox::warning(this,tr("Error"), tr("You do not have permission to remove this file."));
		}
	} else QMessageBox::warning(this,tr("Error"), tr("You can not remove built-in templates."));

}

void Texmaker::templateEdit(){
	QStringList templates=findResourceFiles("templates/","template_*.tex");
	int len=templates.size();
	if(templateSelectorDialog->ui.listWidget->currentRow()>=len){
		load(userTemplatesList.at(templateSelectorDialog->ui.listWidget->currentRow()-len),false);
		templateSelectorDialog->close();
	} else QMessageBox::warning(this,tr("Error"), tr("You can not edit built-in templates."));
}

void Texmaker::fileNewFromTemplate() {
	// select Template
	QString f_real;
	if(!templateSelectorDialog) {
		templateSelectorDialog=new templateselector(this,tr("Templates"));
		QAction *act=new QAction(tr("Edit"),this);
		connect(act,SIGNAL(triggered()),this,SLOT(templateEdit()));
		templateSelectorDialog->ui.listWidget->addAction(act);
		act=new QAction(tr("Remove"),this);
		connect(act,SIGNAL(triggered()),this,SLOT(templateRemove()));
		templateSelectorDialog->ui.listWidget->addAction(act);
	}
	QStringList templates=findResourceFiles("templates/","template_*.tex");
	int len=templates.size();
	templates << userTemplatesList;
	templates.replaceInStrings(QRegExp("(^|^.*/)(template_)?"),"");
	templates.replaceInStrings(QRegExp(".tex$"),"");
	templateSelectorDialog->ui.listWidget->clear();
	templateSelectorDialog->ui.listWidget->insertItems(0,templates);

	if(templateSelectorDialog->exec()){
		if(templateSelectorDialog->ui.listWidget->currentRow()<len){
			f_real="templates/template_"+templateSelectorDialog->ui.listWidget->currentItem()->text()+".tex";
			f_real=findResourceFile(f_real);
		}else {
			f_real=userTemplatesList.at(templateSelectorDialog->ui.listWidget->currentRow()-len);
		}
		QFile file(f_real);
		if (!file.open(QIODevice::ReadOnly)) {
			QMessageBox::warning(this,tr("Error"), tr("You do not have read permission to this file."));
			return;
		}
		//set up new editor with template
		LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig);
		if (configManager.newfile_encoding)
			edit->editor->setFileCodec(configManager.newfile_encoding);
		else
			edit->editor->setFileCodec(QTextCodec::codecForName("utf-8"));

		configureNewEditorView(edit);

		edit->document=new LatexDocument();
		edit->document->setEditorView(edit);
		documents.addDocument(edit->document);

		EditorView->addTab(edit, "untitled");
		EditorView->setCurrentWidget(edit);

		QString mTemplate;
		QTextStream in(&file);
		in.setAutoDetectUnicode(true);
		while (!in.atEnd()) {
			QString line = in.readLine();
			mTemplate+=line+"\n";
		}
		CodeSnippet toInsert(mTemplate);
		bool flag=edit->editor->flag(QEditor::AutoIndent);
		edit->editor->setFlag(QEditor::AutoIndent,false);
		toInsert.insert(edit->editor);
		edit->editor->setFlag(QEditor::AutoIndent,flag);
		edit->editor->setCursorPosition(0,0);
		edit->editor->nextPlaceHolder();
		edit->editor->ensureCursorVisible();
		/*if (configManager.autodetectLoadedFile) edit->editor->load(f_real,QDocument::defaultcodec);
		else edit->editor->load(f_real,configManager.newfile_encoding);
		edit->editor->document()->setLineEnding(edit->editor->document()->originalLineEnding());
		*/

		//edit->editor->setFileName("untitled");
		UpdateCaption();
		NewDocumentStatus(true);

		edit->editor->setFocus();

	}
}


void Texmaker::fileOpen() {
	QString currentDir=QDir::homePath();
	if (!configManager.lastDocument.isEmpty()) {
		QFileInfo fi(configManager.lastDocument);
		if (fi.exists() && fi.isReadable()) currentDir=fi.absolutePath();
	}
	QStringList files = QFileDialog::getOpenFileNames(this,tr("Open Files"),currentDir,"TeX files (*.tex *.bib *.sty *.cls *.mp);;All files (*)");
	foreach (const QString& fn, files)
		load(fn);
}

void Texmaker::fileRestoreSession(){
	fileCloseAll();
	for (int i=0; i<configManager.sessionFilesToRestore.size(); i++)
		load(configManager.sessionFilesToRestore[i], configManager.sessionFilesToRestore[i]==configManager.sessionMaster);
	FileAlreadyOpen(configManager.sessionCurrent);
}

void Texmaker::fileSave() {
	if (!currentEditor())
		return;

	if (currentEditor()->fileName()=="" || !currentEditor()->fileInfo().exists())
		fileSaveAs();
	else {
		/*QFile file( *filenames.find( currentEditorView() ) );
		if ( !file.open( QIODevice::WriteOnly ) )
			{
			QMessageBox::warning( this,tr("Error"),tr("The file could not be saved. Please check if you have write permission."));
			return;
			}*/
		currentEditor()->save();
		//currentEditorView()->editor->setModified(false);
		MarkCurrentFileAsRecent();
		if(configManager.autoCheckinAfterSave) {
			checkin(QStringList(currentEditor()->fileName()));
			if(configManager.svnUndo) currentEditor()->document()->clearUndo();
		}
	}
	UpdateCaption();
	updateStructure();
}

void Texmaker::fileSaveAs(QString fileName) {
	if (!currentEditorView())
		return;

	// select a directory/filepath
	QString currentDir=QDir::homePath();
	if (fileName.isEmpty()) {
		if (!configManager.lastDocument.isEmpty()) {
			QFileInfo fi(configManager.lastDocument);
			if (fi.exists() && fi.isReadable())
				currentDir=fi.absolutePath();
		}
	} else {
		QFileInfo currentFile(fileName);
		if (currentFile.absoluteDir().exists())
			currentDir = fileName;
	}

	// get a file name
	QString fn = QFileDialog::getSaveFileName(this,tr("Save As"),currentDir,"TeX files (*.tex *.bib *.sty *.cls *.mp);;All files (*.*)");
	if (!fn.isEmpty()) {
		int lastsep=qMax(fn.lastIndexOf("/"),fn.lastIndexOf("\\"));
		int lastpoint=fn.lastIndexOf(".");
		if (lastpoint <= lastsep) //if both aren't found or point is in directory name
			fn.append(".tex");
		// save file
		currentEditor()->save(fn);
		currentEditorView()->document->setEditorView(currentEditorView()); //update file name
		MarkCurrentFileAsRecent();

		if(configManager.autoCheckinAfterSave){
			if(svnadd(QStringList(currentEditor()->fileName()))){
				checkin(QStringList(currentEditor()->fileName()));
			} else {
				//create simple repository
				svncreateRep(currentEditor()->fileName());
				svnadd(QStringList(currentEditor()->fileName()));
				checkin(QStringList(currentEditor()->fileName()));
			}

		}

		EditorView->setTabText(EditorView->indexOf(currentEditorView()),currentEditor()->name());
	}

	UpdateCaption();
}

void Texmaker::fileSaveAll() {
//LatexEditorView *temp = new LatexEditorView(EditorView,colorMath,colorCommand,colorKeyword);
//temp=currentEditorView();
	int currentIndex=EditorView->indexOf(currentEditorView());
	for (int i=0;i<EditorView->count(); i++){
		LatexEditorView *edView = qobject_cast<LatexEditorView*>(EditorView->widget(i));
		if (edView->editor->fileName().isEmpty() || edView->editor->isInConflict()) {
			EditorView->setCurrentIndex(i);
			if (edView->editor->fileName().isEmpty()) fileSaveAs();
			else edView->editor->save();
		} else if (!edView->editor->fileName().endsWith(".bib"))
			edView->editor->save();
		else if (edView->editor->isContentModified()){ //only save modified bib files, to prevent unecessary recompilations
			edView->editor->save();

			QString temp=edView->editor->fileName();
			temp=temp.replace(QDir::separator(),"/");
			documents.bibTeXFilesModified = documents.bibTeXFilesModified  || documents.mentionedBibTeXFiles.contains(temp);//call bibtex on next compilation (this would also set as soon as the user switch to a tex file, but he could compile before switching)
		}
		//currentEditor()->save();
		//UpdateCaption();
	}
	if (EditorView->currentIndex()!=currentIndex)
		EditorView->setCurrentIndex(currentIndex);
	//UpdateCaption();
}

void Texmaker::fileClose() {
	if (!currentEditorView())	return;
	if (currentEditorView()->editor->isContentModified()) {
		switch (QMessageBox::warning(this, "TexMakerX",
					     tr("The document contains unsaved work. "
						"Do you want to save it before closing?"),
					     tr("Save and Close"), tr("Don't Save and Close"), tr("Cancel"),
					     0,
					     2)) {
		case 0:
			fileSave();
			documents.deleteDocument(currentEditorView()->document);
			break;
		case 1:
			documents.deleteDocument(currentEditorView()->document);
			break;
		case 2:
		default:
			return;
			break;
		}
	} else documents.deleteDocument(currentEditorView()->document);
	UpdateCaption();
}

void Texmaker::fileCloseAll() {
	bool go=true;
	while (currentEditorView() && go) {
		if (currentEditorView()->editor->isContentModified()) {
			switch (QMessageBox::warning(this, "TexMakerX",
						     tr("The document contains unsaved work. "
							"Do you want to save it before exiting?"),
						     tr("Save and Close"), tr("Don't Save and Close"), tr("Cancel"),
						     0,
						     2)) {
			case 0:
				fileSave();
				documents.deleteDocument(currentEditorView()->document);
				break;
			case 1:
				documents.deleteDocument(currentEditorView()->document);
				break;
			case 2:
			default:
				go=false;
				return;
				break;
			}
		} else
			documents.deleteDocument(currentEditorView()->document);
	}
	if (!singlemode)
		ToggleMode();
	UpdateCaption();
}

void Texmaker::fileExit() {
	if (canCloseNow())
		qApp->quit();
}

bool Texmaker::canCloseNow(){
	SaveSettings();
	bool accept=true;
	while (currentEditorView() && accept) {
		if (currentEditorView()->editor->isContentModified()) {
			switch (QMessageBox::warning(this, "TexMakerX",
						     tr("The document contains unsaved work. "
							"Do you want to save it before exiting?"),
						     tr("Save and Close"), tr("Don't Save and Close"), tr("Cancel"),
						     0,
						     2)) {
			case 0:
				fileSave();
				documents.deleteDocument(currentEditorView()->document);
				break;
			case 1:
				documents.deleteDocument(currentEditorView()->document);
				break;
			case 2:
			default:
				accept=false;
				break;
			}
		} else
			documents.deleteDocument(currentEditorView()->document);
	}
	if (accept)
		if (mainSpeller) {
			delete mainSpeller; //this saves the ignore list
			mainSpeller=0;
		}
	return accept;
}
void Texmaker::closeEvent(QCloseEvent *e) {
	if (canCloseNow())  e->accept();
	else e->ignore();
}


void Texmaker::fileOpenRecent() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (action) load(action->data().toString());
}

void Texmaker::fileOpenRecentProject() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (action) load(action->data().toString(),true);
}

void Texmaker::MarkCurrentFileAsRecent(){
	configManager.addRecentFile(getCurrentFileName(),!singlemode && MasterName==getCurrentFileName());
}

void Texmaker::filePrint() {
	if (!currentEditorView()) return;
	currentEditorView()->editor->print();

}
//////////////////////////// EDIT ///////////////////////
void Texmaker::editUndo() {
	if (!currentEditorView()) return;

	QVariant zw=currentEditor()->property("undoRevision");
	int undoRevision=zw.canConvert<int>()?zw.toInt():0;

	if(currentEditor()->document()->canUndo()){
		currentEditor()->undo();
		if(undoRevision>0) {
			undoRevision=-1;
			currentEditor()->setProperty("undoRevision",undoRevision);
		}
	}else{
		if(configManager.svnUndo && (undoRevision>=0)){
			svnUndo();
		}
	}

}

void Texmaker::editRedo() {
	if (!currentEditorView()) return;

	QVariant zw=currentEditor()->property("undoRevision");
	int undoRevision=zw.canConvert<int>()?zw.toInt():0;

	if(currentEditor()->document()->canUndo()){
		currentEditorView()->editor->redo();
	} else {
		if(configManager.svnUndo && (undoRevision>0)){
			svnUndo(true);
		}
	}
}

void Texmaker::editCut() {
	if (!currentEditorView()) return;
	currentEditorView()->editor->cut();
}

void Texmaker::editCopy() {
	if (!currentEditorView()) return;
	currentEditorView()->editor->copy();
}

void Texmaker::editPaste() {
	if (!currentEditorView()) return;
	currentEditorView()->editor->paste();
}

void Texmaker::editPasteLatex() {
	if (!currentEditorView()) return;
// manipulate clipboard text
	QClipboard *clipboard = QApplication::clipboard();
	QString originalText = clipboard->text();
	QString newText=textToLatex(originalText);
	//clipboard->setText(newText);
// insert
	//currentEditorView()->editor->paste();
	QMimeData md;
	md.setText(newText);
	currentEditorView()->editor->insertFromMimeData(&md);
}

void Texmaker::convertToLatex() {
	if (!currentEditorView()) return;
// get selection and change it
	QDocumentCursor c = currentEditorView()->editor->cursor();
	QString originalText = c.selectedText();
	QString newText=textToLatex(originalText);
// insert
	c.insertText(newText);
}

void Texmaker::editSelectAll() {
	if (!currentEditorView()) return;
	currentEditorView()->editor->selectAll();
}

void Texmaker::editEraseLine() {
	if (!currentEditorView()) return;
	QDocumentCursor c = currentEditorView()->editor->cursor();
	c.eraseLine();
}

void Texmaker::editFind() {
	if (!currentEditorView())	return;
	currentEditorView()->editor->find();
}

void Texmaker::editFindNext() {
	if (!currentEditorView())	return;
	currentEditorView()->editor->findNext();
}


void Texmaker::editReplace() {
	if (!currentEditorView())	return;
	currentEditorView()->editor->replace();
}

void Texmaker::editGotoLine() {
	if (!currentEditorView())	return;
	currentEditorView()->editor->gotoLine();
}

void Texmaker::editJumpToLastChange() {
	if (!currentEditorView())	return;
	currentEditorView()->jumpChangePositionBackward();
}
void Texmaker::editJumpToLastChangeForward() {
	if (!currentEditorView())	return;
	currentEditorView()->jumpChangePositionForward();
}

void Texmaker::editGotoDefinition(){
	if (!currentEditorView())	return;
	QDocumentCursor c=currentEditor()->cursor();
	QString command, value;
	switch (LatexParser::findContext(c.line().text(), c.columnNumber(), command, value)) {
		case LatexParser::Reference:
			currentEditorView()->gotoToLabel(value);
			break;
		default:; //TODO: Jump to command definition and in bib files
	}
}

void Texmaker::editComment() {
	if (!currentEditorView())	return;
	currentEditorView()->editor->commentSelection();
}

void Texmaker::editUncomment() {
	if (!currentEditorView())	return;
	currentEditorView()->editor->uncommentSelection();
}

void Texmaker::editIndent() {
	if (!currentEditorView())	return;
	currentEditorView()->editor->indentSelection();
}

void Texmaker::editUnindent() {
	if (!currentEditorView())	return;
	currentEditorView()->editor->unindentSelection();
}

void Texmaker::editHardLineBreak(){
	if (!currentEditorView()) return;
	UniversalInputDialog dialog;
	dialog.addVariable(&configManager.lastHardWrapColumn, "Insert hard line breaks after so many characters:");
	dialog.addVariable(&configManager.lastHardWrapSmartScopeSelection, "Smart scope selecting");
	dialog.addVariable(&configManager.lastHardWrapJoinLines, "Join lines before wrapping");
	if (dialog.exec()==QDialog::Accepted)
		currentEditorView()->insertHardLineBreaks(configManager.lastHardWrapColumn, configManager.lastHardWrapSmartScopeSelection, configManager.lastHardWrapJoinLines);
}

void Texmaker::editHardLineBreakRepeat() {
	if (!currentEditorView()) return;
	currentEditorView()->insertHardLineBreaks(configManager.lastHardWrapColumn, configManager.lastHardWrapSmartScopeSelection, configManager.lastHardWrapJoinLines);
}

void Texmaker::editSpell() {
	if (!currentEditorView()) {
		QMessageBox::information(this,"TexMakerX",tr("No document open"),0);
		return;
	}
	if (!spellDlg) spellDlg=new SpellerDialog(this,mainSpeller);
	spellDlg->setEditorView(currentEditorView());
	spellDlg->startSpelling();
}

void Texmaker::editThesaurus() {
	if (!currentEditorView()) {
		QMessageBox::information(this,"TexMakerX",tr("No document open"),0);
		return;
	}
	if (thesaurusFileName=="<dontLoad>") {
		QMessageBox::warning(this,tr("Error"), tr("Can't load Thesaurus Database"));
		return;
	}
	QDocumentCursor m_cursor=currentEditorView()->editor->cursor();
	if(thesaurusDialog==0) thesaurusDialog=new ThesaurusDialog(this);
	//thesaurusDialog->readDatabase(thesaurus_database);
	// alternative version for concurrent setup
	if (thesaurusFileName!=configManager.thesaurus_database){


		thesaurusFileName=configManager.thesaurus_database;

#if QT_VERSION >= 0x040500
		//thesaurusFuture=QtConcurrent::run(&ThesaurusDialog::loadDatabase,file);
		ThesaurusDatabaseType database=thesaurusFuture.result();
#else
		if (!QFile::exists(configManager.thesaurus_database)) return;

		databasefile=new QFile(configManagerthesaurus_database);
		if (!databasefile->open(QIODevice::ReadOnly)) {
			QMessageBox::warning(this,tr("Error"), tr("You do not have read permission to this file."));
			thesaurusFileName="<dontLoad>";
			return;
		}
		ThesaurusDatabaseType database=ThesaurusDialog::loadDatabase(databasefile);

#endif
		thesaurusDialog->setDatabase(database);
		delete databasefile;
		databasefile=0;
	}
	// end of mocifications
	QString word;
	if(m_cursor.hasSelection()){
		word=m_cursor.selectedText();
	} else {
		m_cursor.select(QDocumentCursor::WordUnderCursor);
		word=m_cursor.selectedText();
	}
	if(word.isEmpty()) return;
	word=latexToPlainWord(word);
	thesaurusDialog->setSearchWord(word);
	if(thesaurusDialog->exec()){
		QString replace=thesaurusDialog->getReplaceWord();
		m_cursor.insertText(replace);
	}
}

void Texmaker::editChangeLineEnding() {
	if (!currentEditorView()) return;
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	currentEditorView()->editor->document()->setLineEnding(QDocument::LineEnding(action->data().toInt()));
	UpdateCaption();
}
void Texmaker::editSetupEncoding() {
	if (!currentEditorView()) return;
	EncodingDialog enc(this,currentEditorView()->editor);
	enc.exec();
	UpdateCaption();
}

void Texmaker::editIndentSection() {
	StructureEntry *entry=LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry || !entry->document->getEditorView()) return;
	EditorView->setCurrentWidget(entry->document->getEditorView());
	QDocumentSelection sel = entry->document->sectionSelection(entry);

	// replace list
	QStringList m_replace;
	m_replace << "\\subparagraph" << "\\paragraph" << "\\subsubsection" << "\\subsection" << "\\section" << "\\chapter";
	// replace sections
	QString m_line;
	QDocumentCursor m_cursor=currentEditorView()->editor->cursor();
	for (int l=sel.startLine; l<sel.endLine; l++) {
		currentEditorView()->editor->setCursorPosition(l,0);
		m_cursor=currentEditorView()->editor->cursor();
		m_line=currentEditorView()->editor->cursor().line().text();
		QString m_old="";
		foreach(QString elem,m_replace) {
			if (m_old!="") m_line.replace(elem,m_old);
			m_old=elem;
		}

		m_cursor.movePosition(1,QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
		currentEditorView()->editor->setCursor(m_cursor);
		currentEditorView()->editor->cursor().insertText(m_line);
	}

}

void Texmaker::editUnIndentSection() {
	StructureEntry *entry=LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry || !entry->document->getEditorView()) return;
	EditorView->setCurrentWidget(entry->document->getEditorView());
	QDocumentSelection sel = entry->document->sectionSelection(entry);

	QStringList m_replace;

	m_replace << "\\chapter" << "\\section" << "\\subsection" << "\\subsubsection" << "\\paragraph" << "\\subparagraph" ;

	// replace sections
	QString m_line;
	QDocumentCursor m_cursor=currentEditorView()->editor->cursor();
	for (int l=sel.startLine; l<sel.endLine; l++) {
		currentEditorView()->editor->setCursorPosition(l,0);
		m_cursor=currentEditorView()->editor->cursor();
		m_line=currentEditorView()->editor->cursor().line().text();
		QString m_old="";
		foreach(QString elem,m_replace) {
			if (m_old!="") m_line.replace(elem,m_old);
			m_old=elem;
		}

		m_cursor.movePosition(1,QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
		currentEditorView()->editor->setCursor(m_cursor);
		currentEditorView()->editor->cursor().insertText(m_line);
	}

}

void Texmaker::editSectionCopy() {
	// called by action
	StructureEntry *entry=LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry || !entry->document->getEditorView()) return;
	EditorView->setCurrentWidget(entry->document->getEditorView());
	QDocumentSelection sel = entry->document->sectionSelection(entry);
	editSectionCopy(sel.startLine+1,sel.endLine);
}

void Texmaker::editSectionCut() {
	// called by action
	StructureEntry *entry=LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry || !entry->document->getEditorView()) return;
	EditorView->setCurrentWidget(entry->document->getEditorView());
	QDocumentSelection sel = entry->document->sectionSelection(entry);
	editSectionCut(sel.startLine+1,sel.endLine);
	//UpdateStructure();
}

void Texmaker::editSectionCopy(int startingLine, int endLine) {
	if (!currentEditorView()) return;

	currentEditorView()->editor->setCursorPosition(startingLine-1,0);
	QDocumentCursor m_cursor=currentEditorView()->editor->cursor();
	//m_cursor.movePosition(1, QDocumentCursor::NextLine, QDocumentCursor::KeepAnchor);
	m_cursor.setSilent(true);
	m_cursor.movePosition(endLine-startingLine, QDocumentCursor::NextLine, QDocumentCursor::KeepAnchor);
	m_cursor.movePosition(0,QDocumentCursor::EndOfLine,QDocumentCursor::KeepAnchor);
	currentEditorView()->editor->setCursor(m_cursor);
	currentEditorView()->editor->copy();
}

void Texmaker::editSectionCut(int startingLine, int endLine) {
	if (!currentEditorView()) return;
	currentEditorView()->editor->setCursorPosition(startingLine-1,0);
	QDocumentCursor m_cursor=currentEditorView()->editor->cursor();
	m_cursor.setSilent(true);
	m_cursor.movePosition(endLine-startingLine, QDocumentCursor::NextLine, QDocumentCursor::KeepAnchor);
	m_cursor.movePosition(0,QDocumentCursor::EndOfLine,QDocumentCursor::KeepAnchor);
	currentEditorView()->editor->setCursor(m_cursor);
	currentEditorView()->editor->cut();
}

void Texmaker::editSectionPasteBefore() {
	StructureEntry *entry=LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry || !entry->document->getEditorView()) return;
	EditorView->setCurrentWidget(entry->document->getEditorView());
	editSectionPasteBefore(entry->getRealLineNumber());
	//UpdateStructure();
}

void Texmaker::editSectionPasteAfter() {
	StructureEntry *entry=LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry || !entry->document->getEditorView()) return;
	EditorView->setCurrentWidget(entry->document->getEditorView());
	QDocumentSelection sel=entry->document->sectionSelection(entry);
	editSectionPasteAfter(sel.endLine);
	//UpdateStructure();
}

void Texmaker::editSectionPasteAfter(int line) {
	if (line>=currentEditorView()->editor->document()->lines()) {
		currentEditorView()->editor->setCursorPosition(line-1,0);
		QDocumentCursor c=currentEditorView()->editor->cursor();
		c.movePosition(1,QDocumentCursor::End,QDocumentCursor::MoveAnchor);
		currentEditorView()->editor->setCursor(c);
		currentEditorView()->editor->cursor().insertText("\n");
	} else {
		currentEditorView()->editor->setCursorPosition(line,0);
		currentEditorView()->editor->cursor().insertText("\n");
		currentEditorView()->editor->setCursorPosition(line,0);
	}
	editPaste();
	//UpdateStructure();
}

void Texmaker::editSectionPasteBefore(int line) {
	currentEditorView()->editor->setCursorPosition(line,0);
	currentEditorView()->editor->cursor().insertText("\n");
	currentEditorView()->editor->setCursorPosition(line,0);
	editPaste();
	//UpdateStructure();
}


/////////////// CONFIG ////////////////////
void Texmaker::ReadSettings() {
	configManager.buildManager=&buildManager;
	QSettings *config=configManager.readSettings();

	config->beginGroup("texmaker");
	singlemode=true;

	QRect screen = QApplication::desktop()->screenGeometry();
	int w= config->value("Geometries/MainwindowWidth",screen.width()-100).toInt();
	int h= config->value("Geometries/MainwindowHeight",screen.height()-100).toInt() ;
	int x= config->value("Geometries/MainwindowX",10).toInt();
	int y= config->value("Geometries/MainwindowY",10).toInt() ;
	resize(w,h);
	// in case desktop has changed since last run
	while(x>screen.width() && screen.width() > 0) x-=screen.width();
	move(x,y);
	windowstate=config->value("MainWindowState").toByteArray();
	stateFullScreen=config->value("MainWindowFullssscreenState").toByteArray();
	tobemaximized=config->value("MainWindow/Maximized",false).toBool();
	tobefullscreen=config->value("MainWindow/FullScreen",false).toBool();


	showoutputview=config->value("Show/OutputView",true).toBool();
	showstructview=config->value("Show/Structureview",true).toBool();

	userClassList=config->value("Tools/User Class").toStringList();
	userPaperList=config->value("Tools/User Paper").toStringList();
	userEncodingList=config->value("Tools/User Encoding").toStringList();
	userOptionsList=config->value("Tools/User Options").toStringList();

	userTemplatesList=config->value("User/Templates").toStringList();

	/*for (int i=0; i<=9; i++) {
		UserMenuName[i]=config->value(QString("User/Menu%1").arg(i+1),"").toString();
		UserMenuTag[i]=config->value(QString("User/Tag%1").arg(i+1),"").toString();
		}*/
	UserMenuName=config->value("User/TagNames",QStringList()<<""<<""<<""<<""<<""<<""<<""<<""<<""<<"").toStringList();
	UserMenuTag=config->value("User/Tags",QStringList()<<""<<""<<""<<""<<""<<""<<""<<""<<""<<"").toStringList();
	UserMenuAbbrev=config->value("User/TagAbbrevs",QStringList()<<""<<""<<""<<""<<""<<""<<""<<""<<""<<"").toStringList();
	for (int i=0; i<=4; i++) {
		UserToolName[i]=config->value(QString("User/ToolName%1").arg(i+1),"").toString();
		UserToolCommand[i]=config->value(QString("User/Tool%1").arg(i+1),"").toString();
	}

	LatexParser::structureCommands.clear();
	if(config->value("Structure/Structure Level 1","").toString()==""){
		LatexParser::structureCommands << "\\part" << "\\chapter" << "\\section" << "\\subsection" << "\\subsubsection";
	}else{
		int i=0;
		QString elem;
		while((elem=config->value("Structure/Structure Level "+QString::number(i+1),"").toString())!=""){
			if (!elem.startsWith("\\")) elem=elem.prepend("\\");
			LatexParser::structureCommands << elem;
			i++;
		}
	}

	document_class=config->value("Quick/Class","article").toString();
	typeface_size=config->value("Quick/Typeface","10pt").toString();
	paper_size=config->value("Quick/Papersize","a4paper").toString();
	document_encoding=config->value("Quick/Encoding","latin1").toString();
	ams_packages=config->value("Quick/AMS",true).toBool();
	makeidx_package=config->value("Quick/MakeIndex",false).toBool();
	author=config->value("Quick/Author","").toString();

#if QT_VERSION >= 0x040500
	if (QFile::exists(configManager.thesaurus_database)) {

	databasefile=new QFile(configManager.thesaurus_database);
	if (!databasefile->open(QIODevice::ReadOnly)) {
		//QMessageBox::warning(this,tr("Error"), tr("You do not have read permission to this file."));
		thesaurusFileName="<dontLoad>";
	}

		thesaurusFuture=QtConcurrent::run(&ThesaurusDialog::loadDatabase,databasefile);
	} else
		thesaurusFileName="<dontLoad>";
#endif


	//for (int i=0; i <412 ; i++)
	//	symbolScore[i]=config->value("Symbols/symbol"+QString::number(i),0).toInt();
	MapForSymbols= new QVariantMap;
	*MapForSymbols=config->value("Symbols/Quantity").toMap();

	hiddenLeftPanelWidgets=config->value("Symbols/hiddenlists","").toString();
	symbolFavorites=config->value("Symbols/Favorite IDs",QStringList()).toStringList();

	config->endGroup();

	config->beginGroup("formats");
	m_formats = new QFormatFactory(":/qxs/defaultFormats.qxf", this); //load default formats from resource file
	m_formats->load(*config,true); //load customized formats
	config->endGroup();

	delete config;

	documents.settingsRead();
}

void Texmaker::SaveSettings() {
	QSettings *config=configManager.saveSettings();

	config->beginGroup("texmaker");
	QList<int> sizes;
	QList<int>::Iterator it;

	if(isFullScreen()){
		config->setValue("MainWindowState",windowstate);
		config->setValue("MainWindowFullssscreenState",saveState(1));
	}else {
		config->setValue("MainWindowState",saveState(0));
		config->setValue("MainWindowFullssscreenState",stateFullScreen);
	}
	config->setValue("MainWindow/Maximized", isMaximized());
	config->setValue("MainWindow/FullScreen", isFullScreen());

	config->setValue("Geometries/MainwindowWidth", width());

	config->setValue("Geometries/MainwindowHeight", height());
	config->setValue("Geometries/MainwindowX", x());
	config->setValue("Geometries/MainwindowY", y());


	config->setValue("Show/OutputView",showoutputview);

	config->setValue("Show/Structureview",showstructview);

	if (userClassList.count()>0)
		config->setValue("Tools/User Class",userClassList);  // not removable , okay this way ?
	if (userPaperList.count()>0) config->setValue("Tools/User Paper",userPaperList);
	if (userEncodingList.count()>0) config->setValue("Tools/User Encoding",userEncodingList);
	if (userOptionsList.count()>0) config->setValue("Tools/User Options",userOptionsList);

	config->setValue("User/Templates",userTemplatesList);

	config->setValue("Files/RestoreSession",ToggleRememberAct->isChecked());
	//always store session for manual reload
	QStringList curFiles;//store in order
	for (int i=0; i<EditorView->count(); i++) {
		LatexEditorView *ed=qobject_cast<LatexEditorView *>(EditorView->widget(i));
		if (ed) curFiles.append(ed->editor->fileName());
	}
	config->setValue("Files/Session/Files",curFiles);
	config->setValue("Files/Session/CurrentFile",currentEditorView()?currentEditor()->fileName():"");
	config->setValue("Files/Session/MasterFile",singlemode?"":MasterName);

	config->setValue("User/TagNames",UserMenuName);
	config->setValue("User/Tags",UserMenuTag);
	config->setValue("User/TagAbbrevs",UserMenuAbbrev);

	for (int i=0; i<=4; i++) {
		config->setValue(QString("User/ToolName%1").arg(i+1),UserToolName[i]);
		config->setValue(QString("User/Tool%1").arg(i+1),UserToolCommand[i]);
	}

	for(int i=0;i<struct_level.count();i++)
	    config->setValue("Structure/Structure Level "+QString::number(i+1),struct_level[i]);

	config->setValue("Quick/Class",document_class);

	config->setValue("Quick/Typeface",typeface_size);
	config->setValue("Quick/Papersize",paper_size);
	config->setValue("Quick/Encoding",document_encoding);
	config->setValue("Quick/AMS",ams_packages);

	config->setValue("Quick/MakeIndex",makeidx_package);
	config->setValue("Quick/Author",author);

	//for (int i=0; i <412 ; i++) {
	//	config->setValue("Symbols/symbol"+QString::number(i),symbolScore[i]);
	//}
	MapForSymbols= new QVariantMap;
	for(int i=0;i<leftPanel->widgetCount();i++){
		if (!leftPanel->widget(i)->property("isSymbolGrid").toBool()) continue;
		QTableWidget* tw=qobject_cast<QTableWidget*>(leftPanel->widget(i));
		foreach(QTableWidgetItem* elem,tw->findItems("*",Qt::MatchWildcard)){
			if(!elem) continue;
			int cnt=elem->data(Qt::UserRole).toInt();
			if (cnt<1) continue;
			QString text=elem->text();
			if(MapForSymbols->value(text).toInt()>cnt) cnt=MapForSymbols->value(text).toInt();
			MapForSymbols->insert(text,cnt);
		}
	}
	config->setValue("Symbols/Quantity",*MapForSymbols);
	delete MapForSymbols;
	config->setValue("Symbols/Favorite IDs",symbolFavorites);

	config->setValue("Symbols/hiddenlists",leftPanel->hiddenWidgets());



	config->endGroup();

	config->beginGroup("formats");
	m_formats->save(*config);
	config->endGroup();

	delete config;
}

////////////////// STRUCTURE ///////////////////
void Texmaker::ShowStructure() {
	leftPanel->setCurrentWidget(structureTreeView);
}

void Texmaker::updateStructure() {
// collect user define tex commands for completer
// initialize List
	if (!currentEditorView() || !currentEditorView()->document) return;
	currentEditorView()->document->updateStructure();

	if (configManager.parseBibTeX) documents.updateBibFiles();
	updateCompleter();
	cursorPositionChanged();

	//structureTreeView->reset();
}

void Texmaker::clickedOnStructureEntry(const QModelIndex & index){
	const StructureEntry* entry = LatexDocumentsModel::indexToStructureEntry(index);
	if (!entry) return;
	if (!entry->document) return;

	Qt::MouseButtons mb=QApplication::mouseButtons();
	if (QApplication::mouseButtons()==Qt::RightButton) return; // avoid jumping to line if contextmenu is called

	switch (entry->type){
		case StructureEntry::SE_DOCUMENT_ROOT:
			if (entry->document->getEditorView())
				EditorView->setCurrentWidget(entry->document->getEditorView());
			else
				load(entry->document->getFileName());
			break;

		case StructureEntry::SE_OVERVIEW:
			break;

		case StructureEntry::SE_SECTION:
		case StructureEntry::SE_TODO:
		case StructureEntry::SE_LABEL:{
			int lineNr=-1;
			mDontScrollToItem = entry->type!=StructureEntry::SE_SECTION;
			LatexEditorView* edView=entry->document->getEditorView();
			if (!entry->document->getEditorView()){
				lineNr=entry->lineNumber;
				edView=load(entry->document->getFileName());
				if (!edView) return;
				//entry is now invalid
			} else lineNr=entry->getRealLineNumber();
			EditorView->setCurrentWidget(edView);
			edView->editor->setFocus();
			edView->editor->setCursorPosition(lineNr,1);
			break;
		}

		case StructureEntry::SE_INCLUDE:
		case StructureEntry::SE_BIBTEX:{
			QString defaultExt=entry->type==StructureEntry::SE_BIBTEX?".bib":".tex";
			QString curPath=ensureTrailingDirSeparator(entry->document->getFileInfo().absolutePath());
			if (load(getAbsoluteFilePath(entry->title,defaultExt)));
			else if (load(getAbsoluteFilePath(curPath+entry->title,defaultExt)));
			else QMessageBox::warning(this,"TexMakerX","Sorry, I couldn't find the file \""+entry->title+"\"",QMessageBox::Ok);
			break;
		}
	}
}

void Texmaker::editRemovePlaceHolders(){
	if (!currentEditor()) return;
	for (int i=currentEditor()->placeHolderCount();i>=0;i--)
		currentEditor()->removePlaceHolder(i);
	currentEditor()->viewport()->update();
}
//////////TAGS////////////////
void Texmaker::NormalCompletion() {
	if (!currentEditorView())	return;
	// complete text if no command is present
	QDocumentCursor c = currentEditorView()->editor->cursor();
	QString eow=getCommonEOW();
	int i=0;
	int col=c.columnNumber();
	QString word=c.line().text();
	while (c.columnNumber()>0 && !eow.contains(c.previousChar())) {
		c.movePosition(1,QDocumentCursor::PreviousCharacter);
		i++;
	}

	if(c.previousChar()==QChar('\\')) currentEditorView()->complete(true);
	else {
		// check further with reduced eow
		eow="}\\ ";
		int j=0;
		while (c.columnNumber()>0 && !eow.contains(c.previousChar())) {
			c.movePosition(1,QDocumentCursor::PreviousCharacter);
			j++;
		}
		if(c.previousChar()==QChar('\\')){
                        QString cmd=word.mid(col-i-j);
                        if(cmd.startsWith("ref{")||cmd.startsWith("pageref{")){
				currentEditorView()->complete(true,false,true);
				return;
			}
                        if(cmd.startsWith("begin{")||cmd.startsWith("end{")){
                                currentEditorView()->complete(true,false,false);
                                return;
                        }
		}
		if (i>1) {
			QString my_text=currentEditorView()->editor->text();
			int end=0;
			int k=0; // number of occurences of search word.
			word=word.mid(col-i,i);
			//TODO: Boundary needs to specified more exactly
			//TODO: type in text needs to be excluded, if not already present
			QString wrd;
			QStringList words;
			while ((i=my_text.indexOf(QRegExp("\\b"+word),end))>0) {
				end=my_text.indexOf(QRegExp("\\b"),i+1);
				if (end>i) {
					if (word==my_text.mid(i,end-i)) {
						k=k+1;
						if (k==2) words << my_text.mid(i,end-i);
					} else {
						if (!words.contains(my_text.mid(i,end-i)))
							words << my_text.mid(i,end-i);
					}
				} else {
					if (word==my_text.mid(i,end-i)) {
						k=k+1;
						if (k==2) words << my_text.mid(i,end-i);
					} else {
						if (!words.contains(my_text.mid(i,end-i)))
							words << my_text.mid(i,my_text.length()-i);
					}
				}
			}

			completer->setAdditionalWords(words, true);
			currentEditorView()->complete(true,true);
		}
	}
}
void Texmaker::InsertEnvironmentCompletion() {
	if (!currentEditorView())	return;
	QDocumentCursor c = currentEditorView()->editor->cursor();
	QString eow=getCommonEOW();
	while (c.columnNumber()>0 && !eow.contains(c.previousChar())) c.movePosition(1,QDocumentCursor::PreviousCharacter);
	c.insertText("\\begin{");//remaining part is up to the completion engine
	//c=currentEditorView()->editor->cursor();
	//c.movePosition(QString("\\begin{)").length(), QDocumentCursor::NextCharacter);
	//currentEditorView()->editor->setCursor(c);
	//if (currentEditorView()->editor->completionEngine())
	//    currentEditorView()->editor->completionEngine()->complete();
	currentEditorView()->complete(true);
}
// tries to complete normal text
// only starts up if already 2 characters have been typed in
void Texmaker::InsertTextCompletion() {
	if (!currentEditorView())    return;
	QDocumentCursor c = currentEditorView()->editor->cursor();
	QString eow=getCommonEOW();
	int i=0;
	int col=c.columnNumber();
	QString word=c.line().text();
	while (c.columnNumber()>0 && !eow.contains(c.previousChar())) {
		c.movePosition(1,QDocumentCursor::PreviousCharacter);
		i++;
	}
	if (i>1) {
		QString my_text=currentEditorView()->editor->text();
		int end=0;
		int k=0; // number of occurences of search word.
		word=word.mid(col-i,i);
		//TODO: Boundary needs to specified more exactly
		//TODO: type in text needs to be excluded, if not already present
		QString wrd;
		QStringList words;
		while ((i=my_text.indexOf(QRegExp("\\b"+word),end))>0) {
			end=my_text.indexOf(QRegExp("\\b"),i+1);
			if (end>i) {
				if (word==my_text.mid(i,end-i)) {
					k=k+1;
					if (k==2) words << my_text.mid(i,end-i);
				} else {
					if (!words.contains(my_text.mid(i,end-i)))
						words << my_text.mid(i,end-i);
				}
			} else {
				if (word==my_text.mid(i,end-i)) {
					k=k+1;
					if (k==2) words << my_text.mid(i,end-i);
				} else {
					if (!words.contains(my_text.mid(i,end-i)))
						words << my_text.mid(i,my_text.length()-i);
				}
			}
		}

		completer->setAdditionalWords(words, true);
		currentEditorView()->complete(true,true);
	}
}

void Texmaker::InsertTag(QString Entity, int dx, int dy) {
	if (!currentEditorView())	return;
	int curline,curindex;
	currentEditorView()->editor->getCursorPosition(curline,curindex);
	currentEditorView()->editor->cursor().insertText(Entity);
	if (dy==0) currentEditorView()->editor->setCursorPosition(curline,curindex+dx);
	else if (dx==0) currentEditorView()->editor->setCursorPosition(curline+dy,0);
	else currentEditorView()->editor->setCursorPosition(curline+dy,curindex+dx);
	currentEditorView()->editor->setFocus();
//	outputView->setMessage("");
	//logViewerTabBar->setCurrentIndex(0);
	//OutputTable->hide();
	//logpresent=false;
}

void Texmaker::InsertSymbolPressed(QTableWidgetItem *) {
	mb=QApplication::mouseButtons();
}

void Texmaker::InsertSymbol(QTableWidgetItem *item) {

	if (mb==Qt::RightButton) return; // avoid jumping to line if contextmenu is called

	QString code_symbol;
	if (item) {
		int cnt=item->data(Qt::UserRole).toInt();
		if(cnt<0) {
			item=item->data(Qt::UserRole+1).value<QTableWidgetItem*>();
			cnt=item->data(Qt::UserRole).toInt();
		}
		item->setData(Qt::UserRole,cnt+1);
		code_symbol=item->text();
		InsertTag(code_symbol,code_symbol.length(),0);
		SetMostUsedSymbols(item);
	}
}

void Texmaker::InsertXmlTag(QListWidgetItem *item)
{
	if (!currentEditorView())	return;
	if (item  && !item->font().bold()){
		QString code=item->data(Qt::UserRole).toString();
		QDocumentCursor c = currentEditorView()->editor->cursor();
		CodeSnippet(code).insertAt(currentEditorView()->editor,&c);
		currentEditorView()->editor->setFocus();
	}
}

void Texmaker::InsertFromAction() {
	if (!currentEditorView())	return;
	QAction *action = qobject_cast<QAction *>(sender());
	if (action)	{
		QDocumentCursor c = currentEditorView()->editor->cursor();
		CodeSnippet cs=CodeSnippet(action->data().toString());
		cs.setTMX(this);
		cs.insertAt(currentEditorView()->editor,&c);
		outputView->setMessage(CodeSnippet(action->whatsThis()).lines.join("\n"));
	}
}

void Texmaker::InsertWithSelectionFromString(const QString& text) {
	bool ok;
	QStringList tagList;
	if (!currentEditorView())	return;
	tagList= text.split("/");
	if (!currentEditorView()->editor->cursor().hasSelection()) {
		InsertTag(tagList.at(0)+tagList.at(1),tagList.at(2).toInt(&ok, 10),tagList.at(3).toInt(&ok, 10));
	} else {
		currentEditorView()->editor->cut();
		InsertTag(tagList.at(0),tagList.at(2).toInt(&ok, 10),tagList.at(3).toInt(&ok, 10));
		currentEditorView()->editor->paste();
		InsertTag(tagList.at(1),0,0);
	}
}

void Texmaker::InsertFromString(const QString& text) {
	bool ok;
	QStringList tagList;
	if (!currentEditorView()) return;
	tagList= text.split("/");
	InsertTag(tagList.at(0),tagList.at(1).toInt(&ok, 10),tagList.at(2).toInt(&ok, 10));
}

void Texmaker::InsertBib() {
	if (!currentEditorView())	return;
//currentEditorView()->editor->viewport()->setFocus();
	QString tag;
	tag=QString("\\bibliography{");
	tag +=currentEditor()->fileInfo().completeBaseName();
	tag +=QString("}\n");
	InsertTag(tag,0,1);
	outputView->setMessage(QString("The argument to \\bibliography refers to the bib file (without extension)\n")+
					"which should contain your database in BibTeX format.\n"+
					"Texmaker inserts automatically the base name of the TeX file");
}

void Texmaker::InsertStruct() {
	QString actData, tag;
	if (!currentEditorView())	return;
//currentEditorView()->editor->viewport()->setFocus();
	QAction *action = qobject_cast<QAction *>(sender());
	if (action) {
		actData=action->data().toString();
		StructDialog *stDlg = new StructDialog(this,actData);
		if (stDlg->exec()) {
			if (stDlg->ui.checkBox->isChecked()) {
				tag=actData+"{";
			} else {
				tag=actData+"*{";
			}
			tag +=stDlg->ui.TitlelineEdit->text();
			tag +=QString("}\n");
			InsertTag(tag,0,1);
			updateStructure();
		}
	}
}

void Texmaker::InsertStructFromString(const QString& text) {
	QString tag;
	if (!currentEditorView())	return;
//currentEditorView()->editor->viewport()->setFocus();
	StructDialog *stDlg = new StructDialog(this,text);
	if (stDlg->exec()) {
		if (stDlg->ui.checkBox->isChecked()) {
			tag=text+"{";
		} else {
			tag=text+"*{";
		}
		tag +=stDlg->ui.TitlelineEdit->text();
		tag +=QString("}\n");
		InsertTag(tag,0,1);
		updateStructure();
	}
}

void Texmaker::QuickTabular() {
	if (!currentEditorView())	return;
	QString al="";
	QString vs="";
	QString hs="";
	QString tag;
	TabDialog *quickDlg = new TabDialog(this,"Tabular");
	QTableWidgetItem *item=new QTableWidgetItem();
	if (quickDlg->exec()) {
		int y = quickDlg->ui.spinBoxRows->value();
		int x = quickDlg->ui.spinBoxColumns->value();
		if ((quickDlg->ui.comboSeparator->currentIndex())==0) vs=QString("|");
		if ((quickDlg->ui.comboSeparator->currentIndex())==1) vs=QString("||");
		if ((quickDlg->ui.comboSeparator->currentIndex())==2) vs=QString("");
		if ((quickDlg->ui.comboSeparator->currentIndex())==3) vs=QString("@{}");
		tag = QString("\\begin{tabular}{")+vs;
		if ((quickDlg->ui.comboAlignment->currentIndex())==0) al=QString("c")+vs;
		if ((quickDlg->ui.comboAlignment->currentIndex())==1) al=QString("l")+vs;
		if ((quickDlg->ui.comboAlignment->currentIndex())==2) al=QString("r")+vs;
		if ((quickDlg->ui.comboAlignment->currentIndex())==3) al=QString("p{}")+vs;
		if (quickDlg->ui.checkBox->isChecked()) hs=QString("\\hline ");
		for (int j=0; j<x; j++) {
			tag +=al;
		}
		tag +=QString("}\n");
		for (int i=0; i<y; i++) {
			tag +=hs;
			for (int j=0; j<x-1; j++) {
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

void Texmaker::QuickArray() {
	if (!currentEditorView())	return;
	QString al;
	ArrayDialog *arrayDlg = new ArrayDialog(this,"Array");
	QTableWidgetItem *item=new QTableWidgetItem();
	if (arrayDlg->exec()) {
		int y = arrayDlg->ui.spinBoxRows->value();
		int x = arrayDlg->ui.spinBoxColumns->value();
		QString env=arrayDlg->ui.comboEnvironment->currentText();
		QString tag = QString("\\begin{")+env+"}";
		if (env=="array") {
			tag+="{";
			if ((arrayDlg->ui.comboAlignment->currentIndex())==0) al=QString("c");
			if ((arrayDlg->ui.comboAlignment->currentIndex())==1) al=QString("l");
			if ((arrayDlg->ui.comboAlignment->currentIndex())==2) al=QString("r");
			for (int j=0; j<x; j++) {
				tag +=al;
			}
			tag+="}";
		}
		tag +=QString("\n");
		for (int i=0; i<y-1; i++) {
			for (int j=0; j<x-1; j++) {
				item =arrayDlg->ui.tableWidget->item(i,j);
				if (item) tag +=item->text()+ QString(" & ");
				else tag +=QString(" & ");
			}
			item =arrayDlg->ui.tableWidget->item(i,x-1);
			if (item) tag +=item->text()+ QString(" \\\\ \n");
			else tag +=QString(" \\\\ \n");
		}
		for (int j=0; j<x-1; j++) {
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

void Texmaker::QuickTabbing() {
	if (!currentEditorView()) return;
	TabbingDialog *tabDlg = new TabbingDialog(this,"Tabbing");
	if (tabDlg->exec()) {
		int	x = tabDlg->ui.spinBoxColumns->value();
		int	y = tabDlg->ui.spinBoxRows->value();
		QString s=tabDlg->ui.lineEdit->text();
		QString tag = QString("\\begin{tabbing}\n");
		for (int j=1; j<x; j++) {
			tag +="\\hspace{"+s+"}\\=";
		}
		tag+="\\kill\n";
		for (int i=0; i<y-1; i++) {
			for (int j=1; j<x; j++) {
				tag +=" \\> ";
			}
			tag+="\\\\ \n";
		}
		for (int j=1; j<x; j++) {
			tag +=" \\> ";
		}
		tag += QString("\n\\end{tabbing} ");
		InsertTag(tag,0,2);
	}
}

void Texmaker::QuickLetter() {
	if (!currentEditorView()) {
		fileNew();
		if (!currentEditorView()) return;
	}
	QString tag=QString("\\documentclass[");
	LetterDialog *ltDlg = new LetterDialog(this,"Letter");
	if (ltDlg->exec()) {
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
		if (ltDlg->ui.checkBox->isChecked()) {
			InsertTag(tag,9,5);
		} else {
			InsertTag(tag,9,2);
		}
	}
}

void Texmaker::QuickDocument() {
	QString opt="";
	int li=3;
	int f;
	if (!currentEditorView()) {
		fileNew();
		if (!currentEditorView()) return;
	}
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
	if (startDlg->exec()) {
		tag+=startDlg->ui.comboBoxSize->currentText()+QString(",");
		tag+=startDlg->ui.comboBoxPaper->currentText();
		QList<QListWidgetItem *> selectedItems=startDlg->ui.listWidgetOptions->selectedItems();
		for (int i = 0; i < selectedItems.size(); ++i) {
			if (selectedItems.at(i)) opt+=QString(",")+selectedItems.at(i)->text();
		}
		tag+=opt+QString("]{");
		tag+=startDlg->ui.comboBoxClass->currentText()+QString("}");
		tag+=QString("\n");
		if (startDlg->ui.comboBoxEncoding->currentText()!="NONE") tag+=QString("\\usepackage[")+startDlg->ui.comboBoxEncoding->currentText()+QString("]{inputenc}");
		tag+=QString("\n");
		if (startDlg->ui.comboBoxEncoding->currentText().startsWith("utf8x")) {
			tag+=QString("\\usepackage{ucs}\n");
			li=li+1;
		}
		if (startDlg->ui.checkBoxAMS->isChecked()) {
			tag+=QString("\\usepackage{amsmath}\n\\usepackage{amsfonts}\n\\usepackage{amssymb}\n");
			li=li+3;
		}
		if (startDlg->ui.checkBoxIDX->isChecked()) {
			tag+=QString("\\usepackage{makeidx}\n");
			li=li+1;
		}
		if (startDlg->ui.lineEditAuthor->text()!="") {
			tag+="\\author{"+startDlg->ui.lineEditAuthor->text()+"}\n";
			li=li+1;
		}
		if (startDlg->ui.lineEditTitle->text()!="") {
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


void Texmaker::InsertBibEntryFromAction(){
	if (!currentEditorView()) return;
	QAction* action=qobject_cast<QAction*>(sender());
	if (!action) return;
	QString insertText=BibTeXDialog::textToInsert(action->data().toString());
	if (!insertText.isEmpty())
		CodeSnippet(insertText).insert(currentEditor());
}

void Texmaker::CleanBib() {
	if (!currentEditorView()) return;
	currentEditorView()->cleanBib();
}

void Texmaker::InsertBibEntry(){
	InsertBibEntry("");
}

void Texmaker::InsertBibEntry(const QString& id){
	QStringList possibleBibFiles;
	int usedFile=0;
	if (currentEditor()){
		if (currentEditor()->fileName().isEmpty())
			possibleBibFiles.prepend(tr("<current file>"));
		else {
			usedFile=documents.mentionedBibTeXFiles.indexOf(currentEditor()->fileName());
			if (usedFile<0 && !documents.mentionedBibTeXFiles.empty()) usedFile=0;
		}
	}
	foreach (const QString &s, documents.mentionedBibTeXFiles)
		possibleBibFiles << QFileInfo(s).fileName();
	BibTeXDialog* bd=new BibTeXDialog(0,possibleBibFiles,usedFile,id);
	if (bd->exec()){
		usedFile=bd->resultFileId;
		if (usedFile<0 || usedFile>=possibleBibFiles.count()) fileNew();
		else if (currentEditor()->fileName().isEmpty() && usedFile==0); //stay in current editor
		else if (QFileInfo(currentEditor()->fileName())==QFileInfo(possibleBibFiles[usedFile])); //stay in current editor
		else {
			if (currentEditor()->fileName().isEmpty()) usedFile--;
			load(documents.mentionedBibTeXFiles[usedFile]);
			currentEditor()->setCursorPosition(currentEditor()->document()->lines()-1,0);
			bd->resultString="\n"+bd->resultString;
		}

		CodeSnippet(bd->resultString).insert(currentEditor());
	}
	delete bd;
}

void Texmaker::InsertUserTag() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	int id = action->data().toInt();
	if (id<0 || id>=10) return;
	QString userTag=UserMenuTag[id];
	if (userTag.left(8)=="%SCRIPT\n"){
		scriptengine eng(this);
		eng.setEditor(currentEditor());
		userTag=userTag.remove(0,8);
		eng.setScript(userTag);
		eng.run();
	} else {
		if (userTag.left(1)=="%") {
			userTag=userTag.remove(0,1);
			CodeSnippet s("\\begin{"+userTag+"}");
			s.insert(currentEditorView()->editor);
		} else CodeSnippet(userTag).insert(currentEditorView()->editor);
	}
}

void Texmaker::EditUserMenu() {
	UserMenuDialog *umDlg = new UserMenuDialog(this,tr("Edit User &Tags"));
	umDlg->Name=UserMenuName;
	umDlg->Tag=UserMenuTag;
	umDlg->Abbrev=UserMenuAbbrev;
	umDlg->init();
	if (umDlg->exec())
		UserMenuName=umDlg->Name;
		UserMenuTag=umDlg->Tag;
		UserMenuAbbrev=umDlg->Abbrev;
		for (int i = 0; i <= 9; i++) {
		QAction * act=getManagedAction("main/user/tags/tag"+QString::number(i));
		if (act) act->setText(QString::number(i+1)+": "+UserMenuName[i]);
	}
	completer->setAbbreviations(UserMenuAbbrev,UserMenuTag);
}

void Texmaker::SectionCommand() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	if (!currentEditorView()) return;
	InsertStructFromString("\\"+action->text());
	combo1->defaultAction()->setText(action->text());
}

void Texmaker::OtherCommand() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	if (!currentEditorView()) return;

	QString text=action->text();
	combo2->defaultAction()->setText(text);

	if (text=="label") {
		InsertFromString("\\label{} /7/0");
		return;
	}
	if (text=="ref") {
		InsertRef();
		return;
	}
	if (text=="pageref") {
		InsertPageRef();
		return;
	}
	if (text=="index") {
		InsertFromString("\\index{}/7/0");
		return;
	}
	if (text=="cite") {
		InsertFromString("\\cite{}/6/0");
		return;
	}
	if (text=="footnote") {
		InsertFromString("\\footnote{}/10/0");
		return;
	}
}

void Texmaker::InsertRef() {
	updateStructure();

        LatexEditorView* edView=currentEditorView();
        QStringList labels;
        if(edView && edView->document){
                QList<LatexDocument*> docs;
                if (singlemode) docs << edView->document;
                else docs << documents.documents;
                foreach(const LatexDocument* doc,docs)
                        labels << doc->labelItem;
        } else return;
	UniversalInputDialog dialog;
	dialog.addVariable(&labels, tr("Labels:"));
	if (dialog.exec() && !labels.isEmpty()) {
		QString tag="\\ref{"+labels.first()+"}";
		InsertTag(tag,tag.length(),0);
	} else InsertTag("\\ref{}",5,0);
	outputView->setMessage("\\ref{key}");
}

void Texmaker::InsertPageRef() {
	updateStructure();
        LatexEditorView* edView=currentEditorView();
        QStringList labels;
        if(edView && edView->document){
                QList<LatexDocument*> docs;
                if (singlemode) docs << edView->document;
                else docs << documents.documents;
                foreach(const LatexDocument* doc,docs)
                        labels << doc->labelItem;
        } else return;
        UniversalInputDialog dialog;
	dialog.addVariable(&labels, tr("Labels:"));
	if (dialog.exec() && !labels.isEmpty()) {
		QString tag="\\pageref{"+labels.first()+"}";
		InsertTag(tag,tag.length(),0);
	} else InsertTag("\\pageref{}",9,0);
	outputView->setMessage("\\pageref{key}");
}

void Texmaker::SizeCommand() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;

	if (!currentEditorView()) return;

	QString text=action->text();
	combo3->defaultAction()->setText(text);

	if (text=="tiny") {
		InsertWithSelectionFromString("\\begin{tiny}/\\end{tiny}/12/0");
		return;
	}
	if (text=="scriptsize") {
		InsertWithSelectionFromString("\\begin{scriptsize}/\\end{scriptsize}/18/0");
		return;
	}
	if (text=="footnotesize") {
		InsertWithSelectionFromString("\\begin{footnotesize}/\\end{footnotesize}/20/0");
		return;
	}
	if (text=="small") {
		InsertWithSelectionFromString("\\begin{small}/\\end{small}/13/0");
		return;
	}
	if (text=="normalsize") {
		InsertWithSelectionFromString("\\begin{normalsize}/\\end{normalsize}/18/0");
		return;
	}
	if (text=="large") {
		InsertWithSelectionFromString("\\begin{large}/\\end{large}/13/0");
		return;
	}
	if (text=="Large") {
		InsertWithSelectionFromString("\\begin{Large}/\\end{Large}/13/0");
		return;
	}
	if (text=="LARGE") {
		InsertWithSelectionFromString("\\begin{LARGE}/\\end{LARGE}/13/0");
		return;
	}
	if (text=="huge") {
		InsertWithSelectionFromString("\\begin{huge}/\\end{huge}/12/0");
		return;
	}
	if (text=="Huge") {
		InsertWithSelectionFromString("\\begin{Huge}/\\end{Huge}/12/0");
		return;
	}
}

void Texmaker::LeftDelimiter() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	if (!currentEditorView()) return;
	QString text=action->text();
	combo4->defaultAction()->setText(text);

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

void Texmaker::RightDelimiter() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	if (!currentEditorView()) return;
	QString text=action->text();
	combo5->defaultAction()->setText(text);

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

void Texmaker::SpellingLanguageChanged() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	if (!currentEditorView()) return;
	QString text=action->text();
	comboSpell->defaultAction()->setText(text);

	QString baseName=QFileInfo(configManager.spell_dic).absolutePath();
	configManager.spell_dic=baseName+"/"+text;
	mainSpeller->loadDictionary(configManager.spell_dic,configManager.configFileNameBase);
}

///////////////TOOLS////////////////////
void Texmaker::runCommand(BuildManager::LatexCommand cmd,bool waitendprocess,bool showStdout){
	bool compileLatex=cmd==BuildManager::CMD_LATEX||cmd==BuildManager::CMD_PDFLATEX;
	if(compileLatex) ClearMarkers();
	runCommand(buildManager.getLatexCommand(cmd),waitendprocess,showStdout,compileLatex);
}
void Texmaker::runCommand(QString comd,bool waitendprocess,bool showStdout,bool compileLatex,QString *buffer) {
	QString finame=getCompileFileName();
	QString commandline=comd;
	QByteArray result;
	if ((singlemode && !currentEditorView()) || finame=="") {
		QMessageBox::warning(this,tr("Error"),tr("Can't detect the file name"));
		return;
	}

	if (commandline.trimmed().isEmpty()) {
		ERRPROCESS=true;
		outputView->insertMessageLine("Error : no command given \n");
		return;
	}

	ProcessX* procX = buildManager.newProcess(comd,finame,getCurrentFileName(),currentEditorView()->editor->cursor().lineNumber()+1);

	procX->setBuffer(buffer);

	connect(procX, SIGNAL(readyReadStandardError()),this, SLOT(readFromStderr()));
	if (showStdout) connect(procX, SIGNAL(readyReadStandardOutput()),this, SLOT(readFromStdoutput()));
	connect(procX, SIGNAL(finished(int)),this, SLOT(SlotEndProcess(int)));

	outputView->resetMessages();

	//OutputTextEdit->insertLine(commandline+"\n");
	FINPROCESS = false;
	procX->startCommand();
	if (!procX->waitForStarted(1000)) {
		ERRPROCESS=true;
		outputView->insertMessageLine("Error: "+tr("could not start the command:")+" "+commandline+"\n");
		return;
	} else outputView->insertMessageLine(tr("Process started")+"\n");

	if (compileLatex && configManager.showLogAfterCompiling)
		connect(procX,SIGNAL(finished(int)),this,SLOT(ViewAndHighlightError()));

	if (waitendprocess) {
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
		QTime time;
		time.start();
		KILLPROCESS=false;
		PROCESSRUNNING=true;
		while (!FINPROCESS) {
			qApp->instance()->processEvents(QEventLoop::ExcludeUserInputEvents);
			if (time.elapsed()>2000)
				qApp->instance()->processEvents(QEventLoop::AllEvents);
			if (KILLPROCESS) {
				procX->kill();
				FINPROCESS=ERRPROCESS=true;
				break;
			}
		}
		PROCESSRUNNING=false;
		QApplication::restoreOverrideCursor();
	}
}

void Texmaker::RunPreCompileCommand() {
	outputView->resetMessagesAndLog();//log to old (whenever latex is called)
	if (!buildManager.getLatexCommand(BuildManager::CMD_USER_PRECOMPILE).isEmpty()) {
		stat2->setText(QString(" %1 ").arg(tr("Pre-LaTeX")));
		runCommand(BuildManager::CMD_USER_PRECOMPILE,true,false);
	}
	if (documents.bibTeXFilesModified && configManager.runLaTeXBibTeXLaTeX) {
		ERRPROCESS=false;
		stat2->setText(QString(" %1 ").arg(tr("LaTeX")));
		runCommand(BuildManager::CMD_LATEX,true,false);
		if (ERRPROCESS && !LogExists()) {
			QMessageBox::warning(this,tr("Error"),tr("Could not start LaTeX."));
			return;
		}
		if (NoLatexErrors()) {
			ERRPROCESS=false;
			stat2->setText(QString(" %1 ").arg(tr("BibTeX")));
			runCommand(BuildManager::CMD_BIBTEX,true,false);
			if (!ERRPROCESS) {
				stat2->setText(QString(" %1 ").arg(tr("LaTeX")));
				runCommand(BuildManager::CMD_LATEX,true,false);
			}
		}
		documents.bibTeXFilesModified = false;
	}
}

void Texmaker::readFromStderr() {
	ProcessX* procX = qobject_cast<ProcessX*> (sender());
	if (!procX) return;
	QByteArray result=procX->readAllStandardError();
	QString t=QString(result).simplified();
	if (!t.isEmpty()) outputView->insertMessageLine(t+"\n");
}

void Texmaker::readFromStdoutput() {
	ProcessX* procX = qobject_cast<ProcessX*> (sender());
	if (!procX) return;
	QByteArray result=procX->readAllStandardOutput();
	QString t=QString(result).trimmed();
	QString *buffer=procX->getBuffer();
	if(buffer) buffer->append(t);
	if (!t.isEmpty()) outputView->insertMessageLine(t+"\n");
}

void Texmaker::SlotEndProcess(int err) {
	ProcessX* procX = qobject_cast<ProcessX*> (sender());
	FINPROCESS=true;
	QString result=((err) ? "Process exited with error(s)" : "Process exited normally");
	if (err) ERRPROCESS=true;
	outputView->insertMessageLine(result);
	stat2->setText(QString(" %1 ").arg(tr("Ready")));
	if(!procX) return;
	QString *buffer=procX->getBuffer();
	if(buffer){
		QByteArray result=procX->readAllStandardOutput();
		QString t=QString(result).trimmed();
		buffer->append(t);
	}
}

void Texmaker::QuickBuild() {
	fileSaveAll();
	RunPreCompileCommand();
	stat2->setText(QString(" %1 ").arg(tr("Quick Build")));
	ERRPROCESS=false;
	switch (buildManager.quickmode) {
	case 1: {
		stat2->setText(QString(" %1 ").arg("Latex"));
		runCommand(BuildManager::CMD_LATEX,true,false);
		if (ERRPROCESS && !LogExists()) {
			QMessageBox::warning(this,tr("Error"),tr("Could not start LaTeX."));
			return;
		}
		if (NoLatexErrors()) {
			stat2->setText(QString(" %1 ").arg("Dvips"));
			if (!ERRPROCESS) runCommand(BuildManager::CMD_DVIPS,true,false);
			else return;
			if (!ERRPROCESS) runCommand(BuildManager::CMD_VIEWPS, false, false);
			else return;
		}
	}
	break;
	case 2: {
		stat2->setText(QString(" %1 ").arg("Latex"));
		runCommand(BuildManager::CMD_LATEX,true,false);
		if (ERRPROCESS && !LogExists()) {
			QMessageBox::warning(this,tr("Error"),tr("Could not start LaTeX."));
			return;
		}
		if (NoLatexErrors()) {
			if (!ERRPROCESS) runCommand(BuildManager::CMD_VIEWDVI, false, false);
			else return;
		}
	}
	break;
	case 3: {
		stat2->setText(QString(" %1 ").arg("Pdf Latex"));
		runCommand(BuildManager::CMD_PDFLATEX,true,false);
		if (ERRPROCESS && !LogExists()) {
			QMessageBox::warning(this,tr("Error"),tr("Could not start PdfLaTeX."));
			return;
		}
		if (NoLatexErrors()) {
			if (!ERRPROCESS) runCommand(BuildManager::CMD_VIEWPDF, false, false);
			else return;
		}
	}
	break;
	case 4: {
		stat2->setText(QString(" %1 ").arg("Latex"));
		runCommand(BuildManager::CMD_LATEX,true,false);
		if (ERRPROCESS && !LogExists()) {
			QMessageBox::warning(this,tr("Error"),tr("Could not start LaTeX."));
			return;
		}
		if (NoLatexErrors()) {
			stat2->setText(QString(" %1 ").arg("Dvi to Pdf"));
			if (!ERRPROCESS) runCommand(BuildManager::CMD_DVIPDF,true,false);
			else return;
			if (!ERRPROCESS) runCommand(BuildManager::CMD_VIEWPDF, false, false);
			else return;
		}
	}
	break;
	case 5: {
		stat2->setText(QString(" %1 ").arg("Latex"));
		runCommand(BuildManager::CMD_LATEX,true,false);
		if (ERRPROCESS && !LogExists()) {
			QMessageBox::warning(this,tr("Error"),tr("Could not start LaTeX."));
			return;
		}
		if (NoLatexErrors()) {
			stat2->setText(QString(" %1 ").arg("Dvips"));
			if (!ERRPROCESS) runCommand(BuildManager::CMD_DVIPS,true,false);
			else return;
			stat2->setText(QString(" %1 ").arg("Ps to Pdf"));
			if (!ERRPROCESS) runCommand(BuildManager::CMD_PS2PDF,true,false);
			else return;
			if (!ERRPROCESS) runCommand(BuildManager::CMD_VIEWPDF, false, false);
		}
	}
	break;
	case 6: {
		QStringList commandList=buildManager.getLatexCommand(BuildManager::CMD_USER_QUICK).split("|");
		for (int i = 0; i < commandList.size(); ++i) {
			if ((!ERRPROCESS)&&(!commandList.at(i).isEmpty())) runCommand(commandList.at(i),true,true);
			else break;
		}
		ViewAndHighlightError();
	}
	break;
	}
//	if (NoLatexErrors()) ViewLog();
//ViewLog();
//DisplayLatexError();
}

void Texmaker::commandFromAction(){
	QAction* act = qobject_cast<QAction*>(sender());
	if (!act) return;
	fileSaveAll();
	BuildManager::LatexCommand cmd=(BuildManager::LatexCommand) act->data().toInt();
	bool compileLatex=(cmd==BuildManager::CMD_LATEX || cmd==BuildManager::CMD_PDFLATEX);
	if (compileLatex)
		RunPreCompileCommand();
	stat2->setText(QString(" %1 ").arg(act->text()));
	runCommand(cmd, false, false);
}

void Texmaker::CleanAll() {
	QString finame=getCompileFileName();
	if ((singlemode && !currentEditorView()) || finame=="") {
		QMessageBox::warning(this,tr("Error"),tr("Can't detect the file name"));
		return;
	}
	QString extensionStr=".log,.aux,.dvi,.lof,.lot,.bit,.idx,.glo,.bbl,.ilg,.toc,.ind";
	int query =QMessageBox::warning(this, "TexMakerX", tr("Delete the output files generated by LaTeX?")+QString("\n(%1)").arg(extensionStr),tr("Delete Files"), tr("Cancel"));
	if (query==0) {
		fileSave();
		QFileInfo fi(finame);
		QString basename=fi.absolutePath()+"/"+fi.completeBaseName();
		QStringList extension=extensionStr.split(",");
		stat2->setText(QString(" %1 ").arg(tr("Clean")));
		foreach(QString ext, extension)
		QFile::remove(basename+ext);
		stat2->setText(QString(" %1 ").arg(tr("Ready")));
	}
}

void Texmaker::UserTool() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	if (action->data().toInt()<0 || action->data().toInt()>=5) return;
	QString cmd=UserToolCommand[action->data().toInt()];
	if (cmd.isEmpty()) return;
	fileSaveAll();
	QStringList commandList=cmd.split("|");
	ERRPROCESS=false;
	for (int i = 0; i < commandList.size(); ++i)
		if ((!ERRPROCESS)&&(!commandList.at(i).isEmpty())) runCommand(commandList.at(i),true,true);
		else return;
}


void Texmaker::EditUserTool() {
	UserToolDialog *utDlg = new UserToolDialog(this,tr("Edit User &Commands"));
	for (int i = 0; i <= 4; i++) {
		utDlg->Name[i]=UserToolName[i];
		utDlg->Tool[i]=UserToolCommand[i];
		utDlg->init();
	}
	if (utDlg->exec())
		for (int i = 0; i <= 4; i++) {
			UserToolName[i]=utDlg->Name[i];
			UserToolCommand[i]=utDlg->Tool[i];
			QAction * act=getManagedAction("main/user/commands/cmd"+QString::number(i));
			if (act) act->setText(QString::number(i+1)+": "+UserToolName[i]);
		}
}

void Texmaker::WebPublish() {
	if (!currentEditorView()) {
		QMessageBox::information(this,"TexMakerX",tr("No document open"),0);
		return;
	}
	if (!currentEditorView()->editor->getFileCodec()) return;
	fileSave();
	QString finame=getCompileFileName();

	WebPublishDialog *ttwpDlg = new WebPublishDialog(this,configManager.webPublishDialogConfig, &buildManager,
		currentEditorView()->editor->getFileCodec());
	ttwpDlg->ui.inputfileEdit->setText(finame);
	ttwpDlg->exec();
	delete ttwpDlg;
}


void Texmaker::AnalyseText() {
	if (!currentEditorView()) {
		QMessageBox::information(this,"TexMakerX",tr("No document open"),0);
		return;
	}
	if (!textAnalysisDlg) {
		textAnalysisDlg = new TextAnalysisDialog(this,tr("Text Analysis"));
		connect(textAnalysisDlg,SIGNAL(destroyed()),this,SLOT(AnalyseTextFormDestroyed()));
	}
	if (!textAnalysisDlg) return;
	textAnalysisDlg->setEditor(currentEditorView()->editor);//->document(), currentEditorView()->editor->cursor());
	textAnalysisDlg->init();
	textAnalysisDlg->interpretStructureTree(currentEditorView()->document->baseStructure);

	textAnalysisDlg->show();
	textAnalysisDlg->raise(); //not really necessary, since the dlg is always on top
	textAnalysisDlg->activateWindow();
}
void Texmaker::AnalyseTextFormDestroyed() {
	textAnalysisDlg=0;
}
void Texmaker::GenerateRandomText(){
	if (!currentEditorView()){
		QMessageBox::warning(this ,"TexMakerX", tr("The random text generator constructs new texts from existing words, so you have to open some text files"), QMessageBox::Ok);
		return;
	}

	QStringList allLines;
	for (int i=0;i<EditorView->count();i++)
		allLines<<(qobject_cast<LatexEditorView*>(EditorView->widget(i)))->editor->document()->textLines();
	RandomTextGenerator generator(this, allLines);
	generator.exec();
}

//////////////// MESSAGES - LOG FILE///////////////////////
bool Texmaker::LogExists() {
	QString finame=getCompileFileName();
	if ((singlemode && !currentEditorView()) || finame=="")
		return false;
	QString logname=getAbsoluteFilePath(QFileInfo(finame).baseName(),".log");
	QFileInfo fic(logname);
	if (fic.exists() && fic.isReadable()) return true;
	else return false;
}


//shows the log (even if it is empty)
void Texmaker::RealViewLog(bool noTabChange) {
	ViewLog(noTabChange);
	outputView->showLogOrErrorList(noTabChange);
}

//shows the log if there are errors
void Texmaker::ViewLog(bool noTabChange) {
	outputView->resetLog(noTabChange);
	QString finame=getCompileFileName();
	if ((singlemode && !currentEditorView()) || finame=="") {
		QMessageBox::warning(this,tr("Error"),tr("File must be saved and compiling before you can view the log"));
		ERRPROCESS=true;
		return;
	}
	QString logname=getAbsoluteFilePath(QFileInfo(finame).baseName(),".log");
	QString line;
	QFileInfo fic(logname);
	if (fic.exists() && fic.isReadable()) {
		//OutputLogTextEdit->insertLine("LOG FILE :");
		QString overrideFileName=""; //workaround, see parseLogDocument for reason
		if (configManager.ignoreLogFileNames==2 ||
			(configManager.ignoreLogFileNames==1 && singlemode)) overrideFileName=getCurrentFileName();
		outputView->loadLogFile(logname,getCompileFileName(),overrideFileName);
		//display errors in editor
		DisplayLatexError();
		if (outputView->getLogModel()->found(LT_ERROR))
			if (!NextError()) //jump to an error
				PreviousError();


	} else {
		QMessageBox::warning(this,tr("Error"),tr("Log File not found !"));
	}
}

//this is show after latex compilation to show the errors (it only opens the log them if there are any)
void Texmaker::ViewAndHighlightError(){
	ViewLog();
	//it seems viewlog does this already, it calls nexterror if there are errors and
	//nexterror shows the log;
	//but should nextError really show the log?
	/*if (!NoLatexErrors()) {
		//NextError();
		outputView->showErrorListOrLog();
	}*/
}

////////////////////////// ERRORS /////////////////////////////
void Texmaker::DisplayLatexError() {
	int errorMarkID = QLineMarksInfoCenter::instance()->markTypeId("error");
	int warningMarkID = QLineMarksInfoCenter::instance()->markTypeId("warning");
	int badboxMarkID = QLineMarksInfoCenter::instance()->markTypeId("badbox");
	for (int i=0; i<EditorView->count(); i++) {
		LatexEditorView *ed=qobject_cast<LatexEditorView *>(EditorView->widget(i));
		if (ed) {
			ed->editor->document()->removeMarks(errorMarkID);
			ed->editor->document()->removeMarks(warningMarkID);
			ed->editor->document()->removeMarks(badboxMarkID);
			ed->logEntryToLine.clear();
			ed->lineToLogEntries.clear();
		}
	}
	//backward, so the more important marks (with lower indices) will be inserted last and
	//returned first be QMultiHash.value
	LatexLogModel* logModel = outputView->getLogModel();
	QHash<QString, LatexEditorView*> tempFilenames; //temporary maps the filenames (as they appear in this log!) to the editor
	for (int i = logModel->count()-1; i >= 0; i--)
		if (logModel->at(i).oldline!=-1){
			LatexEditorView* edView;
			if (tempFilenames.contains(logModel->at(i).file)) edView=tempFilenames.value(logModel->at(i).file);
			else{
				edView=getEditorViewFromFileName(logModel->at(i).file);
				tempFilenames[logModel->at(i).file]=edView;
			}
			if (edView) {
				QDocumentLine l=edView->editor->document()->line(logModel->at(i).oldline-1);
				if (logModel->at(i).type==LT_ERROR) l.addMark(errorMarkID);
				else if (logModel->at(i).type==LT_WARNING) l.addMark(warningMarkID);
				else if (logModel->at(i).type==LT_BADBOX) l.addMark(badboxMarkID);
				edView->lineToLogEntries.insert(l.handle(),i);
				edView->logEntryToLine[i]=l.handle();
			}
		}
}

bool Texmaker::NoLatexErrors() {
	return !outputView->getLogModel()->found(LT_ERROR);
}

void Texmaker::NextMark() {
	if (!currentEditorView()) return;
	gotoMark(false,-1);
}
void Texmaker::PreviousMark() {
	if (!currentEditorView()) return;
	gotoMark(true,-1);
}


bool Texmaker::gotoNearLogEntry(LogType lt, bool backward, QString notFoundMessage) {
	if (!outputView->logPresent()) {
		ViewLog();
	}
	if (outputView->logPresent()) {
		if (outputView->getLogModel()->found(lt)){
			outputView->showErrorListOrLog(); //always show log if a mark of this type exists (even if is in another file)
			return gotoMark(backward, outputView->getLogModel()->markID(lt));
		} else {
			QMessageBox::information(this,"TexMakerX",notFoundMessage);
			//OutputTextEdit->setCursorPosition(0 , 0);
		}
	}
	return false;
}
bool Texmaker::NextError() {
	return gotoNearLogEntry(LT_ERROR,false,tr("No LaTeX errors detected !"));
}

bool Texmaker::PreviousError() {
	return gotoNearLogEntry(LT_ERROR,true,tr("No LaTeX errors detected !"));
}

void Texmaker::NextWarning() {
	gotoNearLogEntry(LT_WARNING,false,tr("No LaTeX warnings detected !"));
}
void Texmaker::PreviousWarning() {
	gotoNearLogEntry(LT_WARNING,true,tr("No LaTeX warnings detected !"));
}

void Texmaker::NextBadBox() {
	gotoNearLogEntry(LT_BADBOX,false,tr("No bad boxes detected !"));
}
void Texmaker::PreviousBadBox() {
	gotoNearLogEntry(LT_BADBOX,true,tr("No bad boxes detected !"));
}

void Texmaker::ClearMarkers(){
	int errorMarkID = QLineMarksInfoCenter::instance()->markTypeId("error");
	int warningMarkID = QLineMarksInfoCenter::instance()->markTypeId("warning");
	int badboxMarkID = QLineMarksInfoCenter::instance()->markTypeId("badbox");
	for (int i=0; i<EditorView->count(); i++) {
		LatexEditorView *ed=qobject_cast<LatexEditorView *>(EditorView->widget(i));
		if (ed) {
			ed->editor->document()->removeMarks(errorMarkID);
			ed->editor->document()->removeMarks(warningMarkID);
			ed->editor->document()->removeMarks(badboxMarkID);
			//ed->logEntryToLine.clear();
			//ed->lineToLogEntries.clear();
		}
	}
}
//////////////// HELP /////////////////
void Texmaker::LatexHelp() {
	QString latexHelp=findResourceFile("latexhelp.html");
	if (latexHelp!="") QDesktopServices::openUrl("file:///"+latexHelp);
	else QMessageBox::warning(this,tr("Error"),tr("File not found"));
}

void Texmaker::UserManualHelp() {
	QString locale = QString(QLocale::system().name()).left(2);
	if (locale.length() < 2 || locale!="fr") locale = "en";
	QString latexHelp=findResourceFile("usermanual_"+locale+".html");
	if (latexHelp!="") QDesktopServices::openUrl("file:///"+latexHelp);
	else QMessageBox::warning(this,tr("Error"),tr("File not found"));
}

void Texmaker::HelpAbout() {
	AboutDialog *abDlg = new AboutDialog(this);
	abDlg->exec();
}
////////////// OPTIONS //////////////////////////////////////
void Texmaker::GeneralOptions() {
	if (configManager.execConfigDialog()) {
		mainSpeller->loadDictionary(configManager.spell_dic,configManager.configFileNameBase);
		// refresh quick language selection combobox
		QFontMetrics fontMetrics(runToolBar->font());
		QStringList list;
		QDir fic=QFileInfo(configManager.spell_dic).absoluteDir();
		if (fic.exists() && fic.isReadable())
			list << fic.entryList(QStringList("*.dic"),QDir::Files,QDir::Name);
		createComboToolButton(spellToolBar,list,runToolBar->height()-2,fontMetrics,this,SLOT(SpellingLanguageChanged()),QFileInfo(configManager.spell_dic).fileName(),comboSpell);

		if (configManager.autodetectLoadedFile) QDocument::setDefaultCodec(0);
		else QDocument::setDefaultCodec(configManager.newfile_encoding);

#if QT_VERSION >= 0x040500
		if (thesaurusFileName!=configManager.thesaurus_database){
			if (!QFile::exists(configManager.thesaurus_database))
				thesaurusFileName="<dontLoad>";
			else {
				databasefile=new QFile(configManager.thesaurus_database);
				if (!databasefile->open(QIODevice::ReadOnly)) {
					//QMessageBox::warning(this,tr("Error"), tr("You do not have read permission to this file."));
					thesaurusFileName="<dontLoad>";
					delete databasefile;
					databasefile=0;
				} else {
					thesaurusFileName="";
					thesaurusFuture=QtConcurrent::run(&ThesaurusDialog::loadDatabase,databasefile);
				}
			}
		}
#endif

		if (currentEditorView()) {
			for (int i=0; i<EditorView->count();i++) {
				LatexEditorView* edView=qobject_cast<LatexEditorView*>(EditorView->widget(i));
				if (edView) edView->updateSettings();
			}
			UpdateCaption();
		}
		//custom toolbar
		QHash<QString, QVariant>::const_iterator i = configManager.replacedIconsOnMenus.constBegin();
		while (i != configManager.replacedIconsOnMenus.constEnd()) {
			QString id=i.key();
			QVariant zw=i.value();
			QAction * act= getManagedAction(id);
			if (act) {
				if(zw.canConvert<QString>()) act->setIcon(QIcon(zw.toString()));
			}
			i++;
		}
		customToolBar->clear();
		int l=configManager.listCustomActions.size();
		if(l>0){
			for (int i=0; i<l; i++){
				QAction *act=getManagedAction(configManager.listCustomActions.at(i));
				if(act->icon().isNull()){
					act->setIcon(QIcon(":/images/appicon.png"));
				}
				customToolBar->addAction(act);
			}
		}
		//completion
		updateCompleter();
	}
}
void Texmaker::executeCommandLine(const QStringList& args, bool realCmdLine) {
	// parse command line
	QString fileToLoad;
	bool activateMasterMode = false;
	int line=-1;
	for (int i = 0; i < args.size(); ++i) {
		if (args[i]=="") continue;
		if (args[i][0] != '-')  fileToLoad=args[i];
		//-form is for backward compatibility
		if (args[i] == "--master") activateMasterMode=true;
		if (args[i] == "--line" && i+1<args.size())  line=args[++i].toInt()-1;
	}

	// execute command line
	QFileInfo ftl(fileToLoad);
	if (fileToLoad != "") {
		if (ftl.exists())
			load(fileToLoad, activateMasterMode);
		else if (ftl.absoluteDir().exists()) {
			fileNew(ftl.absoluteFilePath());
			if (activateMasterMode) {
				if (singlemode) ToggleMode();
				else {
					ToggleMode();
					ToggleMode();
				}
			}
			return ;
		}
	}

	if (line!=-1){
		QApplication::processEvents();
		gotoLine(line);
		QTimer::singleShot(1000,currentEditor(),SLOT(ensureCursorVisible()));
	}

	#ifndef QT_NO_DEBUG
	//execute test after command line is known
	if (realCmdLine){ //only at start
		QFileInfo myself(QCoreApplication::applicationFilePath());
		if ((myself.lastModified()!=configManager.debugLastFileModification
			|| args.contains("--execute-tests") || args.contains("--execute-all-tests"))&& !args.contains("--disable-tests")){
			fileNew();
			if (!currentEditorView() || !currentEditorView()->editor)
				QMessageBox::critical(0,"wtf?","test failed",QMessageBox::Ok);
			//execute all tests once a week or if command paramter is set
			bool allTests=args.contains("--execute-all-tests");
			if (configManager.debugLastFullTestRun.daysTo(myself.lastModified())>6) allTests=true;
			if (allTests) configManager.debugLastFullTestRun=myself.lastModified();
			currentEditorView()->editor->document()->setText(TestManager::execute(allTests?TestManager::TL_ALL:TestManager::TL_FAST, currentEditorView(),currentEditorView()->codeeditor,currentEditorView()->editor));
			configManager.debugLastFileModification=QFileInfo(QCoreApplication::applicationFilePath()).lastModified();
		}
	}
	#endif
}
void Texmaker::onOtherInstanceMessage(const QString &msg) { // Added slot for messages to the single instance
	show();
	activateWindow();
	executeCommandLine(msg.split("#!#"),false);
}
void Texmaker::ToggleMode() {
//QAction *action = qobject_cast<QAction *>(sender());
	if (!singlemode) {
		documents.setMasterDocument(0);
		ToggleAct->setText(tr("Define Current Document as 'Master Document'"));
		outputView->resetMessagesAndLog();
		singlemode=true;
		stat1->setText(QString(" %1 ").arg(tr("Normal Mode")));
		return;
	}
	if (singlemode && currentEditorView()) {
		if (getCurrentFileName()=="")
			fileSave();
		MasterName=getCurrentFileName();
		if (MasterName=="") {
			QMessageBox::warning(this,tr("Error"),tr("You must save the file before switching to master mode."));
			return;
		}
		documents.setMasterDocument(currentEditorView()->document);
		QString shortName = MasterName;
		int pos;
		while ((pos = (int)shortName.indexOf('/')) != -1) shortName.remove(0,pos+1);
		ToggleAct->setText(tr("Normal Mode (current master document :")+shortName+")");
		singlemode=false;
		stat1->setText(QString(" %1 ").arg(tr("Master Document")+ ": "+shortName));
		MarkCurrentFileAsRecent();
		return;
	}
}
////////////////// VIEW ////////////////

void Texmaker::gotoNextDocument() {
	if (EditorView->count() < 2) return;
	int cPage = EditorView->currentIndex() + 1;
	if (cPage >= EditorView->count()) EditorView->setCurrentIndex(0);
	else EditorView->setCurrentIndex(cPage);
}

void Texmaker::gotoPrevDocument() {
	if (EditorView->count() < 2) return;
	int cPage = EditorView->currentIndex() - 1;
	if (cPage < 0) EditorView->setCurrentIndex(EditorView->count() - 1);
	else EditorView->setCurrentIndex(cPage);
}
void Texmaker::viewToggleOutputView(){
	bool mVis=outputView->isVisible();
	outputView->setVisible(!mVis);
	outputViewAction->setChecked(!mVis);
}

void Texmaker::viewCloseSomething(){
	if (PROCESSRUNNING) {
		KILLPROCESS=true;
		return;
	}
	if(windowState()==Qt::WindowFullScreen){
	    stateFullScreen=saveState(1);
	    setWindowState(Qt::WindowNoState);
			restoreState(windowstate,0);
	    fullscreenModeAction->setChecked(false);
	    return;
	}
	if (textAnalysisDlg) {
		textAnalysisDlg->close();
		return;
	}
	if (currentEditorView() && currentEditorView()->closeSomething())
		return;
	if (outputView->isVisible()) {
		viewToggleOutputView();
		return;
	}

}

void Texmaker::setFullScreenMode() {
    if(!fullscreenModeAction->isChecked()) {
		stateFullScreen=saveState(1);
		setWindowState(Qt::WindowNoState);
		restoreState(windowstate,0);
    }
    else {
		windowstate=saveState(0);
		setWindowState(Qt::WindowFullScreen);
		restoreState(stateFullScreen,1);
    }
}

void Texmaker::viewCollapseEverything() {
	if (!currentEditorView()) return;
	currentEditorView()->foldEverything(false);
}
void Texmaker::viewCollapseLevel() {
	if (!currentEditorView()) return;
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	currentEditorView()->foldLevel(false,action->data().toInt());
}
void Texmaker::viewCollapseBlock() {
	if (!currentEditorView()) return;
	currentEditorView()->foldBlockAt(false,currentEditorView()->editor->cursor().lineNumber());
}
void Texmaker::viewExpandEverything() {
	if (!currentEditorView()) return;
	currentEditorView()->foldEverything(true);
}
void Texmaker::viewExpandLevel() {
	if (!currentEditorView()) return;
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	currentEditorView()->foldLevel(true,action->data().toInt());
}
void Texmaker::viewExpandBlock() {
	if (!currentEditorView()) return;
	currentEditorView()->foldBlockAt(true,currentEditorView()->editor->cursor().lineNumber());
}


void Texmaker::gotoBookmark() {
	if (!currentEditorView()) return;
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	currentEditorView()->jumpToBookmark(action->data().toInt());
}
void Texmaker::toggleBookmark() {
	if (!currentEditorView()) return;
	QAction *action = qobject_cast<QAction*>(sender());
	if (!action) return;
	currentEditorView()->toggleBookmark(action->data().toInt()); //-1 is unnamed bookmark
}

//*********************************
void Texmaker::dragEnterEvent(QDragEnterEvent *event) {
	if (event->mimeData()->hasFormat("text/uri-list")) event->acceptProposedAction();
}

void Texmaker::dropEvent(QDropEvent *event) {
	QRegExp rx("file://(.*\\.(?:tex|bib|sty|cls|mp))");
	QList<QUrl> uris=event->mimeData()->urls();
	QString uri;
	for (int i = 0; i < uris.size(); ++i) {
		uri=uris.at(i).toString();
		//QMessageBox::information(0,uri,uri,0);
		if (rx.exactMatch(uri)) load(rx.cap(1));
	}
	event->acceptProposedAction();
}

void Texmaker::changeEvent(QEvent *e) {
	switch (e->type()) {
	case QEvent::LanguageChange:
		if (configManager.lastLanguage==configManager.language) return; //don't update if config not changed
		//QMessageBox::information(0,"rt","retranslate",0);
		setupMenus();
		setupDockWidgets();
		UpdateCaption();
		break;
	default:
		break;
	}
}

//***********************************
void Texmaker::SetMostUsedSymbols(QTableWidgetItem* item) {

	bool changed=false;
	int index=symbolMostused.indexOf(item);
	if(index<0){
		if(symbolMostused.size()<12){
			symbolMostused.prepend(item);
			changed=true;
		}else {
			if(item->data(Qt::UserRole).toInt()>symbolMostused[0]->data(Qt::UserRole).toInt()){
				symbolMostused.removeFirst();
				symbolMostused.prepend(item);
				changed=true;
			}
		}
	} else {
		symbolMostused.removeAt(index);
		while(index<symbolMostused.size()&&symbolMostused[index]->data(Qt::UserRole).toInt()<item->data(Qt::UserRole).toInt()){
			index++;
		}
		symbolMostused.insert(index,item);
		changed=true;
	}
	if(changed) MostUsedSymbolWidget->SetUserPage(symbolMostused);
}

void Texmaker::updateCompleter() {
	QStringList words;

	foreach (const LatexDocument* doc, documents.documents)
		words << doc->userCommandList;

	LatexEditorView* edView=currentEditorView();
	if(edView && edView->document){
		QList<LatexDocument*> docs;
		if (singlemode) docs << edView->document;
		else docs << documents.documents;
		foreach(const LatexDocument* doc,docs)
			foreach(const QString& refCommand, LatexParser::refCommands){
				QString temp=refCommand+"{%1}";
				for (int i=0; i<doc->labelItem.count(); ++i)
					words.append(temp.arg(doc->labelItem.at(i)));
			}
	}

	//add cite commands from the cwls to LatexParser::citeCommands
	LatexCompleterConfig *conf=configManager.completerConfig;
	QStringList citeCommands=conf->words;
	citeCommands=citeCommands.filter(QRegExp("^\\\\[Cc]ite.*"));
	foreach(QString elem,citeCommands)
		LatexParser::citeCommands.insert(elem.remove("{%<keylist%>}"));

	if (configManager.parseBibTeX)
		for (int i=0; i<documents.mentionedBibTeXFiles.count();i++){
			if (!documents.bibTeXFiles.contains(documents.mentionedBibTeXFiles[i])){
				qDebug("BibTex-File %s not loaded",documents.mentionedBibTeXFiles[i].toLatin1().constData());
				continue; //wtf?s
			}
			BibTeXFileInfo& bibTex=documents.bibTeXFiles[documents.mentionedBibTeXFiles[i]];

			//automatic use of cite commands
			foreach(const QString& citeCommand, LatexParser::citeCommands){
				QString temp=citeCommand+"{%1}";
				for (int i=0; i<bibTex.ids.count();i++)
					words.append(temp.arg(bibTex.ids[i]));
			}
		}

	completer->setAdditionalWords(words);

	if (!LatexCompleter::hasHelpfile()) {
		QFile f(findResourceFile("latexhelp.html"));
		if (!f.open(QIODevice::ReadOnly| QIODevice::Text))  LatexCompleter::parseHelpfile("<missing>");
		else LatexCompleter::parseHelpfile(QTextStream(&f).readAll());
	}
}

void Texmaker::tabChanged(int i) {
	if (i>0 && i<3 && !outputView->logPresent()) RealViewLog(true);
}

void Texmaker::jumpToSearch(QString filename,int lineNumber){
    if(currentEditor()->fileName()==filename && currentEditor()->cursor().lineNumber()==lineNumber)
    {
	QDocumentCursor c=currentEditor()->cursor();
	int col=c.columnNumber();
	gotoLine(lineNumber);
	col=outputView->getNextSearchResultColumn(c.line().text() ,col+1);
	currentEditor()->setCursorPosition(lineNumber,col);
    } else {
	gotoLocation(lineNumber,filename);
	int col=outputView->getNextSearchResultColumn(currentEditor()->document()->line(lineNumber).text() ,0);
	currentEditor()->setCursorPosition(lineNumber,col);
	outputView->showSearchResults();
    }
}

void Texmaker::gotoLine(int line) {
	if (currentEditorView() && line>=0)	{
		currentEditorView()->editor->setCursorPosition(line,0);
		currentEditorView()->editor->ensureCursorVisible();
		currentEditorView()->editor->setFocus();
	}
}
void Texmaker::gotoLocation(int line, const QString &fileName){
	if (!load(fileName)) return;
	gotoLine(line);
}

void Texmaker::gotoLogEntryEditorOnly(int logEntryNumber) {
	if (logEntryNumber<0 || logEntryNumber>=outputView->getLogModel()->count()) return;
	if (!load(outputView->getLogModel()->at(logEntryNumber).file)) return;
	//get line
	QDocumentLineHandle* lh = currentEditorView()->logEntryToLine.value(logEntryNumber, 0);
	if (!lh) return;
	//goto
	gotoLine(QDocumentLine(lh).lineNumber());
}

bool Texmaker::gotoLogEntryAt(int newLineNumber) {
	//goto line
	if (newLineNumber<0) return false;
	gotoLine(newLineNumber);
	//find error number
	QDocumentLineHandle* lh=currentEditorView()->editor->document()->line(newLineNumber).handle();
	int logEntryNumber=currentEditorView()->lineToLogEntries.value(lh,-1);
	if (logEntryNumber==-1) return false;
	//goto log entry
	outputView->selectLogEntry(logEntryNumber);

	QPoint p=currentEditorView()->editor->mapToGlobal(currentEditorView()->editor->mapFromContents(currentEditorView()->editor->cursor().documentPosition()));
	//  p.ry()+=2*currentEditorView()->editor->document()->fontMetrics().lineSpacing();
	QToolTip::showText(p, outputView->getLogModel()->at(logEntryNumber).niceMessage(), 0);
	LatexEditorView::hideTooltipWhenLeavingLine=newLineNumber;
	return true;
}

bool Texmaker::gotoMark(bool backward, int id) {
	if (backward)
		return gotoLogEntryAt(currentEditorView()->editor->document()->findPreviousMark(id,qMax(0,currentEditorView()->editor->cursor().lineNumber()-1),0));
	else
		return gotoLogEntryAt(currentEditorView()->editor->document()->findNextMark(id,currentEditorView()->editor->cursor().lineNumber()+1));
}

void Texmaker::StructureContextMenu(const QPoint& point) {
	StructureEntry *entry = LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry) return;
	if(entry->parent && entry->type!=StructureEntry::SE_OVERVIEW){
		if (entry->type==StructureEntry::SE_LABEL) {
			QMenu menu;
			menu.addAction(tr("Insert"),this, SLOT(editPasteRef()));
			menu.addAction(tr("Insert as %1").arg("\\ref{...}"),this, SLOT(editPasteRef()));
			menu.addAction(tr("Insert as %1").arg("\\pageref{...}"),this, SLOT(editPasteRef()));
			menu.exec(structureTreeView->mapToGlobal(point));
		} else {
			QMenu menu(this);
			menu.addAction(tr("Copy"),this, SLOT(editSectionCopy()));
			menu.addAction(tr("Cut"),this, SLOT(editSectionCut()));
			menu.addAction(tr("Paste before"),this, SLOT(editSectionPasteBefore()));
			menu.addAction(tr("Paste after"),this, SLOT(editSectionPasteAfter()));
			menu.addSeparator();
			menu.addAction(tr("Indent Section"),this, SLOT(editIndentSection()));
			menu.addAction(tr("Unindent Section"),this, SLOT(editUnIndentSection()));
			menu.exec(structureTreeView->mapToGlobal(point));
		}
	}
}

void Texmaker::editPasteRef() {
	if (!currentEditorView()) return;
	StructureEntry *entry=LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry) return;

	QAction *action = qobject_cast<QAction *>(sender());
	QString name=action->text();
	if (name==tr("Insert")) {
		QDocumentCursor m_cursor=currentEditorView()->editor->cursor();
		m_cursor.insertText(entry->title);
	} else {
		name.remove(0,name.indexOf("\\"));
		name.chop(name.length()-name.indexOf("{"));
		QDocumentCursor m_cursor=currentEditorView()->editor->cursor();
		m_cursor.insertText(name+"{"+entry->title+"}");
	}
}

void Texmaker::previewLatex(){
    if (!currentEditorView()) return;
    // get selection
	QDocumentCursor c = currentEditorView()->editor->cursor();
    QString originalText="";
	if (c.hasSelection()) {
		originalText = c.selectedText();
	} else {
		//search matching parantheses
		//it will just get the ones with the greatest distance to each other
		//=>problem if multiple matches appear (e.g ()|$...$)
		//TODO: it doesn't work if the match is in another line
		QDocumentLine l = c.line();
		int matchFormat=m_formats->id("braceMatch");
		QFormatRange first= l.getFirstOverlayBetween(0,l.length(),matchFormat);
		QFormatRange last=l.getLastOverlayBetween(0,l.length(),matchFormat);
		//QMessageBox::information(0,originalText,QString("%1 %2:%3 %4 %5").arg(first.offset).arg(first.length).arg(last.offset).arg(last.length).arg(last.format),0);
		if (first.length==0 || last.length==0) return;
		//const QVector<QParenthesis>& parens = l.parentheses();
		//int first=l.length();
		//int last=-1;
		/*for (int i=0;i< parens.count();i++)
			if (parens[i].role & QParenthesis::Match){
				if (parens[i].offset<first) first=parens[i].offset;
				else if (parens[i].offset+parens[i].length>last) first=parens[i].offset+parens[i].length;
			}*/
		//if (first==l.length() || last==-1) return;
		//originalText=l.text().mid(first,last-first);
		originalText=l.text().mid(first.offset,last.offset+last.length-first.offset);
		//QMessageBox::information(0,originalText,originalText,0);
	}
	if (originalText=="") return;
    // get document definitions
    //preliminary code ...
	LatexEditorView* edView=getEditorViewFromFileName(getCompileFileName());
	if (!edView) return;
    int m_endingLine=edView->editor->document()->findLineContaining("\\begin{document}",0,Qt::CaseSensitive);
    if (m_endingLine<0) return; // can't create header
    QStringList header;
	for (int l=0; l<m_endingLine; l++)
		header << edView->editor->document()->line(l).text();
	header << "\\pagestyle{empty}";// << "\\begin{document}";
	buildManager.preview(header.join("\n"), originalText, edView->editor->document()->codec());
}
void Texmaker::previewAvailable(const QString& imageFile, const QString& /*text*/){
	if (configManager.previewMode == ConfigManager::PM_BOTH ||
		configManager.previewMode == ConfigManager::PM_PANEL||
		(configManager.previewMode == ConfigManager::PM_TOOLTIP_AS_FALLBACK && outputView->isPreviewPanelVisible())) {
		outputView->showPreview();
		outputView->previewLatex(QPixmap(imageFile));
	}
	if (configManager.previewMode == ConfigManager::PM_BOTH ||
		configManager.previewMode == ConfigManager::PM_TOOLTIP||
		previewEquation||
		(configManager.previewMode == ConfigManager::PM_TOOLTIP_AS_FALLBACK && !outputView->isPreviewPanelVisible())) {
		QPoint p;
		if(previewEquation)
		    p=currentEditorView()->getHoverPosistion();
		else
		    p=currentEditorView()->editor->mapToGlobal(currentEditorView()->editor->mapFromContents(currentEditorView()->editor->cursor().documentPosition()));
		QRect screen = QApplication::desktop()->screenGeometry();
		QPixmap img(imageFile);
		int w=img.width();
		if(w>screen.width()) w=screen.width()-2;
		QToolTip::showText(p, QString("<img src=\""+imageFile+"\" width=%1 />").arg(w), 0);
		LatexEditorView::hideTooltipWhenLeavingLine=currentEditorView()->editor->cursor().lineNumber();

	}
	previewEquation=false;
}

void Texmaker::showPreview(const QString text){
	LatexEditorView* edView=getEditorViewFromFileName(getCompileFileName());
	if (!edView) return;
	int m_endingLine=edView->editor->document()->findLineContaining("\\begin{document}",0,Qt::CaseSensitive);
	if (m_endingLine<0) return; // can't create header
	QStringList header;
	for (int l=0; l<m_endingLine; l++)
		header << edView->editor->document()->line(l).text();
	header << "\\pagestyle{empty}";// << "\\begin{document}";
	previewEquation=true;
	buildManager.preview(header.join("\n"), text, edView->editor->document()->codec());
}

 void Texmaker::editInsertRefToNextLabel(bool backward) {
	if (!currentEditorView()) return;
	QDocumentCursor c = currentEditorView()->editor->cursor();
	int l=c.lineNumber();
	int m=currentEditorView()->editor->document()->findLineContaining("\\label",l,Qt::CaseSensitive,backward);
	if(!backward && m<l) return;
	if(m<0) return;
	QDocumentLine dLine=currentEditorView()->editor->document()->line(m);
	QString mLine=dLine.text();
	QRegExp rx("\\\\label\\{(.*)\\}");
	if(rx.indexIn(mLine)>-1){
		c.insertText("\\ref{"+rx.cap(1)+"}");
	}
}
void Texmaker::editInsertRefToPrevLabel() {
	editInsertRefToNextLabel(true);
}

 void Texmaker::SymbolGridContextMenu(QWidget* widget, const QPoint& point) {
	if (!widget->property("isSymbolGrid").toBool()) return;
	if(widget==MostUsedSymbolWidget){
		QMenu menu;
		menu.addAction(tr("Add to favorites"),this,SLOT(symbolAddFavorite()));
		menu.addAction(tr("Remove"),this,SLOT(MostUsedSymbolsTriggered()));
		menu.addAction(tr("Remove all"),this,SLOT(MostUsedSymbolsTriggered()));
		menu.exec(point);
	} else if (widget==FavoriteSymbolWidget) {
		QMenu menu;
		menu.addAction(tr("Remove from favorites"),this,SLOT(symbolRemoveFavorite()));
		menu.addAction(tr("Remove all favorites"),this,SLOT(symbolRemoveAllFavorites()));
		menu.exec(point);
	} else {
		QMenu menu;
		menu.addAction(tr("Add to favorites"),this,SLOT(symbolAddFavorite()));
		menu.exec(point);
	}

}

void Texmaker::symbolAddFavorite(){
	SymbolGridWidget* grid=qobject_cast<SymbolGridWidget*>(leftPanel->currentWidget());
	if (!grid) return;
	QString symbol=grid->getCurrentSymbol();
	if (symbol.isEmpty()) return;
	if (!symbolFavorites.contains(symbol)) symbolFavorites.append(symbol);
	FavoriteSymbolWidget->loadSymbols(symbolFavorites);
}
void Texmaker::symbolRemoveFavorite(){
	QString symbol=FavoriteSymbolWidget->getCurrentSymbol();
	if (symbol.isEmpty()) return;
	symbolFavorites.removeAll(symbol);
	FavoriteSymbolWidget->loadSymbols(symbolFavorites);
}
void Texmaker::symbolRemoveAllFavorites(){
	symbolFavorites.clear();
	FavoriteSymbolWidget->loadSymbols(symbolFavorites);
}

void Texmaker::MostUsedSymbolsTriggered(bool direct){
	 QAction *action = 0;
	 QTableWidgetItem *item=0;
	 if(!direct){
		 action = qobject_cast<QAction *>(sender());
		 item=MostUsedSymbolWidget->currentItem();
	 }
	 if(direct || action->text()==tr("remove")){
		 if(!direct){
			 QTableWidgetItem *elem=item->data(Qt::UserRole+1).value<QTableWidgetItem*>();
			 elem->setData(Qt::UserRole,0);
		 }
		symbolMostused.clear();
		for(int i=0;i<leftPanel->widgetCount();i++){
			if (!leftPanel->widget(i)->property("isSymbolGrid").toBool()) continue;
			QTableWidget* tw=qobject_cast<QTableWidget*>(leftPanel->widget(i));
			foreach(QTableWidgetItem* elem,tw->findItems("*",Qt::MatchWildcard)){
				if(!elem) continue;
				int cnt=elem->data(Qt::UserRole).toInt();
				if (cnt<1) continue;
				if(symbolMostused.isEmpty()){
					symbolMostused.append(elem);
				}else {
					int index=0;
					while(index<symbolMostused.size()&&symbolMostused[index]->data(Qt::UserRole).toInt()<cnt){
						index++;
					}
					if(index==12){
						symbolMostused.removeFirst();
						index--;
					}
					symbolMostused.insert(index,elem);
				}
			}
		}
	}else{
		for(int i=0;i<leftPanel->widgetCount();i++){
			if (!leftPanel->widget(i)->property("isSymbolGrid").toBool()) continue;
			QTableWidget* tw=qobject_cast<QTableWidget*>(leftPanel->widget(i));
			foreach(QTableWidgetItem* elem,tw->findItems("*",Qt::MatchWildcard)){
				if(!elem) continue;
				elem->setData(Qt::UserRole,0);
			}
			symbolMostused.clear();
		}
	}
	// Update Most Used Symbols Widget
	MostUsedSymbolWidget->SetUserPage(symbolMostused);
 }

void Texmaker::editFindGlobal(){
	if(!currentEditor()) return;
	QEditor *e=currentEditor();
	findGlobalDialog* dlg=new findGlobalDialog(this);
	if(e->cursor().hasSelection()){
		dlg->setSearchWord(e->cursor().selectedText());
	}
	if(dlg->exec()){
		QList<QEditor *> editors;
		switch (dlg->getSearchScope()) {
			case 0:
				editors << currentEditorView()->editor;
				break;
			case 1:
				for(int i=0;i<EditorView->count();i++){
					LatexEditorView *edView=qobject_cast<LatexEditorView *>(EditorView->widget(i));
					if (!edView) continue;
					editors << edView->editor;
				}
				break;
			default:
				break;
		}
		outputView->clearSearch();
		outputView->setSearchExpression(dlg->getSearchWord(),dlg->isCase(),dlg->isWords(),dlg->isRegExp());
		foreach(QEditor *ed,editors){
			QDocument *doc=ed->document();
			QList<QDocumentLineHandle *> lines;
			for(int l=0;l<doc->lineCount();l++){
				l=doc->findLineRegExp(dlg->getSearchWord(),l,dlg->isCase() ? Qt::CaseSensitive : Qt::CaseInsensitive,dlg->isWords(),dlg->isRegExp());
				if(l>-1) lines << doc->line(l).handle();
				if(l==-1) break;
			}

			if(!lines.isEmpty()){ // don't add empty searches
				outputView->addSearch(lines,ed->fileName());
				outputView->showSearchResults();
			}
		}
	}
	delete dlg;
}

// show current cursor position in structure view
void Texmaker::cursorPositionChanged(){
	if (!currentEditorView()) return;
	int i=currentEditor()->cursor().lineNumber();
	int oldLine=currentLine;
	// search line in structure
	if (currentLine==i) return;
	currentLine=i;

	LatexDocumentsModel *model=qobject_cast<LatexDocumentsModel*>(structureTreeView->model());
	if (!model) return; //shouldn't happen

	StructureEntry *oldSection = model->highlightedEntry();
	if (oldSection && currentLine>oldLine && currentLine<oldSection->lineNumber && oldSection->document==currentEditorView()->document)
		return; //still in the same section

	StructureEntryIterator iter(currentEditorView()->document->baseStructure);
	StructureEntry *newSection=0;

	while (/*iter.hasNext()*/true){
		StructureEntry *curSection=0;
		while (iter.hasNext()){
			curSection=iter.next();
			if (curSection->type==StructureEntry::SE_SECTION)
				break;
		}
		if (curSection==0 || curSection->type!=StructureEntry::SE_SECTION)
			break;

		if (curSection->lineNumber > currentLine) break; //curSection is after newSection where the cursor is
		else newSection=curSection;
	}

	if (newSection==0 || newSection->lineNumber>currentLine){
		model->setHighlightedEntry(0);
		return;
	}

	model->setHighlightedEntry(newSection);
	if(!mDontScrollToItem)
		structureTreeView->scrollTo(model->index(model->highlightedEntry()));
}
/*void Texmaker::treeWidgetChanged(){
	currentLine=-1;
	cursorPositionChanged();
}*/

void Texmaker::fileCheckin(QString filename){
	QString fn=filename.isEmpty() ? currentEditor()->fileName() : filename;
	UniversalInputDialog dialog;
	QString text;
	dialog.addTextEdit(&text, tr("commit comment:"));
	if (dialog.exec()==QDialog::Accepted){
		fileSave();
		checkin(QStringList(fn),text);
	}
}

void Texmaker::checkin(QStringList fns, QString text, bool blocking){
	QString cmd=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	cmd+=" ci -m \""+text+"\" "+fns.join(" ");
	stat2->setText(QString(" svn check in "));
	runCommand(cmd, blocking, true,false);
	foreach(QString elem,fns){
		LatexEditorView *edView=getEditorViewFromFileName(elem);
		edView->editor->setProperty("undoRevision",0);
	}
}

bool Texmaker::svnadd(QStringList fns,int stage){
	foreach(QString elem,fns){
		QString path=QFileInfo(elem).absolutePath();
		if(!QFile::exists(path+"/.svn")){
			if(stage<configManager.svnSearchPathDepth){
				if(stage>0){
					QDir dr(path);
					dr.cdUp();
					path=dr.absolutePath();
				}
				if(svnadd(QStringList(path),stage+1)){
					checkin(QStringList(path));
				} else
					return false;
			} else {
				return false;
			}
		}
	}
	QString cmd=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	cmd+=" add "+fns.join(" ");
	stat2->setText(QString(" svn add "));
	runCommand(cmd, false, true,false);
	return true;
}

void Texmaker::svncreateRep(QString fn){
	QString cmd=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	QString admin=buildManager.getLatexCommand(BuildManager::CMD_SVNADMIN);
	QString path=QFileInfo(fn).absolutePath();
	admin+=" create "+path+"/repo";
	stat2->setText(QString(" svn create repo "));
	runCommand(admin, true, true,false);
	QString scmd=cmd+" mkdir file:///"+path+"/repo/trunk -m\"tmx auto generate\"";
	runCommand(scmd, true, true,false);
	scmd=cmd+" mkdir file:///"+path+"/repo/branches -m\"tmx auto generate\"";
	runCommand(scmd, true, true,false);
	scmd=cmd+" mkdir file:///"+path+"/repo/tags -m\"tmx auto generate\"";
	runCommand(scmd, true, true,false);
	stat2->setText(QString(" svn checkout repo"));
	cmd+=" co file:///"+path+"/repo/trunk "+path;
	runCommand(cmd, true, true,false);
}

void Texmaker::svnUndo(bool redo){
	QString cmd_svn=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	QString fn=currentEditor()->fileName();
	// get revisions of current file
	QString cmd=cmd_svn+" log "+fn;
	QString buffer;
	runCommand(cmd,true,false,false,&buffer);
	QStringList revisions=buffer.split("\n",QString::SkipEmptyParts);
	buffer.clear();
	QMutableStringListIterator i(revisions);
	bool keep=false;
	QString elem;
	while(i.hasNext()){
		elem=i.next();
		if(!keep) i.remove();
		keep=elem.contains(QRegExp("-{60,}"));
	}

	QVariant zw=currentEditor()->property("undoRevision");
	int undoRevision=zw.canConvert<int>()?zw.toInt():0;

	int l=revisions.size();
	if(undoRevision>=l-1) return;
	if(!redo) undoRevision++;

	if(redo) changeToRevision(revisions.at(undoRevision-1),revisions.at(undoRevision));
	else changeToRevision(revisions.at(undoRevision),revisions.at(undoRevision-1));

	currentEditor()->document()->clearUndo();
	if(redo) undoRevision--;
	currentEditor()->setProperty("undoRevision",undoRevision);
}

void Texmaker::svnPatch(QEditor *ed,QString diff){
	QStringList lines;
	if(diff.contains("\r\n")){
		lines=diff.split("\r\n");
	}else{
		if(diff.contains("\n")){
			lines=diff.split("\n");
		}else{
			lines=diff.split("\r");
		}
	}
	for(int i=0;i<4;i++) lines.removeFirst();
	QRegExp rx("@@ -(\\d+),(\\d+) \\+(\\d+),(\\d+)");
	int cur_line;
	bool atDocEnd=false;
	QDocumentCursor c=ed->cursor();
	foreach(QString elem,lines){
		QChar ch=elem.at(0);
		if(ch=='@'){
			if(rx.indexIn(elem)>-1){
				cur_line=rx.cap(3).toInt();
				c.moveTo(cur_line-1,0);
			}
		}else{
			if(ch=='-'){
				atDocEnd=(c.lineNumber()==ed->document()->lineCount()-1);
				c.eraseLine();
				if(atDocEnd) c.deletePreviousChar();
			}else{
				if(ch=='+'){
					atDocEnd=(c.lineNumber()==ed->document()->lineCount()-1);
					if(atDocEnd){
						c.movePosition(1,QDocumentCursor::EndOfLine,QDocumentCursor::MoveAnchor);
						c.insertLine();
					}
					c.insertText(elem.right(elem.length()-1));
					// if line contains \r, no further line break needed
					if(!atDocEnd){
						c.insertText("\n");
					}
				} else {
					atDocEnd=(c.lineNumber()==ed->document()->lineCount()-1);
					if(!atDocEnd){
						c.movePosition(1,QDocumentCursor::NextLine,QDocumentCursor::MoveAnchor);
						c.movePosition(1,QDocumentCursor::StartOfLine,QDocumentCursor::MoveAnchor);
					}
				}
			}
		}
	}
}

void Texmaker::showOldRevisions(){
	// check if a dialog is already open
	if(svndlg) return;
	//needs to save first if modified
	if (!currentEditor())
		return;

	if (currentEditor()->fileName()=="" || !currentEditor()->fileInfo().exists())
		return;

	if(currentEditor()->isContentModified()){
		currentEditor()->save();
		//currentEditorView()->editor->setModified(false);
		MarkCurrentFileAsRecent();
		checkin(QStringList(currentEditor()->fileName()),"tmx auto checkin",true);
	}
	UpdateCaption();

	QStringList log=svnLog();
	if(log.size()<1) return;

	svndlg=new QDialog(this);
	QVBoxLayout *lay=new QVBoxLayout(svndlg);
	QLabel *label=new QLabel(tr("Attention: dialog is automatically closed if the text is manually edited!"),svndlg);
	lay->addWidget(label);
	cmbLog=new QComboBox(svndlg);
	cmbLog->insertItems(0,log);
	lay->addWidget(cmbLog);
	connect(svndlg,SIGNAL(finished(int)),this,SLOT(svnDialogClosed()));
	connect(cmbLog,SIGNAL(currentIndexChanged(QString)),this,SLOT(changeToRevision(QString)));
	connect(currentEditor(),SIGNAL(textEdited(QKeyEvent*)),svndlg,SLOT(close()));
	currentEditor()->setProperty("Revision",log.first());
	svndlg->setAttribute(Qt::WA_DeleteOnClose,true);
	svndlg->show();
}
void Texmaker::svnDialogClosed(){
	if(cmbLog->currentIndex()==0) currentEditor()->document()->setClean();
	svndlg=0;
}

void Texmaker::changeToRevision(QString rev,QString old_rev){
	QString cmd_svn=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	QString fn=currentEditor()->fileName();
	// get diff
	QRegExp rx("^[r](\\d+) \\|");
	QString old_revision;
	if(old_rev.isEmpty()){
		disconnect(currentEditor(),SIGNAL(contentModified(bool)),svndlg,SLOT(close()));
		QVariant zw=currentEditor()->property("Revision");
		Q_ASSERT(zw.isValid());
		old_revision= zw.toString();
	}else{
		old_revision=old_rev;
	}
	if(rx.indexIn(old_revision)>-1){
		old_revision=rx.cap(1);
	} else return;
	QString new_revision=rev;
	if(rx.indexIn(new_revision)>-1){
		new_revision=rx.cap(1);
	} else return;
	QString cmd=cmd_svn+" diff -r "+old_revision+":"+new_revision+" "+fn;
	QString buffer;
	runCommand(cmd,true,false,false,&buffer);
	// patch
	svnPatch(currentEditor(),buffer);
	currentEditor()->setProperty("Revision",rev);
	if(old_rev.isEmpty()){
		connect(currentEditor(),SIGNAL(textEdited(QKeyEvent*)),svndlg,SLOT(close()));
	}
}

QStringList Texmaker::svnLog(){
	QString cmd_svn=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	QString fn=currentEditor()->fileName();
	// get revisions of current file
	QString cmd=cmd_svn+" log "+fn;
	QString buffer;
	runCommand(cmd,true,false,false,&buffer);
	QStringList revisions=buffer.split("\n",QString::SkipEmptyParts);
	buffer.clear();
	QMutableStringListIterator i(revisions);
	bool keep=false;
	QString elem;
	while(i.hasNext()){
		elem=i.next();
		if(!keep) i.remove();
		keep=elem.contains(QRegExp("-{60,}"));
	}
	return revisions;
}
