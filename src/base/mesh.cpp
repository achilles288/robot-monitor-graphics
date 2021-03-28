/**
 * @file mesh.cpp
 * @brief Structural build of a 3D model consisting of polygons
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "mesh.hpp"

#include <cstdlib>
#include <cstring>
#include <utility>

#include "assert.hpp"


namespace rmg {

/**
 * @brief Constructor from pointers of arrays
 * 
 * @param vert Vertex array
 * @param vcount Number of vertices
 * @param smooth Generate smooth surface normals
 */
Mesh::Mesh(const Vec3* vert, uint32_t vcount, bool smooth)
     :Mesh(vert, nullptr, vcount, smooth)
{}

/**
 * @brief Constructor from pointers of arrays
 * 
 * @param vert Vertex array
 * @param tex Textural coordinate array
 * @param vcount Number of vertices
 * @param smooth Generate smooth surface normals
 */
Mesh::Mesh(const Vec3* vert, const Vec2* tex, uint32_t vcount, bool smooth) {
    RMG_EXPECT(vcount % 3 == 0);
    #ifndef NDEBUG
    if(vcount % 3 != 0) return;
    #endif
    
    vertices = (Vec3*) malloc(sizeof(Vec3)*vcount);
    memcpy(vertices, vert, sizeof(Vec3)*vcount);
    vertex_count = vcount;
    indices = nullptr;
    index_count = 0;
    
    if(tex != nullptr) {
        texCoords = (Vec2*) malloc(sizeof(Vec2)*vcount);
        memcpy(texCoords, tex, sizeof(Vec2)*vcount);
    }
    else {
        texCoords = nullptr;
    }
    
    buildNormals(smooth);
    buildIndices();
}

/**
 * @brief Constructor from pointers of arrays
 * 
 * @param vert Vertex array
 * @param norm Normal array
 * @param tex Textural coordinate array
 * @param vcount Number of vertices
 */
Mesh::Mesh(const Vec3* vert, const Vec3* norm, const Vec2* tex,
           uint32_t vcount)
{
    RMG_EXPECT(vcount % 3 == 0);
    #ifndef NDEBUG
    if(vcount % 3 != 0) return;
    #endif
    
    vertices = (Vec3*) malloc(sizeof(Vec3)*vcount);
    memcpy(vertices, vert, sizeof(Vec3)*vcount);
    normals = (Vec3*) malloc(sizeof(Vec3)*vcount);
    memcpy(normals, norm, sizeof(Vec3)*vcount);
    vertex_count = vcount;
    
    if(tex != nullptr) {
        texCoords = (Vec2*) malloc(sizeof(Vec2)*vcount);
        memcpy(texCoords, tex, sizeof(Vec2)*vcount);
    }
    
    buildIndices();
}

/**
 * @brief Constructor from pointers of arrays
 * 
 * @param vert Vertex array
 * @param norm Normal array
 * @param tex Textural coordinate array (optional)
 * @param vcount Number of vertices
 * @param in Indices
 * @param icount Number of indices
 */
Mesh::Mesh(const Vec3* vert, const Vec3* norm, const Vec2* tex,
           uint32_t vcount, const uint32_t* in, uint32_t icount)
{
    RMG_EXPECT(icount % 3 == 0);
    #ifndef NDEBUG
    if(icount % 3 != 0) return;
    #endif
    
    vertices = (Vec3*) malloc(sizeof(Vec3)*vcount);
    memcpy(vertices, vert, sizeof(Vec3)*vcount);
    vertex_count = vcount;
    indices = (uint32_t*) malloc(sizeof(uint32_t)*icount);
    memcpy(indices, in, sizeof(uint32_t)*icount);
    index_count = icount;
    
    if(tex != nullptr) {
        texCoords = (Vec2*) malloc(sizeof(Vec2)*vcount);
        memcpy(texCoords, tex, sizeof(Vec2)*vcount);
    }
    
    if(norm != nullptr) {
        normals = (Vec3*) malloc(sizeof(Vec3)*vcount);
        memcpy(normals, norm, sizeof(Vec3)*vcount);
    }
    else {
        buildNormals();
        buildIndices();
    }
}

/**
 * @brief Destructor
 */
Mesh::~Mesh() {
    free(vertices);
    free(normals);
    free(texCoords);
    free(indices);
}

/**
 * @brief Copy constructor
 * 
 * @param mesh Source
 */
Mesh::Mesh(const Mesh& mesh) {
    vertex_count = mesh.vertex_count;
    index_count = mesh.index_count;
    
    if(mesh.vertices != nullptr) {
        vertices = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
        memcpy(vertices, mesh.vertices, sizeof(Vec3)*vertex_count);
    }
    
    if(mesh.normals != nullptr) {
        normals = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
        memcpy(normals, mesh.normals, sizeof(Vec3)*vertex_count);
    }
    
    if(mesh.texCoords != nullptr) {
        texCoords = (Vec2*) malloc(sizeof(Vec2)*vertex_count);
        memcpy(texCoords, mesh.texCoords, sizeof(Vec2)*vertex_count);
    }
    
    if(mesh.indices != nullptr) {
        indices = (uint32_t*) malloc(sizeof(uint32_t)*index_count);
        memcpy(indices, mesh.indices, sizeof(uint32_t)*index_count);
    }
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
    indices = std::exchange(mesh.indices, nullptr);
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
    std::swap(indices, mesh.indices);
}

/**
 * @brief Checks if the mesh is valid
 * 
 * @return True if the mesh is usable as VBO
 */
bool Mesh::isValid() const {
    if(vertices == nullptr)
        return false;
    if(normals == nullptr)
        return false;
    if(indices == nullptr)
        return false;
    if(index_count % 3 != 0)
        return false;
    return true;
}

/**
 * @brief Gets the number of vertices
 * 
 * @return Vertex count
 */
uint32_t Mesh::getVertexCount() const { return vertex_count; }

/**
 * @brief Gets the number of polygons
 * 
 * @return Number of triangles or quads constituting the model
 */
uint32_t Mesh::getPolygonCount() const {
    return index_count / 3;
}

}
