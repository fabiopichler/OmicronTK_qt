set(PROJECT OmicronTK_qt_custom-widgets)

project(${PROJECT} LANGUAGES CXX)

set(SRC_FILES
    Plugin.hpp
    Plugin.cpp

    ComboBoxPlugin.hpp
    ComboBoxPlugin.cpp
    LabelPlugin.hpp
    LabelPlugin.cpp
    SliderPlugin.hpp
    SliderPlugin.cpp

    ../../include/OmicronTK/qt/ComboBox.hpp
    ../../src/core/src/ComboBox.cpp
    ../../include/OmicronTK/qt/Label.hpp
    ../../src/core/src/Label.cpp
    ../../include/OmicronTK/qt/Slider.hpp
    ../../src/core/src/Slider.cpp
)

if(WIN32)
    #set(SRC_FILES ${SRC_FILES} plugin.rc)
endif()

add_library(${PROJECT} SHARED ${SRC_FILES})

target_link_libraries(${PROJECT} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Designer)
