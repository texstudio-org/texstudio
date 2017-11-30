DEFINES += _QCODE_EDIT_BUILD_
DEPENDPATH += $$PWD/lib/ \
    $$PWD/lib/document \
#    $$PWD/lib/language \
    $$PWD/lib/widgets \
    $$PWD/lib/qnfa
INCLUDEPATH += $$PWD/lib/ \
    $$PWD/lib/document \
#    $$PWD/lib/language \
    $$PWD/lib/widgets \
    $$PWD/lib/qnfa
QT *= xml

# Input
HEADERS += $$PWD/lib/qce-config.h \
    $$PWD/lib/qeditor.h \
    $$PWD/lib/qeditorfactory.h \
    $$PWD/lib/qcodeedit.h \
    $$PWD/lib/qpanellayout.h \
    $$PWD/lib/qformatfactory.h \
    $$PWD/lib/qformatscheme.h \
    $$PWD/lib/qlinemarksinfocenter.h \
    $$PWD/lib/qreliablefilewatch.h \
    $$PWD/lib/qeditorinputbinding.h \
    $$PWD/lib/qeditorinputbindinginterface.h \
    $$PWD/lib/qformat.h \
    $$PWD/lib/document/qdocument.h \
    $$PWD/lib/document/qdocument_p.h \
    $$PWD/lib/document/qdocumentcommand.h \
    $$PWD/lib/document/qdocumentcursor.h \
    $$PWD/lib/document/qdocumentline.h \
    $$PWD/lib/document/qdocumentsearch.h \
    $$PWD/lib/qcodecompletionengine.h \
    $$PWD/lib/qlanguagedefinition.h \
    $$PWD/lib/qlanguagefactory.h \
    $$PWD/lib/widgets/qpanel.h \
    $$PWD/lib/widgets/qlinenumberpanel.h \
    $$PWD/lib/widgets/qlinemarkpanel.h \
    $$PWD/lib/widgets/qlinechangepanel.h \
    $$PWD/lib/widgets/qfoldpanel.h \
    $$PWD/lib/widgets/qstatuspanel.h \
    $$PWD/lib/widgets/qsearchreplacepanel.h \
    $$PWD/lib/widgets/qgotolinedialog.h \
    $$PWD/lib/widgets/qgotolinepanel.h \
    $$PWD/lib/widgets/qeditconfig.h \
    $$PWD/lib/widgets/qformatconfig.h \
    $$PWD/lib/widgets/qsimplecolorpicker.h \
    $$PWD/lib/widgets/qcalltip.h
SOURCES += $$PWD/lib/qeditor.cpp \
    $$PWD/lib/qeditorfactory.cpp \
    $$PWD/lib/qcodeedit.cpp \
    $$PWD/lib/qpanellayout.cpp \
    $$PWD/lib/qformatscheme.cpp \
    $$PWD/lib/qlinemarksinfocenter.cpp \
    $$PWD/lib/qreliablefilewatch.cpp \
    $$PWD/lib/qeditorinputbinding.cpp \
    $$PWD/lib/qformat.cpp \
    $$PWD/lib/document/qdocument.cpp \
    $$PWD/lib/document/qdocumentcommand.cpp \
    $$PWD/lib/document/qdocumentcursor.cpp \
    $$PWD/lib/document/qdocumentcursor_p.h \
    $$PWD/lib/document/qdocumentline.cpp \
    $$PWD/lib/document/qdocumentline_p.h \
    $$PWD/lib/document/qdocumentsearch.cpp \
    $$PWD/lib/qcodecompletionengine.cpp \
    $$PWD/lib/qlanguagedefinition.cpp \
    $$PWD/lib/qlanguagefactory.cpp \
    $$PWD/lib/widgets/qpanel.cpp \
    $$PWD/lib/widgets/qlinenumberpanel.cpp \
    $$PWD/lib/widgets/qlinemarkpanel.cpp \
    $$PWD/lib/widgets/qlinechangepanel.cpp \
    $$PWD/lib/widgets/qfoldpanel.cpp \
    $$PWD/lib/widgets/qstatuspanel.cpp \
    $$PWD/lib/widgets/qsearchreplacepanel.cpp \
    $$PWD/lib/widgets/qgotolinedialog.cpp \
    $$PWD/lib/widgets/qgotolinepanel.cpp \
    $$PWD/lib/widgets/qeditconfig.cpp \
    $$PWD/lib/widgets/qformatconfig.cpp \
    $$PWD/lib/widgets/qsimplecolorpicker.cpp \
    $$PWD/lib/widgets/qcalltip.cpp
FORMS += $$PWD/lib/widgets/gotoline.ui \
    $$PWD/lib/widgets/gotolinedialog.ui \
    $$PWD/lib/widgets/editconfig.ui \
    $$PWD/lib/widgets/formatconfig.ui
DEFINES += QNFA_BUILD
HEADERS += $$PWD/lib/qnfa/qnfa.h \
    $$PWD/lib/qnfa/qnfadefinition.h \
    $$PWD/lib/qnfa/light_vector.h \
    $$PWD/lib/qnfa/xml2qnfa.h
SOURCES += $$PWD/lib/qnfa/qnfa.cpp \
    $$PWD/lib/qnfa/qnfadefinition.cpp \
    $$PWD/lib/qnfa/xml2qnfa.cpp
