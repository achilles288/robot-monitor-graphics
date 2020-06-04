set(RMGCONFIG_RESOURCE_PATH ${PROJECT_SOURCE_DIR}/share)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in
    ${CMAKE_BINARY_DIR}/config/rmg/config.hpp
)


# 
# RMGraphics Base Library
# 
include_directories(
    ../include
    ${CMAKE_BINARY_DIR}/config
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
)

set(RMGBASE_LIBRARY rmgbase)

set(RMGBASE_SOURCES
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
    math/ostream.cpp
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
    rmg/internal/window_callback.hpp
    
    rmg/assert.inc
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

set_target_properties(${RMGBASE_LIBRARY}_s
    PROPERTIES FOLDER ${PROJECT_NAME}
)


# 
# RMGraphics Image Library
# 
include_directories(
    ${PNG_INCLUDE_DIR}
    ${TIFF_INCLUDE_DIR}
)

set(RMGIMAGE_LIBRARY rmgimage)

set(RMGIMAGE_SOURCES
    bitmap.cpp
    bitmap_png.cpp
    bitmap_tiff.cpp
    rmg/bitmap.hpp
)

add_library(${RMGIMAGE_LIBRARY}_s STATIC ${RMGIMAGE_SOURCES})

target_link_libraries(${RMGIMAGE_LIBRARY}_s PUBLIC
    ${GLFW_LIBRARIES}
    ${PNG_LIBRARY}
    ${TIFF_LIBRARY}
)

set_target_properties(${RMGIMAGE_LIBRARY}_s
    PROPERTIES FOLDER ${PROJECT_NAME}
)


# 
# RMGraphics Window Framework Library
# 
include_directories(${GLFW_INCLUDE_DIRS})

set(RMGWINDOW_LIBRARY rmgwindow)

set(RMGWINDOW_SOURCES
    window.cpp
    rmg/window.hpp
)

add_library(${RMGWINDOW_LIBRARY}_s STATIC ${RMGWINDOW_SOURCES})

target_link_libraries(${RMGWINDOW_LIBRARY}_s PUBLIC
    ${RMGIMAGE_LIBRARY}_s
    ${GLFW_LIBRARIES}
)

set_target_properties(${RMGWINDOW_LIBRARY}_s
    PROPERTIES FOLDER ${PROJECT_NAME}
)
