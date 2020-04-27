#include <rmg/math/euler.hpp>
#include <rmg/math/mat3.hpp>
#include <gtest/gtest.h>
#include <cmath>


TEST(EulerConstructorTest, works) {
    rmg::Euler rot1 = rmg::Euler();
    ASSERT_EQ(0, rot1.roll);
    ASSERT_EQ(0, rot1.pitch);
    ASSERT_EQ(0, rot1.yaw);
    
    rmg::Euler rot2 = rmg::Euler(0.524f, 1.442f, -0.892f);
    ASSERT_EQ( 0.524f, rot2.roll);
    ASSERT_EQ( 1.442f, rot2.pitch);
    ASSERT_EQ(-0.892f, rot2.yaw);
    
    rmg::Euler rot3 = rmg::Euler(-0.824f, 0.245f, -1.873f, UNIT_RADIAN);
    ASSERT_EQ(-0.824f, rot3.roll);
    ASSERT_EQ( 0.245f, rot3.pitch);
    ASSERT_EQ(-1.873f, rot3.yaw);
    
    rmg::Euler rot4 = rmg::Euler(40.37f, 67.4f, 121.55f, UNIT_DEGREE);
    ASSERT_NEAR(0.7046f, rot4.roll,  0.0001f);
    ASSERT_NEAR(1.1764f, rot4.pitch, 0.0001f);
    ASSERT_NEAR(2.1214f, rot4.yaw,   0.0001f);
}




TEST(EulerFromMat3Test, normal) {
    rmg::Mat3 R = {
      {0.5922f, -0.8050f, -0.0356f},
      {0.6823f,  0.5244f, -0.5093f},
      {0.4287f,  0.2773f,  0.8599f}
    };
    rmg::Euler rot(R);
    EXPECT_NEAR( 0.312f, rot.roll,  0.001f);
    EXPECT_NEAR(-0.443f, rot.pitch, 0.001f);
    EXPECT_NEAR( 0.856f, rot.yaw,   0.001f);
}

TEST(EulerFromMat3Test, pitchPos90) {
    rmg::Mat3 R = {
      { 0.0000f, -0.9785f,  0.2063f},
      { 0.0000f,  0.2063f,  0.9785f},
      {-1.0000f,  0.0000f,  0.0000f}
    };
    rmg::Euler rot(R);
    EXPECT_NEAR(0.000f, rot.roll,  0.001f);
    EXPECT_NEAR(M_PI/2, rot.pitch, 0.001f);
    EXPECT_NEAR(1.363f, rot.yaw,   0.001f);
}

TEST(EulerFromMat3Test, pitchNeg90) {
    rmg::Mat3 R = {
      {0.0000f, -0.9014f, -0.4330f},
      {0.0000f,  0.4330f, -0.9014f},
      {1.0000f,  0.0000f,  0.0000f}
    };
    rmg::Euler rot(R);
    EXPECT_NEAR( 0.000f, rot.roll,  0.001f);
    EXPECT_NEAR(-M_PI/2, rot.pitch, 0.001f);
    EXPECT_NEAR( 1.123f, rot.yaw,   0.001f);
}




TEST(EulerToMat3, normal) { 
    rmg::Euler rot = {0.312f, -0.443f, 0.856f};
    rmg::Mat3 R = rot.toRotationMatrix();
    ASSERT_NEAR( 0.5922f, R[0][0], 0.0001f);
    ASSERT_NEAR(-0.8050f, R[0][1], 0.0001f);
    ASSERT_NEAR(-0.0356f, R[0][2], 0.0001f);
    ASSERT_NEAR( 0.6823f, R[1][0], 0.0001f);
    ASSERT_NEAR( 0.5244f, R[1][1], 0.0001f);
    ASSERT_NEAR(-0.5093f, R[1][2], 0.0001f);
    ASSERT_NEAR( 0.4287f, R[2][0], 0.0001f);
    ASSERT_NEAR( 0.2773f, R[2][1], 0.0001f);
    ASSERT_NEAR( 0.8599f, R[2][2], 0.0001f);
}

TEST(EulerToMat3, pitchPos90) { 
    rmg::Euler rot = {-1.028f, M_PI/2, 0.335f};
    rmg::Mat3 R = rot.toRotationMatrix();
    ASSERT_NEAR( 0.0000f, R[0][0], 0.0001f);
    ASSERT_NEAR(-0.9785f, R[0][1], 0.0001f);
    ASSERT_NEAR( 0.2063f, R[0][2], 0.0001f);
    ASSERT_NEAR( 0.0000f, R[1][0], 0.0001f);
    ASSERT_NEAR( 0.2063f, R[1][1], 0.0001f);
    ASSERT_NEAR( 0.9785f, R[1][2], 0.0001f);
    ASSERT_NEAR(-1.0000f, R[2][0], 0.0001f);
    ASSERT_NEAR( 0.0000f, R[2][1], 0.0001f);
    ASSERT_NEAR( 0.0000f, R[2][2], 0.0001f);
}
