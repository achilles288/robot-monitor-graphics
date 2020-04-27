/**
 * @file mat3.cpp
 * @brief 3x3 matrix
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
Mat3::Mat3(): data {
                {1, 0, 0},
                {0, 1, 0},
                {0, 0, 1}
              }
{}

/**
 * @brief Initialize a matrix with a specific value at every cell
 * 
 * @param f Cell value
 */
Mat3::Mat3(float f) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++)
            data[i][j] = f;
    }
}

/**
 * @brief Converts Mat3 to Mat4
 */
Mat3::operator Mat4() const {
    Mat4 M;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++)
            M[i][j] = data[i][j];
    }
    for(int i=0; i<3; i++) {
        M[i][3] = 0;
        M[3][i] = 0;
    }
    M[3][3] = 1;
    return M;
}

/**
 * @brief Matrix multiplication
 * 
 * @param B Matrix B
 * 
 * @return Answer matrix
 */
Mat3 Mat3::operator * (const Mat3 &B) const {    
    Mat3 C(0);
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            for(int k=0; k<3; k++)
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
Vec3 Mat3::operator * (const Vec3 &P) const {
    Vec3 Y;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++)
            Y[i] += data[i][j] * P[j];
    }
    return Y;
}

}
