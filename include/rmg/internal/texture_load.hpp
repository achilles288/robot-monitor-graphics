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

#include <rmg/math.h>

#include <vector>
#include <cstdint>


class rmg::Context;
class rmg::Texture;


namespace rmg {
namespace internal {

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
class TextureLoadPending {
  private:
    Texture* texture;
    std::vector<uint8_t> data;
    uint16_t width;
    uint16_t height;
    uint8_t channel;
    
  public:
    /**
     * Constructs a pending object
     * 
     * @param tex Address to a Texture instance. This is to redirect 
     *            responses after loading.
     * @param dat Data array
     * @param w Image width
     * @param h Image height
     * @param c Color channel
     */
    TextureLoadPending(Texture* tex, std::vector<uint8_t>& dat,
                       uint16_t w, uint16_t h, uint8_t c);
    
    /**
     * @brief Destructor
     */
    ~TextureLoadPending();
    
    /**
     * @brief Copy constructor
     * 
     * @param tex Source
     */
    TextureLoadPending(const TextureLoadPending& tex);
    
    /**
     * @brief Move constructor
     * 
     * @param tex Source
     */
    TextureLoadPending(TextureLoadPending&& tex) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param tex Source
     */
    TextureLoadPending& operator=(const TextureLoadPending& tex);
    
    /**
     * @brief Move assignment
     * 
     * @param tex Source
     */
    TextureLoadPending& operator=(TextureLoadPending&& tex) noexcept;
    
    /**
     * @brief Loads the texture data to the GPU
     * 
     * Loads a chunk of image data into GPU for shader processing.
     * Also this pending object's load function assigns the resource
     * addresses to the related Texture instance.
     */
    void load();
};

}}

#endif
