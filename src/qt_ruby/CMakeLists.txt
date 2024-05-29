
project(${PROJECT_QT_RUBY} LANGUAGES CXX)

add_definitions(-DOTKQT_BUILD_RUBY_LIB)

include_directories(${MRUBY_INCLUDE_PATH})

set(SRC_FILES
    RubyComboBox.cpp
    RubyLabel.cpp
    RubyLayout.cpp
    RubyLineEdit.cpp
    RubyObject.cpp
    RubyProgressBar.cpp
    RubyPushButton.cpp
    RubySlider.cpp
    RubyTitleBarWidget.cpp
    RubyVolumeControl.cpp
    RubyWidget.cpp
    base/RubyObjectBase.cpp
    base/RubyWidgetBase.cpp
    RubyWidgetWrapper.cpp
    ../../include/OmicronTK/qt_ruby/omicrontk_qt_ruby_global.hpp
    ../../include/OmicronTK/qt_ruby/RubyComboBox.hpp
    ../../include/OmicronTK/qt_ruby/RubyLabel.hpp
    ../../include/OmicronTK/qt_ruby/RubyLayout.hpp
    ../../include/OmicronTK/qt_ruby/RubyLineEdit.hpp
    ../../include/OmicronTK/qt_ruby/RubyObject.hpp
    ../../include/OmicronTK/qt_ruby/RubyProgressBar.hpp
    ../../include/OmicronTK/qt_ruby/RubyPushButton.hpp
    ../../include/OmicronTK/qt_ruby/RubySlider.hpp
    ../../include/OmicronTK/qt_ruby/RubyTitleBarWidget.hpp
    ../../include/OmicronTK/qt_ruby/RubyVolumeControl.hpp
    ../../include/OmicronTK/qt_ruby/RubyWidget.hpp
    ../../include/OmicronTK/qt_ruby/base/RubyObjectBase.hpp
    ../../include/OmicronTK/qt_ruby/base/RubyWidgetBase.hpp
    ../../include/OmicronTK/qt_ruby/RubyWidgetWrapper.hpp
)

if(WIN32)
    #set(SRC_FILES ${SRC_FILES} rc/lua.rc)
endif()

add_library(${PROJECT_QT_RUBY} SHARED ${SRC_FILES})

target_link_directories(${PROJECT_QT_RUBY} PRIVATE ${MRUBY_LIB_PATH_UNIX64})

target_link_libraries(${PROJECT_QT_RUBY} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    mruby
    ${PROJECT_QT})
    
