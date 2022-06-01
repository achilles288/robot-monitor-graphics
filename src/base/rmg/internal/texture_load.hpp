/**
 * @file texture_load.hpp
 * @brief Manages the GPU resources for textures
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_TEXTURE_LOAD_H__
#define __RMG_TEXTURE_LOAD_H__

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


#include "../bitmap.hpp"
#include "../color.hpp"
#include "../math/vec2.hpp"
#include "context_load.hpp"


namespace rmg {
namespace internal {

class Texture;


/**
 * @brief Maintains the image data before context startup
 * 
 * During the texture loading function, it translate the file to a chunk of
 * data and they are desired to be loaded into GPU for shader computations.
 * However this can't be done before the OpenGL context shows up.
 * So, this temporary storage class is made to maintain the data for a while.
 * before the context startup.
 * 
 * @see VBOLoad
 * @see SpriteLoad
 */
class RMG_API TextureLoad: public ContextLoad {
  private:
    Texture* texture;
    Bitmap basecolor;
    Bitmap heightmap;
    Bitmap normalmap;
    Bitmap mrao;
    Bitmap emissivity;
    uint16_t width;
    uint16_t height;
    
  public:
    /**
     * @brief Constructs a pending object
     * 
     * @param tex Address to a Texture instance. This is to redirect 
     *            responses after loading.
     * @param f Path to texture file, folder or zip
     */
    TextureLoad(Texture* tex, const char* f);
    
    /**
     * @brief Constructs a pending object
     * 
     * @param tex Address to a Texture instance. This is to redirect 
     *            responses after loading.
     * @param bmp Image data
     */
    TextureLoad(Texture* tex, const Bitmap& bmp);
    
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
    TextureLoad(Texture* tex, const Bitmap& base, const Bitmap& h,
                const Bitmap& norm, const Bitmap& m, const Bitmap& e);
    
    /**
     * @brief Destructor
     */
    ~TextureLoad();
    
    /**
     * @brief Loads the texture data to the GPU
     * 
     * Loads a chunk of image data into GPU for shader processing.
     * Also this pending object's load function assigns the resource
     * addresses to the related Texture instance.
     */
    void load() override;
    
    /**
     * @brief Gets the width of the image
     * 
     * @return Image width in pixels
     */
    uint16_t getWidth() const;
    
    /**
     * @brief Gets the height of the image
     * 
     * @return Image height in pixels
     */
    uint16_t getHeight() const;
};


/**
 * @brief To enhance the appearance of 2D/3D objects with image data
 */
class RMG_API Texture {
  private:
    uint32_t basecolor;
    uint32_t heightMap;
    uint32_t normalMap;
    uint32_t mraoMap;
    uint32_t opacity;
    uint32_t emissivity;
    
    Vec2 size;
    
    Color color;
    float metalness;
    float roughness;
    float ambientOcculation;
    float depth;
    
    friend class TextureLoad;
    
  public:
    /**
     * @brief Default constructor
     */
    Texture();
    
    /**
     * @brief Destructor
     */
    virtual ~Texture();
    
    /**
     * @brief Copy constructor (deleted)
     * 
     * Copy constructor is not allowed to use since it contains a unique
     * pointer.
     * 
     * @param tex Source texture
     */
    Texture(const Texture& tex) = delete;
    
    /**
     * @brief Move constructor
     * 
     * @param tex Source texture
     */
    Texture(Texture&& tex) noexcept = default;
    
    /**
     * @brief Copy assignment (deleted)
     * 
     * Copy assignment is not allowed to use since it contains a unique
     * pointer.
     * 
     * @param tex Source texture
     */
    Texture& operator=(const Texture& tex) = delete;
    
    /**
     * @brief Move assignment
     * 
     * @param tex Source texture
     */
    Texture& operator=(Texture&& tex) noexcept = default;
    
    /**
     * @brief Gets the physical dimensions of the texture
     * 
     * @param s Texture length
     */
    void setSize(float s);
    
    /**
     * @brief Gets the physical dimensions of the texture
     * 
     * @param w Texture width
     * @param h Texture height
     */
    void setSize(float w, float h);
    
    /**
     * @brief Gets the physical dimensions of the texture
     * 
     * @param size Texture size
     */
    inline void setSize(const Vec2 &size) { setSize(size.x, size.y); }
    
    /**
     * @brief Gets the physical dimension of the texture
     * 
     * @return Texture width and height
     */
    Vec2 getSize() const;
    
    /**
     * @brief Sets material color
     * 
     * @param r Red
     * @param g Green
     * @param b Blue
     */
    void setColor(float r, float g, float b);
    
    /**
     * @brief Sets material color
     * 
     * @param r Red
     * @param g Green
     * @param b Blue
     * @param a Alpha
     */
    void setColor(float r, float g, float b, float a);
    
    /**
     * @brief Sets material color
     * 
     * @param col RGBA color
     */
    void setColor(const Color &col);
    
    /**
     * @brief Gets material color
     * 
     * @return RGBA color
     */
    Color getColor() const;
    
    /**
     * @brief Sets the metalness coefficient of the texture
     * 
     * @param m Metalness coefficient
     */
    void setMetalness(float m);
    
    /**
     * @brief Gets the metalness coefficient of the texturey.
     * 
     * @return Metalness coefficient
     */
    float getMetalness() const;
    
    /**
     * @brief Sets the roughness coefficient of the texture.
     * 
     * @param r Roughness coefficient
     */
    void setRoughness(float r);
    
    /**
     * @brief Gets the roughness coefficient of the texture
     * 
     * @return Roughness coefficient
     */
    float getRoughness() const;
    
    /**
     * @brief Sets the ambient occulation of the texture.
     * 
     * @param ao Ambient occulation
     */
    void setAmbientOcculation(float ao);
    
    /**
     * @brief Gets the ambient occulation of the texture
     * 
     * @return Ambient occulation
     */
    float getAmbientOcculation() const;
    
    /**
     * @brief Sets the maximum unit for height mapping
     */
    void setDepth(float d);
    
    /**
     * @brief Gets the maximum unit for height mapping
     */
    float getDepth() const;
    
    /**
     * @brief Binds the texture to process
     */
    void bind() const;
};

}}

#endif
