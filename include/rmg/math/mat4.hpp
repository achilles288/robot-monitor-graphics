/**
 * @file mat4.hpp
 * @brief 4x4 matrix
 * 
 * Matrix multiplication operator. Matricies here are row major.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_MAT4_H__
#define __RMG_MAT4_H__


#include <cstdint>


namespace rmg {

/**
 * @brief Row of a 4x4 matrix
 * 
 * Takes part in subscript operator and handles assertion.
 */
struct Mat4Row {
    float data[4]; /**< Matrix cells */
    
    /**
     * @brief Gets reference to matrix cell
     * 
     * @param i Column index
     * 
     * @return Reference to matrix cell
     */
    float& operator [] (uint8_t i);
    
    /**
     * @brief Gets reference to matrix cell
     * 
     * @param i Column index
     * 
     * @return Reference to matrix cell
     */
    float const& operator [] (uint8_t i) const;
};


struct Mat3;
struct Vec4;


/**
 * @brief 4x4 matrix
 * 
 * Matrix multiplication operator. Matricies here are row major.
 */
struct Mat4 {
    /**
     * @brief Access by 2 dimensional array or array of row structures
     * 
     * Row structure is used for assertion during subscript operation.
     */
    union {
        float data[4][4]; /**< Matrix cells */
        Mat4Row rows[4]; /**< Matrix rows */
    };
    
    /**
     * @brief Default constructor makes an identity matrix
     */
    Mat4();
    
    /**
     * @brief Constructs with detailed cell values
     * 
     * Intented to use for brace initialization
     */
    Mat4(Mat4Row row0, Mat4Row row1, Mat4Row row2, Mat4Row row3);
    
    /**
     * @brief Initialize a matrix with a specific value at every cell
     * 
     * @param f Cell value
     */
    Mat4(float f);
    
    /**
     * @brief Converts Mat4 to Mat3
     */
    explicit operator Mat3() const;
    
    /**
     * @brief Matrix multiplication
     * 
     * @param B Matrix B
     * 
     * @return Answer matrix
     */
    Mat4 operator * (const Mat4 &B) const;
    
    /**
     * @brief Matrix multiplication
     * 
     * @param P A vector
     * 
     * @return Answer vector
     */
    Vec4 operator * (const Vec4 &P) const;
    
    /**
     * @brief Gets reference to matrix row
     * 
     * @param i Row index
     * 
     * @return Reference to matrix row
     */
    Mat4Row& operator [] (uint8_t i);
    
    /**
     * @brief Gets reference to matrix row
     * 
     * @param i Row index
     * 
     * @return Reference to matrix row
     */
    Mat4Row const& operator [] (uint8_t i) const;
};

}


#include <rmg/math/mat4.inc>


#endif