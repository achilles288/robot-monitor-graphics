#include <rmg/math/vec.hpp>

#include <gtest/gtest.h>

using namespace rmg;


/**
 * @brief Vec3 constructor test
 */
TEST(Vec3, constructor) {
    Vec3 v1 = Vec3();
    ASSERT_EQ(0, v1.x);
    ASSERT_EQ(0, v1.y);
    ASSERT_EQ(0, v1.z);
    
    Vec3 v2 = Vec3(-6.35f, 17.467f, 0.532f);
    ASSERT_EQ(-6.350f, v2.x);
    ASSERT_EQ(17.467f, v2.y);
    ASSERT_EQ( 0.532f, v2.z);
    
    Vec2 a = {9.505f, -6.332f};
    Vec3 b = Vec3(a, 8.231f);
    ASSERT_EQ( 9.505f, b.x);
    ASSERT_EQ(-6.332f, b.y);
    ASSERT_EQ( 8.231f, b.z);
}




/**
 * @brief Vec3 magnitude and normalization test
 */
TEST(Vec3, magnitude) {
    Vec3 v = {19.095f, -10.553f, 4.451f};
    EXPECT_NEAR(22.2665f, v.magnitude(), 0.0001f);
}


TEST(Vec3, normalize) {
    Vec3 v = {-43.764f, 30.401f, 17.664f};
    Vec3 n = v.normalize();
    EXPECT_NEAR(-0.7796f, n.x, 0.0001f);
    EXPECT_NEAR( 0.5415f, n.y, 0.0001f);
    EXPECT_NEAR( 0.3147f, n.z, 0.0001f);
}




/**
 * @brief Vec2 arithmatic test
 */
TEST(Vec3, add) {
    Vec3 a = { 3.245f,  22.5031f, -9.3249f};
    Vec3 b = {14.3375f, -7.523f,  10.9544f};
    Vec3 c = a + b;
    ASSERT_NEAR(17.5825f, c.x, 0.0001f);
    ASSERT_NEAR(14.9801f, c.y, 0.0001f);
    ASSERT_NEAR( 1.6295f, c.z, 0.0001f);
    a += b;
    ASSERT_NEAR(17.5825f, a.x, 0.0001f);
    ASSERT_NEAR(14.9801f, a.y, 0.0001f);
    ASSERT_NEAR( 1.6295f, a.z, 0.0001f);
}


TEST(Vec3, subtract) {
    Vec3 a = {16.3569f, -8.7431f, 12.435f};
    Vec3 b = { 7.0503f, -6.446f,  -3.2565f};
    Vec3 c = a - b;
    ASSERT_NEAR( 9.3066f, c.x, 0.0001f);
    ASSERT_NEAR(-2.2971f, c.y, 0.0001f);
    ASSERT_NEAR(15.6915f, c.z, 0.0001f);
    a -= b;
    ASSERT_NEAR( 9.3066f, a.x, 0.0001f);
    ASSERT_NEAR(-2.2971f, a.y, 0.0001f);
    ASSERT_NEAR(15.6915f, a.z, 0.0001f);
}


TEST(Vec3, multiply) {
    Vec3 a = {16.1159f, 8.8122f, -4.5105f};
    Vec3 b;
    b = a * 6.3211f;
    ASSERT_NEAR(101.8702f, b.x, 0.0001f);
    ASSERT_NEAR( 55.7028f, b.y, 0.0001f);
    ASSERT_NEAR(-28.5113f, b.z, 0.0001f);
    b = 6.3211f * a;
    ASSERT_NEAR(101.8702f, b.x, 0.0001f);
    ASSERT_NEAR( 55.7028f, b.y, 0.0001f);
    ASSERT_NEAR(-28.5113f, b.z, 0.0001f);
    a *= 6.3211f;
    ASSERT_NEAR(101.8702f, a.x, 0.0001f);
    ASSERT_NEAR( 55.7028f, a.y, 0.0001f);
    ASSERT_NEAR(-28.5113f, a.z, 0.0001f);
}


TEST(Vec3, divide) {
    Vec3 a = {-30.5651f, 117.3502f, 43.0063f};
    Vec3 b;
    b = a / 12.103f;
    ASSERT_NEAR(-2.5254f, b.x, 0.0001f);
    ASSERT_NEAR( 9.6960f, b.y, 0.0001f);
    ASSERT_NEAR( 3.5534f, b.z, 0.0001f);
    a /= 12.103f;
    ASSERT_NEAR(-2.5254f, a.x, 0.0001f);
    ASSERT_NEAR( 9.6960f, a.y, 0.0001f);
    ASSERT_NEAR( 3.5534f, a.z, 0.0001f);
}




/**
 * @brief Vec3 dot and cross test
 */
TEST(Vec3, dotProduct) {
    Vec3 a = {  4.567f, 7.536f, -10.230f};
    Vec3 b = {-12.090f, 8.446f,  -8.112f};
    EXPECT_NEAR(91.4198f, Vec3::dot(a, b), 0.0001f);
}


TEST(Vec3, crossProduct) {
    Vec3 a = {  4.567f, 7.536f, -10.230f};
    Vec3 b = {-12.090f, 8.446f,  -8.112f};
    Vec3 c;
    c = Vec3::cross(a, b);
    EXPECT_NEAR( 25.2705f, c.x, 0.0001f);
    EXPECT_NEAR(160.7282f, c.y, 0.0001f);
    EXPECT_NEAR(129.6831f, c.z, 0.0001f);
    c = a * b;
    EXPECT_NEAR( 25.2705f, c.x, 0.0001f);
    EXPECT_NEAR(160.7282f, c.y, 0.0001f);
    EXPECT_NEAR(129.6831f, c.z, 0.0001f);
}




/**
 * @brief Vec3 type conversion test
 */
TEST(Vec3, toVec2) {
    Vec3 a = {14.345f, 6.4344f, -9.7701f};
    Vec2 b = (Vec2) a;
    EXPECT_NEAR(14.3450f, b.x, 0.0001f);
    EXPECT_NEAR( 6.4344f, b.y, 0.0001f);
}

TEST(Vec3, toVec4) {
    Vec3 a = {14.345f, 6.4344f, -9.7701f};
    Vec4 b = a;
    EXPECT_NEAR(14.3450f, b.x, 0.0001f);
    EXPECT_NEAR( 6.4344f, b.y, 0.0001f);
    EXPECT_NEAR(-9.7701f, b.z, 0.0001f);
    EXPECT_NEAR( 0.0000f, b.w, 0.0001f);
}
