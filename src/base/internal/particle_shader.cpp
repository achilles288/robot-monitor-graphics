/**
 * @file particle_shader.hpp
 * @brief Calculates the location of particle and displays as a 2D sprite
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "../rmg/internal/particle_shader.hpp"

#include "shader_def.h"
#include "../../config/rmg/config.h"
#include "../rmg/particle.hpp"
#include "../rmg/internal/sprite_load.hpp"

#include <map>


namespace rmg {
namespace internal {

/**
 * @brief Desturctor
 */
ParticleShader::~ParticleShader() {
    if(quadVertexBuffer != 0)
      glDeleteBuffers(1, &quadVertexBuffer);
    if(quadVertexArrayID != 0)
      glDeleteVertexArrays(1, &quadVertexArrayID);
}

/**
 * @brief Compiles and links shader program and assigns parameter IDs
 */
void ParticleShader::load() {
    id = compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/particle.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/particle.fs.glsl"
    );
    idTV = glGetUniformLocation(id, "TV");
    idModel = glGetUniformLocation(id, "model");
    idProjection = glGetUniformLocation(id, "projection");
    idColor = glGetUniformLocation(id, "color");
    idTexture = glGetUniformLocation(id, "image");
    
    const float vertices[] = {
         0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, 1.0f, 1.0f,
         0.5f,  0.5f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &quadVertexArrayID);
    glBindVertexArray(quadVertexArrayID);
    glGenBuffers(1, &quadVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

/**
 * @brief Renders the given list of particles
 * 
 * @param V View matrix
 * @param P Projection matrix
 * @param list List of particles
 */
void ParticleShader::render(const Mat4 &V, const Mat4 &P,
                            const ObjectList &list)
{
    if(id == 0)
        return;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glFrontFace(GL_CCW);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glUseProgram(id);
    glBindVertexArray(quadVertexArrayID);
    glUniformMatrix4fv(idProjection, 1, GL_TRUE, &P[0][0]);
    glUniform1i(idTexture, TEXTURE_SPRITE);
    std::map<float, Particle3D*> sorted;
    
    for(auto it=list.begin(); it!=list.end(); it++) {
        Particle3D* obj = (Particle3D*) &(*it);
        if(obj->isHidden())
            continue;
        Vec3 TV = Vec3(V * Vec4(obj->getTranslation(), 1));
        auto elem = std::pair<float,Particle3D*>(TV.z,obj);
        sorted.insert(elem);
    }
    
    for(auto it=sorted.begin(); it!=sorted.end(); it++) {
        Particle3D* obj = it->second;
        if(obj->getTexture() == nullptr)
            continue;
        Vec3 TV = Vec3(V * Vec4(obj->getTranslation(), 1));
        glUniform3fv(idTV, 1, &TV[0]);
        glUniformMatrix3fv(idModel, 1, GL_TRUE, &obj->getModelMatrix()[0][0]);
        glUniform4fv(idColor, 1, &obj->getColor()[0]);
        obj->getTexture()->bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

}}
