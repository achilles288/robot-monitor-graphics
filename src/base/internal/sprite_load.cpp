/**
 * @file sprite_load.cpp
 * @brief Manages the GPU resources for textures
 *
 * @copyright Copyright (c) 2022 Khant Kyaw Khaung
 *
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "../rmg/internal/sprite_load.hpp"

#include "shader_def.h"
#include "../rmg/internal/glcontext.hpp"


namespace rmg {
namespace internal {

// Class: SpriteLoad

/**
 * @brief Constructs a pending object
 * 
 * @param tex Address to a Texture instance. This is to redirect 
 *            responses after loading.
 * @param f Path to texture file, folder or zip
 */
SpriteLoad::SpriteLoad(SpriteTexture* tex, const std::string &f) {
    texture = tex;
    bitmap = Bitmap::loadFromFile(f);
    width = bitmap.getWidth();
    height = bitmap.getHeight();
}

/**
 * @brief Constructs a pending object
 * 
 * @param tex Address to a Texture instance. This is to redirect 
 *            responses after loading.
 * @param bmp Image data
 */
SpriteLoad::SpriteLoad(SpriteTexture* tex, const Bitmap& bmp) {
    texture = tex;
    bitmap = bmp;
    width = bmp.getWidth();
    height = bmp.getHeight();
}
    
/**
 * @brief Destructor
 */
SpriteLoad::~SpriteLoad() {}

/**
 * @brief Loads the texture data to the GPU
 * 
 * Loads a chunk of image data into GPU for shader processing.
 * Also this pending object's load function assigns the resource
 * addresses to the related Texture instance.
 */
void SpriteLoad::load() {
    if(bitmap.getPointer() == NULL)
        return;
    
    glGenTextures(1, &texture->texture);
    glBindTexture(GL_TEXTURE_2D, texture->texture);
    
    int channel = 0;
    if(bitmap.getChannel() == 1)
        channel = GL_RED;
    else if(bitmap.getChannel() == 3)
        channel = GL_RGB;
    else if(bitmap.getChannel() == 4)
        channel = GL_RGBA;
    else
        return;
    
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        channel,
        width,
        height,
        0,
        channel,
        GL_UNSIGNED_BYTE,
        bitmap.getPointer()
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glBindTexture(GL_TEXTURE_2D, 0);
}

/**
 * @brief Gets the width of the image
 * 
 * @return Image width in pixels
 */
uint16_t SpriteLoad::getWidth() const { return width; }

/**
 * @brief Gets the height of the image
 * 
 * @return Image height in pixels
 */
uint16_t SpriteLoad::getHeight() const { return height; }




// Class: Texture

/**
 * @brief Default constructor
 */
SpriteTexture::SpriteTexture() {
    texture = 0;
}

/**
 * @brief Destructor
 */
SpriteTexture::~SpriteTexture() {
    if(texture)
        glDeleteTextures(1, &texture);
}

/**
 * @brief Binds the texture to process
 */
void SpriteTexture::bind() const {
    if(texture) {
        glActiveTexture(_GL_TEXTURE_SPRITE);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}

}}
