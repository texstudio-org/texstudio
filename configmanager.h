#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "mostQtHeaders.h"

#include "buildmanager.h"


class ConfigDialog;
class LatexCompleterConfig;
class LatexEditorViewConfig;
class WebPublishDialogConfig;

class ConfigManager: public QObject {
	Q_OBJECT
public:
	ConfigManager(QObject *parent=0);
	
	QSettings* readSettings();
	QSettings* saveSettings();

	ConfigDialog* createConfigDialog(QWidget* parent);
	bool execConfigDialog(ConfigDialog* confDlg);

//public configuration

	QTextCodec* newfile_encoding;
	bool autodetectLoadedFile;
	int ignoreLogFileNames; //0: never, 1: in single mode, 2: always | see LatexLog::parseDocument for reason

	QStringList keyReplace, keyReplaceAfterWord, keyReplaceBeforeWord;
	
	//build
	BuildManager* buildManager; 
	bool showLogAfterCompiling;
	
	//appearance 
	QString interfaceStyle;
	QString interfaceFontFamily;
	bool modernStyle;
	int interfaceFontSize;
	bool tabbedLogView;
	bool newLeftPanelLayout;
	bool configShowAdvancedOptions;
	
	//language
	QString lastLanguage;
	QString language;
	QTranslator* appTranslator;
	QTranslator* basicTranslator;	
	
	
	//editor 
	LatexEditorViewConfig * const editorConfig;
	//completion
	LatexCompleterConfig * const completerConfig;
	//webpublish dialog
	WebPublishDialogConfig * const webPublishDialogConfig;
	
	//other dialogs
	int lastHardWrapColumn;
	
	//preview
	enum PreviewMode {PM_TOOLTIP_AS_FALLBACK=0, PM_PANEL,PM_TOOLTIP,PM_BOTH};
	PreviewMode previewMode; 
	
	//files
	QString lastDocument; //last opened document, for file open directory
	QStringList recentFilesList, recentProjectList;
	int maxRecentFiles, maxRecentProjects;
	bool sessionRestore;
	QStringList sessionFilesToRestore;
	QString sessionMaster;
	QString sessionCurrent;
	bool parseBibTeX, parseMaster;
	
	bool addRecentFile(const QString & fileName, bool asMaster); //adds a recent file
	void updateRecentFiles(bool alwaysRecreateMenuItems=false);
	
	//debug
	#ifndef QT_NO_DEBUG
	QDateTime debugLastFileModification;
	#endif
	
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
	QAction* getManagedAction(QString id);
	QMenu* getManagedMenu(QString id);
	void removeManagedMenus();
	void triggerManagedAction(QString id);
	
	void modifyManagedShortcuts();
	void loadManagedMenu(QMenu* parent,const QDomElement &f);
	void loadManagedMenus(const QString &f);
	void managedMenuToTreeWidget(QTreeWidgetItem* parent, QMenu* menu);
	void treeWidgetToManagedMenuTo(QTreeWidgetItem* item);

signals:
	void tabbedLogViewChanged(bool changed);
	void newLeftPanelLayoutChanged(bool newValue);
public:
//private:
	QString configFileName,configFileNameBase,defaultStyleName;
	QMap<QPushButton*, BuildManager::LatexCommand> buttonsToCommands;
	QMap<BuildManager::LatexCommand, QLineEdit*> commandsToEdits;
	void loadTranslations(QString locale);
private slots:
	void browseCommand();
	void undoCommand();
};
#endif
