#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "mostQtHeaders.h"

#include "buildmanager.h"
#include "configmanagerinterface.h"

class ConfigDialog;
class LatexCompleterConfig;
class LatexEditorViewConfig;
class WebPublishDialogConfig;
class PDFDocumentConfig;

struct ManagedToolBar{
	QString name;
	QStringList defaults;
	QStringList actualActions;
	QToolBar *toolbar;
	ManagedToolBar(const QString &newName, const QStringList &defs);
};


struct ManagedProperty{ //TODO: Merge with the universal input dialog
	QString name;
	void* storage;
	PropertyType type;
	QVariant def;
	ptrdiff_t widgetOffset;

	ManagedProperty();
	QVariant valueToQVariant() const;
	void valueFromQVariant(const QVariant v);
	void writeToWidget(QWidget* w) const;
	bool readFromWidget(const QWidget* w);
};

class ConfigManager: public QObject, public ConfigManagerInterface {
	Q_OBJECT
public:
	ConfigManager(QObject *parent=0);
	~ConfigManager();

	QSettings* readSettings();
	QSettings* saveSettings();

	QSettings* readProfile(QString fname);

	bool execConfigDialog();

//public configuration

	static QTextCodec* newFileEncoding;
	QString newFileEncodingName;
	bool autodetectLoadedFile;
	int ignoreLogFileNames; //0: never, 1: in single mode, 2: always | see LatexLog::parseDocument for reason

	QStringList keyReplace, keyReplaceAfterWord, keyReplaceBeforeWord;
	QHash<int, int> editorKeys;
	QSet<int> editorAvailableOperations;

	//build
	BuildManager* buildManager; 
	bool singleViewerInstance;
	bool showLogAfterCompiling;
	bool runLaTeXBibTeXLaTeX;

	bool autoCheckinAfterSave;
	bool svnUndo;
	bool svnKeywordSubstitution;
	int svnSearchPathDepth;
	
	//appearance 
	QPalette systemPalette; 
	QString interfaceStyle;
	QString interfaceFontFamily;
	bool modernStyle;
	bool useTexmakerPalette;
	int interfaceFontSize;
	bool tabbedLogView;
	bool newLeftPanelLayout;
	bool configShowAdvancedOptions;
	bool useSystemTheme;
	bool centralVisible;
	
	//language
	QString language, lastLanguage;
	QTranslator* appTranslator;
	QTranslator* basicTranslator;	
		
	//editor 
	LatexEditorViewConfig * const editorConfig;
	//completion
	LatexCompleterConfig * const completerConfig;

	QHash<QString,QVariant> completerUsageHash;
	//webpublish dialog
	WebPublishDialogConfig * const webPublishDialogConfig;
	//pdf preview
	PDFDocumentConfig * const pdfDocumentConfig;

	//other dialogs
	int lastHardWrapColumn;
	bool lastHardWrapSmartScopeSelection;
	bool lastHardWrapJoinLines;

	//bool autoReplaceCommands; // moved to static codesnippet

	int tabstop;

	bool useEscForClosingLog;
	
	//preview
	enum PreviewMode {PM_TOOLTIP_AS_FALLBACK=0, PM_PANEL,PM_TOOLTIP,PM_BOTH};
	PreviewMode previewMode; 
	
	//files
	QString lastDocument; //last opened document, for file open directory
	QStringList recentFilesList, recentProjectList;
	int maxRecentFiles, maxRecentProjects;
	bool sessionRestore;
	QStringList sessionFilesToRestore;
	QList<QVariant> sessionCurRowsToRestore,sessionCurColsToRestore,sessionFirstLinesToRestore;
	QString sessionMaster;
	QString sessionCurrent;
	bool parseBibTeX, parseMaster;

        //autosave
        int autosaveEveryMinutes;
	
	bool addRecentFile(const QString & fileName, bool asMaster); //adds a recent file
	void updateRecentFiles(bool alwaysRecreateMenuItems=false);
	QMenu* updateListMenu(const QString& menuName, const QStringList& items, const QString& namePrefix, bool prefixNumber, const char* slotName, const int baseShortCut, bool alwaysRecreateMenuItems=false, int additionalEntries = 2);
	void updateUserMacroMenu(bool alwaysRecreateMenuItems=false);
	void updateUserToolMenu(bool alwaysRecreateMenuItems=false);
	
	//dictionaries
	QString spell_dic, thesaurus_database;

	// custom highlighting
	QStringList enviromentModes;
	QMap<QString,QVariant> customEnvironments;

	//user macros
	QStringList userMacroMenuName, userMacroTag, userMacroAbbrev, userToolMenuName, userToolCommand;

	//debug
	#ifndef QT_NO_DEBUG
	QDateTime debugLastFileModification;
	QDateTime debugLastFullTestRun;
	#endif
	
	//menus
	QObject* menuParent; //lets assume there is only one
	QMenuBar* menuParentsBar; //that's ugly, but faster as long as there is only one (both values could be extracted from the action's name)
	QList<QMenu*> managedMenus;
	QHash<QString,QKeySequence> managedMenuShortcuts;
	QList<QPair<QString,QString> > managedMenuNewShortcuts;
		
	QString getRealIconFile(const QString& icon) const;
	QIcon getRealIcon(const QString& icon) const;
	QMenu* newManagedMenu(const QString &id,const QString &text);
	QMenu* newManagedMenu(QMenu* menu, const QString &id,const QString &text);
	QAction* newManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QList<QKeySequence> &shortCuts = QList<QKeySequence>(), const QString & iconFile="");
	QAction* newManagedAction(QWidget* menu, const QString &id, QAction* act);
	QAction* newOrLostOldManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QList<QKeySequence> &shortCuts = QList<QKeySequence>(), const QString & iconFile="");
	QAction* getManagedAction(QString id);
	QMenu* getManagedMenu(QString id);
	void removeManagedMenus();
	void triggerManagedAction(QString id);
	
	void modifyManagedShortcuts();
	void loadManagedMenu(QMenu* parent,const QDomElement &f);
	void loadManagedMenus(const QString &f);
	void managedMenuToTreeWidget(QTreeWidgetItem* parent, QMenu* menu);
	void treeWidgetToManagedMenuTo(QTreeWidgetItem* item);

	QTreeWidgetItem* managedLatexMenuToTreeWidget(QTreeWidgetItem* parent, QMenu* menu);
	void treeWidgetToManagedLatexMenuTo();

	// custom toolbar
	QList<ManagedToolBar> managedToolBars;
	QStringList watchedMenus;  //list of all sub menus mapped on toolbars
	QMap<QString,QVariant> replacedIconsOnMenus;

	void populateCustomActions(QListWidget* parent, QMenu* menu, bool go=false);

signals:
	void tabbedLogViewChanged(bool changed);
	void newLeftPanelLayoutChanged(bool newValue);
	void watchedMenuChanged();
public:
//private:
	QString configFileName,configFileNameBase,defaultStyleName;
	QMap<QPushButton*, BuildManager::LatexCommand> buttonsToCommands;
	QMap<BuildManager::LatexCommand, QLineEdit*> commandsToEdits;
	void loadTranslations(QString locale);

	void registerOption(const QString& name, void* storage, PropertyType type, QVariant def, void* displayWidgetOffset);
	void registerOption(const QString& name, bool* storage, QVariant def,  void* displayWidgetOffset);
	void registerOption(const QString& name, int* storage, QVariant def, void* displayWidgetOffset);
	void registerOption(const QString& name, QString* storage, QVariant def, void* displayWidgetOffset);
	void registerOption(const QString& name, QStringList* storage, QVariant def, void* displayWidgetOffset);
	void registerOption(const QString& name, QDateTime* storage, QVariant def, void* displayWidgetOffset);
	void registerOption(const QString& name, double* storage, QVariant def, void* displayWidgetOffset);
	void registerOption(const QString& name, QByteArray* storage, QVariant def, void* displayWidgetOffset);
	void registerOption(const QString& name, QList<QVariant>* storage, QVariant def, void* displayWidgetOffset);
	virtual void registerOption(const QString& name, void* storage, PropertyType type, QVariant def);
	virtual void registerOption(const QString& name, bool* storage, QVariant def=QVariant());
	virtual void registerOption(const QString& name, int* storage, QVariant def=QVariant());
	virtual void registerOption(const QString& name, QString* storage, QVariant def=QVariant());
	virtual void registerOption(const QString& name, QStringList* storage, QVariant def=QVariant());
	virtual void registerOption(const QString& name, QDateTime* storage, QVariant def=QVariant());
	virtual void registerOption(const QString& name, double* storage, QVariant def=QVariant());
	virtual void registerOption(const QString& name, QByteArray* storage, QVariant def=QVariant());
	virtual void registerOption(const QString& name, QList<QVariant>* storage, QVariant def=QVariant());
	virtual void linkOptionToWidget(const void* optionStorage, QWidget* widget);

	static void getDefaultEncoding(const QByteArray& unused, QTextCodec* &guess, int &sure);
private:
	void setInterfaceStyle();

	QList<QTreeWidgetItem*> changedItemsList;

	QMap<QString,QVariant> manipulatedMenus;

	QList<ManagedProperty> managedProperties;

	QMap<QWidget*, QList<QWidget*> > managedOptionDialogs;
	ManagedProperty* getManagedProperty(const void* storage);
private slots:
	void browseCommand();
	void undoCommand();
	void latexTreeItemChanged(QTreeWidgetItem* item,int l);
	void activateInternalViewer(bool activated);

	void managedOptionDialogAccepted();
};
#endif
