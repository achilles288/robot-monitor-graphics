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
 * @brief Displays 2D objects like sprites and texts
 */
class RMG_API SpriteShader: public Shader {
  private:
    uint32_t idMVP;
    
  public:
    /**
     * @brief Default constructor
     */
    SpriteShader() = default;
    
    /**
     * @brief Compile, link and assign program parameters
     */
    void load() override;
};

}}

#endif
