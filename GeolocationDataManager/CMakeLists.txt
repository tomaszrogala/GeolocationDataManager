cmake_minimum_required(VERSION 3.5)

project(GeolocationDataManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
endif()


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Network Concurrent Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Network Concurrent Core)

file(GLOB PERSISTENCE_SOURCES "Persistence/*.cpp" "Persistence/*/*.cpp")
file(GLOB PERSISTENCE_HEADERS "Persistence/*.h" "Persistence/*/*.h")
file(GLOB HTTPNETWORK_SOURCES "HttpNetwork/*.cpp" "HttpNetwork/*/*.cpp")
file(GLOB HTTPNETWORK_HEADERS "HttpNetwork/*.h" "HttpNetwork/*/*.h")
file(GLOB HELPERS_SOURCES "Helpers/*.cpp" "Helpers/*/*.cpp")
file(GLOB HELPERS_HEADERS "Helpers/*.h" "Helpers/*/*.h")

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${PERSISTENCE_SOURCES}
        ${PERSISTENCE_HEADERS}
        ${HTTPNETWORK_SOURCES}
        ${HTTPNETWORK_HEADERS}
        ${HELPERS_SOURCES}
        ${HELPERS_HEADERS}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GeolocationDataManager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GeolocationDataManager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(GeolocationDataManager SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GeolocationDataManager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GeolocationDataManager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets PRIVATE Qt${QT_VERSION_MAJOR}::Core PRIVATE Qt${QT_VERSION_MAJOR}::Sql PRIVATE Qt${QT_VERSION_MAJOR}::Network PRIVATE Qt${QT_VERSION_MAJOR}::Concurrent)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GeolocationDataManager)
endif()
set_target_properties(GeolocationDataManager PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS GeolocationDataManager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GeolocationDataManager)
endif()
