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


#include "../mesh.hpp"
#include "context_load.hpp"


namespace rmg {
namespace internal {

class VBO;


/**
 * @brief Options to render a VBO
 */
enum class VBOMode {
    None,
    Default,
    Textured
};


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
 * @see TextureLoad
 * @see SpriteLoad
 */
class RMG_API VBOLoad: public ContextLoad, public Mesh {
  private:
    VBO* vbo;
    
    void setAttributePointers();
    
  public:
    /**
     * @brief Constructs a pending object
     * 
     * @param vbo Address to a VBO instance. This is to redirect 
     *            responses after loading.
     * @param mesh Mesh
     */
    VBOLoad(VBO* vbo, const Mesh& mesh);
    
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
class RMG_API VBO {
  private:
    uint32_t vertexArrayID = 0;
    uint32_t vertexbuffer = 0;
    uint32_t normalbuffer = 0;
    uint32_t texturebuffer = 0;
    uint32_t elementbuffer = 0;
    uint32_t indexCount = 0;
    VBOMode mode = VBOMode::None;
    
    friend class VBOLoad;
    
  public:
    /**
     * @brief Constructor
     */
    VBO() = default;
    
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
    VBO(VBO&& vbo) noexcept = default;
    
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
    VBO& operator=(VBO&& vbo) noexcept = default;
    
    /**
     * @brief Gets the mode of VBO rendering
     */
    VBOMode getMode() const;
    
    /**
     * @brief Draws the VBO using a shader program
     */
    void draw() const;
};

}}

#endif
