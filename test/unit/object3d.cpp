#include <rmg/object3d.hpp>

#include <gtest/gtest.h>

#include <rmg/context.hpp>
#include <rmg/config.h>
#include <rmg/internal/context_load.hpp>

using namespace rmg;


/**
 * @brief Object3D constructor test
 */
TEST(Object3D, constructor) {
    Context ctx = Context();
    Object3D obj = Object3D(&ctx);
    
    Vec3 pos = obj.getTranslation();
    ASSERT_EQ(0, pos.x);
    ASSERT_EQ(0, pos.y);
    ASSERT_EQ(0, pos.z);
    
    Euler rot = obj.getRotation();
    ASSERT_EQ(0, rot.roll);
    ASSERT_EQ(0, rot.pitch);
    ASSERT_EQ(0, rot.yaw);
    
    Vec3 scale = obj.getScale();
    ASSERT_EQ(1, scale.x);
    ASSERT_EQ(1, scale.y);
    ASSERT_EQ(1, scale.z);
    
    ASSERT_EQ(NULL, obj.getMaterial());
    ASSERT_EQ(0.0f, obj.getMetalness());
    ASSERT_EQ(0.6f, obj.getRoughness());
    ASSERT_EQ(0.6f, obj.getAmbientOcculation());
    
    ASSERT_EQ(ObjectType::Object3D, obj.getObjectType());
}


/**
 * @brief Object3D OBJ file loading test
 */
TEST(Object3D, load_obj) {
    Context ctx = Context();
    Object3D obj = Object3D(&ctx, RMG_RESOURCE_PATH "/models/teapot.obj");
    
    Vec3 pos = obj.getTranslation();
    ASSERT_EQ(0, pos.x);
    ASSERT_EQ(0, pos.y);
    ASSERT_EQ(0, pos.z);
    
    Euler rot = obj.getRotation();
    ASSERT_EQ(0, rot.roll);
    ASSERT_EQ(0, rot.pitch);
    ASSERT_EQ(0, rot.yaw);
    
    Vec3 scale = obj.getScale();
    ASSERT_EQ(1, scale.x);
    ASSERT_EQ(1, scale.y);
    ASSERT_EQ(1, scale.z);
    
    ASSERT_EQ(NULL, obj.getMaterial());
    ASSERT_EQ(0.0f, obj.getMetalness());
    ASSERT_EQ(0.6f, obj.getRoughness());
    ASSERT_EQ(0.6f, obj.getAmbientOcculation());
    
    ASSERT_EQ(ObjectType::Object3D, obj.getObjectType());
}


/**
 * @brief Object3D copy test
 */
TEST(Object3D, copy) {
    Context ctx = Context();
    Object3D obj1 = Object3D(&ctx, RMG_RESOURCE_PATH "/models/teapot.obj");
    obj1.setTranslation(3.34f, -7.85f, 6.05f);
    obj1.setRotation(0.99f, 0.73f, 2.75f);
    obj1.setScale(1.05f, 1.4f, 2.19f);
    Object3D obj2 = Object3D(obj1);
    
    Mat4 A = obj1.getModelMatrix();
    Mat4 B = obj2.getModelMatrix();
    ASSERT_EQ(A[0][0], B[0][0]);
    ASSERT_EQ(A[0][1], B[0][1]);
    ASSERT_EQ(A[0][2], B[0][2]);
    ASSERT_EQ(A[0][3], B[0][3]);
    ASSERT_EQ(A[1][0], B[1][0]);
    ASSERT_EQ(A[1][1], B[1][1]);
    ASSERT_EQ(A[1][2], B[1][2]);
    ASSERT_EQ(A[1][3], B[1][3]);
    ASSERT_EQ(A[2][0], B[2][0]);
    ASSERT_EQ(A[2][1], B[2][1]);
    ASSERT_EQ(A[2][2], B[2][2]);
    ASSERT_EQ(A[2][3], B[2][3]);
    
    Vec3 pos = obj2.getTranslation();
    ASSERT_EQ( 3.34f, pos.x);
    ASSERT_EQ(-7.85f, pos.y);
    ASSERT_EQ( 6.05f, pos.z);
    
    Euler rot = obj2.getRotation();
    ASSERT_EQ(0.99f, rot.roll);
    ASSERT_EQ(0.73f, rot.pitch);
    ASSERT_EQ(2.75f, rot.yaw);
    
    Vec3 scale = obj2.getScale();
    ASSERT_EQ(1.05f, scale.x);
    ASSERT_EQ(1.40f, scale.y);
    ASSERT_EQ(2.19f, scale.z);
    
    ASSERT_EQ(obj1.getMaterial(), obj2.getMaterial());
    ASSERT_EQ(obj1.getMetalness(), obj2.getMetalness());
    ASSERT_EQ(obj1.getRoughness(), obj2.getRoughness());
    ASSERT_EQ(obj1.getAmbientOcculation(), obj2.getAmbientOcculation());
    
    ASSERT_EQ(ObjectType::Object3D, obj2.getObjectType());
    
    ASSERT_EQ(obj1.getVBO(), obj2.getVBO());
    ASSERT_EQ(obj1.getTexture(), obj2.getTexture());;
    
    internal::ContextLoader loader;
    ASSERT_EQ(0, loader.getLoadCount());
    loader.push(obj1.getVBOLoad());
    ASSERT_EQ(1, loader.getLoadCount());
    loader.push(obj2.getVBOLoad());
    ASSERT_EQ(1, loader.getLoadCount());
    loader.push(obj1.getTextureLoad());
}


/**
 * @brief Object3D translation test
 */
TEST(Object3D, translation) {
    Context ctx = Context();
    Object3D obj = Object3D(&ctx);
    obj.setTranslation(3.34f, -7.85f, 6.05f);
    Vec3 pos = obj.getTranslation();
    ASSERT_EQ( 3.34f, pos.x);
    ASSERT_EQ(-7.85f, pos.y);
    ASSERT_EQ( 6.05f, pos.z);
    
    Mat4 M = obj.getModelMatrix();
    ASSERT_EQ( 3.34f, M[0][3]);
    ASSERT_EQ(-7.85f, M[1][3]);
    ASSERT_EQ( 6.05f, M[2][3]);
}


/**
 * @brief Object3D rotation test
 */
TEST(Object3D, rotation) {
    Context ctx = Context();
    Object3D obj = Object3D(&ctx);
    obj.setRotation(0.99f, 0.73f, 2.75f);
    
    Mat4 M = obj.getModelMatrix();
    ASSERT_NEAR(-0.6888f, M[0][0], 0.0001f);
    ASSERT_NEAR(-0.7247f, M[0][1], 0.0001f);
    ASSERT_NEAR(-0.0191f, M[0][2], 0.0001f);
    ASSERT_NEAR( 0.2844f, M[1][0], 0.0001f);
    ASSERT_NEAR(-0.2944f, M[1][1], 0.0001f);
    ASSERT_NEAR( 0.9124f, M[1][2], 0.0001f);
    ASSERT_NEAR(-0.6669f, M[2][0], 0.0001f);
    ASSERT_NEAR( 0.6230f, M[2][1], 0.0001f);
    ASSERT_NEAR( 0.4089f, M[2][2], 0.0001f);
    
    obj.setScale(1.41f, 1.09f, 2.5f);
    Euler rot = obj.getRotation();
    ASSERT_NEAR(0.99f, rot.roll, 0.001f);
    ASSERT_NEAR(0.73f, rot.pitch, 0.001f);
    ASSERT_NEAR(2.75f, rot.yaw, 0.001f);
}


/**
 * @brief Object3D scale test
 */
TEST(Object3D, scale) {
    Context ctx = Context();
    Object3D obj1 = Object3D(&ctx);
    obj1.setScale(1.71f, 0.79f, 0.5f);
    obj1.setScale(1.05f, 1.4f, 2.19f);
    Vec3 scale = obj1.getScale();
    ASSERT_EQ(1.05f, scale.x);
    ASSERT_EQ(1.40f, scale.y);
    ASSERT_EQ(2.19f, scale.z);
    Mat4 M = obj1.getModelMatrix();
    ASSERT_EQ(1.05f, M[0][0]);
    ASSERT_EQ(1.40f, M[1][1]);
    ASSERT_EQ(2.19f, M[2][2]);
    
    Object3D obj2 = Object3D(&ctx);
    obj2.setScale(1.61f, 0.88f, 1.05f);
    obj2.setScale(3.39f);
    scale = obj2.getScale();
    ASSERT_EQ(3.39f, scale.x);
    ASSERT_EQ(3.39f, scale.y);
    ASSERT_EQ(3.39f, scale.z);
    M = obj2.getModelMatrix();
    ASSERT_EQ(3.39f, M[0][0]);
    ASSERT_EQ(3.39f, M[1][1]);
    ASSERT_EQ(3.39f, M[2][2]);
}


/**
 * @brief Object3D model transform matrix test
 */
TEST(Object3D, transform) {
    Context ctx = Context();
    Object3D obj1 = Object3D(&ctx);
    obj1.setRotation(0.99f, 0.73f, 2.75f);
    obj1.setScale(1.71f, 0.79f, 0.5f);
    
    Mat4 M = obj1.getModelMatrix();
    ASSERT_NEAR(-1.1778f, M[0][0], 0.0001f);
    ASSERT_NEAR(-0.5725f, M[0][1], 0.0001f);
    ASSERT_NEAR(-0.0096f, M[0][2], 0.0001f);
    ASSERT_NEAR( 0.4863f, M[1][0], 0.0001f);
    ASSERT_NEAR(-0.2326f, M[1][1], 0.0001f);
    ASSERT_NEAR( 0.4562f, M[1][2], 0.0001f);
    ASSERT_NEAR(-1.1403f, M[2][0], 0.0001f);
    ASSERT_NEAR( 0.4922f, M[2][1], 0.0001f);
    ASSERT_NEAR( 0.2044f, M[2][2], 0.0001f);
    
    Object3D obj2 = Object3D(&ctx);
    obj2.setScale(1.88f, 1.19f, 2.5f);
    obj2.setRotation(1.99f, -1.13f, -1.75f);
    
    M = obj2.getModelMatrix();
    ASSERT_NEAR(-0.1430f, M[0][0], 0.0001f);
    ASSERT_NEAR(-0.3014f, M[0][1], 0.0001f);
    ASSERT_NEAR(-2.4110f, M[0][2], 0.0001f);
    ASSERT_NEAR(-0.7893f, M[1][0], 0.0001f);
    ASSERT_NEAR( 1.0537f, M[1][1], 0.0001f);
    ASSERT_NEAR(-0.4985f, M[1][2], 0.0001f);
    ASSERT_NEAR( 1.7003f, M[2][0], 0.0001f);
    ASSERT_NEAR( 0.4638f, M[2][1], 0.0001f);
    ASSERT_NEAR(-0.4342f, M[2][2], 0.0001f);
}


/**
 * @brief Object3D MRAO assertion test
 */
TEST(Object3D, mrao) {
    Context ctx = Context();
    Object3D obj = Object3D(&ctx);
    obj.setMetalness(0.23f);
    ASSERT_EQ(0.23f, obj.getMetalness());
    obj.setRoughness(0.51f);
    ASSERT_EQ(0.51f, obj.getRoughness());
    obj.setAmbientOcculation(0.44f);
    ASSERT_EQ(0.44f, obj.getAmbientOcculation());
    
    obj.setMRAO(0.8f, 0.13f, 0.33f);
    ASSERT_EQ(0.80f, obj.getMetalness());
    ASSERT_EQ(0.13f, obj.getRoughness());
    ASSERT_EQ(0.33f, obj.getAmbientOcculation());
}
