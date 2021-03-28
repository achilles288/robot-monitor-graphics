/**
 * @file cube.cpp
 * @brief Visual 3D cube model
 *
 * Generates a 3D cube model. Manipulate the cube dimension, location,
 * rotation and scale.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "cube.hpp"


namespace rmg {

/**
 * @brief Default constructor
 */
Cube3D::Cube3D() {    
    length = 1.0f;
    breadth = 1.0f;
    height = 1.0f;
}

/**
 * @brief Constructs a 3D cube model from specific dimensions
 * 
 * @param ctx Container context
 * @param l Length
 * @param b Breadth
 * @param h Height
 */
Cube3D::Cube3D(Context* ctx, float l, float b, float h): Object3D(ctx)
{
    length = l;
    breadth = b;
    height = h;
    setMesh(createMesh());
}

Mesh Cube3D::createMesh() {
    Vec3 vertices[6][4];
    Vec3 normals[6][4];
    Vec2 texCoords[6][4];
    uint32_t indecies[6][6];
    
    // Left and right faces
    for(int i=-1; i<=1; i+=2) {
        int a = (i==-1) ? 0 : 1;
        vertices[a][0] = Vec3(i*length/2,  i*breadth/2, -height/2);
        vertices[a][1] = Vec3(i*length/2,  i*breadth/2,  height/2);
        vertices[a][2] = Vec3(i*length/2, -i*breadth/2,  height/2);
        vertices[a][3] = Vec3(i*length/2, -i*breadth/2, -height/2);
        Vec3 n = Vec3(i, 0, 0);
        for(int j=0; j<4; j++)
            normals[a][j] = n;
        if(getMaterial() == nullptr) {
            float d = (i==-1) ? 0 : length+breadth;
            texCoords[a][0] = Vec2(d+breadth, breadth);
            texCoords[a][1] = Vec2(d+breadth, breadth+height);
            texCoords[a][2] = Vec2(d, breadth+height);
            texCoords[a][3] = Vec2(d, breadth);
        }
    }
    
    // Front and back faces
    for(int i=-1; i<=1; i+=2) {
        int a = (i==-1) ? 2 : 3;
        vertices[a][0] = Vec3(-i*length/2, i*breadth/2, -height/2);
        vertices[a][1] = Vec3(-i*length/2, i*breadth/2,  height/2);
        vertices[a][2] = Vec3( i*length/2, i*breadth/2,  height/2);
        vertices[a][3] = Vec3( i*length/2, i*breadth/2, -height/2);
        Vec3 n = Vec3(0, i, 0);
        for(int j=0; j<4; j++)
            normals[a][j] = n;
        if(getMaterial() == nullptr) {
            float d = (i==-1) ? breadth : length+2*breadth;
            texCoords[a][0] = Vec2(d+length, breadth);
            texCoords[a][1] = Vec2(d+length, breadth+height);
            texCoords[a][2] = Vec2(d, breadth+height);
            texCoords[a][3] = Vec2(d, breadth);
        }
    }
    
    // Top and bottom faces
    for(int i=-1; i<=1; i+=2) {
        int a = (i==-1) ? 4 : 5;
        vertices[a][0] = Vec3( length/2, -i*breadth/2, i*height/2);
        vertices[a][1] = Vec3( length/2,  i*breadth/2, i*height/2);
        vertices[a][2] = Vec3(-length/2,  i*breadth/2, i*height/2);
        vertices[a][3] = Vec3(-length/2, -i*breadth/2, i*height/2);
        Vec3 n = Vec3(0, 0, i);
        for(int j=0; j<4; j++)
            normals[a][j] = n;
        if(getMaterial() == nullptr) {
            float d = (i==-1) ? breadth : breadth+length;
            texCoords[a][0] = Vec2(d+length, height);
            texCoords[a][1] = Vec2(d+length, height+breadth);
            texCoords[a][2] = Vec2(d, height+breadth);
            texCoords[a][3] = Vec2(d, height);
        }
    }
    
    // Scaling textural coordinates
    if(getMaterial() == nullptr) {
        float imageWidth = 2*(breadth+length);
        float imageHeight = height + 2*breadth;
        for(int i=0; i<6; i++) {
            for(int j=0; j<4; j++) {
                texCoords[i][j].x /= imageWidth;
                texCoords[i][j].y /= imageHeight;
            }
        }
    }
    
    // The textural coordinates when using a material
    if(getMaterial() != nullptr) {
        for(int i=0; i<6; i++) {
            texCoords[i][0] = Vec2(1, 0);
            texCoords[i][1] = Vec2(1, 1);
            texCoords[i][2] = Vec2(0, 1);
            texCoords[i][3] = Vec2(0, 0);
        }
    }
    
    // Setting indecies for all 6 faces
    for(int i=0; i<6; i++) {
        indecies[i][0] = i*4 + 0;
        indecies[i][1] = i*4 + 1;
        indecies[i][2] = i*4 + 2;
        indecies[i][3] = i*4 + 2;
        indecies[i][4] = i*4 + 3;
        indecies[i][5] = i*4 + 0;
    }
    
    return Mesh(&vertices[0][0], &normals[0][0], &texCoords[0][0], 24,
                &indecies[0][0], 36);
}

/**
 * @brief Gets the dimension of the cube
 * 
 * @return Cubic dimension
 */
Vec3 Cube3D::getDimension() const {
    return Vec3(length, breadth, height);
}

/**
 * @brief Sets the material texture
 * 
 * Sets the object to use a predefined material. This material data uses
 * OpenGL context for texture image, normal maps, .etc.
 * 
 * @param mat Predefined material
 */
void Cube3D::setMaterial(Material* mat) {
    Material *prev = getMaterial();
    Object3D::setMaterial(mat);
    if(prev == nullptr)
        setMesh(createMesh());
}

}
