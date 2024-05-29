
add_subdirectory(qt)
add_subdirectory(network)
add_subdirectory(plugins)

if(NOT WIN32)
    add_subdirectory(lua)
    add_subdirectory(ruby)
endif()
