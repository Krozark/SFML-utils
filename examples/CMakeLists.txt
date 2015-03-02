set(INCROOT ${PROJECT_SOURCE_DIR}/examples)
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples)

add_executable(core core.cpp)
target_link_libraries(core ${CMAKE_PROJECT_NAME}-core)

add_executable(gui gui.cpp)
target_link_libraries(gui ${CMAKE_PROJECT_NAME}-gui)

add_executable(map map.cpp)
target_link_libraries(map ${CMAKE_PROJECT_NAME}-map)

add_executable(es es.cpp)
target_link_libraries(es ${CMAKE_PROJECT_NAME}-es)


