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
#include "insertgraphics.h"

#ifndef QT_NO_DEBUG
#include "tests/testmanager.h"
#endif

#include "qdocument.h"
#include "qdocumentcursor.h"
#include "qdocumentline.h"
#include "qdocumentline_p.h"

#include "qnfadefinition.h"


Texmaker::Texmaker(QWidget *parent, Qt::WFlags flags)
		: QMainWindow(parent, flags), spellToolBar(0), textAnalysisDlg(0), spellDlg(0), PROCESSRUNNING(false), mDontScrollToItem(false) {

	MapForSymbols=0;
	currentLine=-1;
	thesaurusFileName.clear();
	previewEquation=false;
	svndlg=0;
	mCompleterNeedsUpdate=false;

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

	QDocument::fmtWidthCache.clear();

	if (configManager.autodetectLoadedFile) QDocument::setDefaultCodec(0);
	else QDocument::setDefaultCodec(configManager.newFileEncoding);


	QString qxsPath=QFileInfo(findResourceFile("qxs/tex.qnfa")).path();
	m_languages = new QLanguageFactory(m_formats, this);
	m_languages->addDefinitionPath(qxsPath);

	// custom evironments
	if(!configManager.customEnvironments.isEmpty()){
	    QLanguageFactory::LangData m_lang=m_languages->languageData("(La-)Tex");

	    QFile f(findResourceFile("qxs/tex.qnfa"));
	    QDomDocument doc;
	    doc.setContent(&f);

	    QMap<QString, QVariant>::const_iterator i;
	    for (i = configManager.customEnvironments.constBegin(); i != configManager.customEnvironments.constEnd(); ++i){
		QString mode=configManager.enviromentModes.value(i.value().toInt(),"verbatim");
		addEnvironmentToDom(doc,i.key(),mode);
	    }
	    QNFADefinition::load(doc,&m_lang,dynamic_cast<QFormatScheme*>(m_formats));

	    m_languages->addLanguage(m_lang);
	}

	QLineMarksInfoCenter::instance()->loadMarkTypes(qxsPath+"/marks.qxm");


// TAB WIDGET EDITEUR
        connect(&documents,SIGNAL(masterDocumentChanged(LatexDocument *)), SLOT(masterDocumentChanged(LatexDocument *)));

        EditorView=new TmxTabWidget(this);
	EditorView->setFocusPolicy(Qt::ClickFocus);
	EditorView->setFocus();
	connect(EditorView, SIGNAL(currentChanged(int)), this, SLOT(UpdateCaption()));
	if (hasAtLeastQt(4,5)){
		EditorView->setProperty("tabsClosable",true);
		EditorView->setProperty("movable",true);
		connect(EditorView, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseEditorTab(int)));
                connect(EditorView, SIGNAL(tabMoved(int,int)), this, SLOT(EditorTabMoved(int,int)));
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
		list=new XmlTagsListWidget(this,":/tags/"+tagFile);
		list->setObjectName("tags/"+tagFile.left(tagFile.indexOf("_tags.xml")));
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

	addTagList("brackets", ":/images/leftright.png", tr("Left/Right Brackets"),"brackets_tags.xml");
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
	newManagedAction(menu, "new",tr("&New"), SLOT(fileNew()), Qt::CTRL+Qt::Key_N, ":/images/filenew.png");
	newManagedAction(menu, "newfromtemplate",tr("New from &template"), SLOT(fileNewFromTemplate()));
	newManagedAction(menu, "open",tr("&Open"), SLOT(fileOpen()), Qt::CTRL+Qt::Key_O, ":/images/fileopen.png");

	QMenu *submenu=newManagedMenu(menu, "openrecent",tr("Open Recent")); //only create the menu here, actions are created by config manager
	newManagedAction(menu, "restoresession",tr("Restore previous session"), SLOT(fileRestoreSession()));

	menu->addSeparator();
	newManagedAction(menu,"save",tr("&Save"), SLOT(fileSave()), Qt::CTRL+Qt::Key_S, ":/images/filesave.png");
	newManagedAction(menu,"saveas",tr("Save &As"), SLOT(fileSaveAs()), Qt::CTRL+Qt::ALT+Qt::Key_S);
	newManagedAction(menu,"saveall",tr("Save A&ll"), SLOT(fileSaveAll()), Qt::CTRL+Qt::SHIFT+Qt::ALT+Qt::Key_S);
	newManagedAction(menu, "maketemplate",tr("&Make Template"), SLOT(fileMakeTemplate()));
	newManagedAction(menu, "checkin",tr("Check &in"), SLOT(fileCheckin()));
	newManagedAction(menu, "showrevisions",tr("Sh&ow old Revisions"), SLOT(showOldRevisions()));

	menu->addSeparator();
	newManagedAction(menu,"close",tr("&Close"), SLOT(fileClose()), Qt::CTRL+Qt::Key_W, ":/images/fileclose.png");
	newManagedAction(menu,"closeall",tr("Clos&e All"), SLOT(fileCloseAll()));

	menu->addSeparator();
	newManagedAction(menu, "print",tr("Print"), SLOT(filePrint()), Qt::CTRL+Qt::Key_P);

	menu->addSeparator();
	newManagedAction(menu,"exit",tr("Exit"), SLOT(fileExit()), Qt::CTRL+Qt::Key_Q);

//edit

	menu=newManagedMenu("main/edit",tr("&Edit"));
	newManagedAction(menu, "undo",tr("&Undo"), SLOT(editUndo()), Qt::CTRL+Qt::Key_Z, ":/images/undo.png");
	newManagedAction(menu, "redo",tr("&Redo"), SLOT(editRedo()), Qt::CTRL+Qt::Key_Y, ":/images/redo.png");

	menu->addSeparator();
	newManagedAction(menu,"copy",tr("&Copy"), SLOT(editCopy()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_C)<<Qt::CTRL+Qt::Key_Insert, ":/images/editcopy.png");
	newManagedAction(menu,"cut",tr("C&ut"), SLOT(editCut()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_X)<<Qt::SHIFT+Qt::Key_Delete, ":/images/editcut.png");
	newManagedAction(menu,"paste",tr("&Paste"), SLOT(editPaste()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_V)<<Qt::AltModifier+Qt::Key_Insert, ":/images/editpaste.png");
	newManagedAction(menu,"selectall",tr("Select &All"), SLOT(editSelectAll()), Qt::CTRL+Qt::Key_A);
	newManagedAction(menu,"eraseLine",tr("Erase &Line"), SLOT(editEraseLine()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_K));
	newManagedAction(menu,"eraseWord",tr("Erase &Word/Cmd/Env"), SLOT(editEraseWordCmdEnv()), Qt::ALT+Qt::Key_Delete);
	menu->addSeparator();
	newManagedAction(menu,"pasteAsLatex",tr("Pas&te as Latex"), SLOT(editPasteLatex()), Qt::CTRL+Qt::SHIFT+Qt::Key_V, ":/images/editpaste.png");
	newManagedAction(menu,"convertToLatex",tr("Co&nvert to Latex"), SLOT(convertToLatex()));
	newManagedAction(menu,"previewLatex",tr("Pre&view Selection/Parantheses"), SLOT(previewLatex()),Qt::ALT+Qt::Key_P);

	if (LatexEditorView::getBaseActions().empty()) //only called at first menu created
		LatexEditorView::setBaseActions(menu->actions());

	menu->addSeparator();
	newManagedAction(menu,"comment", tr("Co&mment"), SLOT(editComment()));
	newManagedAction(menu,"uncomment",tr("&Uncomment"), SLOT(editUncomment()));
	newManagedAction(menu,"indent",tr("In&dent"), SLOT(editIndent()));
	newManagedAction(menu,"unindent",tr("Unind&ent"), SLOT(editUnindent()));
	newManagedAction(menu,"hardbreak",tr("Hard Line &Break"), SLOT(editHardLineBreak()));
	newManagedAction(menu,"hardbreakrepeat",tr("R&epeat Hard Line Break"), SLOT(editHardLineBreakRepeat()));

	menu->addSeparator();
	newManagedAction(menu,"find", tr("&Find"), SLOT(editFind()), Qt::CTRL+Qt::Key_F);
	newManagedAction(menu,"findnext",tr("Find &Next"), SLOT(editFindNext()), Qt::CTRL+Qt::Key_M);
	newManagedAction(menu,"findglobal",tr("Find D&ialog"), SLOT(editFindGlobal()));
	newManagedAction(menu,"replace",tr("&Replace"), SLOT(editReplace()), Qt::CTRL+Qt::Key_R);
	newManagedAction(menu,"generateMirror",tr("Re&name Environment"), SLOT(generateMirror()));

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
	newManagedAction(menu, "latex",tr("&LaTeX"), SLOT(commandFromAction()), Qt::Key_F2, ":/images/latex.png")->setData(BuildManager::CMD_LATEX);
	newManagedAction(menu, "viewdvi",tr("&View Dvi"), SLOT(commandFromAction()), Qt::Key_F3, ":/images/viewdvi.png")->setData(BuildManager::CMD_VIEWDVI);
	newManagedAction(menu, "dvi2ps",tr("&Dvi->PS"), SLOT(commandFromAction()), Qt::Key_F4, ":/images/dvips.png")->setData(BuildManager::CMD_DVIPS);
	newManagedAction(menu, "viewps",tr("Vie&w PS"), SLOT(commandFromAction()), Qt::Key_F5, ":/images/viewps.png")->setData(BuildManager::CMD_VIEWPS);
	newManagedAction(menu, "pdflatex",tr("&PDFLaTeX"), SLOT(commandFromAction()), Qt::Key_F6, ":/images/pdflatex.png")->setData(BuildManager::CMD_PDFLATEX);
	newManagedAction(menu, "viewpdf",tr("View PD&F"), SLOT(commandFromAction()), Qt::Key_F7, ":/images/viewpdf.png")->setData(BuildManager::CMD_VIEWPDF);
	newManagedAction(menu, "ps2pdf",tr("P&S->PDF"), SLOT(commandFromAction()), Qt::Key_F8, ":/images/ps2pdf.png")->setData(BuildManager::CMD_PS2PDF);
	newManagedAction(menu, "dvipdf",tr("DV&I->PDF"), SLOT(commandFromAction()), Qt::Key_F9, ":/images/dvipdf.png")->setData(BuildManager::CMD_DVIPDF);
	newManagedAction(menu, "viewlog",tr("View &Log"), SLOT(RealViewLog()), Qt::Key_F10, ":/images/viewlog.png");
	newManagedAction(menu, "bibtex",tr("&BibTeX"), SLOT(commandFromAction()), Qt::Key_F11)->setData(BuildManager::CMD_BIBTEX);
	newManagedAction(menu, "makeindex",tr("&MakeIndex"), SLOT(commandFromAction()), Qt::Key_F12)->setData(BuildManager::CMD_MAKEINDEX);
	newManagedAction(menu, "clearmarkers",tr("&Clear Markers"), SLOT(ClearMarkers()));

	menu->addSeparator();
	newManagedAction(menu, "metapost",tr("&MetaPost"), SLOT(commandFromAction()))->setData(BuildManager::CMD_METAPOST);
	menu->addSeparator();
	newManagedAction(menu, "clean",tr("Cle&an"), SLOT(CleanAll()));
	menu->addSeparator();
	newManagedAction(menu, "htmlexport",tr("C&onvert to Html"), SLOT(WebPublish()));
	menu->addSeparator();
	newManagedAction(menu, "analysetext",tr("A&nalyse Text"), SLOT(AnalyseText()));
	newManagedAction(menu, "generaterandomtext",tr("Generate &Random Text"), SLOT(GenerateRandomText()));

//  Latex/Math external
	configManager.loadManagedMenus(":/uiconfig.xml");
	// add some additional items
	menu=newManagedMenu("main/latex",tr("&Latex"));
	newManagedAction(menu, "insertrefnextlabel",tr("Insert \\ref to next label"), SLOT(editInsertRefToNextLabel()), Qt::ALT+Qt::CTRL+Qt::Key_R);
	newManagedAction(menu, "insertrefprevlabel",tr("Insert \\ref to previous label"), SLOT(editInsertRefToPrevLabel()));

//wizards

	menu=newManagedMenu("main/wizards",tr("&Wizards"));
	newManagedAction(menu, "start",tr("Quick &Start"), SLOT(QuickDocument()));
	newManagedAction(menu, "letter",tr("Quick &Letter"), SLOT(QuickLetter()));

	menu->addSeparator();
	newManagedAction(menu, "tabular",tr("Quick &Tabular"), SLOT(QuickTabular()));
	newManagedAction(menu, "tabbing",tr("Quick T&abbing"), SLOT(QuickTabbing()));
	newManagedAction(menu, "array",tr("Quick &Array"), SLOT(QuickArray()));
	newManagedAction(menu, "graphic",tr("Insert &Graphic"), SLOT(QuickGraphics()));

	menu=newManagedMenu("main/bibtex",tr("&Bibliography"));
	foreach (const BibTeXType& bt, BibTeXDialog::getPossibleBibTeXTypes())
		newManagedAction(menu,bt.name.mid(1), bt.description, SLOT(InsertBibEntryFromAction()))->setData(bt.name);
	menu->addSeparator();
	newManagedAction(menu, "clean", tr("&Clean"), SLOT(CleanBib()));
	menu->addSeparator();
	newManagedAction(menu, "dialog", tr("BibTeX &insert dialog"), SLOT(InsertBibEntry()));


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
	//This method will be called multiple times and must not create something if this something already exists
// spelling language
	if (!spellToolBar){
		spellToolBar = addToolBar("Spelling");
		spellToolBar->setObjectName("Spelling");
		QFontMetrics fontMetrics(spellToolBar->font());
		QStringList list;
		QDir fic=QFileInfo(configManager.spell_dic).absoluteDir();
		if (fic.exists() && fic.isReadable())
				list << fic.entryList(QStringList("*.dic"),QDir::Files,QDir::Name);


		comboSpell=createComboToolButton(spellToolBar,list,spellToolBar->height()-2,fontMetrics,this,SLOT(SpellingLanguageChanged()),QFileInfo(configManager.spell_dic).fileName());
		spellToolBar->addWidget(comboSpell);
	}
//customizable toolbars
	//first apply custom icons
	QMap<QString, QVariant>::const_iterator i = configManager.replacedIconsOnMenus.constBegin();
	while (i != configManager.replacedIconsOnMenus.constEnd()) {
		QString id=i.key();
		QVariant zw=i.value();
		QObject *obj=configManager.menuParent->findChild<QObject*>(id);
		QAction *act=qobject_cast<QAction*>(obj);
		if (act) {
			if(zw.canConvert<QString>()) act->setIcon(QIcon(zw.toString()));
		}
		i++;
	}
	//setup customizable toolbars
	for (int i=0;i<configManager.managedToolBars.size();i++){
		ManagedToolBar &mtb = configManager.managedToolBars[i];
		if (!mtb.toolbar) { //create actual toolbar on first call
			mtb.toolbar = addToolBar(mtb.name);
			mtb.toolbar->setObjectName(mtb.name);
		} else mtb.toolbar->clear();
		foreach (const QString& actionName, mtb.actualActions){
			if (actionName == "separator") mtb.toolbar->addSeparator(); //Case 1: Separator
			else if (actionName.startsWith("tags/")) {
				//Case 2: One of the xml tag widgets mapped on a toolbutton
				int tagCategorySep=actionName.indexOf("/",5);
				XmlTagsListWidget* tagsWidget = findChild<XmlTagsListWidget*>(actionName.left(tagCategorySep));
				if (!tagsWidget) continue;
				QStringList list=tagsWidget->tagsTxtFromCategory(actionName.mid(tagCategorySep+1));
				if (list.isEmpty()) continue;
				QFontMetrics fontMetrics(mtb.toolbar->font());
				QToolButton* combo=createComboToolButton(mtb.toolbar,list,mtb.toolbar->height()-2,fontMetrics,this,SLOT(insertXmlTagFromToolButtonAction()));
				combo->setProperty("tagsID", actionName);
				mtb.toolbar->addWidget(combo);
			} else {
				QObject *obj=configManager.menuParent->findChild<QObject*>(actionName);
				QAction *act=qobject_cast<QAction*>(obj);
				if (act) {
					//Case 3: A normal QAction
					if(act->icon().isNull())
						act->setIcon(QIcon(":/images/appicon.png"));
					mtb.toolbar->addAction(act);
				} else {
					QMenu* menu=qobject_cast<QMenu*>(obj);
					if (!menu) {
						qWarning("Unkown toolbar command %s", qPrintable(actionName));
						continue;
					}
					//Case 4: A submenu mapped on a toolbutton
					QFontMetrics fontMetrics(mtb.toolbar->font());
					QStringList list;
					foreach (const QAction* act, menu->actions())
						if (!act->isSeparator())
							list.append(act->text());
					QToolButton* combo=createComboToolButton(mtb.toolbar,list,mtb.toolbar->height()-2,fontMetrics,this,SLOT(insertFromActionFromToolButtonAction()));
					combo->setProperty("menuID", actionName);
					mtb.toolbar->addWidget(combo);
				}
			}
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
	else {
	    documents.currentDocument=currentEditorView()->document;
	    documents.updateStructure();
	}
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
			currentEditorView()->editor->setFocus();
		}
	}
	setWindowTitle(title);
	//updateStructure();
	cursorPositionChanged();
	if (documents.singleMode()) {
		outputView->resetMessagesAndLog();
		if(currentEditorView()) updateCompleter();
	}
	QString finame=getCurrentFileName();
	if (finame!="") configManager.lastDocument=finame;
}

void Texmaker::EditorTabMoved(int from,int to){
    documents.documents.move(from,to);
    documents.updateLayout();
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
	return getPathfromFilename(compFile);
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
	return getRelativeBaseNameToPath(file,basepath);
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

	//test is already opened
	LatexEditorView* existingView = getEditorViewFromFileName(f_real);
	if (existingView) {
		if (asProject) documents.setMasterDocument(existingView->document);
		EditorView->setCurrentWidget(existingView);
		return existingView;
	}

	//load it otherwise
	if (!QFile::exists(f_real)) return 0;
	bool bibTeXmodified=documents.bibTeXFilesModified;

	LatexDocument *doc=new LatexDocument(this);
	LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig,doc);
	configureNewEditorView(edit);

	edit->document=documents.findDocument(f_real);
	if (!edit->document) {
		edit->document=doc;
		edit->document->setEditorView(edit);
		documents.addDocument(edit->document);
	} else edit->document->setEditorView(edit);
	EditorView->addTab(edit, "[*] "+QFileInfo(f_real).fileName());
	EditorView->setCurrentWidget(edit);
	connect(edit->editor,SIGNAL(fileReloaded()),this,SLOT(fileReloaded()));
        connect(edit->editor,SIGNAL(fileAutoReloading(QString)),this,SLOT(fileAutoReloading(QString)));

	QFile file(f_real);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this,tr("Error"), tr("You do not have read permission to this file."));
		return 0;
	}

	edit->editor->load(f_real,QDocument::defaultCodec());
	edit->editor->document()->setLineEnding(edit->editor->document()->originalLineEnding());

	edit->editor->setFocus();
	edit->document->setEditorView(edit); //update file name (if document didn't exist)
	if (edit->editor->fileInfo().suffix()!="tex")
		m_languages->setLanguage(edit->editor, f_real);
	UpdateCaption();
	NewDocumentStatus(false);
	MarkCurrentFileAsRecent();
	updateStructure();
	ShowStructure();

	//patch Structure
	connect(edit->editor->document(),SIGNAL(contentsChange(int, int)),edit->document,SLOT(patchStructure(int,int)));
	connect(edit->editor->document(),SIGNAL(lineRemoved(QDocumentLineHandle*)),edit->document,SLOT(patchStructureRemoval(QDocumentLineHandle*)));
	connect(edit->editor->document(),SIGNAL(lineDeleted(QDocumentLineHandle*)),edit->document,SLOT(patchStructureRemoval(QDocumentLineHandle*)));
	connect(edit->document,SIGNAL(updateCompleter()),this,SLOT(completerNeedsUpdate()));
	connect(edit->document,SIGNAL(updateCompleter()),edit->editor,SLOT(completerNeedsUpdate()));
	connect(edit->editor,SIGNAL(updateCompleter()),this,SLOT(updateCompleter()));


	if (asProject) documents.setMasterDocument(edit->document);

	if (outputView->logPresent()) DisplayLatexError(); //show marks
	if (!bibTeXmodified)
		documents.bibTeXFilesModified=false; //loading a file can change the list of included bib files, but we won't consider that as a modification of them, because then they don't have to be recompiled
	return edit;
}

void Texmaker::completerNeedsUpdate(){
	mCompleterNeedsUpdate=true;
}

void Texmaker::fileNew(QString fileName) {
	LatexDocument *doc=new LatexDocument();
	LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig,doc);
	if (configManager.newFileEncoding)
		edit->editor->setFileCodec(configManager.newFileEncoding);
	else
		edit->editor->setFileCodec(QTextCodec::codecForName("utf-8"));

	configureNewEditorView(edit);

	edit->document=doc;
	edit->document->setEditorView(edit);
	documents.addDocument(edit->document);

	connect(edit->editor->document(),SIGNAL(contentsChange(int, int)),edit->document,SLOT(patchStructure(int,int)));
	connect(edit->editor->document(),SIGNAL(lineRemoved(QDocumentLineHandle*)),edit->document,SLOT(patchStructureRemoval(QDocumentLineHandle*)));
	connect(edit->editor->document(),SIGNAL(lineDeleted(QDocumentLineHandle*)),edit->document,SLOT(patchStructureRemoval(QDocumentLineHandle*)));
	connect(edit->document,SIGNAL(updateCompleter()),this,SLOT(completerNeedsUpdate()));
	connect(edit->document,SIGNAL(updateCompleter()),edit->editor,SLOT(completerNeedsUpdate()));
	connect(edit->editor,SIGNAL(updateCompleter()),this,SLOT(updateCompleter()));

	EditorView->addTab(edit, fileName);
	EditorView->setCurrentWidget(edit);

	UpdateCaption();
	NewDocumentStatus(false);

	connect(edit->editor,SIGNAL(fileReloaded()),this,SLOT(fileReloaded()));

	edit->editor->setFocus();
}

void Texmaker::fileAutoReloading(QString fname){
    LatexDocument* document=documents.findDocument(fname);
    if (!document) return;
	document->clearStructure();
}

void Texmaker::fileReloaded(){
	QEditor *mEditor = qobject_cast<QEditor *>(sender());
	if(mEditor==currentEditor()){
		updateStructure();
	}else{
		LatexDocument* document=documents.findDocument(mEditor->fileName());
		if (!document) return;
		document->updateStructure();
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
		LatexDocument *doc=new LatexDocument(this);
		LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig,doc);
		if (configManager.newFileEncoding)
			edit->editor->setFileCodec(configManager.newFileEncoding);
		else
			edit->editor->setFileCodec(QTextCodec::codecForName("utf-8"));

		configureNewEditorView(edit);

		edit->document=doc;
		edit->document->setEditorView(edit);
		documents.addDocument(edit->document);

		connect(edit->editor->document(),SIGNAL(contentsChange(int, int)),edit->document,SLOT(patchStructure(int,int)));
		connect(edit->editor->document(),SIGNAL(lineRemoved(QDocumentLineHandle*)),edit->document,SLOT(patchStructureRemoval(QDocumentLineHandle*)));
		connect(edit->editor->document(),SIGNAL(lineDeleted(QDocumentLineHandle*)),edit->document,SLOT(patchStructureRemoval(QDocumentLineHandle*)));
		connect(edit->document,SIGNAL(updateCompleter()),this,SLOT(completerNeedsUpdate()));
		connect(edit->document,SIGNAL(updateCompleter()),edit->editor,SLOT(completerNeedsUpdate()));
		connect(edit->editor,SIGNAL(updateCompleter()),this,SLOT(updateCompleter()));

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
			checkin(currentEditor()->fileName());
			if(configManager.svnUndo) currentEditor()->document()->clearUndo();
		}
	}
	UpdateCaption();
	//updateStructure(); (not needed anymore for autoupdate)
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
			if(svnadd(currentEditor()->fileName())){
				checkin(currentEditor()->fileName(),"tmx auto checkin",configManager.svnKeywordSubstitution);
			} else {
				//create simple repository
				svncreateRep(currentEditor()->fileName());
				svnadd(currentEditor()->fileName());
				checkin(currentEditor()->fileName(),"tmx auto checkin",configManager.svnKeywordSubstitution);
			}
			// set SVN Properties if desired
			if(configManager.svnKeywordSubstitution){
				QString cmd=buildManager.getLatexCommand(BuildManager::CMD_SVN);
				cmd+=" propset svn:keywords \"Date Author HeadURL Revision\" \""+currentEditor()->fileName()+"\"";
				stat2->setText(QString(" svn propset svn:keywords "));
				runCommand(cmd, false, true,false);
			}
		}

		EditorView->setTabText(EditorView->indexOf(currentEditorView()),currentEditor()->name());
		if (currentEditor()->fileInfo().suffix()!="tex")
			m_languages->setLanguage(currentEditor(), fn);

	}

	UpdateCaption();
}

void Texmaker::fileSaveAll() {
	fileSaveAll(true);
}
void Texmaker::fileSaveAll(bool alsoUnnamedFiles) {
//LatexEditorView *temp = new LatexEditorView(EditorView,colorMath,colorCommand,colorKeyword);
//temp=currentEditorView();
	int currentIndex=EditorView->indexOf(currentEditorView());
	for (int i=0;i<EditorView->count(); i++){
		LatexEditorView *edView = qobject_cast<LatexEditorView*>(EditorView->widget(i));
		if (edView->editor->fileName().isEmpty()){
			if ((i==currentIndex || alsoUnnamedFiles) ) {
				EditorView->setCurrentIndex(i);
				fileSaveAs();
			}
		//else if (edView->editor->isInConflict()) {
		//edView->editor->save();
		//}
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
	documents.setMasterDocument(0);
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
	if (accept){
		if (mainSpeller) {
			delete mainSpeller; //this saves the ignore list
			mainSpeller=0;
		}
		qDeleteAll(QDocument::fmtWidthCache);
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
	configManager.addRecentFile(getCurrentFileName(),documents.masterDocument == currentEditorView()->document);
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
	QString originalText = currentEditor()->cursor().selectedText();
	QString newText=textToLatex(originalText);
// insert
	currentEditor()->insertTextAtCursor(newText);
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
void Texmaker::editEraseWordCmdEnv(){
	if (!currentEditorView()) return;
	QDocumentCursor cursor = currentEditorView()->editor->cursor();
	QString line=cursor.line().text();
	QString command, value;
	switch(LatexParser::findContext(line, cursor.columnNumber(), command, value)){

	case LatexParser::Command:
		if (command=="\\begin" || command=="\\end"){
			//remove environment (surrounding)
			currentEditorView()->editor->document()->beginMacro();
			cursor.movePosition(1,QDocumentCursor::EndOfWord);
			cursor.movePosition(1,QDocumentCursor::StartOfWord,QDocumentCursor::KeepAnchor);
			cursor.movePosition(1,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
			cursor.removeSelectedText();
			// remove curly brakets as well
			if(cursor.nextChar()==QChar('{')){
				cursor.deleteChar();
				line=cursor.line().text();
				int col=cursor.columnNumber();
				int i=findClosingBracket(line,col);
				if(i>-1) {
					cursor.movePosition(i-col+1,QDocumentCursor::Right,QDocumentCursor::KeepAnchor);
					cursor.removeSelectedText();
					QDocument* doc=currentEditorView()->editor->document();
					QString searchWord="\\end{"+value+"}";
					QString inhibitor="\\begin{"+value+"}";
					bool backward=(command=="\\end");
					int step=1;
					if(backward) {
						qSwap(searchWord,inhibitor);
						step=-1;
					}
					int startLine=cursor.lineNumber();
					int startCol=cursor.columnNumber();
					int endLine=doc->findLineContaining(searchWord,startLine,Qt::CaseSensitive,backward);
					int inhibitLine=doc->findLineContaining(inhibitor,startLine,Qt::CaseSensitive,backward); // not perfect (same line end/start ...)
					while (inhibitLine>0 && endLine>0 && inhibitLine*step<endLine*step) {
						endLine=doc->findLineContaining(searchWord,endLine+step,Qt::CaseSensitive,backward); // not perfect (same line end/start ...)
						inhibitLine=doc->findLineContaining(inhibitor,inhibitLine+step,Qt::CaseSensitive,backward);
					}
					if(endLine>-1){
						line=doc->line(endLine).text();
						int start=line.indexOf(searchWord);
						cursor.moveTo(endLine,start);
						cursor.movePosition(searchWord.length(),QDocumentCursor::Right,QDocumentCursor::KeepAnchor);
						cursor.removeSelectedText();
						cursor.moveTo(startLine,startCol); // move cursor back to text edit pos
					}
				}
			}

			currentEditorView()->editor->document()->endMacro();
		}else{
			currentEditorView()->editor->document()->beginMacro();
			cursor.movePosition(1,QDocumentCursor::EndOfWord);
			cursor.movePosition(1,QDocumentCursor::StartOfWord,QDocumentCursor::KeepAnchor);
			cursor.movePosition(1,QDocumentCursor::Left,QDocumentCursor::KeepAnchor);
			cursor.removeSelectedText();
			// remove curly brakets as well
			if(cursor.nextChar()==QChar('{')){
				cursor.deleteChar();
				line=cursor.line().text();
				int col=cursor.columnNumber();
				int i=findClosingBracket(line,col);
				if(i>-1) {
					cursor.moveTo(cursor.lineNumber(),i);
					cursor.deleteChar();
					cursor.moveTo(cursor.lineNumber(),col);
				}
			}
			currentEditorView()->editor->document()->endMacro();
		}
		break;

	default:
		//cursor.movePosition(1,QDocumentCursor::StartOfWord);
		cursor.select(QDocumentCursor::WordUnderCursor);
		cursor.removeSelectedText();
		break;
	}
	currentEditorView()->editor->setCursor(cursor);
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

		databasefile=new QFile(configManager.thesaurus_database);
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
		currentEditor()->insertTextAtCursor(replace);
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
		currentEditor()->setCursor(m_cursor);
		currentEditor()->insertTextAtCursor(m_line);
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
		currentEditor()->setCursor(m_cursor);
		currentEditor()->insertTextAtCursor(m_line);
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
		currentEditor()->setCursor(c);
		currentEditor()->insertTextAtCursor("\n");
	} else {
		currentEditor()->setCursorPosition(line,0);
		currentEditor()->insertTextAtCursor("\n");
		currentEditor()->setCursorPosition(line,0);
	}
	editPaste();
	//UpdateStructure();
}

void Texmaker::editSectionPasteBefore(int line) {
	currentEditor()->setCursorPosition(line,0);
	currentEditor()->insertTextAtCursor("\n");
	currentEditor()->setCursorPosition(line,0);
	editPaste();
	//UpdateStructure();
}


/////////////// CONFIG ////////////////////
void Texmaker::ReadSettings() {
	QuickDocumentDialog::registerOptions(configManager);
	buildManager.registerOptions(configManager);
	configManager.registerOption("User/Templates",&userTemplatesList);

	configManager.buildManager=&buildManager;
	QSettings *config=configManager.readSettings();

	config->beginGroup("texmaker");

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

	/*for (int i=0; i<=9; i++) {
		UserMenuName[i]=config->value(QString("User/Menu%1").arg(i+1),"").toString();
		UserMenuTag[i]=config->value(QString("User/Tag%1").arg(i+1),"").toString();
		}*/
	UserMenuName=config->value("User/TagNames",QStringList()<<""<<""<<""<<""<<""<<""<<""<<""<<""<<"").toStringList();
	UserMenuTag=config->value("User/Tags",QStringList()<<""<<""<<""<<""<<""<<""<<""<<""<<""<<"").toStringList();
	UserMenuAbbrev=config->value("User/TagAbbrevs",QStringList()<<""<<""<<""<<""<<""<<""<<""<<""<<""<<"").toStringList();
	UserToolName << ""<< ""<< ""<< ""<< "";
	UserToolCommand<< ""<< ""<< ""<< ""<< "";
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

	config->setValue("Files/RestoreSession",ToggleRememberAct->isChecked());
	//always store session for manual reload
	QStringList curFiles;//store in order
	for (int i=0; i<EditorView->count(); i++) {
		LatexEditorView *ed=qobject_cast<LatexEditorView *>(EditorView->widget(i));
		if (ed) curFiles.append(ed->editor->fileName());
	}
	config->setValue("Files/Session/Files",curFiles);
	config->setValue("Files/Session/CurrentFile",currentEditorView()?currentEditor()->fileName():"");
	config->setValue("Files/Session/MasterFile",documents.singleMode()?"":documents.masterDocument->getFileName());

	config->setValue("User/TagNames",UserMenuName);
	config->setValue("User/Tags",UserMenuTag);
	config->setValue("User/TagAbbrevs",UserMenuAbbrev);

	for (int i=0; i<=4; i++) {
		config->setValue(QString("User/ToolName%1").arg(i+1),UserToolName[i]);
		config->setValue(QString("User/Tool%1").arg(i+1),UserToolCommand[i]);
	}

	for(int i=0;i<struct_level.count();i++)
	    config->setValue("Structure/Structure Level "+QString::number(i+1),struct_level[i]);

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
			} else lineNr=LatexDocumentsModel::indexToStructureEntry(index)->getRealLineNumber();
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
	if(mCompleterNeedsUpdate) updateCompleter();
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
	if(mCompleterNeedsUpdate) updateCompleter();
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
	currentEditor()->getCursorPosition(curline,curindex);
	currentEditor()->insertTextAtCursor(Entity);
	if (dy==0) currentEditor()->setCursorPosition(curline,curindex+dx);
	else if (dx==0) currentEditor()->setCursorPosition(curline+dy,0);
	else currentEditor()->setCursorPosition(curline+dy,curindex+dx);
	currentEditor()->setFocus();
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

void Texmaker::insertXmlTagFromToolButtonAction(){
	if (!currentEditorView()) return;
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	QToolButton *button = comboToolButtonFromAction(action);
	if (!button) return;
	button->defaultAction()->setText(action->text());

	QString tagsID = button->property("tagsID").toString();
	int tagCategorySep=tagsID.indexOf("/",5);
	XmlTagsListWidget* tagsWidget = findChild<XmlTagsListWidget*>(tagsID.left(tagCategorySep));
	if (!tagsWidget) return;
	QString code=tagsWidget->tagsFromTagTxt(action->text());
	CodeSnippet(code).insert(currentEditorView()->editor);
	currentEditorView()->editor->setFocus();
}

void Texmaker::insertFromActionFromToolButtonAction(){
	if (!currentEditorView()) return;
	QAction *action = qobject_cast<QAction *>(sender());
	QToolButton *button = comboToolButtonFromAction(action);
	if (!button) return;
	button->defaultAction()->setText(action->text());

	QString menuID = button->property("menuID").toString();
	QMenu* menu=configManager.getManagedMenu(menuID);
	if (!menu) return;

	foreach (QAction* act, menu->actions())
		if (act->text()==action->text()) {
			act->trigger();
			return;
		}
}

void Texmaker::InsertFromAction() {
	if (!currentEditorView())	return;
	QAction *action = qobject_cast<QAction *>(sender());
	if (action)	{
		QDocumentCursor c = currentEditorView()->editor->cursor();
		CodeSnippet cs=CodeSnippet(action->data().toString());
		cs.insertAt(currentEditorView()->editor,&c);
		outputView->setMessage(CodeSnippet(action->whatsThis()).lines.join("\n"));
	}
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

void Texmaker::QuickGraphics(){
    if (!currentEditorView())	return;

    InsertGraphics *graphicsDlg = new InsertGraphics(this,"Insert Graphic");
    if (graphicsDlg->exec()) {
	QString insert;
	if(graphicsDlg->ui.cbFloat->isChecked()){
	    insert.append("\\begin{figure}");
	    QString placement;
	    if(graphicsDlg->ui.cbHere->isChecked()) placement.append("h");
	    if(graphicsDlg->ui.cbBottom->isChecked()) placement.append("b");
	    if(graphicsDlg->ui.cbTop->isChecked()) placement.append("t");
	    if(graphicsDlg->ui.cbPage->isChecked()) placement.append("p");
	    if(!placement.isEmpty()){
		insert.append("["+placement+"]");
	    }
	    insert.append("\n");
	}
	if(graphicsDlg->ui.cbPosition->currentIndex()==0){
	    if(!graphicsDlg->ui.leCaption->text().isEmpty()) insert.append("\\caption{"+graphicsDlg->ui.leCaption->text()+"}\n");
	    if(!graphicsDlg->ui.leLabel->text().isEmpty()) insert.append("\\label{"+graphicsDlg->ui.leLabel->text()+"}\n");
	}
	insert.append("\\includegraphics");
	if(!graphicsDlg->ui.leScale->text().isEmpty()) insert.append("["+graphicsDlg->ui.leScale->text()+"]");
	insert.append("{"+graphicsDlg->ui.lineEdit->text()+"}\n");
	// caption below ?
	if(graphicsDlg->ui.cbPosition->currentIndex()==1){
	    if(!graphicsDlg->ui.leCaption->text().isEmpty()) insert.append("\\caption{"+graphicsDlg->ui.leCaption->text()+"}\n");
	    if(!graphicsDlg->ui.leLabel->text().isEmpty()) insert.append("\\label{"+graphicsDlg->ui.leLabel->text()+"}\n");
	}
	if(graphicsDlg->ui.cbFloat->isChecked()){
	    insert.append("\\end{figure}\n");
	}
	int lines=insert.count("\n");
	InsertTag(insert,0,lines);
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
	if (!currentEditorView()) {
		fileNew();
		Q_ASSERT(currentEditorView());
	}
	QuickDocumentDialog *startDlg = new QuickDocumentDialog(this,tr("Quick Start"));
	startDlg->Init();
	if (startDlg->exec()) {
		Q_ASSERT(currentEditor());
		currentEditor()->insertTextAtCursor(startDlg->getNewDocumentText());
	}
	delete startDlg;
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
	if (!currentEditorView()) return;
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

void Texmaker::InsertRef() {
	updateStructure();

	LatexEditorView* edView=currentEditorView();
	QStringList labels;
	if(edView && edView->document){
		QList<LatexDocument*> docs;
		if (documents.singleMode()) docs << edView->document;
		else docs << documents.documents;
		foreach(const LatexDocument* doc,docs)
			labels << doc->labelItem();
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
		if (documents.singleMode()) docs << edView->document;
		else docs << documents.documents;
		foreach(const LatexDocument* doc,docs)
			labels << doc->labelItem();
	} else return;
	UniversalInputDialog dialog;
	dialog.addVariable(&labels, tr("Labels:"));
	if (dialog.exec() && !labels.isEmpty()) {
		QString tag="\\pageref{"+labels.first()+"}";
		InsertTag(tag,tag.length(),0);
	} else InsertTag("\\pageref{}",9,0);
	outputView->setMessage("\\pageref{key}");
}

void Texmaker::SpellingLanguageChanged() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	if (!currentEditorView()) return;
	QString text=action->text();
	comboSpell->setDefaultAction(action);

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
	if (finame=="") {
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
	QString result=((err) ? tr("Process exited with error(s)") : tr("Process exited normally"));
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
	fileSaveAll(buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ALWAYS);
	if (getCompileFileName()=="") {
		QMessageBox::warning(this,tr("Error"),tr("Can't detect the file name.\nYou have to save a document before you can compile it."));
		return;
	}

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
	fileSaveAll(buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ALWAYS);
	BuildManager::LatexCommand cmd=(BuildManager::LatexCommand) act->data().toInt();
	bool compileLatex=(cmd==BuildManager::CMD_LATEX || cmd==BuildManager::CMD_PDFLATEX);
	if (compileLatex)
		RunPreCompileCommand();
	stat2->setText(QString(" %1 ").arg(act->text()));
	runCommand(cmd, false, false);
}

void Texmaker::CleanAll() {
	QString finame=getCompileFileName();
	if (finame=="") {
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
	fileSaveAll(buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ALWAYS);
	QStringList commandList=cmd.split("|");
	ERRPROCESS=false;
	for (int i = 0; i < commandList.size(); ++i)
		if ((!ERRPROCESS)&&(!commandList.at(i).isEmpty())) runCommand(commandList.at(i),(i<(commandList.size()-1)),true);
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
	if (finame=="")
		return false;
	QString logname=getAbsoluteFilePath(QFileInfo(finame).completeBaseName(),".log");
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
	if (finame=="") {
		QMessageBox::warning(this,tr("Error"),tr("File must be saved and compiling before you can view the log"));
		ERRPROCESS=true;
		return;
	}
	QString logname=getAbsoluteFilePath(QFileInfo(finame).completeBaseName(),".log");
	QString line;
	QFileInfo fic(logname);
	if (fic.exists() && fic.isReadable()) {
		//OutputLogTextEdit->insertLine("LOG FILE :");
		QString overrideFileName=""; //workaround, see parseLogDocument for reason
		if (configManager.ignoreLogFileNames==2 ||
			(configManager.ignoreLogFileNames==1 && documents.singleMode())) overrideFileName=getCurrentFileName();
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
	bool customEnvironmentExisted = !configManager.customEnvironments.isEmpty();
	if (configManager.execConfigDialog()) {
		mainSpeller->loadDictionary(configManager.spell_dic,configManager.configFileNameBase);
		//clear letter width cache
		qDeleteAll(QDocument::fmtWidthCache);
		QDocument::fmtWidthCache.clear();
		// refresh quick language selection combobox
		QFontMetrics fontMetrics(spellToolBar->font());
		QStringList list;
		QDir fic=QFileInfo(configManager.spell_dic).absoluteDir();
		if (fic.exists() && fic.isReadable())
			list << fic.entryList(QStringList("*.dic"),QDir::Files,QDir::Name);
		createComboToolButton(spellToolBar,list,spellToolBar->height()-2,fontMetrics,this,SLOT(SpellingLanguageChanged()),QFileInfo(configManager.spell_dic).fileName(),comboSpell);

		if (configManager.autodetectLoadedFile) QDocument::setDefaultCodec(0);
		else QDocument::setDefaultCodec(configManager.newFileEncoding);

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
		setupToolBars();

		// custom evironments
		if(customEnvironmentExisted || !configManager.customEnvironments.isEmpty()){
			QLanguageFactory::LangData m_lang=m_languages->languageData("(La-)Tex");

			QFile f(findResourceFile("qxs/tex.qnfa"));
			QDomDocument doc;
			doc.setContent(&f);

			QMap<QString, QVariant>::const_iterator i;
			for (i = configManager.customEnvironments.constBegin(); i != configManager.customEnvironments.constEnd(); ++i){
				QString mode=configManager.enviromentModes.value(i.value().toInt(),"verbatim");
				addEnvironmentToDom(doc,i.key(),mode);
			}
			QNFADefinition::load(doc,&m_lang,dynamic_cast<QFormatScheme*>(m_formats));
			m_languages->addLanguage(m_lang);
		}

		//completion
		updateCompleter();

		// update all docuemnts views as spellcheck may be different
		for (int i=0; i<EditorView->count();i++) {
			LatexEditorView* edView=qobject_cast<LatexEditorView*>(EditorView->widget(i));
			if (edView) {
				QEditor* ed = edView->editor;
				m_languages->setLanguage(ed, ed->fileName());
				ed->document()->markFormatCacheDirty();
				ed->update();
			}
		}
	}
}
void Texmaker::executeCommandLine(const QStringList& args, bool realCmdLine) {
	// parse command line
	QStringList filesToLoad;
	bool activateMasterMode = false;
	int line=-1;
	for (int i = 0; i < args.size(); ++i) {
		if (args[i]=="") continue;
		if (args[i][0] != '-')  filesToLoad << args[i];
		//-form is for backward compatibility
		if (args[i] == "--master") activateMasterMode=true;
		if (args[i] == "--line" && i+1<args.size())  line=args[++i].toInt()-1;
	}

	// execute command line
	foreach(QString fileToLoad,filesToLoad){
		QFileInfo ftl(fileToLoad);
		if (fileToLoad != "") {
			if (ftl.exists())
				load(fileToLoad, activateMasterMode);
			else if (ftl.absoluteDir().exists()) {
				fileNew(ftl.absoluteFilePath());
				if (activateMasterMode) {
					if (documents.singleMode()) ToggleMode(); //will save the new file
					else {
						ToggleMode();
						ToggleMode();
					}
				}
				//return ;
			}
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
			|| args.contains("--execute-tests") || args.contains("--execute-all-tests"))
			&& !args.contains("--disable-tests")){
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

		if (args.contains("--update-translations")) {
			QStringList translations;
			translations << "#undef UNDEFINED";
			translations << "#ifdef UNDEFINED";
			translations << "static const char* translations[] = {";
			QRegExp commandOnly("\\\\['`^\"~=.^]?[a-zA-Z]*(\\{\\})* *"); //latex command
			//copy menu item text
			QFile xmlFile(":/uiconfig.xml");
			xmlFile.open(QIODevice::ReadOnly);
			QDomDocument xml;
			xml.setContent(&xmlFile);
			QDomNode current = xml.documentElement();
			while (!current.isNull()) {
				QDomNamedNodeMap attribs = current.attributes();
				QString text = attribs.namedItem("text").nodeValue();
				if (text!="" && !commandOnly.exactMatch(text))
					translations << "QT_TRANSLATE_NOOP(\"ConfigManager\", \""+text.replace("\\","\\\\").replace("\"","\\\"")+"\"), ";
				if (current.hasChildNodes()) current=current.firstChild();
				else if (!current.nextSibling().isNull()) current=current.nextSibling();
				else if (!current.parentNode().isNull()) current = current.parentNode().nextSibling();
				else current = current.parentNode();
			}
			//copy
			QFile xmlFile2(":/qxs/defaultFormats.qxf");
			xmlFile2.open(QIODevice::ReadOnly);
			xml.setContent(&xmlFile2);
			QDomNodeList formats=xml.documentElement().elementsByTagName("format");
			for (int i=0;i<formats.size();i++)
				translations << "QT_TRANSLATE_NOOP(\"QFormatConfig\", \""+formats.at(i).attributes().namedItem("id").nodeValue()+"\"), ";

			translations << "\"\"};";
			translations << "#endif\n\n";


			QFile translationFile("additionaltranslations.cpp");
			translationFile.open(QIODevice::WriteOnly);
			translationFile.write(translations.join("\n\r").toLatin1());;
			translationFile.close();
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
	if (!documents.singleMode()) documents.setMasterDocument(0);
	else if (currentEditorView()) {
		if (getCurrentFileName()=="")
			fileSave();
		if (getCurrentFileName()=="") {
			QMessageBox::warning(this,tr("Error"),tr("You must save the file before switching to master mode."));
			return;
		}
		documents.setMasterDocument(currentEditorView()->document);
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

void Texmaker::masterDocumentChanged(LatexDocument * doc){
	Q_UNUSED(doc);
	Q_ASSERT(documents.singleMode()==!documents.masterDocument);
	if (documents.singleMode()){
		ToggleAct->setText(tr("Define Current Document as 'Master Document'"));
		outputView->resetMessagesAndLog();
		stat1->setText(QString(" %1 ").arg(tr("Normal Mode")));
	} else {
		QString shortName = documents.masterDocument->getFileInfo().fileName();
		ToggleAct->setText(tr("Normal Mode (current master document :")+shortName+")");
		stat1->setText(QString(" %1 ").arg(tr("Master Document")+ ": "+shortName));
		configManager.addRecentFile(documents.masterDocument->getFileName(),true);
                int pos=EditorView->currentIndex();
                EditorView->moveTab(pos,0);
	}
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

	if (configManager.parseBibTeX) documents.updateBibFiles();

	LatexEditorView* edView=currentEditorView();

	if(documents.singleMode()){
		if(edView && edView->document){
			words << edView->document->userCommandList();
		}
	} else {
		foreach (const LatexDocument* doc, documents.documents)
			words << doc->userCommandList();
	}


	if(edView && edView->document){
		QList<LatexDocument*> docs;
		if (documents.singleMode()) docs << edView->document;
		else docs << documents.documents;
		foreach(const LatexDocument* doc,docs)
			foreach(const QString& refCommand, LatexParser::refCommands){
				QString temp=refCommand+"{%1}";
				for (int i=0; i<doc->labelItem().count(); ++i)
					words.append(temp.arg(doc->labelItem().at(i)));
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
	if(edView) edView->viewActivated();

	if (!LatexCompleter::hasHelpfile()) {
		QFile f(findResourceFile("latexhelp.html"));
		if (!f.open(QIODevice::ReadOnly| QIODevice::Text))  LatexCompleter::parseHelpfile("<missing>");
		else LatexCompleter::parseHelpfile(QTextStream(&f).readAll());
	}

	mCompleterNeedsUpdate=false;
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
	if (entry->type==StructureEntry::SE_DOCUMENT_ROOT){
		QMenu menu;
		if (entry->document != documents.masterDocument) {
			menu.addAction(tr("Close document"), this, SLOT(structureContextMenuCloseDocument()));
			menu.addAction(tr("Set this document as master document"), this, SLOT(structureContextMenuSwitchMasterDocument()));
		} else
			menu.addAction(tr("Remove master document role"), this, SLOT(structureContextMenuSwitchMasterDocument()));
		menu.exec(structureTreeView->mapToGlobal(point));
	}
	if (!entry->parent) return;
	if (entry->type==StructureEntry::SE_LABEL) {
		QMenu menu;
		menu.addAction(tr("Insert"),this, SLOT(editPasteRef()));
		menu.addAction(tr("Insert as %1").arg("\\ref{...}"),this, SLOT(editPasteRef()));
		menu.addAction(tr("Insert as %1").arg("\\pageref{...}"),this, SLOT(editPasteRef()));
		menu.exec(structureTreeView->mapToGlobal(point));
	}
	if (entry->type==StructureEntry::SE_SECTION) {
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

void Texmaker::structureContextMenuCloseDocument(){
	StructureEntry *entry=LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry) return;
	LatexDocument* document = entry->document;
	if (!document) return;
	if (document->getEditorView()) CloseEditorTab(EditorView->indexOf(document->getEditorView()));
	else if (document == documents.masterDocument) structureContextMenuSwitchMasterDocument();
}
void Texmaker::structureContextMenuSwitchMasterDocument(){
	StructureEntry *entry=LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry) return;
	LatexDocument* document = entry->document;
	if (document == documents.masterDocument) documents.setMasterDocument(0);
	else if (document->getFileName()!="") documents.setMasterDocument(document);
	else if (document->getEditorView()) { //we have to save the document before
		documents.setMasterDocument(0);
		EditorView->setCurrentWidget(document->getEditorView());
		ToggleMode();
	}
}


void Texmaker::editPasteRef() {
	if (!currentEditorView()) return;
	StructureEntry *entry=LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry) return;

	QAction *action = qobject_cast<QAction *>(sender());
	QString name=action->text();
	if (name==tr("Insert")) {
		currentEditor()->insertTextAtCursor(entry->title);
	} else {
		name.remove(0,name.indexOf("\\"));
		name.chop(name.length()-name.indexOf("{"));
		currentEditor()->insertTextAtCursor(name+"{"+entry->title+"}");
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
	QDocumentCursor c = currentEditor()->cursor();
	int l=c.lineNumber();
	int m=currentEditorView()->editor->document()->findLineContaining("\\label",l,Qt::CaseSensitive,backward);
	if(!backward && m<l) return;
	if(m<0) return;
	QDocumentLine dLine=currentEditor()->document()->line(m);
	QString mLine=dLine.text();
	QRegExp rx("\\\\label\\{(.*)\\}");
	if(rx.indexIn(mLine)>-1){
		currentEditor()->insertTextAtCursor("\\ref{"+rx.cap(1)+"}");
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

	// search line in structure
	if (currentLine==i) return;
	currentLine=i;

	LatexDocumentsModel *model=qobject_cast<LatexDocumentsModel*>(structureTreeView->model());
	if (!model) return; //shouldn't happen

	StructureEntry *newSection=currentEditorView()->document->findSectionForLine(currentLine);

	model->setHighlightedEntry(newSection);
	if(!mDontScrollToItem)
		structureTreeView->scrollTo(model->highlightedEntry());
}

void Texmaker::fileCheckin(QString filename){
	QString fn=filename.isEmpty() ? currentEditor()->fileName() : filename;
	UniversalInputDialog dialog;
	QString text;
	dialog.addTextEdit(&text, tr("commit comment:"));
	if (dialog.exec()==QDialog::Accepted){
		fileSave();
		checkin(fn,text);
	}
}

void Texmaker::checkin(QString fn, QString text, bool blocking){
	QString cmd=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	cmd+=" ci -m \""+text+"\" \""+fn+("\"");
	stat2->setText(QString(" svn check in "));
	runCommand(cmd, blocking, true,false);
	LatexEditorView *edView=getEditorViewFromFileName(fn);
	edView->editor->setProperty("undoRevision",0);
}

bool Texmaker::svnadd(QString fn,int stage){
	QString path=QFileInfo(fn).absolutePath();
	if(!QFile::exists(path+"/.svn")){
		if(stage<configManager.svnSearchPathDepth){
			if(stage>0){
				QDir dr(path);
				dr.cdUp();
				path=dr.absolutePath();
			}
			if(svnadd(path,stage+1)){
				checkin(path);
			} else
				return false;
		} else {
			return false;
		}
	}
	QString cmd=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	cmd+=" add \""+fn+("\"");
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
		checkin(currentEditor()->fileName(),"tmx auto checkin",true);
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
	QString fn="\""+currentEditor()->fileName()+"\"";
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
	QString fn="\""+currentEditor()->fileName()+"\"";
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

void Texmaker::generateMirror(){
	if (!currentEditorView()) return;
	QDocumentCursor cursor = currentEditorView()->editor->cursor();
	QString line=cursor.line().text();
	QString command, value;
	LatexParser::ContextType result=LatexParser::findContext(line, cursor.columnNumber(), command, value);
	if(result==LatexParser::Command || result==LatexParser::Environment){
		if (command=="\\begin" || command=="\\end"){
			if (currentEditor()->currentPlaceHolder()!=-1 &&
				currentEditor()->getPlaceHolder(currentEditor()->currentPlaceHolder()).cursor.isWithinSelection(cursor))
				currentEditor()->removePlaceHolder(currentEditor()->currentPlaceHolder()); //remove currentplaceholder to prevent nesting
			//move cursor to env name
			//currentEditorView()->editor->document()->beginMacro();
			if(result==LatexParser::Environment){
				cursor.select(QDocumentCursor::WordUnderCursor);
			}else{
				cursor.movePosition(1,QDocumentCursor::EndOfWord);
				cursor.movePosition(1,QDocumentCursor::NextWord);
				cursor.movePosition(1,QDocumentCursor::NextWord,QDocumentCursor::KeepAnchor);
			}
			//currentEditorView()->editor->setCursor(cursor);
			int magicPlaceHolder=currentEditor()->placeHolderCount();
			QEditor::PlaceHolder ph;
			ph.cursor=cursor;
			currentEditor()->addPlaceHolder(ph,true);
			// remove curly brakets as well
			QDocument* doc=currentEditorView()->editor->document();
			QString searchWord="\\end{"+value+"}";
			QString inhibitor="\\begin{"+value+"}";
			bool backward=(command=="\\end");
			int step=1;
			if(backward) {
				qSwap(searchWord,inhibitor);
				step=-1;
			}
			int startLine=cursor.lineNumber();
			//int startCol=cursor.columnNumber();
			int endLine=doc->findLineContaining(searchWord,startLine+step,Qt::CaseSensitive,backward);
			int inhibitLine=doc->findLineContaining(inhibitor,startLine+step,Qt::CaseSensitive,backward); // not perfect (same line end/start ...)
			while (inhibitLine>0 && endLine>0 && inhibitLine*step<endLine*step) {
				endLine=doc->findLineContaining(searchWord,endLine+step,Qt::CaseSensitive,backward); // not perfect (same line end/start ...)
				inhibitLine=doc->findLineContaining(inhibitor,inhibitLine+step,Qt::CaseSensitive,backward);
			}
			if(endLine>-1){
				line=doc->line(endLine).text();
				int start=line.indexOf(searchWord);
				int offset=searchWord.indexOf("{");
				QEditor::PlaceHolder ph;
				ph.length=searchWord.length()-offset-1;
				ph.cursor=currentEditor()->document()->cursor(endLine,start+offset+1,endLine,start+searchWord.length()-1);
				currentEditor()->addPlaceHolderMirror(magicPlaceHolder,ph.cursor);
			}
			currentEditor()->setPlaceHolder(magicPlaceHolder);
		}

		//currentEditorView()->editor->document()->endMacro();
		//currentEditorView()->editor->setCursor(cursor);
	}

}
