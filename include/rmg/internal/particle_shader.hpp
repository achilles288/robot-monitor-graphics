/**
 * @file particle_shader.hpp
 * @brief Calculates the location of particle and displays as a 2D sprite
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
 * @brief Calculates the location of particle and displays as a 2D sprite
 */
class ParticleShader: public Shader {
  private:
    uint32_t idMVP;
    
  public:
    /**
     * @brief Constructor with its container
     * 
     * @param ctx Container context
     */
    ParticleShader(Context* ctx);
    
    /**
     * @brief Destructor
     */
    virtual ~ParticleShader();
    
    /**
     * @brief Shader process
     */
    void process();
};

}}

#endif
