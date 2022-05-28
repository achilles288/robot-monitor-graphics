#include <rmg/internal/particle_shader.hpp>

#include <GLFW/glfw3.h>
#include <gtest/gtest.h>

#include <rmg/config.h>
#include <rmg/context.hpp>
#include <rmg/particle.hpp>

#include "../../testconf.h"

using namespace rmg;
using rmg::internal::glDeleteProgram;
using rmg::internal::glDeleteShader;
using rmg::internal::ContextLoader;
using rmg::internal::GLContext;
using rmg::internal::Shader;


class ParticleShader: public ::testing::Test {
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
TEST_F(ParticleShader, compileVertex) {
    uint32_t id = Shader::compileShader(
        GL_VERTEX_SHADER,
        RMG_RESOURCE_PATH "/shaders/particle.vs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteShader(id);
}

TEST_F(ParticleShader, compileFrag) {
    uint32_t id = Shader::compileShader(
        GL_FRAGMENT_SHADER,
        RMG_RESOURCE_PATH "/shaders/particle.fs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteShader(id);
}

TEST_F(ParticleShader, link) {
    uint32_t id = Shader::compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/particle.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/particle.fs.glsl"
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
TEST_F(ParticleShader, runtime) {
    auto shader = rmg::internal::ParticleShader();
    shader.load();
    
    Context ctx;
    ContextLoader loader;
    Particle3D *obj1 = new Particle3D(&ctx, RMG_RESOURCE_PATH "/dot.png");
    Particle3D *obj2 = new Particle3D(&ctx, RMGTEST_RESOURCE_PATH
                                            "/open_png_rgba.png");
    loader.push(obj1->getTextureLoad());
    loader.push(obj2->getTextureLoad());
    loader.load();
    ObjectList list;
    list.push_front(obj1);
    list.push_front(obj2);
    
    shader.render(Mat4(), Mat4(), list);
    glfwSwapBuffers(window);
    glfwPollEvents();
    delete obj1;
    delete obj2;
}
