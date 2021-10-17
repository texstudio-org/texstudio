#ifndef Header_DebugHelper
#define Header_DebugHelper

#include "modifiedQObject.h"
#include "smallUsefulFunctions.h"


QString print_backtrace(const QString &message);

void recover(); //defined in texstudio.cpp

void initCrashHandler(int mode);
QString getLastCrashInformation(bool &wasLoop);
void catchUnhandledException();


class Guardian: public SafeThread
{
	Q_OBJECT

public:
	Guardian(): SafeThread(), slowOperations(0) {}
	static void summon();
	static void calm();
	static void shutdown();

	static void continueEndlessLoop();

	static Guardian *instance();
	
protected:
	void run();

public slots:
	void slowOperationStarted();
	void slowOperationEnded();

private:
	int slowOperations;
};


#endif // DEBUGHELPER_H
