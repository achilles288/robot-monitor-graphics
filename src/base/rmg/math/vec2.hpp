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
 * @brief 2D vector to represent a 2D-point or a rectangular dimension
 */
struct RMG_API Vec2 {
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
     */
    Vec2 operator + (const Vec2 &b) const;
    
    /**
     * @brief Subtract the vector by vector B
     */
    Vec2 operator - (const Vec2 &b) const;
    
    /**
     * @brief Minus vector
     */
    Vec2 operator - () const;
    
    /**
     * @brief Multiply the vector by a number
     */
    Vec2 operator * (float f) const;
    
    /**
     * @brief Divide the vector by a number
     */
    Vec2 operator / (float f) const;
    
    /**
     * @brief Adds 2 vectors
     */
    Vec2& operator += (const Vec2 &b);
    
    /**
     * @brief Subtract the vector by vector B
     */
    Vec2& operator -= (const Vec2 &b);
    
    /**
     * @brief Multiply the vector by a number
     */
    Vec2& operator *= (float f);
    
    /**
     * @brief Divide the vector by a number
     */
    Vec2& operator /= (float f);
    
    /**
     * @brief Vector cross product operation
     */
    float operator * (const Vec2 &b) const;
    
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
    bool operator == (const Vec2 &b) const;
    
    /**
     * @brief Unequality operator
     */
    bool operator != (const Vec2 &b) const;
};

/**
 * @brief Multiply the vector by a number
 */
RMG_API Vec2 operator * (float f, const Vec2 &v);

/**
 * @brief Prints a vector
 */
RMG_API std::ostream& operator << (std::ostream& os, const Vec2& v);




/**
 * @brief 2D vector to represent a 2D-point or a rectangular dimension
 */
struct RMG_API Vec2i {
    int16_t x; ///< X-coordinate
    int16_t y; ///< Y-coordinate
    
    /**
     * @brief Default constructor
     */
    Vec2i();
    
    /**
     * @brief Constructor with xy values
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     */
    Vec2i(int16_t x, int16_t y);
};




/**
 * @brief A rectangular dimension or 2D point of screen coordinates
 */
struct RMG_API Rect {
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
 */
RMG_API std::ostream& operator << (std::ostream& os, const Rect& rect);

}





#include <functional>

namespace std {

/**
 * @brief Hash code for 2D vector values
 */
template<>
struct hash<rmg::Vec2> {
    /**
     * @brief Hashes the 2D vector values
     */
    size_t operator () (const rmg::Vec2& v) const noexcept {
        size_t seed = 0;
        seed ^= std::hash<float>{}(v.x) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        seed ^= std::hash<float>{}(v.y) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        return seed;
    }
};

}


#include "vec2.inc"


#endif
