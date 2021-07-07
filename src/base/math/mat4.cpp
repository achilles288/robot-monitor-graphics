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


#define RMG_EXPORT


#include "../rmg/math/mat4.hpp"

#include "../rmg/math/mat3.hpp"
#include "../rmg/math/vec.hpp"


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

/**
 * @brief Gets the inverse matrix
 * 
 * Determinant checking is not included for performance. The function
 * doesn't determine if the output matrix is valid or not.
 * 
 * @return Inverse matrix
 */
Mat4 Mat4::inverse() const {
    // Gauss-Jordan elimination method
    Mat4 A = *this;
    Mat4 B;
    for(int i=0; i<4; i++) {
        // Make pivot in ith column by dividing the ith row
        float p = A[i][i];
        if(fabs(p) < 0.0001f) {
            // Pivot is zero and need to swap with another row
            for(int k=i+1; ; k++) {
                if(k >= 4)
                    return Mat4(NAN);
                if(fabs(A[k][i]) < 0.001f)
                    continue;
                Mat4Row tmp;
                tmp = A[i];
                A[i] = A[k];
                A[k] = tmp;
                tmp = B[i];
                B[i] = B[k];
                B[k] = tmp;
                p = A[i][i];
                break;
            }
        }
        for(int j=0; j<4; j++) {
            A[i][j] /= p;
            B[i][j] /= p;
        }
        // Eliminate ith column
        for(int j=0; j<4; j++) {
            if(j==i)
                continue;
            float q = A[j][i];
            for(int k=0; k<4; k++) {
                A[j][k] -= q*A[i][k];
                B[j][k] -= q*B[i][k];
            }
        }
    }
    return B;
}

}
