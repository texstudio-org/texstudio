
#include "configmanager.h"

#include "latexeditorview.h"
#include "smallUsefulFunctions.h"

#include <QFile>
QSettings* ConfigManager::readSettings(){
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
            QSettings oldconfig (QSettings::IniFormat,QSettings::UserScope,"xm1","texmaker");
            QStringList keys=oldconfig.allKeys();
            foreach (QString key, keys) config->setValue(key,oldconfig.value(key,""));
        }
    }
    configFileName=config->fileName();
    configFileNameBase=configFileName;
    if (configFileNameBase.endsWith(".ini")) configFileNameBase=configFileNameBase.replace(QString(".ini"),"");

    config->beginGroup( "texmaker" );

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
    } else for (int i=0;i<keyReplaceCount;i++) {
      keyReplace.append(config->value("User/KeyReplace"+QVariant(i).toString(),i!=0?"'":"\"").toString());
      keyReplaceAfterWord.append(config->value("User/KeyReplaceAfterWord"+QVariant(i).toString(),i!=0?"":"").toString());
      keyReplaceBeforeWord.append(config->value("User/KeyReplaceBeforeWord"+QVariant(i).toString(),i!=0?"":"\">").toString());
    }
    LatexEditorView::setKeyReplacements(&keyReplace,&keyReplaceAfterWord,&keyReplaceBeforeWord);
    
    config->endGroup( );
    
    return config;
}
QSettings* ConfigManager::saveSettings(){
    QSettings *config=new QSettings (configFileName, QSettings::IniFormat);
    config->setValue( "IniMode",true);

    config->beginGroup( "texmaker" );

    config->setValue("Files/New File Encoding", newfile_encoding?newfile_encoding->name():"??");
    config->setValue("Files/Auto Detect Encoding Of Loaded Files", autodetectLoadedFile);


    int keyReplaceCount = keyReplace.count();
    config->setValue("User/KeyReplaceCount",keyReplaceCount);
    for (int i=0;i<keyReplaceCount;i++) {
      config->setValue("User/KeyReplace"+QVariant(i).toString(),keyReplace[i]);
      config->setValue("User/KeyReplaceAfterWord"+QVariant(i).toString(),keyReplaceAfterWord[i]);
      config->setValue("User/KeyReplaceBeforeWord"+QVariant(i).toString(),keyReplaceBeforeWord[i]);
    }

    config->endGroup( );
    
    return config;
}


ConfigDialog* ConfigManager::createConfigDialog(QWidget* parent){
    ConfigDialog *confDlg = new ConfigDialog(parent);
    return confDlg;
}
bool ConfigManager::execConfigDialog(ConfigDialog* confDlg){
    QTreeWidgetItem * mainItem=new QTreeWidgetItem((QTreeWidget*)0, QStringList() << ConfigDialog::tr("Editor"));
    //add special key replacements
    QTreeWidgetItem * keyReplacements = new QTreeWidgetItem(mainItem, QStringList() << ConfigDialog::tr("Special Key Replacement"));
    QTreeWidgetItem * columnItem=new QTreeWidgetItem(keyReplacements, QStringList() << ConfigDialog::tr("New column meaning:") << ConfigDialog::tr("Key to replace") << ConfigDialog::tr("Text to insert before word") << ConfigDialog::tr("Text to insert after word"));
    QFont f;f.setUnderline(true);
    columnItem->setFont(0,f);
    f.setBold(true);
    columnItem->setFont(1,f);columnItem->setFont(2,f);columnItem->setFont(3,f);
    for (int i=0;i<keyReplace.size();i++) 
        (new QTreeWidgetItem(keyReplacements, QStringList() << ShortcutDelegate::deleteRowButton << keyReplace[i] << keyReplaceBeforeWord[i] << keyReplaceAfterWord[i]))
        ->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
    new QTreeWidgetItem(keyReplacements, QStringList() << ShortcutDelegate::addRowButton );
    confDlg->ui.shortcutTree->addTopLevelItem(mainItem);
    mainItem->setExpanded(true);

    ShortcutDelegate delegate;
    delegate.treeWidget=confDlg->ui.shortcutTree;
    confDlg->ui.shortcutTree->setItemDelegate(&delegate); //setting in the config dialog doesn't work 
    delegate.connect(confDlg->ui.shortcutTree,SIGNAL(itemClicked (QTreeWidgetItem *, int)),&delegate,SLOT(treeWidgetItemClicked(QTreeWidgetItem * , int)));

    //editor
    if (newfile_encoding)
        confDlg->ui.comboBoxEncoding->setCurrentIndex(confDlg->ui.comboBoxEncoding->findText(newfile_encoding->name(), Qt::MatchExactly));
    confDlg->ui.checkBoxAutoDetectOnLoad->setChecked(autodetectLoadedFile);
    
    //completion lists
    QStringList files=findResourceFiles("completion","*.cwl");
    QListWidgetItem *item;
    foreach(QString elem,files)
    {
        item=new QListWidgetItem(elem,confDlg->ui.completeListWidget);
        item->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        if(words.contains(elem)) item->setCheckState(Qt::Checked);
        else  item->setCheckState(Qt::Unchecked);
    }



    bool executed = confDlg->exec();
    if (executed) {
        newfile_encoding=QTextCodec::codecForName(confDlg->ui.comboBoxEncoding->currentText().toAscii().data());
        autodetectLoadedFile=confDlg->ui.checkBoxAutoDetectOnLoad->isChecked();

        keyReplace.clear();
        keyReplaceBeforeWord.clear();
        keyReplaceAfterWord.clear();
        for (int i=1;i<keyReplacements->childCount()-1;i++){
            keyReplace << keyReplacements->child(i)->text(1);
            keyReplaceBeforeWord << keyReplacements->child(i)->text(2);
            keyReplaceAfterWord << keyReplacements->child(i)->text(3);
        }
        confDlg->fmConfig->apply();

        words.clear();
        QListWidgetItem *elem;
        for(int i=0;i<confDlg->ui.completeListWidget->count();i++)
        {
            elem=confDlg->ui.completeListWidget->item(i);
            if(elem->checkState()==Qt::Checked) words.append(elem->text());
        }
    }
    return executed;
}

