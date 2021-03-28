/**
 * @file line3d_shader.hpp
 * @brief Displays non-polygon objects like lines in 3D space
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_LINE3D_SHADER_H__
#define __RMG_LINE3D_SHADER_H__

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
 * @brief Displays non-polygon objects like lines in 3D space
 */
class RMG_API Line3DShader: public Shader {
  private:
    uint32_t idThickness;
    uint32_t idColor;
    uint32_t idP1;
    uint32_t idP2;
    
  public:
    /**
     * @brief Default constructor
     */
    Line3DShader() = default;
    
    /**
     * @brief Compile, link and assign program parameters
     */
    void load() override;
};

}}

#endif
