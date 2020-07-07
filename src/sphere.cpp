/**
 * @file sphere.hpp
 * @brief Visual sphere model
 *
 * Generates a sphere model. Manipulate the sphere radius, length
 * location, rotation and scale.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "rmg/sphere.hpp"

#include <iostream>

#include "rmg/context.hpp"


namespace rmg {

/**
 * @brief Default constructor
 */
Sphere3D::Sphere3D() {
    diameter = 1.0f;
}

/**
 * @brief Constructs a sphere model with specific diameter
 * 
 * @param ctx Container context
 * @param d Diameter
 */
Sphere3D::Sphere3D(Context* ctx, float d): Object3D(ctx) {    
    diameter = d;
    auto vbo = std::make_shared<internal::VBO>(internal::VBO());
    setSharedVBO(vbo);
    setMesh(createMesh());
}

Mesh Sphere3D::createMesh() {
    #define FRAGMENT_COUNT 6
    
    Vec3 vertices[6][FRAGMENT_COUNT+1][FRAGMENT_COUNT+1];
    Vec3 normals[6][FRAGMENT_COUNT+1][FRAGMENT_COUNT+1];
    Vec2 texCoords[6][FRAGMENT_COUNT+1][FRAGMENT_COUNT+1];
    uint16_t indecies[6][FRAGMENT_COUNT][FRAGMENT_COUNT][6];
    
    float radius = diameter/2.0f;
    
    for(int k=0; k<6; k++) {
        Vec3 s0, u, v;
        if(k == 0) {
            s0 = Vec3(-1, 1, -1);
            u = Vec3(0, -1, 0);
            v = Vec3(0, 0, 1);
        }
        else if(k == 1) {
            s0 = Vec3(1, -1, -1);
            u = Vec3(0, 1, 0);
            v = Vec3(0, 0, 1);
        }
        else if(k == 2) {
            s0 = Vec3(-1, -1, -1);
            u = Vec3(1, 0, 0);
            v = Vec3(0, 0, 1);
        }
        else if(k == 3) {
            s0 = Vec3(1, 1, -1);
            u = Vec3(-1, 0, 0);
            v = Vec3(0, 0, 1);
        }
        else if(k == 4) {
            s0 = Vec3(-1, 1, -1);
            u = Vec3(1, 0, 0);
            v = Vec3(0, -1, 0);
        }
        else if(k == 5) {
            s0 = Vec3(-1, -1, 1);
            u = Vec3(1, 0, 0);
            v = Vec3(0, 1, 0);
        }
        
        for(int i=0; i<FRAGMENT_COUNT+1; i++) {
            for(int j=0; j<FRAGMENT_COUNT+1; j++) {
                Vec3 du = 2.0f * ((float)j/FRAGMENT_COUNT) * u;
                Vec3 dv = 2.0f * ((float)i/FRAGMENT_COUNT) * v;
                Vec3 n = s0 + du + dv;
                n = n.normalize();
                vertices[k][i][j] = radius*n;
                normals[k][i][j] = n;
                if(i<FRAGMENT_COUNT && j<FRAGMENT_COUNT) {
                    indecies[k][i][j][0] =
                        k * (FRAGMENT_COUNT+1) * (FRAGMENT_COUNT+1) +
                        i * (FRAGMENT_COUNT+1) +
                        j;
                    indecies[k][i][j][1] =
                        k * (FRAGMENT_COUNT+1) * (FRAGMENT_COUNT+1) +
                        i * (FRAGMENT_COUNT+1) +
                        j+1;
                    indecies[k][i][j][2] =
                        k * (FRAGMENT_COUNT+1) * (FRAGMENT_COUNT+1) +
                        (i+1) * (FRAGMENT_COUNT+1) +
                        j+1;
                    indecies[k][i][j][3] =
                        k * (FRAGMENT_COUNT+1) * (FRAGMENT_COUNT+1) +
                        (i+1) * (FRAGMENT_COUNT+1) +
                        j+1;
                    indecies[k][i][j][4] =
                        k * (FRAGMENT_COUNT+1) * (FRAGMENT_COUNT+1) +
                        (i+1) * (FRAGMENT_COUNT+1) +
                        j;
                    indecies[k][i][j][5] =
                        k * (FRAGMENT_COUNT+1) * (FRAGMENT_COUNT+1) +
                        i * (FRAGMENT_COUNT+1) +
                        j;
                }
            }
        }
    }
    
    return Mesh(
        &vertices[0][0][0],
        &normals[0][0][0],
        &texCoords[0][0][0],
        6 * (FRAGMENT_COUNT+1) * (FRAGMENT_COUNT+1),
        &indecies[0][0][0][0],
        6 * FRAGMENT_COUNT * FRAGMENT_COUNT * 6
    );
    #undef FRAGMENT_COUNT
}

/**
 * @brief Gets sphere diameter
 * 
 * @return Cubic dimension
 */
float Sphere3D::getDiameter() const { return diameter; }

/**
 * @brief Sets the material texture
 * 
 * Sets the object to use a predefined material. This material data uses
 * OpenGL context for texture image, normal maps, .etc.
 * 
 * @param mat Predefined material
 */
void Sphere3D::setMaterial(Material* mat) {
    Material *prev = getMaterial();
    Object3D::setMaterial(mat);
    if(prev == nullptr) {
        auto vbo = std::make_shared<internal::VBO>(internal::VBO());
        setSharedVBO(vbo);
        setMesh(createMesh());
    }
}

}
