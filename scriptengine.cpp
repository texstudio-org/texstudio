#include "scriptengine.h"
#include "filechooser.h"

Q_DECLARE_METATYPE(QDocument*);

//copied from trolltech mailing list
template <typename Tp> QScriptValue qScriptValueFromQObject(QScriptEngine *engine, Tp const &qobject)
{
	return engine->newQObject(qobject);
}

template <typename Tp> void qScriptValueToQObject(const QScriptValue &value, Tp &qobject) {
	qobject = qobject_cast<Tp>(value.toQObject());
}

template <typename Tp> int qScriptRegisterQObjectMetaType( QScriptEngine *engine, const QScriptValue &prototype = QScriptValue(), Tp * /* dummy */ = 0)
{
    return qScriptRegisterMetaType<Tp>(engine, qScriptValueFromQObject, qScriptValueToQObject, prototype);
}
//


QScriptValue qScriptValueFromDocumentCursor(QScriptEngine *engine, QDocumentCursor const &cursor)
{
	return engine->newQObject(new QDocumentCursor(cursor), QScriptEngine::ScriptOwnership);
}
void qScriptValueToDocumentCursor(const QScriptValue &value, QDocumentCursor &qobject) {
	qobject = *qobject_cast<QDocumentCursor*>(value.toQObject());
}




scriptengine::scriptengine(QObject *parent) : QObject(parent),m_editor(0)
{
	engine=new QScriptEngine(this);
	qScriptRegisterQObjectMetaType<QDocument*>(engine);
	qScriptRegisterMetaType<QDocumentCursor>(engine, qScriptValueFromDocumentCursor, qScriptValueToDocumentCursor, QScriptValue());
//	qScriptRegisterMetaType<QDocumentCursor>(engine);
//	engine->setDefaultPrototype(qMetaTypeId<QDocument*>(), QScriptValue());
	//engine->setDefaultPrototype(qMetaTypeId<QDocumentCursor>(), QScriptValue());
}

scriptengine::~scriptengine(){
	delete engine;
}

void scriptengine::setScript(const QString& script){
	m_script=script;
}
void scriptengine::setEditor(QEditor *editor){
	m_editor = editor;
}

QScriptValue alertFunction(QScriptContext *context, QScriptEngine *engine)
{
	if (context->argumentCount()<1)  {
		context->throwError(scriptengine::tr("no arguments to alert"));
		return engine->undefinedValue();
	}
	if (context->argumentCount()>1)  {
		context->throwError(scriptengine::tr("too much arguments to alert"));
		return engine->undefinedValue();
	}
	QMessageBox::information(0, scriptengine::tr("Script-Message"), context->argument(0).toString());
	return engine->undefinedValue();
}

void scriptengine::run(){
	if(m_editor){
		QScriptValue editorValue = engine->newQObject(m_editor);
		engine->globalObject().setProperty("editor", editorValue);
		QDocumentCursor c=m_editor->cursor();
		c.setAutoUpdated(true); //auto updated so the editor text insert functions actually move the cursor
		QScriptValue cursorValue = engine->newQObject(&c);
		engine->globalObject().setProperty("cursor", cursorValue);
		QScriptValue qsMetaObject = engine->newQMetaObject(c.metaObject());
		engine->globalObject().setProperty("cursorEnums", qsMetaObject);
		FileChooser flchooser(0,scriptengine::tr("File Chooser"));
		QScriptValue qsFileChooserObject = engine->newQObject(&flchooser);
		engine->globalObject().setProperty("fileChooser", qsFileChooserObject);
		engine->globalObject().setProperty("alert", engine->newFunction(&alertFunction));

		engine->evaluate(m_script);

		if(engine->hasUncaughtException()){
			QString error = QString(tr("Uncaught exception at line %1: %2\n")).arg(engine->uncaughtExceptionLineNumber()).arg(engine->uncaughtException().toString());
			error += "\n"+QString(tr("Backtrace %1")).arg(engine->uncaughtExceptionBacktrace().join(", "));
			qDebug() << error;
			QMessageBox::critical(0, tr("Script-Error"), error);
		}
		m_editor->setCursor(c);
	}
}
