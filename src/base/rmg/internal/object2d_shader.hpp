/**
 * @file object2d_shader.hpp
 * @brief Displays 2D objects like sprites and texts
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_OBJECT2D_SHADER_H__
#define __RMG_OBJECT2D_SHADER_H__

#ifndef RMG_API
#ifdef _WIN32
#ifdef RMG_EXPORT
#define RMG_API __declspec(dllexport)
#else
#define RMG_API __declspec(dllimport)
#endif
#else
#define RMG_API
#endif
#endif


#include "shader.hpp"
#include "../sprite.hpp"
#include "../text2d.hpp"


namespace rmg {
namespace internal {

/**
 * @brief Displays 2D sprites
 */
class RMG_API SpriteShader: public Shader {
  private:
    uint32_t idMVP;
    uint32_t idColor;
    uint32_t idTexture;
    
    uint32_t quadVertexArrayID = 0;
    uint32_t quadVertexBuffer = 0;
    
  public:
    /**
     * @brief Default constructor
     */
    SpriteShader() = default;
    
    /**
     * @brief Destructor
     */
    virtual ~SpriteShader();
    
    /**
     * @brief Compile, link and assign program parameters
     */
    void load() override;
    
    /**
     * @brief Renders a sprite image on 2D panel
     * 
     * @param sprite The sprite image to render
     * @param VP The combination of view matrix and projection matrix
     */
    void render(Sprite2D* sprite, const Mat3 &VP);
};

/**
 * @brief Displays 2D texts
 */
class RMG_API Text2DShader: public Shader {
  private:
    uint32_t idMVP;
    uint32_t idColor;
    uint32_t idTexture;
    uint32_t idChar;
    uint32_t idSize;
    
    uint32_t quadVertexArrayID = 0;
    uint32_t quadVertexBuffer = 0;
    
  public:
    /**
     * @brief Default constructor
     */
    Text2DShader() = default;
    
    /**
     * @brief Destructor
     */
    virtual ~Text2DShader();
    
    /**
     * @brief Compile, link and assign program parameters
     */
    void load() override;
    
    /**
     * @brief Renders a 2D text on 2D panel
     * 
     * @param txt The 2D text object to render
     * @param VP The combination of view matrix and projection matrix
     */
    void render(Text2D* txt, const Mat3 &VP);
};

/**
 * @brief Displays 2D objects like sprites and texts
 */
class RMG_API Object2DShader {
  private:
    SpriteShader spriteShader;
    Text2DShader text2dShader;
    Mat3 projectionMatrix;
    uint16_t width;
    uint16_t height;
    
  public:
    /**
     * @brief Default constructor
     */
    Object2DShader();
    
    /**
     * @brief Compile, link and assign program parameters
     */
    void load();
    
    /**
     * @brief Sets OpenGL viewport size
     * 
     * @param w Viewport width
     * @param h Viewport height
     */
    void setContextSize(uint16_t w, uint16_t h);
    
    /**
     * @brief Renders the given list of 2D objects
     * 
     * @param list List of 2D objects
     */
    void render(const ObjectList &list);
};

}}

#endif
