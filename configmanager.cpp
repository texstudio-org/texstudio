
#include "configmanager.h"

#include "latexeditorview.h"
#include "smallUsefulFunctions.h"

#include <QFile>
#include <QMessageBox>
#include <QStyleFactory>

ConfigManager::ConfigManager(QObject *parent): QObject (parent),buildManager(0),menuParent(0), menuParentsBar(0){
}

QSettings* ConfigManager::readSettings() {
	//load config
	bool usbMode = isExistingFileRealWritable(QCoreApplication::applicationDirPath()+"/texmakerx.ini");
	if (!usbMode)
		if (isExistingFileRealWritable(QCoreApplication::applicationDirPath()+"/texmaker.ini")) {
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
			QSettings oldconfig(QSettings::IniFormat,QSettings::UserScope,"xm1","texmaker");
			QStringList keys=oldconfig.allKeys();
			foreach(QString key, keys) config->setValue(key,oldconfig.value(key,""));
		}
	}
	configFileName=config->fileName();
	configFileNameBase=configFileName;
	if (configFileNameBase.endsWith(".ini")) configFileNameBase=configFileNameBase.replace(QString(".ini"),"");

	config->beginGroup("texmaker");

	//-----------------------files---------------------------
	//editor
	newfile_encoding=QTextCodec::codecForName(config->value("Files/New File Encoding", "utf-8").toString().toAscii().data());
	autodetectLoadedFile=config->value("Files/Auto Detect Encoding Of Loaded Files", "true").toBool();

	ignoreLogFileNames=config->value("Files/Ignore Log File Names",1).toInt(); //default only ignore in single mode

	//preview
	//todo...
	previewShownInOutputView=true;
	previewShownInTooltip=true;

	//recent files
	maxRecentFiles=config->value("Files/Max Recent Files", 5).toInt();
	maxRecentProjects=config->value("Files/Max Recent Projects", 3).toInt();
	recentFilesList=config->value("Files/Recent Files").toStringList();
	recentProjectList=config->value("Files/Recent Project Files").toStringList();
	if (config->value("Files/RestoreSession",false).toBool()) {
		sessionFilesToRestore=config->value("Files/Session/Files").toStringList();
		sessionCurrent=config->value("Files/Session/CurrentFile","").toString();
		sessionMaster=config->value("Files/Session/MasterFile","").toString();
	}
	lastDocument=config->value("Files/Last Document","").toString();

	//build commands
	if (!buildManager) QMessageBox::critical(0,"TexMakerX","No build Manager created! => crash",QMessageBox::Ok);
	buildManager->readSettings(*config);
	
	//read user key replacements
	keyReplace.clear();
	keyReplaceAfterWord.clear();
	keyReplaceBeforeWord.clear();
	int keyReplaceCount = config->value("User/KeyReplaceCount",-1).toInt();
	if (keyReplaceCount ==-1) {
		//default
		keyReplace.append("\"");
		QString loc=QString(QLocale::system().name()).left(2);
		if (loc=="de") {
			keyReplaceBeforeWord.append("\">");
			keyReplaceAfterWord.append("\"<");

			keyReplace.append("'");
			keyReplaceBeforeWord.append("''");
			keyReplaceAfterWord.append("``");
		} else {
			keyReplaceBeforeWord.append("''");
			keyReplaceAfterWord.append("``");
		}
		keyReplace.append("%");
		keyReplaceBeforeWord.append("%");
		keyReplaceAfterWord.append(" %");
	} else for (int i=0; i<keyReplaceCount; i++) {
			keyReplace.append(config->value("User/KeyReplace"+QVariant(i).toString(),i!=0?"'":"\"").toString());
			keyReplaceAfterWord.append(config->value("User/KeyReplaceAfterWord"+QVariant(i).toString(),i!=0?"":"").toString());
			keyReplaceBeforeWord.append(config->value("User/KeyReplaceBeforeWord"+QVariant(i).toString(),i!=0?"":"\">").toString());
		}
	LatexEditorView::setKeyReplacements(&keyReplace,&keyReplaceAfterWord,&keyReplaceBeforeWord);

	//menu shortcuts
	int size = config->beginReadArray("keysetting");
	for (int i = 0; i < size; ++i) {
		config->setArrayIndex(i);
		managedMenuNewShortcuts.append(QPair<QString, QString> (config->value("id").toString(), config->value("key").toString()));
	}
	config->endArray();
	
	
	//--------------------appearance------------------------------------
	QFontDatabase fdb;
	QStringList xf = fdb.families();
	QString deft;
	//editor
#ifdef Q_WS_WIN
	if (xf.contains("Courier New",Qt::CaseInsensitive)) deft="Courier New";
	else deft=qApp->font().family();
	QString fam=config->value("Editor/Font Family",deft).toString();
	int si=config->value("Editor/Font Size",10).toInt();
#else
	if (xf.contains("DejaVu Sans Mono",Qt::CaseInsensitive)) deft="DejaVu Sans Mono";
//else if (xf.contains("Lucida Sans Unicode",Qt::CaseInsensitive)) deft="Lucida Sans Unicode";
	else if (xf.contains("Lucida Sans Typewriter",Qt::CaseInsensitive)) deft="Lucida Sans Typewriter";
	else deft=qApp->font().family();
	QString fam=config->value("Editor/Font Family",deft).toString();
	int si=config->value("Editor/Font Size",qApp->font().pointSize()).toInt();
#endif
	editorFont=QFont(fam,si);
	
	//interface
#ifdef Q_WS_X11
	if ((x11desktop_env() != 4) || (!QStyleFactory::keys().contains("Oxygen")))
		interfaceStyle="Plastique"; //plastique style if not kde4
	else
		interfaceStyle="";
		
	if (xf.contains("DejaVu Sans",Qt::CaseInsensitive)) interfaceFontFamily="DejaVu Sans";
	else if (xf.contains("DejaVu Sans LGC",Qt::CaseInsensitive)) interfaceFontFamily="DejaVu Sans LGC";
	else if (xf.contains("Bitstream Vera Sans",Qt::CaseInsensitive)) interfaceFontFamily="Bitstream Vera Sans";
	else if (xf.contains("Luxi Sans",Qt::CaseInsensitive)) interfaceFontFamily="Luxi Sans";
	else interfaceFontFamily=QApplication::font().family();
#else
	interfaceStyle="";
	interfaceFontFamily=QApplication::font().family();
#endif
		
	interfaceStyle=config->value("X11/Style",interfaceStyle).toString(); //named X11 for backward compatibility
	defaultStyle=QApplication::style();
	if (interfaceStyle!="") QApplication::setStyle(interfaceStyle); 

	interfaceFontFamily = config->value("X11/Font Family",QApplication::font().family()).toString();
	interfaceFontSize = config->value("X11/Font Size",QApplication::font().pointSize()).toInt();		
	QApplication::setFont(QFont(interfaceFontFamily, interfaceFontSize));
	
#ifdef Q_WS_X11
	QPalette pal = QApplication::palette();
	pal.setColor(QPalette::Active, QPalette::Highlight, QColor("#4490d8"));
	pal.setColor(QPalette::Inactive, QPalette::Highlight, QColor("#4490d8"));
	pal.setColor(QPalette::Disabled, QPalette::Highlight, QColor("#4490d8"));

	pal.setColor(QPalette::Active, QPalette::HighlightedText, QColor("#ffffff"));
	pal.setColor(QPalette::Inactive, QPalette::HighlightedText, QColor("#ffffff"));
	pal.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor("#ffffff"));

	pal.setColor(QPalette::Active, QPalette::Base, QColor("#ffffff"));
	pal.setColor(QPalette::Inactive, QPalette::Base, QColor("#ffffff"));
	pal.setColor(QPalette::Disabled, QPalette::Base, QColor("#ffffff"));

	pal.setColor(QPalette::Active, QPalette::WindowText, QColor("#000000"));
	pal.setColor(QPalette::Inactive, QPalette::WindowText, QColor("#000000"));
	pal.setColor(QPalette::Disabled, QPalette::WindowText, QColor("#000000"));

	pal.setColor(QPalette::Active, QPalette::ButtonText, QColor("#000000"));
	pal.setColor(QPalette::Inactive, QPalette::ButtonText, QColor("#000000"));
	pal.setColor(QPalette::Disabled, QPalette::ButtonText, QColor("#000000"));

	if (x11desktop_env() ==4) {
		pal.setColor(QPalette::Active, QPalette::Window, QColor("#eae9e9"));
		pal.setColor(QPalette::Inactive, QPalette::Window, QColor("#eae9e9"));
		pal.setColor(QPalette::Disabled, QPalette::Window, QColor("#eae9e9"));

		pal.setColor(QPalette::Active, QPalette::Button, QColor("#eae9e9"));
		pal.setColor(QPalette::Inactive, QPalette::Button, QColor("#eae9e9"));
		pal.setColor(QPalette::Disabled, QPalette::Button, QColor("#eae9e9"));
	} else {
		pal.setColor(QPalette::Active, QPalette::Window, QColor("#fbf8f1"));
		pal.setColor(QPalette::Inactive, QPalette::Window, QColor("#fbf8f1"));
		pal.setColor(QPalette::Disabled, QPalette::Window, QColor("#fbf8f1"));

		pal.setColor(QPalette::Active, QPalette::Button, QColor("#fbf8f1"));
		pal.setColor(QPalette::Inactive, QPalette::Button, QColor("#fbf8f1"));
		pal.setColor(QPalette::Disabled, QPalette::Button, QColor("#fbf8f1"));
	}

	QApplication::setPalette(pal);
#endif

	tabbedLogView=config->value("LogView/Tabbed","true").toBool();
	
	
	config->endGroup();

	return config;
}
QSettings* ConfigManager::saveSettings() {
	QSettings *config=new QSettings(configFileName, QSettings::IniFormat);
	config->setValue("IniMode",true);

	config->beginGroup("texmaker");

	//-----------------------files------------------------
	//editor
	config->setValue("Files/New File Encoding", newfile_encoding?newfile_encoding->name():"??");
	config->setValue("Files/Auto Detect Encoding Of Loaded Files", autodetectLoadedFile);
	
	config->setValue("Files/Ignore Log File Names",ignoreLogFileNames);
	
	//recent files
	config->setValue("Files/Max Recent Files", maxRecentFiles);
	config->setValue("Files/Max Recent Projects", maxRecentProjects);
	if (recentFilesList.count()>0) config->setValue("Files/Recent Files",recentFilesList);
	if (recentProjectList.count()>0) config->setValue("Files/Recent Project Files",recentProjectList);
	//session is saved by main class (because we don't know the active files here)
	config->setValue("Files/Last Document",lastDocument);
	
	//---------------------build commands----------------
	buildManager->saveSettings(*config);
	
	//-------------------key replacements-----------------
	int keyReplaceCount = keyReplace.count();
	config->setValue("User/KeyReplaceCount",keyReplaceCount);
	for (int i=0; i<keyReplaceCount; i++) {
		config->setValue("User/KeyReplace"+QVariant(i).toString(),keyReplace[i]);
		config->setValue("User/KeyReplaceAfterWord"+QVariant(i).toString(),keyReplaceAfterWord[i]);
		config->setValue("User/KeyReplaceBeforeWord"+QVariant(i).toString(),keyReplaceBeforeWord[i]);
	}

	//menu shortcuts
	config->beginWriteArray("keysetting");
	for (int i = 0; i < managedMenuNewShortcuts.size(); ++i) {
		config->setArrayIndex(i);
		config->setValue("id", managedMenuNewShortcuts[i].first);
		config->setValue("key", managedMenuNewShortcuts[i].second);
	}
	config->endArray();

	//------------------appearance---------------------
	//config->setValue("Interface/Language",language); //named X11/ for backward compatibility

	config->setValue("X11/Style",interfaceStyle); //named X11/ for backward compatibility
	config->setValue("X11/Font Family",interfaceFontFamily);
	config->setValue("X11/Font Size",interfaceFontSize);

	config->setValue("LogView/Tabbed",tabbedLogView);
	
	//editor
	config->setValue("Editor/Font Family",editorFont.family());
	config->setValue("Editor/Font Size",editorFont.pointSize());
	
	config->endGroup();

	return config;
}


ConfigDialog* ConfigManager::createConfigDialog(QWidget* parent) {
	ConfigDialog *confDlg = new ConfigDialog(parent);
	return confDlg;
}
bool ConfigManager::execConfigDialog(ConfigDialog* confDlg) {

	//files
	if (newfile_encoding)
		confDlg->ui.comboBoxEncoding->setCurrentIndex(confDlg->ui.comboBoxEncoding->findText(newfile_encoding->name(), Qt::MatchExactly));
	confDlg->ui.checkBoxAutoDetectOnLoad->setChecked(autodetectLoadedFile);
	confDlg->ui.comboBoxIgnoreLogFileNames->setCurrentIndex(ignoreLogFileNames);
	
	confDlg->ui.spinBoxMaxRecentFiles->setValue(maxRecentFiles);
	confDlg->ui.spinBoxMaxRecentProjects->setValue(maxRecentProjects);
	
	//build things
	confDlg->ui.lineEditLatex->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_LATEX));
	confDlg->ui.lineEditPdflatex->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_PDFLATEX));
	confDlg->ui.lineEditDvips->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_DVIPS));
	confDlg->ui.lineEditDviviewer->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_VIEWDVI));
	confDlg->ui.lineEditPsviewer->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_VIEWPS));
	confDlg->ui.lineEditDvipdfm->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_DVIPDF));
	confDlg->ui.lineEditPs2pdf->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_PS2PDF));
	confDlg->ui.lineEditBibtex->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_BIBTEX));
	confDlg->ui.lineEditMakeindex->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_MAKEINDEX));
	confDlg->ui.lineEditPdfviewer->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_VIEWPDF));
	confDlg->ui.lineEditMetapost->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_METAPOST));
	confDlg->ui.lineEditGhostscript->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_GHOSTSCRIPT));
	confDlg->ui.lineEditExecuteBeforeCompiling->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_USER_PRECOMPILE));
	confDlg->ui.lineEditUserquick->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_USER_QUICK));
	
	//completion lists
	QStringList files=findResourceFiles("completion","*.cwl");
	QListWidgetItem *item;
	foreach(QString elem,files) {
		item=new QListWidgetItem(elem,confDlg->ui.completeListWidget);
		item->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
		if (words.contains(elem)) item->setCheckState(Qt::Checked);
		else  item->setCheckState(Qt::Unchecked);
	}

	//menu shortcuts
	QTreeWidgetItem * menuShortcuts=new QTreeWidgetItem((QTreeWidget*)0, QStringList() << QString(tr("Menus")));
	foreach(QMenu* menu, managedMenus)
	managedMenuToTreeWidget(menuShortcuts,menu);
	confDlg->ui.shortcutTree->addTopLevelItem(menuShortcuts);
	menuShortcuts->setExpanded(true);

	QTreeWidgetItem * editorItem=new QTreeWidgetItem((QTreeWidget*)0, QStringList() << ConfigDialog::tr("Editor"));
	//add special key replacements
	QTreeWidgetItem * keyReplacements = new QTreeWidgetItem(editorItem, QStringList() << ConfigDialog::tr("Special Key Replacement"));
	QTreeWidgetItem * columnItem=new QTreeWidgetItem(keyReplacements, QStringList() << ConfigDialog::tr("New column meaning:") << ConfigDialog::tr("Key to replace") << ConfigDialog::tr("Text to insert before word") << ConfigDialog::tr("Text to insert after word"));
	QFont f;
	f.setUnderline(true);
	columnItem->setFont(0,f);
	f.setBold(true);
	columnItem->setFont(1,f);
	columnItem->setFont(2,f);
	columnItem->setFont(3,f);
	for (int i=0; i<keyReplace.size(); i++)
		(new QTreeWidgetItem(keyReplacements, QStringList() << ShortcutDelegate::deleteRowButton << keyReplace[i] << keyReplaceBeforeWord[i] << keyReplaceAfterWord[i]))
		->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
	new QTreeWidgetItem(keyReplacements, QStringList() << ShortcutDelegate::addRowButton);
	confDlg->ui.shortcutTree->addTopLevelItem(editorItem);
	editorItem->setExpanded(true);

	ShortcutDelegate delegate;
	delegate.treeWidget=confDlg->ui.shortcutTree;
	confDlg->ui.shortcutTree->setItemDelegate(&delegate); //setting in the config dialog doesn't work
	delegate.connect(confDlg->ui.shortcutTree,SIGNAL(itemClicked(QTreeWidgetItem *, int)),&delegate,SLOT(treeWidgetItemClicked(QTreeWidgetItem * , int)));

	//appearance
	confDlg->ui.comboBoxInterfaceStyle->clear();
	confDlg->ui.comboBoxInterfaceStyle->addItems(QStyleFactory::keys()<<tr("default"));
	if (interfaceStyle=="") //default
		confDlg->ui.comboBoxInterfaceStyle->setCurrentIndex(confDlg->ui.comboBoxInterfaceStyle->count()-1);
	else 
		confDlg->ui.comboBoxInterfaceStyle->setCurrentIndex(QStyleFactory::keys().indexOf(interfaceStyle));
	confDlg->ui.comboBoxInterfaceStyle->setEditText(interfaceStyle);
	confDlg->ui.comboBoxInterfaceFont->setCurrentFont(QFont(interfaceFontFamily));
	confDlg->ui.spinBoxInterfaceFontSize->setValue(interfaceFontSize);

	confDlg->ui.checkBoxTabbedLogView->setChecked(tabbedLogView);
	
	//editor font
	confDlg->ui.comboBoxFont->lineEdit()->setText(editorFont.family());
	confDlg->ui.spinBoxSize->setValue(editorFont.pointSize());
	
	
	//EXECUTE IT
	bool executed = confDlg->exec();
	//handle changes
	if (executed) {
		//files
		newfile_encoding=QTextCodec::codecForName(confDlg->ui.comboBoxEncoding->currentText().toAscii().data());
		autodetectLoadedFile=confDlg->ui.checkBoxAutoDetectOnLoad->isChecked();
		ignoreLogFileNames=confDlg->ui.comboBoxIgnoreLogFileNames->currentIndex();
		
		if (maxRecentFiles!=confDlg->ui.spinBoxMaxRecentFiles->value() ||
		   maxRecentProjects != confDlg->ui.spinBoxMaxRecentProjects->value()){
			maxRecentFiles=confDlg->ui.spinBoxMaxRecentFiles->value();
			maxRecentProjects=confDlg->ui.spinBoxMaxRecentProjects->value();
			updateRecentFiles(true);
		}

		//build things
		buildManager->setLatexCommand(BuildManager::CMD_LATEX,confDlg->ui.lineEditLatex->text());
		buildManager->setLatexCommand(BuildManager::CMD_PDFLATEX,confDlg->ui.lineEditPdflatex->text());
		buildManager->setLatexCommand(BuildManager::CMD_DVIPS,confDlg->ui.lineEditDvips->text());
		buildManager->setLatexCommand(BuildManager::CMD_VIEWDVI,confDlg->ui.lineEditDviviewer->text());
		buildManager->setLatexCommand(BuildManager::CMD_VIEWPS,confDlg->ui.lineEditPsviewer->text());
		buildManager->setLatexCommand(BuildManager::CMD_DVIPDF,confDlg->ui.lineEditDvipdfm->text());
		buildManager->setLatexCommand(BuildManager::CMD_PS2PDF,confDlg->ui.lineEditPs2pdf->text());
		buildManager->setLatexCommand(BuildManager::CMD_BIBTEX,confDlg->ui.lineEditBibtex->text());
		buildManager->setLatexCommand(BuildManager::CMD_MAKEINDEX,confDlg->ui.lineEditMakeindex->text());
		buildManager->setLatexCommand(BuildManager::CMD_VIEWPDF,confDlg->ui.lineEditPdfviewer->text());
		buildManager->setLatexCommand(BuildManager::CMD_METAPOST,confDlg->ui.lineEditMetapost->text());
		buildManager->setLatexCommand(BuildManager::CMD_GHOSTSCRIPT,confDlg->ui.lineEditGhostscript->text());
		buildManager->setLatexCommand(BuildManager::CMD_USER_PRECOMPILE,confDlg->ui.lineEditExecuteBeforeCompiling->text());
		buildManager->setLatexCommand(BuildManager::CMD_USER_QUICK,confDlg->ui.lineEditUserquick->text());

		//key replacements
		keyReplace.clear();
		keyReplaceBeforeWord.clear();
		keyReplaceAfterWord.clear();
		for (int i=1; i<keyReplacements->childCount()-1; i++) {
			keyReplace << keyReplacements->child(i)->text(1);
			keyReplaceBeforeWord << keyReplacements->child(i)->text(2);
			keyReplaceAfterWord << keyReplacements->child(i)->text(3);
		}
		confDlg->fmConfig->apply();

		words.clear();
		QListWidgetItem *elem;
		for (int i=0; i<confDlg->ui.completeListWidget->count(); i++) {
			elem=confDlg->ui.completeListWidget->item(i);
			if (elem->checkState()==Qt::Checked) words.append(elem->text());
		}
		
		//menus
		managedMenuNewShortcuts.clear();
		treeWidgetToManagedMenuTo(menuShortcuts);
				
		//appearance
		//  interface
		if (confDlg->ui.comboBoxInterfaceFont->currentFont().family()!=interfaceFontFamily ||
			confDlg->ui.spinBoxInterfaceFontSize->value()!=interfaceFontSize) {
			interfaceFontSize=confDlg->ui.spinBoxInterfaceFontSize->value();
			interfaceFontFamily=confDlg->ui.comboBoxInterfaceFont->currentFont().family();
			QApplication::setFont(QFont(interfaceFontFamily, interfaceFontSize));
		}
		if (confDlg->ui.comboBoxInterfaceStyle->currentText()!=interfaceStyle){
			interfaceStyle=confDlg->ui.comboBoxInterfaceStyle->currentText();
			if (interfaceStyle==tr("default")) interfaceStyle="";
			QPalette pal = QApplication::palette();
			if (interfaceStyle=="") QApplication::setStyle(defaultStyle);
			else QApplication::setStyle(interfaceStyle);
			QApplication::setPalette(pal);
		}
	
		// read checkbox and set logViewer accordingly
		if (tabbedLogView!=confDlg->ui.checkBoxTabbedLogView->isChecked()) 
			emit tabbedLogViewChanged(confDlg->ui.checkBoxTabbedLogView->isChecked());
		tabbedLogView=confDlg->ui.checkBoxTabbedLogView->isChecked();
		
		//  editor font
		QString fam=confDlg->ui.comboBoxFont->lineEdit()->text();
		int si=confDlg->ui.spinBoxSize->value();
		editorFont=QFont (fam,si);		
		
	}
	return executed;
}


bool ConfigManager::addRecentFile(const QString & fileName, bool asMaster){ 
	int p=recentFilesList.indexOf(fileName);
	bool changed=p!=0;
	if (p>0) recentFilesList.removeAt(p);
	if (changed) recentFilesList.prepend(fileName);
	if (recentFilesList.count()>maxRecentFiles) recentFilesList.removeLast();

	if (asMaster) {
		p=recentProjectList.indexOf(fileName);
		changed|=p!=0;
		if (p>0) recentProjectList.removeAt(p);
		if (p!=0) recentProjectList.prepend(fileName);
		if (recentProjectList.count()>maxRecentProjects) recentProjectList.removeLast();
	}

	if (changed) updateRecentFiles();
	
	return changed;
}

void ConfigManager::updateRecentFiles(bool alwaysRecreateMenuItems) {
	QMenu* recentMenu = getManagedMenu("main/file/openrecent");
	if (alwaysRecreateMenuItems || (recentMenu->actions().count()!=maxRecentFiles+maxRecentProjects+1)) {
		QList<QAction*> actions=recentMenu->actions(); //recentMenu->clear() doesn't seem to delete the actions (why?)
		for (int i = 0; i< actions.count(); i++)
			recentMenu->removeAction(actions[i]); //neccessary or it crashes
		for (int i = 0; i < maxRecentProjects; ++i) {
			QAction* old=menuParent->findChild<QAction*>("main/file/openrecent/p"+QString::number(i));
			if (old!=NULL) recentMenu->addAction(old);
			else newManagedAction(recentMenu, "p"+QString::number(i), tr("Recent 'Master Document' %1").arg(i), SLOT(fileOpenRecentProject()))->setVisible(false);
		}
		recentMenu->addSeparator();
		for (int i = 0; i < maxRecentFiles; ++i){
			QAction* old=menuParent->findChild<QAction*>("main/file/openrecent/"+QString::number(i));
			if (old!=NULL) recentMenu->addAction(old);
			else newManagedAction(recentMenu, QString::number(i), tr("Recent File %1").arg(i), SLOT(fileOpenRecent()))->setVisible(false);		
		}
	}

	for (int i=0; i < maxRecentProjects; i++) {
		QAction* act = getManagedAction(QString("main/file/openrecent/p%1").arg(i));
		if (i<recentProjectList.count()) {
			act->setVisible(true);
			act->setText(tr("Master Document: ")+recentProjectList.at(i));
			act->setData(recentProjectList.at(i));
		} else act->setVisible(false);
	}
	for (int i=0; i < maxRecentFiles; i++) {
		QAction* act = getManagedAction(QString("main/file/openrecent/%1").arg(i));
		if (i<recentFilesList.count()) {
			act->setVisible(true);
			act->setText(recentFilesList.at(i));
			act->setData(recentFilesList.at(i));
		} else act->setVisible(false);
	}
}


QMenu* ConfigManager::newManagedMenu(const QString &id,const QString &text) {
	if (!menuParentsBar) qFatal("No menu parent bar!");
	QMenu* menu=menuParentsBar->addMenu(text);
	menu->setObjectName(id);
	managedMenus.append(menu);
	return menu;
}
QMenu* ConfigManager::newManagedMenu(QMenu* menu, const QString &id,const QString &text) {
	if (!menu) return newManagedMenu(id,text);
	QMenu* submenu=menu->addMenu(text);
	submenu->setObjectName(menu->objectName()+"/"+ id);
	return submenu;
}
QAction* ConfigManager::newManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QList<QKeySequence> &shortCuts, const QString & iconFile) {
	if (!menuParent) qFatal("No menu parent!");
	QAction *act;
	if (iconFile.isEmpty()) act=new QAction(text, menuParent);
	else act=new QAction(QIcon(iconFile), text, menuParent);
	act->setShortcuts(shortCuts);
	if (slotName) connect(act, SIGNAL(triggered()), menuParent, slotName);
	act->setObjectName(menu->objectName()+"/"+id);
	menu->addAction(act);
	for (int i=0; i<shortCuts.size(); i++)
		managedMenuShortcuts.insert(act->objectName()+QString::number(i),shortCuts[i]);
	return act;
}
QAction* ConfigManager::newManagedAction(QWidget* menu, const QString &id, QAction* act) {
	act->setObjectName(menu->objectName()+"/"+id);
	menu->addAction(act);
	managedMenuShortcuts.insert(act->objectName()+"0",act->shortcut());
	return act;
}
QAction* ConfigManager::getManagedAction(QString id) {
	QAction* act=0;
	if (menuParent) act=menuParent->findChild<QAction*>(id);
	if (act==0) qWarning("Can't find internal menu %s",id.toAscii().data());
	return act;
}
QMenu* ConfigManager::getManagedMenu(QString id) {
	QMenu* menu=0;
	if (menuParent) menu=menuParent->findChild<QMenu*>(id);
	if (menu==0) qWarning("Can't find internal menu %s",id.toAscii().data());
	return menu;
}
void ConfigManager::triggerManagedAction(QString id){
	QAction* act = getManagedAction(id);
	if (act) act->trigger();
}
void ConfigManager::modifyManagedShortcuts(){
	//modify shortcuts
	for (int i=0; i< managedMenuNewShortcuts.size(); i++) {
		QString id=managedMenuNewShortcuts[i].first;
		int num=-1;
		if (managedMenuNewShortcuts[i].first.endsWith("~0")) num=0;
		else if (managedMenuNewShortcuts[i].first.endsWith("~1")) num=1;
		else { } //backward compatibility
		if (num!=-1) id.chop(2);
		QAction * act= getManagedAction(id);
		if (act) {
			if (num!=1) act->setShortcut(QKeySequence(managedMenuNewShortcuts[i].second));
			else act->setShortcuts((QList<QKeySequence>()<<act->shortcut())<<managedMenuNewShortcuts[i].second);
		}
	}
}
void ConfigManager::loadManagedMenu(QMenu* parent,const QDomElement &f) {
	QMenu *menu = newManagedMenu(parent,f.attributes().namedItem("id").nodeValue(),f.attributes().namedItem("text").nodeValue());
	QDomNodeList children = f.childNodes();
	for (int i = 0; i < children.count(); i++) {
		QDomElement c = children.at(i).toElement();
		if (c.nodeName()=="menu") loadManagedMenu(menu,c);
		else if (c.nodeName()=="insert" || c.nodeName()=="action") {
			QDomNamedNodeMap  att=c.attributes();
			QByteArray ba;
			const char* slotfunc;
			if (c.nodeName()=="insert") slotfunc=SLOT(InsertFromAction());
			else {
				ba=att.namedItem("slot").nodeValue().toLocal8Bit();
				slotfunc=ba.data();
			}
			QAction * act=newManagedAction(menu,
			                               att.namedItem("id").nodeValue(),
			                               att.namedItem("text").nodeValue(),slotfunc,
			                               QList<QKeySequence>()<<  QKeySequence(att.namedItem("shortcut").nodeValue()),
										   att.namedItem("icon").nodeValue());
			act->setWhatsThis(att.namedItem("info").nodeValue());
			act->setData(att.namedItem("insert").nodeValue());
		} else if (c.nodeName()=="separator") menu->addSeparator();
	}
}
void ConfigManager::loadManagedMenus(const QString &f) {
	QFile settings(f);

	if (settings.open(QFile::ReadOnly | QFile::Text)) {
		QDomDocument doc;
		doc.setContent(&settings);

		QDomNodeList f = doc.documentElement().childNodes();

		for (int i = 0; i < f.count(); i++)
			if (f.at(i).nodeName()=="menu")
				loadManagedMenu(0,f.at(i).toElement());
	}
}

void ConfigManager::managedMenuToTreeWidget(QTreeWidgetItem* parent, QMenu* menu) {
	if (!menu) return;
	QTreeWidgetItem* menuitem= new QTreeWidgetItem(parent, QStringList(menu->title().replace("&","")));
	if (menu->objectName().count("/")<=2) menuitem->setExpanded(true);
	QList<QAction *> acts=menu->actions();
	for (int i=0; i<acts.size(); i++)
		if (acts[i]->menu()) managedMenuToTreeWidget(menuitem, acts[i]->menu());
		else {
			QTreeWidgetItem* twi=new QTreeWidgetItem(menuitem, QStringList() << acts[i]->text()
			        << managedMenuShortcuts[acts[i]->objectName()+"0"]
			        << acts[i]->shortcut().toString(QKeySequence::NativeText));
			twi->setIcon(0,acts[i]->icon());
			if (!acts[i]->isSeparator()) twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
			twi->setData(0,Qt::UserRole,acts[i]->objectName());
			if (acts[i]->shortcuts().size()>1) twi->setText(3,acts[i]->shortcuts()[1].toString(QKeySequence::NativeText));
		}


}
void ConfigManager::treeWidgetToManagedMenuTo(QTreeWidgetItem* item) {
	if (item->childCount() > 0) {
		for (int i=0; i< item->childCount(); i++)
			treeWidgetToManagedMenuTo(item->child(i));
	} else {
		QString id=item->data(0,Qt::UserRole).toString();
		if (id=="") return;
		QAction * act=getManagedAction(id);
		if (act) {
			QKeySequence sc=QKeySequence(item->text(2));
			act->setShortcut(sc);
			if (sc!=managedMenuShortcuts.value(act->objectName()+"0",QKeySequence()))
				managedMenuNewShortcuts.append(QPair<QString, QString> (id+"~0", item->text(2)));
			sc=QKeySequence(item->text(3));
			if (item->text(3)!="") act->setShortcuts((QList<QKeySequence>()<<act->shortcut()) << sc);
			if (sc!=managedMenuShortcuts.value(act->objectName()+"1",QKeySequence()))
				managedMenuNewShortcuts.append(QPair<QString, QString> (id+"~1", item->text(3)));
		}
	}
}

