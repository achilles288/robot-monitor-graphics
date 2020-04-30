cmake_minimum_required(VERSION 3.10)

project("RMGraphics")

set(RMGAPHICS_VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 17)

if(NOT UNIX)
add_subdirectory(external/glfw)
endif()

add_subdirectory(include)
add_subdirectory(src)

set(RMGRAPHICS_LIBRARIES
    ${RMGCORE_LIBRARY}
    ${RMGGLFW_LIBRARY}
    ${RMGWX_LIBRARY}
)

set(gtest_force_shared_crt ON CACHE BOOL "compile gtest with MD" FORCE)
add_subdirectory(external/googletest/googletest)
add_subdirectory(test)
