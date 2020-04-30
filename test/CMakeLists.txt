include_directories(../external/googletest/googletest/include)
include_directories(../include)

file(GLOB_RECURSE RMGTEST_SOURCES *.cpp)

add_executable(rmg_test ${RMGTEST_SOURCES})

set(RMGRAPHICS_LIBRARIES_STATIC
    rmgbase_s
)

target_link_libraries(rmg_test PUBLIC
    ${RMGRAPHICS_LIBRARIES_STATIC}
    gtest
    gtest_main
)

if(MSVC)
set(RMGTEST_PROGRAM ${CMAKE_CURRENT_BINARY_DIR}/Debug/rmg_test)
else()
set(RMGTEST_PROGRAM ${CMAKE_CURRENT_BINARY_DIR}/rmg_test)
endif()

add_custom_target(check
    COMMAND ${RMGTEST_PROGRAM}
    DEPENDS rmg_test
)