#include <rmg/object.hpp>

#include <algorithm>

#include <gtest/gtest.h>

#include <rmg/context.hpp>

using namespace rmg;


/**
 * @brief Object constructor test
 */
TEST(Object, constructor) {
    Context ctx = Context();
    Object obj1 = Object(&ctx);
    Object obj2 = Object(&ctx);
    // Tests ID increment
    uint32_t id1 = obj1.getID();
    ASSERT_EQ(id1+1, obj2.getID());
    
    ASSERT_EQ(&ctx, obj1.getContext());
    
    // Tests default color
    Color col = obj1.getColor();
    ASSERT_EQ(1.0f, col.red);
    ASSERT_EQ(1.0f, col.green);
    ASSERT_EQ(1.0f, col.blue);
    ASSERT_EQ(1.0f, col.alpha);
    
    ASSERT_EQ(false, obj1.isHidden());
    ASSERT_EQ(ObjectType::Default, obj1.getObjectType());
}


/**
 * @brief Object copy constructor test
 */
TEST(Object, copyConstructor) {
    Context ctx = Context();
    Object obj1 = Object(&ctx);
    obj1.setColor(0.96f, 0.4f, 0.0f, 0.9f);
    obj1.setHidden(true);
    
    Object obj2;
    obj2 = obj1;
    
    // Tests ID increment
    uint32_t id1 = obj1.getID();
    ASSERT_EQ(id1+1, obj2.getID());
    
    ASSERT_EQ(obj1.getContext(), obj2.getContext());
    
    Color col1 = obj1.getColor();
    Color col2 = obj2.getColor();
    ASSERT_EQ(col1.red, col2.red);
    ASSERT_EQ(col1.green, col2.green);
    ASSERT_EQ(col1.blue, col2.blue);
    ASSERT_EQ(col1.alpha, col2.alpha);
    
    ASSERT_EQ(obj1.isHidden(), obj2.isHidden());
    ASSERT_EQ(obj1.getObjectType(), obj2.getObjectType());
}


/**
 * @brief Object move constructor test
 */
TEST(Object, moveConstructor) {
    Context ctx = Context();
    Object obj1 = Object(&ctx);
    obj1.setColor(0.7f, 0.7f, 0.95f, 0.6f);
    obj1.setHidden(true);
    
    uint32_t id1 = obj1.getID();
    Context *ctx1 = obj1.getContext();
    Color col1 = obj1.getColor();
    bool hidden1 = obj1.isHidden();
    
    Object obj2;
    obj2 = std::move(obj1);
    
    ASSERT_EQ(id1, obj2.getID());
    ASSERT_EQ(ctx1, obj2.getContext());
    ASSERT_EQ(hidden1, obj2.isHidden());
    Color col;
    col = obj2.getColor();
    ASSERT_EQ(col1.red, col.red);
    ASSERT_EQ(col1.green, col.green);
    ASSERT_EQ(col1.blue, col.blue);
    ASSERT_EQ(col1.alpha, col.alpha);
    ASSERT_EQ(ObjectType::Default, obj1.getObjectType());
    
    ASSERT_EQ(0, obj1.getID());
    ASSERT_EQ(nullptr, obj1.getContext());
    ASSERT_EQ(false, obj1.isHidden());
    col = obj1.getColor();
    ASSERT_EQ(1, col.red);
    ASSERT_EQ(1, col.green);
    ASSERT_EQ(1, col.blue);
    ASSERT_EQ(1, col.alpha);
    ASSERT_EQ(ObjectType::Default, obj2.getObjectType());
}


/**
 * @brief Object color assertion test
 */
TEST(Object, color) {
    Context ctx = Context();
    Object obj = Object(&ctx);
    Color col;
    col = Color(0.5f, 0.9f, 0.1f, 0.4f);
    obj.setColor(col);
    col = obj.getColor();
    EXPECT_EQ(0.5f, col.red);
    EXPECT_EQ(0.9f, col.green);
    EXPECT_EQ(0.1f, col.blue);
    EXPECT_EQ(0.4f, col.alpha);
}


/**
 * @brief Object show/hide assertion test
 */
TEST(Object, hidden) {
    Context ctx = Context();
    Object obj = Object(&ctx);
    obj.setHidden(false);
    EXPECT_EQ(false, obj.isHidden());
    obj.setHidden(true);
    EXPECT_EQ(true, obj.isHidden());
}
