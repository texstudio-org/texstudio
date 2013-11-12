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

//#include "/usr/include/valgrind/callgrind.h"

#include "texmaker.h"
#include "latexeditorview.h"

#include "smallUsefulFunctions.h"

#include "cleandialog.h"

#include "debughelper.h"

#include "dblclickmenubar.h"
#include "structdialog.h"
#include "filechooser.h"
#include "tabdialog.h"
#include "arraydialog.h"
#include "bibtexdialog.h"
#include "tabbingdialog.h"
#include "letterdialog.h"
#include "quickdocumentdialog.h"
#include "mathassistant.h"
#include "maketemplatedialog.h"
#include "templateselector.h"
#include "templatemanager.h"
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
#include "scriptengine.h"
#include "grammarcheck.h"
#include "qmetautils.h"
#include "updatechecker.h"
#include "session.h"
#include "help.h"
#include "fileselector.h"

#ifndef QT_NO_DEBUG
#include "tests/testmanager.h"
#endif

#include "qdocument.h"
#include "qdocumentcursor.h"
#include "qdocumentline.h"
#include "qdocumentline_p.h"

#include "qnfadefinition.h"




bool programStopped = false;
Texmaker* txsInstance = 0;
QCache<QString,QIcon>IconCache;

Texmaker::Texmaker(QWidget *parent, Qt::WindowFlags flags, QSplashScreen *splash)
	: QMainWindow(parent, flags), textAnalysisDlg(0), spellDlg(0), mDontScrollToItem(false), runBibliographyIfNecessaryEntered(false) {
	
	programStopped = false;
	spellLanguageActions=0;
	MapForSymbols=0;
	currentLine=-1;
	svndlg=0;
	userMacroDialog = 0;
	mCompleterNeedsUpdate=false;
	latexStyleParser=0;
	packageListReader=0;
	bibtexEntryActions = 0;
	biblatexEntryActions = 0;
	bibTypeActions = 0;
	highlightLanguageActions = 0;
	runningPDFCommands = runningPDFAsyncCommands = 0;
	completerPreview=false;
    recheckLabels=true;
	
	ReadSettings();

    qRegisterMetaType<QSet<QString> >();
    readinAllPackageNames(); // asynchrnous read in of all available sty/cls
	
	txsInstance = this;
	static int crashHandlerType = 1;
	configManager.registerOption("Crash Handler Type", &crashHandlerType, 1);

    registerCrashHandler(crashHandlerType);
	QTimer * t  = new QTimer(this);
	connect(t, SIGNAL(timeout()), SLOT(iamalive()));
	t->start(9500);

	setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
	setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
	
	setWindowIcon(QIcon(":/images/logo128.png"));
	
	setIconSize(QSize(22,22));
	
	leftPanel=0;
	structureTreeView=0;
	outputView=0;
	
	qRegisterMetaType<LatexParser>();
	latexParser.importCwlAliases();
	
	m_formatsOldDefault = QDocument::defaultFormatScheme();
	QDocument::setDefaultFormatScheme(m_formats);
	SpellerUtility::spellcheckErrorFormat = m_formats->id("spellingMistake");
	
	qRegisterMetaType<QList<LineInfo> >();
	qRegisterMetaType<QList<GrammarError> >();
	qRegisterMetaType<LatexParser>();
	qRegisterMetaType<GrammarCheckerConfig>();

	grammarCheck = new GrammarCheck();
	grammarCheck->moveToThread(&grammarCheckThread);
	GrammarCheck::staticMetaObject.invokeMethod(grammarCheck, "init", Qt::QueuedConnection, Q_ARG(LatexParser, latexParser), Q_ARG(GrammarCheckerConfig, *configManager.grammarCheckerConfig));
	connect(grammarCheck, SIGNAL(checked(const void*,const void*,int,QList<GrammarError>)), &documents, SLOT(lineGrammarChecked(const void*,const void*,int,QList<GrammarError>)));
    if(configManager.autoLoadChildren)
        connect(&documents, SIGNAL(docToLoad(QString)),this,SLOT(addDocToLoad(QString)));

	grammarCheckThread.start();
	
	if (configManager.autodetectLoadedFile) QDocument::setDefaultCodec(0);
	else QDocument::setDefaultCodec(configManager.newFileEncoding);
	
	
	QString qxsPath=QFileInfo(findResourceFile("qxs/tex.qnfa")).path();
	m_languages = new QLanguageFactory(m_formats, this);
	m_languages->addDefinitionPath(qxsPath);
	
	// custom evironments<
	if(!configManager.customEnvironments.isEmpty()){
		QLanguageFactory::LangData m_lang=m_languages->languageData("(La)TeX");
		
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
		else
			marks[i].color = Qt::transparent;
	
	LatexEditorView::updateFormatSettings();

	// TAB WIDGET EDITEUR
	documents.indentationInStructure=configManager.indentationInStructure;
	documents.indentIncludesInStructure=configManager.indentIncludesInStructure;
	documents.showLineNumbersInStructure=configManager.showLineNumbersInStructure;
	connect(&documents,SIGNAL(masterDocumentChanged(LatexDocument *)), SLOT(masterDocumentChanged(LatexDocument *)));
	connect(&documents,SIGNAL(aboutToDeleteDocument(LatexDocument*)), SLOT(aboutToDeleteDocument(LatexDocument*)));
	
	centralFrame=new QFrame(this);
	centralFrame->setLineWidth(0);
	centralFrame->setFrameShape(QFrame::NoFrame);
	centralFrame->setFrameShadow(QFrame::Plain);
	
	//edit
	centralToolBar=new QToolBar(tr("Central"),this);
	centralToolBar->setFloatable(false);
	centralToolBar->setOrientation(Qt::Vertical);
	centralToolBar->setMovable(false);
	centralToolBar->setIconSize(QSize(16,16));
	
	EditorTabs=new TxsTabWidget(centralFrame);
	EditorTabs->setFocus();

	connect(&documents, SIGNAL(docToHide(LatexEditorView *)), EditorTabs, SLOT(removeEditor(LatexEditorView *)));
	connect(EditorTabs, SIGNAL(tabBarContextMenuRequested(QPoint)), SLOT(editorTabContextMenu(QPoint)));
	connect(EditorTabs, SIGNAL(currentChanged(int)), SLOT(editorTabChanged(int)));
	if (hasAtLeastQt(4,5)){
		EditorTabs->setProperty("tabsClosable",true);
		EditorTabs->setProperty("movable",true);
		connect(EditorTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseEditorTab(int)));
		connect(EditorTabs, SIGNAL(tabMoved(int,int)), this, SLOT(EditorTabMoved(int,int)));
	}
	connect(EditorTabs, SIGNAL(editorAboutToChangeByTabClick(LatexEditorView*,LatexEditorView*)), this, SLOT(editorAboutToChangeByTabClick(LatexEditorView*,LatexEditorView*)));

	cursorHistory = new CursorHistory(&documents);
	bookmarks = new Bookmarks(&documents, this);

	QLayout* centralLayout= new QHBoxLayout(centralFrame);
	centralLayout->setSpacing(0);
	centralLayout->setMargin(0);
	centralLayout->addWidget(centralToolBar);
	centralLayout->addWidget(EditorTabs);

	centralVSplitter = new QSplitter(Qt::Vertical, this);
	centralVSplitter->setChildrenCollapsible(false);
	centralVSplitter->addWidget(centralFrame);
	centralVSplitter->setStretchFactor(0,1);

	mainHSplitter = new QSplitter(Qt::Horizontal, this);
	mainHSplitter->addWidget(centralVSplitter);
	mainHSplitter->setChildrenCollapsible(false);
	setCentralWidget(mainHSplitter);
	
	setContextMenuPolicy(Qt::ActionsContextMenu);
	
	symbolMostused.clear();
	setupDockWidgets();

	setMenuBar(new DblClickMenuBar());
	setupMenus();
	TitledPanelPage *logPage = outputView->pageFromId(outputView->LOG_PAGE);
	if (logPage) {
		logPage->addToolbarAction(getManagedAction("main/tools/logmarkers"));
		logPage->addToolbarAction(getManagedAction("main/edit2/goto/errorprev"));
		logPage->addToolbarAction(getManagedAction("main/edit2/goto/errornext"));
	}
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
	if (splash)
		splash->raise();
	
	statusLabelMode->setText(QString(" %1 ").arg(tr("Normal Mode")));
	statusLabelProcess->setText(QString(" %1 ").arg(tr("Ready")));
	
	setAcceptDrops(true);
	installEventFilter(this);
	
	UpdateChecker::instance()->autoCheck();
	
	completer=new LatexCompleter(latexParser, this);
	completer->setConfig(configManager.completerConfig);
    completer->setPackageList(&latexPackageList);
    connect(completer,SIGNAL(showImagePreview(QString)),this,SLOT(showImgPreview(QString)));
    connect(this,SIGNAL(ImgPreview(QString)),completer,SLOT(bibtexSectionFound(QString)));
    //updateCompleter();
	LatexEditorView::setCompleter(completer);
	completer->updateAbbreviations();
	
	TemplateManager::setConfigBaseDir(configManager.configBaseDir);
	TemplateManager::ensureUserTemplateDirExists();
	TemplateManager::checkForOldUserTemplates();

    QDocument::addGuessEncodingCallback(&LatexParser::guessEncoding); // encodingcallback before restoer session !!!
    QDocument::addGuessEncodingCallback(&ConfigManager::getDefaultEncoding);

    if (configManager.sessionRestore) {
        fileRestoreSession(false);
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

  QStringList filters;
  filters << tr("TeX files")+" (*.tex *.bib *.sty *.cls *.mp *.dtx *.cfg *.ins *.ltx)";
  filters << tr("LilyPond files")+" (*.lytex)";
  filters << tr("Plaintext files")+" (*.txt)";
  filters << tr("Pweave files")+" (*.Pnw)";
  filters << tr("Sweave files")+" (*.Snw *.Rnw)";
  filters << tr("PDF files")+" (*.pdf)";
  filters << tr("All files")+" (*)";
  fileFilters = filters.join(";;");
  if (!configManager.rememberFileFilter)
      selectedFileFilter=filters.first();


  //setup autosave timer
  connect(&autosaveTimer,SIGNAL(timeout()),this,SLOT(fileSaveAll()));
  if(configManager.autosaveEveryMinutes>0){
    autosaveTimer.start(configManager.autosaveEveryMinutes*1000*60);
  }


  //script things
  setProperty("applicationName",TEXSTUDIO);
  QTimer::singleShot(500, this, SLOT(autoRunScripts()));

  connectWithAdditionalArguments(this, SIGNAL(infoNewFile()), this, "runScripts", QList<QVariant>() << Macro::ST_NEW_FILE);
  connectWithAdditionalArguments(this, SIGNAL(infoNewFromTemplate()), this, "runScripts", QList<QVariant>() << Macro::ST_NEW_FROM_TEMPLATE);
  connectWithAdditionalArguments(this, SIGNAL(infoLoadFile(QString)), this, "runScripts", QList<QVariant>() << Macro::ST_LOAD_FILE);
  connectWithAdditionalArguments(this, SIGNAL(infoFileSaved(QString)), this, "runScripts", QList<QVariant>() << Macro::ST_FILE_SAVED);
  connectWithAdditionalArguments(this, SIGNAL(infoFileClosed()), this, "runScripts", QList<QVariant>() << Macro::ST_FILE_CLOSED);
  connectWithAdditionalArguments(&documents, SIGNAL(masterDocumentChanged(LatexDocument*)), this, "runScripts", QList<QVariant>() << Macro::ST_MASTER_CHANGED);
  connectWithAdditionalArguments(this, SIGNAL(infoAfterTypeset()), this, "runScripts", QList<QVariant>() << Macro::ST_AFTER_TYPESET);
  connectWithAdditionalArguments(&buildManager, SIGNAL(endRunningCommands(QString,bool,bool,bool)), this, "runScripts", QList<QVariant>() << Macro::ST_AFTER_COMMAND_RUN);
}


Texmaker::~Texmaker(){

    IconCache.clear();
	QDocument::setDefaultFormatScheme(m_formatsOldDefault); //prevents crash when deleted latexeditorview accesses the default format scheme, as m_format is going to be deleted

	programStopped = true;

    Guardian::shutdown();
	
	delete MapForSymbols;
	if(latexStyleParser){
		latexStyleParser->stop();
		latexStyleParser->wait();
	}
	if(packageListReader){
        packageListReader->stop();
		packageListReader->wait();
    }
	GrammarCheck::staticMetaObject.invokeMethod(grammarCheck, "deleteLater", Qt::BlockingQueuedConnection);
	grammarCheckThread.quit();
	grammarCheckThread.wait(5000); //TODO: timeout causes sigsegv, is there any better solution?
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
		
        leftPanel->addWidget(structureTreeView, "structureTreeView", tr("Structure"), getRealIconFile("structure"));
	} else leftPanel->setWidgetText(structureTreeView,tr("Structure"));
	if(!leftPanel->widget("bookmarks")) {
		QListWidget *bookmarksWidget = bookmarks->widget();
		connect(bookmarks, SIGNAL(loadFileRequest(QString)), this, SLOT(load(QString)));
		connect(bookmarks, SIGNAL(gotoLineRequest(int,int,LatexEditorView*)), this, SLOT(gotoLine(int,int,LatexEditorView*)));
        leftPanel->addWidget(bookmarksWidget, "bookmarks", tr("Bookmarks"), getRealIconFile("bookmarks"));
	} else leftPanel->setWidgetText("bookmarks", tr("Bookmarks"));
	
    int cnt=modernStyle ? 11 : 1;
    addSymbolGrid("operators", QString(":/symbols-ng/icons/img0%1icons.png").arg(cnt++,2,10,QLatin1Char('0')),tr("Operator symbols"));
    addSymbolGrid("relation", QString(":/symbols-ng/icons/img0%1icons.png").arg(cnt++,2,10,QLatin1Char('0')),tr("Relation symbols"));
    addSymbolGrid("arrows", QString(":/symbols-ng/icons/img0%1icons.png").arg(cnt++,2,10,QLatin1Char('0')),tr("Arrow symbols"));
    addSymbolGrid("delimiters",QString(":/symbols-ng/icons/img0%1icons.png").arg(cnt++,2,10,QLatin1Char('0')),tr("Delimiters"));
    addSymbolGrid("greek", QString(":/symbols-ng/icons/img0%1icons.png").arg(cnt++,2,10,QLatin1Char('0')),tr("Greek letters"));
    addSymbolGrid("cyrillic", QString(":/symbols-ng/icons/img0%1icons.png").arg(cnt++,2,10,QLatin1Char('0')),tr("Cyrillic letters"));
    addSymbolGrid("misc-math", QString(":/symbols-ng/icons/img0%1icons.png").arg(cnt++,2,10,QLatin1Char('0')),tr("Miscellaneous math symbols"));
    addSymbolGrid("misc-text", QString(":/symbols-ng/icons/img0%1icons.png").arg(cnt++,2,10,QLatin1Char('0')),tr("Miscellaneous text symbols"));
    addSymbolGrid("wasysym", QString(":/symbols-ng/icons/img0%1icons.png").arg(cnt++,2,10,QLatin1Char('0')),tr("Miscellaneous text symbols (wasysym)"));
    addSymbolGrid("special", QString(":/symbols-ng/icons/img0%1icons.png").arg(cnt++,2,10,QLatin1Char('0')),tr("Accented letters"));
	
    MostUsedSymbolWidget=addSymbolGrid("!mostused",getRealIconFile("math6"),tr("Most used symbols"));
	MostUsedSymbolWidget->loadSymbols(MapForSymbols->keys(),MapForSymbols);
    FavoriteSymbolWidget=addSymbolGrid("!favorite",getRealIconFile("math7"),tr("Favorites"));
	FavoriteSymbolWidget->loadSymbols(symbolFavorites);
	
    addTagList("brackets", getRealIconFile("leftright"), tr("Left/Right Brackets"),"brackets_tags.xml");
    addTagList("pstricks", getRealIconFile("pstricks"), tr("Pstricks Commands"),"pstricks_tags.xml");
    addTagList("metapost", getRealIconFile("metapost"), tr("MetaPost Commands"),"metapost_tags.xml");
    addTagList("tikz", getRealIconFile("tikz"), tr("Tikz Commands"),"tikz_tags.xml");
    addTagList("asymptote", getRealIconFile("asymptote"), tr("Asymptote Commands"),"asymptote_tags.xml");
	
	leftPanel->showWidgets(configManager.newLeftPanelLayout);
	
	// update MostOftenUsed
	MostUsedSymbolsTriggered(true);
	// OUTPUT WIDGETS
	if (!outputView) {
		outputView = new OutputViewWidget(this);
		outputView->setObjectName("OutputView");
		centralVSplitter->addWidget(outputView);
		centralVSplitter->setStretchFactor(1,0);

		connect(outputView->getLogWidget(),SIGNAL(logEntryActivated(int)),this,SLOT(gotoLogEntryEditorOnly(int)));
		connect(outputView->getLogWidget(),SIGNAL(logLoaded()),this,SLOT(updateLogEntriesInEditors()));
		connect(outputView->getLogWidget(),SIGNAL(logResetted()),this,SLOT(clearLogEntriesInEditors()));
		connect(outputView,SIGNAL(pageChanged(QString)),this,SLOT(outputPageChanged(QString)));
		connect(outputView,SIGNAL(jumpToSearch(QDocument*,int)),this,SLOT(jumpToSearch(QDocument*,int)));
		connect(&buildManager,SIGNAL(previewAvailable(const QString&, const PreviewSource&)),this,SLOT(previewAvailable	(const QString&,const PreviewSource&)));
		connect(&buildManager, SIGNAL(processNotification(QString)), SLOT(processNotification(QString)));
		
		connect(&buildManager, SIGNAL(beginRunningCommands(QString,bool,bool,bool)), SLOT(beginRunningCommand(QString,bool,bool,bool)));
		connect(&buildManager, SIGNAL(beginRunningSubCommand(ProcessX*,QString,QString,RunCommandFlags)), SLOT(beginRunningSubCommand(ProcessX*,QString,QString,RunCommandFlags)));
		connect(&buildManager, SIGNAL(endRunningSubCommand(ProcessX*,QString,QString,RunCommandFlags)), SLOT(endRunningSubCommand(ProcessX*,QString,QString,RunCommandFlags)));
		connect(&buildManager, SIGNAL(endRunningCommands(QString,bool,bool,bool)), SLOT(endRunningCommand(QString,bool,bool,bool)));
		connect(&buildManager, SIGNAL(latexCompiled(LatexCompileResult*)), SLOT(ViewLogOrReRun(LatexCompileResult*)));
		connect(&buildManager, SIGNAL(runInternalCommand(QString,QFileInfo,QString)), SLOT(runInternalCommand(QString,QFileInfo,QString)));
		connect(&buildManager, SIGNAL(commandLineRequested(QString,QString*,bool*)), SLOT(commandLineRequested(QString,QString*,bool*)));
		
		
		addAction(outputView->toggleViewAction());
		QAction* temp = new QAction(this); temp->setSeparator(true);
		addAction(temp);
	}
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
					QStringList actionTexts;
					QList<QIcon> actionIcons;
					foreach (const QAction* act, menu->actions())
						if (!act->isSeparator()) {
							actionTexts.append(act->text());
							actionIcons.append(act->icon());
						}
					createComboToolButton(tb.toolbar, actionTexts, actionIcons, -1, this, SLOT(callToolButtonAction()), "", combo);

					if (menuName == "main/view/documents") {
						//workaround to select the current document
						int index = EditorTabs->currentIndex();
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
	getManagedMenu("main/file");
	newManagedAction(menu, "new",tr("&New"), SLOT(fileNew()), Qt::CTRL+Qt::Key_N, "filenew");
	newManagedAction(menu, "newfromtemplate",tr("New From &Template..."), SLOT(fileNewFromTemplate()));
	newManagedAction(menu, "open",tr("&Open..."), SLOT(fileOpen()), Qt::CTRL+Qt::Key_O, "fileopen");
	
	QMenu *submenu=newManagedMenu(menu, "openrecent",tr("Open &Recent")); //only create the menu here, actions are created by config manager

	submenu = newManagedMenu(menu, "session", tr("Session"));
	newManagedAction(submenu, "loadsession", tr("Load Session..."), SLOT(fileLoadSession()));
	newManagedAction(submenu, "savesession", tr("Save Session..."), SLOT(fileSaveSession()));
	newManagedAction(submenu, "restoresession",tr("Restore Previous Session"), SLOT(fileRestoreSession()));
	
	menu->addSeparator();
	actSave = newManagedAction(menu,"save",tr("&Save"), SLOT(fileSave()), Qt::CTRL+Qt::Key_S, "filesave");
	newManagedAction(menu,"saveas",tr("Save &As..."), SLOT(fileSaveAs()), Qt::CTRL+Qt::ALT+Qt::Key_S);
	newManagedAction(menu,"saveall",tr("Save A&ll"), SLOT(fileSaveAll()), Qt::CTRL+Qt::SHIFT+Qt::ALT+Qt::Key_S);
	newManagedAction(menu, "maketemplate",tr("&Make Template..."), SLOT(fileMakeTemplate()));


	submenu=newManagedMenu(menu, "utilities",tr("Fifi&x"));
	newManagedAction(submenu, "rename", tr("Save renamed/&moved file..."), "fileUtilCopyMove",0,QString(),QList<QVariant>() << true);
	newManagedAction(submenu, "copy", tr("Save copied file..."), "fileUtilCopyMove",0,QString(),QList<QVariant>() << false);
	newManagedAction(submenu, "delete", tr("&Delete file"), SLOT(fileUtilDelete()));
	newManagedAction(submenu, "chmod", tr("Set &permissions..."), SLOT(fileUtilPermissions()));
	submenu->addSeparator();
	newManagedAction(submenu, "revert", tr("&Revert to saved..."), SLOT(fileUtilRevert()));
	submenu->addSeparator();
	newManagedAction(submenu, "copyfilename", tr("Copy filename to &clipboard"), SLOT(fileUtilCopyFileName()));
	newManagedAction(submenu, "copymasterfilename", tr("Copy master filename to clipboard"), SLOT(fileUtilCopyMasterFileName()));

	QMenu *svnSubmenu=newManagedMenu(menu, "svn",tr("S&VN..."));
	newManagedAction(svnSubmenu, "checkin",tr("Check &in..."), SLOT(fileCheckin()));
	newManagedAction(svnSubmenu, "svnupdate",tr("SVN &update..."), SLOT(fileUpdate()));
	newManagedAction(svnSubmenu, "svnupdatecwd",tr("SVN update &work directory"), SLOT(fileUpdateCWD()));
	newManagedAction(svnSubmenu, "showrevisions",tr("Sh&ow old Revisions"), SLOT(showOldRevisions()));
	newManagedAction(svnSubmenu, "lockpdf",tr("Lock &PDF"), SLOT(fileLockPdf()));
	newManagedAction(svnSubmenu, "checkinpdf",tr("Check in P&DF"), SLOT(fileCheckinPdf()));
	newManagedAction(svnSubmenu, "difffiles",tr("Show difference between two files"), SLOT(fileDiff()));
	newManagedAction(svnSubmenu, "diff3files",tr("Show difference between two files in relation to base file"), SLOT(fileDiff3()));
	newManagedAction(svnSubmenu, "checksvnconflict",tr("Check SVN Conflict"), SLOT(checkSVNConflicted()));
	newManagedAction(svnSubmenu, "mergediff",tr("Try to merge differences"), SLOT(fileDiffMerge()));
	newManagedAction(svnSubmenu, "removediffmakers",tr("Remove Difference-Markers"), SLOT(removeDiffMarkers()));
	newManagedAction(svnSubmenu, "declareresolved",tr("Declare Conflict Resolved"), SLOT(declareConflictResolved()));
	newManagedAction(svnSubmenu, "nextdiff",tr("Jump to next difference"), SLOT(jumpNextDiff()),0,"go-next-diff");
	newManagedAction(svnSubmenu, "prevdiff",tr("Jump to previous difference"), SLOT(jumpPrevDiff()),0,"go-previous-diff");
	
	menu->addSeparator();
	newManagedAction(menu,"close",tr("&Close"), SLOT(fileClose()), Qt::CTRL+Qt::Key_W, "fileclose");
	newManagedAction(menu,"closeall",tr("Clos&e All"), SLOT(fileCloseAll()));
	
	menu->addSeparator();
	newManagedEditorAction(menu, "print",tr("Print..."), "print", Qt::CTRL+Qt::Key_P);
	
	menu->addSeparator();
	newManagedAction(menu,"exit",tr("Exit"), SLOT(fileExit()), Qt::CTRL+Qt::Key_Q)->setMenuRole(QAction::QuitRole);
	
	//edit
	menu=newManagedMenu("main/edit",tr("&Edit"));
	actUndo = newManagedAction(menu, "undo",tr("&Undo"), SLOT(editUndo()), Qt::CTRL+Qt::Key_Z, "undo");
	actRedo = newManagedAction(menu, "redo",tr("&Redo"), SLOT(editRedo()), Qt::CTRL+Qt::Key_Y, "redo");
#ifndef QT_NO_DEBUG
	newManagedAction(menu, "debughistory",tr("Debug undo stack"), SLOT(editDebugUndoStack()));
#endif
	menu->addSeparator();
	newManagedAction(menu,"copy",tr("&Copy"), SLOT(editCopy()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_C)<<Qt::CTRL+Qt::Key_Insert, "editcopy");
	newManagedEditorAction(menu,"cut",tr("C&ut"), "cut", (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_X)<<Qt::SHIFT+Qt::Key_Delete, "editcut");
	newManagedAction(menu,"paste",tr("&Paste"), SLOT(editPaste()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_V)<<Qt::AltModifier+Qt::Key_Insert, "editpaste");
	//newManagedEditorAction(menu,"paste",tr("&Paste"), "paste", (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_V)<<Qt::AltModifier+Qt::Key_Insert, "editpaste");
	newManagedEditorAction(menu,"selectall",tr("Select &All"), "selectAll", Qt::CTRL+Qt::Key_A);

	submenu = newManagedMenu(menu, "lineoperations", tr("&Line Operations"));
	newManagedAction(submenu,"eraseLine",tr("Erase &Line"), SLOT(editEraseLine()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_K));
	newManagedAction(submenu,"eraseEndLine",tr("Erase until E&nd of Line"), SLOT(editEraseEndLine()), (QList<QKeySequence>()<< Qt::AltModifier+Qt::Key_K));
	newManagedAction(submenu,"moveLineUp",tr("Move Line &Up"), SLOT(editMoveLineUp()));
	newManagedAction(submenu,"moveLineDown",tr("Move Line &Down"), SLOT(editMoveLineDown()));
	newManagedAction(submenu,"duplicateLine",tr("Duplicate Line"), SLOT(editDuplicateLine()));

	menu->addSeparator();
	submenu = newManagedMenu(menu, "searching", tr("&Searching"));
	newManagedEditorAction(submenu,"find", tr("&Find"), "find", Qt::CTRL+Qt::Key_F);
	newManagedEditorAction(submenu,"findinsamedir",tr("Continue F&ind"), "findInSameDir", (QList<QKeySequence>()<< Qt::Key_F3)<<Qt::CTRL+Qt::Key_M);
	newManagedEditorAction(submenu,"findnext",tr("Find &Next"), "findNext");
	newManagedEditorAction(submenu,"findprev",tr("Find &Prev"), "findPrev");
	newManagedEditorAction(submenu,"findcount",tr("&Count"), "findCount");
	newManagedEditorAction(submenu,"select",tr("&Select all matches..."), "selectAllMatches");
	newManagedAction(submenu,"findglobal",tr("Find &Dialog..."), SLOT(editFindGlobal()));
	submenu->addSeparator();
	newManagedEditorAction(submenu,"replace",tr("&Replace"), "replacePanel", Qt::CTRL+Qt::Key_R);
	newManagedEditorAction(submenu,"replacenext",tr("Replace Next"), "replaceNext");
	newManagedEditorAction(submenu,"replaceprev",tr("Replace Prev"), "replacePrev");
	newManagedEditorAction(submenu,"replaceall",tr("Replace &All"), "replaceAll");
	
	menu->addSeparator();
	submenu=newManagedMenu(menu, "goto",tr("Go to"));

    newManagedEditorAction(submenu,"line", tr("Line"), "gotoLine", Qt::CTRL+Qt::Key_G, "goto");
	newManagedEditorAction(submenu,"lastchange",tr("Previous Change"), "jumpChangePositionBackward", Qt::CTRL+Qt::Key_H);
	newManagedEditorAction(submenu,"nextchange",tr("Next Change"), "jumpChangePositionForward", Qt::CTRL+Qt::SHIFT+Qt::Key_H);
	submenu->addSeparator();
	newManagedAction(submenu,"markprev",tr("Previous mark"),"gotoMark",Qt::CTRL+Qt::Key_Up,"",QList<QVariant>() << true << -1);//, ":/images/errorprev.png");
	newManagedAction(submenu,"marknext",tr("Next mark"),"gotoMark",Qt::CTRL+Qt::Key_Down,"",QList<QVariant>() << false << -1);//, ":/images/errornext.png");
	submenu->addSeparator();
    cursorHistory->setBackAction(newManagedAction(submenu,"goback",tr("Go Back"), SLOT(goBack()), Qt::ALT+Qt::Key_Left, "back"));
    cursorHistory->setForwardAction(newManagedAction(submenu,"goforward",tr("Go Forward"), SLOT(goForward()), Qt::ALT+Qt::Key_Right, "forward"));
	
	submenu=newManagedMenu(menu, "gotoBookmark",tr("Goto Bookmark"));
	for (int i=0; i<=9; i++)
		newManagedEditorAction(submenu,QString("bookmark%1").arg(i),tr("Bookmark %1").arg(i),"jumpToBookmark",Qt::CTRL+Qt::Key_0+i,"",QList<QVariant>() << i);
	
	submenu=newManagedMenu(menu, "toggleBookmark",tr("Toggle Bookmark"));
	newManagedEditorAction(submenu,QString("bookmark"),tr("Unnamed Bookmark"),"toggleBookmark",Qt::CTRL+Qt::SHIFT+Qt::Key_B,"",QList<QVariant>() <<-1);
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
	
	
	newManagedAction(menu,"encoding",tr("Setup Encoding..."),SLOT(editSetupEncoding()))->setMenuRole(QAction::NoRole); // with the default "QAction::TextHeuristicRole" this was interperted as Preferences on OSX
	newManagedAction(menu,"unicodeChar",tr("Insert Unicode Character..."),SLOT(editInsertUnicode()), Qt::ALT + Qt::CTRL + Qt::Key_U);
	
	
	
	//Edit 2 (for LaTeX related things)
	menu=newManagedMenu("main/edit2",tr("&Idefix"));
	newManagedAction(menu,"eraseWord",tr("Erase &Word/Cmd/Env"), SLOT(editEraseWordCmdEnv()), Qt::ALT+Qt::Key_Delete);
	
	menu->addSeparator();
    newManagedAction(menu,"pasteAsLatex",tr("Pas&te as LaTeX"), SLOT(editPasteLatex()), Qt::CTRL+Qt::SHIFT+Qt::Key_V, "editpaste");
	newManagedAction(menu,"convertTo",tr("Co&nvert to LaTeX"), SLOT(convertToLatex()));
	newManagedAction(menu,"previewLatex",tr("Pre&view Selection/Parentheses"), SLOT(previewLatex()),Qt::ALT+Qt::Key_P);
	newManagedAction(menu,"removePreviewLatex",tr("C&lear Inline Preview"), SLOT(clearPreview()));
	
	menu->addSeparator();
	newManagedEditorAction(menu,"comment", tr("&Comment"), "commentSelection", Qt::CTRL+Qt::Key_T);
	newManagedEditorAction(menu,"uncomment",tr("&Uncomment"), "uncommentSelection", Qt::CTRL+Qt::Key_U);
	newManagedEditorAction(menu,"indent",tr("&Indent"), "indentSelection");
	newManagedEditorAction(menu,"unindent",tr("Unin&dent"), "unindentSelection");
	newManagedAction(menu,"hardbreak",tr("Hard Line &Break..."), SLOT(editHardLineBreak()));
	newManagedAction(menu,"hardbreakrepeat",tr("R&epeat Hard Line Break"), SLOT(editHardLineBreakRepeat()));
	
	menu->addSeparator();
	submenu=newManagedMenu(menu, "goto",tr("&Go to"));
	
    newManagedAction(submenu,"errorprev",tr("Previous Error"),"gotoNearLogEntry",Qt::CTRL+Qt::SHIFT+Qt::Key_Up, "errorprev", QList<QVariant>() << LT_ERROR << true << tr("No LaTeX errors detected !"));
    newManagedAction(submenu,"errornext",tr("Next Error"),"gotoNearLogEntry",Qt::CTRL+Qt::SHIFT+Qt::Key_Down, "errornext", QList<QVariant>() << LT_ERROR << false << tr("No LaTeX errors detected !"));
	newManagedAction(submenu,"warningprev",tr("Previous Warning"),"gotoNearLogEntry",QKeySequence(),"", QList<QVariant>() << LT_WARNING << true << tr("No LaTeX warnings detected !"));//, ":/images/errorprev.png");
	newManagedAction(submenu,"warningnext",tr("Next Warning"),"gotoNearLogEntry",QKeySequence(),"", QList<QVariant>() << LT_WARNING << false << tr("No LaTeX warnings detected !"));//, ":/images/errornext.png");
	newManagedAction(submenu,"badboxprev",tr("Previous Bad Box"),"gotoNearLogEntry",Qt::SHIFT+Qt::ALT+Qt::Key_Up, "", QList<QVariant>() << LT_BADBOX << true << tr("No bad boxes detected !"));//, ":/images/errorprev.png");
	newManagedAction(submenu,"badboxnext",tr("Next Bad Box"),"gotoNearLogEntry",Qt::SHIFT+Qt::ALT+Qt::Key_Down, "", QList<QVariant>() << LT_BADBOX << true << tr("No bad boxes detected !"));//, ":/images/errornext.png");
	submenu->addSeparator();

	QKeySequence sc(Qt::CTRL+Qt::ALT+Qt::Key_F);
#ifdef Q_OS_WIN32
	// on win ctrl+alt = altGr, hungarian: altGr+F = [
	// so we should not use this as shortcut in this special case
	if (QApplication::keyboardInputLocale().language() == QLocale::Hungarian)
		sc = QKeySequence(Qt::CTRL+Qt::ALT+Qt::SHIFT+Qt::Key_F);
#endif
	newManagedAction(submenu,"definition",tr("Definition"),SLOT(editGotoDefinition()),sc);
	
	menu->addSeparator();
	newManagedAction(menu,"generateMirror",tr("Re&name Environment"), SLOT(generateMirror()));
	
	submenu = newManagedMenu(menu, "parens", tr("Parenthesis"));
	newManagedAction(submenu, "jump", tr("Jump to Match"), SLOT(jumpToBracket()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_J));
	newManagedAction(submenu, "selectBracketInner", tr("Select Inner"), SLOT(selectBracket()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_I))->setProperty("minimal", true);
	newManagedAction(submenu, "selectBracketOuter", tr("Select Outer"), SLOT(selectBracket()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_O))->setProperty("minimal", false);
	newManagedAction(submenu, "selectBracketCommand", tr("Select Command"), SLOT(selectBracket()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_C))->setProperty("backslash", true);
	newManagedAction(submenu, "selectBracketLine", tr("Select Line"), SLOT(selectBracket()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_L))->setProperty("line", true);
	newManagedAction(submenu, "generateInvertedBracketMirror", tr("Select Inverting"), SLOT(generateBracketInverterMirror()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_S));

	submenu->addSeparator();
	newManagedAction(submenu, "findMissingBracket", tr("Find Mismatch"), SLOT(findMissingBracket()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_M));
	
	submenu=newManagedMenu(menu, "complete",tr("Complete"));
	newManagedAction(submenu, "normal", tr("Normal"), SLOT(NormalCompletion()),Qt::CTRL+Qt::Key_Space);
	newManagedAction(submenu, "environment", tr("\\begin{ Completion"), SLOT(InsertEnvironmentCompletion()),Qt::CTRL+Qt::ALT+Qt::Key_Space);
	newManagedAction(submenu, "text", tr("Normal Text"), SLOT(InsertTextCompletion()),Qt::SHIFT+Qt::ALT+Qt::Key_Space);
	newManagedAction(submenu, "closeEnvironment", tr("Close latest open environment"), SLOT(CloseEnv()),Qt::ALT+Qt::Key_Return);
	
	menu->addSeparator();
	newManagedAction(menu,"reparse",tr("Refresh Structure"),SLOT(updateStructure()));
	newManagedAction(menu,"removePlaceHolders",tr("Remove Placeholders"),SLOT(editRemovePlaceHolders()),Qt::CTRL+Qt::SHIFT+Qt::Key_K);
	
	//tools
	
	
	menu=newManagedMenu("main/tools",tr("&Tools"));
	menu->setProperty("defaultSlot", QByteArray(SLOT(commandFromAction())));
	newManagedAction(menu, "quickbuild",tr("&Build && View"), SLOT(commandFromAction()), Qt::Key_F1, "build")->setData(BuildManager::CMD_QUICK);
	newManagedAction(menu, "compile",tr("&Compile"), SLOT(commandFromAction()), Qt::Key_F6,"compile")->setData(BuildManager::CMD_COMPILE);
	newManagedAction(menu, "view",tr("&View"), SLOT(commandFromAction()), Qt::Key_F7,"viewer")->setData(BuildManager::CMD_VIEW);
	newManagedAction(menu, "bibtex",tr("&Bibliography"), SLOT(commandFromAction()), Qt::Key_F11)->setData(BuildManager::CMD_BIBLIOGRAPHY);
	newManagedAction(menu, "index",tr("&Index"), SLOT(commandFromAction()), Qt::Key_F12)->setData(BuildManager::CMD_INDEX);

	menu->addSeparator();
	submenu=newManagedMenu(menu, "commands",tr("&Commands", "menu"));
	newManagedAction(submenu, "latexmk",tr("&Latexmk"), SLOT(commandFromAction()))->setData(BuildManager::CMD_LATEXMK);
	submenu->addSeparator();
    newManagedAction(submenu, "latex",tr("&LaTeX"), SLOT(commandFromAction()), QKeySequence(), "compile-latex")->setData(BuildManager::CMD_LATEX);
    newManagedAction(submenu, "pdflatex",tr("&PDFLaTeX"), SLOT(commandFromAction()), QKeySequence(), "compile-pdf")->setData(BuildManager::CMD_PDFLATEX);
    newManagedAction(submenu, "xelatex","&XeLaTeX", SLOT(commandFromAction()), QKeySequence(), "compile-xelatex")->setData(BuildManager::CMD_XELATEX);
    newManagedAction(submenu, "lualatex","L&uaLaTeX", SLOT(commandFromAction()), QKeySequence(), "compile-lua")->setData(BuildManager::CMD_LUALATEX);
	submenu->addSeparator();
    newManagedAction(submenu, "dvi2ps",tr("DVI->PS"), SLOT(commandFromAction()), QKeySequence(), "convert-dvips")->setData(BuildManager::CMD_DVIPS);
    newManagedAction(submenu, "ps2pdf",tr("P&S->PDF"), SLOT(commandFromAction()), QKeySequence(), "convert-pspdf")->setData(BuildManager::CMD_PS2PDF);
    newManagedAction(submenu, "dvipdf",tr("DV&I->PDF"), SLOT(commandFromAction()), QKeySequence(), "convert-dvipdf")->setData(BuildManager::CMD_DVIPDF);
	submenu->addSeparator();
    newManagedAction(submenu, "viewdvi",tr("View &DVI"), SLOT(commandFromAction()), QKeySequence(), "view-doc-dvi")->setData(BuildManager::CMD_VIEW_DVI);
    newManagedAction(submenu, "viewps",tr("Vie&w PS"), SLOT(commandFromAction()), QKeySequence(), "view-doc-ps")->setData(BuildManager::CMD_VIEW_PS);
    newManagedAction(submenu, "viewpdf",tr("View PD&F"), SLOT(commandFromAction()), QKeySequence(), "view-doc-pdf")->setData(BuildManager::CMD_VIEW_PDF);
	submenu->addSeparator();
	newManagedAction(submenu, "makeindex",tr("&MakeIndex"), SLOT(commandFromAction()))->setData(BuildManager::CMD_MAKEINDEX);
	newManagedAction(submenu, "texindy",tr("&TexIndy"), SLOT(commandFromAction()), QKeySequence())->setData(BuildManager::CMD_TEXINDY);
	submenu->addSeparator();
	newManagedAction(submenu, "metapost",tr("&MetaPost"), SLOT(commandFromAction()))->setData(BuildManager::CMD_METAPOST);
	newManagedAction(submenu, "asymptote",tr("&Asymptote"), SLOT(commandFromAction()))->setData(BuildManager::CMD_ASY);

	submenu=newManagedMenu(menu, "user",tr("&User", "menu"));
	updateUserToolMenu();
	menu->addSeparator();
	newManagedAction(menu, "clean",tr("Cle&an Auxiliary Files..."), SLOT(CleanAll()));
	menu->addSeparator();
	newManagedAction(menu, "viewlog",tr("View &Log"), SLOT(commandFromAction()), QKeySequence(), "viewlog")->setData(BuildManager::CMD_VIEW_LOG);
	act = newManagedAction(menu, "logmarkers", tr("Show Log Markers"), 0, 0, "logmarkers");
	act->setCheckable(true);
	connect(act, SIGNAL(triggered(bool)), SLOT(setLogMarksVisible(bool)));
	menu->addSeparator();
	newManagedAction(menu, "htmlexport",tr("C&onvert to Html..."), SLOT(WebPublish()));
	newManagedAction(menu, "htmlsourceexport",tr("C&onvert Source to Html..."), SLOT(WebPublishSource()));
	menu->addSeparator();
	newManagedAction(menu, "analysetext",tr("A&nalyse Text..."), SLOT(AnalyseText()));
	newManagedAction(menu, "generaterandomtext",tr("Generate &Random Text..."), SLOT(GenerateRandomText()));
	menu->addSeparator();
	newManagedAction(menu,"spelling",tr("Check Spelling..."),SLOT(editSpell()),Qt::CTRL+Qt::SHIFT+Qt::Key_F7);
	newManagedAction(menu,"thesaurus",tr("Thesaurus..."),SLOT(editThesaurus()),Qt::CTRL+Qt::SHIFT+Qt::Key_F8);
	newManagedAction(menu,"wordrepetions",tr("Find Word Repetitions..."),SLOT(findWordRepetions()));
	
	//  Latex/Math external
	configManager.loadManagedMenus(":/uiconfig.xml");
	// add some additional items
	menu=newManagedMenu("main/latex",tr("&LaTeX"));
	menu->setProperty("defaultSlot", QByteArray(SLOT(InsertFromAction())));
	newManagedAction(menu, "insertrefnextlabel",tr("Insert \\ref to Next Label"), SLOT(editInsertRefToNextLabel()), Qt::ALT+Qt::CTRL+Qt::Key_R);
	newManagedAction(menu, "insertrefprevlabel",tr("Insert \\ref to Previous Label"), SLOT(editInsertRefToPrevLabel()));
	submenu=newManagedMenu(menu, "tabularmanipulation",tr("Manipulate Tables","table"));
	newManagedAction(submenu, "addRow",tr("Add Row","table"), SLOT(addRowCB()),QKeySequence(),"addRow");
	newManagedAction(submenu, "addColumn",tr("Add Column","table"), SLOT(addColumnCB()),QKeySequence(),"addCol");
	newManagedAction(submenu, "removeRow",tr("Remove Row","table"), SLOT(removeRowCB()),QKeySequence(),"remRow");
	newManagedAction(submenu, "removeColumn",tr("Remove Column","table"), SLOT(removeColumnCB()),QKeySequence(),"remCol");
	newManagedAction(submenu, "cutColumn",tr("Cut Column","table"), SLOT(cutColumnCB()),QKeySequence(),"cutCol");
	newManagedAction(submenu, "pasteColumn",tr("Paste Column","table"), SLOT(pasteColumnCB()),QKeySequence(),"pasteCol");
	newManagedAction(submenu, "addHLine",tr("Add \\hline","table"), SLOT(addHLineCB()));
	newManagedAction(submenu, "remHLine",tr("Remove \\hline","table"), SLOT(remHLineCB()));
	newManagedAction(submenu, "insertTableTemplate",tr("Remodel Table Using Template","table"), SLOT(insertTableTemplate()));
	newManagedAction(submenu, "alignColumns", tr("Align Columns"), SLOT(alignTableCols()),QKeySequence(),"alignCols");
	submenu=newManagedMenu(menu, "magicComments",tr("Add magic comments ..."));
	newManagedAction(submenu, "addMagicRoot", tr("Insert root document name as TeX comment"), SLOT(addMagicRoot()));
	newManagedAction(submenu, "addMagicLang", tr("Insert language as TeX comment"), SLOT(InsertSpellcheckMagicComment()));
	newManagedAction(submenu, "addMagicCoding", tr("Insert document coding as TeX comment"), SLOT(addMagicCoding()));

	menu=newManagedMenu("main/math",tr("&Math"));
	menu->setProperty("defaultSlot", QByteArray(SLOT(InsertFromAction())));
	//wizards
	
	menu=newManagedMenu("main/wizards",tr("&Wizards"));
	newManagedAction(menu, "start",tr("Quick &Start..."), SLOT(QuickDocument()));
	newManagedAction(menu, "letter",tr("Quick &Letter..."), SLOT(QuickLetter()));
	
	menu->addSeparator();
	newManagedAction(menu, "tabular",tr("Quick &Tabular..."), SLOT(QuickTabular()));
	newManagedAction(menu, "tabbing",tr("Quick T&abbing..."), SLOT(QuickTabbing()));
	newManagedAction(menu, "array",tr("Quick &Array..."), SLOT(QuickArray()));
    newManagedAction(menu, "graphic",tr("Insert &Graphic..."), SLOT(QuickGraphics()), QKeySequence(), "image");
#ifdef Q_OS_WIN
	if (QSysInfo::windowsVersion() >= QSysInfo::WV_WINDOWS7) {
        newManagedAction(menu, "math",tr("Math Assistant..."), SLOT(QuickMath()), QKeySequence(), "TexTablet");
	}
#endif

	menu=newManagedMenu("main/bibliography",tr("&Bibliography"));
	if (!bibtexEntryActions) {
		bibtexEntryActions = new QActionGroup(this);
		foreach (const BibTeXType& bt, BibTeXDialog::getPossibleEntryTypes(BibTeXDialog::BIBTEX)) {
			QAction *act = newManagedAction(menu,"bibtex/"+bt.name.mid(1), bt.description, SLOT(InsertBibEntryFromAction()));
			act->setData(bt.name);
			act->setActionGroup(bibtexEntryActions);
		}
	} else {
		foreach (const BibTeXType& bt, BibTeXDialog::getPossibleEntryTypes(BibTeXDialog::BIBTEX))
			newManagedAction(menu,"bibtex/"+bt.name.mid(1), bt.description, SLOT(InsertBibEntryFromAction()))->setData(bt.name);
	}

	if (!biblatexEntryActions) {
		biblatexEntryActions = new QActionGroup(this);
		foreach (const BibTeXType& bt, BibTeXDialog::getPossibleEntryTypes(BibTeXDialog::BIBLATEX)) {
			QAction *act = newManagedAction(menu,"biblatex/"+bt.name.mid(1), bt.description, SLOT(InsertBibEntryFromAction()));
			act->setData(bt.name);
			act->setActionGroup(biblatexEntryActions);
		}
	} else {
		foreach (const BibTeXType& bt, BibTeXDialog::getPossibleEntryTypes(BibTeXDialog::BIBLATEX))
			newManagedAction(menu,"biblatex/"+bt.name.mid(1), bt.description, SLOT(InsertBibEntryFromAction()))->setData(bt.name);
	}
	menu->addSeparator();
	newManagedEditorAction(menu, "clean", tr("&Clean"), "cleanBib");
	menu->addSeparator();
	newManagedAction(menu, "dialog", tr("&Insert Bibliography Entry..."), SLOT(InsertBibEntry()));
	menu->addSeparator();
	QMenu *bibTypeMenu = newManagedMenu(menu, "type", tr("Type"));
	if (!bibTypeActions) {
		bibTypeActions = new QActionGroup(this);
		bibTypeActions->setExclusive(true);
		act = newManagedAction(bibTypeMenu, "bibtex", tr("BibTeX"), SLOT(SetBibTypeFromAction()));
		act->setData("bibtex");
		act->setCheckable("true");
		act->setChecked(true);
		bibTypeActions->addAction(act);
		act = newManagedAction(bibTypeMenu, "biblatex", tr("BibLaTeX"), SLOT(SetBibTypeFromAction()));
		act->setData("biblatex");
		act->setCheckable("true");
		bibTypeActions->addAction(act);
	}
	act = newManagedAction(bibTypeMenu, "bibtex", tr("BibTeX"), SLOT(SetBibTypeFromAction()));
	act = newManagedAction(bibTypeMenu, "biblatex", tr("BibLaTeX"), SLOT(SetBibTypeFromAction()));
	act->trigger(); // initialize menu for specified type




	//  User
	menu=newManagedMenu("main/macros",tr("Ma&cros"));
	updateUserMacros();
	scriptengine::macros = &configManager.completerConfig->userMacros;

	//---view---
	menu=newManagedMenu("main/view",tr("&View"));
	newManagedAction(menu, "prevdocument",tr("Previous Document"), SLOT(gotoPrevDocument()), QList<QKeySequence>() << Qt::CTRL+Qt::Key_PageUp << Qt::CTRL+Qt::SHIFT+Qt::Key_Tab);
	newManagedAction(menu, "nextdocument",tr("Next Document"), SLOT(gotoNextDocument()), QList<QKeySequence>() << Qt::CTRL+Qt::Key_PageDown << Qt::CTRL+Qt::Key_Tab);
	newManagedMenu(menu, "documents",tr("Open Documents"));
	newManagedAction(menu, "documentlist",tr("List Of Open Documents"), SLOT(viewDocumentList()));

	newManagedAction(menu, "focuseditor", tr("Focus Editor"), SLOT(focusEditor()), QList<QKeySequence>() << Qt::ALT+Qt::CTRL+Qt::Key_Left);
	newManagedAction(menu, "focusviewer", tr("Focus Viewer"), SLOT(focusViewer()), QList<QKeySequence>() << Qt::ALT+Qt::CTRL+Qt::Key_Right);
	
	menu->addSeparator();
	newManagedAction(menu, "structureview",leftPanel->toggleViewAction());
	newManagedAction(menu, "outputview",outputView->toggleViewAction());
    newManagedAction(menu, "enlargePDF",tr("Show embedded PDF large"),SLOT(enlargeEmbeddedPDFViewer()));
    newManagedAction(menu, "shrinkPDF",tr("Show embedded PDF small"),SLOT(shrinkEmbeddedPDFViewer()));

	newManagedAction(menu, "closesomething",tr("Close Something"), SLOT(viewCloseSomething()), Qt::Key_Escape);
	
	menu->addSeparator();
	submenu=newManagedMenu(menu, "collapse", tr("Collapse"));
	newManagedEditorAction(submenu, "all", tr("Everything"), "foldEverything", 0, "", QList<QVariant>() << false);
	newManagedAction(submenu, "block", tr("Nearest Block"), SLOT(viewCollapseBlock()));
	for (int i=1; i<=4; i++)
		newManagedEditorAction(submenu, QString::number(i), tr("Level %1").arg(i), "foldLevel", 0, "", QList<QVariant>() << false << i);
	submenu=newManagedMenu(menu, "expand", tr("Expand"));
	newManagedEditorAction(submenu, "all", tr("Everything"), "foldEverything", 0, "", QList<QVariant>() << true);
	newManagedAction(submenu, "block", tr("Nearest Block"), SLOT(viewExpandBlock()));
	for (int i=1; i<=4; i++)
		newManagedEditorAction(submenu, QString::number(i), tr("Level %1").arg(i), "foldLevel", 0, "", QList<QVariant>() << true << i);
	
	submenu=newManagedMenu(menu, "grammar", tr("Grammar errors"));
	static bool showGrammarType[8] = {false};
	for (int i=0;i<8;i++) configManager.registerOption(QString("Grammar/Display Error %1").arg(i), &showGrammarType[i], true);
	newManagedAction(submenu, "0", tr("Word Repetition"), "toggleGrammar", 0, "", QList<QVariant>() << 0);
	newManagedAction(submenu, "1", tr("Long-range Word Repetition"), "toggleGrammar", 0, "", QList<QVariant>() << 1);
	newManagedAction(submenu, "2", tr("Bad words"), "toggleGrammar", 0, "", QList<QVariant>() << 2);
    newManagedAction(submenu, "3", tr("Grammar Mistake"), "toggleGrammar", 0, "", QList<QVariant>() << 3);
	for (int i=4;i<8;i++)
        newManagedAction(submenu, QString("%1").arg(i), tr("Grammar Mistake Special %1").arg(i-3), "toggleGrammar", 0, "", QList<QVariant>() << i);
	for (int i=0;i<submenu->actions().size();i++)
		if (!submenu->actions()[i]->isCheckable()){
			submenu->actions()[i]->setCheckable(true);
			configManager.linkOptionToObject(&showGrammarType[i], submenu->actions()[i], 0);
			LatexEditorView::setGrammarOverlayDisabled(i,!submenu->actions()[i]->isChecked());
		}
	
	menu->addSeparator();
	newManagedAction(menu, "alignwindows", tr("Align Windows"), SLOT(viewAlignWindows()));
	fullscreenModeAction=newManagedAction(menu, "fullscreenmode",tr("Fullscreen Mode"));
	fullscreenModeAction->setCheckable(true);
	connectUnique(fullscreenModeAction, SIGNAL(toggled(bool)), this, SLOT(setFullScreenMode()));
	connectUnique(menuBar(), SIGNAL(doubleClicked()), fullscreenModeAction, SLOT(toggle()));

	menu->addSeparator();
	QMenu *hlMenu = newManagedMenu(menu, "highlighting", tr("Highlighting"));
	if (!highlightLanguageActions) {
		highlightLanguageActions = new QActionGroup(this);
		highlightLanguageActions->setExclusive(true);
		connect(highlightLanguageActions, SIGNAL(triggered(QAction*)), this, SLOT(viewSetHighlighting(QAction*)));
		connect(hlMenu, SIGNAL(aboutToShow()), this, SLOT(showHighlightingMenu()));
		int id = 0;
		foreach (const QString &s, m_languages->languages()) {
#ifdef QT_NO_DEBUG
			if (s == "TXS Test Results") continue;
#endif
			QAction *act = newManagedAction(hlMenu, QString::number(id++), tr(qPrintable(s)));
			act->setData(s);
			act->setCheckable(true);
			hlMenu->addAction(act);
			highlightLanguageActions->addAction(act);
		}
	} else {
		int id = 0;
		foreach (const QString &s, m_languages->languages())
			newManagedAction(hlMenu, QString::number(id++), tr(qPrintable(s)));
	}

	//---options---
	menu=newManagedMenu("main/options",tr("&Options"));
    newManagedAction(menu, "config",tr("&Configure TeXstudio..."), SLOT(GeneralOptions()), 0,"configure")->setMenuRole(QAction::PreferencesRole);
	
	menu->addSeparator();
	newManagedAction(menu, "loadProfile",tr("Load &Profile..."), SLOT(loadProfile()));
	newManagedAction(menu, "saveProfile",tr("S&ave Profile..."), SLOT(saveProfile()));
	newManagedAction(menu, "saveSettings",tr("Save Current Settings","menu"), SLOT(SaveSettings()));
	menu->addSeparator();
	ToggleAct=newManagedAction(menu, "masterdocument",tr("Define Current Document as '&Master Document'"), SLOT(ToggleMode()));
	ToggleRememberAct=newManagedAction(menu, "remembersession",tr("Automatically Restore &Session at Next Start"));
	ToggleRememberAct->setCheckable(true);
	
	//---help---
	menu=newManagedMenu("main/help",tr("&Help"));
    newManagedAction(menu, "latexreference",tr("LaTeX Reference..."), SLOT(LatexHelp()), 0,"help");
    newManagedAction(menu, "usermanual",tr("User Manual..."), SLOT(UserManualHelp()), 0,"help");
	newManagedAction(menu, "texdocdialog", tr("Packages Help..."), SLOT(TexdocHelp()));
	
	menu->addSeparator();
	newManagedAction(menu, "checkinstall",tr("Check LaTeX Installation"), SLOT(checkLatexInstall()));
    newManagedAction(menu, "appinfo",tr("About TeXstudio..."), SLOT(HelpAbout()), 0,"appicon")->setMenuRole(QAction::AboutRole);
	
	//additional elements for development
	
	
	//-----context menus-----
	if (LatexEditorView::getBaseActions().empty()) { //only called at first menu created
		QList<QAction*> baseContextActions;
		QAction *sep = new QAction(menu);
		sep->setSeparator(true);
		baseContextActions << getManagedActions(QStringList() << "copy" << "cut" << "paste", "main/edit/");
		baseContextActions << getManagedActions(QStringList() << "main/edit2/pasteAsLatex" << "main/edit2/convertTo" << "main/edit/selectall");
		baseContextActions << sep;
		baseContextActions << getManagedActions(QStringList() << "previewLatex" << "removePreviewLatex", "main/edit2/");
		LatexEditorView::setBaseActions(baseContextActions);
	}
	
	structureTreeView->setObjectName("StructureTree");
	structureTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
	newManagedAction(structureTreeView,"CopySection",tr("Copy"), SLOT(editSectionCopy()));
	newManagedAction(structureTreeView,"CutSection",tr("Cut"), SLOT(editSectionCut()));
	newManagedAction(structureTreeView,"PasteBefore",tr("Paste Before"), SLOT(editSectionPasteBefore()));
	newManagedAction(structureTreeView,"PasteAfter",tr("Paste After"), SLOT(editSectionPasteAfter()));
	QAction* sep = new QAction(structureTreeView);
	sep->setSeparator(true);
	structureTreeView->addAction(sep);
	newManagedAction(structureTreeView,"IndentSection",tr("Indent Section"), SLOT(editIndentSection()));
	newManagedAction(structureTreeView,"UnIndentSection",tr("Unindent Section"), SLOT(editUnIndentSection()));
	connect(structureTreeView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(StructureContextMenu(QPoint)));
	
	configManager.updateRecentFiles(true);
	
	configManager.modifyMenuContents();
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
		//qDebug() << "Icon:" << id << zw.toString();
		++i;
	}
	//setup customizable toolbars
	for (int i=0;i<configManager.managedToolBars.size();i++){
		ManagedToolBar &mtb = configManager.managedToolBars[i];
		if (!mtb.toolbar) { //create actual toolbar on first call
			if (mtb.name == "Central") mtb.toolbar = centralToolBar;
			else mtb.toolbar = addToolBar(tr(qPrintable(mtb.name)));
			mtb.toolbar->setObjectName(mtb.name);
			addAction(mtb.toolbar->toggleViewAction());
			if(mtb.name=="Spelling") addToolBarBreak();
		} else mtb.toolbar->clear();
		foreach (const QString& actionName, mtb.actualActions){
			if (actionName == "separator") mtb.toolbar->addSeparator(); //Case 1: Separator
			else if (actionName.startsWith("tags/")) {
				//Case 2: One of the xml tag widgets mapped on a toolbutton
				int tagCategorySep=actionName.indexOf("/",5);
				XmlTagsListWidget* tagsWidget = findChild<XmlTagsListWidget*>(actionName.left(tagCategorySep));
				if (!tagsWidget) continue;
				if(!tagsWidget->isPopulated())
					tagsWidget->populate();
				QStringList list=tagsWidget->tagsTxtFromCategory(actionName.mid(tagCategorySep+1));
				if (list.isEmpty()) continue;
				QToolButton* combo=createComboToolButton(mtb.toolbar,list,QList<QIcon>(),0,this,SLOT(insertXmlTagFromToolButtonAction()));
				combo->setProperty("tagsID", actionName);
				mtb.toolbar->addWidget(combo);
			} else {
				QObject *obj=configManager.menuParent->findChild<QObject*>(actionName);
				QAction *act=qobject_cast<QAction*>(obj);
				if (act) {
					//Case 3: A normal QAction
					if(act->icon().isNull())
                        act->setIcon(QIcon("appicon"));
					mtb.toolbar->addAction(act);
				} else {
					QMenu* menu=qobject_cast<QMenu*>(obj);
					if (!menu) {
						qWarning("Unknown toolbar command %s", qPrintable(actionName));
						continue;
					}
					//Case 4: A submenu mapped on a toolbutton
					configManager.watchedMenus << actionName;
					QStringList list;
					QList<QIcon> icons;
					foreach (const QAction* act, menu->actions())
						if (!act->isSeparator()) {
							list.append(act->text());
							icons.append(act->icon());
						}
					//TODO: Is the callToolButtonAction()-slot really needed? Can't we just add the menu itself as the menu of the qtoolbutton, without creating a copy? (should be much faster)
					QToolButton* combo=createComboToolButton(mtb.toolbar,list,icons,0,this,SLOT(callToolButtonAction()));
					combo->setProperty("menuID", actionName);
					mtb.toolbar->addWidget(combo);
				}
			}
		}
		if(mtb.actualActions.empty()) mtb.toolbar->setVisible(false);
	}
}

void Texmaker::UpdateAvailableLanguages() {
	if (spellLanguageActions) delete spellLanguageActions;
	
	spellLanguageActions = new QActionGroup(statusTbLanguage);
	spellLanguageActions->setExclusive(true);
	
	foreach (const QString& s, spellerManager.availableDicts()) {
		QAction *act = new QAction(spellLanguageActions);
		act->setText(spellerManager.prettyName(s));
		act->setData(QVariant(s));
		act->setCheckable(true);
		connect(act, SIGNAL(triggered()), this, SLOT(ChangeEditorSpeller()));
	}
	
	QAction *act = new QAction(spellLanguageActions);
	act->setSeparator(true);
	act = new QAction(spellLanguageActions);
	act->setText(tr("Default")+QString(": %1").arg(spellerManager.prettyName(spellerManager.defaultSpellerName())));
	act->setData(QVariant("<default>"));
	connect(act, SIGNAL(triggered()), this, SLOT(ChangeEditorSpeller()));
	act->setCheckable(true);
	act->setChecked(true);
	
	act = new QAction(spellLanguageActions);
	act->setSeparator(true);
	act = new QAction(spellLanguageActions);
	act->setText(tr("Insert language as TeX comment"));
	connect(act, SIGNAL(triggered()), this, SLOT(InsertSpellcheckMagicComment()));
	
	statusTbLanguage->addActions(spellLanguageActions->actions());
	
	if (currentEditorView()) {
		EditorSpellerChanged(currentEditorView()->getSpeller());
	} else {
		EditorSpellerChanged("<default>");
	}
}

void Texmaker::createStatusBar() {
	QStatusBar * status=statusBar();
	status->setContextMenuPolicy(Qt::PreventContextMenu);
	
	QAction *act;
	QToolButton *tb;
	act = getManagedAction("main/view/structureview");
	if (act) {
		tb = new QToolButton(status);
		tb->setCheckable(true);
		tb->setChecked(act->isChecked());
		tb->setAutoRaise(true);
		tb->setIcon(act->icon());
		tb->setToolTip(act->toolTip());
		connect(tb, SIGNAL(clicked()), act, SLOT(trigger()));
		connect(act, SIGNAL(toggled(bool)), tb, SLOT(setChecked(bool)));
		status->addPermanentWidget(tb, 0);
	}
	act = getManagedAction("main/view/outputview");
	if (act) {
		tb = new QToolButton(status);
		tb->setCheckable(true);
		tb->setChecked(act->isChecked());
		tb->setAutoRaise(true);
		tb->setIcon(act->icon());
		tb->setToolTip(act->toolTip());
		connect(tb, SIGNAL(clicked()), act, SLOT(trigger()));
		connect(act, SIGNAL(toggled(bool)), tb, SLOT(setChecked(bool)));
		status->addPermanentWidget(tb, 0);
	}
	
	// spacer eating up all the space between "left" and "right" permanent widgets.
	QLabel* messageArea = new QLabel(status);
	connect(status, SIGNAL(messageChanged(QString)), messageArea, SLOT(setText(QString)));
	status->addPermanentWidget(messageArea, 1);
	
	// language
	statusTbLanguage = new QToolButton(status);
	statusTbLanguage->setToolTip(tr("Language"));
	statusTbLanguage->setPopupMode(QToolButton::InstantPopup);
	statusTbLanguage->setAutoRaise(true);
	statusTbLanguage->setMinimumWidth(status->fontMetrics().width("OOOOOOO"));
	connect(&spellerManager, SIGNAL(dictPathChanged()), this, SLOT(UpdateAvailableLanguages()));
	connect(&spellerManager, SIGNAL(defaultSpellerChanged()), this, SLOT(UpdateAvailableLanguages()));
	UpdateAvailableLanguages();
	statusTbLanguage->setText(spellerManager.defaultSpellerName());
	status->addPermanentWidget(statusTbLanguage,0);
	
	// encoding
	statusTbEncoding = new QToolButton(status);
	statusTbEncoding->setToolTip(tr("Encoding"));
	statusTbEncoding->setText(tr("Encoding")+ "  ");
	statusTbEncoding->setPopupMode(QToolButton::InstantPopup);
	statusTbEncoding->setAutoRaise(true);
	statusTbEncoding->setMinimumWidth(status->fontMetrics().width("OOOOO"));

	QSet<int> encodingMibs;
	foreach (const QString& s, configManager.commonEncodings) {
		QTextCodec *codec = QTextCodec::codecForName(s.toLocal8Bit());
		if (!codec) continue;
		encodingMibs.insert(codec->mibEnum());
	}
	foreach (int mib, encodingMibs) {
		QAction *act = new QAction(statusTbEncoding);
		act->setText(QTextCodec::codecForMib(mib)->name());
		act->setData(mib);
		statusTbEncoding->addAction(act);
		connect(act, SIGNAL(triggered()), this, SLOT(changeTextCodec()));
	}
	act = new QAction(statusTbEncoding);
	act->setSeparator(true);
	statusTbEncoding->addAction(act);
	act = new QAction(statusTbEncoding);
	act->setText(tr("More Encodings..."));
	statusTbEncoding->addAction(act);
	connect(act, SIGNAL(triggered()), this, SLOT(editSetupEncoding()));
	act = new QAction(statusTbEncoding);
	act->setSeparator(true);
	statusTbEncoding->addAction(act);

	act = new QAction(statusTbEncoding);
	act->setText(tr("Insert encoding as TeX comment"));
	statusTbEncoding->addAction(act);
	connect(act, SIGNAL(triggered()), this, SLOT(addMagicCoding()));

	status->addPermanentWidget(statusTbEncoding,0);


	statusLabelMode=new QLabel(status);
	statusLabelProcess=new QLabel(status);
	status->addPermanentWidget(statusLabelProcess, 0);
	status->addPermanentWidget(statusLabelMode, 0);
	for (int i=1; i<=3; i++) {
        QPushButton* pb = new QPushButton(getRealIcon(QString("bookmark%1").arg(i)), "", status);
		pb->setToolTip(tr("Click to jump to the bookmark"));
		connect(pb, SIGNAL(clicked()), getManagedAction(QString("main/edit/gotoBookmark/bookmark%1").arg(i)), SIGNAL(triggered()));
		pb->setMaximumSize(20,20);
		pb->setFlat(true);
		status->addPermanentWidget(pb, 0);
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
		title=TEXSTUDIO;
	} else {
		QString file = QDir::toNativeSeparators(getCurrentFileName());
		if (file.isEmpty() && EditorTabs->currentIndex()>=0)
			file = EditorTabs->tabText(EditorTabs->currentIndex());
		title = file + " - " + TEXSTUDIO;
		if (currentEditorView()->editor) {
			NewDocumentStatus();
			NewDocumentLineEnding();
			//currentEditorView()->editor->setFocus();
		}
	}
	setWindowTitle(title);
	//updateStructure();
	updateUndoRedoStatus();
	cursorPositionChanged();
	if (documents.singleMode()) {
		//outputView->resetMessagesAndLog();
		if(currentEditorView()) completerNeedsUpdate();
	}
	QString finame=getCurrentFileName();
	if (finame!="") configManager.lastDocument=finame;
}

void Texmaker::updateMasterDocumentCaption(){
	if (documents.singleMode()){
		ToggleAct->setText(tr("Define Current Document as 'Master Document'"));
		statusLabelMode->setText(QString(" %1 ").arg(tr("Normal Mode")));
	} else {
		QString shortName = documents.masterDocument->getFileInfo().fileName();
		ToggleAct->setText(tr("Normal Mode (current master document: ")+shortName+")");
		statusLabelMode->setText(QString(" %1 ").arg(tr("Master Document")+ ": "+shortName));
	}
}

void Texmaker::editorTabChanged(int index){
	UpdateCaption();
	if (index < 0) return; //happens if no tab is open
	if (configManager.watchedMenus.contains("main/view/documents"))
		updateToolBarMenu("main/view/documents");
	if (currentEditorView()) {
		EditorSpellerChanged(currentEditorView()->getSpeller());
		currentEditorView()->lastUsageTime = QDateTime::currentDateTime();
	}
}

void Texmaker::EditorTabMoved(int from,int to){
	//documents.aboutToUpdateLayout();
	documents.move(from,to);
	//documents.updateLayout();
	updateOpenDocumentMenu(false);
}

void Texmaker::editorAboutToChangeByTabClick(LatexEditorView *edFrom, LatexEditorView *edTo) {
	Q_UNUSED(edTo);
	saveEditorCursorToHistory(edFrom);
}

void Texmaker::CloseEditorTab(int tab) {
	int cur=EditorTabs->currentIndex();
	int total=EditorTabs->count();
	EditorTabs->setCurrentIndex(tab);
	fileClose();
	if (cur>tab) cur--;//removing moves to left
	if (total!=EditorTabs->count() && cur!=tab)//if user clicks cancel stay in clicked editor
		EditorTabs->setCurrentIndex(cur);
}
void Texmaker::showMarkTooltipForLogMessage(QList<int> errors) {
	if (!currentEditorView()) return;
	REQUIRE(outputView->getLogWidget());
	REQUIRE(outputView->getLogWidget()->getLogModel());
	QString msg = outputView->getLogWidget()->getLogModel()->htmlErrorTable(errors);
	currentEditorView()->setLineMarkToolTip(msg);
}

void Texmaker::NewDocumentStatus() {
	LatexEditorView* edView = currentEditorView();
	if (!edView) return;
	int index=EditorTabs->currentIndex();
	if (qobject_cast<QEditor*>(sender()) && edView->editor!=sender()){
		edView=0;
		for (int i=0;i<EditorTabs->count();i++)
			if (qobject_cast<LatexEditorView*>(EditorTabs->widget(i))->editor==sender()){
				edView=	qobject_cast<LatexEditorView*>(EditorTabs->widget(i));
				index=i;
				break;
			}
		if (!edView) return;
	}
	QEditor * ed = edView->editor;
	actSave->setEnabled(ed->isContentModified() || ed->fileName().isEmpty());
	static QIcon modified = getRealIcon("modified"), empty =  QIcon(":/images/empty.png"); //cache icons, getRealIcon is *really* slow
	EditorTabs->setTabIcon(index, ed->isContentModified() ? modified : empty);
	QString tabText = edView->displayName().replace("&", "&&");
	if (EditorTabs->tabText(index) != tabText) {
		EditorTabs->setTabText(index, tabText);
		updateOpenDocumentMenu(true);
	}
	// child ?
	LatexDocument *doc=edView->document;
	LatexDocument *masterDoc=doc->getTopMasterDocument();
	QString tooltip=QDir::toNativeSeparators(ed->fileName());
	if(masterDoc!=doc){
		tooltip+=tr("\nincluded document in %1").arg(masterDoc->getName());
	}
	EditorTabs->setTabToolTip(index, tooltip);
	if (currentEditorView()->editor->getFileCodec()) {
		QTextCodec *codec = currentEditorView()->editor->getFileCodec();
		statusTbEncoding->setText(codec->name()+"  ");
		QStringList aliases;
		foreach (const QByteArray& b, codec->aliases()) {
			aliases << QString(b);
		}
		if (!aliases.isEmpty()) {
			statusTbEncoding->setToolTip(tr("Encoding Aliases: ") + aliases.join(", "));
		} else {
			statusTbEncoding->setToolTip(tr("Encoding"));
		}
	}
	else {
		statusTbEncoding->setText(tr("Encoding")+"  ");
		statusTbEncoding->setToolTip(tr("Encoding"));
	}
}

void Texmaker::NewDocumentLineEnding(){
	if (!currentEditorView()) return;
	QDocument::LineEnding le = currentEditorView()->editor->document()->lineEnding();
	if (le==QDocument::Conservative) le= currentEditorView()->editor->document()->originalLineEnding();
	switch (le) {
#ifdef Q_OS_WIN32
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
}

void Texmaker::updateUndoRedoStatus() {
	if (currentEditor()) {
		actSave->setEnabled(!currentEditor()->document()->isClean() || currentEditor()->fileName().isEmpty());
		bool canUndo=currentEditor()->document()->canUndo();
		if(!canUndo && configManager.svnUndo){
		    QVariant zw=currentEditor()->property("undoRevision");
		    int undoRevision=zw.canConvert<int>()?zw.toInt():0;
		    if(undoRevision>=0)
			canUndo=true;
		}
		actUndo->setEnabled(canUndo);
		actRedo->setEnabled(currentEditor()->document()->canRedo());
	} else {
		actSave->setEnabled(false);
		actUndo->setEnabled(false);
		actRedo->setEnabled(false);
	}
}

LatexEditorView *Texmaker::currentEditorView() const {
	return EditorTabs->currentEditorView();
}
QEditor* Texmaker::currentEditor() const{
	LatexEditorView* edView = currentEditorView();
	if (!edView) return 0;
	return edView->editor;
}
void Texmaker::configureNewEditorView(LatexEditorView *edit) {
	REQUIRE(m_languages);REQUIRE(edit->codeeditor);
	m_languages->setLanguage(edit->codeeditor->editor(), ".tex");
	
	//edit->setFormats(m_formats->id("environment"),m_formats->id("referenceMultiple"),m_formats->id("referencePresent"),m_formats->id("referenceMissing"));
	
	connect(edit->editor, SIGNAL(undoAvailable(bool)), this, SLOT(updateUndoRedoStatus()));
	connect(edit->editor, SIGNAL(redoAvailable(bool)), this, SLOT(updateUndoRedoStatus()));
	connect(edit->editor, SIGNAL(contentModified(bool)), this, SLOT(NewDocumentStatus()));
	connect(edit->editor->document(), SIGNAL(lineEndingChanged(int)), this, SLOT(NewDocumentLineEnding()));
	connect(edit->editor, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChanged()));
	connect(edit->editor, SIGNAL(cursorHovered()), this, SLOT(cursorHovered()));
	connect(edit->editor, SIGNAL(emitWordDoubleClicked()), this, SLOT(cursorHovered()));
	connect(edit, SIGNAL(showMarkTooltipForLogMessage(QList<int>)),this,SLOT(showMarkTooltipForLogMessage(QList<int>)));
	connect(edit, SIGNAL(needCitation(const QString&)),this,SLOT(InsertBibEntry(const QString&)));
	connect(edit, SIGNAL(showPreview(QString)),this,SLOT(showPreview(QString)));
    connect(edit, SIGNAL(showImgPreview(QString)),this,SLOT(showImgPreview(QString)));
	connect(edit, SIGNAL(showPreview(QDocumentCursor)),this,SLOT(showPreview(QDocumentCursor)));
	connect(edit, SIGNAL(gotoDefinition(QDocumentCursor)),this,SLOT(editGotoDefinition(QDocumentCursor)));
	connect(edit, SIGNAL(syncPDFRequested(QDocumentCursor)), this, SLOT(syncPDFViewer(QDocumentCursor)));
	connect(edit, SIGNAL(openFile(QString)),this,SLOT(openExternalFile(QString)));
	connect(edit, SIGNAL(openFile(QString,QString)),this,SLOT(openExternalFile(QString,QString)));
	connect(edit, SIGNAL(bookmarkRemoved(QDocumentLineHandle*)), bookmarks, SLOT(bookmarkDeleted(QDocumentLineHandle*)));
	connect(edit, SIGNAL(bookmarkAdded(QDocumentLineHandle*,int)), bookmarks, SLOT(bookmarkAdded(QDocumentLineHandle*,int)));
	connect(edit, SIGNAL(mouseBackPressed()), this, SLOT(goBack()));
	connect(edit, SIGNAL(mouseForwardPressed()), this, SLOT(goForward()));
	connect(edit, SIGNAL(cursorChangeByMouse()), this, SLOT(saveCurrentCursorToHistory()));
	connect(edit, SIGNAL(colonTyped()), this, SLOT(NormalCompletion()));
    connect(edit, SIGNAL(openInternalDocViewer(QString,QString)),this,SLOT(openInternalDocViewer(QString,QString)));

	connect(edit->editor,SIGNAL(fileReloaded()),this,SLOT(fileReloaded()));
	connect(edit->editor,SIGNAL(fileInConflict()),this,SLOT(fileInConflict()));
	connect(edit->editor,SIGNAL(fileAutoReloading(QString)),this,SLOT(fileAutoReloading(QString)));
	
    if (Guardian::instance()) { // Guardian is not yet there when this is called at program startup
		connect(edit->editor,SIGNAL(slowOperationStarted()), Guardian::instance(), SLOT(slowOperationStarted()));
		connect(edit->editor,SIGNAL(slowOperationEnded()), Guardian::instance(), SLOT(slowOperationEnded()));
    }
	connect(edit, SIGNAL(linesChanged(QString,const void*,QList<LineInfo>,int)), grammarCheck, SLOT(check(QString,const void*,QList<LineInfo>,int)));
	
	connect(edit, SIGNAL(spellerChanged(QString)), this, SLOT(EditorSpellerChanged(QString)));
	edit->setSpellerManager(&spellerManager);
	edit->setSpeller("<default>");
	
}

//complete the new editor view configuration (edit->document is set)
void Texmaker::configureNewEditorViewEnd(LatexEditorView *edit,bool reloadFromDoc,bool hidden){
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
	connect(edit->document, SIGNAL(bookmarkLineUpdated(int)), bookmarks, SLOT(updateLineWithBookmark(int)));
	connect(edit,SIGNAL(thesaurus(int,int)),this,SLOT(editThesaurus(int,int)));
	connect(edit,SIGNAL(changeDiff(QPoint)),this,SLOT(editChangeDiff(QPoint)));
	connect(edit,SIGNAL(saveCurrentCursorToHistoryRequested()),this,SLOT(saveCurrentCursorToHistory()));
	edit->document->saveLineSnapshot(); // best guess of the lines used during last latex compilation
	
	if(!hidden){
		EditorTabs->insertEditor(edit, reloadFromDoc ? documents.documents.indexOf(edit->document,0) : -1);
		updateOpenDocumentMenu(false);

		edit->editor->setFocus();
		UpdateCaption();
		NewDocumentStatus();
	}
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
QString Texmaker::getRelativeFileName(const QString & file,QString basepath,bool keepSuffix){
    return getRelativeBaseNameToPath(file,basepath,true,keepSuffix);
}

bool Texmaker::ActivateEditorForFile(QString f, bool checkTemporaryNames, bool setFocus) {
	LatexEditorView* edView = getEditorViewFromFileName(f, checkTemporaryNames);
	if (!edView) return false;
	saveCurrentCursorToHistory();
	if (!EditorTabs->containsEditor(edView)) return false;
	EditorTabs->setCurrentEditor(edView);
	if (setFocus) {
		edView->editor->setFocus();
	}
	return true;
}
///////////////////FILE//////////////////////////////////////

LatexEditorView *Texmaker::editorViewForLabel(LatexDocument *doc, const QString &label) {
	// doc can be any document, in which the label is valid
	REQUIRE_RET(doc, 0);
	QMultiHash<QDocumentLineHandle*,int> result = doc->getLabels(label);
	if (result.count() <= 0) return 0;
	QDocumentLine line(result.keys().first());
	LatexDocument *targetDoc = qobject_cast<LatexDocument *>(line.document());
	REQUIRE_RET(targetDoc, 0);
	return qobject_cast<LatexEditorView *>(targetDoc->getEditorView());
}

void guessLanguageFromContent(QLanguageFactory* m_languages, QEditor* e){
	QDocument* doc = e->document();
	if (doc->lineCount() == 0) return;
	if (doc->line(0).text().startsWith("<?xml") ||
	    doc->line(0).text().startsWith("<!DOCTYPE"))
		m_languages->setLanguage(e, ".xml");
}

LatexEditorView* Texmaker::load(const QString &f , bool asProject, bool hidden,bool recheck) {
	QString f_real=f;
#ifdef Q_OS_WIN32
	QRegExp regcheck("/([a-zA-Z]:[/\\\\].*)");
	if (regcheck.exactMatch(f)) f_real=regcheck.cap(1);
#endif
	
	
#ifndef NO_POPPLER_PREVIEW
	if (f_real.endsWith(".pdf",Qt::CaseInsensitive)) {
		if (PDFDocument::documentList().isEmpty())
			newPdfPreviewer();
		PDFDocument::documentList().first()->loadFile(f_real,QString(f_real).replace(".pdf", ".tex"));
		PDFDocument::documentList().first()->show();
		PDFDocument::documentList().first()->setFocus();
		return 0;
	}
#endif
	
	if (f_real.endsWith(".log",Qt::CaseInsensitive) &&
			txsConfirm(QString("Do you want to load file %1 as LaTeX log file?").arg(QFileInfo(f).completeBaseName()))) {
		outputView->getLogWidget()->loadLogFile(f,documents.getTemporaryCompileFileName());
		setLogMarksVisible(true);
		return 0;
	}

	if(!hidden)
		raise();
	
	//test is already opened
	LatexEditorView* existingView = getEditorViewFromFileName(f_real);
	LatexDocument *doc;
	if (!existingView) {
		doc = documents.findDocumentFromName(f_real);
		if (doc) existingView = doc->getEditorView();
	}
	if (existingView) {
		if (asProject) documents.setMasterDocument(existingView->document);
		if(existingView->document->isHidden()){
            existingView->editor->setLineWrapping(configManager.editorConfig->wordwrap>0);
			documents.deleteDocument(existingView->document,true);
            existingView->editor->setFlag(QEditor::SilentReloadOnExternalChanges,existingView->document->remeberAutoReload);
			documents.addDocument(existingView->document,false);
			EditorTabs->insertEditor(existingView);
			updateOpenDocumentMenu(false);
            updateStructure(false,existingView->document,true);
			existingView->editor->setFocus();
			UpdateCaption();
			NewDocumentStatus();
			return existingView;
		}
		EditorTabs->setCurrentEditor(existingView);
		return existingView;
	}

	// find closed master doc
	if(doc){
		LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig,doc);
        edit->setLatexPackageList(&latexPackageList);
		edit->document=doc;
		edit->editor->setFileName(doc->getFileName());
		disconnect(edit->editor->document(),SIGNAL(contentsChange(int, int)),edit->document,SLOT(patchStructure(int,int)));
		configureNewEditorView(edit);
		if (edit->editor->fileInfo().suffix()!="tex")
			m_languages->setLanguage(edit->editor, f_real);
		if (!edit->editor->languageDefinition())
			guessLanguageFromContent(m_languages, edit->editor);

		doc->setLineEnding(edit->editor->document()->originalLineEnding());
		doc->setEditorView(edit); //update file name (if document didn't exist)

		configureNewEditorViewEnd(edit,!hidden,hidden);
		//edit->document->initStructure();
		//updateStructure(true);
		if(!hidden){
			ShowStructure();
			bookmarks->restoreBookmarks(edit);
		}
		return edit;
	}
	
	//load it otherwise
	if (!QFile::exists(f_real)) return 0;
	QFile file(f_real);
	if (!file.open(QIODevice::ReadOnly)) {
        if(!hidden)
            QMessageBox::warning(this,tr("Error"), tr("You do not have read permission to the file %1.").arg(f_real));
		return 0;
	}
	file.close();

	bool bibTeXmodified=documents.bibTeXFilesModified;
	
	doc=new LatexDocument(this);
	LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig,doc);
    edit->setLatexPackageList(&latexPackageList);
    if(hidden)
        edit->editor->setLineWrapping(false); //disable linewrapping in hidden docs to speed-up updates
	configureNewEditorView(edit);
	
	edit->document=documents.findDocument(f_real);
	if (!edit->document) {
		edit->document=doc;
		edit->document->setEditorView(edit);
        documents.addDocument(edit->document,hidden);
	} else edit->document->setEditorView(edit);

	if (edit->editor->fileInfo().suffix()!="tex")
		m_languages->setLanguage(edit->editor, f_real);
	
	//QTime time;
	//time.start();
    edit->editor->load(f_real,QDocument::defaultCodec());

	if (!edit->editor->languageDefinition())
		guessLanguageFromContent(m_languages, edit->editor);


	//qDebug() << "Load time: " << time.elapsed();
	edit->editor->document()->setLineEndingDirect(edit->editor->document()->originalLineEnding());
	
	edit->document->setEditorView(edit); //update file name (if document didn't exist)
	
    configureNewEditorViewEnd(edit,asProject,hidden);
	
	//check for svn conflict
    if(!hidden){
        checkSVNConflicted();
	
        MarkCurrentFileAsRecent();
    }
	
    documents.updateMasterSlaveRelations(doc,recheck);

    if(recheck){
        edit->updateLtxCommands();
    }
	
    if(!hidden){
        if (QFile::exists(f_real + ".recover.bak~")
                && QFileInfo(f_real + ".recover.bak~").lastModified() > QFileInfo(f_real).lastModified()) {
            if (txsConfirm(tr("A crash recover file from %1 has been found for \"%2\".\nDo you want to restore it?").arg(QFileInfo(f_real + ".recover.bak~").lastModified().toString()).arg(f_real))){
                QFile f(f_real + ".recover.bak~");
                if (f.open(QFile::ReadOnly)) {
                    QByteArray ba = f.readAll();
                    QString recovered = QTextCodec::codecForMib(MIB_UTF8)->toUnicode(ba); //TODO: chunk loading?
                    edit->document->setText(recovered, true);
                } else txsWarning(tr("Failed to open recover file \"%1\".").arg(f_real + ".recover.bak~"));
            }
        }

    }
	
    updateStructure(true,doc,true);

    if(!hidden)
        ShowStructure();
	bookmarks->restoreBookmarks(edit);
	
	if (asProject) documents.setMasterDocument(edit->document);
	
	if (outputView->getLogWidget()->logPresent()) {
		updateLogEntriesInEditors();
		setLogMarksVisible(true);
	}
	if (!bibTeXmodified)
		documents.bibTeXFilesModified=false; //loading a file can change the list of included bib files, but we won't consider that as a modification of them, because then they don't have to be recompiled
	LatexDocument* master = edit->document->getTopMasterDocument();
	if (master) foreach (const FileNamePair& fnp, edit->document->mentionedBibTeXFiles().values()) {
		Q_ASSERT(!fnp.absolute.isEmpty());
		master->lastCompiledBibTeXFiles.insert(fnp.absolute);
	}
	
	
#ifndef Q_OS_MAC
    if(!hidden){
        if (windowState() == Qt::WindowMinimized || !isVisible() || !QApplication::activeWindow()) {
            show();
            if (windowState()==Qt::WindowMinimized)
                setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
            show();
            raise();
            QApplication::setActiveWindow(this);
            activateWindow();
            setFocus();
            edit->editor->setFocus();
        }
    }
	//raise();
    //#ifdef Q_OS_WIN32
	//        if (IsIconic (this->winId())) ShowWindow(this->winId(), SW_RESTORE);
	//#endif
#endif
	
	runScriptsInList(Macro::ST_LOAD_THIS_FILE, doc->localMacros);

	emit infoLoadFile(f_real);
	
	return edit;
}

void Texmaker::completerNeedsUpdate(){
	mCompleterNeedsUpdate=true;
}

void Texmaker::needUpdatedCompleter(){
	if (mCompleterNeedsUpdate)
		updateCompleter();
}
void Texmaker::updateUserToolMenu(){
	CommandMapping cmds = buildManager.getAllCommands();
	QStringList order = buildManager.getCommandsOrder();
	QStringList ids;
	QStringList displayName;
	for (int i=0;i<order.size();i++){
		const CommandInfo &ci = cmds.value(order[i]);
		if (!ci.user) continue;
		ids << ci.id;
		displayName << ci.displayName;
	}
	configManager.updateListMenu("main/tools/user", displayName, "cmd", true, SLOT(commandFromAction()), Qt::ALT+Qt::SHIFT+Qt::Key_F1, false, 0);
	QMenu* m = getManagedMenu("main/tools/user"); REQUIRE(m);
	QList<QAction *> actions = m->actions();
	for (int i=0;i<actions.size();i++)
		actions[i]->setData(BuildManager::TXS_CMD_PREFIX+ids[i]);
}

#include "QMetaMethod"
void Texmaker::linkToEditorSlot(QAction* act, const char* methodName, const QList<QVariant>& args){
	REQUIRE(act);
	connectUnique(act, SIGNAL(triggered()), this, SLOT(relayToEditorSlot()));
	act->setProperty("primarySlot", QString(SLOT(relayToEditorSlot())));
	QByteArray signature = createMethodSignature(methodName, args);
	if (!args.isEmpty())
		act->setProperty("args", QVariant::fromValue<QList<QVariant> >(args));
	for (int i=0;i<LatexEditorView::staticMetaObject.methodCount();i++)
#if QT_VERSION>=0x050000
        if (signature == LatexEditorView::staticMetaObject.method(i).methodSignature()) {
			act->setProperty("editorViewSlot", methodName);
			return;
		} //else qDebug() << LatexEditorView::staticMetaObject.method(i).signature();
	for (int i=0;i<QEditor::staticMetaObject.methodCount();i++)
        if (signature == QEditor::staticMetaObject.method(i).methodSignature()) {
			act->setProperty("editorSlot", methodName);
			return;
		}
#else
        if (signature == LatexEditorView::staticMetaObject.method(i).signature()) {
            act->setProperty("editorViewSlot", methodName);
            return;
        } //else qDebug() << LatexEditorView::staticMetaObject.method(i).signature();
    for (int i=0;i<QEditor::staticMetaObject.methodCount();i++)
        if (signature == QEditor::staticMetaObject.method(i).signature()) {
            act->setProperty("editorSlot", methodName);
            return;
        }
#endif
	
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

void Texmaker::autoRunScripts(){
	QStringList vers = QString(QT_VERSION_STR).split('.');
	Q_ASSERT(vers.length() >= 2);
	int major = vers.at(0).toInt();
	int minor = vers.at(1).toInt();
	if (!hasAtLeastQt(major,minor))
		txsWarning(tr("%1 has been compiled with Qt %2, but is running with Qt %3.\nPlease get the correct runtime library (e.g. .dll or .so files).\nOtherwise there might be random errors and crashes.")
							 .arg(TEXSTUDIO).arg(QT_VERSION_STR).arg(qVersion()));
	runScripts(Macro::ST_TXS_START);
}

void Texmaker::runScripts(int trigger){
	runScriptsInList(trigger, configManager.completerConfig->userMacros);
}

void Texmaker::runScriptsInList(int trigger, const QList<Macro> &scripts) {
	foreach (const Macro &macro, scripts) {
		if (macro.isActiveForTrigger((Macro::SpecialTrigger)trigger))
			insertUserTag(macro.tag, trigger);
	}
}

void Texmaker::fileNewInternal(QString fileName) {
	LatexDocument *doc = new LatexDocument(this);
	LatexEditorView *edit = new LatexEditorView (0, configManager.editorConfig, doc);
    edit->setLatexPackageList(&latexPackageList);
	if (configManager.newFileEncoding)
		edit->editor->setFileCodec(configManager.newFileEncoding);
	else
		edit->editor->setFileCodec(QTextCodec::codecForName("utf-8"));
	doc->clearUndo(); // inital file codec setting should not be undoable
	edit->editor->setFileName(fileName);

	configureNewEditorView(edit);

	edit->document = doc;
	edit->document->setEditorView(edit);
	documents.addDocument(edit->document);

	configureNewEditorViewEnd(edit);
	edit->updateLtxCommands();
    if(!fileName.isEmpty())
        fileSave(true);
}

void Texmaker::fileNew(QString fileName) {
	fileNewInternal(fileName);
	emit infoNewFile();
}

void Texmaker::fileAutoReloading(QString fname){
	LatexDocument* document=documents.findDocument(fname);
	if (!document) return;
	document->initClearStructure();
}

void Texmaker::fileReloaded(){
	QEditor *mEditor = qobject_cast<QEditor *>(sender());
	if(mEditor==currentEditor()){
		currentEditorView()->document->initClearStructure();
		updateStructure(true);
	}else{
		LatexDocument* document=documents.findDocument(mEditor->fileName());
		if (!document) return;
		document->initClearStructure();
        document->patchStructure(0,-1);
	}
}

void Texmaker::fileMakeTemplate() {
	if (!currentEditorView())
		return;
	
	MakeTemplateDialog templateDialog(TemplateManager::userTemplateDir(), currentEditor()->fileName());
	if (templateDialog.exec()) {
		// save file
		QString fn = templateDialog.suggestedFile();
		QString old_name=currentEditor()->fileName();
		QTextCodec *mCodec=currentEditor()->getFileCodec();
		currentEditor()->setFileCodec(QTextCodec::codecForName("utf-8"));
		currentEditor()->save(fn);
		currentEditor()->setFileName(old_name);
		currentEditor()->setFileCodec(mCodec);

		// save metaData
		QFileInfo fi(fn);
		fn = fi.absoluteFilePath();
		fn.remove(fn.lastIndexOf('.'), 4);
		fn.append(".json");
		QFile file(fn);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			txsInformation(tr("Could not write template meta data:") + "\n" + fn);
		} else {
			QTextStream out(&file);
			out.setCodec("UTF-8");
			out << templateDialog.generateMetaData();
			file.close();
		}
	}
}

void Texmaker::templateEdit(const QString &fname){
	load(fname, false);
}

void Texmaker::fileNewFromTemplate() {
	TemplateManager tmplMgr;
	connectUnique(&tmplMgr, SIGNAL(editRequested(QString)), this, SLOT(templateEdit(QString)));

	TemplateSelector *dialog = tmplMgr.createLatexTemplateDialog();
	if (!dialog->exec()) return;

	TemplateHandle th = dialog->selectedTemplate();
	if (!th.isValid()) return;

	if (dialog->createInFolder()) {
		th.createInFolder(dialog->creationFolder());
		if (th.isMultifile()) {
			QDir dir(dialog->creationFolder());
			foreach (const QString &f, th.filesToOpen()) {
				QFileInfo fi(dir, f);
				if (fi.exists() && fi.isFile())
					load(fi.absoluteFilePath());
			}
		} else {
			QDir dir(dialog->creationFolder());
			QFileInfo fi(dir, QFileInfo(th.file()).fileName());
			load(fi.absoluteFilePath());
		}
	} else {
		QString fname = th.file();
		QFile file(fname);
		if (!file.exists()) {
			txsWarning(tr("File not found:")+QString("\n%1").arg(fname));
			return;
		}
		if (!file.open(QIODevice::ReadOnly)) {
			txsWarning(tr("You do not have read permission to this file:")+QString("\n%1").arg(fname));
			return;
		}

		//set up new editor with template
		fileNewInternal();
		LatexEditorView *edit = currentEditorView();

		QString mTemplate;
		QTextStream in(&file);
		in.setCodec(QTextCodec::codecForMib(MIB_UTF8));
		while (!in.atEnd()) {
			QString line = in.readLine();
			mTemplate+=line+"\n";
		}
		CodeSnippet toInsert(mTemplate, false);
		bool flag=edit->editor->flag(QEditor::AutoIndent);
		edit->editor->setFlag(QEditor::AutoIndent,false);
		toInsert.insert(edit->editor);
		edit->editor->setFlag(QEditor::AutoIndent,flag);
		edit->editor->setCursorPosition(0,0, false);
		edit->editor->nextPlaceHolder();
		edit->editor->ensureCursorVisible(QEditor::KeepSurrounding);

		emit infoNewFromTemplate();
	}
	delete dialog;
}

void Texmaker::insertTableTemplate() {
	QEditor *m_edit=currentEditor();
	if(!m_edit)
		return;
	QDocumentCursor c=m_edit->cursor();
	if(!LatexTables::inTableEnv(c))
		return;

	// select Template
	TemplateManager tmplMgr;
	connectUnique(&tmplMgr, SIGNAL(editRequested(QString)), this, SLOT(templateEdit(QString)));
	if (tmplMgr.tableTemplateDialogExec()) {
		QString fname = tmplMgr.selectedTemplateFile();
		QFile file(fname);
		if (!file.exists()) {
			txsWarning(tr("File not found:")+QString("\n%1").arg(fname));
			return;
		}
		if (!file.open(QIODevice::ReadOnly)) {
			txsWarning(tr("You do not have read permission to this file:")+QString("\n%1").arg(fname));
			return;
		}
		QString tableDef=LatexTables::getSimplifiedDef(c);
		QString tableText=LatexTables::getTableText(c);
		//remove table
		c.removeSelectedText();
		m_edit->setCursor(c);
		// split table text into line/column list
		QStringList values;
		QList<int> starts;
		QString env;
        //tableText.remove("\n");
		tableText.remove("\\hline");
		if(tableText.startsWith("\\begin")){
			LatexParser::resolveCommandOptions(tableText,0,values,&starts);
			env=values.takeFirst();
			env.remove(0,1);
			env.remove(env.length()-1,1);
            // special treatment for tabu/longtabu
            if((env=="tabu"||env=="longtabu")&&values.count()<1){
                int startExtra=env.length()+8;
                int endExtra=tableText.indexOf("{",startExtra);
                if(endExtra>=0 && endExtra>startExtra){
                    QString textHelper=tableText;
                    textHelper.remove(startExtra,endExtra-startExtra); // remove to/spread definition
                    values.clear();
                    starts.clear();
                    LatexParser::resolveCommandOptions(textHelper,0,values,&starts);
                    for(int i=1;i<starts.count();i++){
                        starts[i]+=endExtra-startExtra;
                    }
                }
                if(!values.isEmpty())
                    values.takeFirst();
            }
			if(LatexTables::tabularNames.contains(env)){
				if(!values.isEmpty()){
					int i=starts.at(1);
					i+=values.first().length();
					tableText.remove(0,i);
				}
			}
			if(LatexTables::tabularNamesWithOneOption.contains(env)){
				if(values.size()>1){
					int i=starts.at(2);
					i+=values.at(1).length();
					tableText.remove(0,i);
				}
			}
			tableText.remove(QRegExp("\\\\end\\{"+env+"\\}$"));
		}
		tableText.replace("\\endhead","\\\\");
		QStringList lines=tableText.split("\\\\");
		QList<QStringList> tableContent;
		foreach(QString line,lines){
            //line=line.simplified();
            if(line.isEmpty() || line=="\n")
				continue;
			QStringList elems=line.split(QRegExp("&"));
            if(elems.count()>0){
                if(elems[0].startsWith("\n"))
                    elems[0]=elems[0].mid(1);
            }
            //QList<QString>::iterator i;
            /*for(i=elems.begin();i!=elems.end();i++){
				QString elem=*i;
                *i=elem.simplified();
            }*/
			
			// handle \& correctly
			for(int i=elems.size()-1;i>=0;--i){
				if(elems.at(i).endsWith("\\")){
					QString add=elems.at(i)+elems.at(i+1);
					elems.replace(i,add);
					elems.removeAt(i+1);
				}
			}
			tableContent<<elems;
		}
		LatexTables::generateTableFromTemplate(currentEditorView(),fname,tableDef,tableContent,env);
	}
}

void Texmaker::alignTableCols() {
  if (!currentEditor()) return;
  QDocumentCursor cur(currentEditor()->cursor());
  if(!cur.isValid())
      return;
  LatexTables::alignTableCols(cur);
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

    recheckLabels=false; // impede label rechecking on hidden docs
    QList<LatexEditorView*>listViews;
	foreach (const QString& fn, files)
        listViews<<load(fn);

    // update ref/labels in one go;
    QList<LatexDocument*> completedDocs;
    foreach(LatexEditorView* edView,listViews){
        if(!edView)
            continue;
        LatexDocument *docBase=edView->getDocument();
        foreach(LatexDocument *doc,docBase->getListOfDocs()){
            doc->recheckRefsLabels();
            if(completedDocs.contains(doc))
                continue;
            LatexEditorView *edView=doc->getEditorView();
            if(edView){
                edView->updateLtxCommands(true);
                completedDocs<<doc->getListOfDocs();
            }
        }
    }
    recheckLabels=true;
    // update completer
    if(currentEditorView())
        updateCompleter(currentEditorView());
}

void Texmaker::fileRestoreSession(bool showProgress){

	QFileInfo f(QDir(configManager.configBaseDir), "lastSession.txss");
	Session s;
	if (f.exists()) {
		if (!s.load(f.filePath())) {
			txsCritical(tr("Loading of last session failed."));
		}
	} else {
		// fallback to loading from the config (import the session saved by TXS <= 2.5.1)
		s.load(configManager);
	}
	restoreSession(s, showProgress);
}

void Texmaker::fileSave(const bool saveSilently) {
	if (!currentEditor())
		return;
	
    if (currentEditor()->fileName()=="" || !QFileInfo(currentEditor()->fileName()).exists()){
        removeDiffMarkers();// clean document from diff markers first
        fileSaveAs(currentEditor()->fileName(),saveSilently);
    } else {
		/*QFile file( *filenames.find( currentEditorView() ) );
	if ( !file.open( QIODevice::WriteOnly ) )
	 {
	 QMessageBox::warning( this,tr("Error"),tr("The file could not be saved. Please check if you have write permission."));
	 return;
	 }*/
        removeDiffMarkers();// clean document from diff markers first
		currentEditor()->save();
		currentEditor()->document()->markViewDirty();//force repaint of line markers (yellow -> green)
		MarkCurrentFileAsRecent();
		if(configManager.autoCheckinAfterSave) {
			checkin(currentEditor()->fileName());
			if(configManager.svnUndo) currentEditor()->document()->clearUndo();
		}
		emit infoFileSaved(currentEditor()->fileName());
	}
	UpdateCaption();
	//updateStructure(); (not needed anymore for autoupdate)
}

void Texmaker::fileSaveAs(const QString& fileName,const bool saveSilently) {
	if (!currentEditorView())
		return;
	
	// select a directory/filepath
	QString currentDir=QDir::homePath();
	if (fileName.isEmpty()) {
		if (currentEditor()->fileInfo().isFile()) {
			currentDir = currentEditor()->fileInfo().absoluteFilePath();
        } else {
            if (!configManager.lastDocument.isEmpty()) {
                QFileInfo fi(configManager.lastDocument);
                if (fi.exists() && fi.isReadable())
                    currentDir=fi.absolutePath();
            }
            currentDir = currentDir +"/"+ tr("document");
        }
	} else {
		currentDir = fileName;
		/*QFileInfo currentFile(fileName);
	if (currentFile.absoluteDir().exists())
	 currentDir = fileName;*/
	}
	
	// get a file name
    QString fn =fileName;
    if(!saveSilently || fn.isEmpty())
        fn = QFileDialog::getSaveFileName(this,tr("Save As"),currentDir,fileFilters, &selectedFileFilter);
	if (!fn.isEmpty()) {
		static QRegExp fileExt("\\*(\\.[^ )]+)");
		if (fileExt.indexIn(selectedFileFilter) > -1) {
			//add
			int lastsep=qMax(fn.lastIndexOf("/"),fn.lastIndexOf("\\"));
			int lastpoint=fn.lastIndexOf(".");
			if (lastpoint <= lastsep) //if both aren't found or point is in directory name
				fn.append(fileExt.cap(1));
		}
		if (getEditorViewFromFileName(fn) && getEditorViewFromFileName(fn) != currentEditorView()) {
			// trying to save with same name as another already existing file
			LatexEditorView *otherEdView = getEditorViewFromFileName(fn);
			if (!otherEdView->document->isClean()) {
				txsWarning(tr("Saving under the name\n"
							  "%1\n"
                              "is currently not possible because a modified version of a file\n"
							  "with this name is open in TeXstudio. You have to save or close\n"
							  "this other file before you can overwrite it.").arg(fn));
				return;
			}
			// other editor does not contain unsaved changes, so it can be closed
			LatexEditorView *currentEdView = currentEditorView();
			EditorTabs->setCurrentEditor(otherEdView);
			fileClose();
			EditorTabs->setCurrentEditor(currentEdView);
		}
		
		// save file
        removeDiffMarkers();// clean document from diff markers first
		currentEditor()->save(fn);
		currentEditorView()->document->setEditorView(currentEditorView()); //update file name
		MarkCurrentFileAsRecent();
		
		//update Master/Child relations
		LatexDocument *doc=currentEditorView()->document;
		documents.updateMasterSlaveRelations(doc);
		
		
		if(configManager.autoCheckinAfterSave){
			if(svnadd(currentEditor()->fileName())){
				checkin(currentEditor()->fileName(),"txs auto checkin",configManager.svnKeywordSubstitution);
			} else {
				//create simple repository
				svncreateRep(currentEditor()->fileName());
				svnadd(currentEditor()->fileName());
				checkin(currentEditor()->fileName(),"txs auto checkin",configManager.svnKeywordSubstitution);
			}
			// set SVN Properties if desired
			if(configManager.svnKeywordSubstitution){
				QString cmd = BuildManager::CMD_SVN + " propset svn:keywords \"Date Author HeadURL Revision\" \""+currentEditor()->fileName()+"\"";
				statusLabelProcess->setText(QString(" svn propset svn:keywords "));
				runCommand(cmd, 0);
			}
		}
		
		EditorTabs->setTabText(EditorTabs->currentIndex(),currentEditor()->name().replace("&","&&"));
		EditorTabs->setTabToolTip(EditorTabs->currentIndex(), QDir::toNativeSeparators(currentEditor()->fileName()));
		updateOpenDocumentMenu(true);
		if (currentEditor()->fileInfo().suffix()!="tex")
			m_languages->setLanguage(currentEditor(), fn);
		
		emit infoFileSaved(currentEditor()->fileName());
	}
	
	UpdateCaption();
}

void Texmaker::fileSaveAll() {
	fileSaveAll(true,true);
}
void Texmaker::fileSaveAll(bool alsoUnnamedFiles, bool alwaysCurrentFile) {
	//LatexEditorView *temp = new LatexEditorView(EditorView,colorMath,colorCommand,colorKeyword);
	//temp=currentEditorView();
	REQUIRE(EditorTabs);

	LatexEditorView *currentEdView = currentEditorView();

	foreach (LatexEditorView *edView, EditorTabs->editors()) {
		REQUIRE(edView->editor);

		if (edView->editor->fileName().isEmpty()){
			if ((alsoUnnamedFiles || (alwaysCurrentFile && edView==currentEdView) ) ) {
				EditorTabs->setCurrentEditor(edView);
				fileSaveAs();
			} else if (!edView->document->getTemporaryFileName().isEmpty())
				edView->editor->saveCopy(edView->document->getTemporaryFileName());
			//else if (edView->editor->isInConflict()) {
			//edView->editor->save();
			//}
		} else if (edView->editor->isContentModified() || edView->editor->isInConflict()){
            removeDiffMarkers();// clean document from diff markers first
			edView->editor->save(); //only save modified documents

			if (edView->editor->fileName().endsWith(".bib")) {
				QString temp=edView->editor->fileName();
				temp=temp.replace(QDir::separator(),"/");
				documents.bibTeXFilesModified = documents.bibTeXFilesModified  || documents.mentionedBibTeXFiles.contains(temp);//call bibtex on next compilation (this would also set as soon as the user switch to a tex file, but he could compile before switching)
			}

			emit infoFileSaved(edView->editor->fileName());
		}
		//currentEditor()->save();
		//UpdateCaption();
	}

	if (currentEditorView() != currentEdView)
		EditorTabs->setCurrentEditor(currentEdView);
	//UpdateCaption();
}

//TODO: handle svn in all these methods

void Texmaker::fileUtilCopyMove(bool move){
	QString fn = documents.getCurrentFileName();
	if (fn.isEmpty()) return;
	QString newfn = QFileDialog::getSaveFileName(this,move ? tr("Rename/Move") : tr("Copy"),fn,fileFilters, &selectedFileFilter);
	if (newfn.isEmpty()) return;
	if (fn == newfn) return;
	QFile::Permissions permissions = QFile(fn).permissions();
	if (move) fileSaveAs(newfn, true);
	else currentEditor()->saveCopy(newfn);
	if (documents.getCurrentFileName() != newfn) return;
	if (move) QFile(fn).remove();
	QFile(newfn).setPermissions(permissions); //keep permissions. (better: actually move the file, keeping the inode. but then all that stuff (e.g. master/slave) has to be updated here
}


void Texmaker::fileUtilDelete(){
	QString fn = documents.getCurrentFileName();
	if (fn.isEmpty()) return;
	if (txsConfirmWarning(tr("Do you really want to delete the file \"%1\"?").arg(fn)))
		QFile(fn).remove();
}

void Texmaker::fileUtilRevert(){
	if (!currentEditor()) return;
	QString fn = documents.getCurrentFileName();
	if (fn.isEmpty()) return;
	if (txsConfirmWarning(tr("Do you really want to revert the file \"%1\"?").arg(documents.getCurrentFileName())))
		currentEditor()->reload();
}

void Texmaker::fileUtilPermissions(){
	QString fn = documents.getCurrentFileName();
	if (fn.isEmpty()) return;

	QFile f(fn);

	int permissionsRaw = f.permissions();
	int permissionsUnixLike = ((permissionsRaw & 0x7000) >> 4) | (permissionsRaw & 0x0077); //ignore qt "user" flags
	QString permissionsUnixLikeHex = QString::number(permissionsUnixLike, 16);
	QString permissions;
	const QString PERMISSIONSCODES = "rwx";
	int flag = QFile::ReadUser; REQUIRE(QFile::ReadUser == 0x400);
	int temp = permissionsUnixLike;
	for (int b=0;b<3;b++) {
		for (int i=0;i<3;i++, flag >>= 1)
			permissions += (temp & flag) ? PERMISSIONSCODES[i] : QChar('-');
		flag >>= 1;
	}
	QString oldPermissionsUnixLikeHex = permissionsUnixLikeHex, oldPermissions = permissions;


	UniversalInputDialog uid;
	uid.addVariable(&permissionsUnixLikeHex, tr("Numeric permissions"));
	uid.addVariable(&permissions, tr("Verbose permissions"));
	if (uid.exec() == QDialog::Accepted && (permissionsUnixLikeHex != oldPermissionsUnixLikeHex || permissions != oldPermissions)) {
		if (permissionsUnixLikeHex != oldPermissionsUnixLikeHex)
			permissionsRaw = permissionsUnixLikeHex.toInt(0, 16);
		else {
			permissionsRaw = 0;
			int flag = QFile::ReadUser;
			int p = 0;
			for (int b=0;b<3;b++) {
				for (int i=0;i<3;i++, flag >>= 1) {
					if (permissions[p] == '-') p++;
					else if (permissions[p] == PERMISSIONSCODES[i]) {
						permissionsRaw |= flag;
						p++;
					} else if (!QString("rwx").contains(permissions[p])) {
						txsWarning("invalid character in permission: "+permissions[p]);
						return;
					}
					if (p >= permissions.length()) p=0; //wrap around
				}
				flag >>= 1;
			}
		}
		permissionsRaw = ((permissionsRaw << 4) & 0x7000) | permissionsRaw; //use qt "user" as owner flags
		f.setPermissions(QFile::Permissions(permissionsRaw)) ;
	}


}

void Texmaker::fileUtilCopyFileName(){
	QApplication::clipboard()->setText(documents.getCurrentFileName());
}

void Texmaker::fileUtilCopyMasterFileName(){
	QApplication::clipboard()->setText(documents.getCompileFileName());
}


void Texmaker::fileClose() {
	if (!currentEditorView())	return;
	bookmarks->updateBookmarks(currentEditorView());
	QFileInfo fi = currentEditorView()->document->getFileInfo();

repeatAfterFileSavingFailed:
	if (currentEditorView()->editor->isContentModified()) {
		switch (QMessageBox::warning(this, TEXSTUDIO,
																 tr("The document \"%1\" contains unsaved work. "
																		"Do you want to save it before closing?").arg(currentEditorView()->displayName()),
																 tr("Save and Close"), tr("Don't Save and Close"), tr("Cancel"),
																 0,
																 2)) {
		case 0:
			fileSave();
			if (currentEditorView()->editor->isContentModified())
				goto repeatAfterFileSavingFailed;
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

#ifndef NO_POPPLER_PREVIEW
	//close associated embedded pdf viewer
	foreach(PDFDocument *viewer,PDFDocument::documentList())
		if (viewer->autoClose && viewer->getMasterFile()==fi)
			viewer->close();
#endif
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
repeatAfterFileSavingFailed:
		if (currentEditorView()->editor->isContentModified()) {
			switch (QMessageBox::warning(this, TEXSTUDIO,
																	 tr("The document \"%1\" contains unsaved work. "
																			"Do you want to save it before closing?").arg(currentEditorView()->displayName()),
																	 tr("Save and Close"), tr("Don't Save and Close"), tr("Cancel"),
																	 0,
																	 2)) {
			case 0:
				fileSave();
				if (currentEditorView()->editor->isContentModified())
					goto repeatAfterFileSavingFailed;
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
#ifndef NO_POPPLER_PREVIEW
	foreach (PDFDocument* viewer, PDFDocument::documentList())
		viewer->saveGeometryToConfig();
#endif
	SaveSettings();
	bool accept = closeAllFilesAsking();
	if (accept){
		if (userMacroDialog) delete userMacroDialog;
		spellerManager.unloadAll();  //this saves the ignore list
	}
	programStopped = true;
    Guardian::shutdown();
	return accept;
}
void Texmaker::closeEvent(QCloseEvent *e) {
	if (canCloseNow())  e->accept();
	else e->ignore();
}

void Texmaker::updateUserMacros(bool updateMenu){
	if (updateMenu) configManager.updateUserMacroMenu();
	for (int i=0; i<configManager.completerConfig->userMacros.size(); i++) {
		configManager.completerConfig->userMacros[i].parseTriggerLanguage(m_languages);
	}
}

void Texmaker::fileOpenRecent() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	QString fn = action->data().toString();
	if (!QFile::exists(fn)) {
		if (txsConfirmWarning(tr("The file \"%1\" does not exist anymore. Do you want to remove it from the recent file list?").arg(fn))){
			if (configManager.recentFilesList.removeAll(fn))
				configManager.updateRecentFiles();
			return;
		}
	}
	load(fn);
}
void Texmaker::fileOpenAllRecent() {
	foreach (const QString& s, configManager.recentFilesList)
		load(s);
}
void Texmaker::fileRecentList(){
	if (fileSelector) fileSelector.data()->deleteLater();
	fileSelector = new FileSelector(this, true);

	fileSelector.data()->init(QStringList() << configManager.recentProjectList << configManager.recentFilesList, 0);

	connect(fileSelector.data(), SIGNAL(fileChoosen(QString,int,int,int)), SLOT(fileDocumentOpenFromChoosen(QString,int,int,int)));
	fileSelector.data()->setVisible(true);
	fileSelector.data()->setCentered(centralFrame->geometry());
}

void Texmaker::fileDocumentOpenFromChoosen(const QString& doc, int duplicate, int lineNr, int column){
	Q_UNUSED(duplicate);
	if (!QFile::exists(doc)) {
		if (txsConfirmWarning(tr("The file \"%1\" does not exist anymore. Do you want to remove it from the recent file list?").arg(doc))){
			if (configManager.recentFilesList.removeAll(doc) + configManager.recentProjectList.removeAll(doc) > 0)
				configManager.updateRecentFiles();
			return;
		}
	}

	if (!load(doc, duplicate < configManager.recentProjectList.count(doc))) return;
	if (lineNr < 0) return;
	REQUIRE(currentEditor());
	currentEditor()->setCursorPosition(lineNr, column);
}

bool mruEditorViewLessThan(const LatexEditorView* e1, const LatexEditorView* e2)
{
		return e1->lastUsageTime > e2->lastUsageTime;
}

void Texmaker::viewDocumentList(){
	if (fileSelector) fileSelector.data()->deleteLater();
    fileSelector = new FileSelector(this, false);

	QStringList sl;
	LatexEditorView *curEdView = currentEditorView();
	int curIndex = 0;
	QList<LatexEditorView*> editors = EditorTabs->editors();

	if (configManager.mruDocumentChooser) {
		qSort(editors.begin(), editors.end(), mruEditorViewLessThan);
		if (editors.size() > 1)
			if (editors.first() == currentEditorView())
				curIndex = 1;
	}

	int i = 0;
	foreach (LatexEditorView *edView, editors){
		sl << edView->displayName();
		if (!configManager.mruDocumentChooser && edView == curEdView) curIndex = i;
		i++;
	}

	fileSelector.data()->init(sl, curIndex);
	connect(fileSelector.data(), SIGNAL(fileChoosen(QString,int,int,int)), SLOT(viewDocumentOpenFromChoosen(QString,int,int,int)));
	fileSelector.data()->setVisible(true);
	fileSelector.data()->setCentered(centralFrame->geometry());

}

void Texmaker::viewDocumentOpenFromChoosen(const QString& doc, int duplicate, int lineNr, int column){
	if (duplicate < 0) return;
	foreach (LatexEditorView *edView, EditorTabs->editors()) {
		QString  name = edView->displayName();
		if (name == doc) {
			duplicate -= 1;
			if (duplicate < 0) {
				EditorTabs->setCurrentWidget(edView);
				if (lineNr >= 0)
					edView->editor->setCursorPosition(lineNr, column);
				edView->setFocus();
				return;
			}
		}
	}
}

void Texmaker::fileOpenFirstNonOpen(){
	foreach (const QString& f, configManager.recentFilesList)
		if (!getEditorViewFromFileName(f)){
			load(f);
			break;
		}
}

void Texmaker::fileOpenRecentProject() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	QString fn = action->data().toString();
	if (!QFile::exists(fn)) {
		if (txsConfirmWarning(tr("The file \"%1\" does not exist anymore. Do you want to remove it from the recent file list?").arg(fn))){
			if (configManager.recentProjectList.removeAll(fn))
				configManager.updateRecentFiles();
			return;
		}
	}
	load(fn, true);
}

void Texmaker::loadSession(const QString &fileName) {
	Session s;
	if (!s.load(fileName)) {
		txsCritical(tr("Loading of session failed."));
		return;
	}
	restoreSession(s);
}

void Texmaker::fileLoadSession() {
	QString openDir = QDir::homePath();
	if (currentEditorView()) {
		LatexDocument *doc = currentEditorView()->document;
		if (doc->getMasterDocument()) {
			openDir = doc->getMasterDocument()->getFileInfo().path();
		} else {
			openDir = doc->getFileInfo().path();
		}
	}
	QString fn = QFileDialog::getOpenFileName(this, tr("Load Session"), openDir, tr("TeXstudio Session") + " (*." + Session::fileExtension() + ")");
	if (fn.isNull()) return;
	loadSession(fn);
}

void Texmaker::fileSaveSession() {
	QString openDir = QDir::homePath();
	if (currentEditorView()) {
		LatexDocument *doc = currentEditorView()->document;
		if (doc->getMasterDocument()) {
			openDir = replaceFileExtension(doc->getMasterDocument()->getFileName(), Session::fileExtension());
		} else {
			openDir = replaceFileExtension(doc->getFileName(), Session::fileExtension());
		}
	}

	QString fn = QFileDialog::getSaveFileName(this, tr("Save Session"), openDir, tr("TeXstudio Session") + " (*." + Session::fileExtension() + ")");
	if (fn.isNull()) return;
	if (!getCurrentSession().save(fn))
		txsCritical(tr("Saving of session failed."));
}

void Texmaker::restoreSession(const Session &s, bool showProgress) {
	fileCloseAll();

	cursorHistory->setInsertionEnabled(false);
	QProgressDialog progress(this);
	if (showProgress) {
		progress.setMaximum(s.files().size());
		progress.setCancelButton(0);
		progress.setMinimumDuration(3000);
		progress.setLabel(new QLabel());
	}
    recheckLabels=false; // impede label rechecking on hidden docs

	bookmarks->setBookmarks(s.bookmarks()); // set before loading, so that bookmarks are automatically restored on load

	for (int i=0; i<s.files().size(); i++) {
		FileInSession f = s.files().at(i);

		if (showProgress) {
			progress.setValue(i);
			progress.setLabelText(QFileInfo(f.fileName).fileName());
		}
        LatexEditorView* edView=load(f.fileName, f.fileName==s.masterFile(),false,false);
		if (edView) {
			int line = f.cursorLine;
			int col = f.cursorCol;
			if (line >= edView->document->lineCount()) {
				line = 0;
				col = 0;
			} else {
				if (edView->document->line(line).length() < col) {
					col = 0;
				}
			}
			edView->editor->setCursorPosition(line, col);
			edView->editor->scrollToFirstLine(f.firstLine);
			edView->document->foldLines(f.foldedLines);
		}
	}
    // update ref/labels in one go;
    QList<LatexDocument*> completedDocs;
    foreach(LatexDocument *doc,documents.getDocuments()){
        doc->recheckRefsLabels();
        if(completedDocs.contains(doc))
            continue;
        LatexEditorView *edView=doc->getEditorView();
        if(edView){
            edView->updateLtxCommands(true);
            completedDocs<<doc->getListOfDocs();
        }
    }
    recheckLabels=true;

	if (showProgress) {
		progress.setValue(progress.maximum());
	}
	ActivateEditorForFile(s.currentFile());
	cursorHistory->setInsertionEnabled(true);

	if (!s.PDFFile().isEmpty()) {
		runInternalCommand("txs:///view-pdf-internal", QFileInfo(s.PDFFile()), s.PDFEmbedded()?"--embedded":"--windowed");
	}
    // update completer
    if(currentEditorView())
        updateCompleter(currentEditorView());
}

Session Texmaker::getCurrentSession() {
	Session s;

	foreach (LatexEditorView *edView, EditorTabs->editors()) {
		FileInSession f;
		f.fileName = edView->editor->fileName();
		f.cursorLine = edView->editor->cursor().lineNumber();
		f.cursorCol = edView->editor->cursor().columnNumber();
		f.firstLine = edView->editor->getFirstVisibleLine();
		f.foldedLines = edView->document->foldedLines();
		s.addFile(f);
	}
	s.setMasterFile(documents.singleMode()?"":documents.masterDocument->getFileName());
	s.setCurrentFile(currentEditorView()?currentEditor()->fileName():"");

	s.setBookmarks(bookmarks->getBookmarks());
#ifndef NO_POPPLER_PREVIEW
	if (!PDFDocument::documentList().isEmpty()) {
		PDFDocument *doc = PDFDocument::documentList().at(0);
		s.setPDFEmbedded(doc->embeddedMode);
		s.setPDFFile(doc->fileName());
	}
#endif

	return s;
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
	
	if(currentEditor()->document()->canRedo()){
		currentEditorView()->editor->redo();
	} else {
		if(configManager.svnUndo && (undoRevision>0)){
			svnUndo(true);
		}
	}
}

void Texmaker::editDebugUndoStack(){
	if (!currentEditor()) return;
	QString history = currentEditor()->document()->debugUndoStack();
	fileNew();
	currentEditor()->document()->setText(history, false);
}

void Texmaker::editCopy() {
	if ((!currentEditor() || !currentEditor()->hasFocus()) &&
			outputView->childHasFocus() ) {
		outputView->copy();
		return;
	}
	if (!currentEditorView()) return;
	currentEditorView()->editor->copy();
}

void Texmaker::editPaste() {
	if (!currentEditorView()) return;
	
	const QMimeData *d = QApplication::clipboard()->mimeData();
	if (d->hasUrls()) {
		QList<QUrl> uris=d->urls();
		
		bool onlyLocalImages = true;
		for (int i=0; i<uris.length(); i++) {
			QFileInfo fi = QFileInfo(uris.at(i).toLocalFile());
			if (!fi.exists() || !InsertGraphics::imageFormats().contains(fi.suffix())) {
				onlyLocalImages = false;
				break;
			}
		}

		if (onlyLocalImages) {
			for (int i=0; i<uris.length(); i++) {
				QuickGraphics(uris.at(i).toLocalFile());
			}
		} else {
			currentEditorView()->paste();
		}
	} else {
		currentEditorView()->paste();
	}
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
	currentEditor()->write(newText);
}

void Texmaker::editEraseLine() {
	if (!currentEditorView()) return;
	QDocumentCursor c = currentEditorView()->editor->cursor();
	c.beginEditBlock();
	c.removeSelectedText(); // reduces multi-line selections to a single line
	c.eraseLine();
	c.endEditBlock();
}
void Texmaker::editEraseEndLine() {
  if (!currentEditorView()) return;
  QDocumentCursor c = currentEditorView()->editor->cursor();
  c.movePosition(1,QDocumentCursor::EndOfLine,QDocumentCursor::KeepAnchor);
  currentEditorView()->editor->setCursor(c);
  currentEditorView()->editor->cut();
}
void Texmaker::editMoveLineUp() {
	if (!currentEditorView()) return;
	QDocumentCursor c = currentEditorView()->editor->cursor();
	QDocumentCursor anchor(c.document(), c.anchorLineNumber(), c.anchorColumnNumber());
	QDocumentCursor start = c.selectionStart();
	QDocumentCursor end = c.selectionEnd();
	if (start.lineNumber() <= 0) return;
	start.movePosition(1, QDocumentCursor::StartOfLine);
	end.movePosition(1, QDocumentCursor::EndOfLine);
	QDocumentCursor edit(start, end);
	edit.beginEditBlock();
	QString text = edit.selectedText();
	edit.removeSelectedText();
	edit.eraseLine();
	edit.movePosition(1, QDocumentCursor::PreviousLine);
	edit.movePosition(1, QDocumentCursor::StartOfLine);
	edit.insertText(text+"\n");
	edit.endEditBlock();
	c.movePosition(1, QDocumentCursor::Up);
	anchor.movePosition(1, QDocumentCursor::Up);
	currentEditorView()->editor->setCursor(QDocumentCursor(anchor, c));
}
void Texmaker::editMoveLineDown() {
	if (!currentEditorView()) return;
	QDocumentCursor c = currentEditorView()->editor->cursor();
	QDocumentCursor anchor(c.document(), c.anchorLineNumber(), c.anchorColumnNumber());
	QDocumentCursor start = c.selectionStart();
	QDocumentCursor end = c.selectionEnd();
	if (end.lineNumber() >= c.document()->lineCount()-1) return;
	start.movePosition(1, QDocumentCursor::StartOfLine);
	end.movePosition(1, QDocumentCursor::EndOfLine);
	QDocumentCursor edit(start, end);
	edit.beginEditBlock();
	QString text = edit.selectedText();
	edit.removeSelectedText();
	edit.eraseLine();
	edit.movePosition(1, QDocumentCursor::EndOfLine);
	edit.insertText("\n"+text);
	edit.endEditBlock();
	c.movePosition(1, QDocumentCursor::Down);
	anchor.movePosition(1, QDocumentCursor::Down);
	currentEditorView()->editor->setCursor(QDocumentCursor(anchor, c));
}
void Texmaker::editDuplicateLine() {
	if (!currentEditorView()) return;
	QDocumentCursor c = currentEditorView()->editor->cursor();
	QDocumentCursor start = c.selectionStart();
	QDocumentCursor end = c.selectionEnd();
	start.movePosition(1, QDocumentCursor::StartOfLine);
	end.movePosition(1, QDocumentCursor::EndOfLine);
	QDocumentCursor edit(start, end);
	//edit.beginEditBlock();
	QString text = edit.selectedText();
	start.insertText(text+"\n");
	currentEditorView()->editor->setCursor(c);
}

void Texmaker::editEraseWordCmdEnv(){
	if (!currentEditorView()) return;
	QDocumentCursor cursor = currentEditorView()->editor->cursor();
	QString line=cursor.line().text();
	QString command, value;

	// Hack to fix problem problem reported in bug report 3443336 (see also detailed description there):
	// findContext does not work at beginning of commands. Actually it would need
	// pre-context and post-context otherwise, what context is either ambigous, like in
	// \cmd|\cmd or it cannot work simultaneously at beginning and and (you cannot assign
	// the context for |\cmd and \cmd| even if \cmd is surrounded by spaces. The latter
	// both assignments make sense for editEraseWordCmdEnv().
	//
	// pre-context and post-context may be added when revising the latex parser
	//
	// Prelimiary solution part I:
	// Predictable behaviour on selections: do nothing except in easy cases
	if (cursor.hasSelection()) {
		QRegExp partOfWordOrCmd("\\\\?\\w*");
		if (!partOfWordOrCmd.exactMatch(cursor.selectedText()))
			return;
	}
	// Prelimiary solution part II:
	// If the case |\cmd is encountered, we shift the
	// cursor by one to \|cmd so the regular erase approach works.
	int col = cursor.columnNumber();
	if ((col < line.count())						// not at end of line
			&& (line.at(col) == '\\')					// likely a command/env - check further
			&& (col==0 || line.at(col-1).isSpace()))	// cmd is at start or previous char is space: non-ambiguous situation like word|\cmd
		// don't need to finally check for command |\c should be handled like \|c for any c (even space and empty)
	{
		cursor.movePosition(1);
	}

	switch (latexParser.findContext(line, cursor.columnNumber(), command, value)){
	
	case LatexParser::Command:
		if (command=="\\begin" || command=="\\end"){
			//remove environment (surrounding)
			currentEditorView()->editor->document()->beginMacro();
			cursor.movePosition(1,QDocumentCursor::EndOfWord);
			cursor.movePosition(1,QDocumentCursor::StartOfWord,QDocumentCursor::KeepAnchor);
			cursor.movePosition(1,QDocumentCursor::PreviousCharacter,QDocumentCursor::KeepAnchor);
			cursor.removeSelectedText();
			// remove curly brakets as well
			if(cursor.nextChar()==QChar('{')){
				cursor.deleteChar();
				line=cursor.line().text();
				int col=cursor.columnNumber();
				int i=findClosingBracket(line,col);
				if(i>-1) {
					cursor.movePosition(i-col+1,QDocumentCursor::NextCharacter,QDocumentCursor::KeepAnchor);
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
						cursor.movePosition(searchWord.length(),QDocumentCursor::NextCharacter,QDocumentCursor::KeepAnchor);
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
			cursor.movePosition(1,QDocumentCursor::PreviousCharacter,QDocumentCursor::KeepAnchor);
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

void Texmaker::editGotoDefinition(QDocumentCursor c) {
	if (!currentEditorView())	return;
	if (!c.isValid()) c=currentEditor()->cursor();
	QString command, value;
	saveCurrentCursorToHistory();
	switch (latexParser.findContext(c.line().text(), c.columnNumber(), command, value)) {
	case LatexParser::Reference:
	{
		LatexEditorView *edView = editorViewForLabel(qobject_cast<LatexDocument *>(c.document()), value);
		if (!edView) return;
		if (edView != currentEditorView()) {
			EditorTabs->setCurrentEditor(edView);
		}
		edView->gotoToLabel(value);
		break;
	}
	case LatexParser::Citation:
	{
		QString bibID = trimLeft(getParamItem(c.line().text(), c.columnNumber()));
		// try local \bibitems
		bool found = currentEditorView()->gotoToBibItem(bibID);
		if (found) break;
		// try bib files
		QString bibFile = currentEditorView()->document->findFileFromBibId(bibID);
		LatexEditorView* edView = getEditorViewFromFileName(bibFile);
		if (!edView) {
			if (!load(bibFile)) return;
			edView = currentEditorView();
		}
		int line = edView->document->findLineRegExp("@\\w+{\\s*"+bibID, 0, Qt::CaseSensitive, true, true);
		if (line < 0) {
			line = edView->document->findLineContaining(bibID); // fallback in case the above regexp does not reflect the most general case
			if (line < 0) return;
		}
		int col = edView->document->line(line).text().indexOf(bibID);
		if (col<0) col = 0;
		gotoLine(line, col, edView);
		break;
	}
	default:; //TODO: Jump to command definition
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
		txsWarning(tr("No document open"));
		return;
	}
	SpellerUtility *su = spellerManager.getSpeller(currentEditorView()->getSpeller());
	if (!su) return; // getSpeller already gives a warning message
	if (su->name() == "<none>") {
		txsWarning(tr("No dictionary available."));
		return;
	}
	if (!spellDlg) spellDlg=new SpellerDialog(this, su);
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
			m_cursor.document()->clearLanguageMatches();
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
	EditorTabs->setCurrentEditor(entry->document->getEditorView());
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
		foreach(const QString& elem,m_replace) {
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
	EditorTabs->setCurrentEditor(entry->document->getEditorView());
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
		foreach(const QString& elem,m_replace) {
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
	EditorTabs->setCurrentEditor(entry->document->getEditorView());
	QDocumentSelection sel = entry->document->sectionSelection(entry);
	editSectionCopy(sel.startLine+1,sel.endLine);
}

void Texmaker::editSectionCut() {
	// called by action
	StructureEntry *entry=LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry || !entry->document->getEditorView()) return;
	EditorTabs->setCurrentEditor(entry->document->getEditorView());
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
	EditorTabs->setCurrentEditor(entry->document->getEditorView());
	editSectionPasteBefore(entry->getRealLineNumber());
	//UpdateStructure();
}

void Texmaker::editSectionPasteAfter() {
	StructureEntry *entry=LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry || !entry->document->getEditorView()) return;
	EditorTabs->setCurrentEditor(entry->document->getEditorView());
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
void Texmaker::ReadSettings(bool reread) {
	QuickDocumentDialog::registerOptions(configManager);
	buildManager.registerOptions(configManager);
	configManager.registerOption("Files/Default File Filter", &selectedFileFilter);
	configManager.registerOption("PDFSplitter",&pdfSplitterRel,0.5);
	
	configManager.buildManager=&buildManager;
	scriptengine::buildManager=&buildManager;
	scriptengine::app=this;
	QSettings *config=configManager.readSettings(reread);
	completionBaseCommandsUpdated=true;
	
	config->beginGroup("texmaker");

	QRect screen = QApplication::desktop()->availableGeometry();
	int w= config->value("Geometries/MainwindowWidth",screen.width()-100).toInt();
	int h= config->value("Geometries/MainwindowHeight",screen.height()-100).toInt() ;
	int x= config->value("Geometries/MainwindowX",screen.x()+10).toInt();
	int y= config->value("Geometries/MainwindowY",screen.y()+10).toInt() ;
	int screenNumber = QApplication::desktop()->screenNumber(QPoint(x,y));
	screen = QApplication::desktop()->availableGeometry(screenNumber);
	if (!screen.contains(x,y)) {
		// top left is not on screen
		x = screen.x() + 10;
		y = screen.y() + 10;
		if (x+w > screen.right()) w = screen.width()-100;
		if (y+h > screen.height()) h = screen.height()-100;
	}
	resize(w,h);
	move(x,y);
	windowstate=config->value("MainWindowState").toByteArray();
	stateFullScreen=config->value("MainWindowFullssscreenState").toByteArray();
	tobemaximized=config->value("MainWindow/Maximized",false).toBool();
	tobefullscreen=config->value("MainWindow/FullScreen",false).toBool();
	
	documents.model->setSingleDocMode(config->value("StructureView/SingleDocMode",false).toBool());
	
	latexParser.structureCommands.clear();
	if(config->value("Structure/Structure Level 1","").toString()==""){
		latexParser.structureCommands << "\\part" << "\\chapter" << "\\section" << "\\subsection" << "\\subsubsection";
	}else{
		int i=0;
		QString elem;
		while((elem=config->value("Structure/Structure Level "+QString::number(i+1),"").toString())!=""){
			if (!elem.startsWith("\\")) elem=elem.prepend("\\");
			latexParser.structureCommands << elem;
			i++;
		}
	}
	
	spellerManager.setIgnoreFilePrefix(configManager.configFileNameBase);
	spellerManager.setDictPath(configManager.spellDictDir);
	spellerManager.setDefaultSpeller(configManager.spellLanguage);
	
	ThesaurusDialog::setUserPath(configManager.configFileNameBase);
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
    // import and remove old key mapping
    {config->beginGroup("Editor Key Mapping");
    QStringList sl = config->childKeys();
    if (!sl.empty()) {
        foreach (const QString& key, sl) {
            int k = key.toInt();
            if (k==0) continue;
            configManager.editorKeys.insert(QKeySequence(k).toString(), config->value(key).toInt());
        }
        QEditor::setEditOperations(configManager.editorKeys);
        config->remove("");
    }
    config->endGroup();}
    config->beginGroup("Editor Key Mapping New");
	QStringList sl = config->childKeys();
	if (!sl.empty()) {
		foreach (const QString& key, sl) {
            //int k = key.toInt(); compatibility to old ?
            if (key.isEmpty()) continue;
            configManager.editorKeys.insert(key, config->value(key).toInt());
		}
		QEditor::setEditOperations(configManager.editorKeys);
	}
	config->endGroup();
	config->endGroup();
	
	config->beginGroup("formats");
	m_formats = new QFormatFactory(":/qxs/defaultFormats.qxf", this); //load default formats from resource file
	if (config->contains("data/styleHint/bold")) {
		//rename data/styleHint/* => data/wordRepetition/*
		config->beginGroup("data");
		config->beginGroup("styleHint");
		QStringList temp = config->childKeys();
		config->endGroup();
		foreach (const QString& s, temp) config->setValue("wordRepetition/"+s, config->value("styleHint/"+s));
		config->remove("styleHint");
		config->endGroup();
	}
	
	m_formats->load(*config,true); //load customized formats
	config->endGroup();
	
	// read usageCount from file of its own.
	if (!reread) {
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

				conf->usage.clear();
				while (!in.atEnd()) {
					in >> key >> length >> usage;
					if(usage>0){
						conf->usage.insert(key,qMakePair(length,usage));
					}
				}
			}
		}
	}

	documents.settingsRead();
	
	configManager.editorConfig->settingsChanged();
	
	
}

void Texmaker::SaveSettings(const QString& configName) {
	bool asProfile=!configName.isEmpty();
	configManager.centralVisible=centralToolBar->isVisible();
	// update completion usage
	LatexCompleterConfig *conf=configManager.completerConfig;
#ifndef NO_POPPLER_PREVIEW
  //pdf viewer embedded open ?
  if(!PDFDocument::documentList().isEmpty()){
    PDFDocument* doc=PDFDocument::documentList().first();
    if(doc->embeddedMode){
	  QList<int> sz=mainHSplitter->sizes(); // set widths to 50%, eventually restore user setting
      int sum=0;
      int last=0;
      foreach(int i,sz){
        sum+=i;
        last=i;
      }
      if(last>10)
        pdfSplitterRel=1.0*last/sum;
    }
  }
#endif

	
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

		Session s = getCurrentSession();
		s.save(QFileInfo(QDir(configManager.configBaseDir), "lastSession.txss").filePath());
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
	
	
    QHash<QString, int> keys = QEditor::getEditOperations(true);
	config->remove("Editor/Use Tab for Move to Placeholder");
    config->beginGroup("Editor Key Mapping New");
	if (!keys.empty() || !config->childKeys().empty()) {
		config->remove("");
        QHash<QString, int>::const_iterator i = keys.begin();
		while (i != keys.constEnd()) {
            config->setValue(i.key(), i.value());
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

void Texmaker::updateStructure(bool initial,LatexDocument *doc,bool hidden) {
	// collect user define tex commands for completer
	// initialize List
    if ((!currentEditorView() || !currentEditorView()->document) && !doc) return;
    if(!doc)
        doc = currentEditorView()->document;
	if(initial){
        //int len=doc->lineCount();
        doc->patchStructure(0,-1); //len

		doc->updateMagicCommentScripts();
		configManager.completerConfig->userMacros << doc->localMacros;
		updateUserMacros();
	}
	else {
        doc->updateStructure();
	}
	
    if(!hidden){
        updateCompleter(doc->getEditorView());
        cursorPositionChanged();
    }
	
	//structureTreeView->reset();
}

void Texmaker::clickedOnStructureEntry(const QModelIndex & index){
	const StructureEntry* entry = LatexDocumentsModel::indexToStructureEntry(index);
	if (!entry) return;
	if (!entry->document) return;
	
	if (QApplication::mouseButtons()==Qt::RightButton) return; // avoid jumping to line if contextmenu is called

    LatexDocument *doc=entry->document;
	switch (entry->type){
	case StructureEntry::SE_DOCUMENT_ROOT:
		if (entry->document->getEditorView())
			EditorTabs->setCurrentEditor(entry->document->getEditorView());
		else
			load(entry->document->getFileName());
		break;
		
	case StructureEntry::SE_OVERVIEW:
		break;
    case StructureEntry::SE_MAGICCOMMENT:
        if(entry->valid){
            QString s=entry->title;
            QString name;
            QString val;
            doc->splitMagicComment(s, name, val);
            if ((name.toLower() == "texroot")||(name.toLower() == "root")){
                    QString fname=doc->findFileName(val);
                    load(fname);
                    break;
            }
        }
	case StructureEntry::SE_SECTION:
    case StructureEntry::SE_TODO:
	case StructureEntry::SE_LABEL:{
		int lineNr=-1;
		mDontScrollToItem = entry->type!=StructureEntry::SE_SECTION;
		LatexEditorView* edView=entry->document->getEditorView();
		QEditor::MoveFlags mflags = QEditor::NavigationToHeader;
		if (!entry->document->getEditorView()){
			lineNr=entry->getRealLineNumber();
			edView=load(entry->document->getFileName());
			if (!edView) return;
			mflags &= ~QEditor::Animated;
			//entry is now invalid
		} else lineNr=LatexDocumentsModel::indexToStructureEntry(index)->getRealLineNumber();
		gotoLine(lineNr,0,edView, mflags);
		break;
	}
		
	case StructureEntry::SE_INCLUDE:
	case StructureEntry::SE_BIBTEX:{
		saveCurrentCursorToHistory();
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
	
	QString command,value;
	LatexParser::ContextType ctx=latexParser.findContext(word, c.columnNumber(), command, value);
	switch(ctx){
	case LatexParser::Command:
        if(mCompleterNeedsUpdate) updateCompleter();
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST);
		break;
	case LatexParser::Environment:
        if(mCompleterNeedsUpdate) updateCompleter();
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST);
		break;
	case LatexParser::Reference:
        if(mCompleterNeedsUpdate) updateCompleter();
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_REF);
		break;
	case LatexParser::Citation:
        if(mCompleterNeedsUpdate) updateCompleter();
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_CITE);
		break;
    case LatexParser::Graphics:
        {QString fn=documents.getCompileFileName();
        QFileInfo fi(fn);
        completer->setWorkPath(fi.absolutePath());
        currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_GRAPHIC);}
        break;
    case LatexParser::Package:
        if(latexParser.possibleCommands["%usepackage"].contains(command)){
            QString preambel;
            if(command.endsWith("theme")){ // special treatment for  \usetheme
                preambel=command;
                preambel.remove(0,4);
                preambel.prepend("beamer");
                currentPackageList.clear();
                foreach(QString elem,latexPackageList){
                    if(elem.startsWith(preambel))
                        currentPackageList<<elem.mid(preambel.length());
                }
                completer->setPackageList(&currentPackageList);
            }else{
                completer->setPackageList(&latexPackageList);
            }
            currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_PACKAGE);
            break;
        }
	default:
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
			
			completer->setAdditionalWords(words,CT_NORMALTEXT);
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
	
	currentEditor()->document()->clearLanguageMatches();
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
		
		completer->setAdditionalWords(words, CT_NORMALTEXT);
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_NORMAL_TEXT);
	}
}

void Texmaker::InsertTag(const QString &Entity, int dx, int dy) {
	if (!currentEditorView()) return;
	int curline,curindex;
	currentEditor()->getCursorPosition(curline,curindex);
	currentEditor()->write(Entity);
	if (dy==0) currentEditor()->setCursorPosition(curline,curindex+dx);
	else if (dx==0) currentEditor()->setCursorPosition(curline+dy,0);
	else currentEditor()->setCursorPosition(curline+dy,curindex+dx);
	currentEditor()->setFocus();
	//	outputView->setMessage("");
	//logViewerTabBar->setCurrentIndex(0);
	//OutputTable->hide();
	//logpresent=false;
}

/*!
  \brief Inserts a citation at the cursor position.

  \a text may be either a complete (also custom) command like \mycite{key} or just the key. In the
  latter case it is expanded to \cite{key}. Key may also be a comma separated list of keys.
  The cursor context is evaluated: If it is within a citation command only the key is inserted at the correct
  position within the existing citation. If not, the whole command is inserted.
*/
void Texmaker::InsertCitation(const QString &text) {
	QString citeCmd, citeKey;

	if (text.length() > 1 && text.at(0) == '\\') {
		LatexParser::ContextType ctx = latexParser.findContext(text, 1, citeCmd, citeKey);
		if (LatexParser::Command != ctx) {
			citeCmd = "";
			citeKey = text;
		}
	} else {
		citeCmd = "";
		citeKey = text;
	}

	if (!currentEditorView()) return;
	QDocumentCursor c=currentEditor()->cursor();
	QString line = c.line().text();
	int cursorCol = c.columnNumber();
	QString command, value;
	LatexParser::ContextType context = latexParser.findContext(line, cursorCol, command, value);

	// Workaround: findContext yields Citation for \cite{..}|\n, but cursorCol is beyond the line,
	// which causes a crash when determining the insertCol later on.
	if (context == LatexParser::Citation && cursorCol == line.length() && cursorCol > 0) cursorCol--;

	// if cursor is directly behind a cite command, isert into that command
	if (context != LatexParser::Citation && cursorCol > 0) {
		LatexParser::ContextType prevContext = LatexParser::Unknown;
		prevContext = latexParser.findContext(line, cursorCol-1, command, value);
		if (prevContext == LatexParser::Citation) {
			cursorCol--;
			context = prevContext;
		}
	}


	int insertCol = -1;
	if (context == LatexParser::Command && latexParser.possibleCommands["%cite"].contains(command)) {
		insertCol = line.indexOf('{', cursorCol)+1;
	} else if (context == LatexParser::Citation) {
		if (cursorCol <= 0) return; // should not be possible,
		if (line.at(cursorCol) == '{' || line.at(cursorCol) == ',') {
			insertCol = cursorCol+1;
		} else if (line.at(cursorCol-1) == '{' || line.at(cursorCol-1) == ',') {
			insertCol = cursorCol;
		} else {
			int nextComma = line.indexOf(',', cursorCol);
			int closingBracket = line.indexOf('}', cursorCol);
			if (nextComma >= 0 && (closingBracket == -1 || closingBracket > nextComma)) {
				insertCol = nextComma+1;
			} else if (closingBracket >= 0) {
				insertCol = closingBracket;
			}
		}
	} else {
		QString tag;
		if (citeCmd.isEmpty())
			tag = citeCmd = "\\cite{"+citeKey+"}";
		else
			tag = text;
		InsertTag(tag, tag.length());
		return;
	}

	if (insertCol < 0 || insertCol >= line.length()) return;

	currentEditor()->setCursorPosition(c.lineNumber(), insertCol);
	// now the insertCol is either behind '{', behind ',' or at '}'
	if (insertCol > 0 && line.at(insertCol-1) == '{') {
		if (line.at(insertCol) == '}') {
			InsertTag(citeKey, citeKey.length());
		} else {
			InsertTag(citeKey+",", citeKey.length()+1);
		}
	} else if (insertCol > 0 && line.at(insertCol-1) == ',') {
		InsertTag(citeKey+",", citeKey.length()+1);
	} else {
		InsertTag(","+citeKey, citeKey.length()+1);
	}
}

void Texmaker::InsertFormula(const QString &formula) {
	if (!currentEditorView()) return;

	QString fm = formula;
	QDocumentCursor cur = currentEditorView()->editor->cursor();

	//TODO: Is there a more elegant solution to determine if the cursor is inside a math environment.
	QDocumentLine dl = cur.line();
	int col = cur.columnNumber();
	QList<int> mathFormats = QList<int>() << m_formats->id("numbers") << m_formats->id("math-keyword");
	int mathDelimiter = m_formats->id("math-delimiter");
	mathFormats.removeAll(0); // keep only valid entries in list
	if (mathFormats.contains(dl.getFormatAt(col))) {     // inside math
		fm = fm.mid(1, fm.length()-2);                   // removes surrounding $...$
	} else if (dl.getFormatAt(col) == mathDelimiter) {   // on delimiter
		while (col>0 && dl.getFormatAt(col-1) == mathDelimiter) col--;
		if (mathFormats.contains(dl.getFormatAt(col))) { // was an end-delimiter
			cur.setColumnNumber(col);
			currentEditorView()->editor->setCursor(cur);
			fm = fm.mid(1, fm.length()-2);               // removes surrounding $...$
		} else {
			//TODO is terhe a better way than hard coding? Since there is no difference in the formats between
			//start and end tags. \[|\] is hard identify without.
			QString editorFormula = dl.text().mid(col);
			if (editorFormula.startsWith("\\[")) {
				col+=2;
				currentEditorView()->editor->setCursor(cur);
				fm = fm.mid(1, fm.length()-2);           // removes surrounding $...$
			} else if (editorFormula.startsWith("$")) {
				col+=1;
				currentEditorView()->editor->setCursor(cur);
				fm = fm.mid(1, fm.length()-2);           // removes surrounding $...$
			} else {
				qDebug() << "Unknown math formula tag. Giving up trying to locate formula boundaries.";
			}
		}
	}

	InsertTag(fm, fm.length());
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
        if(configManager.insertUTF && item->data(Qt::UserRole+4).isValid()){
            code_symbol=item->data(Qt::UserRole+4).toString();
        }else{
            code_symbol=item->text();
        }
        item->setData(Qt::UserRole,cnt+1);
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
	QList<QAction *> actions = menu->actions();
	for (int i=0;i<actions.size();i++) {
		if (actions[i]->isSeparator()) continue;
		if (index == 0) {
			actions[i]->trigger();
			break;
		} else index--;
	}
}

void Texmaker::InsertFromAction() {
  LatexEditorView *edView=currentEditorView();
  if (!edView)	return;
  QAction *action = qobject_cast<QAction *>(sender());
  if (action)	{
    if(completer->isVisible())
      completer->close();
    /*QDocumentCursor c = currentEditorView()->editor->cursor();
  CodeSnippet cs=CodeSnippet(action->data().toString());
        cs.insertAt(currentEditorView()->editor,&c);*/
    edView->insertMacro(action->data().toString(),QRegExp(),0,true);
	outputView->setMessage(CodeSnippet(action->whatsThis(), false).lines.join("\n"));
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
												 "TeXstudio inserts automatically the base name of the TeX file");
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
				QTableWidgetItem * item =quickDlg->ui.tableWidget->item(i,j);
				if (item) tag +=item->text()+ QString(" & ");
				else tag +=QString(" & ");
			}
			QTableWidgetItem * item =quickDlg->ui.tableWidget->item(i,x-1);
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
				QTableWidgetItem * item =arrayDlg->ui.tableWidget->item(i,j);
				if (item) tag +=item->text()+ QString(" & ");
				else tag +=QString(" & ");
			}
			QTableWidgetItem * item =arrayDlg->ui.tableWidget->item(i,x-1);
			if (item) tag +=item->text()+ QString(" \\\\ \n");
			else tag +=QString(" \\\\ \n");
		}
		for (int j=0; j<x-1; j++) {
			QTableWidgetItem * item =arrayDlg->ui.tableWidget->item(y-1,j);
			if (item) tag +=item->text()+ QString(" & ");
			else tag +=QString(" & ");
		}
		QTableWidgetItem * item =arrayDlg->ui.tableWidget->item(y-1,x-1);
		if (item) tag +=item->text()+ QString("\n\\end{")+env+"} ";
		else tag +=QString("\n\\end{")+env+"} ";
		InsertTag(tag,0,0);
	}
}

// returns true if line is inside in the specified environment. In that case start and end lines of the environment are supplied
bool findEnvironmentLines(const QDocument *doc, const QString &env, int line, int &startLine, int &endLine, int scanRange) {
	QString name, arg;
	
	startLine = -1;
	for (int l=line; l>=0; l--) {
		if (scanRange>0 && line-l > scanRange) break;
		if (findTokenWithArg(doc->line(l).text(), "\\end{", name, arg) && name == env) {
			if (l<line) return false;
		}
		if (findTokenWithArg(doc->line(l).text(), "\\begin{", name, arg) && name == env) {
			startLine = l;
			break;
		}
	}
	if (startLine == -1) return false;
	
	endLine = -1;
	for (int l=line; l<doc->lineCount(); l++) {
		if (scanRange>0 && l-line > scanRange) break;
		if (findTokenWithArg(doc->line(l).text(), "\\end{", name, arg) && name == env) {
			endLine = l;
			break;
		}
		if (findTokenWithArg(doc->line(l).text(), "\\begin{", name, arg) && name == env) {
			if (l>line) return false; //second begin without end
		}
	}
	if (endLine == -1) return false;
	return true;
}

void Texmaker::QuickGraphics(const QString &graphicsFile) {
	if (!currentEditorView()) return;
	
	InsertGraphics *graphicsDlg = new InsertGraphics(this, configManager.insertGraphicsConfig);
	
	QEditor *editor = currentEditor();
	
	int startLine, endLine, cursorLine, cursorCol;
	editor->getCursorPosition(cursorLine, cursorCol);
	QDocument* doc=editor->document();
	
	QDocumentCursor cur = currentEditor()->cursor();
	QDocumentCursor origCur = cur;
	origCur.setAutoUpdated(true);
	cur.beginEditBlock();
	bool hasCode = false;
	if (findEnvironmentLines(doc, "figure", cursorLine, startLine, endLine, 20)) {
		cur.moveTo(startLine, 0, QDocumentCursor::MoveAnchor);
		cur.moveTo(endLine+1, 0, QDocumentCursor::KeepAnchor);
		hasCode = true;
	} else if (findEnvironmentLines(doc, "figure*", cursorLine, startLine, endLine, 20)) {
		cur.moveTo(startLine, 0, QDocumentCursor::MoveAnchor);
		cur.moveTo(endLine+1, 0, QDocumentCursor::KeepAnchor);
		hasCode = true;
	} else if (findEnvironmentLines(doc, "center", cursorLine, startLine, endLine, 3)) {
		cur.moveTo(startLine, 0, QDocumentCursor::MoveAnchor);
		cur.moveTo(endLine+1, 0, QDocumentCursor::KeepAnchor);
		hasCode = true;
	} else if (currentEditor()->text(cursorLine).contains("\\includegraphics")) {
		cur.moveTo(cursorLine, 0, QDocumentCursor::MoveAnchor);
		cur.moveTo(cursorLine+1, 0, QDocumentCursor::KeepAnchor);
		hasCode = true;
	}
	
	if (hasCode) {
		editor->setCursor(cur);
		graphicsDlg->setCode(cur.selectedText());
	}
	
	QFileInfo docInfo=currentEditorView()->document->getFileInfo();
	graphicsDlg->setTexFile(docInfo);
	if (documents.masterDocument) graphicsDlg->setMasterTexFile(documents.masterDocument->getFileInfo());
	if (!graphicsFile.isNull()) graphicsDlg->setGraphicsFile(graphicsFile);
	
	if (graphicsDlg->exec()) {
		QString code = graphicsDlg->getCode();
		
		editor->cursor().replaceSelectedText(code);
		if (editor->cursor().hasSelection()) {
			editor->setCursor(cur.selectionEnd());
		}
	} else {
		editor->setCursor(origCur);
	}
	
	cur.endEditBlock();
	
	delete graphicsDlg;
}

void Texmaker::QuickMath() {
#ifdef Q_OS_WIN
	connectUnique(MathAssistant::instance(), SIGNAL(formulaReceived(QString)), this, SLOT(InsertFormula(QString)));
	MathAssistant::instance()->exec();
#endif
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
		currentEditorView()->insertMacro(startDlg->getNewDocumentText());
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
		CodeSnippet(insertText, false).insert(currentEditor());
}

void Texmaker::InsertBibEntry(const QString& id){
	QStringList possibleBibFiles;
	int usedFile=0;
	if (currentEditor()){
		if (currentEditor()->fileName().isEmpty())
			possibleBibFiles.prepend(tr("<Current File>"));
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
		
		CodeSnippet(bd->resultString, false).insert(currentEditor());
	}
	delete bd;
}

void Texmaker::SetBibTypeFromAction() {
	QMenu *menu = getManagedMenu("main/bibliography/type");
	QAction *act = qobject_cast<QAction *>(sender());
	if (!act) return;
	if (menu) {
		menu->setTitle(QString(tr("Type: %1")).arg(act->text()));
	}

	bool isBibtex = (act->data().toString() == "bibtex");
	bibtexEntryActions->setVisible(isBibtex);
	biblatexEntryActions->setVisible(!isBibtex);
	BibTeXDialog::setBibType(isBibtex ? BibTeXDialog::BIBTEX : BibTeXDialog::BIBLATEX);
}

void Texmaker::insertUserTag() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	int id = action->data().toInt();
	const QString& userTag=configManager.completerConfig->userMacros.value(id,Macro()).tag;
	insertUserTag(userTag);
}

void Texmaker::insertUserTag(const QString& macro, int triggerId){
	//dont'check that, if (!currentEditorView()) return; insertMacro is 0 save
	currentEditorView()->insertMacro(macro, QRegExp(), triggerId);
}

void Texmaker::editMacros() {
	if (!userMacroDialog)  {
		userMacroDialog = new UserMenuDialog(0,tr("Edit User &Tags"),m_languages);
		foreach (const Macro& m, configManager.completerConfig->userMacros) {
			if(m.name=="TMX:Replace Quote Open" || m.name=="TMX:Replace Quote Close" || m.document)
				continue;
			userMacroDialog->addMacro(m);
		}
		userMacroDialog->init();
		connect(userMacroDialog, SIGNAL(accepted()), SLOT(macroDialogAccepted()));
		connect(userMacroDialog, SIGNAL(runScript(QString)), SLOT(insertUserTag(QString)));
	}
	userMacroDialog->show();
	userMacroDialog->setFocus();
}

void Texmaker::macroDialogAccepted(){
	configManager.completerConfig->userMacros.clear();
	for (int i=0; i<userMacroDialog->macroCount(); i++) {
		configManager.completerConfig->userMacros << userMacroDialog->getMacro(i);
	}
	for (int i=0;i<documents.documents.size();i++)
		configManager.completerConfig->userMacros << documents.documents[i]->localMacros;
	updateUserMacros();
	completer->updateAbbreviations();
	userMacroDialog->deleteLater();
	userMacroDialog = 0;
}

void Texmaker::InsertRef(const QString &refCmd) {
	//updateStructure();
	
	LatexEditorView* edView=currentEditorView();
	QStringList labels;
	if(edView && edView->document){
		QList<LatexDocument*> docs;
        docs << edView->document->getListOfDocs();
		foreach(const LatexDocument* doc,docs)
			labels << doc->labelItems();
	} else return;
    labels.sort();
	UniversalInputDialog dialog;
	dialog.addVariable(&labels, tr("Labels:"));
	if (dialog.exec() && !labels.isEmpty()) {
		QString tag=refCmd+"{"+labels.first()+"}";
		InsertTag(tag,tag.length(),0);
	} else
		InsertTag(refCmd+"{}",refCmd.length()+1,0);
}

void Texmaker::InsertRef() {
	InsertRef("\\ref");
}

void Texmaker::InsertEqRef() {
	InsertRef("\\eqref");
}

void Texmaker::InsertPageRef() {
	InsertRef("\\pageref");
}

void Texmaker::createLabelFromAction()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (!act) return;
	StructureEntry *entry = qvariant_cast<StructureEntry *>(act->data());
	if (!entry || !entry->document) return;

	// find editor and line nr
	int lineNr=entry->getRealLineNumber();
	int level = entry->level;

	mDontScrollToItem = entry->type!=StructureEntry::SE_SECTION;
	LatexEditorView* edView=entry->document->getEditorView();
	QEditor::MoveFlags mflags = QEditor::NavigationToHeader;
	if (!edView){
		edView=load(entry->document->getFileName());
		if (!edView) return;
		mflags &= ~QEditor::Animated;
		//entry is now invalid
	}
	REQUIRE(edView->getDocument());

	if (lineNr < 0) return; //not found. (document was closed)

	// find column position after structure command
	QString lineText = edView->getDocument()->line(lineNr).text();
	int pos = lineText.indexOf(latexParser.structureCommands[level]);
	if (pos>=0) {
		pos += latexParser.structureCommands[level].length();
		// workaround for starred commands: \section*{Cap}
		if ((lineText.length() > pos+1) && lineText.at(pos) == '*') pos++;
	} else {
		// fallback if structure commands are redefined
		foreach (const QString &cmd, latexParser.structureCommands) {
			pos = lineText.indexOf(cmd);
			if (pos<0) continue;
			pos += cmd.length();
		}
		if (pos<0) return; // could not find associated command
	}

	// advance pos behind options, and use title to guess a label
	QList<CommandArgument> args = getCommandOptions(lineText, pos, &pos);
	QString label = "sec:";
	if (args.length()>0) {
		label+=args.at(0).value.toLower();
		label.replace(' ','-');
	}
	if (label.contains('\\') || label.contains('$')) { // title too complicated to extract label: fall back
		label = "sec:";
	}

	gotoLine(lineNr,pos,edView,mflags);

	InsertTag(QString("\\label{%1}").arg(label),7);
	QDocumentCursor cur(edView->editor->cursor());
	cur.movePosition(label.length(),QDocumentCursor::NextCharacter,QDocumentCursor::KeepAnchor);
	edView->editor->setCursor(cur);
}

void Texmaker::changeTextCodec() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	bool ok;
	int mib = action->data().toInt(&ok);
	if (!ok) return;
	if (!currentEditorView()) return;

	currentEditorView()->editor->setFileCodec(QTextCodec::codecForMib(mib));
	UpdateCaption();
}

void Texmaker::EditorSpellerChanged(const QString &name) {
	foreach (QAction *act, statusTbLanguage->actions()) {
		if (act->data().toString() == name) {
			act->setChecked(true);
			break;
		}
	}
	if (name == "<default>") {
		statusTbLanguage->setText(spellerManager.defaultSpellerName());
	} else {
		statusTbLanguage->setText(name);
	}
}

void Texmaker::ChangeEditorSpeller() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	if (!currentEditorView()) return;
	
	if (!currentEditorView()->setSpeller(action->data().toString())) {
		// restore activity of previous action
		foreach (QAction *act, statusTbLanguage->actions()) {
			if (act->data().toString() == currentEditorView()->getSpeller()) {
				act->setChecked(true);
				break;
			}
		}
	}
}

void Texmaker::InsertSpellcheckMagicComment() {
	if (currentEditorView()) {
		QString name = currentEditorView()->getSpeller();
		if (name=="<default>") {
			name = spellerManager.defaultSpellerName();
		}
		currentEditorView()->document->updateMagicComment("spellcheck", name, true);
	}
}



void Texmaker::addMagicRoot() {
    if (currentEditorView()) {
        LatexDocument *doc=currentEditorView()->getDocument();
        if(!doc) return;
        QString name=doc->getTopMasterDocument()->getFileName();
        name=getRelativeFileName(name,doc->getFileName(),true);
        currentEditorView()->document->updateMagicComment("root", name, true);
    }
}
void Texmaker::addMagicCoding() {
    if (currentEditorView()) {
        QString name=currentEditor()->getFileCodec()->name();
        currentEditorView()->document->updateMagicComment("encoding", name, true);
    }
}

///////////////TOOLS////////////////////
bool Texmaker::runCommand(const QString& commandline, QString* buffer) {
	fileSaveAll(buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ALWAYS, buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ONLY_CURRENT_OR_NAMED);
	if (documents.getTemporaryCompileFileName()=="") {
		if (buildManager.saveFilesBeforeCompiling==BuildManager::SFBC_ONLY_NAMED && currentEditorView()){
			QString tmpName = buildManager.createTemporaryFileName();
			currentEditor()->saveCopy(tmpName);
			currentEditorView()->document->setTemporaryFileName(tmpName);
		} else {
			QMessageBox::warning(this,tr("Error"),tr("Can't detect the file name.\nYou have to save a document before you can compile it."));
			return false;
		}
	}
	
	QString finame=documents.getTemporaryCompileFileName();
	if (finame == "") {
		txsWarning(tr("Can't detect the file name"));
		return false;
	}
	
	int ln = currentEditorView() ? currentEditorView()->editor->cursor().lineNumber() + 1 : 0;
	
	return buildManager.runCommand(commandline, finame, getCurrentFileName(), ln, buffer);
}

void Texmaker::runInternalPdfViewer(const QFileInfo& master, const QString& options){
#ifndef NO_POPPLER_PREVIEW
	QStringList ol = options.split(" ");
	for (int i=ol.size()-1;i>=0;i--)
		if (!ol[i].startsWith("-")) ol.removeAt(i);
		else if (ol[i].startsWith("--")) ol[i] = ol[i].mid(2);
		else ol[i] = ol[i].mid(1);
	bool preserveExisting = ol.contains("preserve-existing");                  //completely ignore all existing internal viewers
	bool preserveExistingEmbedded = ol.contains("preserve-existing-embedded"); //completely ignore all existing embedded internal viewers
	bool preserveExistingWindowed = ol.contains("preserve-existing-windowed"); //completely ignore all existing windowed internal viewers
	bool preserveDuplicates = ol.contains("preserve-duplicates");              //open the document only in one pdf viewer
	bool embedded = ol.contains("embedded");                                   //if a new pdf viewer is opened, use the embedded mode
	bool windowed = ol.contains("windowed");                                   //if a new pdf viewer is opened, use the windowed mode (default)
	bool closeAll = ol.contains("close-all");                                  //close all existing viewers
	bool closeEmbedded = closeAll || ol.contains("close-embedded");            //close all embedded existing viewer
	bool closeWindowed = closeAll || ol.contains("close-windowed");            //close all windowed existing viewer
	
	bool autoClose;
	if (embedded) autoClose = ! ol.contains("no-auto-close");                  //Don't close the viewer, if the corresponding document is closed
	else autoClose = ol.contains("auto-close");                                //Close the viewer, if the corresponding document is closed
	
	bool focus = 0; //1: always, 0: auto, -1: never
	if (ol.contains("focus")) focus = 1;
	else if (ol.contains("no-focus")) focus = -1;
	
    if (!(embedded || windowed || closeEmbedded || closeWindowed)) windowed = true; //default
	
	//embedded/windowed are mutual exclusive
	//no viewer will be opened, if one already exist (unless it was closed by a explicitely given close command)
	

	QList<PDFDocument*> oldPDFs = PDFDocument::documentList();
	
	if (preserveExisting) oldPDFs.clear();
	if (preserveExistingWindowed)
		for (int i=oldPDFs.size() - 1; i >= 0; i--)
			if (!oldPDFs[i]->embeddedMode)
				oldPDFs.removeAt(i);
	if (preserveExistingEmbedded)
		for (int i=oldPDFs.size() - 1; i >= 0; i--)
			if (oldPDFs[i]->embeddedMode)
				oldPDFs.removeAt(i);
	
	//if closing and opening is set, reuse the first document (reuse = optimization, so it does not close a viewer and creates an equal viewer afterwards)
	PDFDocument* reuse = 0;
	if ((embedded || windowed) && (closeEmbedded || closeWindowed) && !oldPDFs.isEmpty() ) {
		for (int i=0;i<oldPDFs.size();i++)
			if (oldPDFs[i]->embeddedMode == embedded){
				reuse = oldPDFs.takeAt(i);
				break;
			}
	}
	
	//close old
	for (int i=oldPDFs.size()-1;i>=0;i--)
		if ( (oldPDFs[i]->embeddedMode && closeEmbedded) ||
				 (!oldPDFs[i]->embeddedMode && closeWindowed) )
			oldPDFs[i]->close(), oldPDFs.removeAt(i);
	
	
	//open new
	if (!embedded && !windowed) return;
	
	if (reuse) oldPDFs.insert(0, reuse);
	if (oldPDFs.isEmpty()){
		PDFDocument* doc = qobject_cast<PDFDocument*>(newPdfPreviewer(embedded));
		doc->autoClose = autoClose;
		REQUIRE(doc);
		oldPDFs << doc;
	}
	
	QString pdfDefFile = BuildManager::parseExtendedCommandLine("?am.pdf", master).first();
	QString pdfFile = buildManager.findFile(pdfDefFile, buildManager.additionalPdfPaths);
	if (pdfFile == "") pdfFile = pdfDefFile; //use old file name, so pdf viewer shows reasonable error message
	int ln = 0;
	if (currentEditorView()) {
		ln = currentEditorView()->editor->cursor().lineNumber();
		int originalLineNumber = currentEditorView()->document->lineToLineSnapshotLineNumber(currentEditorView()->editor->cursor().line());
		if (originalLineNumber >= 0) ln = originalLineNumber;
	}
	foreach (PDFDocument* viewer, oldPDFs) {
		bool focusViewer = (focus == 1) || (focus == 0 && !viewer->embeddedMode);
		viewer->loadFile(pdfFile, master, focusViewer);
		int pg = viewer->syncFromSource(getCurrentFileName(), ln , focusViewer);
		viewer->fillRenderCache(pg);
		
		if (preserveDuplicates) break;
    }
#if QT_VERSION>=0x050000 && defined Q_OS_MAC
    if(embedded)
        setMenuBar(configManager.menuParentsBar);
#endif
    if(embedded){
        if(configManager.viewerEnlarged)
            enlargeEmbeddedPDFViewer();
    }
#else
	txsCritical(tr("You have called the command to open the internal pdf viewer.\nHowever, you are using a version of TeXstudio that was compiled without the internal pdf viewer."));
#endif
	
}

bool Texmaker::checkProgramPermission(const QString& program, const QString& cmdId, LatexDocument* master){
	static const QRegExp txsCmd(QRegExp::escape(BuildManager::TXS_CMD_PREFIX) + "([^/ [{]+))");
	if (txsCmd.exactMatch(program)) return true;
	static QStringList programWhiteList; configManager.registerOption("Tools/Program Whitelist", &programWhiteList, QStringList() << "latex" << "pdflatex");
	if (programWhiteList.contains(program)) return true;
	if (buildManager.hasCommandLine(program)) return true;
	if (!master) return false;
	QString id = master->getMagicComment("document-id");
	if (id.contains("=")) return false;
	static QStringList individualProgramWhiteList; configManager.registerOption("Tools/Individual Program Whitelist", &individualProgramWhiteList, QStringList());
	if (!id.isEmpty() && individualProgramWhiteList.contains(id+"="+program)) return true;
	int t = QMessageBox::warning(0, TEXSTUDIO,
																tr("The document \"%1\" wants to override the command \"%2\" with \"%3\".\n\n"
																	 "Do you want to allow and run the new, overriding command?\n\n"
																	 "(a) Yes, allow the new command for this document (only if you trust this document)\n"
																	 "(b) Yes, allow the new command to be used for all documents (only if you trust the new command to handle arbitrary documents)\n"
																	 "(c) No, do not use the command \"%3\" and run the default \"%2\" command"
																	 ).arg(master?master->getFileName():"").arg(cmdId).arg(program),
																tr("(a) allow for this document"),
																tr("(b) allow for all documents"),
																tr("(c) use the default command"), 0, 2);
	if (t == 2) return false;
	if (t == 1) {
		programWhiteList.append(program);
		return true;
	}
	if (id.isEmpty()) {
		id = QUuid::createUuid().toString();
		master->updateMagicComment("document-id", id, true);
		if (master->getMagicComment("document-id") != id) return false;
	}
	individualProgramWhiteList.append(id+"="+program);
	return true;
}

void Texmaker::runBibliographyIfNecessary(const QFileInfo& mainFile){	
	if (!configManager.runLaTeXBibTeXLaTeX) return;
	if (runBibliographyIfNecessaryEntered) return;
	
	//LatexDocument* master = currentEditorView()->document->getTopMasterDocument(); //crashes if masterdoc is defined but closed
	LatexDocument* master = documents.getMasterDocumentForDoc(); //TODO: use mainFile master
	REQUIRE(master);
	
	QList<LatexDocument*> docs = master->getListOfDocs();
	QSet<QString> bibFiles;
	foreach (const LatexDocument* doc, docs)
		foreach (const FileNamePair& bf, doc->mentionedBibTeXFiles())
			bibFiles.insert(bf.absolute);
	if (bibFiles == master->lastCompiledBibTeXFiles) {
		QFileInfo bbl(BuildManager::parseExtendedCommandLine("?am.bbl", documents.getTemporaryCompileFileName()).first());
		if (bbl.exists()) {
			bool bibFilesChanged = false;
			QDateTime bblChanged = bbl.lastModified();
			foreach (const QString& bf, bibFiles){
				//qDebug() << bf << ": "<<QFileInfo(bf).lastModified()<<" "<<bblChanged;
				
				if (QFileInfo(bf).exists() && QFileInfo(bf).lastModified() > bblChanged) {
					bibFilesChanged = true;
					break;
				}
			}
			if (!bibFilesChanged) return;
		} else return;
	} else master->lastCompiledBibTeXFiles = bibFiles;

	runBibliographyIfNecessaryEntered = true;
	buildManager.runCommand(BuildManager::CMD_RECOMPILE_BIBLIOGRAPHY, mainFile);
	runBibliographyIfNecessaryEntered = false;
}


void Texmaker::runInternalCommand(const QString& cmd, const QFileInfo& mainfile, const QString& options){
	if (cmd == BuildManager::CMD_VIEW_PDF_INTERNAL || (cmd.startsWith(BuildManager::CMD_VIEW_PDF_INTERNAL) && cmd[BuildManager::CMD_VIEW_PDF_INTERNAL.length()] == ' '))
		runInternalPdfViewer(mainfile, options);
	else if (cmd == BuildManager::CMD_CONDITIONALLY_RECOMPILE_BIBLIOGRAPHY)
		runBibliographyIfNecessary(mainfile);
	else if (cmd == BuildManager::CMD_VIEW_LOG) {
		loadLog();
		ViewLog();
	}
	else txsWarning(tr("Unknown internal command: %1").arg(cmd));
}

void Texmaker::commandLineRequested(const QString& cmdId, QString* result, bool *){
	LatexDocument* master = documents.getMasterDocumentForDoc();
	if (!master) return;
	QString magic = master->getMagicComment("TXS-program:"+cmdId);
	if (!magic.isEmpty()) {
		if (!checkProgramPermission(magic, cmdId, master)) return;
		*result = magic;
		return;
	}
	if (cmdId != "quick" && cmdId != "compile" && cmdId != "view") return;
	QString program = master->getMagicComment("program");
	if (program.isEmpty()) program = master->getMagicComment("TS-program");
	if (program.isEmpty()) return;
	if (program == "pdflatex" || program == "latex" || program == "xelatex" || program == "luatex"  || program == "lualatex") {
		//TODO: don't replicate build logic here
		QString viewer = BuildManager::CMD_VIEW_PDF;
		QString compiler = BuildManager::CMD_PDFLATEX;
		if (program == "latex") viewer = BuildManager::CMD_VIEW_DVI, compiler = BuildManager::CMD_LATEX;
		else if (program == "xelatex") compiler = BuildManager::CMD_XELATEX;
		else if (program == "luatex" || program == "lualatex") compiler = BuildManager::CMD_LUALATEX;
		//else {} // pdflatex (default)
		
		if (cmdId == "quick") *result = BuildManager::chainCommands(compiler, viewer);
		else if (cmdId == "compile") *result = compiler;
		else if (cmdId == "view") *result = viewer;
	} else if (cmdId == "quick" && checkProgramPermission(program, cmdId, master)) *result = program;
}

void Texmaker::beginRunningCommand(const QString& commandMain, bool latex, bool pdf, bool async){
	if (pdf) {
		runningPDFCommands++;
		if (async && pdf) runningPDFAsyncCommands++;
#ifndef NO_POPPLER_PREVIEW
		PDFDocument::isCompiling = true;
		PDFDocument::isMaybeCompiling |= runningPDFAsyncCommands > 0;
#endif
		
		if (configManager.autoCheckinAfterSave) {
			QFileInfo fi(documents.getTemporaryCompileFileName());
			fi.setFile(fi.path()+"/"+fi.baseName()+".pdf");
			if(fi.exists() && !fi.isWritable()){
				//pdf not writeable, needs locking ?
				svnLock(fi.filePath());
			}
		}
	}
	if (latex) {
		outputView->resetMessagesAndLog(!configManager.showMessagesWhenCompiling);//log to old (whenever latex is called)
		foreach (LatexEditorView *edView, EditorTabs->editors()) {
			edView->document->saveLineSnapshot();
		}
	}
	else outputView->resetMessages(!configManager.showMessagesWhenCompiling);
	statusLabelProcess->setText(QString(" %1 ").arg(buildManager.getCommandInfo(commandMain).displayName));
}
void Texmaker::connectSubCommand(ProcessX* p, bool showStdoutLocally){
	connect(p, SIGNAL(standardErrorRead(QString)), outputView, SLOT(insertMessageLine(QString)));
	if (p->showStdout()) {
		p->setShowStdout((configManager.showStdoutOption == 2) || (showStdoutLocally && configManager.showStdoutOption == 1));
		connect(p, SIGNAL(standardOutputRead(QString)), outputView, SLOT(insertMessageLine(QString)));
	}
}

void Texmaker::beginRunningSubCommand(ProcessX* p, const QString& commandMain, const QString& subCommand, const RunCommandFlags& flags){
	if (commandMain != subCommand)
		statusLabelProcess->setText(QString(" %1: %2 ").arg(buildManager.getCommandInfo(commandMain).displayName).arg(buildManager.getCommandInfo(subCommand).displayName));
	if (flags & RCF_COMPILES_TEX)
		clearLogEntriesInEditors();
	//outputView->resetMessages();
	connectSubCommand(p, (RCF_SHOW_STDOUT & flags));
}


void Texmaker::endRunningSubCommand(ProcessX* p, const QString& commandMain, const QString& subCommand, const RunCommandFlags& flags){
	if (p->exitCode() && (flags & RCF_COMPILES_TEX) && !LogExists()) {
		if (!QFileInfo(QFileInfo(documents.getTemporaryCompileFileName()).absolutePath()).isWritable())
			txsWarning(tr("You cannot compile the document in a non writable directory."));
		else
			txsWarning(tr("Could not start %1.").arg( buildManager.getCommandInfo(commandMain).displayName + ":" + buildManager.getCommandInfo(subCommand).displayName + ":\n" + p->getCommandLine()));
	}
	if ((flags & RCF_CHANGE_PDF)  && !(flags & RCF_WAITFORFINISHED) && (runningPDFAsyncCommands > 0)) {
		runningPDFAsyncCommands--;
#ifndef NO_POPPLER_PREVIEW
		if (runningPDFAsyncCommands <= 0) PDFDocument::isMaybeCompiling = false;
#endif
	}

}

void Texmaker::endRunningCommand(const QString& commandMain, bool latex, bool pdf, bool async){
	Q_UNUSED(commandMain)
	Q_UNUSED(async);
	if (pdf) {
		runningPDFCommands--;
#ifndef NO_POPPLER_PREVIEW
		if (runningPDFCommands <= 0)
			PDFDocument::isCompiling = false;
#endif
	}
	statusLabelProcess->setText(QString(" %1 ").arg(tr("Ready")));
	if (latex) emit infoAfterTypeset();
}


void Texmaker::processNotification(const QString& message){
	outputView->insertMessageLine(message+"\n");
}

void Texmaker::commandFromAction(){
	QAction* act = qobject_cast<QAction*>(sender());
	if (!act) return;
	runCommand(act->data().toString());
}

void Texmaker::CleanAll() {
	CleanDialog cleanDlg(this);
	if (cleanDlg.checkClean(documents)) {
		cleanDlg.exec();
	} else {
		txsInformation(tr("No open project or tex file to clean."));
	}
}

void Texmaker::WebPublish() {
	if (!currentEditorView()) {
		txsWarning(tr("No document open"));
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
		txsWarning(tr("No document open"));
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
		txsWarning(tr("The random text generator constructs new texts from existing words, so you have to open some text files"));
		return;
	}
	
	QStringList allLines;
	foreach (LatexEditorView *edView, EditorTabs->editors())
		allLines << edView->editor->document()->textLines();
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

bool Texmaker::loadLog() {
	outputView->getLogWidget()->resetLog();
	if (!documents.getCurrentDocument()) return false;
	QString finame=documents.getTemporaryCompileFileName();
	if (finame=="") {
		QMessageBox::warning(this,tr("Error"),tr("File must be saved and compiling before you can view the log"));
		return false;
	}
	QString logname=buildManager.findFile(getAbsoluteFilePath(QFileInfo(finame).completeBaseName(),".log"), buildManager.additionalLogPaths);
	QFileInfo fic(logname);
	return outputView->getLogWidget()->loadLogFile(logname,documents.getTemporaryCompileFileName());
}

void Texmaker::showLog() {
	outputView->showPage(outputView->LOG_PAGE);
}

//shows the log (even if it is empty)
void Texmaker::ViewLog() {
	showLog();
	setLogMarksVisible(true);
	if (configManager.goToErrorWhenDisplayingLog && HasLatexErrors()) {
		int errorMarkID = outputView->getLogWidget()->getLogModel()->markID(LT_ERROR);
		if (!gotoMark(false, errorMarkID)) {
			gotoMark(true, errorMarkID);
		}
	}
}

void Texmaker::ViewLogOrReRun(LatexCompileResult* result){
	loadLog();
	REQUIRE(result);
	if (HasLatexErrors()) {
		ViewLog();
		*result = LCR_ERROR;
	} else {
		*result = LCR_NORMAL;
		if (outputView->getLogWidget()->getLogModel()->existsReRunWarning())
			*result = LCR_RERUN;
		else if (configManager.runLaTeXBibTeXLaTeX) {
			//run bibtex if citation is unknown to bibtex but contained in an included bib file
			QStringList missingCitations = outputView->getLogWidget()->getLogModel()->getMissingCitations();
			bool runBibTeX = false;
			foreach (const QString & s,missingCitations) {
				for (int i=0; i<documents.mentionedBibTeXFiles.count();i++){
					if (!documents.bibTeXFiles.contains(documents.mentionedBibTeXFiles[i])) continue;
					BibTeXFileInfo& bibTex=documents.bibTeXFiles[documents.mentionedBibTeXFiles[i]];
					for (int i=0; i<bibTex.ids.count();i++)
						if (bibTex.ids[i] == s) {
							runBibTeX = true;
							break;
						}
					if (runBibTeX) break;
				}
			}
			if (runBibTeX)
				*result = LCR_RERUN_WITH_BIBLIOGRAPHY;
		}
	}
}

////////////////////////// ERRORS /////////////////////////////

// changes visibilita of log markers in all editors
void Texmaker::setLogMarksVisible(bool visible) {
	foreach (LatexEditorView *edView, EditorTabs->editors()) {
		edView->setLogMarksVisible(visible);
	}
	QAction *act = getManagedAction("main/tools/logmarkers");
	if (act) act->setChecked(visible);
}

// removes the log entries from all editors
void Texmaker::clearLogEntriesInEditors() {
	foreach (LatexEditorView *edView, EditorTabs->editors()) {
		edView->clearLogMarks();
	}
}

// adds the current log entries to all editors
void Texmaker::updateLogEntriesInEditors() {
	clearLogEntriesInEditors();
	LatexLogModel* logModel = outputView->getLogWidget()->getLogModel();
	QHash<QString, LatexEditorView*> tempFilenames; //temporary maps the filenames (as they appear in this log!) to the editor
	int errorMarkID = QLineMarksInfoCenter::instance()->markTypeId("error");
	int warningMarkID = QLineMarksInfoCenter::instance()->markTypeId("warning");
	int badboxMarkID = QLineMarksInfoCenter::instance()->markTypeId("badbox");

	for (int i = logModel->count()-1; i >= 0; i--) {
		if (logModel->at(i).oldline!=-1){
			LatexEditorView* edView;
			if (tempFilenames.contains(logModel->at(i).file)) edView=tempFilenames.value(logModel->at(i).file);
			else{
				edView=getEditorViewFromFileName(logModel->at(i).file, true);
				tempFilenames[logModel->at(i).file]=edView;
			}
			if (edView) {
				int markID;
				switch (logModel->at(i).type) {
				case LT_ERROR:   markID = errorMarkID;   break;
				case LT_WARNING: markID = warningMarkID; break;
				case LT_BADBOX:  markID = badboxMarkID;  break;
				default: markID = -1;
				}
				edView->addLogEntry(i, logModel->at(i).oldline-1, markID);
			}
		}
	}
}

bool Texmaker::HasLatexErrors() {
	return outputView->getLogWidget()->getLogModel()->found(LT_ERROR);
}

bool Texmaker::gotoNearLogEntry(int lt, bool backward, QString notFoundMessage) {
	if (!outputView->getLogWidget()->logPresent()) {
		loadLog();
	}
	if (outputView->getLogWidget()->logPresent()) {
		if (outputView->getLogWidget()->getLogModel()->found((LogType) lt)){
			showLog();
			setLogMarksVisible(true);
			return gotoMark(backward, outputView->getLogWidget()->getLogModel()->markID((LogType) lt));
		} else {
			txsInformation(notFoundMessage);
		}
	}
	return false;
}

void Texmaker::ClearMarkers() {
	setLogMarksVisible(false);
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

void Texmaker::TexdocHelp() {
	QString selection;
	QStringList packages;
	if (currentEditorView()) {
		selection = currentEditorView()->editor->cursor().selectedText();
		// TODO is there a better way to get the used packages than using the .cwl files and removing cwls for native commands
		packages = currentEditorView()->document->parent->cachedPackages.keys();
        // remove empty packages whicjh probably do not exist
        QMutableStringListIterator it(packages);
        while (it.hasNext()) {
            QString elem=it.next();
            LatexPackage ltxPackage=currentEditorView()->document->parent->cachedPackages.value(elem);
            if(ltxPackage.completionWords.isEmpty())
                it.remove();;
        }

		packages.replaceInStrings(".cwl", "");
		packages.removeAll("latex-209");
		packages.removeAll("latex-dev");
		packages.removeAll("latex-l2tabu");
		packages.removeAll("latex-document");
		packages.removeAll("latex-mathsymbols");
		packages.removeAll("tex");
	}

	Help::instance()->execTexdocDialog(packages, selection);
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
	int oldReplaceQuotes = configManager.replaceQuotes;
	autosaveTimer.stop();
	m_formats->modified = false;
	bool realtimeChecking=configManager.editorConfig->realtimeChecking;
	bool inlineSpellChecking=configManager.editorConfig->inlineSpellChecking;
	bool inlineCitationChecking=configManager.editorConfig->inlineCitationChecking;
	bool inlineReferenceChecking=configManager.editorConfig->inlineReferenceChecking;
	bool inlineSyntaxChecking=configManager.editorConfig->inlineSyntaxChecking;
	QStringList loadFiles=configManager.completerConfig->getLoadedFiles();
	
#if QT_VERSION<0x050000
	if (configManager.possibleMenuSlots.isEmpty()) {
		for (int i=0;i<staticMetaObject.methodCount();i++) configManager.possibleMenuSlots.append(staticMetaObject.method(i).signature());
		for (int i=0;i<QEditor::staticMetaObject.methodCount();i++) configManager.possibleMenuSlots.append("editor:"+QString(QEditor::staticMetaObject.method(i).signature()));
		for (int i=0;i<LatexEditorView::staticMetaObject.methodCount();i++) configManager.possibleMenuSlots.append("editorView:"+QString(LatexEditorView::staticMetaObject.method(i).signature()));
		configManager.possibleMenuSlots = configManager.possibleMenuSlots.filter(QRegExp("^[^*]+$"));
	}
#else
    if (configManager.possibleMenuSlots.isEmpty()) {
        for (int i=0;i<staticMetaObject.methodCount();i++) configManager.possibleMenuSlots.append(staticMetaObject.method(i).methodSignature());
        for (int i=0;i<QEditor::staticMetaObject.methodCount();i++) configManager.possibleMenuSlots.append("editor:"+QString(QEditor::staticMetaObject.method(i).methodSignature()));
        for (int i=0;i<LatexEditorView::staticMetaObject.methodCount();i++) configManager.possibleMenuSlots.append("editorView:"+QString(LatexEditorView::staticMetaObject.method(i).methodSignature()));
        configManager.possibleMenuSlots = configManager.possibleMenuSlots.filter(QRegExp("^[^*]+$"));
    }
#endif
	
	if (configManager.execConfigDialog()) {
		QApplication::setOverrideCursor(Qt::WaitCursor);

		configManager.editorConfig->settingsChanged();
		
		spellerManager.setDictPath(configManager.spellDictDir);
		spellerManager.setDefaultSpeller(configManager.spellLanguage);
		
		GrammarCheck::staticMetaObject.invokeMethod(grammarCheck, "init", Qt::QueuedConnection, Q_ARG(LatexParser, latexParser), Q_ARG(GrammarCheckerConfig, *configManager.grammarCheckerConfig));
		
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
		foreach(const QString& elem,newLoadedFiles){
			if(loadFiles.removeAll(elem)==0)
				updateHighlighting=true;
			if(updateHighlighting)
				break;
		}
		if(!loadFiles.isEmpty())
			updateHighlighting=true;
		buildManager.clearPreviewPreambleCache();//possible changed latex command / preview behaviour
		
		if (currentEditorView()) {
			foreach (LatexEditorView *edView, EditorTabs->editors()) {
				edView->updateSettings();
				if(updateHighlighting){
					if(configManager.editorConfig->realtimeChecking){
						edView->updateLtxCommands();
						edView->documentContentChanged(0,edView->document->lines());
                        edView->document->updateCompletionFiles(false,true);
					}else{
						edView->clearOverlays();
					}
				}

			}
			if (m_formats->modified)
				QDocument::setFont(QDocument::font(), true);
			UpdateCaption();

			if (documents.indentIncludesInStructure!=configManager.indentIncludesInStructure) {
				documents.indentIncludesInStructure = configManager.indentIncludesInStructure;
				foreach (LatexDocument* doc, documents.documents)
					updateStructure(false, doc);
			}
		}
		if (oldReplaceQuotes != configManager.replaceQuotes)
			updateUserMacros();
		//custom toolbar
		setupToolBars();
		// custom evironments
		bool customEnvironmentChanged = configManager.customEnvironments != oldCustomEnvironments;
		QLanguageDefinition *oldLaTeX = 0, *newLaTeX = 0;
		if (customEnvironmentChanged){
			QLanguageFactory::LangData m_lang=m_languages->languageData("(La)TeX");
			
			oldLaTeX = m_lang.d;
			Q_ASSERT(oldLaTeX);
			
			QFile f(findResourceFile("qxs/tex.qnfa"));
			QDomDocument doc;
			doc.setContent(&f);
			
			{
				QMap<QString, QVariant>::const_iterator i;
				for (i = configManager.customEnvironments.constBegin(); i != configManager.customEnvironments.constEnd(); ++i){
					QString mode=configManager.enviromentModes.value(i.value().toInt(),"verbatim");
					addEnvironmentToDom(doc,i.key(),mode);
				}
			}
			//detected math envs
			{
				QMap<QString, QString>::const_iterator i;
				for (i = detectedEnvironmentsForHighlighting.constBegin(); i != detectedEnvironmentsForHighlighting.constEnd(); ++i){
					QString envMode=i.value()=="verbatim" ? "verbatim" :  "numbers";
                    QString env=i.key();
                    if(env.contains('*')){
                        env.replace("*","\\*");
                    }
                    addEnvironmentToDom(doc,env,envMode);
				}
			}
			QNFADefinition::load(doc,&m_lang,qobject_cast<QFormatScheme*>(m_formats));
			m_languages->addLanguage(m_lang);
			
			newLaTeX = m_lang.d;
			Q_ASSERT(oldLaTeX != newLaTeX);
		}
		//completion
		completionBaseCommandsUpdated=true;
		completerNeedsUpdate();
		completer->setConfig(configManager.completerConfig);
		//update changed line mark colors
		QList<QLineMarkType> &marks = QLineMarksInfoCenter::instance()->markTypes();
		for (int i=0;i<marks.size();i++)
			if (m_formats->format("line:"+marks[i].id).background.isValid())
				marks[i].color = m_formats->format("line:"+marks[i].id).background;
			else
				marks[i].color = Qt::transparent;
		// update all docuemnts views as spellcheck may be different
		QEditor::setEditOperations(configManager.editorKeys,true);
		foreach (LatexEditorView *edView, EditorTabs->editors()) {
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
		if (oldModernStyle != modernStyle || oldSystemTheme != useSystemTheme) {
			setupMenus();
			setupDockWidgets();
		}
		updateUserToolMenu();
		QApplication::restoreOverrideCursor();
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
	int col=0;
	QString cite;
#ifndef NO_POPPLER_PREVIEW
	int page=-1;
	bool pdfViewerOnly = false;
#endif
	for (int i = 0; i < args.size(); ++i) {
		if (args[i]=="") continue;
		if (args[i][0] != '-')  filesToLoad << args[i];
		//-form is for backward compatibility
		if (args[i] == "--master") activateMasterMode=true;
		if (args[i] == "--line" && i+1<args.size()) {
			QStringList lineCol = args[++i].split(":");
			line = lineCol.at(0).toInt()-1;
			if (lineCol.count() >= 2) {
				col = lineCol.at(1).toInt();
				if ((col)<0) col = 0;
			}
		}
		if (args[i] == "--insert-cite" && i+1<args.size()) {
			cite = args[++i];
		}
#ifndef NO_POPPLER_PREVIEW
		if (args[i] == "--pdf-viewer-only") pdfViewerOnly = true;
		if (args[i] == "--page") page = args[++i].toInt()-1;
#endif
	}
	
#ifndef NO_POPPLER_PREVIEW
	if (pdfViewerOnly) {
		if (PDFDocument::documentList().isEmpty())
			newPdfPreviewer();
		foreach (PDFDocument* viewer, PDFDocument::documentList()) {
			if (!filesToLoad.isEmpty()) viewer->loadFile(filesToLoad.first(),filesToLoad.first().replace(".pdf", ".tex"));
			connect(viewer,SIGNAL(destroyed()), SLOT(deleteLater()));
			viewer->show();
			viewer->setFocus();
			if (page!=-1) viewer->goToPage(page);
		}
		hide();
		return;
	}
#endif
	
	// execute command line
	foreach(const QString& fileToLoad,filesToLoad){
		QFileInfo ftl(fileToLoad);
		if (fileToLoad != "") {
			if (ftl.exists()) {
				if (ftl.suffix() == Session::fileExtension()) {
					loadSession(ftl.filePath());
				} else {
					load(fileToLoad, activateMasterMode);
				}
			} else if (ftl.absoluteDir().exists()) {
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
		gotoLine(line, col, 0, QEditor::KeepSurrounding | QEditor::ExpandFold);
		QTimer::singleShot(1000,currentEditor(),SLOT(ensureCursorVisible()));
	}

	if (!cite.isNull()) {
		InsertCitation(cite);
	}

	
#ifndef QT_NO_DEBUG
	//execute test after command line is known
	if (realCmdLine){ //only at start
		executeTests(args);

		if (args.contains("--update-translations")) {
			generateAddtionalTranslations();
		}
	}
#endif

    if (realCmdLine) Guardian::summon();
}

void Texmaker::executeTests(const QStringList &args){
	QFileInfo myself(QCoreApplication::applicationFilePath());
	if (args.contains("--disable-tests")) return;
#if !defined(QT_NO_DEBUG) && !defined(NO_TESTS)
	bool allTests = args.contains("--execute-all-tests")
			//execute all tests once a week or if command paramter is set
			|| (configManager.debugLastFullTestRun.daysTo(myself.lastModified())>6);
	if (args.contains("--execute-tests") || myself.lastModified()!=configManager.debugLastFileModification || allTests) {
		fileNew();
		if (!currentEditorView() || !currentEditorView()->editor)
			QMessageBox::critical(0,"wtf?","test failed",QMessageBox::Ok);
		if (allTests) configManager.debugLastFullTestRun=myself.lastModified();

		TestManager testManager;
		connect(&testManager, SIGNAL(newMessage(QString)), this, SLOT(showTestProgress(QString)));
		QString result = testManager.execute(allTests?TestManager::TL_ALL:TestManager::TL_FAST, currentEditorView(),currentEditorView()->codeeditor,currentEditorView()->editor, &buildManager);
		m_languages->setLanguageFromName(currentEditorView()->editor, "TXS Test Results");
		currentEditorView()->editor->setText(result, false);
		configManager.debugLastFileModification=QFileInfo(QCoreApplication::applicationFilePath()).lastModified();
	}
#endif
}

void Texmaker::showTestProgress(const QString &message) {
	outputView->insertMessageLine(message);
	QApplication::processEvents(QEventLoop::ExcludeUserInputEvents | QEventLoop::ExcludeSocketNotifiers);
}

void Texmaker::generateAddtionalTranslations(){
	QStringList translations;
	translations << "/******************************************************************************";
	translations << " * Do not manually edit this file. It is automatically generated by a call to";
	translations << " * texstudio --update-translations";
	translations << " * This generates some additional translations which lupdate doesn't find";
	translations << " * (e.g. from uiconfig.xml, color names, qnfa format names) ";
	translations << " ******************************************************************************/";

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
	CodeSnippet::debugDisableAutoTranslate = true;
	while (!current.isNull()) {
		QDomNamedNodeMap attribs = current.attributes();
		QString text = attribs.namedItem("text").nodeValue();
		if (text!="" && !commandOnly.exactMatch(text))
			translations << "QT_TRANSLATE_NOOP(\"ConfigManager\", \""+text.replace("\\","\\\\").replace("\"","\\\"")+"\"), ";
		QString insert = attribs.namedItem("insert").nodeValue();
		if (insert != "") {
			CodeSnippet cs(insert, false);
			for (int i=0;i<cs.placeHolders.size();i++)
				for (int j=0;j<cs.placeHolders[i].size();j++)
					if (cs.placeHolders[i][j].flags & CodeSnippetPlaceHolder::Translatable)
						translations << "QT_TRANSLATE_NOOP(\"CodeSnippet_PlaceHolder\", \""+cs.lines[i].mid(cs.placeHolders[i][j].offset,cs.placeHolders[i][j].length)+"\"), ";

		}
		if (current.hasChildNodes()) current=current.firstChild();
		else if (!current.nextSibling().isNull()) current=current.nextSibling();
		else if (!current.parentNode().isNull()) current = current.parentNode().nextSibling();
		else current = current.parentNode();
	}
	CodeSnippet::debugDisableAutoTranslate = false;
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

	foreach (const QString &s, m_languages->languages())
		translations << "QT_TRANSLATE_NOOP(\"Texmaker\", \""+s+"\", \"Format name of language definition \"), ";

	translations << "\"\"};";
	translations << "#endif\n\n";

	QFile translationFile("additionaltranslations.cpp");
	translationFile.open(QIODevice::WriteOnly);
	translationFile.write(translations.join("\n").toLatin1());
	translationFile.close();
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
	// TODO check: can we have managed action connecting to the EditorView slot directly? Then we could remove this slot
	EditorTabs->gotoNextDocument();
}

void Texmaker::gotoPrevDocument() {
	// TODO check: can we have managed action connecting to the EditorView slot directly? Then we could remove this slot
	EditorTabs->gotoPrevDocument();
}

void Texmaker::gotoOpenDocument(){
	QAction* act = qobject_cast<QAction*>(sender());
	REQUIRE(act);
	int doc = act->data().toInt();
	EditorTabs->setCurrentIndex(doc);
}
void Texmaker::updateOpenDocumentMenu(bool localChange){
	if (localChange) {
		Q_ASSERT(currentEditorView());
		int idx = EditorTabs->currentIndex();
		QString id = "doc"+QString::number(idx);
		QMenu* menu = configManager.getManagedMenu("main/view/documents");
		configManager.newManagedAction(menu, id, currentEditorView()->displayName().replace("&","&&"), SLOT(gotoOpenDocument()))->setData(idx);
		return;
	}
	QStringList sl;
	foreach (LatexEditorView *edView, EditorTabs->editors()) {
		sl << (edView->displayName().replace("&", "&&"));
	}
	configManager.updateListMenu("main/view/documents", sl, "doc", false, SLOT(gotoOpenDocument()), 0, false, 0);
}

void Texmaker::focusEditor(){
	raise();
	activateWindow();
	if (currentEditorView())
		currentEditorView()->setFocus();
}

void Texmaker::focusViewer(){
    #ifndef NO_POPPLER_PREVIEW
	QList<PDFDocument*> viewers = PDFDocument::documentList();
	if (viewers.isEmpty()) return;

	if (viewers.count() > 1 && currentEditorView()) {
		// try: PDF for current file
		QFileInfo currentFile = currentEditorView()->getDocument()->getFileInfo();
		foreach (PDFDocument* viewer, viewers) {
			if (viewer->getMasterFile() == currentFile) {
				viewer->focus();
				return;
			}
		}
		// try: PDF for master file
		LatexDocument *masterDoc = documents.getMasterDocumentForDoc(0);
		if (masterDoc) {
			QFileInfo masterFile = masterDoc->getFileInfo();
			foreach (PDFDocument* viewer, viewers) {
				if (viewer->getMasterFile() == masterFile) {
					viewer->focus();
					return;
				}
			}
		}
	}
	// fall back to first
	viewers.at(0)->focus();
#endif
}

void Texmaker::viewCloseSomething(){
	if (fileSelector){
		fileSelector.data()->deleteLater();
		return;
	}
	if (buildManager.waitingForProcess()) {
		buildManager.killCurrentProcess();
		return;
	}
	if (unicodeInsertionDialog) {
		unicodeInsertionDialog->close();
		return;
	}
	if (completer && completer->isVisible() && completer->close())
		return;

	if (textAnalysisDlg) {
		textAnalysisDlg->close();
		return;
	}
	if (currentEditorView() && currentEditorView()->closeSomething())
		return;
	if (outputView->isVisible() && configManager.useEscForClosingLog) {
		outputView->hide();
		return;
	}
#ifndef NO_POPPLER_PREVIEW
  foreach (PDFDocument* doc, PDFDocument::documentList())
    if (doc->embeddedMode) {
      doc->close();
      return;
    }
#endif
    if(windowState()==Qt::WindowFullScreen && !configManager.disableEscForClosingFullscreen){
          stateFullScreen=saveState(1);
          setWindowState(Qt::WindowNoState);
          restoreState(windowstate,0);
          fullscreenModeAction->setChecked(false);
          return;
    }
	QTime ct = QTime::currentTime();
	if (ct.second() % 5 != 0) return;
	for (int i=2;i<63;i++) if (ct.minute() != i && ct.minute() % i  == 0) return;
	txsInformation("<html><head></head><body><img src=':/images/egg.png'></body></html>");
}

void Texmaker::setFullScreenMode() {
	if(!fullscreenModeAction->isChecked()) {
		stateFullScreen=saveState(1);
		showNormal();
        restoreState(windowstate,0);
#if QT_VERSION < 0x040701
		setUnifiedTitleAndToolBarOnMac(true);
#endif
	}
	else {
		windowstate=saveState(0);
#if QT_VERSION < 0x040701
		setUnifiedTitleAndToolBarOnMac(false); //prevent crash, see https://bugreports.qt-project.org/browse/QTBUG-16274?page=com.atlassian.jira.plugin.system.issuetabpanels:all-tabpanel
#endif
		showFullScreen();
        restoreState(stateFullScreen,1);
	}
}

void Texmaker::viewAlignWindows() {
  QWidgetList windows = QApplication::topLevelWidgets();
#ifndef NO_POPPLER_PREVIEW
  // find first pdf viewer window
  PDFDocument *pdfViewer = 0;
  foreach (QWidget *w, windows) {
    pdfViewer = qobject_cast<PDFDocument *>(w);
    if (pdfViewer) break;
  }

  int splitXpos = frameGeometry().right();
  int frameWidth = frameGeometry().width() - width();
  int frameHeight = frameGeometry().height() - height();

  // main window "full size" to the left
  QRect screen = QApplication::desktop()->availableGeometry(this);
  move(screen.topLeft());
  resize(splitXpos - screen.left() - frameWidth, screen.height()-frameHeight);

  // pdfViewer "full size" to the left
  if (pdfViewer) {
    pdfViewer->move(splitXpos, screen.top());
    pdfViewer->resize(screen.right() - frameGeometry().right() - frameWidth, screen.height()-frameHeight);
  }
#endif
}

void Texmaker::viewSetHighlighting(QAction *act) {
	if (!currentEditor()) return;
	currentEditorView()->clearOverlays();
	m_languages->setLanguageFromName(currentEditor(), act->data().toString());
	// TODO: Check if reCheckSyntax is really necessary. Setting the language emits (among others) contentsChange(0, lines)
	currentEditorView()->reCheckSyntax();
}

void Texmaker::showHighlightingMenu() {
	// check active item just before showing the menu. So we don't have to keep track of the languages, e.g. when switching editors
	if (!currentEditor()) return;
	QLanguageDefinition *ld = currentEditor()->languageDefinition();
	if (ld) {
		foreach (QAction *act, highlightLanguageActions->actions()) {
			if (act->data().toString() == ld->language()) {
				act->setChecked(true);
				break;
			}
		}
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
void Texmaker::pdfClosed(){
#ifndef NO_POPPLER_PREVIEW
  PDFDocument* from = qobject_cast<PDFDocument*>(sender());
  if(from){
    if(from->embeddedMode){
      shrinkEmbeddedPDFViewer(true);
	  QList<int> sz=mainHSplitter->sizes(); // set widths to 50%, eventually restore user setting
      int sum=0;
      int last=0;
      foreach(int i,sz){
        sum+=i;
        last=i;
      }
      pdfSplitterRel=1.0*last/sum;

    }
  }
  //QTimer::singleShot(100, this, SLOT(restoreMacMenuBar()));
#endif
}

void Texmaker::restoreMacMenuBar(){
#if QT_VERSION<0x050000 && defined Q_OS_MAC
  //workaround to restore mac menubar
  menuBar()->setNativeMenuBar(false);
  menuBar()->setNativeMenuBar(true);
#endif
}

QObject* Texmaker::newPdfPreviewer(bool embedded){
#ifndef NO_POPPLER_PREVIEW
    PDFDocument* pdfviewerWindow=new PDFDocument(configManager.pdfDocumentConfig,embedded);
	if(embedded){
		mainHSplitter->addWidget(pdfviewerWindow);
		QList<int> sz=mainHSplitter->sizes(); // set widths to 50%, eventually restore user setting
		int sum=0;
		foreach(int i,sz){
			sum+=i;
		}
		sz.clear();
        if(pdfSplitterRel<0.1 || pdfSplitterRel>0.9) //sanity check
			pdfSplitterRel=0.5;
		sz << sum-qRound(pdfSplitterRel*sum);
		sz << qRound(pdfSplitterRel*sum);
		mainHSplitter->setSizes(sz);
	}
	connect(pdfviewerWindow, SIGNAL(triggeredAbout()), SLOT(HelpAbout()));
    connect(pdfviewerWindow, SIGNAL(triggeredEnlarge()), SLOT(enlargeEmbeddedPDFViewer()));
    connect(pdfviewerWindow, SIGNAL(triggeredShrink()), SLOT(shrinkEmbeddedPDFViewer()));
	connect(pdfviewerWindow, SIGNAL(triggeredManual()), SLOT(UserManualHelp()));
	connect(pdfviewerWindow, SIGNAL(documentClosed()), SLOT(pdfClosed()));
	connect(pdfviewerWindow, SIGNAL(triggeredQuit()), SLOT(fileExit()));
	connect(pdfviewerWindow, SIGNAL(triggeredConfigure()), SLOT(GeneralOptions()));
	connect(pdfviewerWindow, SIGNAL(syncSource(const QString&, int, bool, QString)), SLOT(syncFromViewer(const QString &, int, bool, QString)));
	connect(pdfviewerWindow, SIGNAL(focusEditor()), SLOT(focusEditor()));
	connect(pdfviewerWindow, SIGNAL(runCommand(const QString&, const QFileInfo&, const QFileInfo&, int)), &buildManager, SLOT(runCommand(const QString&, const QFileInfo&, const QFileInfo&, int)));
	connect(pdfviewerWindow, SIGNAL(triggeredClone()), SLOT(newPdfPreviewer()));
	
	PDFDocument* from = qobject_cast<PDFDocument*>(sender());
	if (from) {
		pdfviewerWindow->loadFile(from->fileName(), from->getMasterFile(), true);
		pdfviewerWindow->goToPage(from->widget()->getPageIndex());
	}//load file before enabling sync or it will jump to the first page
	
	foreach (PDFDocument* doc, PDFDocument::documentList()) {
		if (doc == pdfviewerWindow) continue;
		connect(doc, SIGNAL(syncView(QString,QFileInfo,int)), pdfviewerWindow, SLOT(syncFromView(QString,QFileInfo,int)));
		connect(pdfviewerWindow, SIGNAL(syncView(QString,QFileInfo, int)), doc, SLOT(syncFromView(QString,QFileInfo,int)));
	}
	return pdfviewerWindow;
#else
	return 0;
#endif
}

void Texmaker::masterDocumentChanged(LatexDocument * doc){
	Q_UNUSED(doc);
	Q_ASSERT(documents.singleMode()==!documents.masterDocument);
	if (documents.singleMode()){
		outputView->resetMessagesAndLog();
	} else {
		configManager.addRecentFile(documents.masterDocument->getFileName(),true);
		int pos=EditorTabs->currentIndex();
		EditorTabs->moveTab(pos,0);
	}

	updateMasterDocumentCaption();
	updateOpenDocumentMenu();
}

void Texmaker::aboutToDeleteDocument(LatexDocument * doc){
	emit infoFileClosed();
	for (int i=configManager.completerConfig->userMacros.size()-1;i>=0;i--)
		if (configManager.completerConfig->userMacros[i].document == doc)
			configManager.completerConfig->userMacros.removeAt(i);
}

//*********************************
void Texmaker::dragEnterEvent(QDragEnterEvent *event) {
	if (event->mimeData()->hasFormat("text/uri-list")) event->acceptProposedAction();
}

void Texmaker::dropEvent(QDropEvent *event) {
	QList<QUrl> uris=event->mimeData()->urls();
	
	QStringList imageFormats = InsertGraphics::imageFormats();
	saveCurrentCursorToHistory();

	bool alreadyMovedCursor = false;
	for (int i=0; i<uris.length(); i++) {
		QFileInfo fi = QFileInfo(uris.at(i).toLocalFile());
		if (imageFormats.contains(fi.suffix()) && currentEditor()) {
			if (!alreadyMovedCursor) {
				QPoint p = currentEditor()->mapToContents(currentEditor()->mapToFrame(currentEditor()->mapFrom(this, event->pos())));
				QDocumentCursor cur = currentEditor()->cursorForPosition(p);
				cur.beginEditBlock();
				if (!cur.atLineStart()) {
					if (!cur.movePosition(1, QDocumentCursor::NextBlock, QDocumentCursor::MoveAnchor)) {
						cur.movePosition(1, QDocumentCursor::EndOfBlock, QDocumentCursor::MoveAnchor);
						cur.insertLine();
					}
				}
				currentEditor()->setCursor(cur);
				cur.endEditBlock();
				alreadyMovedCursor = true;
			}
			QuickGraphics(uris.at(i).toLocalFile());
		} else if (fi.suffix() == Session::fileExtension()) {
			loadSession(fi.filePath());
		} else
			load(fi.filePath());
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
		updateMasterDocumentCaption();
		break;
	default:
		break;
	}
}

void Texmaker::resizeEvent(QResizeEvent *e){
	if (fileSelector)
		fileSelector.data()->setCentered(centralFrame->geometry());
	QMainWindow::resizeEvent(e);
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

void Texmaker::updateCompleter(LatexEditorView* edView) {
    QSet<QString> words;
	
	if (configManager.parseBibTeX) documents.updateBibFiles();
	
    if(!edView)
        edView=currentEditorView();
	
	QList<LatexDocument*> docs;
	if(edView && edView->document){
		// determine from which docs data needs to be collected
		docs=edView->document->getListOfDocs();
		// collect user commands and references
        foreach(LatexDocument* doc,docs){
			words.unite(doc->userCommandList());
			words.unite(doc->additionalCommandsList());
		}
	}
	
	// collect user commands and references
	foreach(const LatexDocument* doc,docs){
		foreach(const QString& refCommand, latexParser.possibleCommands["%ref"]){
            QString temp='@'+refCommand+"{%1}";
			foreach (const QString& l, doc->labelItems())
				words.insert(temp.arg(l));
		}
	}
	if (configManager.parseBibTeX){
		QStringList bibIds;

        QStringList collected_mentionedBibTeXFiles;
        foreach(const LatexDocument* doc,docs){
            collected_mentionedBibTeXFiles<<doc->listOfMentionedBibTeXFiles();
        }

        for (int i=0; i<collected_mentionedBibTeXFiles.count();i++){
            if (!documents.bibTeXFiles.contains(collected_mentionedBibTeXFiles[i])){
                qDebug("BibTeX-File %s not loaded",collected_mentionedBibTeXFiles[i].toLatin1().constData());
				continue; //wtf?s
			}
            BibTeXFileInfo& bibTex=documents.bibTeXFiles[collected_mentionedBibTeXFiles[i]];

			// add citation to completer for direct citation completion
			bibIds<<bibTex.ids;
		}
		//handle bibitem definitions
        foreach(const LatexDocument* doc,docs){
            bibIds<<doc->bibItems();
        }
		//automatic use of cite commands
        QStringList citationCommands;
		foreach(const QString& citeCommand, latexParser.possibleCommands["%cite"]){
            QString temp='@'+citeCommand+"{@}";
            citationCommands.append(temp);
            words.insert(temp);
            /*foreach (const QString &value, bibIds)
                words.insert(temp.arg(value));*/
        }
        foreach(QString citeCommand, latexParser.possibleCommands["%citeExtended"]){
            QString temp='@'+citeCommand.replace("%<bibid%>","@");
            citationCommands.append(temp);
            words.insert(temp);
        }
        completer->setAdditionalWords(citationCommands.toSet(),CT_CITATIONCOMMANDS);
		completer->setAdditionalWords(bibIds.toSet(),CT_CITATIONS);
	}
	
	completionBaseCommandsUpdated=false;
	
	completer->setAdditionalWords(words,CT_COMMANDS);
	if(edView) edView->viewActivated();
	
	if (!LatexCompleter::hasHelpfile()) {
		QFile f(findResourceFile("latexhelp.html"));
		if (!f.exists() || !f.open(QIODevice::ReadOnly| QIODevice::Text))  LatexCompleter::parseHelpfile("<missing>");
		else LatexCompleter::parseHelpfile(QTextStream(&f).readAll());
	}
	
	
	GrammarCheck::staticMetaObject.invokeMethod(grammarCheck, "init", Qt::QueuedConnection, Q_ARG(LatexParser, latexParser), Q_ARG(GrammarCheckerConfig, *configManager.grammarCheckerConfig));

    updateHighlighting();

	mCompleterNeedsUpdate=false;
}

void Texmaker::outputPageChanged(const QString &id) {
	if (id == outputView->LOG_PAGE && !outputView->getLogWidget()->logPresent()) {
		if (!loadLog())
			return;
		if (HasLatexErrors())
			ViewLog();
	}
}

void Texmaker::jumpToSearch(QDocument* doc, int lineNumber){
	REQUIRE(qobject_cast<LatexDocument*>(doc));
	if(currentEditor() && currentEditor()->document()==doc && currentEditor()->cursor().lineNumber()==lineNumber)
	{
		QDocumentCursor c=currentEditor()->cursor();
		int col=c.columnNumber();
		gotoLine(lineNumber);
		col=outputView->getNextSearchResultColumn(c.line().text() ,col+1);
		currentEditor()->setCursorPosition(lineNumber,col,false);
		currentEditor()->ensureCursorVisible(QEditor::Navigation);
	} else {
		gotoLine(lineNumber, doc->getFileName().size()?doc->getFileName():qobject_cast<LatexDocument*>(doc)->getTemporaryFileName());
		int col=outputView->getNextSearchResultColumn(currentEditor()->document()->line(lineNumber).text() ,0);
		currentEditor()->setCursorPosition(lineNumber,col,false);
		currentEditor()->ensureCursorVisible(QEditor::Navigation);
		outputView->showPage(outputView->SEARCH_RESULT_PAGE);
	}
	QDocumentCursor highlight = currentEditor()->cursor();
	highlight.movePosition(outputView->searchExpression().length(), QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
	currentEditorView()->temporaryHighlight(highlight);
}

void Texmaker::gotoLine(int line, int col, LatexEditorView *edView, QEditor::MoveFlags mflags, bool setFocus) {
	bool changeCurrentEditor = (edView != currentEditorView());
	if (!edView)
		edView = currentEditorView(); // default

	if (!edView || line<0) return;

	saveCurrentCursorToHistory();

	if (changeCurrentEditor) {
		EditorTabs->setCurrentEditor(edView);
		mflags &= ~QEditor::Animated;
	}
	edView->editor->setCursorPosition(line,col,false);
	edView->editor->ensureCursorVisible(mflags);
	if (setFocus) {
		edView->editor->setFocus();
	}
}

bool Texmaker::gotoLine(int line, const QString &fileName){
	LatexEditorView* edView = getEditorViewFromFileName(fileName, true);
	QEditor::MoveFlags mflags = QEditor::Navigation;
	if (!edView) {
		if (!load(fileName)) return false;
		mflags &= ~QEditor::Animated;
	}
	gotoLine(line, 0, edView, mflags);
	return true;
}

void Texmaker::gotoLogEntryEditorOnly(int logEntryNumber) {
	if (logEntryNumber<0 || logEntryNumber>=outputView->getLogWidget()->getLogModel()->count()) return;
	QString fileName = outputView->getLogWidget()->getLogModel()->at(logEntryNumber).file;
	if (!ActivateEditorForFile(fileName, true))
		if (!load(fileName)) return;
	if (currentEditorView()->logEntryToLine.isEmpty()) {
		updateLogEntriesInEditors();
	}
	if (configManager.showLogMarkersWhenClickingLogEntry) {
		setLogMarksVisible(true);
	}
	//get line
	QDocumentLineHandle* lh = currentEditorView()->logEntryToLine.value(logEntryNumber, 0);
	if (!lh) return;
	//goto
	gotoLine(currentEditor()->document()->indexOf(lh));
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

	REQUIRE_RET(outputView->getLogWidget()->getLogModel(), true);
	QList<int> errors = currentEditorView()->lineToLogEntries.values(lh);
	QString msg = outputView->getLogWidget()->getLogModel()->htmlErrorTable(errors);

	QToolTip::showText(p, msg, 0);
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

void Texmaker::syncFromViewer(const QString &fileName, int line, bool activate, const QString& guessedWord){
	if (!ActivateEditorForFile(fileName, true, activate))
		if (!load(fileName)) return;
    shrinkEmbeddedPDFViewer();

	QDocumentLine l = currentEditorView()->document->lineFromLineSnapshot(line);
	if (l.isValid()) {
		int originalLineNumber = currentEditorView()->document->indexOf(l, line);
		if (originalLineNumber >= 0) line = originalLineNumber;
	}

	gotoLine(line, 0, 0, QEditor::Navigation, activate);
	Q_ASSERT(currentEditor());
	
	//qDebug() << line << guessedWord;

	QString checkLine =currentEditor()->cursor().line().text();
	int column = checkLine.indexOf(guessedWord);
	if (column == -1) column = checkLine.indexOf(guessedWord, Qt::CaseInsensitive);
	QString changedWord = guessedWord;
	if (column == -1) {//search again and ignore useless characters
		QString regex;
		for (int i=0;i<changedWord.size();i++)
			if (changedWord[i].category() == QChar::Other_Control || changedWord[i].category() == QChar::Other_Format)
				changedWord[i] = '\1';
		foreach (const QString& x, changedWord.split('\1', QString::SkipEmptyParts))
			if (regex.isEmpty()) regex += QRegExp::escape(x);
			else regex += ".{0,2}" + QRegExp::escape(x);
		//qDebug() << changedWord << regex;
		column = checkLine.indexOf(QRegExp(regex), Qt::CaseSensitive);
		if (column == -1) column = checkLine.indexOf(QRegExp(regex), Qt::CaseInsensitive);
	}
	if (column == -1) {//search again and allow additional whitespace
		QString regex;
		foreach (const QString & x , changedWord.split(" ",QString::SkipEmptyParts))
			if (regex.isEmpty()) regex = QRegExp::escape(x);
			else regex+="\\s+"+QRegExp::escape(x);
		column = checkLine.indexOf(QRegExp(regex), Qt::CaseSensitive);
		if (column == -1) column = checkLine.indexOf(QRegExp(regex), Qt::CaseInsensitive);
	}
	if (column == -1) {
		int bestMatch = -1, bestScore = 0;
		for (int i=0;i<checkLine.size()-guessedWord.size();i++) {
			int score = 0;
			for (int c = i, s = 0; c < checkLine.size() && s < guessedWord.size(); c++, s++) {
				QChar C = checkLine[c], S = guessedWord[s];
				if (C == S) score += 5; //perfect match
				else if (C.toLower() == S.toLower()) score += 2; //ok match
				else if (C.isSpace()) s--; //skip spaces
				else if (S.isSpace()) c--; //skip spaces
				else if (S.category() == QChar::Other_Control || S.category() == QChar::Other_Format) {
					for (s++; s < guessedWord.size() && (guessedWord[s].category() == QChar::Other_Control||guessedWord[s].category() == QChar::Other_Format);s++); //skip nonsense
					if (s >= guessedWord.size()) continue;
					if (guessedWord[s] == C) { score += 5; continue; }
					if (c+1 < checkLine.size() && guessedWord[s] == checkLine[c+1]) { score += 5; c++; continue; }
					//also skip next character after that nonsense
				}
			}
			if (score > bestScore) bestScore = score, bestMatch = i;
		}
		if (bestScore > guessedWord.size()*5 / 3) column = bestMatch; //accept if 0.33 similarity
	}

	QDocumentCursor highlight(currentEditor()->document(), line, 0);
	if (column > -1 && !guessedWord.isEmpty()) {
		int cursorCol = column+guessedWord.length()/2;
		highlight.setColumnNumber(cursorCol);
		highlight.movePosition(1, QDocumentCursor::StartOfWord, QDocumentCursor::MoveAnchor);
		highlight.movePosition(1, QDocumentCursor::EndOfWord, QDocumentCursor::KeepAnchor);
		if (!highlight.hasSelection()) { // fallback, if we are not at a word
			highlight.setColumnNumber(cursorCol);
			highlight.movePosition(1, QDocumentCursor::PreviousCharacter, QDocumentCursor::MoveAnchor);
			highlight.movePosition(1, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
		}
		currentEditor()->setCursorPosition(currentEditor()->cursor().lineNumber(), cursorCol,false);
		currentEditor()->ensureCursorVisible(QEditor::KeepSurrounding | QEditor::ExpandFold);
	} else {
		highlight.movePosition(1, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
	}
	currentEditorView()->temporaryHighlight(highlight);
	
	if (activate) {
		raise();
		show();
		activateWindow();
		if (isMinimized()) showNormal();
	}
	
}

void Texmaker::goBack() {
	QDocumentCursor currentCur;
	if (currentEditorView()) currentCur = currentEditorView()->editor->cursor();
	setGlobalCursor(cursorHistory->back(currentCur));
}

void Texmaker::goForward() {
	QDocumentCursor currentCur;
	if (currentEditorView()) currentCur = currentEditorView()->editor->cursor();
	setGlobalCursor(cursorHistory->forward(currentCur));
}

void Texmaker::setGlobalCursor(const QDocumentCursor &c) {
	if (c.isValid()) {
		LatexDocument *doc = qobject_cast<LatexDocument*>(c.document());
		if (doc && doc->getEditorView()) {
			LatexEditorView *edView = doc->getEditorView();
			QEditor::MoveFlags mflags = QEditor::KeepSurrounding | QEditor::ExpandFold;
			if (edView == currentEditorView()) mflags |= QEditor::Animated;
			EditorTabs->setCurrentEditor(edView);
			edView->editor->setFocus();
			edView->editor->setCursor(c, false);
			edView->editor->ensureCursorVisible(mflags);
		}
	}
}

void Texmaker::fuzzBackForward(){
#ifdef NOT_DEFINED__FUZZER_NEEDED_ONLY_FOR_DEBUGGING_RANDOM_CRASH_OF_CURSOR_HISTORY
	int rep = random() % (1+cursorHistory->count());
	for (int j = 0; j < rep; j++) goBack();
	rep = random() % (1+cursorHistory->count());
	for (int j = 0; j < rep; j++) goForward();
#endif
}

void Texmaker::fuzzCursorHistory(){
#ifdef NOT_DEFINED__FUZZER_NEEDED_ONLY_FOR_DEBUGGING_RANDOM_CRASH_OF_CURSOR_HISTORY
	QString fillText;
	for (int i = 0; i < 100; i++)
		fillText += "\n" + QString("foobar abc xyz").repeated(random() % 100);
	for (int i = 0; i < 100; i++) {
		if (!documents.documents.isEmpty()) {
			if (random() % 1000 < 500) documents.deleteDocument(documents.documents[random() % documents.documents.length()]);
			fuzzBackForward();
		}
		if (!documents.documents.isEmpty()) {
			QApplication::processEvents();
			if (random() % 1000 < 500) documents.deleteDocument(documents.documents[random() % documents.documents.length()]);
			fuzzBackForward();
		}
		fileNew();
		currentEditor()->setText(fillText);
		QApplication::processEvents();
		int rep = random() % 100;
		for (int j = 0; j < rep; j++) {
			EditorView->setCurrentIndex(EditorView->count());
			int l =  random() % currentEditor()->document()->lineCount();
			int c = random() % (currentEditor()->document()->line(l).length()+100);
			currentEditor()->setCursor(currentEditor()->document()->cursor(l, c, random() % 100, random() % 100));
			saveCurrentCursorToHistory();
			fuzzBackForward();
		}
	}
#endif
}

void Texmaker::saveCurrentCursorToHistory() {
	saveEditorCursorToHistory(currentEditorView());
}

void Texmaker::saveEditorCursorToHistory(LatexEditorView *edView) {
	if (!edView) return;
	cursorHistory->insertPos(edView->editor->cursor());
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
		menu.addSeparator();
		menu.addAction(tr("Move document to &front"), this, SLOT(moveDocumentToFront()));
		menu.addAction(tr("Move document to &end"), this, SLOT(moveDocumentToEnd()));
		menu.addSeparator();
		menu.addAction(tr("Expand Subitems"), this, SLOT(structureContextMenuExpandSubitems()));
		menu.addAction(tr("Collapse Subitems"), this, SLOT(structureContextMenuCollapseSubitems()));
		menu.exec(structureTreeView->mapToGlobal(point));
	}
	if (!entry->parent) return;
	if (entry->type==StructureEntry::SE_LABEL) {
		QMenu menu;
		menu.addAction(tr("Insert"),this, SLOT(editPasteRef()))->setData(entry->title);
		menu.addAction(tr("Insert as %1").arg("\\ref{...}"),this, SLOT(editPasteRef()))->setData(QString("\\ref{%1}").arg(entry->title));
		menu.addAction(tr("Insert as %1").arg("\\pageref{...}"),this, SLOT(editPasteRef()))->setData(QString("\\pageref{%1}").arg(entry->title));
		menu.exec(structureTreeView->mapToGlobal(point));
	}
	if (entry->type==StructureEntry::SE_SECTION) {
		QMenu menu(this);

		StructureEntry *labelEntry = LatexDocumentsModel::labelForStructureEntry(entry);
		if (labelEntry) {
			menu.addAction(tr("Insert Label"),this, SLOT(editPasteRef()))->setData(labelEntry->title);
			menu.addAction(tr("Insert \\ref to Label"),this, SLOT(editPasteRef()))->setData(QString("\\ref{%1}").arg(labelEntry->title));
			menu.addSeparator();
		} else {
			menu.addAction(tr("Create Label"),this, SLOT(createLabelFromAction()))->setData(QVariant::fromValue(entry));
			menu.addSeparator();
		}

		menu.addAction(tr("Copy"),this, SLOT(editSectionCopy()));
		menu.addAction(tr("Cut"),this, SLOT(editSectionCut()));
		menu.addAction(tr("Paste Before"),this, SLOT(editSectionPasteBefore()));
		menu.addAction(tr("Paste After"),this, SLOT(editSectionPasteAfter()));
		menu.addSeparator();
		menu.addAction(tr("Indent Section"),this, SLOT(editIndentSection()));
		menu.addAction(tr("Unindent Section"),this, SLOT(editUnIndentSection()));
		if (!entry->children.isEmpty()) {
			menu.addSeparator();
			menu.addAction(tr("Expand Subitems"), this, SLOT(structureContextMenuExpandSubitems()));
			menu.addAction(tr("Collapse Subitems"), this, SLOT(structureContextMenuCollapseSubitems()));
		}
		menu.exec(structureTreeView->mapToGlobal(point));
	}
    if (entry->type==StructureEntry::SE_MAGICCOMMENT) {
        QMenu menu;
        menu.addAction(LatexEditorView::tr("Go to Definition"),this, SLOT(moveCursorTodlh()))->setData(QVariant::fromValue(entry));
        menu.exec(structureTreeView->mapToGlobal(point));
    }
    if (entry->type==StructureEntry::SE_INCLUDE) {
        QMenu menu;
        menu.addAction(LatexEditorView::tr("Open Document"),this, SLOT(openExternalFile()))->setData(QVariant::fromValue(entry));
        menu.addAction(LatexEditorView::tr("Go to Definition"),this, SLOT(moveCursorTodlh()))->setData(QVariant::fromValue(entry));
        menu.exec(structureTreeView->mapToGlobal(point));
    }

}

void Texmaker::openExternalFile(){
    QAction *act = qobject_cast<QAction *>(sender());
    if (!act) return;
    StructureEntry *entry = qvariant_cast<StructureEntry *>(act->data());
    if(entry){
        openExternalFile(entry->title);
    }
}

void Texmaker::structureContextMenuCloseDocument(){
	StructureEntry *entry=LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry) return;
	LatexDocument* document = entry->document;
	if (!document) return;
	if (document->getEditorView()) CloseEditorTab(EditorTabs->indexOf(document->getEditorView()));
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
		EditorTabs->setCurrentEditor(document->getEditorView());
		ToggleMode();
	}
}

void Texmaker::structureContextMenuExpandSubitems() {
	setSubtreeExpanded(structureTreeView, structureTreeView->currentIndex(), true);
}

void Texmaker::structureContextMenuCollapseSubitems() {
	setSubtreeExpanded(structureTreeView, structureTreeView->currentIndex(), false);
}

void Texmaker::editPasteRef() {
	if (!currentEditorView()) return;
	
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;

	currentEditor()->write(action->data().toString());
	currentEditorView()->setFocus();
}

void Texmaker::previewLatex(){
	if (!currentEditorView()) return;
	// get selection
	QDocumentCursor c = currentEditorView()->editor->cursor();
	QDocumentCursor previewc;
	if (c.hasSelection()) {
		previewc = c; //X o riginalText = c.selectedText();
	} else {
		// if in math mode, move cursor to opening bracket
		//TODO: Is there a more elegant solution to determine the beginning of a math environment.
		QDocumentLine dl = c.line();
		int col = c.columnNumber();
		QList<int> mathFormats = QList<int>() << m_formats->id("numbers") << m_formats->id("math-keyword");
		mathFormats.removeAll(0); // keep only valid entries in list
		while(col>0 && mathFormats.contains(dl.getFormatAt(col-1))) col --;
		c.setColumnNumber(col);
		previewc = currentEditorView()->parenthizedTextSelection(c);
	}
	if (!previewc.hasSelection()) return;
	
	showPreview(previewc,true);
	
}
void Texmaker::previewAvailable(const QString& imageFile, const PreviewSource& source){
	if (configManager.previewMode == ConfigManager::PM_BOTH ||
			configManager.previewMode == ConfigManager::PM_PANEL||
			(configManager.previewMode == ConfigManager::PM_TOOLTIP_AS_FALLBACK && outputView->isPreviewPanelVisible())) {
		outputView->showPage(outputView->PREVIEW_PAGE);
		outputView->previewLatex(QPixmap(imageFile));
	}
	if (configManager.previewMode == ConfigManager::PM_BOTH ||
			configManager.previewMode == ConfigManager::PM_TOOLTIP||
			source.atCursor ||
			(configManager.previewMode == ConfigManager::PM_TOOLTIP_AS_FALLBACK && !outputView->isPreviewPanelVisible()) ||
			(source.fromLine < 0)) {
		QPoint p;
		if(source.atCursor)
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
	if (configManager.previewMode == ConfigManager::PM_INLINE && source.fromLine >= 0){
		QDocument* doc = currentEditor()->document();
		doc->setForceLineWrapCalculation(true);
		int toLine = qBound(0, source.toLine, doc->lines() - 1);
		for (int l = source.fromLine; l <= toLine; l++ )
			if (doc->line(l).getCookie(QDocumentLine::PICTURE_COOKIE).isValid()) {
				doc->line(l).removeCookie(QDocumentLine::PICTURE_COOKIE);
				doc->line(l).removeCookie(QDocumentLine::PICTURE_COOKIE_DRAWING_POS);
				doc->line(l).setFlag(QDocumentLine::LayoutDirty);
				doc->adjustWidth(l);
			}
		doc->line(toLine).setCookie(QDocumentLine::PICTURE_COOKIE, QVariant::fromValue<QPixmap>(QPixmap(imageFile)));
		doc->line(toLine).setFlag(QDocumentLine::LayoutDirty);
		doc->adjustWidth(toLine);
	}
}

void Texmaker::clearPreview() {
	QEditor* edit = currentEditor();
	if (!edit) return;

	int startLine = 0;
	int endLine = 0;

	QAction *act = qobject_cast<QAction *>(sender());
	if (act && act->data().isValid()) {
		// inline preview context menu supplies the calling point in doc coordinates as data
		startLine = edit->document()->indexOf(edit->lineAtPosition(act->data().toPoint()));
		// slight performance penalty for use of lineNumber(), which is not stictly necessary because
		// we convert it back to a QDocumentLine, but easier to handle together with the other cases
		endLine = startLine;
		act->setData(QVariant());
	} else if (edit->cursor().hasSelection()) {
		startLine = edit->cursor().selectionStart().lineNumber();
		endLine = edit->cursor().selectionEnd().lineNumber();
	} else {
		startLine = edit->cursor().lineNumber();
		endLine = startLine;
	}

	for (int i=startLine; i<=endLine; i++){
		edit->document()->line(i).removeCookie(QDocumentLine::PICTURE_COOKIE);
		edit->document()->line(i).removeCookie(QDocumentLine::PICTURE_COOKIE_DRAWING_POS);
		edit->document()->adjustWidth(i);
		for (int j=currentEditorView()->autoPreviewCursor.size()-1;j>=0;j--)
			if (currentEditorView()->autoPreviewCursor[j].selectionStart().lineNumber() <= i &&
					currentEditorView()->autoPreviewCursor[j].selectionEnd().lineNumber() >= i)
				currentEditorView()->autoPreviewCursor.removeAt(j);
	}
}

void Texmaker::showImgPreview(const QString& fname){
    completerPreview=(sender()==completer); // completer needs signal as answer
    QString imageName=fname;
    QFileInfo fi(fname);
    QString suffix;
    QStringList suffixList;
    suffixList<<"jpg"<<"png"<<"pdf";
    if(fi.exists()){
        if(!suffixList.contains(fi.suffix()))
                return;
        suffix=fi.suffix();
    }

    if(suffix.isEmpty()){
        foreach(QString elem,suffixList){
            imageName=fname+elem;
            fi.setFile(imageName);
            if(fi.exists()){
                suffix=elem;
                break;
            }
        }
    }

    suffixList.clear();
    suffixList<<"jpg"<<"png";
    if(suffixList.contains(suffix)){
        QPoint p;
        //if(previewEquation)
            p=currentEditorView()->getHoverPosistion();
        //else
        //    p=currentEditorView()->editor->mapToGlobal(currentEditorView()->editor->mapFromContents(currentEditorView()->editor->cursor().documentPosition()));
        QRect screen = QApplication::desktop()->screenGeometry();
        QPixmap img(imageName);
        int w=img.width();
        if(w>screen.width()) w=screen.width()-2;
        QString text=QString("<img src=\""+imageName+"\" width=%1 />").arg(w);
        if(completerPreview){
            emit ImgPreview(text);
        }else{
            QToolTip::showText(p, text, 0);
            LatexEditorView::hideTooltipWhenLeavingLine=currentEditorView()->editor->cursor().lineNumber();
        }
    }
#ifndef NO_POPPLER_PREVIEW
    if(suffix=="pdf"){
        //render pdf preview
        PDFRenderManager *renderManager=new PDFRenderManager(this,1);
        PDFRenderManager::Error error = PDFRenderManager::NoError;
        QSharedPointer<Poppler::Document> document = renderManager->loadDocument(imageName, error);
        if(error==PDFRenderManager::NoError){
            renderManager->renderToImage(0,this,"showImgPreviewFinished",20,20,-1,-1,-1,-1,false,true);
        }else{
            delete renderManager;
        }
    }
#endif
}

void Texmaker::showImgPreviewFinished(const QPixmap& pm, int page){
    if (!currentEditorView()) return;
    Q_UNUSED(page);
    QPoint p;
    //if(previewEquation)
        p=currentEditorView()->getHoverPosistion();
    //else
    //    p=currentEditorView()->editor->mapToGlobal(currentEditorView()->editor->mapFromContents(currentEditorView()->editor->cursor().documentPosition()));
    QRect screen = QApplication::desktop()->screenGeometry();
    int w=pm.width();
    if(w>screen.width()) w=screen.width()-2;
    QString text;
#if QT_VERSION >= 0x040700
    text= QString("%1").arg(getImageAsText(pm));
#else
    QString tempPath = QDir::tempPath()+QDir::separator()+"."+QDir::separator();
    pm.save(tempPath+"txs_preview.png","PNG");
    buildManager.addPreviewFileName(tempPath+"txs_preview.png");
    text=QString("<img src=\""+tempPath+"txs_preview.png\" width=%1 />").arg(w);
#endif
    if(completerPreview){
        emit ImgPreview(text);
    }else{
        QToolTip::showText(p, text, 0);
        LatexEditorView::hideTooltipWhenLeavingLine=currentEditorView()->editor->cursor().lineNumber();
    }
#ifndef NO_POPPLER_PREVIEW
    PDFRenderManager* renderManager = qobject_cast<PDFRenderManager*>(sender());
    delete renderManager;
#endif
}

void Texmaker::showPreview(const QString& text){
    LatexEditorView* edView=getEditorViewFromFileName(documents.getCompileFileName()); //todo: temporary compi
    if(!edView)
        edView=currentEditorView();
	if (!edView) return;
	int m_endingLine=edView->editor->document()->findLineContaining("\\begin{document}",0,Qt::CaseSensitive);
	if (m_endingLine<0) return; // can't create header
	QStringList header;
	for (int l=0; l<m_endingLine; l++)
		header << edView->editor->document()->line(l).text();
	header << "\\pagestyle{empty}";// << "\\begin{document}";
	buildManager.preview(header.join("\n"), PreviewSource(text, -1, -1, true), documents.getCompileFileName(), edView->editor->document()->codec());
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
	const LatexDocument *doc=documents.getMasterDocumentForDoc();
	LatexEditorView* edView=(doc && doc->getEditorView())?doc->getEditorView():currentEditorView();
	if (!edView) return;
	int m_endingLine=edView->editor->document()->findLineContaining("\\begin{document}",0,Qt::CaseSensitive);
	if (m_endingLine<0) return; // can't create header
	QStringList header;
	for (int l=0; l<m_endingLine; l++)
		header << edView->editor->document()->line(l).text();
	header << "\\pagestyle{empty}";// << "\\begin{document}";
	PreviewSource ps(originalText, previewc.selectionStart().lineNumber(), previewc.selectionEnd().lineNumber(), false);
	buildManager.preview(header.join("\n"), ps,  documents.getCompileFileName(), edView->editor->document()->codec());
	
	if (!addToList)
		return;
	if (configManager.autoPreview == ConfigManager::AP_PREVIOUSLY) {
		QList<QDocumentCursor> & clist = currentEditorView()->autoPreviewCursor;
		for (int i=clist.size()-1;i>=0;i--)
			if (clist[i].anchorLineNumber() <= ps.toLine &&
					clist[i].lineNumber()   >= ps.fromLine)
				clist.removeAt(i);
		
		QDocumentCursor ss = previewc.selectionStart();
		QDocumentCursor se = previewc.selectionEnd();
		QDocumentCursor c(ss, se);
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
		currentEditor()->write("\\ref{"+rx.cap(1)+"}");
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

void Texmaker::editorTabContextMenu(const QPoint &point) {
	if (point.isNull()) return;

	QMenu *documentsMenu = getManagedMenu("main/view/documents");
	documentsMenu->exec(EditorTabs->mapToGlobal(point));
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
			foreach (LatexEditorView *edView, EditorTabs->editors()) {
				editors << edView->editor;
			}
			break;
		default:
			break;
		}
		outputView->clearSearch();
		outputView->setSearchExpression(dlg->getSearchWord(),dlg->isCase(),dlg->isWords(),dlg->isRegExp());
		foreach(QEditor *ed,editors){
			LatexDocument *doc=qobject_cast<LatexDocument*>(ed->document());
			if (!doc) continue;
			QList<QDocumentLineHandle *> lines;
			for(int l=0;l<doc->lineCount();l++){
				l=doc->findLineRegExp(dlg->getSearchWord(),l,dlg->isCase() ? Qt::CaseSensitive : Qt::CaseInsensitive,dlg->isWords(),dlg->isRegExp());
				if(l>-1) lines << doc->line(l).handle();
				if(l==-1) break;
			}
			
			if(!lines.isEmpty()){ // don't add empty searches
				if (ed->fileName().isEmpty() && doc->getTemporaryFileName().isEmpty())
					doc->setTemporaryFileName(buildManager.createTemporaryFileName());
				outputView->addSearch(lines, doc);
				outputView->showPage(outputView->SEARCH_RESULT_PAGE);
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
	syncPDFViewer(currentEditor()->cursor(), false);
}

void Texmaker::syncPDFViewer(QDocumentCursor cur, bool inForeground) {
#ifndef NO_POPPLER_PREVIEW
	if(PDFDocument::documentList().isEmpty() && inForeground) {
		// open new viewer, if none exists
		QAction *viewAct = getManagedAction("main/tools/view");
		if (viewAct) viewAct->trigger();
		return;
	}

	foreach (PDFDocument* viewer, PDFDocument::documentList()) {
		if (inForeground || viewer->followCursor()) {
			int lineNumber = cur.isValid() ? cur.lineNumber() : currentLine;
			LatexDocument *doc = qobject_cast<LatexDocument *>(cur.document());
			if (doc) {
				int originalLineNumber = doc->lineToLineSnapshotLineNumber(cur.line());
				if (originalLineNumber >= 0) lineNumber = originalLineNumber;
			}
			viewer->syncFromSource(getCurrentFileName(), lineNumber, false);
		}
		if (inForeground) {
			viewer->raise();
		}
	}
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
		//checkin(fn,text);
		if(svnadd(fn)){
			checkin(fn,text,configManager.svnKeywordSubstitution);
		} else {
			//create simple repository
			svncreateRep(fn);
			svnadd(fn);
			checkin(fn,text,configManager.svnKeywordSubstitution);
		}
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
	QString cmd=BuildManager::CMD_SVN + " up --non-interactive \""+fn+"\"";
	statusLabelProcess->setText(QString(" svn update "));
	QString buffer;
	runCommand(cmd,&buffer);
	outputView->insertMessageLine(buffer);
}

void Texmaker::fileUpdateCWD(QString filename){
	if (!currentEditorView()) return;
	QString fn=filename.isEmpty() ? currentEditor()->fileName() : filename;
	if(fn.isEmpty()) return;
	QString cmd=BuildManager::CMD_SVN;
	fn=QFileInfo(fn).path();
	cmd+=" up --non-interactive  \""+fn+"\"";
	statusLabelProcess->setText(QString(" svn update "));
	QString buffer;
	runCommand(cmd, &buffer);
	outputView->insertMessageLine(buffer);
}

void Texmaker::checkin(QString fn, QString text, bool blocking){
  Q_UNUSED(blocking)
  QString cmd=BuildManager::CMD_SVN;
  cmd+=" ci -m \""+text+"\" \""+fn+("\"");
  statusLabelProcess->setText(QString(" svn check in "));
  //TODO: blocking
  QString buffer;
  runCommand(cmd,&buffer);
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
	QString cmd=BuildManager::CMD_SVN;
	cmd+=" add \""+fn+("\"");
	statusLabelProcess->setText(QString(" svn add "));
	QString buffer;
	runCommand(cmd, &buffer);
	return true;
}

void Texmaker::svnLock(QString fn){
	QString cmd=BuildManager::CMD_SVN;
	cmd+=" lock \""+fn+("\"");
	statusLabelProcess->setText(QString(" svn lock "));
	QString buffer;
	runCommand(cmd, &buffer);
}


void Texmaker::svncreateRep(QString fn){
	QString cmd=BuildManager::CMD_SVN;
	QString admin=BuildManager::CMD_SVNADMIN;
	QString path=QFileInfo(fn).absolutePath();
	admin+=" create "+path+"/repo";
	statusLabelProcess->setText(QString(" svn create repo "));
	QString buffer;
	runCommand(admin,&buffer);
	QString scmd=cmd+" mkdir file:///"+path+"/repo/trunk -m\"txs auto generate\"";
	runCommand(scmd,&buffer);
	scmd=cmd+" mkdir file:///"+path+"/repo/branches -m\"txs auto generate\"";
	runCommand(scmd,&buffer);
	scmd=cmd+" mkdir file:///"+path+"/repo/tags -m\"txs auto generate\"";
	runCommand(scmd,&buffer);
	statusLabelProcess->setText(QString(" svn checkout repo"));
	cmd+=" co file:///"+path+"/repo/trunk "+path;
	runCommand(cmd,&buffer);
}

void Texmaker::svnUndo(bool redo){
	QString cmd_svn=BuildManager::CMD_SVN;
	QString fn=currentEditor()->fileName();
	// get revisions of current file
	QString cmd=cmd_svn+" log "+fn;
	QString buffer;
	runCommand(cmd, &buffer);
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
    //for(int i=0;i<diff.length();i++)
    //   qDebug()<<diff[i];
	if(diff.contains("\r\n")){
		lines=diff.split("\r\n");
	}else{
		if(diff.contains("\n")){
			lines=diff.split("\n");
		}else{
			lines=diff.split("\r");
		}
	}
    for(int i=0;i<lines.length();i++){
        //workaround for svn bug
        // at times it shows text@@ pos insted of text \n @@ ...
        if(lines[i].contains("@@")){
            int p=lines[i].indexOf("@@");
            lines[i]=lines[i].mid(p);
        }
    }
    for(int i=0;i<3;i++) lines.removeFirst();
    if(!lines.first().contains("@@")){
        lines.removeFirst();
    }

    QRegExp rx("@@ -(\\d+),(\\d+)\\s*\\+(\\d+),(\\d+)");
	int cur_line;
	bool atDocEnd=false;
	QDocumentCursor c=ed->cursor();
	foreach(const QString& elem,lines){
        QChar ch=' ';
        if(!elem.isEmpty()){
            ch=elem.at(0);
        }
		if(ch=='@'){
			if(rx.indexIn(elem)>-1){
                cur_line=rx.cap(3).toInt();
				c.moveTo(cur_line-1,0);
            }else{
                qDebug()<<"Bug";
            }
		}else{
			if(ch=='-'){
				atDocEnd=(c.lineNumber()==ed->document()->lineCount()-1);
                if(c.line().text()!=elem.mid(1))
                    qDebug()<<"del:"<<c.line().text()<<elem;
                c.eraseLine();
				if(atDocEnd) c.deletePreviousChar();
			}else{
				if(ch=='+'){
					atDocEnd=(c.lineNumber()==ed->document()->lineCount()-1);
					if(atDocEnd){
						c.movePosition(1,QDocumentCursor::EndOfLine,QDocumentCursor::MoveAnchor);
						c.insertLine();
					}
                    c.insertText(elem.mid(1));
					// if line contains \r, no further line break needed
					if(!atDocEnd){
						c.insertText("\n");
					}
				} else {
					atDocEnd=(c.lineNumber()==ed->document()->lineCount()-1);
                    int limit=5;
					if(!atDocEnd){
                        while((c.line().text()!=elem.mid(1))&&(limit>0)&&(c.lineNumber()<ed->document()->lineCount()-1)){
                            qDebug()<<c.line().text()<<c.lineNumber()<<"<>"<<elem.mid(1);
                            c.movePosition(1,QDocumentCursor::NextLine,QDocumentCursor::MoveAnchor);
                            c.movePosition(1,QDocumentCursor::StartOfLine,QDocumentCursor::MoveAnchor);
                            limit--;
                            if(limit==0){
                                qDebug()<<"failed";
                            }
                        }
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
        removeDiffMarkers();// clean document from diff markers first
		currentEditor()->save();
		//currentEditorView()->editor->setModified(false);
		MarkCurrentFileAsRecent();
		checkin(currentEditor()->fileName(),"txs auto checkin",true);
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
	QString cmd=BuildManager::CMD_SVN;
	cmd+=" st \""+filename+("\"");
	statusLabelProcess->setText(QString(" svn status "));
	QString buffer;
	runCommand(cmd, &buffer);
	if(buffer.isEmpty()) return CheckedIn;
	if(buffer.startsWith("?")) return Unmanaged;
	if(buffer.startsWith("M")) return Modified;
	if(buffer.startsWith("C")) return InConflict;
	if(buffer.startsWith("L")) return Locked;
	return Unknown;
}

void Texmaker::changeToRevision(QString rev,QString old_rev){
	QString cmd_svn=BuildManager::CMD_SVN;
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
	runCommand(cmd, &buffer);
	// patch
	svnPatch(currentEditor(),buffer);
	currentEditor()->setProperty("Revision",rev);
}

QStringList Texmaker::svnLog(){
	QString cmd_svn=BuildManager::CMD_SVN;
	QString fn="\""+currentEditor()->fileName()+"\"";
	// get revisions of current file
	QString cmd=cmd_svn+" log "+fn;
	QString buffer;
	runCommand(cmd, &buffer);
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
	LatexParser::ContextType result=latexParser.findContext(line, cursor.columnNumber(), command, value);
	if(result==LatexParser::Environment){
		if ((command=="\\begin" || command=="\\end")&& !value.isEmpty()){
			//int l=cursor.lineNumber();
			if (currentEditor()->currentPlaceHolder()!=-1 &&
					currentEditor()->getPlaceHolder(currentEditor()->currentPlaceHolder()).cursor.isWithinSelection(cursor))
				currentEditor()->removePlaceHolder(currentEditor()->currentPlaceHolder()); //remove currentplaceholder to prevent nesting
			//move cursor to env name
			int pos = line.lastIndexOf(command, cursor.columnNumber()) + command.length() + 1;
			cursor.selectColumns(pos, pos+value.length());
			if (cursor.atLineEnd()||cursor.nextChar()!='}'||cursor.selectedText() != value)  // closing brace is missing or wrong env
				return false;
			//currentEditorView()->editor->setCursor(cursor);
			LatexDocument* doc=currentEditorView()->document;
			
			PlaceHolder ph;
			ph.cursor=cursor;
			ph.autoRemove=true;
			ph.autoRemoveIfLeft=true;
			// remove curly brakets as well
			QString searchWord="\\end{"+value+"}";
			QString inhibitor="\\begin{"+value+"}";
			bool backward=(command=="\\end");
			int step=1;
			if(backward) {
				qSwap(searchWord,inhibitor);
				step=-1;
			}
            int ln=cursor.lineNumber();
            int col=cursor.columnNumber();
            bool finished=false;
            int nested=0;
            int colSearch=0;
            int colInhibit=0;
            if(step<0)
                line=line.left(col);
            while(!finished){
                if(step>0){
                    //forward search
                    colSearch=line.indexOf(searchWord,col);
                    colInhibit=line.indexOf(inhibitor,col);
                }else{
                    //backward search
                    colSearch=line.lastIndexOf(searchWord);
                    colInhibit=line.lastIndexOf(inhibitor);
                }
                if(colSearch<0 && colInhibit<0){
                    ln+=step;
                    if(doc->lines()<=ln || ln<0)
                        break;
                    line=doc->line(ln).text();
                    col=0;
                }
                if(colSearch>=0 && colInhibit>=0){
                    if(colSearch*step<colInhibit*step){
                        if(nested==0){
                            finished=true;
                        }
                        nested--;
                        col=colSearch+1;
                        if(step<0)
                            line=line.left(colSearch);
                    }else{
                        if(step>0){
                            col=colInhibit+1;
                        }else {
                            line=line.left(colInhibit);
                        }
                        nested++;
                    }
                }else{
                    if(colSearch>=0){
                        nested--;
                        if(nested<0)
                            finished=true;
                        if(step>0){
                            col=colSearch+1;
                        }else{
                            line=line.left(colSearch);
                        }
                    }
                    if(colInhibit>=0){
                        nested++;
                        if(step>0){
                            col=colInhibit+1;
                        }else{
                            line=line.left(colInhibit);
                        }
                    }
                }
            }
            if(finished){
                line=doc->line(ln).text();
                int start=colSearch;
                int offset=searchWord.indexOf("{");
                ph.mirrors << currentEditor()->document()->cursor(ln,start+offset+1,ln,start+searchWord.length()-1);
            }
            /*int endLine=doc->findLineContaining(searchWord,startLine+step,Qt::CaseSensitive,backward);
			int inhibitLine=doc->findLineContaining(inhibitor,startLine+step,Qt::CaseSensitive,backward); // not perfect (same line end/start ...)
			while (inhibitLine>0 && endLine>0 && inhibitLine*step<endLine*step) {
				endLine=doc->findLineContaining(searchWord,endLine+step,Qt::CaseSensitive,backward); // not perfect (same line end/start ...)
				inhibitLine=doc->findLineContaining(inhibitor,inhibitLine+step,Qt::CaseSensitive,backward);
			}
			if(endLine>-1){
				line=doc->line(endLine).text();
				int start=line.indexOf(searchWord);
				int offset=searchWord.indexOf("{");
				ph.mirrors << currentEditor()->document()->cursor(endLine,start+offset+1,endLine,start+searchWord.length()-1);
            }*/
			currentEditor()->addPlaceHolder(ph);
			currentEditor()->setPlaceHolder(currentEditor()->placeHolderCount()-1);
			if(setCur)
				currentEditorView()->editor->setCursor(oldCursor);
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

void Texmaker::jumpToBracket(){
	if (!currentEditor()) return;
	REQUIRE(sender() && currentEditor()->document() && currentEditor()->document()->languageDefinition());
	QDocumentCursor orig, to;
	const QDocumentCursor se = currentEditor()->cursor().selectionEnd();
	se.getMatchingPair(orig, to, false);
	if (orig.selectionEnd() == se) currentEditor()->setCursor(to.selectionStart());
	else currentEditor()->setCursor(to.selectionEnd());
}

void Texmaker::selectBracket(){
	if (!currentEditor()) return;
	REQUIRE(sender() && currentEditor()->document());
	if (!currentEditor()->document()->languageDefinition()) return;
	QDocumentCursor orig, to;
	currentEditor()->cursor().getMatchingPair(orig, to, !sender()->property("minimal").toBool());
	if (!orig.isValid() && !to.isValid()) return;
	
	if (sender()->property("line").toBool()) {
		if (to < orig) to.setColumnNumber(0);
		else to.setColumnNumber(to.line().length());
	}
	QDocumentCursor::sort(orig, to);
	if (sender()->property("minimal").toBool()) {
		if (orig.hasSelection()) orig = orig.selectionEnd();
		if (to.hasSelection()) to = to.selectionStart();
	} else {
		if (orig.hasSelection()) orig = orig.selectionStart();
		if (to.hasSelection()) to = to.selectionEnd();
	}
	if (sender()->property("backslash").toBool()) {
		int backslash = orig.line().text().lastIndexOf('\\', orig.columnNumber());
		if (backslash >= 0) orig.setColumnNumber(backslash);
	}

	currentEditor()->setCursor(currentEditor()->document()->cursor(orig.lineNumber(), orig.columnNumber(), to.lineNumber(), to.columnNumber()));
}

void Texmaker::findMissingBracket(){
	if (!currentEditor()) return;
	REQUIRE(currentEditor()->document() && currentEditor()->document()->languageDefinition());
	QDocumentCursor c = currentEditor()->languageDefinition()->getNextMismatch(currentEditor()->cursor());
	if (c.isValid()) currentEditor()->setCursor(c);
}

void Texmaker::openExternalFile(const QString& name,const QString& defaultExt,LatexDocument *doc){
	if (!doc) {
		if (!currentEditor()) return;
		doc=qobject_cast<LatexDocument*>(currentEditor()->document());
	}
	if (!doc) return;
	QStringList curPaths;
	if(documents.masterDocument)
		curPaths << ensureTrailingDirSeparator(documents.masterDocument->getFileInfo().absolutePath());
	if(doc->getMasterDocument())
		curPaths << ensureTrailingDirSeparator(doc->getTopMasterDocument()->getFileInfo().absolutePath());
	curPaths << ensureTrailingDirSeparator(doc->getFileInfo().absolutePath());
	bool loaded = false;
	for(int i=0;i<curPaths.count();i++){
		const QString& curPath=curPaths.value(i);
		if ((loaded=load(getAbsoluteFilePath(curPath+name,defaultExt))))
			break;
		if ((loaded=load(getAbsoluteFilePath(curPath+name,""))))
			break;
		if ((loaded=load(getAbsoluteFilePath(name,defaultExt))))
			break;
	}
	
	if(!loaded) {
		Q_ASSERT(curPaths.count()>0);
		QFileInfo fi(getAbsoluteFilePath(curPaths[0]+name, defaultExt));
		if (txsConfirmWarning(tr("The file \"%1\" does not exist.\nDo you want to create it?").arg(fi.fileName()))) {
            int lineNr=-1;
            if(currentEditor()){
                lineNr=currentEditor()->cursor().lineNumber();
            }
			fileNew(fi.absoluteFilePath());
            doc->patchStructure(lineNr,1);
		}
	}
}


void Texmaker::cursorHovered(){
	if(completer->isVisible()) return;
	generateMirror(true);
}

void Texmaker::saveProfile(){
	QString currentDir=configManager.configBaseDir;
	QString fname = QFileDialog::getSaveFileName(this,tr("Save Profile"),currentDir,tr("TXS Profile","filter")+"(*.txsprofile);;"+tr("All files")+" (*)");
	QFileInfo info(fname);
	if(info.suffix().isEmpty())
		fname+=".txsprofile";
	SaveSettings(fname);
}

void Texmaker::loadProfile(){
	QString currentDir=configManager.configBaseDir;
	QString fname = QFileDialog::getOpenFileName(this,tr("Load Profile"),currentDir,tr("TXS Profile","filter")+"(*.txsprofile *.tmxprofile);;"+tr("All files")+" (*)");  //*.tmxprofile for compatibility - may be removed later
	if (fname.isNull())
		return;
	if(QFileInfo(fname).isReadable()){
		bool macro=false;
		bool userCommand=false;
		SaveSettings();
		QSettings *profile=new QSettings(fname,QSettings::IniFormat);
		QSettings *config=new QSettings(QSettings::IniFormat,QSettings::UserScope,"texstudio","texstudio");
		if(profile && config){
			QStringList keys = profile->allKeys();
			foreach(const QString& key,keys){
				//special treatment for macros/usercommands
				if(key.startsWith("texmaker/Macros")){
					QStringList ls = profile->value(key).toStringList();
					if (!ls.isEmpty()){
						configManager.completerConfig->userMacros.append(Macro(ls));
						macro=true;
					}
					continue;
				}
				if((key=="texmaker/Tools/User Order")||(key=="texmaker/Tools/Display Names")){
					// logic assumes that the user command name is exclusive
					QStringList order=config->value(key).toStringList()<<profile->value(key).toStringList();
					config->setValue(key,order);
					userCommand=true;
					continue;
				}
				config->setValue(key,profile->value(key));
			}
		}
		delete profile;
		delete config;
		ReadSettings(true);
		if(macro)
			updateUserMacros();
		if(userCommand)
			updateUserToolMenu();
	} else txsWarning(tr("Failed to read profile file %1.").arg(fname));
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
	dlg->setWindowTitle(tr("Find Word Repetitions"));
	QGridLayout *layout = new QGridLayout;
	layout->setColumnStretch(1, 1);
	layout->setColumnStretch(0, 1);
	QComboBox *cb = new QComboBox(dlg);
	cb->addItems(QStringList() << "spellingMistake" << "wordRepetition" << "wordRepetitionLongRange"<< "badWord" << "grammarMistake" << "grammarMistakeSpecial1" << "grammarMistakeSpecial2" << "grammarMistakeSpecial3" << "grammarMistakeSpecial4");
	cb->setCurrentIndex(1);
	cb->setObjectName("kind");
	cb->setEditable(true); //so people can search for other things as well
	QPushButton *btNext= new QPushButton(tr("&Find Next"), dlg);
	btNext->setObjectName("next");
	QPushButton *btPrev= new QPushButton(tr("&Find Previous"), dlg);
	btPrev->setObjectName("prev");
	QPushButton *btClose= new QPushButton(tr("&Close"), dlg);
	btClose->setObjectName("close");
	layout->addWidget(cb,0,0);
	layout->addWidget(btNext,0,1);
	layout->addWidget(btPrev,0,2);
	layout->addWidget(btClose,0,3);
	dlg->setLayout(layout);
	connect(btNext,SIGNAL(clicked()),this,SLOT(findNextWordRepetion()));
	connect(btPrev,SIGNAL(clicked()),this,SLOT(findNextWordRepetion()));
	connect(btClose,SIGNAL(clicked()),dlg,SLOT(close()));
	dlg->setModal(false);
	dlg->show();
	dlg->raise();
	
}

void Texmaker::findNextWordRepetion(){
	QPushButton *mButton = qobject_cast<QPushButton *>(sender());
	bool backward=mButton->objectName()=="prev";
	if (!currentEditorView()) return;
	typedef QFormatRange (QDocumentLine::*OverlaySearch) (int, int, int);
	OverlaySearch overlaySearch = backward?&QDocumentLine::getLastOverlayBetween:&QDocumentLine::getFirstOverlayBetween;
	QComboBox* kind = mButton->parent()->findChild<QComboBox*>("kind");
	int overlayType = currentEditorView()->document->getFormatId(kind ? kind->currentText() : "wordRepetition");
	QDocumentCursor cur = currentEditor()->cursor();
	if (cur.hasSelection()){
		if (backward) cur = cur.selectionStart();
		else cur = cur.selectionEnd();
	}
	int lineNr = cur.lineNumber();
	QDocumentLine line = cur.line();
	int fx = backward?0:(cur.endColumnNumber()+1), tx = backward?cur.startColumnNumber()-1:line.length();
	while (line.isValid()){
		if (line.hasOverlay(overlayType)){
			QFormatRange range = (line.*overlaySearch)(fx, tx, overlayType);
			if (range.length > 0){
				currentEditor()->setCursor(currentEditor()->document()->cursor(lineNr,range.offset,lineNr,range.offset+range.length));
				return;
			}
		}
		if(backward)
			lineNr--;
		else
			lineNr++;
		line = currentEditor()->document()->line(lineNr);
		fx = 0;
		tx = line.length();
	}
	txsInformation(backward ? tr("Reached beginning of text.") : tr("Reached end of text."));
}

void Texmaker::latexModelViewMode(){
	bool mode=documents.model->getSingleDocMode();
	documents.model->setSingleDocMode(!mode);
}

void Texmaker::moveDocumentToFront(){
	moveDocumentToDest(0);
}

void Texmaker::moveDocumentToEnd(){
	moveDocumentToDest(EditorTabs->count()-1);
}

void Texmaker::moveDocumentToDest(int dest){
	StructureEntry *entry = LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry || entry->type != StructureEntry::SE_DOCUMENT_ROOT) return;
	int cur = documents.documents.indexOf(entry->document);
	if (cur < 0) return;
	EditorTabs->moveTab(cur, dest);
	EditorTabMoved(cur, dest);
}

void Texmaker::importPackage(QString name){
	if(!latexStyleParser){
		QString cmd_latex=buildManager.getCommandInfo(BuildManager::CMD_LATEX).commandLine;
		QString baseDir;
		if(!QFileInfo(cmd_latex).isRelative())
			baseDir=QFileInfo(cmd_latex).absolutePath()+"/";
		latexStyleParser=new LatexStyleParser(this,configManager.configBaseDir,baseDir+"kpsewhich");
		connect(latexStyleParser,SIGNAL(scanCompleted(QString)),this,SLOT(packageScanCompleted(QString)));
		connect(latexStyleParser,SIGNAL(finished()),this,SLOT(packageParserFinished()));
		latexStyleParser->start();
		QTimer::singleShot(30000,this,SLOT(stopPackageParser()));
	}
	name.chop(4);
	name.append(".sty");
	latexStyleParser->addFile(name);
	name.chop(4);
	name.append(".cls"); // try also cls
	latexStyleParser->addFile(name);
}

void Texmaker::packageScanCompleted(QString name){
    QStringList lst=name.split('#');
    QString baseName=name;
    if(lst.size()>1){
        baseName=lst.first();
        name=lst.last();
    }
	foreach(LatexDocument *doc,documents.documents){
        if(doc->containsPackage(baseName)){
			documents.cachedPackages.remove(name+".cwl");
            doc->updateCompletionFiles(false);
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

void Texmaker::readinAllPackageNames(){
	if (!packageListReader) {
		// preliminarily use cached packages
		QSet<QString> cachedPackages = KpathSeaParser::readPackageList(QFileInfo(QDir(configManager.configBaseDir), "packageCache.dat").absoluteFilePath());
		packageListReadCompleted(cachedPackages);
		// start reading actually installed packages
		QString cmd_latex=buildManager.getCommandInfo(BuildManager::CMD_LATEX).commandLine;
		QString baseDir;
		if (!QFileInfo(cmd_latex).isRelative())
			baseDir=QFileInfo(cmd_latex).absolutePath()+"/";
		packageListReader = new KpathSeaParser(this,baseDir+"kpsewhich");
		connect(packageListReader, SIGNAL(scanCompleted(QSet<QString>)), this, SLOT(packageListReadCompleted(QSet<QString>)));
		packageListReader->start();
	}
}

void Texmaker::packageListReadCompleted(QSet<QString> packages){
	latexPackageList = packages;
	if (qobject_cast<KpathSeaParser*>(sender())) {
		KpathSeaParser::savePackageList(packages, QFileInfo(QDir(configManager.configBaseDir), "packageCache.dat").absoluteFilePath());
		packageListReader->wait();
		packageListReader=0;
	}
	foreach(LatexDocument *doc,documents.getDocuments()){
		LatexEditorView *edView=doc->getEditorView();
		if(edView)
		edView->updatePackageFormats();
	}
}

QString Texmaker::clipboardText(const QClipboard::Mode& mode) const{
	return QApplication::clipboard()->text(mode);
}
void Texmaker::setClipboardText(const QString& text, const QClipboard::Mode& mode){
	QApplication::clipboard()->setText(text, mode);
}
int Texmaker::getVersion() const{
	return TXSVERSION_NUMERIC;
}

void Texmaker::updateHighlighting(){
	
	QStringList envList;
	envList<<"math"<<"verbatim";
	bool updateNecessary=false;
    QMultiHash<QString, QString>::const_iterator it = latexParser.environmentAliases.constBegin();
    while (it != latexParser.environmentAliases.constEnd()) {
        if(envList.contains(it.value())){
            if(!detectedEnvironmentsForHighlighting.contains(it.key())){
                detectedEnvironmentsForHighlighting.insert(it.key(),it.value());
                updateNecessary=true;
            }
        }
        ++it;
    }
    foreach(LatexDocument *doc,documents.getDocuments()){
        QMultiHash<QString, QString>::const_iterator it = doc->ltxCommands.environmentAliases.constBegin();
        while (it != doc->ltxCommands.environmentAliases.constEnd()) {
            if(envList.contains(it.value())){
                if(!detectedEnvironmentsForHighlighting.contains(it.key())){
                    detectedEnvironmentsForHighlighting.insert(it.key(),it.value());
                    updateNecessary=true;
                }
            }
            ++it;
    }
    }
	if(!updateNecessary)
		return;
	
	QLanguageDefinition *oldLaTeX = 0, *newLaTeX = 0;
	QLanguageFactory::LangData m_lang=m_languages->languageData("(La)TeX");
	
	oldLaTeX = m_lang.d;
	Q_ASSERT(oldLaTeX);
	
	QFile f(findResourceFile("qxs/tex.qnfa"));
	QDomDocument doc;
	doc.setContent(&f);
	
	for (QMap<QString, QVariant>::const_iterator i = configManager.customEnvironments.constBegin(); i != configManager.customEnvironments.constEnd(); ++i){
		QString mode=configManager.enviromentModes.value(i.value().toInt(),"verbatim");
		addEnvironmentToDom(doc,i.key(),mode);
	}
	//detected math envs
	for (QMap<QString, QString>::const_iterator i = detectedEnvironmentsForHighlighting.constBegin(); i != detectedEnvironmentsForHighlighting.constEnd(); ++i){
		QString envMode=i.value()=="verbatim" ? "verbatim" :  "numbers";
        QString env=i.key();
        if(env.contains('*')){
            env.replace("*","\\*");
        }
        addEnvironmentToDom(doc,env,envMode);
	}
	QNFADefinition::load(doc,&m_lang,qobject_cast<QFormatScheme*>(m_formats));
	m_languages->addLanguage(m_lang);
	
	newLaTeX = m_lang.d;
	Q_ASSERT(oldLaTeX != newLaTeX);
    documents.enablePatch(false);
	foreach (LatexEditorView *edView, EditorTabs->editors()) {
		QEditor* ed = edView->editor;
		//if (customEnvironmentChanged) ed->highlight();
		if (ed->languageDefinition() == oldLaTeX) {
			ed->setLanguageDefinition(newLaTeX);
            ed->highlight();
		}
	}
    documents.enablePatch(true);

	updateUserMacros(false); //update macros depending on the language to newLatex
}

void Texmaker::toggleGrammar(int type){
	QAction* a = qobject_cast<QAction*>(sender());
	REQUIRE(a);
	LatexEditorView::setGrammarOverlayDisabled(type, !a->isChecked());
	//a->setChecked(!a->isChecked());
	for (int i=0;i<documents.documents.size();i++)
		if (documents.documents[i]->getEditorView())
			documents.documents[i]->getEditorView()->updateGrammarOverlays();
}

void Texmaker::fileDiff(){
	LatexDocument *doc=documents.currentDocument;
	if(!doc)
		return;
	
	//remove old markers
	removeDiffMarkers();
	
	QString currentDir=QDir::homePath();
	if (!configManager.lastDocument.isEmpty()) {
		QFileInfo fi(configManager.lastDocument);
		if (fi.exists() && fi.isReadable()) {
			currentDir=fi.absolutePath();
		}
	}
	QStringList files = QFileDialog::getOpenFileNames(this,tr("Open Files"),currentDir,tr("LaTeX Files (*.tex);;All Files (*)"),  &selectedFileFilter);
	if(files.isEmpty())
		return;
	//
	LatexDocument* doc2=diffLoadDocHidden(files.first());
	doc2->setObjectName("diffObejct");
	doc2->setParent(doc);
	diffDocs(doc,doc2);
	//delete doc2;
	
	// show changes (by calling LatexEditorView::documentContentChanged)
	LatexEditorView *edView=currentEditorView();
	edView->documentContentChanged(0,edView->document->lines());
}

void Texmaker::jumpNextDiff(){
	QEditor *m_edit=currentEditor();
	if(!m_edit)
		return;
	QDocumentCursor c=m_edit->cursor();
	if(c.hasSelection()){
		int l,col;
		c.endBoundary(l,col);
		c.moveTo(l,col);
	}
	LatexDocument *doc=documents.currentDocument;
	
	//search for next diff
	int lineNr=c.lineNumber();
	QVariant var=doc->line(lineNr).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
	if(var.isValid()){
		DiffList lineData=var.value<DiffList>();
		for(int j=0;j<lineData.size();j++){
			DiffOp op=lineData.at(j);
			if(op.start+op.length>c.columnNumber()){
				c.moveTo(lineNr,op.start);
				c.moveTo(lineNr,op.start+op.length,QDocumentCursor::KeepAnchor);
				m_edit->setCursor(c);
				return;
			}
		}
	}
	lineNr++;
	
	
	for(;lineNr<doc->lineCount();lineNr++) {
		var=doc->line(lineNr).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
		if(var.isValid()){
			break;
		}
	}
	if(var.isValid()){
		DiffList lineData=var.value<DiffList>();
		DiffOp op=lineData.first();
		c.moveTo(lineNr,op.start);
		c.moveTo(lineNr,op.start+op.length,QDocumentCursor::KeepAnchor);
		m_edit->setCursor(c);
	}
}

void Texmaker::jumpPrevDiff(){
	QEditor *m_edit=currentEditor();
	if(!m_edit)
		return;
	QDocumentCursor c=m_edit->cursor();
	if(c.hasSelection()){
		int l,col;
		c.beginBoundary(l,col);
		c.moveTo(l,col);
	}
	LatexDocument *doc=documents.currentDocument;
	
	//search for next diff
	int lineNr=c.lineNumber();
	QVariant var=doc->line(lineNr).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
	if(var.isValid()){
		DiffList lineData=var.value<DiffList>();
		for(int j=lineData.size()-1;j>=0;j--){
			DiffOp op=lineData.at(j);
			if(op.start<c.columnNumber()){
				c.moveTo(lineNr,op.start);
				c.moveTo(lineNr,op.start+op.length,QDocumentCursor::KeepAnchor);
				m_edit->setCursor(c);
				return;
			}
		}
	}
	lineNr--;
	
	
	for(;lineNr>=0;lineNr--) {
		var=doc->line(lineNr).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
		if(var.isValid()){
			break;
		}
	}
	if(var.isValid()){
		DiffList lineData=var.value<DiffList>();
		DiffOp op=lineData.last();
		c.moveTo(lineNr,op.start);
		c.moveTo(lineNr,op.start+op.length,QDocumentCursor::KeepAnchor);
		m_edit->setCursor(c);
	}
}

void Texmaker::removeDiffMarkers(bool theirs){
	LatexDocument *doc=documents.currentDocument;
	if(!doc)
		return;
	
	diffRemoveMarkers(doc,theirs);
	QList<QObject *>lst=doc->children();
	foreach (QObject* o, lst)
		delete o;

	LatexEditorView *edView=currentEditorView();
	edView->documentContentChanged(0,edView->document->lines());
	
}

void Texmaker::editChangeDiff(QPoint pt){
	LatexDocument *doc=documents.currentDocument;
	if(!doc)
		return;
	
	bool theirs=(pt.x()<0);
	int ln=pt.x();
	if(ln<0)
		ln=-ln-1;
	int col=pt.y();
	
	diffChange(doc,ln,col,theirs);
	LatexEditorView *edView=currentEditorView();
	edView->documentContentChanged(0,edView->document->lines());
}

void Texmaker::fileDiffMerge(){
	LatexDocument *doc=documents.currentDocument;
	if(!doc)
		return;
	
	diffMerge(doc);
	
	LatexEditorView *edView=currentEditorView();
	edView->documentContentChanged(0,edView->document->lines());
}

LatexDocument* Texmaker::diffLoadDocHidden(QString f){
	QString f_real=f;
#ifdef Q_OS_WIN32
	QRegExp regcheck("/([a-zA-Z]:[/\\\\].*)");
	if (regcheck.exactMatch(f)) f_real=regcheck.cap(1);
#endif
	
	if (!QFile::exists(f_real)) return 0;
	
	LatexDocument *doc=new LatexDocument(this);
	//LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig,doc);
	
	//edit->document=doc;
	//edit->document->setEditorView(edit);
	
	QFile file(f_real);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this,tr("Error"), tr("You do not have read permission to this file."));
		return 0;
	}
	file.close();
	
	//if (edit->editor->fileInfo().suffix()!="tex")
	//	m_languages->setLanguage(edit->editor, f_real);
	
	//QTime time;
	//time.start();

	//edit->editor->load(f_real,QDocument::defaultCodec());
	doc->load(f_real,QDocument::defaultCodec());

	//qDebug() << "Load time: " << time.elapsed();
	//edit->editor->document()->setLineEndingDirect(edit->editor->document()->originalLineEnding());
	
	//edit->document->setEditorView(edit); //update file name (if document didn't exist)
	
	
	return doc;
}

void Texmaker::fileDiff3(){
	LatexDocument *doc=documents.currentDocument;
	if(!doc)
		return;
	
	//remove old markers
	removeDiffMarkers();
	
	QString currentDir=QDir::homePath();
	if (!configManager.lastDocument.isEmpty()) {
		QFileInfo fi(configManager.lastDocument);
		if (fi.exists() && fi.isReadable()) {
			currentDir=fi.absolutePath();
		}
	}
	QStringList files = QFileDialog::getOpenFileNames(this,tr("Open Compare File"),currentDir,tr("LaTeX Files (*.tex);;All Files (*)"),  &selectedFileFilter);
	if(files.isEmpty())
		return;
	QStringList basefiles = QFileDialog::getOpenFileNames(this,tr("Open Base File"),currentDir,tr("LaTeX Files (*.tex);;All Files (*)"),  &selectedFileFilter);
	if(basefiles.isEmpty())
		return;
	showDiff3(files.first(),basefiles.first());
}

void Texmaker::showDiff3(const QString file1,const QString file2){
	LatexDocument *doc=documents.currentDocument;
	if(!doc)
		return;
	
	LatexDocument* doc2=diffLoadDocHidden(file1);
	doc2->setObjectName("diffObejct");
	doc2->setParent(doc);
	LatexDocument* docBase=diffLoadDocHidden(file2);
	docBase->setObjectName("baseObejct");
	docBase->setParent(doc);
	diffDocs(doc2,docBase,true);
	diffDocs(doc,doc2);
	
	// show changes (by calling LatexEditorView::documentContentChanged)
	LatexEditorView *edView=currentEditorView();
	edView->documentContentChanged(0,edView->document->lines());
}

void Texmaker::declareConflictResolved(){
	LatexDocument *doc=documents.currentDocument;
	if(!doc)
		return;
	
	QString fn=doc->getFileName();
	QString cmd=BuildManager::CMD_SVN;
	cmd+=" resolve --accept working \""+fn+("\"");
	statusLabelProcess->setText(QString(" svn resolve conflict "));
	QString buffer;
	runCommand(cmd,&buffer);
	checkin(fn,"txs: commit after resolve");
}

void Texmaker::fileInConflict(){
	QEditor *mEditor = qobject_cast<QEditor *>(sender());
	REQUIRE(mEditor);
	if (!QFileInfo(mEditor->fileName()).exists())  //create new qfileinfo to avoid caching
		return;
	int ret = QMessageBox::warning(this,
																 tr("Conflict!"),
																 tr(
																	 "%1\nhas been modified by another application.\n"
																	 "Press \"OK\" to show differences\n"
																	 "Press \"Cancel\"to do nothing.\n"
																	 ).arg(mEditor->fileName()),
																 QMessageBox::Ok
																 |
																 QMessageBox::Cancel
																 );
	if(ret==QMessageBox::Ok){
		//remove old markers
		removeDiffMarkers();
		
		if(!checkSVNConflicted(false)){
			
			LatexDocument* doc2=diffLoadDocHidden(mEditor->fileName());
			if(!doc2)
				return;
			LatexDocument* doc=qobject_cast<LatexDocument*>(mEditor->document());
			doc2->setObjectName("diffObejct");
			doc2->setParent(doc);
			diffDocs(doc,doc2);
			//delete doc2;
			
			// show changes (by calling LatexEditorView::documentContentChanged)
			LatexEditorView *edView=doc->getEditorView();
			if(edView)
				edView->documentContentChanged(0,edView->document->lines());
		}
	}
}

bool Texmaker::checkSVNConflicted(bool substituteContents){
	LatexDocument *doc=documents.currentDocument;
	if(!doc)
		return false;
	
	QString fn=doc->getFileName();
	QFileInfo qf(fn+".mine");
	if(qf.exists()){
		SVNSTATUS status=svnStatus(fn);
		if(status==InConflict){
			int ret = QMessageBox::warning(this,
																		 tr("SVN Conflict!"),
																		 tr(
																			 "%1is conflicted with repository.\n"
																			 "Press \"OK\" to show differences instead of the generated source by subversion\n"
																			 "Press \"Cancel\"to do nothing.\n"
																			 ).arg(doc->getFileName()),
																		 QMessageBox::Ok
																		 |
																		 QMessageBox::Cancel
																		 );
			if(ret==QMessageBox::Ok){
				QString path=qf.absolutePath();
				QDir dir(path);
				dir.setSorting(QDir::Name);
				qf.setFile(fn);
				QString filter=qf.fileName()+".r*";
				QFileInfoList list = dir.entryInfoList(QStringList(filter));
				QStringList lst;
				foreach(QFileInfo elem,list){
					lst<<elem.absoluteFilePath();
				}
				if(lst.count()!=2)
					return false;
				if(substituteContents){
					QTextCodec *codec=doc->codec();
					doc->load(fn+".mine",codec);
				}
				QString baseFile=lst.takeFirst();
				QString compFile=lst.takeFirst();
				showDiff3(compFile,baseFile);
				return true;
			}
		}
	}
	return false;
}


QThread* killAtCrashedThread = 0;
QThread* lastCrashedThread = 0;

void recover(){
	Texmaker::recoverFromCrash();
}
void Texmaker::recoverFromCrash(){
	bool wasLoop;
	QString name = getLastCrashInformation(wasLoop);
	if (QThread::currentThread() != QCoreApplication::instance()->thread()) {
		QThread* t = QThread::currentThread();
		lastCrashedThread = t;
		if (qobject_cast<SafeThread*>(t)) qobject_cast<SafeThread*>(t)->crashed = true;
		QTimer::singleShot(0, txsInstance, SLOT(threadCrashed()));
		while(!programStopped) {
			ThreadBreaker::sleep(1);
			if (t &&  t == killAtCrashedThread) {
				name += QString(" forced kill in %1").arg((long int)t, sizeof(long int)*2, 16,QChar('0'));
				name += QString(" (TXS-Version %1 %2 )").arg(TEXSTUDIO_SVN_VERSION).arg(COMPILED_DEBUG_OR_RELEASE);
				print_backtrace(name);
				exit(1);
			}
		};
		ThreadBreaker::forceTerminate();
		return;
	}

	static int nestedCrashes = 0;

	nestedCrashes++;

	if (nestedCrashes > 5) { qFatal("Forced kill after recovering failed after: %s\n", qPrintable(name)); exit(1); }

	fprintf(stderr, "crashed with signal %s\n", qPrintable(name));
	
	if (nestedCrashes <= 2) {
		print_backtrace(name + QString(" (TXS-Version %1 %2 )").arg(TEXSTUDIO_SVN_VERSION).arg(COMPILED_DEBUG_OR_RELEASE));
	}

	//hide editor views in case the error occured during drawing
	foreach (LatexEditorView *edView, txsInstance->EditorTabs->editors())
		edView->hide();
	
	//save recover information
	foreach (LatexEditorView *edView, txsInstance->EditorTabs->editors()) {
		QEditor* ed = edView ? edView->editor : 0;
		if (ed && ed->isContentModified() && !ed->fileName().isEmpty())
			ed->saveEmergencyBackup(ed->fileName()+".recover.bak~");
	}
	
	
	
	QMessageBox * mb = new QMessageBox(); //Don't use the standard methods like ::critical, because they load an icon, which will cause a crash again with gtk. ; mb must be on the heap, or continuing a paused loop can crash
	mb->setWindowTitle(tr("TeXstudio Emergency"));
	if (!wasLoop) {
		mb->setText(tr( "TeXstudio has CRASHED due to a %1.\nDo you want to keep it running? This may cause data corruption.").arg(name));
		mb->setDefaultButton(mb->addButton(tr("Yes, try to recover"), QMessageBox::AcceptRole));
		mb->addButton(tr("No, kill the program"), QMessageBox::RejectRole); //can't use destructiverole, it always becomes rejectrole
	} else {
		mb->setText(tr( "TeXstudio has been paused due to a possible endless loop.\nDo you want to keep the program running? This may cause data corruption."));
		mb->setDefaultButton(mb->addButton(tr("Yes, stop the loop and try to recover"), QMessageBox::AcceptRole));
		mb->addButton(tr("Yes, continue the loop"), QMessageBox::RejectRole);
		mb->addButton(tr("No, kill the program"), QMessageBox::DestructiveRole);
	}
	
	//show the dialog (non modal, because on Windows showing the dialog modal here, permanently disables all other windows)
	mb->setWindowFlags(Qt::WindowStaysOnTopHint);
	mb->setWindowModality(Qt::NonModal);
	mb->setModal(false);
	mb->show();
	QApplication::processEvents(QEventLoop::AllEvents);
	mb->setFocus(); //without it, raise doesn't work. If it is in the loop, the buttons can't be clicked on (windows)
	while (mb->isVisible()) {
		QApplication::processEvents(QEventLoop::AllEvents);
		mb->raise(); //sometimes the box is not visible behind the main window (windows)
	}

	//print edit history
	int i=0;
	foreach (LatexEditorView *edView, txsInstance->EditorTabs->editors()) {
		Q_ASSERT(edView);
		if (!edView) continue;

		QFile tf(QDir::tempPath() + QString("/texstudio_undostack%1%2.txt").arg(i++).arg(edView->editor->fileInfo().completeBaseName()));
		if (tf.open(QFile::WriteOnly)){
			tf.write(edView->editor->document()->debugUndoStack(100).toLocal8Bit());
			tf.close();
		};
	}
	
	
	//fprintf(stderr, "result: %i, accept: %i, yes: %i, reject: %i, dest: %i\n",mb->result(),QMessageBox::AcceptRole,QMessageBox::YesRole,QMessageBox::RejectRole,QMessageBox::DestructiveRole);
	if (mb->result() == QMessageBox::DestructiveRole || (!wasLoop && mb->result() == QMessageBox::RejectRole)) {
		qFatal("Killed on user request after error: %s\n", qPrintable(name));
		exit(1);
	}
	if (wasLoop && mb->result() == QMessageBox::RejectRole) {
		delete mb;
		Guardian::continueEndlessLoop();
		while (1) ;
	}
	
	//restore editor views
	foreach (LatexEditorView *edView, txsInstance->EditorTabs->editors())
		edView->show();
	
	if (!programStopped)
		QApplication::processEvents(QEventLoop::AllEvents);

	nestedCrashes = 0; //assume it was successfully recovered if it gets this far

	while (!programStopped) {
		QApplication::processEvents(QEventLoop::AllEvents);
		ThreadBreaker::msleep(1);
	}
	name = "Normal close after " + name;
	print_backtrace(name);
	exit(0);
}

void Texmaker::threadCrashed(){
	bool wasLoop;
	QString signal = getLastCrashInformation(wasLoop);
	QThread* thread = lastCrashedThread;
	
	QString threadName = "<unknown>";
	QString threadId = QString("%1").arg((long)(thread),sizeof(long int)*2,16,QChar('0'));
	if (qobject_cast<QThread*>(static_cast<QObject*>(thread)))
		threadName = QString("%1 %2").arg(threadId).arg(qobject_cast<QThread*>(thread)->objectName());
	
	fprintf(stderr, "crashed with signal %s in thread %s\n", qPrintable(signal), qPrintable(threadName));
	
	int btn = QMessageBox::warning(this, tr("TeXstudio Emergency"),
																 tr("TeXstudio has CRASHED due to a %1 in thread %2.\nThe thread has been stopped.\nDo you want to keep TeXstudio running? This may cause data corruption.").arg(signal).arg(threadId),
																 tr("Yes"), tr("No, kill the program"));
	if (btn) {
		killAtCrashedThread = thread;
		ThreadBreaker::sleep(10);
		QMessageBox::warning(this, tr("TeXstudio Emergency"), tr("I tried to die, but nothing happened."));
	}
}

void Texmaker::iamalive(){
	Guardian::calm();
}

void Texmaker::slowOperationStarted(){
	Guardian::instance()->slowOperationStarted();
}

void Texmaker::slowOperationEnded(){
	Guardian::instance()->slowOperationEnded();
	
}

void Texmaker::checkLatexInstall(){
	fileNew(tr("System Report"));
	m_languages->setLanguageFromName(currentEditor(), "Plain text");

	QString result;
	// run pdflatex
	statusLabelProcess->setText(QString("check pdflatex"));
	QString buffer;
	CommandInfo cmdInfo=buildManager.getCommandInfo(BuildManager::CMD_PDFLATEX);
	QString cmd=cmdInfo.getBaseName();
	// where is pdflatex located
#ifdef Q_OS_WIN
	runCommand("where "+cmd, &buffer);
	result="where pdflatex: "+buffer+"\n\n";
#else
	runCommand("which "+cmd, &buffer);
	result="which pdflatex: "+buffer+"\n\n";
#endif
  buffer.clear();
  cmd+=" -version";
  // run pdflatex
  runCommand(cmd, &buffer);
  result+="PDFLATEX: "+cmd+"\n";
  result+=buffer;
  result+="\n\n";
  // check env
  result+="Environment variables:\n";
  buffer.clear();
#ifdef Q_OS_WIN
	// TODO: it's not guaranteed that a process started with runCommand has the same environment
	// currently that should be the case, as long as we don't start to change the environment in
	// runCommand before execution.
	// The equivalent to printenv on windows would be set. However this is not a program, but a
	// command directly built into cmd.com, so we cannot directly use runCommand("set");
	buffer = QProcessEnvironment::systemEnvironment().toStringList().join("\n");
#else
	runCommand("printenv", &buffer);
#endif
	result+=buffer;



	result+= "\n\nCommand configuration in TeXstudio:\n";
	const CommandMapping& cmds = buildManager.getAllCommands();
	foreach (const CommandInfo& ci, cmds)
		result += QString("    %1 (%2)%3: %4\n").arg(ci.displayName).arg(ci.id).arg(ci.rerunCompiler?" (r)":"").arg(ci.commandLine);

	result+= "\nAdditional Search Paths:\n";
	result+= "    Command: "+buildManager.additionalSearchPaths+"\n";
	result+= "    Log: "+buildManager.additionalLogPaths+"\n";
	result+= "    Pdf: "+buildManager.additionalPdfPaths+"\n";


	currentEditorView()->editor->setText(result, false);
}

void Texmaker::addDocToLoad(QString filename){
    //qDebug()<<"fname:"<<filename;
    if(filename.isEmpty())
        return;
    load(filename,false,true,recheckLabels);
}

void Texmaker::moveCursorTodlh(){
    QAction *act = qobject_cast<QAction *>(sender());
    if (!act) return;
    StructureEntry *entry = qvariant_cast<StructureEntry *>(act->data());
    LatexDocument *doc=entry->document;
    QDocumentLineHandle *dlh=entry->getLineHandle();
    LatexEditorView* edView=doc->getEditorView();
    if(edView){
        int lineNr=-1;
        if((lineNr=doc->indexOf(dlh))>=0){
            gotoLine(lineNr,0,edView);
        }
    }
}

void Texmaker::openInternalDocViewer(QString package,const QString command){
#ifndef NO_POPPLER_PREVIEW
    runInternalCommand("txs:///view-pdf-internal", QFileInfo(package), "--embedded");
    QList<PDFDocument*> pdfs = PDFDocument::documentList();
    if(pdfs.count()>0){
		pdfs[0]->raise();
        PDFDocument* pdf=pdfs.first();
        pdf->goToPage(0);
        pdf->doFindDialog(command);
        if(!command.isEmpty())
            pdf->doFindAgain();
    }
#endif
}

void Texmaker::CloseEnv(){
    LatexEditorView* edView=currentEditorView();
    if(!edView)
        return;
    QEditor *m_edit=currentEditor();
    if(!m_edit)
        return;
    QDocumentCursor cursor=m_edit->cursor();
    StackEnvironment env;
    edView->getEnv(cursor.lineNumber(),env);
    LatexDocument *doc=edView->document;
    int lineCount=doc->lineCount();
    if(lineCount<1)
        return;
    StackEnvironment env_end;
    QDocumentLineHandle *dlh=edView->document->line(lineCount-1).handle();
    QVariant envVar=dlh->getCookie(QDocumentLine::STACK_ENVIRONMENT_COOKIE);
    if(envVar.isValid())
        env_end=envVar.value<StackEnvironment>();
    else
        return;

    if(env.count()>0 && env_end.count()>0){
        Environment mostRecentEnv=env.pop();
        while(!env_end.isEmpty()){
            Environment e=env_end.pop();
            if(env_end.isEmpty()) // last env is for internal use only
                break;
            if(e==mostRecentEnv){ // found, now close it
                QString txt="\\end{"+e.name+"}";
                m_edit->insertText(txt);
                break;
            }
        }
    }
}

void Texmaker::enlargeEmbeddedPDFViewer(){
#ifndef NO_POPPLER_PREVIEW
    QList<PDFDocument*> oldPDFs = PDFDocument::documentList();
    if(oldPDFs.isEmpty())
        return;
    PDFDocument* viewer=oldPDFs.first();
    if(!viewer->embeddedMode)
        return;
	centralVSplitter->hide();
    configManager.viewerEnlarged=true;
    viewer->setStateEnlarged(true);
#endif
}

void Texmaker::shrinkEmbeddedPDFViewer(bool preserveConfig){
#ifndef NO_POPPLER_PREVIEW
	centralVSplitter->show();
    if(!preserveConfig)
        configManager.viewerEnlarged=false;
    QList<PDFDocument*> oldPDFs = PDFDocument::documentList();
    if(oldPDFs.isEmpty())
        return;
    PDFDocument* viewer=oldPDFs.first();
    if(!viewer->embeddedMode)
        return;
    viewer->setStateEnlarged(false);
#endif
}
