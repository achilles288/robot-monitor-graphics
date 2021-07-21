/**
 * @file sprite.cpp
 * @brief 2D sprite images for 2D games
 *
 * Easily manipulatable model. Display 2D graphics at lowest cost.
 * Make 2D games like Mario.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "rmg/sprite.hpp"

#include "rmg/bitmap.hpp"
#include "rmg/internal/texture_load.hpp"


namespace rmg {

/**
 * @brief Constructs a sprite object loading a sprite image
 * 
 * @param ctx Container context
 * @param img Image file (supports the same format Texture class does)
 * @param size Image size
 */
Sprite2D::Sprite2D(Context* ctx, const std::string &img, const Vec2 &size)
         :Object2D(ctx)
{
    texture = std::make_shared<internal::Texture>(internal::Texture());
    auto load = new internal::TextureLoad(texture.get(), img);
    load->setOptimize2D(true);
    texLoad = internal::ContextLoader::Pending(load);
    setSize(size);
    type2D = Object2DType::Sprite;
}

/**
 * @brief Constructs a sprite object from bitmap
 * 
 * @param ctx Conatiner context
 * @param bmp Sprite image
 * @param size Image size
 */
Sprite2D::Sprite2D(Context* ctx, const Bitmap &bmp, const Vec2 &size)
         :Object2D(ctx)
{
    texture = std::make_shared<internal::Texture>(internal::Texture());
    auto load = new internal::TextureLoad(texture.get(), bmp);
    load->setOptimize2D(true);
    texLoad = internal::ContextLoader::Pending(load);
    setSize(size);
    type2D = Object2DType::Sprite;
}

}
