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

#include "cleandialog.h"

//#define no_debughelper
#ifndef no_debughelper
#include "debughelper.h"
#endif

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
#include "scriptengine.h"
#include "grammarcheck.h"
#include "qmetautils.h"
#include "updatechecker.h"

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

Texmaker::Texmaker(QWidget *parent, Qt::WFlags flags)
       : QMainWindow(parent, flags), textAnalysisDlg(0), spellDlg(0), mDontScrollToItem(false), runBibliographyIfNecessaryEntered(false) {
	
	programStopped = false;
	spellLanguageActions=0;
	MapForSymbols=0;
	currentLine=-1;
	previewEquation=false;
	svndlg=0;
	userMacroDialog = 0;
	mCompleterNeedsUpdate=false;
	latexStyleParser=0;
	bibtexEntryActions = 0;
	biblatexEntryActions = 0;
	bibTypeActions = 0;
	highlightLanguageActions = 0;
	
	ReadSettings();
	
	txsInstance = this;
	static int crashHandlerType = 1; 
	configManager.registerOption("Crash Handler Type", &crashHandlerType, 1);
#ifndef no_debughelper
    registerCrashHandler(crashHandlerType);
	QTimer * t  = new QTimer(this);
	connect(t, SIGNAL(timeout()), SLOT(iamalive()));
	t->start(3000);
#endif
	              
	
	setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
	setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
	
	setWindowIcon(QIcon(":/images/logo128.png"));
	
	setIconSize(QSize(22,22));
	
	leftPanel=0;
	structureTreeView=0;
	bookmarksWidget=0;
	
	outputView=0;
	templateSelectorDialog=0;
	
	qRegisterMetaType<LatexParser>();
	latexParser.importCwlAliases();
	
	QDocument::setFormatFactory(m_formats);
	SpellerUtility::spellcheckErrorFormat = m_formats->id("spellingMistake");
	
	qRegisterMetaType<QList<LineInfo> >();
	qRegisterMetaType<QList<GrammarError> >();
	qRegisterMetaType<LatexParser>();
	qRegisterMetaType<GrammarCheckerConfig>();
	grammarCheck = new GrammarCheck();
	grammarCheck->moveToThread(&grammarCheckThread);
	GrammarCheck::staticMetaObject.invokeMethod(grammarCheck, "init", Qt::QueuedConnection, Q_ARG(LatexParser, latexParser), Q_ARG(GrammarCheckerConfig, *configManager.grammarCheckerConfig));
	connect(grammarCheck, SIGNAL(checked(const void*,const void*,int,QList<GrammarError>)), &documents, SLOT(lineGrammarChecked(const void*,const void*,int,QList<GrammarError>)));
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
	
	LatexEditorView::updateFormatSettings();
		
	// TAB WIDGET EDITEUR
	documents.indentationInStructure=configManager.indentationInStructure;
	documents.showLineNumbersInStructure=configManager.showLineNumbersInStructure;
	connect(&documents,SIGNAL(masterDocumentChanged(LatexDocument *)), SLOT(masterDocumentChanged(LatexDocument *)));
	connect(&documents,SIGNAL(aboutToDeleteDocument(LatexDocument*)), SLOT(aboutToDeleteDocument(LatexDocument*)));
	
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
	
	EditorView=new TxsTabWidget(centralFrame);
	EditorView->setFocusPolicy(Qt::ClickFocus);
	EditorView->setFocus();
	EditorView->setContextMenuPolicy(Qt::PreventContextMenu);

	connect(EditorView, SIGNAL(tabBarContextMenuRequested(QPoint)), SLOT(editorTabContextMenu(QPoint)));
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
    splitter=new QSplitter(Qt::Horizontal);
    centralLayout->addWidget(splitter);
    splitter->addWidget(EditorView);
	
	setCentralWidget(centralFrame);
	
	setContextMenuPolicy(Qt::ActionsContextMenu);
	
	symbolMostused.clear();
	setupDockWidgets();
	
	setupMenus();
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
	
	statusLabelMode->setText(QString(" %1 ").arg(tr("Normal Mode")));
	statusLabelProcess->setText(QString(" %1 ").arg(tr("Ready")));
	
	setAcceptDrops(true);
	installEventFilter(this);
	
	UpdateChecker::instance()->autoCheck();
	
	completer=new LatexCompleter(latexParser, this);
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
	filters << tr("TeX files")+" (*.tex *.bib *.sty *.cls *.mp *.dtx *.cfg *.ins)";
	filters << tr("Plaintext files")+" (*.txt)";
	filters << tr("Sweave files")+" (*.Snw *.Rnw)";
	filters << tr("PDF files")+" (*.pdf)";
	filters << tr("All files")+" (*)";
	fileFilters = filters.join(";;");
	
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
	connectWithAdditionalArguments(&buildManager, SIGNAL(endRunningCommands(QString,bool,bool)), this, "runScripts", QList<QVariant>() << Macro::ST_AFTER_COMMAND_RUN);
	
}


Texmaker::~Texmaker(){
	programStopped = true;
#ifndef no_debughelper
    Guardian::shutdown();
#endif
	delete MapForSymbols;
	if(latexStyleParser){
		latexStyleParser->stop();
		latexStyleParser->wait();
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
		
		leftPanel->addWidget(structureTreeView, "structureTreeView", tr("Structure"), ":/images/structure.png");
	} else leftPanel->setWidgetText(structureTreeView,tr("Structure"));
    if(!bookmarksWidget){
        bookmarksWidget=new QListWidget(this);
        bookmarksWidget->setAlternatingRowColors(true);
        bookmarksWidget->setStyleSheet(
                    "QListWidget::item {"
                        "padding: 4px;"
                        "border-bottom: 1px solid palette(dark); }"
                    "QListWidget::item:selected {"
                        "color: palette(highlighted-text);"
                        "background-color: palette(highlight); }");
        connect(bookmarksWidget, SIGNAL(itemPressed(QListWidgetItem*)), SLOT(clickedOnBookmark(QListWidgetItem *))); //single click
        leftPanel->addWidget(bookmarksWidget, "bookmarks", tr("Bookmarks"), ":/images/bookmarks.png");
        // read bookmarks
        QStringList bookmark;
        bookmarksWidget->clear();
        for(int i=0;i<configManager.bookmarkList.count();i++){
            bookmark=configManager.bookmarkList.at(i).toStringList();
            QString fn=bookmark.takeFirst();
            int lineNr=bookmark.takeFirst().toInt();
            QString text=bookmark.takeFirst();
            QListWidgetItem *item=new QListWidgetItem(text,bookmarksWidget);
            item->setData(Qt::UserRole,fn);
            item->setData(Qt::UserRole+1,lineNr);
            LatexDocument *doc=documents.findDocumentFromName(fn);
            if(doc && lineNr<doc->lineCount() && lineNr>=0) {
                QDocumentLineHandle *dlh=doc->line(lineNr).handle();
                item->setData(Qt::UserRole+2,qVariantFromValue(dlh));
            }else{
                item->setData(Qt::UserRole+2,0);
            }
        }
    } else leftPanel->setWidgetText(bookmarksWidget,tr("Bookmarks"));
	
	addSymbolGrid("operators", "math1.png",tr("Operator symbols"));
	addSymbolGrid("relation", "hi16-action-math1.png",tr("Relation symbols"));
	addSymbolGrid("arrows", "math2.png",tr("Arrow symbols"));
	addSymbolGrid("delimiters","math4.png",tr("Delimiters"));
	addSymbolGrid("greek", "math5.png",tr("Greek letters"));
	addSymbolGrid("cyrillic", "hi16-action-math10.png",tr("Cyrillic letters"));
	addSymbolGrid("misc-math", "math3.png",tr("Miscellaneous math symbols"));
	addSymbolGrid("misc-text", "misc-symbols.png",tr("Miscellaneous text symbols"));
	addSymbolGrid("wasysym", "misc-symbols-wasysym.png",tr("Miscellaneous text symbols (wasysym)"));
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
		outputView->setWindowTitle(tr("Messages / Log File"));
		outputView->toggleViewAction()->setText(tr("Messages / Log File"));
		outputView->setAllowedAreas(Qt::AllDockWidgetAreas);
		outputView->setFeatures(QDockWidget::DockWidgetClosable);
		outputView->setTabbedLogView(configManager.tabbedLogView);
		addDockWidget(Qt::BottomDockWidgetArea,outputView);
		connect(outputView,SIGNAL(locationActivated(int,const QString&)),this,SLOT(gotoLocation(int,const QString&)));
		connect(outputView,SIGNAL(logEntryActivated(int)),this,SLOT(gotoLogEntryEditorOnly(int)));
		connect(outputView,SIGNAL(tabChanged(int)),this,SLOT(tabChanged(int)));
		connect(outputView,SIGNAL(jumpToSearch(QDocument*,int)),this,SLOT(jumpToSearch(QDocument*,int)));
		connect(&configManager,SIGNAL(tabbedLogViewChanged(bool)),outputView,SLOT(setTabbedLogView(bool)));
		connect(&buildManager,SIGNAL(previewAvailable(const QString&, const PreviewSource&)),this,SLOT(previewAvailable	(const QString&,const PreviewSource&)));
		connect(&buildManager, SIGNAL(processNotification(QString)), SLOT(processNotification(QString)));
		
		connect(&buildManager, SIGNAL(beginRunningCommands(QString,bool,bool)), SLOT(beginRunningCommand(QString,bool,bool)));
		connect(&buildManager, SIGNAL(beginRunningSubCommand(ProcessX*,QString,QString,RunCommandFlags)), SLOT(beginRunningSubCommand(ProcessX*,QString,QString,RunCommandFlags)));
		connect(&buildManager, SIGNAL(endRunningSubCommand(ProcessX*,QString,QString,RunCommandFlags)), SLOT(endRunningSubCommand(ProcessX*,QString,QString,RunCommandFlags)));
		connect(&buildManager, SIGNAL(endRunningCommands(QString,bool,bool)), SLOT(endRunningCommand(QString,bool,bool)));
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
					QStringList list;
					foreach (const QAction* act, menu->actions())
						if (!act->isSeparator())
							list.append(act->text());
					createComboToolButton(tb.toolbar,list,-1,this,SLOT(callToolButtonAction()),"",combo);
					
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
	getManagedMenu("main/file");
	newManagedAction(menu, "new",tr("&New"), SLOT(fileNew()), Qt::CTRL+Qt::Key_N, "filenew");
	newManagedAction(menu, "newfromtemplate",tr("New from &template..."), SLOT(fileNewFromTemplate()));
	newManagedAction(menu, "open",tr("&Open..."), SLOT(fileOpen()), Qt::CTRL+Qt::Key_O, "fileopen");
	
	QMenu *submenu=newManagedMenu(menu, "openrecent",tr("Open &Recent")); //only create the menu here, actions are created by config manager
	newManagedAction(menu, "restoresession",tr("Restore previous session"), SLOT(fileRestoreSession()));
	
	menu->addSeparator();
	actSave = newManagedAction(menu,"save",tr("&Save"), SLOT(fileSave()), Qt::CTRL+Qt::Key_S, "filesave");
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
	newManagedAction(svnSubmenu, "difffiles",tr("Show difference between two files"), SLOT(fileDiff()));
	newManagedAction(svnSubmenu, "diff3files",tr("Show difference between two files in relation to base file"), SLOT(fileDiff3()));
	newManagedAction(svnSubmenu, "checksvnconflict",tr("Check SVN Conflict"), SLOT(checkSVNConflicted()));
	newManagedAction(svnSubmenu, "mergediff",tr("Try to merge differences"), SLOT(fileDiffMerge()));
	newManagedAction(svnSubmenu, "removediffmakers",tr("Remove Difference-Markers"), SLOT(removeDiffMarkers()));
	newManagedAction(svnSubmenu, "declareresolved",tr("Declare Conflict Resolved"), SLOT(declareConflictResolved()));
	newManagedAction(svnSubmenu, "nextdiff",tr("Jump to next difference"), SLOT(jumpNextDiff()),0,":/images/go-next-diff.png");
	newManagedAction(svnSubmenu, "prevdiff",tr("Jump to previous difference"), SLOT(jumpPrevDiff()),0,":/images/go-previous-diff.png");
	
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
    newManagedAction(menu,"eraseLine",tr("Erase &Line"), SLOT(editEraseLine()), (QList<QKeySequence>()<< Qt::CTRL+Qt::Key_K));
    newManagedAction(menu,"eraseEndLine",tr("Erase until E&nd of Line"), SLOT(editEraseEndLine()), (QList<QKeySequence>()<< Qt::AltModifier+Qt::Key_K));
	
	latexEditorContextMenu = menu->actions();
	
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
    newManagedAction(submenu,"bookmark",tr("unnamed bookmark"),SLOT(toggleBookmark()),Qt::CTRL+Qt::SHIFT+Qt::Key_B);
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

	QKeySequence sc(Qt::CTRL+Qt::ALT+Qt::Key_F);
#ifdef Q_WS_WIN
	// on win ctrl+alt = altGr, hungarian: altGr+F = [
	// so we should not use this as shortcut in this special case
	if (QApplication::keyboardInputLocale().language() == QLocale::Hungarian)
		sc = QKeySequence(Qt::CTRL+Qt::ALT+Qt::SHIFT+Qt::Key_F);
#endif
	newManagedAction(submenu,"definition",tr("Definition"),SLOT(editGotoDefinition()),sc);
	
	menu->addSeparator();
	newManagedAction(menu,"generateMirror",tr("Re&name Environment"), SLOT(generateMirror()));
	
	submenu = newManagedMenu(menu, "parens", tr("Parenthesis"));
	newManagedAction(submenu, "jump", tr("Jump to match"), SLOT(jumpToBracket()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_J));
	newManagedAction(submenu, "selectBracketInner", tr("Select (inner)"), SLOT(selectBracket()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_I))->setProperty("maximal", false);
	newManagedAction(submenu, "selectBracketOuter", tr("Select (outer)"), SLOT(selectBracket()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_O))->setProperty("maximal", true);
	newManagedAction(submenu, "generateInvertedBracketMirror", tr("Select (inverting)"), SLOT(generateBracketInverterMirror()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_S));
	submenu->addSeparator();
	newManagedAction(submenu, "findMissingBracket", tr("Find mismatch"), SLOT(findMissingBracket()), QKeySequence(Qt::SHIFT+Qt::CTRL+Qt::Key_P, Qt::Key_M));
	
	submenu=newManagedMenu(menu, "complete",tr("Complete"));
	newManagedAction(submenu, "normal", tr("normal"), SLOT(NormalCompletion()),Qt::CTRL+Qt::Key_Space);
	newManagedAction(submenu, "environment", tr("\\begin{ completion"), SLOT(InsertEnvironmentCompletion()),Qt::CTRL+Qt::ALT+Qt::Key_Space);
	newManagedAction(submenu, "text", tr("normal text"), SLOT(InsertTextCompletion()),Qt::SHIFT+Qt::ALT+Qt::Key_Space);
	
	menu->addSeparator();
	newManagedAction(menu,"reparse",tr("Refresh Structure"),SLOT(updateStructure()));
	newManagedAction(menu,"removePlaceHolders",tr("Remove Placeholders"),SLOT(editRemovePlaceHolders()),Qt::CTRL+Qt::SHIFT+Qt::Key_K);
	
	//tools
	
	
	menu=newManagedMenu("main/tools",tr("&Tools"));
	menu->setProperty("defaultSlot", QByteArray(SLOT(commandFromAction())));
	newManagedAction(menu, "quickbuild",tr("&Quick"), SLOT(commandFromAction()), Qt::Key_F1, ":/images/2rightarrow.png")->setData(BuildManager::CMD_QUICK);
	newManagedAction(menu, "compile",tr("&Compile"), SLOT(commandFromAction()), Qt::Key_F6,":/images/1rightarrow.png")->setData(BuildManager::CMD_COMPILE);
	newManagedAction(menu, "view",tr("&View"), SLOT(commandFromAction()), Qt::Key_F7,":/images/viewer.png")->setData(BuildManager::CMD_VIEW);
	newManagedAction(menu, "bibtex",tr("&Bibliography"), SLOT(commandFromAction()))->setData(BuildManager::CMD_BIBLIOGRAPHY);
	newManagedAction(menu, "index",tr("&Index"), SLOT(commandFromAction()))->setData(BuildManager::CMD_INDEX);

	menu->addSeparator();
	submenu=newManagedMenu(menu, "commands",tr("&Commands", "menu"));
	newManagedAction(submenu, "latexmk",tr("&Latexmk"), SLOT(commandFromAction()))->setData(BuildManager::CMD_LATEXMK);
	submenu->addSeparator();
	newManagedAction(submenu, "latex",tr("&LaTeX"), SLOT(commandFromAction()), QKeySequence(), ":/images/latex.png")->setData(BuildManager::CMD_LATEX);
	newManagedAction(submenu, "pdflatex",tr("&PDFLaTeX"), SLOT(commandFromAction()), QKeySequence(), ":/images/pdflatex.png")->setData(BuildManager::CMD_PDFLATEX);
	newManagedAction(submenu, "xelatex","&XeLaTeX", SLOT(commandFromAction()), QKeySequence(), ":/images/xelatex.png")->setData(BuildManager::CMD_XELATEX);
	newManagedAction(submenu, "lualatex","L&uaLaTeX", SLOT(commandFromAction()), QKeySequence(), ":/images/lualatex.png")->setData(BuildManager::CMD_LUALATEX);
	submenu->addSeparator();
	newManagedAction(submenu, "dvi2ps",tr("Dvi->PS"), SLOT(commandFromAction()), QKeySequence(), ":/images/dvips.png")->setData(BuildManager::CMD_DVIPS);
	newManagedAction(submenu, "ps2pdf",tr("P&S->PDF"), SLOT(commandFromAction()), QKeySequence(), ":/images/ps2pdf.png")->setData(BuildManager::CMD_PS2PDF);
	newManagedAction(submenu, "dvipdf",tr("DV&I->PDF"), SLOT(commandFromAction()), QKeySequence(), ":/images/dvipdf.png")->setData(BuildManager::CMD_DVIPDF);
	submenu->addSeparator();
	newManagedAction(submenu, "viewdvi",tr("View &Dvi"), SLOT(commandFromAction()), QKeySequence(), ":/images/viewdvi.png")->setData(BuildManager::CMD_VIEW_DVI);
    newManagedAction(submenu, "viewps",tr("Vie&w PS"), SLOT(commandFromAction()), QKeySequence(), ":/images/viewps.png")->setData(BuildManager::CMD_VIEW_PS);
    newManagedAction(submenu, "viewpdf",tr("View PD&F"), SLOT(commandFromAction()), QKeySequence(), ":/images/viewpdf.png")->setData(BuildManager::CMD_VIEW_PDF);
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
	newManagedAction(menu, "viewlog",tr("View &Log"), SLOT(commandFromAction()), QKeySequence(), ":/images/viewlog.png")->setData(BuildManager::CMD_VIEW_LOG);
	newManagedAction(menu, "clearmarkers",tr("Cl&ear Markers"), SLOT(ClearMarkers()));
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
	menu->setProperty("defaultSlot", QByteArray(SLOT(InsertFromAction())));
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
	newManagedAction(submenu, "insertTableTemplate",tr("remodel table after template","table"), SLOT(insertTableTemplate()));
	newManagedAction(submenu, "alignColumns", tr("Align Columns"), SLOT(alignTableCols()),QKeySequence(),":/images/alignCols.png");
	
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
	newManagedAction(menu, "graphic",tr("Insert &Graphic..."), SLOT(QuickGraphics()), QKeySequence(), ":images/image.png");
	

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
	menu=newManagedMenu("main/user",tr("&User"));
	submenu=newManagedMenu(menu,"tags",tr("User &Tags"));
	updateUserMacros();
	scriptengine::macros = &configManager.completerConfig->userMacro;
		
	//---view---
	menu=newManagedMenu("main/view",tr("&View"));
	newManagedAction(menu, "nextdocument",tr("Next Document"), SLOT(gotoNextDocument()), QList<QKeySequence>() << Qt::ALT+Qt::Key_PageUp << Qt::CTRL+Qt::Key_Tab);
	newManagedAction(menu, "prevdocument",tr("Previous Document"), SLOT(gotoPrevDocument()), QList<QKeySequence>() << Qt::ALT+Qt::Key_PageDown << Qt::CTRL+Qt::SHIFT+Qt::Key_Backtab);
	newManagedMenu(menu, "documents",tr("Open Documents"));
	
	menu->addSeparator();
	newManagedAction(menu, "structureview",leftPanel->toggleViewAction());
	newManagedAction(menu, "outputview",outputView->toggleViewAction());

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
	
	submenu=newManagedMenu(menu, "grammar", tr("Grammar errors"));
	static bool showGrammarType[8] = {false};
	for (int i=0;i<8;i++) configManager.registerOption(QString("Grammar/Display Error %1").arg(i), &showGrammarType[i], true);
	newManagedAction(submenu, "0", tr("Word repetition"), "toggleGrammar", 0, "", QList<QVariant>() << 0);
	newManagedAction(submenu, "1", tr("Long range word repetition"), "toggleGrammar", 0, "", QList<QVariant>() << 1);
	newManagedAction(submenu, "2", tr("Bad words"), "toggleGrammar", 0, "", QList<QVariant>() << 2);
	newManagedAction(submenu, "3", tr("Grammer mistake"), "toggleGrammar", 0, "", QList<QVariant>() << 3);
	for (int i=4;i<8;i++)
		newManagedAction(submenu, QString("%1").arg(i), tr("Grammer mistake special %1").arg(i-3), "toggleGrammar", 0, "", QList<QVariant>() << i);
	for (int i=0;i<submenu->actions().size();i++)
		if (!submenu->actions()[i]->isCheckable()){
			submenu->actions()[i]->setCheckable(true);
			configManager.linkOptionToObject(&showGrammarType[i], submenu->actions()[i], 0);
			LatexEditorView::setGrammarOverlayDisabled(i,!submenu->actions()[i]->isChecked());
		}
	
	menu->addSeparator();
	newManagedAction(menu, "alignwindows", tr("Align Windows"), SLOT(viewAlignWindows()));
	fullscreenModeAction=newManagedAction(menu, "fullscreenmode",tr("Fullscreen Mode"), SLOT(setFullScreenMode()));
	fullscreenModeAction->setCheckable(true);
	
	menu->addSeparator();
	QMenu *hlMenu = newManagedMenu(menu, "highlighting", tr("Highlighting"));
	if (!highlightLanguageActions) {
		highlightLanguageActions = new QActionGroup(this);
		highlightLanguageActions->setExclusive(true);
		connect(highlightLanguageActions, SIGNAL(triggered(QAction*)), this, SLOT(viewSetHighlighting(QAction*)));
		connect(hlMenu, SIGNAL(aboutToShow()), this, SLOT(showHighlightingMenu()));
		int id = 0;
		foreach (const QString &s, m_languages->languages()) {
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
	newManagedAction(menu, "config",tr("&Configure TeXstudio..."), SLOT(GeneralOptions()), 0,":/images/configure.png");
	
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
	newManagedAction(menu, "appinfo",tr("About TeXstudio..."), SLOT(HelpAbout()), 0,":/images/appicon.png");
	
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
	
	bookmarksWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
	newManagedAction(bookmarksWidget,"moveMarkUp",tr("move up"),SLOT(moveBookmarkUp()));
	newManagedAction(bookmarksWidget,"moveMarkDown",tr("move down"),SLOT(moveBookmarkDown()));
	newManagedAction(bookmarksWidget,"removeOneMark",tr("remove"),SLOT(removeBookmark()));
	newManagedAction(bookmarksWidget,"removeAllMark",tr("remove all"),SLOT(removeAllBookmarks()));
	
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
		qDebug() << "Icon:" << id << zw.toString();
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
				QToolButton* combo=createComboToolButton(mtb.toolbar,list,0,this,SLOT(insertXmlTagFromToolButtonAction()));
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
					QStringList list;
					foreach (const QAction* act, menu->actions())
						if (!act->isSeparator())
							list.append(act->text());
					//TODO: Is the callToolButtonAction()-slot really needed? Can't we just add the menu itself as the menu of the qtoolbutton, without creating a copy? (should be much faster)
					QToolButton* combo=createComboToolButton(mtb.toolbar,list,0,this,SLOT(callToolButtonAction()));
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
	
	statusTbLanguage = new QToolButton(status);
	statusTbLanguage->setToolTip(tr("Language"));
	statusTbLanguage->setPopupMode(QToolButton::InstantPopup);
	statusTbLanguage->setAutoRaise(true);
	statusTbLanguage->setMinimumWidth(status->fontMetrics().width("OOOOOO"));
	connect(&spellerManager, SIGNAL(dictPathChanged()), this, SLOT(UpdateAvailableLanguages()));
	connect(&spellerManager, SIGNAL(defaultSpellerChanged()), this, SLOT(UpdateAvailableLanguages()));
	UpdateAvailableLanguages();
	statusTbLanguage->setText(spellerManager.defaultSpellerName());
	status->addPermanentWidget(statusTbLanguage,0);
	
	statusLabelMode=new QLabel(status);
	statusLabelProcess=new QLabel(status);
	statusLabelEncoding=new QLabel(status);
	status->addPermanentWidget(statusLabelEncoding,0);
	status->addPermanentWidget(statusLabelProcess,0);
	status->addPermanentWidget(statusLabelMode,0);
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
		title=TEXSTUDIO;
	} else {
		title="Document : "+getCurrentFileName();
		if (currentEditorView()->editor) {
			NewDocumentStatus();
			NewDocumentLineEnding();
			currentEditorView()->editor->setFocus();
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
		ToggleAct->setText(tr("Normal Mode (current master document :")+shortName+")");
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
	}
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

void Texmaker::NewDocumentStatus() {
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
	QEditor * ed = edView->editor;
	if (ed->isContentModified()) {
		actSave->setEnabled(true);
		EditorView->setTabIcon(index,getRealIcon("modified"));
	} else {
		actSave->setEnabled(false);
		EditorView->setTabIcon(index,QIcon(":/images/empty.png"));
	}
	QString tabText = ed->fileName().isEmpty() ? tr("untitled") : ed->name();
	tabText.replace("&", "&&");
	if (EditorView->tabText(index) != tabText) {
		EditorView->setTabText(index, tabText);
		updateOpenDocumentMenu(true);
	}
    // child ?
    LatexDocument *doc=edView->document;
    LatexDocument *masterDoc=doc->getTopMasterDocument();
    QString tooltip=ed->fileName();
    if(masterDoc!=doc){
        tooltip+=tr("\nincluded document in %1").arg(masterDoc->getName());
    }
    EditorView->setTabToolTip(index, tooltip);
	if (currentEditorView()->editor->getFileCodec()) statusLabelEncoding->setText(currentEditorView()->editor->getFileCodec()->name());
	else statusLabelEncoding->setText("unknown");
}

void Texmaker::NewDocumentLineEnding(){
	if (!currentEditorView()) return;
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
}

void Texmaker::updateUndoRedoStatus() {
	if (currentEditor()) {
		actSave->setEnabled(!currentEditor()->document()->isClean());
		actUndo->setEnabled(currentEditor()->document()->canUndo());
		actRedo->setEnabled(currentEditor()->document()->canRedo());
	} else {
		actSave->setEnabled(false);
		actUndo->setEnabled(false);
		actRedo->setEnabled(false);
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
	
	connect(edit->editor, SIGNAL(undoAvailable(bool)), this, SLOT(updateUndoRedoStatus()));
	connect(edit->editor, SIGNAL(redoAvailable(bool)), this, SLOT(updateUndoRedoStatus()));
	connect(edit->editor, SIGNAL(contentModified(bool)), this, SLOT(NewDocumentStatus()));
	connect(edit->editor->document(), SIGNAL(lineEndingChanged(int)), this, SLOT(NewDocumentLineEnding()));
	connect(edit->editor, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChanged()));
	connect(edit->editor, SIGNAL(cursorHovered()), this, SLOT(cursorHovered()));
	connect(edit->editor, SIGNAL(emitWordDoubleClicked()), this, SLOT(cursorHovered()));
	connect(edit, SIGNAL(showMarkTooltipForLogMessage(int)),this,SLOT(showMarkTooltipForLogMessage(int)));
	connect(edit, SIGNAL(needCitation(const QString&)),this,SLOT(InsertBibEntry(const QString&)));
	connect(edit, SIGNAL(showPreview(QString)),this,SLOT(showPreview(QString)));
	connect(edit, SIGNAL(showPreview(QDocumentCursor)),this,SLOT(showPreview(QDocumentCursor)));
	connect(edit, SIGNAL(openFile(QString)),this,SLOT(openExternalFile(QString)));

	connect(edit->editor,SIGNAL(fileReloaded()),this,SLOT(fileReloaded()));
	connect(edit->editor,SIGNAL(fileInConflict()),this,SLOT(fileInConflict()));
	connect(edit->editor,SIGNAL(fileAutoReloading(QString)),this,SLOT(fileAutoReloading(QString)));
	
	connect(edit, SIGNAL(linesChanged(QString,const void*,QList<LineInfo>,int)), grammarCheck, SLOT(check(QString,const void*,QList<LineInfo>,int)));
	
	connect(edit, SIGNAL(spellerChanged(QString)), this, SLOT(EditorSpellerChanged(QString)));
	edit->setSpellerManager(&spellerManager);
	edit->setSpeller("<default>");
	
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
    connect(edit->document, SIGNAL(bookmarkRemoved(int)),this,SLOT(lineWithBookmarkRemoved(int)));
    connect(edit->document, SIGNAL(bookmarkLineUpdated(int)),this,SLOT(updateLineWithBookmark(int)));
	connect(edit,SIGNAL(thesaurus(int,int)),this,SLOT(editThesaurus(int,int)));
	connect(edit,SIGNAL(changeDiff(QPoint)),this,SLOT(editChangeDiff(QPoint)));
	
	EditorView->insertTab(reloadFromDoc ? documents.documents.indexOf(edit->document,0) : -1,edit, "?bug?");
	updateOpenDocumentMenu(false);
	EditorView->setCurrentWidget(edit);
	
	edit->editor->setFocus();
	UpdateCaption();
	NewDocumentStatus();
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
void Texmaker::restoreBookmarks(LatexEditorView *edView){
    LatexDocument *doc=edView->document;
    if(!doc)
        return;
    // go trough bookmarks
    for(int i=0;i<bookmarksWidget->count();i++){
        QListWidgetItem *item=bookmarksWidget->item(i);
        QString fn=item->data(Qt::UserRole).toString();
        if(doc->getFileName()!=fn)
            continue;
        int lineNr=item->data(Qt::UserRole+1).toInt();
        edView->addBookmark(lineNr,-1);
        QDocumentLineHandle *dlh=doc->line(lineNr).handle();
	if(!dlh)
	    continue;
        item->setData(Qt::UserRole+2,qVariantFromValue(dlh));
        item->text()=dlh->text();
        QString text;
        for(int i=lineNr;(i<lineNr+4)&&(i<doc->lineCount());i++){
            QString ln=doc->line(i).text().trimmed();
            if(ln.length()>40)
                ln=ln.left(40)+"...";
            text+=ln+"\n";
        }
        item->setToolTip(text);
    }
}

LatexEditorView* Texmaker::load(const QString &f , bool asProject) {
	QString f_real=f;
#ifdef Q_WS_WIN
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
        outputView->loadLogFile(f,documents.getTemporaryCompileFileName());
		DisplayLatexError();
		return 0;
	}
	
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
            restoreBookmarks(edit);
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
	edit->editor->document()->setLineEndingDirect(edit->editor->document()->originalLineEnding());
	
	edit->document->setEditorView(edit); //update file name (if document didn't exist)
	
	configureNewEditorViewEnd(edit,asProject);
	
	//check for svn conflict
	checkSVNConflicted();
	
	MarkCurrentFileAsRecent();
	
	documents.updateMasterSlaveRelations(doc);
	
	edit->updateLtxCommands();
	updateStructure(true);
	ShowStructure();
	restoreBookmarks(edit);
	
	if (asProject) documents.setMasterDocument(edit->document);
	
	if (outputView->logPresent()) DisplayLatexError(); //show marks
	if (!bibTeXmodified)
		documents.bibTeXFilesModified=false; //loading a file can change the list of included bib files, but we won't consider that as a modification of them, because then they don't have to be recompiled
	LatexDocument* master = edit->document->getTopMasterDocument();
	if (master) foreach (const FileNamePair& fnp, edit->document->mentionedBibTeXFiles().values()) {
		Q_ASSERT(!fnp.absolute.isEmpty());
		master->lastCompiledBibTeXFiles.insert(fnp.absolute);
	}
	
	
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
		edit->editor->setFocus();
	}
	//raise();
	//#ifdef Q_WS_WIN
	//        if (IsIconic (this->winId())) ShowWindow(this->winId(), SW_RESTORE);
	//#endif
#endif
	
	for (int i=0;i<doc->localMacros.size();i++)
		if (doc->localMacros[i].triggers & Macro::ST_LOAD_THIS_FILE)
			insertUserTag(doc->localMacros[i].tag, Macro::ST_LOAD_THIS_FILE);
			
	
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
#if QT_VERSION >= 0x040600
	connect(act, SIGNAL(triggered()), SLOT(relayToEditorSlot()),Qt::UniqueConnection);
#else
	disconnect(act, SIGNAL(triggered()), this, SLOT(relayToEditorSlot()));
	connect(act, SIGNAL(triggered()), SLOT(relayToEditorSlot()));
#endif
	act->setProperty("primarySlot", QString(SLOT(relayToEditorSlot())));
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

void Texmaker::autoRunScripts(){
	runScripts(Macro::ST_TXS_START); 
}

void Texmaker::runScripts(int trigger){
	for(int i=0;i<configManager.completerConfig->userMacro.count();i++)
		if (configManager.completerConfig->userMacro[i].triggers & trigger)
			insertUserTag(configManager.completerConfig->userMacro[i].tag, trigger);
}

void Texmaker::fileNew(QString fileName) {
	LatexDocument *doc=new LatexDocument();
	LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig,doc);
	if (configManager.newFileEncoding)
		edit->editor->setFileCodec(configManager.newFileEncoding);
	else
		edit->editor->setFileCodec(QTextCodec::codecForName("utf-8"));
	doc->clearUndo(); // inital file codec setting should not be undoable
	edit->editor->setFileName(fileName);

	configureNewEditorView(edit);
	
	edit->document=doc;
	edit->document->setEditorView(edit);
	documents.addDocument(edit->document);

	configureNewEditorViewEnd(edit);
	edit->updateLtxCommands();
	
	emit infoNewFile();
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
		in.setCodec(QTextCodec::codecForMib(MIB_UTF8));
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
		edit->editor->ensureCursorVisibleSurrounding();
		
		emit infoNewFromTemplate();
	}
}

void Texmaker::insertTableTemplate() {
	QEditor *m_edit=currentEditor();
	if(!m_edit)
		return;
	QDocumentCursor c=m_edit->cursor();
	if(!LatexTables::inTableEnv(c))
		return;
	// select Template
	if(!templateSelectorDialog) {
		templateSelectorDialog=new templateselector(this,tr("Templates"));
		QAction *act=new QAction(tr("Edit"),this);
		connect(act,SIGNAL(triggered()),this,SLOT(templateEdit()));
		templateSelectorDialog->ui.listWidget->addAction(act);
		act=new QAction(tr("Remove"),this);
		connect(act,SIGNAL(triggered()),this,SLOT(templateRemove()));
		templateSelectorDialog->ui.listWidget->addAction(act);
	}
	QStringList templates=findResourceFiles("templates/","tabletemplate_*.js");
	templates.replaceInStrings(QRegExp("(^|^.*/)(tabletemplate_)?"),"");
	templates.replaceInStrings(QRegExp(".js$"),"");
	templateSelectorDialog->ui.listWidget->clear();
	templateSelectorDialog->ui.listWidget->insertItems(0,templates);
	
	if(templateSelectorDialog->exec()){
        QListWidgetItem *currentItem = templateSelectorDialog->ui.listWidget->currentItem();
        if (currentItem == 0) return;

        QString f_real="templates/tabletemplate_"+currentItem->text()+".js";
        f_real=findResourceFile(f_real);
		QFile file(f_real);
		if (!file.open(QIODevice::ReadOnly)) {
			QMessageBox::warning(this,tr("Error"), tr("You do not have read permission to this file."));
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
		tableText.remove("\n");
		tableText.remove("\\hline");
		if(tableText.startsWith("\\begin")){
			LatexParser::resolveCommandOptions(tableText,0,values,&starts);
			env=values.takeFirst();
			env.remove(0,1);
			env.remove(env.length()-1,1);
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
			line=line.simplified();
			if(line.isEmpty())
				continue;
			QStringList elems=line.split(QRegExp("&"));
			QList<QString>::iterator i;
			for(i=elems.begin();i!=elems.end();i++){
				QString elem=*i;
				*i=elem.simplified();
			}
			
			// handle \& correctly
			for(int i=elems.size()-1;i>=0;i--){
				if(elems.at(i).endsWith("\\")){
					QString add=elems.at(i)+elems.at(i+1);
					elems.replace(i,add);
					elems.removeAt(i+1);
				}
			}
			tableContent<<elems;
		}
		LatexTables::generateTableFromTemplate(currentEditorView(),f_real,tableDef,tableContent,env);
    }
}

void Texmaker::alignTableCols() {
    if (!currentEditor()) return;
    QDocumentCursor cur(currentEditor()->cursor());
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
		emit infoFileSaved(currentEditor()->fileName());
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
		if (currentEditor()->fileInfo().isFile()) {
			currentDir = currentEditor()->fileInfo().absolutePath();
		} else if (!configManager.lastDocument.isEmpty()) {
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
			if (!txsConfirmWarning(tr("You are trying to save the file under the name %1, but a file with this name is already open.\n TeXstudio does not support multiple instances of the same file.\nAre you sure you want to continue?").arg(fn)))
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
		
		EditorView->setTabText(EditorView->currentIndex(),currentEditor()->name().replace("&","&&"));
		EditorView->setTabToolTip(EditorView->currentIndex(), currentEditor()->fileName());
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
			
			emit infoFileSaved(edView->editor->fileName());
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
	updateBookmarks(currentEditorView());
	QFileInfo fi = currentEditorView()->document->getFileInfo();

repeatAfterFileSavingFailed:
	if (currentEditorView()->editor->isContentModified()) {
		switch (QMessageBox::warning(this, TEXSTUDIO,
		                             tr("The document contains unsaved work. "
		                                "Do you want to save it before closing?"),
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

	//close associated embedded pdf viewer
	foreach(PDFDocument *viewer,PDFDocument::documentList())
		if (viewer->autoClose && viewer->getMasterFile()==fi)
			viewer->close();
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
			                             tr("The document contains unsaved work. "
			                                "Do you want to save it before closing?"),
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
	SaveSettings();
	bool accept = closeAllFilesAsking();
	if (accept){
		if (userMacroDialog) delete userMacroDialog;
		spellerManager.unloadAll();  //this saves the ignore list
	}
	programStopped = true;
#ifndef no_debughelper
    Guardian::shutdown();
#endif
	return accept;
}
void Texmaker::closeEvent(QCloseEvent *e) {
	if (canCloseNow())  e->accept();
	else e->ignore();
}

void Texmaker::updateUserMacros(bool updateMenu){
	if (updateMenu) configManager.updateUserMacroMenu();
	QStringList tempLanguages = m_languages->languages();
	for (int i=0;i<configManager.completerConfig->userMacro.size();i++) {
		if (configManager.completerConfig->userMacro[i].triggerLanguage.isEmpty()) continue;
		configManager.completerConfig->userMacro[i].triggerLanguages.clear();
		QRegExp tempRE(configManager.completerConfig->userMacro[i].triggerLanguage,Qt::CaseInsensitive);
		for (int j=0;j<tempLanguages.size();j++)
			if (tempRE.exactMatch(tempLanguages[j]))
				configManager.completerConfig->userMacro[i].triggerLanguages << m_languages->languageData(tempLanguages[j]).d;
	}
}

void Texmaker::fileOpenRecent() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (action) load(action->data().toString());
}
void Texmaker::fileOpenAllRecent() {
	foreach (const QString& s, configManager.recentFilesList)
		load(s);
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
	currentEditor()->insertText(newText);
}

void Texmaker::editEraseLine() {
	if (!currentEditorView()) return;
	QDocumentCursor c = currentEditorView()->editor->cursor();
	c.eraseLine();
}
void Texmaker::editEraseEndLine() {
    if (!currentEditorView()) return;
    QDocumentCursor c = currentEditorView()->editor->cursor();
    c.movePosition(1,QDocumentCursor::EndOfLine,QDocumentCursor::KeepAnchor);
    currentEditorView()->editor->setCursor(c);
    currentEditorView()->editor->cut();
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
	switch (latexParser.findContext(c.line().text(), c.columnNumber(), command, value)) {
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
		txsWarning(tr("No document open"));
		return;
	}
	if (!spellDlg) spellDlg=new SpellerDialog(this, spellerManager.getSpeller(currentEditorView()->getSpeller()));
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
	configManager.registerOption("Files/Default File Filter", &selectedFileFilter);
	configManager.registerOption("User/Templates",&userTemplatesList);
	configManager.registerOption("PDFSplitter",&pdfSplitterRel,0.5);
	
	configManager.buildManager=&buildManager;
	scriptengine::buildManager=&buildManager;
	scriptengine::app=this;	
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
	config->beginGroup("Editor Key Mapping");
	QStringList sl = config->childKeys();
	if (!sl.empty()) {
		foreach (const QString& key, sl) {
			int k = key.toInt();
			if (k==0) continue;
			configManager.editorKeys.insert(k, config->value(key).toInt());
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
	
	configManager.editorConfig->settingsChanged();
	
	
}

void Texmaker::SaveSettings(const QString& configName) {
	bool asProfile=!configName.isEmpty();
	configManager.centralVisible=centralToolBar->isVisible();
	// update completion usage
	LatexCompleterConfig *conf=configManager.completerConfig;
	//pdf viewer embedded open ?
	if(!PDFDocument::documentList().isEmpty()){
	    PDFDocument* doc=PDFDocument::documentList().first();
	    if(doc->embeddedMode){
		QList<int> sz=splitter->sizes(); // set widths to 50%, eventually restore user setting
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
        // save bookmarks
        QStringList bookmark;
        QList<QVariant> bookmarkList;
        for(int i=0;i<bookmarksWidget->count();i++){
            bookmark.clear();
            QListWidgetItem *item=bookmarksWidget->item(i);
            QString fn=item->data(Qt::UserRole).toString();
            int lineNr=item->data(Qt::UserRole+1).toInt();
            QDocumentLineHandle *dlh=qvariant_cast<QDocumentLineHandle*>(item->data(Qt::UserRole+2));
            LatexDocument *doc=documents.findDocumentFromName(fn);
            if(doc && doc->indexOf(dlh)>=0) {
                lineNr=dlh->line();
            }
            bookmark<<fn;
            bookmark<<QString::number(lineNr);
            bookmark<<item->text();
            bookmarkList<<bookmark;
        }
        config->setValue("Files/Bookmarks",bookmarkList);
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
	LatexDocument* doc = currentEditorView()->document;
	if(initial){
		int len=doc->lineCount();
		doc->patchStructure(0,len);
	
		doc->updateMagicCommentScripts();
		configManager.completerConfig->userMacro << doc->localMacros;
		updateUserMacros();
	}
	else {
		currentEditorView()->document->updateStructure();
	}
	
	updateCompleter();
	cursorPositionChanged();
	
	//structureTreeView->reset();
}

void Texmaker::clickedOnBookmark(QListWidgetItem *item){
    if (QApplication::mouseButtons()==Qt::RightButton) return; // avoid jumping to line if contextmenu is called
    QString fn=item->data(Qt::UserRole).toString();
    int lineNr=item->data(Qt::UserRole+1).toInt();
    QDocumentLineHandle *dlh=qvariant_cast<QDocumentLineHandle*>(item->data(Qt::UserRole+2));
    LatexDocument *doc=documents.findDocumentFromName(fn);
    if(!doc){
        LatexEditorView* edView=load(fn);
		if (!edView) return;
        edView->editor->setFocus();
        edView->editor->setCursorPosition(lineNr,1);
        dlh=edView->editor->document()->line(lineNr).handle();
        item->setData(Qt::UserRole+2,qVariantFromValue(dlh));
    }else{
        LatexEditorView* edView=doc->getEditorView();
        EditorView->setCurrentWidget(edView);
        edView->editor->setFocus();
        if(doc->indexOf(dlh)>=0){
            edView->editor->setCursorPosition(dlh->line(),1);
        }else{
            edView->editor->setCursorPosition(lineNr,1);
            dlh=doc->line(lineNr).handle();
            item->setData(Qt::UserRole+2,qVariantFromValue(dlh));
        }
    }
}

void Texmaker::moveBookmarkUp(){
    QListWidgetItem *item=bookmarksWidget->currentItem();
    if(!item) return;
    int row=bookmarksWidget->row(item);
    if(row<=0) return;
    bookmarksWidget->takeItem(row);
    bookmarksWidget->insertItem(row-1,item);
    bookmarksWidget->setCurrentRow(row-1);
}
void Texmaker::moveBookmarkDown(){
    QListWidgetItem *item=bookmarksWidget->currentItem();
    if(!item) return;
    int row=bookmarksWidget->row(item);
    if(row<0) return;
    if(row==bookmarksWidget->count()-1) return;
    bookmarksWidget->takeItem(row);
    bookmarksWidget->insertItem(row+1,item);
    bookmarksWidget->setCurrentRow(row+1);
}
void Texmaker::removeBookmark(){
    int row=bookmarksWidget->currentRow();
    if(row<0) return;
    QListWidgetItem *item=bookmarksWidget->takeItem(row);
    QString fn=item->data(Qt::UserRole).toString();
    int lineNr=item->data(Qt::UserRole+1).toInt();
    LatexDocument *doc=documents.findDocumentFromName(fn);
    if(!doc) return;
    LatexEditorView* edView=doc->getEditorView();
    edView->removeBookmark(lineNr,-1);
}
void Texmaker::removeAllBookmarks(){
    while(bookmarksWidget->count()>0){
          QListWidgetItem *item=bookmarksWidget->takeItem(0);
          QString fn=item->data(Qt::UserRole).toString();
          int lineNr=item->data(Qt::UserRole+1).toInt();
          LatexDocument *doc=documents.findDocumentFromName(fn);
          if(!doc) return;
          LatexEditorView* edView=doc->getEditorView();
          edView->removeBookmark(lineNr,-1);
    }
}
void Texmaker::lineWithBookmarkRemoved(int lineNr){
     LatexDocument *doc=qobject_cast<LatexDocument*> (sender());
     QString text=doc->getFileInfo().fileName();
     QDocumentLineHandle *dlh=doc->line(lineNr).handle();
     QList<QListWidgetItem*> lst=bookmarksWidget->findItems(text,Qt::MatchStartsWith);
     foreach(QListWidgetItem *item,lst){
         QDocumentLineHandle *dlh_item=qvariant_cast<QDocumentLineHandle*>(item->data(Qt::UserRole+2));
         if(dlh_item==dlh){
             int row=bookmarksWidget->row(item);
             bookmarksWidget->takeItem(row);
             return;
         }
     }
}

void Texmaker::updateLineWithBookmark(int lineNr){
     LatexDocument *doc=qobject_cast<LatexDocument*> (sender());
     if(!doc)
         return;
     QString text=doc->getFileInfo().fileName();
     QDocumentLineHandle *dlh=doc->line(lineNr).handle();
     QList<QListWidgetItem*> lst=bookmarksWidget->findItems(text,Qt::MatchStartsWith);
     foreach(QListWidgetItem *item,lst){
         QDocumentLineHandle *dlh_item=qvariant_cast<QDocumentLineHandle*>(item->data(Qt::UserRole+2));
         if(dlh_item==dlh){
             QString text=doc->getFileInfo().fileName();
             text+="\n"+dlh->text().trimmed();
             item->setText(text);
             lineNr = lineNr>1 ? lineNr-2 : 0;
             text.clear();
             LatexDocument *doc=currentEditorView()->document;
             for(int i=lineNr;(i<lineNr+4)&&(i<doc->lineCount());i++){
                 QString ln=doc->line(i).text().trimmed();
                 if(ln.length()>40)
                     ln=ln.left(40)+"...";
                 text+=ln+"\n";
             }
             item->setToolTip(text);
             return;
         }
     }
     // no bookmark found, add one
     text=doc->getFileInfo().fileName();
     text+="\n"+dlh->text().trimmed();
     QListWidgetItem *item=new QListWidgetItem(text,bookmarksWidget);
     item->setData(Qt::UserRole,documents.currentDocument->getFileName());
     item->setData(Qt::UserRole+1,lineNr);
     item->setData(Qt::UserRole+2,qVariantFromValue(dlh));
     lineNr = lineNr>1 ? lineNr-2 : 0;
     text.clear();
     for(int i=lineNr;(i<lineNr+4)&&(i<doc->lineCount());i++){
         QString ln=doc->line(i).text().trimmed();
         if(ln.length()>40)
             ln=ln.left(40)+"...";
         text+=ln+"\n";
     }
     item->setToolTip(text);
}

void Texmaker::updateBookmarks(LatexEditorView *edView){
    if(!edView)
        return;
    LatexDocument *doc=edView->document;
    QString text=doc->getFileInfo().fileName();
    QList<QListWidgetItem*> lst=bookmarksWidget->findItems(text,Qt::MatchStartsWith);
    foreach(QListWidgetItem *item,lst){
        QDocumentLineHandle *dlh=qvariant_cast<QDocumentLineHandle*>(item->data(Qt::UserRole+2));
        int lineNr=doc->indexOf(dlh);
        item->setData(Qt::UserRole+1,lineNr);
        item->setData(Qt::UserRole+2,0);
    }
}

void Texmaker::toggleBookmark(){
    if (!currentEditorView()) return;
    QDocumentCursor c = currentEditorView()->editor->cursor();
    QDocumentLineHandle *dlh=c.line().handle();
    bool bookmarkSet=currentEditorView()->toggleBookmark(-1);
    if(bookmarkSet){
        QString text=documents.currentDocument->getFileInfo().fileName();
        text+="\n"+dlh->text().trimmed();
        QListWidgetItem *item=new QListWidgetItem(text,bookmarksWidget);
        item->setData(Qt::UserRole,documents.currentDocument->getFileName());
        item->setData(Qt::UserRole+1,c.lineNumber());
        item->setData(Qt::UserRole+2,qVariantFromValue(dlh));
        int lineNr=c.lineNumber();
        lineNr = lineNr>1 ? lineNr-2 : 0;
        text.clear();
        LatexDocument *doc=currentEditorView()->document;
        for(int i=lineNr;(i<lineNr+4)&&(i<doc->lineCount());i++){
            QString ln=doc->line(i).text().trimmed();
            if(ln.length()>40)
                ln=ln.left(40)+"...";
            text+=ln+"\n";
        }
        item->setToolTip(text);
    }else{
        QString text=documents.currentDocument->getFileInfo().fileName();
        QList<QListWidgetItem*> lst=bookmarksWidget->findItems(text,Qt::MatchStartsWith);
        foreach(QListWidgetItem *item,lst){
            //QString fn=item->data(Qt::UserRole).toString();
            //int lineNr=item->data(Qt::UserRole+1).toInt();
            QDocumentLineHandle *dlh_item=qvariant_cast<QDocumentLineHandle*>(item->data(Qt::UserRole+2));
            if(dlh_item==dlh){
                int row=bookmarksWidget->row(item);
                bookmarksWidget->takeItem(row);
                return;
            }
        }
    }
}

void Texmaker::clickedOnStructureEntry(const QModelIndex & index){
	const StructureEntry* entry = LatexDocumentsModel::indexToStructureEntry(index);
	if (!entry) return;
	if (!entry->document) return;
	
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
	case StructureEntry::SE_MAGICCOMMENT:
	case StructureEntry::SE_TODO:
	case StructureEntry::SE_LABEL:{
		int lineNr=-1;
		mDontScrollToItem = entry->type!=StructureEntry::SE_SECTION;
		LatexEditorView* edView=entry->document->getEditorView();
		if (!entry->document->getEditorView()){
			lineNr=entry->getRealLineNumber();
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
	
	QString command,value;
	LatexParser::ContextType ctx=latexParser.findContext(word, c.columnNumber(), command, value);
	switch(ctx){
	case LatexParser::Command:
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST);
		break;
	case LatexParser::Environment:
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST);
		break;
    case LatexParser::Reference:
        currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_REF);
        break;
    case LatexParser::Citation:
        currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_CITE);
        break;
	case LatexParser::Option:
        if(latexParser.possibleCommands["%graphics"].contains(command)){
			QString fn=documents.getCompileFileName();
			QFileInfo fi(fn);
			completer->setWorkPath(fi.absolutePath());
			currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_GRAPHIC);
			break;
		} else {}; //fall through
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
	const QString& userTag=configManager.completerConfig->userMacro.value(id,Macro()).tag;
	insertUserTag(userTag);
}

void Texmaker::insertUserTag(const QString& macro, int triggerId){
	//dont'check that, if (!currentEditorView()) return; insertMacro is 0 save
	currentEditorView()->insertMacro(macro, QRegExp(), triggerId);
}

void Texmaker::EditUserMenu() {
	if (!userMacroDialog)  {
		userMacroDialog = new UserMenuDialog(0,tr("Edit User &Tags"),m_languages);
		foreach (const Macro& m, configManager.completerConfig->userMacro) {
			if(m.name=="TMX:Replace Quote Open" || m.name=="TMX:Replace Quote Close" || m.document)
				continue;
			userMacroDialog->names << m.name;
			userMacroDialog->tags << m.tag;
			userMacroDialog->abbrevs << m.abbrev;
			userMacroDialog->triggers << m.trigger;
		}
		userMacroDialog->init();
		connect(userMacroDialog, SIGNAL(accepted()), SLOT(userMacroDialogAccepted()));
		connect(userMacroDialog, SIGNAL(runScript(QString)), SLOT(insertUserTag(QString)));
	}
	userMacroDialog->show();
	userMacroDialog->setFocus();
}

void Texmaker::userMacroDialogAccepted(){
	configManager.completerConfig->userMacro.clear();
	Q_ASSERT(userMacroDialog->names.size() == userMacroDialog->tags.size());
	Q_ASSERT(userMacroDialog->names.size() == userMacroDialog->abbrevs.size());
	Q_ASSERT(userMacroDialog->names.size() == userMacroDialog->triggers.size());
	for (int i=0;i<userMacroDialog->names.size();i++)
		configManager.completerConfig->userMacro.append(Macro(userMacroDialog->names[i], userMacroDialog->tags[i], userMacroDialog->abbrevs[i], userMacroDialog->triggers[i]));
	for (int i=0;i<documents.documents.size();i++)
		configManager.completerConfig->userMacro << documents.documents[i]->localMacros;
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
		if (documents.singleMode()) docs << edView->document;
		else docs << documents.documents;
		foreach(const LatexDocument* doc,docs)
			labels << doc->labelItems();
	} else return;
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

void Texmaker::EditorSpellerChanged(const QString &name) {
	foreach (QAction *act, statusTbLanguage->actions()) {
		if (act->data().toString() == name) {
			act->setChecked(true);
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
	
	currentEditorView()->setSpeller(action->data().toString());
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
	
	QString pdfFile = BuildManager::parseExtendedCommandLine("?am.pdf", master).first();
	int ln = currentEditorView()?currentEditorView()->editor->cursor().lineNumber():0;
	foreach (PDFDocument* viewer, oldPDFs) {
		viewer->loadFile(pdfFile, master);
		int pg = viewer->syncFromSource(getCurrentFileName(), ln , true);
		viewer->fillRenderCache(pg);
		
		if (preserveDuplicates) break;
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
	int t = QMessageBox::question(0, TEXSTUDIO, 
	                              tr("The document %1 want to override the command %2 with %3.\nDo you trust this document?").arg(master?master->getFileName():"").arg(cmdId).arg(program), 
				  tr("Yes, always run the overridden command"),
				      tr("Yes, allow all documents to use the overridden command"),
	                              tr("No, run the default command"), 0, 2);
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
	else if (cmd == BuildManager::CMD_VIEW_LOG)
		RealViewLog();
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
	if (program == "pdflatex") {
		if (cmdId == "quick") *result = BuildManager::chainCommands(BuildManager::CMD_PDFLATEX, BuildManager::CMD_VIEW_PDF);
		else if (cmdId == "compile") *result = BuildManager::CMD_PDFLATEX;
		else if (cmdId == "view") *result = BuildManager::CMD_VIEW_PDF;
	} else if (program == "latex"){
		if (cmdId == "quick") *result = BuildManager::chainCommands(BuildManager::CMD_LATEX, BuildManager::CMD_VIEW_DVI);
		else if (cmdId == "compile") *result = BuildManager::CMD_LATEX;
		else if (cmdId == "view") *result = BuildManager::CMD_VIEW_DVI;
	} if (cmdId == "quick" && checkProgramPermission(program, cmdId, master)) *result = program;
}

void Texmaker::beginRunningCommand(const QString& commandMain, bool latex, bool pdf){
	if (pdf) {
		#ifndef NO_POPPLER_PREVIEW
		PDFDocument::isCompiling = true;
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
	if (latex) outputView->resetMessagesAndLog();//log to old (whenever latex is called)		
	else outputView->resetMessages();
	statusLabelProcess->setText(QString(" %1 ").arg(buildManager.getCommandInfo(commandMain).displayName));
}

void Texmaker::beginRunningSubCommand(ProcessX* p, const QString& commandMain, const QString& subCommand, const RunCommandFlags& flags){
	if (commandMain != subCommand)
		statusLabelProcess->setText(QString(" %1: %2 ").arg(buildManager.getCommandInfo(commandMain).displayName).arg(buildManager.getCommandInfo(subCommand).displayName));
	if (flags & RCF_COMPILES_TEX) 
		ClearMarkers();
	//outputView->resetMessages();
	
	connect(p, SIGNAL(standardErrorRead(QString)), outputView, SLOT(insertMessageLine(QString)));
	if (p->showStdout()) {
		p->setShowStdout((configManager.showStdoutOption == 2) || ((RCF_SHOW_STDOUT & flags) && configManager.showStdoutOption == 1));
		connect(p, SIGNAL(standardOutputRead(QString)), outputView, SLOT(insertMessageLine(QString)));
	}
}


void Texmaker::endRunningSubCommand(ProcessX* p, const QString& commandMain, const QString& subCommand, const RunCommandFlags& flags){
	if (p->exitCode() && (flags & RCF_COMPILES_TEX) && !LogExists()) {
		if (!QFileInfo(QFileInfo(documents.getTemporaryCompileFileName()).absolutePath()).isWritable()) 
			txsWarning(tr("You cannot compile the document in a non writable directory."));
		else
			txsWarning(tr("Could not start %1.").arg( buildManager.getCommandInfo(commandMain).displayName + ":" + buildManager.getCommandInfo(subCommand).displayName + ":\n" + p->getCommandLine()));
	}	
}

void Texmaker::endRunningCommand(const QString& commandMain, bool latex, bool pdf){
	Q_UNUSED(commandMain)
	Q_UNUSED(pdf)
#ifndef NO_POPPLER_PREVIEW
	if (pdf) 
		PDFDocument::isCompiling = false;
#endif
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
	CleanDialog *cleanDlg = new CleanDialog(this);

	if (cleanDlg->checkClean(documents)) {
		cleanDlg->exec();
	} else {
		txsInformation("No open project or tex file to clean.");
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
		return;
	}
	QString logname=getAbsoluteFilePath(QFileInfo(finame).completeBaseName(),".log");
	QString line;
	QFileInfo fic(logname);
	if (fic.exists() && fic.isReadable()) {
		//OutputLogTextEdit->insertLine("LOG FILE :");
		outputView->loadLogFile(logname,documents.getTemporaryCompileFileName());
		//display errors in editor
		DisplayLatexError();
		if (outputView->getLogModel()->found(LT_ERROR))
			if (!gotoNearLogEntry(LT_ERROR,false,tr("No LaTeX errors detected !"))) //jump to next error
				gotoNearLogEntry(LT_ERROR,true,tr("No LaTeX errors detected !")); //prev error
		
	} else if (!fic.exists()) txsWarning(tr("Log File not found !"));
	else txsWarning(tr("Log File is not readable!"));	
}

void Texmaker::ViewLogOrReRun(LatexCompileResult* result){
	ViewLog();
	REQUIRE(result);
	if (NoLatexErrors()) {
		*result = LCR_NORMAL;
		if (outputView->getLogModel()->existsReRunWarning()) 
			*result = LCR_RERUN;
		else if (configManager.runLaTeXBibTeXLaTeX) {
			//run bibtex if citation is unknown to bibtex but contained in an included bib file
			QStringList missingCitations = outputView->getLogModel()->getMissingCitations();
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
	} else *result = LCR_ERROR;
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
			txsInformation(notFoundMessage);
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
	int oldReplaceQuotes = configManager.replaceQuotes;
	autosaveTimer.stop();
	m_formats->modified = false;
	bool realtimeChecking=configManager.editorConfig->realtimeChecking;
	bool inlineSpellChecking=configManager.editorConfig->inlineSpellChecking;
	bool inlineCitationChecking=configManager.editorConfig->inlineCitationChecking;
	bool inlineReferenceChecking=configManager.editorConfig->inlineReferenceChecking;
	bool inlineSyntaxChecking=configManager.editorConfig->inlineSyntaxChecking;
	QStringList loadFiles=configManager.completerConfig->getLoadedFiles();
	
	
	if (configManager.possibleMenuSlots.isEmpty()) {
		for (int i=0;i<staticMetaObject.methodCount();i++) configManager.possibleMenuSlots.append(staticMetaObject.method(i).signature());
		for (int i=0;i<QEditor::staticMetaObject.methodCount();i++) configManager.possibleMenuSlots.append("editor:"+QString(QEditor::staticMetaObject.method(i).signature()));
		for (int i=0;i<LatexEditorView::staticMetaObject.methodCount();i++) configManager.possibleMenuSlots.append("editorView:"+QString(LatexEditorView::staticMetaObject.method(i).signature()));
		configManager.possibleMenuSlots = configManager.possibleMenuSlots.filter(QRegExp("^[^*]+$"));
	}
	
	if (configManager.execConfigDialog()) {
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
				QDocument::setFont(QDocument::font(), true);
			UpdateCaption();
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
					addEnvironmentToDom(doc,i.key(),envMode);
				}
			}
			QNFADefinition::load(doc,&m_lang,dynamic_cast<QFormatScheme*>(m_formats));
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
		updateUserToolMenu();
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
		gotoLine(line, col);
		QTimer::singleShot(1000,currentEditor(),SLOT(ensureCursorVisible()));
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

#ifndef no_debughelper
    if (realCmdLine) Guardian::summon();
#endif
}

void Texmaker::executeTests(const QStringList &args){
	QFileInfo myself(QCoreApplication::applicationFilePath());
    if (args.contains("--disable-tests")) return;
    #ifndef QT_NO_DEBUG
	bool allTests = args.contains("--execute-all-tests")
		//execute all tests once a week or if command paramter is set
		|| (configManager.debugLastFullTestRun.daysTo(myself.lastModified())>6);
    if (args.contains("--execute-tests") || myself.lastModified()!=configManager.debugLastFileModification || allTests) {
		fileNew();
		if (!currentEditorView() || !currentEditorView()->editor)
			QMessageBox::critical(0,"wtf?","test failed",QMessageBox::Ok);
		if (allTests) configManager.debugLastFullTestRun=myself.lastModified();
		QString result=TestManager::execute(allTests?TestManager::TL_ALL:TestManager::TL_FAST, currentEditorView(),currentEditorView()->codeeditor,currentEditorView()->editor, &buildManager);
		m_languages->setLanguageFromName(currentEditorView()->editor, "TXS Test Results");
		currentEditorView()->editor->setText(result, false);
		configManager.debugLastFileModification=QFileInfo(QCoreApplication::applicationFilePath()).lastModified();
	}
    #endif
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
			CodeSnippet cs(insert);
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
		configManager.newManagedAction(menu, id, ed->fileName().isEmpty() ? tr("untitled") : ed->name().replace("&","&&"), SLOT(gotoOpenDocument()));
		return;
	}
	QStringList sl;
	for (int i=0; i<EditorView->count(); i++){
		ed = qobject_cast<LatexEditorView*>(EditorView->widget(i))->editor;
		REQUIRE(ed);
		sl << (ed->fileName().isEmpty() ? tr("untitled") : ed->name().replace("&", "&&"));
	}
	configManager.updateListMenu("main/view/documents", sl, "doc", false, SLOT(gotoOpenDocument()), 0, false, 0);
}

void Texmaker::viewCloseSomething(){
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
		outputView->hide();
		return;
	}
	foreach (PDFDocument* doc, PDFDocument::documentList())
		if (doc->embeddedMode) {
			doc->close();
			return;
		}
	QTime ct = QTime::currentTime();
	if (ct.second() % 5 != 0) return;
	for (int i=2;i<63;i++) if (ct.minute() != i && ct.minute() % i  == 0) return;
	txsInformation("<html><head></head><body><img src=':/images/egg.jpg'></body></html>");
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

void Texmaker::viewAlignWindows() {
	QWidgetList windows = QApplication::topLevelWidgets();

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
    PDFDocument* from = qobject_cast<PDFDocument*>(sender());
    if(from){
	if(from->embeddedMode){
	    QList<int> sz=splitter->sizes(); // set widths to 50%, eventually restore user setting
	    int sum=0;
	    int last=0;
	    foreach(int i,sz){
		sum+=i;
		last=i;
	    }
	    pdfSplitterRel=1.0*last/sum;
	}
    }
}

QObject* Texmaker::newPdfPreviewer(bool embedded){
#ifndef NO_POPPLER_PREVIEW
	PDFDocument* pdfviewerWindow=new PDFDocument(configManager.pdfDocumentConfig,embedded);
	if(embedded){
		splitter->addWidget(pdfviewerWindow);
		QList<int> sz=splitter->sizes(); // set widths to 50%, eventually restore user setting
		int sum=0;
		foreach(int i,sz){
			sum+=i;
		}
		sz.clear();
        if(pdfSplitterRel<0.1) //sanity check
            pdfSplitterRel=0.5;
		sz << sum-qRound(pdfSplitterRel*sum);
		sz << qRound(pdfSplitterRel*sum);
		splitter->setSizes(sz);
	}
	connect(pdfviewerWindow, SIGNAL(triggeredAbout()), SLOT(HelpAbout()));
	connect(pdfviewerWindow, SIGNAL(triggeredManual()), SLOT(UserManualHelp()));
	connect(pdfviewerWindow, SIGNAL(documentClosed()), SLOT(pdfClosed()));
	connect(pdfviewerWindow, SIGNAL(triggeredQuit()), SLOT(fileExit()));
	connect(pdfviewerWindow, SIGNAL(triggeredConfigure()), SLOT(GeneralOptions()));
	connect(pdfviewerWindow, SIGNAL(syncSource(const QString&, int, bool, QString)), SLOT(syncFromViewer(const QString &, int, bool, QString)));
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
		ToggleAct->setText(tr("Define Current Document as 'Master Document'"));
		outputView->resetMessagesAndLog();
		statusLabelMode->setText(QString(" %1 ").arg(tr("Normal Mode")));
	} else {
		QString shortName = documents.masterDocument->getFileInfo().fileName();
		ToggleAct->setText(tr("Normal Mode (current master document :")+shortName+")");
		statusLabelMode->setText(QString(" %1 ").arg(tr("Master Document")+ ": "+shortName));
		configManager.addRecentFile(documents.masterDocument->getFileName(),true);
		int pos=EditorView->currentIndex();
		EditorView->moveTab(pos,0);
	}
	updateMasterDocumentCaption();
}

void Texmaker::aboutToDeleteDocument(LatexDocument * doc){
	emit infoFileClosed();
	for (int i=configManager.completerConfig->userMacro.size()-1;i>=0;i--)
		if (configManager.completerConfig->userMacro[i].document == doc)
			configManager.completerConfig->userMacro.removeAt(i);
}

//*********************************
void Texmaker::dragEnterEvent(QDragEnterEvent *event) {
	if (event->mimeData()->hasFormat("text/uri-list")) event->acceptProposedAction();
}

void Texmaker::dropEvent(QDropEvent *event) {
	QList<QUrl> uris=event->mimeData()->urls();
	
	QStringList imageFormats = InsertGraphics::imageFormats();
	
	bool alreadyMovedCursor = false;
	for (int i=0; i<uris.length(); i++) {
		QFileInfo fi = QFileInfo(uris.at(i).toLocalFile());
		if (imageFormats.contains(fi.suffix())) {
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
	
	QList<LatexDocument*> docs;
	if(edView && edView->document){
		// determine from which docs data needs to be collected
		docs=edView->document->getListOfDocs();
		// collect user commands and references
		foreach(const LatexDocument* doc,docs){
			words.unite(doc->userCommandList());
			words.unite(doc->additionalCommandsList());
		}
	}
	
	//add cite/ref commands from the cwls to latexParser.citeCommands
	static QRegExp citeCommandCheck(QRegExp("^\\\\([Cc]ite.*|.*\\{(%<)?(keylist|bibid)(%>)?\\}.*)")); 
	static QRegExp refCommandCheck(QRegExp("^\\\\.*\\{(%<)?labelid(%>)?\\}.*")); 
	foreach (const QString& cmd, words) 
		if (citeCommandCheck.exactMatch(cmd)) { //todo: get rid of duplication
			int lastBracket = cmd.lastIndexOf('{');
            latexParser.possibleCommands["%cite"].insert(lastBracket > 0 ? cmd.left(lastBracket) : cmd);
		} else if (refCommandCheck.exactMatch(cmd)){
			int lastBracket = cmd.lastIndexOf('{');
            latexParser.possibleCommands["%ref"].insert(lastBracket > 0 ? cmd.left(lastBracket) : cmd);
		}
	foreach (const QString& cmd, configManager.completerConfig->words) 
		if (citeCommandCheck.exactMatch(cmd)) {
			int lastBracket = cmd.lastIndexOf('{');
            latexParser.possibleCommands["%cite"].insert(lastBracket > 0 ? cmd.left(lastBracket) : cmd);
		} else if (refCommandCheck.exactMatch(cmd)){
			int lastBracket = cmd.lastIndexOf('{');
            latexParser.possibleCommands["%ref"].insert(lastBracket > 0 ? cmd.left(lastBracket) : cmd);
		}

	// collect user commands and references
	foreach(const LatexDocument* doc,docs){
        foreach(const QString& refCommand, latexParser.possibleCommands["%ref"]){
			QString temp=refCommand+"{%1}";
			foreach (const QString& l, doc->labelItems())
				words.insert(temp.arg(l));
		}
	}
    if (configManager.parseBibTeX){
        QStringList bibIds;
        for (int i=0; i<documents.mentionedBibTeXFiles.count();i++){
            if (!documents.bibTeXFiles.contains(documents.mentionedBibTeXFiles[i])){
                qDebug("BibTeX-File %s not loaded",documents.mentionedBibTeXFiles[i].toLatin1().constData());
                continue; //wtf?s
            }
            BibTeXFileInfo& bibTex=documents.bibTeXFiles[documents.mentionedBibTeXFiles[i]];

            //automatic use of cite commands
            foreach(const QString& citeCommand, latexParser.possibleCommands["%cite"]){
                QString temp=citeCommand+"{%1}";
                for (int i=0; i<bibTex.ids.count();i++)
                    words.insert(temp.arg(bibTex.ids[i]));
            }
            // add citation to completer for direct citation completion
            bibIds<<bibTex.ids;
        }
        //handle bibitem definitions
        bibIds<<documents.bibItems.toList();
        //automatic use of cite commands
        foreach(const QString& citeCommand, latexParser.possibleCommands["%cite"]){
            QString temp=citeCommand+"{%1}";
            foreach (const QString &value, documents.bibItems)
                words.insert(temp.arg(value));
        }
        completer->setAdditionalWords(bibIds.toSet(),CT_CITATIONS);
    }
	
	completionBaseCommandsUpdated=false;
	
	completer->setAdditionalWords(words,CT_COMMANDS);
	if(edView) edView->viewActivated();
	
	if (!LatexCompleter::hasHelpfile()) {
		QFile f(findResourceFile("latexhelp.html"));
		if (!f.open(QIODevice::ReadOnly| QIODevice::Text))  LatexCompleter::parseHelpfile("<missing>");
		else LatexCompleter::parseHelpfile(QTextStream(&f).readAll());
	}
	
	
	GrammarCheck::staticMetaObject.invokeMethod(grammarCheck, "init", Qt::QueuedConnection, Q_ARG(LatexParser, latexParser), Q_ARG(GrammarCheckerConfig, *configManager.grammarCheckerConfig));
		
	updateHighlighting();
	
	mCompleterNeedsUpdate=false;
}

void Texmaker::tabChanged(int i) {
	if (i>0 && i<3 && !outputView->logPresent()) RealViewLog(true);
}

void Texmaker::jumpToSearch(QDocument* doc, int lineNumber){
	REQUIRE(qobject_cast<LatexDocument*>(doc));
	if(currentEditor() && currentEditor()->document()==doc && currentEditor()->cursor().lineNumber()==lineNumber)
	{
		QDocumentCursor c=currentEditor()->cursor();
		int col=c.columnNumber();
		gotoLine(lineNumber);
		col=outputView->getNextSearchResultColumn(c.line().text() ,col+1);
		currentEditor()->setCursorPosition(lineNumber,col);
		currentEditor()->ensureCursorVisibleSurrounding();
	} else {
		gotoLocation(lineNumber, doc->getFileName().size()?doc->getFileName():qobject_cast<LatexDocument*>(doc)->getTemporaryFileName());
		int col=outputView->getNextSearchResultColumn(currentEditor()->document()->line(lineNumber).text() ,0);
		currentEditor()->setCursorPosition(lineNumber,col);
		currentEditor()->ensureCursorVisibleSurrounding();
		outputView->showSearchResults();
	}
}

void Texmaker::gotoLine(int line, int col) {
	if (currentEditorView() && line>=0)	{
		currentEditorView()->editor->setCursorPosition(line,col);
		currentEditorView()->editor->ensureCursorVisibleSurrounding();
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

void Texmaker::syncFromViewer(const QString &fileName, int line, bool activate, const QString& guessedWord){
	if (!FileAlreadyOpen(fileName, true))
		if (!load(fileName)) return;
	gotoLine(line);
	Q_ASSERT(currentEditor());
	
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
	if (column > -1) {
		currentEditor()->setCursorPosition(currentEditor()->cursor().lineNumber(),column+guessedWord.length()/2);
		currentEditor()->ensureCursorVisibleSurrounding();
	}
	
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
		menu.addSeparator();
		menu.addAction(tr("Move document to &front"), this, SLOT(moveDocumentToFront()));
		menu.addAction(tr("Move document to &end"), this, SLOT(moveDocumentToEnd()));
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
		currentEditorView()->setFocus();
	} else {
		name.remove(0,name.indexOf("\\"));
		name.chop(name.length()-name.indexOf("{"));
		currentEditor()->insertText(name+"{"+entry->title+"}");
		currentEditorView()->setFocus();	}
}

void Texmaker::previewLatex(){
	if (!currentEditorView()) return;
	// get selection
	QDocumentCursor c = currentEditorView()->editor->cursor();
	QDocumentCursor previewc;
	if (c.hasSelection()) {
		previewc = c; //X o riginalText = c.selectedText();
	} else {
		QDocumentCursor orig, to;
		c.getMatchingPair(orig, to, true);
		if (!orig.hasSelection() || !to.hasSelection()) return;
		QDocumentCursor::sort(orig, to);
		previewc = QDocumentCursor(orig.selectionStart(), to.selectionEnd());
	}
	if (!previewc.hasSelection()) return;
	
	showPreview(previewc,true);
	
}
void Texmaker::previewAvailable(const QString& imageFile, const PreviewSource& source){
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
	              (source.fromLine < 0)) {
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
	if (configManager.previewMode == ConfigManager::PM_INLINE && source.fromLine >= 0){
		QDocument* doc = currentEditor()->document();
		doc->setForceLineWrapCalculation(true);
		int toLine = qBound(0, source.toLine, doc->lines() - 1);
		for (int l = source.fromLine; l <= toLine; l++ ) 
			if (doc->line(l).getCookie(42).isValid()) {
				doc->line(l).removeCookie(42);
				doc->line(l).setFlag(QDocumentLine::LayoutDirty);
				doc->adjustWidth(l);
			}	
		doc->line(toLine).setCookie(42, QVariant::fromValue<QPixmap>(QPixmap(imageFile)));
		doc->line(toLine).setFlag(QDocumentLine::LayoutDirty);
		doc->adjustWidth(toLine);
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
			if (currentEditorView()->autoPreviewCursor[j].selectionStart().lineNumber() <= i &&
			    currentEditorView()->autoPreviewCursor[j].selectionEnd().lineNumber() >= i)
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
	buildManager.preview(header.join("\n"), PreviewSource(text, -1, -1), documents.getCompileFileName(), edView->editor->document()->codec());
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
	PreviewSource ps(originalText, previewc.selectionStart().lineNumber(), previewc.selectionEnd().lineNumber());
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

void Texmaker::editorTabContextMenu(const QPoint &point) {
	if (point.isNull()) return;

	QMenu *documentsMenu = getManagedMenu("main/view/documents");
	documentsMenu->exec(EditorView->mapToGlobal(point));
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
    runCommand(cmd);
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
	runCommand(cmd, 0);
	return true;
}

void Texmaker::svnLock(QString fn){
	QString cmd=BuildManager::CMD_SVN;
	cmd+=" lock \""+fn+("\"");
	statusLabelProcess->setText(QString(" svn lock "));
	runCommand(cmd, 0);
}


void Texmaker::svncreateRep(QString fn){
	QString cmd=BuildManager::CMD_SVN;
	QString admin=BuildManager::CMD_SVNADMIN;
	QString path=QFileInfo(fn).absolutePath();
	admin+=" create "+path+"/repo";
	statusLabelProcess->setText(QString(" svn create repo "));
	runCommand(admin);
	QString scmd=cmd+" mkdir file:///"+path+"/repo/trunk -m\"txs auto generate\"";
	runCommand(scmd);
	scmd=cmd+" mkdir file:///"+path+"/repo/branches -m\"txs auto generate\"";
	runCommand(scmd);
	scmd=cmd+" mkdir file:///"+path+"/repo/tags -m\"txs auto generate\"";
	runCommand(scmd);
	statusLabelProcess->setText(QString(" svn checkout repo"));
	cmd+=" co file:///"+path+"/repo/trunk "+path;
	runCommand(cmd);
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
	foreach(const QString& elem,lines){
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
				ph.mirrors << currentEditor()->document()->cursor(endLine,start+offset+1,endLine,start+searchWord.length()-1);
			}
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

void Texmaker::findMissingBracket(){
	if (!currentEditor()) return;
	REQUIRE(currentEditor()->document() && currentEditor()->document()->languageDefinition());
	QDocumentCursor c = currentEditor()->languageDefinition()->getNextMismatch(currentEditor()->cursor());
	if (c.isValid()) currentEditor()->setCursor(c);
}

void Texmaker::openExternalFile(const QString& name,const QString& defaultExt,LatexDocument *doc){
	if (!doc) {
		if (!currentEditor()) return;
		doc=dynamic_cast<LatexDocument*>(currentEditor()->document());
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
	
	if(!loaded)
		txsWarning(tr("Sorry, I couldn't find the file \"%1\"").arg(name));
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
	if(QFileInfo(fname).isReadable()){
		SaveSettings();
		QSettings *profile=new QSettings(fname,QSettings::IniFormat);
		QSettings *config=new QSettings(QSettings::IniFormat,QSettings::UserScope,"texstudio","texstudio");
		if(profile && config){
			QStringList keys = profile->allKeys();
			foreach(const QString& key,keys){
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
    dlg->setWindowTitle(tr("Find word repetitions"));
	QGridLayout *layout = new QGridLayout;
	layout->setColumnStretch(1, 1);
	layout->setColumnStretch(0, 1);
    QPushButton *btNext= new QPushButton(tr("&Find next"), dlg);
    btNext->setObjectName("next");
    QPushButton *btPrev= new QPushButton(tr("&Find previous"), dlg);
    btPrev->setObjectName("prev");
    QPushButton *btClose= new QPushButton(tr("&Close"), dlg);
    btClose->setObjectName("close");
    layout->addWidget(btNext,0,0);
    layout->addWidget(btPrev,0,1);
    layout->addWidget(btClose,0,2);
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
	int overlayType = QDocument::formatFactory()->id("wordRepetition");
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
	moveDocumentToDest(EditorView->count()-1);
}

void Texmaker::moveDocumentToDest(int dest){
	StructureEntry *entry = LatexDocumentsModel::indexToStructureEntry(structureTreeView->currentIndex());
	if (!entry || entry->type != StructureEntry::SE_DOCUMENT_ROOT) return;
	int cur = documents.documents.indexOf(entry->document); 
	if (cur < 0) return;
	EditorView->moveTab(cur, dest);
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
	foreach(LatexDocument *doc,documents.documents){
		if(doc->containsPackage(name)){
			QStringList added(name);
            documents.cachedPackages.remove(name+".cwl");
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
		addEnvironmentToDom(doc,i.key(),envMode);
	}
	QNFADefinition::load(doc,&m_lang,dynamic_cast<QFormatScheme*>(m_formats));
	m_languages->addLanguage(m_lang);
	
	newLaTeX = m_lang.d;
	Q_ASSERT(oldLaTeX != newLaTeX);
	for (int i=0; i<EditorView->count();i++) {
		LatexEditorView* edView=qobject_cast<LatexEditorView*>(EditorView->widget(i));
		if (edView) {
			QEditor* ed = edView->editor;
			//if (customEnvironmentChanged) ed->highlight();
			if (ed->languageDefinition() == oldLaTeX) {
				ed->setLanguageDefinition(newLaTeX);
				ed->highlight();
			}
		}
	}
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
	QVariant var=doc->line(lineNr).getCookie(2);
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
		var=doc->line(lineNr).getCookie(2);
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
	QVariant var=doc->line(lineNr).getCookie(2);
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
		var=doc->line(lineNr).getCookie(2);
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
	qDeleteAll(lst);
	
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
#ifdef Q_WS_WIN
	QRegExp regcheck("/([a-zA-Z]:[/\\\\].*)");
	if (regcheck.exactMatch(f)) f_real=regcheck.cap(1);
#endif
	
	if (!QFile::exists(f_real)) return 0;
	
	LatexDocument *doc=new LatexDocument(this);
	LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig,doc);
	
	edit->document=doc;
	edit->document->setEditorView(edit);
	
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
	edit->editor->document()->setLineEndingDirect(edit->editor->document()->originalLineEnding());
	
	edit->document->setEditorView(edit); //update file name (if document didn't exist)
	
	
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
	runCommand(cmd);
	checkin(fn,"txs: commit after resolve");
}

void Texmaker::fileInConflict(){
	QEditor *mEditor = qobject_cast<QEditor *>(sender());
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
#ifndef no_debughelper
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
				name += " forced kill in %1";
				name.arg((long int)t, sizeof(long int)*2, 16,QChar('0'));
				print_backtrace(name);
				exit(1);
			}
		};
		ThreadBreaker::forceTerminate();
		return;
	}
		
	fprintf(stderr, "crashed with signal %s\n", qPrintable(name));
	QMessageBox * mb = new QMessageBox(); //Don't use the standard methods like ::critical, because they load an icon, which will cause a crash again with gtk. ; mb must be on the heap, or continuing a paused loop can crash
	mb->setWindowTitle(tr("TeXstudio Emergency"));
	if (!wasLoop) {
		mb->setText(tr( "TeXstudio has CRASHED due to a %1.\nDo you want to keep it running? This may cause data corruption.").arg(name));
		mb->setDefaultButton(mb->addButton(tr("Yes, try to recover."), QMessageBox::AcceptRole));
		mb->addButton(tr("No, kill the programm"), QMessageBox::RejectRole); //can't use destructiverole, it always becomes rejectrole
	} else {
		mb->setText(tr( "TeXstudio has been paused due to a possible endless loop.\nDo you want to keep the program running? This may cause data corruption."));
		mb->setDefaultButton(mb->addButton(tr("Yes, stop the loop and try to recover."), QMessageBox::AcceptRole));
		mb->addButton(tr("Yes, continue the loop."), QMessageBox::RejectRole);
		mb->addButton(tr("No, kill the programm"), QMessageBox::DestructiveRole);
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
	//fprintf(stderr, "result: %i, accept: %i, yes: %i, reject: %i, dest: %i\n",mb->result(),QMessageBox::AcceptRole,QMessageBox::YesRole,QMessageBox::RejectRole,QMessageBox::DestructiveRole);
	if (mb->result() == QMessageBox::DestructiveRole || (!wasLoop && mb->result() == QMessageBox::RejectRole)) {
		print_backtrace(name);
		exit(1);
	}
	if (wasLoop && mb->result() == QMessageBox::RejectRole) {
		delete mb;
		Guardian::continueEndlessLoop();
		while (1) ;
	}
	while (!programStopped) {
		QApplication::processEvents(QEventLoop::AllEvents);
	}
	name = "Normal close after " + name;
	print_backtrace(name);
    exit(0);
#endif
}

void Texmaker::threadCrashed(){
#ifndef no_debughelper
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
#endif
}

void Texmaker::iamalive(){
#ifndef no_debughelper
    Guardian::calm();
#endif
}
