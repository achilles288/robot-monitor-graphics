/**
 * @file material.cpp
 * @brief To enhance the appearance of 2D/3D objects with image data
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "rmg/material.hpp"


namespace rmg {

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
Material::Material(Context* ctx, const std::string &f): Material(ctx)
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

}
