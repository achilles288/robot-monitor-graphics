/**
 * @file mesh.hpp
 * @brief Structural build of a 3D model consisting of polygons
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_MESH_H__
#define __RMG_MESH_H__

#ifndef RMG_API
#ifdef _WIN32
#ifdef RMG_EXPORT
#define RMG_API __declspec(dllexport)
#else
#define RMG_API __declspec(dllimport)
#endif
#else
#define RMG_API
#endif
#endif


#include "math/vec.hpp"


namespace rmg {

/**
 * @brief Structural build of a 3D model consisting of polygons
 */
class RMG_API Mesh {
  private:
    void swap(Mesh& mesh) noexcept;
    
    void buildNormals(bool smooth=true);
    void buildNormals1();
    void buildNormals2();
    
    void removeIndices();
    
    void buildIndices();
    void buildIndices1();
    void buildIndices2();
    
  protected:
    Vec3* vertices = nullptr; ///< Coordinate in 3D space
    Vec3* normals = nullptr; ///< Normal vector used in calculating reflections
    Vec2* texCoords = nullptr; ///< Point of textural image to map
    uint32_t vertex_count = 0; ///< Number of vertecies
    uint32_t* indices = nullptr; ///< Array of vertex indecies forming polygons
    uint32_t index_count = 0; ///< Number of indecies
    
  public:
    /**
     * @brief Default constructor
     */
    Mesh() = default;
    
    /**
     * @brief Constructor from pointers of arrays
     * 
     * @param vert Vertex array
     * @param vcount Number of vertices
     * @param smooth Generate smooth surface normals
     */
    Mesh(const Vec3* vert, uint32_t vcount, bool smooth=true);
    
    /**
     * @brief Constructor from pointers of arrays
     * 
     * @param vert Vertex array
     * @param tex Textural coordinate array
     * @param vcount Number of vertices
     * @param smooth Generate smooth surface normals
     */
    Mesh(const Vec3* vert, const Vec2* tex, uint32_t vcount, bool smooth=true);
    
    /**
     * @brief Constructor from pointers of arrays
     * 
     * @param vert Vertex array
     * @param norm Normal array
     * @param tex Textural coordinate array
     * @param vcount Number of vertices
     */
    Mesh(const Vec3* vert, const Vec3* norm, const Vec2* tex, uint32_t vcount);
    
    /**
     * @brief Constructor from pointers of arrays
     * 
     * @param vert Vertex array
     * @param norm Normal array
     * @param tex Textural coordinate array
     * @param vcount Number of vertices
     * @param in Indecies
     * @param icount Number of indecies
     */
    Mesh(const Vec3* vert, const Vec3* norm, const Vec2* tex, uint32_t vcount,
         const uint32_t* in, uint32_t icount);
    
    /**
     * @brief Destructor
     */
    virtual ~Mesh();
    
    /**
     * @brief Copy constructor
     * 
     * @param mesh Source
     */
    Mesh(const Mesh& mesh);
    
    /**
     * @brief Move constructor
     * 
     * @param mesh Source
     */
    Mesh(Mesh&& mesh) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param mesh Source
     */
    Mesh& operator=(const Mesh& mesh);
    
    /**
     * @brief Move assignment
     * 
     * @param mesh Source
     */
    Mesh& operator=(Mesh&& mesh) noexcept;
    
    /**
     * @brief Checks if the mesh is valid
     * 
     * @return True if the mesh is usable as VBO
     */
    bool isValid() const;
    
    /**
     * @brief Gets the number of vertices
     * 
     * @return Vertex count
     */
    uint32_t getVertexCount() const;
    
    /**
     * @brief Gets the number of polygons
     * 
     * @return Number of triangles or quads constituting the model
     */
    uint32_t getPolygonCount() const;
};

}

#endif
