#include <rmg/internal/line3d_shader.hpp>

#include <GLFW/glfw3.h>
#include <gtest/gtest.h>

#include <rmg/config.h>
#include <rmg/context.hpp>
#include <rmg/line3d.hpp>

using namespace rmg;
using rmg::internal::glDeleteProgram;
using rmg::internal::glDeleteShader;
using rmg::internal::ContextLoader;
using rmg::internal::GLContext;
using rmg::internal::Shader;


class Line3DShader: public ::testing::Test {
  protected:
    GLFWwindow* window;
    GLContext glContext;
    
    virtual void SetUp() {
        if(!glfwInit())
            return;
        glfwWindowHint(GLFW_SAMPLES, 4);
        window = glfwCreateWindow(300, 200, "Context", NULL, NULL);
        if(!window)
            return;
        glfwMakeContextCurrent(window);
        if(glContext.init() != 0) {
            glfwDestroyWindow(window);
            return;
        }
    }
    
    virtual void TearDown() {
        glfwTerminate();
    }
};


/**
 * @brief General shader compilation and linking test
 * 
 * Checks compile timer error
 */
TEST_F(Line3DShader, compileVertex) {
    uint32_t id = Shader::compileShader(
        GL_VERTEX_SHADER,
        RMG_RESOURCE_PATH "/shaders/line3d.vs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteShader(id);
}

TEST_F(Line3DShader, compileFrag) {
    uint32_t id = Shader::compileShader(
        GL_FRAGMENT_SHADER,
        RMG_RESOURCE_PATH "/shaders/line3d.fs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteShader(id);
}

TEST_F(Line3DShader, link) {
    uint32_t id = Shader::compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/line3d.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/line3d.fs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteProgram(id);
}


/**
 * @brief General shader runtime test
 * 
 * To make sure there is no runtime error.
 * Loads the shader program and process it for a certain times in a 
 * death test.
 */
TEST_F(Line3DShader, runtime) {
    auto shader = rmg::internal::Line3DShader();
    shader.load();
    
    Context ctx;
    Line3D *line1 = new Line3D(&ctx, 0.1f);
    Line3D *line2 = new Line3D(&ctx, 0.2f);
    Line3D *line3 = new Line3D(&ctx, 0.15f);
    line1->setPoints(Vec3(-1,-2,2), Vec3(-3,0,3));
    line2->setPoints(Vec3(0,0,5), Vec3(0,-2,3));
    line3->setPoints(Vec3(2,-3,7), Vec3(-7,0,2));
    ObjectList list;
    list.push_front(line1);
    list.push_front(line2);
    list.push_front(line3);
    
    shader.render(Mat4(), list);
    glfwSwapBuffers(window);
    glfwPollEvents();
    delete line1;
    delete line2;
    delete line3;
}
