add_executable(systest_window window.cpp)

target_compile_definitions(systest_window PUBLIC
    ${RMGRAPHICS_DEFINITIONS}
)
