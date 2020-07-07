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
#include <cstring>
#include <utility>


namespace rmg {

/**
 * @brief Default constructor
 */
Mesh::Mesh() {
    vertices = nullptr;
    normals = nullptr;
    texCoords = nullptr;
    vertex_count = 0;
    indecies = nullptr;
    index_count = 0;
}

/**
 * @brief Constructor from pointers of arrays
 * 
 * @param vert Vertex array
 * @param vcount Number of vertices
 */
Mesh::Mesh(Vec3* vert, uint64_t vcount)
     :Mesh(vert, nullptr, vcount)
{}

/**
 * @brief Constructor from pointers of arrays
 * 
 * @param vert Vertex array
 * @param tex Textural coordinate array
 * @param vcount Number of vertices
 */
Mesh::Mesh(Vec3* vert, Vec2* tex, uint64_t vcount) {
    vertices = (Vec3*) malloc(sizeof(Vec3)*vcount);
    memcpy(vertices, vert, sizeof(Vec3)*vcount);
    vertex_count = vcount;
    
    indecies = nullptr;
    index_count = 0;
    
    normals = (Vec3*) malloc(sizeof(Vec3)*vcount);
    buildNormals();
    
    if(tex != nullptr) {
        texCoords = (Vec2*) malloc(sizeof(Vec2)*vcount);
        memcpy(texCoords, tex, sizeof(Vec2)*vcount);
    }
    else {
        texCoords = nullptr;
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
    
    normals = (Vec3*) malloc(sizeof(Vec3)*vcount);
    if(norm != nullptr)
        memcpy(normals, norm, sizeof(Vec3)*vcount);
    else
        buildNormals();
    
    if(tex != nullptr) {
        texCoords = (Vec2*) malloc(sizeof(Vec2)*vcount);
        memcpy(texCoords, tex, sizeof(Vec2)*vcount);
    }
    else {
        texCoords = nullptr;
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
    free(texCoords);
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
    
    if(mesh.texCoords != nullptr) {
        texCoords = (Vec2*) malloc(sizeof(Vec2)*vertex_count);
        memcpy(texCoords, mesh.texCoords, sizeof(Vec2)*vertex_count);
    }
    else
        texCoords = nullptr;
}

/**
 * @brief Move constructor
 * 
 * @param mesh Source
 */
Mesh::Mesh(Mesh&& mesh) noexcept {
    vertices = std::exchange(mesh.vertices, nullptr);
    normals = std::exchange(mesh.normals, nullptr);
    texCoords = std::exchange(mesh.texCoords, nullptr);
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
    Mesh tmp = Mesh(mesh);
    swap(tmp);
    return *this;
}

/**
 * @brief Move assignment
 * 
 * @param mesh Source
 */
Mesh& Mesh::operator=(Mesh&& mesh) noexcept {
    Mesh tmp = std::move(mesh);
    swap(tmp);
    return *this;
}

void Mesh::swap(Mesh& mesh) noexcept {
    std::swap(vertex_count, mesh.vertex_count);
    std::swap(index_count, mesh.index_count);
    std::swap(vertices, mesh.vertices);
    std::swap(normals, mesh.normals);
    std::swap(texCoords, mesh.texCoords);
    std::swap(indecies, mesh.indecies);
}

/**
 * @brief Calculate the normal vectors for every vertex in the array
 */
void Mesh::buildNormals() {
    
}

/**
 * @brief Shuffles the arrays to reuse the duplicate vertices
 */
void Mesh::buildIndecies() {
    
}

}
