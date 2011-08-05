#ifndef SCRIPTOBJECT_H
#define SCRIPTOBJECT_H

#include <QObject>
#include "qdocumentcursor.h"
class ProcessX;
class BuildManager;
class ScriptObject : public QObject
{
	Q_OBJECT

public:
	explicit ScriptObject(const QString& script, BuildManager* buildManager);
signals:

public slots:
	void alert(const QString& message);
	void information(const QString& message);
	void critical(const QString& message);
	void warning(const QString& message);
	bool confirm(const QString& message);
	bool confirmWarning(const QString& message);
	
	ProcessX* system(const QString& commandline);
	
	void writeFile(const QString& filename, const QString& content);
	QVariant readFile(const QString& filename);
private:
	const QString& script;
	BuildManager* buildManager;
	QByteArray scriptHash;
	bool privileges;
	bool needPrivileges(const QString& commandline);
};

#endif // SCRIPTOBJECT_H
