# created: 2013-08-21
# author: Tim Hoffmann

message(Static hunspell)
DEFINES += HUNSPELL_STATIC
HEADERS += \
        $$PWD/affentry.hxx \
        $$PWD/affixmgr.hxx \
        $$PWD/atypes.hxx \
        $$PWD/baseaffix.hxx \
        $$PWD/csutil.hxx \
        #$$PWD/dictmgr.hxx \
        $$PWD/hashmgr.hxx \
        $$PWD/htypes.hxx \
        $$PWD/hunspell.hxx \
        $$PWD/hunspell.h \
        $$PWD/langnum.hxx \
        $$PWD/license.hunspell \
        $$PWD/phonet.hxx \
        $$PWD/suggestmgr.hxx \
        $$PWD/license.myspell \
        $$PWD/filemgr.hxx \
        $$PWD/hunzip.hxx \
        $$PWD/w_char.hxx \
        $$PWD/utf_info.hxx \
        $$PWD/replist.hxx
SOURCES += \
        $$PWD/affentry.cxx \
        $$PWD/affixmgr.cxx \
        $$PWD/csutil.cxx \
        #$$PWD/dictmgr.cxx \
        $$PWD/hashmgr.cxx \
        $$PWD/hunspell.cxx \
        $$PWD/phonet.cxx \
        $$PWD/replist.cxx \
        $$PWD/suggestmgr.cxx \
        $$PWD/filemgr.cxx \
        $$PWD/hunzip.cxx

