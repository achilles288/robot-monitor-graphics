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


#include <string>

#include "object2d.hpp"
#include "internal/context_load.hpp"


namespace rmg {

class Bitmap;

namespace internal {

class SpriteTexture;

}


/**
 * @brief 2D sprite images for 2D games
 * 
 * Easily manipulatable model. Display 2D graphics at lowest cost.
 * Make 2D games like Mario.
 */
class RMG_API Sprite2D: public Object2D {
  private:
    internal::SpriteTexture* texture = nullptr;
    uint32_t* texShareCount = nullptr;
    internal::Pending texLoad;
    
  protected:
    /**
     * @brief Swaps the values of member variables between two objects
     * 
     * @param x The other object
     */
    void swap(Sprite2D& x) noexcept;
    
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
    Sprite2D(Context* ctx, const char* img);
    
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
    Sprite2D(Context* ctx, const char* img, const Vec2 &size);
    
    /**
     * @brief Constructs a sprite object from bitmap
     * 
     * @param ctx Conatiner context
     * @param bmp Sprite image
     * @param size Image size
     */
    Sprite2D(Context* ctx, const Bitmap &bmp, const Vec2 &size);
    
    /**
     * @brief Destructor
     */
    virtual ~Sprite2D();
    
    /**
     * @brief Copy constructor
     * 
     * @param obj Source object
     */
    Sprite2D(const Sprite2D& obj);
    
    /**
     * @brief Move constructor
     * 
     * @param obj Source object
     */
    Sprite2D(Sprite2D&& obj) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param obj Source object
     */
    Sprite2D& operator=(const Sprite2D& obj);
    
    /**
     * @brief Move assignment
     * 
     * @param obj Source object
     */
    Sprite2D& operator=(Sprite2D&& obj) noexcept;
    
    /**
     * @brief Gets the pointer to the texture
     * 
     * @return Pointer to the texture
     */
    const internal::SpriteTexture *getTexture() const;
    
    /**
     * @brief Gets the texture loader
     * 
     * @return Texture loader
     */
    const internal::Pending& getTextureLoad() const;
};

}

#endif
