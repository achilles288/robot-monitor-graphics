add_executable(systest_window
    window.cpp
)

target_link_libraries(systest_window PUBLIC
    ${RMGRAPHICS_LIBRARIES}
    gtest
    gtest_main
)
