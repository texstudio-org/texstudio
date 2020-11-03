#ifndef SCRIPTOBJECT_H
#define SCRIPTOBJECT_H

#include "modifiedQObject.h"
#include <QVariant>
#include "qdocumentcursor.h"
class ProcessX;
class BuildManager;
class Texstudio;
class ScriptObject;

//script object  for texworks compatibility
class SubScriptObject : public QObject
{
	Q_OBJECT

public:
	ScriptObject *script;

public slots:
	QByteArray getScriptHash();

	bool hasGlobal(const QString &name);
	void setGlobal(const QString &name, const QVariant &value);
	QVariant getGlobal(const QString &name);

	bool hasPersistent(const QString &name);
	void setPersistent(const QString &name, const QVariant &value);
	QVariant getPersistent(const QString &name);
};

//global scope object
class ScriptObject : public QObject
{
	Q_OBJECT

	Q_PROPERTY(SubScriptObject *script READ getScript DESIGNABLE false STORED false)
    //Q_PROPERTY(Texstudio *app READ getApp DESIGNABLE false STORED false)

public:
	explicit ScriptObject(const QString &script, BuildManager *buildManager, Texstudio *app);

	bool backgroundScript;

	QByteArray getScriptHash();
	void registerAllowedWrite();

signals:

public slots:
	void alert(const QString &message);
	void information(const QString &message);
	void critical(const QString &message);
	void warning(const QString &message);
	bool confirm(const QString &message);
	bool confirmWarning(const QString &message);
	void debug(const QString &message);

#ifndef QT_NO_DEBUG
	void crash_assert();
#endif
	void crash_sigsegv();
	void crash_sigfpe();
	void crash_stack();
	void crash_loop();
	void crash_throw();

	bool hasReadPrivileges();
	bool hasWritePrivileges();

	bool fileExists(const QString &fn);

	ProcessX *system(const QString &commandline, const QString &workingDirectory=QString());

	void writeFile(const QString &filename, const QString &content);
	QVariant readFile(const QString &filename);

	bool hasGlobal(const QString &name);
	void setGlobal(const QString &name, const QVariant &value);
	QVariant getGlobal(const QString &name);

	bool hasPersistent(const QString &name);
	void setPersistent(const QString &name, const QVariant &value);
	QVariant getPersistent(const QString &name);

	void registerAsBackgroundScript(const QString &name = "");
    QWidget *createUI(const QString &path, QWidget *parent = nullptr);
    QWidget *createUIFromString(const QString &path, QWidget *parent = nullptr);

public:
	bool needReadPrivileges(const QString &fn, const QString &param);
	bool needWritePrivileges(const QString &fn, const QString &param);

	BuildManager *buildManager;

    Texstudio *getApp();

private:
	const QString &script;
	Texstudio *app;
	QByteArray scriptHash;
	SubScriptObject subScriptObject;
	SubScriptObject *getScript();

};

#endif // SCRIPTOBJECT_H
