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
Material::Material(Context* ctx) {
    id = ++lastID;
    context = ctx;
    color = Color(1, 1, 1, 1);
    diffusion = 0.5f;
    specularity = 0.5f;
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
uint32_t Material::getID() { return id; }

/**
 * @brief Gets the container context
 * 
 * @return Container context
 */
Context* Material::getContext() { return context; }

/**
 * @brief Sets material color
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 */
void Material::setColor(float r, float g, float b) {
    color.red = r;
    color.green = g;
    color.blue = b;
}

/**
 * @brief Sets material color
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 * @param a Alpha
 */
void Material::setColor(float r, float g, float b, float a) {
    color.red = r;
    color.green = g;
    color.blue = b;
    color.alpha = a;
}

/**
 * @brief Sets material color
 * 
 * @param col RGBA color
 */
void Material::setColor(const Color &col) { color = col; }

/**
 * @brief Gets material color
 * 
 * @return RGBA color
 */
Color Material::getColor() { return color; }

/**
 * @brief Sets the diffusion coefficient of the 3D object material
 * 
 * Diffused light diffuses along the whole surface almost uniformly.
 * 
 * @param diff Diffusion coefficient
 */
void Material::setDiffusion(float diff) { diffusion = diff; }

/**
 * @brief Gets the diffusion coefficient of the 3D object material
 * 
 * Diffused light diffuses along the whole surface almost uniformly.
 * 
 * @return Diffusion coefficient
 */
float Material::getDiffusion() { return diffusion; }

/**
 * @brief Sets the specularity coefficient of the 3D object material
 * 
 * Specular light means reflected light and this property usually forms
 * bright spot at some angles of the object.
 * 
 * @param spec Specularity coefficient
 */
void Material::setSpecularity(float spec) { specularity = spec; }

/**
 * @brief Gets the specularity coefficient of the 3D object material
 * 
 * Specular light means reflected light and this property usually forms
 * bright spot at some angles of the object.
 * 
 * @return Specularity coefficient
 */
float Material::getSpecularity() { return specularity; }

}
