
add_subdirectory(core)
add_subdirectory(network)

if(NOT WIN32)
    add_subdirectory(lua)
    add_subdirectory(ruby)
endif()
