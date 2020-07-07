/**
 * @file particle.hpp
 * @brief 2D graphics displayed in terms of 3D space
 * 
 * Less detailed 3D graphics like smoke, fog, spark, .etc.
 * Enables wider variety of graphics at low cost.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_PARTICLE_H__
#define __RMG_PARTICLE_H__

#include <memory>

#include "object.hpp"
#include "math/vec.hpp"
#include "internal/context_load.hpp"


namespace rmg {

class Bitmap;

namespace internal {

class ParticleShader;
class Texture;

}


/**
 * @brief 2D graphics displayed in terms of 3D space
 * 
 * Less detailed 3D graphics like smoke, fog, spark, .etc.
 * Enables wider variety of graphics at low cost.
 */
class Particle3D: public Object {
  private:
    std::shared_ptr<internal::Texture> texture;
    internal::ContextLoader::Pending texLoad;
    
    Vec3 position;
    Vec2 size;
    
    friend class internal::ParticleShader;
    
  public:
    /**
     * @brief Default constructor
     */
    Particle3D() = default;
    
    /**
     * @brief Constructs a particle object loading a particle image
     * 
     * @param ctx Container context
     * @param img Image file (supports the same format Texture class does)
     * @param s Particle size
     */
    Particle3D(Context* ctx, const std::string &img, const Vec2 &s=Vec2());
    
    /**
     * @brief Constructs a particle object loading a particle image
     * 
     * @param ctx Container context
     * @param bmp Particle image
     * @param s Particle size
     */
    Particle3D(Context* ctx, const Bitmap &bmp, const Vec2 &s=Vec2());
    
    /**
     * @brief Sets the location which the particle appears
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param z Z-coordinate
     */
    void setTranslation(float x, float y, float z);
    
    /**
     * @brief Sets the location which the particle appears
     * 
     * @param pos Position vector
     */
    void setTranslation(const Vec3 &pos);
    
    /**
     * @brief Gets the location of the particle
     * 
     * @return Position vector
     */
    Vec3 getTranslation() const;
    
    /**
     * @brief Sets the size of the particle
     * 
     * @param w Width
     * @param h Height
     */
    void setSize(float w, float h);
    
    /**
     * @brief Sets the size of the particle
     * 
     * @param s Size
     */
    void setSize(const Vec2 &s);
    
    /**
     * @brief Gets the size of the particle
     * 
     * @return Width and height as a rectangular dimension
     */
    Vec2 getSize() const;
};

}

#endif
