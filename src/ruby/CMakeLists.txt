
project(${PROJECT_QT_RUBY} LANGUAGES CXX)

add_definitions(-DOTKQT_BUILD_RUBY_LIB)

include_directories(${MRUBY_INCLUDE_PATH})

set(SRC_FILES
    src/RubyComboBox.cpp
    src/RubyLabel.cpp
    src/RubyLayout.cpp
    src/RubyLineEdit.cpp
    src/RubyObject.cpp
    src/RubyProgressBar.cpp
    src/RubyPushButton.cpp
    src/RubySlider.cpp
    src/RubyTitleBarWidget.cpp
    src/RubyVolumeControl.cpp
    src/RubyWidget.cpp
    src/base/RubyObjectBase.cpp
    src/base/RubyWidgetBase.cpp
    src/RubyWidgetWrapper.cpp
    ../../include/OmicronTK/qt/ruby/RubyComboBox.hpp
    ../../include/OmicronTK/qt/ruby/RubyLabel.hpp
    ../../include/OmicronTK/qt/ruby/RubyLayout.hpp
    ../../include/OmicronTK/qt/ruby/RubyLineEdit.hpp
    ../../include/OmicronTK/qt/ruby/RubyObject.hpp
    ../../include/OmicronTK/qt/ruby/RubyProgressBar.hpp
    ../../include/OmicronTK/qt/ruby/RubyPushButton.hpp
    ../../include/OmicronTK/qt/ruby/RubySlider.hpp
    ../../include/OmicronTK/qt/ruby/RubyTitleBarWidget.hpp
    ../../include/OmicronTK/qt/ruby/RubyVolumeControl.hpp
    ../../include/OmicronTK/qt/ruby/RubyWidget.hpp
    ../../include/OmicronTK/qt/ruby/base/RubyObjectBase.hpp
    ../../include/OmicronTK/qt/ruby/base/RubyWidgetBase.hpp
    ../../include/OmicronTK/qt/ruby/RubyWidgetWrapper.hpp
)

if(WIN32)
    set(SRC_FILES ${SRC_FILES} rc/lua.rc)
endif()

add_library(${PROJECT_QT_RUBY} SHARED ${SRC_FILES})

target_link_directories(${PROJECT_QT_RUBY} PRIVATE ${MRUBY_LIB_PATH_UNIX64})

target_link_libraries(${PROJECT_QT_RUBY} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    mruby
    ${PROJECT_QT})
    
