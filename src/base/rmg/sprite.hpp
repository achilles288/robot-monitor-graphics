/**
 * @file sprite.hpp
 * @brief 2D sprite images for 2D games
 *
 * Easily manipulatable model. Display 2D graphics at lowest cost.
 * Make 2D games like Mario.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_SPRITE_H__
#define __RMG_SPRITE_H__

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


#include <memory>
#include <string>

#include "object2d.hpp"
#include "internal/context_load.hpp"


namespace rmg {

class Bitmap;

namespace internal {

class Texture;

}


/**
 * @brief 2D sprite images for 2D games
 *
 * Easily manipulatable model. Display 2D graphics at lowest cost.
 * Make 2D games like Mario.
 */
class RMG_API Sprite2D: public Object2D {
  private:
    std::shared_ptr<internal::Texture> texture;
    internal::ContextLoader::Pending texLoad;
    
  public:
    /**
     * @brief Default constructor
     */
    Sprite2D() = default;
    
    /**
     * @brief Constructs a sprite object loading a sprite image
     * 
     * @param ctx Container context
     * @param img Image file (supports the same format Texture class does)
     */
    Sprite2D(Context* ctx, const std::string &img);
    
    /**
     * @brief Constructs a sprite object from bitmap
     * 
     * @param ctx Conatiner context
     * @param bmp Sprite image
     */
    Sprite2D(Context* ctx, const Bitmap &bmp);
    
    /**
     * @brief Constructs a sprite object loading a sprite image
     * 
     * @param ctx Container context
     * @param img Image file (supports the same format Texture class does)
     * @param size Image size
     */
    Sprite2D(Context* ctx, const std::string &img, const Vec2 &size);
    
    /**
     * @brief Constructs a sprite object from bitmap
     * 
     * @param ctx Conatiner context
     * @param bmp Sprite image
     * @param size Image size
     */
    Sprite2D(Context* ctx, const Bitmap &bmp, const Vec2 &size);
    
    /**
     * @brief Gets the pointer to the texture
     * 
     * @return Pointer to the texture
     */
    const internal::Texture *getTexture() const;
    
    /**
     * @brief Gets the texture loader
     * 
     * @return Texture loader
     */
    const internal::ContextLoader::Pending& getTextureLoad() const;
};

}

#endif
