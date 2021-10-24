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
 */
Sprite2D::Sprite2D(Context* ctx, const std::string &img)
         :Sprite2D(ctx, img, Vec2())
{
    internal::TextureLoad *load = (internal::TextureLoad*) texLoad.getData();
    setSize(load->getWidth(), load->getHeight());
}

/**
 * @brief Constructs a sprite object from bitmap
 * 
 * @param ctx Conatiner context
 * @param bmp Sprite image
 * @param size Image size
 */
Sprite2D::Sprite2D(Context* ctx, const Bitmap &bmp)
         :Sprite2D(ctx, bmp, Vec2())
{
    setSize(bmp.getWidth(), bmp.getHeight());
}

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

/**
 * @brief Gets the pointer to the texture
 * 
 * @return Pointer to the texture
 */
const internal::Texture *Sprite2D::getTexture() const {return texture.get(); }


using Pending = internal::ContextLoader::Pending;

/**
 * @brief Gets the texture loader
 * 
 * @return Texture loader
 */
const Pending& Sprite2D::getTextureLoad() const { return texLoad; }

}
