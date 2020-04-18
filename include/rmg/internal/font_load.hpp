/**
 * @file font_load.hpp
 * @brief Manages the GPU resources for fonts
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_FONT_LOAD_H__
#define __RMG_FONT_LOAD_H__

#include <rmg/math.h>

#include <vector>
#include <cstdint>


class rmg::Context;
class rmg::Font;


namespace rmg {
namespace internal {

/**
 * @brief Maintains the image data before context startup
 * 
 * During the font loading function, it translate the file to a chunk of
 * data and they are desired to be loaded into GPU for shader computations.
 * However this can't be done before the OpenGL context shows up.
 * So, this temporary storage class is made to maintain the data for a while.
 * before the context startup.
 * 
 * @see VBOLoadPending
 * @see TextureLoadPending
 */
class FontLoadPending {
  private:
    Font* font;
    std::vector<uint8_t> data;
    
  public:
    /**
     * Constructs a pending object
     * 
     * @param ft Address to a Font instance. This is to redirect 
     *           responses after loading.
     * @param dat Data array
     */
    FontLoadPending(Font* ft, std::vector<uint8_t>& dat);
    
    /**
     * @brief Destructor
     */
    ~FontLoadPending();
    
    /**
     * @brief Copy constructor
     * 
     * @param ft Source
     */
    FontLoadPending(const FontLoadPending& ft);
    
    /**
     * @brief Move constructor
     * 
     * @param ft Source
     */
    FontLoadPending(FontLoadPending&& ft) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param ft Source
     */
    FontLoadPending& operator=(const FontLoadPending& ft);
    
    /**
     * @brief Move assignment
     * 
     * @param ft Source
     */
    FontLoadPending& operator=(FontLoadPending&& ft) noexcept;
    
    /**
     * @brief Loads the font data to the GPU
     * 
     * Loads a chunk of font data into GPU for shader processing.
     * Also this pending object's load function assigns the resource
     * addresses to the related Font instance.
     */
    void load();
};

}}

#endif
