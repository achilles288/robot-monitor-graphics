#include <rmg/internal/general_shader.hpp>

#include <GLFW/glfw3.h>
#include <gtest/gtest.h>

#include <rmg/config.h>
#include <rmg/context.hpp>
#include <rmg/cube.hpp>

using namespace rmg;
using rmg::internal::glDeleteProgram;
using rmg::internal::glDeleteShader;
using rmg::internal::ContextLoader;
using rmg::internal::GLContext;
using rmg::internal::Shader;


class GeneralShader: public ::testing::Test {
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
TEST_F(GeneralShader, compileVertex) {
    uint32_t id = Shader::compileShader(
        GL_VERTEX_SHADER,
        RMG_RESOURCE_PATH "/shaders/general.vs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteShader(id);
}

TEST_F(GeneralShader, compileFrag) {
    uint32_t id = Shader::compileShader(
        GL_FRAGMENT_SHADER,
        RMG_RESOURCE_PATH "/shaders/general.fs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteShader(id);
}

TEST_F(GeneralShader, link) {
    uint32_t id = Shader::compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/general.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/general.fs.glsl"
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
TEST_F(GeneralShader, runtime) {
    auto shader = rmg::internal::GeneralShader();
    shader.load();
    
    Context ctx;
    ContextLoader loader;
    Object3D *obj1 = new Cube3D(&ctx, 1, 1, 1);
    Object3D *obj2 = new Cube3D(&ctx, 2.2f, 1.5f, 1.5f);
    Object3D *obj3 = new Cube3D(&ctx, 1.4f, 3.5f, 3.5f);
    loader.push(obj1->getVBOLoad());
    loader.push(obj2->getVBOLoad());
    loader.push(obj3->getVBOLoad());
    loader.load();
    ObjectList list;
    list.push_front(obj1);
    list.push_front(obj2);
    list.push_front(obj3);
    
    shader.render(Mat4(), Mat4(), Mat4(), Vec3(), Color(), 0, list);
    glfwSwapBuffers(window);
    glfwPollEvents();
    delete obj1;
    delete obj2;
    delete obj3;
}
