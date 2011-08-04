#include "scriptobject.h"

#include "smallUsefulFunctions.h"
ScriptObject::ScriptObject()
{
}

void ScriptObject::alert(const QString& message){
	txsInformation(message);
}

