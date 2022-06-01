/**
 * @file shader.hpp
 * @brief Shader program class taking main backend role in drawing
 * 
 * Compiles vertex and fragment shaders. Link the program. Run it using
 * loaded vertex buffer objects and make drawings.
 * 
 * @copyright Copyright (c) 2022 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_SHADER_H__
#define __RMG_SHADER_H__

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


#include <cstdint>

#include "glcontext.hpp"


namespace rmg {

namespace internal {

/**
 * @brief The shader program taking main backend role in drawing
 * 
 * Compiles vertex and fragment shaders. Link the program. Run it using
 * loaded vertex buffer objects and make drawings.
 */
class RMG_API Shader {
  protected:
    uint32_t id = 0; ///< Shader program ID
    
  public:
    /**
     * @brief Default constructor
     */
    Shader() = default;
    
    /**
     * @brief Destructor
     */
    virtual ~Shader();
    
    /**
     * @brief Compiles and links shader program and assigns parameter IDs
     */
    virtual void load() = 0;
    
    /**
     * @brief Compiles a shader from file (Vertex shader or fragment shader)
     * 
     * @param type Shader type (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, .etc)
     * @param path Path to shader file
     * 
     * @return ID of the compiled shader used to retrive it
     */
    static uint32_t compileShader(uint32_t type, const char* path);
    
    /**
     * @brief Compiles and links a shader program
     * 
     * @param vert Vertex shader file
     * @param frag Fragment shader file
     * 
     * @return Shader program ID
     */
    static uint32_t compileShaderProgram(const char* vert, const char* frag);
};

}}

#endif
