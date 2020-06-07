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

#include "internal/texture_load.hpp"


namespace rmg {

class Context;


/**
 * @brief To enhance the appearance of 2D/3D objects with image data
 */
class Material: public internal::Texture {
  private:
    uint32_t id;
    Context* context;
    internal::ContextLoader::Pending textureLoad;
    
    static uint32_t lastID;
    
    friend class Context;
    
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
     * @param f Path to material textures (folder or zip)
     */
    Material(Context* ctx, const std::string &f);
    
    /**
     * @brief Constructor loads an image from file
     * 
     * Creates a textural material from an image, ceramic tiles, stones,
     * wood, .etc.
     * 
     * @param ctx Conatiner context
     * @param f Path to material textures (folder or zip)
     * @param col Colorize the base image if supported making a color variant
     *            of an existing one
     */
    Material(Context* ctx, const std::string &f, const Color &col);
    
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
    uint32_t getID();
    
    /**
     * @brief Gets the container context
     * 
     * @return Container context
     */
    Context* getContext();
};

}

#endif
