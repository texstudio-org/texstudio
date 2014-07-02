#ifndef WEBPUBLISHDIALOGCONFIG_H
#define WEBPUBLISHDIALOGCONFIG_H

//having the configuration in a single file allows to change it, 
//without having a relationship between completer and configmanager
//so modifying one doesn't lead to a recompilation of the other

#include <QSettings>

class WebPublishDialogConfig
{
public:
	int userwidth, compil, tocdepth, startindex, navigation;
	bool noindex;
	QString title, address, browser, contentname, align, lastdir, dviopt;

	void readSettings(QSettings& settings);
	void saveSettings(QSettings& settings);
private:
};

//implemented in webpublishdialog.cpp

#endif
