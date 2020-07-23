#include <rmg/internal/vbo_load.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gtest/gtest.h>


using rmg::Mesh;
using rmg::Vec3;
using rmg::Vec2;


class VBO: public ::testing::Test {
  protected:
    GLFWwindow* window;
    Mesh mesh1;
    Mesh mesh2;
    
    static const Vec3 vertices[16];
    static const Vec3 normals[16];
    static const Vec2 texCoords[16];
    static const uint32_t indices[24];
    
    virtual void SetUp() {
        if(!glfwInit())
            return;
        glfwWindowHint(GLFW_SAMPLES, 4);
        window = glfwCreateWindow(300, 200, "Context", NULL, NULL);
        if(!window)
            return;
        glfwMakeContextCurrent(window);
        glewExperimental = true;
        if(glewInit() != GLEW_OK) {
            glfwDestroyWindow(window);
            return;
        }
        mesh1 = rmg::Mesh(vertices, normals, nullptr, 16, indices, 24);
        mesh2 = rmg::Mesh(vertices, normals, texCoords, 16, indices, 24);
    }
    
    virtual void TearDown() {
        glfwTerminate();
    }
};

const Vec3 VBO::vertices[16] = {
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
    
const Vec3 VBO::normals[16] = {
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

const Vec2 VBO::texCoords[16] = {
    {0, 0}, {1, 0}, {1, 1}, {0, 1},
    {0, 0}, {1, 0}, {1, 1}, {0, 1},
    {0, 0}, {1, 0}, {1, 1}, {0, 1},
    {0, 0}, {1, 0}, {1, 1}, {0, 1}
};

const uint32_t VBO::indices[24] = {
     0,  1,  2,
     2,  3,  0,
     4,  5,  6,
     6,  7,  4,
     8,  9, 10,
    10, 11,  8,
    12, 13, 14,
    14, 15, 12
};


TEST_F(VBO, load) {
    ASSERT_NE(nullptr, window);
    rmg::internal::VBO vbo1, vbo2;
    rmg::internal::VBOLoad vboLoad1(&vbo1, mesh1);
    rmg::internal::VBOLoad vboLoad2(&vbo2, mesh2);
    vboLoad1.load();
    vboLoad2.load();
    EXPECT_EQ(rmg::internal::VBOMode::Default, vbo1.getMode());
    EXPECT_EQ(rmg::internal::VBOMode::Textured, vbo2.getMode());
    glfwSwapBuffers(window);
    glfwPollEvents();
    glfwDestroyWindow(window);
}

TEST_F(VBO, draw) {
    ASSERT_NE(nullptr, window);
    rmg::internal::VBO vbo1, vbo2;
    rmg::internal::VBOLoad vboLoad1(&vbo1, mesh1);
    rmg::internal::VBOLoad vboLoad2(&vbo2, mesh2);
    vboLoad1.load();
    vboLoad2.load();
    vbo1.draw();
    vbo2.draw();
    glfwSwapBuffers(window);
    glfwPollEvents();
    glfwDestroyWindow(window);
}
