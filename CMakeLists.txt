cmake_minimum_required(VERSION 3.10)

project("RMGraphics" VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)


# RMGraphics C++ API documentation
add_subdirectory(docs)


# Gets OpenGL header and library
set(OpenGL_GL_PREFERENCE LEGACY)
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
#
if(UNIX)
find_package(GLEW REQUIRED)
find_package(PNG REQUIRED)
find_package(TIFF REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

else()
file(COPY
    ${PROJECT_SOURCE_DIR}/external/lib
    DESTINATION ${CMAKE_BINARY_DIR}
)
set(GLEW_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/include)
set(GLEW_LIBRARIES glew32s)
add_definitions(-DGLEW_STATIC)
set(GLFW_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/external/include)
set(GLFW_LIBRARIES glfw3)
set(PNG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/include/libpng)
set(PNG_LIBRARY libpng16_static zlibstatic)
set(TIFF_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/include/libtiff)
set(TIFF_LIBRARY tiff zlibstatic)
endif()

if(WIN32)
set(wxWidgets_ROOT_DIR C:/wxWidgets-3.1.4)
set(wxWidgets_CONFIGURATION mswu)
endif()
find_package(wxWidgets 3.1 COMPONENTS base core gl)




# Compile flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
add_definitions(
    -Wall
    -Wno-unused-function
    -Wno-unused-label
    -Wno-unused-value
    -Wno-unused-variable
)
else()
add_definitions(
    -D_CRT_SECURE_NO_WARNINGS
    /wd26451
    /wd4098
    /wd4217
    /wd4244
    /wd4251
    /wd4267
    /wd4273
)
endif()

# Compile RMGraphics
add_subdirectory(src)


# 
# Compile definitions, include directories and libraries
# 
set(RMGRAPHICS_DEFINITIONS "")

set(RMGRAPHICS_INCLUDE_DIRS
    ${CMAKE_BINARY_DIR}/include
    ${GLEW_INCLUDE_DIR}
)

set(RMGRAPHICS_LIBRARIES
    rmgbase
    rmgwindow
)

if(wxWidgets_FOUND)
list(APPEND RMGRAPHICS_DEFINITIONS ${wxWidgets_DEFINITIONS})
list(APPEND RMGRAPHICS_INCLUDE_DIRS ${wxWidgets_INCLUDE_DIRS})
list(APPEND RMGRAPHICS_LIBRARIES rmgwx)

message(STATUS ${wxWidgets_DEFINITIONS})
endif()




set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "compile gtest with MD" FORCE)
add_subdirectory(external/googletest)
add_subdirectory(test)
