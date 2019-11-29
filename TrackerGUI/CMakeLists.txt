cmake_minimum_required(VERSION 3.1.0)

project(gui)

set ( SOURCES
 main.cpp
 traywindow.cpp
 dbaccess.cpp
)

set ( MOC_HEADERS
 traywindow.h
 dbaccess.h
)


set ( UIS
 traywindow.ui
)

set ( RESOURCES
 systray.qrc
)

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS REQUIRED Core Widgets Sql Charts)

QT5_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT5_WRAP_UI( UI_HEADERS ${UIS} )
QT5_WRAP_CPP( MOC_SRCS ${MOC_HEADERS} )


#add_executable(gui
#    traywindow.cpp
#    dbaccess.cpp
#    main.cpp
#    systray.qrc
#)

add_executable(gui ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )

target_link_libraries(gui Qt5::Widgets Qt5::Sql Qt5::Charts)