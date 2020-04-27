/**
 * @file mat4.cpp
 * @brief 4x4 matrix
 * 
 * Matrix multiplication operator. Matricies here are row major.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include <rmg/math/mat3.hpp>
#include <rmg/math/mat4.hpp>
#include <rmg/math/vec.hpp>


namespace rmg {

/**
 * @brief Default constructor makes an identity matrix
 */
Mat4::Mat4(): data {
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
              }
{}

/**
 * @brief Initialize a matrix with a specific value at every cell
 * 
 * @param f Cell value
 */
Mat4::Mat4(float f) {
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++)
            data[i][j] = f;
    }
}

/**
 * @brief Converts Mat4 to Mat3
 */
Mat4::operator Mat3() const {
    Mat3 M;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++)
            M[i][j] = data[i][j];
    }
    return M;
}

/**
 * @brief Matrix multiplication
 * 
 * @param B Matrix B
 * 
 * @return Answer matrix
 */
Mat4 Mat4::operator * (const Mat4 &B) const {    
    Mat4 C(0);
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            for(int k=0; k<4; k++)
                C[i][j] += data[i][k] * B[k][j];
        }
    }
    return C;
}

/**
 * @brief Matrix multiplication
 * 
 * @param P A vector
 * 
 * @return Answer vector
 */
Vec4 Mat4::operator * (const Vec4 &P) const {
    Vec4 Y;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++)
            Y[i] += data[i][j] * P[j];
    }
    return Y;
}

}
