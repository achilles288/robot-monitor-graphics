/**
 * @file euler.cpp
 * @brief To represent orientation in 3D space
 * 
 * Euler angles represent 3 successive rotations in the order of ZYX.
 * They can also be called yaw, pitch and roll. Values are stored as radian.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "../rmg/math/euler.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#include "../rmg/math/mat3.hpp"


namespace rmg {

/**
 * @brief Default constructor
 */
Euler::Euler() {
    roll = 0;
    pitch = 0;
    yaw = 0;
}

/**
 * @brief Constructor with roll, pitch and yaw
 * 
 * @param x Rotation about x-axis (Roll)
 * @param y Rotation about y-axis (Pitch)
 * @param z Rotation about z-axis (Yaw)
 */
Euler::Euler(float x, float y, float z) {
    roll = x;
    pitch = y;
    yaw = z;
}

/**
 * @brief Constructor with roll, pitch and yaw
 * 
 * @param x Rotation about x-axis (Roll)
 * @param y Rotation about y-axis (Pitch)
 * @param z Rotation about z-axis (Yaw)
 * @param unit Degree or radian
 */
Euler::Euler(float x, float y, float z, AngleUnit unit) {
    if(unit == AngleUnit::Radian) {
        roll = x;
        pitch = y;
        yaw = z;
    }
    else {
        roll = radian(x);
        pitch = radian(y);
        yaw = radian(z);
    }
}

/**
 * @brief Converts rotation matrix to Euler
 * 
 * @param R 3x3 rotation matrix
 */
Euler::Euler(const Mat3 &R) {
    pitch = -asin(R[2][0]);
    float c2 = cos(pitch);
    
    // cos(pitch) != 0
    if(fabs(c2) > 0.001f) {
        roll = atan2(R[2][1]/c2, R[2][2]/c2);
        yaw = atan2(R[1][0]/c2, R[0][0]/c2);
    }
    // Gimbal lock position
    else {
        if(pitch > 0) { // pitch = pi/2
            yaw = atan2(-R[0][1], R[0][2]);
        }
        else { // pitch = -pi/2
            yaw = atan2(-R[0][1], -R[0][2]);
        }
        roll = 0;
    }
}

/**
 * @brief Converts Euler to rotation matrix
 * 
 * @return 3x3 rotation matrix
 */
Mat3 Euler::toRotationMatrix() {
    float c1 = cos(roll);
    float c2 = cos(pitch);
    float c3 = cos(yaw);
    float s1 = sin(roll);
    float s2 = sin(pitch);
    float s3 = sin(yaw);
    return {
        { c2*c3,  s1*s2*c3 - c1*s3,  c1*s2*c3 + s1*s3 },
        { c2*s3,  s1*s2*s3 + c1*c3,  c1*s2*s3 - s1*c3 },
        {  -s2 ,       s1*c2      ,       c1*c2       }
    };
}

}
