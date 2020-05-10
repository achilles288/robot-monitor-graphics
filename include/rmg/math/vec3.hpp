/**
 * @file vec3.hpp
 * @brief 3D vector to represent a 3D-point or a cubic dimension
 * 
 * Vector functions like dot product, cross product and normalization.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_VEC3_H__
#define __RMG_VEC3_H__


#include <cstdint>


namespace rmg {

struct Vec2;
struct Vec3;
struct Vec4;

/**
 * @brief 3D vector to represent a 3D-point or a cubic dimension
 */
struct Vec3 {
    /**
     * @brief To access data as xyz or array
     */
    union {
        struct {
            float x; ///< X-coordinate
            float y; ///< Y-coordinate
            float z; ///< Z-coordinate
        };
        float data[3]; ///< Vector data as array
    };
    
    /**
     * @brief Default constructor
     */
    Vec3();
    
    /**
     * @brief Constructor with xyz values
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param z Z-coordinate
     */
    Vec3(float x, float y, float z);
    
    /**
     * @brief Constructs with a 2D vector and z-coordinate
     * 
     * @param v 2D vector
     * @param c Z-coordinate
     */
    Vec3(const Vec2 &v, float c);
    
    /**
     * @brief Conversion from Vec3 to Vec2
     */
    explicit operator Vec2() const;
    
    /**
     * @brief Conversion from Vec3 to Vec4
     */
    operator Vec4() const;
    
    /**
     * @brief Gets a vector of one unit length in the same direction
     * 
     * @return Unit vector
     */
    Vec3 normalize() const;
    
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
    static float dot(const Vec3 &a, const Vec3 &b);
    
    /**
     * @brief Vector cross product operation
     * 
     * @param a Vector A
     * @param b Vector B
     * 
     * @return Cross product
     */
    static Vec3 cross(const Vec3 &a, const Vec3 &b);
    
    /**
     * @brief Adds 2 vectors
     * 
     * @param b Vector B
     * 
     * @return Sum of 2 vectors
     */
    Vec3 operator + (const Vec3 &b) const;
    
    /**
     * @brief Subtract the vector by vector B
     * 
     * @param b Vector B
     * 
     * @return Answer vector C
     */
    Vec3 operator - (const Vec3 &b) const;
    
    /**
     * @brief Multiply the vector by a number
     * 
     * @param f Multiplicant
     * 
     * @return Multiplied vector
     */
    Vec3 operator * (float f) const;
    
    /**
     * @brief Divide the vector by a number
     * 
     * @param f Divisor
     * 
     * @return Divided vector
     */
    Vec3 operator / (float f) const;
    
    /**
     * @brief Vector cross product operation
     * 
     * @param b Vector B
     * 
     * @return Cross product
     */
    Vec3 operator * (const Vec3 &b) const;
    
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
Vec3 operator * (float f, const Vec3 &v);

}


#include <rmg/math/vec3.inc>


#endif
