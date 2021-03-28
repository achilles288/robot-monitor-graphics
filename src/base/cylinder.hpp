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


#include "object3d.hpp"


namespace rmg {

/**
 * @brief Visual cylinder model
 *
 * Generates a cylinder model. Manipulate the cylinder diameter, length
 * location, rotation and scale.
 */
class RMG_API Cylinder3D: public Object3D {
  private:
    float diameter;
    float length;
    
    Mesh createMesh();
    
  public:
    /**
     * @brief Default constructor
     */
    Cylinder3D();
    
    /**
     * @brief Constructs a cylinder model from specific dimensions
     * 
     * @param ctx Container context
     * @param d Diameter
     * @param l Length
     */
    Cylinder3D(Context* ctx, float d, float l);
    
    /**
     * @brief Gets cylinder diameter
     * 
     * @return Diameter
     */
    float getDiameter() const;
    
    /**
     * @brief Gets cylinder length
     * 
     * @return Length
     */
    float getLength() const;
    
    /**
     * @brief Sets the material texture
     * 
     * Sets the object to use a predefined material. This material data uses
     * OpenGL context for texture image, normal maps, .etc.
     * 
     * @param mat Predefined material
     */
    void setMaterial(Material* mat) override;
};

}

#endif
