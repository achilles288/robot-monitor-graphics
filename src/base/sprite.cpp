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
#include "rmg/internal/sprite_load.hpp"
#include <cstdio>


namespace rmg {

/**
 * @brief Constructs a sprite object loading a sprite image
 * 
 * @param ctx Container context
 * @param img Image file (supports the same format Texture class does)
 */
Sprite2D::Sprite2D(Context* ctx, const char* img)
         :Sprite2D(ctx, img, Vec2())
{
    internal::SpriteLoad *load = (internal::SpriteLoad*) texLoad.getData();
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
Sprite2D::Sprite2D(Context* ctx, const char* img, const Vec2 &size)
         :Object2D(ctx)
{
    texture = new internal::SpriteTexture();
    texShareCount = new uint32_t;
    *texShareCount = 1;
    auto load = new internal::SpriteLoad(texture, img);
    texLoad = internal::Pending(load);
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
    texture = new internal::SpriteTexture();
    texShareCount = new uint32_t;
    *texShareCount = 1;
    auto load = new internal::SpriteLoad(texture, bmp);
    texLoad = internal::Pending(load);
    setSize(size);
    type2D = Object2DType::Sprite;
}

/**
 * @brief Destructor
 */
Sprite2D::~Sprite2D() {
    if(texture != nullptr) {
        (*texShareCount)--;
        if(*texShareCount == 0) {
            delete texture;
            delete texShareCount;
        }
    }
}

/**
 * @brief Copy constructor
 * 
 * @param obj Source object
 */
Sprite2D::Sprite2D(const Sprite2D& obj)
         :Object2D(obj)
{
    texture = obj.texture;
    texShareCount = obj.texShareCount;
    if(texShareCount != nullptr)
        (*texShareCount)++;
    texLoad = obj.texLoad;
}

/**
 * @brief Move constructor
 * 
 * @param obj Source object
 */
Sprite2D::Sprite2D(Sprite2D&& obj) noexcept
         :Object2D(obj)
{
    texture = std::exchange(obj.texture, nullptr);
    texShareCount = std::exchange(obj.texShareCount, nullptr);
    internal::Pending load;
    texLoad = std::exchange(obj.texLoad, load);
}
    
/**
 * @brief Copy assignment
 * 
 * @param obj Source object
 */
Sprite2D& Sprite2D::operator=(const Sprite2D& obj) {
    Sprite2D tmp = Sprite2D(obj);
    swap(tmp);
    return *this;
}

/**
 * @brief Move assignment
 * 
 * @param obj Source object
 */
Sprite2D& Sprite2D::operator=(Sprite2D&& obj) noexcept {
    Sprite2D tmp = std::move(obj);
    swap(tmp);
    return *this;
}

/**
 * @brief Swaps the values of member variables between two objects
 * 
 * @param x The other object
 */
void Sprite2D::swap(Sprite2D& x) noexcept {
    std::swap(texture, x.texture);
    std::swap(texShareCount, x.texShareCount);
    std::swap(texLoad, x.texLoad);
    Object2D::swap(x);
}

/**
 * @brief Gets the pointer to the texture
 * 
 * @return Pointer to the texture
 */
const internal::SpriteTexture *Sprite2D::getTexture() const {return texture; }


/**
 * @brief Gets the texture loader
 * 
 * @return Texture loader
 */
const internal::Pending& Sprite2D::getTextureLoad() const { return texLoad; }

}
