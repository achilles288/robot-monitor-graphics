#include <rmg/cylinder.hpp>

#include <gtest/gtest.h>

#include <rmg/context.hpp>

using namespace rmg;


/**
 * @brief Cylinder3D constructor test
 */
TEST(Cylinder3D, constructor) {
    Context ctx = Context();
    Cylinder3D obj = Cylinder3D(&ctx, 6.62f, 2.98f);
    EXPECT_EQ(&ctx, obj.getContext());
    EXPECT_EQ(6.62f, obj.getDiameter());
    EXPECT_EQ(2.98f, obj.getLength());
}
