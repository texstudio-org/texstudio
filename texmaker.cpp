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
#include "thesaurusdialog.h"
#include "qsearchreplacepanel.h"
#include "latexcompleter_config.h"
#include "universalinputdialog.h"
#include "insertgraphics.h"
#include "latexeditorview_config.h"

#ifndef QT_NO_DEBUG
#include "tests/testmanager.h"
#endif

#include "qdocument.h"
#include "qdocumentcursor.h"
#include "qdocumentline.h"
#include "qdocumentline_p.h"

#include "qnfadefinition.h"

#include <QMessageBox>


Texmaker::Texmaker(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), spellToolBar(0), textAnalysisDlg(0), spellDlg(0), PROCESSRUNNING(false), mDontScrollToItem(false) {

	MapForSymbols=0;
	currentLine=-1;
	previewEquation=false;
	svndlg=0;
	mCompleterNeedsUpdate=false;
	comboSpellHeight=0;
	latexStyleParser=0;

	ReadSettings();
	// set basic set of environemnt aliases (for math and tab)
	LatexParser::environmentAliases.insert("equation","math");
	LatexParser::environmentAliases.insert("equation*","math");
	LatexParser::environmentAliases.insert("displaymath","math");
	LatexParser::environmentAliases.insert("eqnarray","math");
	LatexParser::environmentAliases.insert("eqnarray*","math");
	LatexParser::environmentAliases.insert("align","math");
	LatexParser::environmentAliases.insert("align*","math");
	LatexParser::environmentAliases.insert("flalign","math");
	LatexParser::environmentAliases.insert("flalign*","math");
	LatexParser::environmentAliases.insert("alignat","math");
	LatexParser::environmentAliases.insert("alignat*","math");
	LatexParser::environmentAliases.insert("gather","math");
	LatexParser::environmentAliases.insert("gather*","math");
	LatexParser::environmentAliases.insert("multline","math");
	LatexParser::environmentAliases.insert("multline*","math");
	LatexParser::environmentAliases.insert("longtable","tabular");
	LatexParser::environmentAliases.insert("tabularx","tabular");
	LatexParser::environmentAliases.insert("tabular*","tabular");
	LatexParser::environmentAliases.insert("supertabular","tabular");
	LatexParser::environmentAliases.insert("cases","array");
	LatexParser::environmentAliases.insert("matrix","array");
	LatexParser::environmentAliases.insert("bmatrix","array");
	LatexParser::environmentAliases.insert("pmatrix","array");
	LatexParser::environmentAliases.insert("vmatrix","array");
	LatexParser::environmentAliases.insert("Bmatrix","array");
	LatexParser::environmentAliases.insert("Vmatrix","array");
	LatexParser::environmentAliases.insert("smallmatrix","array");
	LatexParser::environmentAliases.insert("eqnarray","array");
	LatexParser::environmentAliases.insert("eqnarray*","array");
	LatexParser::environmentAliases.insert("align","array");
	LatexParser::environmentAliases.insert("align*","array");
	LatexParser::environmentAliases.insert("flalign","array");
	LatexParser::environmentAliases.insert("flalign*","array");
	LatexParser::environmentAliases.insert("alignat","array");
	LatexParser::environmentAliases.insert("alignat*","array");
	LatexParser::environmentAliases.insert("split","array");

	setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
	setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

	setWindowIcon(QIcon(":/images/logo128.png"));

	setIconSize(QSize(22,22));

	leftPanel=0;
	structureTreeView=0;

	outputView=0;
	templateSelectorDialog=0;

	importCwlAliases();

	mainSpeller=new SpellerUtility();;
	mainSpeller->loadDictionary(configManager.spell_dic,configManager.configFileNameBase);

	LatexEditorView::setSpeller(mainSpeller);

	QDocument::setFormatFactory(m_formats);
	mainSpeller->spellcheckErrorFormat=m_formats->id("spellingMistake");

	if (configManager.autodetectLoadedFile) QDocument::setDefaultCodec(0);
	else QDocument::setDefaultCodec(configManager.newFileEncoding);


	QString qxsPath=QFileInfo(findResourceFile("qxs/tex.qnfa")).path();
	m_languages = new QLanguageFactory(m_formats, this);
	m_languages->addDefinitionPath(qxsPath);

	// custom evironments
	if(!configManager.customEnvironments.isEmpty()){
		QLanguageFactory::LangData m_lang=m_languages->languageData("(La-)TeX");

		QFile f(findResourceFile("qxs/tex.qnfa"));
		QDomDocument doc;
		doc.setContent(&f);

		QMap<QString, QVariant>::const_iterator i;
		for (i = configManager.customEnvironments.constBegin(); i != configManager.customEnvironments.constEnd(); ++i){
			QString mode=configManager.enviromentModes.value(i.value().toInt(),"verbatim");
			addEnvironmentToDom(doc,i.key(),mode);
		}
		QNFADefinition::load(doc,&m_lang,m_formats);

		m_languages->addLanguage(m_lang);
	}

	QLineMarksInfoCenter::instance()->loadMarkTypes(qxsPath+"/marks.qxm");
	QList<QLineMarkType> &marks = QLineMarksInfoCenter::instance()->markTypes();
	for (int i=0;i<marks.size();i++)
		if (m_formats->format("line:"+marks[i].id).background.isValid())
			marks[i].color = m_formats->format("line:"+marks[i].id).background;

	// TAB WIDGET EDITEUR
	documents.indentationInStructure=configManager.indentationInStructure;
	documents.showLineNumbersInStructure=configManager.showLineNumbersInStructure;
	connect(&documents,SIGNAL(masterDocumentChanged(LatexDocument *)), SLOT(masterDocumentChanged(LatexDocument *)));

	QFrame *centralFrame=new QFrame(this);
	centralFrame->setLineWidth(0);
	centralFrame->setFrameShape(QFrame::NoFrame);
	centralFrame->setFrameShadow(QFrame::Plain);

	//edit
	centralToolBar=new QToolBar(tr("Central"),this);
	centralToolBar->setFloatable(false);
	centralToolBar->setOrientation(Qt::Vertical);
	centralToolBar->setMovable(false);
	centralToolBar->setIconSize(QSize(16,16));

	EditorView=new TmxTabWidget(centralFrame);
	EditorView->setFocusPolicy(Qt::ClickFocus);
	EditorView->setFocus();
	connect(EditorView, SIGNAL(currentChanged(int)), SLOT(editorTabChanged(int)));
	if (hasAtLeastQt(4,5)){
		EditorView->setProperty("tabsClosable",true);
		EditorView->setProperty("movable",true);
		connect(EditorView, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseEditorTab(int)));
		connect(EditorView, SIGNAL(tabMoved(int,int)), this, SLOT(EditorTabMoved(int,int)));
	}

	QLayout* centralLayout= new QHBoxLayout(centralFrame);
	centralLayout->setSpacing(0);
	centralLayout->setMargin(0);
	centralLayout->addWidget(centralToolBar);
	centralLayout->addWidget(EditorView);

	setCentralWidget(centralFrame);

	setContextMenuPolicy(Qt::ActionsContextMenu);

	symbolMostused.clear();
	setupDockWidgets();

	setupMenus();
	configManager.updateRecentFiles(true);
	setupToolBars();
	connect(&configManager, SIGNAL(watchedMenuChanged(QString)), SLOT(updateToolBarMenu(QString)));

	restoreState(windowstate, 0);
	//workaround as toolbar central seems not be be handled by windowstate
	centralToolBar->setVisible(configManager.centralVisible);
	if(tobemaximized) showMaximized();
	if(tobefullscreen) {
		showFullScreen();
		restoreState(stateFullScreen,1);
		fullscreenModeAction->setChecked(true);
	}

	createStatusBar();
	completer=0;
	UpdateCaption();

	show();

	stat1->setText(QString(" %1 ").arg(tr("Normal Mode")));
	stat2->setText(QString(" %1 ").arg(tr("Ready")));
	// adapt menu output view visible;
	outputViewAction->setChecked(outputView->isVisible());
	connect(outputView, SIGNAL(visibilityChanged(bool)), outputViewAction, SLOT(setChecked(bool)));  //synchronize toggle action and menu action (todo: insert toggle action in menu, but not that easy with the managed menus)

	setAcceptDrops(true);
	installEventFilter(this);


	completer=new LatexCompleter(this);
	completer->setConfig(configManager.completerConfig);
	updateCompleter();
	LatexEditorView::setCompleter(completer);
	completer->updateAbbreviations();

	if (configManager.sessionRestore) {
		fileRestoreSession();
		ToggleRememberAct->setChecked(true);
	}

	/* The encoding detection works as follow:
	   If QDocument detects the file is UTF16LE/BE, use that encoding
	   Else If QDocument detects UTF-8 {
	      If LatexParser::guessEncoding finds an encoding, use that
	      Else use UTF-8
	   } Else {
	     If LatexParser::guessEncoding finds an encoding use that
	     Else if QDocument detects ascii (only 7bit characters) {
		     if default encoding == utf16: use utf-8 as fallback (because utf16 can be reliable detected and the user seems to like unicode)
		     else use default encoding
	     }
	     Else {
		     if default encoding == utf16/8: use latin1 (because the file contains invalid unicode characters )
		     else use default encoding
	     }
	   }

	*/
	QDocument::addGuessEncodingCallback(&LatexParser::guessEncoding);
	QDocument::addGuessEncodingCallback(&ConfigManager::getDefaultEncoding);


	QStringList filters;
	filters << tr("TeX files")+" (*.tex *.bib *.sty *.cls *.mp)";
	filters << tr("Plaintext files")+" (*.txt)";
	filters << tr("All files")+" (*)";
	fileFilters = filters.join(";;");

	//setup autosave timer
	connect(&autosaveTimer,SIGNAL(timeout()),this,SLOT(fileSaveAll()));
	if(configManager.autosaveEveryMinutes>0){
		autosaveTimer.start(configManager.autosaveEveryMinutes*1000*60);
	}
}

Texmaker::~Texmaker(){
	delete MapForSymbols;
	if(latexStyleParser){
		latexStyleParser->stop();
		latexStyleParser->wait();
	}
}

QMenu* Texmaker::newManagedMenu(QMenu* menu, const QString &id,const QString &text){
	return configManager.newManagedMenu(menu,id,text);
}
QAction* Texmaker::newManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QKeySequence &shortCut, const QString & iconFile, const QList<QVariant>& args) {
	QAction* tmp = configManager.newManagedAction(menu,id,text,args.isEmpty()?slotName:SLOT(relayToOwnSlot()),QList<QKeySequence>() << shortCut, iconFile);
	if (!args.isEmpty()) {
		QString slot = QString(slotName).left(QString(slotName).indexOf("("));
		Q_ASSERT(staticMetaObject.indexOfSlot(createMethodSignature(qPrintable(slot), args)) != -1);
		tmp->setProperty("slot", qPrintable(slot));
		tmp->setProperty("args", QVariant::fromValue<QList<QVariant> >(args));
	}
	return tmp;
}
QAction* Texmaker::newManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QList<QKeySequence> &shortCuts, const QString & iconFile, const QList<QVariant>& args) {
	QAction* tmp = configManager.newManagedAction(menu,id,text, args.isEmpty()?slotName:SLOT(relayToOwnSlot()),shortCuts, iconFile);
	if (!args.isEmpty()) {
		QString slot = QString(slotName).left(QString(slotName).indexOf("("));
		Q_ASSERT(staticMetaObject.indexOfSlot(createMethodSignature(qPrintable(slot), args)) != -1);
		tmp->setProperty("slot", qPrintable(slot));
		tmp->setProperty("args", QVariant::fromValue<QList<QVariant> >(args));
	}
	return tmp;
}
QAction* Texmaker::newManagedEditorAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QKeySequence &shortCut, const QString & iconFile, const QList<QVariant>& args) {
	QAction* tmp = configManager.newManagedAction(menu,id,text,0,QList<QKeySequence>() << shortCut, iconFile);
	linkToEditorSlot(tmp, slotName, args);
	return tmp;
}
QAction* Texmaker::newManagedEditorAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QList<QKeySequence> &shortCuts, const QString & iconFile, const QList<QVariant>& args) {
	QAction* tmp = configManager.newManagedAction(menu,id,text,0,shortCuts, iconFile);
	linkToEditorSlot(tmp, slotName, args);
	return tmp;
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
QAction* Texmaker::insertManagedAction(QAction* before, const QString &id,const QString &text, const char* slotName, const QKeySequence &shortCut, const QString & iconFile){
	QMenu* menu = before->menu();
	REQUIRE_RET(menu, 0);
	QAction* inserted = newManagedAction(menu, id, text, slotName, shortCut, iconFile);
	menu->removeAction(inserted);
	menu->insertAction(before, inserted);
	return inserted;
}

SymbolGridWidget* Texmaker::addSymbolGrid(const QString& SymbolList,  const QString& iconName, const QString& text){
	SymbolGridWidget* list = qobject_cast<SymbolGridWidget*>(leftPanel->widget(SymbolList));
	if (!list) {
		list=new SymbolGridWidget(this,SymbolList,MapForSymbols);
		list->setProperty("isSymbolGrid",true);
		connect(list, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(InsertSymbol(QTableWidgetItem*)));
		connect(list, SIGNAL(itemPressed(QTableWidgetItem*)), this, SLOT(InsertSymbolPressed(QTableWidgetItem*)));
		leftPanel->addWidget(list, SymbolList, text, getRealIconFile(iconName));
	} else {
		leftPanel->setWidgetText(list,text);
		leftPanel->setWidgetIcon(list,getRealIconFile(iconName));
	}
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
		addAction(leftPanel->toggleViewAction());
	}

	if (!structureTreeView) {
		structureTreeView=new QTreeView(this);
		structureTreeView->header()->hide();
		if(configManager.indentationInStructure>0)
			structureTreeView->setIndentation(configManager.indentationInStructure);
		structureTreeView->setModel(documents.model);
		//disabled because it also reacts to expand, connect(structureTreeView, SIGNAL(activated(const QModelIndex &)), SLOT(clickedOnStructureEntry(const QModelIndex &))); //enter or double click (+single click on some platforms)
		connect(structureTreeView, SIGNAL(pressed(const QModelIndex &)), SLOT(clickedOnStructureEntry(const QModelIndex &))); //single click
		//		connect(structureTreeView, SIGNAL(expanded(const QModelIndex &)), SLOT(treeWidgetChanged()));
		//		connect(structureTreeView, SIGNAL(collapsed(const QModelIndex &)), SLOT(treeWidgetChanged()));
		//-- connect( StructureTreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *,int )), SLOT(DoubleClickedOnStructure(QTreeWidgetItem *,int))); // qt4 bugs - don't use it ?? also true for view??

		leftPanel->addWidget(structureTreeView, "structureTreeView", tr("Structure"), ":/images/structure.png");
	} else leftPanel->setWidgetText(structureTreeView,tr("Structure"));

	addSymbolGrid("operators", "math1.png",tr("Operator symbols"));
	addSymbolGrid("relation", "hi16-action-math1.png",tr("Relation symbols"));
	addSymbolGrid("arrows", "math2.png",tr("Arrow symbols"));
	addSymbolGrid("delimiters","math4.png",tr("Delimiters"));
	addSymbolGrid("greek", "math5.png",tr("Greek letters"));
	addSymbolGrid("cyrillic", "hi16-action-math10.png",tr("Cyrillic letters"));
	addSymbolGrid("misc-math", "math3.png",tr("Miscellaneous math symbols"));
	addSymbolGrid("misc-text", "hi16-action-math5.png",tr("Miscellaneous text symbols"));
	addSymbolGrid("wasysym", "hi16-action-math5.png",tr("Miscellaneous text symbols (wasysym)"));
	addSymbolGrid("special", "math-accent.png",tr("Accented letters"));

	MostUsedSymbolWidget=addSymbolGrid("!mostused",":/images/math6.png",tr("Most used symbols"));
	MostUsedSymbolWidget->loadSymbols(MapForSymbols->keys(),MapForSymbols);
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
		connect(&buildManager,SIGNAL(previewAvailable(const QString&, const QString&, int)),this,SLOT(previewAvailable	(const QString&,const QString&, int)));
		connect(&buildManager, SIGNAL(processNotification(QString)), SLOT(processNotification(QString)));
		addAction(outputView->toggleViewAction());
		QAction* temp = new QAction(this); temp->setSeparator(true);
		addAction(temp);
	}
	outputView->setWindowTitle(tr("Messages / Log File"));

}

void Texmaker::updateToolBarMenu(const QString& menuName){
	QMenu* menu = configManager.getManagedMenu(menuName);
	if (!menu) return;
	foreach (const ManagedToolBar& tb, configManager.managedToolBars)
		if (tb.toolbar && tb.actualActions.contains(menuName))
			foreach (QObject* w, tb.toolbar->children())
				if (w->property("menuID").toString() == menuName) {
		QToolButton* combo = qobject_cast<QToolButton*>(w);
		REQUIRE(combo);

		QFontMetrics fontMetrics(tb.toolbar->font());
		QStringList list;
		foreach (const QAction* act, menu->actions())
			if (!act->isSeparator())
				list.append(act->text());
		createComboToolButton(tb.toolbar,list,0,fontMetrics,this,SLOT(callToolButtonAction()),"",combo);

		if (menuName == "main/view/documents") {
			//workaround to select the current document
			int index = EditorView->currentIndex();
			if (index >= 0 && index < combo->menu()->actions().size())
				combo->setDefaultAction(combo->menu()->actions()[index]);
		}
	}

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
	newManagedAction(menu, "new",tr("&New"), SLOT(fileNew()), Qt::CTRL+Qt::Key_N, "filenew");
	newManagedAction(menu, "newfromtemplate",tr("New from &template..."), SLOT(fileNewFromTemplate()));
	newManagedAction(menu, "open",tr("&Open..."), SLOT(fileOpen()), Qt::CTRL+Qt::Key_O, "fileopen");

	QMenu *submenu=newManagedMenu(menu, "openrecent",tr("Open &Recent")); //only create the menu here, actions are created by config manager
	newManagedAction(menu, "restoresession",tr("Restore previous session"), SLOT(fileRestoreSession()));

	menu->addSeparator();
	newManagedAction(menu,"save",tr("&Save"), SLOT(fileSave()), Qt::CTRL+Qt::Key_S, "filesave");
	newManagedAction(menu,"saveas",tr("Save &As..."), SLOT(fileSaveAs()), Qt::CTRL+Qt::ALT+Qt::Key_S);
	newManagedAction(menu,"saveall",tr("Save A&ll"), SLOT(fileSaveAll()), Qt::CTRL+Qt::SHIFT+Qt::ALT+Qt::Key_S);
	newManagedAction(menu, "maketemplate",tr("&Make Template..."), SLOT(fileMakeTemplate()));
	QMenu *svnSubmenu=newManagedMenu(menu, "svn",tr("S&VN..."));
	newManagedAction(svnSubmenu, "checkin",tr("Check &in..."), SLOT(fileCheckin()));
	newManagedAction(svnSubmenu, "svnupdate",tr("SVN &update..."), SLOT(fileUpdate()));
	newManagedAction(svnSubmenu, "svnupdatecwd",tr("SVN update &work directory"), SLOT(fileUpdateCWD()));
	newManagedAction(svnSubmenu, "showrevisions",tr("Sh&ow old Revisions"), SLOT(showOldRevisions()));
	newManagedAction(svnSubmenu, "lockpdf",tr("Lock &PDF"), SLOT(fileLockPdf()));
	newManagedAction(svnSubmenu, "checkinpdf",tr("Check in P&DF"), SLOT(fileCheckinPdf()));

	menu->addSeparator();
	newManagedAction(menu,"close",tr("&Close"), SLOT(fileClose()), Qt::CTRL+Qt::Key_W, ":/images/fileclose.png");
	newManagedAction(menu,"closeall",tr("Clos&e All"), SLOT(fileCloseAll()));

	menu->addSeparator();
	newManagedEditorAction(menu, "print",tr("Print..."), "print", Qt::CTRL+Qt::Key_P);

	menu->addSeparator();
	newManagedAction(menu,"exit",tr("Exit"), SLOT(fileExit()), Qt::CTRL+Qt::Key_Q);

	//edit
	QList<QAction*> latexEditorContextMenu;

	menu=newManagedMenu("main/edit",tr("&Edit"));
	newManagedAction(menu, "undo",tr("&Undo"), SLOT(editUndo()), Qt::CTRL+Qt::Key_Z, "undo");
	newManagedAction(menu, "redo",tr("&Redo"), SLOT(editRedo()), Qt::CTRL+Qt::Key_Y, "redo");

	menu->addSeparator();
	newManagedAction(menu,"copy",tr("&Copy"), SLOT(editCopy()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_C)<<Qt::CTRL+Qt::Key_Insert, "editcopy");
	newManagedEditorAction(menu,"cut",tr("C&ut"), "cut", (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_X)<<Qt::SHIFT+Qt::Key_Delete, "editcut");
	newManagedEditorAction(menu,"paste",tr("&Paste"), "paste", (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_V)<<Qt::AltModifier+Qt::Key_Insert, "editpaste");
	newManagedEditorAction(menu,"selectall",tr("Select &All"), "selectAll", Qt::CTRL+Qt::Key_A);
	newManagedAction(menu,"eraseLine",tr("Erase &Line"), SLOT(editEraseLine()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_K));

	latexEditorContextMenu = menu->actions();

	menu->addSeparator();
	submenu = newManagedMenu(menu, "searching", tr("&Searching"));
	newManagedEditorAction(submenu,"find", tr("&Find"), "find", Qt::CTRL+Qt::Key_F);
	newManagedEditorAction(submenu,"findinsamedir",tr("Continue F&ind"), "findInSameDir", Qt::CTRL+Qt::Key_M);
	newManagedEditorAction(submenu,"findnext",tr("Find &Next"), "findNext");
	newManagedEditorAction(submenu,"findprev",tr("Find &Prev"), "findPrev");
	newManagedEditorAction(submenu,"findcount",tr("&Count"), "findCount");
	newManagedAction(submenu,"findglobal",tr("Find &Dialog..."), SLOT(editFindGlobal()));
	submenu->addSeparator();
	newManagedEditorAction(submenu,"replace",tr("&Replace"), "replace", Qt::CTRL+Qt::Key_R);
	newManagedEditorAction(submenu,"replacenext",tr("Replace Next"), "replaceNext");
	newManagedEditorAction(submenu,"replaceprev",tr("Replace Prev"), "replacePrev");
	newManagedEditorAction(submenu,"replaceall",tr("Replace &All"), "replaceAll");

	menu->addSeparator();
	submenu=newManagedMenu(menu, "goto",tr("Go to"));
	newManagedEditorAction(submenu,"line", tr("Line"), "gotoLine", Qt::CTRL+Qt::Key_G, ":/images/goto.png");
	newManagedEditorAction(submenu,"lastchange",tr("last change"), "jumpChangePositionBackward", Qt::CTRL+Qt::Key_H);
	newManagedEditorAction(submenu,"nextchange",tr("\"next\" change"), "jumpChangePositionForward", Qt::CTRL+Qt::SHIFT+Qt::Key_H);
	submenu->addSeparator();
	newManagedAction(submenu,"markprev",tr("Previous mark"),"gotoMark",Qt::CTRL+Qt::Key_Up,"",QList<QVariant>() << true << -1);//, ":/images/errorprev.png");
	newManagedAction(submenu,"marknext",tr("Next mark"),"gotoMark",Qt::CTRL+Qt::Key_Down,"",QList<QVariant>() << false << -1);//, ":/images/errornext.png");

	submenu=newManagedMenu(menu, "gotoBookmark",tr("Goto Bookmark"));
	for (int i=0; i<=9; i++)
		newManagedEditorAction(submenu,QString("bookmark%1").arg(i),tr("Bookmark %1").arg(i),"jumpToBookmark",Qt::CTRL+Qt::Key_0+i,"",QList<QVariant>() << i);

	submenu=newManagedMenu(menu, "toggleBookmark",tr("Toggle Bookmark"));
	newManagedEditorAction(submenu,QString("bookmark"),tr("unnamed bookmark"),"toggleBookmark",Qt::CTRL+Qt::SHIFT+Qt::Key_B, "", QList<QVariant>() << -1);
	for (int i=0; i<=9; i++)
		newManagedEditorAction(submenu,QString("bookmark%1").arg(i),tr("Bookmark %1").arg(i),"toggleBookmark",Qt::CTRL+Qt::SHIFT+Qt::Key_0+i,"",QList<QVariant>() << i);


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


	newManagedAction(menu,"encoding",tr("Setup Encoding..."),SLOT(editSetupEncoding()));
	newManagedAction(menu,"unicodeChar",tr("Insert Unicode Character..."),SLOT(editInsertUnicode()), Qt::ALT + Qt::CTRL + Qt::Key_U);



	//Edit 2 (for LaTeX related things)
	menu=newManagedMenu("main/edit2",tr("&Idefix"));
	latexEditorContextMenu << newManagedAction(menu,"eraseWord",tr("Erase &Word/Cmd/Env"), SLOT(editEraseWordCmdEnv()), Qt::ALT+Qt::Key_Delete);

	latexEditorContextMenu << menu->addSeparator();
	latexEditorContextMenu << newManagedAction(menu,"pasteAsLatex",tr("Pas&te as LaTeX"), SLOT(editPasteLatex()), Qt::CTRL+Qt::SHIFT+Qt::Key_V, "editpaste.png");
	latexEditorContextMenu << newManagedAction(menu,"convertTo",tr("Co&nvert to LaTeX"), SLOT(convertToLatex()));
	latexEditorContextMenu << newManagedAction(menu,"previewLatex",tr("Pre&view Selection/Parantheses"), SLOT(previewLatex()),Qt::ALT+Qt::Key_P);
	latexEditorContextMenu << newManagedAction(menu,"removePreviewLatex",tr("C&lear Inline Preview"), SLOT(clearPreview()));

	menu->addSeparator();
	newManagedEditorAction(menu,"comment", tr("&Comment"), "commentSelection", Qt::CTRL+Qt::Key_T);
	newManagedEditorAction(menu,"uncomment",tr("&Uncomment"), "uncommentSelection", Qt::CTRL+Qt::Key_U);
	newManagedEditorAction(menu,"indent",tr("&Indent"), "indentSelection");
	newManagedEditorAction(menu,"unindent",tr("Unin&dent"), "unindentSelection");
	newManagedAction(menu,"hardbreak",tr("Hard Line &Break..."), SLOT(editHardLineBreak()));
	newManagedAction(menu,"hardbreakrepeat",tr("R&epeat Hard Line Break"), SLOT(editHardLineBreakRepeat()));

	menu->addSeparator();
	submenu=newManagedMenu(menu, "goto",tr("&Go to"));

	newManagedAction(submenu,"errorprev",tr("Previous error"),"gotoNearLogEntry",Qt::CTRL+Qt::SHIFT+Qt::Key_Up, ":/images/errorprev.png", QList<QVariant>() << LT_ERROR << true << tr("No LaTeX errors detected !"));
	newManagedAction(submenu,"errornext",tr("Next error"),"gotoNearLogEntry",Qt::CTRL+Qt::SHIFT+Qt::Key_Down, ":/images/errornext.png", QList<QVariant>() << LT_ERROR << false << tr("No LaTeX errors detected !"));
	newManagedAction(submenu,"warningprev",tr("Previous warning"),"gotoNearLogEntry",Qt::CTRL+Qt::ALT+Qt::Key_Up,"", QList<QVariant>() << LT_WARNING << true << tr("No LaTeX warnings detected !"));//, ":/images/errorprev.png");
	newManagedAction(submenu,"warningnext",tr("Next warning"),"gotoNearLogEntry",Qt::CTRL+Qt::ALT+Qt::Key_Down, "", QList<QVariant>() << LT_WARNING << false << tr("No LaTeX warnings detected !"));//, ":/images/errornext.png");
	newManagedAction(submenu,"badboxprev",tr("Previous bad box"),"gotoNearLogEntry",Qt::SHIFT+Qt::ALT+Qt::Key_Up, "", QList<QVariant>() << LT_BADBOX << true << tr("No bad boxes detected !"));//, ":/images/errorprev.png");
	newManagedAction(submenu,"badboxnext",tr("Next bad box"),"gotoNearLogEntry",Qt::SHIFT+Qt::ALT+Qt::Key_Down, "", QList<QVariant>() << LT_BADBOX << true << tr("No bad boxes detected !"));//, ":/images/errornext.png");
	submenu->addSeparator();
	newManagedAction(submenu,"definition",tr("Definition"),SLOT(editGotoDefinition()),Qt::CTRL+Qt::ALT+Qt::Key_F);

	menu->addSeparator();
	newManagedAction(menu,"generateMirror",tr("Re&name Environment"), SLOT(generateMirror()));

	submenu = newManagedMenu(menu, "parens", tr("Parenthesis"));
	newManagedAction(submenu, "selectBracketInner", tr("Select (inner)"), SLOT(selectBracket()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_I))->setProperty("maximal", false);
	newManagedAction(submenu, "selectBracketOuter", tr("Select (outer)"), SLOT(selectBracket()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_O))->setProperty("maximal", true);
	newManagedAction(submenu, "generateInvertedBracketMirror", tr("Select (inverting)"), SLOT(generateBracketInverterMirror()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_S));

	submenu=newManagedMenu(menu, "complete",tr("Complete"));
	newManagedAction(submenu, "normal", tr("normal"), SLOT(NormalCompletion()),Qt::CTRL+Qt::Key_Space);
	newManagedAction(submenu, "environment", tr("\\begin{ completion"), SLOT(InsertEnvironmentCompletion()),Qt::CTRL+Qt::ALT+Qt::Key_Space);
	newManagedAction(submenu, "text", tr("normal text"), SLOT(InsertTextCompletion()),Qt::SHIFT+Qt::ALT+Qt::Key_Space);

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
	newManagedAction(menu, "asymptote",tr("&Asymptote"), SLOT(commandFromAction()))->setData(BuildManager::CMD_ASY);
	menu->addSeparator();
	newManagedAction(menu, "clean",tr("Cle&an"), SLOT(CleanAll()));
	menu->addSeparator();
	newManagedAction(menu, "htmlexport",tr("C&onvert to Html..."), SLOT(WebPublish()));
	newManagedAction(menu, "htmlsourceexport",tr("C&onvert Source to Html..."), SLOT(WebPublishSource()));
	menu->addSeparator();
	newManagedAction(menu, "analysetext",tr("A&nalyse Text..."), SLOT(AnalyseText()));
	newManagedAction(menu, "generaterandomtext",tr("Generate &Random Text..."), SLOT(GenerateRandomText()));
	menu->addSeparator();
	newManagedAction(menu,"spelling",tr("Check Spelling..."),SLOT(editSpell()),Qt::CTRL+Qt::SHIFT+Qt::Key_F7);
	newManagedAction(menu,"thesaurus",tr("Thesaurus..."),SLOT(editThesaurus()),Qt::CTRL+Qt::SHIFT+Qt::Key_F8);
	newManagedAction(menu,"wordrepetions",tr("Find word repetitions..."),SLOT(findWordRepetions()));

	//  Latex/Math external
	configManager.loadManagedMenus(":/uiconfig.xml");
	// add some additional items
	menu=newManagedMenu("main/latex",tr("&LaTeX"));
	newManagedAction(menu, "insertrefnextlabel",tr("Insert \\ref to next label"), SLOT(editInsertRefToNextLabel()), Qt::ALT+Qt::CTRL+Qt::Key_R);
	newManagedAction(menu, "insertrefprevlabel",tr("Insert \\ref to previous label"), SLOT(editInsertRefToPrevLabel()));
	submenu=newManagedMenu(menu, "tabularmanipulation",tr("Manipulate tables","table"));
	newManagedAction(submenu, "addRow",tr("add row","table"), SLOT(addRowCB()),QKeySequence(),":/images/addRow.png");
	newManagedAction(submenu, "addColumn",tr("add column","table"), SLOT(addColumnCB()),QKeySequence(),":/images/addCol.png");
	newManagedAction(submenu, "removeRow",tr("remove row","table"), SLOT(removeRowCB()),QKeySequence(),":/images/remRow.png");
	newManagedAction(submenu, "removeColumn",tr("remove column","table"), SLOT(removeColumnCB()),QKeySequence(),":/images/remCol.png");
	newManagedAction(submenu, "cutColumn",tr("cut column","table"), SLOT(cutColumnCB()),QKeySequence(),":/images/cutCol.png");
	newManagedAction(submenu, "pasteColumn",tr("paste column","table"), SLOT(pasteColumnCB()),QKeySequence(),":/images/pasteCol.png");
	newManagedAction(submenu, "addHLine",tr("add \\hline","table"), SLOT(addHLineCB()));
	newManagedAction(submenu, "remHLine",tr("remove \\hline","table"), SLOT(remHLineCB()));

	//wizards

	menu=newManagedMenu("main/wizards",tr("&Wizards"));
	newManagedAction(menu, "start",tr("Quick &Start..."), SLOT(QuickDocument()));
	newManagedAction(menu, "letter",tr("Quick &Letter..."), SLOT(QuickLetter()));

	menu->addSeparator();
	newManagedAction(menu, "tabular",tr("Quick &Tabular..."), SLOT(QuickTabular()));
	newManagedAction(menu, "tabbing",tr("Quick T&abbing..."), SLOT(QuickTabbing()));
	newManagedAction(menu, "array",tr("Quick &Array..."), SLOT(QuickArray()));
	newManagedAction(menu, "graphic",tr("Insert &Graphic..."), SLOT(QuickGraphics()));

	menu=newManagedMenu("main/bibtex",tr("&Bibliography"));
	foreach (const BibTeXType& bt, BibTeXDialog::getPossibleBibTeXTypes())
		newManagedAction(menu,bt.name.mid(1), bt.description, SLOT(InsertBibEntryFromAction()))->setData(bt.name);
	menu->addSeparator();
	newManagedEditorAction(menu, "clean", tr("&Clean"), "cleanBib");
	menu->addSeparator();
	newManagedAction(menu, "dialog", tr("BibTeX &insert dialog..."), SLOT(InsertBibEntry()));


	//  User
	menu=newManagedMenu("main/user",tr("&User"));
	submenu=newManagedMenu(menu,"tags",tr("User &Tags"));
	configManager.updateUserMacroMenu();

	submenu=newManagedMenu(menu,"commands",tr("User &Commands"));
	configManager.updateUserToolMenu();

	//---view---
	menu=newManagedMenu("main/view",tr("&View"));
	newManagedAction(menu, "nextdocument",tr("Next Document"), SLOT(gotoNextDocument()), Qt::ALT+Qt::Key_PageUp);
	newManagedAction(menu, "prevdocument",tr("Previous Document"), SLOT(gotoPrevDocument()), Qt::ALT+Qt::Key_PageDown);
	newManagedMenu(menu, "documents",tr("Open Documents"));

	menu->addSeparator();
	newManagedAction(menu, "structureview",leftPanel->toggleViewAction());
	outputViewAction=newManagedAction(menu, "outputview",tr("Messages / Log File"), SLOT(viewToggleOutputView()));
	outputViewAction->setCheckable(true);
	newManagedAction(menu, "closesomething",tr("Close Something"), SLOT(viewCloseSomething()), Qt::Key_Escape);

	menu->addSeparator();
	submenu=newManagedMenu(menu, "collapse", tr("Collapse"));
	newManagedEditorAction(submenu, "all", tr("Everything"), "foldEverything", 0, "", QList<QVariant>() << false);
	newManagedAction(submenu, "block", tr("Nearest block"), SLOT(viewCollapseBlock()));
	for (int i=1; i<=4; i++)
		newManagedEditorAction(submenu, QString::number(i), tr("Level %1").arg(i), "foldLevel", 0, "", QList<QVariant>() << false << i);
	submenu=newManagedMenu(menu, "expand", tr("Expand"));
	newManagedEditorAction(submenu, "all", tr("Everything"), "foldEverything", 0, "", QList<QVariant>() << true);
	newManagedAction(submenu, "block", tr("Nearest block"), SLOT(viewExpandBlock()));
	for (int i=1; i<=4; i++)
		newManagedEditorAction(submenu, QString::number(i), tr("Level %1").arg(i), "foldLevel", 0, "", QList<QVariant>() << true << i);

	menu->addSeparator();
	fullscreenModeAction=newManagedAction(menu, "fullscreenmode",tr("Fullscreen Mode"), SLOT(setFullScreenMode()));
	fullscreenModeAction->setCheckable(true);

	//---options---
	menu=newManagedMenu("main/options",tr("&Options"));
	newManagedAction(menu, "config",tr("&Configure TexMakerX..."), SLOT(GeneralOptions()), 0,":/images/configure.png");

	menu->addSeparator();
	newManagedAction(menu, "loadProfile",tr("Load &Profile..."), SLOT(loadProfile()));
	newManagedAction(menu, "saveProfile",tr("S&ave Profile..."), SLOT(saveProfile()));
	newManagedAction(menu, "saveSettings",tr("Save all current settings","menu"), SLOT(SaveSettings()));
	menu->addSeparator();
	ToggleAct=newManagedAction(menu, "masterdocument",tr("Define Current Document as '&Master Document'"), SLOT(ToggleMode()));
	ToggleRememberAct=newManagedAction(menu, "remembersession",tr("Automatically Restore &Session at Next Start"));
	ToggleRememberAct->setCheckable(true);

	//---help---
	menu=newManagedMenu("main/help",tr("&Help"));
	newManagedAction(menu, "latexreference",tr("LaTeX Reference..."), SLOT(LatexHelp()), 0,":/images/help.png");
	newManagedAction(menu, "usermanual",tr("User Manual..."), SLOT(UserManualHelp()), 0,":/images/help.png");

	menu->addSeparator();
	newManagedAction(menu, "appinfo",tr("About TexMakerX..."), SLOT(HelpAbout()), 0,":/images/appicon.png");

	//additional elements for development


	//-----context menus-----
	if (LatexEditorView::getBaseActions().empty()) //only called at first menu created
		LatexEditorView::setBaseActions(latexEditorContextMenu);

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

	configManager.watchedMenus.clear();

	//customizable toolbars
	//first apply custom icons
	QMap<QString, QVariant>::const_iterator i = configManager.replacedIconsOnMenus.constBegin();
	while (i != configManager.replacedIconsOnMenus.constEnd()) {
		QString id=i.key();
		QVariant zw=i.value();
		QObject *obj=configManager.menuParent->findChild<QObject*>(id);
		QAction *act=qobject_cast<QAction*>(obj);
		if (act && zw.canConvert<QString>()) act->setIcon(QIcon(zw.toString()));
		i++;
	}
	//setup customizable toolbars
	for (int i=0;i<configManager.managedToolBars.size();i++){
		ManagedToolBar &mtb = configManager.managedToolBars[i];
		if (!mtb.toolbar) { //create actual toolbar on first call
			if (mtb.name == "Central") mtb.toolbar = centralToolBar;
			else mtb.toolbar = addToolBar(tr(qPrintable(mtb.name)));
			mtb.toolbar->setObjectName(mtb.name);
			addAction(mtb.toolbar->toggleViewAction());
			if(mtb.name=="Math"){
				// spelling language
				if (!spellToolBar){
					spellToolBar = addToolBar(tr("Spelling"));
					spellToolBar->setObjectName("Spelling");
					QFontMetrics fontMetrics(spellToolBar->font());
					QStringList list;
					QDir fic=QFileInfo(configManager.spell_dic).absoluteDir();
					if (fic.exists() && fic.isReadable())
						list << fic.entryList(QStringList("*.dic"),QDir::Files,QDir::Name);

					if(comboSpellHeight==0)
						comboSpellHeight=spellToolBar->height()-2;
					comboSpell=createComboToolButton(spellToolBar,list,comboSpellHeight,fontMetrics,this,SLOT(SpellingLanguageChanged()),QFileInfo(configManager.spell_dic).fileName());
					spellToolBar->addWidget(comboSpell);
					addAction(spellToolBar->toggleViewAction());
				}
				addToolBarBreak();
			}
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
				if(comboSpellHeight==0)
					comboSpellHeight=mtb.toolbar->height()-2;
				QToolButton* combo=createComboToolButton(mtb.toolbar,list,comboSpellHeight,fontMetrics,this,SLOT(insertXmlTagFromToolButtonAction()));
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
					configManager.watchedMenus << actionName;
					QFontMetrics fontMetrics(mtb.toolbar->font());
					QStringList list;
					foreach (const QAction* act, menu->actions())
						if (!act->isSeparator())
							list.append(act->text());
					if(comboSpellHeight==0)
						comboSpellHeight=mtb.toolbar->height()-2;
					//TODO: Is the callToolButtonAction()-slot really needed? Can't we just add the menu itself as the menu of the qtoolbutton, without creating a copy? (should be much faster)
					QToolButton* combo=createComboToolButton(mtb.toolbar,list,comboSpellHeight,fontMetrics,this,SLOT(callToolButtonAction()));
					combo->setProperty("menuID", actionName);					
					mtb.toolbar->addWidget(combo);
				}
			}
		}
		if(mtb.actualActions.empty()) mtb.toolbar->setVisible(false);
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
		structureTreeView->setExpanded(documents.model->index(documents.currentDocument->baseStructure),true);
	}
	if(completer && completer->isVisible()) completer->close();
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
			currentEditorView()->editor->setFocus();
		}
	}
	setWindowTitle(title);
	//updateStructure();
	cursorPositionChanged();
	if (documents.singleMode()) {
		outputView->resetMessagesAndLog();
		if(currentEditorView()) completerNeedsUpdate();
	}
	QString finame=getCurrentFileName();
	if (finame!="") configManager.lastDocument=finame;
}

void Texmaker::editorTabChanged(int index){
	UpdateCaption();
	if (index < 0) return; //happens if no tab is open
	if (configManager.watchedMenus.contains("main/view/documents"))
		updateToolBarMenu("main/view/documents");
}

void Texmaker::EditorTabMoved(int from,int to){
	documents.documents.move(from,to);
	documents.updateLayout();
	updateOpenDocumentMenu(false);
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
	REQUIRE(outputView->getLogModel());
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
	QEditor * ed = edView->editor;
	QString tabText = ed->fileName().isEmpty() ? tr("untitled") : ed->name();
	if (EditorView->tabText(index) != tabText) {
		EditorView->setTabText(index, tabText);
		updateOpenDocumentMenu(true);
	}
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
	REQUIRE(m_languages);REQUIRE(edit->codeeditor);
	m_languages->setLanguage(edit->codeeditor->editor(), ".tex");
	//EditorView->setCurrentWidget(edit);

	//edit->setFormats(m_formats->id("environment"),m_formats->id("referenceMultiple"),m_formats->id("referencePresent"),m_formats->id("referenceMissing"));

	connect(edit->editor, SIGNAL(contentModified(bool)), this, SLOT(NewDocumentStatus(bool)));
	connect(edit->editor, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChanged()));
	connect(edit->editor, SIGNAL(cursorHovered()), this, SLOT(cursorHovered()));
	connect(edit->editor, SIGNAL(emitWordDoubleClicked()), this, SLOT(cursorHovered()));
	connect(edit, SIGNAL(showMarkTooltipForLogMessage(int)),this,SLOT(showMarkTooltipForLogMessage(int)));
	connect(edit, SIGNAL(needCitation(const QString&)),this,SLOT(InsertBibEntry(const QString&)));
	connect(edit, SIGNAL(showPreview(QString)),this,SLOT(showPreview(QString)));
	connect(edit, SIGNAL(showPreview(QDocumentCursor)),this,SLOT(showPreview(QDocumentCursor)));
	connect(edit, SIGNAL(openFile(QString)),this,SLOT(openExternalFile(QString)));

	connect(edit->editor,SIGNAL(fileReloaded()),this,SLOT(fileReloaded()));
	connect(edit->editor,SIGNAL(fileAutoReloading(QString)),this,SLOT(fileAutoReloading(QString)));

	edit->setBibTeXIds(&documents.allBibTeXIds);
}

//complete the new editor view configuration (edit->document is set)
void Texmaker::configureNewEditorViewEnd(LatexEditorView *edit,bool reloadFromDoc){
	REQUIRE(edit->document);
	//patch Structure
	//disconnect(edit->editor->document(),SIGNAL(contentsChange(int, int))); // force order of contentsChange update
	connect(edit->editor->document(),SIGNAL(contentsChange(int, int)),edit->document,SLOT(patchStructure(int,int)));
	//connect(edit->editor->document(),SIGNAL(contentsChange(int, int)),edit,SLOT(documentContentChanged(int,int))); now directly called by patchStructure
	connect(edit->editor->document(),SIGNAL(lineRemoved(QDocumentLineHandle*)),edit->document,SLOT(patchStructureRemoval(QDocumentLineHandle*)));
	connect(edit->editor->document(),SIGNAL(lineDeleted(QDocumentLineHandle*)),edit->document,SLOT(patchStructureRemoval(QDocumentLineHandle*)));
	connect(edit->document,SIGNAL(updateCompleter()),this,SLOT(completerNeedsUpdate()));
	connect(edit->editor,SIGNAL(needUpdatedCompleter()), this, SLOT(needUpdatedCompleter()));
	connect(edit->document,SIGNAL(importPackage(QString)),this,SLOT(importPackage(QString)));
	connect(edit,SIGNAL(thesaurus(int,int)),this,SLOT(editThesaurus(int,int)));

	EditorView->insertTab(reloadFromDoc ? documents.documents.indexOf(edit->document,0) : -1,edit, "?bug?");
	updateOpenDocumentMenu(false);
	EditorView->setCurrentWidget(edit);

	edit->editor->setFocus();
	UpdateCaption();
	NewDocumentStatus(!edit->editor->document()->isClean());
}

LatexEditorView* Texmaker::getEditorViewFromFileName(const QString &fileName, bool checkTemporaryNames){
	LatexDocument* document=documents.findDocument(fileName, checkTemporaryNames);
	if (!document) return 0;
	return document->getEditorView();
}


QString Texmaker::getCurrentFileName() {
	return documents.getCurrentFileName();
}
QString Texmaker::getAbsoluteFilePath(const QString & relName, const QString &extension){
	return documents.getAbsoluteFilePath(relName, extension);
}

bool Texmaker::FileAlreadyOpen(QString f, bool checkTemporaryNames) {
	LatexEditorView* edView = getEditorViewFromFileName(f, checkTemporaryNames);
	if (!edView) return false;
	EditorView->setCurrentWidget(edView);
	edView->editor->setFocus();
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
	} else {
		// find closed master doc
		LatexDocument *doc=documents.findDocumentFromName(f_real);
		if(doc){
			LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig,doc);
			edit->document=doc;
			edit->editor->setFileName(doc->getFileName());
			disconnect(edit->editor->document(),SIGNAL(contentsChange(int, int)),edit->document,SLOT(patchStructure(int,int)));
			configureNewEditorView(edit);

			doc->setLineEnding(edit->editor->document()->originalLineEnding());
			doc->setEditorView(edit); //update file name (if document didn't exist)

			configureNewEditorViewEnd(edit,true);
			//edit->document->initStructure();
			//updateStructure(true);
			ShowStructure();
			return edit;
		}
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

	QFile file(f_real);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this,tr("Error"), tr("You do not have read permission to this file."));
		return 0;
	}
	file.close();

	if (edit->editor->fileInfo().suffix()!="tex")
		m_languages->setLanguage(edit->editor, f_real);

	//QTime time;
	//time.start();
	edit->editor->load(f_real,QDocument::defaultCodec());
	//qDebug() << "Load time: " << time.elapsed();
	edit->editor->document()->setLineEnding(edit->editor->document()->originalLineEnding());

	edit->document->setEditorView(edit); //update file name (if document didn't exist)

	configureNewEditorViewEnd(edit,asProject);

	MarkCurrentFileAsRecent();

	documents.updateMasterSlaveRelations(doc);

	edit->updateLtxCommands();
	updateStructure(true);
	ShowStructure();



	if (asProject) documents.setMasterDocument(edit->document);

	if (outputView->logPresent()) DisplayLatexError(); //show marks
	if (!bibTeXmodified)
		documents.bibTeXFilesModified=false; //loading a file can change the list of included bib files, but we won't consider that as a modification of them, because then they don't have to be recompiled

#ifndef Q_WS_MACX
	if (windowState() == Qt::WindowMinimized || !isVisible() || !QApplication::activeWindow()) {
		show();
		if (windowState()==Qt::WindowMinimized)
			setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
		show();
		raise();
		QApplication::setActiveWindow(this);
		activateWindow();
		setFocus();
	}
	//raise();
	//#ifdef Q_WS_WIN
	//        if (IsIconic (this->winId())) ShowWindow(this->winId(), SW_RESTORE);
	//#endif
#endif

	return edit;
}

void Texmaker::completerNeedsUpdate(){
	mCompleterNeedsUpdate=true;
}

void Texmaker::needUpdatedCompleter(){
	if (mCompleterNeedsUpdate)
		updateCompleter();
}
#include "QMetaMethod"
void Texmaker::linkToEditorSlot(QAction* act, const char* methodName, const QList<QVariant>& args){
	REQUIRE(act);
	connect(act, SIGNAL(triggered()), SLOT(relayToEditorSlot()),Qt::UniqueConnection);
	QByteArray signature = createMethodSignature(methodName, args);
	if (!args.isEmpty())
		act->setProperty("args", QVariant::fromValue<QList<QVariant> >(args));
	for (int i=0;i<LatexEditorView::staticMetaObject.methodCount();i++)
		if (signature == LatexEditorView::staticMetaObject.method(i).signature()) {
		act->setProperty("editorViewSlot", methodName);
		return;
	} //else qDebug() << LatexEditorView::staticMetaObject.method(i).signature();
	for (int i=0;i<QEditor::staticMetaObject.methodCount();i++)
		if (signature == QEditor::staticMetaObject.method(i).signature()) {
		act->setProperty("editorSlot", methodName);
		return;
	}

	qDebug() << methodName << signature;
	Q_ASSERT(false);
}

void Texmaker::relayToEditorSlot(){
	if (!currentEditorView()) return;
	QAction* act = qobject_cast<QAction*>(sender());
	REQUIRE(act);
	if (act->property("editorViewSlot").isValid()) QMetaObjectInvokeMethod(currentEditorView(), qPrintable(act->property("editorViewSlot").toString()), act->property("args").value<QList<QVariant> >());
	else if (act->property("editorSlot").isValid()) QMetaObjectInvokeMethod(currentEditor(), qPrintable(act->property("editorSlot").toString()), act->property("args").value<QList<QVariant> >());
}
void Texmaker::relayToOwnSlot(){
	QAction* act = qobject_cast<QAction*>(sender());
	REQUIRE(act && act->property("slot").isValid());
	QMetaObjectInvokeMethod(this, qPrintable(act->property("slot").toString()), act->property("args").value<QList<QVariant> >());
}

void Texmaker::fileNew(QString fileName) {
	LatexDocument *doc=new LatexDocument();
	LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig,doc);
	if (configManager.newFileEncoding)
		edit->editor->setFileCodec(configManager.newFileEncoding);
	else
		edit->editor->setFileCodec(QTextCodec::codecForName("utf-8"));
	edit->editor->setFileName(fileName);

	configureNewEditorView(edit);

	edit->document=doc;
	edit->document->setEditorView(edit);
	documents.addDocument(edit->document);

	configureNewEditorViewEnd(edit);
	edit->updateLtxCommands();
}

void Texmaker::fileAutoReloading(QString fname){
	LatexDocument* document=documents.findDocument(fname);
	if (!document) return;
	document->clearStructure();
}

void Texmaker::fileReloaded(){
	QEditor *mEditor = qobject_cast<QEditor *>(sender());
	if(mEditor==currentEditor()){
		currentEditorView()->document->initStructure();
		updateStructure(true);
	}else{
		LatexDocument* document=documents.findDocument(mEditor->fileName());
		if (!document) return;
		int len=document->lineCount();
		document->initStructure();
		document->patchStructure(0,len);
	}
}

void Texmaker::fileMakeTemplate() {
	if (!currentEditorView())
		return;

	// select a directory/filepath
	QString currentDir=configManager.configBaseDir;

	// get a file name
	QString fn = QFileDialog::getSaveFileName(this,tr("Save As"),currentDir,tr("TeX files")+" (*.tex)");
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

		configureNewEditorViewEnd(edit);
		edit->updateLtxCommands();

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
	}
}


void Texmaker::fileOpen() {
	QString currentDir=QDir::homePath();
	if (!configManager.lastDocument.isEmpty()) {
		QFileInfo fi(configManager.lastDocument);
		if (fi.exists() && fi.isReadable()) {
			currentDir=fi.absolutePath();
		}
	}
	QStringList files = QFileDialog::getOpenFileNames(this,tr("Open Files"),currentDir,fileFilters,  &selectedFileFilter);
	foreach (const QString& fn, files)
		load(fn);
}

void Texmaker::fileRestoreSession(){
	fileCloseAll();
	for (int i=0; i<configManager.sessionFilesToRestore.size(); i++){
		LatexEditorView* edView=load(configManager.sessionFilesToRestore[i], configManager.sessionFilesToRestore[i]==configManager.sessionMaster);
		if(edView){
			int row=configManager.sessionCurRowsToRestore.value(i,QVariant(0)).toInt();
			int col=configManager.sessionCurColsToRestore.value(i,0).toInt();
			if(row>=edView->document->lineCount()){
				row=0;
				col=0;
			}else{
				if(edView->document->line(row).length()<col){
					col=0;
				}
			}
			edView->editor->setCursorPosition(row,col);
			edView->editor->scrollToFirstLine(configManager.sessionFirstLinesToRestore.value(i,0).toInt());
		}
	}
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

void Texmaker::fileSaveAs(const QString& fileName) {
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

	QString oldFileName=currentEditor()->fileName();
	// get a file name
	QString fn = QFileDialog::getSaveFileName(this,tr("Save As"),currentDir,fileFilters, &selectedFileFilter);
	if (!fn.isEmpty()) {
		static QRegExp fileExt("\\*(\\.[^ )]+)");
		if (fileExt.indexIn(selectedFileFilter) > -1) {
			//add
			int lastsep=qMax(fn.lastIndexOf("/"),fn.lastIndexOf("\\"));
			int lastpoint=fn.lastIndexOf(".");
			if (lastpoint <= lastsep) //if both aren't found or point is in directory name
				fn.append(fileExt.cap(1));
		}
		if (getEditorViewFromFileName(fn) && getEditorViewFromFileName(fn) != currentEditorView())
			if (QMessageBox::warning(this, "TexMakerX", tr("You are trying to save the file under the name %1, but a file with this name is already open.\nTexMakerX does not support multiple instances of the same file.\nAre you sure you want to continue?").arg(fn), QMessageBox::Yes|QMessageBox::No, QMessageBox::No) != QMessageBox::Yes)
				return;

		// save file
		currentEditor()->save(fn);
		currentEditorView()->document->setEditorView(currentEditorView()); //update file name
		MarkCurrentFileAsRecent();

		//update Master/Child relations
		LatexDocument *doc=currentEditorView()->document;
		documents.updateMasterSlaveRelations(doc);


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
				runCommand(cmd, 0);
			}
		}

		EditorView->setTabText(EditorView->currentIndex(),currentEditor()->name());
		updateOpenDocumentMenu(true);
		if (currentEditor()->fileInfo().suffix()!="tex")
			m_languages->setLanguage(currentEditor(), fn);

	}

	UpdateCaption();
}

void Texmaker::fileSaveAll() {
	fileSaveAll(true,true);
}
void Texmaker::fileSaveAll(bool alsoUnnamedFiles, bool alwaysCurrentFile) {
	//LatexEditorView *temp = new LatexEditorView(EditorView,colorMath,colorCommand,colorKeyword);
	//temp=currentEditorView();
	REQUIRE(EditorView);
	int currentIndex=EditorView->indexOf(currentEditorView());
	for (int i=0;i<EditorView->count(); i++){
		LatexEditorView *edView = qobject_cast<LatexEditorView*>(EditorView->widget(i));
		REQUIRE(edView);REQUIRE(edView->editor);
		if (edView->editor->fileName().isEmpty()){
			if ((alsoUnnamedFiles || (alwaysCurrentFile && i==currentIndex) ) ) {
				EditorView->setCurrentIndex(i);
				fileSaveAs();
			} else if (!edView->document->getTemporaryFileName().isEmpty())
				edView->editor->saveCopy(edView->document->getTemporaryFileName());
			//else if (edView->editor->isInConflict()) {
			//edView->editor->save();
			//}
		} else if (edView->editor->isContentModified() || edView->editor->isInConflict()){
			edView->editor->save(); //only save modified documents

			if (edView->editor->fileName().endsWith(".bib")) {
				QString temp=edView->editor->fileName();
				temp=temp.replace(QDir::separator(),"/");
				documents.bibTeXFilesModified = documents.bibTeXFilesModified  || documents.mentionedBibTeXFiles.contains(temp);//call bibtex on next compilation (this would also set as soon as the user switch to a tex file, but he could compile before switching)
			}
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
	updateOpenDocumentMenu();
	//UpdateCaption(); unnecessary as called by tabChanged (signal)
}

void Texmaker::fileCloseAll() {
	closeAllFilesAsking();
	documents.setMasterDocument(0);
	UpdateCaption();
}

void Texmaker::fileExit() {
	if (canCloseNow())
		qApp->quit();
}

bool Texmaker::closeAllFilesAsking(){
	while (currentEditorView()) {
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
				updateOpenDocumentMenu();
				return false;
			}
		} else
			documents.deleteDocument(currentEditorView()->document);
	}
#ifndef NO_POPPLER_PREVIEW
	foreach (PDFDocument* viewer, PDFDocument::documentList())
		viewer->close();
#endif
	updateOpenDocumentMenu();
	return true;
}

bool Texmaker::canCloseNow(){
	SaveSettings();
	bool accept = closeAllFilesAsking();
	if (accept){
		if (mainSpeller) {
			delete mainSpeller; //this saves the ignore list
			mainSpeller=0;
		}
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
void Texmaker::fileOpenAllRecent() {
	foreach (const QString& s, configManager.recentFilesList)
		load(s);
}

void Texmaker::fileOpenRecentProject() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (action) load(action->data().toString(),true);
}

void Texmaker::MarkCurrentFileAsRecent(){
	configManager.addRecentFile(getCurrentFileName(),documents.masterDocument == currentEditorView()->document);
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

void Texmaker::editCopy() {
	if ((!currentEditor() || !currentEditor()->hasFocus()) &&
	    outputView->childHasFocus() ) {
		outputView->copy();
	}
	if (!currentEditorView()) return;
	currentEditorView()->editor->copy();
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
	currentEditor()->insertText(newText);
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

void Texmaker::editHardLineBreak(){
	if (!currentEditorView()) return;
	UniversalInputDialog dialog;
	dialog.addVariable(&configManager.lastHardWrapColumn, tr("Insert hard line breaks after so many characters:"));
	dialog.addVariable(&configManager.lastHardWrapSmartScopeSelection, tr("Smart scope selecting"));
	dialog.addVariable(&configManager.lastHardWrapJoinLines, tr("Join lines before wrapping"));
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

void Texmaker::editThesaurus(int line,int col) {
	if (!ThesaurusDialog::retrieveDatabase()) {
		QMessageBox::warning(this,tr("Error"), tr("Can't load Thesaurus Database"));
		return;
	}
	ThesaurusDialog *thesaurusDialog=new ThesaurusDialog(this);
	QString word;
	if (currentEditorView()) {
		QDocumentCursor m_cursor=currentEditorView()->editor->cursor();
		if(line>-1 && col>-1){
			m_cursor.moveTo(line,col);
		}
		if(m_cursor.hasSelection()) word=m_cursor.selectedText();
		else {
			m_cursor.select(QDocumentCursor::WordUnderCursor);
			word=m_cursor.selectedText();
		}
		word=latexToPlainWord(word);
		thesaurusDialog->setSearchWord(word);
		if (thesaurusDialog->exec()){
			QString replace=thesaurusDialog->getReplaceWord();
			m_cursor.insertText(replace);
		}
	}
	delete thesaurusDialog;
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
void Texmaker::editInsertUnicode(){
	if (!currentEditorView()) return;
	QDocumentCursor c=currentEditor()->cursor();
	if (!c.isValid()) return;
	if (c.hasSelection()) {
		c.removeSelectedText();
		currentEditor()->setCursor(c);
	}
	QPoint offset;
	UnicodeInsertion * uid = new UnicodeInsertion (currentEditorView());
	if (!currentEditor()->getPositionBelowCursor(offset, uid->width(), uid->height())){
		delete uid;
		return;
	}
	connect(uid, SIGNAL(insertCharacter(QString)), currentEditor(), SLOT(insertText(QString)));
	connect(uid, SIGNAL(destroyed()), currentEditor(), SLOT(setFocus()));
	connect(currentEditor(), SIGNAL(cursorPositionChanged()), uid, SLOT(close()));
	connect(currentEditor(), SIGNAL(visibleLinesChanged()), uid, SLOT(close()));
	connect(currentEditor()->document(), SIGNAL(contentsChanged()), uid, SLOT(close()));

	uid->move(currentEditor()->mapTo(uid->parentWidget(), offset));
	this->unicodeInsertionDialog = uid;
	uid->show();
	uid->setFocus();
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
		foreach(const QString elem,m_replace) {
			if (m_old!="") m_line.replace(elem,m_old);
			m_old=elem;
		}

		m_cursor.movePosition(1,QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
		currentEditor()->setCursor(m_cursor);
		currentEditor()->insertText(m_line);
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
		foreach(const QString elem,m_replace) {
			if (m_old!="") m_line.replace(elem,m_old);
			m_old=elem;
		}

		m_cursor.movePosition(1,QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
		currentEditor()->setCursor(m_cursor);
		currentEditor()->insertText(m_line);
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
	REQUIRE(currentEditorView());
	if (line>=currentEditorView()->editor->document()->lines()) {
		currentEditorView()->editor->setCursorPosition(line-1,0);
		QDocumentCursor c=currentEditorView()->editor->cursor();
		c.movePosition(1,QDocumentCursor::End,QDocumentCursor::MoveAnchor);
		currentEditor()->setCursor(c);
		currentEditor()->insertText("\n");
	} else {
		currentEditor()->setCursorPosition(line,0);
		currentEditor()->insertText("\n");
		currentEditor()->setCursorPosition(line,0);
	}
	currentEditorView()->paste();
}

void Texmaker::editSectionPasteBefore(int line) {
	REQUIRE(currentEditor());
	currentEditor()->setCursorPosition(line,0);
	currentEditor()->insertText("\n");
	currentEditor()->setCursorPosition(line,0);
	currentEditorView()->paste();
}


/////////////// CONFIG ////////////////////
void Texmaker::ReadSettings() {
	QuickDocumentDialog::registerOptions(configManager);
	buildManager.registerOptions(configManager);
	configManager.registerOption("User/Templates",&userTemplatesList);
	configManager.ltxCommands=&(documents.ltxCommands);

	configManager.buildManager=&buildManager;
	QSettings *config=configManager.readSettings();
	completionBaseCommandsUpdated=true;

	config->beginGroup("texmaker");

	QRect screen = QApplication::desktop()->screenGeometry();
	int w= config->value("Geometries/MainwindowWidth",screen.width()-100).toInt();
	int h= config->value("Geometries/MainwindowHeight",screen.height()-100).toInt() ;
	int x= config->value("Geometries/MainwindowX",10).toInt();
	int y= config->value("Geometries/MainwindowY",10).toInt() ;
	resize(w,h);
	// in case desktop has changed since last run
	while (x>screen.width() && screen.width() > 0) x-=screen.width();
	while (y>screen.height() && screen.height() > 0) y-=screen.height();
	move(x,y);
	windowstate=config->value("MainWindowState").toByteArray();
	stateFullScreen=config->value("MainWindowFullssscreenState").toByteArray();
	tobemaximized=config->value("MainWindow/Maximized",false).toBool();
	tobefullscreen=config->value("MainWindow/FullScreen",false).toBool();

	documents.model->setSingleDocMode(config->value("StructureView/SingleDocMode",false).toBool());

	//import old
	for (int i=1; i<=5; i++) {
		QString temp = config->value(QString("User/Tool%1").arg(i),"").toString();
		if (!temp.isEmpty()) {
			configManager.userToolCommand << temp;
			configManager.userToolMenuName << config->value(QString("User/ToolName%1").arg(i),"").toString();
			config->remove(QString("User/Tool%1").arg(i));
			config->remove(QString("User/ToolName%1").arg(i));
		}
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

	ThesaurusDialog::prepareDatabase(configManager.thesaurus_database);

	MapForSymbols= new QVariantMap;
	*MapForSymbols=config->value("Symbols/Quantity").toMap();

	hiddenLeftPanelWidgets=config->value("Symbols/hiddenlists","").toString();
	symbolFavorites=config->value("Symbols/Favorite IDs",QStringList()).toStringList();

	configManager.editorKeys = QEditor::getEditOperations(false); //this will also initialize the default keys
	configManager.editorAvailableOperations=QEditor::getAvailableOperations();
	if (config->value("Editor/Use Tab for Move to Placeholder",false).toBool()) {
		//import deprecated option
		QEditor::addEditOperation(QEditor::NextPlaceHolder, Qt::ControlModifier, Qt::Key_Tab);
		QEditor::addEditOperation(QEditor::PreviousPlaceHolder, Qt::ShiftModifier | Qt::ControlModifier, Qt::Key_Backtab);
		QEditor::addEditOperation(QEditor::CursorWordLeft, Qt::ControlModifier, Qt::Key_Left);
		QEditor::addEditOperation(QEditor::CursorWordRight, Qt::ControlModifier, Qt::Key_Right);
	};
	config->beginGroup("Editor Key Mapping");
	QStringList sl = config->childKeys();
	if (!sl.empty()) {
		foreach (const QString& key, sl)
			configManager.editorKeys.insert(key.toInt(), config->value(key).toInt());
		QEditor::setEditOperations(configManager.editorKeys);
	}
	config->endGroup();
	config->endGroup();

	config->beginGroup("formats");
	m_formats = new QFormatFactory(":/qxs/defaultFormats.qxf", this); //load default formats from resource file
	m_formats->load(*config,true); //load customized formats
	config->endGroup();

	// read usageCount from file of its own.
	LatexCompleterConfig *conf=configManager.completerConfig;
	QFile file(configManager.configBaseDir+"wordCount.usage");
	if(file.open(QIODevice::ReadOnly)){
		QDataStream in(&file);
		quint32 magicNumer,version;
		in >>  magicNumer >> version;
		if (magicNumer==(quint32)0xA0B0C0D0 && version==1){
			in.setVersion(QDataStream::Qt_4_0);
			uint key;
			int length,usage;

			while (!in.atEnd()) {
				in >> key >> length >> usage;
				if(usage>0){
					conf->usage.insert(key,qMakePair(length,usage));
				}
			}
		}
	}

	documents.settingsRead();
}

void Texmaker::SaveSettings(const QString& configName) {
	bool asProfile=!configName.isEmpty();
	configManager.centralVisible=centralToolBar->isVisible();
	// update completion usage
	LatexCompleterConfig *conf=configManager.completerConfig;

	QSettings *config=configManager.saveSettings(configName);

	config->beginGroup("texmaker");
	QList<int> sizes;
	QList<int>::Iterator it;
	if(!asProfile){
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
		QList<QVariant> firstLines,curCols,curRows;
		for (int i=0; i<EditorView->count(); i++) {
			LatexEditorView *ed=qobject_cast<LatexEditorView *>(EditorView->widget(i));
			if (ed) {
				curFiles.append(ed->editor->fileName());
				curCols.append(ed->editor->cursor().columnNumber());
				curRows.append(ed->editor->cursor().lineNumber());
				firstLines.append(ed->editor->getFirstVisibleLine());
			}
		}
		config->setValue("Files/Session/Files",curFiles);
		config->setValue("Files/Session/curCols",curCols);
		config->setValue("Files/Session/curRows",curRows);
		config->setValue("Files/Session/firstLines",firstLines);
		config->setValue("Files/Session/CurrentFile",currentEditorView()?currentEditor()->fileName():"");
		config->setValue("Files/Session/MasterFile",documents.singleMode()?"":documents.masterDocument->getFileName());
	}


	for(int i=0;i<struct_level.count();i++)
		config->setValue("Structure/Structure Level "+QString::number(i+1),struct_level[i]);

	MapForSymbols->clear();
	foreach(QTableWidgetItem *elem,symbolMostused){
		int cnt=elem->data(Qt::UserRole).toInt();
		if (cnt<1) continue;
		QString text=elem->data(Qt::UserRole+2).toString();
		if(MapForSymbols->value(text).toInt()>cnt) cnt=MapForSymbols->value(text).toInt();
		MapForSymbols->insert(text,cnt);
	}
	config->setValue("Symbols/Quantity",*MapForSymbols);

	config->setValue("Symbols/Favorite IDs",symbolFavorites);

	config->setValue("Symbols/hiddenlists",leftPanel->hiddenWidgets());

	config->setValue("StructureView/SingleDocMode",documents.model->getSingleDocMode());


	QHash<int, int> keys = QEditor::getEditOperations(true);
	config->remove("Editor/Use Tab for Move to Placeholder");
	config->beginGroup("Editor Key Mapping");
	if (!keys.empty() || !config->childKeys().empty()) {
		config->remove("");
		QHash<int, int>::const_iterator i = keys.begin();
		while (i != keys.constEnd()) {
			config->setValue(QString::number(i.key()), i.value());
			++i;
		}
	}
	config->endGroup();

	config->endGroup();

	config->beginGroup("formats");
	QFormatFactory defaultFormats(":/qxs/defaultFormats.qxf", this); //load default formats from resource file
	m_formats->save(*config,&defaultFormats);
	config->endGroup();

	// save usageCount in file of its own.
	if(!asProfile){
		QFile file(configManager.configBaseDir+"wordCount.usage");
		if(file.open(QIODevice::WriteOnly)){
			QDataStream out(&file);
			out << (quint32)0xA0B0C0D0;  //magic number
			out << (qint32)1; //version
			out.setVersion(QDataStream::Qt_4_0);
			QMap<uint, QPair<int,int> >::const_iterator i = conf->usage.constBegin();
			while (i != conf->usage.constEnd()) {
				QPair<int,int> elem=i.value();
				if(elem.second>0){
					out << i.key();
					out << elem.first;
					out << elem.second;
				}
				++i;
			}
		}
	}

	if (asProfile)
		delete config;
}

////////////////// STRUCTURE ///////////////////
void Texmaker::ShowStructure() {
	leftPanel->setCurrentWidget(structureTreeView);
}

void Texmaker::updateStructure(bool initial) {
	// collect user define tex commands for completer
	// initialize List
	if (!currentEditorView() || !currentEditorView()->document) return;
	if(initial){
		int len=currentEditorView()->document->lineCount();
		currentEditorView()->document->patchStructure(0,len);
	}
	else {
		currentEditorView()->document->updateStructure();
	}

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
			openExternalFile(entry->title,defaultExt,entry->document);
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

	if(c.previousChar()==QChar('\\')) currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST);
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
			if(cmd.startsWith("begin{")||cmd.startsWith("end{")){
				currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST);
				return;
			}
			int pos=cmd.indexOf('{');
			cmd.remove(pos,cmd.length()-pos);
			cmd.prepend('\\');
			if(LatexParser::refCommands.contains(cmd)){
				currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_REF);
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
			QSet<QString> words;
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
			currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_NORMAL_TEXT);
		}
	}
}
void Texmaker::InsertEnvironmentCompletion() {
	if (!currentEditorView())	return;
	if(mCompleterNeedsUpdate) updateCompleter();
	QDocumentCursor c = currentEditorView()->editor->cursor();
	if(c.hasSelection()){
		currentEditor()->cutBuffer=c.selectedText();
		c.removeSelectedText();
	}
	QString eow=getCommonEOW();
	while (c.columnNumber()>0 && !eow.contains(c.previousChar())) c.movePosition(1,QDocumentCursor::PreviousCharacter);

	static const QString environmentStart = "\\begin{";

	if (!c.line().text().left(c.columnNumber()).endsWith(environmentStart)){
		c.insertText(environmentStart);//remaining part is up to the completion engine
	}

	currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST);
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
		QSet<QString> words;
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
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_NORMAL_TEXT);
	}
}

void Texmaker::InsertTag(QString Entity, int dx, int dy) {
	if (!currentEditorView())	return;
	int curline,curindex;
	currentEditor()->getCursorPosition(curline,curindex);
	currentEditor()->insertText(Entity);
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
		if(item->data(Qt::UserRole+1).isValid()) {
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
	button->setDefaultAction(action);

	QString tagsID = button->property("tagsID").toString();
	int tagCategorySep=tagsID.indexOf("/",5);
	XmlTagsListWidget* tagsWidget = findChild<XmlTagsListWidget*>(tagsID.left(tagCategorySep));
	if (!tagsWidget) return;
	QString code=tagsWidget->tagsFromTagTxt(action->text());
	CodeSnippet(code).insert(currentEditorView()->editor);
	currentEditorView()->editor->setFocus();
}

void Texmaker::callToolButtonAction(){
	QAction *action = qobject_cast<QAction *>(sender());
	QToolButton *button = comboToolButtonFromAction(action);
	REQUIRE(button && button->defaultAction() && button->menu());
	button->setDefaultAction(action);

	QString menuID = button->property("menuID").toString();
	QMenu* menu=configManager.getManagedMenu(menuID);
	if (!menu) return;

	int index = button->menu()->actions().indexOf(action);
	REQUIRE(index >= 0);
	REQUIRE(index < menu->actions().size());
	menu->actions()[index]->trigger();

}

void Texmaker::InsertFromAction() {
	if (!currentEditorView())	return;
	QAction *action = qobject_cast<QAction *>(sender());
	if (action)	{
		if(completer->isVisible())
			completer->close();
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
			//updateStructure(); automatically done
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
	//TODO: move this in tabdialog.h
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
		if ((quickDlg->ui.comboAlignment->currentIndex())==4) al=QString(">{\\centering\\arraybackslash}p{}")+vs;
		if ((quickDlg->ui.comboAlignment->currentIndex())==5) al=QString(">{\\raggedleft\\arraybackslash}p{}")+vs;
		if (quickDlg->ui.checkBox->isChecked()) {
			hs=QString("\\hline ");
			if (quickDlg->ui.checkBoxMargin->isChecked()) hs+="\\rule[-2ex]{0pt}{5.5ex} ";
		}
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
		if (quickDlg->ui.checkBox->isChecked()) tag +=QString("\\hline \n\\end{tabular} ");
		else tag +=QString("\\end{tabular} ");
		InsertTag(tag,0,0);
	}

}

void Texmaker::QuickArray() {
	if (!currentEditorView())	return;
	//TODO: move this in arraydialog class
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

	QFileInfo docInfo=currentEditorView()->document->getFileInfo();

	InsertGraphics *graphicsDlg = new InsertGraphics(this,tr("Insert Graphic"));
	graphicsDlg->setDir(docInfo.absolutePath());
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
		if(graphicsDlg->ui.cbCentering->isChecked()) insert.append("\\centering\n");
		if(graphicsDlg->ui.cbPosition->currentIndex()==0){
			if(!graphicsDlg->ui.leCaption->text().isEmpty()) insert.append("\\caption{"+graphicsDlg->ui.leCaption->text()+"}\n");
			if(!graphicsDlg->ui.leLabel->text().isEmpty()) insert.append("\\label{"+graphicsDlg->ui.leLabel->text()+"}\n");
		}
		insert.append("\\includegraphics");
		if(!graphicsDlg->ui.leScale->text().isEmpty()) insert.append("["+graphicsDlg->ui.leScale->text()+"]");
		QString fname=graphicsDlg->ui.lineEdit->text();
		QFileInfo info(fname);
		if(info.isAbsolute()){

			QString path=docInfo.absolutePath();
			QString filepath=info.absolutePath();
			if(filepath.startsWith(path)){
				filepath=filepath.mid(path.length()+1);
				if(!filepath.isEmpty())
					filepath="./"+filepath+"/";
				fname=filepath+info.completeBaseName();
			}
		}
		info.setFile(fname);
		fname=info.path();
		if(!fname.isEmpty()) fname+="/"+info.completeBaseName();
#ifdef Q_OS_WIN
		//restore native separators if original filename contains native separators
		if(graphicsDlg->ui.lineEdit->text().contains(QDir::separator())){
			fname=QDir::toNativeSeparators(fname);
		}
#endif
		insert.append("{"+fname+"}\n");
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
		if (ltDlg->ui.comboBoxEncoding->currentText().startsWith("utf8x")) tag+=QString(" \\usepackage{ucs}");
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
		currentEditor()->insertText(startDlg->getNewDocumentText());
		QTextCodec* codec = LatexParser::QTextCodecForLatexName(startDlg->document_encoding);
		if (codec && codec != currentEditor()->document()->codec()){
			currentEditor()->document()->setCodec(codec);
			UpdateCaption();
		}
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
	if (!currentEditorView()) return;
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	int id = action->data().toInt();
	const QString& userTag=configManager.completerConfig->userMacro.value(id,Macro()).tag;
	currentEditorView()->insertMacro(userTag);
}

void Texmaker::EditUserMenu() {
	UserMenuDialog *umDlg = new UserMenuDialog(this,tr("Edit User &Tags"),m_languages);
	foreach (const Macro& m, configManager.completerConfig->userMacro) {
		if(m.name=="TMX:Replace Quote Open" || m.name=="TMX:Replace Quote Close")
			continue;
		umDlg->names << m.name;
		umDlg->tags << m.tag;
		umDlg->abbrevs << m.abbrev;
		umDlg->triggers << m.trigger;
	}
	umDlg->init();
	if (umDlg->exec()) {
		configManager.completerConfig->userMacro.clear();
		Q_ASSERT(umDlg->names.size() == umDlg->tags.size());
		Q_ASSERT(umDlg->names.size() == umDlg->abbrevs.size());
		Q_ASSERT(umDlg->names.size() == umDlg->triggers.size());
		for (int i=0;i<umDlg->names.size();i++)
			configManager.completerConfig->userMacro.append(Macro(umDlg->names[i], umDlg->tags[i], umDlg->abbrevs[i], umDlg->triggers[i]));
		configManager.updateUserMacroMenu();
		completer->updateAbbreviations();
	}
	delete umDlg; //must be deleted before the formatscheme is deleted
}

void Texmaker::InsertRef() {
	//updateStructure();

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
	//updateStructure();
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
void Texmaker::runCommand(BuildManager::LatexCommand cmd, RunCommandFlags flags){
	switch (cmd){
	case BuildManager::CMD_LATEX:
		flags = flags | RCF_VIEW_LOG;
		break;
	case BuildManager::CMD_PDFLATEX:
		flags = flags | RCF_VIEW_LOG | RCF_CHECK_PDF_LOCK;
		break;
	default:
		break;
	}
	bool startViewer = cmd==BuildManager::CMD_VIEWDVI || cmd==BuildManager::CMD_VIEWPS || cmd==BuildManager::CMD_VIEWPDF;
	if (startViewer && configManager.singleViewerInstance)
		flags |= RCF_SINGLE_INSTANCE;
	runCommand(buildManager.getLatexCommand(cmd),flags);
}
void Texmaker::runCommand(const QString& commandline, RunCommandFlags flags, QString *buffer) {
	QString finame=documents.getTemporaryCompileFileName();
	if (finame=="" && !(flags&RCF_NO_DOCUMENT)) {
		QMessageBox::warning(this,tr("Error"),tr("Can't detect the file name"));
		return;
	}

	if (commandline.trimmed().isEmpty()) {
		ERRPROCESS=true;
		outputView->insertMessageLine("Error : no command given \n");
		return;
	}

	if (!(flags & RCF_IS_RERUN_CALL)) {
		if (commandline.trimmed().startsWith(BuildManager::TMX_INTERNAL_PDF_VIEWER)) {
#ifndef NO_POPPLER_PREVIEW
			QString pdfFile = BuildManager::parseExtendedCommandLine("?am.pdf", finame);
			QString externalViewer = buildManager.getLatexCommand(BuildManager::CMD_VIEWPDF);
			if (externalViewer.startsWith(BuildManager::TMX_INTERNAL_PDF_VIEWER)) {
				externalViewer.remove(0,BuildManager::TMX_INTERNAL_PDF_VIEWER.length());
				if (externalViewer.startsWith('/')) externalViewer.remove(0,1);
			}
			externalViewer = BuildManager::parseExtendedCommandLine(externalViewer, finame, getCurrentFileName(),currentEditorView()->editor->cursor().lineNumber()+1);
			if (PDFDocument::documentList().isEmpty()) {
				newPdfPreviewer();
				Q_ASSERT(!PDFDocument::documentList().isEmpty());
			}
			foreach (PDFDocument* viewer, PDFDocument::documentList()) {
				viewer->loadFile(pdfFile,externalViewer);
				int pg=viewer->syncFromSource(getCurrentFileName(), currentEditorView()->editor->cursor().lineNumber(), true);
				viewer->fillRenderCache(pg);
			}
#else
			QMessageBox::critical(this, "TexMakerX", tr("You have called the command to open the internal pdf viewer.\nHowever, you are using a version of TexMakerX that was compiled without the internal pdf viewer."), QMessageBox::Ok);
#endif
			return;
		}


		// check for locking of pdf
		if((flags & RCF_CHECK_PDF_LOCK) && configManager.autoCheckinAfterSave){
			QFileInfo fi(finame);
			QString basename=fi.baseName();
			QString path=fi.path();
			fi.setFile(path+"/"+basename+".pdf");
			if(fi.exists() && !fi.isWritable()){
				//pdf not writeable, needs locking ?
				svnLock(fi.filePath());
			}
		}
	}

	if (configManager.rerunLatex > 0 && (flags & RCF_VIEW_LOG)) {
		if (!(flags & RCF_IS_RERUN_CALL)) {
			remainingReRunCount = configManager.rerunLatex;
			rerunCommand = commandline;
			rerunFlags = flags | RCF_IS_RERUN_CALL;
		} else
			remainingReRunCount--;
	} else
		remainingReRunCount = 0;


	ProcessX* procX = buildManager.newProcess(commandline,finame,getCurrentFileName(),currentEditorView()->editor->cursor().lineNumber()+1,flags & RCF_SINGLE_INSTANCE);

	if (!procX) return; //a singleInstance that is already running

	procX->setBuffer(buffer);

	connect(procX, SIGNAL(readyReadStandardError()),this, SLOT(readFromStderr()));
	if (procX->showStdout())
		procX->setShowStdout((configManager.showStdoutOption == 2) || (RCF_SHOW_STDOUT & flags));
	if (procX->showStdout() || buffer)
		connect(procX, SIGNAL(readyReadStandardOutput()),this, SLOT(readFromStdoutput()));
	connect(procX, SIGNAL(finished(int)),this, SLOT(SlotEndProcess(int)));

	if (flags & RCF_VIEW_LOG) ClearMarkers();
	outputView->resetMessages();

	if (flags & RCF_VIEW_LOG && configManager.showLogAfterCompiling)
		connect(procX,SIGNAL(finished(int)),this,SLOT(ViewLogOrReRun()));

	//OutputTextEdit->insertLine(commandline+"\n");
	FINPROCESS = false;
	procX->startCommand();
	if (!procX->waitForStarted(1000)) {
		ERRPROCESS=true;
		return;
	}

	if (flags & RCF_WAIT_FOR_FINISHED) {
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
		runCommand(BuildManager::CMD_USER_PRECOMPILE, RCF_WAIT_FOR_FINISHED);
	}
	if (documents.bibTeXFilesModified && configManager.runLaTeXBibTeXLaTeX) {
		ERRPROCESS=false;
		stat2->setText(QString(" %1 ").arg(tr("LaTeX","Status")));
		runCommand(BuildManager::CMD_LATEX, RCF_WAIT_FOR_FINISHED);
		if (ERRPROCESS && !LogExists()) {
			QMessageBox::warning(this,tr("Error"),tr("Could not start LaTeX."));
			return;
		}
		if (NoLatexErrors()) {
			ERRPROCESS=false;
			stat2->setText(QString(" %1 ").arg(tr("BibTeX")));
			runCommand(BuildManager::CMD_BIBTEX,RCF_WAIT_FOR_FINISHED);
			if (!ERRPROCESS) {
				stat2->setText(QString(" %1 ").arg(tr("LaTeX","Status")));
				runCommand(BuildManager::CMD_LATEX,RCF_WAIT_FOR_FINISHED);
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
	if (procX->showStdout())
		outputView->insertMessageLine(t+"\n");
}

void Texmaker::SlotEndProcess(int err) {
	ProcessX* procX = qobject_cast<ProcessX*> (sender());
	FINPROCESS=true;
	if (err) ERRPROCESS=true;
	stat2->setText(QString(" %1 ").arg(tr("Ready")));
	if(!procX) return;
	QString *buffer=procX->getBuffer();
	if(buffer){
		QByteArray result=procX->readAllStandardOutput();
		QString t=QString(result).trimmed();
		buffer->append(t);
	}
}

void Texmaker::processNotification(const QString& message){
	outputView->insertMessageLine(message+"\n");
}

void Texmaker::QuickBuild() {
	fileSaveAll(buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ALWAYS, buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ONLY_CURRENT_OR_NAMED);
	if (documents.getTemporaryCompileFileName()=="") {
		if (buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ONLY_NAMED && currentEditorView()){
			QString tmpName = buildManager.createTemporaryFileName();
			currentEditor()->saveCopy(tmpName);
			currentEditorView()->document->setTemporaryFileName(tmpName);
		} else {
			QMessageBox::warning(this,tr("Error"),tr("Can't detect the file name.\nYou have to save a document before you can compile it."));
			return;
		}
	}

	RunPreCompileCommand();
	stat2->setText(QString(" %1 ").arg(tr("Quick Build")));
	ERRPROCESS=false;

	QList<BuildManager::LatexCommand> cmddList;
	if (buildManager.quickmode >= 1 && buildManager.quickmode <= BuildManager::getQuickBuildCommandCount())
		cmddList = BuildManager::getQuickBuildCommands(buildManager.quickmode);

	if (!cmddList.isEmpty()) {
		for (int i=0; i < cmddList.size() - 1; i++) { //skip last command
			BuildManager::LatexCommand cmd = cmddList[i];
			stat2->setText(QString(" %1 ").arg(BuildManager::commandDisplayName(cmd)));
			runCommand(cmd, RCF_WAIT_FOR_FINISHED);
			if (cmd == BuildManager::CMD_LATEX || cmd == BuildManager::CMD_PDFLATEX) {
				if (ERRPROCESS && !LogExists()) {
					QMessageBox::warning(this,tr("Error"),tr("Could not start %1.").arg(BuildManager::commandDisplayName(cmd)));
					return;
				}
				if (!NoLatexErrors()) return;
			}
			if (ERRPROCESS) return;
		}
		runCommand(cmddList.last(), 0);
		return;
	}

	REQUIRE(buildManager.quickmode == 8); //user quick mode

	runCommandList(buildManager.getLatexCommand(BuildManager::CMD_USER_QUICK).split("|"),0);
	ViewLog();
}

void Texmaker::runCommandList(const QStringList& commandList, const RunCommandFlags& additionalFlags){
	ERRPROCESS = false;
	for (int i = 0; i < commandList.size(); ++i) {
		if (commandList.at(i).trimmed().isEmpty()) continue;

		bool isLatex = commandList.at(i).contains("latex") || commandList.at(i)==buildManager.getLatexCommand(BuildManager::CMD_LATEX) || commandList.at(i)==buildManager.getLatexCommand(BuildManager::CMD_PDFLATEX);
		bool isPdfLatex = commandList.at(i).contains("pdflatex") || commandList.at(i)==buildManager.getLatexCommand(BuildManager::CMD_PDFLATEX);
		RunCommandFlags flags = additionalFlags;
		if (isLatex) flags |= RCF_VIEW_LOG;
		if (isPdfLatex) flags |= RCF_CHECK_PDF_LOCK;
		if (isLatex || i != commandList.size()-1) flags |= RCF_WAIT_FOR_FINISHED;
		if (!ERRPROCESS) runCommand(commandList.at(i),flags);
		else break;
	}
}

void Texmaker::commandFromAction(){
	QAction* act = qobject_cast<QAction*>(sender());
	if (!act) return;
	fileSaveAll(buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ALWAYS, buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ONLY_CURRENT_OR_NAMED);
	if (documents.getTemporaryCompileFileName()=="") {
		if (buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ONLY_NAMED && currentEditorView()){
			QString tmpName = buildManager.createTemporaryFileName();
			currentEditor()->saveCopy(tmpName);
			currentEditorView()->document->setTemporaryFileName(tmpName);
		} else {
			QMessageBox::warning(this,tr("Error"),tr("Can't detect the file name.\nYou have to save a document before you can compile it."));
			return;
		}
	}
	BuildManager::LatexCommand cmd=(BuildManager::LatexCommand) act->data().toInt();
	bool compileLatex=(cmd==BuildManager::CMD_LATEX || cmd==BuildManager::CMD_PDFLATEX);
	if (compileLatex)
		RunPreCompileCommand();
	QString status=act->text();
	status.remove(QChar('&'));
	stat2->setText(QString(" %1 ").arg(status));
	runCommand(cmd, 0);
}

void Texmaker::CleanAll() {
	//QString finame=documents.getCompileFileName();
	QStringList finames;
	LatexEditorView* edView=currentEditorView();

	if(edView && edView->document){
		// determine from which docs data needs to be collected
		QList<LatexDocument*> docs=edView->document->getListOfDocs();
		// collect user commands and references
		foreach(const LatexDocument* doc,docs){
			if(!doc->getFileName().isEmpty())
				finames << doc->getFileName();
		}
	}

	if (finames.isEmpty()) {
		QMessageBox::warning(this,tr("Error"),tr("Can't detect the file name"));
		return;
	}
	QString extensionStr=".log,.aux,.dvi,.lof,.lot,.bit,.idx,.glo,.bbl,.ilg,.toc,.ind,.out,.blg";
	int query =QMessageBox::warning(this, "TexMakerX", tr("Delete the output files generated by LaTeX?")+QString("\n(%1)").arg(extensionStr),tr("Delete Files"), tr("Cancel"));
	if (query==0) {
		//fileSave();
		stat2->setText(QString(" %1 ").arg(tr("Clean")));
		foreach(const QString finame,finames){
			QFileInfo fi(finame);
			QString basename=fi.absolutePath()+"/"+fi.completeBaseName();
			QStringList extension=extensionStr.split(",");
			foreach(const QString ext, extension)
				QFile::remove(basename+ext);
		}
		stat2->setText(QString(" %1 ").arg(tr("Ready")));
	}
}

void Texmaker::UserTool() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	QString cmd=configManager.userToolCommand.value(action->data().toInt(),"");
	if (cmd.isEmpty()) return;
	fileSaveAll(buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ALWAYS, buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ONLY_CURRENT_OR_NAMED);
	if (documents.getTemporaryCompileFileName()=="") {
		if (buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ONLY_NAMED && currentEditorView()){
			QString tmpName = buildManager.createTemporaryFileName();
			currentEditor()->saveCopy(tmpName);
			currentEditorView()->document->setTemporaryFileName(tmpName);
		} else {
			QMessageBox::warning(this,tr("Error"),tr("Can't detect the file name.\nYou have to save a document before you can compile it."));
			return;
		}
	}

	RunCommandFlags flags;
	if (configManager.showStdoutOption >= 1) flags |= RCF_SHOW_STDOUT;
	runCommandList(cmd.split("|"), flags);
}


void Texmaker::EditUserTool() {
	UserToolDialog utDlg(this,tr("Edit User &Commands"), &buildManager);
	utDlg.Name = configManager.userToolMenuName;
	utDlg.Tool = configManager.userToolCommand;
	utDlg.init();
	if (utDlg.exec()) {configManager.updateRecentFiles();
		configManager.userToolMenuName = utDlg.Name;
		configManager.userToolCommand = utDlg.Tool;
		configManager.updateUserToolMenu();
	}
}

void Texmaker::WebPublish() {
	if (!currentEditorView()) {
		QMessageBox::information(this,"TexMakerX",tr("No document open"),0);
		return;
	}
	if (!currentEditorView()->editor->getFileCodec()) return;
	fileSave();
	QString finame=documents.getCompileFileName();

	WebPublishDialog *ttwpDlg = new WebPublishDialog(this,configManager.webPublishDialogConfig, &buildManager,
								currentEditorView()->editor->getFileCodec());
	ttwpDlg->ui.inputfileEdit->setText(finame);
	ttwpDlg->exec();
	delete ttwpDlg;
}

void Texmaker::WebPublishSource(){
	if (!currentEditor()) return;
	QDocumentCursor cur = currentEditor()->cursor();
	QString	html = currentEditor()->document()->exportAsHtml(cur.hasSelection()?cur:QDocumentCursor(), true);
	fileNew(getCurrentFileName()+".html");
	currentEditor()->insertText(html);
	/*QLabel* htmll = new QLabel(html, this);
	htmll->show();
	htmll->resize(300,300);*/
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
	QString finame=documents.getTemporaryCompileFileName();
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
	QString finame=documents.getTemporaryCompileFileName();
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
		outputView->loadLogFile(logname,documents.getTemporaryCompileFileName(),overrideFileName);
		//display errors in editor
		DisplayLatexError();
		if (outputView->getLogModel()->found(LT_ERROR))
			if (!gotoNearLogEntry(LT_ERROR,false,tr("No LaTeX errors detected !"))) //jump to next error
				gotoNearLogEntry(LT_ERROR,true,tr("No LaTeX errors detected !")); //prev error

	} else {
		QMessageBox::warning(this,tr("Error"),tr("Log File not found !"));
	}
}

void Texmaker::ViewLogOrReRun(){
	ViewLog();
	if (NoLatexErrors() && remainingReRunCount > 0 && outputView->getLogModel()->existsReRunWarning())
		runCommand(rerunCommand, rerunFlags);
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
			edView=getEditorViewFromFileName(logModel->at(i).file, true);
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

bool Texmaker::gotoNearLogEntry(int lt, bool backward, QString notFoundMessage) {
	if (!outputView->logPresent()) {
		ViewLog();
	}
	if (outputView->logPresent()) {
		if (outputView->getLogModel()->found((LogType) lt)){
			outputView->showErrorListOrLog(); //always show log if a mark of this type exists (even if is in another file)
			return gotoMark(backward, outputView->getLogModel()->markID((LogType) lt));
		} else {
			QMessageBox::information(this,"TexMakerX",notFoundMessage);
			//OutputTextEdit->setCursorPosition(0 , 0);
		}
	}
	return false;
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
	if (latexHelp=="")
		QMessageBox::warning(this,tr("Error"),tr("File not found"));
	else if (!QDesktopServices::openUrl("file:///"+latexHelp))
		QMessageBox::warning(this,tr("Error"),tr("Could not open browser"));
}

void Texmaker::UserManualHelp() {
	QString locale = QString(QLocale::system().name()).left(2);
	if (locale.length() < 2 || locale!="fr") locale = "en";
	QString latexHelp=findResourceFile("usermanual_"+locale+".html");
	if (latexHelp=="")
		QMessageBox::warning(this,tr("Error"),tr("File not found"));
	else if (!QDesktopServices::openUrl("file:///"+latexHelp))
		QMessageBox::warning(this,tr("Error"),tr("Could not open browser"));
}

void Texmaker::HelpAbout() {
	AboutDialog *abDlg = new AboutDialog(0); //if parent!=0 the focus is wrong after pdf viewer about call
	abDlg->exec();
	delete abDlg;
}
////////////// OPTIONS //////////////////////////////////////
void Texmaker::GeneralOptions() {
	QMap<QString,QVariant> oldCustomEnvironments = configManager.customEnvironments;
	bool oldModernStyle = modernStyle;
	bool oldSystemTheme = useSystemTheme;
	autosaveTimer.stop();
	m_formats->modified = false;
	bool realtimeChecking=configManager.editorConfig->realtimeChecking;
	bool inlineSpellChecking=configManager.editorConfig->inlineSpellChecking;
	bool inlineCitationChecking=configManager.editorConfig->inlineCitationChecking;
	bool inlineReferenceChecking=configManager.editorConfig->inlineReferenceChecking;
	bool inlineSyntaxChecking=configManager.editorConfig->inlineSyntaxChecking;
	QStringList loadFiles=configManager.completerConfig->getLoadedFiles();
	if (configManager.execConfigDialog()) {
		mainSpeller->loadDictionary(configManager.spell_dic,configManager.configFileNameBase);
		// refresh quick language selection combobox
		QFontMetrics fontMetrics(spellToolBar->font());
		QStringList list;
		QDir fic=QFileInfo(configManager.spell_dic).absoluteDir();
		if (fic.exists() && fic.isReadable())
			list << fic.entryList(QStringList("*.dic"),QDir::Files,QDir::Name);
		createComboToolButton(spellToolBar,list,comboSpell->height(),fontMetrics,this,SLOT(SpellingLanguageChanged()),QFileInfo(configManager.spell_dic).fileName(),comboSpell);

		if (configManager.autodetectLoadedFile) QDocument::setDefaultCodec(0);
		else QDocument::setDefaultCodec(configManager.newFileEncoding);

		ThesaurusDialog::prepareDatabase(configManager.thesaurus_database);

		//update highlighting ???
		bool updateHighlighting=(inlineSpellChecking!=configManager.editorConfig->inlineSpellChecking);
		updateHighlighting|=(inlineCitationChecking!=configManager.editorConfig->inlineCitationChecking);
		updateHighlighting|=(inlineReferenceChecking!=configManager.editorConfig->inlineReferenceChecking);
		updateHighlighting|=(inlineSyntaxChecking!=configManager.editorConfig->inlineSyntaxChecking);
		updateHighlighting|=(realtimeChecking!=configManager.editorConfig->realtimeChecking);
		// check for change in load completion files
		QStringList newLoadedFiles=configManager.completerConfig->getLoadedFiles();
		foreach(const QString elem,newLoadedFiles){
			if(loadFiles.removeAll(elem)==0)
				updateHighlighting=true;
			if(updateHighlighting)
				break;
		}
		if(!loadFiles.isEmpty())
			updateHighlighting=true;

		buildManager.clearPreviewPreambleCache();//possible changed latex command / preview behaviour

		if (currentEditorView()) {
			for (int i=0; i<EditorView->count();i++) {
				LatexEditorView* edView=qobject_cast<LatexEditorView*>(EditorView->widget(i));
				if (edView) {
					edView->updateSettings();
					if(updateHighlighting){
						if(configManager.editorConfig->realtimeChecking){
							edView->updateLtxCommands();
							edView->documentContentChanged(0,edView->document->lines());
						}else{
							edView->clearOverlays();
						}
					}
				}
			}
			if (m_formats->modified)
				QDocument::setFont(QDocument::font());
			UpdateCaption();
		}
		//custom toolbar
		setupToolBars();

		// custom evironments
		bool customEnvironmentChanged = configManager.customEnvironments != oldCustomEnvironments;
		QLanguageDefinition *oldLaTeX = 0, *newLaTeX = 0;
		if (customEnvironmentChanged){
			QLanguageFactory::LangData m_lang=m_languages->languageData("(La-)TeX");

			oldLaTeX = m_lang.d;
			Q_ASSERT(oldLaTeX);

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

			newLaTeX = m_lang.d;
			Q_ASSERT(oldLaTeX != newLaTeX);
		}

		//completion
		completionBaseCommandsUpdated=true;
		completerNeedsUpdate();

		//update changed line mark colors
		QList<QLineMarkType> &marks = QLineMarksInfoCenter::instance()->markTypes();
		for (int i=0;i<marks.size();i++)
			if (m_formats->format("line:"+marks[i].id).background.isValid())
				marks[i].color = m_formats->format("line:"+marks[i].id).background;
		else
			marks[i].color = marks[i].defaultColor;

		// update all docuemnts views as spellcheck may be different
		QEditor::setEditOperations(configManager.editorKeys,true);
		for (int i=0; i<EditorView->count();i++) {
			LatexEditorView* edView=qobject_cast<LatexEditorView*>(EditorView->widget(i));
			if (edView) {
				QEditor* ed = edView->editor;
				//if (customEnvironmentChanged) ed->highlight();
				if (ed->languageDefinition() == oldLaTeX) {
					ed->setLanguageDefinition(newLaTeX);
					ed->highlight();
				} else {
					ed->document()->markFormatCacheDirty();
					ed->update();
				}
			}
		}

		if (oldModernStyle != modernStyle || oldSystemTheme != useSystemTheme) {
			setupMenus();
			setupDockWidgets();
		}
	}
	if(configManager.autosaveEveryMinutes>0){
		autosaveTimer.start(configManager.autosaveEveryMinutes*1000*60);
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
	foreach(const QString fileToLoad,filesToLoad){
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
			QString result=TestManager::execute(allTests?TestManager::TL_ALL:TestManager::TL_FAST, currentEditorView(),currentEditorView()->codeeditor,currentEditorView()->editor);
			//currentEditorView()->editor->document()->setText(result);
			currentEditorView()->editor->setText(result);
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
			translations << "QT_TRANSLATE_NOOP(\"QFormatConfig\", \"normal\"),";
			for (int i=0;i<configManager.managedToolBars.size();i++)
				translations << "QT_TRANSLATE_NOOP(\"Texmaker\",\""+configManager.managedToolBars[i].name+"\"),";
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
			QMessageBox::warning(this,tr("Error"),tr("You have to save the file before switching to master mode!"));
			return;
		}
		documents.setMasterDocument(currentEditorView()->document);
	}
	completerNeedsUpdate();
}
////////////////// VIEW ////////////////

void Texmaker::gotoNextDocument() {
	if (EditorView->count() <= 1) return;
	int cPage = EditorView->currentIndex() + 1;
	if (cPage >= EditorView->count()) EditorView->setCurrentIndex(0);
	else EditorView->setCurrentIndex(cPage);
}

void Texmaker::gotoPrevDocument() {
	if (EditorView->count() <= 1) return;
	int cPage = EditorView->currentIndex() - 1;
	if (cPage < 0) EditorView->setCurrentIndex(EditorView->count() - 1);
	else EditorView->setCurrentIndex(cPage);
}
void Texmaker::gotoOpenDocument(){
	QAction* act = qobject_cast<QAction*>(sender());
	REQUIRE(act);
	int doc = act->data().toInt();
	EditorView->setCurrentIndex(doc);
}
void Texmaker::updateOpenDocumentMenu(bool localChange){
	QEditor* ed = currentEditor();
	//if (!ed) return;
	if (localChange) {
		QString id = "doc"+QString::number(EditorView->currentIndex());
		QMenu* menu = configManager.getManagedMenu("main/view/documents");
		configManager.newManagedAction(menu, id, ed->fileName().isEmpty() ? tr("untitled") : ed->name(), SLOT(gotoOpenDocument()));
		return;
	}
	QStringList sl;
	for (int i=0; i<EditorView->count(); i++){
		ed = qobject_cast<LatexEditorView*>(EditorView->widget(i))->editor;
		REQUIRE(ed);
		sl << (ed->fileName().isEmpty() ? tr("untitled") : ed->name());
	}
	configManager.updateListMenu("main/view/documents", sl, "doc", false, SLOT(gotoOpenDocument()), 0, false, 0);
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
	if (unicodeInsertionDialog) {
		unicodeInsertionDialog->close();
		return;
	}
	if (completer && completer->isVisible() && completer->close())
		return;
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
	if (outputView->isVisible() && configManager.useEscForClosingLog) {
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

void Texmaker::viewCollapseBlock() {
	if (!currentEditorView()) return;
	currentEditorView()->foldBlockAt(false,currentEditorView()->editor->cursor().lineNumber());
}
void Texmaker::viewExpandBlock() {
	if (!currentEditorView()) return;
	currentEditorView()->foldBlockAt(true,currentEditorView()->editor->cursor().lineNumber());
}

void Texmaker::newPdfPreviewer(){
#ifndef NO_POPPLER_PREVIEW
	PDFDocument* pdfviewerWindow=new PDFDocument(configManager.pdfDocumentConfig);
	connect(pdfviewerWindow, SIGNAL(triggeredAbout()), SLOT(HelpAbout()));
	connect(pdfviewerWindow, SIGNAL(triggeredManual()), SLOT(UserManualHelp()));
	connect(pdfviewerWindow, SIGNAL(triggeredQuit()), SLOT(fileExit()));
	connect(pdfviewerWindow, SIGNAL(triggeredConfigure()), SLOT(GeneralOptions()));
	connect(pdfviewerWindow, SIGNAL(triggeredQuickBuild()), SLOT(QuickBuild()));
	connect(pdfviewerWindow, SIGNAL(syncSource(const QString&, int, bool)), SLOT(syncFromViewer(const QString &, int, bool)));
	connect(pdfviewerWindow, SIGNAL(runCommand(const QString&)), SLOT(runCommand(const QString&)));
	connect(pdfviewerWindow, SIGNAL(triggeredClone()), SLOT(newPdfPreviewer()));

	PDFDocument* from = qobject_cast<PDFDocument*>(sender());
	if (from) {
		pdfviewerWindow->loadFile(from->fileName(), from->externalViewer(), true);
		pdfviewerWindow->goToPage(from->widget()->getCurrentPageIndex());
	}//load file before enabling sync or it will jump to the first page

	foreach (PDFDocument* doc, PDFDocument::documentList()) {
		if (doc == pdfviewerWindow) continue;
		connect(doc, SIGNAL(syncView(QString,QString,int)), pdfviewerWindow, SLOT(syncFromView(QString,QString,int)));
		connect(pdfviewerWindow, SIGNAL(syncView(QString,QString,int)), doc, SLOT(syncFromView(QString,QString,int)));
	}
#endif
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

//*********************************
void Texmaker::dragEnterEvent(QDragEnterEvent *event) {
	if (event->mimeData()->hasFormat("text/uri-list")) event->acceptProposedAction();
}

void Texmaker::dropEvent(QDropEvent *event) {
	QRegExp rx("file://(.*)");
	QList<QUrl> uris=event->mimeData()->urls();
	QString uri;
	for (int i = 0; i < uris.size(); ++i) {
		uri=uris.at(i).toString();
		//QMessageBox::information(0,uri,uri,0);
		if (rx.exactMatch(uri)) load(rx.cap(1));
	}
	event->acceptProposedAction();
	raise();
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
		//check whether it was loaded as mosteUsed ...
		for(int i=0;i<symbolMostused.count();i++){
			QTableWidgetItem *elem=symbolMostused.at(i);
			if(elem->data(Qt::UserRole+2)==item->data(Qt::UserRole+2)){
				index=i;
				item->setData(Qt::UserRole+1,QVariant::fromValue(elem));
				int cnt=elem->data(Qt::UserRole).toInt();
				elem->setData(Qt::UserRole,cnt+1);
				elem->setData(Qt::UserRole+3,QVariant::fromValue(item));//reference to original item for removing later
				item=elem;
				break;
			}
		}
		if(index<0){
			QTableWidgetItem *elem=item->clone();
			item->setData(Qt::UserRole+1,QVariant::fromValue(elem));
			elem->setData(Qt::UserRole+3,QVariant::fromValue(item));//reference to original item for removing later
			symbolMostused.append(elem);
			if(symbolMostused.size()<=12)
				changed=true;
		}
	}
	if(index>-1){
		symbolMostused.removeAt(index);
		while(index>0&&symbolMostused[index-1]->data(Qt::UserRole).toInt()<item->data(Qt::UserRole).toInt()){
			index--;
		}
		symbolMostused.insert(index,item);
		changed=true;
	}
	if(changed) MostUsedSymbolWidget->SetUserPage(symbolMostused);
}

void Texmaker::updateCompleter() {
	QSet<QString> words;

	if (configManager.parseBibTeX) documents.updateBibFiles();

	LatexEditorView* edView=currentEditorView();

	if(edView && edView->document){
		// determine from which docs data needs to be collected
		QList<LatexDocument*> docs=edView->document->getListOfDocs();
		// collect user commands and references
		foreach(const LatexDocument* doc,docs){
			words.unite(doc->userCommandList());
			words.unite(doc->additionalCommandsList());
			foreach(const QString& refCommand, LatexParser::refCommands){
				QString temp=refCommand+"{%1}";
				for (int i=0; i<doc->labelItem().count(); ++i)
					words.insert(temp.arg(doc->labelItem().at(i)));
			}
		}
	}

	//add cite commands from the cwls to LatexParser::citeCommands
	LatexCompleterConfig *conf=configManager.completerConfig;
	QStringList citeCommands=conf->words;
	citeCommands<<words.toList();
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
				words.insert(temp.arg(bibTex.ids[i]));
		}
	}

	completionBaseCommandsUpdated=false;

	completer->setAdditionalWords(words,false);
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
	if (!FileAlreadyOpen(fileName, true))
		if (!load(fileName)) return;
	gotoLine(line);
}

void Texmaker::gotoLogEntryEditorOnly(int logEntryNumber) {
	if (logEntryNumber<0 || logEntryNumber>=outputView->getLogModel()->count()) return;
	QString fileName = outputView->getLogModel()->at(logEntryNumber).file;
	if (!FileAlreadyOpen(fileName, true))
		if (!load(fileName)) return;
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
	if (!currentEditorView()) return false;
	if (backward)
		return gotoLogEntryAt(currentEditorView()->editor->document()->findPreviousMark(id,qMax(0,currentEditorView()->editor->cursor().lineNumber()-1),0));
	else
		return gotoLogEntryAt(currentEditorView()->editor->document()->findNextMark(id,currentEditorView()->editor->cursor().lineNumber()+1));
}

void Texmaker::syncFromViewer(const QString &fileName, int line, bool activate){
	if (!FileAlreadyOpen(fileName, true))
		if (!load(fileName)) return;
	gotoLine(line);
	if (activate) {
		raise();
		show();
		activateWindow();
		if (isMinimized()) showNormal();
	}

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
		if(documents.model->getSingleDocMode()){
			menu.addAction(tr("Show all open documents in this tree"), this, SLOT(latexModelViewMode()));
		}else{
			menu.addAction(tr("Show only current document in this tree"), this, SLOT(latexModelViewMode()));
		}
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
		currentEditor()->insertText(entry->title);
	} else {
		name.remove(0,name.indexOf("\\"));
		name.chop(name.length()-name.indexOf("{"));
		currentEditor()->insertText(name+"{"+entry->title+"}");
	}
}

void Texmaker::previewLatex(){
	if (!currentEditorView()) return;
	// get selection
	QDocumentCursor c = currentEditorView()->editor->cursor();
	QDocumentCursor previewc;
	if (c.hasSelection()) {
		previewc = c; //X o riginalText = c.selectedText();
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
		previewc = currentEditor()->document()->cursor(c.lineNumber(), first.offset, c.lineNumber(), last.offset+last.length);
		//XoriginalText=l.text().mid(first.offset,last.offset+last.length-first.offset);
		//QMessageBox::information(0,originalText,originalText,0);
	}
	if (!previewc.hasSelection()) return;

	showPreview(previewc,true);

}
void Texmaker::previewAvailable(const QString& imageFile, const QString& /*text*/, int line){
	if (configManager.previewMode == ConfigManager::PM_BOTH ||
	    configManager.previewMode == ConfigManager::PM_PANEL||
	    (configManager.previewMode == ConfigManager::PM_TOOLTIP_AS_FALLBACK && outputView->isPreviewPanelVisible())) {
		outputView->showPreview();
		outputView->previewLatex(QPixmap(imageFile));
	}
	if (configManager.previewMode == ConfigManager::PM_BOTH ||
	    configManager.previewMode == ConfigManager::PM_TOOLTIP||
	    previewEquation||
	    (configManager.previewMode == ConfigManager::PM_TOOLTIP_AS_FALLBACK && !outputView->isPreviewPanelVisible()) ||
	    (line < 0)) {
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
	if (configManager.previewMode == ConfigManager::PM_INLINE && line >= 0){
		if (line >= currentEditor()->document()->lines())
			line = currentEditor()->document()->lines()-1;
		currentEditor()->document()->setForceLineWrapCalculation(true);
		currentEditor()->document()->line(line).setCookie(42, QVariant::fromValue<QPixmap>(QPixmap(imageFile)));
		currentEditor()->document()->adjustWidth(line);

	}
	previewEquation=false;
}

void Texmaker::clearPreview(){
	QEditor* edit = currentEditor();
	if (!edit) return;
	int i,t;
	if (edit->cursor().hasSelection()) {
		i = edit->cursor().selectionStart().lineNumber();
		t = edit->cursor().selectionEnd().lineNumber();
	} else {
		i = edit->cursor().lineNumber();
		t = i;
	}
	for (; i<=t; i++){
		edit->document()->line(i).removeCookie(42);
		edit->document()->adjustWidth(i);
		for (int j=currentEditorView()->autoPreviewCursor.size()-1;j>=0;j--)
			if (currentEditorView()->autoPreviewCursor[j].lineNumber() == i)
				currentEditorView()->autoPreviewCursor.removeAt(j);
	}
}

void Texmaker::showPreview(const QString& text){
	LatexEditorView* edView=getEditorViewFromFileName(documents.getCompileFileName()); //todo: temporary compi
	if (!edView) return;
	int m_endingLine=edView->editor->document()->findLineContaining("\\begin{document}",0,Qt::CaseSensitive);
	if (m_endingLine<0) return; // can't create header
	QStringList header;
	for (int l=0; l<m_endingLine; l++)
		header << edView->editor->document()->line(l).text();
	header << "\\pagestyle{empty}";// << "\\begin{document}";
	previewEquation=true;
	buildManager.preview(header.join("\n"), text, -1, documents.getCompileFileName(), edView->editor->document()->codec());
}

void Texmaker::showPreview(const QDocumentCursor& previewc){
	if (previewQueueOwner != currentEditorView())
		previewQueue.clear();
	previewQueueOwner = currentEditorView();
	previewQueue.insert(previewc.lineNumber());
	QTimer::singleShot(qMax(40,configManager.autoPreviewDelay),this, SLOT(showPreviewQueue())); //slow down or it could create thousands of images
}

void Texmaker::showPreview(const QDocumentCursor& previewc, bool addToList){
	REQUIRE(currentEditor());
	REQUIRE(previewc.document() == currentEditor()->document());

	QString originalText = previewc.selectedText();
	if (originalText=="") return;
	// get document definitions
	//preliminary code ...
	LatexDocument *doc=documents.getMasterDocumentForDoc();
	LatexEditorView* edView=(doc && doc->getEditorView())?doc->getEditorView():currentEditorView();
	if (!edView) return;
	int m_endingLine=edView->editor->document()->findLineContaining("\\begin{document}",0,Qt::CaseSensitive);
	if (m_endingLine<0) return; // can't create header
	QStringList header;
	for (int l=0; l<m_endingLine; l++)
		header << edView->editor->document()->line(l).text();
	header << "\\pagestyle{empty}";// << "\\begin{document}";
	buildManager.preview(header.join("\n"), originalText, previewc.selectionEnd().lineNumber(),  documents.getCompileFileName(), edView->editor->document()->codec());

	if (!addToList || previewc.lineNumber() != previewc.anchorLineNumber())
		return;
	if (configManager.autoPreview == ConfigManager::AP_PREVIOUSLY) {
		QList<QDocumentCursor> & clist = currentEditorView()->autoPreviewCursor;
		for (int i=clist.size()-1;i>=0;i--)
			if (clist[i].lineNumber() == previewc.lineNumber() || clist[i].lineNumber() != clist[i].anchorLineNumber())
				clist.removeAt(i);
		QDocumentCursor c = previewc;
		c.setAutoUpdated(true);
		currentEditorView()->autoPreviewCursor.insert(0,c);
	}
}
void Texmaker::showPreviewQueue(){
	if (previewQueueOwner != currentEditorView()) {
		previewQueue.clear();
		return;
	}
	if (configManager.autoPreview == ConfigManager::AP_NEVER) {
		previewQueueOwner->autoPreviewCursor.clear();
		previewQueue.clear();
		return;
	}
	foreach (const int line, previewQueue)
		foreach (const QDocumentCursor& c, previewQueueOwner->autoPreviewCursor)
			if (c.lineNumber() == line)
				showPreview(c,false);
	previewQueue.clear();
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
		currentEditor()->insertText("\\ref{"+rx.cap(1)+"}");
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
	if(direct || action->text()==tr("Remove")){
		if(!direct){
			if(item->data(Qt::UserRole+3).isValid()){
				QTableWidgetItem *elem=item->data(Qt::UserRole+3).value<QTableWidgetItem*>();
				elem->setData(Qt::UserRole+1,QVariant());
			}
			symbolMostused.removeAll(item);
			delete item;
		}else{
			symbolMostused.clear();
			foreach(QTableWidgetItem* elem,MostUsedSymbolWidget->findItems("*",Qt::MatchWildcard)){
				if(!elem) continue;
				int cnt=elem->data(Qt::UserRole).toInt();
				if(symbolMostused.isEmpty()){
					symbolMostused.append(elem);
				}else {
					int index=0;
					while(index<symbolMostused.size()&&symbolMostused[index]->data(Qt::UserRole).toInt()>cnt){
						index++;
					}
					symbolMostused.insert(index,elem);
				}
			}
		}
	}else{
		for(int i=0;symbolMostused.count();i++){
			QTableWidgetItem* item=symbolMostused.at(i);
			QTableWidgetItem *elem=item->data(Qt::UserRole+3).value<QTableWidgetItem*>();
			elem->setData(Qt::UserRole+1,QVariant());
			delete item;
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

	//remove mirror cursors generated after hover if linenumber has changed
	if(currentEditorView()->document->m_mirrorInLine>-1 && i!=currentEditorView()->document->m_mirrorInLine){
		currentEditorView()->document->m_mirrorInLine=-1;
		currentEditor()->removePlaceHolder(currentEditorView()->document->m_magicPlaceHolder);
		currentEditorView()->document->m_magicPlaceHolder=-1;
	}

	// search line in structure
	if (currentLine==i) return;
	currentLine=i;

	LatexDocumentsModel *model=qobject_cast<LatexDocumentsModel*>(structureTreeView->model());
	if (!model) return; //shouldn't happen

	StructureEntry *newSection=currentEditorView()->document->findSectionForLine(currentLine);

	model->setHighlightedEntry(newSection);
	if(!mDontScrollToItem)
		structureTreeView->scrollTo(model->highlightedEntry());

#ifndef NO_POPPLER_PREVIEW
	foreach (PDFDocument* viewer, PDFDocument::documentList())
		if (viewer->followCursor())
			viewer->syncFromSource(getCurrentFileName(), currentLine, false);
#endif
}

void Texmaker::fileCheckin(QString filename){
	if (!currentEditorView()) return;
	QString fn=filename.isEmpty() ? currentEditor()->fileName() : filename;
	UniversalInputDialog dialog;
	QString text;
	dialog.addTextEdit(&text, tr("commit comment:"));
	bool wholeDirectory;
	dialog.addVariable(&wholeDirectory,tr("check in whole directory ?"));
	if (dialog.exec()==QDialog::Accepted){
		fileSave();
		if(wholeDirectory){
			fn=QFileInfo(fn).absolutePath();
		}
		checkin(fn,text);
	}
}

void Texmaker::fileLockPdf(QString filename){
	if (!currentEditorView()) return;
	QString finame=filename;
	if(finame.isEmpty())
		finame=documents.getTemporaryCompileFileName();
	QFileInfo fi(finame);
	QString basename=fi.baseName();
	QString path=fi.path();
	fi.setFile(path+"/"+basename+".pdf");
	if(!fi.isWritable()){
		svnLock(fi.filePath());
	}
}

void Texmaker::fileCheckinPdf(QString filename){
	if (!currentEditorView()) return;
	QString finame=filename;
	if(finame.isEmpty())
		finame=documents.getTemporaryCompileFileName();
	QFileInfo fi(finame);
	QString basename=fi.baseName();
	QString path=fi.path();
	QString fn=path+"/"+basename+".pdf";
	SVNSTATUS status=svnStatus(fn);
	if(status==CheckedIn) return;
	if(status==Unmanaged)
		svnadd(fn);
	fileCheckin(fn);
}

void Texmaker::fileUpdate(QString filename){
	if (!currentEditorView()) return;
	QString fn=filename.isEmpty() ? currentEditor()->fileName() : filename;
	if(fn.isEmpty()) return;
	QString cmd=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	cmd+=" up  \""+fn+"\"";
	stat2->setText(QString(" svn update "));
	runCommand(cmd, RCF_WAIT_FOR_FINISHED);
}

void Texmaker::fileUpdateCWD(QString filename){
	if (!currentEditorView()) return;
	QString fn=filename.isEmpty() ? currentEditor()->fileName() : filename;
	if(fn.isEmpty()) return;
	QString cmd=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	fn=QFileInfo(fn).path();
	cmd+=" up  \""+fn+"\"";
	stat2->setText(QString(" svn update "));
	runCommand(cmd, RCF_WAIT_FOR_FINISHED);
}

void Texmaker::checkin(QString fn, QString text, bool blocking){
	QString cmd=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	cmd+=" ci -m \""+text+"\" \""+fn+("\"");
	stat2->setText(QString(" svn check in "));
	runCommand(cmd, (blocking?RCF_WAIT_FOR_FINISHED:RunCommandFlags()));
	LatexEditorView *edView=getEditorViewFromFileName(fn);
	if(edView)
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
	runCommand(cmd, 0);
	return true;
}

void Texmaker::svnLock(QString fn){
	QString cmd=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	cmd+=" lock \""+fn+("\"");
	stat2->setText(QString(" svn lock "));
	runCommand(cmd, 0);
}


void Texmaker::svncreateRep(QString fn){
	QString cmd=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	QString admin=buildManager.getLatexCommand(BuildManager::CMD_SVNADMIN);
	QString path=QFileInfo(fn).absolutePath();
	admin+=" create "+path+"/repo";
	stat2->setText(QString(" svn create repo "));
	runCommand(admin, RCF_WAIT_FOR_FINISHED);
	QString scmd=cmd+" mkdir file:///"+path+"/repo/trunk -m\"tmx auto generate\"";
	runCommand(scmd, RCF_WAIT_FOR_FINISHED);
	scmd=cmd+" mkdir file:///"+path+"/repo/branches -m\"tmx auto generate\"";
	runCommand(scmd, RCF_WAIT_FOR_FINISHED);
	scmd=cmd+" mkdir file:///"+path+"/repo/tags -m\"tmx auto generate\"";
	runCommand(scmd, RCF_WAIT_FOR_FINISHED);
	stat2->setText(QString(" svn checkout repo"));
	cmd+=" co file:///"+path+"/repo/trunk "+path;
	runCommand(cmd, RCF_WAIT_FOR_FINISHED);
}

void Texmaker::svnUndo(bool redo){
	QString cmd_svn=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	QString fn=currentEditor()->fileName();
	// get revisions of current file
	QString cmd=cmd_svn+" log "+fn;
	QString buffer;
	runCommand(cmd,RCF_WAIT_FOR_FINISHED,&buffer);
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
	foreach(const QString elem,lines){
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
	connect(currentEditor(),SIGNAL(textEdited(QKeyEvent *)),svndlg,SLOT(close()));
	currentEditor()->setProperty("Revision",log.first());
	svndlg->setAttribute(Qt::WA_DeleteOnClose,true);
	svndlg->show();
}
void Texmaker::svnDialogClosed(){
	if(cmbLog->currentIndex()==0) currentEditor()->document()->setClean();
	svndlg=0;
}

SVNSTATUS Texmaker::svnStatus(QString filename){
	QString cmd=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	cmd+=" st \""+filename+("\"");
	stat2->setText(QString(" svn status "));
	QString buffer;
	runCommand(cmd, RCF_WAIT_FOR_FINISHED,&buffer);
	if(buffer.isEmpty()) return CheckedIn;
	if(buffer.startsWith("?")) return Unmanaged;
	if(buffer.startsWith("M")) return Modified;
	if(buffer.startsWith("C")) return InConflict;
	if(buffer.startsWith("L")) return Locked;
	return Unknown;
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
	runCommand(cmd,RCF_WAIT_FOR_FINISHED,&buffer);
	// patch
	svnPatch(currentEditor(),buffer);
	currentEditor()->setProperty("Revision",rev);
}

QStringList Texmaker::svnLog(){
	QString cmd_svn=buildManager.getLatexCommand(BuildManager::CMD_SVN);
	QString fn="\""+currentEditor()->fileName()+"\"";
	// get revisions of current file
	QString cmd=cmd_svn+" log "+fn;
	QString buffer;
	runCommand(cmd,RCF_WAIT_FOR_FINISHED,&buffer);
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

bool Texmaker::generateMirror(bool setCur){
	if (!currentEditorView()) return false;
	QDocumentCursor cursor = currentEditorView()->editor->cursor();
	QDocumentCursor oldCursor = cursor;
	QString line=cursor.line().text();
	QString command, value;
	LatexParser::ContextType result=LatexParser::findContext(line, cursor.columnNumber(), command, value);
	if(result==LatexParser::Command || result==LatexParser::Environment){
		if ((command=="\\begin" || command=="\\end")&& !value.isEmpty()){
			//int l=cursor.lineNumber();
			int c=cursor.columnNumber();
			if (currentEditor()->currentPlaceHolder()!=-1 &&
			    currentEditor()->getPlaceHolder(currentEditor()->currentPlaceHolder()).cursor.isWithinSelection(cursor))
				currentEditor()->removePlaceHolder(currentEditor()->currentPlaceHolder()); //remove currentplaceholder to prevent nesting
			//move cursor to env name
			//currentEditorView()->editor->document()->beginMacro();
			if(result==LatexParser::Environment){
				int pos=c;
				while(pos>-1 && line[pos]!='{'){
					pos--;
				}
				pos++;
				cursor.movePosition(c-pos,QDocumentCursor::PreviousCharacter);
				cursor.movePosition(value.length(),QDocumentCursor::NextCharacter,QDocumentCursor::KeepAnchor);
				if(cursor.atLineEnd()||cursor.nextChar()!='}')  // closing brace is missing
					return false;
				//cursor.select(QDocumentCursor::WordUnderCursor);
			}else{
				cursor.movePosition(1,QDocumentCursor::EndOfWord);
				cursor.movePosition(1,QDocumentCursor::NextWord);
				//cursor.movePosition(1,QDocumentCursor::NextWord,QDocumentCursor::KeepAnchor);
				cursor.movePosition(value.length(),QDocumentCursor::NextCharacter,QDocumentCursor::KeepAnchor);
				if(cursor.atLineEnd()||cursor.nextChar()!='}')   // closing brace is missing
					return false;
			}
			//currentEditorView()->editor->setCursor(cursor);
			LatexDocument* doc=currentEditorView()->document;

			doc->m_magicPlaceHolder=currentEditor()->placeHolderCount();
			PlaceHolder ph;
			ph.cursor=cursor;
			currentEditor()->addPlaceHolder(ph,true);
			// remove curly brakets as well
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
				PlaceHolder ph;
				ph.length=searchWord.length()-offset-1;
				ph.cursor=currentEditor()->document()->cursor(endLine,start+offset+1,endLine,start+searchWord.length()-1);
				currentEditor()->addPlaceHolderMirror(doc->m_magicPlaceHolder,ph.cursor);
			}
			currentEditor()->setPlaceHolder(doc->m_magicPlaceHolder);
			if(setCur) {
				currentEditorView()->editor->setCursor(oldCursor);
			}
			return true;
		}
	}
	return false;
}

void Texmaker::generateBracketInverterMirror(){
	if (!currentEditor()) return;
	REQUIRE(currentEditor()->document() && currentEditor()->document()->languageDefinition());
	QDocumentCursor orig, to;
	currentEditor()->cursor().getMatchingPair(orig, to, false);

	PlaceHolder ph;
	ph.cursor = orig.selectionStart();
	ph.mirrors << to.selectionStart();
	ph.length = orig.selectedText().length();
	ph.affector = BracketInvertAffector::instance();
	currentEditor()->addPlaceHolder(ph);
	currentEditor()->setPlaceHolder(currentEditor()->placeHolderCount()-1);
}

void Texmaker::selectBracket(){
	if (!currentEditor()) return;
	REQUIRE(sender() && currentEditor()->document() && currentEditor()->document()->languageDefinition());
	QDocumentCursor orig, to;
	currentEditor()->cursor().getMatchingPair(orig, to, sender()->property("maximal").toBool());
	QDocumentCursor::sort(orig, to);
	if (sender()->property("maximal").toBool()) {
		if (orig.hasSelection()) orig = orig.selectionStart();
		if (to.hasSelection()) to = to.selectionEnd();
	} else {
		if (orig.hasSelection()) orig = orig.selectionEnd();
		if (to.hasSelection()) to = to.selectionStart();
	}
	currentEditor()->setCursor(currentEditor()->document()->cursor(orig.lineNumber(), orig.columnNumber(), to.lineNumber(), to.columnNumber()));
}

void Texmaker::openExternalFile(const QString name,const QString defaultExt,LatexDocument *doc){
	if(!doc)
		doc=dynamic_cast<LatexDocument*>(currentEditor()->document());
	if(!doc) return;
	QStringList curPaths;
	if(documents.masterDocument)
		curPaths << ensureTrailingDirSeparator(documents.masterDocument->getFileInfo().absolutePath());
	if(doc->getMasterDocument())
		curPaths << ensureTrailingDirSeparator(doc->getTopMasterDocument()->getFileInfo().absolutePath());
	curPaths << ensureTrailingDirSeparator(doc->getFileInfo().absolutePath());
	bool loaded;
	for(int i=0;i<curPaths.count();i++){
		QString curPath=curPaths.value(i);
		if ((loaded=load(getAbsoluteFilePath(curPath+name,defaultExt))))
			break;
		if ((loaded=load(getAbsoluteFilePath(curPath+name,""))))
			break;
		if ((loaded=load(getAbsoluteFilePath(name,defaultExt))))
			break;
	}

	if(!loaded)
		QMessageBox::warning(this,"TexMakerX","Sorry, I couldn't find the file \""+name+"\"",QMessageBox::Ok);
}


void Texmaker::cursorHovered(){
	if(completer->isVisible()) return;
	if(generateMirror(true)){
		currentEditorView()->document->m_mirrorInLine=currentEditorView()->editor->cursor().lineNumber();
	}
}

void Texmaker::saveProfile(){
	QString currentDir=configManager.configBaseDir;
	QString fname = QFileDialog::getSaveFileName(this,tr("Save Profile"),currentDir,tr("TmX Profile","filter")+"(*.tmxprofile);;"+tr("All files")+" (*)");
	QFileInfo info(fname);
	if(info.suffix().isEmpty())
		fname+=".tmxprofile";
	SaveSettings(fname);
}

void Texmaker::loadProfile(){
	QString currentDir=configManager.configBaseDir;
	QString fname = QFileDialog::getOpenFileName(this,tr("Load Profile"),currentDir,tr("TmX Profile","filter")+"(*.tmxprofile);;"+tr("All files")+" (*)");
	if(QFileInfo(fname).isReadable()){
		SaveSettings();
		QSettings *profile=new QSettings(fname,QSettings::IniFormat);
		QSettings *config=new QSettings(QSettings::IniFormat,QSettings::UserScope,"benibela","texmakerx");
		if(profile && config){
			QStringList keys = profile->allKeys();
			foreach(QString key,keys){
				config->setValue(key,profile->value(key));
			}
		}
		delete profile;
		delete config;
		ReadSettings();
	}
}

void Texmaker::addRowCB(){
	if (!currentEditorView()) return;
	QDocumentCursor cur=currentEditorView()->editor->cursor();
	if(!LatexTables::inTableEnv(cur)) return;
	int cols=LatexTables::getNumberOfColumns(cur);
	if(cols<1) return;
	LatexTables::addRow(cur,cols);
}

void Texmaker::addColumnCB(){
	if (!currentEditorView()) return;
	QDocumentCursor cur=currentEditorView()->editor->cursor();
	if(!LatexTables::inTableEnv(cur)) return;
	int col=LatexTables::getColumn(cur)+1;
	if(col<1) return;
	if(col==1 &&cur.atLineStart()) col=0;
	LatexTables::addColumn(currentEditorView()->document,currentEditorView()->editor->cursor().lineNumber(),col);
}

void Texmaker::removeColumnCB(){
	if (!currentEditorView()) return;
	QDocumentCursor cur=currentEditorView()->editor->cursor();
	if(!LatexTables::inTableEnv(cur)) return;
	// check if cursor has selection
	int numberOfColumns=1;
	int col=LatexTables::getColumn(cur);
	if(cur.hasSelection()){
		// if selection span within one row, romove all touched columns
		QDocumentCursor c2(cur.document(),cur.anchorLineNumber(),cur.anchorColumnNumber());
		if(!LatexTables::inTableEnv(c2)) return;
		QString res=cur.selectedText();
		if(res.contains("\\\\")) return;
		int col2=LatexTables::getColumn(c2);
		numberOfColumns=abs(col-col2)+1;
		if(col2<col) col=col2;
	}
	int ln=cur.lineNumber();
	for(int i=0;i<numberOfColumns;i++){
		LatexTables::removeColumn(currentEditorView()->document,ln,col,0);
	}
}

void Texmaker::removeRowCB(){
	if (!currentEditorView()) return;
	QDocumentCursor cur=currentEditorView()->editor->cursor();
	if(!LatexTables::inTableEnv(cur)) return;
	LatexTables::removeRow(cur);
}

void Texmaker::cutColumnCB(){
	if (!currentEditorView()) return;
	QDocumentCursor cur=currentEditorView()->editor->cursor();
	if(!LatexTables::inTableEnv(cur)) return;
	// check if cursor has selection
	int numberOfColumns=1;
	int col=LatexTables::getColumn(cur);
	if(cur.hasSelection()){
		// if selection span within one row, romove all touched columns
		QDocumentCursor c2(cur.document(),cur.anchorLineNumber(),cur.anchorColumnNumber());
		if(!LatexTables::inTableEnv(c2)) return;
		QString res=cur.selectedText();
		if(res.contains("\\\\")) return;
		int col2=LatexTables::getColumn(c2);
		numberOfColumns=abs(col-col2)+1;
		if(col2<col) col=col2;
	}
	int ln=cur.lineNumber();
	m_columnCutBuffer.clear();
	QStringList lst;
	for(int i=0;i<numberOfColumns;i++){
		lst.clear();
		LatexTables::removeColumn(currentEditorView()->document,ln,col,&lst);
		if(m_columnCutBuffer.isEmpty()){
			m_columnCutBuffer=lst;
		}else{
			for(int i=0;i<m_columnCutBuffer.size();i++){
				QString add="&";
				if(!lst.isEmpty()) add+=lst.takeFirst();
				m_columnCutBuffer[i]+=add;
			}
		}
	}

}

void Texmaker::pasteColumnCB(){
	if (!currentEditorView()) return;
	QDocumentCursor cur=currentEditorView()->editor->cursor();
	if(!LatexTables::inTableEnv(cur)) return;
	int col=LatexTables::getColumn(cur)+1;
	if(col==1 &&cur.atLineStart()) col=0;
	LatexTables::addColumn(currentEditorView()->document,currentEditorView()->editor->cursor().lineNumber(),col,&m_columnCutBuffer);
}

void Texmaker::addHLineCB(){
	if (!currentEditorView()) return;
	QDocumentCursor cur=currentEditorView()->editor->cursor();
	if(!LatexTables::inTableEnv(cur)) return;
	LatexTables::addHLine(cur);
}

void Texmaker::remHLineCB(){
	if (!currentEditorView()) return;
	QDocumentCursor cur=currentEditorView()->editor->cursor();
	if(!LatexTables::inTableEnv(cur)) return;
	LatexTables::addHLine(cur,-1,true);
}

void Texmaker::findWordRepetions(){
	if (!currentEditorView()) return;
	if(configManager.editorConfig && !configManager.editorConfig->inlineSpellChecking){
		QMessageBox::information(this,tr("Problem"),tr("Finding word repetitions only works with activated online spell checking !"),QMessageBox::Ok);
		return;
	}
	QDialog *dlg=new QDialog(this);
	dlg->setAttribute(Qt::WA_DeleteOnClose,true);
	QGridLayout *layout = new QGridLayout;
	layout->setColumnStretch(1, 1);
	layout->setColumnStretch(0, 1);
	QPushButton *but= new QPushButton(tr("&Find next"), dlg);
	but->setObjectName("next");
	QPushButton *but2= new QPushButton(tr("&Find previous"), dlg);
	but2->setObjectName("prev");
	layout->addWidget(but,0,0);
	layout->addWidget(but2,0,1);
	dlg->setLayout(layout);
	connect(but,SIGNAL(clicked()),this,SLOT(findNextWordRepetion()));
	connect(but2,SIGNAL(clicked()),this,SLOT(findNextWordRepetion()));
	dlg->setModal(false);
	dlg->show();
	dlg->raise();

}

void Texmaker::findNextWordRepetion(){
	QPushButton *mButton = qobject_cast<QPushButton *>(sender());
	bool backward=mButton->objectName()=="prev";
	if (!currentEditorView()) return;
	QDocumentCursor cur=currentEditor()->cursor();
	bool breaking=false;
	for(QDocumentLine line=cur.line();line.isValid();){
		if(line.hasOverlay(QDocument::formatFactory()->id("styleHint"))){
			QList<QFormatRange> ranges=line.getOverlays(QDocument::formatFactory()->id("styleHint"));
			for(int i=0;i<ranges.size();i++){
				if(!backward&&(line.lineNumber()>cur.lineNumber()||(ranges[i].offset+ranges[i].length>cur.columnNumber()&&ranges[i].offset+ranges[i].length>cur.anchorColumnNumber()))){
					cur.moveTo(line,ranges[i].offset);
					cur.movePosition(ranges[i].length,QDocumentCursor::Right,QDocumentCursor::KeepAnchor);
					breaking=true;
					break;
				}
				if(backward&&(line.lineNumber()<cur.lineNumber()||(ranges[i].offset<cur.columnNumber()&&ranges[i].offset<cur.anchorColumnNumber()))){
					cur.moveTo(line,ranges[i].offset);
					cur.movePosition(ranges[i].length,QDocumentCursor::Right,QDocumentCursor::KeepAnchor);
					breaking=true;
					break;
				}
			}
			if(breaking) break;
		}
		if(backward)
			line--;
		else
			line++;
	}
	if(breaking){
		currentEditor()->setCursor(cur);
	}
}

void Texmaker::latexModelViewMode(){
	bool mode=documents.model->getSingleDocMode();
	documents.model->setSingleDocMode(!mode);
}

void Texmaker::importPackage(QString name){
	if(!latexStyleParser){
		QString cmd_latex=buildManager.getLatexCommand(BuildManager::CMD_LATEX);
		QString baseDir;
		if(!QFileInfo(cmd_latex).isRelative())
			baseDir=QFileInfo(cmd_latex).absolutePath();
		latexStyleParser=new LatexStyleParser(this,configManager.configBaseDir,baseDir+"kpsewhich");
		connect(latexStyleParser,SIGNAL(scanCompleted(QString)),this,SLOT(packageScanCompleted(QString)));
		connect(latexStyleParser,SIGNAL(finished()),this,SLOT(packageParserFinished()));
		latexStyleParser->start();
		QTimer::singleShot(30000,this,SLOT(stopPackageParser()));
	}
	name.chop(4);
	name.append(".sty");
	latexStyleParser->addFile(name);
}

void Texmaker::packageScanCompleted(QString name){
	foreach(LatexDocument *doc,documents.documents){
		if(doc->containsPackage(name)){
			QStringList added(name);
			QStringList removed;
			doc->updateCompletionFiles(added,removed,false);
		}
	}
}

void Texmaker::stopPackageParser(){
	if(latexStyleParser)
		latexStyleParser->stop();
}

void Texmaker::packageParserFinished(){
	delete latexStyleParser;
	latexStyleParser=0;
}
