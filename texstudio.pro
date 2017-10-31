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
else:include(qtsingleapplication/qtsingleapplication.pri)

# ##############################
# precompile_header: PRECOMPILED_HEADER = mostQtHeaders.h
HEADERS += \
    aboutdialog.h \
    arraydialog.h \
    bibtexdialog.h \
    bibtexparser.h \
    bibtexreader.h \
    bidiextender.h \
    bookmarks.h \
    buildmanager.h \
    cleandialog.h \
    codesnippet.h \
    configdialog.h \
    configmanager.h \
    configmanagerinterface.h \
    cursorhistory.h \
    cursorposition.h \
    dblclickmenubar.h \
    debughelper.h \
    diff/diff_match_patch.h \
    diffoperations.h \
    directoryreader.h \
    editors.h \
    encoding.h \
    encodingdialog.h \
    filechooser.h \
    fileselector.h \
    flowlayout.h \
    grammarcheck.h \
    grammarcheck_config.h \
    help.h \
    icondelegate.h \
    insertgraphics.h \
    insertgraphics_config.h \
    kpathseaParser.h \
    latexcompleter.h \
    latexcompleter_config.h \
    latexcompleter_p.h \
    latexdocument.h \
    latexeditorview.h \
    latexeditorview_config.h \
    latexlog.h \
    latexlogwidget.h \
    latexoutputfilter.h \
    latexpackage.h \
    latexrepository.h \
    latexstructure.h \
    latexstyleparser.h \
    letterdialog.h \
    libqmarkedscrollbar/src/markedscrollbar.h \
    logeditor.h \
    loghighlighter.h \
    maketemplatedialog.h \
    manhattanstyle.h \
    mathassistant.h \
    minisplitter.h \
    modifiedQObject.h \
    mostQtHeaders.h \
    pdfsplittool.h \
    qmetautils.h \
    quickbeamerdialog.h \
    quickdocumentdialog.h \
    randomtextgenerator.h \
    scriptengine.h \
    scriptobject.h \
    searchquery.h \
    searchresultmodel.h \
    searchresultwidget.h \
    session.h \
    sessionlist.h \
    smallUsefulFunctions.h \
    spellerdialog.h \
    spellerutility.h \
    structuretreeview.h \
    styleanimator.h \
    stylehelper.h \
    svn.h \
    syntaxcheck.h \
    tabbingdialog.h \
    tabdialog.h \
    tablemanipulation.h \
    templatemanager.h \
    templatemanager_p.h \
    templateselector.h \
    texdocdialog.h \
    texstudio.h \
    textanalysis.h \
    thesaurusdialog.h \
    titledpanel.h \
    toolwidgets.h \
    txstabwidget.h \
    unicodeinsertion.h \
    universalinputdialog.h \
    unixutils.h \
    updatechecker.h \
    usermacro.h \
    usermenudialog.h \
    userquickdialog.h \
    utilsSystem.h \
    utilsUI.h \
    utilsVersion.h \
    webpublishdialog.h \
    webpublishdialog_config.h \
    xmltagslistwidget.h

SOURCES += \
    aboutdialog.cpp \
    additionaltranslations.cpp \
    arraydialog.cpp \
    bibtexdialog.cpp \
    bibtexparser.cpp \
    bibtexreader.cpp \
    bidiextender.cpp \
    bookmarks.cpp \
    buildmanager.cpp \
    cleandialog.cpp \
    codesnippet.cpp \
    configdialog.cpp \
    configmanager.cpp \
    cursorhistory.cpp \
    cursorposition.cpp \
    dblclickmenubar.cpp \
    debughelper.cpp \
    diff/diff_match_patch.cpp \
    diffoperations.cpp \
    directoryreader.cpp \
    editors.cpp \
    encoding.cpp \
    encodingdialog.cpp \
    filechooser.cpp \
    fileselector.cpp \
    flowlayout.cpp \
    grammarcheck.cpp \
    help.cpp \
    icondelegate.cpp \
    insertgraphics.cpp \
    kpathseaParser.cpp \
    latexcompleter.cpp \
    latexdocument.cpp \
    latexeditorview.cpp \
    latexlog.cpp \
    latexlogwidget.cpp \
    latexoutputfilter.cpp \
    latexpackage.cpp \
    latexrepository.cpp \
    latexstructure.cpp \
    latexstyleparser.cpp \
    letterdialog.cpp \
    libqmarkedscrollbar/src/markedscrollbar.cpp \
    logeditor.cpp \
    loghighlighter.cpp \
    main.cpp \
    maketemplatedialog.cpp \
    manhattanstyle.cpp \
    mathassistant.cpp \
    minisplitter.cpp \
    pdfsplittool.cpp \
    qmetautils.cpp \
    quickbeamerdialog.cpp \
    quickdocumentdialog.cpp \
    randomtextgenerator.cpp \
    scriptengine.cpp \
    scriptobject.cpp \
    searchquery.cpp \
    searchresultmodel.cpp \
    searchresultwidget.cpp \
    session.cpp \
    sessionlist.cpp \
    smallUsefulFunctions.cpp \
    spellerdialog.cpp \
    spellerutility.cpp \
    structuretreeview.cpp \
    styleanimator.cpp \
    stylehelper.cpp \
    svn.cpp \
    syntaxcheck.cpp \
    tabbingdialog.cpp \
    tabdialog.cpp \
    tablemanipulation.cpp \
    templatemanager.cpp \
    templatemanager_p.cpp \
    templateselector.cpp \
    texdocdialog.cpp \
    texstudio.cpp \
    textanalysis.cpp \
    thesaurusdialog.cpp \
    titledpanel.cpp \
    toolwidgets.cpp \
    txstabwidget.cpp \
    unicodeinsertion.cpp \
    universalinputdialog.cpp \
    unixutils.cpp \
    updatechecker.cpp \
    usermacro.cpp \
    usermenudialog.cpp \
    userquickdialog.cpp \
    utilsSystem.cpp \
    utilsUI.cpp \
    utilsVersion.cpp \
    webpublishdialog.cpp \
    xmltagslistwidget.cpp

win32: SOURCES += utilssystem_win.cpp
else: SOURCES += utilssystem_unix.cpp

RESOURCES += texstudio.qrc \
    symbols.qrc \
    completion.qrc \
    images.qrc

FORMS += \
    aboutdialog.ui \
    arraydialog.ui \
    bibtexdialog.ui \
    cleandialog.ui \
    configdialog.ui \
    encodingdialog.ui \
    filechooser.ui \
    insertgraphics.ui \
    letterdialog.ui \
    maketemplatedialog.ui \
    pdfsplittool.ui \
    quickbeamerdialog.ui \
    quickdocumentdialog.ui \
    randomtextgenerator.ui \
    spellerdialog.ui \
    tabbingdialog.ui \
    tabdialog.ui \
    templateselector.ui \
    texdocdialog.ui \
    textanalysis.ui \
    usermenudialog.ui \
    userquickdialog.ui \
    webpublishdialog.ui

TRANSLATIONS += texstudio_ar.ts \
    texstudio_cs.ts \
    texstudio_de.ts \
    texstudio_el.ts \
    texstudio_es.ts \
    texstudio_fa.ts \
    texstudio_fr.ts \
    texstudio_hu.ts \
    texstudio_it.ts \
    texstudio_ja.ts \
    texstudio_nl.ts \
    texstudio_pl.ts \
    texstudio_pt_BR.ts \
    texstudio_ru_RU.ts \
    texstudio_tr_TR.ts \
    texstudio_uk.ts \
    texstudio_vi.ts \
    texstudio_zh_CN.ts

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
    SOURCES += xkb/XKeyboard.cpp
    HEADERS += xkb/XKeyboard.h xkb/X11Exception.h
    LIBS += -lX11
}

# ##########UNIX + MACX###############
unix {
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
    utilities.files += utilities/latex2e.html \
        utilities/latex2e.css \
        texstudio_ar.qm \
        texstudio_cs.qm \
        texstudio_de.qm \
        texstudio_el.qm \
        texstudio_es.qm \
        texstudio_fa.qm \
        texstudio_fr.qm \
        texstudio_hu.qm \
        texstudio_it.qm \
        texstudio_ja.qm \
        texstudio_nl.qm \
        texstudio_pl.qm \
        texstudio_pt_BR.qm \
        texstudio_ru_RU.qm \
        texstudio_tr_TR.qm \
        texstudio_uk.qm \
        texstudio_vi.qm \
        texstudio_zh_CN.qm \
        qt_cs.qm \
        qt_de.qm \
        qt_ja.qm \
        qt_fr.qm \
        qt_hu.qm \
        qt_pl.qm \
        qt_zh.qm \
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
  include(hunspell/hunspell.pri)
} else {
  CONFIG += link_pkgconfig
  PKGCONFIG += hunspell
}

include(qcodeedit/qcodeedit.pri)

include(latexparser/latexparser.pri)

include(symbolpanel/symbolpanel.pri)

isEmpty(USE_SYSTEM_QUAZIP) {
  DEFINES += QUAZIP_STATIC
  include(quazip/quazip/quazip.pri)
} else {
  isEmpty(QUAZIP_LIB): QUAZIP_LIB = -lquazip
  isEmpty(QUAZIP_INCLUDE): QUAZIP_INCLUDE = $${PREFIX}/include/quazip

  INCLUDEPATH += $${QUAZIP_INCLUDE}
  LIBS += $${QUAZIP_LIB}
}

include(pdfviewer/pdfviewer.pri)

# ###############################

CONFIG(debug, debug|release) {
    message(Creating debug version)
    CONFIG -= release
    QT += testlib

    SOURCES += \
        tests/codesnippet_t.cpp \
        tests/encoding_t.cpp \
        tests/latexcompleter_t.cpp \
        tests/latexeditorview_bm.cpp \
        tests/latexeditorview_t.cpp \
        tests/latexoutputfilter_t.cpp \
        tests/latexparser_t.cpp \
        tests/latexparsing_t.cpp \
        tests/qcetestutil.cpp \
        tests/qdocumentcursor_t.cpp \
        tests/qdocumentline_t.cpp \
        tests/qdocumentsearch_t.cpp \
        tests/qeditor_t.cpp \
        tests/qsearchreplacepanel_t.cpp \
        tests/scriptengine_t.cpp \
        tests/smallUsefulFunctions_t.cpp \
        tests/structureview_t.cpp \
        tests/syntaxcheck_t.cpp \
        tests/tablemanipulation_t.cpp \
        tests/testmanager.cpp \
        tests/testutil.cpp
    HEADERS += \
        tests/qsearchreplacepanel_t.h \
        tests/updatechecker_t.h \
        tests/qdocumentcursor_t.h \
        tests/qdocumentline_t.h \
        tests/qdocumentsearch_t.h \
        tests/codesnippet_t.h \
        tests/latexcompleter_t.h \
        tests/latexeditorview_bm.h \
        tests/latexeditorview_t.h \
        tests/latexoutputfilter_t.h \
        tests/latexparser_t.h \
        tests/latexparsing_t.h \
        tests/latexstyleparser_t.h \
        tests/scriptengine_t.h \
        tests/qeditor_t.h \
        tests/buildmanager_t.h \
        tests/tablemanipulation_t.h \
        tests/smallUsefulFunctions_t.h \
        tests/utilsui_t.h \
        tests/utilsversion_t.h \
        tests/encoding_t.h \
        tests/help_t.h \
        tests/syntaxcheck_t.h \
        tests/qcetestutil.h \
        tests/testmanager.h \
        tests/testutil.h \
        tests/structureview_t.h
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
exists(./.hg2) | exists(./.hg) {
  win32: {
    message(HG)
    QMAKE_PRE_LINK += \"$${PWD}/hg_revision.bat\" $${QMAKE_CXX} \"$${OUT_PWD}\"
    LIBS += hg_revision.o
  } else {
    QMAKE_PRE_LINK += \"$${PWD}/hg_revision.sh\" $${QMAKE_CXX} \"$${OUT_PWD}\"
    LIBS += hg_revision.o
  }
} else {
  !exists(./hg_revision.cpp){
    win32: system(echo const char * TEXSTUDIO_HG_REVISION = 0; > hg_revision.cpp)
    else: system(echo \"const char * TEXSTUDIO_HG_REVISION = 0;\" > hg_revision.cpp)
  }
  SOURCES += hg_revision.cpp
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
