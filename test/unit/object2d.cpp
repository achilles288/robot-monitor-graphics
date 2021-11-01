#include <rmg/object2d.hpp>

#include <gtest/gtest.h>

#include <rmg/context.hpp>

using namespace rmg;


/**
 * @brief Object2D constructor test
 */
TEST(Object2D, constructor) {
    Context ctx = Context();
    Object2D obj = Object2D(&ctx);
    
    ASSERT_EQ(Alignment::MiddleCenter, obj.getAlignment());
    
    Vec3 pos = obj.getTranslation();
    ASSERT_EQ(0, pos.x);
    ASSERT_EQ(0, pos.y);
    ASSERT_EQ(0, obj.getZOrder());
    
    ASSERT_EQ(0, obj.getRotation());
    
    Vec2 size = obj.getSize();
    ASSERT_EQ(1, size.x);
    ASSERT_EQ(1, size.y);
    
    ASSERT_EQ(ObjectType::Object2D, obj.getObjectType());
}


/**
 * @brief Object2D translation test
 */
TEST(Object2D, translation) {
    Context ctx = Context();
    Object2D obj = Object2D(&ctx);
    obj.setTranslation(582.5f, 75.1f);
    Vec2 pos = obj.getTranslation();
    ASSERT_EQ(582.5f, pos.x);
    ASSERT_EQ( 75.1f, pos.y);
    
    Mat3 M = obj.getModelMatrix();
    ASSERT_EQ(582.5f, M[0][2]);
    ASSERT_EQ( 75.1f, M[1][2]);
}


/**
 * @brief Object2D rotation test
 */
TEST(Object2D, rotation) {
    Context ctx = Context();
    Object2D obj = Object2D(&ctx);
    obj.setRotation(-0.57f);
    
    Mat3 M = obj.getModelMatrix();
    ASSERT_NEAR( 0.8419f, M[0][0], 0.0001f);
    ASSERT_NEAR( 0.5396f, M[0][1], 0.0001f);
    ASSERT_NEAR(-0.5396f, M[1][0], 0.0001f);
    ASSERT_NEAR( 0.8419f, M[1][1], 0.0001f);
}


/**
 * @brief Object2D sizing test
 */
TEST(Object2D, size) {
    Context ctx = Context();
    Object2D obj1 = Object2D(&ctx);
    obj1.setSize(54.4f, 102.3f);
    Vec2 size = obj1.getSize();
    ASSERT_EQ( 54.4f, size.x);
    ASSERT_EQ(102.3f, size.y);
    Mat3 M = obj1.getModelMatrix();
    ASSERT_EQ( 54.4f, M[0][0]);
    ASSERT_EQ(102.3f, M[1][1]);
}


/**
 * @brief Object2D model transform matrix test
 */
TEST(Object2D, transform) {
    Context ctx = Context();
    Object2D obj = Object2D(&ctx);
    obj.setRotation(0.99f);
    obj.setSize(64.3f, 200.1f);
    
    Mat3 M = obj.getModelMatrix();
    ASSERT_NEAR( 35.2808f, M[0][0], 0.0001f);
    ASSERT_NEAR( -0.8360f, M[0][1], 0.0001f);
    ASSERT_NEAR(  0.8360f, M[1][0], 0.0001f);
    ASSERT_NEAR(109.7928f, M[1][1], 0.0001f);
}


/**
 * @brief Object2D assertion test
 */
TEST(Object2D, assert) {
    Context ctx = Context();
    Object2D obj = Object2D(&ctx);
    obj.setZOrder(4);
    ASSERT_EQ(4, obj.getZOrder());
    obj.setAlignment(Alignment::TopRight);
    ASSERT_EQ(Alignment::TopRight, obj.getAlignment());
}
