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
	MOD_VERSION = $$first(MOD_LINES)
	# Compare found module version in MOD_VERSION and required version in argument 2
	# versionAtLeast() is not supported before Qt 5.10, so we have a custom implementation
	# of this function.
	MOD_SEGMENTS = $$split(MOD_VERSION, ".")
	REQ_SEGMENTS = $$split(2, ".")
	INDEX = 0
	for(REQ_ITEM, REQ_SEGMENTS) {
		MOD_ITEM = $$member(MOD_SEGMENTS, $$INDEX)
		if(isEmpty(MOD_ITEM)) {
			MOD_ITEM = 0
		}
		if (lessThan(MOD_ITEM, $$REQ_ITEM)) {
			return(false)
		}
		if (greaterThan(MOD_ITEM, $$REQ_ITEM)) {
			return(true)
		}
		INDEX = $$num_add($$INDEX, 1)
	}
	return(true)
}

####################
# Start of main code
####################
TEMPLATE = app
LANGUAGE = C++
DESTDIR = ./
DISTFILES = texstudio.astylerc
greaterThan(QT_MAJOR_VERSION, 4) {
    message(Building with Qt5)
    CONFIG += qt
    !win32: CONFIG -= precompile_header # precompiling does not work with Qt5 and mingw
    win32: CONFIG -= precompile_header
} else {
    message(Qt4 support has been removed.)

}

# allow loading extra config by file for automatic compilations (OBS)
exists(texstudio.pri):include(texstudio.pri)
QT += network \
    xml \
    svg \
    script \
    printsupport \
    concurrent

QT += \
    widgets \
    uitools

!isEmpty(PHONON){
    QT += phonon4qt5
    LIBS += -lphonon4qt5
    DEFINES += PHONON
}

isEmpty(TERMINAL):pkgAtLeastVersion("qtermwidget5", "0.9.0") {
    TERMINAL=1
    message(Use detected qterminal)
}
!isEmpty(TERMINAL){
    LIBS += -lqtermwidget5
    DEFINES += TERMINAL
    message(Use qterminal)
}

!isEmpty(QJS){
    DEFINES += QJS
    QT += qml
    message(Use experimental JS engine)
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
    translation/texstudio_cs.ts \
    translation/texstudio_de.ts \
    translation/texstudio_el.ts \
    translation/texstudio_es.ts \
    translation/texstudio_fa.ts \
    translation/texstudio_fr.ts \
    translation/texstudio_hu.ts \
    translation/texstudio_id_ID.ts \
    translation/texstudio_it.ts \
    translation/texstudio_ja.ts \
    translation/texstudio_ko.ts \
    translation/texstudio_ko_KR.ts \
    translation/texstudio_nl.ts \
    translation/texstudio_pl.ts \
    translation/texstudio_pt.ts \
    translation/texstudio_pt_BR.ts \
    translation/texstudio_ru_RU.ts \
    translation/texstudio_sk.ts \
    translation/texstudio_sv.ts \
    translation/texstudio_tr_TR.ts \
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
    # QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.4
    target.path = /Applications
    manual.path = Contents/Resources/
    utilities.path = Contents/Resources/
    QMAKE_BUNDLE_DATA += utilities manual
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
        appdata.files = utilities/texstudio.appdata.xml
        INSTALLS += appdata
    }
    INSTALLS += applicationmenu
    INSTALLS += icon
    include(src/xkb/xkb.pri)
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
        translation/texstudio_cs.qm \
        translation/texstudio_de.qm \
        translation/texstudio_el.qm \
        translation/texstudio_es.qm \
        translation/texstudio_fa.qm \
        translation/texstudio_fr.qm \
        translation/texstudio_hu.qm \
        translation/texstudio_id_ID.qm \
        translation/texstudio_it.qm \
        translation/texstudio_ja.qm \
        translation/texstudio_ko.qm \
        translation/texstudio_ko_KR.qm \
        translation/texstudio_nl.qm \
        translation/texstudio_pl.qm \
        translation/texstudio_pt.qm \
        translation/texstudio_pt_BR.qm \
        translation/texstudio_ru_RU.qm \
        translation/texstudio_sk.qm \
        translation/texstudio_sv.qm \
        translation/texstudio_tr_TR.qm \
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
        utilities/manual/CHANGELOG.txt
    manual.files = \
        utilities/manual/usermanual_en.html \
        utilities/manual/usermanual.css \
        utilities/manual/doc1.png \
        utilities/manual/doc10.png \
        utilities/manual/doc11.png \
        utilities/manual/doc12.png \
        utilities/manual/doc13.png \
        utilities/manual/doc14.png \
        utilities/manual/doc15.png \
        utilities/manual/doc16.png \
        utilities/manual/doc17.png \
        utilities/manual/doc18.png \
        utilities/manual/doc19.png \
        utilities/manual/doc2.png \
        utilities/manual/doc20.png \
        utilities/manual/doc21.png \
        utilities/manual/doc3.png \
        utilities/manual/doc5.png \
        utilities/manual/doc6.png \
        utilities/manual/doc7.png \
        utilities/manual/doc8.png \
        utilities/manual/doc9.png \
        utilities/manual/configure_completion.png \
        utilities/manual/configure_commands.png \
        utilities/manual/configure_customizeMenu.png \
        utilities/manual/configure_customToolbar.png \
        utilities/manual/configure_editor.png \
        utilities/manual/configure_general.png \
        utilities/manual/configure_shortcuts.png \
        utilities/manual/configure_svn.png \
        utilities/manual/configure_build.png \
        utilities/manual/compile_toolbar.png \
        utilities/manual/template.png \
        utilities/manual/thesaurus.png \
        utilities/manual/wizard_figure.png \
        utilities/manual/block_selection.png \
        utilities/manual/spellcheck_menu.png \
        utilities/manual/spellcheck_options.png \
        utilities/manual/format_example.png
    INSTALLS += target \
        manual \
        utilities
}

include(src/hunspell/hunspell.pri)

include(src/qcodeedit/qcodeedit.pri)

include(src/latexparser/latexparser.pri)

include(src/symbolpanel/symbolpanel.pri)

include(src/quazip/quazip/quazip.pri)

include(src/pdfviewer/pdfviewer.pri)

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
    message(GIT)
    system(\"$${PWD}/git_revision.bat\" $${QMAKE_CXX} \"$${OUT_PWD}\" \"$${PWD}\")
    SOURCES += src/git_revision.cpp
  } else {
    message(GIT)
    QMAKE_PRE_LINK += \"$${PWD}/git_revision.sh\" $${QMAKE_CXX} \"$${OUT_PWD}\" \"$${PWD}\"
    LIBS += git_revision.o
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
  QMAKE_CXXFLAGS_DEBUG += -Wall -Wextra -Wmissing-include-dirs -Wunknown-pragmas -Wundef -Wpointer-arith -Winline -O0
  QMAKE_CXXFLAGS += -std=c++11
  !win32:!haiku: QMAKE_LFLAGS += -rdynamic # option not supported by mingw and haiku
  else {
    QMAKE_CXXFLAGS += -gstabs -g
    QMAKE_LFLAGS -= -Wl,-s
    QMAKE_LFLAGS_RELEASE -= -Wl,-s
  }
} else {
  DEFINES += _CRT_SECURE_NO_WARNINGS
}

*-g++:equals(QT_MAJOR_VERSION, 5):lessThan(QT_MINOR_VERSION, 13) {
  QMAKE_CXXFLAGS += -Wno-deprecated-copy
}
