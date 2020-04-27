set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#
# RMGraphics Base Library
#
find_package(OpenGL REQUIRED)

include_directories(../include)
include_directories(${OPENGL_INCLUDE_DIR})

set(RMGBASE_LIBRARY rmgbase)

set(RMGBASE_SOURCES
    math/euler.cpp
    math/mat3.cpp
    math/mat4.cpp
    math/vec3.cpp
    math/vec4.cpp
)

add_library(${RMGBASE_LIBRARY}_s STATIC ${RMGBASE_SOURCES})

target_link_libraries(${RMGBASE_LIBRARY}_s PUBLIC
    ${OPENGL_LIBRARIES}
    m
)
