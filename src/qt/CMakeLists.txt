
project(${PROJECT_QT} LANGUAGES CXX)

add_definitions(-DOTK_QT_BUILD_LIB)

set(SRC_FILES
    AppInfo.cpp
    ComboBox.cpp
    Dialog.cpp
    DirectoryDialog.cpp
    DropArea.cpp
    Equalizer.cpp
    ErrorWindow.cpp
    Label.cpp
    PopUp.cpp
    Slider.cpp
    Theme.cpp
    TitleBar.cpp
    TitleBarWidget.cpp
    VolumeControl.cpp
    Widget.cpp
    ../../include/OmicronTK/qt/AppInfo.hpp
    ../../include/OmicronTK/qt/omicrontk_qt_global.hpp
    ../../include/OmicronTK/qt/PopUp.hpp
    ../../include/OmicronTK/qt/ComboBox.hpp
    ../../include/OmicronTK/qt/Dialog.hpp
    ../../include/OmicronTK/qt/DirectoryDialog.hpp
    ../../include/OmicronTK/qt/DropArea.hpp
    ../../include/OmicronTK/qt/Equalizer.hpp
    ../../include/OmicronTK/qt/ErrorWindow.hpp
    ../../include/OmicronTK/qt/Label.hpp
    ../../include/OmicronTK/qt/Slider.hpp
    ../../include/OmicronTK/qt/Theme.hpp
    ../../include/OmicronTK/qt/TitleBar.hpp
    ../../include/OmicronTK/qt/TitleBarWidget.hpp
    ../../include/OmicronTK/qt/Widget.hpp
    ../../include/OmicronTK/qt/VolumeControl.hpp
    ../../include/OmicronTK/qt/version.h)

if(WIN32)
    #set(SRC_FILES ${SRC_FILES} rc/core.rc)
endif()

add_library(${PROJECT_QT} SHARED ${SRC_FILES})

target_link_libraries(${PROJECT_QT} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::UiTools)
    
