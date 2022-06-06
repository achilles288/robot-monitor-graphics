/**
 * @file material.cpp
 * @brief To enhance the appearance of 2D/3D objects with image data
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "rmg/material.hpp"


namespace rmg {

// Class: Material

uint32_t Material::lastID = 0;

/**
 * @brief Constructor
 * 
 * Creates a plain color material.
 * 
 * @param ctx Conatiner context
 */
Material::Material(Context* ctx): internal::Texture() {
    id = ++lastID;
    context = ctx;
}

/**
 * @brief Constructor loads an image from file
 * 
 * Creates a textural material from an image, ceramic tiles, stones,
 * wood, .etc.
 * 
 * @param ctx Conatiner context
 * @param f Path to image file (.png)
 */
Material::Material(Context* ctx, const char* f): Material(ctx)
{
    
    
}

/**
 * @brief Destructor
 */
Material::~Material() {}

/**
 * @brief Gets texture ID
 * 
 * @return Material ID
 */
uint32_t Material::getID() const { return id; }

/**
 * @brief Gets the container context
 * 
 * @return Container context
 */
Context* Material::getContext() const { return context; }

/**
 * @brief Gets the texture loader
 * 
 * @return Texture loader
 */
const internal::Pending& Material::getTextureLoad() const { return texLoad; }




// Class: MaterialList

MaterialList::iterator::iterator(LinkedList<Material>::Node* n, Material* d) {
    next = n;
    data = d;
}

Material& MaterialList::iterator::operator * () { return *data; }

Material* MaterialList::iterator::operator -> () { return data; }

MaterialList::iterator& MaterialList::iterator::operator ++ () {
    if(next != nullptr) {
        data = next->data;
        next = next->next;
    }
    else {
        data = nullptr;
    }
    return *this;
}

MaterialList::iterator MaterialList::iterator::operator ++ (int) {
    iterator tmp = iterator(next, data);
    if(next != nullptr) {
        data = next->data;
        next = next->next;
    }
    else {
        data = nullptr;
    }
    return tmp;
}

bool MaterialList::iterator::operator == (const iterator& it) {
    return next == it.next && data == it.data;
}

bool MaterialList::iterator::operator != (const iterator& it) {
    return next != it.next || data != it.data;
}

/**
 * @brief Gets the start of the list
 * 
 * @return An iterator as in C++ STL containers
 */
MaterialList::iterator MaterialList::begin() const {
    return iterator(next, data);
}

/**
 * @brief Gets the end of the list
 * 
 * @return An iterator as in C++ STL containers
 */
MaterialList::iterator MaterialList::end() const {
    return iterator(nullptr, nullptr);
}

}
