add_subdirectory(core)
add_subdirectory(gui)
add_subdirectory(map)

if(BUILD_BOX2D)
    add_subdirectory(box2D)
endif()
