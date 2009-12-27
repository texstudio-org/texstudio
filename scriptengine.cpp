#include "scriptengine.h"

scriptengine::scriptengine(QObject *parent) : QObject(parent),m_editor(0)
{
    qDebug("reached");
    //QEditor* editor=qobject_cast<QEditor*>(parent);
    engine=new QScriptEngine(this);
    //qScriptRegisterMetaType(engine,)
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
        qDebug() << engine->evaluate(m_script).toString();
        m_editor->setCursor(c);
    }
}
