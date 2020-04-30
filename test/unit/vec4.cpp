#include <rmg/math/vec.hpp>
#include <gtest/gtest.h>


TEST(Vec4, constructor) {
    rmg::Vec4 v1 = rmg::Vec4();
    ASSERT_EQ(0, v1.x);
    ASSERT_EQ(0, v1.y);
    ASSERT_EQ(0, v1.z);
    
    rmg::Vec4 v2 = rmg::Vec4(-7.35f, 17.467f, 3.536f, -4.41f);
    ASSERT_EQ(-7.350f, v2.x);
    ASSERT_EQ(17.467f, v2.y);
    ASSERT_EQ( 3.536f, v2.z);
    ASSERT_EQ(-4.410f, v2.w);
    
    rmg::Vec2 a1 = {8.349f, -6.332f};
    rmg::Vec4 b1 = rmg::Vec4(a1, 7.154f, 11.56f);
    ASSERT_EQ( 8.349f, b1.x);
    ASSERT_EQ(-6.332f, b1.y);
    ASSERT_EQ( 7.154f, b1.z);
    ASSERT_EQ(11.560f, b1.w);
    
    rmg::Vec3 a2 = {36.775f, -7.522f, 21.055f};
    rmg::Vec4 b2 = rmg::Vec4(a2, 17.156f);
    ASSERT_EQ(36.775f, b2.x);
    ASSERT_EQ(-7.522f, b2.y);
    ASSERT_EQ(21.055f, b2.z);
    ASSERT_EQ(17.156f, b2.w);
}




TEST(Vec4, magnitude) {
    rmg::Vec4 v = {7.295f, 20.553f, 14.466f, -5.689f};
    EXPECT_NEAR(26.7819f, v.magnitude(), 0.0001f);
}


TEST(Vec4, normalize) {
    rmg::Vec4 v = {-33.664f, 120.601f, 27.474f, -30.221f};
    rmg::Vec4 n = v.normalize();
    EXPECT_NEAR(-0.2556f, n.x, 0.0001f);
    EXPECT_NEAR( 0.9157f, n.y, 0.0001f);
    EXPECT_NEAR( 0.2086f, n.z, 0.0001f);
    EXPECT_NEAR(-0.2295f, n.w, 0.0001f);
}


TEST(Vec4, add) {
    rmg::Vec4 a = { 3.245f,  22.5031f, -9.3249f, 11.5644f};
    rmg::Vec4 b = {14.3375f, -7.523f,  10.9544f,  7.4801f};
    rmg::Vec4 c = a + b;
    EXPECT_NEAR(17.5825f, c.x, 0.0001f);
    EXPECT_NEAR(14.9801f, c.y, 0.0001f);
    EXPECT_NEAR( 1.6295f, c.z, 0.0001f);
    EXPECT_NEAR(19.0445f, c.w, 0.0001f);
}


TEST(Vec4, subtract) {
    rmg::Vec4 a = {16.3569f, -8.7431f, 12.435f,  19.3557f};
    rmg::Vec4 b = { 7.0503f, -6.446f,  -3.2565f, 15.2205f};
    rmg::Vec4 c = a - b;
    EXPECT_NEAR( 9.3066f, c.x, 0.0001f);
    EXPECT_NEAR(-2.2971f, c.y, 0.0001f);
    EXPECT_NEAR(15.6915f, c.z, 0.0001f);
    EXPECT_NEAR( 4.1352f, c.w, 0.0001f);
}


TEST(Vec4, multiply) {
    rmg::Vec4 a = {16.1159f, 8.8122f, -4.5105f, 0.8467f};
    rmg::Vec4 b;
    b = a * 6.3211f;
    EXPECT_NEAR(101.8702f, b.x, 0.0001f);
    EXPECT_NEAR( 55.7028f, b.y, 0.0001f);
    EXPECT_NEAR(-28.5113f, b.z, 0.0001f);
    EXPECT_NEAR(  5.3521f, b.w, 0.0001f);    
    b = 6.3211f * a;
    EXPECT_NEAR(101.8702f, b.x, 0.0001f);
    EXPECT_NEAR( 55.7028f, b.y, 0.0001f);
    EXPECT_NEAR(-28.5113f, b.z, 0.0001f);
    EXPECT_NEAR(  5.3521f, b.w, 0.0001f);
}


TEST(Vec4, divide) {
    rmg::Vec4 a = {-30.5651f, 117.3502f, 43.0063f, 10.33f};
    rmg::Vec4 b;
    b = a / 12.103f;
    EXPECT_NEAR(-2.5254f, b.x, 0.0001f);
    EXPECT_NEAR( 9.6960f, b.y, 0.0001f);
    EXPECT_NEAR( 3.5534f, b.z, 0.0001f);
    EXPECT_NEAR( 0.8535f, b.w, 0.0001f);
}




TEST(Vec4, toVec2) {
    rmg::Vec4 a = {22.056f, 9.8552f, -9.7701f, 12.5633f};
    rmg::Vec2 b = (rmg::Vec2) a;
    EXPECT_NEAR(22.0560f, b.x, 0.0001f);
    EXPECT_NEAR( 9.8552f, b.y, 0.0001f);
}

TEST(Vec4, toVec3) {
    rmg::Vec4 a = {22.056f, 9.8552f, -9.7701f, 12.5633f};
    rmg::Vec3 b = (rmg::Vec3) a;
    EXPECT_NEAR(22.0560f, b.x, 0.0001f);
    EXPECT_NEAR( 9.8552f, b.y, 0.0001f);
    EXPECT_NEAR(-9.7701f, b.z, 0.0001f);
}
