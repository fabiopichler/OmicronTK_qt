
project(${PROJECT_QT_LUA} LANGUAGES CXX)

add_definitions(-DOTKQT_BUILD_LUA_LIB)

include_directories("${OTKLUA}/include")

set(SRC_FILES
    src/LuaComboBox.cpp
    src/LuaObject.cpp
    src/LuaVolumeControl.cpp
    src/LuaTitleBarWidget.cpp
    src/LuaWidget.cpp
    src/LuaLabel.cpp
    src/LuaLayout.cpp
    src/LuaSlider.cpp
    src/LuaProgressBar.cpp
    src/LuaLineEdit.cpp
    src/LuaPushButton.cpp
    src/base/LuaObjectBase.cpp
    src/base/LuaWidgetBase.cpp
    src/LuaWidgetWrapper.cpp
    ../../include/OmicronTK/qt/lua/LuaComboBox.hpp
    ../../include/OmicronTK/qt/lua/LuaObject.hpp
    ../../include/OmicronTK/qt/lua/LuaVolumeControl.hpp
    ../../include/OmicronTK/qt/lua/LuaTitleBarWidget.hpp
    ../../include/OmicronTK/qt/lua/LuaWidget.hpp
    ../../include/OmicronTK/qt/lua/LuaLabel.hpp
    ../../include/OmicronTK/qt/lua/LuaLayout.hpp
    ../../include/OmicronTK/qt/lua/LuaSlider.hpp
    ../../include/OmicronTK/qt/lua/LuaProgressBar.hpp
    ../../include/OmicronTK/qt/lua/LuaLineEdit.hpp
    ../../include/OmicronTK/qt/lua/LuaPushButton.hpp
    ../../include/OmicronTK/qt/lua/base/LuaObjectBase.hpp
    ../../include/OmicronTK/qt/lua/base/LuaWidgetBase.hpp
    ../../include/OmicronTK/qt/lua/LuaWidgetWrapper.hpp)

if(WIN32)
    set(SRC_FILES ${SRC_FILES} rc/lua.rc)
endif()

add_library(${PROJECT_QT_LUA} SHARED ${SRC_FILES})

target_link_directories(${PROJECT_QT_LUA} PRIVATE "${OTKLUA}/lib/debug")

target_link_libraries(${PROJECT_QT_LUA} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    OmicronTK_lua
    ${PROJECT_QT})
    
