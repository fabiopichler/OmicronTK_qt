
project(${PROJECT_QT_LUA} LANGUAGES CXX)

add_definitions(-DOTKQT_BUILD_LUA_LIB)

include_directories("../../../OmicronTK_lua/include")

set(SRC_FILES
    LuaComboBox.cpp
    LuaObject.cpp
    LuaVolumeControl.cpp
    LuaTitleBarWidget.cpp
    LuaWidget.cpp
    LuaLabel.cpp
    LuaLayout.cpp
    LuaSlider.cpp
    LuaProgressBar.cpp
    LuaLineEdit.cpp
    LuaPushButton.cpp
    base/LuaObjectBase.cpp
    base/LuaWidgetBase.cpp
    LuaWidgetWrapper.cpp
    ../../include/OmicronTK/qt_lua/omicrontk_qt_lua_global.hpp
    ../../include/OmicronTK/qt_lua/LuaComboBox.hpp
    ../../include/OmicronTK/qt_lua/LuaObject.hpp
    ../../include/OmicronTK/qt_lua/LuaVolumeControl.hpp
    ../../include/OmicronTK/qt_lua/LuaTitleBarWidget.hpp
    ../../include/OmicronTK/qt_lua/LuaWidget.hpp
    ../../include/OmicronTK/qt_lua/LuaLabel.hpp
    ../../include/OmicronTK/qt_lua/LuaLayout.hpp
    ../../include/OmicronTK/qt_lua/LuaSlider.hpp
    ../../include/OmicronTK/qt_lua/LuaProgressBar.hpp
    ../../include/OmicronTK/qt_lua/LuaLineEdit.hpp
    ../../include/OmicronTK/qt_lua/LuaPushButton.hpp
    ../../include/OmicronTK/qt_lua/base/LuaObjectBase.hpp
    ../../include/OmicronTK/qt_lua/base/LuaWidgetBase.hpp
    ../../include/OmicronTK/qt_lua/LuaWidgetWrapper.hpp)

if(WIN32)
    #set(SRC_FILES ${SRC_FILES} rc/lua.rc)
endif()

add_library(${PROJECT_QT_LUA} SHARED ${SRC_FILES})

target_link_directories(${PROJECT_QT_LUA} PRIVATE "../../../OmicronTK_lua/lib/linux64/debug")

target_link_libraries(${PROJECT_QT_LUA} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    OmicronTK_lua
    ${PROJECT_QT})
    
