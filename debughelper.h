#ifndef DEBUGHELPER_H
#define DEBUGHELPER_H

#include "modifiedQObject.h"





void recover(); //defined in texmaker.cpp

void registerCrashHandler();
QString getLastCrashInformation();

#endif // DEBUGHELPER_H
