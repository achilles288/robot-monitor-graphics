#include <rmg/sphere.hpp>

#include <gtest/gtest.h>

#include <rmg/context.hpp>

using namespace rmg;


/**
 * @brief Sphere3D constructor test
 */
TEST(Sphere3D, constructor) {
    Context ctx = Context();
    Sphere3D ball = Sphere3D(&ctx, 5.73f);
    EXPECT_EQ(&ctx, ball.getContext());
    EXPECT_EQ(5.73f, ball.getDiameter());
}
