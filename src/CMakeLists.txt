# 
# RMGraphics Base Library
# 
find_package(OpenGL REQUIRED)

if(UNIX)
find_package(GLEW REQUIRED)
else()
add_subdirectory(external/glew)
set(GLEW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include)
set(GLEW_LIBRARIES glew_s)
endif()

include_directories(
    ../include
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
)

set(RMGBASE_LIBRARY rmgbase)

set(RMGBASE_SOURCES
    assert.cpp
    color.cpp
    context_render.cpp
    context_resource.cpp
    context_world.cpp
    font.cpp
    keyboard.cpp
    material.cpp
    mouse.cpp
    object.cpp
    math/euler.cpp
    math/mat3.cpp
    math/mat4.cpp
    math/vec3.cpp
    math/vec4.cpp
    internal/context_load.cpp
    internal/general_shader.cpp
    internal/line3d_shader.cpp
    internal/particle_shader.cpp
    internal/shader.cpp
    internal/shadow_map_shader.cpp
    internal/sprite_shader.cpp
    internal/texture_load.cpp
    internal/vbo_load.cpp
    
    rmg/rmg.hpp
    rmg/assert.hpp
    rmg/color.hpp
    rmg/context.hpp
    rmg/cube.hpp
    rmg/cylinder.hpp
    rmg/font.hpp
    rmg/keyboard.hpp
    rmg/line3d.hpp
    rmg/material.hpp
    rmg/math.hpp
    rmg/model.hpp
    rmg/mouse.hpp
    rmg/object.hpp
    rmg/object2d.hpp
    rmg/object3d.hpp
    rmg/particle.hpp
    rmg/sphere.hpp
    rmg/sprite.hpp
    rmg/text2d.hpp
    rmg/text_alignment.hpp
    rmg/math/angle_unit.hpp
    rmg/math/euler.hpp
    rmg/math/line_equation.hpp
    rmg/math/mat3.hpp
    rmg/math/mat4.hpp
    rmg/math/plane_equation.hpp
    rmg/math/vec2.hpp
    rmg/math/vec3.hpp
    rmg/math/vec4.hpp
    rmg/internal/context_load.hpp
    rmg/internal/general_shader.hpp
    rmg/internal/line3d_shader.hpp
    rmg/internal/particle_shader.hpp
    rmg/internal/shader.hpp
    rmg/internal/shadow_map_shader.hpp
    rmg/internal/sprite_shader.hpp
    rmg/internal/texture_load.hpp
    rmg/internal/vbo_load.hpp
    
    rmg/math/mat3.inc
    rmg/math/mat4.inc
    rmg/math/vec2.inc
    rmg/math/vec3.inc
    rmg/math/vec4.inc
)

add_library(${RMGBASE_LIBRARY}_s STATIC ${RMGBASE_SOURCES})

target_link_libraries(${RMGBASE_LIBRARY}_s PUBLIC
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)


# 
# RMGraphics Window Framework Library
# 
if(UNIX)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
else()
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)
set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include)
endif()

include_directories(${GLFW_INCLUDE_DIRS})

set(RMGWINDOW_LIBRARY rmgwindow)

set(RMGWINDOW_SOURCES
    window.cpp
    rmg/window.hpp
)

add_library(${RMGWINDOW_LIBRARY}_s STATIC ${RMGWINDOW_SOURCES})

target_link_libraries(${RMGWINDOW_LIBRARY}_s PUBLIC
    ${GLFW_LIBRARIES}
)
