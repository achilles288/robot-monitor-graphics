#include <rmg/cube.hpp>

#include <gtest/gtest.h>

#include <rmg/context.hpp>

using namespace rmg;


/**
 * @brief Cube3D constructor test
 */
TEST(Cube3D, constructor) {
    Context ctx = Context();
    Cube3D cube = Cube3D(&ctx, 3.42f, 6.33f, 2.08f);
    EXPECT_EQ(&ctx, cube.getContext());
    Vec3 dim = cube.getDimension();
    EXPECT_EQ(3.42f, dim.x);
    EXPECT_EQ(6.33f, dim.y);
    EXPECT_EQ(2.08f, dim.z);
}
