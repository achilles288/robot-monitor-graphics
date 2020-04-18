/**
 * @file shader.hpp
 * @brief Shader program class taking main backend role in drawing
 * 
 * Compiles vertex and fragment shaders. Link the program. Run it using
 * loaded vertex buffer objects and make drawings.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_SHADER_H__
#define __RMG_SHADER_H__

#include <rmg/context.h>

#include <cstdint>
#include <string>


namespace rmg {
namespace internal {

/**
 * @brief The shader program taking main backend role in drawing
 * 
 * Compiles vertex and fragment shaders. Link the program. Run it using
 * loaded vertex buffer objects and make drawings.
 */
class Shader {
  private:
    uint32_t id;
    Context* context;
    
    void compileShader(uint32_t shaderID, std::string path);
    
  public:
    /**
     * @brief Constructor with its container
     * 
     * @param ctx Container context
     */
    Shader(Context* ctx);
    
    /**
     * @brief Copy constructor
     */
    virtual ~Shader();
    
    /**
     * @brief Compiles a shader program from vertex and fragment shaders
     * 
     * @param vert Path to vertex shader
     * @param frag Path to fragment shader
     */
    void compileShaderProgram(std::string vert, std::string frag);
};

}}

#endif
