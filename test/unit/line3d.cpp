#include <rmg/line3d.hpp>

#include <gtest/gtest.h>

#include <rmg/context.hpp>

using namespace rmg;


/**
 * @brief Line3D constructor test
 */
TEST(Line3D, constructor) {
    Context ctx = Context();
    Line3D line1 = Line3D(&ctx, 0.35f, Color(0.9f,0.1f,0.2f));
    ASSERT_EQ(0.35f, line1.getThickness());
    Color col;
    col = line1.getColor();
    ASSERT_EQ(0.9f, col.red);
    ASSERT_EQ(0.1f, col.green);
    ASSERT_EQ(0.2f, col.blue);
    
    Line3D line2 = Line3D(&ctx, 0.5f, Color(0.5f,0.2f,0.9f),
                          Vec3(1,2,-1), Vec3(3,0,-2));
    ASSERT_EQ(0.5f, line2.getThickness());
    col = line2.getColor();
    ASSERT_EQ(0.5f, col.red);
    ASSERT_EQ(0.2f, col.green);
    ASSERT_EQ(0.9f, col.blue);
    
    Vec3 p;
    p = line2.getPoint1();
    ASSERT_EQ( 1, p.x);
    ASSERT_EQ( 2, p.y);
    ASSERT_EQ(-1, p.z);
    p = line2.getPoint2();
    ASSERT_EQ( 3, p.x);
    ASSERT_EQ( 0, p.y);
    ASSERT_EQ(-2, p.z);
    
    Mat4 M = line2.getModelMatrix();
    ASSERT_NEAR( 2.0000f, M[0][0], 0.0001f);
    ASSERT_NEAR( 0.3536f, M[0][1], 0.0001f);
    ASSERT_NEAR( 0.1179f, M[0][2], 0.0001f);
    ASSERT_NEAR(-2.0000f, M[1][0], 0.0001f);
    ASSERT_NEAR( 0.3536f, M[1][1], 0.0001f);
    ASSERT_NEAR(-0.1179f, M[1][2], 0.0001f);
    ASSERT_NEAR(-1.0000f, M[2][0], 0.0001f);
    ASSERT_NEAR( 0.0000f, M[2][1], 0.0001f);
    ASSERT_NEAR( 0.4714f, M[2][2], 0.0001f);
}


/**
 * @brief Line3D point1 setter test
 */
TEST(Line3D, point1) {
    Context ctx = Context();
    Line3D line = Line3D(&ctx, 0.6f, Color(1,1,1),
                         Vec3(0,3,-1), Vec3(4,-2,2));
    line.setPoint1(2,2,5);
    Vec3 p = line.getPoint1();
    ASSERT_EQ(2, p.x);
    ASSERT_EQ(2, p.y);
    ASSERT_EQ(5, p.z);
    
    Mat4 M = line.getModelMatrix();
    ASSERT_NEAR( 2.0000f, M[0][0], 0.0001f);
    ASSERT_NEAR( 0.5367f, M[0][1], 0.0001f);
    ASSERT_NEAR( 0.1495f, M[0][2], 0.0001f);
    ASSERT_NEAR(-4.0000f, M[1][0], 0.0001f);
    ASSERT_NEAR( 0.2683f, M[1][1], 0.0001f);
    ASSERT_NEAR(-0.2990f, M[1][2], 0.0001f);
    ASSERT_NEAR(-3.0000f, M[2][0], 0.0001f);
    ASSERT_NEAR( 0.0000f, M[2][1], 0.0001f);
    ASSERT_NEAR( 0.4983f, M[2][2], 0.0001f);
}


/**
 * @brief Line3D point2 setter test
 */
TEST(Line3D, point2) {
    Context ctx = Context();
    Line3D line = Line3D(&ctx, 0.47f, Color(0.2f,0.2f,0.2f),
                         Vec3(1.9f,6.7f,-2.1f), Vec3(10.7f,-6.1f,5.5f));
    line.setPoint2(7.1f,0.3f,6.1f);
    Vec3 p = line.getPoint2();
    ASSERT_EQ(7.1f, p.x);
    ASSERT_EQ(0.3f, p.y);
    ASSERT_EQ(6.1f, p.z);
    
    Mat4 M = line.getModelMatrix();
    ASSERT_NEAR(5.2, M[0][0], 0.0001f);
    ASSERT_NEAR( 0.3648f, M[0][1], 0.0001f);
    ASSERT_NEAR(-0.2090f, M[0][2], 0.0001f);
    ASSERT_NEAR(-6.4000f, M[1][0], 0.0001f);
    ASSERT_NEAR( 0.2964f, M[1][1], 0.0001f);
    ASSERT_NEAR( 0.2572f, M[1][2], 0.0001f);
    ASSERT_NEAR( 8.2000f, M[2][0], 0.0001f);
    ASSERT_NEAR( 0.0000f, M[2][1], 0.0001f);
    ASSERT_NEAR( 0.3333f, M[2][2], 0.0001f);
}


/**
 * @brief Line3D point setter test
 */
TEST(Line3D, points) {
    Context ctx = Context();
    Line3D line = Line3D(&ctx, 0.47f, Color(0.2f,0.2f,0.2f),
                         Vec3(1.9f,6.7f,-2.1f), Vec3(10.7f,-6.1f,5.5f));
    line.setPoints(Vec3(3.5f,-1.1f,2.9f), Vec3(-2.3f,4.7f,6.6f));
    Vec3 p;
    p = line.getPoint1();
    ASSERT_EQ( 3.5f, p.x);
    ASSERT_EQ(-1.1f, p.y);
    ASSERT_EQ( 2.9f, p.z);
    p = line.getPoint2();
    ASSERT_EQ(-2.3f, p.x);
    ASSERT_EQ( 4.7f, p.y);
    ASSERT_EQ( 6.6f, p.z);
    
    Mat4 M = line.getModelMatrix();
    ASSERT_NEAR(-5.8000f, M[0][0], 0.0001f);
    ASSERT_NEAR(-0.3323f, M[0][1], 0.0001f);
    ASSERT_NEAR( 0.1367f, M[0][2], 0.0001f);
    ASSERT_NEAR( 5.8000f, M[1][0], 0.0001f);
    ASSERT_NEAR(-0.3323f, M[1][1], 0.0001f);
    ASSERT_NEAR(-0.1367f, M[1][2], 0.0001f);
    ASSERT_NEAR( 3.7000f, M[2][0], 0.0001f);
    ASSERT_NEAR( 0.0000f, M[2][1], 0.0001f);
    ASSERT_NEAR( 0.4284f, M[2][2], 0.0001f);
}


/**
 * @brief Line3D thickness setter test
 */
TEST(Line3D, thickness) {
    Context ctx = Context();
    Line3D line = Line3D(&ctx, 0.3f, Color(0,1,0),
                         Vec3(-1,3,-1), Vec3(5,0,2));
    line.setThickness(0.9f);
    ASSERT_EQ(0.9f, line.getThickness());
    
    Mat4 M = line.getModelMatrix();
    ASSERT_NEAR( 0.4025f, M[0][1], 0.0001f);
    ASSERT_NEAR(-0.3286f, M[0][2], 0.0001f);
    ASSERT_NEAR( 0.8050f, M[1][1], 0.0001f);
    ASSERT_NEAR( 0.1643f, M[1][2], 0.0001f);
    ASSERT_NEAR( 0.0000f, M[2][1], 0.0001f);
    ASSERT_NEAR( 0.8216f, M[2][2], 0.0001f);
}
