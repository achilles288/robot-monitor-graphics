/**
 * @file object3d_obj.cpp
 * @brief Loads and constructs 3D objects from .OBJ files
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "rmg/object3d.hpp"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>


namespace rmg {

static void printLoadError(const char *file) {
    #ifdef _WIN32
    printf("error: Failed to load 3D model `%s`\n", file);
    #else
    printf("\033[0;1;31merror: \033[0m"
           "Failed to load 3D model \033[1m'%s'\033[0m\n", file);
    #endif
}


#define SAFE_PUSH(VEC, I) \
    if(std::max(I[0], std::max(I[1], I[2])) - 1 >= temp_ ## VEC.size()) { \
        printf("Vertex index out of bounds exception\n"); \
        printLoadError(file); \
        return; \
    } \
    VEC.push_back(temp_ ## VEC [I[0] - 1]); \
    VEC.push_back(temp_ ## VEC [I[1] - 1]); \
    VEC.push_back(temp_ ## VEC [I[2] - 1]); \


void Object3D::loadOBJ(const char* file, bool smooth) {
    FILE *fp = fopen(file, "r");
    if(fp == NULL) {
        #ifdef _WIN32
        printf("error: File '%s' could not be opened\n", file);
        #else
        printf("\033[0;1;31merror: \033[0m"
               "File \033[1m'%s'\033[0m "
               "could not be opened\n", file);
        #endif
        return;
    }
    
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> texCoords;
    std::vector<Vec3> temp_vertices;
    std::vector<Vec3> temp_normals;
    std::vector<Vec2> temp_texCoords;
    
    bool indexing = false;
    
    while(true) {
        char lineHeader[128];
        // Reads the first word of the line
        int res = fscanf(fp, "%s", lineHeader);
        if(res == EOF)
            break; // EOF = End Of File. Quit the loop.
        
        // Reads the vertices
        if(!indexing) {
            if(strcmp(lineHeader, "v") == 0) {
                Vec3 vert;
                int matches = fscanf(
                    fp,
                    "%f %f %f\n",
                    &vert[0],
                    &vert[1],
                    &vert[2]
                );
                if(matches != 3) {
                }
                temp_vertices.push_back(vert);
            }
            else if(strcmp(lineHeader, "vn") == 0) {
                Vec3 norm;
                fscanf(fp, "%f %f %f\n", &norm[0], &norm[1], &norm[2]);
                temp_normals.push_back(norm);
            }
            else if(strcmp(lineHeader, "vt") == 0) {
                Vec2 tex;
                fscanf(fp, "%f %f\n", &tex[0], &tex[1]);
                temp_texCoords.push_back(tex);
            }
            else if(strcmp(lineHeader, "f") == 0) {
                indexing = true;
                vertices.reserve(temp_vertices.size());
                normals.reserve(temp_normals.size());
                texCoords.reserve(temp_texCoords.size());
            }
        }
        
        // Builds the polygons
        if(strcmp(lineHeader, "f") == 0) {
            if(temp_vertices.size() > 0 && temp_normals.size() > 0 &&
               temp_texCoords.size() > 0)
            {
                uint32_t vertexIndices[3];
                uint32_t texCoordIndices[3];
                uint32_t normalIndices[3];
                int matches = fscanf(
                    fp,
                    "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &vertexIndices[0],
                    &texCoordIndices[0],
                    &normalIndices[0],
                    &vertexIndices[1],
                    &texCoordIndices[1],
                    &normalIndices[1],
                    &vertexIndices[2],
                    &texCoordIndices[2],
                    &normalIndices[2]
                );
                if(matches != 9) {
                    printLoadError(file);
                    return;
                }
                SAFE_PUSH(vertices, vertexIndices);
                SAFE_PUSH(normals, normalIndices);
                SAFE_PUSH(texCoords, texCoordIndices);
            }
            
            else if(temp_vertices.size() > 0 && temp_normals.size() > 0)
            {
                uint32_t vertexIndices[3];
                uint32_t normalIndices[3];
                int matches = fscanf(
                    fp,
                    "%d//%d %d//%d %d//%d\n",
                    &vertexIndices[0],
                    &normalIndices[0],
                    &vertexIndices[1],
                    &normalIndices[1],
                    &vertexIndices[2],
                    &normalIndices[2]
                );
                if(matches != 6) {
                    printLoadError(file);
                    return;
                }
                SAFE_PUSH(vertices, vertexIndices);
                SAFE_PUSH(normals, normalIndices);
            }
            
            else if(temp_vertices.size() > 0 && temp_texCoords.size() > 0)
            {
                uint32_t vertexIndices[3];
                uint32_t texCoordIndices[3];
                int matches = fscanf(
                    fp,
                    "%d/%d %d/%d %d/%d\n",
                    &vertexIndices[0],
                    &texCoordIndices[0],
                    &vertexIndices[1],
                    &texCoordIndices[1],
                    &vertexIndices[2],
                    &texCoordIndices[2]
                );
                if(matches != 6) {
                    printLoadError(file);
                    return;
                }
                SAFE_PUSH(vertices, vertexIndices);
                SAFE_PUSH(texCoords, texCoordIndices);
            }
            
            else if(temp_vertices.size() > 0) {
                uint32_t vertexIndices[3];
                int matches = fscanf(
                    fp,
                    "%d %d %d\n",
                    &vertexIndices[0],
                    &vertexIndices[1],
                    &vertexIndices[2]
                );
                if(matches != 3) {
                    printLoadError(file);
                    return;
                }
                SAFE_PUSH(vertices, vertexIndices);
            }
            
            else {
                printLoadError(file);
                return;
            }
        }
    }
    
    // Completes the mesh
    if(vertices.size() > 0 && normals.size() > 0 && texCoords.size() > 0) {
        Mesh mesh = Mesh(
            &vertices[0],
            &normals[0],
            &texCoords[0],
            vertices.size()
        );
        setMesh(mesh);
    }
    else if(vertices.size() > 0 && normals.size() > 0) {
        Mesh mesh = Mesh(
            &vertices[0],
            &normals[0],
            nullptr,
            vertices.size()
        );
        setMesh(mesh);
    }
    else if(vertices.size() > 0 && texCoords.size() > 0) {
        Mesh mesh = Mesh(
            &vertices[0],
            &texCoords[0],
            vertices.size(),
            smooth
        );
        setMesh(mesh);
    }
    else if(vertices.size() > 0) {
        Mesh mesh = Mesh(
            &vertices[0],
            vertices.size(),
            smooth
        );
        setMesh(mesh);
    }
}

}
