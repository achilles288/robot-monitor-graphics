/**
 * @file material.hpp
 * @brief To enhance the appearance of 2D/3D objects with image data
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_MATERIAL_H__
#define __RMG_MATERIAL_H__

#include <cstdint>
#include <string>

#include "color.hpp"
#include "internal/context_load.hpp"
#include "internal/texture_load.hpp"


namespace rmg {

class Context;


/**
 * @brief To enhance the appearance of 2D/3D objects with image data
 */
class Material {
  private:
    uint32_t id;
    Context* context;
    internal::Texture texture;
    internal::ContextLoader::Pending textureLoad;
    Color color;
    float diffusion;
    float specularity;
    
    static uint64_t lastID;
    
  public:
    /**
     * @brief Constructor
     * 
     * Creates a plain color material.
     * 
     * @param ctx Conatiner context
     */
    Material(Context* ctx);
    
    /**
     * @brief Constructor loads an image from file
     * 
     * Creates a textural material from an image, ceramic tiles, stones,
     * wood, .etc.
     * 
     * @param ctx Conatiner context
     * @param f Path to image file (.png)
     */
    Material(Context* ctx, const std::string &f);
    
    /**
     * @brief Destructor
     */
    virtual ~Material();
    
    /**
     * @brief Copy constructor (deleted)
     * 
     * Copy constructor is not allowed to use since it contains a unique
     * pointer.
     * 
     * @param mat Source material
     */
    Material(const Material& mat) = delete;
    
    /**
     * @brief Move constructor
     * 
     * @param mat Source material
     */
    Material(Material&& mat) noexcept = default;
    
    /**
     * @brief Copy assignment (deleted)
     * 
     * Copy assignment is not allowed to use since it contains a unique
     * pointer.
     * 
     * @param mat Source material
     */
    Material& operator=(const Material& mat) = delete;
    
    /**
     * @brief Move assignment
     * 
     * @param mat Source material
     */
    Material& operator=(Material&& mat) noexcept = default;
    
    /**
     * @brief Gets texture ID
     * 
     * @return Material ID
     */
    uint64_t getID();
    
    /**
     * @brief Gets the container context
     * 
     * @return Container context
     */
    Context* getContext();
    
    /**
     * @brief Sets material color
     * 
     * @param r Red
     * @param g Green
     * @param b Blue
     */
    void setColor(float r, float g, float b);
    
    /**
     * @brief Sets material color
     * 
     * @param r Red
     * @param g Green
     * @param b Blue
     * @param a Alpha
     */
    void setColor(float r, float g, float b, float a);
    
    /**
     * @brief Sets material color
     * 
     * @param col RGBA color
     */
    void setColor(const Color &col);
    
    /**
     * @brief Gets material color
     * 
     * @return RGBA color
     */
    Color getColor();
    
    /**
     * @brief Sets the diffusion coefficient of the 3D object material
     * 
     * Diffused light diffuses along the whole surface almost uniformly.
     * 
     * @param diff Diffusion coefficient
     */
    void setDiffusion(float diff);
    
    /**
     * @brief Gets the diffusion coefficient of the 3D object material
     * 
     * Diffused light diffuses along the whole surface almost uniformly.
     * 
     * @return Diffusion coefficient
     */
    float getDiffusion();
    
    /**
     * @brief Sets the specularity coefficient of the 3D object material
     * 
     * Specular light means reflected light and this property usually forms
     * bright spot at some angles of the object.
     * 
     * @param spec Specularity coefficient
     */
    void setSpecularity(float spec);
    
    /**
     * @brief Gets the specularity coefficient of the 3D object material
     * 
     * Specular light means reflected light and this property usually forms
     * bright spot at some angles of the object.
     * 
     * @return Specularity coefficient
     */
    float getSpecularity();
};

}

#endif
