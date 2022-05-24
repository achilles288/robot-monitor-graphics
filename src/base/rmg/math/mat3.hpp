/**
 * @file mat3.hpp
 * @brief 3x3 matrix
 * 
 * Matrix multiplication operator. Matricies here are row major.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_MAT3_H__
#define __RMG_MAT3_H__

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

/**
 * @brief Row of a 3x3 matrix
 * 
 * Takes part in subscript operator and handles assertion.
 */
struct RMG_API Mat3Row {
    float data[3]; ///< Matrix cells
    
    /**
     * @brief Gets reference to matrix cell
     */
    float& operator [] (uint8_t i);
    
    /**
     * @brief Gets reference to matrix cell
     */
    float const& operator [] (uint8_t i) const;
};


struct Mat4;
struct Vec3;


/**
 * @brief 3x3 matrix
 * 
 * Matrix multiplication operator. Matricies here are row major.
 */
struct RMG_API Mat3 {
    /**
     * @brief Access by 2 dimensional array or array of row structures
     */
    union {
        float data[3][3]; ///< Matrix cells
        Mat3Row rows[3]; ///< Matrix rows
    };
    
    /**
     * @brief Default constructor makes an identity matrix
     */
    Mat3();
    
    /**
     * @brief Constructs with detailed cell values
     * 
     * Intented to use for brace initialization
     */
    Mat3(Mat3Row row0, Mat3Row row1, Mat3Row row2);
    
    /**
     * @brief Initialize a matrix with a specific value at every cell
     * 
     * @param f Cell value
     */
    Mat3(float f);
    
    /**
     * @brief Converts Mat3 to Mat4
     */
    explicit operator Mat4() const;
    
    /**
     * @brief Matrix multiplication
     */
    Mat3 operator * (const Mat3 &B) const;
    
    /**
     * @brief Matrix multiplication
     */
    Vec3 operator * (const Vec3 &P) const;
    
    /**
     * @brief Gets the inverse matrix
     * 
     * Determinant checking is not included for performance. The function
     * doesn't determine if the output matrix is valid or not.
     * 
     * @return Inverse matrix
     */
    Mat3 inverse() const;
    
    /**
     * @brief Gets reference to matrix row
     */
    Mat3Row& operator [] (uint8_t i);
    
    /**
     * @brief Gets reference to matrix row
     */
    Mat3Row const& operator [] (uint8_t i) const;
};

/**
 * @brief Prints a matrix with UTF-8 encoded characters
 */
RMG_API std::ostream& operator << (std::ostream& os, const Mat3& M);

}


#include "mat3.inc"


#endif
