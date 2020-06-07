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

#include "shader.hpp"

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
     * @brief Default constructor
     */
    Line3DShader();
    
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
     * @brief Compile, link and assign program parameters
     */
    void load();
};

}}

#endif
