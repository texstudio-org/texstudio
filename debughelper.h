#ifndef DEBUGHELPER_H
#define DEBUGHELPER_H

#include "modifiedQObject.h"



void print_backtrace(const QString& message);

void recover(); //defined in texmaker.cpp

void registerCrashHandler(int mode);
QString getLastCrashInformation();

#endif // DEBUGHELPER_H
