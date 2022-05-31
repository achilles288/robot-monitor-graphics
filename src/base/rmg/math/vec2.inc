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


#include "vec.hpp"

#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265359f
#endif

#include "../assert.hpp"


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
    return Vec3(x, y, 0);
}

/**
 * @brief Conversion from Vec2 to Vec4
 */
inline Vec2::operator Vec4() const {
    return Vec4(x, y, 0, 0);
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
 * @brief Adds 2 vectors
 */
inline Vec2 Vec2::operator + (const Vec2 &b) const {
    Vec2 c;
    c.x = x + b.x;
    c.y = y + b.y;
    return c;
}

/**
 * @brief Subtract the vector by vector B
 */
inline Vec2 Vec2::operator - (const Vec2 &b) const {
    Vec2 c;
    c.x = x - b.x;
    c.y = y - b.y;
    return c;
}

/**
 * @brief Minus vector
 */
inline Vec2 Vec2::operator - () const {
    return Vec2(-x, -y);
}

/**
 * @brief Multiply the vector by a number
 */
inline Vec2 Vec2::operator * (float f) const {
    Vec2 v;
    v.x = f * x;
    v.y = f * y;
    return v;
}

/**
 * @brief Divide the vector by a number
 */
inline Vec2 Vec2::operator / (float f) const {
    Vec2 v;
    v.x = x/f;
    v.y = y/f;
    return v;
}

/**
 * @brief Adds 2 vectors
 */
inline Vec2& Vec2::operator += (const Vec2 &b) {
    x += b.x;
    y += b.y;
    return *this;
}

/**
 * @brief Subtract the vector by vector B
 */
inline Vec2& Vec2::operator -= (const Vec2 &b) {
    x -= b.x;
    y -= b.y;
    return *this;
}

/**
 * @brief Multiply the vector by a number
 */
inline Vec2& Vec2::operator *= (float f) {
    x *= f;
    y *= f;
    return *this;
}

/**
 * @brief Divide the vector by a number
 */
inline Vec2& Vec2::operator /= (float f) {
    x /= f;
    y /= f;
    return *this;
}

/**
 * @brief Vector cross product operation
 */
inline float Vec2::operator * (const Vec2 &b) const {
    return Vec2::cross(*this, b);
}

/**
 * @brief Multiply the vector by a number
 */
inline Vec2 operator * (float f, const Vec2 &v) {
    Vec2 u;
    u.x = f * v.x;
    u.y = f * v.y;
    return u;
}

/**
 * @brief Gets reference to vector data as array subscript
 */
inline float& Vec2::operator [] (uint8_t i) {
     RMG_ASSERT(i < 2);
     return data[i];
}

/**
 * @brief Gets reference to vector data as array subscript
 */
inline float const& Vec2::operator [] (uint8_t i) const {
     RMG_ASSERT(i < 2);
     return data[i];
}

/**
 * @brief Equality operator
 */
inline bool Vec2::operator == (const Vec2 &b) const {
    return (x == b.x) && (y == b.y);
}

/**
 * @brief Unquality operator
 */
inline bool Vec2::operator != (const Vec2 &b) const {
    return (x != b.x) || (y != b.y);
}




// Class: Vec2i

/**
 * @brief Default constructor
 */
inline Vec2i::Vec2i() {
    x = 0;
    y = 0;
}

/**
 * @brief Constructor with xy values
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 */
inline Vec2i::Vec2i(int16_t x, int16_t y) {
    this->x = x;
    this->y = y;
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
