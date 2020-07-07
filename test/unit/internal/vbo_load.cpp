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
    
    static Vec3 vertices[16];
    static Vec3 normals[16];
    static Vec2 texCoords[16];
    
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
        uint16_t indecies[24];
        for(int i=0; i<4; i++) {
            indecies[i*6+0] = i*4 + 0;
            indecies[i*6+1] = i*4 + 1;
            indecies[i*6+2] = i*4 + 2;
            indecies[i*6+3] = i*4 + 2;
            indecies[i*6+4] = i*4 + 3;
            indecies[i*6+5] = i*4 + 0;
        }
        mesh1 = rmg::Mesh(vertices, normals, nullptr, 16, indecies, 32);
        mesh2 = rmg::Mesh(vertices, normals, texCoords, 16, indecies, 32);
    }
    
    virtual void TearDown() {
        glfwTerminate();
    }
};

Vec3 VBO::vertices[16] = {
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
    
Vec3 VBO::normals[16] = {
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

Vec2 VBO::texCoords[16] = {
    {0, 0}, {1, 0}, {1, 1}, {0, 1},
    {0, 0}, {1, 0}, {1, 1}, {0, 1},
    {0, 0}, {1, 0}, {1, 1}, {0, 1},
    {0, 0}, {1, 0}, {1, 1}, {0, 1}
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
