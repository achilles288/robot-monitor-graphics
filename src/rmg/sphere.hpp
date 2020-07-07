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

#include "object3d.hpp"


namespace rmg {

namespace internal {

class VBOLoad;

}

/**
 * @brief Visual sphere model
 *
 * Generates a sphere model. Manipulate the sphere diameter, length
 * location, rotation and scale.
 */
class Sphere3D: public Object3D {
  private:
    float diameter;
    
    Mesh createMesh();
    
  public:
    /**
     * @brief Default constructor
     */
    Sphere3D();
    
    /**
     * @brief Constructs a sphere model with specific diameter
     * 
     * @param ctx Container context
     * @param d Diameter
     */
    Sphere3D(Context* ctx, float d);
    
    /**
     * @brief Gets sphere diameter
     * 
     * @return Diameter
     */
    float getDiameter() const;
    
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
