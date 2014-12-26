add_subdirectory(core)
add_subdirectory(gui)

if(BUILD_BOX2D)
    add_subdirectory(box2D)
endif()
