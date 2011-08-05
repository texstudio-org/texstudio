#include "scriptobject.h"

#include "smallUsefulFunctions.h"
#include "qcryptographichash.h"
#include "configmanagerinterface.h"
#include "buildmanager.h"

QStringList privilegedScripts;
int securityMode;

ScriptObject::ScriptObject(const QString& script, BuildManager* buildManager): script(script), buildManager(buildManager)
{
	ConfigManagerInterface::getInstance()->registerOption("Scripts/Privileged Scripts", &privilegedScripts);	
	ConfigManagerInterface::getInstance()->registerOption("Scripts/Security Mode", &securityMode, 1);	
}

void ScriptObject::alert(const QString& message){ txsInformation(message); }
void ScriptObject::information(const QString& message){	txsInformation(message); }
void ScriptObject::critical(const QString& message){ txsCritical(message); }
void ScriptObject::warning(const QString& message){ txsWarning(message); }
bool ScriptObject::confirm(const QString& message){ return txsConfirm(message); }
bool ScriptObject::confirmWarning(const QString& message){ return txsConfirmWarning(message); }

ProcessX* ScriptObject::system(const QString& commandline){
	if (!buildManager || !needPrivileges("system("+commandline+")"))
		return 0;
	ProcessX* p = buildManager->newProcess(commandline,"");
	if (!p) return 0;
	p->startCommand();
	p->waitForStarted();
	return p;
}

void ScriptObject::writeFile(const QString& filename, const QString& content){
	if (!needPrivileges("writeFile("+filename+",...)"))
		return;
	QFile f(filename);
	f.open(QFile::WriteOnly);
	f.write(content.toUtf8());
	f.close();
}

QVariant ScriptObject::readFile(const QString& filename){
	if (!needPrivileges("readFile("+filename+")"))
		return QVariant();
	QFile f(filename);
	if (!f.open(QFile::ReadOnly)) 
		return QVariant();
	QTextStream ts(&f);
	ts.setAutoDetectUnicode(true);
	ts.setCodec(QTextCodec::codecForMib(MIB_UTF8));
	return ts.readAll();
}

bool ScriptObject::hasPrivileges(){
	if (securityMode == 0) 
		return false;
	if (scriptHash.isEmpty()) 
		scriptHash = QCryptographicHash::hash(script.toLatin1(), QCryptographicHash::Sha1);
	if (securityMode == 2 || privilegedScripts.contains(scriptHash)) 
		return true;
	return false;
	
}

bool ScriptObject::needPrivileges(const QString& commandline){
	if (securityMode == 0) return false;
	if (hasPrivileges()) return true;
	int t = QMessageBox::question(0, "TeXstudio script watcher", 
	                              tr("The current script has requested to enter privileged mode and call following function:\n%1\n\nDo you trust this script?").arg(commandline), tr("Yes, allow this call"), 
	                              tr("Yes, allow all calls it will ever make"), tr("No, abort the call"), 0, 2);
	if (t == 0) return true; //only now
	if (t != 1) return false;
	privilegedScripts.append(scriptHash);
	return true;
}

