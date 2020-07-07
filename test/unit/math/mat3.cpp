#include <rmg/math/mat3.hpp>

#include <gtest/gtest.h>

#include <rmg/math/mat4.hpp>
#include <rmg/math/vec3.hpp>

using namespace rmg;


/**
 * @brief Mat3 constructor test
 */
TEST(Mat3, constructor) {
    Mat3 I = Mat3();
    ASSERT_EQ(1, I[0][0]);
    ASSERT_EQ(0, I[0][1]);
    ASSERT_EQ(0, I[0][2]);
    ASSERT_EQ(0, I[1][0]);
    ASSERT_EQ(1, I[1][1]);
    ASSERT_EQ(0, I[1][2]);
    ASSERT_EQ(0, I[2][0]);
    ASSERT_EQ(0, I[2][1]);
    ASSERT_EQ(1, I[2][2]);
    
    Mat3 M = Mat3(6.32f);
    ASSERT_EQ(6.32f, M[0][0]);
    ASSERT_EQ(6.32f, M[0][1]);
    ASSERT_EQ(6.32f, M[0][2]);
    ASSERT_EQ(6.32f, M[1][0]);
    ASSERT_EQ(6.32f, M[1][1]);
    ASSERT_EQ(6.32f, M[1][2]);
    ASSERT_EQ(6.32f, M[2][0]);
    ASSERT_EQ(6.32f, M[2][1]);
    ASSERT_EQ(6.32f, M[2][2]);
}




/**
 * @brief Matrix multiplication test
 * 
 * Check every cell of the output matrix. The correct answer is calculated
 * by hand.
 */
TEST(Mat3, multiply) {
    Mat3 A = {
      {-14.81f,   2.20f,  -6.42f},
      {  6.30f,  19.32f,  21.75f},
      { 10.39f, -33.77f,  -7.84f}
    };
    Mat3 B = {
      { 11.35f,   7.54f,  -1.05f},
      { -4.80f,  21.97f, -31.75f},
      {  0.87f,  -5.33f,  14.21f}
    };
    Mat3 C = B * A;
    
    ASSERT_NEAR(-131.501f, C[0][0], 0.001f);
    ASSERT_NEAR( 206.101f, C[0][1], 0.001f);
    ASSERT_NEAR(  99.360f, C[0][2], 0.001f);
    ASSERT_NEAR(-120.384f, C[1][0], 0.001f);
    ASSERT_NEAR(1486.098f, C[1][1], 0.001f);
    ASSERT_NEAR( 757.584f, C[1][2], 0.001f);
    ASSERT_NEAR( 101.178f, C[2][0], 0.001f);
    ASSERT_NEAR(-580.933f, C[2][1], 0.001f);
    ASSERT_NEAR(-232.919f, C[2][2], 0.001f);
}


TEST(Mat3, multiply_order) {
    Mat3 A = {
      { 1.35f,  1.54f, -7.05f},
      {-2.80f, -0.97f, 21.85f},
      { 0.07f, -0.31f,  1.31f}
    };
    Mat3 B = {
      {-0.81f, -0.77f, -6.42f},
      { 0.43f,  1.32f, -9.33f},
      { 0.46f,  0.33f,  1.84f}
    };
    Mat3 C = {
      { 2.91f,-1.27f, -5.42f},
      {-0.48f, 0.82f, 11.70f },
      { 0.39f,-0.07f,  1.14f}
    };
    Mat3 T = C * B * A;
    
    ASSERT_NEAR(   7.514f, T[0][0], 0.001f);
    ASSERT_NEAR(   2.434f, T[0][1], 0.001f);
    ASSERT_NEAR(-108.641f, T[0][2], 0.001f);
    ASSERT_NEAR(  -5.423f, T[1][0], 0.001f);
    ASSERT_NEAR(  -0.981f, T[1][1], 0.001f);
    ASSERT_NEAR(  95.135f, T[1][2], 0.001f);
    ASSERT_NEAR(   0.304f, T[2][0], 0.001f);
    ASSERT_NEAR(   0.214f, T[2][1], 0.001f);
    ASSERT_NEAR(  -1.295f, T[2][2], 0.001f);
}


TEST(Mat3, multiplyVec3) {
    Mat3 M = {
      { 11.54f,   7.15f,  -1.55f},
      { -4.12f,  21.13f,  -1.42f},
      {  0.86f,  13.73f,  33.60f}
    };
    Vec3 p = {-4.23f, 18.54f, 33.6f};
    Vec3 v = M * p;
    
    EXPECT_NEAR(  31.667f, v.x, 0.001f);
    EXPECT_NEAR( 361.466f, v.y, 0.001f);
    EXPECT_NEAR(1379.876f, v.z, 0.001f);
}


TEST(Mat3, multiplyVec3_order) {
    Mat3 A = {
      { 1.51f, 0.21f,  11.59f},
      {-1.12f, 2.15f, -12.92f},
      { 0.26f, 0.33f,   1.32f}
    };
    Mat3 B = {
      { 1.59f, -0.80f, -1.03f},
      {-0.68f,  3.52f, 21.50f},
      { 0.42f,  0.27f,  1.85f}
    };
    Vec3 p = {-7.43f, 8.84f, -3.62f};
    Vec3 v = B * A * p;
    
    EXPECT_NEAR(-136.968f, v.x, 0.001f);
    EXPECT_NEAR( 214.172f, v.y, 0.001f);
    EXPECT_NEAR(  -8.564f, v.z, 0.001f);
}




/**
 * @brief Inverse matrix test
 * 
 * Check every cell of the output matrix. The correct answer is calculated
 * by hand.
 */
TEST(Mat3, inverse) {
    Mat3 A = {
      {2.16f, -1.51f,  9.05f},
      {1.63f,  1.84f, -5.51f},
      {0.20f, -0.31f,  1.15f}
    };
    Mat3 B = A.inverse();
    
    ASSERT_NEAR( -0.1614f, B[0][0], 0.0001f);
    ASSERT_NEAR(  0.4229f, B[0][1], 0.0001f);
    ASSERT_NEAR(  3.2961f, B[0][2], 0.0001f);
    ASSERT_NEAR(  1.1775f, B[1][0], 0.0001f);
    ASSERT_NEAR( -0.2666f, B[1][1], 0.0001f);
    ASSERT_NEAR(-10.5440f, B[1][2], 0.0001f);
    ASSERT_NEAR(  0.3455f, B[2][0], 0.0001f);
    ASSERT_NEAR( -0.1454f, B[2][1], 0.0001f);
    ASSERT_NEAR( -2.5460f, B[2][2], 0.0001f);
}


TEST(Mat3, inverse_zeroPivot) {
    Mat3 A = {
      {0,  2, -3},
      {0, -2,  1},
      {3,  0,  2},
    };
    Mat3 B = A.inverse();
    
    ASSERT_NEAR( 0.3333f, B[0][0], 0.0001f);
    ASSERT_NEAR( 0.3333f, B[0][1], 0.0001f);
    ASSERT_NEAR( 0.3333f, B[0][2], 0.0001f);
    ASSERT_NEAR(-0.2500f, B[1][0], 0.0001f);
    ASSERT_NEAR(-0.7500f, B[1][1], 0.0001f);
    ASSERT_NEAR( 0.0000f, B[1][2], 0.0001f);
    ASSERT_NEAR(-0.5000f, B[2][0], 0.0001f);
    ASSERT_NEAR(-0.5000f, B[2][1], 0.0001f);
    ASSERT_NEAR( 0.0000f, B[2][2], 0.0001f);
}




/**
 * @brief Mat3 to Mat4 conversion test
 */
TEST(Mat3, toMat4) {
    Mat3 A = {
      {  1.94f,   7.29f,  19.45f},
      { -5.17f,  -9.12f,  -4.02f},
      {  8.86f, -12.63f,  11.00f}
    };
    Mat4 B = (Mat4) A;
    
    ASSERT_EQ(  1.94f, B[0][0]);
    ASSERT_EQ(  7.29f, B[0][1]);
    ASSERT_EQ( 19.45f, B[0][2]);
    ASSERT_EQ(  0    , B[0][3]);
    ASSERT_EQ( -5.17f, B[1][0]);
    ASSERT_EQ( -9.12f, B[1][1]);
    ASSERT_EQ( -4.02f, B[1][2]);
    ASSERT_EQ(  0    , B[1][3]);
    ASSERT_EQ(  8.86f, B[2][0]);
    ASSERT_EQ(-12.63f, B[2][1]);
    ASSERT_EQ( 11.00f, B[2][2]);
    ASSERT_EQ(  0    , B[2][3]);
    ASSERT_EQ(  0    , B[3][0]);
    ASSERT_EQ(  0    , B[3][1]);
    ASSERT_EQ(  0    , B[3][2]);
    ASSERT_EQ(  1    , B[3][3]);
}
