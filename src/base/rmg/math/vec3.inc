/**
 * @file vec3.inc
 * @brief 3D vector to represent a 3D-point or a cubic dimension
 * 
 * Vector functions like dot product, cross product and normalization.
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
inline Vec3::Vec3() {
    x = 0;
    y = 0;
    z = 0;
}

/**
 * @brief Constructor with xyz values
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param z Z-coordinate
 */
inline Vec3::Vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

/**
 * @brief Constructs with a 2D vector and z-coordinate
 * 
 * @param v 2D vector
 * @param c Z-coordinate
 */
inline Vec3::Vec3(const Vec2 &v, float c) {
    x = v.x;
    y = v.y;
    z = c;
}

/**
 * @brief Conversion from Vec3 to Vec2
 */
inline Vec3::operator Vec2() const {
    return Vec2(x, y);
}

/**
 * @brief Conversion from Vec3 to Vec4
 */
inline Vec3::operator Vec4() const {
    return Vec4(x, y, z, 0);
}

/**
 * @brief Gets the magnitude or length of the vector
 * 
 * @return Vector magnitude
 */
inline float Vec3::magnitude() const {
    return sqrt(x*x + y*y + z*z);
}

/**
 * @brief Vector dot product operation
 * 
 * @param a Vector A
 * @param b Vector B
 * 
 * @return Dot product
 */
inline float Vec3::dot(const Vec3 &a, const Vec3 &b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

/**
 * @brief Adds 2 vectors
 */
inline Vec3 Vec3::operator + (const Vec3 &b) const {
    Vec3 c;
    c.x = x + b.x;
    c.y = y + b.y;
    c.z = z + b.z;
    return c;
}
 
/**
 * @brief Subtract the vector by vector B
 */
inline Vec3 Vec3::operator - (const Vec3 &b) const {
    Vec3 c;
    c.x = x - b.x;
    c.y = y - b.y;
    c.z = z - b.z;
    return c;
}
 
/**
 * @brief Subtract the vector by vector B
 */
inline Vec3 Vec3::operator - () const {
    return Vec3(-x, -y, -z);
}

/**
 * @brief Multiply the vector by a number
 */
inline Vec3 Vec3::operator * (float f) const {
    Vec3 v;
    v.x = f * x;
    v.y = f * y;
    v.z = f * z;
    return v;
}

/**
 * @brief Divide the vector by a number
 */
inline Vec3 Vec3::operator / (float f) const {
    Vec3 v;
    v.x = x/f;
    v.y = y/f;
    v.z = z/f;
    return v;
}

/**
 * @brief Vector cross product operation
 */
inline Vec3 Vec3::operator * (const Vec3 &b) const {
    return Vec3::cross(*this, b);
}

/**
 * @brief Multiply the vector by a number
 */
inline Vec3 operator * (float f, const Vec3 &v) {
    Vec3 u;
    u.x = f * v.x;
    u.y = f * v.y;
    u.z = f * v.z;
    return u;
}

/**
 * @brief Adds 2 vectors
 */
inline Vec3& Vec3::operator += (const Vec3 &b) {
    x += b.x;
    y += b.y;
    z += b.z;
    return *this;
}

/**
 * @brief Subtract the vector by vector B
 */
inline Vec3& Vec3::operator -= (const Vec3 &b) {
    x -= b.x;
    y -= b.y;
    z -= b.z;
    return *this;
}

/**
 * @brief Multiply the vector by a number
 */
inline Vec3& Vec3::operator *= (float f) {
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

/**
 * @brief Divide the vector by a number
 */
inline Vec3& Vec3::operator /= (float f) {
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

/**
 * @brief Gets reference to vector data as array subscript
 */
inline float& Vec3::operator [] (uint8_t i) {
     RMG_ASSERT(i < 3);
     return data[i];
}

/**
 * @brief Gets reference to vector data as array subscript
 */
inline float const& Vec3::operator [] (uint8_t i) const {
     RMG_ASSERT(i < 3);
     return data[i];
}

/**
 * @brief Equality operator
 */
inline bool Vec3::operator == (const Vec3 &b) const {
    return (x == b.x) && (y == b.y) && (z == b.z);
}

/**
 * @brief Unequality operator
 */
inline bool Vec3::operator != (const Vec3 &b) const {
    return (x != b.x) || (y != b.y) || (z != b.z);
}

}
