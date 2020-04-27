/**
 * @file sprite_shader.hpp
 * @brief Displays 2D objects like sprites and texts
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_SPRITE_SHADER_H__
#define __RMG_SPRITE_SHADER_H__

#include <rmg/internal/shader.h>

namespace rmg {
namespace internal {

/**
 * @brief Displays 2D objects like sprites and texts
 */
class SpriteShader: public Shader {
  private:
    uint32_t idMVP;
    
  public:
    /**
     * @brief Constructor with its container
     * 
     * @param ctx Container context
     */
    SpriteShader(Context* ctx);
    
    /**
     * @brief Destructor
     */
    virtual ~SpriteShader();
    
    /**
     * @brief Shader process
     */
    void process();
};

}}

#endif
