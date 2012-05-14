#ifndef DEBUGHELPER_H
#define DEBUGHELPER_H

#include "modifiedQObject.h"
#include "smallUsefulFunctions.h"


void print_backtrace(const QString& message);

void recover(); //defined in texmaker.cpp

void registerCrashHandler(int mode);
QString getLastCrashInformation(bool & wasLoop);




class Guardian: public SafeThread{
	void run();
public:
	static void summon();
	static void calm();
	static void shutdown();

	static void continueEndlessLoop();
};


#endif // DEBUGHELPER_H
