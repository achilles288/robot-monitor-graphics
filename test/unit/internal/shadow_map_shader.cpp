#include <rmg/internal/shadow_map_shader.hpp>

#include <map>
#include <utility>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <gtest/gtest.h>

#include <rmg/config.h>
#include <rmg/context.hpp>
#include <rmg/cube.hpp>

using namespace rmg;
using rmg::internal::ContextLoader;
using rmg::internal::Shader;


class ShadowMapShader: public ::testing::Test {
  protected:
    GLFWwindow* window;
    
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
    }
    
    virtual void TearDown() {
        glfwTerminate();
    }
};


/**
 * @brief Shadow map shader compilation and linking test
 * 
 * Checks compile timer error
 */
TEST_F(ShadowMapShader, compileVertex) {
    uint32_t id = Shader::compileShader(
        GL_VERTEX_SHADER,
        RMG_RESOURCE_PATH "/shaders/shadow_map.vs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteShader(id);
}

TEST_F(ShadowMapShader, compileFrag) {
    uint32_t id = Shader::compileShader(
        GL_FRAGMENT_SHADER,
        RMG_RESOURCE_PATH "/shaders/shadow_map.fs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteShader(id);
}

TEST_F(ShadowMapShader, link) {
    uint32_t id = Shader::compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/shadow_map.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/shadow_map.fs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteProgram(id);
}


/**
 * @brief Shadow map shader runtime test
 * 
 * To make sure there is no runtime error.
 * Loads the shader program and process it for a certain times in a 
 * death test.
 */
TEST_F(ShadowMapShader, runtime) {
    auto shader = rmg::internal::ShadowMapShader();
    shader.load();
    
    std::map<uint64_t, Object3D*> list;
    Context ctx;
    ContextLoader loader;
    Object3D *obj1 = new Cube3D(&ctx, 1, 1, 1);
    Object3D *obj2 = new Cube3D(&ctx, 2.2f, 1.5f, 1.5f);
    Object3D *obj3 = new Cube3D(&ctx, 1.4f, 3.5f, 3.5f);
    loader.push(obj1->getVBOLoad());
    loader.push(obj2->getVBOLoad());
    loader.push(obj3->getVBOLoad());
    loader.load();
    list.insert(std::pair<uint64_t,Object3D*>(1, obj1));
    list.insert(std::pair<uint64_t,Object3D*>(2, obj2));
    list.insert(std::pair<uint64_t,Object3D*>(3, obj3));
    
    uint32_t res = shader.createShadowMap(list);
    EXPECT_NE(0, res);
    glfwSwapBuffers(window);
    glfwPollEvents();
    delete obj1;
    delete obj2;
    delete obj3;
}
