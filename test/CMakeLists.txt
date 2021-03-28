configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/testconf.h
)

include_directories(${RMGRAPHICS_INCLUDE_DIRS})
link_libraries(${RMGRAPHICS_LIBRARIES})

file(GLOB_RECURSE RMGTEST_UNIT_SOURCES unit/*.cpp)

add_executable(rmg_test
    ${RMGTEST_UNIT_SOURCES}
)

target_compile_definitions(rmg_test PUBLIC
    ${RMGRAPHICS_DEFINITIONS}
)

target_include_directories(rmg_test PUBLIC
    ${OPENGL_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest/include
)

target_link_libraries(rmg_test PUBLIC
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    gtest
    gtest_main
)

add_subdirectory(system)
