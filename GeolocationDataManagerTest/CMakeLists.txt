cmake_minimum_required(VERSION 3.5)

project(GeolocationDataManagerTest LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui Test Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Test Sql)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GeolocationDataManagerTest
    IpBasedLocationDataRepository_Should.cpp
    #../GeolocationDataManager/Persistence/DatabaseConnectionFactory.h ../GeolocationDataManager/Persistence/DatabaseConnectionFactory.cpp
    ../GeolocationDataManager/Persistence/IpBasedLocationDataRepository.h ../GeolocationDataManager/Persistence/IpBasedLocationDataRepository.cpp)

add_test(NAME GeolocationDataManagerTest COMMAND GeolocationDataManagerTest)

target_link_libraries(GeolocationDataManagerTest PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Test Qt${QT_VERSION_MAJOR}::Sql)

