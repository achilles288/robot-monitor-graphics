/**
 * @file vec2.hpp
 * @brief 2D vector to represent a 2D-point or a rectangular dimension
 * 
 * Vector functions like dot product, cross product and normalization.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_VEC2_H__
#define __RMG_VEC2_H__


#include <cstdint>
#include <ostream>


namespace rmg {

struct Vec2;
struct Vec3;
struct Vec4;

/**
 * @brief 2D vector to represent a 2D-point or a rectangular dimension
 */
struct Vec2 {
    /**
     * @brief To access data as xy or array
     */
    union {
        struct {
            float x; ///< X-coordinate
            float y; ///< Y-coordinate
        };
        float data[2]; ///< Vector data as array
    };
    
    /**
     * @brief Default constructor
     */
    Vec2();
    
    /**
     * @brief Constructor with xy values
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     */
    Vec2(float x, float y);
    
    /**
     * @brief Gets a vector of one unit length in the same direction
     * 
     * @return Unit vector
     */
    Vec2 normalize() const;
    
    /**
     * @brief Gets the magnitude or length of the vector
     * 
     * @return Vector magnitude
     */
    float magnitude() const;
    
    /**
     * @brief Vector dot product operation
     * 
     * @param a Vector A
     * @param b Vector B
     * 
     * @return Dot product
     */
    static float dot(const Vec2 &a, const Vec2 &b);
    
    /**
     * @brief Vector cross product operation
     * 
     * @param a Vector A
     * @param b Vector B
     * 
     * @return Cross product
     */
    static float cross(const Vec2 &a, const Vec2 &b);
    
    /**
     * @brief Conversion from Vec2 to Vec3
     */
    operator Vec3() const;
    
    /**
     * @brief Conversion from Vec2 to Vec4
     */
    operator Vec4() const;
    
    /**
     * @brief Adds 2 vectors
     * 
     * @param b Vector B
     * 
     * @return Sum of 2 vectors
     */
    Vec2 operator + (const Vec2 &b) const;
    
    /**
     * @brief Subtract the vector by vector B
     * 
     * @param b Vector B
     * 
     * @return Answer vector C
     */
    Vec2 operator - (const Vec2 &b) const;
    
    /**
     * @brief Multiply the vector by a number
     * 
     * @param f Multiplicant
     * 
     * @return Multiplied vector
     */
    Vec2 operator * (float f) const;
    
    /**
     * @brief Divide the vector by a number
     * 
     * @param f Divisor
     * 
     * @return Divided vector
     */
    Vec2 operator / (float f) const;
    
    /**
     * @brief Vector cross product operation
     * 
     * @param b Vector B
     * 
     * @return Cross product
     */
    float operator * (const Vec2 &b) const;
    
    /**
     * @brief Gets reference to vector data as array subscript
     * 
     * @param i Index
     * 
     * @return Reference to vector member
     */
    float& operator [] (uint8_t i);
    
    /**
     * @brief Gets reference to vector data as array subscript
     * 
     * @param i Index
     * 
     * @return Reference to vector member
     */
    float const& operator [] (uint8_t i) const;
};

/**
 * @brief Multiply the vector by a number
 * 
 * @param f Multiplicant
 * @param v The Vector
 * 
 * @return Multiplied vector
 */
Vec2 operator * (float f, const Vec2 &v);

/**
 * @brief Prints a vector
 * 
 * @param os Output stream
 * @param v The vector to print
 * 
 * @return Reference of passed output stream
 */
std::ostream& operator << (std::ostream& os, const Vec2& v);




/**
 * @brief A rectangular dimension or 2D point of screen coordinates
 */
struct Rect {
    uint16_t x; ///< X-coordinate
    uint16_t y; ///< Y-coordinate
    
    /**
     * @brief Default constructor
     */
    Rect();
    
    /**
     * @brief Constructor with xy values
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     */
    Rect(uint16_t x, uint16_t y);
};

/**
 * @brief Prints a screen coordinate
 * 
 * @param os Output stream
 * @param rect The rectangular dimension
 * 
 * @return Reference of passed output stream
 */
std::ostream& operator << (std::ostream& os, const Rect& rect);

}




#include "vec2.inc"


#endif
