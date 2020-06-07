/**
 * @file vbo_load.cpp
 * @brief Manages the GPU resources mainly for 3D objects
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "../rmg/internal/vbo_load.hpp"

#include <cstdlib>
#include <utility>

#include <GL/glew.h>
#include <GL/gl.h>


namespace rmg {
namespace internal {


// Class: VBOLoad

/**
 * @brief Constructs a pending object
 * 
 * @param vbo Address to a VBO instance. This is to redirect 
 *            responses after loading.
 * @param mesh Mesh
 */
VBOLoad::VBOLoad(VBO* vbo, const Mesh& mesh): Mesh(mesh) {
    this->vbo = vbo;
}

/**
 * @brief Destructor
 */
VBOLoad::~VBOLoad() {}

/**
 * @brief Loads the array of VBOs to the GPU
 * 
 * Loads the arrays of vertices, normals, texture coordinate and indecies
 * which are created by model constructors (Cube3D, Model3D, .etc) into
 * GPU. Also this pending object's load function assigns the resource
 * addresses to the related VBO object.
 */
void VBOLoad::load() {
    if(vbo->vertexArrayID != 0)
        return;
    
    glGenVertexArrays(1, &vbo->vertexArrayID);
    glBindVertexArray(vbo->vertexArrayID);
    
    // Vertices
    glGenBuffers(1, &vbo->vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbo->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_count*sizeof(Vec3), vertices,
                 GL_STATIC_DRAW);
    // Normals
    glGenBuffers(1, &vbo->normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbo->normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_count*sizeof(Vec3), normals,
                 GL_STATIC_DRAW);
    // Textural coordinates
    glGenBuffers(1, &vbo->texturebuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbo->texturebuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_count*sizeof(Vec2), textures,
                 GL_STATIC_DRAW);
    // Indecies
    glGenBuffers(1, &vbo->elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo->elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count*sizeof(uint32_t),
                 indecies, GL_STATIC_DRAW);
}




// Class: VBO

/**
 * @brief Constructor
 */
VBO::VBO() {
    vertexArrayID = 0;
    vertexbuffer = 0;
    normalbuffer = 0;
    texturebuffer = 0;
    elementbuffer = 0;
    indexCount = 0;
}

/**
 * @brief Destructor
 */
VBO::~VBO() {
    if(vertexArrayID != 0) {
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteBuffers(1, &normalbuffer);
        glDeleteBuffers(1, &texturebuffer);
        glDeleteBuffers(1, &elementbuffer);
        glDeleteVertexArrays(1, &vertexArrayID);
    }
}

/**
 * @brief Move constructor
 * 
 * @param vbo Source
 */
VBO::VBO(VBO&& vbo) noexcept {
    vertexArrayID = std::exchange(vbo.vertexArrayID, 0);
    vertexbuffer = std::exchange(vbo.vertexbuffer, 0);
    normalbuffer = std::exchange(vbo.normalbuffer, 0);
    texturebuffer = std::exchange(vbo.texturebuffer, 0);
    elementbuffer = std::exchange(vbo.elementbuffer, 0);
    indexCount = std::exchange(vbo.indexCount, 0);
}

/**
 * @brief Move assignment
 * 
 * @param vbo Source
 */
VBO& VBO::operator=(VBO&& vbo) noexcept {
    vertexArrayID = std::exchange(vbo.vertexArrayID, 0);
    vertexbuffer = std::exchange(vbo.vertexbuffer, 0);
    normalbuffer = std::exchange(vbo.normalbuffer, 0);
    texturebuffer = std::exchange(vbo.texturebuffer, 0);
    elementbuffer = std::exchange(vbo.elementbuffer, 0);
    indexCount = std::exchange(vbo.indexCount, 0);
    return *this;
}

/**
 * @brief Draws the VBO using a shader program
 */
void VBO::draw() {
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,              // attribute
        3,              // size
        GL_FLOAT,       // type
        GL_FALSE,       // normalized?
        0,              // stride
        (void*)0        // array buffer offset
    );
    // 2nd attribute buffer : normals
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_TRUE,
        0,
        (void*)0
    );
    // 3nd attribute buffer : textures
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, texturebuffer);
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );
    
    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    
    // Draw the triangles !
    glDrawElements(
        GL_TRIANGLES,      // mode
        indexCount,        // count
        GL_UNSIGNED_SHORT, // type
        (void*)0           // element array buffer offset
    );
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

}}
