
add_library(rmgbase SHARED
    bitmap.cpp
    bitmap_png.cpp
    bitmap_tiff.cpp
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
    mesh_indices.cpp
    mesh_normals.cpp
    mouse.cpp
    line3d.cpp
    object.cpp
    object2d.cpp
    object3d.cpp
    object3d_obj.cpp
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
    internal/glcontext.cpp
    internal/line3d_shader.cpp
    internal/object2d_shader.cpp
    internal/particle_shader.cpp
    internal/shader.cpp
    internal/shadow_map_shader.cpp
    internal/sprite_load.cpp
    internal/texture_load.cpp
    internal/vbo_load.cpp
    
    rmg/alignment.hpp
    rmg/assert.hpp
    rmg/assert.inc
    rmg/bitmap.hpp
    rmg/camera.hpp
    rmg/color.hpp
    rmg/context.hpp
    rmg/cube.hpp
    rmg/cylinder.hpp
    rmg/font.hpp
    rmg/keyboard.hpp
    rmg/material.hpp
    rmg/mesh.hpp
    rmg/mouse.hpp
    rmg/line3d.hpp
    rmg/object.hpp
    rmg/object2d.hpp
    rmg/object3d.hpp
    rmg/particle.hpp
    rmg/rmg.hpp
    rmg/sphere.hpp
    rmg/sprite.hpp
    rmg/text2d.hpp
    rmg/math/euler.hpp
    rmg/math/mat3.hpp
    rmg/math/mat3.inc
    rmg/math/mat4.hpp
    rmg/math/mat4.inc
    rmg/math/vec.hpp
    rmg/math/vec2.hpp
    rmg/math/vec2.inc
    rmg/math/vec3.hpp
    rmg/math/vec3.inc
    rmg/math/vec4.hpp
    rmg/math/vec4.inc
    rmg/internal/context_load.hpp
    rmg/internal/general_shader.hpp
    rmg/internal/glcontext.hpp
    rmg/internal/line3d_shader.hpp
    rmg/internal/object2d_shader.hpp
    rmg/internal/particle_shader.hpp
    rmg/internal/shader.hpp
    rmg/internal/shadow_map_shader.hpp
    rmg/internal/sprite_load.hpp
    rmg/internal/texture_load.hpp
    rmg/internal/vbo_load.hpp
)




target_include_directories(rmgbase PUBLIC
    ${OPENGL_INCLUDE_DIR}
    ${PNG_INCLUDE_DIR}
    ${TIFF_INCLUDE_DIR}
)

target_link_libraries(rmgbase PUBLIC
    ${OPENGL_LIBRARIES}
    ${PNG_LIBRARY}
    ${TIFF_LIBRARY}
)

set_target_properties(rmgbase PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
