/**
 * @file cylinder.hpp
 * @brief Visual cylinder model
 *
 * Generates a cylinder model. Manipulate the cylinder radius, length
 * location, rotation and scale.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "rmg/cylinder.hpp"


namespace rmg {

/**
 * @brief Default constructor
 */
Cylinder3D::Cylinder3D() {    
    diameter = 1.0f;
    length = 1.0f;
}

/**
 * @brief Constructs a cylinder model from specific dimensions
 * 
 * @param ctx Container context
 * @param d Diameter
 * @param l Length
 */
Cylinder3D::Cylinder3D(Context* ctx, float d, float l): Object3D(ctx)
{
    diameter = d;
    length = l;
    setMesh(createMesh());
}

Mesh Cylinder3D::createMesh() {
    #define FRAGMENT_COUNT 32
    
    Vec3 vertices[FRAGMENT_COUNT+1][4];
    Vec3 normals[FRAGMENT_COUNT+1][4];
    Vec2 texCoords[FRAGMENT_COUNT+1][4];
    uint32_t indecies[FRAGMENT_COUNT][12];
    
    float radius = diameter/2.0f;
    Vec2 c1 = Vec2(radius, radius);
    Vec2 c2 = Vec2(radius, diameter+length);
    float imageWidth = M_PI * diameter;
    float imageHeight = 2*diameter + length;
    
    // Pole vertices
    vertices[FRAGMENT_COUNT][0] = Vec3(0, 0, -length/2);
    vertices[FRAGMENT_COUNT][1] = Vec3(0, 0, length/2);
    normals[FRAGMENT_COUNT][0] = Vec3(0, 0, -1);
    normals[FRAGMENT_COUNT][1] = Vec3(0, 0, 1);
    texCoords[FRAGMENT_COUNT][0].x = c1.x / imageWidth;
    texCoords[FRAGMENT_COUNT][0].y = c1.y / imageHeight;
    texCoords[FRAGMENT_COUNT][1].x = c2.x / imageWidth;
    texCoords[FRAGMENT_COUNT][1].y = c2.y / imageHeight;
    
    // Iterate through the circumference
    for(int i=0; i<FRAGMENT_COUNT; i++) {
        float t = - M_PI/2 - 1 + 2*M_PI*((float)i/FRAGMENT_COUNT);
        float c = cos(t);
        float s = sin(t);
        
        vertices[i][0] = Vec3(radius*c, radius*s, -length/2);
        vertices[i][1] = Vec3(radius*c, radius*s, -length/2);
        vertices[i][2] = Vec3(radius*c, radius*s, length/2);
        vertices[i][3] = Vec3(radius*c, radius*s, length/2);
        normals[i][0] = Vec3(0, 0, -1);
        normals[i][1] = Vec3(c, s, 0);
        normals[i][2] = Vec3(c, s, 0);
        normals[i][3] = Vec3(0, 0, 1);
        
        texCoords[i][0] = c1 + Vec2(radius*c, radius*s);
        texCoords[i][1] = Vec2(radius*t, radius);
        texCoords[i][1] = Vec2(radius*t, diameter+length);
        texCoords[i][3] = c2 + Vec2(radius*c, radius*s);
        
        if(i == 0) {
            indecies[0][0] = (FRAGMENT_COUNT-1)*4;
            indecies[0][1] = FRAGMENT_COUNT*4;
            indecies[0][2] = 0;
            
            indecies[0][3] = (FRAGMENT_COUNT-1)*4 + 2;
            indecies[0][4] = (FRAGMENT_COUNT-1)*4 + 1;
            indecies[0][5] = 1;
            indecies[0][6] = 1;
            indecies[0][7] = 2;
            indecies[0][8] = (FRAGMENT_COUNT-1)*4 + 2;
            
            indecies[0][9] = (FRAGMENT_COUNT-1)*4 + 3;
            indecies[0][10] = 3;
            indecies[0][11] = FRAGMENT_COUNT*4 + 1;
        }
        else {
            indecies[i][0] = (i-1)*4;
            indecies[i][1] = FRAGMENT_COUNT*4;
            indecies[i][2] = i*4;
            
            indecies[i][3] = (i-1)*4 + 2;
            indecies[i][4] = (i-1)*4 + 1;
            indecies[i][5] = i*4 + 1;
            indecies[i][6] = i*4 + 1;
            indecies[i][7] = i*4 + 2;
            indecies[i][8] = (i-1)*4 + 2;
            
            indecies[i][9] = (i-1)*4 + 3;
            indecies[i][10] = i*4 + 3;
            indecies[i][11] = FRAGMENT_COUNT*4 + 1;
        }
    }
    
    // Scaling textural coordinates
    if(getMaterial() == nullptr) {
        float imageWidth = M_PI * diameter;
        float imageHeight = length + 2*diameter;
        for(int i=0; i<FRAGMENT_COUNT; i++) {
            for(int j=0; j<4; j++) {
                texCoords[i][j].x /= imageWidth;
                texCoords[i][j].y /= imageHeight;
            }
        }
    }
    
    return Mesh(
        &vertices[0][0],
        &normals[0][0],
        &texCoords[0][0],
        FRAGMENT_COUNT*4 + 2,
        &indecies[0][0],
        FRAGMENT_COUNT*12
    );
    #undef FRAGMENT_COUNT
}

/**
 * @brief Gets the cylinder diameter
 * 
 * @return Diameter
 */
float Cylinder3D::getDiameter() const { return diameter; }

/**
 * @brief Gets the cylinder length
 * 
 * @return Length
 */
float Cylinder3D::getLength() const { return length; }

/**
 * @brief Sets the material texture
 * 
 * Sets the object to use a predefined material. This material data uses
 * OpenGL context for texture image, normal maps, .etc.
 * 
 * @param mat Predefined material
 */
void Cylinder3D::setMaterial(Material* mat) {
    Material *prev = getMaterial();
    Object3D::setMaterial(mat);
    if(prev == nullptr)
        setMesh(createMesh());
}

}
