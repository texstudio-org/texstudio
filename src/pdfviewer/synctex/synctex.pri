INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

win32: {
    LIBS *= -lshlwapi
}

HEADERS += \
    $$PWD/synctex_parser.h \
    $$PWD/synctex_parser_utils.h \
    $$PWD/synctex_parser_advanced.h \
    $$PWD/synctex_version.h

SOURCES += \
    $$PWD/synctex_parser.c \
    $$PWD/synctex_parser_utils.c
