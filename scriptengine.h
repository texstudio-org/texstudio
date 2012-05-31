#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include "mostQtHeaders.h"
#include <QtScript>
#include <QScriptEngine>

#include "qeditor.h"
class BuildManager;
class Texmaker;
class ScriptObject;
class LatexEditorView;
class scriptengine : public QObject
{
Q_OBJECT
public:
	scriptengine(QObject *parent=0);
	~scriptengine();
	void run();
	void setScript(const QString& script);
	void setEditorView(LatexEditorView* edView);

	static BuildManager* buildManager;
	static Texmaker* app;
	
	QStringList triggerMatches;
	int triggerId;
	
	ScriptObject *globalObject;
protected:
	QScriptEngine *engine;
	QPointer<LatexEditorView> m_editorView;
	QPointer<QEditor> m_editor;
	QString m_script;
};

#include "universalinputdialog.h"

class UniversalInputDialogScript: public UniversalInputDialog{
	Q_OBJECT
public:
	UniversalInputDialogScript(QScriptEngine* engine, QWidget* parent=0);
	~UniversalInputDialogScript();
public slots:
	QScriptValue add(const QScriptValue& def, const QScriptValue& description, const QScriptValue& id = QScriptValue());
	QScriptValue exec();
	QScriptValue getAll();
	QScriptValue get(const QScriptValue& id);
private:
	QScriptEngine* engine;
};
	

#endif // SCRIPTENGINE_H
