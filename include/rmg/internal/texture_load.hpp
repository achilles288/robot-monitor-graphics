/**
 * @file texture_load.hpp
 * @brief Manages the GPU resources for textures
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_TEXTURE_LOAD_H__
#define __RMG_TEXTURE_LOAD_H__

#include <vector>

#include "../bitmap.hpp"
#include "context_load.hpp"


namespace rmg {
namespace internal {

class Texture;


/**
 * @brief Maintains the image data before context startup
 * 
 * During the texture loading function, it translate the file to a chunk of
 * data and they are desired to be loaded into GPU for shader computations.
 * However this can't be done before the OpenGL context shows up.
 * So, this temporary storage class is made to maintain the data for a while.
 * before the context startup.
 * 
 * @see VBOLoadPending
 * @see FontLoadPending
 */
class TextureLoad: public ContextLoad {
  private:
    Texture* texture;
    Bitmap bitmap;
    
  public:
    /**
     * @brief Constructs a pending object
     * 
     * @param tex Address to a Texture instance. This is to redirect 
     *            responses after loading.
     * @param dat Data array
     * @param bmp Image data
     */
    TextureLoad(Texture* tex, const Bitmap& bmp);
    
    /**
     * @brief Destructor
     */
    ~TextureLoad();
    
    /**
     * @brief Copy constructor
     * 
     * @param tex Source
     */
    TextureLoad(const TextureLoad& tex);
    
    /**
     * @brief Move constructor
     * 
     * @param tex Source
     */
    TextureLoad(TextureLoad&& tex) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param tex Source
     */
    TextureLoad& operator=(const TextureLoad& tex);
    
    /**
     * @brief Move assignment
     * 
     * @param tex Source
     */
    TextureLoad& operator=(TextureLoad&& tex) noexcept;
    
    /**
     * @brief Loads the texture data to the GPU
     * 
     * Loads a chunk of image data into GPU for shader processing.
     * Also this pending object's load function assigns the resource
     * addresses to the related Texture instance.
     */
    void load() override;
};


/**
 * @brief To enhance the appearance of 2D/3D objects with image data
 */
class Texture {
  private:
    uint32_t textureID;
    uint8_t channel;
    
    friend class TextureLoad;
    
  public:
    /**
     * @brief Default constructor
     */
    Texture();
    
    /**
     * @brief Destructor
     */
    virtual ~Texture();
    
    /**
     * @brief Copy constructor (deleted)
     * 
     * Copy constructor is not allowed to use since it contains a unique
     * pointer.
     * 
     * @param tex Source texture
     */
    Texture(const Texture& tex) = delete;
    
    /**
     * @brief Move constructor
     * 
     * @param tex Source texture
     */
    Texture(Texture&& tex) noexcept;
    
    /**
     * @brief Copy assignment (deleted)
     * 
     * Copy assignment is not allowed to use since it contains a unique
     * pointer.
     * 
     * @param tex Source texture
     */
    Texture& operator=(const Texture& tex) = delete;
    
    /**
     * @brief Move assignment
     * 
     * @param tex Source texture
     */
    Texture& operator=(Texture&& tex) noexcept;
};

}}

#endif
