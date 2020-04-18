/**
 * @file cylinder.hpp
 * @brief Visual cylinder model
 *
 * Generates a cylinder model. Manipulate the cylinder radius, length
 * location, rotation and scale.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */
 

#pragma once
#ifndef __RMG_CYLINDER_H__
#define __RMG_CYLINDER_H__

#include <rmg/object3d.hpp>

#include <cstdint>
#include <vector>
#include <utility>


class rmg::internal::VBOLoad;


namespace rmg {

/**
 * @brief Visual cylinder model
 *
 * Generates a cylinder model. Manipulate the cylinder diameter, length
 * location, rotation and scale.
 */
class Cylinder3D: public Object3D {
  private:
    float diameter;
    float length;
    
    static std::vector<std::pair<uint32_t, internal::VBOLoad>> samples;
    
  public:
    /**
     * @brief Constructs a cylinder model from specific dimensions
     * 
     * @param ctx Container context
     * @param d Diameter
     * @param l Length
     */
    Cylinder3D(Context* ctx, float d, float l);
    
    /**
     * @brief Destructor
     */
    virtual ~Cylinder3D();
    
    /**
     * @brief Copy constructor
     * 
     * @param obj Source object
     */
    Cylinder3D(const Cylinder3D& obj);
    
    /**
     * @brief Move constructor
     * 
     * @param obj Source object
     */
    Cylinder3D(Cylinder3D&& obj) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param obj Source object
     */
    Cylinder3D& operator=(const Cylinder3D& obj);
    
    /**
     * @brief Move assignment
     * 
     * @param obj Source object
     */
    Cylinder3D& operator=(Cylinder3D&& obj) noexcept;
    
    /**
     * @brief Sets cylinder diameter
     * 
     * @param d Diameter
     */
    void setDiameter(float d);
    
    /**
     * @brief Gets cylinder diameter
     * 
     * @return Diameter
     */
    float getDiameter();
    
    /**
     * @brief Sets cylinder length
     * 
     * @param l Length
     */
    void setLength(float l);
    
    /**
     * @brief Gets cylinder length
     * 
     * @return Length
     */
    float getLength();
    
    /**
     * @brief Sets the orientaion of the cylinder
     * 
     * Sets the rotation matrix and the model matrix. Rotation of the cylinder
     * is in Euler angles. Rotation order is ZYX (Yaw-Pitch-Roll).
     * Model matrix calculation includes additional factors diameter and
     * length.
     * 
     * @param x Roll
     * @param y Pitch
     * @param z Yaw
     */
    void setRotation(float x, float y, float z) override;
    
    /**
     * @brief Sets the scale of the cylinder
     * 
     * Sets the scale and the model matrix.
     * The function is virtual as the derived classes' handling of model
     * matrix involves additional scaling components.
     * Model matrix calculation includes additional factors diameter and
     * length.
     * 
     * @param x Scaling factor in x-component
     * @param y Scaling factor in y-component
     * @param z Scaling factor in z-component
     */
    void setScale(float x, float y, float z) override;
};

}

#endif
