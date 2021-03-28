/**
 * @file mesh_normals.cpp
 * @brief Calculates the normal vectors of the polygons
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "mesh.hpp"

#include <algorithm>
#include <cstdlib>
#include <unordered_map>


namespace rmg {

void Mesh::buildNormals(bool smooth) {
    removeIndices();
    if(smooth)
        buildNormals2();
    else
        buildNormals1();
}


void Mesh::buildNormals1() {
    normals = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
    uint32_t polygon_count = vertex_count / 3;
    for(uint32_t i=0; i<polygon_count; i++) {
        Vec3 p01 = vertices[i*3 + 1] - vertices[i*3];
        Vec3 p02 = vertices[i*3 + 2] - vertices[i*3];
        Vec3 n = (p01 * p02).normalize();
        normals[i*3 + 0] = n;
        normals[i*3 + 1] = n;
        normals[i*3 + 2] = n;
    }
}


void Mesh::buildNormals2() {
    normals = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
    uint32_t polygon_count = vertex_count / 3;
    Vec3 *faceNormals = (Vec3*) malloc(sizeof(Vec3)*polygon_count);
    float *angles = (float*) malloc(sizeof(float)*vertex_count);
    std::unordered_multimap<Vec3, uint32_t> table;
    
    // Generate hard edged normals and vertex angles
    for(uint32_t i=0; i<polygon_count; i++) {
        Vec3 p01 = vertices[i*3 + 1] - vertices[i*3];
        Vec3 p02 = vertices[i*3 + 2] - vertices[i*3];
        Vec3 p12 = vertices[i*3 + 2] - vertices[i*3 + 1];
        
        faceNormals[i] = (p01 * p02).normalize();
        
        float cosT0, cosT1, cosT2;
        cosT0 = Vec3::dot( p01,  p02) / (p01.magnitude() * p02.magnitude());
        cosT1 = Vec3::dot( p12, -p01) / (p12.magnitude() * p01.magnitude());
        cosT2 = Vec3::dot(-p02, -p12) / (p02.magnitude() * p12.magnitude());
        angles[i*3 + 0] = acos(cosT0);
        angles[i*3 + 1] = acos(cosT1);
        angles[i*3 + 2] = acos(cosT2);
        
        table.insert(std::make_pair(vertices[i*3 + 0], i*3));
        table.insert(std::make_pair(vertices[i*3 + 1], i*3 + 1));
        table.insert(std::make_pair(vertices[i*3 + 2], i*3 + 2));
    }
    
    // Soften the edges with slightly different normals
    for(uint32_t i=0; i<vertex_count; i++) {
        auto range = table.equal_range(vertices[i]);
        int count = std::distance(range.first, range.second);
        
        if(count > 1) {
            Vec3 n;
            Vec3 n1 = faceNormals[i/3];
            for(auto it=range.first; it!=range.second; it++) {
                Vec3 n2 = faceNormals[it->second/3];
                float cosT = Vec3::dot(n1, n2);
                if(cosT > 0.866025f) // 30 degrees
                    n += n2 * angles[it->second];
            }
            normals[i] = n.normalize();
        }
        else {
            normals[i] = faceNormals[i/3];
        }
    }
}

}
