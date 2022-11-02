
#configure_file(config-adwaita.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-adwaita.h )

set(Adwaita_SRCS
    animations/adwaitaanimation.cpp
    animations/adwaitaanimations.cpp
    animations/adwaitaanimationdata.cpp
    animations/adwaitabaseengine.cpp
    animations/adwaitabusyindicatordata.cpp
    animations/adwaitabusyindicatorengine.cpp
    animations/adwaitadialdata.cpp
    animations/adwaitadialengine.cpp
    animations/adwaitaenabledata.cpp
    animations/adwaitagenericdata.cpp
    animations/adwaitaheaderviewdata.cpp
    animations/adwaitaheaderviewengine.cpp
    animations/adwaitascrollbardata.cpp
    animations/adwaitascrollbarengine.cpp
    animations/adwaitaspinboxengine.cpp
    animations/adwaitaspinboxdata.cpp
    animations/adwaitastackedwidgetdata.cpp
    animations/adwaitastackedwidgetengine.cpp
    animations/adwaitatabbarengine.cpp
    animations/adwaitatabbardata.cpp
    animations/adwaitatoolboxengine.cpp
    animations/adwaitatransitiondata.cpp
    animations/adwaitatransitionwidget.cpp
    animations/adwaitawidgetstateengine.cpp
    animations/adwaitawidgetstatedata.cpp
    debug/adwaitawidgetexplorer.cpp
    adwaitaaddeventfilter.cpp
    adwaitahelper.cpp
    adwaitamnemonics.cpp
    adwaitasplitterproxy.cpp
    adwaitastyle.cpp
    adwaitastyleplugin.cpp
    adwaitawindowmanager.cpp
)
#add_definitions(-DQT_PLUGIN)

if (MSVC)
    add_definitions(-D_USE_MATH_DEFINES) # Needed for M_PI on MSVC
endif()

include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR} # for adwaita-config.h
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/animations/
    ${CMAKE_CURRENT_SOURCE_DIR}/debug/
)

set(LIBRARY_NAME "adwaita-qt${QT_VERSION_NUMBER}")

add_library(${LIBRARY_NAME} STATIC ${Adwaita_SRCS})
#add_library(quazip STATIC ${QUAZIP_HEADER_FILES} ${QUAZIP_SOURCE_FILES})
target_compile_definitions(${LIBRARY_NAME} PUBLIC -DADWAITA-QT_STATIC
    Qt${QT_VERSION_NUMBER}::Gui
    Qt${QT_VERSION_NUMBER}::Widgets
    Qt${QT_VERSION_NUMBER}::Core
    Qt${QT_VERSION_NUMBER}::DBus
) 


#target_link_libraries(${LIBRARY_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTDBUS_LIBRARY})
#set_target_properties(${LIBRARY_NAME} PROPERTIES
#    LINK_FLAGS "-Wl,--no-undefined"
#    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
#    OUTPUT_NAME "adwaita"
#    PREFIX "")

#install(TARGETS ${LIBRARY_NAME} DESTINATION "${QT_PLUGINS_DIR}/styles")
