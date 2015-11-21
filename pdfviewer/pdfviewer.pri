# created: 2015-11-21
# author: Tim Hoffmann

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    pdfviewer/PDFDocument.h \
    pdfviewer/PDFDocks.h \
    pdfviewer/pdfrenderengine.h \
    pdfviewer/pdfrendermanager.h \
    pdfviewer/PDFDocument_config.h \
    pdfviewer/pdfannotationdlg.h \
    pdfviewer/pdfannotation.h

SOURCES += \
    pdfviewer/PDFDocument.cpp \
    pdfviewer/PDFDocks.cpp \
    pdfviewer/pdfrenderengine.cpp \
    pdfviewer/pdfrendermanager.cpp \
    pdfviewer/pdfannotationdlg.cpp \
    pdfviewer/pdfannotation.cpp

FORMS += \
    pdfviewer/PDFDocument.ui \
    pdfviewer/pdfannotationdlg.ui


# ################################
# Poppler PDF Preview, will only be used if NO_POPPLER_PREVIEW is not set
isEmpty(NO_POPPLER_PREVIEW) {
    !win32 {
	macx { # PATH to pkgconfig needs to be present in build PATH
	    QT_CONFIG -= no-pkg-config
	}
	poppler_qt_pkg = poppler-qt$${QT_MAJOR_VERSION}

	CONFIG += link_pkgconfig
	PKGCONFIG += $${poppler_qt_pkg}
	system(pkg-config --atleast-version=0.24 $${poppler_qt_pkg}):DEFINES += HAS_POPPLER_24
    } else: {
	!greaterThan(QT_MAJOR_VERSION, 4) { #Qt4
	   # unix:!macx {
	   #
	   #     INCLUDEPATH += /usr/include/poppler/qt4
	   #     LIBS += -L/usr/lib \
	   #         -lpoppler-qt4 \
	   #         -lz
	   # }
	   # macx {
	   #     INCLUDEPATH += /usr/local/include/poppler/qt4
	   #     LIBS += -L/usr/lib \
	   #         -L/usr/local/lib \
	   #         -lpoppler-qt4 \
	   #         -lz
	   # }
	    win32 {
	       INCLUDEPATH  += ./pdfviewer/include_win32
	       LIBS += ./zlib1.dll \
		   ./libpoppler-qt4.dll \

	       DEFINES += HAS_POPPLER_24
	    }
	  }else:{ # Qt5
	    #unix:!macx {
	    #
	#	INCLUDEPATH += /usr/include/poppler/qt5
	 #       LIBS += -L/usr/lib \
	#	     -L/usr/include/poppler/lib \
	 #           -lpoppler-qt5 \
	  #          -lz
	   # }
	    #macx {
	    #    INCLUDEPATH += /usr/local/include/poppler/qt5
	    #   LIBS += -L/usr/lib \
	    #        -L/usr/local/lib \
	    #       -lpoppler-qt5 \
	    #        -lz
	    #}
	    win32 {
		INCLUDEPATH  += ./pdfviewer/include_win32_qt5
		LIBS += ./zlib1.dll \
			./libpoppler-qt5.dll

		DEFINES += HAS_POPPLER_24
	    }
	}
    }
}
!isEmpty(NO_POPPLER_PREVIEW) {
    DEFINES += NO_POPPLER_PREVIEW
    message("Internal pdf previewer disabled as you wish.")
}
