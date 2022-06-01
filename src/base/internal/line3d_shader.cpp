/**
 * @file line3d_shader.hpp
 * @brief Displays lines in 3D space
 * 
 * @copyright Copyright (c) 2022 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "../rmg/internal/line3d_shader.hpp"

#include "../rmg/line3d.hpp"
#include "../../config/rmg/config.h"


namespace rmg {
namespace internal {

/**
 * @brief Desturctor
 */
Line3DShader::~Line3DShader() {
    if(vertexbuffer != 0)
      glDeleteBuffers(1, &vertexbuffer);
    if(elementbuffer != 0)
      glDeleteBuffers(1, &elementbuffer);
    if(vertexArrayID != 0)
      glDeleteVertexArrays(1, &vertexArrayID);
}


#define FRAGMENT_COUNT 8
#define VERTEX_COUNT (2 * (FRAGMENT_COUNT + 1))
#define INDEX_COUNT (12 * FRAGMENT_COUNT)


/**
 * @brief Compiles and links shader program and assigns parameter IDs
 */
void Line3DShader::load() {
    id = compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/line3d.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/line3d.fs.glsl"
    );
    idMVP = glGetUniformLocation(id, "MVP");
    idColor = glGetUniformLocation(id, "color");
    
    Vec3 vertices[FRAGMENT_COUNT+1][2];
    uint32_t indecies[FRAGMENT_COUNT][12];
    
    // Pole vertices
    vertices[FRAGMENT_COUNT][0] = Vec3(0, 0, 0);
    vertices[FRAGMENT_COUNT][1] = Vec3(1, 0, 0);
    
    // Iterates through the circumference
    for(int i=0; i<FRAGMENT_COUNT; i++) {
        float t = 2 * M_PI * ((float)i/FRAGMENT_COUNT);
        float c = 0.5f * cos(t);
        float s = 0.5f * sin(t);
        vertices[i][0] = Vec3(0, c, s);
        vertices[i][1] = Vec3(1, c, s);
        
        if(i == 0) {
            indecies[0][0] = (FRAGMENT_COUNT-1)*2;
            indecies[0][1] = FRAGMENT_COUNT*2;
            indecies[0][2] = 0;
            
            indecies[0][3] = (FRAGMENT_COUNT-1)*2 + 1;
            indecies[0][4] = (FRAGMENT_COUNT-1)*2;
            indecies[0][5] = 0;
            indecies[0][6] = 0;
            indecies[0][7] = 1;
            indecies[0][8] = (FRAGMENT_COUNT-1)*2 + 1;
            
            indecies[0][9] = (FRAGMENT_COUNT-1)*2 + 1;
            indecies[0][10] = 1;
            indecies[0][11] = FRAGMENT_COUNT*2 + 1;
        }
        else {
            indecies[i][0] = (i-1)*2;
            indecies[i][1] = FRAGMENT_COUNT*2;
            indecies[i][2] = i*2;
            
            indecies[i][3] = (i-1)*2 + 1;
            indecies[i][4] = (i-1)*2;
            indecies[i][5] = i*2;
            indecies[i][6] = i*2;
            indecies[i][7] = i*2 + 1;
            indecies[i][8] = (i-1)*2 + 1;
            
            indecies[i][9] = (i-1)*2 + 1;
            indecies[i][10] = i*2 + 1;
            indecies[i][11] = FRAGMENT_COUNT*2 + 1;
        }
    }
    
    // Loads vertex array
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, VERTEX_COUNT*sizeof(Vec3), &vertices[0][0],
                 GL_STATIC_DRAW);
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDEX_COUNT*sizeof(uint32_t),
                 &indecies[0][0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
}

/**
 * @brief Renders the given list of lines in 3D space
 * 
 * @param VP The composition of view and projection matrix
 * @param list List of 3D objects
 */
void Line3DShader::render(const Mat4 &VP, const LinkedList<Object> &list) {
    if(id == 0)
        return;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glFrontFace(GL_CCW);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glUseProgram(id);
    glBindVertexArray(vertexArrayID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    
    for(auto it=list.begin(); it!=list.end(); it++) {
        Line3D* line = (Line3D*) &(*it);
        if(line->isHidden())
            continue;
        Mat4 MVP = VP * line->getModelMatrix();
        glUniformMatrix4fv(idMVP, 1, GL_TRUE, &MVP[0][0]);
        glUniform3fv(idColor, 1, &line->getColor()[0]);
        
        glDrawElements(
            GL_TRIANGLES,    // mode
            INDEX_COUNT,     // count
            GL_UNSIGNED_INT, // type
            (void*)0         // element array buffer offset
        );
    }
}

}}
