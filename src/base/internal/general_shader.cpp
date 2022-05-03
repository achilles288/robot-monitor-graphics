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


#define RMG_EXPORT


#include "../rmg/internal/general_shader.hpp"

#include "../../config/rmg/config.h"
#include "../rmg/object3d.hpp"


namespace rmg {
namespace internal {

/**
 * @brief Compiles and links shader program and assigns parameter IDs
 */
void GeneralShader::load() {
    id = compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/general.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/general.fs.glsl"
    );
    idMVP = glGetUniformLocation(id, "MVP");
    idMV = glGetUniformLocation(id, "MV");
    idScale = glGetUniformLocation(id, "scale");
    idShadow = glGetUniformLocation(id, "shadowMap");
    idShadowMVP = glGetUniformLocation(id, "shadowMVP");
    idDLCamera = glGetUniformLocation(id, "dirLight.direction");
    idDLColor = glGetUniformLocation(id, "dirLight.color");
    idMatColor = glGetUniformLocation(id, "mat.color");
    idMatMetal = glGetUniformLocation(id, "mat.metalness");
    idMatRough = glGetUniformLocation(id, "mat.roughness");
    idMatAO = glGetUniformLocation(id, "mat.ao");
    idFlags = glGetUniformLocation(id, "vflags");
}

/**
 * @brief Renders the given list of 3D objects with world model, object model
 *        and material properties
 * 
 * @param V View matrix
 * @param P Projection matrix
 * @param S Shadow matrix
 * @param dlCam Directional light vector in camera space
 * @param dlColor Directional light color
 * @param shadow Shadow map
 * @param list List of 3D objects
 */
void GeneralShader::render(const Mat4 &V, const Mat4 &P, const Mat4 &S,
                           const Vec3 &dlCam, const Color &dlColor,
                           uint32_t shadow, const ObjectList &list)
{
    if(id == 0)
        return;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glFrontFace(GL_CCW);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glUseProgram(id);
    glUniform3fv(idDLCamera, 1, &dlCam[0]);
    glUniform4fv(idDLColor, 1, &dlColor[0]);
    for(auto it=list.begin(); it!=list.end(); it++) {
        uint32_t flags = 0;
        Object3D *obj = (Object3D*) &(*it);
        if(obj->isHidden() || obj->getVBO() == nullptr)
            continue;
        Mat4 MV = V * obj->getModelMatrix();
        Mat4 MVP = P * MV;
        glUniformMatrix4fv(idMVP, 1, GL_TRUE, &MVP[0][0]);
        glUniformMatrix4fv(idMV, 1, GL_TRUE, &MV[0][0]);
        glUniform3fv(idScale, 1, &obj->getScale()[0]);
        
        if(shadow != 0) {
            flags |= (1 << 0);
            Mat4 shadowMVP = S * obj->getModelMatrix();
            glUniformMatrix4fv(idShadowMVP, 1, GL_TRUE, &shadowMVP[0][0]);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, shadow);
            glUniform1i(idShadow, 0);
        }
        
        glUniform4fv(idMatColor, 1, &obj->getColor()[0]);
        glUniform1f(idMatMetal, obj->getMetalness());
        glUniform1f(idMatRough, obj->getRoughness());
        glUniform1f(idMatAO, obj->getAmbientOcculation());
        
        if(obj->getVBO()->getMode() == VBOMode::Textured &&
           obj->getTexture() != nullptr)
        {
            flags |= (1 << 8);
        }
        glUniform1i(idFlags, flags);
        obj->getVBO()->draw();
    }
}

}}
