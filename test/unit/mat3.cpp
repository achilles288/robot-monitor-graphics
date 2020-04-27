#include <rmg/math/mat3.hpp>
#include <rmg/math/mat4.hpp>
#include <rmg/math/vec3.hpp>
#include <gtest/gtest.h>


TEST(Mat3ConstructorTest, works) {
    rmg::Mat3 I = rmg::Mat3();
    ASSERT_EQ(1, I[0][0]);
    ASSERT_EQ(0, I[0][1]);
    ASSERT_EQ(0, I[0][2]);
    ASSERT_EQ(0, I[1][0]);
    ASSERT_EQ(1, I[1][1]);
    ASSERT_EQ(0, I[1][2]);
    ASSERT_EQ(0, I[2][0]);
    ASSERT_EQ(0, I[2][1]);
    ASSERT_EQ(1, I[2][2]);
    
    rmg::Mat3 M = rmg::Mat3(6.32f);
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




TEST(Mat3MultiplyTest, works) {
    rmg::Mat3 A = {
      { 11.35f,   7.54f,  -1.05f},
      { -4.80f,  21.97f, -31.75f},
      {  0.87f,  -5.33f,  14.21f}
    };
    rmg::Mat3 B = {
      {-14.81f,   2.20f,  -6.42f},
      {  6.30f,  19.32f,  21.75f},
      { 10.39f, -33.77f,  -7.84f}
    };
    rmg::Mat3 C = A * B;
    
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


TEST(Mat3MultiplyWithVec3Test, works) {
    rmg::Mat3 M = {
      { 11.54f,   7.15f,  -1.55f},
      { -4.12f,  21.13f,  -1.42f},
      {  0.86f,  13.73f,  33.60f}
    };
    rmg::Vec3 P = {-4.23f, 18.54f, 33.6f};
    rmg::Vec3 A = M * P;
    
    EXPECT_NEAR(  31.667f, A.x, 0.001f);
    EXPECT_NEAR( 361.466f, A.y, 0.001f);
    EXPECT_NEAR(1379.876f, A.z, 0.001f);
}


TEST(Mat3ToMat4Test, works) {
    rmg::Mat3 A = {
      {  1.94f,   7.29f,  19.45f},
      { -5.17f,  -9.12f,  -4.02f},
      {  8.86f, -12.63f,  11.00f}
    };
    rmg::Mat4 B = A;
    
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
