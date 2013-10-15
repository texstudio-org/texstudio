
include(texstudio.pro)

#correct flags for old mingw
QMAKE_CXXFLAGS_DEBUG -=  -Wmain  -Wtype-limits  -Wclobbered  -Wempty-body -Wlogical-op 

#correct libs
LIBS += -L/tmpnetworks/ -L/usr/local/qt-cross/lib/
LIBS -= ./zlib1.dll ./libpoppler-qt4.dll ./libpoppler.dll
LIBS +=  -lzlib1 -llibpoppler-qt4 -llibpoppler 

#correct include path
QMAKE_INCDIR_QT=/usr/local/qt-cross/include/QtUiTools /usr/local/qt-cross/include/QtCore /usr/local/qt-cross/include/QtNetwork /usr/local/qt-cross/include/QtGui /usr/local/qt-cross/include/QtXml /usr/local/qt-cross/include/QtScript /usr/local/qt-cross/include qtsingleapplication qcodeedit/lib qcodeedit/lib/document qcodeedit/lib/language qcodeedit/lib/widgets qcodeedit/lib/qnfa include_win32 /usr/local/qt-cross/include/ActiveQt . .

#remove uitools
CONFIG-=uitools
SOURCES += uitoolshack.cpp


#remove precompiled header
PRECOMPILED_HEADER -= mostQtHeaders.h
CONFIG -= precompile_header


#correct svnrevision (we are on unix)
#QMAKE_PRE_LINK =
#LIBS -= svn_revision.o  
#svn_revision.target = svn_revision.cpp
#svn_revision.depends = .svn/entries  
#svn_revision.commands = echo \"const char* TEXSTUDIO_SVN_VERSION = \\\"$(shell svnversion)X\\\";\" > $$svn_revision.target
#QMAKE_EXTRA_TARGETS += svn_revision
#!exists(./svn_revision.cpp): message("svn_revision.cpp was not found and will be created. Don't worry about repeated warnings.")
#SOURCES += svn_revision.cpp

# add mercurial revision
QMAKE_PRE_LINK =
LIBS -= hg_revision.o
exists(./.hg) {
    # Just as a fall back. TODO: implement this analogous to the svn_revision an linux and mac
    QMAKE_PRE_LINK += \"$${PWD}/hg_revision.sh\" $${QMAKE_CXX} \"$${OUT_PWD}\"
    LIBS += hg_revision.o
} else {
  !exists(./hg_revision.cpp){
    system(echo \"const char * TEXSTUDIO_HG_REVISION = 0;\" > hg_revision.cpp)
  }
  SOURCES += hg_revision.cpp
}


QMAKE_CXXFLAGS += -gstabs 
QMAKE_LFLAGS -= -Wl,-s
QMAKE_LFLAGS_RELEASE -= -Wl,-s

#QMAKE_POST_LINK += cp txscross.exe /tmpnetworks
