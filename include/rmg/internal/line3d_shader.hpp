/**
 * @file line3d_shader.hpp
 * @brief Displays non-polygon objects like lines in 3D space
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
 * @brief Displays non-polygon objects like lines in 3D space
 */
class Line3DShader: public Shader {
  private:
    uint32_t idMVP;
    
  public:
    /**
     * @brief Constructor with its container
     * 
     * @param ctx Container context
     */
    Line3DShader(Context* ctx);
    
    /**
     * @brief Destructor
     */
    virtual ~Line3DShader();
    
    /**
     * @brief Shader process
     */
    void process();
};

}}

#endif
