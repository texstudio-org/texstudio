#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QObject>
#include <QtScript>
#include <QScriptEngine>

#include "qeditor.h"

class scriptengine : public QObject
{
Q_OBJECT
public:
    scriptengine(QObject *parent=0);
    ~scriptengine();
    void run();
    void setScript(const QString script);
    void setEditor(QEditor *editor){
        m_editor=editor;
    }

protected:
    QScriptEngine *engine;
    QEditor *m_editor;
    QString m_script;
};

#endif // SCRIPTENGINE_H
