cmake_minimum_required(VERSION 3.10)

project("RMGraphics")

set(RMGAPHICS_VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 17)

# RMGraphics C++ API documentation
add_subdirectory(docs)


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


set(CMAKE_INSTALL_FULL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
set(CMAKE_INSTALL_FULL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_INSTALL_FULL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)




#
# Preparing external dependencies.
# GLEW, GLFW, PNG, TIFF, ZLIB
#
if(UNIX)
find_package(GLEW REQUIRED)
find_package(PNG REQUIRED)
find_package(TIFF REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

else()
# Install prebuilt GLEW binary and headers
file(COPY
    ${PROJECT_SOURCE_DIR}/external/glew/lib/glew32s.lib
    DESTINATION ${CMAKE_BINARY_DIR}/lib
)
set(GLEW_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/glew/include)
set(GLEW_LIBRARIES glew32s)
add_definitions(-DGLEW_STATIC)

# Build GLFW from source
set(BUILD_SHARED_LIBS OFF)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)
set(GLFW_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/external/glfw/include)
set(GLFW_LIBRARIES glfw)

# Install ZLIB
file(COPY
    ${PROJECT_SOURCE_DIR}/external/zlib/lib/zlibstatic.lib
    DESTINATION ${CMAKE_BINARY_DIR}/lib
)
set(ZLIB_FOUND TRUE)
set(ZLIB_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/external/zlib/include)
set(ZLIB_LIBRARIES zlibstatic)

# Build PNG
set(PNG_SHARED OFF CACHE BOOL "" FORCE)
set(PNG_BUILD_ZLIB ON CACHE BOOL "" FORCE)

add_subdirectory(external/libpng)
set(PNG_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/external/libpng
    ${CMAKE_BINARY_DIR}/external/libpng
)
set(PNG_LIBRARY png_static)

# Build TIFF
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(zlib OFF CACHE BOOL "" FORCE)
add_subdirectory(external/libtiff)
target_compile_definitions(tiff PUBLIC _CRT_SECURE_NO_WARNINGS)
set(TIFF_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/libtiff/libtiff)
set(TIFF_LIBRARY tiff)
endif()




# Compile RMGraphics
add_subdirectory(src)


set(RMGRAPHICS_LIBRARIES
    rmgbase_s
    rmgimage_s
    rmgwindow_s
)


set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "compile gtest with MD" FORCE)

add_subdirectory(external/googletest)

set_target_properties(gtest
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<0:>
)
set_target_properties(gtest_main
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<0:>
)

add_subdirectory(test)
