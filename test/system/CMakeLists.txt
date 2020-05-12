add_executable(systest_window
    window.cpp
)

target_link_libraries(systest_window PUBLIC
    ${RMGRAPHICS_LIBRARIES}
    gtest
    gtest_main
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)

set_target_properties(systest_window
    PROPERTIES FOLDER ${PROJECT_NAME}/system_test
)
