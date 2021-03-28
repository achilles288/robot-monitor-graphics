
add_library(rmgbase SHARED
    assert.hpp
    assert.inc
    bitmap.cpp
    bitmap.hpp
    bitmap_png.cpp
    bitmap_tiff.cpp
    camera.cpp
    camera.hpp
    color.cpp
    color.hpp
    context.hpp
    context_container.cpp
    context_renderer.cpp
    context_world.cpp
    cube.cpp
    cube.hpp
    cylinder.cpp
    cylinder.hpp
    font.cpp
    font.hpp
    keyboard.cpp
    keyboard.hpp
    material.cpp
    material.hpp
    mesh.cpp
    mesh.hpp
    mesh_indices.cpp
    mesh_normals.cpp
    mouse.cpp
    mouse.hpp
    line3d.cpp
    line3d.hpp
    object.cpp
    object.hpp
    object2d.cpp
    object2d.hpp
    object3d.cpp
    object3d.hpp
    object3d_obj.cpp
    particle.cpp
    particle.hpp
    rmg.hpp
    sphere.cpp
    sphere.hpp
    sprite.cpp
    sprite.hpp
    text_alignment.hpp
    text2d.cpp
    text2d.hpp
    math/euler.cpp
    math/euler.hpp
    math/mat3.cpp
    math/mat3.hpp
    math/mat3.inc
    math/mat4.cpp
    math/mat4.hpp
    math/mat4.inc
    math/ostream.cpp
    math/vec.hpp
    math/vec2.hpp
    math/vec2.inc
    math/vec3.cpp
    math/vec3.hpp
    math/vec3.inc
    math/vec4.cpp
    math/vec4.hpp
    math/vec4.inc
    internal/context_load.cpp
    internal/context_load.hpp
    internal/general_shader.cpp
    internal/general_shader.hpp
    internal/line3d_shader.cpp
    internal/line3d_shader.hpp
    internal/particle_shader.cpp
    internal/particle_shader.hpp
    internal/shader.cpp
    internal/shader.hpp
    internal/shadow_map_shader.cpp
    internal/shadow_map_shader.hpp
    internal/sprite_shader.cpp
    internal/sprite_shader.hpp
    internal/texture_load.cpp
    internal/texture_load.hpp
    internal/vbo_load.cpp
    internal/vbo_load.hpp
)

file(COPY
    rmg.hpp
    assert.hpp
    assert.inc
    bitmap.hpp
    camera.hpp
    color.hpp
    context.hpp
    cube.hpp
    cylinder.hpp
    font.hpp
    keyboard.hpp
    line3d.hpp
    material.hpp
    math.hpp
    mesh.hpp
    mouse.hpp
    object.hpp
    object2d.hpp
    object3d.hpp
    particle.hpp
    sphere.hpp
    sprite.hpp
    text_alignment.hpp
    text2d.hpp
    DESTINATION ${CMAKE_BINARY_DIR}/include/rmg
)

file(COPY
    math/angle_unit.hpp
    math/euler.hpp
    math/line_equation.hpp
    math/mat3.hpp
    math/mat3.inc
    math/mat4.hpp
    math/mat4.inc
    math/plane_equation.hpp
    math/vec.hpp
    math/vec2.hpp
    math/vec2.inc
    math/vec3.hpp
    math/vec3.inc
    math/vec4.hpp
    math/vec4.inc
    DESTINATION ${CMAKE_BINARY_DIR}/include/rmg/math
)

file(COPY
    internal/context_load.hpp
    internal/general_shader.hpp
    internal/line3d_shader.hpp
    internal/particle_shader.hpp
    internal/shader.hpp
    internal/shadow_map_shader.hpp
    internal/sprite_shader.hpp
    internal/texture_load.hpp
    internal/vbo_load.hpp
    DESTINATION ${CMAKE_BINARY_DIR}/include/rmg/internal
)




target_include_directories(rmgbase PUBLIC
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${PNG_INCLUDE_DIR}
    ${TIFF_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}/include
)

target_link_libraries(rmgbase PUBLIC
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${PNG_LIBRARY}
    ${TIFF_LIBRARY}
)

set_target_properties(rmgbase PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)