#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "configdialog.h"
#include <QSettings>
class ConfigManager {
public:
    QSettings* readSettings();
    QSettings* saveSettings();
    
    ConfigDialog* createConfigDialog(QWidget* parent); 
    bool execConfigDialog(ConfigDialog* confDlg);
    
//public configuration
    
    QStringList keyReplace, keyReplaceAfterWord, keyReplaceBeforeWord;

//private:
    QString configFileName,configFileNameBase;
};
#endif
