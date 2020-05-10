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

#include <vector>

#include <rmg/math/vec.hpp>
#include <rmg/internal/context_load.hpp>


namespace rmg {
namespace internal {

class VBO;


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
class VBOLoad: public ContextLoad {
  private:
    VBO* vbo;
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> text_coords;
    std::vector<uint16_t> indecies;
    
  public:
    /**
     * @brief Constructs a pending object
     * 
     * @param vbo Address to a VBO instance. This is to redirect 
     *            responses after loading.
     * @param vert Vertices
     * @param norm Normals
     * @param tex Texture coordinates
     * @param in Indecies
     */
    VBOLoad(VBO* vbo,
            const std::vector<Vec3> &vert,
            const std::vector<Vec3> &norm,
            const std::vector<Vec2> &tex,
            const std::vector<uint16_t> &in);
    
    /**
     * @brief Destructor
     */
    ~VBOLoad();
    
    /**
     * @brief Copy constructor
     * 
     * @param vbo Source
     */
    VBOLoad(const VBOLoad& vbo);
    
    /**
     * @brief Move constructor
     * 
     * @param vbo Source
     */
    VBOLoad(VBOLoad&& vbo) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param vbo Source
     */
    VBOLoad& operator=(const VBOLoad& vbo);
    
    /**
     * @brief Move assignment
     * 
     * @param vbo Source
     */
    VBOLoad& operator=(VBOLoad&& vbo) noexcept;
    
    /**
     * @brief Loads the array of VBOs to the GPU
     * 
     * Loads the arrays of vertices, normals, texture coordinate and indecies
     * which are created by model constructors (Cube3D, Model3D, .etc) into
     * GPU. Also this pending object's load function assigns the resource
     * addresses to the related VBO object.
     */
    void load() override;
};


/**
 * @brief Handles the GPU resource for drawing
 * 
 * Select a Shader, trigger the draw() function of this class and make
 * actual drawing by the GPU processing power. Multiple Object3D may use
 * the common instance for efficient GPU memory space.
 */
class VBO {
  private:
    uint32_t vertexArrayID;
    uint32_t vertexbuffer;
    uint32_t normalbuffer;
    uint32_t texturebuffer;
    uint32_t elementbuffer;
    uint32_t indexCount;
    
    friend class VBOLoad;
    
  public:
    /**
     * @brief Constructor
     */
    VBO();
    
    /**
     * @brief Destructor
     */
    ~VBO();
    
    /**
     * @brief Copy constructor (deleted)
     * 
     * Deleted since this class uses unique pointers to GPU resources and
     * to prevent improper usage.
     * 
     * @param vbo Source
     */
    VBO(const VBO& vbo) = delete;
    
    /**
     * @brief Move constructor
     * 
     * @param vbo Source
     */
    VBO(VBO&& vbo) noexcept;
    
    /**
     * @brief Copy assignment (deleted)
     * 
     * Deleted since this class uses unique pointers to GPU resources and
     * to prevent improper usage.
     * 
     * @param vbo Source
     */
    VBO& operator=(const VBO& vbo) = delete;
    
    /**
     * @brief Move assignment
     * 
     * @param vbo Source
     */
    VBO& operator=(VBO&& vbo) noexcept;
    
    /**
     * @brief Draws the VBO using a shader program
     */
    void draw();
};

}}

#endif
