#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "configdialog.h"
#include <QSettings>
#include <QStyle>

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


	QStringList keyReplace, keyReplaceAfterWord, keyReplaceBeforeWord;
	QStringList words;

	//appearance 
	QString interfaceStyle;
	QString interfaceFontFamily;
	int interfaceFontSize;
	
	QFont editorFont;
	
//private:
	QString configFileName,configFileNameBase;
	QStyle* defaultStyle;
};
#endif
