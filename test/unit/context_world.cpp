#include <rmg/context.hpp>

#include <gtest/gtest.h>

using namespace rmg;


/**
 * @brief Context ID test
 */
TEST(Context, id) {
    Context ctx1 = Context();
    Context ctx2 = Context();
    uint32_t id1 = ctx1.getID();
    ASSERT_EQ(id1+1, ctx2.getID());
}


/**
 * @brief Context find by ID
 */
TEST(Context, find) {
    Context *ctx1 = new Context();
    Context *ctx2 = new Context();
    uint32_t id1 = ctx1->getID();
    ASSERT_EQ(ctx1, Context::getContextByID(id1));
    delete ctx2;
    delete ctx1;
}




/**
 * @brief Test for setter and getter of context background color
 */
TEST(Context, backgroundColor) {
    Color col;
    Context ctx = Context();
    ctx.setBackgroundColor(0.8f, 0.3f, 0.35f);
    col = ctx.getBackgroundColor();
    ASSERT_EQ(0.8f, col.red);
    ASSERT_EQ(0.3f, col.green);
    ASSERT_EQ(0.35f, col.blue);
    
    Color bg = Color(0.1f, 0.4f, 0.85f);
    ctx.setBackgroundColor(bg);
    col = ctx.getBackgroundColor();
    ASSERT_EQ(0.1f, col.red);
    ASSERT_EQ(0.4f, col.green);
    ASSERT_EQ(0.85f, col.blue);
}




/**
 * @brief Directional light vector test
 */
TEST(Context, directionalLightColor) {
    Context ctx = Context();
    ctx.setDirectionalLightColor(1.0f, 0.969f, 0.769f, 0.9f);
    Color col1 = ctx.getDirectionalLightColor();
    ASSERT_EQ(1.000f, col1.red);
    ASSERT_EQ(0.969f, col1.green);
    ASSERT_EQ(0.769f, col1.blue);
    ASSERT_EQ(0.900f, col1.alpha);
    
    ctx.setDirectionalLightColor(Color(0.651f, 0.69f, 1.0f, 0.62f));
    Color col2 = ctx.getDirectionalLightColor();
    ASSERT_EQ(0.651f, col2.red);
    ASSERT_EQ(0.690f, col2.green);
    ASSERT_EQ(1.000f, col2.blue);
    ASSERT_EQ(0.620f, col2.alpha);
}

TEST(Context, directionalLightAngles) {
    Context ctx = Context();
    ctx.setDirectionalLightAngles(38.13f, 120.33f, AngleUnit::Degree);
    Euler rot = ctx.getDirectionalLightAngles();
    EXPECT_EQ(0, rot.roll);
    EXPECT_NEAR(radian( 38.13f), rot.pitch, 0.0001f);
    EXPECT_NEAR(radian(120.33f), rot.yaw, 0.0001f);
}
