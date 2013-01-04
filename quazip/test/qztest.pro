TEMPLATE = app
QT -= gui
CONFIG += qtestlib
TARGET = 
DEPENDPATH += .
INCLUDEPATH += . ..
LIBS += -L../quazip
LIBS += -lquazip

# Input
HEADERS += qztest.h \
testjlcompress.h \
testquachecksum32.h \
testquagzipfile.h \
testquaziodevice.h \
testquazipdir.h \
testquazipfile.h \
testquazip.h

SOURCES += qztest.cpp \
testjlcompress.cpp \
testquachecksum32.cpp \
testquagzipfile.cpp \
testquaziodevice.cpp \
testquazip.cpp \
testquazipdir.cpp \
testquazipfile.cpp

OBJECTS_DIR = .obj
MOC_DIR = .moc
