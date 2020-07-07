#include <rmg/math/mat4.hpp>

#include <gtest/gtest.h>

#include <rmg/math/mat3.hpp>
#include <rmg/math/vec4.hpp>

using namespace rmg;


/**
 * @brief Mat4 constructor test
 */
TEST(Mat4, constructor) {
    Mat4 I = Mat4();
    ASSERT_EQ(1, I[0][0]);
    ASSERT_EQ(0, I[0][1]);
    ASSERT_EQ(0, I[0][2]);
    ASSERT_EQ(0, I[0][3]);
    ASSERT_EQ(0, I[1][0]);
    ASSERT_EQ(1, I[1][1]);
    ASSERT_EQ(0, I[1][2]);
    ASSERT_EQ(0, I[1][3]);
    ASSERT_EQ(0, I[2][0]);
    ASSERT_EQ(0, I[2][1]);
    ASSERT_EQ(1, I[2][2]);
    ASSERT_EQ(0, I[2][3]);
    ASSERT_EQ(0, I[3][0]);
    ASSERT_EQ(0, I[3][1]);
    ASSERT_EQ(0, I[3][2]);
    ASSERT_EQ(1, I[3][3]);
    
    Mat4 M = Mat4(-12.73f);
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++)
            ASSERT_EQ(M[i][j], -12.73f);
    }
}




/**
 * @brief Matrix multiplication test
 * 
 * Check every cell of the output matrix. The correct answer is calculated
 * by hand.
 */
TEST(Mat4, multiply) {
    Mat4 A = {
      {  9.01f,  5.31f, -7.54f,  1.11f},
      { -5.00f, 16.33f, -1.94f, 11.75f},
      {  8.34f,  2.85f,  1.12f,  0.56f},
      {  0.63f, -8.52f, -0.07f,  3.85f}
    };
    Mat4 B = {
      { 4.20f,   8.54f,  -5.13f,  0.56f},
      {15.94f,  -3.37f,   7.83f, 13.01f},
      {-2.45f, -11.65f,   5.67f, -3.32f},
      { 9.09f,   0.19f, -10.06f,  4.41f}
    };
    Mat4 C = B * A;
    
    ASSERT_NEAR( -47.289f, C[0][0], 0.001f);
    ASSERT_NEAR( 142.369f, C[0][1], 0.001f);
    ASSERT_NEAR( -54.020f, C[0][2], 0.001f);
    ASSERT_NEAR( 104.290f, C[0][3], 0.001f);
    ASSERT_NEAR( 233.968f, C[1][0], 0.001f);
    ASSERT_NEAR( -58.920f, C[1][1], 0.001f);
    ASSERT_NEAR(-105.791f, C[1][2], 0.001f);
    ASSERT_NEAR(  32.569f, C[1][3], 0.001f);
    ASSERT_NEAR(  81.372f, C[2][0], 0.001f);
    ASSERT_NEAR(-158.808f, C[2][1], 0.001f);
    ASSERT_NEAR(  47.657f, C[2][2], 0.001f);
    ASSERT_NEAR(-149.214f, C[2][3], 0.001f);
    ASSERT_NEAR(  -0.171f, C[3][0], 0.001f);
    ASSERT_NEAR( -14.874f, C[3][1], 0.001f);
    ASSERT_NEAR( -80.483f, C[3][2], 0.001f);
    ASSERT_NEAR(  23.667f, C[3][3], 0.001f);
}


TEST(Mat4, multiply_order) {
    Mat4 A = {
      {-1.20f,  0.54f, -1.13f,  2.86f},
      { 0.94f, -1.47f, -1.13f, 13.71f},
      { 1.45f, -0.47f,  3.57f, -3.31f},
      { 0.59f,  0.19f, -0.06f,  1.13f}
    };
    Mat4 B = {
      { 1.31f,  2.31f,  1.54f, -1.11f},
      {-1.20f, -1.93f, -0.01f, 11.75f},
      { 0.54f,  0.85f,  1.16f, 16.56f},
      {-0.11f,  0.52f, -0.27f,  1.05f}
    };
    Mat4 C = {
      { 1.01f,  0.31f, -1.54f,  9.11f},
      {-1.00f, -2.33f, -1.94f,  4.75f},
      { 0.34f,  1.85f,  0.12f, 31.16f},
      { 0.63f,  0.52f, -0.07f,  1.25f}
    };
    Mat4 T = C * B * A;
    
    ASSERT_NEAR(  -5.909f, T[0][0], 0.001f);
    ASSERT_NEAR(  -9.349f, T[0][1], 0.001f);
    ASSERT_NEAR( -13.649f, T[0][2], 0.001f);
    ASSERT_NEAR(  62.017f, T[0][3], 0.001f);
    ASSERT_NEAR( -35.903f, T[1][0], 0.001f);
    ASSERT_NEAR( -12.241f, T[1][1], 0.001f);
    ASSERT_NEAR( -18.127f, T[1][2], 0.001f);
    ASSERT_NEAR(  -2.637f, T[1][3], 0.001f);
    ASSERT_NEAR(  40.687f, T[2][0], 0.001f);
    ASSERT_NEAR(  -8.345f, T[2][1], 0.001f);
    ASSERT_NEAR( -40.571f, T[2][2], 0.001f);
    ASSERT_NEAR( 259.736f, T[2][3], 0.001f);
    ASSERT_NEAR(   5.023f, T[3][0], 0.001f);
    ASSERT_NEAR(  -0.718f, T[3][1], 0.001f);
    ASSERT_NEAR(   0.409f, T[3][2], 0.001f);
    ASSERT_NEAR(  18.842f, T[3][3], 0.001f);
}


TEST(Mat4, multiplyVec4) {
    Mat4 M = {
      {  7.31f,  5.31f, -5.84f,  1.19f},
      {  6.12f,  1.33f,  1.94f, 21.35f},
      { -8.31f, -2.85f, -7.13f,  1.56f},
      {  3.03f, 14.52f, -1.08f,  3.75f}
    };
    Vec4 p = {-3.13f, 18.54f, 6.6f, 1.34f};
    Vec4 v = M * p;
    
    ASSERT_NEAR( 38.618f, v.x, 0.001f);
    ASSERT_NEAR( 46.916f, v.y, 0.001f);
    ASSERT_NEAR(-71.796f, v.z, 0.001f);
    ASSERT_NEAR(257.614f, v.w, 0.001f);
}


TEST(Mat4, multiplyVec4_order) {
    Mat4 A = {
      { 2.01f,  1.31f, -0.54f, 10.11f},
      {-0.20f, -2.33f, -1.94f,  8.75f},
      { 0.54f,  1.85f,  1.12f, 16.56f},
      { 0.11f,  0.52f, -0.27f,  1.25f}
    };
    Mat4 B = {
      { 1.31f, -0.31f, -0.84f,  6.19f},
      { 0.22f,  3.33f, -1.94f, 11.35f},
      {-1.31f, -1.85f, -1.13f, 21.56f},
      { 0.03f,  0.52f,  0.08f, 1.05f}
    };
    Vec4 p = {-6.53f, -8.54f, 5.3f, 3.37f};
    Vec4 v = B * A * p;
    
    ASSERT_NEAR( -53.842f, v.x, 0.001f);
    ASSERT_NEAR(  26.805f, v.y, 0.001f);
    ASSERT_NEAR(-182.985f, v.z, 0.001f);
    ASSERT_NEAR(  22.117f, v.w, 0.001f);
}




/**
 * @brief Inverse matrix test
 * 
 * Check every cell of the output matrix. The correct answer is calculated
 * by hand.
 */
TEST(Mat4, inverse) {
    Mat4 A = {
      {1.16f, -1.51f,  1.22f, 12.05f},
      {1.63f,  2.54f, -0.53f, -5.51f},
      {0.20f, -1.31f,  1.01f,  7.12f},
      {2.00f,  0.31f,  1.12f,  3.31f}
    };
    Mat4 B = A.inverse();
    
    ASSERT_NEAR( 0.9946f, B[0][0], 0.0001f);
    ASSERT_NEAR(-1.1881f, B[0][1], 0.0001f);    
    ASSERT_NEAR(-3.1642f, B[0][2], 0.0001f);
    ASSERT_NEAR( 1.2078f, B[0][3], 0.0001f);
    ASSERT_NEAR(-0.8896f, B[1][0], 0.0001f);
    ASSERT_NEAR( 1.9168f, B[1][1], 0.0001f);    
    ASSERT_NEAR( 3.6447f, B[1][2], 0.0001f);
    ASSERT_NEAR(-1.4107f, B[1][3], 0.0001f);
    ASSERT_NEAR(-1.6592f, B[2][0], 0.0001f);
    ASSERT_NEAR( 0.7751f, B[2][1], 0.0001f);    
    ASSERT_NEAR( 3.4127f, B[2][2], 0.0001f);
    ASSERT_NEAR(-0.0106f, B[2][3], 0.0001f);
    ASSERT_NEAR( 0.0437f, B[3][0], 0.0001f);
    ASSERT_NEAR( 0.2761f, B[3][1], 0.0001f);
    ASSERT_NEAR( 0.4158f, B[3][2], 0.0001f);
    ASSERT_NEAR(-0.2920f, B[3][3], 0.0001f);
}


TEST(Mat4, inverse_zeroPivot) {
    Mat4 A = {
      {0.00f,  0.00f,  1.22f,  2.15f},
      {1.63f,  2.24f, -0.53f, -5.51f},
      {1.20f, -1.31f,  1.01f,  6.22f},
      {2.00f,  0.31f,  1.12f,  1.31f}
    };
    Mat4 B = A.inverse();
    
    ASSERT_NEAR(-0.5454f, B[0][0], 0.0001f);
    ASSERT_NEAR(-0.0708f, B[0][1], 0.0001f);    
    ASSERT_NEAR( 0.0095f, B[0][2], 0.0001f);
    ASSERT_NEAR( 0.5520f, B[0][3], 0.0001f);
    ASSERT_NEAR( 1.2864f, B[1][0], 0.0001f);
    ASSERT_NEAR( 1.3518f, B[1][1], 0.0001f);    
    ASSERT_NEAR( 1.1274f, B[1][2], 0.0001f);
    ASSERT_NEAR(-1.7782f, B[1][3], 0.0001f);
    ASSERT_NEAR( 0.2196f, B[2][0], 0.0001f);
    ASSERT_NEAR(-0.7366f, B[2][1], 0.0001f);    
    ASSERT_NEAR(-0.9785f, B[2][2], 0.0001f);
    ASSERT_NEAR( 1.1875f, B[2][3], 0.0001f);
    ASSERT_NEAR( 0.3405f, B[3][0], 0.0001f);
    ASSERT_NEAR( 0.4180f, B[3][1], 0.0001f);
    ASSERT_NEAR( 0.5553f, B[3][2], 0.0001f);
    ASSERT_NEAR(-0.6738f, B[3][3], 0.0001f);
}




/**
 * @brief Mat3 to Mat4 conversion test
 */
TEST(Mat4, toMat3) {
    Mat4 A = {
      {-4.24f,   8.54f,  -5.13f,  5.56f},
      { 5.70f, -13.60f,   7.83f, 15.31f},
      { 2.45f, -11.43f, -15.77f, -3.32f},
      {19.16f,   0.19f,   0.06f,  8.16f}
    };
    Mat3 B = (Mat3) A;
    
    ASSERT_EQ( -4.24f, B[0][0]);
    ASSERT_EQ(  8.54f, B[0][1]);
    ASSERT_EQ( -5.13f, B[0][2]);
    ASSERT_EQ(  5.70f, B[1][0]);
    ASSERT_EQ(-13.60f, B[1][1]);
    ASSERT_EQ(  7.83f, B[1][2]);
    ASSERT_EQ(  2.45f, B[2][0]);
    ASSERT_EQ(-11.43f, B[2][1]);
    ASSERT_EQ(-15.77f, B[2][2]);
}
