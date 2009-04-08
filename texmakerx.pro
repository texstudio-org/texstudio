TEMPLATE	=  app
LANGUAGE	= C++
DESTDIR = ./
CONFIG = $$unique(CONFIG)
CONFIG -= debug debug_and_release release
CONFIG	+= qt debug_and_release
QT += network xml
###############################
HEADERS	+= texmaker.h \
	buildmanager.h \
	dsingleapplication.h \
	symbollistwidget.h \
	icondelegate.h \
	latexcompleter.h \
	latexeditorview.h \
	latexlog.h \
	logeditor.h \
	loghighlighter.h \
	metapostlistwidget.h \
	smallUsefulFunctions.h \
	structdialog.h \
	filechooser.h \
	tabbingdialog.h \
	arraydialog.h \
	tabdialog.h \
	letterdialog.h \
	addoptiondialog.h \
	quickdocumentdialog.h \
	usermenudialog.h \
	usertooldialog.h \
	refdialog.h \
	configmanager.h \
	configdialog.h \
	aboutdialog.h \
	webpublishdialog.h \
	spellerdialog.h \
	spellerutility.h \
	pstrickslistwidget.h \
	textanalysis.h \
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
	hunspell/replist.hxx \
	hunspell/suggestmgr.hxx \
	hunspell/license.myspell \
	hunspell/filemgr.hxx \
	hunspell/hunzip.hxx \
	hunspell/w_char.hxx
SOURCES	+= main.cpp \
	buildmanager.cpp \
	dsingleapplication.cpp \
	texmaker.cpp \
	symbollistwidget.cpp \
	icondelegate.cpp \
	latexcompleter.cpp \
	latexeditorview.cpp \
	latexlog.cpp \
	logeditor.cpp \
	loghighlighter.cpp \
	metapostlistwidget.cpp \
	smallUsefulFunctions.cpp \
	structdialog.cpp \
	filechooser.cpp \
	tabbingdialog.cpp \
	arraydialog.cpp \
	tabdialog.cpp \
	letterdialog.cpp \
	addoptiondialog.cpp \
	quickdocumentdialog.cpp \
	usermenudialog.cpp \
	usertooldialog.cpp \
	refdialog.cpp \
	configmanager.cpp \
	configdialog.cpp \
	aboutdialog.cpp \
	webpublishdialog.cpp \
	spellerdialog.cpp \
	spellerutility.cpp \
	pstrickslistwidget.cpp \
  textanalysis.cpp \
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
	hunspell/hunzip.cxx
RESOURCES += texmaker.qrc
FORMS   += structdialog.ui \
	filechooser.ui \
	tabbingdialog.ui \
	arraydialog.ui \
	tabdialog.ui \
	letterdialog.ui \
	addoptiondialog.ui \
	quickdocumentdialog.ui \
    usermenudialog.ui \
	usertooldialog.ui \
	refdialog.ui \
	aboutdialog.ui \
	webpublishdialog.ui \
	configdialog.ui \
	spellerdialog.ui \
  textanalysis.ui
TRANSLATIONS += texmakerx_fr.ts  texmakerx_de.ts


################################
unix:!macx {
UI_DIR = .ui
MOC_DIR = .moc
OBJECTS_DIR = .obj
isEmpty( PREFIX ) {
    PREFIX=/usr
}
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
	utilities/texmaker_fr.qm \
	utilities/texmaker_de.qm \
	utilities/qt_fr.qm \
	utilities/qt_de.qm \
	utilities/usermanual_en.html \
	utilities/usermanual_fr.html \
	utilities/en_GB.aff \
	utilities/en_GB.dic \
	utilities/fr_FR.aff \
	utilities/fr_FR.dic \
	utilities/AUTHORS \
	utilities/COPYING \
	utilities/CHANGELOG.txt \
	utilities/texmaker16x16.png \
	utilities/texmaker22x22.png \
	utilities/texmaker32x32.png \
	utilities/texmaker48x48.png \
	utilities/texmaker64x64.png \
	utilities/texmaker128x128.png \
	utilities/texmaker.desktop \
	utilities/texmaker.svg 
INSTALLS += utilities
}
################################
win32 {
INCLUDEPATH += C:\MinGW\include
RC_FILE = win.rc
}
###############################
macx {
UI_DIR = .ui
MOC_DIR = .moc
OBJECTS_DIR = .obj
##universal tiger
CONFIG += link_prl x86 ppc
QMAKE_MAC_SDK=/Developer/SDKs/MacOSX10.4u.sdk
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
	utilities/texmaker_fr.qm \
	utilities/texmaker_de.qm \
	utilities/qt_fr.qm \
	utilities/qt_de.qm \
	utilities/usermanual_en.html \
	utilities/usermanual_fr.html \
	utilities/en_GB.aff \
	utilities/en_GB.dic \
	utilities/fr_FR.aff \
	utilities/fr_FR.dic \
	utilities/AUTHORS \
	utilities/COPYING \
	utilities/CHANGELOG.txt
QMAKE_BUNDLE_DATA += utilities
INSTALLS += utilities
ICON = texmaker.icns
QMAKE_INFO_PLIST =Info.plist
}

HEADERS	+= x11fontdialog.h
SOURCES	+= x11fontdialog.cpp
FORMS += x11fontdialog.ui

###########QCODEEDIT###############

DEFINES += _QCODE_EDIT_BUILD_

DEPENDPATH += qcodeedit/lib/ qcodeedit/lib/document qcodeedit/lib/language qcodeedit/lib/widgets qcodeedit/lib/qnfa
INCLUDEPATH += qcodeedit/lib/ qcodeedit/lib/document qcodeedit/lib/language qcodeedit/lib/widgets qcodeedit/lib/qnfa

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
	qcodeedit/lib/document/qdocumentline.cpp \
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
	qcodeedit/lib/widgets/qeditconfig.cpp \
	qcodeedit/lib/widgets/qformatconfig.cpp \
	qcodeedit/lib/widgets/qsimplecolorpicker.cpp \
	qcodeedit/lib/widgets/qcalltip.cpp

FORMS += qcodeedit/lib/widgets/searchreplace.ui \
	qcodeedit/lib/widgets/gotoline.ui \
	qcodeedit/lib/widgets/editconfig.ui \
	qcodeedit/lib/widgets/formatconfig.ui


DEFINES += QNFA_BUILD

HEADERS += qcodeedit/lib/qnfa/qnfa.h \
	qcodeedit/lib/qnfa/qnfadefinition.h \
	qcodeedit/lib/qnfa/light_vector.h

SOURCES += qcodeedit/lib/qnfa/qnfa.cpp \
	qcodeedit/lib/qnfa/qnfadefinition.cpp \
	qcodeedit/lib/qnfa/xml2qnfa.cpp





CONFIG(debug, debug|release) {
  TARGET	 = texmakerxd
} else {
  TARGET	 = texmakerx
}
 
