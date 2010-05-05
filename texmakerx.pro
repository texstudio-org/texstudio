TEMPLATE = app
LANGUAGE = C++
DESTDIR = ./
CONFIG = $$unique(CONFIG)
CONFIG -= debug \
    debug_and_release \
    release
CONFIG += qt \
    debug_and_release
exists(texmakerx_my.pri):include(texmakerx_my.pri)
QT += network \
    xml \
    script
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
    universalinputdialog.h \
    hunspell/replist.hxx \
	scriptengine.h
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
    universalinputdialog.cpp \
    scriptengine.cpp
RESOURCES += texmaker.qrc
FORMS += structdialog.ui \
    filechooser.ui \
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
    findGlobalDialog.ui
TRANSLATIONS += texmakerx_fr.ts \
    texmakerx_de.ts \
    texmakerx_it.ts \
    texmakerx_cs.ts

# ###############################
unix:!macx { 
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
    isEmpty( PREFIX ):PREFIX = /usr
    DEFINES += PREFIX=\\\"$${PREFIX}\\\"
    target.path = $${PREFIX}/bin
    INSTALLS = target
    utilities.path = $${PREFIX}/share/texmakerx
    utilities.files = utilities/doc1.png \
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
        utilities/latexhelp.html \
        texmakerx_fr.qm \
        texmakerx_de.qm \
        texmakerx_it.qm \
        utilities/qt_fr.qm \
        utilities/qt_de.qm \
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
        utilities/fr_FR.aff \
        utilities/fr_FR.dic \
        utilities/de_DE.aff \
        utilities/de_DE.dic \
        utilities/th_en_US_v2.dat \
        utilities/th_fr_FR_v2.dat \
        utilities/th_de_DE_v2.dat \
        utilities/AUTHORS \
        utilities/COPYING \
        utilities/CHANGELOG.txt \
        utilities/texmaker16x16.png \
        utilities/texmaker22x22.png \
        utilities/texmaker32x32.png \
        utilities/texmaker48x48.png \
        utilities/texmaker64x64.png \
        utilities/texmaker128x128.png \
        utilities/texmaker.svg
    
    applicationmenu.path = $${PREFIX}/share/applications
    applicationmenu.files = utilities/texmakerx.desktop
    INSTALLS += utilities applicationmenu
}

# ###############################
win32 { 
    INCLUDEPATH += C:\MinGW\include
    RC_FILE = win.rc
}

# ##############################
macx { 
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
    
    # #universal tiger
    CONFIG += link_prl \
        x86 \
        ppc
    QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.4u.sdk
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.4
    target.path = /Applications
    INSTALLS = target
    utilities.path = Contents/Resources
    utilities.files = utilities/doc1.png \
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
        utilities/latexhelp.html \
        texmakerx_fr.qm \
        texmakerx_de.qm \
        texmakerx_it.qm \
        utilities/qt_fr.qm \
        utilities/qt_de.qm \
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
        utilities/fr_FR.aff \
        utilities/fr_FR.dic \
        utilities/de_DE.aff \
        utilities/de_DE.dic \
        utilities/th_en_US_v2.dat \
        utilities/th_fr_FR_v2.dat \
        utilities/th_de_DE_v2.dat \
        utilities/AUTHORS \
        utilities/COPYING \
        utilities/CHANGELOG.txt
    QMAKE_BUNDLE_DATA += utilities
    INSTALLS += utilities
    ICON = texmaker.icns
    QMAKE_INFO_PLIST = Info.plist
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
FORMS += qcodeedit/lib/widgets/searchreplace.ui \
    qcodeedit/lib/widgets/gotoline.ui \
    qcodeedit/lib/widgets/gotolinedialog.ui \
    qcodeedit/lib/widgets/editconfig.ui \
    qcodeedit/lib/widgets/formatconfig.ui
DEFINES += QNFA_BUILD
HEADERS += qcodeedit/lib/qnfa/qnfa.h \
    qcodeedit/lib/qnfa/qnfadefinition.h \
    qcodeedit/lib/qnfa/light_vector.h
SOURCES += qcodeedit/lib/qnfa/qnfa.cpp \
    qcodeedit/lib/qnfa/qnfadefinition.cpp \
    qcodeedit/lib/qnfa/xml2qnfa.cpp

# ###############################
# these files should be debug only, but debug-only thing in a qmake file become an
# incredible mess, so they are always compiled (but empty through #define in release mode)
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
    tests/structureview_t.cpp
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
    tests/structureview_t.h
#win32:LIBS += -lQtTest4
win32:LIBS += -lQtTestd4
unix:!macx:LIBS += -lQtTest
macx:LIBS += -framework \
    QtTest

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


svn_revision.target   = svn_revision.h
exists(./.svn/entries){
	win32 {
		svn_revision.commands = echo $${LITERAL_HASH}define SVN_REVISION_NUMBER \"$(shell svnversion)\" > $$svn_revision.target
	}else{
		svn_revision.commands = echo \"$${LITERAL_HASH}define SVN_REVISION_NUMBER \\\"$(shell svnversion)\\\"\" > $$svn_revision.target
	}
    svn_revision.depends  = .svn/entries 
} else {
	win32 {
		svn_revision.commands = echo $${LITERAL_HASH}define SVN_REVISION_NUMBER \"?\" > $$svn_revision.target
	}else{
		svn_revision.commands = echo \"$${LITERAL_HASH}define SVN_REVISION_NUMBER \\\"?\\\"\" > $$svn_revision.target
	}
    svn_revision.depends  = 
}

HEADERS += $$svn_revision.target
QMAKE_EXTRA_TARGETS += svn_revision
