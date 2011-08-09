#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QObject>
#include <QtScript>
#include <QScriptEngine>

#include "qeditor.h"
class BuildManager;
class Texmaker;
class scriptengine : public QObject
{
Q_OBJECT
public:
	scriptengine(QObject *parent=0);
	~scriptengine();
	void run();
	void setScript(const QString& script);
	void setEditor(QEditor *editor);

	static BuildManager* buildManager;
	static Texmaker* app;
	
protected:
	QScriptEngine *engine;
	QPointer<QEditor> m_editor;
	QString m_script;
};

#endif // SCRIPTENGINE_H
