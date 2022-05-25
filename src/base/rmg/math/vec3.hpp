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

#ifndef RMG_API
#ifdef _WIN32
#ifdef RMG_EXPORT
#define RMG_API __declspec(dllexport)
#else
#define RMG_API __declspec(dllimport)
#endif
#else
#define RMG_API
#endif
#endif


#include <cstdint>
#include <ostream>


namespace rmg {

struct Vec2;
struct Vec3;
struct Vec4;

/**
 * @brief 3D vector to represent a 3D-point or a cubic dimension
 */
struct RMG_API Vec3 {
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
     */
    Vec3 operator + (const Vec3 &b) const;
    
    /**
     * @brief Subtract the vector by vector B
     */
    Vec3 operator - (const Vec3 &b) const;
    
    /**
     * @brief Minus vector
     */
    Vec3 operator - () const;
    
    /**
     * @brief Multiply the vector by a number
     */
    Vec3 operator * (float f) const;
    
    /**
     * @brief Divide the vector by a number
     */
    Vec3 operator / (float f) const;
    
    /**
     * @brief Adds 2 vectors
     */
    Vec3& operator += (const Vec3 &b);
    
    /**
     * @brief Subtract the vector by vector B
     */
    Vec3& operator -= (const Vec3 &b);
    
    /**
     * @brief Multiply the vector by a number
     */
    Vec3& operator *= (float f);
    
    /**
     * @brief Divide the vector by a number
     */
    Vec3& operator /= (float f);
    
    /**
     * @brief Vector cross product operation
     */
    Vec3 operator * (const Vec3 &b) const;
    
    /**
     * @brief Gets reference to vector data as array subscript
     */
    float& operator [] (uint8_t i);
    
    /**
     * @brief Gets reference to vector data as array subscript
     */
    float const& operator [] (uint8_t i) const;
    
    /**
     * @brief Equality operator
     */
    bool operator == (const Vec3 &b) const;
    
    /**
     * @brief Unequality operator
     */
    bool operator != (const Vec3 &b) const;
};

/**
 * @brief Multiply the vector by a number
 */
RMG_API Vec3 operator * (float f, const Vec3 &v);

/**
 * @brief Prints a vector
 */
RMG_API std::ostream& operator << (std::ostream& os, const Vec3& v);

}


#include <functional>


namespace std {

/**
 * @brief Hash code for 3D vector values
 */
template<>
struct RMG_API hash<rmg::Vec3> {
    /**
     * @brief Hashes the 3D vector values
     */
    size_t operator () (const rmg::Vec3& v) const noexcept {
        size_t seed = 0;
        seed ^= std::hash<float>{}(v.x) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        seed ^= std::hash<float>{}(v.y) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        seed ^= std::hash<float>{}(v.z) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        return seed;
    }
};

}


#include "vec3.inc"


#endif
