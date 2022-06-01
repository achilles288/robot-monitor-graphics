#include <rmg/internal/object2d_shader.hpp>

#include <GLFW/glfw3.h>
#include <gtest/gtest.h>

#include <rmg/config.h>
#include <rmg/context.hpp>
#include <rmg/sprite.hpp>

#include "../../testconf.h"

using namespace rmg;
using rmg::internal::glDeleteProgram;
using rmg::internal::glDeleteShader;
using rmg::internal::ContextLoader;
using rmg::internal::GLContext;
using rmg::internal::Shader;


class Object2DShader: public ::testing::Test {
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
 * @brief 2D object shader compilation and linking test
 * 
 * Checks compile timer error
 */
TEST_F(Object2DShader, compileVertex) {
    uint32_t id;
    id = Shader::compileShader(
        GL_VERTEX_SHADER,
        RMG_RESOURCE_PATH "/shaders/sprite.vs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteShader(id);
    
    id = Shader::compileShader(
        GL_VERTEX_SHADER,
        RMG_RESOURCE_PATH "/shaders/text2d.vs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteShader(id);
}

TEST_F(Object2DShader, compileFrag) {
    uint32_t id;
    id = Shader::compileShader(
        GL_VERTEX_SHADER,
        RMG_RESOURCE_PATH "/shaders/sprite.fs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteShader(id);
    
    id = Shader::compileShader(
        GL_VERTEX_SHADER,
        RMG_RESOURCE_PATH "/shaders/text2d.fs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteShader(id);
}

TEST_F(Object2DShader, link) {
    uint32_t id;
    id = Shader::compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/sprite.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/sprite.fs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteProgram(id);
    
    id = Shader::compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/text2d.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/text2d.fs.glsl"
    );
    ASSERT_NE(0, id);
    glDeleteProgram(id);
}


/**
 * @brief 2D object shader runtime test
 * 
 * To make sure there is no runtime error.
 * Loads the shader program and process it for a certain times in a 
 * death test.
 */
TEST_F(Object2DShader, runtime) {
    auto shader = rmg::internal::Object2DShader();
    shader.load();
    
    Context ctx;
    ContextLoader loader;
    Sprite2D *sprite1 = new Sprite2D(&ctx, RMG_RESOURCE_PATH "/icon64.png");
    sprite1->setAlignment(Alignment::BottomLeft);
    sprite1->setTranslation(48, -48);
    Sprite2D *sprite2 = new Sprite2D(&ctx, RMGTEST_RESOURCE_PATH
                                           "/open_png_rgba.png");
    sprite2->setAlignment(Alignment::BottomRight);
    sprite2->setTranslation(-32, -48);
    Font *ft = new Font(&ctx, RMG_DEFAULT_FONT, 16);
    Text2D *text = new Text2D(&ctx, ft, "Testing");
    loader.push(sprite1->getTextureLoad());
    loader.push(sprite2->getTextureLoad());
    loader.push(ft->getTextureLoad());
    loader.load();
    LinkedList<Object> list;
    list.push_front(sprite1);
    list.push_front(sprite2);
    list.push_front(text);
    
    shader.render(list);
    glfwSwapBuffers(window);
    glfwPollEvents();
    delete sprite1;
    delete sprite2;
}
