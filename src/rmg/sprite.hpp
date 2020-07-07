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

#include <memory>
#include <string>

#include "object2d.hpp"
#include "internal/context_load.hpp"


namespace rmg {

class Bitmap;

namespace internal {

class SpriteShader;
class Texture;

}


/**
 * @brief 2D sprite images for 2D games
 *
 * Easily manipulatable model. Display 2D graphics at lowest cost.
 * Make 2D games like Mario.
 */
class Sprite2D: public Object2D {
  private:
    std::shared_ptr<internal::Texture> texture;
    internal::ContextLoader::Pending texLoad;
    
    friend class internal::SpriteShader;
    
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
     * @param size Image size
     */
    Sprite2D(Context* ctx, const std::string &img, const Vec2 &size=Vec2());
    
    /**
     * @brief Constructs a sprite object from bitmap
     * 
     * @param ctx Conatiner context
     * @param bmp Sprite image
     * @param size Image size
     */
    Sprite2D(Context* ctx, const Bitmap &bmp, const Vec2 &size=Vec2());
};

}

#endif
