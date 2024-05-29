
project(${PROJECT_QT_NETWORK} LANGUAGES CXX)

add_definitions(-DOTKQT_BUILD_NETWORK_LIB)

set(SRC_FILES
    src/LocalServer.cpp
    src/LocalSocket.cpp
    ../../include/OmicronTK/qt/network/LocalServer.hpp
    ../../include/OmicronTK/qt/network/LocalSocket.hpp)

if(WIN32)
    #set(SRC_FILES ${SRC_FILES} rc/network.rc)
endif()

add_library(${PROJECT_QT_NETWORK} SHARED ${SRC_FILES})

target_link_libraries(${PROJECT_QT_NETWORK} PRIVATE
    Qt6::Core
    Qt6::Network
    ${PROJECT_QT})
