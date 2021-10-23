/**
 * @file sprite_shader.hpp
 * @brief Displays 2D objects like sprites and texts
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "../rmg/internal/object2d_shader.hpp"

#include "../../config/rmg/config.h"


namespace rmg {
namespace internal {

static uint32_t prevShader = 0;


/**
 * @brief Compiles and links shader program and assigns parameter IDs
 */
void SpriteShader::load() {
    id = compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/sprite.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/sprite.fs.glsl"
    );
    idModel = glGetUniformLocation(id, "model");
    idColor = glGetUniformLocation(id, "color");
}

/**
 * @brief Renders a sprite image on 2D panel
 * 
 * @param sprite The sprite image to render
 */
void SpriteShader::render(Object2D* sprite) {
    if(id == 0)
        return;
    if(prevShader != id)
        glUseProgram(id);
}




/**
 * @brief Compiles and links shader program and assigns parameter IDs
 */
void Text2DShader::load() {
    id = compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/text2d.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/text2d.fs.glsl"
    );
    idModel = glGetUniformLocation(id, "model");
    idColor = glGetUniformLocation(id, "color");
}

/**
 * @brief Renders a 2D text on 2D panel
 * 
 * @param txt The 2D text object to render
 */
void Text2DShader::render(Object2D* txt) {
    if(id == 0)
        return;
    if(prevShader != id)
        glUseProgram(id);
}




/**
 * @brief Compile, link and assign program parameters
 */
void Object2DShader::load() {
    spriteShader.load();
    text2dShader.load();
}

/**
 * @brief Sets OpenGL viewport size
 * 
 * @param w Viewport width
 * @param h Viewport height
 */
void Object2DShader::setContextSize(uint16_t w, uint16_t h) {
    
}

/**
 * @brief Renders the given list of 2D objects
 * 
 * @param list List of 2D objects
 */
void Object2DShader::render(const std::map<uint64_t, Object2D*> &list) {
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::map<int16_t, Object2D*> sorted;
    for(auto it=list.begin(); it!=list.end(); it++) {
        Object2D* obj = it->second;
        int16_t zOrder = -2 * obj->getZOrder();
        if(obj->getObject2DType() == Object2DType::Text)
            zOrder += 1;;
        auto elem = std::pair<int16_t,Object2D*>(zOrder,obj);
        sorted.insert(elem);
    }
    for(auto it=sorted.begin(); it!=sorted.end(); it++) {
        Object2D* obj = it->second;
        if(obj->getObject2DType() == Object2DType::Sprite)
            spriteShader.render(obj);
        else if(obj->getObject2DType() == Object2DType::Sprite)
            text2dShader.render(obj);
    }
    prevShader = 0;
}

}}
