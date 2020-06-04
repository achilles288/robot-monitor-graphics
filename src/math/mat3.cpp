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


#include "../rmg/math/mat3.hpp"

#include "../rmg/math/mat4.hpp"
#include "../rmg/math/vec.hpp"


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

/**
 * @brief Gets the inverse matrix
 * 
 * Determinant checking is not included for performance. The function
 * doesn't determine if the output matrix is valid or not.
 * 
 * @return Inverse matrix
 */
Mat3 Mat3::inverse() const {
    // Gauss-Jordan elimination method
    Mat3 A = *this;
    Mat3 B;
    for(int i=0; i<3; i++) {
        // Make pivot in ith column by dividing the ith row
        float p = A[i][i];
        if(fabs(p) < 0.0001f) {
            // Pivot is zero and need to swap with another row
            for(int k=i+1; ; k++) {
                if(k >= 3)
                    return Mat3(NAN);
                if(fabs(A[k][i]) < 0.001f)
                    continue;
                Mat3Row tmp;
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
        for(int j=0; j<3; j++) {
            A[i][j] /= p;
            B[i][j] /= p;
        }
        // Eliminate ith column
        for(int j=0; j<3; j++) {
            if(j == i)
                continue;
            float q = A[j][i];
            for(int k=0; k<3; k++) {
                A[j][k] -= q*A[i][k];
                B[j][k] -= q*B[i][k];
            }
        }
    }
    return B;
}

}
