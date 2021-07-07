/**
 * @file mesh_indices.cpp
 * @brief Discards the duplicated verticies and performs VBO indexing
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "rmg/mesh.hpp"

#include <cstdlib>
#include <cstring>
#include <unordered_map>


namespace rmg {

void Mesh::removeIndices() {
    if(indices == nullptr)
        return;
    Vec3 *tempVertices = nullptr;
    Vec3 *tempNormals = nullptr;
    Vec2 *tempTexCoords = nullptr;
    if(vertices != nullptr) {
        tempVertices = (Vec3*) malloc(sizeof(Vec3)*index_count);
        for(uint32_t i=0; i<index_count; i++)
            tempVertices[i] = vertices[indices[i]];
        free(vertices);
        vertices = tempVertices;
    }
    if(normals != nullptr) {
        tempNormals = (Vec3*) malloc(sizeof(Vec3)*index_count);
        for(uint32_t i=0; i<index_count; i++)
            tempNormals[i] = normals[indices[i]];
        free(normals);
        normals = tempNormals;
    }
    if(texCoords != nullptr) {
        tempTexCoords = (Vec2*) malloc(sizeof(Vec2)*index_count);
        for(uint32_t i=0; i<index_count; i++)
            tempTexCoords[i] = texCoords[indices[i]];
        free(texCoords);
        texCoords = tempTexCoords;
    }
    free(indices);
    vertex_count = index_count;
    index_count = 0;
}


void Mesh::buildIndices() {
    removeIndices();
    if(texCoords == nullptr)
        buildIndices1();
    else
        buildIndices2();
}


template <typename T>
static void combineHash(size_t& seed, const T& key) {
    seed ^= std::hash<T>{}(key) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}


void Mesh::buildIndices1() {
    auto hash = [](const std::pair<Vec3,Vec3>& k) {
        size_t seed = 0;
        combineHash(seed, k.first);
        combineHash(seed, k.second);
        return seed;
    };
    
    auto equal = [](const std::pair<Vec3,Vec3>& a,
                    const std::pair<Vec3,Vec3>& b)
    {
        return (a.first == b.first) && (a.second == b.second);
    };
    
    std::unordered_map
        <std::pair<Vec3,Vec3>, uint32_t,
         decltype(hash), decltype(equal)> table(65536, hash, equal);
    
    index_count = vertex_count;
    indices = (uint32_t*) malloc(sizeof(uint32_t)*index_count);
    Vec3 *tempVertices = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
    Vec3 *tempNormals = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
    
    for(uint32_t i=0; i<vertex_count; i++) {
        auto key = std::make_pair(vertices[i], normals[i]);
        auto res = table.find(key);
        if(res == table.end()) {
            uint32_t k = table.size();
            tempVertices[k] = vertices[i];
            tempNormals[k] = normals[i];
            indices[i] = k;
            auto elem = std::make_pair(key, k);
            table.insert(elem);
        }
        else {
            indices[i] = res->second;
        }
    }
    
    vertex_count = table.size();
    free(vertices);
    free(normals);
    vertices = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
    normals = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
    memcpy(vertices, tempVertices, sizeof(Vec3)*table.size());
    memcpy(normals, tempNormals, sizeof(Vec3)*table.size());
    free(tempVertices);
    free(tempNormals);
}


void Mesh::buildIndices2() {
    auto hash = [](const std::tuple<Vec3,Vec3,Vec2>& k) {
        size_t seed = 0;
        combineHash(seed, std::get<0>(k));
        combineHash(seed, std::get<1>(k));
        combineHash(seed, std::get<2>(k));
        return seed;
    };
    
    auto equal = [](const std::tuple<Vec3,Vec3,Vec2>& a,
                    const std::tuple<Vec3,Vec3,Vec2>& b)
    {
        return (std::get<0>(a) == std::get<0>(b)) &&
               (std::get<1>(a) == std::get<1>(b)) &&
               (std::get<2>(a) == std::get<2>(b));
    };
    
    std::unordered_map
        <std::tuple<Vec3,Vec3,Vec2>, uint32_t,
         decltype(hash), decltype(equal)> table(65536, hash, equal);
    
    index_count = vertex_count;
    indices = (uint32_t*) malloc(sizeof(uint32_t)*index_count);
    Vec3 *tempVertices = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
    Vec3 *tempNormals = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
    Vec2 *tempTexCoords = (Vec2*) malloc(sizeof(Vec2)*vertex_count);
    
    for(uint32_t i=0; i<vertex_count; i++) {
        auto key = std::make_tuple(vertices[i], normals[i], texCoords[i]);
        auto res = table.find(key);
        if(res == table.end()) {
            uint32_t k = table.size();
            tempVertices[k] = vertices[i];
            tempNormals[k] = normals[i];
            tempTexCoords[k] = texCoords[i];
            indices[i] = k;
            auto elem = std::make_pair(key, k);
            table.insert(elem);
        }
        else {
            indices[i] = res->second;
        }
    }
    
    vertex_count = table.size();
    free(vertices);
    free(normals);
    free(texCoords);
    vertices = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
    normals = (Vec3*) malloc(sizeof(Vec3)*vertex_count);
    texCoords = (Vec2*) malloc(sizeof(Vec2)*vertex_count);
    memcpy(vertices, tempVertices, sizeof(Vec3)*table.size());
    memcpy(normals, tempNormals, sizeof(Vec3)*table.size());
    memcpy(texCoords, tempTexCoords, sizeof(Vec2)*table.size());
    free(tempVertices);
    free(tempNormals);
    free(tempTexCoords);
}

}
