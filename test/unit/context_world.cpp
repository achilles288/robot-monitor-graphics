#include <rmg/context.hpp>

#include <gtest/gtest.h>

using namespace rmg;


/**
 * @brief Context ID test
 */
TEST(ContextID, increment) {
    Context ctx1 = Context();
    Context ctx2 = Context();
    uint32_t id1 = ctx1.getID();
    ASSERT_EQ(id1+1, ctx2.getID());
}


/**
 * @brief Context find by ID
 */
TEST(ContextID, find) {
    Context *ctx1 = new Context();
    Context *ctx2 = new Context();
    uint32_t id1 = ctx1->getID();
    ASSERT_EQ(ctx1, Context::getContextByID(id1));
}




/**
 * @brief Test for setter and getter of context background color
 */
TEST(ContextBackgroundColor, assertion) {
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
 * @brief Camera translation test
 * 
 * Only checks setter and getter. If getter returns the same value passed to
 * setter, the test is passed.
 */
TEST(ContextVP, cameraTranslationAssert) {
    Context ctx = Context();
    Vec3 v;
    ctx.setCameraTranslation(4.9f, -7.1f, 3.3f);
    v = ctx.getCameraTranslation();
    ASSERT_EQ( 4.9f, v.x);
    ASSERT_EQ(-7.1f, v.y);
    ASSERT_EQ( 3.3f, v.z);
    
    Vec3 p = Vec3(-5.0f, 3.2f, 14.3f);
    ctx.setCameraTranslation(p);
    v = ctx.getCameraTranslation();
    ASSERT_EQ(-5.0f, v.x);
    ASSERT_EQ( 3.2f, v.y);
    ASSERT_EQ(14.3f, v.z);
}


/**
 * @brief Camera rotation test
 * 
 * Only checks setter and getter. If getter returns the same value passed to
 * setter, the test is passed.
 */
TEST(ContextVP, cameraRotationAssert) {
    Context ctx = Context();
    ctx.setCameraRotation(0.96f, 0.65f, -2.50f);
    Euler rot = ctx.getCameraRotation();
    EXPECT_NEAR( 0.96f, rot.roll, 0.001f);
    EXPECT_NEAR( 0.65f, rot.pitch, 0.001f);
    EXPECT_NEAR(-2.50f, rot.yaw, 0.001f);
}

TEST(ContextVP, cameraRotationAssert_pitchPositive90) {
    Context ctx = Context();
    ctx.setCameraRotation(0.57f, M_PI/2, 1.51f);
    Euler rot = ctx.getCameraRotation();
    EXPECT_EQ(0, rot.roll);
    EXPECT_NEAR(M_PI/2, rot.pitch, 0.001f);
    EXPECT_NEAR(0.94f, rot.yaw, 0.001f);
}

TEST(ContextVP, cameraRotationAssert_pitchNegative90) {
    Context ctx = Context();
    ctx.setCameraRotation(-0.43f, -M_PI/2, 0.98f);
    Euler rot = ctx.getCameraRotation();
    EXPECT_EQ(0, rot.roll);
    EXPECT_NEAR(-M_PI/2, rot.pitch, 0.001f);
    EXPECT_NEAR(0.55f, rot.yaw, 0.001f);
}


/**
 * @brief Perspective FOV test
 * 
 * Only checks setter and getter. If getter returns the same value passed to
 * setter, the test is passed.
 */
TEST(ContextVP, perspectiveFOVAssert) {
    Context ctx = Context();
    ctx.setFieldOfView(radian(35.0f));
    float fov = ctx.getFieldOfView();
    EXPECT_NEAR(radian(35.0f), fov, 0.0001f);
}


/**
 * @brief World space to clip space conversion test
 * 
 * Tests the work done by the view and projection matricies.
 * Although the setter and getter tests for the matricies pass, it can't
 * be ensured that the data stored inside are correct.
 */
TEST(ContextVP, worldToClip_default) {
    Context ctx = Context();
    Vec3 p1 = ctx.worldToClip(7.56f, -1.52f, 3.01f);
    // Camera space = (1.52, 3.01, -7.56)
    ASSERT_NEAR( 0.4854f, p1.x, 0.0001f);
    ASSERT_NEAR( 0.9611f, p1.y, 0.0001f);
    ASSERT_NEAR(-0.9283f, p1.z, 0.0001f);
    
    Vec3 p2 = ctx.worldToClip(3.55f, 2.81f, -1.32f);
    // Camera space = (-2.81, -1.32, -3.55)
    ASSERT_NEAR(-1.9108f, p2.x, 0.0001f);
    ASSERT_NEAR(-0.8976f, p2.y, 0.0001f);
    ASSERT_NEAR(-0.5962f, p2.z, 0.0001f);
}

TEST(ContextVP, worldToClip_cameraTranslated) {
    Context ctx = Context();
    ctx.setCameraTranslation(-4.05f, -5.16f, 3.19f);
    Vec3 p = ctx.worldToClip( 1.52f, -3.13f, 3.98f);
    // Camera space = (-2.03, 0.79, -5.57)
    EXPECT_NEAR(-0.8798f, p.x, 0.0001f);
    EXPECT_NEAR( 0.3424f, p.y, 0.0001f);
    EXPECT_NEAR(-0.8233f, p.z, 0.0001f);
}

TEST(ContextVP, worldToClip_cameraRotated) {
    Context ctx = Context();
    ctx.setCameraRotation(30.4f, 41.3f, 155.7f, AngleUnit::Degree);
    Vec3 p = ctx.worldToClip(-2.5543f, 0.8303f, -1.9611f);
    EXPECT_NEAR(-0.2926f, p.x, 0.0001f);
    EXPECT_NEAR( 0.0731f, p.y, 0.0001f);
    EXPECT_NEAR(-0.5488f, p.z, 0.0001f);
}

TEST(ContextVP, worldToClip_cameraTransformed) {
    Context ctx = Context();
    ctx.setCameraRotation(30.4f, 41.3f, 155.7f, AngleUnit::Degree);
    ctx.setCameraTranslation(-3.0f, 2.0f, 1.0f);
    Vec3 p = ctx.worldToClip(-5.5543f, 2.8303f, -0.9611f);
    EXPECT_NEAR(-0.2926f, p.x, 0.0001f);
    EXPECT_NEAR( 0.0731f, p.y, 0.0001f);
    EXPECT_NEAR(-0.5488f, p.z, 0.0001f);
}

TEST(ContextVP, worldToClip_perspectiveAspectChanged) {
    Context ctx = Context();
    ctx.setContextSize(640, 360);
    // aspect = 9/16,  d = 2.414
    Vec3 p = ctx.worldToClip(7.56f, -1.52f, 3.01f);
    // Camera space = (1.52, 3.01, -7.56)
    EXPECT_NEAR( 0.2730f, p.x, 0.0001f);
    EXPECT_NEAR( 0.9611f, p.y, 0.0001f);
    EXPECT_NEAR(-0.9283f, p.z, 0.0001f);
}

TEST(ContextVP, worldToClip_perspectiveFOVChanged) {
    /**
     * The function involves context aspect ratio. So, if the perspective
     * matrix changed on aspect ratio change fails, this also fails.
     */
    Context ctx = Context();
    ctx.setContextSize(640, 360);
    ctx.setFieldOfView(radian(60));
    // aspect = 9/16,  d = 1/tan(30deg)
    Vec3 p = ctx.worldToClip(3.55f, 2.81f, -1.32f);
    // Camera space = (-2.81, -1.32, -3.55)
    EXPECT_NEAR(-0.7712f, p.x, 0.0001f);
    EXPECT_NEAR(-0.6440f, p.y, 0.0001f);
    EXPECT_NEAR(-0.5962f, p.z, 0.0001f);
}

TEST(ContextVP, worldToClip_perspectiveNearChanged) {
    Context ctx = Context();
    ctx.setMinimumDistance(2.5f);
    // A = 5/3,  B = 20/3
    Vec3 p = ctx.worldToClip(7.56f, -1.52f, 3.01f);
    // Camera space = (1.52, 3.01, -7.56)
    EXPECT_NEAR( 0.4854f, p.x, 0.0001f);
    EXPECT_NEAR( 0.9611f, p.y, 0.0001f);
    EXPECT_NEAR(-0.7848f, p.z, 0.0001f);
}

TEST(ContextVP, worldToClip_perspectiveFarChanged) {
    Context ctx = Context();
    ctx.setMinimumDistance(2.0f);
    ctx.setMaximumDistance(100.0f);
    // A = 51/49,  B = 200/49
    Vec3 p = ctx.worldToClip(60.55f, 12.01f, -9.62f);
    // Camera space = (-12.01, -9.62, -60.55)
    EXPECT_NEAR(-0.4788f, p.x, 0.0001f);
    EXPECT_NEAR(-0.3835f, p.y, 0.0001f);
    EXPECT_NEAR(-0.9734f, p.z, 0.0001f);
}

TEST(ContextVP, worldToClip_perspectiveChanged) {
    Context ctx = Context();
    ctx.setContextSize(400, 300);
    ctx.setPerspectiveProjection(radian(60), 2.0f, 50.0f);
    /**
     * aspect = 3/4,
     * d = 1/tan(30deg),
     * A = 13/12,
     * B = 25/6
     */
    Vec3 p = ctx.worldToClip(46.321f, 17.57f, -12.42f);
    // Camera space = (-17.57, -12.42, -46.321)
    EXPECT_NEAR(-0.4927f, p.x, 0.0001f);
    EXPECT_NEAR(-0.4644f, p.y, 0.0001f);
    EXPECT_NEAR(-0.9934f, p.z, 0.0001f);
}




/**
 * @brief Directional light vector test
 */
TEST(DirectionalLight, color) {
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

TEST(DirectionalLight, anglesAssert) {
    Context ctx = Context();
    ctx.setDirectionalLightAngles(38.13f, 120.33f, AngleUnit::Degree);
    Euler rot = ctx.getDirectionalLightAngles();
    EXPECT_EQ(0, rot.roll);
    EXPECT_NEAR(radian( 38.13f), rot.pitch, 0.0001f);
    EXPECT_NEAR(radian(120.33f), rot.yaw, 0.0001f);
}
