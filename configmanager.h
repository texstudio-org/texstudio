#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "mostQtHeaders.h"

#include "buildmanager.h"
#include "configmanagerinterface.h"
#include "smallUsefulFunctions.h"

class ConfigDialog;
class LatexCompleterConfig;
class LatexEditorViewConfig;
class WebPublishDialogConfig;
class InsertGraphicsConfig;
struct PDFDocumentConfig;
class GrammarCheckerConfig;

struct ManagedToolBar{
	QString name;
	QStringList defaults;
	QStringList actualActions;
	QToolBar *toolbar;
	ManagedToolBar(const QString &newName, const QStringList &defs);
};

class ConfigManager: public QObject, public ConfigManagerInterface {
	Q_OBJECT
public:
	ConfigManager(QObject *parent=0);
	~ConfigManager();

	QSettings* readSettings(bool reread=false);
	QSettings* saveSettings(const QString& saveName="");

	bool execConfigDialog();

//public configuration

	static QTextCodec* newFileEncoding;
	QString newFileEncodingName;
	bool autoDetectEncodingFromChars;
	bool autoDetectEncodingFromLatex;
	QStringList commonEncodings;

    QHash<QString, int> editorKeys;
	QSet<int> editorAvailableOperations;

	//build
	BuildManager* buildManager; 
	bool singleViewerInstance;
	bool showMessagesWhenCompiling;
	bool runLaTeXBibTeXLaTeX;
	int showStdoutOption; //never = 0, user commands, always
	
	//svn
	bool autoCheckinAfterSave;
	bool svnUndo;
	bool svnKeywordSubstitution;
	int svnSearchPathDepth;
	
	//appearance 
	QPalette systemPalette; 
	QString interfaceStyle;
	QString interfaceFontFamily;
	bool useTexmakerPalette;
	int interfaceFontSize;
	bool newLeftPanelLayout;
	bool mruDocumentChooser;
	bool configShowAdvancedOptions, configRiddled;
	bool centralVisible;
	bool showLineNumbersInStructure;
	int indentationInStructure;
	bool indentIncludesInStructure;
	QString referenceCommandsInContextMenu;
	
	//update
	bool autoUpdateCheck;
	int autoUpdateCheckIntervalDays;
	QDateTime lastUpdateCheck;

	//language
	QString language, lastLanguage;
	QTranslator* appTranslator;
	QTranslator* basicTranslator;	
		
	//editor 
	LatexEditorViewConfig * const editorConfig;
	//completion
	LatexCompleterConfig * const completerConfig;

	//webpublish dialog
	WebPublishDialogConfig * const webPublishDialogConfig;
	//pdf preview
	PDFDocumentConfig * const pdfDocumentConfig;

	//other dialogs
	int lastHardWrapColumn;
	bool lastHardWrapSmartScopeSelection;
	bool lastHardWrapJoinLines;

	//insert graphics dialog
	InsertGraphicsConfig * const insertGraphicsConfig;
	
	//Grammar check
	GrammarCheckerConfig * const grammarCheckerConfig;

	//bool autoReplaceCommands; // moved to static codesnippet

	int tabstop;

	bool useEscForClosingLog;
	int replaceQuotes; //0: none, 1: ``..'', 2: \"< \"> 3: \"`..\"' , 4: \\og..\\fg{} 5: \"> \"<

	// table autoformat
	QString tableAutoFormatSpecialCommands; // colon separated
	int tableAutoFormatSpecialCommandPos;
	bool tableAutoFormatOneLinePerCell;

	// LogView
	double logViewWarnIfFileSizeLargerMB;

	//preview
	enum PreviewMode {PM_TOOLTIP_AS_FALLBACK=0, PM_PANEL,PM_TOOLTIP,PM_BOTH,PM_INLINE};
	enum AutoPreviewMode {AP_NEVER = 0, AP_PREVIOUSLY = 1};
	PreviewMode previewMode; 
	AutoPreviewMode autoPreview;
	int autoPreviewDelay;

    // embedded viewer
    bool viewerEnlarged;
	
	//files
	QString lastDocument; //last opened document, for file open directory
	QStringList recentFilesList, recentProjectList;
	int maxRecentFiles, maxRecentProjects;
	bool rememberFileFilter;
	bool sessionRestore;
	bool parseBibTeX, parseMaster;
    bool autoLoadChildren;

        //autosave
        int autosaveEveryMinutes;
	
	bool addRecentFile(const QString & fileName, bool asMaster); //adds a recent file
	void updateRecentFiles(bool alwaysRecreateMenuItems=false);
	QMenu* updateListMenu(const QString& menuName, const QStringList& items, const QString& namePrefix, bool prefixNumber, const char* slotName, const int baseShortCut, bool alwaysRecreateMenuItems=false, int additionalEntries = 2);
	void updateUserMacroMenu(bool alwaysRecreateMenuItems=false);
	
	QString additionalBibPaths;
	QString additionalImagePaths;

	//dictionaries
	QString spellDictDir;
	QString spellLanguage;
	QString spell_dic, thesaurus_database;

	// custom highlighting
	QStringList enviromentModes;
	QMap<QString,QVariant> customEnvironments;

	//debug
	#ifndef QT_NO_DEBUG
	QDateTime debugLastFileModification;
	QDateTime debugLastFullTestRun;
	#endif
	
    // disable usage of esc for closing fullscreen view
    bool disableEscForClosingFullscreen;
	bool goToErrorWhenDisplayingLog;
	bool showLogMarkersWhenClickingLogEntry;

    // input unicode instead of latex command from symbolgrid (if available)
    bool insertUTF;

	//menus
	QObject* menuParent; //lets assume there is only one
	QMenuBar* menuParentsBar; //that's ugly, but faster as long as there is only one (both values could be extracted from the action's name)
	QList<QMenu*> managedMenus;
	QHash<QString,QKeySequence> managedMenuShortcuts;
	QList<QPair<QString,QString> > managedMenuNewShortcuts;
		
	QMenu* newManagedMenu(const QString &id,const QString &text);
	QMenu* newManagedMenu(QMenu* menu, const QString &id,const QString &text);
	QAction* newManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QList<QKeySequence> &shortCuts = QList<QKeySequence>(), const QString & iconFile="");
	QAction* newManagedAction(QWidget* menu, const QString &id, QAction* act);
	QAction* newOrLostOldManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QList<QKeySequence> &shortCuts = QList<QKeySequence>(), const QString & iconFile="");
	QAction* getManagedAction(const QString& id);
	QList<QAction *> getManagedActions(const QStringList& ids, const QString &commonPrefix="");
	QMenu* getManagedMenu(const QString& id);
	void removeManagedMenus();
	void triggerManagedAction(const QString& id);
	
	static QString iniFileOverride;
private:
	void connectExtendedSlot(QAction* act, const QString& slot);
	bool modifyMenuContentsFirstCall;
	void modifyMenuContent(QStringList& ids, const QString& id);
public:
	void modifyMenuContents();
	void modifyManagedShortcuts();
	void setManagedShortCut(QAction* act, int num, const QKeySequence& key);
	void loadManagedMenu(QMenu* parent,const QDomElement &f);
	void loadManagedMenus(const QString &f);
	QStringList possibleMenuSlots;
private:
	void managedMenuToTreeWidget(QTreeWidgetItem* parent, QMenu* menu);
	void treeWidgetToManagedMenuTo(QTreeWidgetItem* item);

	QTreeWidgetItem* managedLatexMenuToTreeWidget(QTreeWidgetItem* parent, QMenu* menu);
	void treeWidgetToManagedLatexMenuTo();
	
public:
	// custom toolbar
	QList<ManagedToolBar> managedToolBars;
	QStringList watchedMenus;  //list of all sub menus mapped on toolbars
	QMap<QString,QVariant> replacedIconsOnMenus;

	void populateCustomActions(QListWidget* parent, QMenu* menu, bool go=false);

signals:
	void newLeftPanelLayoutChanged(bool newValue);
	void watchedMenuChanged(const QString& menuId);
public:
//private:
	QString configFileName,configFileNameBase,defaultStyleName,configBaseDir;
	enum CommmandGridWidgetType {CG_ID, CG_RERUN, CG_CMD, CG_PROGRAM, CG_RESET, CG_CONFIG, CG_DEL, CG_MOVEUP, CG_MOVEDOWN, CG_ADD};
	CommandMapping tempCommands;
	QList<QPushButton*> rerunButtons; // only for non-user commands
	QList<QWidget*> commandInputs;    // only for non-user commands
	QGridLayout* userGridLayout;
	QLineEdit* pdflatexEdit;
	void loadTranslations(QString locale);

	void registerOption(const QString& name, void* storage, PropertyType type, QVariant def, void* displayWidgetOffset);
	virtual void registerOption(const QString& name, void* storage, PropertyType type, QVariant def);

#define REGISTER_OPTION(TYPE, dummy) \
	void registerOption(const QString& name, TYPE* storage, QVariant def,  void* displayWidgetOffset); \
	virtual void registerOption(const QString& name, TYPE* storage, QVariant def=QVariant());
PROPERTY_TYPE_FOREACH_MACRO(REGISTER_OPTION)
#undef REGISTER_OPTION
	
	//virtual void registerOption(const QString& name, QVariant* storage, QVariant def);
	virtual void setOption(const QString& name, const QVariant& value);
	virtual QVariant getOption(const QString& name) const;
	virtual bool existsOption(const QString& name) const;
	virtual void linkOptionToDialogWidget(const void* optionStorage, QWidget* widget);
	virtual void linkOptionToObject(const void* optionStorage, QObject* widget, LinkOptions options);
	virtual void updateAllLinkedObjects(const void* optionStorage);
	
	static void getDefaultEncoding(const QByteArray& unused, QTextCodec* &guess, int &sure);
private:
	void setInterfaceStyle();

	QSettings* persistentConfig;

	QList<QTreeWidgetItem*> changedItemsList, superAdvancedItems;
	QHash<QString, QTreeWidgetItem*> manipulatedMenuTree;

	QMap<QString,QVariant> manipulatedMenus;

	QList<ManagedProperty> managedProperties;

	QMap<QWidget*, QList<QWidget*> > managedOptionDialogs;
	ManagedProperty* getManagedProperty(const void* storage);
	ManagedProperty* getManagedProperty(const QString& name);
	const ManagedProperty* getManagedProperty(const QString& name) const;

	QMap<ManagedProperty*, QPair<LinkOptions, QList<QObject*> > > managedOptionObjects;
	
	int userCommandRowCount();
	void addCommandRow(QGridLayout* parent, const CommandInfo& cmd, int row);
	void createCommandList(QGroupBox* box, const QStringList& order, bool user, bool meta);
	void setFirstRowMoveUpEnable(bool enable);
	void setLastRowMoveDownEnable(bool enable);
private slots:
	void browseCommand();
	void undoCommand();
	void editCommand();
	void addCommand();
	void removeCommand();
	void moveUpCommand();
	void moveDownCommand();
	void moveCommand(int dir, int atRow=-1);

	void latexTreeItemChanged(QTreeWidgetItem* item,int l);
	void latexTreeNewItem(bool menu = false);
	void latexTreeNewMenuItem();
	void toggleVisibleTreeItems(bool show);
	void activateInternalViewer(bool activated);

	void managedOptionDialogAccepted();
	void managedOptionObjectDestroyed(QObject* obj);
	void managedOptionBoolToggled();
private:
	void updateManagedOptionObjects(ManagedProperty* property);
};
#endif
