set(gtest_force_shared_crt ON CACHE BOOL "compile gtest with MD" FORCE)
add_subdirectory(googletest)

include_directories(googletest/include)
include_directories(../include)

file(GLOB RMGTEST_UNIT_SOURCES unit/*.cpp)

add_executable(rmg_test
    ${RMGTEST_UNIT_SOURCES}
)

target_link_libraries(rmg_test PUBLIC
    ${RMGRAPHICS_LIBRARIES}
    gtest
    gtest_main
)

if(MSVC)
set(RMGTEST_PROGRAM ${CMAKE_BINARY_DIR}/bin/Debug/rmg_test)
else()
set(RMGTEST_PROGRAM ${CMAKE_BINARY_DIR}/bin/rmg_test)
endif()

add_custom_target(check
    COMMAND ${RMGTEST_PROGRAM}
    DEPENDS rmg_test
)

add_subdirectory(system)
