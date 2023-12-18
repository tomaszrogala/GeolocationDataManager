cmake_minimum_required(VERSION 3.5)

project(GeolocationDataManagerTest LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui Test Sql Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Test Sql Widgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GeolocationDataManagerTest
    GeolocationDataManagerTestMain.cpp
    InMemoryDatabaseConnectionFactory.h InMemoryDatabaseConnectionFactory.cpp
    IpBasedLocationDataRepository_Should.h IpBasedLocationDataRepository_Should.cpp
    ../GeolocationDataManager/Persistence/IpBasedLocationDataRepository.h ../GeolocationDataManager/Persistence/IpBasedLocationDataRepository.cpp
    UrlBasedLocationDataRepository_Should.h UrlBasedLocationDataRepository_Should.cpp
    ../GeolocationDataManager/Persistence/UrlBasedLocationDataRepository.h ../GeolocationDataManager/Persistence/UrlBasedLocationDataRepository.cpp
    InputValidator_Should.h InputValidator_Should.cpp
    ../GeolocationDataManager/Helpers/InputValidator.h ../GeolocationDataManager/Helpers/InputValidator.cpp)

add_test(NAME GeolocationDataManagerTest COMMAND GeolocationDataManagerTest)

target_link_libraries(GeolocationDataManagerTest PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Test Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Widgets )

