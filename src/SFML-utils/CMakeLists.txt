set(INCROOT ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME})

add_subdirectory(core)

if(SFML_UTILS_BUILD_MODULE_ENTITY_SYSTEM)
    add_subdirectory(es)
endif()

if(SFML_UTILS_BUILD_MODULE_GUI)
    add_subdirectory(gui)
endif()


if(SFML_UTILS_BUILD_MODULE_MAP)
    add_subdirectory(map)

    if(SFML_UTILS_BUILD_MODULE_MAP_EDITOR)
        add_subdirectory(map-editor)
    endif()
endif()

if(SFML_UTILS_BUILD_MODULE_BOX2D)
    add_subdirectory(box2D)
endif()

if(SFML_UTILS_BUILD_MODULE_CEGUI)
    add_subdirectory(cegui)
endif()

deploy(ROOT ${INCROOT}
    DESTINATION include
)

