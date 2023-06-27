cmake_minimum_required(VERSION 3.5)

project(OmicronTK_qt LANGUAGES CXX)

set(PROJECT_QT OmicronTK_qt)
set(PROJECT_QT_NETWORK OmicronTK_qt_network)
set(PROJECT_QT_LUA OmicronTK_qt_lua)
set(PROJECT_QT_RUBY OmicronTK_qt_ruby)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib/linux64/debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/lib/linux64)

find_package(Qt5 5.7 COMPONENTS Core Gui Widgets Network REQUIRED)

include("${CMAKE_SOURCE_DIR}/.env.cmake")

add_definitions(-DQT_DEPRECATED_WARNINGS)

include_directories(include)

add_subdirectory(src)
