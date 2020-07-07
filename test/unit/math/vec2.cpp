#include <rmg/math/vec.hpp>

#include <gtest/gtest.h>

using namespace rmg;


/**
 * @brief Vec2 constructor test
 */
TEST(Vec2, constructor) {
    Vec2 v1 = Vec2();
    ASSERT_EQ(0, v1.x);
    ASSERT_EQ(0, v1.y);
    
    Vec2 v2 = Vec2(3.453f, -5.21f);
    ASSERT_EQ( 3.453f, v2.x);
    ASSERT_EQ(-5.210f, v2.y);
}




/**
 * @brief Vec2 magnitude and normalization test
 */
TEST(Vec2, magnitude) {
    Vec2 v = {-23.6421f, -32.453f};
    EXPECT_NEAR(40.1515f, v.magnitude(), 0.0001f);
}


TEST(Vec2, normalize) {
    Vec2 v = {18.7618f, -24.5395f};
    Vec2 n = v.normalize();
    EXPECT_NEAR( 0.6074f, n.x, 0.0001f);
    EXPECT_NEAR(-0.7944f, n.y, 0.0001f);
}




/**
 * @brief Vec2 arithmatic test
 */
TEST(Vec2, add) {
    Vec2 a = {12.3458f, -9.0323f};
    Vec2 b = { 8.1663f,  3.9226f};
    Vec2 c = a + b;
    EXPECT_NEAR(20.5121f, c.x, 0.0001f);
    EXPECT_NEAR(-5.1097f, c.y, 0.0001f);
}


TEST(Vec2, subtract) {
    Vec2 a = {20.0019f, 14.4054f};
    Vec2 b = { 8.7503f, -6.446f};
    Vec2 c = a - b;
    EXPECT_NEAR(11.2516f, c.x, 0.0001f);
    EXPECT_NEAR(20.8514f, c.y, 0.0001f);
}


TEST(Vec2, multiply) {
    Vec2 a = {13.3049f, 7.0522f};
    Vec2 b;
    b = a * 2.451f;
    EXPECT_NEAR(32.6103f, b.x, 0.0001f);
    EXPECT_NEAR(17.2849f, b.y, 0.0001f);
    b = 2.451f * a;
    EXPECT_NEAR(32.6103f, b.x, 0.0001f);
    EXPECT_NEAR(17.2849f, b.y, 0.0001f);
}


TEST(Vec2, divide) {
    Vec2 a = {20.3954f, -37.3502f};
    Vec2 b;
    b = a / 3.3106f;
    EXPECT_NEAR(  6.1606f, b.x, 0.0001f);
    EXPECT_NEAR(-11.2820f, b.y, 0.0001f);
}




/**
 * @brief Vec2 dot and cross test
 */
TEST(Vec2, dotProduct) {
    Vec2 a = {15.774f,  6.092f};
    Vec2 b = { 8.081f, -9.442f};
    EXPECT_NEAR(69.949f, Vec2::dot(a, b), 0.0001f);
}


TEST(Vec2, crossProduct) {
    Vec2 a = {15.774f,  6.092f};
    Vec2 b = { 8.081f, -9.442f};
    EXPECT_NEAR(-198.1676f, Vec2::cross(a, b), 0.0001f);
    EXPECT_NEAR(-198.1676f, a * b, 0.0001f);
}




/**
 * @brief Vec2 type conversion test
 */
TEST(Vec2, toVec3) {
    Vec2 a = {5.325f, -35.32f};
    Vec3 b = a;
    EXPECT_NEAR(  5.325f, b.x, 0.0001f);
    EXPECT_NEAR(-35.320f, b.y, 0.0001f);
    EXPECT_NEAR(  0.000f, b.z, 0.0001f);
}

TEST(Vec2, toVec4) {
    Vec2 a = {5.325f, -35.32f};
    Vec4 b = a;
    EXPECT_NEAR(  5.325f, b.x, 0.0001f);
    EXPECT_NEAR(-35.320f, b.y, 0.0001f);
    EXPECT_NEAR(  0.000f, b.z, 0.0001f);
    EXPECT_NEAR(  0.000f, b.w, 0.0001f);
}
