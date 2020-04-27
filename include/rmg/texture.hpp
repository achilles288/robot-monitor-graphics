/**
 * @file texture.hpp
 * @brief To enhance the appearance of 2D/3D objects with image data
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_TEXTURE_H__
#define __RMG_TEXTURE_H__

#include <cstdint>
#include <string>


class rmg::Context;
class rmg::internal::TextureLoadPending;


namespace rmg {

/**
 * @brief To enhance the appearance of 2D/3D objects with image data
 */
class Texture {
  private:
    uint32_t id;
    uint32_t loadID;
    Context* context;
    
    friend class internal::TextureLoadPending;
    
    static uint64_t lastID;
    static uint64_t generateID();
    
  public:
    /**
     * @brief Constructor loads an image from file
     * 
     * @param ctx Conatiner context
     * @param f Path to image file (.png)
     */
    Texture(Context* ctx, const std::string &f);
    
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
    
    /**
     * @brief Gets texture ID
     * 
     * @return Texture ID
     */
    uint32_t getID();
    
    /**
     * @brief Gets the container context
     * 
     * @return Container context
     */
    Context* getContext();
};

}

#endif
