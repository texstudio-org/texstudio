#include "scriptengine.h"
#include "filechooser.h"

scriptengine::scriptengine(QObject *parent) : QObject(parent),m_editor(0)
{
    engine=new QScriptEngine(this);
	//qScriptRegisterMetaType<QDocumentCursor>(engine);
}

scriptengine::~scriptengine(){
	delete engine;
}

void scriptengine::setScript(const QString script){
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
