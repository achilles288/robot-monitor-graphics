include_directories(
    ../include
    external/googletest/googletest/include
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
)

file(GLOB RMGTEST_UNIT_SOURCES unit/*.cpp)

add_executable(rmg_test
    ${RMGTEST_UNIT_SOURCES}
)

target_link_libraries(rmg_test PUBLIC
    ${RMGRAPHICS_LIBRARIES}
    gtest
    gtest_main
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)

set_target_properties(rmg_test PROPERTIES FOLDER ${PROJECT_NAME})

add_subdirectory(system)
