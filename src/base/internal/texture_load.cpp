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
TextureLoad::TextureLoad(Texture* tex, const std::string &f) {
    texture = tex;
    basecolor = Bitmap::loadFromFile(f);
    heightmap = Bitmap();
    normalmap = Bitmap();
    mrao = Bitmap();
    emissivity = Bitmap();
    optimize2d = false;
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
    optimize2d = false;
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
    optimize2d = false;
}
    
/**
 * @brief Destructor
 */
TextureLoad::~TextureLoad() {}

/**
 * @brief Sets whether to optimize the texture for 2D graphics
 * 
 * In drawing 2D sprites, no concept about object distance from the camera is
 * included and hence, mipmap generation is to be skipped.
 * 
 * @param b True to optimize the texture for 2D graphics
 */
void TextureLoad::setOptimize2D(bool b) { optimize2d = true; }

/**
 * @brief Loads the texture data to the GPU
 * 
 * Loads a chunk of image data into GPU for shader processing.
 * Also this pending object's load function assigns the resource
 * addresses to the related Texture instance.
 */
void TextureLoad::load() {
    if(optimize2d)
        loadOptimize2D();
    else
        loadDefault();
}

void TextureLoad::loadDefault() {
    uint16_t width = 0;
    uint16_t height = 0;
    if(basecolor.getPointer() != NULL) {
        width = basecolor.getWidth();
        height = basecolor.getHeight();
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

void TextureLoad::loadOptimize2D() {
    if(basecolor.getPointer() == NULL)
        return;
    
    glGenTextures(1, &texture->basecolor);
    glBindTexture(GL_TEXTURE_2D, texture->basecolor);
    
    int channel = 0;
    if(basecolor.getChannel() == 3)
        channel = GL_RGB;
    else if(basecolor.getChannel() == 4)
        channel = GL_RGBA;
    else
        return;
    
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        channel,
        basecolor.getWidth(),
        basecolor.getHeight(),
        0,
        channel,
        GL_UNSIGNED_BYTE,
        basecolor.getPointer()
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glBindTexture(GL_TEXTURE_2D, 0);
}




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
    width = 1.0f;
    height = 1.0f;
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
    width = s;
    height = s;
}

/**
 * @brief Gets the physical dimensions of the texture
 * 
 * @param w Texture width
 * @param h Texture height
 */
void Texture::setSize(float w, float h) {
    width = w;
    height = h;
}

/**
 * @brief Gets the physical dimension of the texture
 * 
 * @return Texture width
 */
float Texture::getWidth() const { return width; }

/**
 * @brief Gets the physical dimension of the texture
 * 
 * @return Texture height
 */
float Texture::getHeight() const { return height; }

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

}}
