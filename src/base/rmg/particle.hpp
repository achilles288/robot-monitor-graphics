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


#include "object.hpp"
#include "math/angle_unit.hpp"
#include "math/mat3.hpp"
#include "math/vec.hpp"
#include "internal/context_load.hpp"


namespace rmg {

class Bitmap;

namespace internal {

class SpriteTexture;

}


/**
 * @brief 2D graphics displayed in terms of 3D space
 * 
 * Less detailed 3D graphics like smoke, fog, spark, .etc.
 * Enables wider variety of graphics at low cost.
 */
class RMG_API Particle3D: public Object {
  private:
    internal::SpriteTexture* texture = nullptr;
    uint32_t* texShareCount = nullptr;
    internal::Pending texLoad;
    
    Vec3 position;
    Vec2 size;
    float rotation;
    Mat3 modelMatrix;
    
  protected:
    /**
     * @brief Swaps the values of member variables between two objects
     * 
     * @param x The other object
     */
    void swap(Particle3D& x) noexcept;
    
  public:
    /**
     * @brief Default constructor
     */
    Particle3D();
    
    /**
     * @brief Constructs a particle object loading a particle image
     * 
     * @param ctx Container context
     * @param img Image file (supports the same format Texture class does)
     * @param s Particle size
     */
    Particle3D(Context* ctx, const char* img, const Vec2 &s=Vec2(1,1));
    
    /**
     * @brief Constructs a particle object loading a particle image
     * 
     * @param ctx Container context
     * @param bmp Particle image
     * @param s Particle size
     */
    Particle3D(Context* ctx, const Bitmap &bmp, const Vec2 &s=Vec2(1,1));
    
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
     * @brief The matrix composed of all the transformations done by the object
     * 
     * @return Model matrix
     */
    const Mat3& getModelMatrix() const;
    
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
     * @brief Sets the rotation of the particle
     * 
     * @param t Rotation in radian
     */
    void setRotation(float t);
    
    /**
     * @brief Sets the rotation of the particle
     * 
     * @param t Rotation
     * @param unit If the rotation value is degree or radian
     */
    inline void setRotation(float t, AngleUnit unit) {
        setRotation((unit == AngleUnit::Radian) ? t : radian(t));
    }
    
    /**
     * @brief Gets the rotation of the particle
     * 
     * @return Rotation in radian
     */
    float getRotation() const;
    
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
    
    /**
     * @brief Gets the pointer to the texture
     * 
     * @return Pointer to the texture
     */
    const internal::SpriteTexture *getTexture() const;
    
    /**
     * @brief Gets the texture loader
     * 
     * @return Texture loader
     */
    const internal::Pending& getTextureLoad() const;
};

}

#endif
