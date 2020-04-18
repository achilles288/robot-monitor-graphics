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

#include <rmg/object2d.hpp>

#include <string>


namespace rmg {

/**
 * @brief 2D sprite images for 2D games
 *
 * Easily manipulatable model. Display 2D graphics at lowest cost.
 * Make 2D games like Mario.
 */
class Sprite2D: public Object2D {
  public:
    /**
     * @brief Constructs a sprite object loading a sprite image
     * 
     * @param ctx Container context
     * @param img Image file (supports the same format Texture class does)
     */
    Sprite2D(Context* ctx, std::string img);
    
    /**
     * @brief Constructs a sprite object with a preloaded texture
     * 
     * @param ctx Container context
     * @param tex Loaded texture
     */
    Sprite2D(Context* ctx, Texture* tex);
    
    /**
     * @brief Constructs a sprite object loading a sprite image
     * 
     * @param ctx Container context
     * @param img Image file (supports the same format Texture class does)
     * @param size Sprite size
     */
    Sprite2D(Context* ctx, std::string img, Vec2 size);
    
    /**
     * @brief Constructs a sprite object with a preloaded texture
     * 
     * @param ctx Container context
     * @param tex Loaded texture
     * @param size Sprite size
     */
    Sprite2D(Context* ctx, Texture* tex, Vec2 size);
    
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
};

}

#endif
