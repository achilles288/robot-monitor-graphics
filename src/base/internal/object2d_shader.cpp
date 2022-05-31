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

#include "shader_def.h"
#include "../rmg/internal/sprite_load.hpp"
#include "../../config/rmg/config.h"

#include <map>

#include <cstdio>
#include <iostream>


namespace rmg {
namespace internal {

static uint32_t prevShader = 0;


/**
 * @brief Destructor
 */
SpriteShader::~SpriteShader() {
    if(quadVertexBuffer != 0)
      glDeleteBuffers(1, &quadVertexBuffer);
    if(quadVertexArrayID != 0)
      glDeleteVertexArrays(1, &quadVertexArrayID);
}

/**
 * @brief Compiles and links shader program and assigns parameter IDs
 */
void SpriteShader::load() {
    id = compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/sprite.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/sprite.fs.glsl"
    );
    idMVP = glGetUniformLocation(id, "MVP");
    idColor = glGetUniformLocation(id, "color");
    idTexture = glGetUniformLocation(id, "image");
    
    const float vertices[] = {
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f
    };
    glGenVertexArrays(1, &quadVertexArrayID);
    glBindVertexArray(quadVertexArrayID);
    glGenBuffers(1, &quadVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

/**
 * @brief Renders a sprite image on 2D panel
 * 
 * @param sprite The sprite image to render
 * @param VP The combination of view matrix and projection matrix
 */
void SpriteShader::render(Sprite2D* sprite, const Mat3 &VP) {
    if(id == 0 || sprite->getTexture() == nullptr)
        return;
    if(prevShader != id) {
        glUseProgram(id);
        glBindVertexArray(quadVertexArrayID);
        glUniform1i(idTexture, TEXTURE_SPRITE);
    }
    Mat3 MVP = VP * sprite->getModelMatrix();
    Color color = sprite->getColor();
    glUniformMatrix3fv(idMVP, 1, GL_TRUE, &MVP[0][0]);
    glUniform4fv(idColor, 1, &color[0]);
    sprite->getTexture()->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}




/**
 * @brief Destructor
 */
Text2DShader::~Text2DShader() {
    if(quadVertexBuffer != 0)
      glDeleteBuffers(1, &quadVertexBuffer);
    if(quadVertexArrayID != 0)
      glDeleteVertexArrays(1, &quadVertexArrayID);
}

/**
 * @brief Compiles and links shader program and assigns parameter IDs
 */
void Text2DShader::load() {
    id = compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/text2d.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/text2d.fs.glsl"
    );
    idMVP = glGetUniformLocation(id, "MVP");
    idColor = glGetUniformLocation(id, "color");
    idTexture = glGetUniformLocation(id, "font");
    idChar = glGetUniformLocation(id, "char");
    idSize = glGetUniformLocation(id, "size");
    
    const float vertices[] = {
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };
    glGenVertexArrays(1, &quadVertexArrayID);
    glBindVertexArray(quadVertexArrayID);
    glGenBuffers(1, &quadVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

/**
 * @brief Renders a 2D text on 2D panel
 * 
 * @param txt The 2D text object to render
 * @param VP The combination of view matrix and projection matrix
 */
void Text2DShader::render(Text2D* txt, const Mat3 &VP) {
    if(id == 0)
        return;
    Font* ft = txt->getFont();
    if(ft == nullptr || ft->getTexture() == nullptr)
        return;
    if(prevShader != id) {
        glUseProgram(id);
        glBindVertexArray(quadVertexArrayID);
        glUniform1i(idTexture, TEXTURE_SPRITE);
    }
    
    Color color = txt->getColor();
    Mat3 MVP = VP * txt->getModelMatrix();
    glUniform4fv(idColor, 1, &color[0]);
    ft->getTexture()->bind();
    
    const char* ptr;
    char c;
    int16_t x = 0;
    if(txt->getTextAlignment() != HorizontalAlign::Left) {
        ptr = txt->getText();
        c = *ptr;
        uint16_t width = 0;
        while(c != '\0') {
            GlyphMetrics glyph = ft->getGlyphMetrics(c);
            width += glyph.advance;
            c = *(++ptr);
        }
        if(txt->getTextAlignment() == HorizontalAlign::Right)
            x = -width;
        else // Center
            x = -width/2;
    }
    
    ptr = txt->getText();
    c = *ptr;
    while(c != '\0') {
        GlyphMetrics glyph = ft->getGlyphMetrics(c);
        if(glyph.width == 0 || glyph.height == 0) {
            x += glyph.advance;
            c = *(++ptr);
            continue;
        }
        
        Mat3 L;
        L[0][0] = glyph.width;
        L[1][1] = glyph.height;
        L[0][2] = x/64.0f + glyph.bearing.x;
        L[1][2] = -glyph.bearing.y;
        
        Mat3 M = MVP * L;
        glUniformMatrix3fv(idMVP, 1, GL_TRUE, &M[0][0]);
        uint8_t i = (uint8_t) c;
        glUniform2f(idChar, 0.0625f*(i % 16), 0.0625f*(i / 16));
        float w = glyph.width / (16.0f * ft->getSize());
        float h = glyph.height / (16.0f * ft->getSize());
        glUniform2f(idSize, w, h);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += glyph.advance;
        c = *(++ptr);
    }
}




/**
 * @brief Default constructor
 */
Object2DShader::Object2DShader() {
    projectionMatrix = Mat3();
    width = 0;
    height = 0;
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
    projectionMatrix[0][0] = 2.0f / w;
    projectionMatrix[1][1] = -2.0f / h;
    width = w;
    height = h;
}

/**
 * @brief Renders the given list of 2D objects
 * 
 * @param list List of 2D objects
 */
void Object2DShader::render(const ObjectList &list) {
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    prevShader = 0;
    std::multimap<int16_t, Object2D*> sorted;
    
    for(auto it=list.begin(); it!=list.end(); it++) {
        Object2D* obj = (Object2D*) &(*it);
        if(obj->isHidden())
            continue;
        int16_t zOrder = 2 * obj->getZOrder();
        if(obj->getObject2DType() == Object2DType::Text)
            zOrder += 1;
        auto elem = std::pair<int16_t,Object2D*>(zOrder,obj);
        sorted.insert(elem);
    }
    
    for(auto it=sorted.begin(); it!=sorted.end(); it++) {
        Object2D* obj = (Object2D*) it->second;
        Mat3 V = Mat3();
        switch(obj->getAlignment()) {
          case Alignment::TopLeft:
            V[0][2] = -width/2;
            V[1][2] = -height/2;
            break;
          case Alignment::TopCenter:
            V[1][2] = -height/2;
            break;
          case Alignment::TopRight:
            V[0][2] = width/2;
            V[1][2] = -height/2;
            break;
          case Alignment::MiddleLeft:
            V[0][2] = -width/2;
            break;
          case Alignment::MiddleCenter:
            break;
          case Alignment::MiddleRight:
            V[0][2] = width/2;
            break;
          case Alignment::BottomLeft:
            V[0][2] = -width/2;
            V[1][2] = height/2;
            break;
          case Alignment::BottomCenter:
            V[1][2] = height/2;
            break;
          case Alignment::BottomRight:
            V[0][2] = width/2;
            V[1][2] = height/2;
            break;
        }
        Mat3 VP = projectionMatrix * V;
        
        switch(obj->getObject2DType()) {
          case Object2DType::Sprite:
            spriteShader.render((Sprite2D*) obj, VP);
            break;
          case Object2DType::Text:
            text2dShader.render((Text2D*) obj, VP);
            break;
          case Object2DType::Default:
            break;
        }
    }
    prevShader = 0;
}

}}
