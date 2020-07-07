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

#include "math/vec.hpp"


namespace rmg {

/**
 * @brief Structural build of a 3D model consisting of polygons
 */
class Mesh {
  private:
    void swap(Mesh& mesh) noexcept;
    
  protected:
    Vec3* vertices; ///< Coordinate in 3D space
    Vec3* normals; ///< Normal vector used in calculating reflections
    Vec2* texCoords; ///< Coordinate representing a portion of textural image
    uint64_t vertex_count; ///< Number of vertecies
    uint16_t* indecies; ///< Array of vertex indecies forming polygons
    uint64_t index_count; ///< Number of indecies
    
    /**
     * @brief Calculate the normal vectors for every vertex in the array
     */
    void buildNormals();
    
    /**
     * @brief Shuffles the arrays to reuse the duplicate vertecies
     */
    void buildIndecies();
    
  public:
    /**
     * @brief Default constructor
     */
    Mesh();
    
    /**
     * @brief Constructor from pointers of arrays
     * 
     * @param vert Vertex array
     * @param vcount Number of vertices
     */
    Mesh(Vec3* vert, uint64_t vcount);
    
    /**
     * @brief Constructor from pointers of arrays
     * 
     * @param vert Vertex array
     * @param tex Textural coordinate array
     * @param vcount Number of vertices
     */
    Mesh(Vec3* vert, Vec2* tex, uint64_t vcount);
    
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
    Mesh(Vec3* vert, Vec3* norm, Vec2* tex, uint64_t vcount,
         uint16_t* in, uint64_t icount);
    
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
};

}

#endif
