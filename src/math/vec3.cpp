/**
 * @file vec3.cpp
 * @brief 3D vector to represent a 3D-point or a cubic dimension
 * 
 * Vector functions like dot product, cross product and normalization.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "../rmg/math/vec3.hpp"


namespace rmg {

/**
 * @brief Gets a vector of one unit length in the same direction
 * 
 * @return Unit vector
 */
Vec3 Vec3::normalize() const {
    float r = sqrt(x*x + y*y + z*z);
    Vec3 u;
    u.x = x/r;
    u.y = y/r;
    u.z = z/r;
    return u;
}

/**
 * @brief Vector cross product operation
 * 
 * @param a Vector A
 * @param b Vector B
 * 
 * @return Cross product
 */
Vec3 Vec3::cross(const Vec3 &a, const Vec3 &b) {
    Vec3 c;
    c.x = a.y*b.z - a.z*b.y;
    c.y = a.z*b.x - a.x*b.z;
    c.z = a.x*b.y - a.y*b.x;
    return c;
}

}
