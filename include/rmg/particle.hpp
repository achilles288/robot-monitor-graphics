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

#include <rmg/math.hpp>
#include <rmg/object.hpp>


class rmg::internal::ParticleShader;


namespace rmg {

/**
 * @brief 2D graphics displayed in terms of 3D space
 * 
 * Less detailed 3D graphics like smoke, fog, spark, .etc.
 * Enables wider variety of graphics at low cost.
 */
class Particle3D: public Object {
  private:
    glm::mat3 modelMatrix;
    Vec3 position;
    float t;
    float width;
    float height;
    
    friend class internal::ParticleShader;
    
  public:
    /**
     * @brief Constructs a particle object loading a particle image
     * 
     * @param ctx Container context
     * @param img Image file (supports the same format Texture class does)
     */
    Particle3D(Context* ctx, std::string img);
    
    /**
     * @brief Constructs a particle object with a preloaded texture
     * 
     * @param ctx Container context
     * @param tex Loaded texture
     */
    Particle3D(Context* ctx, Texture* tex);
    
    /**
     * @brief Constructs a particle object loading a particle image
     * 
     * @param ctx Container context
     * @param img Image file (supports the same format Texture class does)
     * @param size Sprite size
     */
    Particle3D(Context* ctx, std::string img, Vec2 size);
    
    /**
     * @brief Constructs a particle object with a preloaded texture
     * 
     * @param ctx Container context
     * @param tex Loaded texture
     * @param size Sprite size
     */
    Particle3D(Context* ctx, Texture* tex, Vec2 size);    
    
    /**
     * @brief Destructor
     */
    virtual ~Particle3D();
    
    /**
     * @brief Copy constructor
     * 
     * @param obj Source object
     */
    Particle3D(const Particle3D& obj);
    
    /**
     * @brief Move constructor
     * 
     * @param obj Source object
     */
    Particle3D(Particle3D&& obj) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param obj Source object
     */
    Particle3D& operator=(const Particle3D& obj);
    
    /**
     * @brief Move assignment
     * 
     * @param obj Source object
     */
    Particle3D& operator=(Particle3D&& obj) noexcept;
    
    /**
     * @brief Sets the location which the particle appears
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param z Z-coordinate
     */
    void setPosition(float x, float y, float z);
    
    /**
     * @brief Sets the location which the particle appears
     * 
     * @param pos Position vector
     */
    void setPosition(const Vec3 &pos);
    
    /**
     * @brief Gets the location of the particle
     * 
     * @return Position vector
     */
    Vec3 getPosition();
    
    /**
     * @brief Sets the rotation of the particle
     * 
     * @param t Rotation in degrees
     */
    void setRotation(float t);
    
    /**
     * @brief Gets the rotation of the particle
     * 
     * @return Rotation in degrees
     */
    float getRotation();
    
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
     * @param size Size
     */
    void setSize(const Vec2 &size);
    
    /**
     * @brief Gets the size of the particle
     * 
     * @return Width and height as a rectangular dimension
     */
    Vec2 getSize();
};

}

#endif
