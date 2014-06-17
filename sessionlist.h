#ifndef SESSIONLIST_H
#define SESSIONLIST_H

#include "mostQtHeaders.h"

class ConfigManager;

class SessionList: public QObject
{
	Q_OBJECT
public:
	SessionList(QMenu *menu, QObject *parent);

	void addFilenameToList(const QString &file);
	void updateMostRecentMenu();
signals:
	void loadSessionRequest(const QString &filename);
private slots:
	void menuActionTriggered();
private:
	QMenu *m_menu;
	ConfigManager *m_config;
};

#endif // SESSIONLIST_H
