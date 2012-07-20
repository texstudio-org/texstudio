#ifndef DEBUGHELPER_H
#define DEBUGHELPER_H

#include "modifiedQObject.h"
#include "smallUsefulFunctions.h"


void print_backtrace(const QString& message);

void recover(); //defined in texmaker.cpp

void registerCrashHandler(int mode);
QString getLastCrashInformation(bool & wasLoop);




class Guardian: public SafeThread{
	Q_OBJECT
	
	void run();
public:
	static void summon();
	static void calm();
	static void shutdown();

	static void continueEndlessLoop();
	
	static Guardian* instance();
	
public slots: 
	void slowOperationStarted();
	void slowOperationEnded();

private:
	int slowOperations;
};


#endif // DEBUGHELPER_H
