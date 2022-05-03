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
#include "../color.hpp"
#include "../object.hpp"
#include "../math/mat4.hpp"
#include "../math/vec3.hpp"


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
class RMG_API GeneralShader: public Shader {
  private:
    uint32_t idMVP;
    uint32_t idMV;
    uint32_t idScale;
    uint32_t idShadow;
    uint32_t idShadowMVP;
    uint32_t idDLCamera;
    uint32_t idDLColor;
    uint32_t idMatColor;
    uint32_t idMatMetal;
    uint32_t idMatRough;
    uint32_t idMatAO;
    uint32_t idFlags;
    
  public:
    /**
     * @brief Default constructor
     */
    GeneralShader() = default;
    
    /**
     * @brief Compiles and links shader program and assigns parameter IDs
     */
    void load() override;
    
    /**
     * @brief Renders the given list of 3D objects with world model, object
     *        model and material properties
     * 
     * @param V View matrix
     * @param P Projection matrix
     * @param S Shadow matrix
     * @param dlCam Directional light vector in camera space
     * @param dlColor Directional light color
     * @param shadow Shadow map
     * @param list List of 3D objects
     */
    void render(const Mat4 &V, const Mat4 &P, const Mat4 &S,
                const Vec3 &dlCam, const Color &dlColor, uint32_t shadow,
                const ObjectList &list);
};

}}

#endif
