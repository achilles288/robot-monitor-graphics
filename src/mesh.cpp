/**
 * @file mesh.cpp
 * @brief Structural build of a 3D model consisting of polygons
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "rmg/mesh.hpp"

#include <cstdlib>
#include <utility>


namespace rmg {

/**
 * @brief Default constructor
 */
Mesh::Mesh() {
    vertices = NULL;
    normals = NULL;
    textures = NULL;
    vertex_count = 0;
    indecies = NULL;
    index_count = 0;
}

/**
 * @brief Constructor from pointers of arrays
 * 
 * @param vert Vertex array
 * @param tex Textural coordinate array (optional)
 * @param vcount Number of vertices
 */
Mesh::Mesh(Vec3* vert, Vec2* tex, uint64_t vcount) {
    vertices = (Vec3*) malloc(sizeof(Vec3)*vcount);
    memcpy(vertices, vert, sizeof(Vec3)*vcount);
    vertex_count = vcount;
    
    indecies = NULL;
    index_count = 0;
    
    normals = (Vec3*) malloc(sizeof(Vec3)*vcount);
    buildNormals();
    
    if(tex != NULL) {
        textures = (Vec2*) malloc(sizeof(Vec2)*vcount);
        memcpy(textures, tex, sizeof(Vec2)*vcount);
    }
    else {
        textures = NULL;
    }
    
    buildIndecies();
}

/**
 * @brief Constructor from pointers of arrays
 * 
 * @param vert Vertex array
 * @param norm Normal array
 * @param tex Textural coordinate array (optional)
 * @param vcount Number of vertices
 * @param in Indecies
 * @param icount Number of indecies
 */
Mesh::Mesh(Vec3* vert, Vec3* norm, Vec2* tex, uint64_t vcount,
           uint16_t* in, uint64_t icount)
{
    vertices = (Vec3*) malloc(sizeof(Vec3)*vcount);
    memcpy(vertices, vert, sizeof(Vec3)*vcount);
    vertex_count = vcount;
    
    normals = (Vec2*) malloc(sizeof(Vec3)*vcount);
    if(norm != NULL)
        memcpy(normals, norm, sizeof(Vec3)*vcount);
    else
        buildNormals();
    
    if(tex != NULL) {
        textures = (Vec2*) malloc(sizeof(Vec2)*vcount);
        memcpy(textures, tex, sizeof(Vec2)*vcount);
    }
    else {
        textures = NULL;
    }
    indecies = (uint16_t*) malloc(sizeof(uint16_t)*icount);
    memcpy(indecies, in, sizeof(uint16_t)*icount);
    index_count = icount;
}

/**
 * @brief Destructor
 */
Mesh::~Mesh() {
    free(vertices);
    free(normals);
    free(textures);
    free(indecies);
}

/**
 * @brief Copy constructor
 * 
 * @param mesh Source
 */
Mesh::Mesh(const Mesh& mesh) {
    vertex_count = mesh.vertex_count;
    index_count = mesh.index_count;
    vertices = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
    normals = (Vec3*) malloc(sizeof(Vec3)*vertex_count);;
    indecies = (uint16_t*) malloc(sizeof(uint16_t)*index_count);
    
    memcpy(vertices, mesh.vertices, sizeof(Vec3)*vertex_count);
    memcpy(normals, mesh.normals, sizeof(Vec3)*vertex_count);
    memcpy(indecies, mesh.indecies, sizeof(uint16_t)*index_count);
    
    if(mesh.textures != NULL) {
        textures = (Vec2*) malloc(sizeof(Vec2)*vertex_count)
        memcpy(textures, mesh.textures, sizeof(Vec2)*vertex_count);
    }
    else
        textures = NULL;
}

/**
 * @brief Move constructor
 * 
 * @param mesh Source
 */
Mesh::Mesh(Mesh&& mesh) noexcept {
    vertecies = std::exchange(mesh.vertecies, nullptr);
    normals = std::exchange(mesh.normals, nullptr);
    textures = std::exchange(mesh.textures, nullptr);
    vertex_count = std::exchange(mesh.vertex_count, 0);
    indecies = std::exchange(mesh.indecies, nullptr);
    index_count = std::exchange(mesh.index_count, 0);
}

/**
 * @brief Copy assignment
 * 
 * @param mesh Source
 */
Mesh& Mesh::operator=(const Mesh& mesh) {
    vertex_count = mesh.vertex_count;
    index_count = mesh.index_count;
    vertices = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
    normals = (Vec3*) malloc(sizeof(Vec3)*vertex_count);;
    indecies = (uint16_t*) malloc(sizeof(uint16_t)*index_count);
    
    memcpy(vertices, mesh.vertices, sizeof(Vec3)*vertex_count);
    memcpy(normals, mesh.normals, sizeof(Vec3)*vertex_count);
    memcpy(indecies, mesh.indecies, sizeof(uint16_t)*index_count);
    
    if(mesh.textures != NULL) {
        textures = (Vec2*) malloc(sizeof(Vec2)*vertex_count)
        memcpy(textures, mesh.textures, sizeof(Vec2)*vertex_count);
    }
    else
        textures = NULL;
    
    return *this;
}

/**
 * @brief Move assignment
 * 
 * @param mesh Source
 */
Mesh& Mesh::operator=(Mesh&& mesh) noexcept {
    vertecies = std::exchange(mesh.vertecies, nullptr);
    normals = std::exchange(mesh.normals, nullptr);
    textures = std::exchange(mesh.textures, nullptr);
    vertex_count = std::exchange(mesh.vertex_count, 0);
    indecies = std::exchange(mesh.indecies, nullptr);
    index_count = std::exchange(mesh.index_count, 0);
}

/**
 * @brief Calculate the normal vectors for every vertex in the array
 */
void Mesh::Mesh buildNormals() {
    
}

/**
 * @brief Shuffles the arrays to reuse the duplicate vertecies
 */
void Mesh::Mesh buildIndecies() {
    
}

}
