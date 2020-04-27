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


#include <rmg/math/vec.hpp>
#include <cassert>
#include <cmath>


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
    Vec2 v;
    v.x = x;
    v.y = y;
    return v;
}

/**
 * @brief Conversion from Vec2 to Vec4
 */
inline Vec3::operator Vec4() const {
    Vec4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = 0;
    return v;
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
 * 
 * @param b Vector B
 * 
 * @return Sum of 2 vectors
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
 * 
 * @param b Vector B
 * 
 * @return Answer vector C
 */
inline Vec3 Vec3::operator - (const Vec3 &b) const {
    Vec3 c;
    c.x = x - b.x;
    c.y = y - b.y;
    c.z = z - b.z;
    return c;
}

/**
 * @brief Multiply the vector by a number
 * 
 * @param f Multiplicant
 * 
 * @return Multiplied vector
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
 * 
 * @param f Divisor
 * 
 * @return Divided vector
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
 * 
 * @param b Vector B
 * 
 * @return Cross product
 */
inline Vec3 Vec3::operator * (const Vec3 &b) const {
    return Vec3::cross(*this, b);
}

/**
 * @brief Multiply the vector by a number
 * 
 * @param f Multiplicant
 * @param v The Vector
 * 
 * @return Multiplied vector
 */
inline Vec3 operator * (float f, const Vec3 &v) {
    Vec3 u;
    u.x = f * v.x;
    u.y = f * v.y;
    u.z = f * v.z;
    return u;
}

/**
 * @brief Gets reference to vector data as array subscript
 * 
 * @param i Index
 * 
 * @return Reference to vector member
 */
inline float& Vec3::operator [] (uint8_t i) {
     assert(i < 3);
     return data[i];
}

/**
 * @brief Gets reference to vector data as array subscript
 * 
 * @param i Index
 * 
 * @return Reference to vector member
 */
inline float const& Vec3::operator [] (uint8_t i) const{
     assert(i < 3);
     return data[i];
}

}
