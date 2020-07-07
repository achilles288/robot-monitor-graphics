#include "../rmg/internal/texture_load.hpp"

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
TextureLoad::TextureLoad(Texture* tex, const std::string &f) {}

/**
 * @brief Constructs a pending object
 * 
 * @param tex Address to a Texture instance. This is to redirect 
 *            responses after loading.
 * @param bmp Image data
 */
TextureLoad::TextureLoad(Texture* tex, const Bitmap& bmp) {}

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
void TextureLoad::load() {}




// Class: Texture

/**
 * @brief Default constructor
 */
Texture::Texture() {}

/**
 * @brief Destructor
 */
Texture::~Texture() {}
    
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
