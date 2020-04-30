#include <rmg/math/mat3.hpp>
#include <rmg/math/mat4.hpp>
#include <rmg/math/vec4.hpp>
#include <gtest/gtest.h>


TEST(Mat4, constructor) {
    rmg::Mat4 I = rmg::Mat4();
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
    
    rmg::Mat4 M = rmg::Mat4(-12.73f);
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++)
            ASSERT_EQ(M[i][j], -12.73f);
    }
}




TEST(Mat4, multiply) {
    rmg::Mat4 A = {
      { 4.20f,   8.54f,  -5.13f,  0.56f},
      {15.94f,  -3.37f,   7.83f, 13.01f},
      {-2.45f, -11.65f,   5.67f, -3.32f},
      { 9.09f,   0.19f, -10.06f,  4.41f}
    };
    rmg::Mat4 B = {
      {  9.01f,  5.31f, -7.54f,  1.11f},
      { -5.00f, 16.33f, -1.94f, 11.75f},
      {  8.34f,  2.85f,  1.12f,  0.56f},
      {  0.63f, -8.52f, -0.07f,  3.85f}
    };
    rmg::Mat4 C = A * B;
    
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


TEST(Mat4, multiplyVec4) {
    rmg::Mat4 M = {
      {  7.31f,  5.31f, -5.84f,  1.19f},
      {  6.12f,  1.33f,  1.94f, 21.35f},
      { -8.31f, -2.85f, -7.13f,  1.56f},
      {  3.03f, 14.52f, -1.08f,  3.75f}
    };
    rmg::Vec4 P = {-3.13f, 18.54f, 6.6f, 1.34f};
    rmg::Vec4 A = M * P;
    
    ASSERT_NEAR( 38.618f, A.x, 0.001f);
    ASSERT_NEAR( 46.916f, A.y, 0.001f);
    ASSERT_NEAR(-71.796f, A.z, 0.001f);
    ASSERT_NEAR(257.614f, A.w, 0.001f);
}


TEST(Mat4, toMat3) {
    rmg::Mat4 A = {
      {-4.24f,   8.54f,  -5.13f,  5.56f},
      { 5.70f, -13.60f,   7.83f, 15.31f},
      { 2.45f, -11.43f, -15.77f, -3.32f},
      {19.16f,   0.19f,   0.06f,  8.16f}
    };
    rmg::Mat3 B = (rmg::Mat3) A;
    
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
