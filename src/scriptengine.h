#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include "mostQtHeaders.h"
#if defined(__GNUC__) && !defined(__INTEL_COMPILER) && !defined(__clang__) && (__GNUC__ >= 8)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif
#ifdef QJS
#include <QJSEngine>
#include <QJSValueIterator>
#include <QQmlEngine>
#else
#include <QtScript>
#include <QScriptEngine>
#endif
#if defined(__GNUC__) && !defined(__INTEL_COMPILER) && !defined(__clang__) && (__GNUC__ >= 8)
#pragma GCC diagnostic pop
#endif

#include "qeditor.h"
//#include "latexeditorview.h"
class BuildManager;
class Texstudio;
class ScriptObject;

class LatexEditorView;
class Macro;
class scriptengine : public QObject
{
	Q_OBJECT

public:
    scriptengine(QObject *parent = nullptr);
	~scriptengine();
	void run();
	void setScript(const QString &script, bool allowWrite = false);
	void setEditorView(LatexEditorView *edView);

	static BuildManager *buildManager;
	static Texstudio *app;

	QStringList triggerMatches;
	int triggerId;

	ScriptObject *globalObject;

	static QList<Macro> *macros;
#ifdef QJS
protected slots:
    void insertSnippet(const QString& arg);
    QJSValue replaceSelectedText(QJSValue replacementText,QJSValue options=QJSValue());
    QJSValue searchFunction(QJSValue searchFor, QJSValue arg1=QJSValue(), QJSValue arg2=QJSValue(), QJSValue arg3=QJSValue());
    QJSValue replaceFunction(QJSValue searchFor, QJSValue arg1=QJSValue(), QJSValue arg2=QJSValue(), QJSValue arg3=QJSValue());
    //void save();
    //void saveCopy(const QString& fileName);
#endif

protected:
#ifdef QJS
    QJSEngine *engine;
#else
	QScriptEngine *engine;
#endif
#ifdef QJS
    QJSValue searchReplaceFunction(QJSValue searchText, QJSValue arg1, QJSValue arg2, QJSValue arg3, bool replace);
#endif

    QPointer<LatexEditorView> m_editorView;
    QPointer<QEditor> m_editor;
	QString m_script;
	bool m_allowWrite;
};

#include "universalinputdialog.h"
#ifdef QJS
class UniversalInputDialogScript: public UniversalInputDialog
{
    Q_OBJECT

public:
    Q_INVOKABLE UniversalInputDialogScript(QWidget *parent = nullptr);
    ~UniversalInputDialogScript();

public slots:
    QWidget* add(const QJSValue &def, const QJSValue &description, const QJSValue &id = QJSValue());

    QJSValue execDialog();

    QJSValue getAll();
    QVariant get(const QJSValue &id);

private:
    QJSEngine *engine;
};
#else
class UniversalInputDialogScript: public UniversalInputDialog
{
	Q_OBJECT

public:
    UniversalInputDialogScript(QScriptEngine *engine, QWidget *parent = nullptr);
	~UniversalInputDialogScript();

public slots:
	QScriptValue add(const QScriptValue &def, const QScriptValue &description, const QScriptValue &id = QScriptValue());
	QScriptValue execDialog();
	QScriptValue getAll();
	QScriptValue get(const QScriptValue &id);

private:
	QScriptEngine *engine;
};


class TimeoutWrapper: public QObject
{
	Q_OBJECT

public:
	QScriptValue fun;

public slots:
	void run();
};
#endif
#endif // SCRIPTENGINE_H
