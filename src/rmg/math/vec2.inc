/**
 * @file vec2.inc
 * @brief 2D vector to represent a 2D-point or a rectangular dimension
 * 
 * Vector functions like dot product, cross product and normalization.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include <rmg/math/vec.hpp>

#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265359f
#endif

#include <rmg/assert.hpp>


namespace rmg {

// Class: Vec2

/**
 * @brief Default constructor
 */
inline Vec2::Vec2() {
    x = 0;
    y = 0;
}

/**
 * @brief Constructor with xy values
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 */
inline Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

/**
 * @brief Conversion from Vec2 to Vec3
 */
inline Vec2::operator Vec3() const {
    Vec3 v;
    v.x = x;
    v.y = y;
    v.z = 0;
    return v;
}

/**
 * @brief Gets a vector of one unit length in the same direction
 * 
 * @return Unit vector
 */
inline Vec2 Vec2::normalize() const {
    float r = sqrt(x*x + y*y);
    Vec2 u;
    u.x = x/r;
    u.y = y/r;
    return u;
}

/**
 * @brief Gets the magnitude or length of the vector
 * 
 * @return Vector magnitude
 */
inline float Vec2::magnitude() const {
    return sqrt(x*x + y*y);
}

/**
 * @brief Vector dot product operation
 * 
 * @param a Vector A
 * @param b Vector B
 * 
 * @return Dot product
 */
inline float Vec2::dot(const Vec2 &a, const Vec2 &b) {
    return a.x*b.x + a.y*b.y;
}

/**
 * @brief Vector cross product operation
 * 
 * @param a Vector A
 * @param b Vector B
 * 
 * @return Cross product
 */
inline float Vec2::cross(const Vec2 &a, const Vec2 &b) {
    return a.x*b.y - b.x*a.y;
}

/**
 * @brief Conversion from Vec2 to Vec4
 */
inline Vec2::operator Vec4() const {
    Vec4 v;
    v.x = x;
    v.y = y;
    v.z = 0;
    v.w = 0;
    return v;
}

/**
 * @brief Adds 2 vectors
 * 
 * @param b Vector B
 * 
 * @return Sum of 2 vectors
 */
inline Vec2 Vec2::operator + (const Vec2 &b) const {
    Vec2 c;
    c.x = x + b.x;
    c.y = y + b.y;
    return c;
}
 
/**
 * @brief Subtract the vector by vector B
 * 
 * @param b Vector B
 * 
 * @return Answer vector C
 */
inline Vec2 Vec2::operator - (const Vec2 &b) const {
    Vec2 c;
    c.x = x - b.x;
    c.y = y - b.y;
    return c;
}

/**
 * @brief Multiply the vector by a number
 * 
 * @param f Multiplicant
 * 
 * @return Multiplied vector
 */
inline Vec2 Vec2::operator * (float f) const {
    Vec2 v;
    v.x = f * x;
    v.y = f * y;
    return v;
}

/**
 * @brief Divide the vector by a number
 * 
 * @param f Divisor
 * 
 * @return Divided vector
 */
inline Vec2 Vec2::operator / (float f) const {
    Vec2 v;
    v.x = x/f;
    v.y = y/f;
    return v;
}

/**
 * @brief Vector cross product operation
 * 
 * @param b Vector B
 * 
 * @return Cross product
 */
inline float Vec2::operator * (const Vec2 &b) const {
    return Vec2::cross(*this, b);
}

/**
 * @brief Multiply the vector by a number
 * 
 * @param f Multiplicant
 * @param v The Vector
 * 
 * @return Multiplied vector
 */
inline Vec2 operator * (float f, const Vec2 &v) {
    Vec2 u;
    u.x = f * v.x;
    u.y = f * v.y;
    return u;
}

/**
 * @brief Gets reference to vector data as array subscript
 * 
 * @param i Index
 * 
 * @return Reference to vector member
 */
inline float& Vec2::operator [] (uint8_t i) {
     RMG_ASSERT(i < 2);
     return data[i];
}

/**
 * @brief Gets reference to vector data as array subscript
 * 
 * @param i Index
 * 
 * @return Reference to vector member
 */
inline float const& Vec2::operator [] (uint8_t i) const {
     RMG_ASSERT(i < 2);
     return data[i];
}




// Class: Rect

/**
 * @brief Default constructor
 */
inline Rect::Rect() {
    x = 0;
    y = 0;
}

/**
 * @brief Constructor with xy values
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 */
inline Rect::Rect(uint16_t x, uint16_t y) {
    this->x = x;
    this->y = y;
}

}
