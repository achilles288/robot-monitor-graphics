/**
 * @file euler.hpp
 * @brief To represent orientation in 3D space
 * 
 * Euler angles represent 3 successive rotations in the order of ZYX.
 * They can also be called yaw, pitch and roll. Values are stored as radian.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_EULER_H__
#define __RMG_EULER_H__


#include "angle_unit.hpp"

#include <ostream>


namespace rmg {

struct Mat3;

/**
 * @brief To represent orientation in 3D space
 * 
 * Euler angles represent 3 successive rotations in the order of ZYX.
 * They can also be called yaw, pitch and roll. Values are stored as radian.
 */
struct Euler {
    float roll;  ///< Rotation along X-axis
    float pitch; ///< Rotation along Y-axis
    float yaw;   ///< Rotation along Z-axis
    
    /**
     * @brief Default constructor
     */
    Euler();
    
    /**
     * @brief Constructor with roll, pitch and yaw
     * 
     * @param x Rotation about x-axis (Roll)
     * @param y Rotation about y-axis (Pitch)
     * @param z Rotation about z-axis (Yaw)
     */
    Euler(float x, float y, float z);
    
    /**
     * @brief Constructor with roll, pitch and yaw
     * 
     * @param x Rotation about x-axis (Roll)
     * @param y Rotation about y-axis (Pitch)
     * @param z Rotation about z-axis (Yaw)
     * @param unit Degree or radian
     */
    Euler(float x, float y, float z, AngleUnit unit);
    
    /**
     * @brief Converts rotation matrix to Euler
     * 
     * @param R 3x3 rotation matrix
     */
    Euler(const Mat3 &R);
    
    /**
     * @brief Converts Euler to rotation matrix
     * 
     * @return 3x3 rotation matrix
     */
    Mat3 toRotationMatrix();
};

/**
 * @brief Prints a tuple of Euler angles
 * 
 * @param os Output stream
 * @param euler The Euler angles
 * 
 * @return Reference of passed output stream
 */
std::ostream& operator << (std::ostream& os, const Euler& euler);

}

#endif
