/**
 * @file general_shader.hpp
 * @brief Peforms general tasks like positioning and lighting
 * 
 * Operates MVP matricies through the list of 3D objects.
 * Reads the appearance model of the objects and display them on screen
 * processing in the general fragment shader. Positioning is done by
 * processing MVP (Model-View-Projection) matricies in vertex shader.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_GENERAL_SHADER_H__
#define __RMG_GENERAL_SHADER_H__

#include <rmg/internal/shader.hpp>

namespace rmg {
namespace internal {

/**
 * @brief Peforms general tasks like positioning and lighting
 * 
 * Operates MVP matricies through the list of 3D objects.
 * Reads the appearance model of the objects and display them on screen
 * processing in the general fragment shader. Positioning is done by
 * processing MVP (Model-View-Projection) matricies in vertex shader.
 */
class GeneralShader: public Shader {
  private:
    uint32_t idMVP;
    
  public:
    /**
     * @brief Default constructor
     */
    GeneralShader();
    
    /**
     * @brief Constructor with its container
     * 
     * @param ctx Container context
     */
    GeneralShader(Context* ctx);
    
    /**
     * @brief Destructor
     */
    virtual ~GeneralShader();
    
    /**
     * @brief Compile, link and assign program parameters
     */
    void load();
};

}}

#endif
