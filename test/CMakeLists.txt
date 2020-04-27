include_directories(../external/googletest/googletest/include)
include_directories(../include)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.cpp)

add_executable(rmg_test ${TEST_SOURCES})

set(RMGRAPHICS_LIBRARIES_STATIC
    rmgbase_s
)

target_link_libraries(rmg_test PUBLIC
    ${RMGRAPHICS_LIBRARIES_STATIC}
    gtest
    gtest_main
)

add_custom_target(check
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/rmg_test
    DEPENDS rmg_test
)
