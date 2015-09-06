set(INCROOT ${PROJECT_SOURCE_DIR}/examples)
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples)


add_executable(core core.cpp)
target_link_libraries(core ${PROJECT_NAME}-core-${SFML_UTILS_BUILD_SUFIX})

if(SFML_UTILS_BUILD_MODULE_GUI)
    add_executable(gui gui.cpp)
    target_link_libraries(gui ${PROJECT_NAME}-gui-${SFML_UTILS_BUILD_SUFIX})
endif()

if(SFML_UTILS_BUILD_MODULE_MAP)
    add_executable(map map.cpp)
    target_link_libraries(map ${PROJECT_NAME}-map-${SFML_UTILS_BUILD_SUFIX})

    if(SFML_UTILS_BUILD_MODULE_MAP_EDITOR)
        add_executable(editor editor.cpp)
        target_link_libraries(editor ${PROJECT_NAME}-editor-${SFML_UTILS_BUILD_SUFIX})
    endif()
endif()

if(SFML_UTILS_BUILD_MODULE_ENTITY_SYSTEM)
    add_executable(es es.cpp)
    target_link_libraries(es ${LIBS} ${UTILS_LIBRARY})
endif()

if(SFML_UTILS_BUILD_MODULE_BOX2D)
    add_executable(box2D box2D.cpp)
    target_link_libraries(box2D ${LIBS} ${BOX2D_LIBRARY} ${PROJECT_NAME}-box2D-${SFML_UTILS_BUILD_SUFIX})
endif()

if(SFML_UTILS_BUILD_MODULE_CEGUI)
    add_executable(cegui cegui.cpp)
    target_link_libraries(cegui ${LIBS} ${LIBS_CEGUI} ${PROJECT_NAME}-cegui-${SFML_UTILS_BUILD_SUFIX})
endif()



