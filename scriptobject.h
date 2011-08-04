#ifndef SCRIPTOBJECT_H
#define SCRIPTOBJECT_H

#include <QObject>
#include "qdocumentcursor.h"
class ScriptObject : public QObject
{
	Q_OBJECT

public:
	explicit ScriptObject();
signals:

public slots:
	void alert(const QString& message);
private:
	
};

#endif // SCRIPTOBJECT_H
