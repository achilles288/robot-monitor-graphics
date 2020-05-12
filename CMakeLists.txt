cmake_minimum_required(VERSION 3.10)

project("RMGraphics")

set(RMGAPHICS_VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 17)

# RMGraphics C++ API documentation
add_subdirectory(include)


# Gets OpenGL header and library
find_package(OpenGL REQUIRED)


if(UNIX)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<0:>)
else()
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<0:>)
endif()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<0:>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<0:>)

link_directories(${CMAKE_BINARY_DIR}/lib)


# Uses external libraries GLEW and GLFW
if(UNIX)
find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

else()
# Install prebuilt GLEW binary and headers
file(COPY
    ${PROJECT_SOURCE_DIR}/external/glew/bin/glew32.dll
    DESTINATION ${CMAKE_BINARY_DIR}/bin
)
file(COPY
    ${PROJECT_SOURCE_DIR}/external/glew/lib/glew32.lib
    DESTINATION ${CMAKE_BINARY_DIR}/lib
)
set(GLEW_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/glew/include)
set(GLEW_LIBRARIES glew32)

# Build GLFW from source
set(BUILD_SHARED_LIBS ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)
set(GLFW_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/external/glfw/include)
set(GLFW_LIBRARIES glfw)
set(BUILD_SHARED_LIBS OFF)
endif()


# Compile RMGraphics
add_subdirectory(src)


set(RMGRAPHICS_LIBRARIES
    rmgbase_s
    rmgwindow_s
)


set(gtest_force_shared_crt ON CACHE BOOL "compile gtest with MD" FORCE)

add_subdirectory(external/googletest/googletest)

set_target_properties(gtest
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<0:>
)
set_target_properties(gtest_main
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<0:>
)

add_subdirectory(test)
