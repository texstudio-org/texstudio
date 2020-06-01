isEmpty(BUILD_ADWAITA) {}
else {
INCLUDEPATH += $$PWD/style
INCLUDEPATH += $$PWD/style/animations
INCLUDEPATH += $$PWD/style/debug
DEPENDPATH += $$PWD

qt += dbus

HEADERS += \
    $$PWD/style/adwaitaaddeventfilter.h \
    $$PWD/style/adwaitadebug.h \
    $$PWD/style/adwaita.h \
    $$PWD/style/adwaitahelper.h \
    $$PWD/style/adwaitamnemonics.h \
    $$PWD/style/adwaitasplitterproxy.h \
    $$PWD/style/adwaitastyle.h \
    $$PWD/style/adwaitawindowmanager.h \
    $$PWD/style/config-adwaita.h \
    $$PWD/style/kstylekde4compat.h \

SOURCES += \
    $$PWD/style/adwaitaaddeventfilter.cpp \
    $$PWD/style/adwaitahelper.cpp \
    $$PWD/style/adwaitamnemonics.cpp \
    $$PWD/style/adwaitasplitterproxy.cpp \
    $$PWD/style/adwaitastyle.cpp \
    $$PWD/style/adwaitawindowmanager.cpp \
    $$PWD/style/kstylekde4compat.cpp \
    
HEADERS += \
    $$PWD/style/animations/adwaitaanimationdata.h \
    $$PWD/style/animations/adwaitaanimation.h \
    $$PWD/style/animations/adwaitaanimations.h \
    $$PWD/style/animations/adwaitabaseengine.h \
    $$PWD/style/animations/adwaitabusyindicatordata.h \
    $$PWD/style/animations/adwaitabusyindicatorengine.h \
    $$PWD/style/animations/adwaitadatamap.h \
    $$PWD/style/animations/adwaitadialdata.h \
    $$PWD/style/animations/adwaitadialengine.h \
    $$PWD/style/animations/adwaitaenabledata.h \
    $$PWD/style/animations/adwaitagenericdata.h \
    $$PWD/style/animations/adwaitaheaderviewdata.h \
    $$PWD/style/animations/adwaitaheaderviewengine.h \
    $$PWD/style/animations/adwaitawidgetstateengine.h \
    $$PWD/style/animations/adwaitascrollbardata.h \
    $$PWD/style/animations/adwaitascrollbarengine.h \
    $$PWD/style/animations/adwaitaspinboxdata.h \
    $$PWD/style/animations/adwaitaspinboxengine.h \
    $$PWD/style/animations/adwaitastackedwidgetdata.h \
    $$PWD/style/animations/adwaitastackedwidgetengine.h \
    $$PWD/style/animations/adwaitatabbardata.h \
    $$PWD/style/animations/adwaitatabbarengine.h \
    $$PWD/style/animations/adwaitatoolboxengine.h \
    $$PWD/style/animations/adwaitatransitiondata.h \
    $$PWD/style/animations/adwaitatransitionwidget.h \
    $$PWD/style/animations/adwaitawidgetstatedata.h \
    $$PWD/style/debug/adwaitawidgetexplorer.h

SOURCES += \
    $$PWD/style/animations/adwaitaanimation.cpp \
    $$PWD/style/animations/adwaitaanimationdata.cpp \
    $$PWD/style/animations/adwaitaanimations.cpp \
    $$PWD/style/animations/adwaitabaseengine.cpp \
    $$PWD/style/animations/adwaitabusyindicatordata.cpp \
    $$PWD/style/animations/adwaitabusyindicatorengine.cpp \
    $$PWD/style/animations/adwaitadialdata.cpp \
    $$PWD/style/animations/adwaitadialengine.cpp \
    $$PWD/style/animations/adwaitaenabledata.cpp \
    $$PWD/style/animations/adwaitagenericdata.cpp \
    $$PWD/style/animations/adwaitaheaderviewdata.cpp \
    $$PWD/style/animations/adwaitaheaderviewengine.cpp \
    $$PWD/style/animations/adwaitascrollbardata.cpp \
    $$PWD/style/animations/adwaitascrollbarengine.cpp \
    $$PWD/style/animations/adwaitaspinboxdata.cpp \
    $$PWD/style/animations/adwaitaspinboxengine.cpp \
    $$PWD/style/animations/adwaitastackedwidgetdata.cpp \
    $$PWD/style/animations/adwaitastackedwidgetengine.cpp \
    $$PWD/style/animations/adwaitatabbardata.cpp \
    $$PWD/style/animations/adwaitatabbarengine.cpp \
    $$PWD/style/animations/adwaitatoolboxengine.cpp \
    $$PWD/style/animations/adwaitatransitiondata.cpp \
    $$PWD/style/animations/adwaitatransitionwidget.cpp \
    $$PWD/style/animations/adwaitawidgetstatedata.cpp \
    $$PWD/style/animations/adwaitawidgetstateengine.cpp \
    $$PWD/style/debug/adwaitawidgetexplorer.cpp



    DEFINES += ADWAITA
    message("integrate adwaita style")
    QT += dbus
}
