TEMPLATE = app
LANGUAGE = C++
DESTDIR = ./
CONFIG = $$unique(CONFIG)
CONFIG -= debug \
    debug_and_release \
    release
CONFIG += qt debug_and_release 
QT += network xml


SOURCES += smallUsefulFunctions_t.cpp \ 
          ../smallUsefulFunctions.cpp 	
		

HEADERS += ../smallUsefulFunctions.h
	
TARGET = test
