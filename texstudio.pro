cd#########################################################################################
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

####################
# Start of main code
####################
TEMPLATE = app
LANGUAGE = C++
DESTDIR = ./
DISTFILES = texstudio.astylerc \
    pdf.js/build/pdf.js \
    pdf.js/build/pdf.js.map \
    pdf.js/build/pdf.worker.js \
    pdf.js/build/pdf.worker.js.map \
    pdf.js/web/cmaps/78-EUC-H.bcmap \
    pdf.js/web/cmaps/78-EUC-V.bcmap \
    pdf.js/web/cmaps/78-H.bcmap \
    pdf.js/web/cmaps/78-RKSJ-H.bcmap \
    pdf.js/web/cmaps/78-RKSJ-V.bcmap \
    pdf.js/web/cmaps/78-V.bcmap \
    pdf.js/web/cmaps/78ms-RKSJ-H.bcmap \
    pdf.js/web/cmaps/78ms-RKSJ-V.bcmap \
    pdf.js/web/cmaps/83pv-RKSJ-H.bcmap \
    pdf.js/web/cmaps/90ms-RKSJ-H.bcmap \
    pdf.js/web/cmaps/90ms-RKSJ-V.bcmap \
    pdf.js/web/cmaps/90msp-RKSJ-H.bcmap \
    pdf.js/web/cmaps/90msp-RKSJ-V.bcmap \
    pdf.js/web/cmaps/90pv-RKSJ-H.bcmap \
    pdf.js/web/cmaps/90pv-RKSJ-V.bcmap \
    pdf.js/web/cmaps/Add-H.bcmap \
    pdf.js/web/cmaps/Add-RKSJ-H.bcmap \
    pdf.js/web/cmaps/Add-RKSJ-V.bcmap \
    pdf.js/web/cmaps/Add-V.bcmap \
    pdf.js/web/cmaps/Adobe-CNS1-0.bcmap \
    pdf.js/web/cmaps/Adobe-CNS1-1.bcmap \
    pdf.js/web/cmaps/Adobe-CNS1-2.bcmap \
    pdf.js/web/cmaps/Adobe-CNS1-3.bcmap \
    pdf.js/web/cmaps/Adobe-CNS1-4.bcmap \
    pdf.js/web/cmaps/Adobe-CNS1-5.bcmap \
    pdf.js/web/cmaps/Adobe-CNS1-6.bcmap \
    pdf.js/web/cmaps/Adobe-CNS1-UCS2.bcmap \
    pdf.js/web/cmaps/Adobe-GB1-0.bcmap \
    pdf.js/web/cmaps/Adobe-GB1-1.bcmap \
    pdf.js/web/cmaps/Adobe-GB1-2.bcmap \
    pdf.js/web/cmaps/Adobe-GB1-3.bcmap \
    pdf.js/web/cmaps/Adobe-GB1-4.bcmap \
    pdf.js/web/cmaps/Adobe-GB1-5.bcmap \
    pdf.js/web/cmaps/Adobe-GB1-UCS2.bcmap \
    pdf.js/web/cmaps/Adobe-Japan1-0.bcmap \
    pdf.js/web/cmaps/Adobe-Japan1-1.bcmap \
    pdf.js/web/cmaps/Adobe-Japan1-2.bcmap \
    pdf.js/web/cmaps/Adobe-Japan1-3.bcmap \
    pdf.js/web/cmaps/Adobe-Japan1-4.bcmap \
    pdf.js/web/cmaps/Adobe-Japan1-5.bcmap \
    pdf.js/web/cmaps/Adobe-Japan1-6.bcmap \
    pdf.js/web/cmaps/Adobe-Japan1-UCS2.bcmap \
    pdf.js/web/cmaps/Adobe-Korea1-0.bcmap \
    pdf.js/web/cmaps/Adobe-Korea1-1.bcmap \
    pdf.js/web/cmaps/Adobe-Korea1-2.bcmap \
    pdf.js/web/cmaps/Adobe-Korea1-UCS2.bcmap \
    pdf.js/web/cmaps/B5-H.bcmap \
    pdf.js/web/cmaps/B5-V.bcmap \
    pdf.js/web/cmaps/B5pc-H.bcmap \
    pdf.js/web/cmaps/B5pc-V.bcmap \
    pdf.js/web/cmaps/CNS-EUC-H.bcmap \
    pdf.js/web/cmaps/CNS-EUC-V.bcmap \
    pdf.js/web/cmaps/CNS1-H.bcmap \
    pdf.js/web/cmaps/CNS1-V.bcmap \
    pdf.js/web/cmaps/CNS2-H.bcmap \
    pdf.js/web/cmaps/CNS2-V.bcmap \
    pdf.js/web/cmaps/ETHK-B5-H.bcmap \
    pdf.js/web/cmaps/ETHK-B5-V.bcmap \
    pdf.js/web/cmaps/ETen-B5-H.bcmap \
    pdf.js/web/cmaps/ETen-B5-V.bcmap \
    pdf.js/web/cmaps/ETenms-B5-H.bcmap \
    pdf.js/web/cmaps/ETenms-B5-V.bcmap \
    pdf.js/web/cmaps/EUC-H.bcmap \
    pdf.js/web/cmaps/EUC-V.bcmap \
    pdf.js/web/cmaps/Ext-H.bcmap \
    pdf.js/web/cmaps/Ext-RKSJ-H.bcmap \
    pdf.js/web/cmaps/Ext-RKSJ-V.bcmap \
    pdf.js/web/cmaps/Ext-V.bcmap \
    pdf.js/web/cmaps/GB-EUC-H.bcmap \
    pdf.js/web/cmaps/GB-EUC-V.bcmap \
    pdf.js/web/cmaps/GB-H.bcmap \
    pdf.js/web/cmaps/GB-V.bcmap \
    pdf.js/web/cmaps/GBK-EUC-H.bcmap \
    pdf.js/web/cmaps/GBK-EUC-V.bcmap \
    pdf.js/web/cmaps/GBK2K-H.bcmap \
    pdf.js/web/cmaps/GBK2K-V.bcmap \
    pdf.js/web/cmaps/GBKp-EUC-H.bcmap \
    pdf.js/web/cmaps/GBKp-EUC-V.bcmap \
    pdf.js/web/cmaps/GBT-EUC-H.bcmap \
    pdf.js/web/cmaps/GBT-EUC-V.bcmap \
    pdf.js/web/cmaps/GBT-H.bcmap \
    pdf.js/web/cmaps/GBT-V.bcmap \
    pdf.js/web/cmaps/GBTpc-EUC-H.bcmap \
    pdf.js/web/cmaps/GBTpc-EUC-V.bcmap \
    pdf.js/web/cmaps/GBpc-EUC-H.bcmap \
    pdf.js/web/cmaps/GBpc-EUC-V.bcmap \
    pdf.js/web/cmaps/H.bcmap \
    pdf.js/web/cmaps/HKdla-B5-H.bcmap \
    pdf.js/web/cmaps/HKdla-B5-V.bcmap \
    pdf.js/web/cmaps/HKdlb-B5-H.bcmap \
    pdf.js/web/cmaps/HKdlb-B5-V.bcmap \
    pdf.js/web/cmaps/HKgccs-B5-H.bcmap \
    pdf.js/web/cmaps/HKgccs-B5-V.bcmap \
    pdf.js/web/cmaps/HKm314-B5-H.bcmap \
    pdf.js/web/cmaps/HKm314-B5-V.bcmap \
    pdf.js/web/cmaps/HKm471-B5-H.bcmap \
    pdf.js/web/cmaps/HKm471-B5-V.bcmap \
    pdf.js/web/cmaps/HKscs-B5-H.bcmap \
    pdf.js/web/cmaps/HKscs-B5-V.bcmap \
    pdf.js/web/cmaps/Hankaku.bcmap \
    pdf.js/web/cmaps/Hiragana.bcmap \
    pdf.js/web/cmaps/KSC-EUC-H.bcmap \
    pdf.js/web/cmaps/KSC-EUC-V.bcmap \
    pdf.js/web/cmaps/KSC-H.bcmap \
    pdf.js/web/cmaps/KSC-Johab-H.bcmap \
    pdf.js/web/cmaps/KSC-Johab-V.bcmap \
    pdf.js/web/cmaps/KSC-V.bcmap \
    pdf.js/web/cmaps/KSCms-UHC-H.bcmap \
    pdf.js/web/cmaps/KSCms-UHC-HW-H.bcmap \
    pdf.js/web/cmaps/KSCms-UHC-HW-V.bcmap \
    pdf.js/web/cmaps/KSCms-UHC-V.bcmap \
    pdf.js/web/cmaps/KSCpc-EUC-H.bcmap \
    pdf.js/web/cmaps/KSCpc-EUC-V.bcmap \
    pdf.js/web/cmaps/Katakana.bcmap \
    pdf.js/web/cmaps/LICENSE \
    pdf.js/web/cmaps/NWP-H.bcmap \
    pdf.js/web/cmaps/NWP-V.bcmap \
    pdf.js/web/cmaps/RKSJ-H.bcmap \
    pdf.js/web/cmaps/RKSJ-V.bcmap \
    pdf.js/web/cmaps/Roman.bcmap \
    pdf.js/web/cmaps/UniCNS-UCS2-H.bcmap \
    pdf.js/web/cmaps/UniCNS-UCS2-V.bcmap \
    pdf.js/web/cmaps/UniCNS-UTF16-H.bcmap \
    pdf.js/web/cmaps/UniCNS-UTF16-V.bcmap \
    pdf.js/web/cmaps/UniCNS-UTF32-H.bcmap \
    pdf.js/web/cmaps/UniCNS-UTF32-V.bcmap \
    pdf.js/web/cmaps/UniCNS-UTF8-H.bcmap \
    pdf.js/web/cmaps/UniCNS-UTF8-V.bcmap \
    pdf.js/web/cmaps/UniGB-UCS2-H.bcmap \
    pdf.js/web/cmaps/UniGB-UCS2-V.bcmap \
    pdf.js/web/cmaps/UniGB-UTF16-H.bcmap \
    pdf.js/web/cmaps/UniGB-UTF16-V.bcmap \
    pdf.js/web/cmaps/UniGB-UTF32-H.bcmap \
    pdf.js/web/cmaps/UniGB-UTF32-V.bcmap \
    pdf.js/web/cmaps/UniGB-UTF8-H.bcmap \
    pdf.js/web/cmaps/UniGB-UTF8-V.bcmap \
    pdf.js/web/cmaps/UniJIS-UCS2-H.bcmap \
    pdf.js/web/cmaps/UniJIS-UCS2-HW-H.bcmap \
    pdf.js/web/cmaps/UniJIS-UCS2-HW-V.bcmap \
    pdf.js/web/cmaps/UniJIS-UCS2-V.bcmap \
    pdf.js/web/cmaps/UniJIS-UTF16-H.bcmap \
    pdf.js/web/cmaps/UniJIS-UTF16-V.bcmap \
    pdf.js/web/cmaps/UniJIS-UTF32-H.bcmap \
    pdf.js/web/cmaps/UniJIS-UTF32-V.bcmap \
    pdf.js/web/cmaps/UniJIS-UTF8-H.bcmap \
    pdf.js/web/cmaps/UniJIS-UTF8-V.bcmap \
    pdf.js/web/cmaps/UniJIS2004-UTF16-H.bcmap \
    pdf.js/web/cmaps/UniJIS2004-UTF16-V.bcmap \
    pdf.js/web/cmaps/UniJIS2004-UTF32-H.bcmap \
    pdf.js/web/cmaps/UniJIS2004-UTF32-V.bcmap \
    pdf.js/web/cmaps/UniJIS2004-UTF8-H.bcmap \
    pdf.js/web/cmaps/UniJIS2004-UTF8-V.bcmap \
    pdf.js/web/cmaps/UniJISPro-UCS2-HW-V.bcmap \
    pdf.js/web/cmaps/UniJISPro-UCS2-V.bcmap \
    pdf.js/web/cmaps/UniJISPro-UTF8-V.bcmap \
    pdf.js/web/cmaps/UniJISX0213-UTF32-H.bcmap \
    pdf.js/web/cmaps/UniJISX0213-UTF32-V.bcmap \
    pdf.js/web/cmaps/UniJISX02132004-UTF32-H.bcmap \
    pdf.js/web/cmaps/UniJISX02132004-UTF32-V.bcmap \
    pdf.js/web/cmaps/UniKS-UCS2-H.bcmap \
    pdf.js/web/cmaps/UniKS-UCS2-V.bcmap \
    pdf.js/web/cmaps/UniKS-UTF16-H.bcmap \
    pdf.js/web/cmaps/UniKS-UTF16-V.bcmap \
    pdf.js/web/cmaps/UniKS-UTF32-H.bcmap \
    pdf.js/web/cmaps/UniKS-UTF32-V.bcmap \
    pdf.js/web/cmaps/UniKS-UTF8-H.bcmap \
    pdf.js/web/cmaps/UniKS-UTF8-V.bcmap \
    pdf.js/web/cmaps/V.bcmap \
    pdf.js/web/cmaps/WP-Symbol.bcmap \
    pdf.js/web/debugger.js \
    pdf.js/web/images/annotation-check.svg \
    pdf.js/web/images/annotation-comment.svg \
    pdf.js/web/images/annotation-help.svg \
    pdf.js/web/images/annotation-insert.svg \
    pdf.js/web/images/annotation-key.svg \
    pdf.js/web/images/annotation-newparagraph.svg \
    pdf.js/web/images/annotation-noicon.svg \
    pdf.js/web/images/annotation-note.svg \
    pdf.js/web/images/annotation-paragraph.svg \
    pdf.js/web/images/findbarButton-next-rtl.png \
    pdf.js/web/images/findbarButton-next-rtl@2x.png \
    pdf.js/web/images/findbarButton-next.png \
    pdf.js/web/images/findbarButton-next@2x.png \
    pdf.js/web/images/findbarButton-previous-rtl.png \
    pdf.js/web/images/findbarButton-previous-rtl@2x.png \
    pdf.js/web/images/findbarButton-previous.png \
    pdf.js/web/images/findbarButton-previous@2x.png \
    pdf.js/web/images/grab.cur \
    pdf.js/web/images/grabbing.cur \
    pdf.js/web/images/loading-icon.gif \
    pdf.js/web/images/loading-small.png \
    pdf.js/web/images/loading-small@2x.png \
    pdf.js/web/images/secondaryToolbarButton-documentProperties.png \
    pdf.js/web/images/secondaryToolbarButton-documentProperties@2x.png \
    pdf.js/web/images/secondaryToolbarButton-firstPage.png \
    pdf.js/web/images/secondaryToolbarButton-firstPage@2x.png \
    pdf.js/web/images/secondaryToolbarButton-handTool.png \
    pdf.js/web/images/secondaryToolbarButton-handTool@2x.png \
    pdf.js/web/images/secondaryToolbarButton-lastPage.png \
    pdf.js/web/images/secondaryToolbarButton-lastPage@2x.png \
    pdf.js/web/images/secondaryToolbarButton-rotateCcw.png \
    pdf.js/web/images/secondaryToolbarButton-rotateCcw@2x.png \
    pdf.js/web/images/secondaryToolbarButton-rotateCw.png \
    pdf.js/web/images/secondaryToolbarButton-rotateCw@2x.png \
    pdf.js/web/images/secondaryToolbarButton-selectTool.png \
    pdf.js/web/images/secondaryToolbarButton-selectTool@2x.png \
    pdf.js/web/images/shadow.png \
    pdf.js/web/images/texture.png \
    pdf.js/web/images/toolbarButton-bookmark.png \
    pdf.js/web/images/toolbarButton-bookmark@2x.png \
    pdf.js/web/images/toolbarButton-download.png \
    pdf.js/web/images/toolbarButton-download@2x.png \
    pdf.js/web/images/toolbarButton-menuArrows.png \
    pdf.js/web/images/toolbarButton-menuArrows@2x.png \
    pdf.js/web/images/toolbarButton-openFile.png \
    pdf.js/web/images/toolbarButton-openFile@2x.png \
    pdf.js/web/images/toolbarButton-pageDown-rtl.png \
    pdf.js/web/images/toolbarButton-pageDown-rtl@2x.png \
    pdf.js/web/images/toolbarButton-pageDown.png \
    pdf.js/web/images/toolbarButton-pageDown@2x.png \
    pdf.js/web/images/toolbarButton-pageUp-rtl.png \
    pdf.js/web/images/toolbarButton-pageUp-rtl@2x.png \
    pdf.js/web/images/toolbarButton-pageUp.png \
    pdf.js/web/images/toolbarButton-pageUp@2x.png \
    pdf.js/web/images/toolbarButton-presentationMode.png \
    pdf.js/web/images/toolbarButton-presentationMode@2x.png \
    pdf.js/web/images/toolbarButton-print.png \
    pdf.js/web/images/toolbarButton-print@2x.png \
    pdf.js/web/images/toolbarButton-search.png \
    pdf.js/web/images/toolbarButton-search@2x.png \
    pdf.js/web/images/toolbarButton-secondaryToolbarToggle-rtl.png \
    pdf.js/web/images/toolbarButton-secondaryToolbarToggle-rtl@2x.png \
    pdf.js/web/images/toolbarButton-secondaryToolbarToggle.png \
    pdf.js/web/images/toolbarButton-secondaryToolbarToggle@2x.png \
    pdf.js/web/images/toolbarButton-sidebarToggle-rtl.png \
    pdf.js/web/images/toolbarButton-sidebarToggle-rtl@2x.png \
    pdf.js/web/images/toolbarButton-sidebarToggle.png \
    pdf.js/web/images/toolbarButton-sidebarToggle@2x.png \
    pdf.js/web/images/toolbarButton-viewAttachments.png \
    pdf.js/web/images/toolbarButton-viewAttachments@2x.png \
    pdf.js/web/images/toolbarButton-viewOutline-rtl.png \
    pdf.js/web/images/toolbarButton-viewOutline-rtl@2x.png \
    pdf.js/web/images/toolbarButton-viewOutline.png \
    pdf.js/web/images/toolbarButton-viewOutline@2x.png \
    pdf.js/web/images/toolbarButton-viewThumbnail.png \
    pdf.js/web/images/toolbarButton-viewThumbnail@2x.png \
    pdf.js/web/images/toolbarButton-zoomIn.png \
    pdf.js/web/images/toolbarButton-zoomIn@2x.png \
    pdf.js/web/images/toolbarButton-zoomOut.png \
    pdf.js/web/images/toolbarButton-zoomOut@2x.png \
    pdf.js/web/images/treeitem-collapsed-rtl.png \
    pdf.js/web/images/treeitem-collapsed-rtl@2x.png \
    pdf.js/web/images/treeitem-collapsed.png \
    pdf.js/web/images/treeitem-collapsed@2x.png \
    pdf.js/web/images/treeitem-expanded.png \
    pdf.js/web/images/treeitem-expanded@2x.png \
    pdf.js/web/locale/fr/viewer.properties \
    pdf.js/web/locale/locale.properties \
    pdf.js/web/viewer.css \
    pdf.js/web/viewer.html \
    pdf.js/web/viewer.js \
    pdf.js/web/viewer.js.map
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
    script \
    printsupport \
    concurrent \
    webenginewidgets

QT += sql
QT += pdf pdfwidgets

QT += \
    widgets \
    uitools

!isEmpty(MXE){
    DEFINES += MXE
}

!isEmpty(PHONON){
    QT += phonon4qt5
    LIBS += -lphonon4qt5
    DEFINES += PHONON
}

isEmpty(INTERNAL_TERMINAL):pkgAtLeastVersion("qtermwidget5", "0.9.0") {
    INTERNAL_TERMINAL=1
    message(Use detected qterminal)
}
!isEmpty(INTERNAL_TERMINAL){
    LIBS += -lqtermwidget5
    DEFINES += INTERNAL_TERMINAL
    message(Use qterminal)
}

!isEmpty(QJS){
    DEFINES += QJS
    QT += qml
    QT -= script
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
isEmpty(USE_SYSTEM_HUNSPELL){
    include(src/hunspell/hunspell.pri)
}else{
    message(System hunspell)
    CONFIG += link_pkgconfig
    PKGCONFIG += hunspell
}

include(src/qcodeedit/qcodeedit.pri)

include(src/latexparser/latexparser.pri)

include(src/DataTeX/datatex.pri)

include(src/symbolpanel/symbolpanel.pri)

isEmpty(USE_SYSTEM_QUAZIP) {
    include(src/quazip/quazip/quazip.pri)
} else {
        message(System quazip5)
        isEmpty(QUAZIP_LIB): QUAZIP_LIB = -lquazip5
        isEmpty(QUAZIP_INCLUDE): QUAZIP_INCLUDE = $${PREFIX}/include/quazip5
        INCLUDEPATH += $${QUAZIP_INCLUDE}
        LIBS += $${QUAZIP_LIB}
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
    message(GIT)
    system(\"$${PWD}/git_revision.bat\" $${QMAKE_CXX} \"$${OUT_PWD}\" \"$${PWD}\")
    SOURCES +=
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
  SOURCES +=
}

!win32-msvc*: {
  QMAKE_CXXFLAGS_DEBUG -= -O -O1 -O2 -O3
  QMAKE_CXXFLAGS_DEBUG += -Wall -Wextra -Wmissing-include-dirs -Wunknown-pragmas -Wundef -Wpointer-arith -Winline -O0
  QMAKE_CXXFLAGS += -std=c++11
  !isEmpty(MXE): QMAKE_CXXFLAGS += -fpermissive
  !win32:!haiku: QMAKE_LFLAGS += -rdynamic # option not supported by mingw and haiku
  else {
    QMAKE_CXXFLAGS += -gstabs -g
    QMAKE_LFLAGS -= -Wl,-s
    isEmpty(STRIP){
        QMAKE_LFLAGS_RELEASE -= -Wl,-s
    }
  }
} else {
  DEFINES += _CRT_SECURE_NO_WARNINGS
}

*-g++:equals(QT_MAJOR_VERSION, 5):lessThan(QT_MINOR_VERSION, 13) {
  QMAKE_CXXFLAGS += -Wno-deprecated-copy
}

FORMS +=

HEADERS +=

SOURCES +=
