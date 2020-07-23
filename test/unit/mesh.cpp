#include <rmg/mesh.hpp>

#include <utility>

#include <gtest/gtest.h>

using namespace rmg;


static const Vec3 vertices1[16] = {
    {-0.5f, -0.5f, -0.5f},
    { 0.5f, -0.5f, -0.5f},
    { 0.5f, -0.5f,  0.5f},
    {-0.5f, -0.5f,  0.5f},
    { 0.5f, -0.5f, -0.5f},
    { 0.5f,  0.5f, -0.5f},
    { 0.5f,  0.5f,  0.5f},
    { 0.5f, -0.5f,  0.5f},
    { 0.5f,  0.5f, -0.5f},
    {-0.5f,  0.5f, -0.5f},
    {-0.5f,  0.5f,  0.5f},
    { 0.5f,  0.5f,  0.5f},
    {-0.5f,  0.5f, -0.5f},
    {-0.5f, -0.5f, -0.5f},
    {-0.5f, -0.5f,  0.5f},
    {-0.5f,  0.5f,  0.5f}
};
    
static const Vec3 normals1[16] = {
    { 0, -1, 0},
    { 0, -1, 0},
    { 0, -1, 0},
    { 0, -1, 0},
    { 1,  0, 0},
    { 1,  0, 0},
    { 1,  0, 0},
    { 1,  0, 0},
    { 0,  1, 0},
    { 0,  1, 0},
    { 0,  1, 0},
    { 0,  1, 0},
    {-1,  0, 0},
    {-1,  0, 0},
    {-1,  0, 0},
    {-1,  0, 0}
};

static const Vec2 texCoords1[16] = {
    {0, 0}, {1, 0}, {1, 1}, {0, 1},
    {0, 0}, {1, 0}, {1, 1}, {0, 1},
    {0, 0}, {1, 0}, {1, 1}, {0, 1},
    {0, 0}, {1, 0}, {1, 1}, {0, 1}
};

static const uint32_t indices1[24] = {
     0,  1,  2,
     2,  3,  0,
     4,  5,  6,
     6,  7,  4,
     8,  9, 10,
    10, 11,  8,
    12, 13, 14,
    14, 15, 12
};


/**
 * @brief Mesh class constructor test
 */
TEST(Mesh, constructor) {
    Mesh mesh1 = Mesh(vertices1, normals1, texCoords1, 16, indices1, 24);
    ASSERT_TRUE(mesh1.isValid());
    
    Mesh mesh2 = Mesh(vertices1, normals1, texCoords1, 16, indices1, 23);
    ASSERT_FALSE(mesh2.isValid());
    
    Mesh mesh3 = Mesh(vertices1, normals1, nullptr, 16, indices1, 24);
    ASSERT_TRUE(mesh3.isValid());
    
    Mesh mesh4;
    mesh4 = mesh1;
    ASSERT_TRUE(mesh4.isValid());
    
    Mesh mesh5;
    mesh5 = std::move(mesh3);
    ASSERT_FALSE(mesh3.isValid());
    ASSERT_TRUE(mesh5.isValid());
}
