set(INCROOT ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME})

add_subdirectory(core)
add_subdirectory(es)
add_subdirectory(gui)
add_subdirectory(map)
add_subdirectory(map-editor)

if(SFML_UTILS_BUILD_BOX2D)
    add_subdirectory(box2D)
endif()

deploy(ROOT ${INCROOT}
    DESTINATION include
)

