/**
 * @file cube.hpp
 * @brief Visual 3D cube model
 *
 * Generates a 3D cube model. Manipulate the cube dimension, location,
 * rotation and scale.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_CUBE_H__
#define __RMG_CUBE_H__

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
 * @brief Visual 3D cube model
 *
 * Generates a 3D cube model. Manipulate the cube dimensions, locations,
 * rotation and scale.
 */
class RMG_API Cube3D: public Object3D {
  private:
    float length;
    float breadth;
    float height;
    
    Mesh createMesh();
    
  public:
    /**
     * @brief Default constructor
     */
    Cube3D();
    
    /**
     * @brief Constructs a 3D cube model from specific dimensions
     * 
     * @param ctx Container context
     * @param l Length
     * @param b Breadth
     * @param h Height
     */
    Cube3D(Context* ctx, float l, float b, float h);
    
    /**
     * @brief Gets the dimension of the cube
     * 
     * @return Cubic dimension
     */
    Vec3 getDimension() const;
    
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
