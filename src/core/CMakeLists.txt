
project(${PROJECT_QT} LANGUAGES CXX)

add_definitions(-DOTKQT_BUILD_CORE_LIB)

set(SRC_FILES
    src/AppInfo.cpp
    src/ComboBox.cpp
    src/Dialog.cpp
    src/DirectoryDialog.cpp
    src/DropArea.cpp
    src/Equalizer.cpp
    src/ErrorWindow.cpp
    src/Label.cpp
    src/PopUp.cpp
    src/Slider.cpp
    src/Theme.cpp
    src/TitleBar.cpp
    src/TitleBarWidget.cpp
    src/VolumeControl.cpp
    src/Widget.cpp
    ../../include/OmicronTK/qt/AppInfo.hpp
    ../../include/OmicronTK/qt/global.h
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
    set(SRC_FILES ${SRC_FILES} rc/core.rc)
endif()

add_library(${PROJECT_QT} SHARED ${SRC_FILES})

target_link_libraries(${PROJECT_QT} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets)
    
