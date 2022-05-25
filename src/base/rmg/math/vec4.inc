/**
 * @file vec4.inc
 * @brief 4D vector
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "vec.hpp"

#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265359f
#endif

#include "../assert.hpp"


namespace rmg {

/**
 * @brief Default constructor
 */
inline Vec4::Vec4() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

/**
 * @brief Constructor with xyzw values
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param z Z-coordinate
 * @param w W-coordinate (4th coordinate)
 */
inline Vec4::Vec4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

/**
 * @brief Constructs with a 2D vector and 2 remaining components
 * 
 * @param v 2D vector
 * @param c Z-coordinate
 * @param d W-coordinate
 */
inline Vec4::Vec4(const Vec2 &v, float c, float d) {
    x = v.x;
    y = v.y;
    z = c;
    w = d;
}

/**
 * @brief Constructs with a 3D vector and a remaining component
 * 
 * @param v 3D vector
 * @param d W-coordinate
 */
inline Vec4::Vec4(const Vec3 &v, float d) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = d;
}

/**
 * @brief Conversion from Vec4 to Vec2
 */
inline Vec4::operator Vec2() const {
    return Vec2(x, y);
}

/**
 * @brief Conversion from Vec4 to Vec3
 */
inline Vec4::operator Vec3() const {
    return Vec3(x, y, z);
}

/**
 * @brief Gets the magnitude or length of the vector
 * 
 * @return Vector magnitude
 */
inline float Vec4::magnitude() const {
    return sqrt(x*x + y*y + z*z + w*w);
}

/**
 * @brief Adds 2 vectors
 */
inline Vec4 Vec4::operator + (const Vec4 &b) const {
    Vec4 c;
    c.x = x + b.x;
    c.y = y + b.y;
    c.z = z + b.z;
    c.w = w + b.w;
    return c;
}

/**
 * @brief Subtract the vector by vector B
 */
inline Vec4 Vec4::operator - (const Vec4 &b) const {
    Vec4 c;
    c.x = x - b.x;
    c.y = y - b.y;
    c.z = z - b.z;
    c.w = w - b.w;
    return c;
}


/**
 * @brief Minus vector
 */
inline Vec4 Vec4::operator - () const {
    return Vec4(-x, -y, -z, -w);
}

/**
 * @brief Multiply the vector by a number
 */
inline Vec4 Vec4::operator * (float f) const {
    Vec4 v;
    v.x = f * x;
    v.y = f * y;
    v.z = f * z;
    v.w = f * w;
    return v;
}

/**
 * @brief Divide the vector by a number
 */
inline Vec4 Vec4::operator / (float f) const {
    Vec4 v;
    v.x = x/f;
    v.y = y/f;
    v.z = z/f;
    v.w = w/f;
    return v;
}

/**
 * @brief Multiply the vector by a number
 */
inline Vec4 operator * (float f, const Vec4 &v) {
    Vec4 u;
    u.x = f * v.x;
    u.y = f * v.y;
    u.z = f * v.z;
    u.w = f * v.w;
    return u;
}

/**
 * @brief Adds 2 vectors
 */
inline Vec4& Vec4::operator += (const Vec4 &b) {
    x += b.x;
    y += b.y;
    z += b.z;
    w += b.w;
    return *this;
}

/**
 * @brief Subtract the vector by vector B
 */
inline Vec4& Vec4::operator -= (const Vec4 &b) {
    x -= b.x;
    y -= b.y;
    z -= b.z;
    w -= b.w;
    return *this;
}

/**
 * @brief Multiply the vector by a number
 */
inline Vec4& Vec4::operator *= (float f) {
    x *= f;
    y *= f;
    z *= f;
    w *= f;
    return *this;
}

/**
 * @brief Divide the vector by a number
 */
inline Vec4& Vec4::operator /= (float f) {
    x /= f;
    y /= f;
    z /= f;
    w /= f;
    return *this;
}

/**
 * @brief Gets reference to vector data as array subscript
 */
inline float& Vec4::operator [] (uint8_t i) {
     RMG_ASSERT(i < 4);
     return data[i];
}

/**
 * @brief Gets reference to vector data as array subscript
 */
inline float const& Vec4::operator [] (uint8_t i) const {
     RMG_ASSERT(i < 4);
     return data[i];
}

/**
 * @brief Equality operator
 */
inline bool Vec4::operator == (const Vec4 &b) const {
    return (x == b.x) && (y == b.y) && (z == b.z) && (w == b.w);
}

/**
 * @brief Unequality operator
 */
inline bool Vec4::operator != (const Vec4 &b) const {
    return (x != b.x) || (y != b.y) || (z != b.z) || (w != b.w);
}

}
