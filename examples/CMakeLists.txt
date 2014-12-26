set(INCROOT ${PROJECT_SOURCE_DIR}/examples)
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples)

add_executable(gui gui.cpp)
target_link_libraries(gui ${CMAKE_PROJECT_NAME}-gui)


