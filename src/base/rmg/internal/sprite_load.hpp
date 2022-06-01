/**
 * @file sprite_load.hpp
 * @brief Manages the GPU resources for textures
 * 
 * @copyright Copyright (c) 2022 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_SPRITE_LOAD_H__
#define __RMG_SPRITE_LOAD_H__

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


#include "../bitmap.hpp"
#include "../color.hpp"
#include "../math/vec2.hpp"
#include "context_load.hpp"


namespace rmg {
namespace internal {

class SpriteTexture;


/**
 * @brief Maintains the image data before context startup
 * 
 * During the texture loading function, it translate the file to a chunk of
 * data and they are desired to be loaded into GPU for shader computations.
 * However this can't be done before the OpenGL context shows up.
 * So, this temporary storage class is made to maintain the data for a while.
 * before the context startup.
 * 
 * @see VBOLoad
 * @see TextureLoad
 */
class RMG_API SpriteLoad: public ContextLoad {
  private:
    SpriteTexture* texture;
    Bitmap bitmap;
    uint16_t width;
    uint16_t height;
    
  public:
    /**
     * @brief Constructs a pending object
     * 
     * @param tex Address to a Texture instance. This is to redirect 
     *            responses after loading.
     * @param f Path to texture file
     */
    SpriteLoad(SpriteTexture* tex, const char* f);
    
    /**
     * @brief Constructs a pending object
     * 
     * @param tex Address to a Texture instance. This is to redirect 
     *            responses after loading.
     * @param bmp Image data
     */
    SpriteLoad(SpriteTexture* tex, const Bitmap& bmp);
    
    /**
     * @brief Destructor
     */
    ~SpriteLoad();
    
    /**
     * @brief Loads the texture data to the GPU
     * 
     * Loads a chunk of image data into GPU for shader processing.
     * Also this pending object's load function assigns the resource
     * addresses to the related Texture instance.
     */
    void load() override;
    
    /**
     * @brief Gets the width of the image
     * 
     * @return Image width in pixels
     */
    uint16_t getWidth() const;
    
    /**
     * @brief Gets the height of the image
     * 
     * @return Image height in pixels
     */
    uint16_t getHeight() const;
};


/**
 * @brief To enhance the appearance of 2D/3D objects with image data
 */
class RMG_API SpriteTexture {
  private:
    uint32_t texture;
    
    friend class SpriteLoad;
    
  public:
    /**
     * @brief Default constructor
     */
    SpriteTexture();
    
    /**
     * @brief Destructor
     */
    virtual ~SpriteTexture();
    
    /**
     * @brief Copy constructor (deleted)
     * 
     * Copy constructor is not allowed to use since it contains a unique
     * pointer.
     * 
     * @param tex Source texture
     */
    SpriteTexture(const SpriteTexture& tex) = delete;
    
    /**
     * @brief Move constructor
     * 
     * @param tex Source texture
     */
    SpriteTexture(SpriteTexture&& tex) noexcept = default;
    
    /**
     * @brief Copy assignment (deleted)
     * 
     * Copy assignment is not allowed to use since it contains a unique
     * pointer.
     * 
     * @param tex Source texture
     */
    SpriteTexture& operator=(const SpriteTexture& tex) = delete;
    
    /**
     * @brief Move assignment
     * 
     * @param tex Source texture
     */
    SpriteTexture& operator=(SpriteTexture&& tex) noexcept = default;
    
    /**
     * @brief Binds the texture to process
     */
    void bind() const;
};

}}

#endif
