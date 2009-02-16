DEFINES += _QCODE_EDIT_BUILD_

CONFIG *= qnfa console

QT *= xml

# Input

HEADERS += qce-config.h \
	qeditor.h \
	qeditorfactory.h \
	qcodeedit.h \
	qpanellayout.h \
	qformatfactory.h \
	qformatscheme.h \
	qlinemarksinfocenter.h \
	qreliablefilewatch.h \
	document/qdocument.h \
	document/qdocument_p.h \
	document/qdocumentcommand.h \
	document/qdocumentcursor.h \
	document/qdocumentline.h \
	document/qdocumentsearch.h \
	qcodecompletionengine.h \
	qlanguagedefinition.h \
	qlanguagefactory.h \
	widgets/qpanel.h \
	widgets/qlinenumberpanel.h \
	widgets/qlinemarkpanel.h \
	widgets/qlinechangepanel.h \
	widgets/qfoldpanel.h \
	widgets/qstatuspanel.h \
	widgets/qsearchreplacepanel.h \
	widgets/qgotolinedialog.h \
	widgets/qeditconfig.h \
	widgets/qcalltip.h

SOURCES += qeditor.cpp \
	qeditorfactory.cpp \
	qcodeedit.cpp \
	qpanellayout.cpp \
	qformatscheme.cpp \
	qlinemarksinfocenter.cpp \
	qreliablefilewatch.cpp \
	document/qdocument.cpp \
	document/qdocumentcommand.cpp \
	document/qdocumentcursor.cpp \
	document/qdocumentline.cpp \
	document/qdocumentsearch.cpp \
	qcodecompletionengine.cpp \
	qlanguagedefinition.cpp \
	qlanguagefactory.cpp \
	widgets/qpanel.cpp \
	widgets/qlinenumberpanel.cpp \
	widgets/qlinemarkpanel.cpp \
	widgets/qlinechangepanel.cpp \
	widgets/qfoldpanel.cpp \
	widgets/qstatuspanel.cpp \
	widgets/qsearchreplacepanel.cpp \
	widgets/qgotolinedialog.cpp \
	widgets/qeditconfig.cpp \
	widgets/qcalltip.cpp

FORMS += widgets/searchreplace.ui \
	widgets/gotoline.ui \
	widgets/editconfig.ui

qnfa {
	DEFINES += QNFA_BUILD

	HEADERS += qnfa/qnfa.h \
		qnfa/qnfadefinition.h \
		qnfa/light_vector.h

	SOURCES += qnfa/qnfa.cpp \
		qnfa/qnfadefinition.cpp \
		qnfa/xml2qnfa.cpp
}

