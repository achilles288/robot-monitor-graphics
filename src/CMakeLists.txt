set(RMGCONFIG_RESOURCE_PATH ${PROJECT_SOURCE_DIR}/share)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/rmg/config.h
)


# 
# RMGraphics Base Library
# 
add_library(rmgbase SHARED
    camera.cpp
    color.cpp
    context_container.cpp
    context_renderer.cpp
    context_world.cpp
    cube.cpp
    cylinder.cpp
    font.cpp
    keyboard.cpp
    material.cpp
    mesh.cpp
    mouse.cpp
    line3d.cpp
    object.cpp
    object2d.cpp
    object3d.cpp
    particle.cpp
    sphere.cpp
    sprite.cpp
    text2d.cpp
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
    rmg/camera.hpp
    rmg/color.hpp
    rmg/context.hpp
    rmg/cube.hpp
    rmg/cylinder.hpp
    rmg/font.hpp
    rmg/keyboard.hpp
    rmg/line3d.hpp
    rmg/material.hpp
    rmg/math.hpp
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

target_include_directories(rmgbase PUBLIC
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
)

target_link_libraries(rmgbase PUBLIC
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)


# 
# RMGraphics Image Library
# 
add_library(rmgimage SHARED
    bitmap.cpp
    bitmap_png.cpp
    bitmap_tiff.cpp
    rmg/bitmap.hpp
)

target_include_directories(rmgimage PUBLIC
    ${PNG_INCLUDE_DIR}
    ${TIFF_INCLUDE_DIR}
)

target_link_libraries(rmgimage PUBLIC
    ${GLFW_LIBRARIES}
    ${PNG_LIBRARY}
    ${TIFF_LIBRARY}
)


# 
# RMGraphics Window Framework Library
# 
add_library(rmgwindow SHARED
    window.cpp
    rmg/window.hpp
)

target_include_directories(rmgwindow PUBLIC
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIRS}
)

target_link_libraries(rmgwindow PUBLIC
    rmgimage
    ${GLFW_LIBRARIES}
)


# 
# RMGraphics wxWidgets port
# 
if(${wxWidgets_FOUND})
add_library(rmgwx SHARED
    wxcanvas.cpp
    rmg/wxcanvas.hpp
)

target_compile_definitions(rmgwx PUBLIC ${wxWidgets_DEFINITIONS})

target_include_directories(rmgwx PUBLIC
    ${GLEW_INCLUDE_DIRS}
    ${wxWidgets_INCLUDE_DIRS}
)

target_link_libraries(rmgwx PUBLIC ${wxWidgets_LIBRARIES})

set_target_properties(rmgwx PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    FOLDER ${PROJECT_NAME}
)
endif()




set_target_properties(rmgbase rmgimage rmgwindow PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    FOLDER ${PROJECT_NAME}
)
