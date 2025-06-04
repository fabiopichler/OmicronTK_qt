
project(${PROJECT_QT_NETWORK} LANGUAGES CXX)

add_definitions(-DOTKQT_BUILD_NETWORK_LIB)

set(SRC_FILES
    ../../include/OmicronTK/qt_network/omicrontk_qt_network_global.hpp
    ../../include/OmicronTK/qt_network/LocalServer.hpp
    ../../include/OmicronTK/qt_network/LocalClient.hpp
    LocalServer.cpp
    LocalClient.cpp
)

if(WIN32)
    #set(SRC_FILES ${SRC_FILES} rc/network.rc)
endif()

add_library(${PROJECT_QT_NETWORK} SHARED ${SRC_FILES})

target_link_libraries(${PROJECT_QT_NETWORK} PRIVATE
    Qt6::Core
    Qt6::Network
    ${PROJECT_QT})
