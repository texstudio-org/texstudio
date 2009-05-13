
#include "configmanager.h"

#include "latexeditorview.h"
#include "smallUsefulFunctions.h"

#include <QFile>
#include <QStyleFactory>

ConfigManager::ConfigManager(QObject *parent): QObject (parent){
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

	newfile_encoding=QTextCodec::codecForName(config->value("Files/New File Encoding", "utf-8").toString().toAscii().data());
	autodetectLoadedFile=config->value("Files/Auto Detect Encoding Of Loaded Files", "true").toBool();

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
	
	
	config->endGroup();

	return config;
}
QSettings* ConfigManager::saveSettings() {
	QSettings *config=new QSettings(configFileName, QSettings::IniFormat);
	config->setValue("IniMode",true);

	config->beginGroup("texmaker");

	//-----------------------files------------------------
	config->setValue("Files/New File Encoding", newfile_encoding?newfile_encoding->name():"??");
	config->setValue("Files/Auto Detect Encoding Of Loaded Files", autodetectLoadedFile);

	//-------------------key replacements-----------------
	int keyReplaceCount = keyReplace.count();
	config->setValue("User/KeyReplaceCount",keyReplaceCount);
	for (int i=0; i<keyReplaceCount; i++) {
		config->setValue("User/KeyReplace"+QVariant(i).toString(),keyReplace[i]);
		config->setValue("User/KeyReplaceAfterWord"+QVariant(i).toString(),keyReplaceAfterWord[i]);
		config->setValue("User/KeyReplaceBeforeWord"+QVariant(i).toString(),keyReplaceBeforeWord[i]);
	}

	//------------------appearance---------------------
	config->setValue("X11/Style",interfaceStyle); //named X11/ for backward compatibility
	config->setValue("X11/Font Family",interfaceFontFamily);
	config->setValue("X11/Font Size",interfaceFontSize);

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
	QTreeWidgetItem * mainItem=new QTreeWidgetItem((QTreeWidget*)0, QStringList() << ConfigDialog::tr("Editor"));
	//add special key replacements
	QTreeWidgetItem * keyReplacements = new QTreeWidgetItem(mainItem, QStringList() << ConfigDialog::tr("Special Key Replacement"));
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
	confDlg->ui.shortcutTree->addTopLevelItem(mainItem);
	mainItem->setExpanded(true);

	ShortcutDelegate delegate;
	delegate.treeWidget=confDlg->ui.shortcutTree;
	confDlg->ui.shortcutTree->setItemDelegate(&delegate); //setting in the config dialog doesn't work
	delegate.connect(confDlg->ui.shortcutTree,SIGNAL(itemClicked(QTreeWidgetItem *, int)),&delegate,SLOT(treeWidgetItemClicked(QTreeWidgetItem * , int)));

	//editor
	if (newfile_encoding)
		confDlg->ui.comboBoxEncoding->setCurrentIndex(confDlg->ui.comboBoxEncoding->findText(newfile_encoding->name(), Qt::MatchExactly));
	confDlg->ui.checkBoxAutoDetectOnLoad->setChecked(autodetectLoadedFile);

	//completion lists
	QStringList files=findResourceFiles("completion","*.cwl");
	QListWidgetItem *item;
	foreach(QString elem,files) {
		item=new QListWidgetItem(elem,confDlg->ui.completeListWidget);
		item->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
		if (words.contains(elem)) item->setCheckState(Qt::Checked);
		else  item->setCheckState(Qt::Unchecked);
	}

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

	//editor font
	confDlg->ui.comboBoxFont->lineEdit()->setText(editorFont.family());
	confDlg->ui.spinBoxSize->setValue(editorFont.pointSize());
	
	
	//EXECUTE IT
	bool executed = confDlg->exec();
	//handle changes
	if (executed) {
		newfile_encoding=QTextCodec::codecForName(confDlg->ui.comboBoxEncoding->currentText().toAscii().data());
		autodetectLoadedFile=confDlg->ui.checkBoxAutoDetectOnLoad->isChecked();

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
		
		//  editor font
		QString fam=confDlg->ui.comboBoxFont->lineEdit()->text();
		int si=confDlg->ui.spinBoxSize->value();
		editorFont=QFont (fam,si);		
	}
	return executed;
}

