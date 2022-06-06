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
#include "../object.hpp"
#include "../math/mat4.hpp"

namespace rmg {
namespace internal {

/**
 * @brief Calculates the location of particle and displays as a 2D sprite
 */
class RMG_API ParticleShader: public Shader {
  private:
    uint32_t idTV;
    uint32_t idModel;
    uint32_t idProjection;
    uint32_t idColor;
    uint32_t idTexture;
    
    uint32_t quadVertexArrayID = 0;
    uint32_t quadVertexBuffer = 0;
    
  public:
    /**
     * @brief Default constructor
     */
    ParticleShader() = default;
    
    /**
     * @brief Destructor
     */
    virtual ~ParticleShader();
    
    /**
     * @brief Compile, link and assign program parameters
     */
    void load() override;
    
    /**
     * @brief Renders the given list of particles
     * 
     * @param V View matrix
     * @param P Projection matrix
     * @param list List of particles
     */
    void render(const Mat4 &V, const Mat4 &P, const ObjectList &list);
};

}}

#endif
