/**
 * @file vec4.cpp
 * @brief 4D vector
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "../rmg/math/vec4.hpp"


namespace rmg {

/**
 * @brief Gets a vector of one unit length in the same direction
 * 
 * @return Unit vector
 */
Vec4 Vec4::normalize() const {
    float r = sqrt(x*x + y*y + z*z + w*w);
    Vec4 u;
    u.x = x/r;
    u.y = y/r;
    u.z = z/r;
    u.w = w/r;
    return u;
}

}
