#include "scriptengine.h"

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

        engine->evaluate(m_script);
        if(engine->hasUncaughtException()){
            qDebug() << "uncaught exception at line "<< engine->uncaughtExceptionLineNumber() << ":" << engine->uncaughtException().toString();
            qDebug() << "Backtrace: " << engine->uncaughtExceptionBacktrace().join(", ");
        }
        m_editor->setCursor(c);
    }
}
