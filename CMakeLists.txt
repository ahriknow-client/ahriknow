cmake_minimum_required(VERSION 3.17)

project(ahriknow VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(plugin)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Svg LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Svg LinguistTools)

find_library(MODULE module PATHS ${CMAKE_SOURCE_DIR}/plugin/module/lib)

set(TS_FILES ahriknow_en_US.ts)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${CMAKE_SOURCE_DIR}/plugin/module/inc)

set(PROJECT_SOURCES
        main.cpp

        plugin/inc/ipluginmodule.h
        plugin/inc/ipluginfunction.h
        plugin/inc/iplugintheme.h

        plugin/module/inc/activitybutton.h
        plugin/module/inc/sidewidget.h
        plugin/module/inc/editwidget.h

        inc/ahriknowwindow.h
        inc/generate.h
        inc/layout.h
        inc/wrapperwidget.h
        inc/setting.h
        inc/pluginmanager.h

        src/ahriknowwindow.cpp
        src/generate.cpp
        src/layout.cpp
        src/wrapperwidget.cpp
        src/setting.cpp
        src/pluginmanager.cpp

        ${TS_FILES}
)

qt5_add_resources(PROJECT_SOURCES ahriknow.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ahriknow
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ahriknow APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(ahriknow SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ahriknow
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(ahriknow PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Svg
    ${MODULE}
)

set_target_properties(ahriknow PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER ahriknow.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ahriknow
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ahriknow)
endif()
