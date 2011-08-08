#ifndef SCRIPTOBJECT_H
#define SCRIPTOBJECT_H

#include <QObject>
#include "qdocumentcursor.h"
class ProcessX;
class BuildManager;
class ScriptObject;

//script object  for texworks compatibility
class SubScriptObject : public QObject
{
	Q_OBJECT
public:	
	ScriptObject *script;
	
public slots:
	QByteArray getScriptHash();

	bool hasGlobal(const QString& name);
	void setGlobal(const QString& name, const QVariant& value);
	QVariant getGlobal(const QString& name);
	
	bool hasPersistent(const QString& name);
	void setPersistent(const QString& name, const QVariant& value);
	QVariant getPersistent(const QString& name);
};

//global scope object
class ScriptObject : public QObject
{
	Q_OBJECT

	Q_PROPERTY(SubScriptObject* script READ getScript DESIGNABLE false STORED false CONSTANT FINAL)
public:
	explicit ScriptObject(const QString& script, BuildManager* buildManager);

	QByteArray getScriptHash();
signals:

public slots:
	void alert(const QString& message);
	void information(const QString& message);
	void critical(const QString& message);
	void warning(const QString& message);
	bool confirm(const QString& message);
	bool confirmWarning(const QString& message);
	
	bool hasPrivileges();
	
	ProcessX* system(const QString& commandline);
		
	void writeFile(const QString& filename, const QString& content);
	QVariant readFile(const QString& filename);	
	
private:
	const QString& script;
	BuildManager* buildManager;
	QByteArray scriptHash;
	bool needPrivileges(const QString& commandline);
	SubScriptObject subScriptObject;
	SubScriptObject* getScript();
};

#endif // SCRIPTOBJECT_H
