#########################################################################################
# pkgAtLeastVersion(widget_name, widget_version)
# Custom test that checks if widget_name is installed and at least version widget_version
#########################################################################################
defineTest(pkgAtLeastVersion) {
	# We do not use "pkg-config --atleast-version ..." because there is bug in
	# Ubuntu 16.04 which causes the command to fail.
	MOD_LINES = $$system($$pkgConfigExecutable() "--modversion " $$1, lines, exitCode)
	if (!isEqual(exitCode, 0)) {
		return (false)
	}
	if (isEmpty(MOD_LINES)) {
		return (false)
	}
	if (versionGreaterOrEqual($$first(MOD_LINES), $$2)) {
		return (true)
	} else {
		return (false)
	}
}

###########################################################################################
# versionGreaterOrEqual(VERSION_1, VERSION_2)
# Custom test that compares two dot-separated versions and checks if VERSION_1 >= VERSION_2
# versionAtLeast() is not supported before Qt 5.10, so we have a custom implementation of
# this function.
###########################################################################################
defineTest(versionGreaterOrEqual) {
	VER_1_SEGMENTS = $$split(1, ".")
	VER_2_SEGMENTS = $$split(2, ".")
	INDEX = 0
	for(VER_2_ITEM, VER_2_SEGMENTS) {
		VER_1_ITEM = $$member(VER_1_SEGMENTS, $$INDEX)
		if(isEmpty(VER_1_ITEM)) {
			VER_1_ITEM = 0
		}
		if (lessThan(VER_1_ITEM, $$VER_2_ITEM)) {
			return(false)
		}
		if (greaterThan(VER_1_ITEM, $$VER_2_ITEM)) {
			return(true)
		}
		INDEX = $$num_add($$INDEX, 1)
	}
	return(true)
}
message(Building via qmake (.pro) deprecated. Please use cmake instead.)
####################
# Start of main code
####################
TEMPLATE = app
LANGUAGE = C++
DESTDIR = ./
DISTFILES = texstudio.astylerc
win32 {
	!versionGreaterOrEqual($$QT_VERSION, "5.10.0") {
		error(Windows builds require Qt version 5.10.0 or newer)
	}
} else {
	!versionGreaterOrEqual($$QT_VERSION, "5.0.0") {
		error(Non-Windows builds require Qt version 5.0.0 or newer)
	}
}
message(Building with Qt $$QT_VERSION)
CONFIG += qt
CONFIG -= precompile_header

# allow loading extra config by file for automatic compilations (OBS)
exists(texstudio.pri):include(texstudio.pri)
QT += network \
    xml \
    svg \
    qml \
    printsupport \
    concurrent

QT += \
    widgets \
    uitools


versionGreaterOrEqual($$QT_VERSION, "6.0.0") {
    QT += core5compat
}

!isEmpty(MXE){
    DEFINES += MXE
}

!isEmpty(MEDIAPLAYER){
    QT += multimedia multimediawidgets
    DEFINES += MEDIAPLAYER
}

!versionGreaterOrEqual($$QT_VERSION, "6.0.0") {
    isEmpty(INTERNAL_TERMINAL):pkgAtLeastVersion("qtermwidget5", "0.9.0") {
        INTERNAL_TERMINAL=1
        message(Use detected qterminal)
    }
    !isEmpty(INTERNAL_TERMINAL){
        LIBS += -lqtermwidget5
        DEFINES += INTERNAL_TERMINAL
        message(Use qterminal)
    }
}

include(src/qtsingleapplication/qtsingleapplication.pri)

# ##############################
# precompile_header: PRECOMPILED_HEADER = mostQtHeaders.h
# principal sources
include(src/sources.pri)
include(src/debug/debug.pri)

RESOURCES += texstudio.qrc \
    symbols.qrc \
    completion.qrc \
    images.qrc


TRANSLATIONS += translation/texstudio_ar.ts \
    translation/texstudio_br.ts \
    translation/texstudio_ca.ts \
    translation/texstudio_cs.ts \
    translation/texstudio_de.ts \
    translation/texstudio_el.ts \
    translation/texstudio_es.ts \
    translation/texstudio_fa.ts \
    translation/texstudio_fr.ts \
    translation/texstudio_hu.ts \
    translation/texstudio_id_ID.ts \
    translation/texstudio_ie.ts \
    translation/texstudio_it.ts \
    translation/texstudio_ja.ts \
    translation/texstudio_ko.ts \
    translation/texstudio_ko_KR.ts \
    translation/texstudio_nb_NO.ts \
    translation/texstudio_nl.ts \
    translation/texstudio_pl.ts \
    translation/texstudio_pt.ts \
    translation/texstudio_pt_BR.ts \
    translation/texstudio_ru_RU.ts \
    translation/texstudio_si.ts \
    translation/texstudio_sk.ts \
    translation/texstudio_sv.ts \
    translation/texstudio_tr_TR.ts \
    translation/texstudio_ug.ts \
    translation/texstudio_uk.ts \
    translation/texstudio_vi.ts \
    translation/texstudio_zh_CN.ts

# ###############################
win32:RC_FILE = win.rc

# ##############################
macx {
    # make sure that the documentation is right
    config += unix

    # #universal tiger
    CONFIG += link_prl \
        x86_64

    # QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.4u.sdk
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15
    target.path = /Applications
    manual.path = Contents/Resources
    manualOSX.path = Contents/Resources
    manualOSX.files = utilities/manual/build/html
    manualImages.path = Contents/Resources/_images
    manualStatic.path = Contents/Resources
    manualSphinx.path = Contents/Resources/_sphinx_design_static
    utilities.path = Contents/Resources/
    QMAKE_BUNDLE_DATA += utilities manualOSX
    ICON = texstudio.icns
    QMAKE_INFO_PLIST = Info.plist
}

# ###############################
unix:!macx {
    isEmpty( PREFIX ):PREFIX = /usr
    isEmpty( DATADIR ):DATADIR = $${PREFIX}/share
    DEFINES += PREFIX=\\\"$${PREFIX}\\\"
    target.path = $${PREFIX}/bin
    utilities.path = $${DATADIR}/texstudio
    manual.path = $${DATADIR}/texstudio
    manualImages.path = $${DATADIR}/texstudio/_images
    manualStatic.path = $${DATADIR}/texstudio
    manualSphinx.path = $${DATADIR}/texstudio/_sphinx_design_static
    utilities.files = utilities/texstudio16x16.png \
        utilities/texstudio22x22.png \
        utilities/texstudio32x32.png \
        utilities/texstudio48x48.png \
        utilities/texstudio64x64.png \
        utilities/texstudio128x128.png
    applicationmenu.path = $${DATADIR}/applications
    applicationmenu.files = utilities/texstudio.desktop
    icon.path = $${DATADIR}/icons/hicolor/scalable/apps
    icon.files = utilities/texstudio.svg
    isEmpty(NO_APPDATA) {
        appdata.path = $${DATADIR}/metainfo
        appdata.files = utilities/texstudio.metainfo.xml 
        INSTALLS += appdata
    }
    INSTALLS += applicationmenu
    INSTALLS += icon
!haiku {
    include(src/xkb/xkb.pri)
    }
}

# ##########UNIX + MACX###############
unix {
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
    utilities.files += utilities/latex2e.html \
        utilities/latex2e.css \
        translation/texstudio_ar.qm \
        translation/texstudio_br.qm \
        translation/texstudio_ca.qm \
        translation/texstudio_cs.qm \
        translation/texstudio_de.qm \
        translation/texstudio_el.qm \
        translation/texstudio_es.qm \
        translation/texstudio_fa.qm \
        translation/texstudio_fr.qm \
        translation/texstudio_hu.qm \
        translation/texstudio_id_ID.qm \
        translation/texstudio_ie.qm \
        translation/texstudio_it.qm \
        translation/texstudio_ja.qm \
        translation/texstudio_ko.qm \
        translation/texstudio_ko_KR.qm \
        translation/texstudio_nb_NO.qm \
        translation/texstudio_nl.qm \
        translation/texstudio_pl.qm \
        translation/texstudio_pt.qm \
        translation/texstudio_pt_BR.qm \
        translation/texstudio_ru_RU.qm \
        translation/texstudio_si.qm \
        translation/texstudio_sk.qm \
        translation/texstudio_sv.qm \
        translation/texstudio_tr_TR.qm \
        translation/texstudio_ug.qm \
        translation/texstudio_uk.qm \
        translation/texstudio_vi.qm \
        translation/texstudio_zh_CN.qm \
        translation/qt_cs.qm \
        translation/qt_de.qm \
        translation/qt_ja.qm \
        translation/qt_fr.qm \
        translation/qt_hu.qm \
        translation/qt_pl.qm \
        translation/qt_zh.qm \
        templates/tabletemplate_fullyframed_firstBold.js \
        templates/tabletemplate_fullyframed_firstBold.png \
        templates/tabletemplate_fullyframed_longtable.js \
        templates/tabletemplate_fullyframed_longtable.png \
        templates/tabletemplate_plain_tabular.js \
        templates/tabletemplate_plain_tabular.png \
        templates/tabletemplate_plain_tabularx.js \
        templates/tabletemplate_plain_tabularx.png \
        templates/tabletemplate_rowcolors_tabular.js \
        templates/tabletemplate_rowcolors_tabular.png \
        templates/template_Article.json \
        templates/template_Article.png \
        templates/template_Article.tex \
        templates/template_Article_French.json \
        templates/template_Article_French.png \
        templates/template_Article_French.tex \
        templates/template_Article_LuaLaTeX_French.json \
        templates/template_Article_LuaLaTeX_French.png \
        templates/template_Article_LuaLaTeX_French.tex \
        templates/template_Beamer.json \
        templates/template_Beamer.tex \
        templates/template_Book.json \
        templates/template_Book.png \
        templates/template_Book.zip \
        templates/template_HA-prosper.json \
        templates/template_HA-prosper.tex \
        templates/template_Letter.json \
        templates/template_Letter.png \
        templates/template_Letter.tex \
        templates/template_Moderncv.json \
        templates/template_Moderncv.png \
        templates/template_Moderncv.tex \
        templates/template_Moderncv_French.json \
        templates/template_Moderncv_French.png \
        templates/template_Moderncv_French.tex \
        templates/template_Prosper.json \
        templates/template_Prosper.tex \
        templates/template_Report.json \
        templates/template_Report.png \
        templates/template_Report.tex \
        templates/template_Scrartcl.json \
        templates/template_Scrartcl.png \
        templates/template_Scrartcl.tex \
        templates/template_Scrbook.json \
        templates/template_Scrbook.tex \
        templates/template_Scrlttr2.json \
        templates/template_Scrlttr2.tex \
        templates/template_Scrreprt.json \
        templates/template_Scrreprt.tex \
        utilities/dictionaries/de_DE.aff \
        utilities/dictionaries/de_DE.dic \
        utilities/dictionaries/en_GB.aff \
        utilities/dictionaries/en_GB.dic \
        utilities/dictionaries/en_US.aff \
        utilities/dictionaries/en_US.dic \
        utilities/dictionaries/es_ES.aff \
        utilities/dictionaries/es_ES.dic \
        utilities/dictionaries/fr_FR.aff \
        utilities/dictionaries/fr_FR.dic \
        utilities/dictionaries/hu_HU.aff \
        utilities/dictionaries/hu_HU.dic \
        utilities/dictionaries/it_IT.aff \
        utilities/dictionaries/it_IT.dic \
        utilities/dictionaries/pt_BR.aff \
        utilities/dictionaries/pt_BR.dic \
        utilities/dictionaries/de_DE.badWords \
        utilities/dictionaries/de_DE.stopWords \
        utilities/dictionaries/de_DE.stopWords.level2 \
        utilities/dictionaries/en_GB.stopWords \
        utilities/dictionaries/en_US.stopWords \
        utilities/dictionaries/fr_FR.stopWords \
        utilities/dictionaries/th_en_US_v2.dat \
        utilities/dictionaries/th_fr_FR_v2.dat \
        utilities/dictionaries/th_it_IT_v2.dat \
        utilities/dictionaries/th_de_DE_v2.dat \
        utilities/AUTHORS \
        utilities/COPYING \
        utilities/manual/CHANGELOG.md
    manual.files = \
        utilities/manual/build/html/*.html
        utilities/manual/build/html/searchindex.js
   manualImages.files = \
        utilities/manual/build/html/_images/*.png
   manualSphinx.files = \
        utilities/manual/build/html/_sphinx_design_static/*
   manualStatic.files = \
        utilities/manual/build/html/_static

    INSTALLS += target \
        manual \
        manualImages \
        manualStatic \
        manualSphinx \
        utilities
}
isEmpty(USE_SYSTEM_HUNSPELL){
    include(src/hunspell/hunspell.pri)
}else{
    message(System hunspell)
    CONFIG += link_pkgconfig
    PKGCONFIG += hunspell
}

include(src/qcodeedit/qcodeedit.pri)

include(src/latexparser/latexparser.pri)

include(src/symbolpanel/symbolpanel.pri)

isEmpty(USE_SYSTEM_QUAZIP) {
    include(src/quazip/quazip/quazip.pri)
} else {
    versionGreaterOrEqual($$QT_VERSION, "6.0.0") {
        message(System quazip6)
        CONFIG += link_pkgconfig
        PKGCONFIG += quazip1-qt6
    }
    !versionGreaterOrEqual($$QT_VERSION, "6.0.0") {
            message(System quazip5)
            isEmpty(QUAZIP_LIB): QUAZIP_LIB = -lquazip5
            isEmpty(QUAZIP_INCLUDE): QUAZIP_INCLUDE = $${PREFIX}/include/quazip5
            INCLUDEPATH += $${QUAZIP_INCLUDE}
            LIBS += $${QUAZIP_LIB}
    }
}

include(src/pdfviewer/pdfviewer.pri)

include(src/adwaita-qt/adwaita.pri)

# ###############################

CONFIG(debug, debug|release) {
    message(Creating debug version)
    CONFIG -= debug_and_release release
} else {
    message(Creating release version)
    CONFIG -= debug_and_release debug
    NO_TESTS = 1
}

macx:LIBS += -framework CoreFoundation

freebsd-* {
    LIBS += -lexecinfo
}

!isEmpty(NO_CRASH_HANDLER) {
    DEFINES += NO_CRASH_HANDLER
    message("Internal crash handler disabled as you wish.")
}
include(src/tests/tests.pri)
!isEmpty(DEBUG_LOGGER) {
    DEFINES += DEBUG_LOGGER
    message("Enabling debug logger.")
}

# add git revision
exists(./.git)  {
  win32:isEmpty(MXE): {
    message(GIT bat)
    system(\"$${PWD}/git_revision.bat\" $${QMAKE_CXX} \"$${OUT_PWD}\" \"$${PWD}\")
    SOURCES += src/git_revision.cpp
  } else {
    message(GIT sh)
    system(\"$${PWD}/git_revision_qmake.sh\" $${QMAKE_CXX} \"$${OUT_PWD}\" \"$${PWD}\")
    SOURCES += src/git_revision.cpp
  }
} else {
  !exists(src/git_revision.cpp){
    win32:isEmpty(MXE): system(echo const char * TEXSTUDIO_GIT_REVISION = 0; > src\git_revision.cpp)
    else: system(echo \"const char * TEXSTUDIO_GIT_REVISION = 0;\" > src/git_revision.cpp)
  }
  SOURCES += src/git_revision.cpp
}

!win32-msvc*: {
  QMAKE_CXXFLAGS_DEBUG -= -O -O1 -O2 -O3
  QMAKE_CXXFLAGS_DEBUG += -Wall -Wextra -Wmissing-include-dirs -Wunknown-pragmas -Wundef -Wpointer-arith -Winline -O0 -Wno-deprecated-declarations

  QMAKE_CXXFLAGS += -fno-omit-frame-pointer
  win32: QMAKE_CXXFLAGS += -fpermissive
  !win32:!haiku: QMAKE_LFLAGS += -rdynamic # option not supported by mingw and haiku
} else {
  DEFINES += _CRT_SECURE_NO_WARNINGS
}

*-g++:equals(QT_MAJOR_VERSION, 5):lessThan(QT_MINOR_VERSION, 13) {
  QMAKE_CXXFLAGS += -Wno-deprecated-copy
}
