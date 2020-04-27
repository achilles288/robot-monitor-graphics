/**
 * @file angle_unit.hpp
 * @brief Representation of angle values degree or radian
 * 
 * An enumeration to represent the unit and some 2 functions to do conversions
 * between the units.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_ANGLE_UNIT_H__
#define __RMG_ANGLE_UNIT_H__


#include <cmath>


namespace rmg {

/**
 * @brief Represents if the unit is degree or radian
 */
enum AngleUnit {
    UNIT_DEGREE,
    UNIT_RADIAN
};

/**
 * @brief Converts degree to radian
 * 
 * @param deg Angle value in degree
 * 
 * @return Angle value in radian
 */
inline float radian(float deg) { return deg * M_PI/180; }

/**
 * @brief Converts radian to degree
 * 
 * @param rad Angle value in radian
 * 
 * @return Angle value in degree
 */
inline float degree(float rad) { return rad * 180/M_PI; }

}


using rmg::AngleUnit::UNIT_RADIAN;
using rmg::AngleUnit::UNIT_DEGREE;


#endif
