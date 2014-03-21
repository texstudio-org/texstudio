TEMPLATE = app
LANGUAGE = C++
DESTDIR = ./
CONFIG += qt precompile_header uitools
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
PRECOMPILED_HEADER = mostQtHeaders.h
HEADERS += texmaker.h \
    buildmanager.h \
    dsingleapplication.h \
    symbolgridwidget.h \
    icondelegate.h \
    latexcompleter.h \
    latexeditorview.h \
    latexeditorview_config.h \
    latexlog.h \
    logeditor.h \
    loghighlighter.h \
    smallUsefulFunctions.h \
    structdialog.h \
    encodingdialog.h \
    filechooser.h \
    tabbingdialog.h \
    arraydialog.h \
    tabdialog.h \
    letterdialog.h \
    quickdocumentdialog.h \
    usermenudialog.h \
    usertooldialog.h \
    configmanager.h \
    configdialog.h \
    aboutdialog.h \
    webpublishdialog.h \
    spellerdialog.h \
    spellerutility.h \
    textanalysis.h \
    toolwidgets.h \
    latexoutputfilter.h \
    latexcompleter_config.h \
    latexcompleter_p.h \
    codesnippet.h \
    debughelper.h \
    thesaurusdialog.h \
    xmltagslistwidget.h \
    randomtextgenerator.h \
    templateselector.h \
    bibtexdialog.h \
    manhattanstyle.h \
    stylehelper.h \
    styleanimator.h \
    webpublishdialog_config.h \
    findGlobalDialog.h \
    searchresultmodel.h \
    bibtexparser.h \
    latexdocument.h \
    unicodeinsertion.h \
    universalinputdialog.h \
    scriptengine.h \
    insertgraphics.h \
    txstabwidget.h \
    configmanagerinterface.h \
    modifiedQObject.h \
    mostQtHeaders.h \
    tablemanipulation.h \
    syntaxcheck.h \
    tests/latexcompleter_t.h \
    tests/qdocumentline_t.h \
    userquickdialog.h \
    PDFDocument.h \
    PDFDocks.h \
    synctex_parser_utils.h \
    synctex_parser.h \
    latexstyleparser.h \
    pdfrenderengine.h \
    pdfrendermanager.h \
    PDFDocument_config.h \
    scriptobject.h \
    directoryreader.h \
    insertgraphics_config.h \
    diff/diff_match_patch.h \
    diffoperations.h \
    grammarcheck.h \
    grammarcheck_config.h \
    bibtexreader.h \
    cleandialog.h \
    qmetautils.h \
    updatechecker.h \
    usermacro.h \
    dblclickmenubar.h \
    tests/updatechecker_t.h \
    mathassistant.h \
    cursorhistory.h \
    maketemplatedialog.h \
    templatemanager.h \
    templatemanager_p.h \
    texdocdialog.h \
    help.h \
    bookmarks.h \
    session.h \
    fileselector.h \
    utilsUI.h \
    utilsSystem.h \
    utilsVersion.h \
    latexpackages.h \
    cursorposition.h \
    tests/help_t.h \
    titledpanel.h \
    latexlogwidget.h \
    pdfannotationdlg.h \
    pdfannotation.h \
    kpathseaParser.h \
    tests/latexoutputfilter_t.h \
    sessionlist.h
SOURCES += main.cpp \
    buildmanager.cpp \
    dsingleapplication.cpp \
    texmaker.cpp \
    symbolgridwidget.cpp \
    icondelegate.cpp \
    latexcompleter.cpp \
    latexeditorview.cpp \
    latexlog.cpp \
    logeditor.cpp \
    loghighlighter.cpp \
    smallUsefulFunctions.cpp \
    structdialog.cpp \
    filechooser.cpp \
    tabbingdialog.cpp \
    arraydialog.cpp \
    tabdialog.cpp \
    letterdialog.cpp \
    quickdocumentdialog.cpp \
    usermenudialog.cpp \
    usertooldialog.cpp \
    configmanager.cpp \
    configdialog.cpp \
    debughelper.cpp \
    aboutdialog.cpp \
    webpublishdialog.cpp \
    spellerdialog.cpp \
    spellerutility.cpp \
    textanalysis.cpp \
    latexoutputfilter.cpp \
    toolwidgets.cpp \
    codesnippet.cpp \
    thesaurusdialog.cpp \
    xmltagslistwidget.cpp \
    encodingdialog.cpp \
    randomtextgenerator.cpp \
    templateselector.cpp \
    bibtexdialog.cpp \
    manhattanstyle.cpp \
    stylehelper.cpp \
    styleanimator.cpp \
    findGlobalDialog.cpp \
    searchresultmodel.cpp \
    bibtexparser.cpp \
    latexdocument.cpp \
    unicodeinsertion.cpp \
    universalinputdialog.cpp \
    scriptengine.cpp \
    insertgraphics.cpp \
    txstabwidget.cpp \
    additionaltranslations.cpp \
    tablemanipulation.cpp \
    syntaxcheck.cpp \
    tests/latexcompleter_t.cpp \
    tests/qdocumentline_t.cpp \
    userquickdialog.cpp \
    PDFDocument.cpp \
    PDFDocks.cpp \
    latexstyleparser.cpp \
    pdfrenderengine.cpp \
    pdfrendermanager.cpp \
    scriptobject.cpp \
    directoryreader.cpp \
    diff/diff_match_patch.cpp \
    diffoperations.cpp \
    grammarcheck.cpp \
    bibtexreader.cpp \
    cleandialog.cpp \
    qmetautils.cpp \
    updatechecker.cpp \
    dblclickmenubar.cpp \
    mathassistant.cpp \
    cursorhistory.cpp \
    maketemplatedialog.cpp \
    templatemanager.cpp \
    templatemanager_p.cpp \
    texdocdialog.cpp \
    help.cpp \
    bookmarks.cpp \
    session.cpp \
    fileselector.cpp \
    utilsUI.cpp \
    utilsSystem.cpp \
    latexpackages.cpp \
    cursorposition.cpp \
    usermacro.cpp \
    titledpanel.cpp \
    latexlogwidget.cpp \
    pdfannotationdlg.cpp \
    pdfannotation.cpp \
    kpathseaParser.cpp \
    tests/latexoutputfilter_t.cpp \
    sessionlist.cpp
RESOURCES += texstudio.qrc \
    symbols.qrc \
    completion.qrc \
    images.qrc
FORMS += structdialog.ui \
    filechooser.ui \
    insertgraphics.ui \
    tabbingdialog.ui \
    arraydialog.ui \
    tabdialog.ui \
    letterdialog.ui \
    quickdocumentdialog.ui \
    usermenudialog.ui \
    usertooldialog.ui \
    aboutdialog.ui \
    webpublishdialog.ui \
    configdialog.ui \
    spellerdialog.ui \
    textanalysis.ui \
    encodingdialog.ui \
    randomtextgenerator.ui \
    templateselector.ui \
    bibtexdialog.ui \
    findGlobalDialog.ui \
    userquickdialog.ui \
    PDFDocument.ui \
    cleandialog.ui \
    maketemplatedialog.ui \
    texdocdialog.ui \
    pdfannotationdlg.ui
TRANSLATIONS += texstudio_cs.ts \
    texstudio_de.ts \
    texstudio_es.ts \
    texstudio_fr.ts \
    texstudio_hu.ts \
    texstudio_it.ts \
    texstudio_pt_BR.ts \
    texstudio_uk.ts \
    texstudio_ru.ts \
    texstudio_ja.ts \
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
    utilities.path = Contents/Resources
    QMAKE_BUNDLE_DATA += utilities
    ICON = texstudio.icns
    QMAKE_INFO_PLIST = Info.plist
}

# ###############################
unix:!macx {
    isEmpty( PREFIX ):PREFIX = /usr
    DEFINES += PREFIX=\\\"$${PREFIX}\\\"
    target.path = $${PREFIX}/bin
    utilities.path = $${PREFIX}/share/texstudio
    utilities.files = utilities/texstudio16x16.png \
        utilities/texstudio22x22.png \
        utilities/texstudio32x32.png \
        utilities/texstudio48x48.png \
        utilities/texstudio64x64.png \
        utilities/texstudio128x128.png \
        utilities/texstudio.svg
    applicationmenu.path = $${PREFIX}/share/applications
    applicationmenu.files = utilities/texstudio.desktop
    INSTALLS += applicationmenu
}

# ##########UNIX + MACX###############
unix {
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
    utilities.files += utilities/doc1.png \
        utilities/doc10.png \
        utilities/doc11.png \
        utilities/doc12.png \
        utilities/doc13.png \
        utilities/doc14.png \
        utilities/doc15.png \
        utilities/doc16.png \
        utilities/doc17.png \
        utilities/doc18.png \
        utilities/doc19.png \
        utilities/doc2.png \
        utilities/doc20.png \
        utilities/doc21.png \
        utilities/doc3.png \
        utilities/doc4.png \
        utilities/doc5.png \
        utilities/doc6.png \
        utilities/doc7.png \
        utilities/doc8.png \
        utilities/doc9.png \
        utilities/configure_completion.png \
        utilities/configure_customizeMenu.png \
        utilities/configure_customToolbar.png \
        utilities/configure_editor.png \
        utilities/configure_general.png \
        utilities/configure_shortcuts.png \
        utilities/configure_svn.png \
        utilities/configure_build.png \
        utilities/compile_toolbar.png \
        utilities/template.png \
        utilities/thesaurus.png \
        utilities/latex2e.html \
        utilities/latex2e.css \
        utilities/wizard_figure.png \
	utilities/block_selection.png \
	utilities/spellcheck_menu.png \
	texstudio_cs.qm \
	texstudio_de.qm \
	texstudio_es.qm \
	texstudio_fr.qm \
	texstudio_hu.qm \
	texstudio_it.qm \
	texstudio_ja.qm \
	texstudio_pt_BR.qm \
	texstudio_uk.qm \
	texstudio_ru.qm \
	texstudio_zh_CN.qm \
        qt_cs.qm \
        qt_de.qm \
        qt_ja.qm \
        qt_fr.qm \
        qt_hu.qm \
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
	templates/template_Article_French.json \
	templates/template_Article_French.tex \
	templates/template_Article.json \
	templates/template_Article.png \
	templates/template_Article.tex \
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
        templates/template_Moderncv_French.json \
        templates/template_Moderncv_French.png \
        templates/template_Moderncv_French.tex \
        templates/template_Moderncv.json \
        templates/template_Moderncv.png \
        templates/template_Moderncv.tex \
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
        utilities/usermanual_en.html \
	utilities/usermanual.css \
        utilities/usermanual_fr.html \
	utilities/dictionaries/en_GB.aff \
	utilities/dictionaries/en_GB.dic \
	utilities/dictionaries/en_US.aff \
	utilities/dictionaries/en_US.dic \
	utilities/dictionaries/fr_FR.aff \
	utilities/dictionaries/fr_FR.dic \
	utilities/dictionaries/de_DE.aff \
	utilities/dictionaries/de_DE.dic \
	utilities/dictionaries/hu_HU.aff \
	utilities/dictionaries/hu_HU.dic \
	utilities/dictionaries/pt_BR.aff \
	utilities/dictionaries/pt_BR.dic \
	utilities/dictionaries/de.badWords \
	utilities/dictionaries/de.stopWords \
	utilities/dictionaries/de.stopWords.level2 \
	utilities/dictionaries/en.stopWords \
	utilities/dictionaries/fr.stopWords \
	utilities/dictionaries/th_en_US_v2.dat \
	utilities/dictionaries/th_fr_FR_v2.dat \
	utilities/dictionaries/th_de_DE_v2.dat \
        utilities/AUTHORS \
        utilities/COPYING \
        utilities/CHANGELOG.txt
    INSTALLS += target \
        utilities
}

DEFINES += HUNSPELL_STATIC
include(hunspell/hunspell.pri)

include(qcodeedit/qcodeedit.pri)

DEFINES += QUAZIP_STATIC
include(quazip/quazip/quazip.pri)


# ###############################


debug{
    message(Creating debug version)
    CONFIG -= release
    QT += testlib

    SOURCES += tests/testmanager.cpp \
        tests/testutil.cpp \
        tests/qcetestutil.cpp \
        tests/codesnippet_t.cpp \
        tests/scriptengine_t.cpp \
        tests/qdocumentcursor_t.cpp \
        tests/qdocumentsearch_t.cpp \
        tests/qsearchreplacepanel_t.cpp \
        tests/qeditor_t.cpp \
        tests/latexeditorview_t.cpp \
        tests/latexeditorview_bm.cpp \
        tests/tablemanipulation_t.cpp \
        tests/structureview_t.cpp \
        tests/syntaxcheck_t.cpp
    HEADERS += tests/testmanager.h \
        tests/testutil.h \
        tests/qcetestutil.h \
        tests/smallUsefulFunctions_t.h \
	tests/buildmanager_t.h \
        tests/codesnippet_t.h \
        tests/scriptengine_t.h \
        tests/qdocumentcursor_t.h \
        tests/qdocumentsearch_t.h \
        tests/qsearchreplacepanel_t.h \
        tests/qeditor_t.h \
        tests/latexeditorview_t.h \
        tests/latexeditorview_bm.h \
        tests/tablemanipulation_t.h \
        tests/structureview_t.h \
        tests/syntaxcheck_t.h
# win32:LIBS += -lQtTest4
win32:LIBS += -lQtTestd4
#unix:!macx:LIBS += -lQtTest
macx:LIBS += -framework QtTest
}
macx:LIBS += -framework CoreFoundation

unix {
    LIBS += -L/usr/lib \
    -lz
}

# ################################
# Poppler PDF Preview, will only be used if NO_POPPLER_PREVIEW is not set
isEmpty(NO_POPPLER_PREVIEW) {
  !greaterThan(QT_MAJOR_VERSION, 4) { #Qt4
    unix:!macx {
    
        INCLUDEPATH += /usr/include/poppler/qt4
        LIBS += -L/usr/lib \
            -lpoppler-qt4 \
            -lz
    }
    macx {
        INCLUDEPATH += /usr/local/include/poppler/qt4
        LIBS += -L/usr/lib \
            -L/usr/local/lib \
            -lpoppler-qt4 \
            -lz
    }
    win32 {
	INCLUDEPATH  += ./include_win32
	LIBS += ./zlib1.dll \
	    ./libpoppler-qt4.dll \
    }
  }else:{ # Qt5
    unix:!macx {
    
	INCLUDEPATH += /home/sdm/Dokumente/Programmieren/poppler/include/poppler/qt5
        LIBS += -L/usr/lib \
	     -L/home/sdm/Dokumente/Programmieren/poppler/lib \
            -lpoppler-qt5 \
            -lz
    }
    macx {
        INCLUDEPATH += /usr/local/include/poppler/qt5
        LIBS += -L/usr/lib \
            -L/usr/local/lib \
            -lpoppler-qt5 \
            -lz
    }
    win32 {
	INCLUDEPATH  += ./include_win32
	LIBS += ./zlib1.dll \
	    ./libpoppler-qt5.dll \
    }
  }
}
!isEmpty(NO_POPPLER_PREVIEW) {
    DEFINES += NO_POPPLER_PREVIEW
    message("Internal pdf previewer disabled as you wish.")
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

# add SVN revision (deprecated)
exists(./.svn/entries)|exists(./.svn/wc.db){
  win32: {
    QMAKE_PRE_LINK += \"$${PWD}/svn_revision.bat\" $${QMAKE_CXX} \"$${OUT_PWD}\"
    LIBS += svn_revision.o
  } else: {
    svn_revision.target = svn_revision.cpp
    exists(./.svn/wc.db){
      svn_revision.depends = .svn/entries .svn/wc.db  # storage of information changed from entries to wc.db in SVN 1.7, entries is kept for compatibility with earlier versions
    }else{
      svn_revision.depends = .svn/entries
    }
    svn_revision.commands = echo \"const char* TEXSTUDIO_SVN_VERSION = \\\"$(shell svnversion)\\\";\" > $$svn_revision.target
    QMAKE_EXTRA_TARGETS += svn_revision
    !exists(./svn_revision.cpp): message("svn_revision.cpp was not found and will be created. Don't worry about repeated warnings.")
    SOURCES += svn_revision.cpp
  }
} else {
  !exists(./svn_revision.cpp){
    win32: system(echo const char * TEXSTUDIO_SVN_VERSION = 0; > svn_revision.cpp)
    else: system(echo \"const char * TEXSTUDIO_SVN_VERSION = 0;\" > svn_revision.cpp)
  }
  SOURCES += svn_revision.cpp

}

# add mercurial revision
exists(./.hg) {
  win32: {
    message(HG)
    QMAKE_PRE_LINK += \"$${PWD}/hg_revision.bat\" $${QMAKE_CXX} \"$${OUT_PWD}\"
    LIBS += hg_revision.o
  } else {
    # Just as a fall back. TODO: implement this analogous to the svn_revision an linux and mac
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

# moved to the end because it seems to destroy the precompiled header
SOURCES+=synctex_parser_utils.c synctex_parser.c

#QMAKE_CXXFLAGS_DEBUG += -Werror  -Wall -Wextra  -Winit-self -Wmain -Wmissing-include-dirs -Wtrigraphs -Wunused -Wunknown-pragmas  -Wundef  -Wpointer-arith -Wtype-limits -Wwrite-strings -Wclobbered  -Wempty-body -Wsign-compare -Waddress -Wlogical-op   -Winline
QMAKE_CXXFLAGS_DEBUG += -Wall -Wextra  -Winit-self -Wmissing-include-dirs -Wtrigraphs -Wunused -Wunknown-pragmas  -Wundef  -Wpointer-arith  -Wwrite-strings -Wempty-body -Wsign-compare -Waddress   -Winline

!win32: QMAKE_LFLAGS += -rdynamic # option not supported by mingw
else {
  QMAKE_CXXFLAGS += -gstabs -g
  QMAKE_LFLAGS -= -Wl,-s
  QMAKE_LFLAGS_RELEASE -= -Wl,-s
}

