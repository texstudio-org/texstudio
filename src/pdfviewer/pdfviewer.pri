# created: 2015-11-21
# author: Tim Hoffmann

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# ################################
# Poppler PDF Preview, will only be used if NO_POPPLER_PREVIEW is not set
isEmpty(NO_POPPLER_PREVIEW) {

    include(synctex/synctex.pri)

    HEADERS += \
        $$PWD/PDFDocument.h \
        $$PWD/PDFDocks.h \
        $$PWD/pdfrenderengine.h \
        $$PWD/pdfrendermanager.h \
        $$PWD/PDFDocument_config.h \
        $$PWD/pdfannotationdlg.h \
        $$PWD/pdfannotation.h \
        $$PWD/qsynctex.h

    SOURCES += \
        $$PWD/PDFDocument.cpp \
        $$PWD/PDFDocks.cpp \
        $$PWD/pdfrenderengine.cpp \
        $$PWD/pdfrendermanager.cpp \
        $$PWD/pdfannotationdlg.cpp \
        $$PWD/pdfannotation.cpp \
        $$PWD/qsynctex.cpp


    FORMS += \
        $$PWD/pdfannotationdlg.ui

    win32:isEmpty(MXE) {
        INCLUDEPATH  += ./src/pdfviewer/include_win32_qt5
        win32-msvc*: {
            LIBS += ./zlib.lib ./libpoppler-qt5.lib
        } else {
            LIBS += ./zlib1.dll ./libpoppler-qt5.dll
        }
        DEFINES += HAS_POPPLER_31
        LIBS *= -lshlwapi
    } else {
        macx { # PATH to pkgconfig needs to be present in build PATH
            QT_CONFIG -= no-pkg-config
        }
        poppler_qt_pkg = poppler-qt$${QT_MAJOR_VERSION} poppler-cpp

        CONFIG += link_pkgconfig

        PKGCONFIG += $${poppler_qt_pkg}

	!isEmpty(MXE){
		message("Using MXE")
		PKGCONFIG += lcms2
		PKGCONFIG += libtiff-4
		PKGCONFIG += libopenjp2
	}

        PKG_CONFIG_EXE = $$pkgConfigExecutable()
        isEmpty(PKG_CONFIG_EXE) {
            error("pkg-config not found. This tool is required if building with poppler. Please install it.")
        }


    }
    LIBS *= -lz
} else {
    DEFINES += NO_POPPLER_PREVIEW
    message("Internal pdf previewer disabled as you wish.")
}

