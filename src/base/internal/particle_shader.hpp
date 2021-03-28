/**
 * @file particle_shader.hpp
 * @brief Calculates the location of particle and displays as a 2D sprite
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_PARTICLE_SHADER_H__
#define __RMG_PARTICLE_SHADER_H__

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

namespace rmg {
namespace internal {

/**
 * @brief Calculates the location of particle and displays as a 2D sprite
 */
class RMG_API ParticleShader: public Shader {
  private:
    uint32_t idMVP;
    
  public:
    /**
     * @brief Default constructor
     */
    ParticleShader() = default;
    
    /**
     * @brief Compile, link and assign program parameters
     */
    void load() override;
};

}}

#endif
