INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
QT *= network
SOURCES += $$PWD/qtsingleapplication.cpp \
    $$PWD/qtlocalpeer.cpp \
    ../qcodeedit/lib/qformat.cpp
HEADERS += $$PWD/qtsingleapplication.h \
    $$PWD/qtlocalpeer.h
