/**
 * @file vec4.hpp
 * @brief 4D vector
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_VEC4_H__
#define __RMG_VEC4_H__


#include <cstdint>
#include <ostream>


namespace rmg {

struct Vec2;
struct Vec3;
struct Vec4;

/**
 * @brief 4D vector
 */
struct Vec4 {
    /**
     * @brief To access data as xyzw or array
     */
    union {
        struct {
            float x; ///< X-coordinate
            float y; ///< Y-coordinate
            float z; ///< Z-coordinate
            float w; ///< W-coordinate (4th coordinate)
        };
        float data[4]; ///< Vector data as array
    };
    
    /**
     * @brief Default constructor
     */
    Vec4();
    
    /**
     * @brief Constructor with xyzw values
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param z Z-coordinate
     * @param w W-coordinate (4th coordinate)
     */
    Vec4(float x, float y, float z, float w);
    
    /**
     * @brief Constructs with a 2D vector and 2 remaining components
     * 
     * @param v 2D vector
     * @param c Z-coordinate
     * @param d W-coordinate
     */
    Vec4(const Vec2 &v, float c, float d);
    
    /**
     * @brief Constructs with a 3D vector and a remaining component
     * 
     * @param v 3D vector
     * @param d W-coordinate
     */
    Vec4(const Vec3 &v, float d);
    
    /**
     * @brief Conversion from Vec4 to Vec2
     */
    explicit operator Vec2() const;
    
    /**
     * @brief Conversion from Vec4 to Vec3
     */
    explicit operator Vec3() const;
    
    /**
     * @brief Gets a vector of one unit length in the same direction
     * 
     * @return Unit vector
     */
    Vec4 normalize() const;
    
    /**
     * @brief Gets the magnitude or length of the vector
     * 
     * @return Vector magnitude
     */
    float magnitude() const;
    
    /**
     * @brief Adds 2 vectors
     * 
     * @param b Vector B
     * 
     * @return Sum of 2 vectors
     */
    Vec4 operator + (const Vec4 &b) const;
    
    /**
     * @brief Subtract the vector by vector B
     * 
     * @param b Vector B
     * 
     * @return Answer vector C
     */
    Vec4 operator - (const Vec4 &b) const;
    
    /**
     * @brief Multiply the vector by a number
     * 
     * @param f Multiplicant
     * 
     * @return Multiplied vector
     */
    Vec4 operator * (float f) const;
    
    /**
     * @brief Divide the vector by a number
     * 
     * @param f Divisor
     * 
     * @return Divided vector
     */
    Vec4 operator / (float f) const;
    
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
Vec4 operator * (float f, const Vec4 &v);

/**
 * @brief Prints a vector
 * 
 * @param os Output stream
 * @param v The vector to print
 * 
 * @return Reference of passed output stream
 */
std::ostream& operator << (std::ostream& os, const Vec4& v);

}


#include <rmg/math/vec4.inc>


#endif
