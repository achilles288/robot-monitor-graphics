#include <rmg/context.hpp>

#include <rmg/cube.hpp>
#include <rmg/cylinder.hpp>
#include <rmg/sphere.hpp>

#include <gtest/gtest.h>

using namespace rmg;


/**
 * @brief Adding objects to container test
 */
TEST(ContextContainer, addObject) {
    Context ctx = Context();
    Object3D *cube, *cylinder, *sphere;
    cube = new Cube3D(&ctx, 4.41f, 6.44f, 3.09f);
    cylinder = new Cylinder3D(&ctx, 3.71f, 4.13f);
    sphere = new Sphere3D(&ctx, 5.05f);
    ASSERT_EQ(0, ctx.getObjectCount());
    ctx.addObject(cube);
    ASSERT_EQ(1, ctx.getObjectCount());
    ctx.addObject(cylinder);
    ASSERT_EQ(2, ctx.getObjectCount());
    ctx.addObject(sphere);
    ASSERT_EQ(3, ctx.getObjectCount());
    ctx.cleanup();
    ASSERT_EQ(0, ctx.getObjectCount());
}

TEST(ContextContainer, removeObject) {
    Context ctx = Context();
    Object3D *cube, *cylinder, *sphere;
    cube = new Cube3D(&ctx, 4.41f, 6.44f, 3.09f);
    cylinder = new Cylinder3D(&ctx, 3.71f, 4.13f);
    sphere = new Sphere3D(&ctx, 5.05f);
    ctx.addObject(cube);
    ctx.addObject(cylinder);
    ctx.addObject(sphere);
    ASSERT_EQ(3, ctx.getObjectCount());
    ctx.removeObject(cylinder);
    ASSERT_EQ(2, ctx.getObjectCount());
    ctx.removeObject(sphere);
    ASSERT_EQ(1, ctx.getObjectCount());
    ctx.cleanup();
    ASSERT_EQ(0, ctx.getObjectCount());
}
