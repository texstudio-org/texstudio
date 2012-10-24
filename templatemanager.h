#ifndef TEMPLATEMANAGER_H
#define TEMPLATEMANAGER_H

#include <QObject>

class TemplateManager : public QObject
{
	Q_OBJECT
public:
	explicit TemplateManager(QObject *parent = 0);
	
	static void setUserTemplateDir(const QString &dir) { userTemplateDir = dir; }
	static QString getUserTemplateDir() { return userTemplateDir; }

	static bool ensureUserTemplateDirExists();
	static void checkForOldUserTemplates();

signals:
	
public slots:

private:
	static QString userTemplateDir;
};

#endif // TEMPLATEMANAGER_H
