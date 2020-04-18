/**
 * @file math.hpp
 * @brief Mathematical functions and representations used by RMG
 * 
 * Mainly uses the GLM library. Mathematical objects are remade with the
 * ::rmg namespace. Includes minor modifications.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_MATH_H__
#define __RMG_MATH_H__

#include <glm/glm.hpp>


namespace rmg {

/**
 * @brief 2D vector
 * 
 * Represents a 2D-point or a rectangular dimension.
 */
struct Vec2 {
    float x; /**< X-coordinate */
    float y; /**< Y-coordinate */
};

/**
 * @brief 3D vector
 * 
 * Represents a 3D-point, Euler angles or a cubic dimension.
 */
struct Vec3 {
    float x; /**< X-coordinate */
    float y; /**< Y-coordinate */
    float z; /**< Z-coordinate */
};

/**
 * @brief RGBA color model
 */
struct Color {
    float r; /**< Red */
    float g; /**< Green */
    float b; /**< Blue */
    float a; /**< Alpha */
};

}

#endif
