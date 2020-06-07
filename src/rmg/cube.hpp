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

#include <cstdint>
#include <vector>
#include <utility>

#include "object3d.hpp"


namespace rmg {

/**
 * @brief Visual 3D cube model
 *
 * Generates a 3D cube model. Manipulate the cube dimensions, locations,
 * rotation and scale.
 */
class Cube3D: public Object3D {
  private:
    float length;
    float breadth;
    float height;
    
    using Sample = shared_ptr<internal::VBO>;
    static std::vector<std::pair<uint32_t, Sample>> samples;
    
  public:
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
     * @brief Destructor
     */
    virtual ~Cube3D();
    
    /**
     * @brief Modify the dimension of the cube
     * 
     * @param l Length
     * @param b Breadth
     * @param h Height
     */
    void setDimension(float l, float b, float h);
    
    /**
     * Gets the dimension of the cube
     * 
     * @return Cubic dimension
     */
    Vec3 getDimension();
    
    /**
     * @brief Sets the orientaion of the cube
     * 
     * Sets the rotation matrix and the model matrix. Rotation of the cube
     * is in Euler angles. Rotation order is ZYX (Yaw-Pitch-Roll).
     * Model matrix calculation includes additional factors length, width and
     * height.
     * 
     * @param rot Euler angles
     */
    void setRotation(const Euler& rot) override;
    
    /**
     * @brief Sets the scale of the cube
     * 
     * Sets the scale and the model matrix.
     * The function is virtual as the derived classes' handling of model
     * matrix involves additional scaling components.
     * Model matrix calculation includes additional factors length, width and
     * height.
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
