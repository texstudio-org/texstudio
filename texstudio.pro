TEMPLATE = app
LANGUAGE = C++
DESTDIR = ./
CONFIG += qt precompile_header uitools
exists(texmakerx_my.pri):include(texmakerx_my.pri)
QT += network \
    xml \
    script  
!isEmpty(PHONON){
    QT += phonon
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
    hunspell/affentry.hxx \
    hunspell/affixmgr.hxx \
    hunspell/atypes.hxx \
    hunspell/baseaffix.hxx \
    hunspell/csutil.hxx \
    hunspell/dictmgr.hxx \
    hunspell/hashmgr.hxx \
    hunspell/htypes.hxx \
    hunspell/hunspell.hxx \
    hunspell/hunspell.h \
    hunspell/langnum.hxx \
    hunspell/license.hunspell \
    hunspell/phonet.hxx \
    hunspell/suggestmgr.hxx \
    hunspell/license.myspell \
    hunspell/filemgr.hxx \
    hunspell/hunzip.hxx \
    hunspell/w_char.hxx \
    qcodeedit/lib/qeditorinputbinding.h \
    qcodeedit/lib/qeditorinputbindinginterface.h \
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
    hunspell/replist.hxx \
    scriptengine.h \
    insertgraphics.h \
    txstabwidget.h \
    configmanagerinterface.h \
    qcodeedit/lib/qformat.h \
    modifiedQObject.h \
    mostQtHeaders.h \
    qcodeedit/lib/qnfa/xml2qnfa.h \
    tablemanipulation.h \
    syntaxcheck.h \
    tests/latexcompleter_t.h \
    userquickdialog.h \
    PDFDocument.h \
    PDFDocks.h \
    synctex_parser_utils.h \
    synctex_parser.h \
    tests/qdocumentline_t.h \
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
    dblclickmenubar.h
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
    hunspell/affentry.cxx \
    hunspell/affixmgr.cxx \
    hunspell/csutil.cxx \
    hunspell/dictmgr.cxx \
    hunspell/hashmgr.cxx \
    hunspell/hunspell.cxx \
    hunspell/phonet.cxx \
    hunspell/replist.cxx \
    hunspell/suggestmgr.cxx \
    hunspell/utf_info.cxx \
    hunspell/filemgr.cxx \
    hunspell/hunzip.cxx \
    encodingdialog.cpp \
    qcodeedit/lib/qeditorinputbinding.cpp \
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
    userquickdialog.cpp \
    PDFDocument.cpp \
    PDFDocks.cpp \
    tests/qdocumentline_t.cpp \
    latexstyleparser.cpp \
    pdfrenderengine.cpp \
    pdfrendermanager.cpp \
    qcodeedit/lib/qformat.cpp \
    scriptobject.cpp \
    directoryreader.cpp \
    diff/diff_match_patch.cpp \
    diffoperations.cpp \
    grammarcheck.cpp \
    bibtexreader.cpp \
    cleandialog.cpp \
    qmetautils.cpp \
    updatechecker.cpp \
    dblclickmenubar.cpp
RESOURCES += texstudio.qrc \
    symbols.qrc
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
    cleandialog.ui
TRANSLATIONS += texstudio_fr.ts \
    texstudio_de.ts \
    texstudio_it.ts \
    texstudio_cs.ts \
    texstudio_hu.ts \
    texstudio_pt_BR.ts \
    texstudio_uk.ts

# ###############################
win32:RC_FILE = win.rc

# ##############################
macx { 
    # make sure that the documentation is right
    config += unix
    
    # #universal tiger
    CONFIG += link_prl \
        x86
    
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
        utilities/template.png \
        utilities/thesaurus.png \
        utilities/latexhelp.html \
        utilities/wizard_figure.png \
	texstudio_fr.qm \
	texstudio_de.qm \
	texstudio_it.qm \
	texstudio_cs.qm \
	texstudio_hu.qm \
	texstudio_pt_BR.qm \
        qt_fr.qm \
        qt_de.qm \
        qt_hu.qm \
        qt_cs.qm \
        templates/template_Article.tex \
        templates/template_Beamer.tex \
        templates/template_Book.tex \
        templates/template_HA-prosper.tex \
        templates/template_Letter.tex \
        templates/template_Prosper.tex \
        templates/template_Report.tex \
        templates/template_Scrartcl.tex \
        templates/template_Scrbook.tex \
        templates/template_Scrlttr2.tex \
        templates/template_Scrreprt.tex \
        utilities/usermanual_en.html \
        utilities/usermanual_fr.html \
        utilities/en_GB.aff \
        utilities/en_GB.dic \
        utilities/en_US.aff \
        utilities/en_US.dic \
        utilities/fr_FR.aff \
        utilities/fr_FR.dic \
        utilities/de_DE.aff \
        utilities/de_DE.dic \
        utilities/de.stopWords \
        utilities/en.stopWords \
        utilities/fr.stopWords \
        utilities/th_en_US_v2.dat \
        utilities/th_fr_FR_v2.dat \
        utilities/th_de_DE_v2.dat \
        utilities/AUTHORS \
        utilities/COPYING \
        utilities/CHANGELOG.txt
    INSTALLS += target \
        utilities
}

# ##########QCODEEDIT###############
DEFINES += _QCODE_EDIT_BUILD_
DEPENDPATH += qcodeedit/lib/ \
    qcodeedit/lib/document \
    qcodeedit/lib/language \
    qcodeedit/lib/widgets \
    qcodeedit/lib/qnfa
INCLUDEPATH += qcodeedit/lib/ \
    qcodeedit/lib/document \
    qcodeedit/lib/language \
    qcodeedit/lib/widgets \
    qcodeedit/lib/qnfa
QT *= xml

# Input
HEADERS += qcodeedit/lib/qce-config.h \
    qcodeedit/lib/qeditor.h \
    qcodeedit/lib/qeditorfactory.h \
    qcodeedit/lib/qcodeedit.h \
    qcodeedit/lib/qpanellayout.h \
    qcodeedit/lib/qformatfactory.h \
    qcodeedit/lib/qformatscheme.h \
    qcodeedit/lib/qlinemarksinfocenter.h \
    qcodeedit/lib/qreliablefilewatch.h \
    qcodeedit/lib/document/qdocument.h \
    qcodeedit/lib/document/qdocument_p.h \
    qcodeedit/lib/document/qdocumentcommand.h \
    qcodeedit/lib/document/qdocumentcursor.h \
    qcodeedit/lib/document/qdocumentline.h \
    qcodeedit/lib/document/qdocumentsearch.h \
    qcodeedit/lib/qcodecompletionengine.h \
    qcodeedit/lib/qlanguagedefinition.h \
    qcodeedit/lib/qlanguagefactory.h \
    qcodeedit/lib/widgets/qpanel.h \
    qcodeedit/lib/widgets/qlinenumberpanel.h \
    qcodeedit/lib/widgets/qlinemarkpanel.h \
    qcodeedit/lib/widgets/qlinechangepanel.h \
    qcodeedit/lib/widgets/qfoldpanel.h \
    qcodeedit/lib/widgets/qstatuspanel.h \
    qcodeedit/lib/widgets/qsearchreplacepanel.h \
    qcodeedit/lib/widgets/qgotolinedialog.h \
    qcodeedit/lib/widgets/qgotolinepanel.h \
    qcodeedit/lib/widgets/qeditconfig.h \
    qcodeedit/lib/widgets/qformatconfig.h \
    qcodeedit/lib/widgets/qsimplecolorpicker.h \
    qcodeedit/lib/widgets/qcalltip.h
SOURCES += qcodeedit/lib/qeditor.cpp \
    qcodeedit/lib/qeditorfactory.cpp \
    qcodeedit/lib/qcodeedit.cpp \
    qcodeedit/lib/qpanellayout.cpp \
    qcodeedit/lib/qformatscheme.cpp \
    qcodeedit/lib/qlinemarksinfocenter.cpp \
    qcodeedit/lib/qreliablefilewatch.cpp \
    qcodeedit/lib/document/qdocument.cpp \
    qcodeedit/lib/document/qdocumentcommand.cpp \
    qcodeedit/lib/document/qdocumentcursor.cpp \
    qcodeedit/lib/document/qdocumentcursor_p.h \
    qcodeedit/lib/document/qdocumentline.cpp \
    qcodeedit/lib/document/qdocumentline_p.h \
    qcodeedit/lib/document/qdocumentsearch.cpp \
    qcodeedit/lib/qcodecompletionengine.cpp \
    qcodeedit/lib/qlanguagedefinition.cpp \
    qcodeedit/lib/qlanguagefactory.cpp \
    qcodeedit/lib/widgets/qpanel.cpp \
    qcodeedit/lib/widgets/qlinenumberpanel.cpp \
    qcodeedit/lib/widgets/qlinemarkpanel.cpp \
    qcodeedit/lib/widgets/qlinechangepanel.cpp \
    qcodeedit/lib/widgets/qfoldpanel.cpp \
    qcodeedit/lib/widgets/qstatuspanel.cpp \
    qcodeedit/lib/widgets/qsearchreplacepanel.cpp \
    qcodeedit/lib/widgets/qgotolinedialog.cpp \
    qcodeedit/lib/widgets/qgotolinepanel.cpp \
    qcodeedit/lib/widgets/qeditconfig.cpp \
    qcodeedit/lib/widgets/qformatconfig.cpp \
    qcodeedit/lib/widgets/qsimplecolorpicker.cpp \
    qcodeedit/lib/widgets/qcalltip.cpp
FORMS += qcodeedit/lib/widgets/gotoline.ui \
    qcodeedit/lib/widgets/gotolinedialog.ui \
    qcodeedit/lib/widgets/editconfig.ui \
    qcodeedit/lib/widgets/formatconfig.ui
DEFINES += QNFA_BUILD
HEADERS += qcodeedit/lib/qnfa/qnfa.h \
    qcodeedit/lib/qnfa/qnfadefinition.h \
    qcodeedit/lib/qnfa/light_vector.h \
    qcodeedit/lib/qnfa/xml2qnfa.h
SOURCES += qcodeedit/lib/qnfa/qnfa.cpp \
    qcodeedit/lib/qnfa/qnfadefinition.cpp \
    qcodeedit/lib/qnfa/xml2qnfa.cpp

# ###############################



debug{
    message(Creating debug version)
    CONFIG -= release
    
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
        tests/buildManager_t.h \
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
unix:!macx:LIBS += -lQtTest
macx:LIBS += -framework QtTest
}
macx:LIBS += -framework CoreFoundation

# ################################
# Poppler PDF Preview, will only be used if NO_POPPLER_PREVIEW is not set
isEmpty(NO_POPPLER_PREVIEW) { 
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
}
!isEmpty(NO_POPPLER_PREVIEW) { 
    DEFINES += NO_POPPLER_PREVIEW
    message("Internal pdf previewer disabled as you wish.")
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


exists(./.svn/entries){
  win32: {
    QMAKE_PRE_LINK += \"$${PWD}/svn_revision.bat\" $${QMAKE_CXX} \"$${OUT_PWD}\"
    LIBS += svn_revision.o
  } else: {
    svn_revision.target = svn_revision.cpp
    svn_revision.depends = .svn/entries  
    svn_revision.commands = echo \"const char* TEXSTUDIO_SVN_VERSION = \\\"$(shell svnversion)\\\";\" > $$svn_revision.target
    QMAKE_EXTRA_TARGETS += svn_revision
    !exists(./svn_revision.cpp): message("svn_revision.cpp was not found and will be created. Don't worry about repeated warnings.")
    SOURCES += svn_revision.cpp
  }
} else {
  win32: system(echo const char * TEXSTUDIO_SVN_VERSION = 0; > svn_revision.cpp)
  else: system(echo \"const char * TEXSTUDIO_SVN_VERSION = 0;\" > svn_revision.cpp)
  SOURCES += svn_revision.cpp
}

# moved to the end because it seems to destroy the precompiled header
SOURCES+=synctex_parser_utils.c synctex_parser.c 


#QMAKE_CXXFLAGS_DEBUG += -Werror  -Wall -Wextra  -Winit-self -Wmain -Wmissing-include-dirs -Wtrigraphs -Wunused -Wunknown-pragmas  -Wundef  -Wpointer-arith -Wtype-limits -Wwrite-strings -Wclobbered  -Wempty-body -Wsign-compare -Waddress -Wlogical-op   -Winline
QMAKE_CXXFLAGS_DEBUG += -Wall -Wextra  -Winit-self -Wmissing-include-dirs -Wtrigraphs -Wunused -Wunknown-pragmas  -Wundef  -Wpointer-arith  -Wwrite-strings -Wempty-body -Wsign-compare -Waddress   -Winline


