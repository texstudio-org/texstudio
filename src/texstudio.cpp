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

#include "texstudio.h"
#include "latexeditorview.h"

#include "smallUsefulFunctions.h"

#include "cleandialog.h"

#include "debughelper.h"
#include "debuglogger.h"

#include "dblclickmenubar.h"
#include "filechooser.h"
#include "filedialog.h"
#include "findindirs.h"
#include "tabdialog.h"
#include "arraydialog.h"
#include "bibtexdialog.h"
#include "tabbingdialog.h"
#include "letterdialog.h"
#include "quickdocumentdialog.h"
#include "quickbeamerdialog.h"
#include "mathassistant.h"
#include "maketemplatedialog.h"
#include "PDFDocument.h"
#include "templateselector.h"
#include "templatemanager.h"
#include "usermenudialog.h"
#include "aboutdialog.h"
#include "encodingdialog.h"
#include "encoding.h"
#include "randomtextgenerator.h"
#include "webpublishdialog.h"
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
#include "searchquery.h"
#include "fileselector.h"
#include "utilsUI.h"
#include "utilsSystem.h"
#include "minisplitter.h"
#include "latexpackage.h"
#include "latexparser/argumentlist.h"
#include "latexparser/latextokens.h"
#include "latexparser/latexparser.h"
#include "latexparser/latexparsing.h"
#include "latexstructure.h"
#include "symbollistmodel.h"
#include "symbolwidget.h"
#include "execprogram.h"

#include <QScreen>

#ifndef QT_NO_DEBUG
#include "tests/testmanager.h"
#endif

#include "qdocument.h"
#include "qdocumentcursor.h"
#include "qdocumentline.h"
#include "qdocumentline_p.h"

#include "qnfadefinition.h"

#include "PDFDocument_config.h"
#include <set>
#include <QStyleHints>
#ifdef Q_OS_WIN
#include <windows.h>
#endif

/*! \file texstudio.cpp
 * contains the GUI definition as well as some helper functions
 */

/*!
    \defgroup txs Mainwindow
	\ingroup txs
	@{
*/

/*! \class Texstudio
 * This class sets up the GUI and handles the GUI interaction (menus and toolbar).
 * It uses QEditor with LatexDocument as actual text editor and PDFDocument for viewing pdf.
 *
 * \see QEditor
 * \see LatexDocument
 * \see PDFDocument
 */


const QString APPICON(":appicon");

bool programStopped = false;
Texstudio *txsInstance = nullptr;
QCache<QString, QIcon> iconCache;

// workaround needed on OSX due to https://bugreports.qt.io/browse/QTBUG-49576
void hideSplash()
{
#ifdef Q_OS_MAC
	if (txsInstance)
		txsInstance->hideSplash();
#endif
}
/*!
 * \brief constructor
 *
 * set-up GUI
 *
 * \param parent
 * \param flags
 * \param splash
 */
Texstudio::Texstudio(QWidget *parent, Qt::WindowFlags flags, QSplashScreen *splash)
        : QMainWindow(parent, flags), textAnalysisDlg(nullptr), spellDlg(nullptr), mDontScrollToItem(false), runBibliographyIfNecessaryEntered(false)
{

	splashscreen = splash;
	programStopped = false;
	spellLanguageActions = nullptr;
	currentLine = -1;
	svndlg = nullptr;
	userMacroDialog = nullptr;
	mCompleterNeedsUpdate = false;
	latexStyleParser = nullptr;
	packageListReader = nullptr;
	bibtexEntryActions = nullptr;
	biblatexEntryActions = nullptr;
	bibTypeActions = nullptr;
	highlightLanguageActions = nullptr;
	runningPDFCommands = runningPDFAsyncCommands = 0;
	previewEditorPending = nullptr;
	previewIsAutoCompiling = false;
	completerPreview = false;
	recheckLabels = true;
	cursorHistory = nullptr;
	recentSessionList = nullptr;
	editors = nullptr;
	m_languages = nullptr; //initial state to avoid crash on OSX
    currentSection=nullptr;

	connect(&buildManager, SIGNAL(hideSplash()), this, SLOT(hideSplash()));

	readSettings();

#ifdef Q_OS_WIN
    // work-around for ´+t bug
    QCoreApplication::instance()->installEventFilter(this);
#endif

	latexReference = new LatexReference();
	latexReference->setFile(findResourceFile("latex2e.html"));

	qRegisterMetaType<QSet<QString> >();
    qRegisterMetaType<std::set<QString> >();

	txsInstance = this;
	static int crashHandlerType = 1;
	configManager.registerOption("Crash Handler Type", &crashHandlerType, 1);

	initCrashHandler(crashHandlerType);

	QTimer *t  = new QTimer(this);
	connect(t, SIGNAL(timeout()), SLOT(iamalive()));
	t->start(9500);

	setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
	setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

	QFile styleSheetFile(configManager.configBaseDir + "stylesheet.qss");
	if (styleSheetFile.exists()) {
        if(styleSheetFile.open(QFile::ReadOnly)){
            setStyleSheet(styleSheetFile.readAll());
            styleSheetFile.close();
        }
	}

    // dpi aware icon scaling
    // screen dpi is read and the icon are scaled up in reference to 96 dpi
    // this should be helpful on X11 (Xresouces) and possibly windows
    double dpi=QGuiApplication::primaryScreen()->logicalDotsPerInch();
    double scale=dpi/96;

	setWindowIcon(QIcon(":/images/logo128.png"));

    int iconSize = qRound(qMax(16, configManager.guiToolbarIconSize)*scale);
	setIconSize(QSize(iconSize, iconSize));

	leftPanel = nullptr;
	sidePanel = nullptr;
    //structureTreeView = nullptr;
    structureTreeWidget = nullptr;
    topTOCTreeWidget = nullptr;
	outputView = nullptr;

	qRegisterMetaType<LatexParser>();
	latexParser.importCwlAliases(findResourceFile("completion/cwlAliases.dat"));

	m_formatsOldDefault = QDocument::defaultFormatScheme();
	QDocument::setDefaultFormatScheme(m_formats);
	SpellerUtility::spellcheckErrorFormat = m_formats->id("spellingMistake");

	qRegisterMetaType<QList<LineInfo> >();
	qRegisterMetaType<QList<GrammarError> >();
	qRegisterMetaType<LatexParser>();
	qRegisterMetaType<GrammarCheckerConfig>();
    qRegisterMetaType<QDocumentLineHandle*>();

	grammarCheck = new GrammarCheck();
	grammarCheck->moveToThread(&grammarCheckThread);
	GrammarCheck::staticMetaObject.invokeMethod(grammarCheck, "init", Qt::QueuedConnection, Q_ARG(LatexParser, latexParser), Q_ARG(GrammarCheckerConfig, *configManager.grammarCheckerConfig));
    //connect(grammarCheck, SIGNAL(checked(LatexDocument*,QDocumentLineHandle*,int,QList<GrammarError>)), &documents, SLOT(lineGrammarChecked(LatexDocument*,QDocumentLineHandle*,int,QList<GrammarError>)));
    connect(grammarCheck, &GrammarCheck::checked, &documents, &LatexDocuments::lineGrammarChecked);
    connect(grammarCheck, SIGNAL(errorMessage(QString)),this,SLOT(LTErrorMessage(QString)));
	if (configManager.autoLoadChildren)
		connect(&documents, SIGNAL(docToLoad(QString)), this, SLOT(addDocToLoad(QString)));
	connect(&documents, SIGNAL(updateQNFA()), this, SLOT(updateTexQNFA()));

	grammarCheckThread.start();

	if (configManager.autoDetectEncodingFromLatex || configManager.autoDetectEncodingFromChars) QDocument::setDefaultCodec(nullptr);
	else QDocument::setDefaultCodec(configManager.newFileEncoding);
	if (configManager.autoDetectEncodingFromLatex)
		QDocument::addGuessEncodingCallback(&Encoding::guessEncoding); // encodingcallbacks before restoer session !!!
	if (configManager.autoDetectEncodingFromChars)
		QDocument::addGuessEncodingCallback(&ConfigManager::getDefaultEncoding);

	QString qxsPath = QFileInfo(findResourceFile("qxs/tex.qnfa")).path();
	m_languages = new QLanguageFactory(m_formats, this);
	m_languages->addDefinitionPath(qxsPath);
	m_languages->addDefinitionPath(configManager.configBaseDir + "languages");  // definitions here overwrite previous ones

	// custom evironments & structure commands
	updateTexQNFA();

	QLineMarksInfoCenter::instance()->loadMarkTypes(qxsPath + "/marks.qxm");
	QList<QLineMarkType> &marks = QLineMarksInfoCenter::instance()->markTypes();
	for (int i = 0; i < marks.size(); i++)
		if (m_formats->format("line:" + marks[i].id).background.isValid())
			marks[i].color = m_formats->format("line:" + marks[i].id).background;
		else
			marks[i].color = Qt::transparent;

	LatexEditorView::updateFormatSettings();

	// TAB WIDGET EDITEUR
	documents.indentationInStructure = configManager.indentationInStructure;
	documents.showCommentedElementsInStructure = configManager.showCommentedElementsInStructure;
	documents.indentIncludesInStructure = configManager.indentIncludesInStructure;
	documents.markStructureElementsBeyondEnd = configManager.markStructureElementsBeyondEnd;
	documents.markStructureElementsInAppendix = configManager.markStructureElementsInAppendix;
	documents.showLineNumbersInStructure = configManager.showLineNumbersInStructure;
    connect(&documents, SIGNAL(masterDocumentChanged(LatexDocument*)), SLOT(masterDocumentChanged(LatexDocument*)));
    connect(&documents, SIGNAL(aboutToDeleteDocument(LatexDocument*)), SLOT(aboutToDeleteDocument(LatexDocument*)));

	centralFrame = new QFrame(this);
	centralFrame->setLineWidth(0);
	centralFrame->setFrameShape(QFrame::NoFrame);
	centralFrame->setFrameShadow(QFrame::Plain);



	//edit
	centralToolBar = new QToolBar(tr("Central"), this);
	centralToolBar->setFloatable(false);
	centralToolBar->setOrientation(Qt::Vertical);
	centralToolBar->setMovable(false);
	iconSize = qRound(configManager.guiSecondaryToolbarIconSize*scale);
	centralToolBar->setIconSize(QSize(iconSize, iconSize));

	editors = new Editors(centralFrame);
	editors->setFocus();

	TxsTabWidget *leftEditors = new TxsTabWidget(this);
	leftEditors->setActive(true);
	editors->addTabWidget(leftEditors);
	TxsTabWidget *rightEditors = new TxsTabWidget(this);
	editors->addTabWidget(rightEditors);

    connect(&documents, SIGNAL(docToHide(LatexEditorView*)), editors, SLOT(removeEditor(LatexEditorView*)));
	connect(editors, SIGNAL(currentEditorChanged()), SLOT(currentEditorChanged()));
	connect(editors, SIGNAL(listOfEditorsChanged()), SLOT(updateOpenDocumentMenu()));
	connect(editors, SIGNAL(editorsReordered()), SLOT(onEditorsReordered()));
	connect(editors, SIGNAL(closeCurrentEditorRequested()), this, SLOT(fileClose()));
    connect(editors, SIGNAL(editorAboutToChangeByTabClick(LatexEditorView*,LatexEditorView*)), this, SLOT(editorAboutToChangeByTabClick(LatexEditorView*,LatexEditorView*)));

	cursorHistory = new CursorHistory(&documents);
	bookmarks = new Bookmarks(&documents, this);

	QLayout *centralLayout = new QHBoxLayout(centralFrame);
	centralLayout->setSpacing(0);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    centralLayout->setMargin(0);
#else
    centralLayout->setContentsMargins(0,0,0,0);
#endif
	centralLayout->addWidget(centralToolBar);
	centralLayout->addWidget(editors);

	centralVSplitter = new MiniSplitter(Qt::Vertical, this);
	centralVSplitter->setChildrenCollapsible(false);
	centralVSplitter->addWidget(centralFrame);
	centralVSplitter->setStretchFactor(0, 1);  // all stretch goes to the editor (0th widget)

	sidePanelSplitter = new MiniSplitter(Qt::Horizontal, this);
	sidePanelSplitter->addWidget(centralVSplitter);

	mainHSplitter = new MiniSplitter(Qt::Horizontal, this);  // top-level element: splits: [ everything else | PDF ]
	mainHSplitter->addWidget(sidePanelSplitter);
	mainHSplitter->setChildrenCollapsible(false);
	setCentralWidget(mainHSplitter);

	setContextMenuPolicy(Qt::ActionsContextMenu);

	setupDockWidgets();

	setMenuBar(new DblClickMenuBar());
	setupMenus();
#ifndef QT_NO_DEBUG
    checkForShortcutDuplicate();
#endif
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

	createStatusBar();
	completer = nullptr;
	updateCaption();
	updateMasterDocumentCaption();
	setStatusMessageProcess(QString(" %1 ").arg(tr("Ready")));

	if (tobefullscreen) {
		showFullScreen();
		restoreState(stateFullScreen, 1);
		fullscreenModeAction->setChecked(true);
	} else if (tobemaximized) {
#ifdef Q_OS_WIN
		// Workaround a Qt/Windows bug which prevents too small windows from maximizing
		// For more details see:
		// https://stackoverflow.com/questions/27157312/qt-showmaximized-not-working-in-windows
		// https://bugreports.qt.io/browse/QTBUG-77077
		resize(800, 600);
#endif
		showMaximized();
	} else {
		show();
	}
	if (splash)
		splash->raise();

	setAcceptDrops(true);
	//installEventFilter(this);

    completer = new LatexCompleter(latexParser, this);
    completer->setConfig(configManager.completerConfig);
    completer->setPackageList(&latexPackageList);
    connect(completer, &LatexCompleter::showImagePreview, this, &Texstudio::showImgPreview);
    connect(completer, SIGNAL(showPreview(QString)), this, SLOT(showPreview(QString)));
    connect(this, &Texstudio::imgPreview, completer, &LatexCompleter::bibtexSectionFound);
    //updateCompleter();
    LatexEditorView::setCompleter(completer);
    completer->setLatexReference(latexReference);
    completer->updateAbbreviations();

	TemplateManager::setConfigBaseDir(configManager.configBaseDir);
	TemplateManager::ensureUserTemplateDirExists();
	TemplateManager::checkForOldUserTemplates();

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

    connect(&svn, &SVN::statusMessage, this, &Texstudio::setStatusMessageProcess);
    connect(&svn, SIGNAL(runCommand(QString,QString*)), this, SLOT(runCommandNoSpecialChars(QString,QString*)));
    connect(&git, &GIT::statusMessage, this, &Texstudio::setStatusMessageProcess);
    connect(&git, SIGNAL(runCommand(QString,QString*)), this, SLOT(runCommandNoSpecialChars(QString,QString*)));

    connect(&help, &Help::statusMessage, this, &Texstudio::setStatusMessageProcess);
    connect(&help, SIGNAL(runCommand(QString,QString*)), this, SLOT(runCommandNoSpecialChars(QString,QString*)));
    connect(&help, SIGNAL(runCommandAsync(QString,const char*)), this, SLOT(runCommandAsync(QString,const char*)));

    connect(qGuiApp,&QGuiApplication::paletteChanged,this,&Texstudio::paletteChanged);
#if (QT_VERSION >= 0x060500) && (defined( Q_OS_WIN )||defined( Q_OS_LINUX ))
    connect(qGuiApp->styleHints(),&QStyleHints::colorSchemeChanged,this,&Texstudio::colorSchemeChanged);
#endif


	QStringList filters;
	filters << tr("TeX files") + " (*.tex *.bib *.sty *.cls *.mp *.dtx *.cfg *.ins *.ltx *.tikz *.pdf_tex *.ctx)";
	filters << tr("LilyPond files") + " (*.lytex)";
	filters << tr("Plaintext files") + " (*.txt)";
	filters << tr("Pweave files") + " (*.Pnw)";
	filters << tr("Sweave files") + " (*.Snw *.Rnw)";
	filters << tr("Asymptote files") + " (*.asy)";
	filters << tr("PDF files") + " (*.pdf)";
	filters << tr("All files") + " (*)";
	fileFilters = filters.join(";;");
	if (!configManager.rememberFileFilter)
		selectedFileFilter = filters.first();

    enlargedViewer=false;

	//setup autosave timer
    connect(&autosaveTimer, SIGNAL(timeout()), this, SLOT(fileSaveAllFromTimer()));
	if (configManager.autosaveEveryMinutes > 0) {
		autosaveTimer.start(configManager.autosaveEveryMinutes * 1000 * 60);
	}
	connect(&previewDelayTimer,SIGNAL(timeout()),this,SLOT(showPreviewQueue()));
	previewDelayTimer.setSingleShot(true);
	connect(&previewFullCompileDelayTimer,SIGNAL(timeout()),this,SLOT(recompileForPreviewNow()));
	previewFullCompileDelayTimer.setSingleShot(true);

    connect(this, SIGNAL(infoFileSaved(QString,int)), this, SLOT(checkinAfterSave(QString,int)));

	//script things
	setProperty("applicationName", TEXSTUDIO);
	QTimer::singleShot(500, this, SLOT(autoRunScripts()));
	connectWithAdditionalArguments(this, SIGNAL(infoNewFile()), this, "runScripts", QList<QVariant>() << Macro::ST_NEW_FILE);
	connectWithAdditionalArguments(this, SIGNAL(infoNewFromTemplate()), this, "runScripts", QList<QVariant>() << Macro::ST_NEW_FROM_TEMPLATE);
	connectWithAdditionalArguments(this, SIGNAL(infoLoadFile(QString)), this, "runScripts", QList<QVariant>() << Macro::ST_LOAD_FILE);
	connectWithAdditionalArguments(this, SIGNAL(infoFileSaved(QString)), this, "runScripts", QList<QVariant>() << Macro::ST_FILE_SAVED);
	connectWithAdditionalArguments(this, SIGNAL(infoFileClosed()), this, "runScripts", QList<QVariant>() << Macro::ST_FILE_CLOSED);
	connectWithAdditionalArguments(&documents, SIGNAL(masterDocumentChanged(LatexDocument *)), this, "runScripts", QList<QVariant>() << Macro::ST_MASTER_CHANGED);
	connectWithAdditionalArguments(this, SIGNAL(infoAfterTypeset()), this, "runScripts", QList<QVariant>() << Macro::ST_AFTER_TYPESET);
	connectWithAdditionalArguments(&buildManager, SIGNAL(endRunningCommands(QString, bool, bool, bool)), this, "runScripts", QList<QVariant>() << Macro::ST_AFTER_COMMAND_RUN);

	if (configManager.sessionRestore && !ConfigManager::dontRestoreSession) {
		fileRestoreSession(false, false);
	}
	splashscreen = nullptr;
}
/*!
 * \brief destructor
 */
Texstudio::~Texstudio()
{
    //structureTreeView->setModel(nullptr);
	iconCache.clear();
	QDocument::setDefaultFormatScheme(m_formatsOldDefault); //prevents crash when deleted latexeditorview accesses the default format scheme, as m_format is going to be deleted

	programStopped = true;

	Guardian::shutdown();

	if (latexStyleParser) latexStyleParser->stop();
	if (packageListReader) packageListReader->stop();
	GrammarCheck::staticMetaObject.invokeMethod(grammarCheck, "shutdown", Qt::BlockingQueuedConnection);
	grammarCheckThread.quit();

	if (latexStyleParser) latexStyleParser->wait();
	if (packageListReader) packageListReader->wait();
	grammarCheckThread.wait(5000); //TODO: timeout causes sigsegv, is there any better solution?
}

/*!
 * \brief code to be executed at end of start-up
 *
 * Check for Latex installation.
 * Read in all package names for usepackage completion.
 */
void Texstudio::startupCompleted()
{
	if (configManager.checkLatexConfiguration) {
		bool noWarnAgain = false;
		buildManager.checkLatexConfiguration(noWarnAgain);
		configManager.checkLatexConfiguration = !noWarnAgain;
	}
	UpdateChecker::instance()->autoCheck();
	// package reading (at least with Miktex) apparently slows down the startup
	// the first rendering of lines in QDocumentPrivate::draw() gets very slow
	// therefore we defer it until the main window is completely loaded
	readinAllPackageNames(); // asynchrnous read in of all available sty/cls
}

QAction *Texstudio::newManagedAction(QWidget *menu, const QString &id, const QString &text, const char *slotName, const QKeySequence &shortCut, const QString &iconFile, const QList<QVariant> &args)
{
	QAction *tmp = configManager.newManagedAction(menu, id, text, args.isEmpty() ? slotName : SLOT(relayToOwnSlot()), QList<QKeySequence>() << shortCut, iconFile);
	if (!args.isEmpty()) {
		QString slot = QString(slotName).left(QString(slotName).indexOf("("));
		Q_ASSERT(staticMetaObject.indexOfSlot(createMethodSignature(qPrintable(slot), args)) != -1);
		tmp->setProperty("slot", qPrintable(slot));
		tmp->setProperty("args", QVariant::fromValue<QList<QVariant> >(args));
	}
	return tmp;
}

QAction *Texstudio::newManagedAction(QWidget *menu, const QString &id, const QString &text, const char *slotName, const QList<QKeySequence> &shortCuts, const QString &iconFile, const QList<QVariant> &args)
{
	QAction *tmp = configManager.newManagedAction(menu, id, text, args.isEmpty() ? slotName : SLOT(relayToOwnSlot()), shortCuts, iconFile);
	if (!args.isEmpty()) {
		QString slot = QString(slotName).left(QString(slotName).indexOf("("));
		Q_ASSERT(staticMetaObject.indexOfSlot(createMethodSignature(qPrintable(slot), args)) != -1);
		tmp->setProperty("slot", qPrintable(slot));
		tmp->setProperty("args", QVariant::fromValue<QList<QVariant> >(args));
	}
	return tmp;
}

QAction *Texstudio::newManagedEditorAction(QWidget *menu, const QString &id, const QString &text, const char *slotName, const QKeySequence &shortCut, const QString &iconFile, const QList<QVariant> &args)
{
        QAction *tmp = configManager.newManagedAction(menu, id, text, nullptr, QList<QKeySequence>() << shortCut, iconFile);
	linkToEditorSlot(tmp, slotName, args);
	return tmp;
}

QAction *Texstudio::newManagedEditorAction(QWidget *menu, const QString &id, const QString &text, const char *slotName, const QList<QKeySequence> &shortCuts, const QString &iconFile, const QList<QVariant> &args)
{
        QAction *tmp = configManager.newManagedAction(menu, id, text, nullptr, shortCuts, iconFile);
	linkToEditorSlot(tmp, slotName, args);
	return tmp;
}

QAction *Texstudio::insertManagedAction(QAction *before, const QString &id, const QString &text, const char *slotName, const QKeySequence &shortCut, const QString &iconFile)
{
	QMenu *menu = before->menu();
	REQUIRE_RET(menu, nullptr);
	QAction *inserted = newManagedAction(menu, id, text, slotName, shortCut, iconFile);
	menu->removeAction(inserted);
	menu->insertAction(before, inserted);
    return inserted;
}
/*!
 * \brief loadManagedMenu for script use
 * \param fn
 */
void Texstudio::loadManagedMenu(const QString &fn)
{
    configManager.loadManagedMenus(fn);
}

/*!
 * \brief add TagList to side panel
 *
 * add Taglist to side panel.
 *
 * \param id
 * \param iconName icon used for selecting taglist
 * \param text name of taglist
 * \param tagFile file to be read as tag list
 */
void Texstudio::addTagList(const QString &id, const QString &iconName, const QString &text, const QString &tagFile)
{
	XmlTagsListWidget *list = qobject_cast<XmlTagsListWidget *>(leftPanel->widget(id));
	if (!list) {
		list = new XmlTagsListWidget(this, ":/tags/" + tagFile);
		list->setObjectName("tags/" + tagFile.left(tagFile.indexOf("_tags.xml")));
		UtilsUi::enableTouchScrolling(list);
        connect(list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(insertXmlTag(QListWidgetItem*)));
		leftPanel->addWidget(list, id, text, iconName);
		//(*list)->setProperty("mType",2);
    } else {
        leftPanel->setWidgetText(list, text);
        leftPanel->setWidgetIcon(list,iconName);
    }
}

/*!
 * \brief add all macros as TagList to side panel
 *
 * add Macros as Taglist to side panel as an alternative way to call them.
 * This may be helpful if the number of macros becomes large and overcrowd the menu or are too many for generic keyboard shortcuts
 *
 */
void Texstudio::addMacrosAsTagList()
{
    bool addToPanel=true;
    QListWidget *list = qobject_cast<QListWidget *>(leftPanel->widget("txs-macros"));
    if (!list) {
        list = new QListWidget(this);
        list->setObjectName("tags/txs-macros");
    }else{
        list->clear();
        addToPanel=false;
    }
    // add elements
    for(const auto &m:configManager.completerConfig->userMacros) {
        if (m.name == "TMX:Replace Quote Open" || m.name == "TMX:Replace Quote Close" || m.document)
            continue;
        QListWidgetItem* item=new QListWidgetItem(m.name);
        item->setData(Qt::UserRole, m.typedTag());
        list->addItem(item);
    }
    UtilsUi::enableTouchScrolling(list);
    connect(list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(insertFromTagList(QListWidgetItem*)),Qt::UniqueConnection);
    if(addToPanel){
        leftPanel->addWidget(list, "txs-macros", tr("Macros"), getRealIconFile("executeMacro"));
    }else{
        leftPanel->setWidgetText(list,tr("Macros"));
        leftPanel->setWidgetIcon(list,getRealIconFile("executeMacro"));
    }
}

/*! set-up side- and bottom-panel
 */
void Texstudio::setupDockWidgets()
{
    //to allow retranslate this function must be able to be called multiple times

    // adapt icon size to dpi
    double dpi=QGuiApplication::primaryScreen()->logicalDotsPerInch();
    double scale=dpi/96;

    if (!sidePanel) {
        sidePanel = new SidePanel(this);
        sidePanel->toggleViewAction()->setIcon(getRealIcon("sidebar"));
        sidePanel->toggleViewAction()->setText(tr("Side Panel"));
        sidePanel->toggleViewAction()->setChecked(configManager.getOption("GUI/sidePanel/visible", true).toBool());
        addAction(sidePanel->toggleViewAction());

        sidePanelSplitter->insertWidget(0, sidePanel);
        sidePanelSplitter->setStretchFactor(0, 0);  // panel does not get rescaled
        sidePanelSplitter->setStretchFactor(1, 1);
    }else{
        sidePanel->toggleViewAction()->setIcon(getRealIcon("sidebar"));
    }

    //Structure panel
    if (!leftPanel) {
        leftPanel = new CustomWidgetList(this);
        leftPanel->setObjectName("leftPanel");
        TitledPanelPage *page = new TitledPanelPage(leftPanel, "leftPanel", "TODO");
        sidePanel->appendPage(page);
        if (hiddenLeftPanelWidgets != "") {
            leftPanel->setHiddenWidgets(hiddenLeftPanelWidgets);
            hiddenLeftPanelWidgets = ""; //not needed anymore after the first call
        }
        connect(leftPanel, SIGNAL(titleChanged(QString)), page, SLOT(setTitle(QString)));
        connect(leftPanel, SIGNAL(currentWidgetChanged(QWidget*)), this, SLOT(leftPanelChanged(QWidget*)));
        connect(sidePanel,&TitledPanel::showPanel,this,&Texstudio::updateTOCs);
    }

    // load icons for structure view
    setStructureSectionIcons();

    if(!structureTreeWidget){
        structureTreeWidget = new QTreeWidget();
        connect(structureTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(gotoLine(QTreeWidgetItem*,int)));
        connect(structureTreeWidget, &QTreeWidget::itemExpanded, this, &Texstudio::syncExpanded);
        connect(structureTreeWidget, &QTreeWidget::itemCollapsed, this, &Texstudio::syncCollapsed);
        connect(structureTreeWidget, &QTreeWidget::customContextMenuRequested, this, &Texstudio::customMenuStructure);
        structureTreeWidget->setHeaderHidden(true);
        structureTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        structureTreeWidget->installEventFilter(this);
        leftPanel->addWidget(structureTreeWidget, "structureTreeWidget", tr("Structure"), getRealIconFile("structure"));
    } else {
        leftPanel->setWidgetText(structureTreeWidget, tr("Structure"));
        leftPanel->setWidgetIcon(structureTreeWidget, getRealIconFile("structure"));
    }
    if(!topTOCTreeWidget){
        topTOCTreeWidget = new QTreeWidget();
        connect(topTOCTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(gotoLine(QTreeWidgetItem*,int)));
        connect(topTOCTreeWidget, &QTreeWidget::itemExpanded, this, &Texstudio::syncExpanded);
        connect(topTOCTreeWidget, &QTreeWidget::itemCollapsed, this, &Texstudio::syncCollapsed);
        connect(topTOCTreeWidget, &QTreeWidget::customContextMenuRequested, this, &Texstudio::customMenuStructure);
        topTOCTreeWidget->setHeaderHidden(true);
        topTOCTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        topTOCTreeWidget->installEventFilter(this);
        leftPanel->addWidget(topTOCTreeWidget, "topTOCTreeWidget", tr("TOC"), getRealIconFile("toc"));
    } else {
        leftPanel->setWidgetText(topTOCTreeWidget, tr("TOC"));
        leftPanel->setWidgetIcon(topTOCTreeWidget, getRealIconFile("toc"));
    }
    if (!leftPanel->widget("bookmarks")) {
        QListWidget *bookmarksWidget = bookmarks->widget();
        bookmarks->setDarkMode(darkMode);
        connect(bookmarks, SIGNAL(loadFileRequest(QString)), this, SLOT(load(QString)));
        connect(bookmarks, SIGNAL(gotoLineRequest(int,int,LatexEditorView*)), this, SLOT(gotoLine(int,int,LatexEditorView*)));
        leftPanel->addWidget(bookmarksWidget, "bookmarks", tr("Bookmarks"), getRealIconFile("bookmarks"));
    } else {
        leftPanel->setWidgetText("bookmarks", tr("Bookmarks"));
        leftPanel->setWidgetIcon("bookmarks", getRealIconFile("bookmarks"));
        bookmarks->setDarkMode(darkMode);
    }

    if (!leftPanel->widget("symbols")) {
        symbolWidget = new SymbolWidget(symbolListModel, configManager.insertSymbolsAsUnicode, this);
        symbolWidget->restoreSplitter(configManager.stateSymbolsWidget);
        symbolWidget->setSymbolSize(qRound(configManager.guiSymbolGridIconSize*scale));
        connect(symbolWidget, SIGNAL(insertSymbol(QString)), this, SLOT(insertSymbol(QString)));
        leftPanel->addWidget(symbolWidget, "symbols", tr("Symbols"), getRealIconFile("symbols"));
    } else {
        leftPanel->setWidgetText("symbols", tr("Symbols"));
        leftPanel->setWidgetIcon("symbols", getRealIconFile("symbols"));
        symbolListModel->setDarkmode(darkMode);
        symbolWidget->reloadData();
    }

    addTagList("brackets", getRealIconFile("leftright"), tr("Left/Right Brackets"), "brackets_tags.xml");
    addTagList("pstricks", getRealIconFile("pstricks"), tr("PSTricks Commands"), "pstricks_tags.xml");
    addTagList("metapost", getRealIconFile("metapost"), tr("MetaPost Commands"), "metapost_tags.xml");
    addTagList("tikz", getRealIconFile("tikz"), tr("TikZ Commands"), "tikz_tags.xml");
    addTagList("asymptote", getRealIconFile("asymptote"), tr("Asymptote Commands"), "asymptote_tags.xml");
    addTagList("beamer", getRealIconFile("beamer"), tr("Beamer Commands"), "beamer_tags.xml");
    addTagList("xymatrix", getRealIconFile("xy"), tr("XY Commands"), "xymatrix_tags.xml");
    addMacrosAsTagList();

    leftPanel->showWidgets();
    // restore selected view in sidepanel
	QList<QString> hiddenWidgetsIdsList = leftPanel->hiddenWidgets().split("|");
    int viewNr = configManager.getOption("GUI/sidePanel/currentPage", 0).toInt();
	int k = -1; // index of visible tool found
	for (int i = 0; i < leftPanel->widgetCount(); i++)  {
		QString currentWidgetId = leftPanel->widget(i)->property("id").toString();
		if (!hiddenWidgetsIdsList.contains(currentWidgetId)) {
			k++;
			if (k == viewNr) {
				leftPanel->setCurrentWidget(leftPanel->widget(i));
				emit leftPanel->titleChanged(leftPanel->widget(i)->property("Name").toString());
				break;
			}
		}
	}
	if (k == -1) // there are no visible tools
		emit leftPanel->titleChanged("");

    // OUTPUT WIDGETS
    if (!outputView) {
        outputView = new OutputViewWidget(this, configManager.terminalConfig);
        outputView->setObjectName("OutputView");
        centralVSplitter->addWidget(outputView);
        outputView->toggleViewAction()->setChecked(configManager.getOption("GUI/outputView/visible", true).toBool());
        centralVSplitter->setStretchFactor(1, 0);
        centralVSplitter->restoreState(configManager.getOption("centralVSplitterState").toByteArray());

        connect(outputView->getLogWidget(), SIGNAL(logEntryActivated(int)), this, SLOT(gotoLogEntryEditorOnly(int)));
        connect(outputView->getLogWidget(), SIGNAL(logLoaded()), this, SLOT(updateLogEntriesInEditors()));
        connect(outputView->getLogWidget(), SIGNAL(logResetted()), this, SLOT(clearLogEntriesInEditors()));
        connect(outputView, SIGNAL(pageChanged(QString)), this, SLOT(outputPageChanged(QString)));
        connect(outputView->getSearchResultWidget(), SIGNAL(jumpToSearchResult(QDocument*,int,const SearchQuery*)), this, SLOT(jumpToSearchResult(QDocument*,int,const SearchQuery*)));
        connect(outputView->getSearchResultWidget(), SIGNAL(runSearch(SearchQuery*)), this, SLOT(runSearch(SearchQuery*)));

        connect(&buildManager, SIGNAL(previewAvailable(const QString&,const PreviewSource&)), this, SLOT(previewAvailable(const QString&,const PreviewSource&)));
        connect(&buildManager, SIGNAL(processNotification(QString)), SLOT(processNotification(QString)));
        connect(&buildManager, SIGNAL(clearLogs()), SLOT(clearLogs()));

        connect(&buildManager, SIGNAL(beginRunningCommands(QString,bool,bool,bool)), SLOT(beginRunningCommand(QString,bool,bool,bool)));
        connect(&buildManager, SIGNAL(beginRunningSubCommand(ProcessX*,QString,QString,RunCommandFlags)), SLOT(beginRunningSubCommand(ProcessX*,QString,QString,RunCommandFlags)));
        connect(&buildManager, SIGNAL(endRunningSubCommand(ProcessX*,QString,QString,RunCommandFlags)), SLOT(endRunningSubCommand(ProcessX*,QString,QString,RunCommandFlags)));
        connect(&buildManager, SIGNAL(endRunningCommands(QString,bool,bool,bool)), SLOT(endRunningCommand(QString,bool,bool,bool)));
        connect(&buildManager, SIGNAL(latexCompiled(LatexCompileResult*)), SLOT(viewLogOrReRun(LatexCompileResult*)));
        connect(&buildManager, SIGNAL(runInternalCommand(QString,QFileInfo,QString)), SLOT(runInternalCommand(QString,QFileInfo,QString)));
        connect(&buildManager, SIGNAL(commandLineRequested(QString,QString*,bool*)), SLOT(commandLineRequested(QString,QString*,bool*)));

        addAction(outputView->toggleViewAction());
        QAction *temp = new QAction(this);
        temp->setSeparator(true);
        addAction(temp);
    }else{
        outputView->updateIcon();
    }
    sidePanelSplitter->restoreState(configManager.getOption("GUI/sidePanelSplitter/state").toByteArray());
}

void Texstudio::updateToolBarMenu(const QString &menuName)
{
	QMenu *menu = configManager.getManagedMenu(menuName);
	if (!menu) return;
	LatexEditorView *edView = currentEditorView();
    foreach (const ManagedToolBar &tb, configManager.managedToolBars){
        if (tb.toolbar && tb.actualActions.contains(menuName)){
            foreach (QObject *w, tb.toolbar->children()){
				if (w->property("menuID").toString() == menuName) {
					QToolButton *combo = qobject_cast<QToolButton *>(w);
					REQUIRE(combo);

					QStringList actionTexts;
					QStringList actionInfos;
					QList<QIcon> actionIcons;
					int defaultIndex = -1;
					foreach (const QAction *act, menu->actions()) {
						if (!act->isSeparator()) {
							actionTexts.append(act->text());
							actionInfos.append(act->toolTip());
							actionIcons.append(act->icon());
							if (menuName == "main/view/documents" && edView == act->data().value<LatexEditorView *>()) {
								defaultIndex = actionTexts.length() - 1;
							}
						}
						else {
							actionTexts.append("");
							actionInfos.append("");
							actionIcons.append(QIcon());
						}
					}
					UtilsUi::createComboToolButton(tb.toolbar, actionTexts, actionInfos, actionIcons, -1, this, SLOT(callToolButtonAction()), defaultIndex, combo);

					if (menuName == "main/view/documents") {
						// workaround to select the current document
						// combobox uses separate actions. So we have to get the current action from the menu (by comparing its data()
						// attribute to the currentEditorView(). Then map it to a combobox action using the index.
						// TODO: should this menu be provided by Editors?
						LatexEditorView *edView = currentEditorView();
						foreach (QAction* act, menu->actions()) {
							if (edView == act->data().value<LatexEditorView *>()) {
								int i = menu->actions().indexOf(act);
								if (i < 0 || i>= combo->menu()->actions().length()) continue;
								combo->setDefaultAction(combo->menu()->actions()[i]);
							}
						}
					}
				}
            }
        }
    }
}

// we different native shortcuts on OSX and Win/Linux
// note: in particular many key combination with arrows are reserved for text navigation in OSX
// and we already set them in QEditor. Don't overwrite them here.
#ifdef Q_OS_MAC
    #define MAC_OR_DEFAULT(shortcutMac, shortcutOther) shortcutMac
#else
    #define MAC_OR_DEFAULT(shortcutMac, shortcutOther) shortcutOther
#endif
/*! \brief set-up all menus in the menu-bar
 *
 * This function is called whenever the menu changes (= start and retranslation)
 * This means if you call it repeatedly with the same language setting it should not change anything
 * Currently this is not true, because it adds additional separator, which are invisible
 * creates new action groups and new context menu, although all invisible, they are a memory leak
 * But not a bad one, because no one is expected to change the language multiple times
 */
void Texstudio::setupMenus()
{
	//This function is called whenever the menu changes (= start and retranslation)
	//This means if you call it repeatedly with the same language setting it should not change anything
	//Currently this is not true, because it adds additional separator, which are invisible
	//creates new action groups and new context menu, although all invisible, they are a memory leak
	//But not a bad one, because no one is expected to change the language multiple times
	//TODO: correct somewhen

	configManager.menuParent = this;
    if(configManager.menuParents.isEmpty()){
        configManager.menuParents.append(this);
    }
	configManager.menuParentsBar = menuBar();

	//file
	QMenu *menu = newManagedMenu("main/file", tr("&File"));
    //getManagedMenu("main/file");
	newManagedAction(menu, "new", tr("&New"), SLOT(fileNew()), QKeySequence::New, "document-new");
	newManagedAction(menu, "newfromtemplate", tr("New From &Template..."), SLOT(fileNewFromTemplate()));
	newManagedAction(menu, "open", tr("&Open..."), SLOT(fileOpen()), QKeySequence::Open, "document-open");

	QMenu *submenu = newManagedMenu(menu, "openrecent", tr("Open &Recent")); //only create the menu here, actions are created by config manager

	submenu = newManagedMenu(menu, "session", tr("Session"));
	newManagedAction(submenu, "loadsession", tr("Load Session..."), SLOT(fileLoadSession()));
	newManagedAction(submenu, "savesession", tr("Save Session..."), SLOT(fileSaveSession()));
	newManagedAction(submenu, "restoresession", tr("Restore Previous Session"), SLOT(fileRestoreSession()));
	submenu->addSeparator();
	if (!recentSessionList) {
		recentSessionList = new SessionList(submenu, this);
		connect(recentSessionList, SIGNAL(loadSessionRequest(QString)), this, SLOT(loadSession(QString)));
	}
	recentSessionList->updateMostRecentMenu();

	menu->addSeparator();
	actSave = newManagedAction(menu, "save", tr("&Save"), SLOT(fileSave()), QKeySequence::Save, "document-save");
    newManagedAction(menu, "saveas", tr("Save &As..."), SLOT(fileSaveAs()), filterLocaleShortcut(Qt::CTRL | Qt::ALT | Qt::Key_S));
    newManagedAction(menu, "saveall", tr("Save A&ll"), SLOT(fileSaveAll()), Qt::CTRL | Qt::SHIFT | Qt::Key_S);
	newManagedAction(menu, "maketemplate", tr("&Make Template..."), SLOT(fileMakeTemplate()));


	submenu = newManagedMenu(menu, "utilities", tr("Fifi&x"));
	newManagedAction(submenu, "rename", tr("Save renamed/&moved file..."), "fileUtilCopyMove", 0, QString(), QList<QVariant>() << true);
	newManagedAction(submenu, "copy", tr("Save copied file..."), "fileUtilCopyMove", 0, QString(), QList<QVariant>() << false);
	newManagedAction(submenu, "delete", tr("&Delete file"), SLOT(fileUtilDelete()));
	newManagedAction(submenu, "chmod", tr("Set &permissions..."), SLOT(fileUtilPermissions()));
	submenu->addSeparator();
	newManagedAction(submenu, "revert", tr("&Revert to saved..."), SLOT(fileUtilRevert()));
	submenu->addSeparator();
	newManagedAction(submenu, "copyfilename", tr("Copy filename to &clipboard"), SLOT(fileUtilCopyFileName()));
	newManagedAction(submenu, "copymasterfilename", tr("Copy root filename to clipboard"), SLOT(fileUtilCopyMasterFileName()));

    QMenu *svnSubmenu = newManagedMenu(menu, "svn", tr("S&VN/GIT..."));
	newManagedAction(svnSubmenu, "checkin", tr("Check &in..."), SLOT(fileCheckin()));
	newManagedAction(svnSubmenu, "svnupdate", tr("SVN &update..."), SLOT(fileUpdate()));
	newManagedAction(svnSubmenu, "svnupdatecwd", tr("SVN update &work directory"), SLOT(fileUpdateCWD()));
	newManagedAction(svnSubmenu, "showrevisions", tr("Sh&ow old Revisions"), SLOT(showOldRevisions()));
	newManagedAction(svnSubmenu, "lockpdf", tr("Lock &PDF"), SLOT(fileLockPdf()));
	newManagedAction(svnSubmenu, "checkinpdf", tr("Check in P&DF"), SLOT(fileCheckinPdf()));
	newManagedAction(svnSubmenu, "difffiles", tr("Show difference between two files"), SLOT(fileDiff()));
	newManagedAction(svnSubmenu, "diff3files", tr("Show difference between two files in relation to base file"), SLOT(fileDiff3()));
	newManagedAction(svnSubmenu, "checksvnconflict", tr("Check SVN Conflict"), SLOT(checkSVNConflicted()));
	newManagedAction(svnSubmenu, "mergediff", tr("Try to merge differences"), SLOT(fileDiffMerge()));
	newManagedAction(svnSubmenu, "removediffmakers", tr("Remove Difference-Markers"), SLOT(removeDiffMarkers()));
	newManagedAction(svnSubmenu, "declareresolved", tr("Declare Conflict Resolved"), SLOT(declareConflictResolved()));
	newManagedAction(svnSubmenu, "nextdiff", tr("Jump to next difference"), SLOT(jumpNextDiff()), 0, "go-next-diff");
	newManagedAction(svnSubmenu, "prevdiff", tr("Jump to previous difference"), SLOT(jumpPrevDiff()), 0, "go-previous-diff");

	menu->addSeparator();
    newManagedAction(menu, "close", tr("&Close"), SLOT(fileClose()), Qt::CTRL | Qt::Key_W, "document-close");
	newManagedAction(menu, "closeall", tr("Clos&e All"), SLOT(fileCloseAll()));

	menu->addSeparator();
    newManagedEditorAction(menu, "print", tr("Print Source Code..."), "print", Qt::CTRL | Qt::Key_P);

	menu->addSeparator();
    newManagedAction(menu, "exit", tr("Exit"), SLOT(fileExit()), Qt::CTRL | Qt::Key_Q)->setMenuRole(QAction::QuitRole);

	//edit
	menu = newManagedMenu("main/edit", tr("&Edit"));
	actUndo = newManagedAction(menu, "undo", tr("&Undo"), SLOT(editUndo()), QKeySequence::Undo, "edit-undo");
	actRedo = newManagedAction(menu, "redo", tr("&Redo"), SLOT(editRedo()), QKeySequence::Redo, "edit-redo");
#ifndef QT_NO_DEBUG
	newManagedAction(menu, "debughistory", tr("Debug undo stack"), SLOT(editDebugUndoStack()));
#endif
	menu->addSeparator();
    newManagedEditorAction(menu, "cut", tr("C&ut"), "cut", QKeySequence::Cut, "edit-cut");
	newManagedAction(menu, "copy", tr("&Copy"), SLOT(editCopy()), QKeySequence::Copy, "edit-copy");
	newManagedAction(menu, "paste", tr("&Paste"), SLOT(editPaste()), QKeySequence::Paste, "edit-paste");

	submenu = newManagedMenu(menu, "selection", tr("&Selection"));
    newManagedEditorAction(submenu, "selectAll", tr("Select &All"), "selectAll", Qt::CTRL | Qt::Key_A);
	newManagedEditorAction(submenu, "selectAllOccurences", tr("Select All &Occurrences"), "selectAllOccurences");
	newManagedEditorAction(submenu, "selectPrevOccurence", tr("Select &Prev Occurrence"), "selectPrevOccurence");
	newManagedEditorAction(submenu, "selectNextOccurence", tr("Select &Next Occurrence"), "selectNextOccurence");
	newManagedEditorAction(submenu, "selectPrevOccurenceKeepMirror", tr("Also Select Prev Occurrence"), "selectPrevOccurenceKeepMirror");
	newManagedEditorAction(submenu, "selectNextOccurenceKeepMirror", tr("Also Select Next Occurrence"), "selectNextOccurenceKeepMirror");
    newManagedEditorAction(submenu, "expandSelectionToWord", tr("Expand Selection to Word"), "selectExpandToNextWord", Qt::CTRL | Qt::Key_D);
    newManagedEditorAction(submenu, "expandSelectionToLine", tr("Expand Selection to Line"), "selectExpandToNextLine", Qt::CTRL | Qt::Key_L);

	submenu = newManagedMenu(menu, "lineoperations", tr("&Line Operations"));
    newManagedAction(submenu, "deleteLine", tr("Delete &Line"), SLOT(editDeleteLine()), Qt::CTRL | Qt::Key_K);
    newManagedAction(submenu, "cutLine", tr("C&ut Line or Selection"), SLOT(editCutLine()), Qt::SHIFT | Qt::Key_Delete);
#if QT_VERSION>=QT_VERSION_CHECK(6,0,0)
    newManagedAction(submenu, "deleteToEndOfLine", tr("Delete To &End Of Line"), SLOT(editDeleteToEndOfLine()), MAC_OR_DEFAULT(Qt::CTRL | Qt::Key_Delete,  Qt::AltModifier | Qt::Key_K));
#else
    newManagedAction(submenu, "deleteToEndOfLine", tr("Delete To &End Of Line"), SLOT(editDeleteToEndOfLine()), MAC_OR_DEFAULT(Qt::CTRL | Qt::Key_Delete,  Qt::AltModifier + Qt::Key_K));
#endif
    newManagedAction(submenu, "deleteFromStartOfLine", tr("Delete From &Start Of Line"), SLOT(editDeleteFromStartOfLine()), MAC_OR_DEFAULT(Qt::CTRL | Qt::Key_Backspace, 0));
	newManagedAction(submenu, "moveLineUp", tr("Move Line &Up"), SLOT(editMoveLineUp()));
	newManagedAction(submenu, "moveLineDown", tr("Move Line &Down"), SLOT(editMoveLineDown()));
	newManagedAction(submenu, "duplicateLine", tr("Du&plicate Line"), SLOT(editDuplicateLine()));
	newManagedAction(submenu, "sortLines", tr("S&ort Lines"), SLOT(editSortLines()));
	newManagedAction(submenu, "alignMirrors", tr("&Align Cursors"), SLOT(editAlignMirrors()));

	submenu = newManagedMenu(menu, "textoperations", tr("&Text Operations"));
	newManagedAction(submenu, "textToLowercase", tr("To Lowercase"), SLOT(editTextToLowercase()));
	newManagedAction(submenu, "textToUppercase", tr("To Uppercase"), SLOT(editTextToUppercase()));
	newManagedAction(submenu, "textToTitlecaseStrict", tr("To Titlecase (strict)"), SLOT(editTextToTitlecase()));
	newManagedAction(submenu, "textToTitlecaseSmart", tr("To Titlecase (smart)"), SLOT(editTextToTitlecaseSmart()));


	menu->addSeparator();
	submenu = newManagedMenu(menu, "searching", tr("&Searching"));
	newManagedAction(submenu, "find", tr("&Find"), SLOT(editFind()), QKeySequence::Find);
    newManagedEditorAction(submenu, "findnext", tr("Find &Next"), "findNext", MAC_OR_DEFAULT(Qt::CTRL | Qt::Key_G, Qt::Key_F3));
    newManagedEditorAction(submenu, "findprev", tr("Find &Prev"), "findPrev", MAC_OR_DEFAULT(Qt::CTRL | Qt::SHIFT | Qt::Key_G, Qt::SHIFT | Qt::Key_F3));
    newManagedEditorAction(submenu, "findinsamedir", tr("Continue F&ind"), "findInSameDir");
	newManagedEditorAction(submenu, "findcount", tr("&Count"), "findCount");
	newManagedEditorAction(submenu, "select", tr("&Select all matches..."), "selectAllMatches");
	submenu->addSeparator();
    newManagedEditorAction(submenu, "replace", tr("&Replace"), "replacePanel", Qt::CTRL | Qt::Key_R);
	newManagedEditorAction(submenu, "replacenext", tr("Replace Next"), "replaceNext");
	newManagedEditorAction(submenu, "replaceprev", tr("Replace Prev"), "replacePrev");
	newManagedEditorAction(submenu, "replaceall", tr("Replace &All"), "replaceAll");

	menu->addSeparator();
	submenu = newManagedMenu(menu, "goto", tr("Go to"));

    newManagedEditorAction(submenu, "line", tr("Line"), "gotoLine", MAC_OR_DEFAULT(Qt::CTRL + Qt::Key_L, Qt::CTRL | Qt::Key_G), "goto");
    newManagedEditorAction(submenu, "lastchange", tr("Previous Change"), "jumpChangePositionBackward", Qt::CTRL | Qt::Key_H);
#if (QT_VERSION>=QT_VERSION_CHECK(6,0,0))
    newManagedEditorAction(submenu, "nextchange", tr("Next Change"), "jumpChangePositionForward", QKeyCombination(Qt::CTRL | Qt::SHIFT , Qt::Key_H));
#else
    newManagedEditorAction(submenu, "nextchange", tr("Next Change"), "jumpChangePositionForward", Qt::CTRL | Qt::SHIFT | Qt::Key_H);
#endif
	submenu->addSeparator();
    newManagedAction(submenu, "markprev", tr("Previous mark"), "gotoMark", MAC_OR_DEFAULT(0, Qt::CTRL | Qt::Key_Up), "", QList<QVariant>() << true << -1); //, ":/images/errorprev.png");
    newManagedAction(submenu, "marknext", tr("Next mark"), "gotoMark", MAC_OR_DEFAULT(0, Qt::CTRL | Qt::Key_Down), "", QList<QVariant>() << false << -1); //, ":/images/errornext.png");
	submenu->addSeparator();
	if (cursorHistory) {
        cursorHistory->setBackAction(newManagedAction(submenu, "goback", tr("Go Back"), SLOT(goBack()), MAC_OR_DEFAULT(0, Qt::ALT | Qt::Key_Left), "back"));
        cursorHistory->setForwardAction(newManagedAction(submenu, "goforward", tr("Go Forward"), SLOT(goForward()), MAC_OR_DEFAULT(0, Qt::ALT | Qt::Key_Right), "forward"));
	}

	submenu = newManagedMenu(menu, "gotoBookmark", tr("Goto Bookmark"));
	QList<int> bookmarkIndicies = QList<int>() << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 0;
    foreach (int i, bookmarkIndicies) {
        QKeySequence shortcut;
#if (QT_VERSION>=QT_VERSION_CHECK(6,0,0))
        if (i != 0){
            shortcut = Qt::CTRL | static_cast<Qt::Key>(static_cast<int>(Qt::Key_0) + i);
        }
#else
        if (i != 0){
            shortcut = Qt::CTRL + Qt::Key_0 + i;
        }
#endif
        newManagedEditorAction(submenu, QString("bookmark%1").arg(i), tr("Bookmark %1").arg(i), "jumpToBookmark", shortcut, "", QList<QVariant>() << i);
    }


	submenu = newManagedMenu(menu, "toggleBookmark", tr("Toggle Bookmark"));

#if (QT_VERSION>=QT_VERSION_CHECK(6,0,0))
    newManagedEditorAction(submenu, QString("bookmark"), tr("Unnamed Bookmark"), "toggleBookmark", QKeyCombination(Qt::CTRL | Qt::SHIFT , Qt::Key_B), "", QList<QVariant>() << -1);
        foreach (int i, bookmarkIndicies)
            newManagedEditorAction(submenu, QString("bookmark%1").arg(i), tr("Bookmark %1").arg(i), "toggleBookmark", QKeyCombination(Qt::CTRL | Qt::SHIFT , static_cast<Qt::Key>(static_cast<int>(Qt::Key_0) + i)), "", QList<QVariant>() << i);
#else
    newManagedEditorAction(submenu, QString("bookmark"), tr("Unnamed Bookmark"), "toggleBookmark", Qt::CTRL | Qt::SHIFT | Qt::Key_B, "", QList<QVariant>() << -1);
    foreach (int i, bookmarkIndicies)
        newManagedEditorAction(submenu, QString("bookmark%1").arg(i), tr("Bookmark %1").arg(i), "toggleBookmark", Qt::CTRL + Qt::SHIFT + Qt::Key_0 + i, "", QList<QVariant>() << i);
#endif


	menu->addSeparator();
	submenu = newManagedMenu(menu, "lineend", tr("Line Ending"));
	QActionGroup *lineEndingGroup = new QActionGroup(this);
	QAction *act = newManagedAction(submenu, "crlf", tr("DOS/Windows (CR LF)"), SLOT(editChangeLineEnding()));
	act->setData(QDocument::Windows);
	act->setCheckable(true);
	lineEndingGroup->addAction(act);
	act = newManagedAction(submenu, "lf", tr("Unix (LF)"), SLOT(editChangeLineEnding()));
	act->setData(QDocument::Unix);
	act->setCheckable(true);
	lineEndingGroup->addAction(act);
	act = newManagedAction(submenu, "cr", tr("Old Mac (CR)"), SLOT(editChangeLineEnding()));
	act->setData(QDocument::Mac);
	act->setCheckable(true);
	lineEndingGroup->addAction(act);


	newManagedAction(menu, "encoding", tr("Setup Encoding..."), SLOT(editSetupEncoding()))->setMenuRole(QAction::NoRole); // with the default "QAction::TextHeuristicRole" this was interperted as Preferences on OSX
#if (QT_VERSION>=QT_VERSION_CHECK(6,0,0))
    newManagedAction(menu, "unicodeChar", tr("Insert Unicode Character..."), SLOT(editInsertUnicode()), filterLocaleShortcut(QKeyCombination(Qt::ALT | Qt::CTRL , Qt::Key_U)));
#else
    newManagedAction(menu, "unicodeChar", tr("Insert Unicode Character..."), SLOT(editInsertUnicode()), filterLocaleShortcut(Qt::ALT | Qt::CTRL | Qt::Key_U));
#endif



	//Edit 2 (for LaTeX related things)
	menu = newManagedMenu("main/edit2", tr("&Idefix"));
    newManagedAction(menu, "eraseWord", tr("Erase &Word/Cmd/Env"), SLOT(editEraseWordCmdEnv()), MAC_OR_DEFAULT(0, Qt::ALT | Qt::Key_Delete));

	menu->addSeparator();
    newManagedAction(menu, "pasteAsLatex", tr("Pas&te as LaTeX"), SLOT(editPasteLatex()), QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_V), "editpaste");
	newManagedAction(menu, "convertTo", tr("Co&nvert to LaTeX"), SLOT(convertToLatex()));

	menu->addSeparator();
    newManagedAction(menu, "previewLatex", tr("Pre&view Selection/Parentheses"), SLOT(previewLatex()), Qt::ALT | Qt::Key_P);
	newManagedAction(menu, "removePreviewLatex", tr("C&lear Inline Preview"), SLOT(clearPreview()));

	submenu = newManagedMenu(menu, "previewMode", tr("Preview Dis&play Mode"));
	QActionGroup *previewModeGroup = new QActionGroup(this);
	act = newManagedAction(submenu, "PM_TOOLTIP_AS_FALLBACK", tr("Show preview as tooltip if panel is hidden"), SLOT(setPreviewMode()));
	act->setData(ConfigManager::PM_TOOLTIP_AS_FALLBACK);
	act->setCheckable(true);
	previewModeGroup->addAction(act);
	act = newManagedAction(submenu, "PM_PANEL", tr("Always show preview in preview panel"), SLOT(setPreviewMode()));
	act->setData(ConfigManager::PM_PANEL);
	act->setCheckable(true);
	previewModeGroup->addAction(act);
	act = newManagedAction(submenu, "PM_TOOLTIP", tr("Always show preview as tool tip"), SLOT(setPreviewMode()));
	act->setData(ConfigManager::PM_TOOLTIP);
	act->setCheckable(true);
	previewModeGroup->addAction(act);
	act = newManagedAction(submenu, "PM_BOTH", tr("Always show both"), SLOT(setPreviewMode()));
	act->setData(ConfigManager::PM_BOTH);
	act->setCheckable(true);
	previewModeGroup->addAction(act);
	act = newManagedAction(submenu, "PM_INLINE", tr("Inline"), SLOT(setPreviewMode()));
	act->setData(ConfigManager::PM_INLINE);
	act->setCheckable(true);
	previewModeGroup->addAction(act);
	// poppler preview
#ifndef NO_POPPLER_PREVIEW
	act = newManagedAction(submenu, "PM_EMBEDDED", tr("Show in embedded viewer"), SLOT(setPreviewMode()));
	act->setData(ConfigManager::PM_EMBEDDED);
	act->setCheckable(true);
	previewModeGroup->addAction(act);
#endif

	setCheckedPreviewModeAction();

	menu->addSeparator();
    newManagedEditorAction(menu, "togglecomment", tr("Toggle &Comment"), "toggleCommentSelection", Qt::CTRL | Qt::Key_T);
	newManagedEditorAction(menu, "comment", tr("&Comment"), "commentSelection");
    newManagedEditorAction(menu, "uncomment", tr("&Uncomment"), "uncommentSelection", Qt::CTRL | Qt::Key_U);
	newManagedEditorAction(menu, "indent", tr("&Indent"), "indentSelection");
	newManagedEditorAction(menu, "unindent", tr("Unin&dent"), "unindentSelection");
	newManagedAction(menu, "hardbreak", tr("Hard Line &Break..."), SLOT(editHardLineBreak()));
	newManagedAction(menu, "hardbreakrepeat", tr("R&epeat Hard Line Break"), SLOT(editHardLineBreakRepeat()));

	menu->addSeparator();
	submenu = newManagedMenu(menu, "goto", tr("&Go to"));

    newManagedAction(submenu, "errorprev", tr("Previous Error"), "gotoNearLogEntry", MAC_OR_DEFAULT(0, QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Up)), "errorprev", QList<QVariant>() << LT_ERROR << true << tr("No LaTeX errors detected !"));
    newManagedAction(submenu, "errornext", tr("Next Error"), "gotoNearLogEntry", MAC_OR_DEFAULT(0, QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Down)), "errornext", QList<QVariant>() << LT_ERROR << false << tr("No LaTeX errors detected !"));
	newManagedAction(submenu, "warningprev", tr("Previous Warning"), "gotoNearLogEntry", QKeySequence(), "", QList<QVariant>() << LT_WARNING << true << tr("No LaTeX warnings detected !")); //, ":/images/errorprev.png");
	newManagedAction(submenu, "warningnext", tr("Next Warning"), "gotoNearLogEntry", QKeySequence(), "", QList<QVariant>() << LT_WARNING << false << tr("No LaTeX warnings detected !")); //, ":/images/errornext.png");
    newManagedAction(submenu, "badboxprev", tr("Previous Bad Box"), "gotoNearLogEntry", MAC_OR_DEFAULT(0, QKeySequence(Qt::SHIFT | Qt::ALT | Qt::Key_Up)), "", QList<QVariant>() << LT_BADBOX << true << tr("No bad boxes detected !")); //, ":/images/errorprev.png");
    newManagedAction(submenu, "badboxnext", tr("Next Bad Box"), "gotoNearLogEntry", MAC_OR_DEFAULT(0, QKeySequence(Qt::SHIFT | Qt::ALT | Qt::Key_Down)), "", QList<QVariant>() << LT_BADBOX << false << tr("No bad boxes detected !")); //, ":/images/errornext.png");

	submenu->addSeparator();
    newManagedAction(submenu, "definition", tr("Definition"), SLOT(editGotoDefinition()), filterLocaleShortcut(QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_F)));

	menu->addSeparator();
	newManagedAction(menu, "generateMirror", tr("Re&name Environment"), SLOT(generateMirror()));

	submenu = newManagedMenu(menu, "parens", tr("Parenthesis"));
#if (QT_VERSION>=QT_VERSION_CHECK(6,0,0))
    newManagedAction(submenu, "jump", tr("Jump to Match"), SLOT(jumpToBracket()), QKeySequence(QKeyCombination(Qt::SHIFT | Qt::CTRL , Qt::Key_P), QKeyCombination(Qt::Key_J)));
    newManagedAction(submenu, "selectBracketInner", tr("Select Inner"), SLOT(selectBracket()), QKeySequence(QKeyCombination(Qt::SHIFT | Qt::CTRL , Qt::Key_P), QKeyCombination(Qt::Key_I)))->setProperty("type", "inner");
    newManagedAction(submenu, "selectBracketOuter", tr("Select Outer"), SLOT(selectBracket()), QKeySequence(QKeyCombination(Qt::SHIFT | Qt::CTRL , Qt::Key_P), QKeyCombination(Qt::Key_O)))->setProperty("type", "outer");
    newManagedAction(submenu, "selectBracketCommand", tr("Select Command"), SLOT(selectBracket()), QKeySequence(QKeyCombination(Qt::SHIFT | Qt::CTRL , Qt::Key_P), QKeyCombination(Qt::Key_C)))->setProperty("type", "command");
    newManagedAction(submenu, "selectBracketLine", tr("Select Line"), SLOT(selectBracket()), QKeySequence(QKeyCombination(Qt::SHIFT | Qt::CTRL , Qt::Key_P), QKeyCombination(Qt::Key_L)))->setProperty("type", "line");
    newManagedAction(submenu, "generateInvertedBracketMirror", tr("Select Inverting"), SLOT(generateBracketInverterMirror()), QKeySequence(QKeyCombination(Qt::SHIFT | Qt::CTRL , Qt::Key_P), QKeyCombination(Qt::Key_S)));

    submenu->addSeparator();
    newManagedAction(submenu, "findMissingBracket", tr("Find Mismatch"), SLOT(findMissingBracket()), QKeySequence(QKeyCombination(Qt::SHIFT | Qt::CTRL , Qt::Key_P), QKeyCombination(Qt::Key_M)));
#else
    newManagedAction(submenu, "jump", tr("Jump to Match"), SLOT(jumpToBracket()), QKeySequence(Qt::SHIFT | Qt::CTRL | Qt::Key_P, Qt::Key_J));
    newManagedAction(submenu, "selectBracketInner", tr("Select Inner"), SLOT(selectBracket()), QKeySequence(Qt::SHIFT | Qt::CTRL | Qt::Key_P, Qt::Key_I))->setProperty("type", "inner");
    newManagedAction(submenu, "selectBracketOuter", tr("Select Outer"), SLOT(selectBracket()), QKeySequence(Qt::SHIFT | Qt::CTRL | Qt::Key_P, Qt::Key_O))->setProperty("type", "outer");
    newManagedAction(submenu, "selectBracketCommand", tr("Select Command"), SLOT(selectBracket()), QKeySequence(Qt::SHIFT | Qt::CTRL | Qt::Key_P, Qt::Key_C))->setProperty("type", "command");
    newManagedAction(submenu, "selectBracketLine", tr("Select Line"), SLOT(selectBracket()), QKeySequence(Qt::SHIFT | Qt::CTRL |Qt::Key_P, Qt::Key_L))->setProperty("type", "line");
    newManagedAction(submenu, "generateInvertedBracketMirror", tr("Select Inverting"), SLOT(generateBracketInverterMirror()), QKeySequence(QKeySequence(Qt::SHIFT | Qt::CTRL | Qt::Key_P, Qt::Key_S)));

	submenu->addSeparator();
    newManagedAction(submenu, "findMissingBracket", tr("Find Mismatch"), SLOT(findMissingBracket()), QKeySequence(Qt::SHIFT | Qt::CTRL | Qt::Key_P, Qt::Key_M));
#endif

	submenu = newManagedMenu(menu, "complete", tr("Complete"));
    newManagedAction(submenu, "normal", tr("Normal"), SLOT(normalCompletion()), MAC_OR_DEFAULT(QKeySequence(Qt::META | Qt::Key_Space), QKeySequence(Qt::CTRL | Qt::Key_Space)));
    newManagedAction(submenu, "environment", tr("\\begin{ Completion"), SLOT(insertEnvironmentCompletion()), QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_Space));
    newManagedAction(submenu, "text", tr("Normal Text"), SLOT(insertTextCompletion()), QKeySequence(Qt::SHIFT | Qt::ALT | Qt::Key_Space));
    newManagedAction(submenu, "closeEnvironment", tr("Close latest open environment"), SLOT(closeEnvironment()), QKeySequence(Qt::ALT | Qt::Key_Return));

	menu->addSeparator();
    newManagedAction(menu, "updateTOC", tr("update TOC"), SLOT(updateTOCs()));
	newManagedAction(menu, "reparse", tr("Refresh Structure"), SLOT(updateStructure()));
	act = newManagedAction(menu, "refreshQNFA", tr("Refresh Language Model"), SLOT(updateTexQNFA()));
	act->setStatusTip(tr("Force an update of the dynamic language model used for highlighting and folding. Likely, you do not need to call this because updates are usually automatic."));
    newManagedAction(menu, "removePlaceHolders", tr("Remove Placeholders"), SLOT(editRemovePlaceHolders()), QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_K));
	newManagedAction(menu, "removeCurrentPlaceHolder", tr("Remove Current Placeholder"), SLOT(editRemoveCurrentPlaceHolder()));

	//tools


	menu = newManagedMenu("main/tools", tr("&Tools"));
	menu->setProperty("defaultSlot", QByteArray(SLOT(commandFromAction())));
    newManagedAction(menu, "quickbuild", tr("&Build && View"), SLOT(commandFromAction()), (QList<QKeySequence>() << Qt::Key_F5 << Qt::Key_F1), "build")->setData(BuildManager::CMD_QUICK);
    newManagedAction(menu, "compile", tr("&Compile"), SLOT(commandFromAction()), Qt::Key_F6, "compile")->setData(BuildManager::CMD_COMPILE);
    QAction *stopAction = new QAction(getRealIcon("stop"), tr("Stop Compile"), menu);
    connect(stopAction, SIGNAL(triggered()), &buildManager, SLOT(killCurrentProcess()));
    newManagedAction(menu, "stopcompile", stopAction)->setEnabled(false);
    connect(&buildManager,SIGNAL(buildRunning(bool)),this,SLOT(setBuildButtonsDisabled(bool)));
	newManagedAction(menu, "view", tr("&View"), SLOT(commandFromAction()), Qt::Key_F7, "viewer")->setData(BuildManager::CMD_VIEW);
	newManagedAction(menu, "bibtex", tr("&Bibliography"), SLOT(commandFromAction()), Qt::Key_F8)->setData(BuildManager::CMD_BIBLIOGRAPHY);
	newManagedAction(menu, "glossary", tr("&Glossary"), SLOT(commandFromAction()), Qt::Key_F9)->setData(BuildManager::CMD_GLOSSARY);
	newManagedAction(menu, "index", tr("&Index"), SLOT(commandFromAction()))->setData(BuildManager::CMD_INDEX);

	menu->addSeparator();
	submenu = newManagedMenu(menu, "commands", tr("&Commands", "menu"));
	newManagedAction(submenu, "latexmk", tr("&Latexmk"), SLOT(commandFromAction()))->setData(BuildManager::CMD_LATEXMK);
	submenu->addSeparator();
	newManagedAction(submenu, "latex", tr("&LaTeX"), SLOT(commandFromAction()), QKeySequence(), "compile-latex")->setData(BuildManager::CMD_LATEX);
	newManagedAction(submenu, "pdflatex", tr("&PDFLaTeX"), SLOT(commandFromAction()), QKeySequence(), "compile-pdf")->setData(BuildManager::CMD_PDFLATEX);
	newManagedAction(submenu, "xelatex", "&XeLaTeX", SLOT(commandFromAction()), QKeySequence(), "compile-xelatex")->setData(BuildManager::CMD_XELATEX);
	newManagedAction(submenu, "lualatex", "L&uaLaTeX", SLOT(commandFromAction()), QKeySequence(), "compile-lua")->setData(BuildManager::CMD_LUALATEX);
	submenu->addSeparator();
	newManagedAction(submenu, "dvi2ps", tr("DVI->PS"), SLOT(commandFromAction()), QKeySequence(), "convert-dvips")->setData(BuildManager::CMD_DVIPS);
	newManagedAction(submenu, "ps2pdf", tr("P&S->PDF"), SLOT(commandFromAction()), QKeySequence(), "convert-pspdf")->setData(BuildManager::CMD_PS2PDF);
	newManagedAction(submenu, "dvipdf", tr("DV&I->PDF"), SLOT(commandFromAction()), QKeySequence(), "convert-dvipdf")->setData(BuildManager::CMD_DVIPDF);
	submenu->addSeparator();
	newManagedAction(submenu, "viewdvi", tr("View &DVI"), SLOT(commandFromAction()), QKeySequence(), "view-doc-dvi")->setData(BuildManager::CMD_VIEW_DVI);
	newManagedAction(submenu, "viewps", tr("Vie&w PS"), SLOT(commandFromAction()), QKeySequence(), "view-doc-ps")->setData(BuildManager::CMD_VIEW_PS);
	newManagedAction(submenu, "viewpdf", tr("View PD&F"), SLOT(commandFromAction()), QKeySequence(), "view-doc-pdf")->setData(BuildManager::CMD_VIEW_PDF);
	submenu->addSeparator();
	newManagedAction(submenu, "bibtex", tr("&Bibtex"), SLOT(commandFromAction()))->setData(BuildManager::CMD_BIBTEX);
	newManagedAction(submenu, "bibtex8", tr("&Bibtex 8-Bit"), SLOT(commandFromAction()))->setData(BuildManager::CMD_BIBTEX8);
	newManagedAction(submenu, "biber", tr("Bibe&r"), SLOT(commandFromAction()))->setData(BuildManager::CMD_BIBER);
	submenu->addSeparator();
	newManagedAction(submenu, "makeindex", tr("&MakeIndex"), SLOT(commandFromAction()))->setData(BuildManager::CMD_MAKEINDEX);
	newManagedAction(submenu, "texindy", tr("&TexIndy"), SLOT(commandFromAction()), QKeySequence())->setData(BuildManager::CMD_TEXINDY);
	newManagedAction(submenu, "xindex", tr("&Xindex"), SLOT(commandFromAction()), QKeySequence())->setData(BuildManager::CMD_XINDEX);
	newManagedAction(submenu, "makeglossaries", tr("&Makeglossaries"), SLOT(commandFromAction()), QKeySequence())->setData(BuildManager::CMD_MAKEGLOSSARIES);
	submenu->addSeparator();
	newManagedAction(submenu, "metapost", tr("&MetaPost"), SLOT(commandFromAction()))->setData(BuildManager::CMD_METAPOST);
	newManagedAction(submenu, "asymptote", tr("&Asymptote"), SLOT(commandFromAction()))->setData(BuildManager::CMD_ASY);

	submenu = newManagedMenu(menu, "user", tr("&User", "menu"));
	updateUserToolMenu();
	menu->addSeparator();
	newManagedAction(menu, "clean", tr("Cle&an Auxiliary Files..."), SLOT(cleanAll()));
	newManagedAction(menu, "terminal", tr("Open External &Terminal"), SLOT(openExternalTerminal()));
	menu->addSeparator();
	newManagedAction(menu, "viewlog", tr("View &Log"), SLOT(commandFromAction()), QKeySequence(), "viewlog")->setData(BuildManager::CMD_VIEW_LOG);
	act = newManagedAction(menu, "logmarkers", tr("Show Log Markers"), nullptr, 0, "logmarkers");
	act->setCheckable(true);
	connect(act, SIGNAL(triggered(bool)), SLOT(setLogMarksVisible(bool)));
	menu->addSeparator();
	newManagedAction(menu, "htmlexport", tr("C&onvert to Html..."), SLOT(webPublish()));
	newManagedAction(menu, "htmlsourceexport", tr("C&onvert Source to Html..."), SLOT(webPublishSource()));
	menu->addSeparator();
	newManagedAction(menu, "textexport", tr("Convert to Abridged Plaintext"), SLOT(convertToPlainText()));
	newManagedAction(menu, "analysetext", tr("A&nalyse Text..."), SLOT(analyseText()));
	newManagedAction(menu, "generaterandomtext", tr("Generate &Random Text..."), SLOT(generateRandomText()));
	menu->addSeparator();
    newManagedAction(menu, "spelling", tr("Check Spelling..."), SLOT(editSpell()), MAC_OR_DEFAULT(Qt::CTRL | Qt::SHIFT | Qt::Key_F7, Qt::CTRL | Qt::Key_Colon));
    newManagedAction(menu, "thesaurus", tr("Thesaurus..."), SLOT(editThesaurus()), Qt::CTRL | Qt::SHIFT | Qt::Key_F8);
	newManagedAction(menu, "wordrepetions", tr("Find Word Repetitions..."), SLOT(findWordRepetions()));

	//  Latex/Math external
	configManager.loadManagedMenus(":/uiconfig.xml");
	// add some additional items
	menu = newManagedMenu("main/latex", tr("&LaTeX"));
	menu->setProperty("defaultSlot", QByteArray(SLOT(insertFromAction())));
    newManagedAction(menu, "insertrefnextlabel", tr("Insert \\ref to Next Label"), SLOT(editInsertRefToNextLabel()), filterLocaleShortcut(Qt::ALT | Qt::CTRL | Qt::Key_R));
	newManagedAction(menu, "insertrefprevlabel", tr("Insert \\ref to Previous Label"), SLOT(editInsertRefToPrevLabel()));
	submenu = newManagedMenu(menu, "tabularmanipulation", tr("Manipulate Tables", "table"));
	newManagedAction(submenu, "addRow", tr("Add Row", "table"), SLOT(addRowCB()), QKeySequence(), "addRow");
	newManagedAction(submenu, "addColumn", tr("Add Column", "table"), SLOT(addColumnCB()), QKeySequence(), "addCol");
	newManagedAction(submenu, "removeRow", tr("Remove Row", "table"), SLOT(removeRowCB()), QKeySequence(), "remRow");
	newManagedAction(submenu, "removeColumn", tr("Remove Column", "table"), SLOT(removeColumnCB()), QKeySequence(), "remCol");
	newManagedAction(submenu, "cutColumn", tr("Cut Column", "table"), SLOT(cutColumnCB()), QKeySequence(), "cutCol");
	newManagedAction(submenu, "pasteColumn", tr("Paste Column", "table"), SLOT(pasteColumnCB()), QKeySequence(), "pasteCol");
	newManagedAction(submenu, "addHLine", tr("Add \\hline", "table"), SLOT(addHLineCB()));
	newManagedAction(submenu, "remHLine", tr("Remove \\hline", "table"), SLOT(remHLineCB()));
	newManagedAction(submenu, "insertTableTemplate", tr("Remodel Table Using Template", "table"), SLOT(insertTableTemplate()));
	newManagedAction(submenu, "alignColumns", tr("Align Columns"), SLOT(alignTableCols()), QKeySequence(), "alignCols");
	submenu = newManagedMenu(menu, "magicComments", tr("Add magic comments ..."));
	newManagedAction(submenu, "addMagicRoot", tr("Insert root document name as TeX comment"), SLOT(addMagicRoot()));
	newManagedAction(submenu, "addMagicLang", tr("Insert language as TeX comment"), SLOT(insertSpellcheckMagicComment()));
	newManagedAction(submenu, "addMagicCoding", tr("Insert document coding as TeX comment"), SLOT(addMagicCoding()));
	newManagedAction(submenu, "addMagicProgram", tr("Insert program as TeX comment"), SLOT(addMagicProgram()));
	newManagedAction(submenu, "addMagicBibliography", tr("Insert bibliography tool as TeX comment"), SLOT(addMagicBibliography()));

	menu = newManagedMenu("main/math", tr("&Math"));
	menu->setProperty("defaultSlot", QByteArray(SLOT(insertFromAction())));
	//wizards

	menu = newManagedMenu("main/wizards", tr("&Wizards"));
	newManagedAction(menu, "start", tr("Quick &Start..."), SLOT(quickDocument()));
	newManagedAction(menu, "beamer", tr("Quick &Beamer Presentation..."), SLOT(quickBeamer()));
	newManagedAction(menu, "letter", tr("Quick &Letter..."), SLOT(quickLetter()));

	menu->addSeparator();
	newManagedAction(menu, "tabular", tr("Quick &Tabular..."), SLOT(quickTabular()));
	newManagedAction(menu, "tabbing", tr("Quick T&abbing..."), SLOT(quickTabbing()));
	newManagedAction(menu, "array", tr("Quick &Array..."), SLOT(quickArray()));
	newManagedAction(menu, "graphic", tr("Insert &Graphic..."), SLOT(quickGraphics()), QKeySequence(), "image");
#ifdef Q_OS_WIN
	newManagedAction(menu, "math", tr("Math Assistant..."), SLOT(quickMath()), QKeySequence(), "TexTablet");
#endif

	menu = newManagedMenu("main/bibliography", tr("&Bibliography"));
	if (!bibtexEntryActions) {
		bibtexEntryActions = new QActionGroup(this);
		foreach (const BibTeXType &bt, BibTeXDialog::getPossibleEntryTypes(BibTeXDialog::BIBTEX)) {
			QAction *act = newManagedAction(menu, "bibtex/" + bt.name.mid(1), bt.description, SLOT(insertBibEntryFromAction()));
			act->setData(bt.name);
			act->setActionGroup(bibtexEntryActions);
		}
	} else {
		foreach (const BibTeXType &bt, BibTeXDialog::getPossibleEntryTypes(BibTeXDialog::BIBTEX))
			newManagedAction(menu, "bibtex/" + bt.name.mid(1), bt.description, SLOT(insertBibEntryFromAction()))->setData(bt.name);
	}

	if (!biblatexEntryActions) {
		biblatexEntryActions = new QActionGroup(this);
		foreach (const BibTeXType &bt, BibTeXDialog::getPossibleEntryTypes(BibTeXDialog::BIBLATEX)) {
			QAction *act = newManagedAction(menu, "biblatex/" + bt.name.mid(1), bt.description, SLOT(insertBibEntryFromAction()));
			act->setData(bt.name);
			act->setActionGroup(biblatexEntryActions);
		}
	} else {
		foreach (const BibTeXType &bt, BibTeXDialog::getPossibleEntryTypes(BibTeXDialog::BIBLATEX))
			newManagedAction(menu, "biblatex/" + bt.name.mid(1), bt.description, SLOT(insertBibEntryFromAction()))->setData(bt.name);
	}
	menu->addSeparator();
	newManagedEditorAction(menu, "clean", tr("&Clean"), "cleanBib");
	menu->addSeparator();
	newManagedAction(menu, "dialog", tr("&Insert Bibliography Entry..."), SLOT(insertBibEntry()));
	menu->addSeparator();
	QMenu *bibTypeMenu = newManagedMenu(menu, "type", tr("Type"));
	if (!bibTypeActions) {
		bibTypeActions = new QActionGroup(this);
		bibTypeActions->setExclusive(true);
		act = newManagedAction(bibTypeMenu, "bibtex", tr("BibTeX"), SLOT(setBibTypeFromAction()));
		act->setData("bibtex");
		act->setCheckable(true);
		act->setChecked(true);
		bibTypeActions->addAction(act);
		act = newManagedAction(bibTypeMenu, "biblatex", tr("BibLaTeX"), SLOT(setBibTypeFromAction()));
		act->setData("biblatex");
		act->setCheckable(true);
		bibTypeActions->addAction(act);
	}
	act = newManagedAction(bibTypeMenu, "bibtex", tr("BibTeX"), SLOT(setBibTypeFromAction()));
	act = newManagedAction(bibTypeMenu, "biblatex", tr("BibLaTeX"), SLOT(setBibTypeFromAction()));
	act->trigger(); // initialize menu for specified type

	//  User
        newManagedMenu("main/macros", tr("Ma&cros"));
	updateUserMacros();
	scriptengine::macros = &configManager.completerConfig->userMacros;

	//---view---
	menu = newManagedMenu("main/view", tr("&View"));
    newManagedAction(menu, "prevdocument", tr("Previous Document"), SLOT(gotoPrevDocument()), QList<QKeySequence>() << QKeySequence(Qt::CTRL | Qt::Key_PageUp) << MAC_OR_DEFAULT(QKeySequence(Qt::META  | Qt::SHIFT | Qt::Key_Tab),QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Tab)));
    newManagedAction(menu, "nextdocument", tr("Next Document"), SLOT(gotoNextDocument()), QList<QKeySequence>() << QKeySequence(Qt::CTRL | Qt::Key_PageDown) << MAC_OR_DEFAULT(QKeySequence(Qt::META | Qt::Key_Tab),QKeySequence(Qt::CTRL | Qt::Key_Tab)));
	newManagedMenu(menu, "documents", tr("Open Documents"));
	newManagedAction(menu, "documentlist", tr("List Of Open Documents"), SLOT(viewDocumentList()));
	newManagedAction(menu, "documentlisthidden", tr("List Of Hidden Documents"), SLOT(viewDocumentListHidden()));

    newManagedAction(menu, "focuseditor", tr("Focus Editor"), SLOT(focusEditor()), QList<QKeySequence>() << QKeySequence(Qt::ALT | Qt::CTRL | Qt::Key_Left));
    newManagedAction(menu, "focusviewer", tr("Focus Viewer"), SLOT(focusViewer()), QList<QKeySequence>() << QKeySequence(Qt::ALT | Qt::CTRL | Qt::Key_Right));

	menu->addSeparator();
	submenu = newManagedMenu(menu, "show", tr("Show"));
	newManagedAction(submenu, "structureview", sidePanel->toggleViewAction());
	newManagedAction(submenu, "outputview", outputView->toggleViewAction());
	act = newManagedAction(submenu, "statusbar", tr("Statusbar"), SLOT(showStatusbar()));
	act->setCheckable(true);
	act->setChecked(configManager.getOption("View/ShowStatusbar").toBool());

	newManagedAction(menu, "enlargePDF", tr("Show embedded PDF large"), SLOT(enlargeEmbeddedPDFViewer()));
	newManagedAction(menu, "shrinkPDF", tr("Show embedded PDF small"), SLOT(shrinkEmbeddedPDFViewer()));

	newManagedAction(menu, "closeelement", tr("Close Element"), SLOT(viewCloseElement()), Qt::Key_Escape);

	menu->addSeparator();
	submenu = newManagedMenu(menu, "collapse", tr("Collapse"));
	newManagedEditorAction(submenu, "all", tr("Everything"), "foldEverything", 0, "", QList<QVariant>() << false);
	newManagedAction(submenu, "block", tr("Nearest Block"), SLOT(viewCollapseBlock()));
	for (int i = 1; i <= 4; i++)
		newManagedEditorAction(submenu, QString::number(i), tr("Level %1").arg(i), "foldLevel", 0, "", QList<QVariant>() << false << i);
	submenu = newManagedMenu(menu, "expand", tr("Expand"));
	newManagedEditorAction(submenu, "all", tr("Everything"), "foldEverything", 0, "", QList<QVariant>() << true);
	newManagedAction(submenu, "block", tr("Nearest Block"), SLOT(viewExpandBlock()));
	for (int i = 1; i <= 4; i++)
		newManagedEditorAction(submenu, QString::number(i), tr("Level %1").arg(i), "foldLevel", 0, "", QList<QVariant>() << true << i);

	submenu = newManagedMenu(menu, "grammar", tr("Grammar errors"));
	static bool showGrammarType[8] = {false};
	for (int i = 0; i < 8; i++) configManager.registerOption(QString("Grammar/Display Error %1").arg(i), &showGrammarType[i], true);
	newManagedAction(submenu, "0", tr("Word Repetition"), "toggleGrammar", 0, "", QList<QVariant>() << 0);
	newManagedAction(submenu, "1", tr("Long-range Word Repetition"), "toggleGrammar", 0, "", QList<QVariant>() << 1);
	newManagedAction(submenu, "2", tr("Bad words"), "toggleGrammar", 0, "", QList<QVariant>() << 2);
	newManagedAction(submenu, "3", tr("Grammar Mistake"), "toggleGrammar", 0, "", QList<QVariant>() << 3);
	for (int i = 4; i < 8; i++)
		newManagedAction(submenu, QString("%1").arg(i), tr("Grammar Mistake Special %1").arg(i - 3), "toggleGrammar", 0, "", QList<QVariant>() << i);
	for (int i = 0; i < submenu->actions().size(); i++)
        if (!submenu->actions().at(i)->isCheckable()) {
            submenu->actions().at(i)->setCheckable(true);
            configManager.linkOptionToObject(&showGrammarType[i], submenu->actions().at(i), LinkOptions());
            LatexEditorView::setGrammarOverlayDisabled(i, !submenu->actions().at(i)->isChecked());
		}

	menu->addSeparator();
	submenu = newManagedMenu(menu, "editorZoom", tr("Editor Zoom"));
    newManagedEditorAction(submenu, "zoomIn", tr("Zoom In"), "zoomIn", QKeySequence(Qt::CTRL | Qt::Key_Plus));
    newManagedEditorAction(submenu, "zoomOut", tr("Zoom Out"), "zoomOut", QKeySequence(Qt::CTRL | Qt::Key_Minus));
    newManagedEditorAction(submenu, "resetZoom", tr("Reset Zoom"), "resetZoom", QKeySequence(Qt::CTRL | Qt::Key_0));

	fullscreenModeAction = newManagedAction(menu, "fullscreenmode", tr("Full &Screen"), nullptr, QKeySequence::FullScreen);

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
	menu = newManagedMenu("main/options", tr("&Options"));
	newManagedAction(menu, "config", tr("&Configure TeXstudio..."), SLOT(generalOptions()), 0, "configure")->setMenuRole(QAction::PreferencesRole);

	menu->addSeparator();
	newManagedAction(menu, "loadProfile", tr("Load &Profile..."), SLOT(loadProfile()));
	newManagedAction(menu, "saveProfile", tr("S&ave Profile..."), SLOT(saveProfile()));
	newManagedAction(menu, "saveSettings", tr("Save &Current Settings", "menu"), SLOT(saveSettings()));
	newManagedAction(menu, "restoreDefaultSettings", tr("Restore &Default Settings..."), SLOT(restoreDefaultSettings()));
	menu->addSeparator();

	submenu = newManagedMenu(menu, "rootdoc", tr("Root Document", "menu"));
	actgroupRootDocMode = new QActionGroup(this);
	actgroupRootDocMode->setExclusive(true);
	actRootDocAutomatic = newManagedAction(submenu, "auto", tr("Detect &Automatically"), SLOT(setAutomaticRootDetection()));
	actRootDocAutomatic->setCheckable(true);
	actRootDocAutomatic->setChecked(true);
	actgroupRootDocMode->addAction(actRootDocAutomatic);
	actRootDocExplicit = newManagedAction(submenu, "currentExplicit", "Shows Current Explicit Root");
	actRootDocExplicit->setCheckable(true);
	actRootDocExplicit->setVisible(false);
	actgroupRootDocMode->addAction(actRootDocExplicit);
	actRootDocSetExplicit = newManagedAction(submenu, "setExplicit", tr("Set Current Document As Explicit Root"), SLOT(setCurrentDocAsExplicitRoot()));

	//---help---
	menu = newManagedMenu("main/help", tr("&Help"));
	newManagedAction(menu, "latexreference", tr("LaTeX Reference..."), SLOT(latexHelp()), 0, "help-contents");
	newManagedAction(menu, "usermanual", tr("User Manual..."), SLOT(userManualHelp()), 0, "help-contents");
	newManagedAction(menu, "texdocdialog", tr("Packages Help..."), SLOT(texdocHelp()));

	menu->addSeparator();
	newManagedAction(menu, "checkinstall", tr("Check LaTeX Installation"), SLOT(checkLatexInstall()));
	newManagedAction(menu, "checkcwls", tr("Check Active Completion Files"), SLOT(checkCWLs()));
    newManagedAction(menu, "checklt", tr("Check LanguageTool"), SLOT(checkLanguageTool()));
	newManagedAction(menu, "bugreport", tr("Bugs Report/Feature Request"), SLOT(openBugsAndFeatures()));
	newManagedAction(menu, "appinfo", tr("About TeXstudio..."), SLOT(helpAbout()), 0, APPICON)->setMenuRole(QAction::AboutRole);

	//additional elements for development


	//-----context menus-----
	if (LatexEditorView::getBaseActions().empty()) { //only called at first menu created
		QList<QAction *> baseContextActions;
		QAction *sep = new QAction(menu);
		sep->setSeparator(true);
        baseContextActions << getManagedActions(QStringList() << "cut" << "copy" << "paste", "main/edit/");
		baseContextActions << getManagedActions(QStringList() << "main/edit2/pasteAsLatex" << "main/edit2/convertTo" << "main/edit/selection/selectAll");
		baseContextActions << sep;
		baseContextActions << getManagedActions(QStringList() << "previewLatex" << "removePreviewLatex", "main/edit2/");
		LatexEditorView::setBaseActions(baseContextActions);
	}

	configManager.updateRecentFiles(true);

	configManager.modifyMenuContents();
	configManager.modifyManagedShortcuts();
}
/*! \brief slot for actions from Menu Preview Display Mode
*/
void Texstudio::setPreviewMode()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (act) {
		configManager.previewMode = act->data().value<ConfigManager::PreviewMode>();
	}
}
/*! \brief set action for Menu Preview Display Mode
*/
void Texstudio::setCheckedPreviewModeAction()
{
	ConfigManager::PreviewMode pm = configManager.previewMode;
	switch (pm) {
		case ConfigManager::PM_TOOLTIP_AS_FALLBACK:
			getManagedAction("main/edit2/previewMode/PM_TOOLTIP_AS_FALLBACK")->setChecked(true);
			break;
		case ConfigManager::PM_PANEL:
			getManagedAction("main/edit2/previewMode/PM_PANEL")->setChecked(true);
			break;
		case ConfigManager::PM_TOOLTIP:
			getManagedAction("main/edit2/previewMode/PM_TOOLTIP")->setChecked(true);
			break;
		case ConfigManager::PM_BOTH:
			getManagedAction("main/edit2/previewMode/PM_BOTH")->setChecked(true);
			break;
#ifndef NO_POPPLER_PREVIEW
		case ConfigManager::PM_EMBEDDED:
			getManagedAction("main/edit2/previewMode/PM_EMBEDDED")->setChecked(true);
			break;
#endif
		default:	// PM_INLINE
			getManagedAction("main/edit2/previewMode/PM_INLINE")->setChecked(true);
	}
}
/*! \brief set-up all tool-bars
 */
void Texstudio::setupToolBars()
{
	//This method will be called multiple times and must not create something if this something already exists

	configManager.watchedMenus.clear();

	//customizable toolbars
	//first apply custom icons
	QMap<QString, QVariant>::const_iterator i = configManager.replacedIconsOnMenus.constBegin();
	while (i != configManager.replacedIconsOnMenus.constEnd()) {
		QString id = i.key();
		QString iconFilename = configManager.parseDir(i.value().toString());
		QObject *obj = configManager.menuParent->findChild<QObject *>(id);
		QAction *act = qobject_cast<QAction *>(obj);
		if (act && !iconFilename.isEmpty()) act->setIcon(QIcon(iconFilename));
		++i;
	}
	//setup customizable toolbars
	for (int i = 0; i < configManager.managedToolBars.size(); i++) {
		ManagedToolBar &mtb = configManager.managedToolBars[i];
		if (!mtb.toolbar) { //create actual toolbar on first call
			if (mtb.name == "Central") mtb.toolbar = centralToolBar;
			else mtb.toolbar = addToolBar(tr(qPrintable(mtb.name)));
			mtb.toolbar->setObjectName(mtb.name);
			addAction(mtb.toolbar->toggleViewAction());
			if (mtb.name == "Spelling") addToolBarBreak();
		} else mtb.toolbar->clear();
		foreach (const QString &actionName, mtb.actualActions) {
			if (actionName == "separator") mtb.toolbar->addSeparator(); //Case 1: Separator
			else if (actionName.startsWith("tags/")) {
				//Case 2: One of the xml tag widgets mapped on a toolbutton
				int tagCategorySep = actionName.indexOf("/", 5);
				XmlTagsListWidget *tagsWidget = findChild<XmlTagsListWidget *>(actionName.left(tagCategorySep));
				if (!tagsWidget) continue;
				if (!tagsWidget->isPopulated())
					tagsWidget->populate();
				QStringList list = tagsWidget->tagsTxtFromCategory(actionName.mid(tagCategorySep + 1));
				if (list.isEmpty()) continue;
				QToolButton *combo = UtilsUi::createComboToolButton(mtb.toolbar, list, QStringList(), QList<QIcon>(), 0, this, SLOT(insertXmlTagFromToolButtonAction()));
				combo->setProperty("tagsID", actionName);
				mtb.toolbar->addWidget(combo);
			} else {
				QObject *obj = configManager.menuParent->findChild<QObject *>(actionName);
				QAction *act = qobject_cast<QAction *>(obj);
				if (act) {
					//Case 3: A normal QAction
					if (act->icon().isNull())
						act->setIcon(QIcon(APPICON));
					UtilsUi::updateToolTipWithShortcut(act, configManager.showShortcutsInTooltips);
					mtb.toolbar->addAction(act);
				} else {
					QMenu *menu = qobject_cast<QMenu *>(obj);
					if (!menu) {
						qWarning("Unknown toolbar command %s", qPrintable(actionName));
						continue;
					}
					//Case 4: A submenu mapped on a toolbutton
					configManager.watchedMenus << actionName;
					QStringList list;
					QStringList infos;
					QList<QIcon> icons;
					foreach (const QAction *act, menu->actions())
						if (!act->isSeparator()) {
							list.append(act->text());
							infos.append(act->toolTip());
							icons.append(act->icon());
						}
						else {
							list.append("");
							infos.append("");
							icons.append(QIcon());
						}
					//TODO: Is the callToolButtonAction()-slot really needed? Can't we just add the menu itself as the menu of the qtoolbutton, without creating a copy? (should be much faster)
					QToolButton *combo = UtilsUi::createComboToolButton(mtb.toolbar, list, infos, icons, 0, this, SLOT(callToolButtonAction()));
					combo->setProperty("menuID", actionName);
					mtb.toolbar->addWidget(combo);
				}
			}
		}
		if (mtb.actualActions.empty()) mtb.toolbar->setVisible(false);
	}
}

void Texstudio::updateAvailableLanguages()
{
	delete spellLanguageActions;

	spellLanguageActions = new QActionGroup(statusTbLanguage);
	spellLanguageActions->setExclusive(true);

    bool reduceDictDisplay=spellerManager.availableDicts().size()>20;
    bool hiddenEntries=false;
    if(!configManager.previouslyUsedDictionaries.contains(spellerManager.defaultSpellerName())){
        configManager.previouslyUsedDictionaries.append(spellerManager.defaultSpellerName());
    }

    foreach (const QString &s, spellerManager.availableDicts()) {
        QAction *act = new QAction(spellLanguageActions);
        act->setText(spellerManager.prettyName(s));
        act->setData(QVariant(s));
        act->setCheckable(true);
        if(reduceDictDisplay && !configManager.previouslyUsedDictionaries.contains(s) && (s != "<none>")){
            act->setVisible(false);
            hiddenEntries=true;
        }
        connect(act, SIGNAL(triggered()), this, SLOT(changeEditorSpeller()));
    }
    if(hiddenEntries){
        QAction *act = new QAction(spellLanguageActions);
        act->setText(tr("show more entries ..."));
        act->setData(QVariant(true));
        connect(act, SIGNAL(triggered()), this, SLOT(showMoreDictionaries()));
    }

	QAction *act = new QAction(spellLanguageActions);
	act->setSeparator(true);
	act = new QAction(spellLanguageActions);
	act->setText(tr("Default") + QString(": %1").arg(spellerManager.prettyName(spellerManager.defaultSpellerName())));
	act->setData(QVariant("<default>"));
	connect(act, SIGNAL(triggered()), this, SLOT(changeEditorSpeller()));
	act->setCheckable(true);
	act->setChecked(true);

	act = new QAction(spellLanguageActions);
	act->setSeparator(true);
	act = new QAction(spellLanguageActions);
	act->setText(tr("Insert language as TeX comment"));
	connect(act, SIGNAL(triggered()), this, SLOT(insertSpellcheckMagicComment()));

	statusTbLanguage->addActions(spellLanguageActions->actions());

	if (currentEditorView()) {
		editorSpellerChanged(currentEditorView()->getSpeller());
	} else {
		editorSpellerChanged("<default>");
	}
}

void Texstudio::updateLanguageToolStatus()
{
    // adapt icon size to dpi
    double dpi=QGuiApplication::primaryScreen()->logicalDotsPerInch();
    double scale=dpi/96;

    int iconWidth=qRound(configManager.guiSecondaryToolbarIconSize*scale);

	QIcon icon = getRealIconCached("languagetool");
    QSize iconSize = QSize(iconWidth, iconWidth);
	switch (grammarCheck->languageToolStatus()) {
		case GrammarCheck::LTS_Working:
			statusLabelLanguageTool->setPixmap(icon.pixmap(iconSize));
			statusLabelLanguageTool->setToolTip(QString(tr("Connected to LanguageTool at %1")).arg(grammarCheck->serverUrl()));
			break;
		case GrammarCheck::LTS_Error:
			statusLabelLanguageTool->setPixmap(icon.pixmap(iconSize, QIcon::Disabled));
			statusLabelLanguageTool->setToolTip(QString(tr("No LanguageTool server found at %1")).arg(grammarCheck->serverUrl()));
			break;
		case GrammarCheck::LTS_Unknown:
			statusLabelLanguageTool->setPixmap(icon.pixmap(iconSize, QIcon::Disabled));
			statusLabelLanguageTool->setToolTip(tr("LanguageTool status unknown"));
	}
    if (!configManager.editorConfig->realtimeChecking || !configManager.editorConfig->inlineGrammarChecking) {
        statusLabelLanguageTool->setPixmap(icon.pixmap(iconSize, QIcon::Disabled));
        statusLabelLanguageTool->setToolTip(tr("Inline grammar checking disabled by user!"));
    }
}

/*! \brief set-up status bar
 */
void Texstudio::createStatusBar()
{
	QStatusBar *status = statusBar();
	status->setContextMenuPolicy(Qt::PreventContextMenu);
	status->setVisible(configManager.getOption("View/ShowStatusbar").toBool());

    // adapt icon size to dpi
    double dpi=QGuiApplication::primaryScreen()->logicalDotsPerInch();
    double scale=dpi/96;

    int iconWidth=qRound(configManager.guiSecondaryToolbarIconSize*scale);

    QSize iconSize = QSize(iconWidth, iconWidth);
	QAction *act;
	QToolButton *tb;
	act = getManagedAction("main/view/show/structureview");
	if (act) {
		tb = new QToolButton(status);
		tb->setCheckable(true);
		tb->setChecked(act->isChecked());
		tb->setAutoRaise(true);
		tb->setIcon(act->icon());
		tb->setIconSize(iconSize);
		tb->setToolTip(act->toolTip());
        tb->setObjectName("structureViewToggle");
		connect(tb, SIGNAL(clicked()), act, SLOT(trigger()));
		connect(act, SIGNAL(toggled(bool)), tb, SLOT(setChecked(bool)));
		status->addPermanentWidget(tb, 0);
	}
	act = getManagedAction("main/view/show/outputview");
	if (act) {
		tb = new QToolButton(status);
		tb->setCheckable(true);
		tb->setChecked(act->isChecked());
		tb->setAutoRaise(true);
		tb->setIcon(act->icon());
		tb->setIconSize(iconSize);
		tb->setToolTip(act->toolTip());
        tb->setObjectName("outputViewToggle");
		connect(tb, SIGNAL(clicked()), act, SLOT(trigger()));
		connect(act, SIGNAL(toggled(bool)), tb, SLOT(setChecked(bool)));
		status->addPermanentWidget(tb, 0);
	}

	// spacer eating up all the space between "left" and "right" permanent widgets.
	QLabel *messageArea = new QLabel(status);
	connect(status, SIGNAL(messageChanged(QString)), messageArea, SLOT(setText(QString)));
	status->addPermanentWidget(messageArea, 1);

	// LanguageTool
	connect(grammarCheck, SIGNAL(languageToolStatusChanged()), this, SLOT(updateLanguageToolStatus()));
	statusLabelLanguageTool = new QLabel();
	updateLanguageToolStatus();
	status->addPermanentWidget(statusLabelLanguageTool);

	// language
	statusTbLanguage = new QToolButton(status);
	statusTbLanguage->setToolTip(tr("Language"));
	statusTbLanguage->setPopupMode(QToolButton::InstantPopup);
	statusTbLanguage->setAutoRaise(true);
	statusTbLanguage->setMinimumWidth(UtilsUi::getFmWidth(status->fontMetrics(), "OOOOOOO"));
	connect(&spellerManager, SIGNAL(dictPathChanged()), this, SLOT(updateAvailableLanguages()));
	connect(&spellerManager, SIGNAL(defaultSpellerChanged()), this, SLOT(updateAvailableLanguages()));
	updateAvailableLanguages();
	statusTbLanguage->setText(spellerManager.defaultSpellerName());
	status->addPermanentWidget(statusTbLanguage, 0);

	// encoding
	statusTbEncoding = new QToolButton(status);
	statusTbEncoding->setToolTip(tr("Encoding"));
	statusTbEncoding->setText(tr("Encoding") + "  ");
	statusTbEncoding->setPopupMode(QToolButton::InstantPopup);
	statusTbEncoding->setAutoRaise(true);
	statusTbEncoding->setMinimumWidth(UtilsUi::getFmWidth(status->fontMetrics(), "OOOOO"));

	QSet<int> encodingMibs;
	foreach (const QString &s, configManager.commonEncodings) {
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

	status->addPermanentWidget(statusTbEncoding, 0);


	statusLabelMode = new QLabel(status);
	statusLabelProcess = new QLabel(status);
	status->addPermanentWidget(statusLabelProcess, 0);
	status->addPermanentWidget(statusLabelMode, 0);
	for (int i = 1; i <= 3; i++) {
		QPushButton *pb = new QPushButton(getRealIcon(QString("bookmark%1").arg(i)), "", status);
		pb->setIconSize(iconSize);
		pb->setToolTip(tr("Go to bookmark") + QString(" %1").arg(i));
		connect(pb, SIGNAL(clicked()), getManagedAction(QString("main/edit/gotoBookmark/bookmark%1").arg(i)), SIGNAL(triggered()));
		pb->setFlat(true);
		status->addPermanentWidget(pb, 0);
	}
}

void Texstudio::updateCaption()
{
	if (!currentEditorView()) documents.currentDocument = nullptr;
	else {
		documents.currentDocument = currentEditorView()->document;
	}
	if (completer && completer->isVisible()) completer->close();
	QString title;
	if (!currentEditorView()) {
		title = TEXSTUDIO;
	} else {
		QString file = QDir::toNativeSeparators(getCurrentFileName());
		if (file.isEmpty())
			file = currentEditorView()->displayNameForUI();
		title = file + " - " + TEXSTUDIO;
		updateStatusBarEncoding();
		updateOpenDocumentMenu(true);
		newDocumentLineEnding();
	}
	setWindowTitle(title);
	updateUndoRedoStatus();
	cursorPositionChanged();
	if (documents.singleMode()) {
        if (currentEditorView()) completerCommandsNeedsUpdate();
	}
	QString finame = getCurrentFileName();
	if (finame != "") configManager.lastDocument = finame;
    setWindowFilePath(finame);
}

void Texstudio::updateMasterDocumentCaption()
{
	if (documents.singleMode()) {
		actRootDocAutomatic->setChecked(true);
		actRootDocExplicit->setVisible(false);
		statusLabelMode->setText(QString(" %1 ").arg(tr("Automatic")));
		statusLabelMode->setToolTip(tr("Automatic root document detection active"));
	} else {
		QString shortName = documents.masterDocument->getFileInfo().fileName();
		actRootDocExplicit->setChecked(true);
		actRootDocExplicit->setVisible(true);
		actRootDocExplicit->setText(tr("&Explicit") + ": " + shortName);
		statusLabelMode->setText(QString(" %1 ").arg(tr("Root", "explicit root document") + ": " + shortName));
		statusLabelMode->setToolTip(QString(tr("Explict root document:\n%1")).arg(shortName));
	}
}

void Texstudio::currentEditorChanged()
{
	updateCaption();
#ifdef INTERNAL_TERMINAL
	outputView->getTerminalWidget()->setCurrentFileName(getCurrentFileName());
#endif
	if (!currentEditorView()) return;
	if (configManager.watchedMenus.contains("main/view/documents"))
		updateToolBarMenu("main/view/documents");
	editorSpellerChanged(currentEditorView()->getSpeller());
	currentEditorView()->lastUsageTime = QDateTime::currentDateTime();
	currentEditorView()->checkRTLLTRLanguageSwitching();
    // update global toc
    updateTOCs();
}

/*!
 * \brief called when a editor tab is moved in position
 * \param from starting position
 * \param to ending position
 */
void Texstudio::editorTabMoved(int from, int to)
{
	documents.move(from, to);
    // update structure
    updateStructureLocally();
}

void Texstudio::editorAboutToChangeByTabClick(LatexEditorView *edFrom, LatexEditorView *edTo)
{
	Q_UNUSED(edTo)
	saveEditorCursorToHistory(edFrom);
}

void Texstudio::showMarkTooltipForLogMessage(QList<int> errors)
{
	if (!currentEditorView()) return;
	REQUIRE(outputView->getLogWidget());
	REQUIRE(outputView->getLogWidget()->getLogModel());
	QString msg = outputView->getLogWidget()->getLogModel()->htmlErrorTable(errors);
	currentEditorView()->setLineMarkToolTip(msg);
}

void Texstudio::newDocumentLineEnding()
{
	if (!currentEditorView()) return;
	QDocument::LineEnding le = currentEditorView()->editor->document()->lineEnding();
	if (le == QDocument::Conservative) le = currentEditorView()->editor->document()->originalLineEnding();
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

void Texstudio::updateUndoRedoStatus()
{
    if (currentEditor()) {
		actSave->setEnabled(!currentEditor()->document()->isClean() || currentEditor()->fileName().isEmpty());
		bool canUndo = currentEditor()->document()->canUndo();
		if (!canUndo && configManager.svnUndo) {
			QVariant zw = currentEditor()->property("undoRevision");
			int undoRevision = zw.canConvert<int>() ? zw.toInt() : 0;
			if (undoRevision >= 0)
				canUndo = true;
		}
		actUndo->setEnabled(canUndo);
		actRedo->setEnabled(currentEditor()->document()->canRedo());
	} else {
		actSave->setEnabled(false);
		actUndo->setEnabled(false);
		actRedo->setEnabled(false);
	}
}
/*!
 * \brief return current editor
 *
 * return current editorview
 * \return current editor (LatexEditorView)
 */
LatexEditorView *Texstudio::currentEditorView() const
{
	return editors->currentEditor();
}

/*!
 * \brief return current editor
 *
 * return current editor
 * \return current editor (QEditor)
 */
QEditor *Texstudio::currentEditor() const
{
    LatexEditorView *edView = currentEditorView();
    if (!edView) return nullptr;
    return edView->editor;
}

void Texstudio::configureNewEditorView(LatexEditorView *edit)
{
    REQUIRE(m_languages);
    REQUIRE(edit->codeeditor);
    m_languages->setLanguage(edit->codeeditor->editor(), ".tex");

    connect(edit->editor, SIGNAL(undoAvailable(bool)), this, SLOT(updateUndoRedoStatus()));
    connect(edit->editor, SIGNAL(requestClose()), &documents, SLOT(requestedClose()));
    connect(edit->editor, SIGNAL(redoAvailable(bool)), this, SLOT(updateUndoRedoStatus()));
    connect(edit->editor->document(), SIGNAL(lineEndingChanged(int)), this, SLOT(newDocumentLineEnding()));
    connect(edit->editor, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChanged()));
    connect(edit->editor, SIGNAL(cursorHovered()), this, SLOT(cursorHovered()));
    connect(edit->editor, SIGNAL(emitWordDoubleClicked()), this, SLOT(cursorHovered()));
    connect(edit, SIGNAL(showMarkTooltipForLogMessage(QList<int>)), this, SLOT(showMarkTooltipForLogMessage(QList<int>)));
    connect(edit, SIGNAL(needCitation(const QString&)), this, SLOT(insertBibEntry(const QString&)));
    connect(edit, SIGNAL(showPreview(QString)), this, SLOT(showPreview(QString)));
    connect(edit, SIGNAL(showImgPreview(QString)), this, SLOT(showImgPreview(QString)));
    connect(edit, SIGNAL(showPreview(QDocumentCursor)), this, SLOT(showPreview(QDocumentCursor)));
    connect(edit, SIGNAL(showFullPreview()), this, SLOT(recompileForPreview()));
    connect(edit, SIGNAL(gotoDefinition(QDocumentCursor)), this, SLOT(editGotoDefinition(QDocumentCursor)));
    connect(edit, SIGNAL(findLabelUsages(LatexDocument*,QString)), this, SLOT(findLabelUsages(LatexDocument*,QString)));
    connect(edit, SIGNAL(syncPDFRequested(QDocumentCursor)), this, SLOT(syncPDFViewer(QDocumentCursor)));
    connect(edit, SIGNAL(openFile(QString)), this, SLOT(openExternalFile(QString)));
    connect(edit, SIGNAL(openFile(QString,QString)), this, SLOT(openExternalFile(QString,QString)));
    connect(edit, SIGNAL(bookmarkRemoved(QDocumentLineHandle*)), bookmarks, SLOT(bookmarkDeleted(QDocumentLineHandle*)));
    connect(edit, SIGNAL(bookmarkAdded(QDocumentLineHandle*,int)), bookmarks, SLOT(bookmarkAdded(QDocumentLineHandle*,int)));
    connect(edit, SIGNAL(mouseBackPressed()), this, SLOT(goBack()));
    connect(edit, SIGNAL(mouseForwardPressed()), this, SLOT(goForward()));
    connect(edit, SIGNAL(cursorChangeByMouse()), this, SLOT(saveCurrentCursorToHistory()));
    connect(edit, SIGNAL(openCompleter()), this, SLOT(normalCompletion()));
    connect(edit, SIGNAL(openInternalDocViewer(QString,QString)), this, SLOT(openInternalDocViewer(QString,QString)));
    connect(edit, SIGNAL(showExtendedSearch()), this, SLOT(showExtendedSearch()));
    connect(edit, SIGNAL(execMacro(Macro,MacroExecContext)), this, SLOT(execMacro(Macro,MacroExecContext)));

    connect(edit->editor, SIGNAL(fileReloaded()), this, SLOT(fileReloaded()));
    connect(edit->editor, SIGNAL(fileInConflictShowDiff()), this, SLOT(fileInConflictShowDiff()));
    connect(edit->editor, SIGNAL(fileAutoReloading(QString)), this, SLOT(fileAutoReloading(QString)));

    if (Guardian::instance()) { // Guardian is not yet there when this is called at program startup
        connect(edit->editor, SIGNAL(slowOperationStarted()), Guardian::instance(), SLOT(slowOperationStarted()));
        connect(edit->editor, SIGNAL(slowOperationEnded()), Guardian::instance(), SLOT(slowOperationEnded()));
    }
    connect(edit, SIGNAL(linesChanged(QString,LatexDocument *,QList<LineInfo>,int)), grammarCheck, SLOT(check(QString,LatexDocument *,QList<LineInfo>,int)));

    connect(edit, SIGNAL(spellerChanged(QString)), this, SLOT(editorSpellerChanged(QString)));
    connect(edit->editor, SIGNAL(focusReceived()), edit, SIGNAL(focusReceived()));
}

/*!
 * \brief complete the new editor view configuration (edit->document is set)
 * \param edit used editorview
 * \param reloadFromDoc
 * \param hidden if editor is not shown
 */
void Texstudio::configureNewEditorViewEnd(LatexEditorView *edit, bool reloadFromDoc, bool hidden)
{
    REQUIRE(edit->document);
    // set speller here as document is needed
    edit->setSpellerManager(&spellerManager);
    edit->setSpeller("<default>");
    //patch Structure
    //disconnect(edit->editor->document(),SIGNAL(contentsChange(int, int))); // force order of contentsChange update
    connect(edit->editor->document(), SIGNAL(contentsChange(int,int)), edit->document, SLOT(patchStructure(int,int)));
    //connect(edit->editor->document(),SIGNAL(contentsChange(int, int)),edit,SLOT(documentContentChanged(int,int))); now directly called by patchStructure
    connect(edit->editor->document(), SIGNAL(linesRemoved(QDocumentLineHandle*,int,int)), edit->document, SLOT(patchStructureRemoval(QDocumentLineHandle*,int,int)));
    //connect(edit->editor->document(), SIGNAL(lineDeleted(QDocumentLineHandle*,int)), edit->document, SLOT(patchStructureRemoval(QDocumentLineHandle*,int)));
    connect(edit->document, &LatexDocument::updateCompleter, this, &Texstudio::completerNeedsUpdate);
    connect(edit->document, &LatexDocument::updateCompleterCommands, this, &Texstudio::completerCommandsNeedsUpdate);
    connect(edit->editor, SIGNAL(needUpdatedCompleter()), this, SLOT(needUpdatedCompleter()));
    connect(edit->document, SIGNAL(importPackage(QString)), this, SLOT(importPackage(QString)));
    connect(edit->document, SIGNAL(bookmarkLineUpdated(int)), bookmarks, SLOT(updateLineWithBookmark(int)));
    connect(edit->document, SIGNAL(encodingChanged()), this, SLOT(updateStatusBarEncoding()));
    connect(edit, SIGNAL(thesaurus(int,int)), this, SLOT(editThesaurus(int,int)));
    connect(edit, SIGNAL(changeDiff(QPoint)), this, SLOT(editChangeDiff(QPoint)));
    connect(edit, SIGNAL(saveCurrentCursorToHistoryRequested()), this, SLOT(saveCurrentCursorToHistory()));
    connect(edit->document,SIGNAL(structureUpdated(LatexDocument*)),this,SLOT(updateTOCs()));
    edit->document->saveLineSnapshot(); // best guess of the lines used during last latex compilation

    if (!hidden) {
        int index = reloadFromDoc ? documents.documents.indexOf(edit->document, 0) : -1; // index: we still assume here that the order of documents and editors is synchronized
        editors->insertEditor(edit, index);
        edit->editor->setFocus();
        updateCaption();
    }
}
/*!
 * \brief get editor which handles FileName
 *
 * get editor which handles FileName
 *
 * \param fileName
 * \param checkTemporaryNames
 * \return editorview, 0 if no editor matches
 */
LatexEditorView *Texstudio::getEditorViewFromFileName(const QString &fileName, bool checkTemporaryNames)
{
	LatexDocument *document = documents.findDocument(fileName, checkTemporaryNames);
	if (!document) return nullptr;
	return document->getEditorView();
}

/*!
 * \brief get the editor referenced by a given line handle
 * \param dlh the line handle
 * \return the editor view, null if the handle is null
 */
LatexEditorView *Texstudio::getEditorViewFromHandle(const QDocumentLineHandle *dlh)
{
	if (!dlh) return nullptr;
	LatexDocument *targetDoc = qobject_cast<LatexDocument *>(dlh->document());
	REQUIRE_RET(targetDoc, nullptr);
	return qobject_cast<LatexEditorView *>(targetDoc->getEditorView());
}

/*!
 * \brief get filename of current editor
 *
 * get filename of current editor
 * \return filename
 */
QString Texstudio::getCurrentFileName()
{
	return documents.getCurrentFileName();
}

QString Texstudio::getAbsoluteFilePath(const QString &relName, const QString &extension)
{
	return documents.getAbsoluteFilePath(relName, extension);
}

QString Texstudio::getRelativeFileName(const QString &file, QString basepath, bool keepSuffix)
{
	return getRelativeBaseNameToPath(file, basepath, true, keepSuffix);
}
bool Texstudio::fileExists(const QString &file){
    return QFileInfo::exists(file);
}

bool Texstudio::activateEditorForFile(QString f, bool checkTemporaryNames, bool setFocus)
{
	LatexEditorView *edView = getEditorViewFromFileName(f, checkTemporaryNames);
	if (!edView) return false;
	saveCurrentCursorToHistory();
	if (!editors->containsEditor(edView)) return false;
	editors->setCurrentEditor(edView, setFocus);
	return true;
}

///////////////////FILE//////////////////////////////////////

void guessLanguageFromContent(QLanguageFactory *m_languages, QEditor *e)
{
	QDocument *doc = e->document();
	if (doc->lineCount() == 0) return;
	if (doc->line(0).text().startsWith("<?xml") ||
	        doc->line(0).text().startsWith("<!DOCTYPE"))
		m_languages->setLanguage(e, ".xml");
}
/*!
 * \brief load file
 *
 * load file from disc
 * \param f filename
 * \param asProject load file as master-file
 * \param hidden hide editor
 * \param recheck
 * \param dontAsk
 * \return
 */
LatexEditorView *Texstudio::load(const QString &f , bool asProject, bool hidden, bool recheck, bool dontAsk)
{
    QString f_real = f;
#ifdef Q_OS_WIN32
    QRegExp regcheck("/([a-zA-Z]:[/\\\\].*)");
    if (regcheck.exactMatch(f)) f_real = regcheck.cap(1);
#endif

#ifndef NO_POPPLER_PREVIEW
    if (f_real.endsWith(".pdf", Qt::CaseInsensitive)) {
        if (PDFDocument::documentList().isEmpty())
            newPdfPreviewer();
        PDFDocument::documentList().at(0)->loadFile(f_real);
        PDFDocument::documentList().at(0)->show();
        PDFDocument::documentList().at(0)->setFocus();
        return nullptr;
    }
    if ((f_real.endsWith(".synctex.gz", Qt::CaseInsensitive) ||
         f_real.endsWith(".synctex", Qt::CaseInsensitive))
            && UtilsUi::txsConfirm(tr("Do you want to debug a SyncTeX file?"))) {
        fileNewInternal();
        currentEditor()->document()->setText(PDFDocument::debugSyncTeX(f_real), false);
        return currentEditorView();
    }
#endif

    if (f_real.endsWith(".log", Qt::CaseInsensitive) &&
            UtilsUi::txsConfirm(QString("Do you want to load file %1 as LaTeX log file?").arg(QFileInfo(f).completeBaseName()))) {
        outputView->getLogWidget()->loadLogFile(f, documents.getTemporaryCompileFileName(), QTextCodec::codecForName(configManager.logFileEncoding.toLatin1()));
        setLogMarksVisible(true);
        return nullptr;
    }

    if (!hidden)
        raise();

    //test is already opened
    LatexEditorView *existingView = getEditorViewFromFileName(f_real);
    LatexDocument *doc=nullptr;
    if (!existingView) {
        doc = documents.findDocumentFromName(f_real);
        if (doc) existingView = doc->getEditorView();
    }
    if (existingView) {
        if (hidden)
            return existingView;
        if (asProject) documents.setMasterDocument(existingView->document);
        if (existingView->document->isHidden()) {
            // clear baseStructure outside treeview context
            /*foreach(StructureEntry *elem,existingView->document->baseStructure->children){
                    delete elem;
                }
                existingView->document->baseStructure->children.clear();*/
            //
            existingView->editor->setLineWrapping(configManager.editorConfig->wordwrap > 0);
            documents.deleteDocument(existingView->document, true);
            existingView->editor->setSilentReloadOnExternalChanges(existingView->document->remeberAutoReload);
            existingView->editor->setHidden(false);
            documents.addDocument(existingView->document, false);
            editors->addEditor(existingView);
            if(asProject)
                editors->moveEditor(existingView,Editors::AbsoluteFront); // somewhat redundant, but we run into that problem with issue #899
            //updateStructure(false, existingView->document, true);
            existingView->editor->setFocus();
            updateCaption();
            return existingView;
        }
        editors->setCurrentEditor(existingView);
        return existingView;
    }

    // find closed master doc
    if (doc) {
        LatexEditorView *edit = new LatexEditorView(nullptr, configManager.editorConfig, doc);
        edit->setLatexPackageList(&latexPackageList);
        edit->document = doc;
        edit->editor->setFileName(doc->getFileName());
        edit->setHelp(&help);
        disconnect(edit->editor->document(), SIGNAL(contentsChange(int, int)), edit->document, SLOT(patchStructure(int, int)));
        configureNewEditorView(edit);
        if (edit->editor->fileInfo().suffix().toLower() != "tex")
            m_languages->setLanguage(edit->editor, f_real);
        if (!edit->editor->languageDefinition())
            guessLanguageFromContent(m_languages, edit->editor);

        doc->setLineEnding(edit->editor->document()->originalLineEnding());
        doc->setEditorView(edit); //update file name (if document didn't exist)

        configureNewEditorViewEnd(edit, !hidden, hidden);

        if (!hidden) {
            bookmarks->restoreBookmarks(edit);
        }
        return edit;
    }

    //load it otherwise
    if (!QFile::exists(f_real)) return nullptr;
    QFile file(f_real);
    if (!file.open(QIODevice::ReadOnly)) {
        if (!hidden && !dontAsk)
            QMessageBox::warning(this, tr("Error"), tr("You do not have read permission to the file %1.").arg(f_real));
        return nullptr;
    }
    file.close();

    bool bibTeXmodified = documents.bibTeXFilesModified;

    doc = new LatexDocument(this);
    doc->setCenterDocumentInEditor(configManager.editorConfig->centerDocumentInEditor);
    doc->enableSyntaxCheck(configManager.editorConfig->inlineSyntaxChecking && configManager.editorConfig->realtimeChecking);
    LatexEditorView *edit = new LatexEditorView(nullptr, configManager.editorConfig, doc);
    edit->setLatexPackageList(&latexPackageList);
    edit->setHelp(&help);
    if (hidden) {
        edit->editor->setLineWrapping(false); //disable linewrapping in hidden docs to speed-up updates
        doc->clearWidthConstraint();
    }
    configureNewEditorView(edit);

    edit->document = documents.findDocument(f_real);
    if (!edit->document) {
        edit->document = doc;
        edit->document->setEditorView(edit);
        documents.addDocument(edit->document, hidden);
    } else edit->document->setEditorView(edit);

    if (configManager.recentFileHighlightLanguage.contains(f_real))
        m_languages->setLanguage(edit->editor, configManager.recentFileHighlightLanguage.value(f_real));
    else if (edit->editor->fileInfo().suffix().toLower() != "tex")
        m_languages->setLanguage(edit->editor, f_real);

    edit->editor->load(f_real, QDocument::defaultCodec());

    if (!edit->editor->languageDefinition())
        guessLanguageFromContent(m_languages, edit->editor);

    edit->editor->document()->setLineEndingDirect(edit->editor->document()->originalLineEnding());

    edit->document->setEditorView(edit); //update file name (if document didn't exist)

    configureNewEditorViewEnd(edit, asProject, hidden);

    //check for svn conflict
	if (!hidden) {
		checkSVNConflicted();

		MarkCurrentFileAsRecent();
	}

    documents.updateMasterSlaveRelations(doc, recheck);

    if (recheck || hidden) {
		doc->updateLtxCommands();
	}

	if (!hidden) {
		if (QFile::exists(f_real + ".recover.bak~")
		        && QFileInfo(f_real + ".recover.bak~").lastModified() > QFileInfo(f_real).lastModified()) {
            if (UtilsUi::txsConfirm(tr("A crash recover file from %1 has been found for \"%2\".\nDo you want to restore it?").arg(QFileInfo(f_real + ".recover.bak~").lastModified().toString(),f_real))) {
				QFile f(f_real + ".recover.bak~");
				if (f.open(QFile::ReadOnly)) {
					QByteArray ba = f.readAll();
					QString recovered = QTextCodec::codecForName("UTF-8")->toUnicode(ba); //TODO: chunk loading?
					edit->document->setText(recovered, true);
				} else UtilsUi::txsWarning(tr("Failed to open recover file \"%1\".").arg(f_real + ".recover.bak~"));
			}
		}

	}

	updateStructure(true, doc, true);

	bookmarks->restoreBookmarks(edit);

    if (asProject) documents.setMasterDocument(edit->document);

	if (outputView->getLogWidget()->logPresent()) {
		updateLogEntriesInEditors();
		setLogMarksVisible(true);
	}
	if (!bibTeXmodified)
		documents.bibTeXFilesModified = false; //loading a file can change the list of included bib files, but we won't consider that as a modification of them, because then they don't have to be recompiled
	LatexDocument *rootDoc = edit->document->getRootDocument();
    if (rootDoc) {
        foreach (const FileNamePair &fnp, edit->document->mentionedBibTeXFiles().values()) {
			Q_ASSERT(!fnp.absolute.isEmpty());
			rootDoc->lastCompiledBibTeXFiles.insert(fnp.absolute);
		}
    }

#ifndef Q_OS_MAC
	if (!hidden) {
		if (windowState() == Qt::WindowMinimized || !isVisible() || !QApplication::activeWindow()) {
			show();
			if (windowState() == Qt::WindowMinimized)
				setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
			show();
			raise();
			QApplication::setActiveWindow(this);
			activateWindow();
			setFocus();
			edit->editor->setFocus();
		}
	}
#endif

	runScriptsInList(Macro::ST_LOAD_THIS_FILE, doc->localMacros);

	emit infoLoadFile(f_real);

	return edit;
}

void Texstudio::completerNeedsUpdate()
{
    mCompleterNeedsUpdate = true;
}
/*!
 * \brief used packages has changed, completer commands need update
 */
void Texstudio::completerCommandsNeedsUpdate()
{
    mCompleterCommandsNeedsUpdate = true;
    mCompleterNeedsUpdate = true;
}

void Texstudio::needUpdatedCompleter()
{
	if (mCompleterNeedsUpdate)
		updateCompleter();
}

void Texstudio::updateUserToolMenu()
{
	CommandMapping cmds = buildManager.getAllCommands();
	QStringList order = buildManager.getCommandsOrder();
	QStringList ids;
	QStringList displayName;
	for (int i = 0; i < order.size(); i++) {
		const CommandInfo &ci = cmds.value(order[i]);
		if (!ci.user) continue;
		ids << ci.id;
		displayName << ci.displayName;
	}
    configManager.updateListMenu("main/tools/user", displayName, "cmd", true, SLOT(commandFromAction()), Qt::ALT | Qt::SHIFT | Qt::Key_F1, false, 0);
	QMenu *m = getManagedMenu("main/tools/user");
	REQUIRE(m);
	QList<QAction *> actions = m->actions();
	for (int i = 0; i < actions.size(); i++)
		actions[i]->setData(BuildManager::TXS_CMD_PREFIX + ids[i]);
}

#include "QMetaMethod"
void Texstudio::linkToEditorSlot(QAction *act, const char *methodName, const QList<QVariant> &args)
{
	REQUIRE(act);
	connectUnique(act, SIGNAL(triggered()), this, SLOT(relayToEditorSlot()));
	act->setProperty("primarySlot", QString(SLOT(relayToEditorSlot())));
	QByteArray signature = createMethodSignature(methodName, args);
	if (!args.isEmpty())
		act->setProperty("args", QVariant::fromValue<QList<QVariant> >(args));
	for (int i = 0; i < LatexEditorView::staticMetaObject.methodCount(); i++)
		if (signature == LatexEditorView::staticMetaObject.method(i).methodSignature()) {
			act->setProperty("editorViewSlot", methodName);
			return;
		} //else qDebug() << LatexEditorView::staticMetaObject.method(i).signature();
	for (int i = 0; i < QEditor::staticMetaObject.methodCount(); i++)
		if (signature == QEditor::staticMetaObject.method(i).methodSignature()) {
			act->setProperty("editorSlot", methodName);
			return;
		}

	qDebug() << methodName << signature;
	Q_ASSERT(false);
}

void Texstudio::relayToEditorSlot()
{
	if (!currentEditorView()) return;
	QAction *act = qobject_cast<QAction *>(sender());
	REQUIRE(act);
	if (act->property("editorViewSlot").isValid()) QMetaObjectInvokeMethod(currentEditorView(), qPrintable(act->property("editorViewSlot").toString()), act->property("args").value<QList<QVariant> >());
	else if (act->property("editorSlot").isValid()) QMetaObjectInvokeMethod(currentEditor(), qPrintable(act->property("editorSlot").toString()), act->property("args").value<QList<QVariant> >());
}

void Texstudio::relayToOwnSlot()
{
	QAction *act = qobject_cast<QAction *>(sender());
	REQUIRE(act && act->property("slot").isValid());
	QMetaObjectInvokeMethod(this, qPrintable(act->property("slot").toString()), act->property("args").value<QList<QVariant> >());
}

void Texstudio::autoRunScripts()
{
	QStringList vers = QString(QT_VERSION_STR).split('.');
	Q_ASSERT(vers.length() >= 2);
	int major = vers.at(0).toInt();
	int minor = vers.at(1).toInt();
	if (!hasAtLeastQt(major, minor))
		UtilsUi::txsWarning(tr("%1 has been compiled with Qt %2, but is running with Qt %3.\nPlease get the correct runtime library (e.g. .dll or .so files).\nOtherwise there might be random errors and crashes.")
                   .arg(TEXSTUDIO,QT_VERSION_STR,qVersion()));
	runScripts(Macro::ST_TXS_START);
}

void Texstudio::runScripts(int trigger)
{
	runScriptsInList(trigger, configManager.completerConfig->userMacros);
}

void Texstudio::runScriptsInList(int trigger, const QList<Macro> &scripts)
{
	foreach (const Macro &macro, scripts) {
        if (macro.type == Macro::Script && macro.isActiveForTrigger(static_cast<Macro::SpecialTrigger>(trigger) ))
			runScript(macro.script(), MacroExecContext(trigger));
	}
}

void Texstudio::fileNewInternal(QString fileName)
{
	LatexDocument *doc = new LatexDocument(this);
	doc->enableSyntaxCheck(configManager.editorConfig->inlineSyntaxChecking);
	LatexEditorView *edit = new LatexEditorView (nullptr, configManager.editorConfig, doc);
	edit->setLatexPackageList(&latexPackageList);
    edit->setHelp(&help);
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
	doc->updateLtxCommands();
	if (!fileName.isEmpty())
		fileSave(true);
}

void Texstudio::fileNew(QString fileName)
{
	fileNewInternal(fileName);
	emit infoNewFile();
}

void Texstudio::fileAutoReloading(QString fname)
{
	LatexDocument *document = documents.findDocument(fname);
	if (!document) return;
	document->initClearStructure();
}
/* \brief called when file has been reloaded from disc
 */
void Texstudio::fileReloaded()
{
	QEditor *mEditor = qobject_cast<QEditor *>(sender());
	if (mEditor == currentEditor()) {
		currentEditorView()->document->initClearStructure();
		updateStructure(true);
	} else {
		LatexDocument *document = documents.findDocument(mEditor->fileName());
		if (!document) return;
		document->initClearStructure();
		document->patchStructure(0, -1);
	}
}
/*!
 * \brief make a template from current editor
 */
void Texstudio::fileMakeTemplate()
{
	if (!currentEditorView())
		return;

	MakeTemplateDialog templateDialog(TemplateManager::userTemplateDir(), currentEditor()->fileName());
	if (templateDialog.exec()) {
		// save file
		QString fn = templateDialog.suggestedFile();
		LatexDocument *doc = currentEditorView()->document;
		QString txt = doc->text();
		//txt.replace("%","%%"); not necessary any more
		QFile file_txt(fn);
		if (!file_txt.open(QIODevice::WriteOnly | QIODevice::Text)) {
			UtilsUi::txsInformation(tr("Could not write template data:") + "\n" + fn);
			return;
		} else {
#ifdef Q_OS_WIN
			txt.replace("\r\n", "\n"); //on Windows QTextStream corrupts line endings by replacing "\n" with "\r\n", so "\r\n" becomes "\r\r\n"
#endif
			QTextStream out(&file_txt);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
            out.setCodec("UTF-8");
#endif

			out << txt;
			file_txt.close();
		}

		/* alternate code in order to double %

		QString old_name=currentEditor()->fileName();
		QTextCodec *mCodec=currentEditor()->getFileCodec();
		currentEditor()->setFileCodec(QTextCodec::codecForName("utf-8"));
		currentEditor()->save(fn);
		currentEditor()->setFileName(old_name);
		currentEditor()->setFileCodec(mCodec);
		*/

		// save metaData
		QFileInfo fi(fn);
		fn = fi.absoluteFilePath();
		fn.remove(fn.lastIndexOf('.'), 4);
		fn.append(".json");
		QFile file(fn);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			UtilsUi::txsInformation(tr("Could not write template meta data:") + "\n" + fn);
		} else {
			QTextStream out(&file);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
            out.setCodec("UTF-8");
#endif
			out << templateDialog.generateMetaData();
			file.close();
		}
	}
}
/*!
 * \brief load template file for editing
 * \param fname filename
 */
void Texstudio::templateEdit(const QString &fname)
{
	load(fname, false);
}
/*!
 * \brief generate new file from template
 */
void Texstudio::fileNewFromTemplate()
{
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
			UtilsUi::txsWarning(tr("File not found:") + QString("\n%1").arg(fname));
			return;
		}
		if (!file.open(QIODevice::ReadOnly)) {
			UtilsUi::txsWarning(tr("You do not have read permission to this file:") + QString("\n%1").arg(fname));
			return;
		}

		//set up new editor with template
		fileNewInternal();
		LatexEditorView *edit = currentEditorView();

		QString mTemplate;
		bool loadAsSnippet = false;
		QTextStream in(&file);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
        in.setCodec("UTF-8");
#endif
		QString line = in.readLine();
        if (line.contains(QRegularExpression("^%\\s*!TXS\\s+template"))) {
			loadAsSnippet = true;
		} else {
			mTemplate += line + '\n';
		}
		while (!in.atEnd()) {
			line = in.readLine();
			mTemplate += line + "\n";
		}
		if (loadAsSnippet) {
			bool flag = edit->editor->flag(QEditor::AutoIndent);
			edit->editor->setFlag(QEditor::AutoIndent, false);
			CodeSnippet toInsert(mTemplate, false);
			toInsert.insert(edit->editor);
			edit->editor->setFlag(QEditor::AutoIndent, flag);
			edit->editor->setCursorPosition(0, 0, false);
			edit->editor->nextPlaceHolder();
			edit->editor->ensureCursorVisible(QEditor::KeepSurrounding);
		} else {
			edit->editor->setText(mTemplate, false);
		}

		emit infoNewFromTemplate();
	}
	delete dialog;
}
/*!
 * \brief insert table template
 */
void Texstudio::insertTableTemplate()
{
	QEditor *m_edit = currentEditor();
	if (!m_edit)
		return;
	QDocumentCursor c = m_edit->cursor();
	if (!LatexTables::inTableEnv(c))
		return;

	// select Template
	TemplateManager tmplMgr;
	connectUnique(&tmplMgr, SIGNAL(editRequested(QString)), this, SLOT(templateEdit(QString)));
	if (tmplMgr.tableTemplateDialogExec()) {
		QString fname = tmplMgr.selectedTemplateFile();
		QFile file(fname);
		if (!file.exists()) {
			UtilsUi::txsWarning(tr("File not found:") + QString("\n%1").arg(fname));
			return;
		}
		if (!file.open(QIODevice::ReadOnly)) {
			UtilsUi::txsWarning(tr("You do not have read permission to this file:") + QString("\n%1").arg(fname));
			return;
		}
		QString tableDef = LatexTables::getSimplifiedDef(c);
		QString tableText = LatexTables::getTableText(c);
		QString widthDef;
		//remove table
		c.removeSelectedText();
		m_edit->setCursor(c);
		// split table text into line/column list
		QStringList values;
		QList<int> starts;
		QString env;
		//tableText.remove("\n");
		tableText.remove("\\hline");
		if (tableText.startsWith("\\begin")) {
			LatexParser::resolveCommandOptions(tableText, 0, values, &starts);
			env = values.takeFirst();
			env.remove(0, 1);
			env.remove(env.length() - 1, 1);
			// special treatment for tabu/longtabu
			if ((env == "tabu" || env == "longtabu") && values.count() < 1) {
				int startExtra = env.length() + 8;
				int endExtra = tableText.indexOf("{", startExtra);
				if (endExtra >= 0 && endExtra > startExtra) {
					QString textHelper = tableText;
					widthDef = textHelper.mid(startExtra, endExtra - startExtra);
					textHelper.remove(startExtra, endExtra - startExtra); // remove to/spread definition
					values.clear();
					starts.clear();
					LatexParser::resolveCommandOptions(textHelper, 0, values, &starts);
					for (int i = 1; i < starts.count(); i++) {
						starts[i] += endExtra - startExtra;
					}
				}
				if (!values.isEmpty())
					values.takeFirst();
			}
			if (LatexTables::tabularNames.contains(env)) {
				if (!values.isEmpty()) {
					int i = starts.at(1);
					i += values.first().length();
					tableText.remove(0, i);
				}
			}
			if (LatexTables::tabularNamesWithOneOption.contains(env)) {
				if (values.size() > 1) {
					int i = starts.at(2);
					i += values.at(1).length();
					tableText.remove(0, i);
				}
			}
            tableText.remove(QRegularExpression("\\\\end\\{" + env + "\\}$"));
		}
		tableText.replace("\\endhead", "\\\\");
		QStringList lines = tableText.split("\\\\");
		QList<QStringList> tableContent;
		foreach (QString line, lines) {
			//line=line.simplified();
			if (line.simplified().isEmpty())
				continue;
            QStringList elems = line.split(QRegularExpression("&"));
			if (elems.count() > 0) {
				if (elems[0].startsWith("\n"))
					elems[0] = elems[0].mid(1);
			}
			//QList<QString>::iterator i;
			/*for(i=elems.begin();i!=elems.end();i++){
				QString elem=*i;
			    *i=elem.simplified();
			}*/

			// handle \& correctly
			for (int i = elems.size() - 1; i >= 0; --i) {
				if (elems.at(i).endsWith("\\")) {
					QString add = elems.at(i) + elems.at(i + 1);
					elems.replace(i, add);
					elems.removeAt(i + 1);
				}
			}
			tableContent << elems;
		}
		LatexTables::generateTableFromTemplate(currentEditorView(), fname, tableDef, tableContent, env, widthDef);
	}
}
/*! \brief align columns of latex table in editor
 */
void Texstudio::alignTableCols()
{
	if (!currentEditor()) return;
	QDocumentCursor cur(currentEditor()->cursor());
	int linenr = cur.lineNumber();
	int col = cur.columnNumber();
	if (!cur.isValid())
		return;
	LatexTables::alignTableCols(cur);
	cur.setLineNumber(linenr);
	cur.setColumnNumber(col);
	currentEditor()->setCursor(cur);
}
/*! \brief open file
 *
 * open file is triggered from menu action.
 * It opens a file dialog and lets the user to select a file.
 * If the file is already open, the apropriate editor subwindow is brought to front.
 * If the file is open as hidden, an editor is created and brought to front.
 * pdf files are handled as well and they are forwarded to the pdf viewer.
 */
void Texstudio::fileOpen()
{
	QString currentDir = QDir::homePath();
	if (!configManager.lastDocument.isEmpty()) {
		QFileInfo fi(configManager.lastDocument);
		if (fi.exists() && fi.isReadable()) {
			currentDir = fi.absolutePath();
		}
	}
	QStringList files = FileDialog::getOpenFileNames(this, tr("Open Files"), currentDir, fileFilters,  &selectedFileFilter);

	recheckLabels = false; // impede label rechecking on hidden docs
	QList<LatexEditorView *>listViews;
	foreach (const QString &fn, files)
		listViews << load(fn);

	// update ref/labels in one go;
	QList<LatexDocument *> completedDocs;
	foreach (LatexEditorView *edView, listViews) {
		if (!edView)
			continue;
		LatexDocument *docBase = edView->getDocument();
		foreach (LatexDocument *doc, docBase->getListOfDocs()) {
			doc->recheckRefsLabels();
			if (completedDocs.contains(doc))
				continue;
			doc->updateLtxCommands(true);
			completedDocs << doc->getListOfDocs();
		}
	}
	recheckLabels = true;
	// update completer
	if (currentEditorView())
		updateCompleter(currentEditorView());
}

void Texstudio::fileRestoreSession(bool showProgress, bool warnMissing)
{

    QFileInfo f(QDir(configManager.configBaseDir), "lastSession.txss2");
	Session s;
	if (f.exists()) {
		if (!s.load(f.filePath())) {
			UtilsUi::txsCritical(tr("Loading of last session failed."));
		}
    }else{
        // restore v1 format if it exists
        QFileInfo f(QDir(configManager.configBaseDir), "lastSession.txss");
        if (f.exists()) {
            if (!s.load(f.filePath())) {
                UtilsUi::txsCritical(tr("Loading of last session failed."));
            }
        }
    }
	restoreSession(s, showProgress, warnMissing);
}
/*!
 * \brief save current editor content
 * Optionally a different editor may be used
 * Necessary for hidden docuements
 *
 * \param saveSilently
 */
void Texstudio::fileSave(const bool saveSilently, QEditor *editor)
{
    if(!editor){
        // fallback to current editor
        editor=currentEditor();
    }
    if (!editor)
		return;

    if (editor->fileName() == "" || !QFileInfo::exists(editor->fileName())) {
		removeDiffMarkers();// clean document from diff markers first
        fileSaveAs(editor->fileName(), saveSilently);
	} else {
		removeDiffMarkers();// clean document from diff markers first
        editor->save();
        editor->document()->markViewDirty();//force repaint of line markers (yellow -> green)
		MarkCurrentFileAsRecent();
		int checkIn = (configManager.autoCheckinAfterSaveLevel > 0 && !saveSilently) ? 2 : 1;
        emit infoFileSaved(editor->fileName(), checkIn);
	}
	updateCaption();
}
/*!
 * \brief save current editor content to new filename
 *
 * save current editor content to new filename
 * \param fileName
 * \param saveSilently don't ask for new filename if fileName is empty
 */
void Texstudio::fileSaveAs(const QString &fileName, const bool saveSilently)
{
	if (!currentEditorView())
		return;

	// select a directory/filepath
	QString currentDir = QDir::homePath();
	if (fileName.isEmpty()) {
		if (currentEditor()->fileInfo().isFile()) {
			currentDir = currentEditor()->fileInfo().absoluteFilePath();
		} else {
			if (!configManager.lastDocument.isEmpty())
				currentDir = configManager.lastDocument;
			static QString saveAsDefault;
			configManager.registerOption("Files/Save As Default", &saveAsDefault, "?a)/document");
            currentDir = buildManager.parseExtendedCommandLine(saveAsDefault, QFileInfo(currentDir), QFileInfo(currentDir)).value(0, currentDir);
		}
	} else {
		currentDir = fileName;
	}

	// get a file name
	QString fn = fileName;
	if (!saveSilently || fn.isEmpty()) {
		fn = FileDialog::getSaveFileName(this, tr("Save As"), currentDir, fileFilters, &selectedFileFilter);
		if (!fn.isEmpty()) {
			static QRegExp fileExt("\\*(\\.[^ )]+)");
			if (fileExt.indexIn(selectedFileFilter) > -1) {
				//add
				int lastsep = qMax(fn.lastIndexOf("/"), fn.lastIndexOf("\\"));
				int lastpoint = fn.lastIndexOf(".");
				if (lastpoint <= lastsep) //if both aren't found or point is in directory name
					fn.append(fileExt.cap(1));
			}
		}
	}
	if (!fn.isEmpty()) {
		if (getEditorViewFromFileName(fn) && getEditorViewFromFileName(fn) != currentEditorView()) {
			// trying to save with same name as another already existing file
			LatexEditorView *otherEdView = getEditorViewFromFileName(fn);
			if (!otherEdView->document->isClean()) {
				UtilsUi::txsWarning(tr("Saving under the name\n"
				              "%1\n"
				              "is currently not possible because a modified version of a file\n"
				              "with this name is open in TeXstudio. You have to save or close\n"
				              "this other file before you can overwrite it.").arg(fn));
				return;
			}
			// other editor does not contain unsaved changes, so it can be closed
			LatexEditorView *currentEdView = currentEditorView();
			editors->setCurrentEditor(otherEdView);
			fileClose();
			editors->setCurrentEditor(currentEdView);
		}
#ifndef NO_POPPLER_PREVIEW
		// show message in viewer
		if (currentEditor()->fileInfo() != QFileInfo(fn)) {
			foreach (PDFDocument *viewer, PDFDocument::documentList())
				if (viewer->getMasterFile() == currentEditor()->fileInfo())
					viewer->showMessage(tr("This pdf cannot be synchronized with the tex source any more because the source file has been renamed due to a Save As operation. You should recompile the renamed file and view its result."));
		}
#endif
		// save file
		removeDiffMarkers();// clean document from diff markers first
		currentEditor()->save(fn);
		currentEditorView()->document->setEditorView(currentEditorView()); //update file name
		MarkCurrentFileAsRecent();

		//update Master/Child relations
		LatexDocument *doc = currentEditorView()->document;
		documents.updateMasterSlaveRelations(doc);

		updateOpenDocumentMenu(true);  // TODO: currently duplicate functionality with updateCaption() below
		if (currentEditor()->fileInfo().suffix().toLower() != "tex")
			m_languages->setLanguage(currentEditor(), fn);

		emit infoFileSaved(currentEditor()->fileName());
	}

	updateCaption();
    updateTOCs();
}
/*!
 * \brief save all files
 *
 * This functions is called from menu-action.
 */
void Texstudio::fileSaveAll()
{
	fileSaveAll(true, true);
}
/*!
 * \brief save all files
 *
 * This functions is called from timer (auto save).
 * It does *not* save unnamed files.
 */
void Texstudio::fileSaveAllFromTimer()
{
    fileSaveAll(false, false);
}
/*!
 * \brief save all files
 *
 * \param alsoUnnamedFiles
 * \param alwaysCurrentFile
 */
void Texstudio::fileSaveAll(bool alsoUnnamedFiles, bool alwaysCurrentFile)
{
	//LatexEditorView *temp = new LatexEditorView(EditorView,colorMath,colorCommand,colorKeyword);
	//temp=currentEditorView();
	REQUIRE(editors);

	LatexEditorView *currentEdView = currentEditorView();

	foreach (LatexEditorView *edView, editors->editors()) {
		REQUIRE(edView->editor);

		if (edView->editor->fileName().isEmpty()) {
			if ((alsoUnnamedFiles || (alwaysCurrentFile && edView == currentEdView) ) ) {
				editors->setCurrentEditor(edView);
				fileSaveAs();
			} else if (!edView->document->getTemporaryFileName().isEmpty())
				edView->editor->saveCopy(edView->document->getTemporaryFileName());
			//else if (edView->editor->isInConflict()) {
			//edView->editor->save();
			//}
		} else if (edView->editor->isContentModified() || edView->editor->isInConflict()) {
			removeDiffMarkers();// clean document from diff markers first
			edView->editor->save(); //only save modified documents
            edView->document->markViewDirty();//force repaint of line markers (yellow -> green)

			if (edView->editor->fileName().endsWith(".bib")) {
				QString temp = edView->editor->fileName();
				temp = temp.replace(QDir::separator(), "/");
				documents.bibTeXFilesModified = documents.bibTeXFilesModified  || documents.mentionedBibTeXFiles.contains(temp);//call bibtex on next compilation (this would also set as soon as the user switch to a tex file, but he could compile before switching)
			}

			emit infoFileSaved(edView->editor->fileName());
		}
	}
    // save hidden files (in case that they are changed via replace in all docs
    foreach (LatexDocument *d, documents.hiddenDocuments){
        if(d->getEditorView()->editor->isContentModified())
            d->getEditorView()->editor->save();
    }


	if (currentEditorView() != currentEdView)
		editors->setCurrentEditor(currentEdView);
	updateUndoRedoStatus();
}

//TODO: handle svn in all these methods

void Texstudio::fileUtilCopyMove(bool move)
{
	QString fn = documents.getCurrentFileName();
	if (fn.isEmpty()) return;
	QString newfn = FileDialog::getSaveFileName(this, move ? tr("Rename/Move") : tr("Copy"), fn, fileFilters, &selectedFileFilter);
	if (newfn.isEmpty()) return;
	if (fn == newfn) return;
	QFile::Permissions permissions = QFile(fn).permissions();
	if (move) fileSaveAs(newfn, true);
	else currentEditor()->saveCopy(newfn);
	if (documents.getCurrentFileName() != newfn) return;
	if (move) QFile(fn).remove();
	QFile(newfn).setPermissions(permissions); //keep permissions. (better: actually move the file, keeping the inode. but then all that stuff (e.g. master/slave) has to be updated here
}

void Texstudio::fileUtilDelete()
{
	QString fn = documents.getCurrentFileName();
	if (fn.isEmpty()) return;
	if (UtilsUi::txsConfirmWarning(tr("Do you really want to delete the file \"%1\"?").arg(fn)))
		QFile(fn).remove();
}

void Texstudio::fileUtilRevert()
{
	if (!currentEditor()) return;
	QString fn = documents.getCurrentFileName();
	if (fn.isEmpty()) return;
	if (UtilsUi::txsConfirmWarning(tr("Do you really want to revert the file \"%1\"?").arg(documents.getCurrentFileName())))
		currentEditor()->reload();
}

void Texstudio::fileUtilPermissions()
{
	QString fn = documents.getCurrentFileName();
	if (fn.isEmpty()) return;

	QFile f(fn);

	int permissionsRaw = f.permissions();
	int permissionsUnixLike = ((permissionsRaw & 0x7000) >> 4) | (permissionsRaw & 0x0077); //ignore qt "user" flags
	QString permissionsUnixLikeHex = QString::number(permissionsUnixLike, 16);
	QString permissions;
	const QString PERMISSIONSCODES = "rwx";
	int flag = QFile::ReadUser;
	REQUIRE(QFile::ReadUser == 0x400);
	int temp = permissionsUnixLike;
	for (int b = 0; b < 3; b++) {
		for (int i = 0; i < 3; i++, flag >>= 1)
			permissions += (temp & flag) ? PERMISSIONSCODES[i] : QChar('-');
		flag >>= 1;
	}
	QString oldPermissionsUnixLikeHex = permissionsUnixLikeHex, oldPermissions = permissions;

	UniversalInputDialog uid;
	uid.addVariable(&permissionsUnixLikeHex, tr("Numeric permissions"));
	uid.addVariable(&permissions, tr("Verbose permissions"));
	if (uid.exec() == QDialog::Accepted && (permissionsUnixLikeHex != oldPermissionsUnixLikeHex || permissions != oldPermissions)) {
		if (permissionsUnixLikeHex != oldPermissionsUnixLikeHex)
		        permissionsRaw = permissionsUnixLikeHex.toInt(nullptr, 16);
		else {
			permissionsRaw = 0;
			int flag = QFile::ReadUser;
			int p = 0;
			for (int b = 0; b < 3; b++) {
				for (int i = 0; i < 3; i++, flag >>= 1) {
					if (permissions[p] == '-') p++;
					else if (permissions[p] == PERMISSIONSCODES[i]) {
						permissionsRaw |= flag;
						p++;
					} else if (!QString("rwx").contains(permissions[p])) {
                        UtilsUi::txsWarning(QString("invalid character in permission: ") + permissions[p]);
						return;
					}
					if (p >= permissions.length()) p = 0; //wrap around
				}
				flag >>= 1;
			}
		}
		permissionsRaw = ((permissionsRaw << 4) & 0x7000) | permissionsRaw; //use qt "user" as owner flags
		f.setPermissions(QFile::Permissions(permissionsRaw)) ;
	}
}

void Texstudio::fileUtilCopyFileName()
{
	QApplication::clipboard()->setText(documents.getCurrentFileName());
}

void Texstudio::fileUtilCopyMasterFileName()
{
	QApplication::clipboard()->setText(documents.getCompileFileName());
}

void Texstudio::fileClose()
{
	if (!currentEditorView())	return;
	bookmarks->updateBookmarks(currentEditorView());
	QFileInfo fi = currentEditorView()->document->getFileInfo();

    // check if this is last document
    LatexDocument *doc=currentEditorView()->getDocument();
    auto lst=doc->getListOfDocs();
    int cnt_hidden=0;
    int cnt_open=lst.count();
    for(auto *d:lst){
        if(d->isHidden()) ++cnt_hidden;
    }
    if( (cnt_open-cnt_hidden) > 1){
        //not closing last document
        //no need to save all hidden documents
        lst={doc};
    }

    bool closeFile = saveFilesForClosing(lst);

    if(!closeFile){
        return;
    }
    documents.deleteDocument(currentEditorView()->document);
	//UpdateCaption(); unnecessary as called by tabChanged (signal)
    updateTOCs();

    // if editors are split and tabgroup 0 does not contain any editors, move remaining editors to tabgroup 0
    editors->moveAllToGroupZeroifEmpty();

#ifndef NO_POPPLER_PREVIEW
	//close associated embedded pdf viewer
	foreach (PDFDocument *viewer, PDFDocument::documentList())
		if (viewer->autoClose && viewer->getMasterFile() == fi)
			viewer->close();
#endif
}

void Texstudio::fileCloseAll()
{
	bool accept = saveAllFilesForClosing();
	if (accept) {
		closeAllFiles();
	}
}

void Texstudio::fileExit()
{
    if (canCloseNow())
	qApp->quit();
}

void Texstudio::fileExitWithError()
{
    if (canCloseNow()){
        qApp->exit(1);
    }
}

bool Texstudio::saveAllFilesForClosing()
{
    return saveFilesForClosing(documents.getDocuments());
}

bool Texstudio::saveFilesForClosing(const QList<LatexDocument *> &documentList)
{
	LatexEditorView *savedCurrentEditorView = currentEditorView();
    foreach (LatexDocument *doc, documentList) {
repeatAfterFileSavingFailed:
        LatexEditorView *edView=doc->getEditorView();
        if(!edView) continue;
		if (edView->editor->isContentModified()) {
            if(!doc->isHidden())
                editors->setCurrentEditor(edView);
            int ret=QMessageBox::warning(this, TEXSTUDIO,
                                           tr("The document \"%1\" contains unsaved work. "
                                              "Do you want to save it before closing?").arg(edView->displayName()),
                                           QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                           QMessageBox::Save);
            switch (ret) {
            case QMessageBox::Save:
                fileSave(false,edView->editor);
                if (currentEditorView() && currentEditorView()->editor->isContentModified())
					goto repeatAfterFileSavingFailed;
				break;
            case QMessageBox::Discard:
				break;
            case QMessageBox::Cancel:
			default:
				editors->setCurrentEditor(savedCurrentEditorView);
				return false;
			}
		}
	}
	editors->setCurrentEditor(savedCurrentEditorView);
	return true;
}
/*! \brief close all files
 */
void Texstudio::closeAllFiles()
{
	while (currentEditorView())
		documents.deleteDocument(currentEditorView()->document);
#ifndef NO_POPPLER_PREVIEW
	foreach (PDFDocument *viewer, PDFDocument::documentList())
		viewer->close();
#endif
	documents.setMasterDocument(nullptr);
	updateCaption();
    updateTOCs();
}

bool Texstudio::canCloseNow(bool saveSettings)
{
    if(programStopped) return true; // avoid running through here twice. (Qt6/OSX)
	if (!saveAllFilesForClosing()) return false;
#ifndef NO_POPPLER_PREVIEW
	foreach (PDFDocument *viewer, PDFDocument::documentList())
		viewer->saveGeometryToConfig();
#endif
	if (saveSettings)
		this->saveSettings();
	closeAllFiles();
	delete userMacroDialog;
	spellerManager.unloadAll();  //this saves the ignore list
	programStopped = true;
	Guardian::shutdown();
	return true;
}
/*!
 * \brief closeEvent
 * \param e event
 */
void Texstudio::closeEvent(QCloseEvent *e)
{
    if (canCloseNow()) {
        e->accept();
    } else {
        e->ignore();
    }
}

/*!
 * \brief set icons for structure/TOC pane
 * Needs to be rerun on style change (light/dark mode change)
 */
void Texstudio::setStructureSectionIcons()
{
    // load icons for structure view
    QStringList structureIconNames = QStringList() << "part" << "chapter" << "section" << "subsection" << "subsubsection" << "paragraph" << "subparagraph";
    iconSection.resize(structureIconNames.length());
    for (int i = 0; i < structureIconNames.length(); i++)
        iconSection[i] = getRealIconCached(structureIconNames[i],true);
}

/*!
 * \brief update icons in statusbar
 * Necessary on pallete/color scheme change
 */
void Texstudio::updateStatusBarIcons()
{
    QStatusBar *status = statusBar();
    QToolButton *tb = status->findChild<QToolButton *>("structureViewToggle");
    QAction *act = getManagedAction("main/view/show/structureview");
    tb->setIcon(act->icon());
    act = getManagedAction("main/view/show/outputview");
    tb = status->findChild<QToolButton *>("outputViewToggle");
    tb->setIcon(act->icon());
}
/*!
 * \brief update toolbar/statusbar icon in pdf viewer
 * Called on colorSchemeChanged
 */
void Texstudio::updatePDFIcons()
{
#ifndef NO_POPPLER_PREVIEW
    if (PDFDocument::documentList().isEmpty())
        return;
    PDFDocument::documentList().at(0)->updateIcons();
#endif
}

void Texstudio::updateUserMacros(bool updateMenu)
{
	if (updateMenu) configManager.updateUserMacroMenu();
	for (int i = 0; i < configManager.completerConfig->userMacros.size(); i++) {
		configManager.completerConfig->userMacros[i].parseTriggerLanguage(m_languages);
	}
}

/*!
 * \brief open file from recent list
 *
 * The filename is determind from the sender-action, where it is encoded in data.
 */
void Texstudio::fileOpenRecent()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	QString fn = action->data().toString();
	if (!QFile::exists(fn)) {
		if (UtilsUi::txsConfirmWarning(tr("The file \"%1\" does not exist anymore. Do you want to remove it from the recent file list?").arg(fn))) {
			if (configManager.recentFilesList.removeAll(fn))
				configManager.updateRecentFiles();
			return;
		}
	}
	load(fn);
}

void Texstudio::fileOpenAllRecent()
{
	foreach (const QString &s, configManager.recentFilesList)
		load(s);
}

QRect appendToBottom(QRect r, const QRect &s)
{
	r.setBottom(r.bottom() + s.height());
	return r;
}

void Texstudio::fileRecentList()
{
	if (fileSelector) fileSelector.data()->deleteLater();
	fileSelector = new FileSelector(editors, true);

	fileSelector.data()->init(QStringList() << configManager.recentProjectList << configManager.recentFilesList, 0);

    connect(fileSelector.data(), SIGNAL(fileChoosen(QString,int,int,int)), SLOT(fileDocumentOpenFromChoosen(QString,int,int,int)));
    fileSelector.data()->setVisible(true);
}
/*!
 * \brief clear recent file list
 */
void Texstudio::fileClearRecentList()
{
    configManager.recentFilesList.clear();
    configManager.recentProjectList.clear();
    configManager.updateRecentFiles();
}

void Texstudio::viewDocumentListHidden()
{
	if (fileSelector) fileSelector.data()->deleteLater();
	fileSelector = new FileSelector(editors, true);

	QStringList hiddenDocs;
	foreach (LatexDocument *d, documents.hiddenDocuments)
		hiddenDocs << d->getFileName();
	fileSelector.data()->init(hiddenDocs, 0);

    connect(fileSelector.data(), SIGNAL(fileChoosen(QString,int,int,int)), SLOT(fileDocumentOpenFromChoosen(QString,int,int,int)));
	fileSelector.data()->setVisible(true);
}

void Texstudio::fileDocumentOpenFromChoosen(const QString &doc, int duplicate, int lineNr, int column)
{
	Q_UNUSED(duplicate)
	if (!QFile::exists(doc)) {
		if (UtilsUi::txsConfirmWarning(tr("The file \"%1\" does not exist anymore. Do you want to remove it from the recent file list?").arg(doc))) {
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

bool mruEditorViewLessThan(const LatexEditorView *e1, const LatexEditorView *e2)
{
	return e1->lastUsageTime > e2->lastUsageTime;
}

void Texstudio::viewDocumentList()
{
	if (fileSelector) fileSelector.data()->deleteLater();
	fileSelector = new FileSelector(editors, false);

	LatexEditorView *curEdView = currentEditorView();
	int curIndex = 0;
	QList<LatexEditorView *> editorList = editors->editors();

	if (configManager.mruDocumentChooser) {
		std::sort(editorList.begin(), editorList.end(), mruEditorViewLessThan);
		if (editorList.size() > 1)
			if (editorList.first() == currentEditorView())
				curIndex = 1;
	}

	int i = 0;
	QStringList names;
	foreach (LatexEditorView *edView, editorList) {
		names << edView->displayName();
		if (!configManager.mruDocumentChooser && edView == curEdView) curIndex = i;
		i++;
	}

	fileSelector.data()->init(names, curIndex);
    connect(fileSelector.data(), SIGNAL(fileChoosen(QString,int,int,int)), SLOT(viewDocumentOpenFromChoosen(QString,int,int,int)));
	fileSelector.data()->setVisible(true);
}

void Texstudio::viewDocumentOpenFromChoosen(const QString &doc, int duplicate, int lineNr, int column)
{
	if (duplicate < 0) return;
	foreach (LatexEditorView *edView, editors->editors()) {
		QString  name = edView->displayName();
		if (name == doc) {
			duplicate -= 1;
			if (duplicate < 0) {
				editors->setCurrentEditor(edView);
				if (lineNr >= 0)
					edView->editor->setCursorPosition(lineNr, column);
				edView->setFocus();
				return;
			}
		}
	}
}

void Texstudio::fileOpenFirstNonOpen()
{
	foreach (const QString &f, configManager.recentFilesList)
		if (!getEditorViewFromFileName(f)) {
			load(f);
			break;
		}
}

void Texstudio::fileOpenRecentProject()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	QString fn = action->data().toString();
	if (!QFile::exists(fn)) {
		if (UtilsUi::txsConfirmWarning(tr("The file \"%1\" does not exist anymore. Do you want to remove it from the recent file list?").arg(fn))) {
			if (configManager.recentProjectList.removeAll(fn))
				configManager.updateRecentFiles();
			return;
		}
	}
	load(fn, true);
}

void Texstudio::loadSession(const QString &fileName)
{
	Session s;
	if (!s.load(fileName)) {
		UtilsUi::txsCritical(tr("Loading of session failed."));
		return;
	}
	restoreSession(s);
}

void Texstudio::fileLoadSession()
{
	QString openDir = QDir::homePath();
	if (currentEditorView()) {
		LatexDocument *doc = currentEditorView()->document;
		if (doc->getMasterDocument()) {
			openDir = doc->getMasterDocument()->getFileInfo().path();
		} else {
			openDir = doc->getFileInfo().path();
		}
	}
    QString fn = FileDialog::getOpenFileName(this, tr("Load Session"), openDir, tr("TeXstudio Session") + " (*.txss2 *.txss)");
	if (fn.isNull()) return;
	loadSession(fn);
	recentSessionList->addFilenameToList(fn);
}

void Texstudio::fileSaveSession()
{
	QString openDir = QDir::homePath();
	if (currentEditorView()) {
		LatexDocument *doc = currentEditorView()->document;
		if (doc->getMasterDocument()) {
			openDir = replaceFileExtension(doc->getMasterDocument()->getFileName(), Session::fileExtension());
		} else {
			openDir = replaceFileExtension(doc->getFileName(), Session::fileExtension());
		}
	}

	QString fn = FileDialog::getSaveFileName(this, tr("Save Session"), openDir, tr("TeXstudio Session") + " (*." + Session::fileExtension() + ")");
	if (fn.isNull()) return;
    if(!fn.endsWith(Session::fileExtension())){
        fn=replaceFileExtension(fn, Session::fileExtension(),true);
    }
	if (!getCurrentSession().save(fn, configManager.sessionStoreRelativePaths)) {
		UtilsUi::txsCritical(tr("Saving of session failed."));
		return;
	}
	recentSessionList->addFilenameToList(fn);
}
/*!
 * \brief restore session s
 *
 * closes all files and loads all files given in session s
 * \param s session
 * \param showProgress
 * \param warnMissing give warning if files are missing
 */
void Texstudio::restoreSession(const Session &s, bool showProgress, bool warnMissing)
{
    fileCloseAll();

    cursorHistory->setInsertionEnabled(false);
    QProgressDialog progress(this);
    if (showProgress) {
        progress.setMaximum(s.files().size());
        progress.setCancelButton(nullptr);
        progress.setMinimumDuration(3000);
        progress.setLabel(new QLabel());
    }
    recheckLabels = false; // impede label rechecking on hidden docs

    bookmarks->setBookmarks(s.bookmarks()); // set before loading, so that bookmarks are automatically restored on load

    QStringList missingFiles;
    for (int i = 0; i < s.files().size(); i++) {
        FileInSession f = s.files().at(i);

        if (showProgress) {
            progress.setValue(i);
            progress.setLabelText(QFileInfo(f.fileName).fileName());
        }
        LatexEditorView *edView = load(f.fileName, f.fileName == s.masterFile(), false, false, true);
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
            editors->moveToTabGroup(edView, f.editorGroup, -1);
        } else {
            missingFiles.append(f.fileName);
        }
    }
    // set vertical split
    if(s.getSplitVertical()){
        editors->changeSplitOrientation();
    }
    //qDebug()<<"loaded:"<<tm.elapsed();
    // update ref/labels in one go;
    QList<LatexDocument *> completedDocs;
    foreach (LatexDocument *doc, documents.getDocuments()) {
        doc->recheckRefsLabels();
        if (completedDocs.contains(doc))
            continue;

        doc->updateLtxCommands(true);
        completedDocs << doc->getListOfDocs();
    }
    recheckLabels = true;
    //qDebug()<<"labels:"<<tm.elapsed();

    if (showProgress) {
        progress.setValue(progress.maximum());
    }
    activateEditorForFile(s.currentFile());
    cursorHistory->setInsertionEnabled(true);

    if (!s.PDFFile().isEmpty()) {
        runInternalCommand("txs:///view-pdf-internal", QFileInfo(s.PDFFile()), enquoteStr(s.PDFFile()) +" "+ (s.PDFEmbedded() ? "--embedded" : "--windowed"));
    }
    // update completer
    if (currentEditorView())
        updateCompleter(currentEditorView());

    if (warnMissing && !missingFiles.isEmpty()) {
        UtilsUi::txsInformation(tr("The following files could not be loaded:") + "\n" + missingFiles.join("\n"));
    }
}

Session Texstudio::getCurrentSession()
{
	Session s;

	foreach (LatexEditorView *edView, editors->editors()) {
		FileInSession f;
		f.fileName = edView->editor->fileName();
		f.editorGroup = editors->tabGroupIndexFromEditor(edView);
		f.cursorLine = edView->editor->cursor().lineNumber();
		f.cursorCol = edView->editor->cursor().columnNumber();
		f.firstLine = edView->editor->getFirstVisibleLine();
		f.foldedLines = edView->document->foldedLines();
		if (!f.fileName.isEmpty())
			s.addFile(f);
	}
	s.setMasterFile(documents.masterDocument ? documents.masterDocument->getFileName() : "");
	s.setCurrentFile(currentEditorView() ? currentEditor()->fileName() : "");

    s.setSplitVertical(editors->getSplitVertical());

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

void Texstudio::MarkCurrentFileAsRecent()
{
    if(!currentEditorView()) return;
	configManager.addRecentFile(getCurrentFileName(), documents.masterDocument == currentEditorView()->document);
}

//////////////////////////// EDIT ///////////////////////
void Texstudio::editUndo()
{
	if (!currentEditorView()) return;

	QVariant zw = currentEditor()->property("undoRevision");
	int undoRevision = zw.canConvert<int>() ? zw.toInt() : 0;

	if (currentEditor()->document()->canUndo()) {
		currentEditor()->undo();
		if (undoRevision > 0) {
			undoRevision = -1;
			currentEditor()->setProperty("undoRevision", undoRevision);
		}
	} else {
		if (configManager.svnUndo && (undoRevision >= 0)) {
			svnUndo();
		}
	}
}

void Texstudio::editRedo()
{
	if (!currentEditorView()) return;

	QVariant zw = currentEditor()->property("undoRevision");
	int undoRevision = zw.canConvert<int>() ? zw.toInt() : 0;

	if (currentEditor()->document()->canRedo()) {
		currentEditorView()->editor->redo();
	} else {
		if (configManager.svnUndo && (undoRevision > 0)) {
			svnUndo(true);
		}
	}
}

void Texstudio::editDebugUndoStack()
{
	if (!currentEditor()) return;
	QString history = currentEditor()->document()->debugUndoStack();
	fileNew();
	currentEditor()->document()->setText(history, false);
}

void Texstudio::editCopy()
{
	if ((!currentEditor() || !currentEditor()->hasFocus()) &&
	        outputView->childHasFocus() ) {
		outputView->copy();
		return;
	}
	if (!currentEditorView()) return;
	currentEditorView()->editor->copy();
}

void Texstudio::editPaste()
{
	if (!currentEditorView()) return;

	const QMimeData *d = QApplication::clipboard()->mimeData();
    if ((d->hasFormat("application/x-openoffice-embed-source-xml;windows_formatname=\"Star Embed Source (XML)\"")||d->hasFormat("application/x-qt-windows-mime;value=\"Star Embed Source (XML)\"")) && d->hasFormat("text/plain")) {
		// workaround for LibreOffice (im "application/x-qt-image" has a higher priority for them than "text/plain")
        QDocumentCursor cur = currentEditorView()->editor->cursor();
        if (LatexTables::inTableEnv(cur)){
            // table is defined
            // Insert with "&" as separator
            QString txt = d->text();
            txt = txt.replace("\t", " & ");
            txt = txt.replace("\n", " \\\\\n");
            QMimeData md;
            md.setText(txt);
            currentEditorView()->editor->insertFromMimeData(&md);
        }else{
            // no table defined, call wizard
            quickTabular(d);
        }
		return;
	}

	foreach (const QString &format, d->formats()) {
		// formats is a priority order. Use the first (== most suitable) format
		if (format == "text/uri-list") {
			QList<QUrl> uris = d->urls();

			bool onlyLocalImages = true;
			for (int i = 0; i < uris.length(); i++) {
				QFileInfo fi = QFileInfo(uris.at(i).toLocalFile());
				if (!fi.exists() || !InsertGraphics::imageFormats().contains(fi.suffix())) {
					onlyLocalImages = false;
					break;
				}
			}

			if (onlyLocalImages) {
				for (int i = 0; i < uris.length(); i++) {
					quickGraphics(uris.at(i).toLocalFile());
				}
			} else {
				currentEditorView()->paste();
			}
			return;
		} else if (format == "text/plain" || format == "text/html") {
			currentEditorView()->paste();
			return;
		} else if ((format == "application/x-qt-image" || format.startsWith("image/")) && d->hasImage()) {
			editPasteImage(qvariant_cast<QImage>(d->imageData()));
			return;
		}
	}
	currentEditorView()->paste();  // fallback
}

void Texstudio::editPasteImage(QImage image)
{
	if (!currentEditorView()) return;
	static QString filenameSuggestion;  // keep for future calls
	QString rootDir = currentEditorView()->document->getRootDocument()->getFileInfo().absolutePath();
	if (filenameSuggestion.isEmpty()) {
		filenameSuggestion = rootDir + "/screenshot001.png";
	}
	QStringList filters;
    filters << "*.png";
	QString filter = tr("Image Formats (%1)").arg(filters.join(" "));
	filenameSuggestion = getNonextistentFilename(filenameSuggestion, rootDir);
	QString filename = FileDialog::getSaveFileName(this, tr("Save Image"), filenameSuggestion, filter, &filter);
	if (filename.isEmpty()) return;
	filenameSuggestion = filename;

	if (!image.save(filename)) {
		UtilsUi::txsCritical(tr("Could not save the image file."));
		return;
	}
	quickGraphics(filename);
}

void Texstudio::editPasteLatex()
{
	if (!currentEditorView()) return;
	// manipulate clipboard text
	QClipboard *clipboard = QApplication::clipboard();
	QString originalText = clipboard->text();
	QString newText = textToLatex(originalText);
	//clipboard->setText(newText);
	// insert
	//currentEditorView()->editor->paste();
	QMimeData md;
	md.setText(newText);
	currentEditorView()->editor->insertFromMimeData(&md);
}

void Texstudio::convertToLatex()
{
	if (!currentEditorView()) return;
	// get selection and change it
	QString originalText = currentEditor()->cursor().selectedText();
	QString newText = textToLatex(originalText);
	// insert
	currentEditor()->write(newText);
}

void Texstudio::editDeleteLine()
{
	if (!currentEditorView()) return;
	currentEditorView()->deleteLines(true, true);
}

void Texstudio::editCutLine()
{
    if (!currentEditorView()) return;
    currentEditorView()->cutLines();
}

void Texstudio::editDeleteToEndOfLine()
{
	if (!currentEditorView()) return;
	currentEditorView()->deleteLines(false, true);
}

void Texstudio::editDeleteFromStartOfLine()
{
	if (!currentEditorView()) return;
	currentEditorView()->deleteLines(true, false);
}

void Texstudio::editMoveLineUp()
{
	if (!currentEditorView()) return;
	currentEditorView()->moveLines(-1);
}

void Texstudio::editMoveLineDown()
{
	if (!currentEditorView()) return;
	currentEditorView()->moveLines(1);
}

void Texstudio::editDuplicateLine()
{
	if (!currentEditor()) return;
	QEditor *ed = currentEditor();
	QList<QDocumentCursor> cursors = ed->cursors();
    for (int i = 0; i < cursors.length(); i++){
        cursors[i].setAutoUpdated(false);
    }
	QList<QPair<int, int> > blocks = currentEditorView()->getSelectedLineBlocks();
	for (int i = blocks.size() - 1; i >= 0; i--) {
		QDocumentCursor edit = ed->document()->cursor(blocks[i].first, 0, blocks[i].second);
		QString text = edit.selectedText();
        edit.selectionEnd().insertText("\n" + text);
	}
    if(cursors.length()>0)
        ed->setCursor(cursors[0]);
}

void Texstudio::editSortLines()
{
	if (!currentEditorView()) return;
	QStringList sortingOptions = QStringList() << tr("Ascending") << tr("Descending") << tr("No Sorting") << tr("Random (Shuffle)");
	static int sorting; configManager.registerOption("Editor/Sort Lines/Method", &sorting, 0);
	static bool completelines; configManager.registerOption("Editor/Sort Lines/Complete Lines", &completelines, false);
	static bool casesensitive; configManager.registerOption("Editor/Sort Lines/Case Sensitive", &casesensitive, false);
	static bool removeduplicates; configManager.registerOption("Editor/Sort Lines/Remove Duplicates", &removeduplicates, false);
	UniversalInputDialog dialog;
	dialog.addVariable(&sorting, sortingOptions, tr("Sorting"));
	dialog.addVariable(&completelines, tr("Complete Lines"));
	dialog.addVariable(&casesensitive, tr("Case Sensitive"));
	dialog.addVariable(&removeduplicates, tr("Remove Duplicates"));
	if (dialog.exec() == QDialog::Accepted)
		currentEditorView()->sortSelectedLines(static_cast<LatexEditorView::LineSorting>(sorting), casesensitive ? Qt::CaseSensitive : Qt::CaseInsensitive, completelines, removeduplicates);
}

void Texstudio::editAlignMirrors()
{
	if (!currentEditor()) return;
	currentEditorView()->alignMirrors();
}

void Texstudio::editEraseWordCmdEnv()
{
	if (!currentEditorView()) return;
	QDocumentCursor cursor = currentEditorView()->editor->cursor();
	if (cursor.isNull()) return;
	QString line = cursor.line().text();
	QDocumentLineHandle *dlh = cursor.line().handle();
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
	        && (col == 0 || line.at(col - 1).isSpace()))	// cmd is at start or previous char is space: non-ambiguous situation like word|\cmd
		// don't need to finally check for command |\c should be handled like \|c for any c (even space and empty)
	{
		cursor.movePosition(1);
	}

	TokenList tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	int tkPos = Parsing::getTokenAtCol(tl, cursor.columnNumber());
	Token tk;
	if (tkPos > -1)
		tk = tl.at(tkPos);

	switch (tk.type) {
    case Token::commandUnknown:
        [[gnu::fallthrough]];
	case Token::command:
		command = tk.getText();
		if (command == "\\begin" || command == "\\end") {
			value = Parsing::getArg(tl.mid(tkPos + 1), dlh, 0, ArgumentList::Mandatory);
			//remove environment (surrounding)
			currentEditorView()->editor->document()->beginMacro();
			cursor.select(QDocumentCursor::WordOrCommandUnderCursor);
			cursor.removeSelectedText();
			// remove curly brakets as well
			if (cursor.nextChar() == QChar('{')) {
				cursor.deleteChar();
				line = cursor.line().text();
				int col = cursor.columnNumber();
				int i = findClosingBracket(line, col);
				if (i > -1) {
					cursor.movePosition(i - col + 1, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
					cursor.removeSelectedText();
					QDocument *doc = currentEditorView()->editor->document();
					QString searchWord = "\\end{" + value + "}";
					QString inhibitor = "\\begin{" + value + "}";
					bool backward = (command == "\\end");
					int step = 1;
					if (backward) {
						qSwap(searchWord, inhibitor);
						step = -1;
					}
					int startLine = cursor.lineNumber();
					int startCol = cursor.columnNumber();
					int endLine = doc->findLineContaining(searchWord, startLine, Qt::CaseSensitive, backward);
					int inhibitLine = doc->findLineContaining(inhibitor, startLine, Qt::CaseSensitive, backward); // not perfect (same line end/start ...)
					while (inhibitLine > 0 && endLine > 0 && inhibitLine * step < endLine * step) {
						endLine = doc->findLineContaining(searchWord, endLine + step, Qt::CaseSensitive, backward); // not perfect (same line end/start ...)
						inhibitLine = doc->findLineContaining(inhibitor, inhibitLine + step, Qt::CaseSensitive, backward);
					}
					if (endLine > -1) {
						line = doc->line(endLine).text();
						int start = line.indexOf(searchWord);
						cursor.moveTo(endLine, start);
						cursor.movePosition(searchWord.length(), QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
						cursor.removeSelectedText();
						cursor.moveTo(startLine, startCol); // move cursor back to text edit pos
					}
				}
			}

			currentEditorView()->editor->document()->endMacro();
		} else {
			currentEditorView()->editor->document()->beginMacro();
			cursor.select(QDocumentCursor::WordOrCommandUnderCursor);
			cursor.removeSelectedText();
			// remove curly brakets as well
			if (cursor.nextChar() == QChar('{')) {
				cursor.deleteChar();
				line = cursor.line().text();
				int col = cursor.columnNumber();
				int i = findClosingBracket(line, col);
				if (i > -1) {
					cursor.moveTo(cursor.lineNumber(), i);
					cursor.deleteChar();
					cursor.moveTo(cursor.lineNumber(), col);
				}
			}
			currentEditorView()->editor->document()->endMacro();
		}
		break;

	default:
		cursor.select(QDocumentCursor::WordUnderCursor);
		cursor.removeSelectedText();
		break;
	}
	currentEditorView()->editor->setCursor(cursor);
}

void Texstudio::editGotoDefinition(QDocumentCursor c)
{
	if (!currentEditorView()) return;
	if (!c.isValid()) c = currentEditor()->cursor();
	saveCurrentCursorToHistory();

	LatexDocument *doc = qobject_cast<LatexDocument *>(c.document());
	Token tk = Parsing::getTokenAtCol(c.line().handle(), c.columnNumber());

	switch (tk.type) {
	case Token::labelRef:
	case Token::labelRefList: {
		QMultiHash<QDocumentLineHandle *, int> defs = doc->getLabels(tk.getText());
		if (defs.isEmpty()) return;
        QDocumentLineHandle *target = defs.keys().constFirst();
		LatexEditorView *edView = getEditorViewFromHandle(target);
		if (!edView) return;
		if (edView != currentEditorView()) {
			editors->setCurrentEditor(edView);
		}
		edView->gotoLineHandleAndSearchLabel(target, tk.getText());
		break;
	}
	case Token::bibItem: {
		QString bibID = trimLeft(tk.getText());
		// try local \bibitems
		QMultiHash<QDocumentLineHandle *, int> defs = doc->getBibItems(bibID);
		if (!defs.isEmpty()) {
            QDocumentLineHandle *target = defs.keys().constFirst();
			bool found = currentEditorView()->gotoLineHandleAndSearchBibItem(target, bibID);
			if (found) break;
		}
		// try bib files
		QString bibFile = currentEditorView()->document->findFileFromBibId(bibID);
		LatexEditorView *edView = getEditorViewFromFileName(bibFile);
		if (!edView) {
			if (!load(bibFile)) return;
			edView = currentEditorView();
		}
		int line = edView->document->findLineRegExp("@\\w+{\\s*" + bibID, 0, Qt::CaseSensitive, true, true);
		if (line < 0) {
			line = edView->document->findLineContaining(bibID); // fallback in case the above regexp does not reflect the most general case
			if (line < 0) return;
		}
		int col = edView->document->line(line).text().indexOf(bibID);
		if (col < 0) col = 0;
		gotoLine(line, col, edView);
		break;
	}
	case Token::commandUnknown:
	case Token::command:
	case Token::beginEnv:
	case Token::env: {
		QDocumentLineHandle *target = doc->findCommandDefinition(tk.getText());
		if (target) {
			// command is user-defined, jump to definition
			LatexEditorView *edView = getEditorViewFromHandle(target);
			if (edView) {
				if (edView != currentEditorView()) {
					editors->setCurrentEditor(edView);
				}
				edView->gotoLineHandleAndSearchString(target, tk.getText());
				break;
			}
		}
		// command might be defined by a package, jump to \usepackage (if possible)
		QString command = tk.getText();
		if (tk.type == Token::beginEnv || tk.type == Token::env) {
			command = "\\begin{" + command + "}";
		}
		QString package = doc->parent->findPackageByCommand(command);
		package.chop(4);
		// skip builtin packages (we cannot goto the \usepackage in this case)
		if (package == "tex" || package == "latex-document")
			return;
		target = doc->findUsePackage(package);
		if (!target) return;
		LatexEditorView *edView = getEditorViewFromHandle(target);
		if (!edView) return;
		if (edView != currentEditorView()) {
			editors->setCurrentEditor(edView);
		}
		edView->gotoLineHandleAndSearchString(target, tk.getText());
		break;
	}
	default:;
	}
}

void Texstudio::editHardLineBreak()
{
	if (!currentEditorView()) return;
	UniversalInputDialog dialog;
	dialog.addVariable(&configManager.lastHardWrapColumn, tr("Insert hard line breaks after so many characters:"));
	dialog.addVariable(&configManager.lastHardWrapSmartScopeSelection, tr("Smart scope selecting"));
	dialog.addVariable(&configManager.lastHardWrapJoinLines, tr("Join lines before wrapping"));
	if (dialog.exec() == QDialog::Accepted)
		currentEditorView()->insertHardLineBreaks(configManager.lastHardWrapColumn, configManager.lastHardWrapSmartScopeSelection, configManager.lastHardWrapJoinLines);
}

void Texstudio::editHardLineBreakRepeat()
{
	if (!currentEditorView()) return;
	currentEditorView()->insertHardLineBreaks(configManager.lastHardWrapColumn, configManager.lastHardWrapSmartScopeSelection, configManager.lastHardWrapJoinLines);
}

void Texstudio::editSpell()
{
	if (!currentEditorView()) {
		UtilsUi::txsWarning(tr("No document open"));
		return;
	}
	SpellerUtility *su = spellerManager.getSpeller(currentEditorView()->getSpeller());
	if (!su) return; // getSpeller already gives a warning message
	if (su->name() == "<none>") {
		UtilsUi::txsWarning(tr("No dictionary available."));
		return;
	}
	if (!spellDlg) spellDlg = new SpellerDialog(this, su);
	spellDlg->setEditorView(currentEditorView());
	spellDlg->startSpelling();
}

void Texstudio::editThesaurus(int line, int col)
{
	if (!ThesaurusDialog::retrieveDatabase()) {
		QMessageBox::warning(this, tr("Error"), tr("Can't load Thesaurus Database"));
		return;
	}
	ThesaurusDialog *thesaurusDialog = new ThesaurusDialog(this);
	QString word;
	if (currentEditorView()) {
		QDocumentCursor m_cursor = currentEditorView()->editor->cursor();
		if (line > -1 && col > -1) {
			m_cursor.moveTo(line, col);
		}
		if (m_cursor.hasSelection()) word = m_cursor.selectedText();
		else {
			m_cursor.select(QDocumentCursor::WordUnderCursor);
			word = m_cursor.selectedText();
		}
		word = latexToPlainWord(word);
		thesaurusDialog->setSearchWord(word);
		if (thesaurusDialog->exec()) {
			QString replace = thesaurusDialog->getReplaceWord();
			m_cursor.document()->clearLanguageMatches();
			m_cursor.insertText(replace);
		}
	}
	delete thesaurusDialog;
}

void Texstudio::editChangeLineEnding()
{
	if (!currentEditorView()) return;
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	currentEditorView()->editor->document()->setLineEnding(QDocument::LineEnding(action->data().toInt()));
	updateCaption();
}

void Texstudio::editSetupEncoding()
{
	if (!currentEditorView()) return;
	EncodingDialog enc(this, currentEditorView()->editor);
	enc.exec();
	updateCaption();
}

void Texstudio::editInsertUnicode()
{
	if (!currentEditorView()) return;
	QDocumentCursor c = currentEditor()->cursor();
	if (!c.isValid()) return;
	uint curPoint = 0;
	if (c.hasSelection()) {
		QString sel = c.selectedText();
		if (sel.length() == 1) curPoint = sel[0].unicode();
		else if (sel.length() == 2 && sel.at(0).isHighSurrogate() && sel.at(1).isLowSurrogate()) {
			curPoint = sel.toUcs4().value(0, 0);
		} else c.setAnchorColumnNumber(c.columnNumber());
		currentEditor()->setCursor(c);
	}
    QPointF offset;
	UnicodeInsertion *uid = new UnicodeInsertion (currentEditorView(), curPoint);
	if (!currentEditor()->getPositionBelowCursor(offset, uid->width(), uid->height())) {
		delete uid;
		return;
	}
	connect(uid, SIGNAL(insertCharacter(QString)), currentEditor(), SLOT(insertText(QString)));
	connect(uid, SIGNAL(destroyed()), currentEditor(), SLOT(setFocus()));
	connect(currentEditor(), SIGNAL(cursorPositionChanged()), uid, SLOT(close()));
	connect(currentEditor(), SIGNAL(visibleLinesChanged()), uid, SLOT(close()));
	connect(currentEditor()->document(), SIGNAL(contentsChanged()), uid, SLOT(close()));

    uid->move(currentEditor()->mapTo(uid->parentWidget(), offset.toPoint()));
	this->unicodeInsertionDialog = uid;
	uid->show();
	uid->setFocus();
}

void changeCase(QEditor *editor, QString(*method)(QString))
{
	if (!editor) return;
	QList<QDocumentCursor> cs = editor->cursors();
	bool allEmpty = true;
	foreach (QDocumentCursor c, cs)
		if (!c.selectedText().isEmpty()) {
			allEmpty = false;
			break;
		}
	if (allEmpty) return;

	editor->document()->beginMacro();
	foreach (QDocumentCursor c, editor->cursors())
		c.replaceSelectedText( method(c.selectedText()) );
	editor->document()->endMacro();
}
/*!
 * Helperfunction to convert a string to lower case.
 * \param in input string
 * \result string in lower case
 */
QString txsToLower(QString in)
{
	return in.toLower();
}

/*!
 * Converts the selected text to lower case.
 */
void Texstudio::editTextToLowercase()
{
	changeCase(currentEditor(), &txsToLower);
}
/*!
 * Helperfunction to convert a string to upper case.
 * \param in input string
 * \result string in upper case
 */

QString txsToUpper(QString in)
{
	return in.toUpper();
}

/*!
 * Converts the selected text to upper case.
 */
void Texstudio::editTextToUppercase()
{
	changeCase(currentEditor(), &txsToUpper);
}

/*!
 * Converts the selected text to title case. Small words like a,an etc. are not converted.
 * \param smart: Words containing capital letters are not converted because the are assumed to be acronymes.
 */
void Texstudio::editTextToTitlecase(bool smart)
{
	if (!currentEditorView()) return;
	QDocumentCursor m_cursor = currentEditorView()->editor->cursor();
	QString text = m_cursor.selectedText();
	if (text.isEmpty()) return;
	m_cursor.beginEditBlock();
	// easier to be done in javascript
	scriptengine *eng = new scriptengine();
	eng->setEditorView(currentEditorView());
	QString script =
	    "/* \n" \
	    "	* To Title Case 2.1  http://individed.com/code/to-title-case/ \n" \
	    "	* Copyright © 20082013 David Gouch. Licensed under the MIT License.\n" \
	    "*/ \n" \
	    "toTitleCase = function(text){\n" \
	    "var smallWords = /^(a|an|and|as|at|but|by|en|for|if|in|nor|of|on|or|per|the|to|vs?\\.?|via)$/i;\n" \
	    "return text.replace(/[A-Za-z0-9\\u00C0-\\u00FF]+[^\\s-]*/g, function(match, index, title){\n" \
	    "if (index > 0 && index + match.length !== title.length &&\n" \
	    "  match.search(smallWords) > -1 && title.charAt(index - 2) !== \":\" &&\n" \
	    "  (title.charAt(index + match.length) !== '-' || title.charAt(index - 1) === '-') &&\n" \
	    "  title.charAt(index - 1).search(/[^\\s-]/) < 0) {\n" \
	    "    return match.toLowerCase();\n" \
	    "}\n";
	if (smart) {
		script +=
		    "if (match.substr(1).search(/[A-Z]|\\../) > -1) {\n" \
		    "return match;\n" \
		    "}\n" \
		    "return match.charAt(0).toUpperCase() + match.substr(1);\n";
	} else {
		script +=
		    "return match.charAt(0).toUpperCase() + match.substr(1).toLowerCase();\n";
	}
	script +=
	    "});\n" \
	    "};\n" \
	    "editor.replaceSelectedText(toTitleCase)";
	eng->setScript(script);
	eng->run();

	m_cursor.endEditBlock();

}

void Texstudio::editTextToTitlecaseSmart()
{
	editTextToTitlecase(true);
}

void Texstudio::editFind()
{
#ifndef NO_POPPLER_PREVIEW
    QWidget *w = QApplication::focusWidget();
    while (w && !qobject_cast<PDFDocument *>(w))
        w = w->parentWidget();

    if (qobject_cast<PDFDocument *>(w)) {
        PDFDocument *focusedPdf = qobject_cast<PDFDocument *>(w);
        if (focusedPdf->embeddedMode) {
            focusedPdf->search();
            return;
        }
    }
#endif
    if (!currentEditor()) return;
    currentEditor()->find();
}

/////////////// CONFIG ////////////////////
void Texstudio::readSettings(bool reread)
{
    QuickDocumentDialog::registerOptions(configManager);
    QuickBeamerDialog::registerOptions(configManager);
    buildManager.registerOptions(configManager);
    configManager.registerOption("Files/Default File Filter", &selectedFileFilter);
    configManager.registerOption("PDFSplitter", &pdfSplitterRel, 0.5);

    configManager.buildManager = &buildManager;
    scriptengine::buildManager = &buildManager;
    scriptengine::app = this;
    QSettings *config = configManager.readSettings(reread);
    mCompleterCommandsNeedsUpdate=true;
    config->beginGroup("texmaker");

    QRect screen = QGuiApplication::primaryScreen()->availableGeometry();
    int w = config->value("Geometries/MainwindowWidth", screen.width() - 100).toInt();
    int h = config->value("Geometries/MainwindowHeight", screen.height() - 100).toInt() ;
    int x = config->value("Geometries/MainwindowX", screen.x() + 10).toInt();
    int y = config->value("Geometries/MainwindowY", screen.y() + 10).toInt() ;
    screen = UtilsUi::getAvailableGeometryAt(QPoint(x, y));
    if (screen.width()>100 && !screen.contains(x, y)) {
        // top left is not on screen
        x = screen.x() + 10;
        y = screen.y() + 10;
        if (x + w > screen.right()) w = screen.width() - 100;
        if (y + h > screen.height()) h = screen.height() - 100;
    }
    resize(w, h);
    move(x, y);
    windowstate = config->value("MainWindowState").toByteArray();
    stateFullScreen = config->value("MainWindowFullssscreenState").toByteArray();
    tobemaximized = config->value("MainWindow/Maximized", false).toBool();
    tobefullscreen = config->value("MainWindow/FullScreen", false).toBool();

    //dark mode menu
    if(darkMode && configManager.useTexmakerPalette){
        QString ownStyle;
        ownStyle="QMenuBar {background: #404040 }";
        ownStyle+="QMenuBar::item { background: transparent;}";
        ownStyle+="QMenuBar::item:selected { background: #808080;}";
        ownStyle+="QMenuBar::item:pressed { background: #888888; }";
        ownStyle+="QCheckBox::indicator:unchecked { background: #404040; }";
        ownStyle+="QTableView::indicator:unchecked { background-color: #404040 }";
        ownStyle+="QListView::indicator:unchecked { background-color: #404040 }";
        ownStyle+="QTabBar::tab {background-color: #404040 }";
        ownStyle+="QTabBar::tab:selected {background-color: #606060 }";
        setStyleSheet(ownStyle);
    }

    spellerManager.setIgnoreFilePrefix(configManager.configFileNameBase);
    spellerManager.setDictPaths(configManager.parseDirList(configManager.spellDictDir));
    spellerManager.setDefaultSpeller(configManager.spellLanguage);

    ThesaurusDialog::setUserPath(configManager.configFileNameBase);
    ThesaurusDialog::prepareDatabase(configManager.parseDir(configManager.thesaurus_database));

    symbolListModel = new SymbolListModel(config->value("Symbols/UsageCount").toMap(),
                                          config->value("Symbols/FavoriteIDs").toStringList());
    symbolListModel->setDarkmode(darkMode);
    hiddenLeftPanelWidgets = config->value("Symbols/hiddenlists", "").toString();  // TODO: still needed?

    configManager.editorKeys = QEditor::getEditOperations(false); //this will also initialize the default keys
    configManager.editorAvailableOperations = QEditor::getAvailableOperations();
    if (config->value("Editor/Use Tab for Move to Placeholder", false).toBool()) {
        //import deprecated option
        QEditor::addEditOperation(QEditor::NextPlaceHolder, Qt::ControlModifier, Qt::Key_Tab);
        QEditor::addEditOperation(QEditor::PreviousPlaceHolder, Qt::ShiftModifier | Qt::ControlModifier, Qt::Key_Backtab);
        QEditor::addEditOperation(QEditor::CursorWordLeft, Qt::ControlModifier, Qt::Key_Left);
        QEditor::addEditOperation(QEditor::CursorWordRight, Qt::ControlModifier, Qt::Key_Right);
    }
    // import and remove old key mapping
    {
        config->beginGroup("Editor Key Mapping");
        QStringList sl = config->childKeys();
        if (!sl.empty()) {
            foreach (const QString &key, sl) {
                int k = key.toInt();
                if (k == 0) continue;
                int operationID = config->value(key).toInt();
                QString defaultKey = configManager.editorKeys.key(operationID);
                if (!defaultKey.isNull()) {
                    configManager.editorKeys.remove(defaultKey);
                }
                configManager.editorKeys.insert(QKeySequence(k).toString(), config->value(key).toInt());
            }
            QEditor::setEditOperations(configManager.editorKeys);
            config->remove("");
        }
        config->endGroup();
    }
    config->beginGroup("Editor Key Mapping New");
    QStringList sl = config->childKeys();
    if (!sl.empty()) {
        foreach (const QString &key, sl) {
            if (key.isEmpty()) continue;
            int operationID = config->value(key).toInt();
            if (key.startsWith("#")) {
                // remove predefined key
                QString realKey = key.mid(1);
                if (configManager.editorKeys.value(realKey) == operationID) {
                    configManager.editorKeys.remove(realKey);
                }
            } else {
                // replacement of keys needs to add/remove a key explicitely, as otherwise a simple addition can't be saved into .ini
                configManager.editorKeys.insert(key, operationID);
            }
        }
        QEditor::setEditOperations(configManager.editorKeys);
    }
    config->endGroup();
    config->endGroup();

    if(darkMode){
        config->beginGroup("formatsDark");
        m_formats = new QFormatFactory(":/qxs/defaultFormatsDark.qxf", this); //load default formats from resource file
        m_formats->load(*config, true); //load customized formats
        config->endGroup();
    }else{
        config->beginGroup("formats");
        m_formats = new QFormatFactory(":/qxs/defaultFormats.qxf", this); //load default formats from resource file
        if (config->contains("data/styleHint/bold")) {
            //rename data/styleHint/* => data/wordRepetition/*
            config->beginGroup("data");
            config->beginGroup("styleHint");
            QStringList temp = config->childKeys();
            config->endGroup();
            foreach (const QString & s, temp) config->setValue("wordRepetition/" + s, config->value("styleHint/" + s));
            config->remove("styleHint");
            config->endGroup();
        }

        m_formats->load(*config, true); //load customized formats
        config->endGroup();
    }

    documents.settingsRead();

    configManager.editorConfig->settingsChanged();
}

void Texstudio::saveSettings(const QString &configName)
{
	bool asProfile = !configName.isEmpty();
	configManager.centralVisible = centralToolBar->isVisible();
	// update completion usage
	LatexCompleterConfig *conf = configManager.completerConfig;
#ifndef NO_POPPLER_PREVIEW
	//pdf viewer embedded open ?
	if (!PDFDocument::documentList().isEmpty()) {
        PDFDocument *doc = PDFDocument::documentList().constFirst();
		if (doc->embeddedMode) {
			QList<int> sz = mainHSplitter->sizes(); // set widths to 50%, eventually restore user setting
			int sum = 0;
			int last = 0;
			foreach (int i, sz) {
				sum += i;
				last = i;
			}
			if (last > 10)
				pdfSplitterRel = 1.0 * last / sum;
		}
	}
#endif
    symbolWidget->saveSplitterState(configManager.stateSymbolsWidget); // readout splitter state from symbol widget

	QSettings *config = configManager.saveSettings(configName);

	config->beginGroup("texmaker");
	if (!asProfile) {
		if (isFullScreen()) {
			config->setValue("MainWindowState", windowstate);
			config->setValue("MainWindowFullssscreenState", saveState(1));
		} else {
			config->setValue("MainWindowState", saveState(0));
			config->setValue("MainWindowFullssscreenState", stateFullScreen);
		}
		config->setValue("MainWindow/Maximized", isMaximized());
		config->setValue("MainWindow/FullScreen", isFullScreen());

		config->setValue("Geometries/MainwindowWidth", width());

		config->setValue("Geometries/MainwindowHeight", height());
		config->setValue("Geometries/MainwindowX", x());
		config->setValue("Geometries/MainwindowY", y());

		config->setValue("GUI/sidePanelSplitter/state", sidePanelSplitter->saveState());
		config->setValue("centralVSplitterState", centralVSplitter->saveState());
		config->setValue("GUI/outputView/visible", outputView->isVisible());
		config->setValue("GUI/sidePanel/visible", sidePanel->isVisible());
        config->setValue("GUI/sidePanel/currentPage", leftPanel->currentIndex());

		if (!ConfigManager::dontRestoreSession) { // don't save session when using --no-restore as this is used for single doc handling
			Session s = getCurrentSession();
            QFileInfo f(QDir(configManager.configBaseDir), "lastSession.txss2");
            bool ok=false;
            if(!f.exists() || (f.exists() && f.isWritable())){
                ok=s.save(f.filePath(), configManager.sessionStoreRelativePaths);
            }
            if(!ok){
                QMessageBox::warning(this,tr("Storing session failed"),tr("Storing session information into %1 failed. File exists but is not writeable.").arg(f.filePath()));
            }
		}
	}


	for (int i = 0; i < struct_level.count(); i++)
		config->setValue("Structure/Structure Level " + QString::number(i + 1), struct_level[i]);

	config->setValue("Symbols/UsageCount", symbolWidget->model()->usageCountAsQVariantMap());
	config->setValue("Symbols/FavoriteIDs", symbolWidget->model()->favorites());

	// TODO: parse old "Symbols/Favorite IDs"

	config->setValue("Symbols/hiddenlists", leftPanel->hiddenWidgets());

	QHash<QString, int> keys = QEditor::getEditOperations(true);
	config->remove("Editor/Use Tab for Move to Placeholder");
	config->beginGroup("Editor Key Mapping New");
	if (!keys.empty() || !config->childKeys().empty()) {
		config->remove("");
        QHash<QString, int>::const_iterator i = keys.constBegin();
		while (i != keys.constEnd()) {
			if (!i.key().isEmpty()) //avoid crash
				config->setValue(i.key(), i.value());
			++i;
		}
	}
	config->endGroup();

	config->endGroup();

        // separate light/dark highlight formats
        if(darkMode){
            config->beginGroup("formatsDark");

            if(asProfile){
                // save all color info, don't remove default values
                m_formats->save(*config, nullptr);
            }else{
                QFormatFactory defaultFormats(":/qxs/defaultFormatsDark.qxf", this); //load default formats from resource file
                m_formats->save(*config, &defaultFormats);
            }
            config->endGroup();
        }else{
            config->beginGroup("formats");
            if(asProfile){
                // save all color info, don't remove default values
                m_formats->save(*config, nullptr);
            }else{
                QFormatFactory defaultFormats(":/qxs/defaultFormats.qxf", this); //load default formats from resource file
                m_formats->save(*config, &defaultFormats);
            }
            config->endGroup();
        }

	searchResultWidget()->saveConfig();

	// save usageCount in file of its own.
	if (!asProfile) {
		QFile file(configManager.configBaseDir + "wordCount.usage");
		if (file.open(QIODevice::WriteOnly)) {
			QDataStream out(&file);
            out << static_cast<quint32>(0xA0B0C0D0);  //magic number
            out << static_cast<qint32>(1); //version
			out.setVersion(QDataStream::Qt_4_0);
                        QMultiMap<uint, QPair<int, int> >::const_iterator i = conf->usage.constBegin();
			while (i != conf->usage.constEnd()) {
				QPair<int, int> elem = i.value();
				if (elem.second > 0) {
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

void Texstudio::restoreDefaultSettings()
{
	if (!UtilsUi::txsConfirmWarning(tr("This will reset all settings to their defaults. At the end, TeXstudio will be closed. Please start TeXstudio manually anew afterwards.\n\nDo you want to continue?"))) {
		return;
	}
	if (canCloseNow(false)) {
		QFile f(configManager.configFileName);
		if (f.exists()) {
			if (f.open(QFile::WriteOnly)) {
				f.write("\n");  // delete contents of settings file
				f.close();
			} else {
				UtilsUi::txsWarning(tr("Unable to write to settings file %1").arg(QDir::toNativeSeparators(f.fileName())));
			}
		}
		qApp->exit(0);
	}
}

////////////////// STRUCTURE ///////////////////
void Texstudio::updateStructure(bool initial, LatexDocument *doc, bool hidden)
{
	// collect user define tex commands for completer
	// initialize List
	if ((!currentEditorView() || !currentEditorView()->document) && !doc) return;
	if (!doc)
		doc = currentEditorView()->document;
	if (initial) {
		doc->patchStructure(0, -1);
		// execute QCE highlting
		doc->parent->enablePatch(false);
		doc->highlight();
		doc->parent->enablePatch(true);

		bool previouslyEmpty=doc->localMacros.isEmpty();
		doc->updateMagicCommentScripts();
		configManager.completerConfig->userMacros << doc->localMacros;
		if(!doc->localMacros.isEmpty() || !previouslyEmpty)
			updateUserMacros();
    }

	if (!hidden) {
		updateCompleter(doc->getEditorView());
		cursorPositionChanged();
	}

	//structureTreeView->reset();
}

void Texstudio::structureContextMenuToggleMasterDocument(LatexDocument *document)
{
	if (!document) return;
	if (document == documents.masterDocument) setAutomaticRootDetection();
	else setExplicitRootDocument(document);
}

void Texstudio::editRemovePlaceHolders()
{
	if (!currentEditor()) return;
	for (int i = currentEditor()->placeHolderCount(); i >= 0; i--)
		currentEditor()->removePlaceHolder(i);
	currentEditor()->viewport()->update();
}

void Texstudio::editRemoveCurrentPlaceHolder()
{
	if (!currentEditor()) return;
	currentEditor()->removePlaceHolder(currentEditor()->currentPlaceHolder());
}

//////////TAGS////////////////
void Texstudio::normalCompletion()
{
	if (!currentEditorView())	return;

	QString command;
	QDocumentCursor c = currentEditorView()->editor->cursor();
	QDocumentLineHandle *dlh = c.line().handle();
	//LatexParser::ContextType ctx=view->lp.findContext(word, c.columnNumber(), command, value);
	TokenStack ts = Parsing::getContext(dlh, c.columnNumber());
	Token tk;
	if (!ts.isEmpty()) {
		tk = ts.top();
		if (tk.type == Token::word && tk.subtype == Token::none && ts.size() > 1) {
			// set brace type
			ts.pop();
			tk = ts.top();
		}
	}

	Token::TokenType type = tk.type;
	if (tk.subtype != Token::none && type!=Token::command && type!=Token::commandUnknown){
		type = tk.subtype;
	}
	if (type == Token::specialArg) {
		int df = int(type - Token::specialArg);
		QString cmd = latexParser.mapSpecialArgs.value(df);
		if (mCompleterNeedsUpdate) updateCompleter();
		completer->setWorkPath(cmd);
        currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_SPECIALOPTION);
	}
	switch (type) {
	case Token::command:
	case Token::commandUnknown:
		if (mCompleterNeedsUpdate) updateCompleter();
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST);
		break;
	case Token::env:
	case Token::beginEnv:
		if (mCompleterNeedsUpdate) updateCompleter();
        generateMirror(true);
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST);
		break;
	case Token::labelRef:
		if (mCompleterNeedsUpdate) updateCompleter();
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_REF);
		break;
	case Token::labelRefList:
		if (mCompleterNeedsUpdate) updateCompleter();
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_REF | LatexCompleter::CF_FORCE_REFLIST);
		break;
	case Token::bibItem:
		if (mCompleterNeedsUpdate) updateCompleter();
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_CITE);
		break;
	case Token::width:
		if (mCompleterNeedsUpdate) updateCompleter();
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_LENGTH);
		break;
	case Token::imagefile: {
		QString fn = documents.getCompileFileName();
		QFileInfo fi(fn);
		completer->setWorkPath(fi.absolutePath());
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_GRAPHIC);
	}
	break;
	case Token::file: {
		QString fn = documents.getCompileFileName();
		QFileInfo fi(fn);
		completer->setWorkPath(fi.absolutePath());
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_GRAPHIC);
	}
	break;
	case Token::color:
		if (mCompleterNeedsUpdate) updateCompleter();
		completer->setWorkPath("%color");
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_SPECIALOPTION); //TODO: complete support for special opt
		break;
    case Token::colDef:
	case Token::keyValArg:
	case Token::keyVal_key:
	case Token::keyVal_val: {
        if (mCompleterNeedsUpdate) updateCompleter();
		QString word = c.line().text();
		int col = c.columnNumber();
        command = Parsing::getCommandFromToken(tk);
        if(command=="\\begin"){ // special treatment for begin as it is only meaningful with the env-name
            TokenList tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
            Token tkCmd=Parsing::getCommandTokenFromToken(tl,tk);
            int k = tl.indexOf(tkCmd) + 1;
            Token tk2=tl.value(k);
            QString subcommand=tk2.getText();
            command+=subcommand;
        }

		completer->setWorkPath(command);
		if (!completer->existValues()) {
			// no keys found for command
			// command/arg structure ? (yathesis)
			TokenList tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
			QString subcommand;
            int add = (type == Token::keyVal_val) ? 1 : 0;
			if (tk.type == Token::braces || tk.type == Token::squareBracket)
				add = 0;
			for (int k = tl.indexOf(tk) + 1; k < tl.length(); k++) {
				Token tk_elem = tl.at(k);
				if (tk_elem.level > tk.level - add)
					continue;
				if (tk_elem.level < tk.level - add)
					break;
				if (tk_elem.type == Token::braces) {
					subcommand = word.mid(tk_elem.start + 1, tk_elem.length - 2);
					break;
				}
			}
			if (!subcommand.isEmpty())
				command = command + "/" + subcommand;
			completer->setWorkPath(command);
		}

		bool existValues = completer->existValues();
		// check if c is after keyval
		if (col > tk.start + tk.length) {
			QString interposer = word.mid(tk.start + tk.length, col - tk.start - tk.length);
			if (!interposer.contains(",") && interposer.contains("=")) {
				//assume val for being after key
				command = command + "/" + tk.getText();
				completer->setWorkPath(command);
				existValues = completer->existValues();
			}
		} else {
			if (ts.size() > 1) {
				Token elem = ts.at(ts.size() - 2);
				if (elem.type == Token::keyVal_key && elem.level == tk.level - 1) {
					command = command + "/" + elem.getText();
					completer->setWorkPath(command);
					existValues = completer->existValues();
				}
			}
		}
		completer->setWorkPath(command);
		if (existValues)
			currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_KEYVAL);
	}
	break;
	case Token::beamertheme: {
		QString preambel = "beamertheme";
		currentPackageList.clear();
        for(const QString &elem: latexPackageList) {
			if (elem.startsWith(preambel))
                currentPackageList.insert(elem.mid(preambel.length()));
		}
	}
	completer->setPackageList(&currentPackageList);
	currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_PACKAGE);
	break;
	case Token::package:
		completer->setPackageList(&latexPackageList);
		currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_FORCE_PACKAGE);
		break;

	default:
		insertTextCompletion();
	}
}

void Texstudio::insertEnvironmentCompletion()
{
	if (!currentEditorView())	return;
	if (mCompleterNeedsUpdate) updateCompleter();
	QDocumentCursor c = currentEditorView()->editor->cursor();
	if (c.hasSelection()) {
		currentEditor()->cutBuffer = c.selectedText();
		c.removeSelectedText();
	}
	QString eow = getCommonEOW();
	while (c.columnNumber() > 0 && !eow.contains(c.previousChar())) c.movePosition(1, QDocumentCursor::PreviousCharacter);

	static const QString environmentStart = "\\begin{";

	currentEditor()->document()->clearLanguageMatches();
	if (!c.line().text().left(c.columnNumber()).endsWith(environmentStart)) {
		c.insertText(environmentStart);//remaining part is up to the completion engine
	}

	currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST);
}

// tries to complete normal text
// only starts up if already 2 characters have been typed in
void Texstudio::insertTextCompletion()
{
	if (!currentEditorView())    return;
	QDocumentCursor c = currentEditorView()->editor->cursor();
	QString eow = getCommonEOW();

    if (c.columnNumber() == 0 || eow.contains(c.previousChar()) )
		return;

	int col = c.columnNumber();
	QString line = c.line().text();
    if(col>line.length()){
        col=line.length(); // avoid crash, should not happen but did
    }
	for (; col > 0 && !eow.contains(line[col - 1]); col-- )
		;

    QString word = line.mid(col, c.columnNumber() - col);
    QSet<QString> words;

    QDocument *doc=currentEditor()->document();
    // generate regexp for getting fuzzy results
    // here the first letter must match, the rest can be fuzzy
#if (QT_VERSION>=QT_VERSION_CHECK(5,14,0))
    QStringList chars=word.split("",Qt::SkipEmptyParts);
#else
    QStringList chars=word.split("",QString::SkipEmptyParts);
#endif
    QString regExpression=chars.join(".*");
    QRegExp rx("^"+regExpression);

    for(int i=0;i<doc->lineCount();i++){
        QDocumentLineHandle *dlh=doc->line(i).handle();
        TokenList tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
        QString txt;
        for(int k=0;k<tl.size();k++) {
            Token tk=tl.at(k);
            if(!txt.isEmpty() || (tk.type==Token::word && (tk.subtype==Token::none || tk.subtype==Token::text || tk.subtype==Token::generalArg || tk.subtype==Token::title || tk.subtype==Token::shorttitle || tk.subtype==Token::todo))){
                txt+=tk.getText();
                if(txt.startsWith(word)){
                    if(word.length()<txt.length()){
                        words<<txt;
                    }
                    // advance k if tk comprehends several sub-tokens (braces)
                    while(k+1<tl.size() && tl.at(k+1).start<(tk.start+tk.length)){
                        k++;
                    }
                    // add more variants for variable-name like constructions
                    if(k+2<tl.size()){
                        Token tk2=tl.at(k+1);
                        Token tk3=tl.at(k+2);
                        if(tk2.length==1 && tk2.start==tk.start+tk.length && tk2.type==Token::punctuation&&tk3.start==tk2.start+tk2.length){
                            // next token is directly adjacent and of length 1
                            QString txt2=tk2.getText();
                            if(txt2=="_" || txt2=="-"){
                                txt.append(txt2);
                                k++;
                                continue;
                            }
                            if(txt2=="'" && tk3.type==Token::word){ // e.g. don't but not abc''
                                txt.append(txt2);
                                k++;
                                continue;
                            }
                        }
                        // combine abc\_def
                        if(tk2.length==2 && tk2.start==tk.start+tk.length && (tk2.type==Token::command||tk2.type==Token::commandUnknown)&&tk3.start==tk2.start+tk2.length){
                            // next token is directly adjacent and of length 1
                            QString txt2=tk2.getText();
                            if(txt2=="\\_" ){
                                txt.append(txt2);
                                k++;
                                continue;
                            }
                        }
                        // previous was an already appended command, check if argument is present
                        if(tk.type==Token::command){
                            if(tk2.level==tk.level && tk2.subtype!=Token::none){
                                txt.append(tk2.getText());
                                words<<txt;
                                k++;
                            }
                        }
                    }
                }else{
                    if(rx.indexIn(txt)!=-1){
                        words<<txt;
                    }
                }
            }
            txt.clear();
        }

    }
    /*QString my_text = currentEditorView()->editor->text();
	int end = 0;
	int k = 0; // number of occurences of search word.
	QString word = line.mid(col, c.columnNumber() - col);
	//TODO: Boundary needs to specified more exactly
	//TODO: type in text needs to be excluded, if not already present
	//TODO: editor->text() is far too slow
	QSet<QString> words;
	int i;
	while ((i = my_text.indexOf(QRegExp("\\b" + word), end)) > 0) {
		end = my_text.indexOf(QRegExp("\\b"), i + 1);
		if (end > i) {
            bool addVar=false;
            do {
                addVar=false;
                if (word == my_text.mid(i, end - i)) {
                    k = k + 1;
                    if (k == 2) words << my_text.mid(i, end - i);
                } else {
                    QString txt=my_text.mid(i, end - i);
                    if(txt.endsWith("_")){
                        if(my_text.mid(end,1)=="\\"||my_text.mid(end,1)=="{"){
                            // special handling for abc_\cmd{dsfsdf}
                            QRegExp rx("(\\\\[a-zA-Z]+)?(\\{\\w+\\})?"); // better solution would be employing tokens ...
                            int zw=rx.indexIn(my_text,end);
                            if(zw==end){
                                txt.append(rx.cap());
                                words << txt;
                            }
                        }
                    }else{
                        if (!words.contains(txt))
                            words << txt;
                    }
                }
                // add more variants if word boundary is \_ \- or -
                if(my_text.length()>end+1){
                    addVar|=(my_text.mid(end,2)=="\\_");
                    addVar|=(my_text.mid(end,2)=="\\-");
                    if(addVar)
                        end++;
                }
                if(my_text.mid(end,1)=="-")
                    addVar=true;
                if(addVar){
                    end = my_text.indexOf(QRegExp("\\b"), end+2);
                    addVar=(end>i);
                }
            } while(addVar);
		} else {
			if (word == my_text.mid(i, end - i)) {
				k = k + 1;
				if (k == 2) words << my_text.mid(i, end - i);
			} else {
				if (!words.contains(my_text.mid(i, end - i)))
					words << my_text.mid(i, my_text.length() - i);
			}
		}
	}
    */
	completer->setAdditionalWords(words, CT_NORMALTEXT);
	currentEditorView()->complete(LatexCompleter::CF_FORCE_VISIBLE_LIST | LatexCompleter::CF_NORMAL_TEXT);
}

void Texstudio::insertText(const QString &text)
{
	currentEditor()->write(text);
	currentEditorView()->setFocus();
}

/*! TODO: this API and its defaults are a bit weird. Needs refactoring. */
void Texstudio::insertTag(const QString &Entity, int dx, int dy)
{
	if (!currentEditorView()) return;
	int curline, curindex;
	currentEditor()->getCursorPosition(curline, curindex);
	currentEditor()->write(Entity);
	if (dy == 0) currentEditor()->setCursorPosition(curline, curindex + dx);
	else if (dx == 0) currentEditor()->setCursorPosition(curline + dy, 0);
	else currentEditor()->setCursorPosition(curline + dy, curindex + dx);
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
void Texstudio::insertCitation(const QString &text)
{
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
	QDocumentCursor c = currentEditor()->cursor();
	QString line = c.line().text();
	int cursorCol = c.columnNumber();
	QString command, value;
	LatexParser::ContextType context = latexParser.findContext(line, cursorCol, command, value);

	// Workaround: findContext yields Citation for \cite{..}|\n, but cursorCol is beyond the line,
	// which causes a crash when determining the insertCol later on.
	if (context == LatexParser::Citation && cursorCol == line.length() && cursorCol > 0) cursorCol--;

    // if cursor is directly behind a cite command, insert into that command
	if (context != LatexParser::Citation && cursorCol > 0) {
		LatexParser::ContextType prevContext = LatexParser::Unknown;
		prevContext = latexParser.findContext(line, cursorCol - 1, command, value);
		if (prevContext == LatexParser::Citation) {
			cursorCol--;
			context = prevContext;
		}
	}


	int insertCol = -1;
	if (context == LatexParser::Command && latexParser.possibleCommands["%cite"].contains(command)) {
		insertCol = line.indexOf('{', cursorCol) + 1;
	} else if (context == LatexParser::Citation) {
		if (cursorCol <= 0) return; // should not be possible,
		if (line.at(cursorCol) == '{' || line.at(cursorCol) == ',') {
			insertCol = cursorCol + 1;
		} else if (line.at(cursorCol - 1) == '{' || line.at(cursorCol - 1) == ',') {
			insertCol = cursorCol;
		} else {
			int nextComma = line.indexOf(',', cursorCol);
			int closingBracket = line.indexOf('}', cursorCol);
			if (nextComma >= 0 && (closingBracket == -1 || closingBracket > nextComma)) {
				insertCol = nextComma + 1;
			} else if (closingBracket >= 0) {
				insertCol = closingBracket;
			}
		}
	} else {
		QString tag;
		if (citeCmd.isEmpty())
            tag = citeCmd = configManager.citeCommand+"{" + citeKey + "}";
		else
			tag = text;
		insertTag(tag, tag.length());
		return;
	}

	if (insertCol < 0 || insertCol >= line.length()) return;

	currentEditor()->setCursorPosition(c.lineNumber(), insertCol);
	// now the insertCol is either behind '{', behind ',' or at '}'
	if (insertCol > 0 && line.at(insertCol - 1) == '{') {
		if (line.at(insertCol) == '}') {
			insertTag(citeKey, citeKey.length());
		} else {
			insertTag(citeKey + ",", citeKey.length() + 1);
		}
	} else if (insertCol > 0 && line.at(insertCol - 1) == ',') {
		insertTag(citeKey + ",", citeKey.length() + 1);
	} else {
		insertTag("," + citeKey, citeKey.length() + 1);
	}
}

void Texstudio::insertFormula(const QString &formula)
{
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
		fm = fm.mid(1, fm.length() - 2);                 // removes surrounding $...$
	} else if (dl.getFormatAt(col) == mathDelimiter) {   // on delimiter
		while (col > 0 && dl.getFormatAt(col - 1) == mathDelimiter) col--;
		if (mathFormats.contains(dl.getFormatAt(col))) { // was an end-delimiter
			cur.setColumnNumber(col);
			currentEditorView()->editor->setCursor(cur);
			fm = fm.mid(1, fm.length() - 2);             // removes surrounding $...$
		} else {
            //TODO is there a better way than hard coding? Since there is no difference in the formats between
			//start and end tags. \[|\] is hard identify without.
			QString editorFormula = dl.text().mid(col);
			if (editorFormula.startsWith("\\[")) {
                //col += 2; unused code
				currentEditorView()->editor->setCursor(cur);
				fm = fm.mid(1, fm.length() - 2);         // removes surrounding $...$
			} else if (editorFormula.startsWith("$")) {
                // col += 1; unused code
				currentEditorView()->editor->setCursor(cur);
				fm = fm.mid(1, fm.length() - 2);         // removes surrounding $...$
			} else {
				qDebug() << "Unknown math formula tag. Giving up trying to locate formula boundaries.";
			}
		}
	}

	insertTag(fm, fm.length());
}

void Texstudio::insertSymbol(const QString &text)
{
	insertTag(text, text.length());
}

void Texstudio::insertXmlTag(QListWidgetItem *item)
{
	if (!currentEditorView())	return;
	if (item  && !item->font().bold()) {
		QString code = item->data(Qt::UserRole).toString();
		QDocumentCursor c = currentEditorView()->editor->cursor();
		CodeSnippet(code).insertAt(currentEditorView()->editor, &c);
		currentEditorView()->editor->setFocus();
	}
}

void Texstudio::insertXmlTagFromToolButtonAction()
{
	if (!currentEditorView()) return;
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	QToolButton *button = UtilsUi::comboToolButtonFromAction(action);
	if (!button) return;
	button->setDefaultAction(action);

	QString tagsID = button->property("tagsID").toString();
	int tagCategorySep = tagsID.indexOf("/", 5);
	XmlTagsListWidget *tagsWidget = findChild<XmlTagsListWidget *>(tagsID.left(tagCategorySep));
	if (!tagsWidget) return;
	QString code = tagsWidget->tagsFromTagTxt(action->text());
	CodeSnippet(code).insert(currentEditorView()->editor);
	currentEditorView()->editor->setFocus();
}

void Texstudio::callToolButtonAction()
{
	QAction *action = qobject_cast<QAction *>(sender());
	QToolButton *button = UtilsUi::comboToolButtonFromAction(action);
	REQUIRE(button && button->defaultAction() && button->menu());
	button->setDefaultAction(action);

	QString menuID = button->property("menuID").toString();
	QMenu *menu = configManager.getManagedMenu(menuID);
	if (!menu) return;

	int index = button->menu()->actions().indexOf(action);
	REQUIRE(index >= 0);
	REQUIRE(index < menu->actions().size());
	QList<QAction *> actions = menu->actions();
	for (int i = 0; i < actions.size(); i++) {
		if (actions[i]->isSeparator()) continue;
		if (index == 0) {
			actions[i]->trigger();
			break;
		} else index--;
	}
}

void Texstudio::insertFromAction()
{
	LatexEditorView *edView = currentEditorView();
	if (!edView)	return;
	QAction *action = qobject_cast<QAction *>(sender());
	if (action)	{
		if (completer->isVisible())
			completer->close();
		execMacro(Macro::fromTypedTag(action->data().toString()), MacroExecContext(), true);
		generateMirror();
		outputView->setMessage(CodeSnippet(action->whatsThis(), false).lines.join("\n"));
    }
}

void Texstudio::insertTextFromAction()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;
    insertText(action->data().toString());
}

void Texstudio::insertFromTagList(QListWidgetItem *item)
{
    LatexEditorView *edView = currentEditorView();
    if (!edView)	return;
    if (item)	{
        if (completer->isVisible())
            completer->close();
        execMacro(Macro::fromTypedTag(item->data(Qt::UserRole).toString()), MacroExecContext(), true);
        generateMirror();
    }
}

void Texstudio::insertBib()
{
	if (!currentEditorView())	return;
	//currentEditorView()->editor->viewport()->setFocus();
	QString tag;
	tag = QString("\\bibliography{");
	tag += currentEditor()->fileInfo().completeBaseName();
	tag += QString("}\n");
	insertTag(tag, 0, 1);
	outputView->setMessage(QString("The argument to \\bibliography refers to the bib file (without extension)\n") +
	                       "which should contain your database in BibTeX format.\n" +
	                       "TeXstudio inserts automatically the base name of the TeX file");
}

void Texstudio::quickTabular(const QMimeData *d)
{
	if ( !currentEditorView() )	return;
	TabDialog *tabDialog = new TabDialog(this, "Tabular");
    if(d && d->hasFormat("text/plain")){
        tabDialog->insertTextIntoTable(d->text());
    }
	if ( tabDialog->exec() ) {
		QString latexText = tabDialog->getLatexText();
		QSet<QString> usedPackages = currentEditorView()->document->usedPackages();
		foreach (const QString &package, TabDialog::getRequiredPackages(latexText)) {
			if (!usedPackages.contains(package)) {
				latexText.prepend("% TODO: \\usepackage{" + package + "} required\n");
			}
		}
		insertTag(latexText, 0, 0);
	}
}

void Texstudio::quickArray()
{
	if (!currentEditorView())	return;
	ArrayDialog *arrayDlg = new ArrayDialog(this, "Array");
	if (arrayDlg->exec()) {
		insertTag(arrayDlg->getLatexText(), 0, 0);
	}
}


// returns true if line is inside in the specified environment. In that case start and end lines of the environment are supplied
bool findEnvironmentLines(const QDocument *doc, const QString &env, int line, int &startLine, int &endLine, int scanRange)
{
	QString name, arg;

	startLine = -1;
	for (int l = line; l >= 0; l--) {
		if (scanRange > 0 && line - l > scanRange) break;
		if (findTokenWithArg(doc->line(l).text(), "\\end{", name, arg) && name == env) {
			if (l < line) return false;
		}
		if (findTokenWithArg(doc->line(l).text(), "\\begin{", name, arg) && name == env) {
			startLine = l;
			break;
		}
	}
	if (startLine == -1) return false;

	endLine = -1;
	for (int l = line; l < doc->lineCount(); l++) {
		if (scanRange > 0 && l - line > scanRange) break;
		if (findTokenWithArg(doc->line(l).text(), "\\end{", name, arg) && name == env) {
			endLine = l;
			break;
		}
		if (findTokenWithArg(doc->line(l).text(), "\\begin{", name, arg) && name == env) {
			if (l > line) return false; //second begin without end
		}
	}
	if (endLine == -1) return false;
	return true;
}

void Texstudio::quickGraphics(const QString &graphicsFile)
{
	if (!currentEditorView()) return;

	InsertGraphics *graphicsDlg = new InsertGraphics(this, configManager.insertGraphicsConfig);

	QEditor *editor = currentEditor();

	int startLine, endLine, cursorLine, cursorCol;
	editor->getCursorPosition(cursorLine, cursorCol);
	QDocument *doc = editor->document();

	QDocumentCursor cur = currentEditor()->cursor();
	QDocumentCursor origCur = cur;
	origCur.setAutoUpdated(true);

	bool hasCode = false;
	if (findEnvironmentLines(doc, "figure", cursorLine, startLine, endLine, 20)) {
		cur.moveTo(startLine, 0, QDocumentCursor::MoveAnchor);
		cur.moveTo(endLine + 1, 0, QDocumentCursor::KeepAnchor);
		hasCode = true;
	} else if (findEnvironmentLines(doc, "figure*", cursorLine, startLine, endLine, 20)) {
		cur.moveTo(startLine, 0, QDocumentCursor::MoveAnchor);
		cur.moveTo(endLine + 1, 0, QDocumentCursor::KeepAnchor);
		hasCode = true;
	} else if (findEnvironmentLines(doc, "center", cursorLine, startLine, endLine, 3)) {
		cur.moveTo(startLine, 0, QDocumentCursor::MoveAnchor);
		cur.moveTo(endLine + 1, 0, QDocumentCursor::KeepAnchor);
		hasCode = true;
	} else if (currentEditor()->text(cursorLine).contains("\\includegraphics")) {
		cur.moveTo(cursorLine, 0, QDocumentCursor::MoveAnchor);
		cur.moveTo(cursorLine + 1, 0, QDocumentCursor::KeepAnchor);
		hasCode = true;
	}

	if (hasCode) {
		editor->setCursor(cur);
		graphicsDlg->setCode(cur.selectedText());
	}

	QFileInfo docInfo = currentEditorView()->document->getFileInfo();
	graphicsDlg->setTexFile(docInfo);
    graphicsDlg->setMasterTexFile(QFileInfo(currentEditorView()->document->parent->getCompileFileName()));
	if (!graphicsFile.isNull()) graphicsDlg->setGraphicsFile(graphicsFile);

	if (graphicsDlg->exec()) {
		QString latexText = graphicsDlg->getLatexText();
		if (!currentEditorView()->document->usedPackages().contains("graphicx")) {
			// simplified static version. See quickTabular() for a more generic version.
			latexText.prepend("% TODO: \\usepackage{graphicx} required\n");
		}
		editor->insertText(cur, latexText);
	} else {
		editor->setCursor(origCur);
	}

	delete graphicsDlg;
}

void Texstudio::quickMath()
{
#ifdef Q_OS_WIN
	connectUnique(MathAssistant::instance(), SIGNAL(formulaReceived(QString)), this, SLOT(insertFormula(QString)));
	MathAssistant::instance()->exec();
#endif
}

void Texstudio::quickTabbing()
{
	if (!currentEditorView()) return;
	TabbingDialog *tabDlg = new TabbingDialog(this, "Tabbing");
	if (tabDlg->exec()) {
		int	x = tabDlg->ui.spinBoxColumns->value();
		int	y = tabDlg->ui.spinBoxRows->value();
		QString s = tabDlg->ui.lineEdit->text();
		QString tag = QString("\\begin{tabbing}\n");
		for (int j = 1; j < x; j++) {
			tag += "\\hspace{" + s + "}\\=";
		}
		tag += "\\kill\n";
		for (int i = 0; i < y - 1; i++) {
			for (int j = 1; j < x; j++) {
				tag += " \\> ";
			}
			tag += "\\\\ \n";
		}
		for (int j = 1; j < x; j++) {
			tag += " \\> ";
		}
		tag += QString("\n\\end{tabbing} ");
		insertTag(tag, 0, 2);
	}
}

void Texstudio::quickLetter()
{
	QString tag = QString("\\documentclass[");
	LetterDialog *ltDlg = new LetterDialog(this, "Letter");
	if (ltDlg->exec()) {
		if (!currentEditorView() ||
		        currentEditorView()->getDocument()->lineCount() > 1 || // first faster than text().isEmpty on large documents
		        !currentEditorView()->getDocument()->text().isEmpty()) {
			fileNew();
			Q_ASSERT(currentEditorView());
		}
		tag += ltDlg->ui.comboBoxPt->currentText() + QString(",");
		tag += ltDlg->ui.comboBoxPaper->currentText() + QString("]{letter}");
		tag += QString("\n");
		if (ltDlg->ui.comboBoxEncoding->currentText() != "NONE") tag += QString("\\usepackage[") + ltDlg->ui.comboBoxEncoding->currentText() + QString("]{inputenc}");
		if (ltDlg->ui.comboBoxEncoding->currentText().startsWith("utf8x")) tag += QString(" \\usepackage{ucs}");
		tag += QString("\n");
		if (ltDlg->ui.checkBox->isChecked()) tag += QString("\\usepackage{amsmath}\n\\usepackage{amssymb}\n");
		tag += "\\address{your name and address} \n";
		tag += "\\signature{your signature} \n";
		tag += "\\begin{document} \n";
		tag += "\\begin{letter}{name and address of the recipient} \n";
		tag += "\\opening{saying hello} \n \n";
		tag += "write your letter here \n \n";
		tag += "\\closing{saying goodbye} \n";
		tag += "%\\cc{Cclist} \n";
		tag += "%\\ps{adding a postscript} \n";
		tag += "%\\encl{list of enclosed material} \n";
		tag += "\\end{letter} \n";
		tag += "\\end{document}";
		if (ltDlg->ui.checkBox->isChecked()) {
			insertTag(tag, 9, 5);
		} else {
			insertTag(tag, 9, 2);
		}
	}
}

void Texstudio::quickDocument()
{
	QuickDocumentDialog *startDlg = new QuickDocumentDialog(this, tr("Quick Start"));
	startDlg->Init();
	if (startDlg->exec()) {
		if (!currentEditorView() ||
		        currentEditorView()->getDocument()->lineCount() > 1 || // first faster than text().isEmpty on large documents
		        !currentEditorView()->getDocument()->text().isEmpty()) {
			fileNew();
			Q_ASSERT(currentEditorView());
		}
		Q_ASSERT(currentEditor());
		currentEditorView()->insertSnippet(startDlg->getNewDocumentText());
		QTextCodec *codec = Encoding::QTextCodecForLatexName(startDlg->document_encoding);
		if (codec && codec != currentEditor()->document()->codec()) {
			currentEditor()->document()->setCodec(codec);
			updateCaption();
		}
	}
	delete startDlg;
}

void Texstudio::quickBeamer()
{
	QuickBeamerDialog *startDlg = new QuickBeamerDialog(this, tr("Quick Beamer Presentation"));
	startDlg->Init();
	if (startDlg->exec()) {
		if (!currentEditorView() ||
		        currentEditorView()->getDocument()->lineCount() > 1 || // first faster than text().isEmpty on large documents
		        !currentEditorView()->getDocument()->text().isEmpty()) {
			fileNew();
			Q_ASSERT(currentEditorView());
		}
		Q_ASSERT(currentEditor());
		currentEditorView()->insertSnippet(startDlg->getNewDocumentText());
		QTextCodec *codec = Encoding::QTextCodecForLatexName(startDlg->document_encoding);
		if (codec && codec != currentEditor()->document()->codec()) {
			currentEditor()->document()->setCodec(codec);
			updateCaption();
		}
	}
	delete startDlg;
}

void Texstudio::insertBibEntryFromAction()
{
	if (!currentEditorView()) return;
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;

	QString insertText = BibTeXDialog::textToInsert(action->data().toString());
	if (!insertText.isEmpty())
		CodeSnippet(insertText, false).insert(currentEditor());
}

void Texstudio::insertBibEntry(const QString &id)
{
	QStringList possibleBibFiles;
	int usedFile = 0;
	if (currentEditor()) {
		if (currentEditor()->fileName().isEmpty())
			possibleBibFiles.prepend(tr("<Current File>"));
		else {
			usedFile = documents.mentionedBibTeXFiles.indexOf(currentEditor()->fileName());
			if (usedFile < 0 && !documents.mentionedBibTeXFiles.empty()) usedFile = 0;
		}
	}
	foreach (const QString &s, documents.mentionedBibTeXFiles)
		possibleBibFiles << QFileInfo(s).fileName();
	BibTeXDialog *bd = new BibTeXDialog(nullptr, possibleBibFiles, usedFile, id);
	if (bd->exec()) {
		usedFile = bd->resultFileId;
		if (usedFile < 0 || usedFile >= possibleBibFiles.count()) fileNew();
		else if (currentEditor()->fileName().isEmpty() && usedFile == 0); //stay in current editor
		else if (QFileInfo(currentEditor()->fileName()) == QFileInfo(possibleBibFiles[usedFile])); //stay in current editor
		else {
			if (currentEditor()->fileName().isEmpty()) usedFile--;
			load(documents.mentionedBibTeXFiles[usedFile]);
			currentEditor()->setCursorPosition(currentEditor()->document()->lines() - 1, 0);
			bd->resultString = "\n" + bd->resultString;
		}

		CodeSnippet(bd->resultString, false).insert(currentEditor());
	}
	delete bd;
}

void Texstudio::setBibTypeFromAction()
{
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

void Texstudio::insertUserTag()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	int id = action->data().toInt();
	execMacro(configManager.completerConfig->userMacros.value(id, Macro()));
}

void Texstudio::execMacro(const Macro &m, const MacroExecContext &context, bool allowWrite)
{
	if (m.type == Macro::Script) {
		runScript(m.script(), context, allowWrite);
	} else {
		if (currentEditorView()) {
			currentEditorView()->insertSnippet(m.snippet());
		}
	}
}

void Texstudio::runScript(const QString &script, const MacroExecContext &context, bool allowWrite)
{
	scriptengine *eng = new scriptengine();
	eng->triggerMatches = context.triggerMatches;
	eng->triggerId = context.triggerId;
	if (currentEditorView()) eng->setEditorView(currentEditorView());

	eng->setScript(script, allowWrite);
	eng->run();
}

void Texstudio::editMacros()
{
    if (!userMacroDialog)  {
        userMacroDialog = new UserMenuDialog(nullptr, tr("Edit User &Tags"), m_languages);
        bool atLeastOneAdded=false;
        foreach (const Macro &m, configManager.completerConfig->userMacros) {
            if (m.name == "TMX:Replace Quote Open" || m.name == "TMX:Replace Quote Close" || m.document)
                continue;
            userMacroDialog->addMacro(m);
            atLeastOneAdded=true;
        }
        if(!atLeastOneAdded){
            // add one empty macro in case of empty macro least
            Macro m;
            userMacroDialog->addMacro(m);
        }
        userMacroDialog->selectFirst();
        connect(userMacroDialog, SIGNAL(accepted()), SLOT(macroDialogAccepted()));
        connect(userMacroDialog, SIGNAL(rejected()), SLOT(macroDialogRejected()));
        connect(userMacroDialog, SIGNAL(runScript(QString)), SLOT(runScript(QString)));
        // persistent setting like wrap
        userMacroDialog->setLineWrap(configManager.macroEditorUsesLineWrap);
    }
    userMacroDialog->show();
    userMacroDialog->raise();
    userMacroDialog->setFocus();
}

void Texstudio::macroDialogAccepted()
{
	configManager.completerConfig->userMacros.clear();

        configManager.completerConfig->userMacros << userMacroDialog->getMacros();

	for (int i = 0; i < documents.documents.size(); i++)
		configManager.completerConfig->userMacros << documents.documents[i]->localMacros;
	updateUserMacros();
        configManager.saveMacros();
	completer->updateAbbreviations();
	addMacrosAsTagList();
    // read out wrap setting to make it persistent
    configManager.macroEditorUsesLineWrap=userMacroDialog->getLineWrap();

	userMacroDialog->deleteLater();
	userMacroDialog = nullptr;
}

void Texstudio::macroDialogRejected()
{
	userMacroDialog->deleteLater();
	userMacroDialog = nullptr;
}

void Texstudio::insertRef(const QString &refCmd)
{
	//updateStructure();

	LatexEditorView *edView = currentEditorView();
	QStringList labels;
	if (edView && edView->document) {
		QList<LatexDocument *> docs;
		docs << edView->document->getListOfDocs();
		foreach (const LatexDocument *doc, docs)
			labels << doc->labelItems();
	} else return;
	labels.sort();
	UniversalInputDialog dialog;
	dialog.addVariable(&labels, tr("Labels:"));
	if (dialog.exec() && !labels.isEmpty()) {
		QString tag = refCmd + "{" + labels.first() + "}";
		insertTag(tag, tag.length(), 0);
	} else
		insertTag(refCmd + "{}", refCmd.length() + 1, 0);
}

void Texstudio::insertRef()
{
	insertRef("\\ref");
}

void Texstudio::insertEqRef()
{
	insertRef("\\eqref");
}

void Texstudio::insertPageRef()
{
	insertRef("\\pageref");
}

void Texstudio::changeTextCodec()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	bool ok;
	int mib = action->data().toInt(&ok);
	if (!ok) return;
	if (!currentEditorView()) return;

	currentEditorView()->editor->setFileCodec(QTextCodec::codecForMib(mib));
	updateCaption();
}

void Texstudio::editorSpellerChanged(const QString &name)
{
	foreach (QAction *act, statusTbLanguage->actions()) {
		if (act->data().toString() == name) {
			act->setChecked(true);
			break;
		}
	}
	if (name == "<default>") {
		statusTbLanguage->setText(spellerManager.defaultSpellerName());
        if(!configManager.previouslyUsedDictionaries.contains(spellerManager.defaultSpellerName())){
            configManager.previouslyUsedDictionaries<<spellerManager.defaultSpellerName();
        }
	} else {
		statusTbLanguage->setText(name);
        if(!configManager.previouslyUsedDictionaries.contains(name)){
            configManager.previouslyUsedDictionaries<<name;
        }
	}
}

void Texstudio::changeEditorSpeller()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	if (!currentEditorView()) return;

    if (!currentEditorView()->setSpeller(action->data().toString(),true)) {
		// restore activity of previous action
		foreach (QAction *act, statusTbLanguage->actions()) {
			if (act->data().toString() == currentEditorView()->getSpeller()) {
				act->setChecked(true);
				break;
			}
		}
    }
}

void Texstudio::showMoreDictionaries()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if(!action)
        return; // safety check
    bool showMore=action->data().toBool();
    if(showMore){
        // show more
        foreach (QAction *act, statusTbLanguage->actions()) {
            act->setVisible(true);
        }
        action->setData(QVariant(false));
        action->setText(tr("show less entries ..."));
    }else{
        //show less
        foreach (QAction *act, statusTbLanguage->actions()) {
            QVariant data=act->data();
            if(data.isValid()){
                QString name=data.toString();
                if(!configManager.previouslyUsedDictionaries.contains(name) && (name!="<default>") && (name!="<none>")){
                    act->setVisible(false);
                }
            }
        }
        action->setData(QVariant(true));
        action->setText(tr("show more entries ..."));
        action->setVisible(true);
    }

    statusTbLanguage->showMenu();
}

void Texstudio::insertSpellcheckMagicComment()
{
	if (currentEditorView()) {
		QString name = currentEditorView()->getSpeller();
		if (name == "<default>") {
			name = spellerManager.defaultSpellerName();
		}
		currentEditorView()->document->updateMagicComment("spellcheck", name, true);
	}
}

void Texstudio::updateStatusBarEncoding()
{
	if (currentEditorView() && currentEditorView()->editor->getFileCodec()) {
		QTextCodec *codec = currentEditorView()->editor->getFileCodec();
		statusTbEncoding->setText(codec->name() + "  ");
		QStringList aliases;
		foreach (const QByteArray &b, codec->aliases()) {
			aliases << QString(b);
		}
		if (!aliases.isEmpty()) {
			statusTbEncoding->setToolTip(tr("Encoding Aliases: ") + aliases.join(", "));
		} else {
			statusTbEncoding->setToolTip(tr("Encoding"));
		}
	} else {
		statusTbEncoding->setText(tr("Encoding") + "  ");
		statusTbEncoding->setToolTip(tr("Encoding"));
	}
}

void Texstudio::addMagicRoot()
{
	if (currentEditorView()) {
		LatexDocument *doc = currentEditorView()->getDocument();
		if (!doc) return;
		QString name = doc->getRootDocument()->getFileName();
		name = getRelativeFileName(name, doc->getFileName(), true);
		currentEditorView()->document->updateMagicComment("root", name, true);
	}
}

void Texstudio::addMagicCoding()
{
	if (currentEditorView()) {
		QString name = currentEditor()->getFileCodec()->name();
		currentEditorView()->document->updateMagicComment("encoding", name, true);
	}
}

void Texstudio::addMagicBibliography()
{
    if (currentEditorView()) {
        currentEditorView()->document->updateMagicComment("TXS-program:bibliography", "", true);
    }
}

void Texstudio::addMagicProgram()
{
    if (currentEditorView()) {
        currentEditorView()->document->updateMagicComment("TS-program", "", true);
    }
}

///////////////TOOLS////////////////////
bool Texstudio::runCommand(const QString &commandline, QString *buffer, QTextCodec *codecForBuffer, bool saveAll)
{
    if(saveAll){
        fileSaveAll(buildManager.saveFilesBeforeCompiling == BuildManager::SFBC_ALWAYS, buildManager.saveFilesBeforeCompiling == BuildManager::SFBC_ONLY_CURRENT_OR_NAMED);
    }
	if (documents.getTemporaryCompileFileName() == "") {
		if (buildManager.saveFilesBeforeCompiling == BuildManager::SFBC_ONLY_NAMED && currentEditorView()) {
			QString tmpName = buildManager.createTemporaryFileName();
			currentEditor()->saveCopy(tmpName);
			currentEditorView()->document->setTemporaryFileName(tmpName);
		} else {
			QMessageBox::warning(this, tr("Error"), tr("Can't detect the file name.\nYou have to save a document before you can compile it."));
			return false;
		}
	}

	QString finame = documents.getTemporaryCompileFileName();
	if (finame == "") {
		UtilsUi::txsWarning(tr("Can't detect the file name"));
		return false;
	}

	int ln = currentEditorView() ? currentEditorView()->editor->cursor().lineNumber() + 1 : 0;
    // unified error/stdout into *buffer
    return buildManager.runCommand(commandline, QFileInfo(finame), QFileInfo(getCurrentFileName()), ln, buffer, codecForBuffer,buffer);
}

/*!
 * Workaround method to use runCommand without interpreting special chars in the commandline.
 * TODO: Maybe these kind of calls should be decoupled from the buildmanager altogether, or
 * this should become a separate method of the buildmanager.
 */
bool Texstudio::runCommandNoSpecialChars(QString commandline, QString *buffer, QTextCodec *codecForBuffer) {
	commandline.replace('@', "@@");
	commandline.replace('%', "%%");
	commandline.replace('?', "??");
    return runCommand(commandline, buffer, codecForBuffer,false);
}
/*!
 * \brief set StatusMessage for a process
 * \param message
 */
void Texstudio::setStatusMessageProcess(const QString &message)
{
	statusLabelProcess->setText(message);
}
/*!
 * \brief run the command asynchronously. When finished, SLOT returnCMD is called.
 * See Help::texdocAvailableRequest for an example.
 * \param commandline
 * \param returnCMD provide a SLOT which is called when finishing the process
 * \return true when start works
 */
bool Texstudio::runCommandAsync(const QString &commandline, const char * returnCMD){
    QObject *obj=sender();
    QString finame = documents.getTemporaryCompileFileName();
    ProcessX *proc = buildManager.firstProcessOfDirectExpansion(commandline, QFileInfo(finame));
    setStatusMessageProcess(tr("  Running this command: ") + proc->getCommandLine());
    connect(proc, SIGNAL(finished(int,QProcess::ExitStatus)), obj, returnCMD);
    QString *buffer=new QString();
    proc->setStdoutBuffer(buffer);
    proc->startCommand();
    if (!proc->waitForStarted(1000)) {
        setStatusMessageProcess(tr("Error") + " : " + tr("could not start the command"));
        return false;
    }
    return true;
}

void Texstudio::runInternalPdfViewer(const QFileInfo &master, const QString &options)
{
#ifndef NO_POPPLER_PREVIEW
	QStringList ol = BuildManager::splitOptions(options);
	QString pdfFile;
	for (int i = ol.size() - 1; i >= 0; i--) {
		if (!ol[i].startsWith("-")) {
			if (pdfFile.isNull()) pdfFile = dequoteStr(ol[i]);
			ol.removeAt(i);
		} else if (ol[i].startsWith("--")) ol[i] = ol[i].mid(2);
		else ol[i] = ol[i].mid(1);
	}
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

	PDFDocument::DisplayFlags displayPolicy = PDFDocument::FocusWindowed | PDFDocument::Raise;
	if (ol.contains("no-focus")) displayPolicy &= ~PDFDocument::Focus;
	else if (ol.contains("focus")) displayPolicy |= PDFDocument::Focus;
	if (ol.contains("no-foreground")) displayPolicy &= ~PDFDocument::Raise;
	else if (ol.contains("foreground")) displayPolicy |= PDFDocument::Raise;

	if (!(embedded || windowed || closeEmbedded || closeWindowed)) windowed = true; //default

	//embedded/windowed are mutual exclusive
	//no viewer will be opened, if one already exist (unless it was closed by a explicitely given close command)


	QList<PDFDocument *> oldPDFs = PDFDocument::documentList();

	if (preserveExisting) oldPDFs.clear();
	if (preserveExistingWindowed)
		for (int i = oldPDFs.size() - 1; i >= 0; i--)
			if (!oldPDFs[i]->embeddedMode)
				oldPDFs.removeAt(i);
	if (preserveExistingEmbedded)
		for (int i = oldPDFs.size() - 1; i >= 0; i--)
			if (oldPDFs[i]->embeddedMode)
				oldPDFs.removeAt(i);
	for (int i = oldPDFs.size() - 1; i >= 0; i--)
		if (oldPDFs[i]->ignoreSynchronization())
			oldPDFs.removeAt(i);

	//if closing and opening is set, reuse the first document (reuse = optimization, so it does not close a viewer and creates an equal viewer afterwards)
	PDFDocument *reuse = nullptr;
	if ((embedded || windowed) && (closeEmbedded || closeWindowed) && !oldPDFs.isEmpty() ) {
		for (int i = 0; i < oldPDFs.size(); i++)
			if (oldPDFs[i]->embeddedMode == embedded) {
				reuse = oldPDFs.takeAt(i);
				break;
			}
	}

	//close old
	for (int i = oldPDFs.size() - 1; i >= 0; i--)
		if ( (oldPDFs[i]->embeddedMode && closeEmbedded) ||
		     (!oldPDFs[i]->embeddedMode && closeWindowed) ){
		        oldPDFs[i]->close();
			oldPDFs.removeAt(i);
		}


	//open new
	if (!embedded && !windowed) return;

	if (reuse) oldPDFs.insert(0, reuse);
	if (oldPDFs.isEmpty()) {
		PDFDocument *doc = qobject_cast<PDFDocument *>(newPdfPreviewer(embedded));
		REQUIRE(doc);
		doc->autoClose = autoClose;
		oldPDFs << doc;
                changePDFIconSize(configManager.guiPDFToolbarIconSize);
	}

	if (pdfFile.isNull()) {
		pdfFile = master.completeBaseName() + ".pdf";
	}
    if(!QFileInfo(pdfFile).isAbsolute() || !QFileInfo(pdfFile).isReadable()){
        pdfFile = buildManager.findCompiledFile(pdfFile, master); // don't search if file name is given as absolute path and exists
    }
	int ln = 0;
	int col = 0;
	if (currentEditorView()) {
		col = currentEditorView()->editor->cursor().columnNumber();
		ln = currentEditorView()->editor->cursor().lineNumber();
		int originalLineNumber = currentEditorView()->document->lineToLineSnapshotLineNumber(currentEditorView()->editor->cursor().line());
		if (originalLineNumber >= 0) ln = originalLineNumber;
	}
	foreach (PDFDocument *viewer, oldPDFs) {
		viewer->loadFile(pdfFile, master, displayPolicy);
		int pg = viewer->syncFromSource(getCurrentFileName(), ln, col, displayPolicy);
		viewer->fillRenderCache(pg);
        if (viewer->embeddedMode && configManager.viewerEnlarged) {
            sidePanelSplitter->hide();
			viewer->setStateEnlarged(true);
            //centralVSplitter->hide();
		}

		if (preserveDuplicates) break;
	}
#if defined Q_OS_MAC
	if (embedded)
		setMenuBar(configManager.menuParentsBar);
#endif

#else
	Q_UNUSED(master)
	Q_UNUSED(options)
	UtilsUi::txsCritical(tr("You have called the command to open the internal pdf viewer.\nHowever, you are using a version of TeXstudio that was compiled without the internal pdf viewer."));
#endif

}

bool Texstudio::checkProgramPermission(const QString &program, const QString &cmdId, LatexDocument *master)
{
	static const QRegExp txsCmd(QRegExp::escape(BuildManager::TXS_CMD_PREFIX) + "([^/ [{]+))");
	if (txsCmd.exactMatch(program)) return true;
	static QStringList programWhiteList;
	configManager.registerOption("Tools/Program Whitelist", &programWhiteList, QStringList() << "latex" << "pdflatex");
	if (programWhiteList.contains(program)) return true;
	if (buildManager.hasCommandLine(program)) return true;
	if (!master) return false;
	QString id = master->getMagicComment("document-id");
	if (id.contains("=")) return false;
	static QStringList individualProgramWhiteList;
	configManager.registerOption("Tools/Individual Program Whitelist", &individualProgramWhiteList, QStringList());
	if (!id.isEmpty() && individualProgramWhiteList.contains(id + "=" + program)) return true;
	int t = QMessageBox::warning(nullptr, TEXSTUDIO,
	                             tr("The document \"%1\" wants to override the command \"%2\" with \"%3\".\n\n"
	                                "Do you want to allow and run the new, overriding command?\n\n"
                                    "(a) Yes, allow the new command for this document (only if you trust this document)\n"
	                                "(b) Yes, allow the new command to be used for all documents (only if you trust the new command to handle arbitrary documents)\n"
	                                "(c) No, do not use the command \"%3\" and run the default \"%2\" command"
                                   ).arg(master ? master->getFileName() : "",cmdId,program),
                                 QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No,
                                 QMessageBox::No
                                 );
    if (t == QMessageBox::No) return false;
    if (t == QMessageBox::YesToAll) {
		programWhiteList.append(program);
		return true;
	}
	if (id.isEmpty()) {
		id = QUuid::createUuid().toString();
		master->updateMagicComment("document-id", id, true);
		if (master->getMagicComment("document-id") != id) return false;
	}
	individualProgramWhiteList.append(id + "=" + program);
	return true;
}

void Texstudio::runBibliographyIfNecessary(const QFileInfo &mainFile)
{
	if (!configManager.runLaTeXBibTeXLaTeX) return;
	if (runBibliographyIfNecessaryEntered) return;

	LatexDocument *rootDoc = documents.getRootDocumentForDoc();
	REQUIRE(rootDoc);

	QList<LatexDocument *> docs = rootDoc->getListOfDocs();
	QSet<QString> bibFiles;
	foreach (const LatexDocument *doc, docs) {
		foreach (const FileNamePair &bf, doc->mentionedBibTeXFiles()) {
			bibFiles.insert(bf.absolute);
		}
	}
	if(bibFiles.isEmpty()) {
		return; // don't try to compile bibtex files if there none
	}
	if (bibFiles == rootDoc->lastCompiledBibTeXFiles) {
		QDateTime bblLastModified = GetBblLastModified();
		if (bblLastModified.isValid()) {
			bool bibFilesChanged = false;
			foreach (const QString &bf, bibFiles) {
				//qDebug() << bf << ": "<<QFileInfo(bf).lastModified()<<" "<<bblLastModified;
                if (QFileInfo::exists(bf) && QFileInfo(bf).lastModified() > bblLastModified) {
					bibFilesChanged = true;
					break;
				}
			}
			if (!bibFilesChanged) return;
		}
	} else rootDoc->lastCompiledBibTeXFiles = bibFiles;

	runBibliographyIfNecessaryEntered = true;
	buildManager.runCommand(BuildManager::CMD_RECOMPILE_BIBLIOGRAPHY, mainFile);
	runBibliographyIfNecessaryEntered = false;
}

QDateTime Texstudio::GetBblLastModified(void)
{
	QFileInfo compileFile (documents.getTemporaryCompileFileName());
	QString compileDir(compileFile.absolutePath());
	FindInDirs findInDirs(true, false, compileDir);
	findInDirs.loadDirs(compileDir);
	findInDirs.loadDirs(BuildManager::resolvePaths(buildManager.additionalLogPaths));
	QString bblPathname = findInDirs.findAbsolute(compileFile.completeBaseName() + ".bbl");
	if (bblPathname == "") {
		return QDateTime();
	}
	return QFileInfo(bblPathname).lastModified();
}

void Texstudio::runInternalCommand(const QString &cmd, const QFileInfo &mainfile, const QString &options)
{
	if (cmd == BuildManager::CMD_VIEW_PDF_INTERNAL || (cmd.startsWith(BuildManager::CMD_VIEW_PDF_INTERNAL) && cmd[BuildManager::CMD_VIEW_PDF_INTERNAL.length()] == ' '))
		runInternalPdfViewer(mainfile, options);
	else if (cmd == BuildManager::CMD_CONDITIONALLY_RECOMPILE_BIBLIOGRAPHY)
		runBibliographyIfNecessary(mainfile);
	else if (cmd == BuildManager::CMD_VIEW_LOG) {
		loadLog();
		viewLog();
	} else UtilsUi::txsWarning(tr("Unknown internal command: %1").arg(cmd));
}

void Texstudio::runInternalCommand(const QString &cmd, const QString &mainfile, const QString &options){
    runInternalCommand(cmd,QFileInfo(mainfile),options);
}

void Texstudio::commandLineRequested(const QString &cmdId, QString *result, bool *)
{
	if (!buildManager.m_interpetCommandDefinitionInMagicComment) return;
	LatexDocument *rootDoc = documents.getRootDocumentForDoc();
	if (!rootDoc) return;
	QString magic = rootDoc->getMagicComment("TXS-program:" + cmdId);
	if (!magic.isEmpty()) {
		if (!checkProgramPermission(magic, cmdId, rootDoc)) return;
		*result = magic;
		return;
	}
	QString program = rootDoc->getMagicComment("program");
	if (program.isEmpty()) program = rootDoc->getMagicComment("TS-program");
	if (program.isEmpty()) return;

	if (cmdId == "quick") {
		QString compiler = buildManager.guessCompilerFromProgramMagicComment(program);
		QString viewer = buildManager.guessViewerFromProgramMagicComment(program);
		if (!viewer.isEmpty() && !compiler.isEmpty()) {
			*result = BuildManager::chainCommands(compiler, viewer);
        } else if (checkProgramPermission(program, cmdId, rootDoc)) {  // directly execute whatever program is. Why does quick behave differently from compile ?
			*result = program;
		}
	} else if (cmdId == "compile") {
        QString compiler = buildManager.guessCompilerFromProgramMagicComment(program);
        if(!compiler.isEmpty()){
            *result = compiler;
            // notify used magic comment
            outputView->insertMessageLine(tr("%!TeX program used: %1").arg(program));
        }else{
            // warn about unused magic comment
            outputView->insertMessageLine(tr("%!TeX program not recognized! (%1). Using default.").arg(program));
        }
	} else if (cmdId == "view") {
        QString viewer = buildManager.guessViewerFromProgramMagicComment(program);
        if(!viewer.isEmpty()){
            *result = viewer;
        }
	}
}

void Texstudio::beginRunningCommand(const QString &commandMain, bool latex, bool pdf, bool async)
{
	if (pdf) {
		runningPDFCommands++;
		if (async && pdf) runningPDFAsyncCommands++;
#ifndef NO_POPPLER_PREVIEW
		PDFDocument::isCompiling = true;
		PDFDocument::isMaybeCompiling |= runningPDFAsyncCommands > 0;
#endif

		if (configManager.autoCheckinAfterSaveLevel > 0) {
			QFileInfo fi(documents.getTemporaryCompileFileName());
			fi.setFile(fi.path() + "/" + fi.baseName() + ".pdf");
			if (fi.exists() && !fi.isWritable()) {
				//pdf not writeable, needs locking ?
				svn.lock(fi.filePath());
			}
		}
	}
    //outputView->resetMessagesAndLog(!configManager.showMessagesWhenCompiling);
	if (latex) {
		foreach (LatexEditorView *edView, editors->editors()) {
			edView->document->saveLineSnapshot();
		}
    }
	setStatusMessageProcess(QString(" %1 ").arg(buildManager.getCommandInfo(commandMain).displayName));
}

void Texstudio::connectSubCommand(ProcessX *p, bool showStdoutLocally)
{
	connect(p, SIGNAL(standardErrorRead(QString)), outputView, SLOT(insertMessageLine(QString)));
	if (p->showStdout()) {
		p->setShowStdout((configManager.showStdoutOption == 2) || (showStdoutLocally && configManager.showStdoutOption == 1));
		connect(p, SIGNAL(standardOutputRead(QString)), outputView, SLOT(insertMessageLine(QString)));
	}
}

void Texstudio::beginRunningSubCommand(ProcessX *p, const QString &commandMain, const QString &subCommand, const RunCommandFlags &flags)
{
	if (commandMain != subCommand)
        setStatusMessageProcess(QString(" %1: %2 ").arg(buildManager.getCommandInfo(commandMain).displayName,buildManager.getCommandInfo(subCommand).displayName));
	if (flags & RCF_COMPILES_TEX)
		clearLogEntriesInEditors();
	//outputView->resetMessages();
	connectSubCommand(p, (RCF_SHOW_STDOUT & flags));
}

void Texstudio::endRunningSubCommand(ProcessX *p, const QString &commandMain, const QString &subCommand, const RunCommandFlags &flags)
{
	if (p->exitCode() && (flags & RCF_COMPILES_TEX) && !logExists()) {
		if (!QFileInfo(QFileInfo(documents.getTemporaryCompileFileName()).absolutePath()).isWritable())
			UtilsUi::txsWarning(tr("You cannot compile the document in a non writable directory."));
		else
			UtilsUi::txsWarning(tr("Could not start %1.").arg( buildManager.getCommandInfo(commandMain).displayName + ":" + buildManager.getCommandInfo(subCommand).displayName + ":\n" + p->getCommandLine()));
	}
	if ((flags & RCF_CHANGE_PDF)  && !(flags & RCF_WAITFORFINISHED) && (runningPDFAsyncCommands > 0)) {
		runningPDFAsyncCommands--;
#ifndef NO_POPPLER_PREVIEW
		if (runningPDFAsyncCommands <= 0) PDFDocument::isMaybeCompiling = false;
#endif
	}

}

void Texstudio::endRunningCommand(const QString &commandMain, bool latex, bool pdf, bool async)
{
	Q_UNUSED(commandMain)
	Q_UNUSED(async)
	if (pdf) {
		runningPDFCommands--;
#ifndef NO_POPPLER_PREVIEW
		if (runningPDFCommands <= 0)
			PDFDocument::isCompiling = false;
#endif
	}
	setStatusMessageProcess(QString(" %1 ").arg(tr("Ready")));
	if (latex) emit infoAfterTypeset();
	previewIsAutoCompiling = false;
}

void Texstudio::processNotification(const QString &message)
{
	if (message.startsWith(tr("Error:")))
		outputView->showPage(outputView->MESSAGES_PAGE);
	outputView->insertMessageLine(message + "\n");
}
/*!
 * \brief clear log view in panel
 */
void Texstudio::clearLogs(){
    outputView->resetMessagesAndLog(!configManager.showMessagesWhenCompiling);
}

/*!
 * \brief Opens a new external terminal
 */
void Texstudio::openExternalTerminal(void)
{
	QString fileMain, fileCurrent;

	if ((fileMain = documents.getTemporaryCompileFileName()) == "") {
		fileMain = getUserDocumentFolder() + QDir::separator() + "none.tex";
	}
	if ((fileCurrent = getCurrentFileName()) == "") {
		fileCurrent = fileMain;
	}
	ExpandingOptions expOptions(
        QFileInfo(fileMain),
        QFileInfo(fileCurrent),
		currentEditorView() ? currentEditorView()->editor->cursor().lineNumber() + 1 : 0
	);
	ExpandedCommands expCommands = buildManager.expandCommandLine(
		BuildManager::CMD_TERMINAL_EXTERNAL,
		expOptions
	);
	if (expCommands.commands.isEmpty()) {
		return;
	}
	QString commandLine(expCommands.commands.first().command);
	ExecProgram execProgram(
		commandLine,
		"",
		QFileInfo(fileCurrent).absolutePath()
	);
#ifdef Q_OS_WIN
	execProgram.m_winProcModifier = [] (QProcess::CreateProcessArguments *args) {
		args->flags |= CREATE_NEW_CONSOLE;
	};
#endif
	bool execResult = execProgram.execDetached();
	outputView->insertMessageLine(
		execResult ?
		QString("Started external terminal program %1").arg(commandLine) :
		QString("Could not start external terminal program %1").arg(commandLine)
	);
}

/*!
 * \brief run a command which was triggered from a Qaction (menu or toolbar)
 * The actual command is stored as data in the action.
 * runCommand is used
 */
void Texstudio::commandFromAction()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (!act) return;
	runCommand(act->data().toString());
}
/*!
 * \brief clean auxilliary files
 * Uses CleanDialog for actual functionality
 */
void Texstudio::cleanAll()
{
	CleanDialog cleanDlg(this);
	if (cleanDlg.checkClean(documents)) {
		cleanDlg.exec();
	} else {
		UtilsUi::txsInformation(tr("No open project or tex file to clean."));
	}
}
/*!
 * \brief export document as html
 * Use WebPublishDialog for actual functionality
 */
void Texstudio::webPublish()
{
	if (!currentEditorView()) {
		UtilsUi::txsWarning(tr("No document open"));
		return;
	}
	if (!currentEditorView()->editor->getFileCodec()) return;
	fileSave();
	QString finame = documents.getCompileFileName();

	WebPublishDialog *ttwpDlg = new WebPublishDialog(this, configManager.webPublishDialogConfig, &buildManager,
	        currentEditorView()->editor->getFileCodec());
	ttwpDlg->ui.inputfileEdit->setText(finame);
	ttwpDlg->exec();
	delete ttwpDlg;
}
/*!
 * \brief export current document as html
 * Use document->exportAsHtml
 */
void Texstudio::webPublishSource()
{
	if (!currentEditor()) return;
	QDocumentCursor cur = currentEditor()->cursor();
	QString	html = currentEditor()->document()->exportAsHtml(cur.hasSelection() ? cur : QDocumentCursor(), true);
	fileNew(getCurrentFileName() + ".html");
	currentEditor()->insertText(html);
	/*QLabel* htmll = new QLabel(html, this);
	htmll->show();
	htmll->resize(300,300);*/
}
/*!
 * Remove latex commands
 */
void Texstudio::convertToPlainText(){
	if (!currentEditorView()) return;
	QList<LineInfo> inlines;
	QString plaintext;
	LatexDocument* doc = currentEditorView()->document;
	for (int i=0;i<=doc->lines();i++) {
		if (i != doc->lines() && doc->line(i).firstChar() != -1)
			inlines << LineInfo(doc->line(i).handle());
		else if (inlines.count()){
			//convert to plain text after each paragraph and at the end
			QList<TokenizedBlock> blocks = tokenizeWords(LatexParser::getInstancePtr(), inlines);
			foreach (const TokenizedBlock &tb, blocks)
				plaintext += tb.toString() + "\n\n";
			inlines.clear();
		}
	}
	fileNew();
	currentEditor()->setText(plaintext, false);
}
/*!
 * \brief open analyse text dialog
 * Makes use of TextAnalysisDialog
 */
void Texstudio::analyseText()
{
	if (!currentEditorView()) {
		UtilsUi::txsWarning(tr("No document open"));
		return;
	}
	if (!textAnalysisDlg) {
		textAnalysisDlg = new TextAnalysisDialog(this, tr("Text Analysis"));
		connect(textAnalysisDlg, SIGNAL(destroyed()), this, SLOT(analyseTextFormDestroyed()));
	}
	if (!textAnalysisDlg) return;
	textAnalysisDlg->setEditor(currentEditorView()->editor);//->document(), currentEditorView()->editor->cursor());
	textAnalysisDlg->init();
	textAnalysisDlg->interpretStructureTree(currentEditorView()->document->baseStructure);

	textAnalysisDlg->show();
	textAnalysisDlg->raise(); //not really necessary, since the dlg is always on top
	textAnalysisDlg->activateWindow();
}

void Texstudio::analyseTextFormDestroyed()
{
        textAnalysisDlg = nullptr;
}
/*!
 * \brief generate random text
 * convienience function
 */
void Texstudio::generateRandomText()
{
	if (!currentEditorView()) {
		UtilsUi::txsWarning(tr("The random text generator constructs new texts from existing words, so you have to open some text files"));
		return;
	}
	RandomTextGenerator generator(this, &documents);
	generator.exec();
}

//////////////// MESSAGES - LOG FILE///////////////////////

/// \brief check if log exists
/// \return true if log is found
///
bool Texstudio::logExists()
{
	QString finame = documents.getTemporaryCompileFileName();
	if (finame == "")
		return false;
	QString logPathname(getAbsoluteFilePath(documents.getLogFileName()));
	FindInDirs findInDirs(
		true,
		true,
		QFileInfo(logPathname).absolutePath(),
		BuildManager::resolvePaths(buildManager.additionalLogPaths)
	);
	return findInDirs.findAbsolute(logPathname) != "";
}
/*!
 * \brief load log from latex compilation
 * Try to find log in build dir as well as in additional log paths
 * Assume latin1 as text codec for log.
 * \return operation successful
 */
bool Texstudio::loadLog()
{
	outputView->getLogWidget()->resetLog();
	if (!documents.getCurrentDocument()) return false;
	QString compileFileName = documents.getTemporaryCompileFileName();
	if (compileFileName == "") {
		QMessageBox::warning(this, tr("Error"), tr("File must be saved and compiling before you can view the log"));
		return false;
	}
	QString logPathname(getAbsoluteFilePath(documents.getLogFileName()));
	FindInDirs findInDirs(
		true,
		true,
		QFileInfo(logPathname).absolutePath(),
		BuildManager::resolvePaths(buildManager.additionalLogPaths)
	);
	QString foundPathname = findInDirs.findAbsolute(logPathname);
	if (foundPathname == "") {
		return false;
	}
	QTextCodec * codec = QTextCodec::codecForName(configManager.logFileEncoding.toLatin1());
	return outputView->getLogWidget()->loadLogFile(
		foundPathname,
		compileFileName,
		codec ? codec : documents.getCurrentDocument()->codec()
	);
}
/// open log page on panel
void Texstudio::showLog()
{
	outputView->showPage(outputView->LOG_PAGE);
}

///shows the log (even if it is empty)
void Texstudio::viewLog()
{
	showLog();
	setLogMarksVisible(true);
	if (configManager.goToErrorWhenDisplayingLog && hasLatexErrors()) {
		int errorMarkID = outputView->getLogWidget()->getLogModel()->markID(LT_ERROR);
		if (!gotoMark(false, errorMarkID)) {
			gotoMark(true, errorMarkID);
		}
	}
}

void Texstudio::viewLogOrReRun(LatexCompileResult *result)
{
	loadLog();
	REQUIRE(result);
	if (hasLatexErrors()) {
		onCompileError();
		*result = LCR_ERROR;
	} else {
		*result = LCR_NORMAL;
		if (outputView->getLogWidget()->getLogModel()->existsReRunWarning())
			*result = LCR_RERUN;
		else if (configManager.runLaTeXBibTeXLaTeX) {
			//run bibtex if citation is unknown to bibtex but contained in an included bib file
			QStringList missingCitations = outputView->getLogWidget()->getLogModel()->getMissingCitations();
			bool runBibTeX = false;
			foreach (const QString &s, missingCitations) {
				for (int i = 0; i < documents.mentionedBibTeXFiles.count(); i++) {
					if (!documents.bibTeXFiles.contains(documents.mentionedBibTeXFiles[i])) continue;
					BibTeXFileInfo &bibTex = documents.bibTeXFiles[documents.mentionedBibTeXFiles[i]];
					if (bibTex.ids.contains(s)) {
						runBibTeX = true;
						break;
					}
				}
				if (runBibTeX) break;
			}
			if (runBibTeX)
				*result = LCR_RERUN_WITH_BIBLIOGRAPHY;
		}
	}
}

////////////////////////// ERRORS /////////////////////////////
/*!
 * \brief post processing after latex compilation errors are detected
 */
void Texstudio::onCompileError()
{
	if (!previewIsAutoCompiling && configManager.getOption("Tools/ShowLogInCaseOfCompileError").toBool()) {
		viewLog();
	} else {
		setLogMarksVisible(true);
	}
}

/// changes visibilita of log markers in all editors
void Texstudio::setLogMarksVisible(bool visible)
{
	foreach (LatexEditorView *edView, editors->editors()) {
		edView->setLogMarksVisible(visible);
	}
	QAction *act = getManagedAction("main/tools/logmarkers");
	if (act) act->setChecked(visible);
}

/// removes the log entries from all editors
void Texstudio::clearLogEntriesInEditors()
{
	foreach (LatexEditorView *edView, editors->editors()) {
		edView->clearLogMarks();
	}
}

/// adds the current log entries to all editors
void Texstudio::updateLogEntriesInEditors()
{
	clearLogEntriesInEditors();
	LatexLogModel *logModel = outputView->getLogWidget()->getLogModel();
	QHash<QString, LatexEditorView *> tempFilenames; //temporary maps the filenames (as they appear in this log!) to the editor
	int errorMarkID = QLineMarksInfoCenter::instance()->markTypeId("error");
	int warningMarkID = QLineMarksInfoCenter::instance()->markTypeId("warning");
	int badboxMarkID = QLineMarksInfoCenter::instance()->markTypeId("badbox");

	for (int i = logModel->count() - 1; i >= 0; i--) {
		if (logModel->at(i).oldline != -1) {
			LatexEditorView *edView;
			if (tempFilenames.contains(logModel->at(i).file)) edView = tempFilenames.value(logModel->at(i).file);
			else {
				edView = getEditorViewFromFileName(logModel->at(i).file, true);
				tempFilenames[logModel->at(i).file] = edView;
			}
			if (edView) {
				int markID;
				switch (logModel->at(i).type) {
				case LT_ERROR:
					markID = errorMarkID;
					break;
				case LT_WARNING:
					markID = warningMarkID;
					break;
				case LT_BADBOX:
					markID = badboxMarkID;
					break;
				default:
					markID = -1;
				}
				edView->addLogEntry(i, logModel->at(i).oldline - 1, markID);
			}
		}
	}
}
/*!
 * \brief check if the log viewer contains latex errors
 * \return true if latex errors present
 */
bool Texstudio::hasLatexErrors()
{
	return outputView->getLogWidget()->getLogModel()->found(LT_ERROR);
}

bool Texstudio::gotoNearLogEntry(int lt, bool backward, QString notFoundMessage)
{
	if (!outputView->getLogWidget()->logPresent()) {
		loadLog();
	}
	if (outputView->getLogWidget()->logPresent()) {
        if (outputView->getLogWidget()->getLogModel()->found(static_cast<LogType>(lt) )) {
			showLog();
			setLogMarksVisible(true);
            return gotoMark(backward, outputView->getLogWidget()->getLogModel()->markID(static_cast<LogType>(lt) ));
		} else {
			UtilsUi::txsInformation(notFoundMessage);
		}
	}
	return false;
}

void Texstudio::clearMarkers()
{
	setLogMarksVisible(false);
}
//////////////// HELP /////////////////
/*!
 * \brief opem latex2e.html in external browser
 * The latex2e help file is present as html. An external browser is called via QDesktopService to open that file.
 */

void Texstudio::latexHelp()
{
	QString latexHelp = findResourceFile("latex2e.html");
	if (latexHelp == "")
		QMessageBox::warning(this, tr("Error"), tr("File not found"));
	else if (!QDesktopServices::openUrl("file:///" + latexHelp))
		QMessageBox::warning(this, tr("Error"), tr("Could not open browser"));
}
/*!
 * \brief open user manual in external browser
 * The usermanual is present as html. An external browser is called via QDesktopService to open that file.
 */
void Texstudio::userManualHelp()
{
    QString latexHelp = findResourceFile("getting_started.html");
	if (latexHelp == "")
		QMessageBox::warning(this, tr("Error"), tr("File not found"));
	else if (!QDesktopServices::openUrl("file:///" + latexHelp))
		QMessageBox::warning(this, tr("Error"), tr("Could not open browser"));
}
/*!
 * \brief exec Help
 * First compile a list of all packages (which txs has detected)
 * Present that list via a simple selection dialog which in term calls texdoc to present package help.
 * txs internal package names are filtered out.
 */
void Texstudio::texdocHelp()
{
	QString selection;
	QStringList packages;
	if (currentEditorView()) {
		selection = currentEditorView()->editor->cursor().selectedText();
		foreach (const QString &key, currentEditorView()->document->parent->cachedPackages.keys()) {
			if (currentEditorView()->document->parent->cachedPackages[key].completionWords.isEmpty())
				// remove empty packages which probably do not exist
				continue;
			packages << LatexPackage::keyToPackageName(key);
		}

		packages.removeDuplicates();
		packages.removeAll("latex-209");
		packages.removeAll("latex-dev");
		packages.removeAll("latex-l2tabu");
		packages.removeAll("latex-document");
		packages.removeAll("tex");
	}

    help.execTexdocDialog(packages, selection);
}
/*!
 * \brief show about dialog
 * About dialog is produced in AboutDialog
 */
void Texstudio::helpAbout()
{
	// The focus will return to the parent. Therefore we have to provide the correct caller (may be a viewer window).
	QWidget *parentWindow = UtilsUi::windowForObject(sender(), this);
	AboutDialog *abDlg = new AboutDialog(parentWindow);
	abDlg->exec();
	delete abDlg;
}
////////////// OPTIONS //////////////////////////////////////

/*!
 * \brief Show the general options dialog and activate changed options in the program
 * The method tries to detect some changes in order to redo with changed settings only when necessary.
 * Among otheres these areas include style, dark mode and online sytax check.
 */
void Texstudio::generalOptions()
{
    bool oldDarkMode = darkMode;
    int oldModernStyle = modernStyle;
	int oldIconTheme = iconTheme;
    bool oldSystemTheme = useSystemTheme;
    int oldReplaceQuotes = configManager.replaceQuotes;
    autosaveTimer.stop();
    m_formats->modified = false;
    bool realtimeChecking = configManager.editorConfig->realtimeChecking;
    bool inlineSpellChecking = configManager.editorConfig->inlineSpellChecking;
    bool inlineCitationChecking = configManager.editorConfig->inlineCitationChecking;
    bool inlineReferenceChecking = configManager.editorConfig->inlineReferenceChecking;
    bool inlineSyntaxChecking = configManager.editorConfig->inlineSyntaxChecking;
    QString additionalBibPaths = configManager.additionalBibPaths;
    QStringList loadFiles = configManager.completerConfig->getLoadedFiles();

    // init pdf shortcuts if pdfviewer is not open
#ifndef NO_POPPLER_PREVIEW
    PDFDocument *pdfviewerWindow=nullptr;
    if(PDFDocument::documentList().isEmpty()){
        pdfviewerWindow = new PDFDocument(configManager.pdfDocumentConfig, false);
        pdfviewerWindow->hide();
    }
#endif


    if (configManager.possibleMenuSlots.isEmpty()) {
        for (int i = 0; i < staticMetaObject.methodCount(); i++) configManager.possibleMenuSlots.append(staticMetaObject.method(i).methodSignature());
        for (int i = 0; i < QEditor::staticMetaObject.methodCount(); i++) configManager.possibleMenuSlots.append("editor:" + QString(QEditor::staticMetaObject.method(i).methodSignature()));
        for (int i = 0; i < LatexEditorView::staticMetaObject.methodCount(); i++) configManager.possibleMenuSlots.append("editorView:" + QString(LatexEditorView::staticMetaObject.method(i).methodSignature()));
        configManager.possibleMenuSlots = configManager.possibleMenuSlots.filter(QRegularExpression("^[^*]+$"));
    }
    // GUI scaling
    connect(&configManager, &ConfigManager::iconSizeChanged, this, &Texstudio::changeIconSize);
    connect(&configManager, &ConfigManager::secondaryIconSizeChanged, this, &Texstudio::changeSecondaryIconSize);
    connect(&configManager, &ConfigManager::pdfIconSizeChanged , this, &Texstudio::changePDFIconSize);
    connect(&configManager, &ConfigManager::symbolGridIconSizeChanged, this, [=](int size) { changeSymbolGridIconSize(size); });

    // The focus will return to the parent. Therefore we have to provide the correct caller (may be a viewer window).
    QWidget *parentWindow = UtilsUi::windowForObject(sender(), this);

    if (configManager.execConfigDialog(parentWindow)) {
        QApplication::setOverrideCursor(Qt::WaitCursor);

        configManager.editorConfig->settingsChanged();

        spellerManager.setDictPaths(configManager.parseDirList(configManager.spellDictDir));
        spellerManager.setDefaultSpeller(configManager.spellLanguage);

        GrammarCheck::staticMetaObject.invokeMethod(grammarCheck, "init", Qt::QueuedConnection, Q_ARG(LatexParser, latexParser), Q_ARG(GrammarCheckerConfig, *configManager.grammarCheckerConfig));

        if (configManager.autoDetectEncodingFromLatex || configManager.autoDetectEncodingFromChars) QDocument::setDefaultCodec(nullptr);
        else QDocument::setDefaultCodec(configManager.newFileEncoding);
        QDocument::removeGuessEncodingCallback(&ConfigManager::getDefaultEncoding);
        QDocument::removeGuessEncodingCallback(&Encoding::guessEncoding);
        if (configManager.autoDetectEncodingFromLatex)
            QDocument::addGuessEncodingCallback(&Encoding::guessEncoding);
        if (configManager.autoDetectEncodingFromChars)
            QDocument::addGuessEncodingCallback(&ConfigManager::getDefaultEncoding);

        symbolListModel->setDarkmode(darkMode);

        ThesaurusDialog::prepareDatabase(configManager.parseDir(configManager.thesaurus_database));
        if (additionalBibPaths != configManager.additionalBibPaths) documents.updateBibFiles(true);

        // update syntaxChecking with alls docs
        foreach (LatexDocument *doc, documents.getDocuments()) {
            doc->enableSyntaxCheck(configManager.editorConfig->inlineSyntaxChecking && configManager.editorConfig->realtimeChecking);
        }

        //update highlighting ???
        bool updateHighlighting = (inlineSpellChecking != configManager.editorConfig->inlineSpellChecking);
        updateHighlighting |= (inlineCitationChecking != configManager.editorConfig->inlineCitationChecking);
        updateHighlighting |= (inlineReferenceChecking != configManager.editorConfig->inlineReferenceChecking);
        updateHighlighting |= (inlineSyntaxChecking != configManager.editorConfig->inlineSyntaxChecking);
        updateHighlighting |= (realtimeChecking != configManager.editorConfig->realtimeChecking);
        updateHighlighting |= (additionalBibPaths != configManager.additionalBibPaths);
        // recheck syntax when spellchecking and/or syntaxchecking has been effectively turned on
        bool recheckSyntax=(configManager.editorConfig->realtimeChecking &&(configManager.editorConfig->inlineSyntaxChecking || configManager.editorConfig->inlineSpellChecking)) || ((configManager.editorConfig->inlineSyntaxChecking && !inlineSyntaxChecking)||(configManager.editorConfig->inlineSpellChecking && !inlineSpellChecking));

        // activate/deactivate speller ...
        SpellerUtility::inlineSpellChecking= configManager.editorConfig->inlineSpellChecking && configManager.editorConfig->realtimeChecking;

        // dark/light-mode switch
        if(oldDarkMode != darkMode){
            // reload other formats
            QSettings *config=configManager.getSettings();
            config->beginGroup(darkMode ? "formatsDark" : "formats");
            m_formats = new QFormatFactory(darkMode ? ":/qxs/defaultFormatsDark.qxf" : ":/qxs/defaultFormats.qxf", this); //load default formats from resource file
            m_formats->load(*config, true); //load customized formats
            QDocument::setDefaultFormatScheme(m_formats);
            //m_formats->modified=true;
            config->endGroup();
            updateHighlighting=true;
        }
        // check for change in load completion files
        QStringList newLoadedFiles = configManager.completerConfig->getLoadedFiles();
        foreach (const QString &elem, newLoadedFiles) {
            if (loadFiles.removeAll(elem) == 0)
                updateHighlighting = true;
            if (updateHighlighting)
                break;
        }
        if (!loadFiles.isEmpty())
            updateHighlighting = true;
        buildManager.clearPreviewPreambleCache();//possible changed latex command / preview behaviour

        if (currentEditorView()) {
            foreach (LatexEditorView *edView, editors->editors()) {
                edView->updateSettings();
                if (updateHighlighting) {
                    edView->clearOverlays(); // for disabled syntax check
                    if (configManager.editorConfig->realtimeChecking) {
                        edView->document->updateLtxCommands();
                        edView->documentContentChanged(0, edView->document->lines());
                        edView->document->updateCompletionFiles(false, true);
                        if(recheckSyntax){
                            edView->reCheckSyntax(0);
                        }
                    } else {
                        edView->clearOverlays();
                    }
                }
                QSearchReplacePanel *searchpanel = qobject_cast<QSearchReplacePanel *>(edView->codeeditor->panels("Search")[0]);
                searchpanel->updateIcon();
            }
            if (m_formats->modified)
                QDocument::setBaseFont(QDocument::baseFont(), true);
            updateCaption();

            if (documents.indentIncludesInStructure != configManager.indentIncludesInStructure ||
                    documents.showCommentedElementsInStructure != configManager.showCommentedElementsInStructure ||
                    documents.markStructureElementsBeyondEnd != configManager.markStructureElementsBeyondEnd ||
                    documents.markStructureElementsInAppendix != configManager.markStructureElementsInAppendix) {
                documents.indentIncludesInStructure = configManager.indentIncludesInStructure;
                documents.showCommentedElementsInStructure = configManager.showCommentedElementsInStructure;
                documents.markStructureElementsBeyondEnd = configManager.markStructureElementsBeyondEnd;
                documents.markStructureElementsInAppendix = configManager.markStructureElementsInAppendix;
                foreach (LatexDocument *doc, documents.documents)
                    updateStructure(false, doc);
            }
        }
        if (oldReplaceQuotes != configManager.replaceQuotes)
            updateUserMacros();
        // scale GUI
        changeIconSize(configManager.guiToolbarIconSize);
        changeSecondaryIconSize(configManager.guiSecondaryToolbarIconSize);
        changePDFIconSize(configManager.guiPDFToolbarIconSize);
        changeSymbolGridIconSize(configManager.guiSymbolGridIconSize, false);
        //custom toolbar
        setupToolBars();
        //completion
        mCompleterCommandsNeedsUpdate=true;
        completerNeedsUpdate();
        completer->setConfig(configManager.completerConfig);
        //update changed line mark colors
        QList<QLineMarkType> &marks = QLineMarksInfoCenter::instance()->markTypes();
        for (int i = 0; i < marks.size(); i++)
            if (m_formats->format("line:" + marks[i].id).background.isValid())
                marks[i].color = m_formats->format("line:" + marks[i].id).background;
            else
                marks[i].color = Qt::transparent;
        // update all docuemnts views as spellcheck may be different
        QEditor::setEditOperations(configManager.editorKeys, false); // true -> false, otherwise edit operation can't be removed, e.g. tab for indentSelection
        foreach (LatexEditorView *edView, editors->editors()) {
            QEditor *ed = edView->editor;
            if(configManager.interfaceStyle!="Orion Dark")
                edView->updatePalette(QApplication::palette());
            ed->document()->markFormatCacheDirty();
            ed->update();
        }
        if (oldModernStyle != modernStyle || oldIconTheme != iconTheme|| oldSystemTheme != useSystemTheme) {
            iconCache.clear();
            setupMenus();
            setupDockWidgets();
        }
        updateUserToolMenu();
        QApplication::restoreOverrideCursor();
    }
    if (configManager.autosaveEveryMinutes > 0) {
        autosaveTimer.start(configManager.autosaveEveryMinutes * 1000 * 60);
    }
#ifndef NO_POPPLER_PREVIEW
    foreach (PDFDocument *viewer, PDFDocument::documentList()) {
        viewer->reloadSettings();
    }
    if(pdfviewerWindow){
        pdfviewerWindow->close();
        delete pdfviewerWindow;
    }
#endif
    // update action from Menu Preview Display Mode
	setCheckedPreviewModeAction();
#ifdef INTERNAL_TERMINAL
    outputView->getTerminalWidget()->updateSettings();
#endif
}

/*!
 * \brief execute commandLine arguments
 * txs can be started with command line arguments.
 * Most of them are interpreted here as they interact with documents
 * \param detected command line arguments as string list
 * \param realCmdLine
 */
void Texstudio::executeCommandLine(const QStringList &args, bool realCmdLine)
{
	// parse command line
	QStringList filesToLoad;
	bool hasExplicitRoot = false;

	int line = -1;
	int col = 0;
	QString cite;
#ifndef NO_POPPLER_PREVIEW
	int page = -1;
	bool pdfViewerOnly = false;
#endif
	for (int i = 0; i < args.size(); ++i) {
		if (args[i] == "") continue;
		if (args[i][0] != '-')  filesToLoad << args[i];
		//-form is for backward compatibility
		if (args[i] == "--root" || args[i] == "--master") hasExplicitRoot = true;
		if (args[i] == "--line" && i + 1 < args.size()) {
			QStringList lineCol = args[++i].split(":");
			line = lineCol.at(0).toInt() - 1;
			if (lineCol.count() >= 2) {
				col = lineCol.at(1).toInt();
				if ((col) < 0) col = 0;
			}
		}
		if (args[i] == "--insert-cite" && i + 1 < args.size()) {
			cite = args[++i];
		}
        if (args[i] == "--texpath" && i + 1 < args.size()) {
            QString texPath=args[++i];
            buildManager.resetDefaultCommands(texPath);
        }
#ifndef NO_POPPLER_PREVIEW
		if (args[i] == "--pdf-viewer-only") pdfViewerOnly = true;
		if (args[i] == "--page") page = args[++i].toInt() - 1;
#endif
	}

#ifndef NO_POPPLER_PREVIEW
	if (pdfViewerOnly) {
		if (PDFDocument::documentList().isEmpty())
			newPdfPreviewer();
		foreach (PDFDocument *viewer, PDFDocument::documentList()) {
			if (!filesToLoad.isEmpty()) viewer->loadFile(filesToLoad.first());
			connect(viewer, SIGNAL(destroyed()), SLOT(deleteLater()));
			viewer->show();
			viewer->setFocus();
			if (page != -1) viewer->goToPage(page);
		}
		hide();
        return;
	}
#endif

    	// execute command line
	foreach (const QString &fileToLoad, filesToLoad) {
		QFileInfo ftl(fileToLoad);
		if (fileToLoad != "") {
			if (ftl.isDir()) {
				QMessageBox::warning(this, "", tr("%1 is an invalid TeX project directory.").arg(ftl.absoluteFilePath()));
				exit(1);
			} else if (ftl.exists()) {
				if (ftl.suffix() == Session::fileExtension() || ftl.suffix() == "txss") {
					loadSession(ftl.filePath());
				} else {
					load(fileToLoad, hasExplicitRoot);
				}
			} else if (ftl.absoluteDir().exists()) {
				fileNew(ftl.absoluteFilePath());
				if (hasExplicitRoot) {
					setExplicitRootDocument(currentEditorView()->getDocument());
				}
				//return ;
			}
		}
	}

	if (line != -1) {
	        gotoLine(line, col, nullptr, QEditor::KeepSurrounding | QEditor::ExpandFold);
		QTimer::singleShot(500, currentEditor(), SLOT(ensureCursorVisible())); //reshow cursor in case the windows size changes
	}

	if (!cite.isNull()) {
		insertCitation(cite);
	}

#ifndef QT_NO_DEBUG
	//execute test after command line is known
	if (realCmdLine) { //only at start
        bool result=executeTests(args);

	if (args.contains("--update-translations")) {
	    generateAddtionalTranslations();
	}
        if (args.contains("--auto-tests")) {
            if(result){
                QTimer::singleShot(4000, this, SLOT(fileExit()));
            }else{
                QTimer::singleShot(4000, this, SLOT(fileExitWithError()));
            }
        }
	}
#endif

	if (realCmdLine) Guardian::summon();
    return;
}
/*!
 * \brief hide splash screen again
 */
void Texstudio::hideSplash()
{
	if (splashscreen) splashscreen->hide();
}
/*!
 * \brief execute self tests
 * \param command line arguments which may influence the behavior of this method
 * options are:
 * --disable-tests  : no tests are run
 * --execute-tests  : tests are run even if they were executed already in a previous run
 * --execute-all-tests  : run tests, including some more time consuming ones
 * --auto-tests  : run a subset of tests which work on travis-ci
 * \return false if some tests failed
 */
bool Texstudio::executeTests(const QStringList &args)
{
    QFileInfo myself(QCoreApplication::applicationFilePath());
    if (args.contains("--disable-tests")) return true; // pass
#if !defined(QT_NO_DEBUG) && !defined(NO_TESTS)
    bool testResult=true; // pass, false -> fail
    bool autoTests = args.contains("--auto-tests");
    bool allTests = args.contains("--execute-all-tests")
            //execute all tests once a week or if command paramter is set
            || (configManager.debugLastFullTestRun.daysTo(myself.lastModified()) > 6);
    if(autoTests)
        allTests=false;
    if (args.contains("--execute-tests") || (configManager.debugLastFileModification.isValid() && myself.lastModified() != configManager.debugLastFileModification) || allTests || autoTests) {
        fileNew();
        if (!currentEditorView() || !currentEditorView()->editor){
            if(autoTests){
                qDebug()<<"Autotest execution failed!";
                return false;
            }else{
                QMessageBox::critical(nullptr, "wtf?", "test failed", QMessageBox::Ok);
            }
        }
        if (allTests) configManager.debugLastFullTestRun = myself.lastModified();

        TestManager testManager;
        connect(&testManager, SIGNAL(newMessage(QString)), this, SLOT(showTestProgress(QString)));
        TestManager::TestLevel testLevel=allTests ? TestManager::TL_ALL : TestManager::TL_FAST;
        if(autoTests){
            testLevel=TestManager::TL_AUTO;
        }
        QString result = testManager.execute(testLevel, currentEditorView(), currentEditorView()->codeeditor, currentEditorView()->editor, &buildManager);
        if(autoTests){
            currentEditorView()->close();
            QStringList lines=result.split("\n");
            int cnt=0;
            foreach(const QString line,lines){
                qDebug()<<line;
                if(line.startsWith("FAIL")){
                    cnt++;
                }
            }
            if(cnt>0){
                qDebug()<<QString("%1 tests failed!").arg(cnt);
                return false;
            }
        }else{
            m_languages->setLanguageFromName(currentEditorView()->editor, "TXS Test Results");
            currentEditorView()->editor->setText(result, false);
            if (result.startsWith("*** THERE SEEM TO BE FAILED TESTS! ***")) {
                QSearchReplacePanel *searchpanel = qobject_cast<QSearchReplacePanel *>(currentEditorView()->codeeditor->panels("Search")[0]);
                if (searchpanel) {
                    searchpanel->find("FAIL!", false, false, false, false, true);
                }
            }
        }
        configManager.debugLastFileModification = QFileInfo(QCoreApplication::applicationFilePath()).lastModified();
    }
    return testResult; // pass
#else
    return false;  // trying to execute tests, but tests are not available.
#endif
}

void Texstudio::showTestProgress(const QString &message)
{
	outputView->insertMessageLine(message);
    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents | QEventLoop::ExcludeSocketNotifiers);
}
/*!
 * \brief notfication when left panel was switched
 * Mainly used to notice when global TOC/structureWidget becomes visible
 * \param widget
 */
void Texstudio::leftPanelChanged(QWidget *widget)
{
       if(widget==topTOCTreeWidget){
           // update TOC when the TOC first becomes visisble
           updateTOC();
       }
       if(widget==structureTreeWidget){
           // update StructureWidget when the structure first becomes visisble
           updateStructureLocally();
       }
}
/*!
 * \brief generate translations for definition files
 * some command insertions are control via definition files, not c++ source code
 * This method reads in those commands and generate a pseudo sorce code (additionaltranslations.cpp) which can be used to generate translations
 * The translation for the pseudo code are used to do the translation of the commands in the definition files
 */
void Texstudio::generateAddtionalTranslations()
{
    qDebug()<<"writing translations for uiconfig.xml";
	QStringList translations;
	translations << "/******************************************************************************";
	translations << " * Do not manually edit this file. It is automatically generated by a call to";
	translations << " * texstudio --update-translations";
	translations << " * This generates some additional translations which lupdate doesn't find";
        translations << " * (e.g. from uiconfig.xml, color names, qnfa format names and tags) ";
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

	CodeSnippet::debugDisableAutoTranslate = true;
	QStringList tagNames = QStringList() << "menu" << "insert" << "action";
	foreach (const QString &tag, tagNames) {
		QDomNodeList nodes = xml.elementsByTagName(tag);
		for(int i = 0; i < nodes.count(); i++)
		{
			QDomNode current = nodes.at(i);
			QDomNamedNodeMap attribs = current.attributes();
			QString text = attribs.namedItem("text").nodeValue();
			if (!text.isEmpty() && !commandOnly.exactMatch(text))
				translations << "QT_TRANSLATE_NOOP(\"ConfigManager\", \"" + text.replace("\\", "\\\\").replace("\"", "\\\"") + "\"), ";
            QString info = attribs.namedItem("info").nodeValue();
            if (!info.isEmpty() && !commandOnly.exactMatch(info))
                translations << "QT_TRANSLATE_NOOP(\"ConfigManager\", \"" + info.replace("\\", "\\\\").replace("\"", "\\\"") + "\"), ";
			QString insert = attribs.namedItem("insert").nodeValue();
			if (!insert.isEmpty()) {
				CodeSnippet cs(insert, false);
				for (int i = 0; i < cs.placeHolders.size(); i++)
					for (int j = 0; j < cs.placeHolders[i].size(); j++)
						if (cs.placeHolders[i][j].flags & CodeSnippetPlaceHolder::Translatable)
							translations << "QT_TRANSLATE_NOOP(\"CodeSnippet_PlaceHolder\", \"" + cs.lines[i].mid(cs.placeHolders[i][j].offset, cs.placeHolders[i][j].length) + "\"), ";
			}
		}
	}
        // default formats
	QFile xmlFile2(":/qxs/defaultFormats.qxf");
	xmlFile2.open(QIODevice::ReadOnly);
	xml.setContent(&xmlFile2);
	QDomNodeList formats = xml.documentElement().elementsByTagName("format");
	for (int i = 0; i < formats.size(); i++)
		translations << "QT_TRANSLATE_NOOP(\"QFormatConfig\", \"" + formats.at(i).attributes().namedItem("id").nodeValue() + "\"), ";
	translations << "QT_TRANSLATE_NOOP(\"QFormatConfig\", \"normal\"),";
	for (int i = 0; i < configManager.managedToolBars.size(); i++)
		translations << "QT_TRANSLATE_NOOP(\"Texstudio\",\"" + configManager.managedToolBars[i].name + "\"),";

        // Tags
        QDir dir("tags");
        QStringList l_fn=dir.entryList({"*.xml"});
        for(const QString &fn: l_fn){
            QFile xmlFile3("tags/"+fn);
            xmlFile3.open(QIODevice::ReadOnly);
            xml.setContent(&xmlFile3);

            QStringList tagNames = QStringList() << "section" << "item";
            foreach (const QString &tag, tagNames) {
                    QDomNodeList nodes = xml.elementsByTagName(tag);
                    for(int i = 0; i < nodes.count(); i++)
                    {
                            QDomNode current = nodes.at(i);
                            QDomNamedNodeMap attribs = current.attributes();
                            QString text = attribs.namedItem("txt").nodeValue();
                            if (!text.isEmpty() && !commandOnly.exactMatch(text)){
                                    translations << "QT_TRANSLATE_NOOP(\"XmlTagsListWidget\", \"" + text.replace("\\", "\\\\").replace("\"", "\\\"") + "\"), ";
                            }else{
                                text = attribs.namedItem("title").nodeValue();
                                if (!text.isEmpty()){
                                        translations << "QT_TRANSLATE_NOOP(\"XmlTagsListWidget\", \"" + text.replace("\\", "\\\\").replace("\"", "\\\"") + "\"), ";
                                }
                            }
                            QString insert = attribs.namedItem("insert").nodeValue();
                            if (!insert.isEmpty()) {
                                    CodeSnippet cs(insert, false);
                                    for (int i = 0; i < cs.placeHolders.size(); i++)
                                            for (int j = 0; j < cs.placeHolders[i].size(); j++)
                                                    if (cs.placeHolders[i][j].flags & CodeSnippetPlaceHolder::Translatable)
                                                            translations << "QT_TRANSLATE_NOOP(\"CodeSnippet_PlaceHolder\", \"" + cs.lines[i].mid(cs.placeHolders[i][j].offset, cs.placeHolders[i][j].length) + "\"), ";
                            }
                    }
            }
        }
        CodeSnippet::debugDisableAutoTranslate = false;
        // format names
	foreach (const QString &s, m_languages->languages())
		translations << "QT_TRANSLATE_NOOP(\"Texstudio\", \"" + s + "\", \"Format name of language definition \"), ";

	translations << "\"\"};";
	translations << "#endif\n\n";

    QFile translationFile("src/additionaltranslations.cpp");
	if (translationFile.open(QIODevice::WriteOnly)) {
		translationFile.write(translations.join("\n").toLatin1());
		translationFile.close();
	}
    QFileInfo fi(translationFile);
    qDebug()<<"path:"<<fi.absoluteFilePath();
}

void Texstudio::onOtherInstanceMessage(const QString &msg)   // Added slot for messages to the single instance
{
	show();
	activateWindow();
	executeCommandLine(msg.split("#!#"), false);
}

void Texstudio::setAutomaticRootDetection()
{
        documents.setMasterDocument(nullptr);
}

void Texstudio::setExplicitRootDocument(LatexDocument *doc)
{
	if (!doc) {
		setAutomaticRootDetection();
		return;
	}
	if (doc->getFileName().isEmpty() && doc->getEditorView()) {
		editors->setCurrentEditor(doc->getEditorView());
		fileSave();
	}
	if (doc->getFileName().isEmpty()) {
		UtilsUi::txsWarning(tr("You have to save the file before it can be defined as root document."));
		return;
	}
	documents.setMasterDocument(doc);
}

void Texstudio::setCurrentDocAsExplicitRoot()
{
	if (currentEditorView()) {
		setExplicitRootDocument(currentEditorView()->document);
	}
}

////////////////// VIEW ////////////////
void Texstudio::gotoNextDocument()
{
	// TODO check: can we have managed action connecting to the Editors slot directly? Then we could remove this slot
	editors->activateNextEditor();
}

void Texstudio::gotoPrevDocument()
{
	// TODO check: can we have managed action connecting to the Editors slot directly? Then we could remove this slot
	editors->activatePreviousEditor();
}

void Texstudio::gotoOpenDocument()
{
	QAction *act = qobject_cast<QAction *>(sender());
	REQUIRE(act);
	editors->setCurrentEditor(act->data().value<LatexEditorView *>());
}

/*!
 * Update the document menu. If only the name of the current file changed, use localChange = true
 * for a faster update.
 * Note: localChange is a low-cost variant which is basically there because updateCaption() calls this
 * far too often even when it's not necessary. The calling logic (in particular updateCaption and its
 * uses should be refactored).
 */
void Texstudio::updateOpenDocumentMenu(bool localChange)
{
	if (localChange) {
		LatexEditorView *edView = currentEditorView();
		QMenu *menu = configManager.getManagedMenu("main/view/documents");
		if (!menu) return;
		foreach (QAction *act, menu->actions()) {
			if (edView == act->data().value<LatexEditorView *>()) {
				act->setText(edView->displayNameForUI());
				//qDebug() << "local SUCCESS" << act->text() << edView->displayName();
				return;
			}
		}
		//qDebug() << "local updateOpenDocumentMenu failed. Falling back to complete update.";
		// if there was no editor for a local change, fall back to a complete update of the menu
	}
	QStringList names;
	QList<QVariant> data;
	foreach (LatexEditorView *edView, editors->editors()) {
		names << edView->displayNameForUI();
		data << QVariant::fromValue<LatexEditorView *>(edView);
	}
	//qDebug() << "complete" << names;
	configManager.updateListMenu("main/view/documents", names, "doc", false, SLOT(gotoOpenDocument()), 0, true, 0, data);
}

void Texstudio::onEditorsReordered()
{
	// we currently reorder the documents so that their order matches the order of editors
	// this is purely conventional now (structure view inherits the order of the documents.)
	// There is no technical necessity to align the order of editors and documents. We could drop
	// this behavior in the future
	QList<LatexDocument *> docs;
	foreach (const LatexEditorView *edView, editors->editors()) {
		docs.append(edView->getDocument());
	}
	documents.reorder(docs);
}

void Texstudio::focusEditor()
{
	raise();
	activateWindow();
	if (currentEditorView())
		currentEditorView()->setFocus();
}

void Texstudio::focusViewer()
{
#ifndef NO_POPPLER_PREVIEW
	QList<PDFDocument *> viewers = PDFDocument::documentList();
	if (viewers.isEmpty()) return;

	if (viewers.count() > 1 && currentEditorView()) {
		// try: PDF for current file
		QFileInfo currentFile = currentEditorView()->getDocument()->getFileInfo();
		foreach (PDFDocument *viewer, viewers) {
			if (viewer->getMasterFile() == currentFile) {
				viewer->focus();
				return;
			}
		}
		// try: PDF for master file
		LatexDocument *rootDoc = documents.getRootDocumentForDoc(nullptr);
		if (rootDoc) {
			QFileInfo masterFile = rootDoc->getFileInfo();
			foreach (PDFDocument *viewer, viewers) {
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

void Texstudio::viewCloseElement()
{
	if (fileSelector) {
		fileSelector.data()->deleteLater();
		return;
	}
	if (unicodeInsertionDialog) {
		unicodeInsertionDialog->close();
		return;
	}
	if (completer && completer->isVisible() && completer->close()) {
		return;
	}
    if (currentEditorView() && currentEditorView()->closeElement())
        return;
    if (getManagedAction("main/tools/stopcompile")->isEnabled()) {
        getManagedAction("main/tools/stopcompile")->trigger();
        return;
    }

#ifndef NO_POPPLER_PREVIEW
	// close element in focussed viewer
	QWidget *w = QApplication::focusWidget();
	while (w && !qobject_cast<PDFDocument *>(w))
		w = w->parentWidget();

	if (qobject_cast<PDFDocument *>(w)) {
		PDFDocument *focusedPdf = qobject_cast<PDFDocument *>(w);
		if (focusedPdf->embeddedMode) {
			bool pdfClosed = focusedPdf->closeElement();
			if (pdfClosed) {
				focusEditor();
			} else {
				focusedPdf->widget()->setFocus();
			}
			return;
		}

	}
#endif

	if (textAnalysisDlg) {
		textAnalysisDlg->close();
		return;
	}
	if (outputView->isVisible() && configManager.useEscForClosingLog) {
		outputView->hide();
		return;
	}
#ifndef NO_POPPLER_PREVIEW
	if (configManager.useEscForClosingEmbeddedViewer) {
		foreach (PDFDocument *doc, PDFDocument::documentList()) {
			if (doc->embeddedMode) {
				doc->close();
				return;
			}
		}
	}
#endif
	if (windowState() == Qt::WindowFullScreen && configManager.useEscForClosingFullscreen) {
		stateFullScreen = saveState(1);
		setWindowState(Qt::WindowNoState);
		restoreState(windowstate, 0);
		fullscreenModeAction->setChecked(false);
		return;
	}

	// easter egg
	QTime ct = QTime::currentTime();
	if (ct.second() % 5 != 0) return;
	for (int i = 2; i < 63; i++) if (ct.minute() != i && ct.minute() % i  == 0) return;
	QDate cd = QDate::currentDate();
	const char * mode = "";
	if (cd.month() == 12 && cd.day() >= 20) mode = "-santa";
	else if ( (cd.month() == 10 && cd.day() >= 30) || (cd.month() == 11 && cd.day() == 1)) mode = "-witch";
    else if ( (cd.month() == 3 && cd.day() >= 22) || (cd.month() == 4 && cd.day() <= 25)) mode = "-easter";
	UtilsUi::txsInformation(QString("<html><head></head><body><img src=':/images/egg%1.png'></body></html>").arg(mode));
}

void Texstudio::setFullScreenMode()
{
	if (!fullscreenModeAction->isChecked()) {
		stateFullScreen = saveState(1);
        if(tobemaximized){
            showMaximized();
        }else{
            showNormal();
        }
		restoreState(windowstate, 0);
	} else {
		windowstate = saveState(0);
        tobemaximized=isMaximized();
		showFullScreen();
		restoreState(stateFullScreen, 1);
	}
}

void Texstudio::viewSetHighlighting(QAction *act)
{
	if (!currentEditor()) return;
	if (!m_languages->setLanguageFromName(currentEditor(), act->data().toString())) return;
	currentEditorView()->clearOverlays();
	configManager.recentFileHighlightLanguage.insert(getCurrentFileName(), act->data().toString());
	if (configManager.recentFileHighlightLanguage.size() > configManager.recentFilesList.size()) {
		QMap<QString, QString> recentFileHighlightLanguageNew;
		foreach (QString fn, configManager.recentFilesList)
			if (configManager.recentFileHighlightLanguage.contains(fn))
				recentFileHighlightLanguageNew.insert(fn, configManager.recentFileHighlightLanguage.value(fn));
		configManager.recentFileHighlightLanguage = recentFileHighlightLanguageNew;
	}
	// TODO: Check if reCheckSyntax is really necessary. Setting the language emits (among others) contentsChange(0, lines)
	currentEditorView()->document->reCheckSyntax();
}

void Texstudio::showHighlightingMenu()
{
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

void Texstudio::viewCollapseBlock()
{
	if (!currentEditorView()) return;
	currentEditorView()->foldBlockAt(false, currentEditorView()->editor->cursor().lineNumber());
}

void Texstudio::viewExpandBlock()
{
	if (!currentEditorView()) return;
	currentEditorView()->foldBlockAt(true, currentEditorView()->editor->cursor().lineNumber());
}

void Texstudio::pdfClosed()
{
#ifndef NO_POPPLER_PREVIEW
	PDFDocument *from = qobject_cast<PDFDocument *>(sender());
	if (from) {
		if (from->embeddedMode) {
			shrinkEmbeddedPDFViewer(true);
			QList<int> sz = mainHSplitter->sizes(); // set widths to 50%, eventually restore user setting
			int sum = 0;
			int last = 0;
			foreach (int i, sz) {
				sum += i;
				last = i;
			}
			if (sum > 0)
				pdfSplitterRel = 1.0 * last / sum;

		}
	}
#endif
}


#ifndef NO_POPPLER_PREVIEW
QObject *Texstudio::newPdfPreviewer(bool embedded)
{
	PDFDocument *pdfviewerWindow = new PDFDocument(configManager.pdfDocumentConfig, embedded);
    pdfviewerWindow->setToolbarIconSize(pdfviewerWindow->embeddedMode ? configManager.guiPDFToolbarIconSize : configManager.guiToolbarIconSize);
	if (embedded) {
		mainHSplitter->addWidget(pdfviewerWindow);
		QList<int> sz = mainHSplitter->sizes(); // set widths to 50%, eventually restore user setting
		int sum = 0;
		foreach (int i, sz) {
			sum += i;
		}
		sz.clear();
		if (pdfSplitterRel < 0.1 || pdfSplitterRel > 0.9) //sanity check
			pdfSplitterRel = 0.5;
		sz << sum - qRound(pdfSplitterRel * sum);
		sz << qRound(pdfSplitterRel * sum);
		mainHSplitter->setSizes(sz);
	}
	connect(pdfviewerWindow, SIGNAL(triggeredAbout()), SLOT(helpAbout()));
	connect(pdfviewerWindow, SIGNAL(triggeredEnlarge()), SLOT(enlargeEmbeddedPDFViewer()));
	connect(pdfviewerWindow, SIGNAL(triggeredShrink()), SLOT(shrinkEmbeddedPDFViewer()));
	connect(pdfviewerWindow, SIGNAL(triggeredManual()), SLOT(userManualHelp()));
	connect(pdfviewerWindow, SIGNAL(documentClosed()), SLOT(pdfClosed()));
	connect(pdfviewerWindow, SIGNAL(triggeredQuit()), SLOT(fileExit()));
	connect(pdfviewerWindow, SIGNAL(triggeredConfigure()), SLOT(generalOptions()));
    connect(pdfviewerWindow, SIGNAL(syncSource(const QString&,int,bool,QString)), SLOT(syncFromViewer(const QString&,int,bool,QString)));
	connect(pdfviewerWindow, SIGNAL(focusEditor()), SLOT(focusEditor()));
    connect(pdfviewerWindow, SIGNAL(runCommand(const QString&,const QFileInfo&,const QFileInfo&,int)), &buildManager, SLOT(runCommand(const QString&,const QFileInfo&,const QFileInfo&,int)));
	connect(pdfviewerWindow, SIGNAL(triggeredClone()), SLOT(newPdfPreviewer()));

	PDFDocument *from = qobject_cast<PDFDocument *>(sender());
	if (from) {
		pdfviewerWindow->loadFile(from->fileName(), from->getMasterFile(), PDFDocument::Raise | PDFDocument::Focus);
		pdfviewerWindow->goToPage(from->widget()->getPageIndex());
	}//load file before enabling sync or it will jump to the first page

	foreach (PDFDocument *doc, PDFDocument::documentList()) {
		if (doc == pdfviewerWindow) continue;
        connect(doc, SIGNAL(syncView(QString,QFileInfo,int)), pdfviewerWindow, SLOT(syncFromView(QString,QFileInfo,int)));
        connect(pdfviewerWindow, SIGNAL(syncView(QString,QFileInfo,int)), doc, SLOT(syncFromView(QString,QFileInfo,int)));
	}
	return pdfviewerWindow;
}
#endif

void Texstudio::masterDocumentChanged(LatexDocument *doc)
{
	Q_UNUSED(doc)
	Q_ASSERT(documents.singleMode() == !documents.masterDocument);
	if (documents.singleMode()) {
		outputView->resetMessagesAndLog();
	} else {
		configManager.addRecentFile(documents.masterDocument->getFileName(), true);
		editors->moveEditor(doc->getEditorView(), Editors::GroupFront);
	}

	updateMasterDocumentCaption();
    updateStructureLocally();
	completerNeedsUpdate();
}

void Texstudio::aboutToDeleteDocument(LatexDocument *doc)
{
	emit infoFileClosed();
	editors->removeEditor(doc->getEditorView());
	for (int i = configManager.completerConfig->userMacros.size() - 1; i >= 0; i--)
		if (configManager.completerConfig->userMacros[i].document == doc)
            configManager.completerConfig->userMacros.removeAt(i);
}

//*********************************
void Texstudio::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list")) event->acceptProposedAction();
}

void Texstudio::dropEvent(QDropEvent *event)
{
	QList<QUrl> uris = event->mimeData()->urls();

	QStringList imageFormats = InsertGraphics::imageFormats();
	saveCurrentCursorToHistory();

	bool alreadyMovedCursor = false;
	for (int i = 0; i < uris.length(); i++) {
		QFileInfo fi = QFileInfo(uris.at(i).toLocalFile());
		if (imageFormats.contains(fi.suffix().toLower()) && currentEditor()) {
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
			quickGraphics(uris.at(i).toLocalFile());
		} else if (fi.suffix() == Session::fileExtension()) {
			loadSession(fi.filePath());
		} else
			load(fi.filePath());
	}
	event->acceptProposedAction();
	raise();
}

void Texstudio::changeEvent(QEvent *e)
{
	switch (e->type()) {
	case QEvent::LanguageChange:
		if (configManager.lastLanguage == configManager.language) return; //don't update if config not changed
		//QMessageBox::information(0,"rt","retranslate",0);
		if (!splashscreen) {
			setupMenus();
			setupDockWidgets();
			updateCaption();
			updateMasterDocumentCaption();
		}
		break;
	default:
		break;
	}
}

bool Texstudio::eventFilter(QObject *obj, QEvent *event)
{
    static const QColor beyondEndColor(255, 170, 0);
    static const QColor inAppendixColor(200, 230, 200);
    static const QColor missingFileColor(Qt::red);

#ifdef Q_OS_WIN
    // workaround for ´+t bug
    if (event->type() == QEvent::ShortcutOverride) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        QString key = keyEvent->text();
        if(keyEvent->modifiers()==Qt::NoModifier && key.length()==1 && (key=="´"||key.at(0).isLetter())){
            event->accept();
            return true;
        }
    }
#endif

    if (event->type() == QEvent::ToolTip) {
        if(obj==structureTreeWidget || obj==topTOCTreeWidget){
            QHelpEvent *helpEvent = dynamic_cast<QHelpEvent *>(event);
            QTreeWidgetItem *item=structureTreeWidget->itemAt(helpEvent->pos());
            if(item){
                StructureEntry *entry = item->data(0,Qt::UserRole).value<StructureEntry *>();
                if(!entry)
                    return false;
                QString text;
                if (!entry->tooltip.isNull()) {
                    text=entry->tooltip;
                }
                if (entry->type == StructureEntry::SE_DOCUMENT_ROOT) {
                    text=QDir::toNativeSeparators(entry->document->getFileName());
                }
                if (entry->type == StructureEntry::SE_SECTION) {

                    QString htmlTitle = entry->title.toHtmlEscaped();

                    htmlTitle.replace(' ', "&nbsp;");  // repleacement: prevent line break
                    QString tooltip("<html><b>" + htmlTitle + "</b>");
                    if (entry->getCachedLineNumber() > -1)
                        tooltip.append("<br><i>" + tr("Line") + QString("</i>: %1").arg(entry->getRealLineNumber() + 1));
                    StructureEntry *se = labelForStructureEntry(entry);
                    if (se)
                        tooltip.append("<br><i>" + tr("Label") + "</i>: " + se->title);
                    if (documents.markStructureElementsBeyondEnd && entry->hasContext(StructureEntry::BeyondEnd)){
                        tooltip.append(QString("<br><font color=\"%1\">%2</font>").arg(beyondEndColor.darker(120).name(), tr("Beyond end of document.")));
                    }else{
                        if (documents.markStructureElementsInAppendix && entry->hasContext(StructureEntry::InAppendix))
                            tooltip.append(QString("<br><font color=\"%1\">%2</font>").arg(inAppendixColor.darker(120).name(), tr("In Appendix.")));
                    }
                    // show preview if file is loaded
                    if(LatexDocument *doc=entry->document){
                        int l=entry->getRealLineNumber();
                        tooltip += doc->exportAsHtml(doc->cursor(qMax(0, l - 2), 0, l + 2), true, true, 60);
                    }
                    tooltip.append("</html>");
                    text=tooltip;
                }
                if (entry->type == StructureEntry::SE_LABEL) {

                    QString htmlTitle = entry->title.toHtmlEscaped();

                    htmlTitle.replace(' ', "&nbsp;");  // repleacement: prevent line break
                    QString tooltip("<html><b>" + htmlTitle + "</b>");
                    if (entry->getCachedLineNumber() > -1)
                        tooltip.append("<br><i>" + tr("Line") + QString("</i>: %1").arg(entry->getRealLineNumber() + 1));
                    if (documents.markStructureElementsBeyondEnd && entry->hasContext(StructureEntry::BeyondEnd))
                        tooltip.append(QString("<br><font color=\"%1\">%2</font>").arg(beyondEndColor.darker(120).name(), tr("Beyond end of document.")));
                    if (documents.markStructureElementsInAppendix && entry->hasContext(StructureEntry::InAppendix))
                        tooltip.append(QString("<br><font color=\"%1\">%2</font>").arg(inAppendixColor.darker(120).name(), tr("In Appendix.")));
                    // show preview if file is loaded
                    if(LatexDocument *doc=entry->document){
                        int l=entry->getRealLineNumber();
                        tooltip += doc->exportAsHtml(doc->cursor(qMax(0, l - 2), 0, l + 2), true, true, 60);
                    }
                    tooltip.append("</html>");
                    text=tooltip;
                }
                if (entry->type == StructureEntry::SE_INCLUDE) {

                    QString htmlTitle = entry->title.toHtmlEscaped();

                    htmlTitle.replace(' ', "&nbsp;").replace('-', "&#8209;");  // repleacement: prevent line break
                    QString tooltip("<html><b>" + htmlTitle + "</b>");
                    if (entry->getCachedLineNumber() > -1)
                        tooltip.append("<br><i>" + tr("Line") + QString("</i>: %1").arg(entry->getRealLineNumber() + 1));
                    if (!entry->valid){
                        tooltip.append(QString("<br><font color=\"%1\">%2</font>").arg(missingFileColor.name(), tr("File not found.")));
                    }else{
                        // show preview if file is loaded
                        if(LatexDocument *doc=entry->document){
                            QString fileName=entry->title;
                            fileName=doc->getAbsoluteFilePath(fileName,".tex");
                            LatexDocument *incDoc = documents.findDocument(fileName);
                            if(incDoc){
                                tooltip += incDoc->exportAsHtml(incDoc->cursor(0, 0,qMin(5,incDoc->lines()-1)), true, true, 60);
                            }
                        }
                    }
                    text=tooltip;
                }
                if (text.isEmpty() && entry->getCachedLineNumber() > -1)
                    text=entry->title + QString(tr(" (Line %1)").arg(entry->getRealLineNumber() + 1));
                if(!text.isEmpty()){
                    QToolTip::showText(helpEvent->globalPos(),text);
                    event->accept();
                    return true;
                }
            }
        }


    }
    return false;
}

typedef QPair<int, int> PairIntInt;

void Texstudio::updateCompleter(LatexEditorView *edView)
{
    CodeSnippetList words;

    if(mCompleterCommandsNeedsUpdate){
        mCompleterWords.clear();
    }

    if (configManager.parseBibTeX) documents.updateBibFiles();

    if (!edView)
        edView = currentEditorView();

    QList<LatexDocument *> docs;
    LatexParser ltxCommands = LatexParser::getInstance();
    LatexCompleterConfig *config = completer->getConfig();

    QStringList loadedFiles; // keep track of loaded files to avoid duplicate loading
    if (edView && edView->document) {
        // determine from which docs data needs to be collected
        docs = edView->document->getListOfDocs();

        // collect user commands and references
        foreach (LatexDocument *doc, docs) {
            QList<CodeSnippet> userList=doc->userCommandList();
            if(config){
                CodeSnippetList::iterator it;
                for(it=userList.begin();it!=userList.end();++it){
                    QList<QPair<int, int> >res = config->usage.values(it->index);
                    foreach (const PairIntInt &elem, res) {
                        if (elem.first == it->snippetLength) {
                            (*it).usageCount = elem.second;
                            break;
                        }
                    }
                }
            }
            words.unite(userList);
            if(mCompleterCommandsNeedsUpdate){
                mCompleterWords.unite(doc->additionalCommandsList(loadedFiles));
                ltxCommands.append(doc->ltxCommands);
            }
        }
        mCompleterWords.unite(words);
    }
    // collect user commands and references
    std::set<QString> collected_labels;
    foreach (const LatexDocument *doc, docs) {
        if(doc->labelItems().isEmpty())
            continue;
        QStringList lst=doc->labelItems();
        collected_labels.insert(lst.cbegin(),lst.cend());
    }

    if (configManager.parseBibTeX) {
        std::set<QString> bibIds;

        QStringList collected_mentionedBibTeXFiles;
        foreach (const LatexDocument *doc, docs) {
            collected_mentionedBibTeXFiles << doc->listOfMentionedBibTeXFiles();
        }

        for (int i = 0; i < collected_mentionedBibTeXFiles.count(); i++) {
            if (!documents.bibTeXFiles.contains(collected_mentionedBibTeXFiles[i])) {
                qDebug("BibTeX-File %s not loaded", collected_mentionedBibTeXFiles[i].toLatin1().constData());
                continue; //wtf?s
            }
            BibTeXFileInfo &bibTex = documents.bibTeXFiles[collected_mentionedBibTeXFiles[i]];

            // add citation to completer for direct citation completion
            bibIds.insert(bibTex.ids.cbegin(),bibTex.ids.cend());
        }
        //handle bibitem definitions
        foreach (const LatexDocument *doc, docs) {
            QStringList ids=doc->bibItems();
            bibIds.insert(ids.cbegin(),ids.cend());
        }
        completer->setAdditionalWords(bibIds, CT_CITATIONS);
    }

    completer->setAdditionalWords(collected_labels, CT_LABELS);

    completer->setAdditionalWords(mCompleterWords, CT_COMMANDS);
    if(mCompleterCommandsNeedsUpdate){
        // add keyval completion, add special lists
        foreach (const QString &elem, ltxCommands.possibleCommands.keys()) {
            if (elem.startsWith("key%")) {
                QString name = elem.mid(4);
                if (name.endsWith("#c"))
                    name.chop(2);
                if (!name.isEmpty()) {
                    completer->setKeyValWords(name, ltxCommands.possibleCommands[elem]);
                }
            }
            if (elem.startsWith("%") && latexParser.mapSpecialArgs.values().contains(elem)) {
                completer->setKeyValWords(elem, ltxCommands.possibleCommands[elem]);
            }
        }
        // add context completion
        if (config) {
            foreach (const QString &elem, config->specialCompletionKeys) {
                completer->setContextWords(ltxCommands.possibleCommands[elem], elem);
            }
        }
    }

    if (edView) edView->viewActivated();

    GrammarCheck::staticMetaObject.invokeMethod(grammarCheck, "init", Qt::QueuedConnection, Q_ARG(LatexParser, latexParser), Q_ARG(GrammarCheckerConfig, *configManager.grammarCheckerConfig));

    mCompleterNeedsUpdate = false;
    mCompleterCommandsNeedsUpdate = false;
}

void Texstudio::outputPageChanged(const QString &id)
{
	if (id == outputView->LOG_PAGE && !outputView->getLogWidget()->logPresent()) {
		if (!loadLog())
			return;
		if (hasLatexErrors())
			viewLog();
	}
}

void Texstudio::jumpToSearchResult(QDocument *doc, int lineNumber, const SearchQuery *query)
{
    REQUIRE(qobject_cast<LatexDocument *>(doc));
    if (currentEditor() && currentEditor()->document() == doc && currentEditor()->cursor().lineNumber() == lineNumber) {
        QDocumentCursor c = currentEditor()->cursor();
        int col = c.columnNumber();
        col = query->getNextSearchResultColumn(c.line().text() , col + 1);
        gotoLine(lineNumber, col);
    } else {
        gotoLine(lineNumber, doc->getFileName().size() ? doc->getFileName() : qobject_cast<LatexDocument *>(doc)->getTemporaryFileName());
        int col = query->getNextSearchResultColumn(currentEditor()->document()->line(lineNumber).text(), 0);
        gotoLine(lineNumber, col);
        outputView->showPage(outputView->SEARCH_RESULT_PAGE);
    }
    QDocumentCursor highlight = currentEditor()->cursor();
    highlight.movePosition(query->searchExpression().length(), QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
    currentEditorView()->temporaryHighlight(highlight);
}

void Texstudio::gotoLine(int line, int col, LatexEditorView *edView, QEditor::MoveFlags mflags, bool setFocus)
{
    bool changeCurrentEditor = (edView != currentEditorView());
    if (!edView)
        edView = currentEditorView(); // default

    if (!edView || line < 0) return;

    saveCurrentCursorToHistory();

    if (changeCurrentEditor) {
        if (editors->containsEditor(edView)) {
            editors->setCurrentEditor(edView);
            mflags &= ~QEditor::Animated;
        } else {
            load(edView->getDocument()->getFileName());
        }
    }
    edView->editor->setCursorPosition(line, col, false);
    edView->editor->ensureCursorVisible(mflags);
    if (setFocus) {
        edView->editor->setFocus();
    }
}

bool Texstudio::gotoLine(int line, const QString &fileName)
{
    LatexEditorView *edView = getEditorViewFromFileName(fileName, true);
    QEditor::MoveFlags mflags = QEditor::Navigation;
    if (!edView) {
        if (!load(fileName)) return false;
        mflags &= ~QEditor::Animated;
    }
    gotoLine(line, 0, edView, mflags);
    return true;
}

void Texstudio::gotoLine(LatexDocument *doc, int line, int col)
{
    if (!doc) return;

    LatexEditorView *edView = doc->getEditorView();
    if (edView) {
        gotoLine(line, col, edView);
    }
}

/*!
 * \brief jump to line given by TOC entry (topTOCTreeWidget)
 * \param item
 * \param col
 */
void Texstudio::gotoLine(QTreeWidgetItem *item, int)
{
    StructureEntry *se=item->data(0,Qt::UserRole).value<StructureEntry *>();
    if(!se) return;
    const QList<StructureEntry::Type> lineTypes={StructureEntry::SE_SECTION,StructureEntry::SE_TODO,StructureEntry::SE_LABEL,StructureEntry::SE_MAGICCOMMENT};
    if(lineTypes.contains(se->type)){
        LatexEditorView *edView = se->document->getEditorView();
        if (edView) {
            gotoLine(se->getRealLineNumber(), 0, edView);
        }else{
            // going to hidden doc
            // relevant for hidden master document
            bool unmodified=se->document->isClean();
            openExternalFile(se->document->getFileName(),"tex",se->document);
            if(unmodified)
                se->document->setClean(); // work-around, unclear where that state is reset during load
            LatexEditorView *edView = se->document->getEditorView();
            if (edView) {
                gotoLine(se->getRealLineNumber(), 0, edView);
            }
        }
    }else{
        // unresolved include, go to open file
        if(se->type == StructureEntry::SE_DOCUMENT_ROOT){
            LatexEditorView *edView = se->document->getEditorView();
            if (!edView) return;
            editors->setCurrentEditor(edView);
        }
        if(se->type==StructureEntry::SE_INCLUDE || se->type==StructureEntry::SE_BIBTEX){
            saveCurrentCursorToHistory();
            bool relativeToCurrentDoc=se->hasContext(StructureEntry::Import) || se->document->getStateImportedFile();
            QString defaultExt = se->type == StructureEntry::SE_BIBTEX ? ".bib" : ".tex";
            QString name=se->title;
            name.replace("\\string~",QDir::homePath());
            openExternalFile(name,defaultExt,se->document,relativeToCurrentDoc);
        }
    }
}

void Texstudio::gotoLogEntryEditorOnly(int logEntryNumber)
{
	if (logEntryNumber < 0 || logEntryNumber >= outputView->getLogWidget()->getLogModel()->count()) return;
	LatexLogEntry entry = outputView->getLogWidget()->getLogModel()->at(logEntryNumber);
	QString fileName = entry.file;
	if (!activateEditorForFile(fileName, true))
		if (!load(fileName)) return;
	if (currentEditorView()->logEntryToLine.isEmpty()) {
		updateLogEntriesInEditors();
	}
	if (configManager.showLogMarkersWhenClickingLogEntry) {
		setLogMarksVisible(true);
	}
	//get line
	QDocumentLineHandle *dlh = currentEditorView()->logEntryToLine.value(logEntryNumber, nullptr);
	if (!dlh) return;
	//goto
	gotoLine(currentEditor()->document()->indexOf(dlh));
	QDocumentCursor c = getLogEntryContextCursor(dlh, entry);
	if (c.isValid()) {
		currentEditorView()->editor->setCursor(c, false);
	}
}

/*!
 * Returns a cursor marking the part of the line which the log entry is referring to.
 * This assumes that the cursor was already set to the correct line before calling the function.
 */
QDocumentCursor Texstudio::getLogEntryContextCursor(const QDocumentLineHandle *dlh, const LatexLogEntry &entry)
{
    QRegularExpression rxUndefinedControlSequence("^Undefined\\ control\\ sequence.*(\\\\\\w+)$");
    QRegularExpression rxEnvironmentUndefined("^Environment (\\w+) undefined\\.");
    QRegularExpression rxReferenceMissing("^Reference `(\\w+)' on page (\\d+) undefined");
    QRegularExpression rxCitationMissing("^Citation `(\\w+)' on page (\\d+) undefined");
    QRegularExpressionMatch match;
    if (entry.message.indexOf(rxUndefinedControlSequence,0,&match) == 0) {
        QString cmd = match.captured(1);
		int startCol = dlh->text().indexOf(cmd);
		if (startCol >= 0) {
			QDocumentCursor cursor = currentEditorView()->editor->cursor();
			cursor.selectColumns(startCol, startCol + cmd.length());
			return cursor;
		}
    } else if (entry.message.indexOf(rxEnvironmentUndefined,0,&match) == 0) {
        QString env = match.captured(1);
		int startCol = dlh->text().indexOf("\\begin{" + env + "}");
		if (startCol >= 0) {
			startCol += 7;  // length of \begin{
			QDocumentCursor cursor = currentEditorView()->editor->cursor();
			cursor.selectColumns(startCol, startCol + env.length());
			return cursor;
		}
    } else if (entry.message.indexOf(rxReferenceMissing,0,&match) == 0) {
		int fid = currentEditorView()->document->getFormatId("referenceMissing");
		foreach (const QFormatRange &fmtRange, dlh->getOverlays(fid)) {
            if (dlh->text().mid(fmtRange.offset, fmtRange.length) == match.captured(1)) {
				QDocumentCursor cursor = currentEditorView()->editor->cursor();
				cursor.selectColumns(fmtRange.offset, fmtRange.offset + fmtRange.length);
				return cursor;
			}
		}
    } else if (entry.message.indexOf(rxCitationMissing,0,&match) == 0) {
		int fid = currentEditorView()->document->getFormatId("citationMissing");
		foreach (const QFormatRange &fmtRange, dlh->getOverlays(fid)) {
            if (dlh->text().mid(fmtRange.offset, fmtRange.length) == match.captured(1)) {
				QDocumentCursor cursor = currentEditorView()->editor->cursor();
				cursor.selectColumns(fmtRange.offset, fmtRange.offset + fmtRange.length);
				return cursor;
			}
		}
	} else {
		// error messages that are followed by the context; e.g. Too many }'s. \textit{}}
		QStringList messageStarts = QStringList() << "Too many }'s. " << "Missing $ inserted. ";
		foreach (const QString &messageStart, messageStarts) {
			if (entry.message.startsWith(messageStart)) {
				QString context = entry.message.mid(messageStart.length());
				int startCol = dlh->text().indexOf(context);
				if (startCol >= 0) {
					QDocumentCursor cursor = currentEditorView()->editor->cursor();
					cursor.setColumnNumber(startCol += context.length());
					return cursor;
				}
			}
		}
	}
	return QDocumentCursor();
}

bool Texstudio::gotoLogEntryAt(int newLineNumber)
{
	//goto line
	if (newLineNumber < 0) return false;
	gotoLine(newLineNumber);
	//find error number
	QDocumentLineHandle *lh = currentEditorView()->editor->document()->line(newLineNumber).handle();
	int logEntryNumber = currentEditorView()->lineToLogEntries.value(lh, -1);
	if (logEntryNumber == -1) return false;
	//goto log entry
	outputView->selectLogEntry(logEntryNumber);

    QPointF p = currentEditorView()->editor->mapToGlobal(currentEditorView()->editor->mapFromContents(currentEditorView()->editor->cursor().documentPosition().toPoint()));
	//  p.ry()+=2*currentEditorView()->editor->document()->fontMetrics().lineSpacing();

	REQUIRE_RET(outputView->getLogWidget()->getLogModel(), true);
	QList<int> errors = currentEditorView()->lineToLogEntries.values(lh);
	QString msg = outputView->getLogWidget()->getLogModel()->htmlErrorTable(errors);

    QToolTip::showText(p.toPoint(), msg, nullptr);
	LatexEditorView::hideTooltipWhenLeavingLine = newLineNumber;
	return true;
}

bool Texstudio::gotoMark(bool backward, int id)
{
	if (!currentEditorView()) return false;
	if (backward)
		return gotoLogEntryAt(currentEditorView()->editor->document()->findPreviousMark(id, qMax(0, currentEditorView()->editor->cursor().lineNumber() - 1), 0));
	else
		return gotoLogEntryAt(currentEditorView()->editor->document()->findNextMark(id, currentEditorView()->editor->cursor().lineNumber() + 1));
}

QList<int> Texstudio::findOccurencesApproximate(QString line, const QString &guessedWord)
{
	QList<int> columns;

	// exact match
	columns = indicesOf(line, guessedWord);
	if (columns.isEmpty()) columns = indicesOf(line, guessedWord, Qt::CaseSensitive);

	QString changedWord = guessedWord;
	if (columns.isEmpty()) {
		//search again and ignore useless characters

		QString regex;
		for (int i = 0; i < changedWord.size(); i++)
			if (changedWord[i].category() == QChar::Other_Control || changedWord[i].category() == QChar::Other_Format)
				changedWord[i] = '\1';
#if (QT_VERSION>=QT_VERSION_CHECK(5,14,0))
        foreach (const QString &x, changedWord.split('\1', Qt::SkipEmptyParts)){
            if (regex.isEmpty())
                regex += QRegularExpression::escape(x);
            else
                regex += ".{0,2}" + QRegularExpression::escape(x);
        }
#else
		foreach (const QString &x, changedWord.split('\1', QString::SkipEmptyParts))
			if (regex.isEmpty()) regex += QRegExp::escape(x);
			else regex += ".{0,2}" + QRegExp::escape(x);
#endif
        QRegularExpression rx = QRegularExpression(regex);
		columns = indicesOf(line, rx);
		if (columns.isEmpty()) {
            rx.setPatternOptions(QRegularExpression::NoPatternOption);
			columns = indicesOf(line, rx);
		}
	}
	if (columns.isEmpty()) {
		//search again and allow additional whitespace
		QString regex;
#if (QT_VERSION>=QT_VERSION_CHECK(5,14,0))
        foreach (const QString &x , changedWord.split(" ", Qt::SkipEmptyParts))
            if (regex.isEmpty()) regex = QRegExp::escape(x);
            else regex += "\\s+" + QRegExp::escape(x);
#else
		foreach (const QString &x , changedWord.split(" ", QString::SkipEmptyParts))
			if (regex.isEmpty()) regex = QRegExp::escape(x);
			else regex += "\\s+" + QRegExp::escape(x);
#endif
        QRegularExpression rx = QRegularExpression(regex);
		columns = indicesOf(line, rx);
		if (columns.isEmpty()) {
            rx.setPatternOptions(QRegularExpression::NoPatternOption);
			columns = indicesOf(line, rx);
		}
	}
	if (columns.isEmpty()) {
		int bestMatch = -1, bestScore = 0;
		for (int i = 0; i < line.size() - guessedWord.size(); i++) {
			int score = 0;
			for (int c = i, s = 0; c < line.size() && s < guessedWord.size(); c++, s++) {
				QChar C = line[c], S = guessedWord[s];
				if (C == S) score += 5; //perfect match
				else if (C.toLower() == S.toLower()) score += 2; //ok match
				else if (C.isSpace()) s--; //skip spaces
				else if (S.isSpace()) c--; //skip spaces
				else if (S.category() == QChar::Other_Control || S.category() == QChar::Other_Format) {
					for (s++; s < guessedWord.size() && (guessedWord[s].category() == QChar::Other_Control || guessedWord[s].category() == QChar::Other_Format); s++); //skip nonsense
					if (s >= guessedWord.size()) continue;
					if (guessedWord[s] == C) {
						score += 5;
						continue;
					}
					if (c + 1 < line.size() && guessedWord[s] == line[c + 1]) {
						score += 5;
						c++;
						continue;
					}
					//also skip next character after that nonsense
				}
			}
			if (score > bestScore){
			    bestScore = score;
			    bestMatch = i;
			}
		}
		if (bestScore > guessedWord.size() * 5 / 3) columns.append(bestMatch); //accept if 0.33 similarity
	}
	return columns;
}

void Texstudio::syncFromViewer(const QString &fileName, int line, bool activate, const QString &guessedWord)
{
	if (!activateEditorForFile(fileName, true, activate)) {
		QWidget *w = focusWidget();
		bool success = load(fileName);
		if (!activate)
			w->setFocus();  // restore focus
		if (!success) return;
	}
	shrinkEmbeddedPDFViewer();

	QDocumentLine l = currentEditorView()->document->lineFromLineSnapshot(line);
	if (l.isValid()) {
		int originalLineNumber = currentEditorView()->document->indexOf(l, line);
		if (originalLineNumber >= 0) line = originalLineNumber;
	}

	gotoLine(line, 0, nullptr, QEditor::Navigation, activate);
	Q_ASSERT(currentEditor());

	// guessedWord may appear multiple times -> we highlight them all
	QList<int> columns = findOccurencesApproximate(currentEditor()->cursor().line().text(), guessedWord);

	if (columns.isEmpty() || guessedWord.isEmpty()) {
		// highlight complete line
		QDocumentCursor highlight(currentEditor()->document(), line, 0);
		highlight.movePosition(1, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
		currentEditorView()->temporaryHighlight(highlight);
	} else {
		// highlight all found positions
		QDocumentCursor highlight(currentEditor()->document(), line, 0);
		foreach (int col, columns) {
			int cursorCol = col + guessedWord.length() / 2;
			highlight.setColumnNumber(cursorCol);
			highlight.movePosition(1, QDocumentCursor::StartOfWord, QDocumentCursor::MoveAnchor);
			highlight.movePosition(1, QDocumentCursor::EndOfWord, QDocumentCursor::KeepAnchor);
			if (!highlight.hasSelection()) { // fallback, if we are not at a word
				highlight.setColumnNumber(cursorCol);
				highlight.movePosition(1, QDocumentCursor::PreviousCharacter, QDocumentCursor::MoveAnchor);
				highlight.movePosition(1, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
			}
			currentEditor()->setCursorPosition(currentEditor()->cursor().lineNumber(), cursorCol, false);
			currentEditor()->ensureCursorVisible(QEditor::KeepSurrounding | QEditor::ExpandFold);
			currentEditorView()->temporaryHighlight(highlight);
		}
	}

	if (activate) {
		raise();
		show();
		activateWindow();
		if (isMinimized()) showNormal();
	}

}

void Texstudio::goBack()
{
	QDocumentCursor currentCur;
	if (currentEditorView()) currentCur = currentEditorView()->editor->cursor();
	setGlobalCursor(cursorHistory->back(currentCur));
}

void Texstudio::goForward()
{
	QDocumentCursor currentCur;
	if (currentEditorView()) currentCur = currentEditorView()->editor->cursor();
	setGlobalCursor(cursorHistory->forward(currentCur));
}

void Texstudio::setGlobalCursor(const QDocumentCursor &c)
{
	if (c.isValid()) {
		LatexDocument *doc = qobject_cast<LatexDocument *>(c.document());
		if (doc && doc->getEditorView()) {
			LatexEditorView *edView = doc->getEditorView();
			QEditor::MoveFlags mflags = QEditor::KeepSurrounding | QEditor::ExpandFold;
			if (edView == currentEditorView()) mflags |= QEditor::Animated;
			editors->setCurrentEditor(edView);
			edView->editor->setFocus();
			edView->editor->setCursor(c, false);
			edView->editor->ensureCursorVisible(mflags);
		}
	}
}

void Texstudio::fuzzBackForward()
{
#ifdef NOT_DEFINED__FUZZER_NEEDED_ONLY_FOR_DEBUGGING_RANDOM_CRASH_OF_CURSOR_HISTORY
	int rep = random() % (1 + cursorHistory->count());
	for (int j = 0; j < rep; j++) goBack();
	rep = random() % (1 + cursorHistory->count());
	for (int j = 0; j < rep; j++) goForward();
#endif
}

void Texstudio::setBuildButtonsDisabled(bool c)
{
	getManagedAction("main/tools/stopcompile")->setEnabled(c);
	getManagedAction("main/tools/quickbuild")->setEnabled(!c);
	getManagedAction("main/tools/compile")->setEnabled(!c);
#ifndef NO_POPPLER_PREVIEW
	foreach (PDFDocument *viewer, PDFDocument::documentList())
		viewer->setActionTypesetEnabled(!c);
#endif
}

void Texstudio::fuzzCursorHistory()
{
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
			int c = random() % (currentEditor()->document()->line(l).length() + 100);
			currentEditor()->setCursor(currentEditor()->document()->cursor(l, c, random() % 100, random() % 100));
			saveCurrentCursorToHistory();
			fuzzBackForward();
		}
	}
#endif
}

void Texstudio::saveCurrentCursorToHistory()
{
	saveEditorCursorToHistory(currentEditorView());
}

void Texstudio::saveEditorCursorToHistory(LatexEditorView *edView)
{
	if (!edView) return;
	cursorHistory->insertPos(edView->editor->cursor());
}

void Texstudio::previewLatex()
{
	if (!currentEditorView()) return;
    LatexEditorView *edView=currentEditorView();
    QEditor *editor=edView->editor;

	// get selection
    QDocumentCursor c = editor->cursor();

	QDocumentCursor previewc;
	if (c.hasSelection()) {
		previewc = c; //X o riginalText = c.selectedText();
	} else {
        if (edView->getLineRowforContexMenu()>=0) {
            c.moveTo(edView->getLineRowforContexMenu(), edView->getLineColforContexMenu());
        }
		// math context
		QSet<int> mathFormats = QSet<int>() << m_formats->id("numbers") << m_formats->id("math-keyword") << m_formats->id("align-ampersand");
		QSet<int> lineEndFormats = QSet<int>() << m_formats->id("keyword") /* newline char */ << m_formats->id("comment");
		mathFormats.remove(0); // keep only valid entries in list
		lineEndFormats.remove(0);
        previewc = edView->findFormatsBegin(c, mathFormats, lineEndFormats);
        previewc = edView->parenthizedTextSelection(previewc);
	}
	if (!previewc.hasSelection()) {
		// special handling for cusor in the middle of \[ or \]
		if (c.previousChar() == '\\' && (c.nextChar() == '[' || c.nextChar() == ']')) {
			c.movePosition(1, QDocumentCursor::PreviousCharacter);
            previewc = edView->parenthizedTextSelection(c);
		}
	}
        if (!previewc.hasSelection()) {
            // in environment delimiter (\begin{env} or \end{env})
            QString command;
            Token tk = Parsing::getTokenAtCol(c.line().handle(), c.columnNumber());
            if (tk.type != Token::none)
                command = tk.getText();
            if (tk.type == Token::env || tk.type == Token::beginEnv ) {
                TokenList tl = c.line().handle()->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
                tk=Parsing::getCommandTokenFromToken(tl,tk);
                c.setColumnNumber(tk.start);
                previewc = edView->parenthizedTextSelection(c);
            }
            if (tk.type == Token::command && (command == "\\begin" || command == "\\end")) {
                c.setColumnNumber(tk.start);
                previewc = edView->parenthizedTextSelection(c);
            }
        }
        if (!previewc.hasSelection()) {
            // already at parenthesis
            previewc = edView->parenthizedTextSelection(editor->cursor());
        }
	if (!previewc.hasSelection()) return;

	showPreview(previewc, true);

}

void Texstudio::previewAvailable(const QString &imageFile, const PreviewSource &source)
{
	QPixmap pixmap;
    qreal devPixelRatio = 1.0;

    devPixelRatio = devicePixelRatio();

	double scale = configManager.segmentPreviewScalePercent / 100.;
	double min = 0.2;
	double max = 100;
	scale = qMax(min, qMin(max, scale)) * devPixelRatio;
	bool fromPDF = false;

#ifndef NO_POPPLER_PREVIEW
	fromPDF = imageFile.toLower().endsWith(".pdf");
	if (fromPDF) {
		// special treatment for pdf files (embedded pdf mode)
		if (configManager.previewMode == ConfigManager::PM_EMBEDDED) {
			runInternalCommand("txs:///view-pdf-internal", QFileInfo(imageFile), "--embedded");
			if (currentEditorView())
				currentEditorView()->setFocus();
			return;
		} else {
            std::unique_ptr<Poppler::Document> document(Poppler::Document::load(imageFile));
            if (!document)
                return;
            std::unique_ptr<Poppler::Page> page(document->page(0));
            if (!page)
                return;
			document->setRenderHint(Poppler::Document::Antialiasing);
			document->setRenderHint(Poppler::Document::TextAntialiasing);
			double c = 1.25;  // empirical correction factor because pdf images are smaller than dvipng images. TODO: is logicalDpiX correct?
            pixmap = QPixmap::fromImage(page->renderToImage(qRound(scale*logicalDpiX() * c), qRound(scale*logicalDpiY() * c)));
            previewCache.insert(source.text,pixmap);
		}
	}
#endif
	if (!fromPDF) {
        if(imageFile.isEmpty()){
            // cached
            previewCache.find(source.text,&pixmap);
            fromPDF=true;
        }else{
            pixmap.load(imageFile);
            previewCache.insert(source.text,pixmap);
            if (scale < 0.99 || 1.01 < scale) {
                // TODO: this does scale the pixmaps, but it would be better to render higher resolution images directly in the compilation process.
                pixmap = pixmap.scaledToWidth(qRound(scale*pixmap.width()), Qt::SmoothTransformation);
            }
        }
	}

    if (devPixelRatio > 1.01 || devPixelRatio<0.99) {
		pixmap.setDevicePixelRatio(devPixelRatio);
	}

	if (configManager.previewMode == ConfigManager::PM_BOTH ||
	        configManager.previewMode == ConfigManager::PM_PANEL ||
	        (configManager.previewMode == ConfigManager::PM_TOOLTIP_AS_FALLBACK && outputView->isPreviewPanelVisible())) {
		outputView->showPage(outputView->PREVIEW_PAGE);
		outputView->previewLatex(pixmap);
	}
	if (configManager.previewMode == ConfigManager::PM_BOTH ||
	        configManager.previewMode == ConfigManager::PM_TOOLTIP ||
            (source.atCursor && configManager.previewMode == ConfigManager::PM_INLINE)  || // respect preview setting, except for INLINE
	        (configManager.previewMode == ConfigManager::PM_TOOLTIP_AS_FALLBACK && !outputView->isPreviewPanelVisible()) ||
            (source.fromLine < 0 && !source.atCursor)) { // completer preview
        QPointF p;
		if (source.atCursor)
			p = currentEditorView()->getHoverPosistion();
		else
            p = currentEditorView()->editor->mapToGlobal(currentEditorView()->editor->mapFromContents(currentEditorView()->editor->cursor().documentPosition().toPoint()));

		QRect screen = QGuiApplication::primaryScreen()->geometry();
		int w = pixmap.width();
		if (w > screen.width()) w = screen.width() - 2;
        int w_calculated=qRound(1.0*w / devPixelRatio); //pixmap shown with reduced width to be pixel perfect again
		if (!fromPDF) {
                QToolTip::showText(p.toPoint(), QString("<img src=\"" + imageFile + "\" width=%1 />").arg(w_calculated), nullptr);
		} else {
			QString text;

            text = getImageAsText(pixmap, w_calculated);

			if (completerPreview) {
				completerPreview = false;
				completer->showTooltip(text);
			} else {
                    QToolTip::showText(p.toPoint(), text, nullptr);
			}
		}
		LatexEditorView::hideTooltipWhenLeavingLine = currentEditorView()->editor->cursor().lineNumber();
	}
	if (configManager.previewMode == ConfigManager::PM_INLINE && source.fromLine >= 0) {
		QDocument *doc = currentEditor()->document();
		doc->setForceLineWrapCalculation(true);
		int toLine = qBound(0, source.toLine, doc->lines() - 1);
		for (int l = source.fromLine; l <= toLine; l++ )
			if (doc->line(l).getCookie(QDocumentLine::PICTURE_COOKIE).isValid()) {
				doc->line(l).removeCookie(QDocumentLine::PICTURE_COOKIE);
				doc->line(l).removeCookie(QDocumentLine::PICTURE_COOKIE_DRAWING_POS);
				doc->line(l).setFlag(QDocumentLine::LayoutDirty);
				if (l != toLine) //must not adjust line toLine here, or will recalculate the document height without preview and scroll away if the preview is very height
					doc->adjustWidth(l);
			}
		doc->line(toLine).setCookie(QDocumentLine::PICTURE_COOKIE, QVariant::fromValue<QPixmap>(pixmap));
		doc->line(toLine).setFlag(QDocumentLine::LayoutDirty);
		doc->adjustWidth(toLine);
	}
}

void Texstudio::clearPreview()
{
	QEditor *edit = currentEditor();
	if (!edit) return;

	int startLine = 0;
	int endLine = 0;

    LatexEditorView *edView=currentEditorView();
    int row=edView->getLineRowforContexMenu();
    int col=edView->getLineColforContexMenu();
    if(row>=0 && col<0){
        // context menu position takes precedence when click directly on preview image
        startLine = row;
        endLine = startLine;
    } else if (edit->cursor().hasSelection()) {
		startLine = edit->cursor().selectionStart().lineNumber();
		endLine = edit->cursor().selectionEnd().lineNumber();
	} else if (row>=0) {
        // inline preview context menu supplies the calling point as row/col in LatexEditorView member variable
        // That variable is only >-1 when context menu is active
        startLine = row;
		endLine = startLine;
	} else {
		startLine = edit->cursor().lineNumber();
		endLine = startLine;
	}

        for (int i = startLine; i <= endLine; i++) {
            edit->document()->line(i).removeCookie(QDocumentLine::PICTURE_COOKIE);
            edit->document()->line(i).removeCookie(QDocumentLine::PICTURE_COOKIE_DRAWING_POS);
            edit->document()->adjustWidth(i);
            for (int j = currentEditorView()->autoPreviewCursor.size() - 1; j >= 0; j--)
                if (currentEditorView()->autoPreviewCursor[j].selectionStart().lineNumber() <= i &&
                        currentEditorView()->autoPreviewCursor[j].selectionEnd().lineNumber() >= i) {
                    // remove cookies from last previewed line
                    int el=currentEditorView()->autoPreviewCursor[j].selectionEnd().lineNumber();
                    edit->document()->line(el).removeCookie(QDocumentLine::PICTURE_COOKIE);
                    edit->document()->line(el).removeCookie(QDocumentLine::PICTURE_COOKIE_DRAWING_POS);
                    // remove mark
                    int sid = edit->document()->getFormatId("previewSelection");
                    if (!sid) return;
                    updateEmphasizedRegion(currentEditorView()->autoPreviewCursor[j], -sid);
                    currentEditorView()->autoPreviewCursor.removeAt(j);
                    if(el>endLine){
                        edit->document()->adjustWidth(el); // text line with preview picture needs to be resized
                    }
                }

        }
}

void Texstudio::showImgPreview(const QString &fname)
{
	completerPreview = (sender() == completer); // completer needs signal as answer
	QString imageName = fname;
	QFileInfo fi(fname);
	QString suffix;
	QStringList suffixList;
	suffixList << "jpg" << "jpeg" << "png" << "pdf";
	if (fi.exists()) {
		if (!suffixList.contains(fi.suffix()))
			return;
		suffix = fi.suffix();
	}

	if (suffix.isEmpty()) {
		foreach (QString elem, suffixList) {
			imageName = fname + elem;
			fi.setFile(imageName);
			if (fi.exists()) {
				suffix = elem;
				break;
			}
		}
	}

	suffixList.clear();
	suffixList << "jpg" << "jpeg" << "png";
	if (suffixList.contains(suffix)) {
		QPoint p;
		//if(previewEquation)
		p = currentEditorView()->getHoverPosistion();
		//else
		//    p=currentEditorView()->editor->mapToGlobal(currentEditorView()->editor->mapFromContents(currentEditorView()->editor->cursor().documentPosition()));
		QRect screen = QGuiApplication::primaryScreen()->geometry();
		QPixmap img(imageName);
		int w = qMin(img.width(), configManager.editorConfig->maxImageTooltipWidth);
		w = qMin(w, screen.width() - 8);
		QString text = QString("<img src=\"" + imageName + "\" width=%1 />").arg(w);
		if (completerPreview) {
			completerPreview = false;
			emit imgPreview(text);
		} else {
		        QToolTip::showText(p, text, nullptr);
			LatexEditorView::hideTooltipWhenLeavingLine = currentEditorView()->editor->cursor().lineNumber();
		}
	}
#ifndef NO_POPPLER_PREVIEW
	if (suffix == "pdf") {
		//render pdf preview
		PDFRenderManager *renderManager = new PDFRenderManager(this, 1);
		PDFRenderManager::Error error = PDFRenderManager::NoError;
		QSharedPointer<Poppler::Document> document = renderManager->loadDocument(imageName, error, "");
		if (error == PDFRenderManager::NoError) {
			renderManager->renderToImage(0, this, "showImgPreviewFinished", 20, 20, -1, -1, -1, -1, false, true);
		} else {
			delete renderManager;
		}
	}
#endif
}

void Texstudio::showImgPreviewFinished(const QPixmap &pm, int page)
{
	if (!currentEditorView()) return;
	Q_UNUSED(page)
	QPoint p;
	//if(previewEquation)
	p = currentEditorView()->getHoverPosistion();
	//else
	//    p=currentEditorView()->editor->mapToGlobal(currentEditorView()->editor->mapFromContents(currentEditorView()->editor->cursor().documentPosition()));
	QRect screen = QGuiApplication::primaryScreen()->geometry();
	int w = pm.width();
	if (w > screen.width()) w = screen.width() - 2;
	QString text;
	text = getImageAsText(pm, w);

	if (completerPreview) {
		emit imgPreview(text);
	} else {
	        QToolTip::showText(p, text, nullptr);
		LatexEditorView::hideTooltipWhenLeavingLine = currentEditorView()->editor->cursor().lineNumber();
	}
#ifndef NO_POPPLER_PREVIEW
	PDFRenderManager *renderManager = qobject_cast<PDFRenderManager *>(sender());
	delete renderManager;
#endif
}

void Texstudio::showPreview(const QString &text)
{
	completerPreview = (sender() == completer); // completer needs signal as answer
	LatexEditorView *edView = getEditorViewFromFileName(documents.getCompileFileName()); //todo: temporary compi
	if (!edView)
		edView = currentEditorView();
	if (!edView) return;
	int m_endingLine = edView->editor->document()->findLineContaining("\\begin{document}", 0, Qt::CaseSensitive);
	if (m_endingLine < 0) return; // can't create header
    // use cache if available
    QPixmap pm;
    if(previewCache.find(text,&pm)){
        previewAvailable("",PreviewSource(text, -1, -1, true));
        return;
    }
	QStringList header;
	for (int l = 0; l < m_endingLine; l++)
		header << edView->editor->document()->line(l).text();
	if (buildManager.dvi2pngMode == BuildManager::DPM_EMBEDDED_PDF || buildManager.dvi2pngMode == BuildManager::DPM_LUA_EMBEDDED_PDF) {
		header << "\\usepackage[active,tightpage]{preview}"
		       << "\\usepackage{varwidth}"
		       << "\\AtBeginDocument{\\begin{preview}\\begin{varwidth}{\\linewidth}}"
		       << "\\AtEndDocument{\\end{varwidth}\\end{preview}}";
	}
	header << "\\pagestyle{empty}";// << "\\begin{document}";
	buildManager.preview(header.join("\n"), PreviewSource(text, -1, -1, true), documents.getCompileFileName(), edView->editor->document()->codec());
}

void Texstudio::showPreview(const QDocumentCursor &previewc)
{
	if (previewQueueOwner != currentEditorView())
		previewQueue.clear();
	previewQueueOwner = currentEditorView();
	previewQueue.insert(previewc.lineNumber());

	// mark region which is previewed, or update
	int sid = previewc.document()->getFormatId("previewSelection");
	if (sid)
		updateEmphasizedRegion(previewc, sid);

	  previewDelayTimer.start(qMax(40, configManager.autoPreviewDelay));
    //QTimer::singleShot(qMax(40, configManager.autoPreviewDelay), this, SLOT(showPreviewQueue())); //slow down or it could create thousands of images
}

void Texstudio::showPreview(const QDocumentCursor &previewc, bool addToList)
{
	REQUIRE(currentEditor());
	REQUIRE(previewc.document() == currentEditor()->document());

	QString originalText = previewc.selectedText();
	if (originalText == "") return;
	// get document definitions
	//preliminary code ...
	const LatexDocument *rootDoc = documents.getRootDocumentForDoc();
	if (!rootDoc) return;
	QStringList header = makePreviewHeader(rootDoc);
	if (header.isEmpty()) return;
	PreviewSource ps(originalText, previewc.selectionStart().lineNumber(), previewc.selectionEnd().lineNumber(), false);
	buildManager.preview(header.join("\n"), ps,  documents.getCompileFileName(), rootDoc->codec());

	if (!addToList)
		return;

	if (configManager.autoPreview == ConfigManager::AP_PREVIOUSLY) {
		QList<QDocumentCursor> &clist = currentEditorView()->autoPreviewCursor;
		int sid = previewc.document()->getFormatId("previewSelection");
		for (int i = clist.size() - 1; i >= 0; i--)
			if (clist[i].anchorLineNumber() <= ps.toLine &&
			        clist[i].lineNumber()   >= ps.fromLine) {
				if (sid > 0)
					updateEmphasizedRegion(clist[i], -sid);
				clist.removeAt(i);
			}

		QDocumentCursor ss = previewc.selectionStart();
		QDocumentCursor se = previewc.selectionEnd();
		QDocumentCursor c(ss, se);
		c.setAutoUpdated(true);
		currentEditorView()->autoPreviewCursor.insert(0, c);
		// mark region
		if (sid)
			updateEmphasizedRegion(c, sid);
	}
}

QStringList Texstudio::makePreviewHeader(const LatexDocument *rootDoc)
{
	LatexEditorView *edView = rootDoc->getEditorView();
    if (!edView){
        return QStringList();
    }
	int m_endingLine = edView->editor->document()->findLineContaining("\\begin{document}", 0, Qt::CaseSensitive);
	if (m_endingLine < 0) return QStringList(); // can't create header
	QStringList header;
	for (int l = 0; l < m_endingLine; l++) {
		const QString &line = edView->editor->document()->line(l).text();
		int start = line.indexOf("\\input{");
		if (start < 0) {
			header << line;
		} else {
			// rewrite input to absolute paths
			QString newLine(line);
			start += 7;  // behind curly brace of \\input{
			int end = newLine.indexOf('}', start);
			if (end >= 0) {
				QString filename(newLine.mid(start, end - start));
				QString absPath = documents.getAbsoluteFilePath(filename);
#ifdef Q_OS_WIN
				absPath.replace('\\', '/');  // make sure the path argumment to \input uses '/' as dir separator
#endif
				if (absPath.contains(' ')) {
					absPath = '"' + absPath + '"';
				}
				newLine.replace(start, end - start, absPath);
			}
			header << newLine;
		}
	}
	if ((buildManager.dvi2pngMode == BuildManager::DPM_EMBEDDED_PDF || buildManager.dvi2pngMode == BuildManager::DPM_LUA_EMBEDDED_PDF)
			&& configManager.previewMode != ConfigManager::PM_EMBEDDED) {
		header << "\\usepackage[active,tightpage]{preview}"
		       << "\\usepackage{varwidth}"
		       << "\\AtBeginDocument{\\begin{preview}\\begin{varwidth}{\\linewidth}}"
		       << "\\AtEndDocument{\\end{varwidth}\\end{preview}}";
	}
	header << "\\pagestyle{empty}";// << "\\begin{document}";
	return header;
}

/*!
 * Add a format overlay to the provided selection. Existing overlays of the format will be deleted
 * from all lines that are touched by the selection.
 *
 * \param c: a QDocumentCursor with a selection
 * \param sid: formatScheme id
 */
void Texstudio::updateEmphasizedRegion(QDocumentCursor c, int sid)
{
	QDocument *doc = c.document();
	QDocumentCursor ss = c.selectionStart();
	QDocumentCursor se = c.selectionEnd();
	for (int i = ss.anchorLineNumber(); i <= se.anchorLineNumber(); i++) {
		int begin = i == ss.anchorLineNumber() ? ss.anchorColumnNumber() : 0;
		int end = i == se.anchorLineNumber() ? se.anchorColumnNumber() : doc->line(i).length();
		if (sid > 0) {
			doc->line(i).clearOverlays(sid);
			doc->line(i).addOverlay(QFormatRange(begin, end - begin, sid));
		} else {
			// remove overlay if sid <0 (removes -sid)
			doc->line(i).clearOverlays(-sid);
		}
    }
}
/*!
 * \brief Texstudio::completerIsVisible
 * \return true if completer is visible
 */
bool Texstudio::completerIsVisible()
{
    if(completer && completer->isVisible()){
        return true;
    }
    return false;
}

void Texstudio::showPreviewQueue()
{
	if (previewQueueOwner != currentEditorView()) {
		previewQueue.clear();
		return;
	}
	if (configManager.autoPreview == ConfigManager::AP_NEVER) {
		// remove marks
		int sid = previewQueueOwner->document->getFormatId("previewSelection");
		if (sid > 0) {
			foreach (const QDocumentCursor &c, previewQueueOwner->autoPreviewCursor) {
				updateEmphasizedRegion(c, -sid);
			}
		}
		previewQueueOwner->autoPreviewCursor.clear();
		previewQueue.clear();
		return;
	}
	foreach (const int line, previewQueue)
		foreach (const QDocumentCursor &c, previewQueueOwner->autoPreviewCursor)
			if (c.lineNumber() == line)
				showPreview(c, false);
	previewQueue.clear();
}



void Texstudio::recompileForPreview(){
	if (documents.getCompileFileName().isEmpty()) return;
#ifndef NO_POPPLER_PREVIEW
	if (PDFDocument::documentList().isEmpty()) return;
#endif
	if (!documents.currentDocument || documents.currentDocument->mayHaveDiffMarkers) return;
	previewEditorPending = currentEditor();
	if (!previewEditorPending || previewEditorPending->fileName().isEmpty()) return;
	previewFullCompileDelayTimer.start(qMax(40, configManager.autoPreviewDelay));
}
void Texstudio::recompileForPreviewNow(){
	if (!previewEditorPending || previewEditorPending != currentEditor()) return;
	if (buildManager.waitingForProcess()) {
		if (previewEditorPending->isContentModified()) {
			previewFullCompileDelayTimer.start(qMax(50, configManager.autoPreviewDelay));
		}
		return;
	}
	previewEditorPending->save();
	previewIsAutoCompiling = true;
	runCommand(BuildManager::CMD_COMPILE, nullptr, nullptr, false);
}

void Texstudio::editInsertRefToNextLabel(const QString &refCmd, bool backward)
{
	if (!currentEditorView()) return;
	QDocumentCursor c = currentEditor()->cursor();
	int l = c.lineNumber();
	int m = currentEditorView()->editor->document()->findLineContaining("\\label", l, Qt::CaseSensitive, backward);
	if (!backward && m < l) return;
	if (m < 0) return;
	// TODO: The search of the line should also be switched to the token system

	QDocumentLineHandle *dlh = currentEditor()->document()->line(m).handle();
    TokenList tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	QString label = Parsing::getArg(tl, Token::label);
	if (!label.isEmpty()) {
		currentEditor()->write(refCmd + "{" + label + "}");
	}
}

void Texstudio::editInsertRefToPrevLabel(const QString &refCmd)
{
	editInsertRefToNextLabel(refCmd, true);
}

void Texstudio::runSearch(SearchQuery *query)
{
	if (!currentEditorView() || !query) return;
	query->run(currentEditorView()->document);
}

void Texstudio::findLabelUsages(LatexDocument *contextDoc, const QString &labelText)
{
	if (!contextDoc) return;
	LabelSearchQuery *query = new LabelSearchQuery(labelText);
	searchResultWidget()->setQuery(query);
	query->run(contextDoc);
    outputView->showPage(outputView->SEARCH_RESULT_PAGE);
}

void Texstudio::findLabelUsagesFromAction()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;
    QString labelText = action->data().toString();
    LatexDocument *doc = action->property("doc").value<LatexDocument *>();
    findLabelUsages(doc, labelText);
}

SearchResultWidget *Texstudio::searchResultWidget()
{
	return outputView->getSearchResultWidget();
}

// show current cursor position in structure view
void Texstudio::cursorPositionChanged()
{
	LatexEditorView *view = currentEditorView();
	if (!view) return;
	int i = view->editor->cursor().lineNumber();

	view->checkRTLLTRLanguageSwitching();

	// search line in structure
	if (currentLine == i) return;
	currentLine = i;

	StructureEntry *newSection = currentEditorView()->document->findSectionForLine(currentLine);

    if(newSection!=currentSection){
        StructureEntry *old=currentSection;
        currentSection=newSection;
        updateCurrentPosInTOC(nullptr,old);
    }

	syncPDFViewer(currentEditor()->cursor(), false);
}

void Texstudio::syncPDFViewer(QDocumentCursor cur, bool inForeground)
{
#ifndef NO_POPPLER_PREVIEW
        if (inForeground) {
		// open new viewer, if none exists
		QAction *viewAct = getManagedAction("main/tools/view");
		if (viewAct) viewAct->trigger();
		return;
	}

	LatexDocument *doc = qobject_cast<LatexDocument *>(cur.document());
	if (!doc) doc = documents.currentDocument;
	if (doc) {
		QString filename = doc->getFileNameOrTemporaryFileName();
		if (!filename.isEmpty()) {
			int lineNumber = cur.isValid() ? cur.lineNumber() : currentLine;
			int originalLineNumber = doc->lineToLineSnapshotLineNumber(cur.line());
			if (originalLineNumber >= 0) lineNumber = originalLineNumber;
			int col = cur.columnNumber();
			PDFDocument::DisplayFlags displayPolicy = PDFDocument::NoDisplayFlags;
			if (inForeground) displayPolicy = PDFDocument::Raise | PDFDocument::Focus;
			foreach (PDFDocument *viewer, PDFDocument::documentList()) {
				if (inForeground || viewer->followCursor()) {
					viewer->syncFromSource(filename, lineNumber, col, displayPolicy);
				}
			}
		}
	}
#else
	Q_UNUSED(cur)
	Q_UNUSED(inForeground)
#endif
}

void Texstudio::fileCheckin(QString filename)
{
	if (!currentEditorView()) return;
	QString fn = filename.isEmpty() ? currentEditor()->fileName() : filename;
	UniversalInputDialog dialog;
	QString text;
	dialog.addTextEdit(&text, tr("commit comment:"));
    bool wholeDirectory=false;
    bool push=false;
    if(configManager.useVCS==0){ // SVN only
        dialog.addVariable(&wholeDirectory, tr("check in whole directory ?"));
    }else{
        dialog.addVariable(&push, tr("Push to repository ?"));
    }
	if (dialog.exec() == QDialog::Accepted) {
		fileSave(true);
		if (wholeDirectory) {
			fn = QFileInfo(fn).absolutePath();
		}
		//checkin(fn,text);
		if (svnadd(fn)) {
            checkin(fn, text,push);
		} else {
            if(configManager.useVCS==0){
                svn.createRepository(fn);
            }else{
                git.createRepository(fn);
            }
			svnadd(fn);
            checkin(fn, text);
		}
	}
}
/*!
 * \brief lock pdf file
 *
 * Determines pdf filename by using the current text file name and substitutes its extension to 'pdf'
 * \param filename
 */
void Texstudio::fileLockPdf(QString filename)
{
    if(configManager.useVCS>0){ // GIT
        return;
    }
	if (!currentEditorView()) return;
	QString finame = filename;
	if (finame.isEmpty())
		finame = documents.getTemporaryCompileFileName();
	QFileInfo fi(finame);
	QString basename = fi.baseName();
	QString path = fi.path();
	fi.setFile(path + "/" + basename + ".pdf");
	if (!fi.isWritable()) {
		svn.lock(fi.filePath());
	}
}
/*!
 * \brief check-in pdf file
 *
 * Determines pdf filename by using the current text file name and substitutes its extension to 'pdf'
 * If the file is not under version management, it tries to add the file.
 * \param filename
 */
void Texstudio::fileCheckinPdf(QString filename)
{
	if (!currentEditorView()) return;
	QString finame = filename;
	if (finame.isEmpty())
		finame = documents.getTemporaryCompileFileName();
	QFileInfo fi(finame);
	QString basename = fi.baseName();
	QString path = fi.path();
	QString fn = path + "/" + basename + ".pdf";
    if(configManager.useVCS==0){
        SVN::Status status = svn.status(fn);
        if (status == SVN::CheckedIn) return;
        if (status == SVN::Unmanaged)
            svnadd(fn);
        fileCheckin(fn);
    }else{
        GIT::Status status = git.status(fn);
        if (status == GIT::CheckedIn) return;
        if (status == GIT::Unmanaged)
            svnadd(fn);
        fileCheckin(fn);
    }
}
/*!
 * \brief svn update file
 * \param filename
 */
void Texstudio::fileUpdate(QString filename)
{
	if (!currentEditorView()) return;
	QString fn = filename.isEmpty() ? currentEditor()->fileName() : filename;
	if (fn.isEmpty()) return;
	QString output = svn.runSvn("update", "--non-interactive " + SVN::quote(fn));
	outputView->insertMessageLine(output);
}
/*!
 * \brief svn update work directory
 *
 * Uses the directory of the current file as cwd.
 * \param filename
 */
void Texstudio::fileUpdateCWD(QString filename)
{
	if (!currentEditorView()) return;
	QString fn = filename.isEmpty() ? currentEditor()->fileName() : filename;
	if (fn.isEmpty()) return;
	fn = QFileInfo(fn).path();
    QString output;
    if(configManager.useVCS==0){
        output = svn.runSvn("update", "--non-interactive " + SVN::quote(fn));
    }else{
        output = git.runGit("pull", SVN::quote(fn));
    }
	outputView->insertMessageLine(output);
}

void Texstudio::checkinAfterSave(QString filename, int checkIn)
{
	if (checkIn > 1) { // special treatment for save
		// 2: checkin
		// 1: don't check in
		checkin(filename);
		if (configManager.svnUndo) currentEditor()->document()->clearUndo();
	}
	if (checkIn == 0) { // from fileSaveAs
		if (configManager.autoCheckinAfterSaveLevel > 1) {
			if (svnadd(filename)) {
                checkin(filename, "txs auto checkin");
			} else {
				//create simple repository
                if(configManager.useVCS==0){
                    svn.createRepository(filename);
                }else{
                    git.createRepository(filename);
                }
				svnadd(filename);
                checkin(filename, "txs auto checkin");
			}
			// set SVN Properties if desired
			if (configManager.svnKeywordSubstitution) {
				svn.runSvn("propset svn:keywords", "\"Date Author HeadURL Revision\" " + SVN::quote(filename));
			}
		}
	}
}

void Texstudio::checkin(QString fn, QString text, bool push)
{
    if(configManager.useVCS==0){
        svn.commit(fn, text);
    }else{
        git.commit(fn, text);
        if(push){
            QFileInfo fi(fn);
            git.push(fi.absolutePath());
        }
    }
	LatexEditorView *edView = getEditorViewFromFileName(fn);
	if (edView)
		edView->editor->setProperty("undoRevision", 0);
}

bool Texstudio::svnadd(QString fn, int stage)
{
	QString path = QFileInfo(fn).absolutePath();
    if(configManager.useVCS==0){
        if (!QFile::exists(path + "/.svn")) {
            if (stage < configManager.svnSearchPathDepth) {
                if (stage > 0) {
                    QDir dr(path);
                    dr.cdUp();
                    path = dr.absolutePath();
                }
                if (svnadd(path, stage + 1)) {
                    checkin(path);
                } else
                    return false;
            } else {
                return false;
            }
        }
        svn.runSvn("add", SVN::quote(fn));
        return true;
    }else{
        GIT::Status st=git.status(fn);
        if(st==GIT::NoRepository){
            return false;
        }
        if(st==GIT::Unmanaged){
            git.runGit("add", GIT::quote(fn));
            return true;
        }
        if(st==GIT::Modified){
            return true;
        }
        return false;
    }
}

void Texstudio::svnUndo(bool redo)
{
	QString fn = currentEditor()->fileName();
	// get revisions of current file
	QStringList revisions = svn.log(fn);

	QVariant zw = currentEditor()->property("undoRevision");
	int undoRevision = zw.canConvert<int>() ? zw.toInt() : 0;

	int l = revisions.size();
	if (undoRevision >= l - 1) return;
	if (!redo) undoRevision++;

	if (redo) changeToRevision(revisions.at(undoRevision - 1), revisions.at(undoRevision));
	else changeToRevision(revisions.at(undoRevision), revisions.at(undoRevision - 1));

	currentEditor()->document()->clearUndo();
	if (redo) undoRevision--;
	currentEditor()->setProperty("undoRevision", undoRevision);
}

void Texstudio::svnPatch(QEditor *ed, QString diff)
{
    if(diff.isEmpty()){
        return;
    }
	QStringList lines;
	//for(int i=0;i<diff.length();i++)
	//   qDebug()<<diff[i];
	if (diff.contains("\r\n")) {
		lines = diff.split("\r\n");
	} else {
		if (diff.contains("\n")) {
			lines = diff.split("\n");
		} else {
			lines = diff.split("\r");
		}
	}
	for (int i = 0; i < lines.length(); i++) {
		//workaround for svn bug
		// at times it shows text@@ pos insted of text \n @@ ...
		if (lines[i].contains("@@")) {
			int p = lines[i].indexOf("@@");
			lines[i] = lines[i].mid(p);
		}
	}
    if(lines.size()<4){
        return;
    }
    for (int i = 0; i < 3 ; i++) lines.removeFirst();
	if (!lines.first().contains("@@")) {
		lines.removeFirst();
	}

    QRegExp rx("@@ -(\\d+),?(\\d*)\\s*\\+(\\d+),(\\d+)");
	int cur_line;
	bool atDocEnd = false;
    int realTextLines=ed->document()->lines();
	QDocumentCursor c = ed->cursor();
	foreach (const QString &elem, lines) {
		QChar ch = ' ';
		if (!elem.isEmpty()) {
			ch = elem.at(0);
		}
		if (ch == '@') {
			if (rx.indexIn(elem) > -1) {
				cur_line = rx.cap(3).toInt();
				c.moveTo(cur_line - 1, 0);
			} else {
				qDebug() << "Bug";
			}
		} else {
			if (ch == '-') {
				atDocEnd = (c.lineNumber() == ed->document()->lineCount() - 1);
				if (c.line().text() != elem.mid(1))
					qDebug() << "del:" << c.line().text() << elem;
				c.eraseLine();
                --realTextLines;
                //if (atDocEnd) c.deletePreviousChar();
			} else {
				if (ch == '+') {
                    //atDocEnd = (c.lineNumber() == ed->document()->lineCount() - 1);
                    if (atDocEnd) {
						c.movePosition(1, QDocumentCursor::EndOfLine, QDocumentCursor::MoveAnchor);
                        if(realTextLines>0)
                            c.insertLine();
                    }
					c.insertText(elem.mid(1));
                    ++realTextLines;
					// if line contains \r, no further line break needed
					if (!atDocEnd) {
						c.insertText("\n");
					}
				} else {
					atDocEnd = (c.lineNumber() == ed->document()->lineCount() - 1);
					int limit = 5;
					if (!atDocEnd) {
						while ((c.line().text() != elem.mid(1)) && (limit > 0) && (c.lineNumber() < ed->document()->lineCount() - 1)) {
							qDebug() << c.line().text() << c.lineNumber() << "<>" << elem.mid(1);
							c.movePosition(1, QDocumentCursor::NextLine, QDocumentCursor::MoveAnchor);
							c.movePosition(1, QDocumentCursor::StartOfLine, QDocumentCursor::MoveAnchor);
							limit--;
							if (limit == 0) {
								qDebug() << "failed";
							}
						}
						atDocEnd = (c.lineNumber() == ed->document()->lineCount() - 1);
						if (!atDocEnd) {
							c.movePosition(1, QDocumentCursor::NextLine, QDocumentCursor::MoveAnchor);
							c.movePosition(1, QDocumentCursor::StartOfLine, QDocumentCursor::MoveAnchor);
						}
					}
				}
			}
		}
	}
}
/*!
 * \brief show old revisions from svn/git repository
 * List all stored revision names/numbers in a dialog which allows to switch back to old revisions of the text
 * The text is directly updated when an old revision is selected via a combobox.
 * The user can either select and copy content to bring to the most recent version or he can edit the old revision thereby making it the current one.
 * To enable changing to the most recent version again, text is automatically saved *and* checked in.
 */
void Texstudio::showOldRevisions()
{
	// check if a dialog is already open
	if (svndlg) return;
	//needs to save first if modified
	if (!currentEditor())
		return;

	if (currentEditor()->fileName() == "" || !currentEditor()->fileInfo().exists())
		return;

	if (currentEditor()->isContentModified()) {
		removeDiffMarkers();// clean document from diff markers first
		currentEditor()->save();
		//currentEditorView()->editor->setModified(false);
		MarkCurrentFileAsRecent();
		checkin(currentEditor()->fileName(), "txs auto checkin", true);
    }else{
        bool modifiedOnDisk=false;
        if(configManager.useVCS==0){
            SVN::Status st = svn.status(currentEditor()->fileName());
            modifiedOnDisk=(st==SVN::Modified);
        }else{
            GIT::Status st = git.status(currentEditor()->fileName());
            modifiedOnDisk=(st==GIT::Modified);
        }
        if(modifiedOnDisk){
            checkin(currentEditor()->fileName(), "txs auto checkin", true);
        }
    }
	updateCaption();

    QStringList log;
    if(configManager.useVCS==0){
        log = svn.log(currentEditor()->fileName());
    }else{
        log = git.log(currentEditor()->fileName());
    }
	if (log.size() < 1) return;

	svndlg = new QDialog(this);
	QVBoxLayout *lay = new QVBoxLayout(svndlg);
	QLabel *label = new QLabel(tr("Attention: dialog is automatically closed if the text is manually edited!"), svndlg);
	lay->addWidget(label);
	cmbLog = new QComboBox(svndlg);
	cmbLog->insertItems(0, log);
	lay->addWidget(cmbLog);
    connect(svndlg, &QDialog::finished, this, &Texstudio::svnDialogClosed);
    connect(cmbLog, SIGNAL(currentTextChanged(QString)), this, SLOT(changeToRevision(QString)));
    connect(currentEditor(), SIGNAL(textEdited(QKeyEvent*)), svndlg, SLOT(close()));
	currentEditor()->setProperty("Revision", log.first());
	svndlg->setAttribute(Qt::WA_DeleteOnClose, true);
    svndlg->show();
}
/*!
 * \brief reset when closing svn old revision dialog
 * the dialog itself is deleted
 * if the revision is the most recent, test is declared unmodified
 */
void Texstudio::svnDialogClosed(int)
{
	if (cmbLog->currentIndex() == 0) currentEditor()->document()->setClean();
	svndlg = nullptr;
}
/*!
 * \brief change editor content from one revision to another
 * diff is generated via git/svn
 * and that diff is applied to the current editor
 * \param rev
 * \param old_rev
 */
void Texstudio::changeToRevision(QString rev, QString old_rev)
{
	QString filename = currentEditor()->fileName();
	// get diff
	QRegExp rx("^[r](\\d+) \\|");
    if(configManager.useVCS==1){
        //GIT
        rx.setPattern("^([a-f0-9]+) ");
    }
	QString old_revision;
	if (old_rev.isEmpty()) {
		QVariant zw = currentEditor()->property("Revision");
		Q_ASSERT(zw.isValid());
		old_revision = zw.toString();
	} else {
		old_revision = old_rev;
	}
	if (rx.indexIn(old_revision) > -1) {
		old_revision = rx.cap(1);
	} else return;
	QString new_revision = rev;
	if (rx.indexIn(new_revision) > -1) {
		new_revision = rx.cap(1);
	} else return;
    QString cmd;
    if(configManager.useVCS==0){
        //SVN
        cmd = SVN::makeCmd("diff", "-r " + old_revision + ":" + new_revision + " " + SVN::quote(filename));
    }else{
        //GIT
        cmd = GIT::makeCmd("diff", old_revision + " " + new_revision + " " + SVN::quote(filename));
    }
	QString buffer;
    runCommandNoSpecialChars(cmd, &buffer, currentEditor()->getFileCodec());
	// patch
	svnPatch(currentEditor(), buffer);
    currentEditor()->setProperty("Revision", rev);
}

bool Texstudio::generateMirror(bool setCur)
{
	if (!currentEditorView()) return false;
	QDocumentCursor cursor = currentEditorView()->editor->cursor();
	QDocumentCursor oldCursor = cursor;
	QString line = cursor.line().text();
	QString command, value;
	Token tk = Parsing::getTokenAtCol(cursor.line().handle(), cursor.columnNumber());

	if (tk.type == Token::env || tk.type == Token::beginEnv) {
		if (tk.length > 0) {
			value = tk.getText();
			command = Parsing::getCommandFromToken(tk);
			//int l=cursor.lineNumber();
			if (currentEditor()->currentPlaceHolder() != -1 &&
			        currentEditor()->getPlaceHolder(currentEditor()->currentPlaceHolder()).cursor.isWithinSelection(cursor))
				currentEditor()->removePlaceHolder(currentEditor()->currentPlaceHolder()); //remove currentplaceholder to prevent nesting
			//move cursor to env name
			int pos = tk.start;
			cursor.selectColumns(pos, pos + tk.length);

			LatexDocument *doc = currentEditorView()->document;

			PlaceHolder ph;
			ph.cursor = cursor;
			ph.autoRemove = true;
			ph.autoRemoveIfLeft = true;
			// remove curly brakets as well
			QString searchWord = "\\end{" + value + "}";
			QString inhibitor = "\\begin{" + value + "}";
			bool backward = (command == "\\end");
			int step = 1;
			if (backward) {
				qSwap(searchWord, inhibitor);
				step = -1;
			}
			int ln = cursor.lineNumber();
			int col = cursor.columnNumber();
			bool finished = false;
			int nested = 0;
			int colSearch = 0;
			int colInhibit = 0;
			if (step < 0)
				line = line.left(col);
			while (!finished) {
				if (step > 0) {
					//forward search
					colSearch = line.indexOf(searchWord, col);
					colInhibit = line.indexOf(inhibitor, col);
				} else {
					//backward search
					colSearch = line.lastIndexOf(searchWord);
					colInhibit = line.lastIndexOf(inhibitor);
				}
				if (colSearch < 0 && colInhibit < 0) {
					ln += step;
					if (doc->lines() <= ln || ln < 0)
						break;
					line = doc->line(ln).text();
					col = 0;
				}
				if (colSearch >= 0 && colInhibit >= 0) {
					if (colSearch * step < colInhibit * step) {
						if (nested == 0) {
							finished = true;
						}
						nested--;
						col = colSearch + 1;
						if (step < 0)
							line = line.left(colSearch);
					} else {
						if (step > 0) {
							col = colInhibit + 1;
						} else {
							line = line.left(colInhibit);
						}
						nested++;
					}
				} else {
					if (colSearch >= 0) {
						nested--;
						if (nested < 0)
							finished = true;
						if (step > 0) {
							col = colSearch + 1;
						} else {
							line = line.left(colSearch);
						}
					}
					if (colInhibit >= 0) {
						nested++;
						if (step > 0) {
							col = colInhibit + 1;
						} else {
							line = line.left(colInhibit);
						}
					}
				}
			}
			if (finished) {
				line = doc->line(ln).text();
				int start = colSearch;
				int offset = searchWord.indexOf("{");
				ph.mirrors << currentEditor()->document()->cursor(ln, start + offset + 1, ln, start + searchWord.length() - 1);
			}

			currentEditor()->addPlaceHolder(ph);
			currentEditor()->setPlaceHolder(currentEditor()->placeHolderCount() - 1);
			if (setCur)
				currentEditorView()->editor->setCursor(oldCursor);
			return true;
		}
	}
	return false;
}

void Texstudio::generateBracketInverterMirror()
{
	if (!currentEditor()) return;
	REQUIRE(currentEditor()->document() && currentEditor()->document()->languageDefinition());
	QDocumentCursor orig, to;
	currentEditor()->cursor().getMatchingPair(orig, to, false);
	if (!orig.isValid() && !to.isValid()) return;  // no matching pair found

	PlaceHolder ph;
	ph.cursor = orig.selectionStart();
	ph.mirrors << to.selectionStart();
	ph.length = orig.selectedText().length();
	ph.affector = BracketInvertAffector::instance();
	currentEditor()->addPlaceHolder(ph);
	currentEditor()->setPlaceHolder(currentEditor()->placeHolderCount() - 1);
}

void Texstudio::jumpToBracket()
{
	if (!currentEditor()) return;
	REQUIRE(sender() && currentEditor()->document() && currentEditor()->document()->languageDefinition());
	QDocumentCursor orig, to;
	const QDocumentCursor se = currentEditor()->cursor().selectionEnd();
	se.getMatchingPair(orig, to, false);
	if (!orig.isValid() && !to.isValid()) return;  // no matching pair found
	if (orig.selectionEnd() == se) currentEditor()->setCursor(to.selectionStart());
	else currentEditor()->setCursor(to.selectionEnd());
}

void Texstudio::selectBracket()
{
	if (!currentEditor()) return;
	REQUIRE(sender() && currentEditor()->document());
	if (!currentEditor()->document()->languageDefinition()) return;

	QDocumentCursor cursor = currentEditor()->cursor();
	QString type = sender()->property("type").toString();
	if (type == "inner") {
		cursor.select(QDocumentCursor::ParenthesesInner);
	} else if (type == "outer") {
		cursor.select(QDocumentCursor::ParenthesesOuter);
	} else if (type == "command") {
		Token tk = Parsing::getTokenAtCol(cursor.line().handle(), cursor.columnNumber());
		if (tk.type == Token::command) {
			cursor.setColumnNumber(tk.start + tk.length);
			cursor.select(QDocumentCursor::ParenthesesOuter);
			cursor.setAnchorColumnNumber(tk.start);
		} else {
			cursor.select(QDocumentCursor::ParenthesesOuter);
			if (cursor.anchorColumnNumber() > 0) {
				tk = Parsing::getTokenAtCol(cursor.line().handle(), cursor.anchorColumnNumber() - 1);
				if (tk.type == Token::command) {
					cursor.setAnchorColumnNumber(tk.start);
				}
			}
		}
	} else if (type == "line") {
		QDocumentCursor orig, to;
		cursor.getMatchingPair(orig, to, true);
		if (!orig.isValid() && !to.isValid()) return;  // no matching pair found

		if (to < orig) to.setColumnNumber(0);
		else to.setColumnNumber(to.line().length());

		QDocumentCursor::sort(orig, to);
		if (orig.hasSelection()) orig = orig.selectionStart();
		if (to.hasSelection()) to = to.selectionEnd();

		cursor.select(orig.lineNumber(), orig.columnNumber(), to.lineNumber(), to.columnNumber());
	} else {
		qWarning("Unhandled selectBracket() type");
	}
	currentEditor()->setCursor(cursor);
}

void Texstudio::findMissingBracket()
{
	if (!currentEditor()) return;
	REQUIRE(currentEditor()->document() && currentEditor()->document()->languageDefinition());
	QDocumentCursor c = currentEditor()->languageDefinition()->getNextMismatch(currentEditor()->cursor());
	if (c.isValid()) currentEditor()->setCursor(c);
}

void Texstudio::openExternalFile(QString name, const QString &defaultExt, LatexDocument *doc, bool relativeToCurrentDoc)
{
	if (!doc) {
		if (!currentEditor()) return;
		doc = qobject_cast<LatexDocument *>(currentEditor()->document());
	}
	if (!doc) return;
	name.remove('"');  // ignore quotes (http://sourceforge.net/p/texstudio/bugs/1366/)
    if(name.endsWith('#')){
        relativeToCurrentDoc=true;
        name.chop(1);
    }
    QStringList curPaths;
    if (defaultExt == "bib") {
        curPaths << configManager.additionalBibPaths.split(getPathListSeparator());
    }
    if(relativeToCurrentDoc){
        curPaths<< ensureTrailingDirSeparator(doc->getFileInfo().absolutePath());
    }
    bool loaded = false;
    loaded = load(documents.getAbsoluteFilePath(name, defaultExt,curPaths));
    if(!loaded){
        loaded = load(documents.getAbsoluteFilePath(name, "",curPaths));
    }

	if (!loaded) {
        QFileInfo fi(documents.getAbsoluteFilePath(name, defaultExt,curPaths));
		if (fi.exists()) {
			UtilsUi::txsCritical(tr("Unable to open file \"%1\".").arg(fi.fileName()));
		} else {
			if (UtilsUi::txsConfirmWarning(tr("The file \"%1\" does not exist.\nDo you want to create it?").arg(fi.fileName()))) {
				int lineNr = -1;
				if (currentEditor()) {
					lineNr = currentEditor()->cursor().lineNumber();
				}
				if (!fi.absoluteDir().exists())
					fi.absoluteDir().mkpath(".");
				fileNew(fi.absoluteFilePath());
				doc->patchStructure(lineNr, 1);
			}
		}
    }
}


void Texstudio::openExternalFileFromAction()
{
    QAction *act = qobject_cast<QAction *>(sender());
    QString name = act->data().toString();
    name.replace("\\string~",QDir::homePath());

    if (!name.isEmpty())
        openExternalFile(name);
}

void Texstudio::cursorHovered()
{
	if (completer->isVisible()) return;
	generateMirror(true);
}

void Texstudio::saveProfile()
{
	QString currentDir = configManager.configBaseDir;
	QString fname = FileDialog::getSaveFileName(this, tr("Save Profile"), currentDir, tr("TXS Profile", "filter") + "(*.txsprofile);;" + tr("All files") + " (*)");
	saveSettings(fname);
}

void Texstudio::loadProfile()
{
	QString currentDir = configManager.configBaseDir;
	QString fname = FileDialog::getOpenFileName(this, tr("Load Profile"), currentDir, tr("TXS Profile", "filter") + "(*.txsprofile);;" + tr("All files") + " (*)");
	if (fname.isNull())
		return;
	if (QFileInfo(fname).isReadable()) {
		bool macro = false;
		bool userCommand = false;
		saveSettings();
		QSettings *profile = new QSettings(fname, QSettings::IniFormat);
		QSettings *config = configManager.newQSettings();
		if (profile && config) {
			QStringList keys = profile->allKeys();
			foreach (const QString &key, keys) {
				//special treatment for macros/usercommands (list maybe shorter than before)
				if (key.startsWith("texmaker/Macros")) {
					continue;
				}
				if (key == "texmaker/Tools/User Order") {
					// logic assumes that the user command name is exclusive
					QStringList order = config->value(key).toStringList() << profile->value(key).toStringList();
					config->setValue(key, order);
					userCommand = true;
					QString nameKey("texmaker/Tools/Display Names");
					QStringList displayNames = config->value(nameKey).toStringList() << profile->value(nameKey).toStringList();
					config->setValue(nameKey, displayNames);
					continue;
				}
				if (key == "texmaker/Tools/Display Names") {
					continue;  // handled above
				}
				config->setValue(key, profile->value(key));
			}
			// handle macros
			for (int i = 0; i < ConfigManager::MAX_NUM_MACROS; i++) {
			    QStringList ls = profile->value(QString("texmaker/Macros/%1").arg(i)).toStringList();
			    if (ls.isEmpty()) break;
			    if (!macro) { //remove old values
				config->beginGroup("texmaker");
				config->remove("Macros");
				config->endGroup();
				configManager.completerConfig->userMacros.clear();
			    }
			    configManager.completerConfig->userMacros.append(Macro(ls));
			    macro=true;
			}
		}
		delete profile;
		delete config;
		readSettings(true);
        configManager.modifyManagedShortcuts();
		if (macro)
			updateUserMacros();
		if (userCommand)
			updateUserToolMenu();
	} else UtilsUi::txsWarning(tr("Failed to read profile file %1.").arg(fname));
}

void Texstudio::addRowCB()
{
	if (!currentEditorView()) return;
	QDocumentCursor cur = currentEditorView()->editor->cursor();
	if (!LatexTables::inTableEnv(cur)) return;
	int cols = LatexTables::getNumberOfColumns(cur);
	if (cols < 1) return;
	LatexTables::addRow(cur, cols);
}

void Texstudio::addColumnCB()
{
	if (!currentEditorView()) return;
	QDocumentCursor cur = currentEditorView()->editor->cursor();
	if (!LatexTables::inTableEnv(cur)) return;
	int col = LatexTables::getColumn(cur) + 1;
	if (col < 1) return;
	if (col == 1 && cur.atLineStart()) col = 0;
	LatexTables::addColumn(currentEditorView()->document, currentEditorView()->editor->cursor().lineNumber(), col);
}

void Texstudio::removeColumnCB()
{
	if (!currentEditorView()) return;
	QDocumentCursor cur = currentEditorView()->editor->cursor();
	if (!LatexTables::inTableEnv(cur)) return;
	// check if cursor has selection
	int numberOfColumns = 1;
	int col = LatexTables::getColumn(cur);
	if (cur.hasSelection()) {
		// if selection span within one row, romove all touched columns
		QDocumentCursor c2(cur.document(), cur.anchorLineNumber(), cur.anchorColumnNumber());
		if (!LatexTables::inTableEnv(c2)) return;
		QString res = cur.selectedText();
		if (res.contains("\\\\")) return;
		int col2 = LatexTables::getColumn(c2);
		numberOfColumns = abs(col - col2) + 1;
		if (col2 < col) col = col2;
	}
	int ln = cur.lineNumber();
	for (int i = 0; i < numberOfColumns; i++) {
	        LatexTables::removeColumn(currentEditorView()->document, ln, col, nullptr);
	}
}

void Texstudio::removeRowCB()
{
	if (!currentEditorView()) return;
	QDocumentCursor cur = currentEditorView()->editor->cursor();
	if (!LatexTables::inTableEnv(cur)) return;
	LatexTables::removeRow(cur);
}

void Texstudio::cutColumnCB()
{
	if (!currentEditorView()) return;
	QDocumentCursor cur = currentEditorView()->editor->cursor();
	if (!LatexTables::inTableEnv(cur)) return;
	// check if cursor has selection
	int numberOfColumns = 1;
	int col = LatexTables::getColumn(cur);
	if (cur.hasSelection()) {
		// if selection span within one row, romove all touched columns
		QDocumentCursor c2(cur.document(), cur.anchorLineNumber(), cur.anchorColumnNumber());
		if (!LatexTables::inTableEnv(c2)) return;
		QString res = cur.selectedText();
		if (res.contains("\\\\")) return;
		int col2 = LatexTables::getColumn(c2);
		numberOfColumns = abs(col - col2) + 1;
		if (col2 < col) col = col2;
	}
	int ln = cur.lineNumber();
	m_columnCutBuffer.clear();
	QStringList lst;
	for (int i = 0; i < numberOfColumns; i++) {
		lst.clear();
		LatexTables::removeColumn(currentEditorView()->document, ln, col, &lst);
		if (m_columnCutBuffer.isEmpty()) {
			m_columnCutBuffer = lst;
		} else {
			for (int i = 0; i < m_columnCutBuffer.size(); i++) {
				QString add = "&";
				if (!lst.isEmpty()) add += lst.takeFirst();
				m_columnCutBuffer[i] += add;
			}
		}
	}

}

void Texstudio::pasteColumnCB()
{
	if (!currentEditorView()) return;
	QDocumentCursor cur = currentEditorView()->editor->cursor();
	if (!LatexTables::inTableEnv(cur)) return;
	int col = LatexTables::getColumn(cur) + 1;
	if (col == 1 && cur.atLineStart()) col = 0;
	LatexTables::addColumn(currentEditorView()->document, currentEditorView()->editor->cursor().lineNumber(), col, &m_columnCutBuffer);
}

void Texstudio::addHLineCB()
{
	if (!currentEditorView()) return;
	QDocumentCursor cur = currentEditorView()->editor->cursor();
	if (!LatexTables::inTableEnv(cur)) return;
	LatexTables::addHLine(cur);
}

void Texstudio::remHLineCB()
{
	if (!currentEditorView()) return;
	QDocumentCursor cur = currentEditorView()->editor->cursor();
	if (!LatexTables::inTableEnv(cur)) return;
	LatexTables::addHLine(cur, -1, true);
}

void Texstudio::findWordRepetions()
{
	if (!currentEditorView()) return;
	if (configManager.editorConfig && !configManager.editorConfig->inlineSpellChecking) {
		QMessageBox::information(this, tr("Problem"), tr("Finding word repetitions only works with activated online spell checking !"), QMessageBox::Ok);
		return;
	}
	QDialog *dlg = new QDialog(this);
	dlg->setAttribute(Qt::WA_DeleteOnClose, true);
	dlg->setWindowTitle(tr("Find Word Repetitions"));
	QGridLayout *layout = new QGridLayout;
	layout->setColumnStretch(1, 1);
	layout->setColumnStretch(0, 1);
	QComboBox *cb = new QComboBox(dlg);
	cb->addItems(QStringList() << "spellingMistake" << "wordRepetition" << "wordRepetitionLongRange" << "badWord" << "grammarMistake" << "grammarMistakeSpecial1" << "grammarMistakeSpecial2" << "grammarMistakeSpecial3" << "grammarMistakeSpecial4");
	cb->setCurrentIndex(1);
	cb->setObjectName("kind");
	cb->setEditable(true); //so people can search for other things as well
	QPushButton *btNext = new QPushButton(tr("&Find Next"), dlg);
	btNext->setObjectName("next");
	QPushButton *btPrev = new QPushButton(tr("&Find Previous"), dlg);
	btPrev->setObjectName("prev");
	QPushButton *btClose = new QPushButton(tr("&Close"), dlg);
	btClose->setObjectName("close");
	layout->addWidget(cb, 0, 0);
	layout->addWidget(btNext, 0, 1);
	layout->addWidget(btPrev, 0, 2);
	layout->addWidget(btClose, 0, 3);
	dlg->setLayout(layout);
	connect(btNext, SIGNAL(clicked()), this, SLOT(findNextWordRepetion()));
	connect(btPrev, SIGNAL(clicked()), this, SLOT(findNextWordRepetion()));
	connect(btClose, SIGNAL(clicked()), dlg, SLOT(close()));
	dlg->setModal(false);
	dlg->show();
	dlg->raise();

}

void Texstudio::findNextWordRepetion()
{
	QPushButton *mButton = qobject_cast<QPushButton *>(sender());
	bool backward = mButton->objectName() == "prev";
	if (!currentEditorView()) return;
	typedef QFormatRange (QDocumentLine::*OverlaySearch) (int, int, int) const;
	OverlaySearch overlaySearch = backward ? &QDocumentLine::getLastOverlay : &QDocumentLine::getFirstOverlay;
	QComboBox *kind = mButton->parent()->findChild<QComboBox *>("kind");
	int overlayType = currentEditorView()->document->getFormatId(kind ? kind->currentText() : "wordRepetition");
	QDocumentCursor cur = currentEditor()->cursor();
	if (cur.hasSelection()) {
		if (backward) cur = cur.selectionStart();
		else cur = cur.selectionEnd();
	}
	int lineNr = cur.lineNumber();
	QDocumentLine line = cur.line();
	int fx = backward ? 0 : (cur.endColumnNumber() + 1), tx = backward ? cur.startColumnNumber() - 1 : line.length();
	while (line.isValid()) {
		if (line.hasOverlay(overlayType)) {
			QFormatRange range = (line.*overlaySearch)(fx, tx, overlayType);
			if (range.length > 0) {
				currentEditor()->setCursor(currentEditor()->document()->cursor(lineNr, range.offset, lineNr, range.offset + range.length));
				return;
			}
		}
		if (backward)
			lineNr--;
		else
			lineNr++;
		line = currentEditor()->document()->line(lineNr);
		fx = 0;
		tx = line.length();
	}
	UtilsUi::txsInformation(backward ? tr("Reached beginning of text.") : tr("Reached end of text."));
}

void Texstudio::importPackage(QString name)
{
	if (!latexStyleParser) {
		QString cmd_latex = buildManager.getCommandInfo(BuildManager::CMD_LATEX).getProgramNameUnquoted();
		QString baseDir;
		if (!QFileInfo(cmd_latex).isRelative())
			baseDir = QFileInfo(cmd_latex).absolutePath() + "/";
		latexStyleParser = new LatexStyleParser(this, configManager.configBaseDir, baseDir + "kpsewhich");
		connect(latexStyleParser, SIGNAL(scanCompleted(QString)), this, SLOT(packageScanCompleted(QString)));
		connect(latexStyleParser, SIGNAL(finished()), this, SLOT(packageParserFinished()));
		latexStyleParser->setAlias(latexParser.packageAliases);
		latexStyleParser->start();
		QTimer::singleShot(30000, this, SLOT(stopPackageParser()));
	}
	QString dirName;
	if (name.contains("/")) {
		int i = name.indexOf("/");
		dirName = "/" + name.mid(i + 1);
		name = name.left(i);
	}
	name.chop(4);
	name.append(".sty");
    // remove option# from name
    int i=name.indexOf("#");
    if(i>-1){
        name=name.mid(i+1);
    }
	latexStyleParser->addFile(name + dirName);
	name.chop(4);
	name.append(".cls"); // try also cls
	latexStyleParser->addFile(name + dirName);
}

void Texstudio::packageScanCompleted(QString name)
{
	QStringList lst = name.split('#');
	QString baseName = name;
	if (lst.size() > 1) {
		baseName = lst.first();
		name = lst.last();
	}
	foreach (LatexDocument *doc, documents.documents) {
		if (doc->containsPackage(baseName)) {
            //find proper key
            QStringList keys=documents.cachedPackages.keys();
            keys=keys.filter(name+".cwl");
            foreach(const QString &key,keys){
                documents.cachedPackages.remove(key); // TODO: check is this still correct if keys are complex?
            }
			doc->updateCompletionFiles(false);
		}
	}
}

void Texstudio::stopPackageParser()
{
	if (latexStyleParser)
		latexStyleParser->stop();
}

void Texstudio::packageParserFinished()
{
	delete latexStyleParser;
        latexStyleParser = nullptr;
}

void Texstudio::readinAllPackageNames()
{
	if (!packageListReader) {
		// preliminarily use cached packages
		QFileInfo cacheFileInfo = QFileInfo(QDir(configManager.configBaseDir), "packageCache.dat");
		if (cacheFileInfo.exists()) {
            std::set<QString> cachedPackages = PackageScanner::readPackageList(cacheFileInfo.absoluteFilePath());
			packageListReadCompleted(cachedPackages);
		}
		if (configManager.scanInstalledLatexPackages) {
			// start reading actually installed packages
			QString cmd_latex = buildManager.getCommandInfo(BuildManager::CMD_LATEX).getProgramNameUnquoted();
			QString baseDir;
			if (!QFileInfo(cmd_latex).isRelative())
				baseDir = QFileInfo(cmd_latex).absolutePath() + "/";
#ifdef Q_OS_WIN
			bool isMiktex = false;
			if (baseDir.contains("miktex", Qt::CaseInsensitive)) {
				isMiktex = true;
			} else if (!baseDir.contains("texlive", Qt::CaseInsensitive)) {
				ExecProgram execProgram(baseDir + "latex.exe --version", "");
				execProgram.execAndWait();
				if (execProgram.m_normalRun && execProgram.m_standardOutput.contains("miktex", Qt::CaseInsensitive)) {
					isMiktex = true;
				}
			}
			if (isMiktex)
				packageListReader = new MiktexPackageScanner(quotePath(baseDir + "mpm.exe"), configManager.configBaseDir, this);
			else
				packageListReader = new KpathSeaParser(quotePath(baseDir + "kpsewhich"), this); // TeXlive on windows uses kpsewhich
#else
			QString addPaths=BuildManager::resolvePaths(BuildManager::additionalSearchPaths);
			packageListReader = new KpathSeaParser(quotePath(baseDir + "kpsewhich"), this,addPaths);
#endif
            connect(packageListReader, SIGNAL(scanCompleted(std::set<QString>)), this, SLOT(packageListReadCompleted(std::set<QString>)));
			packageListReader->start();
		}
	}
}

void Texstudio::packageListReadCompleted(std::set<QString> packages)
{
	latexPackageList = packages;
	if (qobject_cast<PackageScanner *>(sender())) {
		PackageScanner::savePackageList(packages, QFileInfo(QDir(configManager.configBaseDir), "packageCache.dat").absoluteFilePath());
		packageListReader->wait();
		delete packageListReader;
		packageListReader = nullptr;
	}
	foreach (LatexDocument *doc, documents.getDocuments()) {
		LatexEditorView *edView = doc->getEditorView();
		if (edView)
			edView->updatePackageFormats();
	}
}

QString Texstudio::clipboardText(const QClipboard::Mode &mode) const
{
	return QApplication::clipboard()->text(mode);
}

void Texstudio::setClipboardText(const QString &text, const QClipboard::Mode &mode)
{
	QApplication::clipboard()->setText(text, mode);
}

int Texstudio::getVersion() const
{
    return Version::parseVersionNumberToInt(TXSVERSION);
}

/*!
 * This function is mainly intended for use in scripting
 * \a shortcut: textual representation of the keysequence, e.g. simulateKeyPress("Shift+Up")
 */
void Texstudio::simulateKeyPress(const QString &shortcut)
{
	QKeySequence seq = QKeySequence::fromString(shortcut, QKeySequence::PortableText);
#if (QT_VERSION>=QT_VERSION_CHECK(6,0,0))
    //TODO Qt6 ?
    if (seq.count() > 0) {
        QKeyCombination keyCombination = seq[0];
        int key = keyCombination.key();
        Qt::KeyboardModifiers modifiers = keyCombination.keyboardModifiers();
        // TODO: we could additionally provide the text for the KeyEvent (necessary for actually typing characters
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, modifiers);
        QApplication::postEvent(QApplication::focusWidget(), event);
        event = new QKeyEvent(QEvent::KeyRelease, key, modifiers);
        QApplication::postEvent(QApplication::focusWidget(), event);
    }
#else
        if (seq.count() > 0) {
        int key = seq[0] & ~Qt::KeyboardModifierMask;
		Qt::KeyboardModifiers modifiers = static_cast<Qt::KeyboardModifiers>(seq[0]) & Qt::KeyboardModifierMask;
		// TODO: we could additionally provide the text for the KeyEvent (necessary for actually typing characters
		QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, modifiers);
		QApplication::postEvent(QApplication::focusWidget(), event);
		event = new QKeyEvent(QEvent::KeyRelease, key, modifiers);
		QApplication::postEvent(QApplication::focusWidget(), event);
        }
#endif
}

void Texstudio::updateTexQNFA()
{
    updateTexLikeQNFA("(La)TeX", "tex.qnfa");
    updateTexLikeQNFA("Sweave", "sweave.qnfa");
    updateTexLikeQNFA("Pweave", "pweave.qnfa");
    updateUserMacros(false); //update macro triggers for languages
}

/*!
 * \brief Extends the given Language with dynamic information
 * \param languageName - the language name as specified in the language attribute of the <QNFA> tag.
 * \param filename - the filename for the language. This is just the filename without a path.
 * the file is searched for in the user language directory and as a fallback in the builtin language files.
 */
void Texstudio::updateTexLikeQNFA(QString languageName, QString filename)
{
	QLanguageFactory::LangData m_lang = m_languages->languageData(languageName);

	QFile f(configManager.configBaseDir + "languages/" + filename);
	if (!f.exists()) {
		f.setFileName(findResourceFile("qxs/" + filename));
	}
	QDomDocument doc;

    if(!f.open(QFile::ReadOnly | QFile::Text))
        return;

    doc.setContent(&f);

	// structure commands
    addStructureCommandsToDom(doc, latexParser.possibleCommands);

	QLanguageDefinition *oldLangDef = nullptr, *newLangDef = nullptr;
	oldLangDef = m_lang.d;
	Q_ASSERT(oldLangDef);

	// update editors using the language
	QNFADefinition::load(doc, &m_lang, m_formats);
    // add single line comments
    QNFADefinition *nd=dynamic_cast<QNFADefinition *>(m_lang.d);
    nd->setSingleLineComment("%");

	m_languages->addLanguage(m_lang);

	newLangDef = m_lang.d;
	Q_ASSERT(oldLangDef != newLangDef);

	if (editors) {
		documents.enablePatch(false);
        foreach (LatexDocument *doc, documents.getDocuments()) {
            LatexEditorView *edView=doc->getEditorView();
            if(edView) {
                QEditor *ed = edView->editor;
                if (ed->languageDefinition() == oldLangDef) {
                    ed->setLanguageDefinition(newLangDef);
                    // ed->highlight(); is executed by caller !
                }
            }
        }
		documents.enablePatch(true);
	}
}

void Texstudio::toggleGrammar(int type)
{
	QAction *a = qobject_cast<QAction *>(sender());
	REQUIRE(a);
	LatexEditorView::setGrammarOverlayDisabled(type, !a->isChecked());
	//a->setChecked(!a->isChecked());
	for (int i = 0; i < documents.documents.size(); i++)
		if (documents.documents[i]->getEditorView())
			documents.documents[i]->getEditorView()->updateGrammarOverlays();
}

void Texstudio::fileDiff()
{
	LatexDocument *doc = documents.currentDocument;
	if (!doc)
		return;

	//remove old markers
	removeDiffMarkers();

	QString currentDir = QDir::homePath();
	if (!configManager.lastDocument.isEmpty()) {
		QFileInfo fi(configManager.lastDocument);
		if (fi.exists() && fi.isReadable()) {
			currentDir = fi.absolutePath();
		}
	}
	QStringList files = FileDialog::getOpenFileNames(this, tr("Open Files"), currentDir, tr("LaTeX Files (*.tex);;All Files (*)"),  &selectedFileFilter);
	if (files.isEmpty())
		return;
	//
	LatexDocument *doc2 = diffLoadDocHidden(files.first());
	doc2->setObjectName("diffObejct");
	doc2->setParent(doc);
	diffDocs(doc, doc2);
	//delete doc2;

	// show changes (by calling LatexEditorView::documentContentChanged)
	LatexEditorView *edView = currentEditorView();
	edView->documentContentChanged(0, edView->document->lines());
}

void Texstudio::jumpNextDiff()
{
	QEditor *m_edit = currentEditor();
	if (!m_edit)
		return;
	QDocumentCursor c = m_edit->cursor();
	if (c.hasSelection()) {
		int l, col;
		c.endBoundary(l, col);
		c.moveTo(l, col);
	}
	LatexDocument *doc = documents.currentDocument;

	//search for next diff
	int lineNr = c.lineNumber();
	QVariant var = doc->line(lineNr).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
	if (var.isValid()) {
		DiffList lineData = var.value<DiffList>();
		for (int j = 0; j < lineData.size(); j++) {
			DiffOp op = lineData.at(j);
			if (op.start + op.length > c.columnNumber()) {
				c.moveTo(lineNr, op.start);
				c.moveTo(lineNr, op.start + op.length, QDocumentCursor::KeepAnchor);
				m_edit->setCursor(c);
				return;
			}
		}
	}
	lineNr++;


	for (; lineNr < doc->lineCount(); lineNr++) {
		var = doc->line(lineNr).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
		if (var.isValid()) {
			break;
		}
	}
	if (var.isValid()) {
		DiffList lineData = var.value<DiffList>();
		DiffOp op = lineData.first();
		c.moveTo(lineNr, op.start);
		c.moveTo(lineNr, op.start + op.length, QDocumentCursor::KeepAnchor);
		m_edit->setCursor(c);
	}
}

void Texstudio::jumpPrevDiff()
{
	QEditor *m_edit = currentEditor();
	if (!m_edit)
		return;
	QDocumentCursor c = m_edit->cursor();
	if (c.hasSelection()) {
		int l, col;
		c.beginBoundary(l, col);
		c.moveTo(l, col);
	}
	LatexDocument *doc = documents.currentDocument;

	//search for next diff
	int lineNr = c.lineNumber();
	QVariant var = doc->line(lineNr).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
	if (var.isValid()) {
		DiffList lineData = var.value<DiffList>();
		for (int j = lineData.size() - 1; j >= 0; j--) {
			DiffOp op = lineData.at(j);
			if (op.start < c.columnNumber()) {
				c.moveTo(lineNr, op.start);
				c.moveTo(lineNr, op.start + op.length, QDocumentCursor::KeepAnchor);
				m_edit->setCursor(c);
				return;
			}
		}
	}
	lineNr--;


	for (; lineNr >= 0; lineNr--) {
		var = doc->line(lineNr).getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
		if (var.isValid()) {
			break;
		}
	}
	if (var.isValid()) {
		DiffList lineData = var.value<DiffList>();
		DiffOp op = lineData.last();
		c.moveTo(lineNr, op.start);
		c.moveTo(lineNr, op.start + op.length, QDocumentCursor::KeepAnchor);
		m_edit->setCursor(c);
	}
}

void Texstudio::removeDiffMarkers(bool theirs)
{
	LatexDocument *doc = documents.currentDocument;
    if (!doc || !doc->mayHaveDiffMarkers)
		return;

	diffRemoveMarkers(doc, theirs);
	QList<QObject *>lst = doc->children();
	foreach (QObject *o, lst)
		delete o;

	LatexEditorView *edView = currentEditorView();
	edView->documentContentChanged(0, edView->document->lines());

}

void Texstudio::editChangeDiff(QPoint pt)
{
	LatexDocument *doc = documents.currentDocument;
	if (!doc)
		return;

	bool theirs = (pt.x() < 0);
	int ln = pt.x();
	if (ln < 0)
		ln = -ln - 1;
	int col = pt.y();

	diffChange(doc, ln, col, theirs);
	LatexEditorView *edView = currentEditorView();
	edView->documentContentChanged(0, edView->document->lines());
}

void Texstudio::fileDiffMerge()
{
	LatexDocument *doc = documents.currentDocument;
	if (!doc)
		return;

	diffMerge(doc);

	LatexEditorView *edView = currentEditorView();
	edView->documentContentChanged(0, edView->document->lines());
}

LatexDocument *Texstudio::diffLoadDocHidden(QString f)
{
	QString f_real = f;
#ifdef Q_OS_WIN32
	QRegExp regcheck("/([a-zA-Z]:[/\\\\].*)");
	if (regcheck.exactMatch(f)) f_real = regcheck.cap(1);
#endif

	if (!QFile::exists(f_real)) return nullptr;

	LatexDocument *doc = new LatexDocument(this);
	//LatexEditorView *edit = new LatexEditorView(0,configManager.editorConfig,doc);

	//edit->document=doc;
	//edit->document->setEditorView(edit);

	QFile file(f_real);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this, tr("Error"), tr("You do not have read permission to this file."));
        delete doc;
		return nullptr;
	}
	file.close();

	//if (edit->editor->fileInfo().suffix().toLower() != "tex")
	//	m_languages->setLanguage(edit->editor, f_real);

	//QTime time;
	//time.start();

	//edit->editor->load(f_real,QDocument::defaultCodec());
	doc->load(f_real, QDocument::defaultCodec());

	//qDebug() << "Load time: " << time.elapsed();
	//edit->editor->document()->setLineEndingDirect(edit->editor->document()->originalLineEnding());

	//edit->document->setEditorView(edit); //update file name (if document didn't exist)


	return doc;
}

void Texstudio::fileDiff3()
{
	LatexDocument *doc = documents.currentDocument;
	if (!doc)
		return;

	//remove old markers
	removeDiffMarkers();

	QString currentDir = QDir::homePath();
	if (!configManager.lastDocument.isEmpty()) {
		QFileInfo fi(configManager.lastDocument);
		if (fi.exists() && fi.isReadable()) {
			currentDir = fi.absolutePath();
		}
	}
	QStringList files = FileDialog::getOpenFileNames(this, tr("Open Compare File"), currentDir, tr("LaTeX Files (*.tex);;All Files (*)"),  &selectedFileFilter);
	if (files.isEmpty())
		return;
	QStringList basefiles = FileDialog::getOpenFileNames(this, tr("Open Base File"), currentDir, tr("LaTeX Files (*.tex);;All Files (*)"),  &selectedFileFilter);
	if (basefiles.isEmpty())
		return;
	showDiff3(files.first(), basefiles.first());
}

void Texstudio::showDiff3(const QString file1, const QString file2)
{
	LatexDocument *doc = documents.currentDocument;
	if (!doc)
		return;

	LatexDocument *doc2 = diffLoadDocHidden(file1);
	doc2->setObjectName("diffObejct");
	doc2->setParent(doc);
	LatexDocument *docBase = diffLoadDocHidden(file2);
	docBase->setObjectName("baseObejct");
	docBase->setParent(doc);
	diffDocs(doc2, docBase, true);
	diffDocs(doc, doc2);

	// show changes (by calling LatexEditorView::documentContentChanged)
	LatexEditorView *edView = currentEditorView();
	edView->documentContentChanged(0, edView->document->lines());
}

void Texstudio::declareConflictResolved()
{
	LatexDocument *doc = documents.currentDocument;
	if (!doc)
		return;

	QString fn = doc->getFileName();
	QString cmd = BuildManager::CMD_SVN;
	cmd += " resolve --accept working \"" + fn + ("\"");
	setStatusMessageProcess(QString(" svn resolve conflict "));
	QString buffer;
	runCommandNoSpecialChars(cmd, &buffer);
	checkin(fn, "txs: commit after resolve");
}
/*!
 * \brief mark svn conflict of current file resolved
 */
void Texstudio::fileInConflictShowDiff()
{
	QEditor *mEditor = qobject_cast<QEditor *>(sender());
	REQUIRE(mEditor);
	if (!QFileInfo(mEditor->fileName()).exists())  //create new qfileinfo to avoid caching
		return;
	removeDiffMarkers();

	if (!checkSVNConflicted(false)) {

		LatexDocument *doc2 = diffLoadDocHidden(mEditor->fileName());
		if (!doc2)
			return;
		LatexDocument *doc = qobject_cast<LatexDocument *>(mEditor->document());
		doc2->setObjectName("diffObejct");
		doc2->setParent(doc);
		diffDocs(doc, doc2);
		//delete doc2;

		// show changes (by calling LatexEditorView::documentContentChanged)
		LatexEditorView *edView = doc->getEditorView();
		if (edView)
			edView->documentContentChanged(0, edView->document->lines());
	}
}

bool Texstudio::checkSVNConflicted(bool substituteContents)
{
	LatexDocument *doc = documents.currentDocument;
	if (!doc)
		return false;

	QString fn = doc->getFileName();
	QFileInfo qf(fn + ".mine");
	if (qf.exists()) {
		SVN::Status status = svn.status(fn);
		if (status == SVN::InConflict) {
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
			if (ret == QMessageBox::Ok) {
				QString path = qf.absolutePath();
				QDir dir(path);
				dir.setSorting(QDir::Name);
				qf.setFile(fn);
				QString filter = qf.fileName() + ".r*";
				QFileInfoList list = dir.entryInfoList(QStringList(filter));
				QStringList lst;
				foreach (QFileInfo elem, list) {
					lst << elem.absoluteFilePath();
				}
				if (lst.count() != 2)
					return false;
				if (substituteContents) {
					QTextCodec *codec = doc->codec();
					doc->load(fn + ".mine", codec);
				}
				QString baseFile = lst.takeFirst();
				QString compFile = lst.takeFirst();
				showDiff3(compFile, baseFile);
				return true;
			}
		}
	}
	return false;
}


QThread *killAtCrashedThread = nullptr;
QThread *lastCrashedThread = nullptr;

void recover()
{
	Texstudio::recoverFromCrash();
}

void Texstudio::recoverFromCrash()
{
	bool wasLoop;
	QString backtraceFilename;
	QString name = getLastCrashInformation(wasLoop);
	if (QThread::currentThread() != QCoreApplication::instance()->thread()) {
		QThread *t = QThread::currentThread();
		lastCrashedThread = t;
		if (qobject_cast<SafeThread *>(t)) qobject_cast<SafeThread *>(t)->crashed = true;
		QTimer::singleShot(0, txsInstance, SLOT(threadCrashed()));
		while (!programStopped) {
			ThreadBreaker::sleep(1);
			if (t &&  t == killAtCrashedThread) {
                name += QString(" forced kill in %1").arg(reinterpret_cast<uintptr_t>(t), sizeof(uintptr_t) * 2, 16, QChar('0'));
                name += QString(" (TXS-Version %1 %2 )").arg(TEXSTUDIO_GIT_REVISION,COMPILED_DEBUG_OR_RELEASE);
				backtraceFilename = print_backtrace(name);
				exit(1);
			}
        }
		ThreadBreaker::forceTerminate();
		return;
	}

	static int nestedCrashes = 0;

	nestedCrashes++;

	if (nestedCrashes > 5) {
		qFatal("Forced kill after recovering failed after: %s\n", qPrintable(name));
        exit(1);
    }

	fprintf(stderr, "crashed with signal %s\n", qPrintable(name));

	if (nestedCrashes <= 2) {
        backtraceFilename = print_backtrace(name + QString(" (TXS-Version %1 %2 )").arg(TEXSTUDIO_GIT_REVISION,COMPILED_DEBUG_OR_RELEASE));
	}

	//hide editor views in case the error occured during drawing
	foreach (LatexEditorView *edView, txsInstance->editors->editors())
		edView->hide();

	//save recover information
	foreach (LatexEditorView *edView, txsInstance->editors->editors()) {
	        QEditor *ed = edView ? edView->editor : nullptr;
		if (ed && ed->isContentModified() && !ed->fileName().isEmpty())
			ed->saveEmergencyBackup(ed->fileName() + ".recover.bak~");
	}



	QMessageBox *mb = new QMessageBox();  //Don't use the standard methods like ::critical, because they load an icon, which will cause a crash again with gtk. ; mb must be on the heap, or continuing a paused loop can crash
	mb->setWindowTitle(tr("TeXstudio Emergency"));
	QString backtraceMsg;
	if (QFileInfo(backtraceFilename).exists()) {
		qDebug() << backtraceFilename;
		backtraceMsg = tr("A backtrace was written to\n%1\nPlease provide this file if you send a bug report.\n\n").arg(QDir::toNativeSeparators(backtraceFilename));
	}
	if (!wasLoop) {
        mb->setText(tr( "TeXstudio has CRASHED due to a %1.\n\n%2Do you want to keep TeXstudio running? This may cause data corruption.").arg(name,backtraceMsg));
		mb->setDefaultButton(mb->addButton(tr("Yes, try to recover"), QMessageBox::AcceptRole));
		mb->addButton(tr("No, kill the program"), QMessageBox::RejectRole); //can't use destructiverole, it always becomes rejectrole
	} else {
		mb->setText(tr( "TeXstudio has been paused due to a possible endless loop.\n\n%1Do you want to keep the program running? This may cause data corruption.").arg(backtraceMsg));
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
	mb->setFocus(); //without it, raise doesn't work. If it is in the loop (outside time checking if), the buttons can't be clicked on (windows)
    QElapsedTimer t;
	t.start();
	while (mb->isVisible()) {
		QApplication::processEvents(QEventLoop::AllEvents);
		if (t.elapsed() > 1000 ) {
			mb->raise(); //sometimes the box is not visible behind the main window (windows)
			t.restart();
		}
		ThreadBreaker::msleep(1);
	}

	//print edit history
	int i = 0;
	foreach (LatexEditorView *edView, txsInstance->editors->editors()) {
		Q_ASSERT(edView);
		if (!edView) continue;

		QFile tf(QDir::tempPath() + QString("/texstudio_undostack%1%2.txt").arg(i++).arg(edView->editor->fileInfo().completeBaseName()));
		if (tf.open(QFile::WriteOnly)) {
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
		while (true) ;
	}

	//restore editor views
	foreach (LatexEditorView *edView, txsInstance->editors->editors())
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

void Texstudio::threadCrashed()
{
	bool wasLoop;
	QString signal = getLastCrashInformation(wasLoop);
	QThread *thread = lastCrashedThread;

	QString threadName = "<unknown>";
    QString threadId = QString("%1").arg(reinterpret_cast<uintptr_t>(thread), sizeof(uintptr_t) * 2, 16, QChar('0'));
	if (qobject_cast<QThread *>(static_cast<QObject *>(thread)))
		threadName = QString("%1 %2").arg(threadId).arg(qobject_cast<QThread *>(thread)->objectName());

	fprintf(stderr, "crashed with signal %s in thread %s\n", qPrintable(signal), qPrintable(threadName));

	int btn = QMessageBox::warning(this, tr("TeXstudio Emergency"),
                                   tr("TeXstudio has CRASHED due to a %1 in thread %2.\nThe thread has been stopped.\nDo you want to keep TeXstudio running? This may cause data corruption.").arg(signal,threadId),
                                   QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    if (btn == QMessageBox::No) {
		killAtCrashedThread = thread;
		ThreadBreaker::sleep(10);
		QMessageBox::warning(this, tr("TeXstudio Emergency"), tr("I tried to die, but nothing happened."));
	}
}

void Texstudio::iamalive()
{
	Guardian::calm();
}

void Texstudio::slowOperationStarted()
{
	Guardian::instance()->slowOperationStarted();
}

void Texstudio::slowOperationEnded()
{
	Guardian::instance()->slowOperationEnded();
}
/*!
 * \brief check current latex install as it is visible from txs
 */
void Texstudio::checkLatexInstall()
{

	QString result;
	// check dpi
	double dpi=QGuiApplication::primaryScreen()->logicalDotsPerInch();
	result+=QString("dpi: %1\n").arg(dpi);
	// run pdflatex
	setStatusMessageProcess(QString("check pdflatex"));
	QString buffer;
	// create result editor here in order to avoid empty editor
	fileNew(QFileInfo(QDir::temp(), tr("System Report") + ".txt").absoluteFilePath());
	m_languages->setLanguageFromName(currentEditor(), "Plain text");

	CommandInfo cmdInfo = buildManager.getCommandInfo(BuildManager::CMD_PDFLATEX);
	QString cmd = cmdInfo.getProgramName();
	// where is pdflatex located
#ifdef Q_OS_WIN
	runCommand("where " + cmd, &buffer);
	result += "where pdflatex: " + buffer + "\n\n";
#else
	runCommand("which " + cmd, &buffer);
	result += "which pdflatex: " + buffer + "\n\n";
#endif
	buffer.clear();
	cmd += " -version";
	// run pdflatex
	runCommand(cmd, &buffer);
	result += "PDFLATEX: " + cmd + "\n";
	result += buffer;
	result += "\n\n";
	// check env
	result += "Environment variables:\n";
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
	result += buffer + "\n";

	result += "\nTeXstudio:\n";
	result += "Path        : " + QDir::toNativeSeparators(QCoreApplication::applicationFilePath()) + "\n";
	result += "Program call: " + QCoreApplication::arguments().join(" ") + "\n";
	result += "Setting file: " + QDir::toNativeSeparators(configManager.configFileName) + "\n";

	result += "\nCommand configuration in TeXstudio:\n";
	const CommandMapping &cmds = buildManager.getAllCommands();
	foreach (const CommandInfo &ci, cmds)
		result += QString("    %1 (%2)%3: %4\n").arg(ci.displayName).arg(ci.id).arg(ci.rerunCompiler ? " (r)" : "").arg(ci.commandLine);

	result += "\nAdditional Search Paths:\n";
	result += "    Command: " + buildManager.additionalSearchPaths + "\n";
	result += "    Log: " + buildManager.additionalLogPaths + "\n";
	result += "    Pdf: " + buildManager.additionalPdfPaths + "\n";

	//fileNew(QFileInfo(QDir::temp(), tr("System Report") + ".txt").absoluteFilePath());
	//m_languages->setLanguageFromName(currentEditor(), "Plain text");
	currentEditorView()->editor->setText(result, false);
}
/*!
 * \brief display which cwls are loaded.
 *
 * This function is for debugging.
 */
void Texstudio::checkCWLs()
{
	bool newFile = currentEditor();
	if (!newFile) fileNew();

	QList<LatexDocument *> docs = currentEditorView()->document->getListOfDocs();
	QStringList res;
	QSet<QString> cwls;
	// collect user commands and references
	foreach (LatexDocument *doc, docs) {
		const QSet<QString> &cwl = doc->getCWLFiles();
		cwls.unite(cwl);
        res << doc->getFileName() + ": " + QStringList(cwl.values()).join(", ");
		QList<CodeSnippet> users = doc->userCommandList();
		if (!users.isEmpty()) {
			QString line = QString("\t%1 user commands: ").arg(users.size());
			foreach (const CodeSnippet & cs, users) line += (line.isEmpty() ? "" : "; ") + cs.word;
			res << line;
		}
	}
    cwls.unite(convertStringListtoSet(configManager.completerConfig->getLoadedFiles()));
	res << "global: " << configManager.completerConfig->getLoadedFiles().join(", ");

	res << "" << "";

	foreach (QString s, cwls) {
		res << QString("------------------- Package %1: ---------------------").arg(s);
		LatexPackage package;
        int p=s.indexOf('#');
        if(p>-1 && !documents.cachedPackages.contains(s)){
            s=s.mid(p+1);
        }
		if (!documents.cachedPackages.contains(s)) {
			res << "Package not cached (normal for global packages)";
			package = loadCwlFile(s);
		} else package = documents.cachedPackages.value(s);

		res << "\tpossible commands";
		foreach (const QString &key, package.possibleCommands.keys())
            res << QString("\t\t%1: %2").arg(key).arg(QStringList(package.possibleCommands.value(key).values()).join(", "));
		res << "\tspecial def commands";
		foreach (const QString &key, package.specialDefCommands.keys())
			res << QString("\t\t%1: %2").arg(key).arg(package.specialDefCommands.value(key));
		res << "\tspecial treatment commands";
		foreach (const QString &key, package.specialDefCommands.keys()) {
			QString line = QString("\t\t%1: ").arg(key);
			foreach (const QPairQStringInt &pair, package.specialTreatmentCommands.value(key))
				line += QString("%1 (%2)").arg(pair.first).arg(pair.second) + ", ";
			line.chop(2);
			res << line;
		}
        res << QString("\toption Commands: %1").arg(QStringList(package.optionCommands.values()).join(", "));
		QString line = QString("\tkinds: ");
		foreach (const QString &key, package.commandDescriptions.keys()) {
			const CommandDescription &cmd = package.commandDescriptions.value(key);
			line += key + "(" + cmd.toDebugString() + "), ";
		}
		line.chop(2);
		res << line;
		line = QString("\tall commands: ");
		foreach (const CodeSnippet & cs, package.completionWords) line += (line.isEmpty() ? "" : "; ") + cs.word;
		res << line;
		res << "" << "";
	}

	if (newFile) fileNew();
	m_languages->setLanguageFromName(currentEditor(), "Plain text");
	currentEditorView()->editor->setText(res.join("\n"), false);

}
/*!
 * \brief check if Language tool is set-up correctly and running
 */
void Texstudio::checkLanguageTool()
{

    QString result;
    // run java
    setStatusMessageProcess(QString("check java"));
    QString buffer;
    // create result editor here in order to avoid empty editor
    fileNew(QFileInfo(QDir::temp(), tr("LT Report") + ".txt").absoluteFilePath());
    m_languages->setLanguageFromName(currentEditor(), "Plain text");

    QString cmd=configManager.grammarCheckerConfig->languageToolJavaPath;

    // where is pdflatex located
#ifdef Q_OS_WIN
    runCommand("where " + quoteSpaces(cmd), &buffer);
    result = "where java: " + buffer + "\n\n";
#else
    runCommand("which " + quoteSpaces(cmd), &buffer);
    result = "which java: " + buffer + "\n\n";
#endif
    buffer.clear();
    // run pdflatex
    QProcess *javaProcess = new QProcess();

    result += "JAVA: " + cmd + "\n";
    javaProcess->start(cmd,QStringList("-version"));
    javaProcess->waitForFinished(500);
    int code=javaProcess->exitCode();
    switch (code) {
    case 0:
        buffer=javaProcess->readAllStandardError();
        break;
    case -2:
        buffer+=tr("process failed to start\n");
        break;
    default:
        buffer+=tr("process crashed\n");
        break;
    }

    delete javaProcess;

    result += buffer;
    result += "\n";

    if (configManager.editorConfig->realtimeChecking){
        result +=tr("Real-time checking is enabled.\n");
    }else{
        result +=tr("Real-time checking is disabled!!!\n");
    }
    if(configManager.editorConfig->inlineGrammarChecking) {
        result +=tr("Grammar checking is enabled.\n\n");
    }else{
        result +=tr("Grammar checking is disabled!!!\n\n");
    }
    if(configManager.grammarCheckerConfig->languageToolAutorun){
        result +=tr("Tries to start automatically.\n\n");
    }else{
        result +=tr("Autostart disabled.\n\n");
    }

    GrammarCheck::LTStatus st=grammarCheck->languageToolStatus();

    result +=tr("LT current status: ");
    switch (st) {
    case GrammarCheck::LTS_Working:
        result +=tr("working");
        break;
    case GrammarCheck::LTS_Error:
        result +=tr("error");
        result +="\n"+grammarCheck->getLastErrorMessage();
        break;
    case GrammarCheck::LTS_Unknown:
        result +=tr("unknown");
    }
    result += "\n\n";
    result +=tr("LT-URL: %1\n").arg(grammarCheck->serverUrl());

    currentEditorView()->editor->setText(result, false);
}
/*!
 * \brief load document hidden
 *
 * when parsing a document, child-documents can be loaded automatically.
 * They are loaded here into the hidden state.
 * \param filename
 */
void Texstudio::addDocToLoad(QString filename)
{
	//qDebug()<<"fname:"<<filename;
	if (filename.isEmpty())
		return;
	load(filename, false, true, recheckLabels);
}

/*!
 * \brief open pdf documentation of latex packages in the internal viewer
 * \param package package name
 * \param command latex command to search within that documentation
 */
void Texstudio::openInternalDocViewer(QString package, const QString command)
{
#ifndef NO_POPPLER_PREVIEW
	runInternalCommand("txs:///view-pdf-internal", QFileInfo(package), "--embedded");
	QList<PDFDocument *> pdfs = PDFDocument::documentList();
	if (pdfs.count() > 0) {
		pdfs[0]->raise();
		PDFDocument *pdf = pdfs.first();
		pdf->goToPage(0);
		pdf->doFindDialog(command);
		if (!command.isEmpty())
			pdf->search(command, false, false, false, false, false);
	}
#else
	Q_UNUSED(package)
	Q_UNUSED(command)
#endif
}
/*!
 * \brief close a latex environment
 *
 * If the cursor is after a \begin{env} which is not closed by the end of the document, \end{env} is inserted.
 *
 * This function uses information which is generated by the syntax checker.
 * As the syntaxchecker works asynchronously, a small delay between typing and functioning of this action is mandatory though that delay is probably too small for any user to notice.
 */
void Texstudio::closeEnvironment()
{
	LatexEditorView *edView = currentEditorView();
	if (!edView)
		return;
	QEditor *m_edit = currentEditor();
	if (!m_edit)
		return;
	QDocumentCursor cursor = m_edit->cursor();

	// handle current line -- based on text parsing of current line
	// the below method is not exact and will fail on certain edge cases
	// for the time being this is good enough. An alternative approach may use the token system:
	//   QDocumentLineHandle *dlh = edView->document->line(cursor.lineNumber()).handle();
    //   TokenList tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
	if (cursor.columnNumber() > 0) {
		QString text = cursor.line().text();
        QRegularExpression rxBegin = QRegularExpression("\\\\begin\\{([^}]+)\\}");
        QRegularExpressionMatch match;
        int beginCol = text.lastIndexOf(rxBegin, cursor.columnNumber()-1,&match);
		while (beginCol >= 0) {
			QDocumentCursor from, to;
			QDocumentCursor c = cursor.clone(false);
			c.setColumnNumber(beginCol);
			c.getMatchingPair(from, to);
            QString endText = "\\end{" + match.captured(1) + "}";
			if (!to.isValid() || to.selectedText() != endText) {
				cursor.insertText(endText);
				return;
			}
			beginCol -= 6;
			if (beginCol < 0) break;
			beginCol = text.lastIndexOf(rxBegin, beginCol);
		}
	}

	// handle previous lines -- based on StackEnvironment / syntax checker
	// This only works on a succeding line of the \begin{env} statement, not in the same line.
	// Therefore the above separate handling of the current line.
	StackEnvironment env;
	LatexDocument *doc = edView->document;
	doc->getEnv(cursor.lineNumber(), env);
	int lineCount = doc->lineCount();
	if (lineCount < 1)
		return;
	StackEnvironment env_end;
	QDocumentLineHandle *dlh = edView->document->line(lineCount - 1).handle();
    QVariant envVar = dlh->getCookieLocked(QDocumentLine::STACK_ENVIRONMENT_COOKIE);
	if (envVar.isValid())
		env_end = envVar.value<StackEnvironment>();
	else
		return;

	if (env.count() > 0 && env_end.count() > 0) {
		Environment mostRecentEnv = env.pop();
		while (!env_end.isEmpty()) {
			Environment e = env_end.pop();
			if (env_end.isEmpty()) // last env is for internal use only
				break;
			if (e == mostRecentEnv) { // found, now close it
				QString txt;
				if (e.origName.isEmpty()) {
					txt = "\\end{" + e.name + "}";
				} else {
					txt = e.origName;
					int i = latexParser.mathStartCommands.indexOf(txt);
					txt = latexParser.mathStopCommands.value(i);
				}
				m_edit->insertText(txt);
				break;
			}
		}
	}
}




/*!
 * \brief make embedded viewer larger so that it covers the text edit
 * If the viewer is not embedded, no action is performed.
 */
void Texstudio::enlargeEmbeddedPDFViewer()
{
#ifndef NO_POPPLER_PREVIEW
	QList<PDFDocument *> oldPDFs = PDFDocument::documentList();
	if (oldPDFs.isEmpty())
		return;
	PDFDocument *viewer = oldPDFs.first();
	if (!viewer->embeddedMode)
		return;
	sidePanelSplitter->hide();
	configManager.viewerEnlarged = true;
	PDFDocumentConfig *pdfConfig=configManager.pdfDocumentConfig;
	if(!enlargedViewer){
		rememberFollowFromScroll=pdfConfig->followFromScroll;
	}
	enlargedViewer=true;
	pdfConfig->followFromScroll=false;
	viewer->setStateEnlarged(true);
#endif
}
/*!
 * \brief set size of embedded viewer back to previous value
 * \param preserveConfig note change in config
 */
void Texstudio::shrinkEmbeddedPDFViewer(bool preserveConfig)
{
#ifndef NO_POPPLER_PREVIEW
	sidePanelSplitter->show();
	if (!preserveConfig)
		configManager.viewerEnlarged = false;
	QList<PDFDocument *> oldPDFs = PDFDocument::documentList();
	if (oldPDFs.isEmpty())
		return;
	PDFDocument *viewer = oldPDFs.first();
	if (!viewer->embeddedMode)
		return;
	if(enlargedViewer){
		PDFDocumentConfig *pdfConfig=configManager.pdfDocumentConfig;
		pdfConfig->followFromScroll=rememberFollowFromScroll;
		enlargedViewer=false;
	}
	viewer->setStateEnlarged(false);
#else
	Q_UNUSED(preserveConfig)
#endif
}

void Texstudio::showStatusbar()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (act) {
		statusBar()->setVisible(act->isChecked());
		configManager.setOption("View/ShowStatusbar", act->isChecked());
	}
}
/*!
 * \brief open extended search in bottom panel
 *
 * This is called from the editor search panel by pressing '+'.
 */
void Texstudio::showExtendedSearch()
{
	LatexEditorView *edView = currentEditorView();
	if (!edView) return;

	bool isWord = edView->getSearchIsWords();
	bool isCase = edView->getSearchIsCase();
	bool isReg = edView->getSearchIsRegExp();
	SearchQuery *query = new SearchQuery(edView->getSearchText(), edView->getReplaceText(), isCase, isWord, isReg);
	query->setScope(searchResultWidget()->searchScope());
	searchResultWidget()->setQuery(query);
	outputView->showPage(outputView->SEARCH_RESULT_PAGE);
	runSearch(query);
}
/*!
 * \brief change icon size of toolbars
 *
 * This is intended to have larger symbols on high-resolution screens.
 * The change is instantly performed from the config dialog as visual feed-back.
 * \param value size in points
 */
void Texstudio::changeIconSize(int value)
{
	// adapt icon size to dpi
	double dpi=QGuiApplication::primaryScreen()->logicalDotsPerInch();
	double scale=dpi/96;

	int iconWidth=qRound(value*scale);

	setIconSize(QSize(iconWidth, iconWidth));
#ifndef NO_POPPLER_PREVIEW
	foreach (PDFDocument *pdfviewer, PDFDocument::documentList()) {
		if (!pdfviewer->embeddedMode) pdfviewer->setToolbarIconSize(iconWidth);
	}
#endif
}
/*!
 * \brief change icon size for central tool-bar
 *
 * This is intended to have larger symbols on high-resolution screens.
 * The change is instantly performed from the config dialog as visual feed-back.
 * \param value size in points
 */
void Texstudio::changeSecondaryIconSize(int value)
{
	// adapt icon size to dpi
	double dpi=QGuiApplication::primaryScreen()->logicalDotsPerInch();
	double scale=dpi/96;

	int iconWidth=qRound(value*scale);

	centralToolBar->setIconSize(QSize(iconWidth, iconWidth));
	leftPanel->setToolbarIconSize(iconWidth);

	foreach (QObject *c, statusBar()->children()) {
		QAbstractButton *bt = qobject_cast<QAbstractButton *>(c);
		if (bt) {
			bt->setIconSize(QSize(iconWidth, iconWidth));
		}
	}
}
/*!
 * \brief change icon size of embbedded pdf viewer toolbar
 * \param value
 */
void Texstudio::changePDFIconSize(int value){
    // adapt icon size to dpi
    double dpi=QGuiApplication::primaryScreen()->logicalDotsPerInch();
    double scale=dpi/96;

    int iconWidth=qRound(value*scale);

#ifndef NO_POPPLER_PREVIEW
        foreach (PDFDocument *pdfviewer, PDFDocument::documentList()) {
                if (pdfviewer->embeddedMode) pdfviewer->setToolbarIconSize(iconWidth);
        }
#endif
}
/*!
 * \brief change symbol grid icon size
 *
 * This is intended to have larger symbols on high-resolution screens.
 * The change is instantly performed from the config dialog as visual feed-back.
 * \param value size in points
 * \param changePanel change to a symbolgrid in sidepanel in order to make the change directly visible
 */
void Texstudio::changeSymbolGridIconSize(int value, bool changePanel)
{
	// adapt icon size to dpi
	double dpi=QGuiApplication::primaryScreen()->logicalDotsPerInch();
	double scale=dpi/96;

	int iconWidth=qRound(value*scale);

	if (changePanel) {
		QWidget *sympanel = leftPanel->widget("symbols");
		if ( !leftPanel->hiddenWidgets().split("|").contains(sympanel->property("id").toString()) ) {
			leftPanel->setCurrentWidget(sympanel);
			emit leftPanel->titleChanged(sympanel->property("Name").toString());
		}
	}
	symbolWidget->setSymbolSize(iconWidth);
}
/*!
 * \brief displays error messages from network replies which are used to communicate with LT
 * \param message
 */

void Texstudio::LTErrorMessage(QString message){
	// adapt icon size to dpi
	double dpi=QGuiApplication::primaryScreen()->logicalDotsPerInch();
	double scale=dpi/96;

	int iconWidth=qRound(configManager.guiSecondaryToolbarIconSize*scale);

	QIcon icon = getRealIconCached("languagetool");
	QSize iconSize = QSize(iconWidth, iconWidth);
	statusLabelLanguageTool->setPixmap(icon.pixmap(iconSize, QIcon::Disabled));
	statusLabelLanguageTool->setToolTip(QString(tr("Error when communicating with LT: %1")).arg(message));
}

/*!
 * \brief react to changed palette
 * i.e. change form light- to dark-mode and vice-versa
 * \param palette new palette
 */
void Texstudio::paletteChanged(const QPalette &palette){
    bool oldDarkMode=darkMode;
    bool newDarkMode=configManager.systemUsesDarkMode(palette);
    if(newDarkMode != oldDarkMode){
        if(!configManager.useTexmakerPalette){
            darkMode=newDarkMode;
            // load appropriate syntax highlighting scheme
            QSettings *config=configManager.getSettings();
            config->beginGroup(darkMode ? "formatsDark" : "formats");
            m_formats = new QFormatFactory(darkMode ? ":/qxs/defaultFormatsDark.qxf" : ":/qxs/defaultFormats.qxf", this); //load default formats from resource file
            m_formats->load(*config, true); //load customized formats
            QDocument::setDefaultFormatScheme(m_formats);
            //m_formats->modified=true;
            config->endGroup();
        }
        setupMenus(); // reload actions for new icons !
        setupDockWidgets();
        setStructureSectionIcons();
        updateStatusBarIcons();
        updateAllTOCs();
        updatePDFIcons();
    }
    foreach (LatexEditorView *edView, editors->editors()) {
        QEditor *ed = edView->editor;
        edView->updatePalette(palette);
        ed->document()->markFormatCacheDirty();
        ed->update();
        QSearchReplacePanel *searchpanel = qobject_cast<QSearchReplacePanel *>(edView->codeeditor->panels("Search")[0]);
        searchpanel->updateIcon();
    }
}

#if (QT_VERSION >= 0x060500) && (defined( Q_OS_WIN )||defined( Q_OS_LINUX ))
/*!
 * \brief react to changed palette
 * i.e. change form light- to dark-mode and vice-versa
 * \param palette new palette
 */
void Texstudio::colorSchemeChanged(Qt::ColorScheme colorScheme)
{
    // only style Fusion & Windows support autochange
    if(configManager.interfaceStyle!="Fusion" && configManager.interfaceStyle!="Windows") return;
    bool oldDarkMode=darkMode;
    bool newDarkMode=(colorScheme == Qt::ColorScheme::Dark);
    if(newDarkMode != oldDarkMode){
        if(!configManager.useTexmakerPalette){
            darkMode=newDarkMode;
            // load appropriate syntax highlighting scheme
            QSettings *config=configManager.getSettings();
            config->beginGroup(darkMode ? "formatsDark" : "formats");
            m_formats = new QFormatFactory(darkMode ? ":/qxs/defaultFormatsDark.qxf" : ":/qxs/defaultFormats.qxf", this); //load default formats from resource file
            m_formats->load(*config, true); //load customized formats
            QDocument::setDefaultFormatScheme(m_formats);
            //m_formats->modified=true;
            config->endGroup();
        }
        setupMenus(); // reload actions for new icons !
        setupDockWidgets();
        setStructureSectionIcons();
        updateStatusBarIcons();
        updateAllTOCs();
        updatePDFIcons();
    }
    foreach (LatexEditorView *edView, editors->editors()) {
        QEditor *ed = edView->editor;
        //edView->updatePalette(palette); // adapt ?
        ed->document()->markFormatCacheDirty();
        ed->update();
        QSearchReplacePanel *searchpanel = qobject_cast<QSearchReplacePanel *>(edView->codeeditor->panels("Search")[0]);
        searchpanel->updateIcon();
    }
}
#endif
/*!
 * \brief open webpage with txs issue submit
 */
void Texstudio::openBugsAndFeatures() {
	QDesktopServices::openUrl(QUrl("https://github.com/texstudio-org/texstudio/issues/"));
}
/*!
    \brief call updateTOC & updateStructureLocally as only one call works with a signal
 */
void Texstudio::updateTOCs(){
    updateTOC();
    updateStructureLocally();
}

/*!
 * \brief update global TOC and *all* local structure view
 * Otherwise only current doc is updated
 */
void Texstudio::updateAllTOCs()
{
    updateTOC();
    updateStructureLocally(true);
}

/*!
 * \brief Collect structure info from all subfiles and create a toplevel TOC
 *
 */
void Texstudio::updateTOC(){
    if(!topTOCTreeWidget->isVisible()) return; // don't update if TOC is not shown, save unnecessary effort
    QTreeWidgetItem *root=topTOCTreeWidget->topLevelItem(0);
    StructureEntry *selectedEntry=nullptr;
    bool itemExpanded=false;
    if(!root){
        root=new QTreeWidgetItem();
    }else{
        // get current selected item, check only first and deduce structureEntry
        QList<QTreeWidgetItem*> selected=topTOCTreeWidget->selectedItems();
        if(!selected.isEmpty()){
            QTreeWidgetItem *item=selected.first();
            if(item){
                selectedEntry = item->data(0,Qt::UserRole).value<StructureEntry *>();
            }
        }
        // remove all item in topTOC but keep itemTODO
        QTreeWidgetItem *itemTODO=root->child(0);
        if(itemTODO && itemTODO->data(0,Qt::UserRole+1).toString()=="TODO"){
            itemExpanded=itemTODO->isExpanded();
        }
        QList<QTreeWidgetItem*> items=root->takeChildren();
        qDeleteAll(items);
    }
    QVector<QTreeWidgetItem *>rootVector(latexParser.MAX_STRUCTURE_LEVEL,root);
    // fill TOC, starting by current master/top
    LatexDocument *doc=documents.getRootDocumentForDoc();
    if(!doc){
        // no root document
        // clear TOC completely
        topTOCTreeWidget->clear();
        return;
    }
    root->setText(0,doc->getFileInfo().fileName());

    StructureEntry *base=doc->baseStructure;
    QList<QTreeWidgetItem*> todoList;
    parseStruct(base,rootVector,nullptr,&todoList);
    topTOCTreeWidget->insertTopLevelItem(0,root);
    if(!todoList.isEmpty()){
        QTreeWidgetItem *itemTODO=new QTreeWidgetItem();
        itemTODO->setText(0,tr("TODO"));
        itemTODO->setData(0,Qt::UserRole+1,"TODO");
        itemTODO->insertChildren(0,todoList);
        root->insertChild(0,itemTODO);
        itemTODO->setExpanded(itemExpanded);
    }
    root->setExpanded(true);
    root->setSelected(false);
    updateCurrentPosInTOC(nullptr,nullptr,selectedEntry);
}
/*!
 * \brief update marking of current position in global TOC
 *
 * Works recursively.
 * \param root nullptr at the start, treewidgetitem of which the children need to be checked later.
 * \param old  previously marked section of which the mark needs to be removed
 * \param selected  selected section
 */
void Texstudio::updateCurrentPosInTOC(QTreeWidgetItem* root, StructureEntry *old, StructureEntry *selected)
{
    if(!topTOCTreeWidget->isVisible() && !structureTreeWidget->isVisible()) return; // don't update if TOC is not shown, save unnecessary effort
    const QColor activeItemColor(UtilsUi::mediumLightColor(QPalette().color(QPalette::Highlight), 75));
    bool tocMode=topTOCTreeWidget->isVisible();
    if(!root){
        if(topTOCTreeWidget->isVisible()){
            root=topTOCTreeWidget->topLevelItem(0);
        }else{
            root=nullptr;
            for(int i=0;i<structureTreeWidget->topLevelItemCount();++i){
                QTreeWidgetItem* item=structureTreeWidget->topLevelItem(i);
                StructureEntry *se = item->data(0,Qt::UserRole).value<StructureEntry *>();
                if(old && old->document!=documents.getCurrentDocument() && se->document==old->document){
                    // remove cursor mark from structureView of not current document (after document switch)
                    updateCurrentPosInTOC(item,old);
                    if(root)
                        break; // no need to search further
                }
                if(se->document == documents.getCurrentDocument()){
                    root=item;
                }
            }
        }
    }
    if(!root) return;
    for(int i=0;i<root->childCount();++i){
        QTreeWidgetItem *item=root->child(i);
        StructureEntry *se = item->data(0,Qt::UserRole).value<StructureEntry *>();
        if(selected && selected==se){
            item->setSelected(true);
        }
        if(old && se==old){
            bool hasColor=item->data(0,Qt::UserRole+1).isValid();
            QBrush bck=item->data(0,Qt::UserRole+1).value<QBrush>();
            if(tocMode || hasColor){
                item->setBackground(0,bck);
            }else{
                item->setBackground(0,palette().brush(QPalette::Base));
            }
        }
        if(currentSection && (se==currentSection)){
            item->setData(0,Qt::UserRole+1,item->background(0));
            item->setBackground(0,activeItemColor);
            if (!mDontScrollToItem && configManager.structureScrollToCurrentPosition){
                if(tocMode){
                    topTOCTreeWidget->scrollToItem(item);
                }else{
                    structureTreeWidget->scrollToItem(item);
                }
            }
        }
        updateCurrentPosInTOC(item,old);
    }
}
/*!
 * \brief parse children of a structure entry se to collect TOC data
 * \param se
 * \param rootVector
 * \return section elements found (true/false)
 */
bool Texstudio::parseStruct(StructureEntry* se, QVector<QTreeWidgetItem *> &rootVector, QSet<LatexDocument*> *visited,QList<QTreeWidgetItem*> *todoList,int currentColor) {
    bool elementsAdded=false;
    bool deleteVisitedDocs=false;
    if (!visited) {
        visited = new QSet<LatexDocument *>();
        deleteVisitedDocs = true;
    }
    QColor colors[6];
    const char nrColors=6;
    if(darkMode){
        for(int i=0;i<nrColors;++i){
            if(configManager.globalTOCbackgroundOptions==1){
                int hue=140;
                colors[i]=QColor::fromHsv(i%2==0 ? hue:hue+30,240-60*(i/2),180);
            }else{
                int hue=240;
                colors[i]=QColor::fromHsv(i%2==0 ? hue:hue-30,240-30*(i/2),120);
            }
        }
    }else{
        for(int i=0;i<nrColors;++i){
            int hue=configManager.globalTOCbackgroundOptions==1 ? 140 : 240;
            colors[i]=QColor::fromHsv(i%2==0 ? hue:hue-30,70-35*(i/2),240);
        }
    }

    char offset=0;
    QString docName=se->document->getName();
    foreach(StructureEntry* elem,se->children){
        if(todoList && (elem->type == StructureEntry::SE_OVERVIEW)&&(elem->title=="TODO")){
            parseStruct(elem,rootVector,visited,todoList);
        }
        if(todoList && (elem->type == StructureEntry::SE_TODO)){
            QTreeWidgetItem * item=new QTreeWidgetItem();
            item->setData(0,Qt::UserRole,QVariant::fromValue<StructureEntry *>(elem));
            item->setText(0,elem->title);
            item->setToolTip(0,tr("Document: ")+docName);
            todoList->append(item);
        }
        if(elem->type == StructureEntry::SE_SECTION){
            QTreeWidgetItem * item=new QTreeWidgetItem();
            item->setData(0,Qt::UserRole,QVariant::fromValue<StructureEntry *>(elem));
            elementsAdded=true;
            item->setText(0,elem->title);
            item->setToolTip(0,tr("Document: ")+docName);
            item->setIcon(0,iconSection.value(elem->level));
            if(configManager.globalTOCbackgroundOptions>0){
                item->setBackground(0,colors[currentColor]);
            }
            rootVector[elem->level]->addChild(item);
            item->setExpanded(elem->expanded);
            // fill rootVector with item for subsequent lower level elements (which are children of item then)
            for(int i=elem->level+1;i<latexParser.MAX_STRUCTURE_LEVEL;i++){
                rootVector[i]=item;
            }
            parseStruct(elem,rootVector,visited,todoList,currentColor);
        }
        if(elem->type == StructureEntry::SE_INCLUDE){
            LatexDocument *doc=elem->document;
            //QString fn=ensureTrailingDirSeparator(doc->getRootDocument()->getFileInfo().absolutePath())+elem->title;
            QFileInfo fi(doc->getRootDocument()->getFileInfo().absolutePath(),elem->title);
            doc=documents.findDocumentFromName(fi.absoluteFilePath());
            if(!doc){
                doc=documents.findDocumentFromName(fi.absoluteFilePath()+".tex");
            }
            bool ea=false;
            if(doc &&!visited->contains(doc)){
                visited->insert(doc);
                ea=parseStruct(doc->baseStructure,rootVector,visited,todoList,(currentColor+1+offset)%nrColors);
            }
            if(!ea){
                QTreeWidgetItem * item=new QTreeWidgetItem();
                item->setData(0,Qt::UserRole,QVariant::fromValue<StructureEntry *>(elem));
                item->setText(0,elem->title);
                item->setToolTip(0,tr("Document: ")+docName);
                item->setIcon(0,getRealIcon("include"));
                if(configManager.globalTOCbackgroundOptions>0){
                    item->setBackground(0,colors[currentColor]);
                }
                rootVector[latexParser.MAX_STRUCTURE_LEVEL-1]->addChild(item);
            }else{
                offset=(offset+1)&1; //toggle between 0 & 1
            }
            elementsAdded=true;
        }
    }
    if(deleteVisitedDocs){
        delete visited;
        visited=nullptr;
    }
    return elementsAdded;
}
/*!
 * \brief sync expanded state to structure entry
 * \param item
 */
void Texstudio::syncExpanded(QTreeWidgetItem *item){
    StructureEntry *se=item->data(0,Qt::UserRole).value<StructureEntry *>();
    if(!se) return;
    se->expanded=true;
}

/*!
 * \brief sync collapsed state to structure entry
 * \param item
 */
void Texstudio::syncCollapsed(QTreeWidgetItem *item){
    StructureEntry *se=item->data(0,Qt::UserRole).value<StructureEntry *>();
    if(!se) return;
    se->expanded=false;
}



/*!
 * \brief custom context menu for structureWidget
 * \param pos mouse position when clicked
 */
void Texstudio::customMenuStructure(const QPoint &pos){
    QTreeWidget* w = structureTreeWidget->isVisible() ? structureTreeWidget : topTOCTreeWidget ;
    QTreeWidgetItem *item = w->itemAt(pos);
    if(!item) return;
    StructureEntry *contextEntry = item->data(0,Qt::UserRole).value<StructureEntry *>();
    if (!contextEntry) return;
    if (contextEntry->type == StructureEntry::SE_DOCUMENT_ROOT) {
        QMenu menu;
        if (contextEntry->document != documents.masterDocument) {
            menu.addAction(tr("Close document"), this, SLOT(closeDocument()))->setData(QVariant::fromValue<LatexDocument *>(contextEntry->document));
            menu.addAction(tr("Set as explicit root document"), this, SLOT(toggleMasterDocument()))->setData(QVariant::fromValue<LatexDocument *>(contextEntry->document));
            menu.addAction(tr("Open all related documents"), this, SLOT(openAllRelatedDocuments()))->setData(QVariant::fromValue<LatexDocument *>(contextEntry->document));
            menu.addAction(tr("Close all related documents"), this, SLOT(closeAllRelatedDocuments()))->setData(QVariant::fromValue<LatexDocument *>(contextEntry->document));
        } else
            menu.addAction(tr("Remove explicit root document role"), this, SLOT(toggleMasterDocument()))->setData(QVariant::fromValue<LatexDocument *>(contextEntry->document));
        if (configManager.structureShowSingleDoc) {
            menu.addAction(tr("Show all open documents in this tree"), this, SLOT(toggleSingleDocMode()));
        } else {
            menu.addAction(tr("Show only current document in this tree"), this, SLOT(toggleSingleDocMode()));
        }
        /*menu.addSeparator();
        menu.addAction(tr("Move document to &front"), this, SLOT(moveDocumentToFront()))->setData(QVariant::fromValue<LatexDocument *>(contextEntry->document));
        menu.addAction(tr("Move document to &end"), this, SLOT(moveDocumentToEnd()))->setData(QVariant::fromValue<LatexDocument *>(contextEntry->document));
        */
		menu.addSeparator();
        menu.addAction(tr("Expand Subitems"), this, SLOT(expandSubitems()));
        menu.addAction(tr("Collapse Subitems"), this, SLOT(collapseSubitems()));
        /*menu.addAction(tr("Expand all documents"), this, SLOT(expandAllDocuments()));
        menu.addAction(tr("Collapse all documents"), this, SLOT(collapseAllDocuments()));
		*/
        menu.addSeparator();
        menu.addAction(tr("Copy filename"), this, SLOT(copyFileName()))->setData(QVariant::fromValue<LatexDocument *>(contextEntry->document));
        menu.addAction(tr("Copy file path"), this, SLOT(copyFilePath()))->setData(QVariant::fromValue<LatexDocument *>(contextEntry->document));
        menu.addAction(msgGraphicalShellAction(), this, SLOT(showInGraphicalShell_()))->setData(QVariant::fromValue<LatexDocument *>(contextEntry->document));
        menu.exec(w->mapToGlobal(pos));
        return;
    }
    if (contextEntry->type == StructureEntry::SE_LABEL) {
        QMenu menu;
        menu.addAction(tr("Insert"), this, SLOT(insertTextFromAction()))->setData(contextEntry->title);
        menu.addAction(tr("Insert as %1").arg("\\ref{...}"), this, SLOT(insertTextFromAction()))->setData(QString("\\ref{%1}").arg(contextEntry->title));
        menu.addAction(tr("Insert as %1").arg("\\pageref{...}"), this, SLOT(insertTextFromAction()))->setData(QString("\\pageref{%1}").arg(contextEntry->title));
        menu.addSeparator();
        QAction *act = menu.addAction(tr("Find Usages"), this, SLOT(findLabelUsagesFromAction()));
        act->setData(contextEntry->title);
        act->setProperty("doc", QVariant::fromValue<LatexDocument *>(contextEntry->document));
        menu.exec(w->mapToGlobal(pos));
        return;
    }
    if (contextEntry->type == StructureEntry::SE_SECTION) {
        QMenu menu(this);

        StructureEntry *labelEntry = labelForStructureEntry(contextEntry);
        if (labelEntry) {
            menu.addAction(tr("Insert Label"), this, SLOT(insertTextFromAction()))->setData(labelEntry->title); // a bit indirect approach, the code should be refactored ...
            foreach (QString refCmd, configManager.referenceCommandsInContextMenu.split(",")) {
                refCmd = refCmd.trimmed();
                if (!refCmd.startsWith('\\')) continue;
                menu.addAction(QString(tr("Insert %1 to Label", "autoreplaced, e.g.: Insert \\ref to Label").arg(refCmd)), this, SLOT(insertTextFromAction()))->setData(QString("%1{%2}").arg(refCmd).arg(labelEntry->title));
            }
            menu.addSeparator();
        } else {
            menu.addAction(tr("Create Label"), this, SLOT(createLabelFromAction()))->setData(QVariant::fromValue(contextEntry));
            menu.addSeparator();
        }

        menu.addAction(tr("Cut"), this, SLOT(editSectionCut()));
        menu.addAction(tr("Copy"), this, SLOT(editSectionCopy()));
        menu.addAction(tr("Paste Before"), this, SLOT(editSectionPasteBefore()));
        menu.addAction(tr("Paste After"), this, SLOT(editSectionPasteAfter()));
        menu.addSeparator();
        menu.addAction(tr("Indent Section"), this, SLOT(editIndentSection()));
        menu.addAction(tr("Unindent Section"), this, SLOT(editUnIndentSection()));
        if (!contextEntry->children.isEmpty()) {
            menu.addSeparator();
            menu.addAction(tr("Expand Subitems"), this, SLOT(expandSubitems()));
            menu.addAction(tr("Collapse Subitems"), this, SLOT(collapseSubitems()));
        }

        menu.exec(w->mapToGlobal(pos));
        return;
    }
    if (contextEntry->type == StructureEntry::SE_INCLUDE) {
        QMenu menu;
        QString fn=contextEntry->title;
        if(contextEntry->document->getStateImportedFile()){
                fn+="#"; // mark as relative to current
        }
        menu.addAction(tr("Open Document"), this, SLOT(openExternalFileFromAction()))->setData(fn);
        menu.addAction(tr("Go to Definition"), this, SLOT(gotoLineFromAction()))->setData(QVariant::fromValue(contextEntry));

        menu.exec(w->mapToGlobal(pos));
        return;
    }
    if (contextEntry->type == StructureEntry::SE_MAGICCOMMENT) {
        QMenu menu;
        menu.addAction(tr("Go to Definition"), this, SLOT(gotoLineFromAction()))->setData(QVariant::fromValue(contextEntry));
        menu.exec(w->mapToGlobal(pos));
        return;
    }

}
/*!
 * \brief create label from structure/toc context menu
 */
void Texstudio::createLabelFromAction()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;
    StructureEntry *entry = qvariant_cast<StructureEntry *>(action->data());
    if (!entry || !entry->document) return;

    // find editor and line nr
    int lineNr = entry->getRealLineNumber();

    mDontScrollToItem = entry->type != StructureEntry::SE_SECTION;
    LatexEditorView *edView = entry->document->getEditorView();
    QEditor::MoveFlags mflags = QEditor::NavigationToHeader;
    if (!edView) {
        edView = load(entry->document->getFileName());
        if (!edView) return;
        mflags &= ~QEditor::Animated;
        //entry is now invalid
    }
    REQUIRE(edView->getDocument());

    if (lineNr < 0) return; //not found. (document was closed)

    // find column position after structure command
    QString lineText = edView->getDocument()->line(lineNr).text();
    int pos = -1;
    for (int i = 0; i < latexParser.structureDepth(); i++) {
        foreach (const QString &cmd, latexParser.possibleCommands[QString("%structure%1").arg(i)]) {
            pos = lineText.indexOf(cmd);
            if (pos >= 0) {
                pos += cmd.length();
                // workaround for starred commands: \section*{Cap}
                // (may have been matched by unstarred version because there is no order in possibleCommands)
                if ((lineText.length() > pos + 1) && lineText.at(pos) == '*') pos++;
                break;
            }
        }
        if (pos >= 0) break;
    }
    if (pos < 0) return; // could not find associated command

    // advance pos behind options, and use title to guess a label
    QList<CommandArgument> args = getCommandOptions(lineText, pos, &pos);
    QString label = "sec:";
    if (args.length() > 0) {
        QString title(args.at(0).value);
        if (!label.contains('\\') && !label.contains('$')) {  // title with these chars are too complicated to extract label
            label += makeLatexLabel(title);
        }
    }

    gotoLine(lineNr, pos, edView, mflags);

    insertTag(QString("\\label{%1}").arg(label), 7);
    QDocumentCursor cur(edView->editor->cursor());
    cur.movePosition(label.length(), QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
    edView->editor->setCursor(cur);
}

void Texstudio::closeDocument()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;
    LatexDocument *document = qvariant_cast<LatexDocument *>(action->data());
    if (!document) return;
    if (document->getEditorView()) editors->requestCloseEditor(document->getEditorView());
    else if (document == documents.masterDocument) structureContextMenuToggleMasterDocument(document);
}

void Texstudio::toggleMasterDocument()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;
    LatexDocument *document = qvariant_cast<LatexDocument *>(action->data());
    if (!document) return;
    structureContextMenuToggleMasterDocument(document);
}

/*!
 * context menu action: Select the selected section and copy it to the clipboard.
 * TODO: the logic should probably be moved to LatexDocument or LatexEditorView
 */
void Texstudio::editSectionCopy()
{
    // called by action
    QTreeWidgetItem *item = nullptr;
    if(topTOCTreeWidget->isVisible()){
        item = topTOCTreeWidget->currentItem();
    }else{
        item = structureTreeWidget->currentItem();
    }
    if(!item) return;
    StructureEntry *entry = item->data(0,Qt::UserRole).value<StructureEntry *>();
    if(!entry) return;
    LatexEditorView *edView = entry->document->getEditorView();
    if(!edView) return;
    editors->setCurrentEditor(edView);
    QDocumentSelection sel = entry->document->sectionSelection(entry);

    edView->editor->setCursorPosition(sel.startLine, 0);
    QDocumentCursor cur = edView->editor->cursor();
    //m_cursor.movePosition(1, QDocumentCursor::NextLine, QDocumentCursor::KeepAnchor);
    cur.setSilent(true);
    cur.movePosition(sel.endLine - sel.startLine - 1, QDocumentCursor::NextLine, QDocumentCursor::KeepAnchor);
    cur.movePosition(0, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
    edView->editor->setCursor(cur);
    edView->editor->copy();
}

/*!
 * context menu action: Cut the selected section to the clipboard.
 * TODO: the logic should probably be moved to LatexDocument or LatexEditorView
 */
void Texstudio::editSectionCut()
{
    // called by action
    QTreeWidgetItem *item = nullptr;
    if(topTOCTreeWidget->isVisible()){
        item = topTOCTreeWidget->currentItem();
    }else{
        item = structureTreeWidget->currentItem();
    }
    if(!item) return;
    StructureEntry *entry = item->data(0,Qt::UserRole).value<StructureEntry *>();
    if (!entry) return;
    LatexEditorView *edView = entry->document->getEditorView();
    if (!edView) return;
    editors->setCurrentEditor(edView);
    QDocumentSelection sel = entry->document->sectionSelection(entry);

    edView->editor->setCursorPosition(sel.startLine, 0);
    QDocumentCursor cur = edView->editor->cursor();
    //m_cursor.movePosition(1, QDocumentCursor::NextLine, QDocumentCursor::KeepAnchor);
    cur.setSilent(true);
    cur.movePosition(sel.endLine - sel.startLine - 1, QDocumentCursor::NextLine, QDocumentCursor::KeepAnchor);
    cur.movePosition(0, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
    edView->editor->setCursor(cur);
    edView->editor->cut();
}

/*!
 * context menu action: Paste the clipboard contents before the selected section.
 * TODO: the logic should probably be moved to LatexDocument or LatexEditorView
 */
void Texstudio::editSectionPasteBefore()
{
    QTreeWidgetItem *item = nullptr;
    if(topTOCTreeWidget->isVisible()){
        item = topTOCTreeWidget->currentItem();
    }else{
        item = structureTreeWidget->currentItem();
    }
    if(!item) return;
    StructureEntry *entry = item->data(0,Qt::UserRole).value<StructureEntry *>();
    if (!entry) return;
    LatexEditorView *edView = entry->document->getEditorView();
    if (!edView) return;
    editors->setCurrentEditor(edView);

    int line = entry->getRealLineNumber();
    edView->editor->setCursorPosition(line, 0);
    edView->editor->insertText("\n");
    edView->editor->setCursorPosition(line, 0);
    edView->paste();
}

/*!
 * context menu action: Paste the clipboard contents after the selected section.
 * TODO: the logic should probably be moved to LatexDocument or LatexEditorView
 */
void Texstudio::editSectionPasteAfter()
{
    QTreeWidgetItem *item = nullptr;
    if(topTOCTreeWidget->isVisible()){
        item = topTOCTreeWidget->currentItem();
    }else{
        item = structureTreeWidget->currentItem();
    }
    if(!item) return;
    StructureEntry *entry = item->data(0,Qt::UserRole).value<StructureEntry *>();
    if (!entry) return;
    LatexEditorView *edView = entry->document->getEditorView();
    if (!edView) return;
    editors->setCurrentEditor(edView);
    QDocumentSelection sel = entry->document->sectionSelection(entry);

    int line = sel.endLine;
    if (line >= edView->editor->document()->lines()) {
        edView->editor->setCursorPosition(line - 1, 0);
        QDocumentCursor c = edView->editor->cursor();
        c.movePosition(1, QDocumentCursor::End, QDocumentCursor::MoveAnchor);
        edView->editor->setCursor(c);
        edView->editor->insertText("\n");
    } else {
        edView->editor->setCursorPosition(line, 0);
        edView->editor->insertText("\n");
        edView->editor->setCursorPosition(line, 0);
    }
    edView->paste();
}

/*!
 * context menu action: Indent the selected section.
 * This replaces the sections and all its sub-sections with a lower heading, e.g.
 *     \section -> \subsection
 *     \chapter -> \section
 * TODO: the logic should probably be moved to LatexDocument or LatexEditorView
 */
void Texstudio::editIndentSection()
{
    QTreeWidgetItem *item = nullptr;
    if(topTOCTreeWidget->isVisible()){
        item = topTOCTreeWidget->currentItem();
    }else{
        item = structureTreeWidget->currentItem();
    }
    if(!item) return;
    StructureEntry *entry = item->data(0,Qt::UserRole).value<StructureEntry *>();
    if (!entry) return;
    LatexEditorView *edView = entry->document->getEditorView();
    if (!edView) return;
    editors->setCurrentEditor(edView);
    QDocumentSelection sel = entry->document->sectionSelection(entry);

    QStringList sectionOrder;
    sectionOrder << "\\subparagraph" << "\\paragraph" << "\\subsubsection" << "\\subsection" << "\\section" << "\\chapter";

    // replace sections
    QString line;
    QDocumentCursor cursor = edView->editor->cursor();
    for (int l = sel.startLine; l < sel.endLine; l++) {
        edView->editor->setCursorPosition(l, 0);
        cursor = edView->editor->cursor();
        line = edView->editor->cursor().line().text();
        QString m_old = "";
        foreach (const QString &elem, sectionOrder) {
            if (m_old != "") line.replace(elem, m_old);
            m_old = elem;
        }

        cursor.movePosition(1, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
        edView->editor->setCursor(cursor);
        edView->editor->insertText(line);
    }
}

/*!
 * context menu action: Unindent the selected section.
 * This replaces the sections and all its sub-sections with a higher heading, e.g.
 *     \subsection -> \section
 *     \section -> \chapter
 * TODO: the logic should probably be moved to LatexDocument or LatexEditorView
 */
void Texstudio::editUnIndentSection()
{
    QTreeWidgetItem *item = nullptr;
    if(topTOCTreeWidget->isVisible()){
        item = topTOCTreeWidget->currentItem();
    }else{
        item = structureTreeWidget->currentItem();
    }
    if(!item) return;
    StructureEntry *entry = item->data(0,Qt::UserRole).value<StructureEntry *>();
    if (!entry) return;
    LatexEditorView *edView = entry->document->getEditorView();
    if (!edView) return;
    editors->setCurrentEditor(edView);
    QDocumentSelection sel = entry->document->sectionSelection(entry);

    QStringList sectionOrder;
    sectionOrder << "\\chapter" << "\\section" << "\\subsection" << "\\subsubsection" << "\\paragraph" << "\\subparagraph" ;

    // replace sections
    QString line;
    QDocumentCursor cursor = edView->editor->cursor();
    for (int l = sel.startLine; l < sel.endLine; l++) {
        edView->editor->setCursorPosition(l, 0);
        cursor = edView->editor->cursor();
        line = edView->editor->cursor().line().text();
        QString m_old = "";
        foreach (const QString &elem, sectionOrder) {
            if (m_old != "") line.replace(elem, m_old);
            m_old = elem;
        }

        cursor.movePosition(1, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
        edView->editor->setCursor(cursor);
        edView->editor->insertText(line);
    }
}

/*! \brief move cursor to position given in calling action (TOC/structure context menu)
 *
 */
void Texstudio::gotoLineFromAction()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;
    StructureEntry *entry = qvariant_cast<StructureEntry *>(action->data());

    if (!entry || !entry->document) return;
    LatexDocument *doc = entry->document;
    QDocumentLineHandle *dlh = entry->getLineHandle();
    int lineNr = -1;
    if ((lineNr = doc->indexOf(dlh)) >= 0) {
        gotoLine(entry->document, lineNr, 0);
    }
}

/*!
 * \brief Collect structure info from file and create a TOC
 * This approach avoid the model/view which repeatedly led to crashes because the view component caches info from the actual model and is not kept up-to-date properly
 *
 */
void Texstudio::updateStructureLocally(bool updateAll){
    if(!structureTreeWidget->isVisible()) return; // don't update if TOC is not shown, save unnecessary effort
    QTreeWidgetItem *root= nullptr;

    LatexDocument *doc=documents.getCurrentDocument();
    if(!doc){
        // no root document
        // clear TOC completely
        structureTreeWidget->clear();
        return;
    }

    QList<LatexDocument*> docs{doc};
    if(updateAll){
        docs=documents.documents; // only visible documents
    }
    for(LatexDocument *doc:docs){
        LatexDocument *master = documents.getMasterDocument();
        bool showHiddenMasterFirst=false;
        bool hiddenMasterStructureIsVisible=false;
        if(configManager.parseMaster && master && master->isHidden()){
            showHiddenMasterFirst=true;
        }
        if(configManager.structureShowSingleDoc){
            root= structureTreeWidget->topLevelItem(0);
            if(structureTreeWidget->topLevelItemCount()>1){
                for(int i=1;structureTreeWidget->topLevelItemCount()>1;){
                    QTreeWidgetItem *item=structureTreeWidget->takeTopLevelItem(i);
                    delete item;
                }
            }
        }else{
            for(int i=0;i<structureTreeWidget->topLevelItemCount();++i){
                QTreeWidgetItem *item = structureTreeWidget->topLevelItem(i);
                StructureEntry *contextEntry = item->data(0,Qt::UserRole).value<StructureEntry *>();
                if (!contextEntry){
                    structureTreeWidget->takeTopLevelItem(i);
                    delete item;
                    --i;
                    continue;
                }
                if (contextEntry->type == StructureEntry::SE_DOCUMENT_ROOT) {
                    if(contextEntry->document == doc){
                        root=item;
                    }else{
                        QFont font=item->font(0);
                        font.setBold(false);
                        item->setFont(0,font);
                        if(!documents.documents.contains(contextEntry->document) || documents.hiddenDocuments.contains(contextEntry->document)){
                            if(showHiddenMasterFirst && contextEntry->document == master && !hiddenMasterStructureIsVisible){
                                // run only once
                                // reload may add more structure views
                                hiddenMasterStructureIsVisible=true;
                                continue; // keep showing master document regardless
                            }
                            structureTreeWidget->takeTopLevelItem(i);
                            delete item;
                            --i;
                        }
                    }
                }else{
                    // remove invalid
                    structureTreeWidget->takeTopLevelItem(i);
                    delete item;
                    --i;
                }
            }
            // reorder documents
            for(int i=0;i<documents.documents.length();++i){
                bool found=false;
                int j=i;
                StructureEntry *contextEntry;
                for(;j<structureTreeWidget->topLevelItemCount();++j){
                    QTreeWidgetItem *item = structureTreeWidget->topLevelItem(j);
                    contextEntry = item->data(0,Qt::UserRole).value<StructureEntry *>();
                    if(contextEntry->document == documents.documents.value(i)){
                        found=true;
                        break;
                    }
                }
                if(found && i<j){
                    QTreeWidgetItem *item = structureTreeWidget->takeTopLevelItem(j);
                    if(contextEntry->document==master){
                        item->setIcon(0,getRealIcon("masterdoc"));
                    }else{
                        item->setIcon(0,getRealIcon("doc"));
                    }
                    structureTreeWidget->insertTopLevelItem(i,item);
                }
                if(!found){
                    QTreeWidgetItem *item=new QTreeWidgetItem();
                    LatexDocument *doc=documents.documents.value(i);
                    StructureEntry *base=doc->baseStructure;

                    item->setText(0,doc->getFileInfo().fileName());
                    item->setData(0,Qt::UserRole,QVariant::fromValue<StructureEntry *>(base));
                    if(doc==master){
                        item->setIcon(0,getRealIcon("masterdoc"));
                    }else{
                        item->setIcon(0,getRealIcon("doc"));
                    }
                    structureTreeWidget->insertTopLevelItem(i,item);
                    if(doc==documents.getCurrentDocument()){
                        root=item;
                    }
                }
            }
        }
        StructureEntry *selectedEntry=nullptr;
        bool itemExpandedLABEL=false;
        bool itemExpandedTODO=false;
        bool itemExpandedMAGIC=false;
        bool itemExpandedBIBLIO=false;
        bool addToTopLevel=false;
        if(!root){
            root=new QTreeWidgetItem();
            addToTopLevel=true;
        }else{
            // get current selected item, check only first and deduce structureEntry
            QList<QTreeWidgetItem*> selected=structureTreeWidget->selectedItems();
            if(!selected.isEmpty()){
                QTreeWidgetItem *item=selected.first();
                if(item){
                    selectedEntry = item->data(0,Qt::UserRole).value<StructureEntry *>();
                }
            }
            // remove all item in topTOC but keep itemTODO
            for(int i=0;i<root->childCount();++i){
                QTreeWidgetItem *item=root->child(i);
                if(item->data(0,Qt::UserRole+1).toString()=="TODO"){
                    itemExpandedTODO=item->isExpanded();
                }
                if(item->data(0,Qt::UserRole+1).toString()=="LABEL"){
                    itemExpandedLABEL=item->isExpanded();
                }
                if(item->data(0,Qt::UserRole+1).toString()=="MAGIC"){
                    itemExpandedMAGIC=item->isExpanded();
                }
                if(item->data(0,Qt::UserRole+1).toString()=="BIBLIO"){
                    itemExpandedBIBLIO=item->isExpanded();
                }
            }
            QList<QTreeWidgetItem*> items=root->takeChildren();
            qDeleteAll(items);
        }
        QVector<QTreeWidgetItem *>rootVector(latexParser.MAX_STRUCTURE_LEVEL,root);
        // fill TOC, starting by current master/top


        StructureEntry *base=doc->baseStructure;

        root->setText(0,doc->getFileInfo().fileName());
        root->setData(0,Qt::UserRole,QVariant::fromValue<StructureEntry *>(base));
        if(doc==master){
            root->setIcon(0,getRealIcon("masterdoc"));
        }else{
            root->setIcon(0,getRealIcon("doc"));
        }
        QFont font=root->font(0);
        font.setBold(true);
        root->setFont(0,font);

        QList<QTreeWidgetItem*> todoList;
        QList<QTreeWidgetItem*> labelList;
        QList<QTreeWidgetItem*> magicList;
        QList<QTreeWidgetItem*> biblioList;
        parseStructLocally(base,rootVector,&todoList,&labelList,&magicList,&biblioList);
        if(addToTopLevel)
            structureTreeWidget->addTopLevelItem(root);

        if(!biblioList.isEmpty()){
            QTreeWidgetItem *itemBIBLIO=new QTreeWidgetItem();
            itemBIBLIO->setText(0,tr("BIBLIOGRAPHY"));
            itemBIBLIO->setData(0,Qt::UserRole+1,"BIBLIO");
            itemBIBLIO->insertChildren(0,biblioList);
            root->insertChild(0,itemBIBLIO);
            itemBIBLIO->setExpanded(itemExpandedBIBLIO);
        }
        if(!magicList.isEmpty()){
            QTreeWidgetItem *itemTODO=new QTreeWidgetItem();
            itemTODO->setText(0,tr("MAGIC_COMMENTS"));
            itemTODO->setData(0,Qt::UserRole+1,"MAGIC");
            itemTODO->insertChildren(0,magicList);
            root->insertChild(0,itemTODO);
            itemTODO->setExpanded(itemExpandedMAGIC);
        }
        if(!todoList.isEmpty()){
            QTreeWidgetItem *itemTODO=new QTreeWidgetItem();
            itemTODO->setText(0,tr("TODO"));
            itemTODO->setData(0,Qt::UserRole+1,"TODO");
            itemTODO->insertChildren(0,todoList);
            root->insertChild(0,itemTODO);
            itemTODO->setExpanded(itemExpandedTODO);
        }
        if(!labelList.isEmpty()){
            QTreeWidgetItem *itemLABEL=new QTreeWidgetItem();
            itemLABEL->setText(0,tr("LABELS"));
            itemLABEL->setData(0,Qt::UserRole+1,"LABEL");
            itemLABEL->insertChildren(0,labelList);
            root->insertChild(0,itemLABEL);
            itemLABEL->setExpanded(itemExpandedLABEL);
        }

        root->setExpanded(true);
        root->setSelected(false);
        updateCurrentPosInTOC(nullptr,nullptr,selectedEntry);
    }
}

/*!
 * \brief parse children of a structure entry se to collect structure data
 * This function parses only the specific document, not any sub-files (unlike parseStruct).
 * For this also labels and magic comments are presented.
 * \param se root structureentry
 * \param rootVector
 */
void Texstudio::parseStructLocally(StructureEntry* se, QVector<QTreeWidgetItem *> &rootVector, QList<QTreeWidgetItem *> *todoList, QList<QTreeWidgetItem *> *labelList, QList<QTreeWidgetItem *> *magicList, QList<QTreeWidgetItem *> *biblioList) {
    const QColor beyondEndColor = darkMode ? QColor(255, 170, 0)  : QColor(255, 170, 0);
    const QColor inAppendixColor= darkMode ? QColor(0, 102,   0): QColor(200, 230, 200);

    foreach(StructureEntry* elem,se->children){
        if(todoList && (elem->type == StructureEntry::SE_OVERVIEW)){
            parseStructLocally(elem,rootVector,todoList,labelList,magicList,biblioList);
        }
        if(todoList && (elem->type == StructureEntry::SE_TODO)){
            QTreeWidgetItem * item=new QTreeWidgetItem();
            item->setData(0,Qt::UserRole,QVariant::fromValue<StructureEntry *>(elem));
            item->setText(0,elem->title);
            todoList->append(item);
        }
        if(labelList && (elem->type == StructureEntry::SE_LABEL)){
            QTreeWidgetItem * item=new QTreeWidgetItem();
            item->setData(0,Qt::UserRole,QVariant::fromValue<StructureEntry *>(elem));
            item->setText(0,elem->title);
            labelList->append(item);
        }
        if(magicList && (elem->type == StructureEntry::SE_MAGICCOMMENT)){
            QTreeWidgetItem * item=new QTreeWidgetItem();
            item->setData(0,Qt::UserRole,QVariant::fromValue<StructureEntry *>(elem));
            item->setText(0,elem->title);
            magicList->append(item);
        }
        if(biblioList && (elem->type == StructureEntry::SE_BIBTEX)){
            QTreeWidgetItem * item=new QTreeWidgetItem();
            item->setData(0,Qt::UserRole,QVariant::fromValue<StructureEntry *>(elem));
            item->setText(0,elem->title);
            biblioList->append(item);
        }
        if(elem->type == StructureEntry::SE_SECTION){
            QTreeWidgetItem * item=new QTreeWidgetItem();
            item->setData(0,Qt::UserRole,QVariant::fromValue<StructureEntry *>(elem));
            item->setText(0,elem->title);
            item->setIcon(0,iconSection.value(elem->level));
            rootVector[elem->level]->addChild(item);
            item->setExpanded(elem->expanded);
            if (documents.markStructureElementsInAppendix && elem->hasContext(StructureEntry::InAppendix)) item->setBackground(0,inAppendixColor);
            if (documents.markStructureElementsBeyondEnd && elem->hasContext(StructureEntry::BeyondEnd)) item->setBackground(0,beyondEndColor);
            // fill rootVector with item for subsequent lower level elements (which are children of item then)
            for(int i=elem->level+1;i<latexParser.MAX_STRUCTURE_LEVEL;i++){
                rootVector[i]=item;
            }
            parseStructLocally(elem,rootVector,todoList,labelList,magicList);
        }
        if(elem->type == StructureEntry::SE_INCLUDE){
            QTreeWidgetItem * item=new QTreeWidgetItem();
            item->setData(0,Qt::UserRole,QVariant::fromValue<StructureEntry *>(elem));
            item->setText(0,elem->title);
            if(!elem->valid){
                item->setForeground(0,Qt::red);
            }
            item->setIcon(0,getRealIcon("include"));
            if(configManager.indentIncludesInStructure){
                rootVector[latexParser.MAX_STRUCTURE_LEVEL-1]->addChild(item);
            }else{
                rootVector[0]->addChild(item);
                for(int i=1;i<latexParser.MAX_STRUCTURE_LEVEL;i++){
                    rootVector[i]=rootVector[0];
                }
            }
        }
    }
}
#ifndef QT_NO_DEBUG
/*!
 * \brief check all currently defined shortcuts for main window for duplicates
 */
void Texstudio::checkForShortcutDuplicate()
{
    QHash<QString, QKeySequence>  ms=configManager.managedMenuShortcuts;
    QMultiMap<QString,QString> shortcuts;
    for(const QString &elem:ms.keys()){
        if(ms.value(elem).toString().isEmpty()) continue; // no shortcut
        if(shortcuts.contains(ms.value(elem).toString())){
            // duplicate found
            qDebug()<<ms.value(elem).toString()<<elem<<" "<<shortcuts.values(ms.value(elem).toString());
        }
        shortcuts.insert(ms.value(elem).toString(),elem);
    }
}
#endif

void Texstudio::openAllRelatedDocuments()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;
    LatexDocument *document = qvariant_cast<LatexDocument *>(action->data());
    if (!document) return;
    QSet<QString> checkedFiles, filesToCheck;
    filesToCheck.insert(document->getFileName());

    while (!filesToCheck.isEmpty()) {
        QString f = *filesToCheck.begin();
        filesToCheck.erase(filesToCheck.begin());
        if (checkedFiles.contains(f)) continue;
        checkedFiles.insert(f);
        document = documents.findDocument(f);
        if (!document) {
            LatexEditorView *lev = load(f);
            document = lev ? lev->document : nullptr;
        }
        if (!document) continue;
        foreach (const QString &fn, document->includedFilesAndParent()) {
            QString t = document->findFileName(fn);
            if (!t.isEmpty()) filesToCheck.insert(t);
        }
    }
}

void Texstudio::closeAllRelatedDocuments()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;
    LatexDocument *document = qvariant_cast<LatexDocument *>(action->data());
    if (!document) return;
    QList<LatexDocument *> l = document->getListOfDocs();

    if (!saveFilesForClosing(l)) return;
    foreach (LatexDocument *d, l) {
        if (documents.documents.contains(d))
            documents.deleteDocument(d); //this might hide the document
        if (documents.hiddenDocuments.contains(d))
            documents.deleteDocument(d, d->isHidden(), d->isHidden());
    }
}

/*!
 * \brief copy file name of document to clipboard
 *
 * Called from structure view
 */
void Texstudio::copyFileName()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;
    LatexDocument *document = qvariant_cast<LatexDocument *>(action->data());
    if (!document) return;
    QClipboard* clipboard = QGuiApplication::clipboard();
    if (!clipboard) return;
    clipboard->setText(document->getFileInfo().fileName());
}

/*!
 * \brief copy file path of document to clipboard
 *
 * Called from structure view
 */
void Texstudio::copyFilePath()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;
    LatexDocument *document = qvariant_cast<LatexDocument *>(action->data());
    if (!document) return;
    QClipboard* clipboard = QGuiApplication::clipboard();
    if (!clipboard) return;
    clipboard->setText(document->getFileInfo().absoluteFilePath());
}
/*!
 * \brief open directory in external explorer
 *
 * Called from structure view
 */

void Texstudio::showInGraphicalShell_()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action) return;
    LatexDocument *document = qvariant_cast<LatexDocument *>(action->data());
    if (!document) return;
    showInGraphicalShell(this, document->getFileName());
}



/*!
 * \brief toggle single/multiple documents view in structureWidget
 */

void Texstudio::toggleSingleDocMode()
{
    bool mode = configManager.structureShowSingleDoc;
    configManager.structureShowSingleDoc= !mode;
    updateStructureLocally();
}

/*!
 Returns an associated SE_LABEL entry for a structure element if one exists, otherwise 0.
 TODO: currently association is checked, by checking, if the label is on the same line or on the next.
 This is not necessarily correct. It fails if:
  - there are multiple labels on one line (always the first label is chosen)
  - the label is more than one line after the entry (label not detected)
*/
StructureEntry* Texstudio::labelForStructureEntry(const StructureEntry *entry)
{
    REQUIRE_RET(entry && entry->document, nullptr );
    QDocumentLineHandle *dlh = entry->getLineHandle();
    if (!dlh) return nullptr;
    QDocumentLineHandle *nextDlh = entry->document->line(entry->getRealLineNumber() + 1).handle();
    StructureEntryIterator iter(entry->document->baseStructure);

    while (iter.hasNext()) {
        StructureEntry *se = iter.next();
        if (se->type == StructureEntry::SE_LABEL) {
            QDocumentLineHandle *labelDlh = se->getLineHandle();
            if (labelDlh == dlh || labelDlh == nextDlh) {
                return se;
            }
        }
    }
    return nullptr;
}
/*!
 * \brief expand item and subitems in structureWidget
 */
void Texstudio::expandSubitems()
{
    QTreeWidgetItem *item = nullptr;
    if(topTOCTreeWidget->isVisible()){
        item = topTOCTreeWidget->currentItem();
    }else{
        item = structureTreeWidget->currentItem();
    }
    if(!item) return;
    UtilsUi::setSubtreeExpanded(item, true);
}
/*!
 * \brief collapse item and subitems in structureWidget
 */
void Texstudio::collapseSubitems()
{
    QTreeWidgetItem *item = nullptr;
    if(topTOCTreeWidget->isVisible()){
        item = topTOCTreeWidget->currentItem();
    }else{
        item = structureTreeWidget->currentItem();
    }
    if(!item) return;
    UtilsUi::setSubtreeExpanded(item, false);
}

/*! @} */


#undef MAC_OR_DEFAULT
