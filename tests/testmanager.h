#ifndef TESTMANAGER_H
#define TESTMANAGER_H
#ifndef QT_NO_DEBUG
#include "mostQtHeaders.h"
//the only reason for this file is to separate the test headers from the remaining program

class TestManager{
private:
	static QString performTest(QObject* obj);
public:
	static QString execute();
};

#endif
#endif
