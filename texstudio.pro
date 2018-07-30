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
    message(Building with Qt4)
    CONFIG += qt uitools
    CONFIG -= precompile_header
}

# allow loading extra config by file for automatic compilations (OBS)
exists(texstudio.pri):include(texstudio.pri)
QT += network \
    xml \
    svg \
    script \
    printsupport \
    concurrent
greaterThan(QT_MAJOR_VERSION, 4) {
QT += \
    widgets \
    uitools
}
!isEmpty(PHONON){
    greaterThan(QT_MAJOR_VERSION, 4) { #Qt5
        QT += phonon4qt5
    } else { #Qt4
        QT += phonon
    }
    DEFINES += PHONON
}
contains($$list($$[QT_VERSION]), 4.3.*):message("qt 4.3.x")
else:include(src/qtsingleapplication/qtsingleapplication.pri)

# ##############################
# precompile_header: PRECOMPILED_HEADER = mostQtHeaders.h
# principal sources
include(src/sources.pri)

RESOURCES += texstudio.qrc \
    symbols.qrc \
    completion.qrc \
    images.qrc


TRANSLATIONS += translation/texstudio_ar.ts \
    translation/texstudio_cs.ts \
    translation/texstudio_de.ts \
    translation/texstudio_el.ts \
    translation/texstudio_es.ts \
    translation/texstudio_fa.ts \
    translation/texstudio_fr.ts \
    translation/texstudio_hu.ts \
    translation/texstudio_it.ts \
    translation/texstudio_ja.ts \
    translation/texstudio_ko.ts \
    translation/texstudio_ko_KR.ts \
    translation/texstudio_nl.ts \
    translation/texstudio_pl.ts \
    translation/texstudio_pt_BR.ts \
    translation/texstudio_ru_RU.ts \
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
        appdata.path = $${DATADIR}/appdata
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
        translation/texstudio_cs.qm \
        translation/texstudio_de.qm \
        translation/texstudio_el.qm \
        translation/texstudio_es.qm \
        translation/texstudio_fa.qm \
        translation/texstudio_fr.qm \
        translation/texstudio_hu.qm \
        translation/texstudio_it.qm \
        translation/texstudio_ja.qm \
        translation/texstudio_ko.qm \
        translation/texstudio_ko_KR.qm \
        translation/texstudio_nl.qm \
        translation/texstudio_pl.qm \
        translation/texstudio_pt_BR.qm \
        translation/texstudio_ru_RU.qm \
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
        utilities/manual/spellcheck_menu.png
    INSTALLS += target \
        manual \
        utilities
}

isEmpty(USE_SYSTEM_HUNSPELL){
  DEFINES += HUNSPELL_STATIC
  include(src/hunspell/hunspell.pri)
} else {
  message(System hunspell)
  CONFIG += link_pkgconfig
  PKGCONFIG += hunspell
}

include(src/qcodeedit/qcodeedit.pri)

include(src/latexparser/latexparser.pri)

include(src/symbolpanel/symbolpanel.pri)

isEmpty(USE_SYSTEM_QUAZIP) {
  DEFINES += QUAZIP_STATIC
  include(src/quazip/quazip/quazip.pri)
} else {
  greaterThan(QT_MAJOR_VERSION, 4) { #Qt5
    message(System quazip5)
    isEmpty(QUAZIP_LIB): QUAZIP_LIB = -lquazip5
    isEmpty(QUAZIP_INCLUDE): QUAZIP_INCLUDE = $${PREFIX}/include/quazip5
  } else { #Qt4
    message(System quazip)
    isEmpty(QUAZIP_LIB): QUAZIP_LIB = -lquazip
    isEmpty(QUAZIP_INCLUDE): QUAZIP_INCLUDE = $${PREFIX}/include/quazip
  }
  INCLUDEPATH += $${QUAZIP_INCLUDE}
  LIBS += $${QUAZIP_LIB}
}

include(src/pdfviewer/pdfviewer.pri)

# ###############################

CONFIG(debug, debug|release) {
    message(Creating debug version)
    CONFIG -= release
    QT += testlib

    SOURCES += \
        src/tests/codesnippet_t.cpp \
        src/tests/encoding_t.cpp \
        src/tests/latexcompleter_t.cpp \
        src/tests/latexeditorview_bm.cpp \
        src/tests/latexeditorview_t.cpp \
        src/tests/latexoutputfilter_t.cpp \
        src/tests/latexparser_t.cpp \
        src/tests/latexparsing_t.cpp \
        src/tests/qcetestutil.cpp \
        src/tests/qdocumentcursor_t.cpp \
        src/tests/qdocumentline_t.cpp \
        src/tests/qdocumentsearch_t.cpp \
        src/tests/qeditor_t.cpp \
        src/tests/qsearchreplacepanel_t.cpp \
        src/tests/scriptengine_t.cpp \
        src/tests/smallUsefulFunctions_t.cpp \
        src/tests/structureview_t.cpp \
        src/tests/syntaxcheck_t.cpp \
        src/tests/tablemanipulation_t.cpp \
        src/tests/testmanager.cpp \
        src/tests/testutil.cpp
    HEADERS += \
        src/tests/qsearchreplacepanel_t.h \
        src/tests/updatechecker_t.h \
        src/tests/qdocumentcursor_t.h \
        src/tests/qdocumentline_t.h \
        src/tests/qdocumentsearch_t.h \
        src/tests/codesnippet_t.h \
        src/tests/latexcompleter_t.h \
        src/tests/latexeditorview_bm.h \
        src/tests/latexeditorview_t.h \
        src/tests/latexoutputfilter_t.h \
        src/tests/latexparser_t.h \
        src/tests/latexparsing_t.h \
        src/tests/latexstyleparser_t.h \
        src/tests/scriptengine_t.h \
        src/tests/qeditor_t.h \
        src/tests/buildmanager_t.h \
        src/tests/tablemanipulation_t.h \
        src/tests/smallUsefulFunctions_t.h \
        src/tests/utilsui_t.h \
        src/tests/utilsversion_t.h \
        src/tests/encoding_t.h \
        src/tests/help_t.h \
        src/tests/syntaxcheck_t.h \
        src/tests/qcetestutil.h \
        src/tests/testmanager.h \
        src/tests/testutil.h \
        src/tests/structureview_t.h
    !greaterThan(QT_MAJOR_VERSION, 4) {
        win32:LIBS += -lQtTestd4
    } else {
        win32:LIBS += -lQt5Testd
    }
    #unix:!macx:LIBS += -lQtTest
    macx:LIBS += -framework QtTest
}
macx:LIBS += -framework CoreFoundation

unix {
    LIBS += -L/usr/lib \
    -lz
}

freebsd-* {
    LIBS += -lexecinfo
}

!isEmpty(NO_CRASH_HANDLER) {
    DEFINES += NO_CRASH_HANDLER
    message("Internal crash handler disabled as you wish.")
}
!isEmpty(NO_TESTS) {
    DEFINES += NO_TESTS
    message("tests disabled as you wish.")
}


# ###############################
# add files to svn if team is set
CONFIG(team):!CONFIG(build_pass) {
    SVNPREPATH = ./
    SVNPATH = /.svn/text-base/
    SVNEXT = .svn-base
    ALLFILES = $${HEADERS}
    ALLFILES += $${SOURCES}
    ALLFILES += $${FORMS}
    for(filename, ALLFILES):!exists($${SVNPREPATH}$$dirname(filename)$${SVNPATH}$$basename(filename)$${SVNEXT}) {
        warning($${filename} not contained in svn base will be added)
        system(svn add $${filename})
    }
}
OTHER_FILES += universalinputdialog.*

# add mercurial revision
exists(./.git)  {
  win32:isEmpty(MXE): {
    message(GIT)
    QMAKE_PRE_LINK += \"$${PWD}/git_revision.bat\" $${QMAKE_CXX} \"$${OUT_PWD}\" \"$${PWD}\"
    LIBS += git_revision.o
  } else {
    message(GIT)
    QMAKE_PRE_LINK += \"$${PWD}/git_revision.sh\" $${QMAKE_CXX} \"$${OUT_PWD}\" \"$${PWD}\"
    LIBS += git_revision.o
  }
} else {
  !exists(./git_revision.cpp){
    win32:isEmpty(MXE): system(echo const char * TEXSTUDIO_GIT_REVISION = 0; > src\git_revision.cpp)
    else: system(echo \"const char * TEXSTUDIO_GIT_REVISION = 0;\" > src/git_revision.cpp)
  }
  SOURCES += src/git_revision.cpp
}

#QMAKE_CXXFLAGS_DEBUG += -Werror  -Wall -Wextra -Winit-self -Wmain -Wmissing-include-dirs -Wtrigraphs -Wunused -Wunknown-pragmas -Wundef -Wpointer-arith -Wtype-limits -Wwrite-strings -Wclobbered -Wempty-body -Wsign-compare -Waddress -Wlogical-op -Winline
QMAKE_CXXFLAGS_DEBUG += -Wall -Wextra -Winit-self -Wmissing-include-dirs -Wtrigraphs -Wunused -Wunknown-pragmas -Wundef -Wpointer-arith -Wwrite-strings -Wempty-body -Wsign-compare -Waddress -Winline
QMAKE_CXXFLAGS += -std=c++0x
!win32: QMAKE_LFLAGS += -rdynamic # option not supported by mingw
else {
  QMAKE_CXXFLAGS += -gstabs -g
  QMAKE_LFLAGS -= -Wl,-s
  QMAKE_LFLAGS_RELEASE -= -Wl,-s
}
