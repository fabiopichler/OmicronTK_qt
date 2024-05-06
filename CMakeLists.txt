cmake_minimum_required(VERSION 3.5)

project(OmicronTK_qt LANGUAGES CXX)

set(PROJECT_QT OmicronTK_qt)
set(PROJECT_QT_NETWORK OmicronTK_qt_network)
set(PROJECT_QT_LUA OmicronTK_qt_lua)
set(PROJECT_QT_RUBY OmicronTK_qt_ruby)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/win64/debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/win64)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/win64/debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/win64)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/win64/debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/win64)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib/WebAssembly/debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/lib/WebAssembly)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib/WebAssembly/debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/lib/WebAssembly)
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib/linux64/debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/lib/linux64)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib/linux64/debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/lib/linux64)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/linux64/debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/linux64)

    string(APPEND CMAKE_EXE_LINKER_FLAGS " -Wl,-rpath,\'$ORIGIN\',-z,origin")
    string(APPEND CMAKE_SHARED_LINKER_FLAGS " -Wl,-rpath,\'$ORIGIN\',-z,origin -Wl,--no-undefined -Wl,--as-needed")
endif()

if(WIN32)
    # TEMP
    set(QT6_BASE_PATH /mnt/projetos/Frameworks/qt/qt6-mingw-w64)

    find_package(Qt6 6.1 COMPONENTS Core Gui Widgets Network UiTools Designer REQUIRED PATHS ${QT6_BASE_PATH} NO_DEFAULT_PATH)
else()
    find_package(Qt6 6.1 COMPONENTS Core Gui Widgets Network UiTools Designer REQUIRED)
endif()

include("${CMAKE_SOURCE_DIR}/.env.cmake")

add_definitions(-DQT_DEPRECATED_WARNINGS)

include_directories(include)

add_subdirectory(plugins)
add_subdirectory(src)
