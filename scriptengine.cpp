#include "scriptengine.h"
#include "filechooser.h"

scriptengine::scriptengine(QObject *parent) : QObject(parent),m_editor(0)
{
    engine=new QScriptEngine(this);
    //qScriptRegisterMetaType<QDocumentCursor>(engine);
}

scriptengine::~scriptengine(){
}

void scriptengine::setScript(const QString script){
    m_script=script;
}

void scriptengine::run(){
    if(m_editor){
        QScriptValue editorValue = engine->newQObject(m_editor);
        engine->globalObject().setProperty("editor", editorValue);
        QDocumentCursor c=m_editor->cursor();
        QScriptValue cursorValue = engine->newQObject(&c);
        engine->globalObject().setProperty("cursor", cursorValue);
        QScriptValue qsMetaObject = engine->newQMetaObject(c.metaObject());
        engine->globalObject().setProperty("cursorEnums", qsMetaObject);
		FileChooser *flchooser=new FileChooser(0,"File Chooser");
		QScriptValue qsFileChooserObject = engine->newQObject(flchooser);
		engine->globalObject().setProperty("fileChooser", qsFileChooserObject);

        engine->evaluate(m_script);
        if(engine->hasUncaughtException()){
            qDebug() << "uncaught exception at line "<< engine->uncaughtExceptionLineNumber() << ":" << engine->uncaughtException().toString();
            qDebug() << "Backtrace: " << engine->uncaughtExceptionBacktrace().join(", ");
        }
        m_editor->setCursor(c);
    }
}
