/**
 * @file particle.cpp
 * @brief 2D graphics displayed in terms of 3D space
 * 
 * Less detailed 3D graphics like smoke, fog, spark, .etc.
 * Enables wider variety of graphics at low cost.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "rmg/particle.hpp"

#include "rmg/bitmap.hpp"


namespace rmg {

/**
 * @brief Constructs a particle object loading a particle image
 * 
 * @param ctx Container context
 * @param img Image file (supports the same format Texture class does)
 * @param size Particle size
 */
Particle3D::Particle3D(Context* ctx, const std::string &img, const Vec2 &s)
           :Object(ctx)
{
    size.x = s.x;
    size.y = s.y;
}

/**
 * @brief Constructs a particle object loading a particle image
 * 
 * @param ctx Container context
 * @param bmp Particle image
 * @param size Particle size
 */
Particle3D::Particle3D(Context* ctx, const Bitmap &bmp, const Vec2 &s)
           :Object(ctx)
{
    size.x = s.x;
    size.y = s.y;
}

/**
 * @brief Sets the location which the particle appears
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param z Z-coordinate
 */
void Particle3D::setTranslation(float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
}

/**
 * @brief Sets the location which the particle appears
 * 
 * @param pos Position vector
 */
void Particle3D::setTranslation(const Vec3 &pos) {
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;
}

/**
 * @brief Gets the location of the particle
 * 
 * @return Position vector
 */
Vec3 Particle3D::getTranslation() const { return position; }

/**
 * @brief Sets the size of the particle
 * 
 * @param w Width
 * @param h Height
 */
void Particle3D::setSize(float w, float h) {
    size.x = w;
    size.y = h;
}

/**
 * @brief Sets the size of the particle
 * 
 * @param size Size
 */
void Particle3D::setSize(const Vec2 &s) { size = s; }

/**
 * @brief Gets the size of the particle
 * 
 * @return Width and height as a rectangular dimension
 */
Vec2 Particle3D::getSize() const { return size; }

}
