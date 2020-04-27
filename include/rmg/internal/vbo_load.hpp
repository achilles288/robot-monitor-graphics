/**
 * @file vbo_load.hpp
 * @brief Manages the GPU resources mainly for 3D objects
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_VBO_LOAD_H__
#define __RMG_VBO_LOAD_H__

#include <rmg/math.h>

#include <vector>
#include <cstdint>


class rmg::internal::VBOLoad;


namespace rmg {
namespace internal {

/**
 * @brief Maintains the array of VBOs before context startup
 * 
 * During construction of 3D objects, they generate VBOs for polygons that
 * compose nice looking graphics. The generated arrays includes vertices,
 * normals, texture coordinates, indecies and they are desired to be loaded
 * into GPU for shader processing. However this can't be done before the
 * OpenGL context shows up. So, this temporary storage class is made to
 * maintain the data for a while before the context startup.
 * 
 * @see TextureLoadPending
 * @see FontLoadPending
 */
class VBOLoadPending {
  private:
    VBOLoad* vboLoad;
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> text_coords;
    std::vector<uint16_t> indecies;
    
  public:
    /**
     * @brief Constructs a pending object
     * 
     * @param vbo Address to a VBOLoad instance. This is to redirect 
     *            responses after loading.
     * @param vert Vertices
     * @param norm Normals
     * @param tex Texture coordinates
     * @param in Indecies
     */
    VBOLoadPending(VBOLoad* vbo,
                   const std::vector<Vec3> &vert,
                   const std::vector<Vec3> &norm,
                   const std::vector<Vec2> &tex,
                   const std::vector<uint16_t> &in);
    
    /**
     * @brief Destructor
     */
    ~VBOLoadPending();
    
    /**
     * @brief Copy constructor
     * 
     * @param vbo Source
     */
    VBOLoadPending(const VBOLoadPending& vbo);
    
    /**
     * @brief Move constructor
     * 
     * @param vbo Source
     */
    VBOLoadPending(VBOLoadPending&& vbo) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param vbo Source
     */
    VBOLoadPending& operator=(const VBOLoadPending& vbo);
    
    /**
     * @brief Move assignment
     * 
     * @param vbo Source
     */
    VBOLoadPending& operator=(VBOLoadPending&& vbo) noexcept;
    
    /**
     * @brief Loads the array of VBOs to the GPU
     * 
     * Loads the arrays of vertices, normals, texture coordinate and indecies
     * which are created by model constructors (Cube3D, Model3D, .etc) into
     * GPU. Also this pending object's load function assigns the resource
     * addresses to the related VBOLoad object.
     */
    void load();
};


/**
 * @brief Handles the GPU resource for drawing
 * 
 * Select a Shader, trigger the draw() function of this class and make
 * actual drawing by the GPU processing power. Multiple Object3D may use
 * the common instance for efficient GPU memory space.
 */
class VBOLoad {
  private:
    uint32_t vertexArrayID;
    uint32_t vertexbuffer;
    uint32_t normalbuffer;
    uint32_t texturebuffer;
    uint32_t elementbuffer;
    uint32_t indexCount;
    
    friend class VBOLoadPending
    
  public:
    /**
     * @brief Constructor
     */
    VBOLoad();
    
    /**
     * @brief Destructor
     */
    ~VBOLoad();
    
    /**
     * @brief Copy constructor (deleted)
     * 
     * Deleted since this class uses unique pointers to GPU resources and
     * to prevent improper usage.
     * 
     * @param vbo Source
     */
    VBOLoad(const VBOLoad& vbo) = delete;
    
    /**
     * @brief Move constructor
     * 
     * @param vbo Source
     */
    VBOLoad(VBOLoad&& vbo) noexcept;
    
    /**
     * @brief Copy assignment (deleted)
     * 
     * Deleted since this class uses unique pointers to GPU resources and
     * to prevent improper usage.
     * 
     * @param vbo Source
     */
    VBOLoad& operator=(const VBOLoad& vbo) = delete;
    
    /**
     * @brief Move assignment
     * 
     * @param vbo Source
     */
    VBOLoad& operator=(VBOLoad&& vbo) noexcept;
    
    /**
     * @brief Draws the VBO using a shader program
     */
    void draw();
};

}}

#endif
