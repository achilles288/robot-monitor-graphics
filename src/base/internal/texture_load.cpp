/**
 * @file texture_load.cpp
 * @brief Manages the GPU resources for textures
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 *
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "../rmg/internal/texture_load.hpp"

#include "shader_def.h"
#include "../rmg/internal/glcontext.hpp"


namespace rmg {
namespace internal {

// Class: TextureLoad

/**
 * @brief Constructs a pending object
 * 
 * @param tex Address to a Texture instance. This is to redirect 
 *            responses after loading.
 * @param f Path to texture file, folder or zip
 */
TextureLoad::TextureLoad(Texture* tex, const char* f) {
    texture = tex;
    basecolor = Bitmap::loadFromFile(f);
    heightmap = Bitmap();
    normalmap = Bitmap();
    mrao = Bitmap();
    emissivity = Bitmap();
    width = basecolor.getWidth();
    height = basecolor.getHeight();
}

/**
 * @brief Constructs a pending object
 * 
 * @param tex Address to a Texture instance. This is to redirect 
 *            responses after loading.
 * @param bmp Image data
 */
TextureLoad::TextureLoad(Texture* tex, const Bitmap& bmp) {
    texture = tex;
    basecolor = bmp;
    heightmap = Bitmap();
    normalmap = Bitmap();
    mrao = Bitmap();
    emissivity = Bitmap();
    width = bmp.getWidth();
    height = bmp.getHeight();
}

/**
 * @brief Constructs a pending object
 * 
 * @param tex Address to a Texture instance. This is to redirect 
 *            responses after loading.
 * @param base Base image
 * @param h Height mapping
 * @param norm Normal mapping
 * @param m Metallic, rough, ambient occulation
 * @param e Emissivity
 */
TextureLoad::TextureLoad(Texture* tex, const Bitmap& base, const Bitmap& h,
                         const Bitmap& norm, const Bitmap& m, const Bitmap& e)
{
    texture = tex;
    basecolor = base;
    heightmap = h;
    normalmap = norm;
    mrao = m;
    emissivity = e;
    width = base.getWidth();
    height = base.getHeight();
}
    
/**
 * @brief Destructor
 */
TextureLoad::~TextureLoad() {}

/**
 * @brief Loads the texture data to the GPU
 * 
 * Loads a chunk of image data into GPU for shader processing.
 * Also this pending object's load function assigns the resource
 * addresses to the related Texture instance.
 */
void TextureLoad::load() {
    if(basecolor.getPointer() != NULL) {
        glGenTextures(1, &texture->basecolor);
        glBindTexture(GL_TEXTURE_2D, texture->basecolor);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            width,
            height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            basecolor.getPointer()
        );
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

/**
 * @brief Gets the width of the image
 * 
 * @return Image width in pixels
 */
uint16_t TextureLoad::getWidth() const { return width; }

/**
 * @brief Gets the height of the image
 * 
 * @return Image height in pixels
 */
uint16_t TextureLoad::getHeight() const { return height; }




// Class: Texture

/**
 * @brief Default constructor
 */
Texture::Texture() {
    basecolor = 0;
    heightMap = 0;
    normalMap = 0;
    mraoMap = 0;
    opacity = 0;
    emissivity = 0;
    size.x = 1.0f;
    size.y = 1.0f;
    color = Color(1.0f, 1.0f, 1.0f);
    metalness = 0.0f;
    roughness = 0.6f;
    ambientOcculation = 0.6f;
    depth = 0.0f;
}

/**
 * @brief Destructor
 */
Texture::~Texture() {
    if(basecolor)
        glDeleteTextures(1, &basecolor);
    if(heightMap)
        glDeleteTextures(1, &heightMap);
    if(normalMap)
        glDeleteTextures(1, &normalMap);
    if(mraoMap)
        glDeleteTextures(1, &mraoMap);
    if(opacity)
        glDeleteTextures(1, &opacity);
    if(emissivity)
        glDeleteTextures(1, &emissivity);
}

/**
 * @brief Gets the physical dimensions of the texture
 * 
 * @param s Texture length
 */
void Texture::setSize(float s) {
    size.x = s;
    size.y = s;
}

/**
 * @brief Gets the physical dimensions of the texture
 * 
 * @param w Texture width
 * @param h Texture height
 */
void Texture::setSize(float w, float h) {
    size.x = w;
    size.y = h;
}

/**
 * @brief Gets the physical dimension of the texture
 * 
 * @return Texture width and height
 */
Vec2 Texture::getSize() const { return size; }

/**
 * @brief Sets material color
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 */
void Texture::setColor(float r, float g, float b) {
    color.red = r;
    color.green = g;
    color.blue = b;
    color.alpha = 1.0f;
}

/**
 * @brief Sets material color
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 * @param a Alpha
 */
void Texture::setColor(float r, float g, float b, float a) {
    color.red = r;
    color.green = g;
    color.blue = b;
    color.alpha = a;
}

/**
 * @brief Sets material color
 * 
 * @param col RGBA color
 */
void Texture::setColor(const Color &col) { color = col; }

/**
 * @brief Gets material color
 * 
 * @return RGBA color
 */
Color Texture::getColor() const { return color; }

/**
 * @brief Sets the metalness coefficient of the texture
 * 
 * @param m Metalness coefficient
 */
void Texture::setMetalness(float m) { metalness = m; }

/**
 * @brief Gets the metalness coefficient of the texturey.
 * 
 * @return Metalness coefficient
 */
float Texture::getMetalness() const { return metalness; }

/**
 * @brief Sets the roughness coefficient of the texture.
 * 
 * @param r Roughness coefficient
 */
void Texture::setRoughness(float r) { roughness = r; }

/**
 * @brief Gets the roughness coefficient of the texture
 * 
 * @return Roughness coefficient
 */
float Texture::getRoughness() const { return roughness; }

/**
 * @brief Sets the ambient occulation of the texture.
 * 
 * @param ao Ambient occulation
 */
void Texture::setAmbientOcculation(float ao) { ambientOcculation = ao; }

/**
 * @brief Gets the ambient occulation of the texture
 * 
 * @return Ambient occulation
 */
float Texture::getAmbientOcculation() const { return ambientOcculation; }

/**
 * @brief Sets the maximum unit for height mapping
 */
void Texture::setDepth(float d) { depth = d; }
 
/**
 * @brief Gets the maximum unit for height mapping
 */
float Texture::getDepth() const { return depth; }

/**
 * @brief Binds the texture to process
 */
void Texture::bind() const {
    if(basecolor) {
        glActiveTexture(_GL_TEXTURE_BASE);
        glBindTexture(GL_TEXTURE_2D, basecolor);
    }
}

}}
