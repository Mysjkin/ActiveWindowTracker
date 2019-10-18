cmake_minimum_required(VERSION 3.1.0)

project(gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)

add_executable(gui
    traywindow.cpp
    dbaccess.cpp
    main.cpp
    systray.qrc
)

target_link_libraries(gui Qt5::Widgets Qt5::Sql)