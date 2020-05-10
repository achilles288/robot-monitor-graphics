/**
 * @file sphere.hpp
 * @brief Visual sphere model
 *
 * Generates a sphere model. Manipulate the sphere radius, length
 * location, rotation and scale.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */
 

#pragma once
#ifndef __RMG_SPHERE_H__
#define __RMG_SPHERE_H__

#include <cstdint>
#include <vector>
#include <utility>

#include "object3d.hpp"


namespace rmg::internal {
class VBOLoad;
}


namespace rmg {

/**
 * @brief Visual sphere model
 *
 * Generates a sphere model. Manipulate the sphere diameter, length
 * location, rotation and scale.
 */
class Sphere3D: public Object3D {
  private:
    float diameter;
    
    static std::vector<std::pair<uint32_t, internal::VBOLoad>> samples;
    
  public:
    /**
     * @brief Constructs a sphere model from specific dimensions
     * 
     * @param ctx Container context
     * @param d Diameter
     */
    Sphere3D(Context* ctx, float d);
    
    /**
     * @brief Destructor
     */
    virtual ~Sphere3D();
    
    /**
     * @brief Copy constructor
     * 
     * @param obj Source object
     */
    Sphere3D(const Sphere3D& obj);
    
    /**
     * @brief Move constructor
     * 
     * @param obj Source object
     */
    Sphere3D(Sphere3D&& obj) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param obj Source object
     */
    Sphere3D& operator=(const Sphere3D& obj);
    
    /**
     * @brief Move assignment
     * 
     * @param obj Source object
     */
    Sphere3D& operator=(Sphere3D&& obj) noexcept;
    
    /**
     * @brief Sets sphere diameter
     * 
     * @param d Diameter
     */
    void setDiameter(float d);
    
    /**
     * @brief Gets sphere diameter
     * 
     * @return Diameter
     */
    float getDiameter();
    
    /**
     * @brief Sets the orientaion of the sphere
     * 
     * Sets the rotation matrix and the model matrix. Rotation of the sphere
     * is in Euler angles. Rotation order is ZYX (Yaw-Pitch-Roll).
     * Model matrix calculation includes additional factors diameter.
     * 
     * @param x Roll
     * @param y Pitch
     * @param z Yaw
     */
    void setRotation(float x, float y, float z) override;
    
    /**
     * @brief Sets the scale of the sphere
     * 
     * Sets the scale and the model matrix.
     * The function is virtual as the derived classes' handling of model
     * matrix involves additional scaling components.
     * Model matrix calculation includes additional factor diameter.
     * 
     * @param x Scaling factor in x-component
     * @param y Scaling factor in y-component
     * @param z Scaling factor in z-component
     */
    void setScale(float x, float y, float z) override;
    
    /**
     * @brief Sets the scale of the cube
     * 
     * Sets the scale and the model matrix.
     * The function is virtual as the derived classes' handling of model
     * matrix involves additional scaling components.
     * Model matrix calculation includes additional factors length, width and
     * height.
     * 
     * @param f Scaling factor
     */
    void setScale(float f) override;
};

}

#endif
