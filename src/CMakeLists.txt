
add_subdirectory(qt)
add_subdirectory(qt_network)
add_subdirectory(plugins)

if(NOT WIN32)
    add_subdirectory(qt_lua)
    add_subdirectory(qt_ruby)
endif()
