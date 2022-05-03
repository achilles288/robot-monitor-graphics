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

#ifndef RMG_API
#ifdef _WIN32
#ifdef RMG_EXPORT
#define RMG_API __declspec(dllexport)
#else
#define RMG_API __declspec(dllimport)
#endif
#else
#define RMG_API
#endif
#endif


#include <cstdint>
#include <string>

#include "bitmap.hpp"
#include "internal/texture_load.hpp"


namespace rmg {

class Context;


/**
 * @brief To enhance the appearance of 2D/3D objects with image data
 */
class RMG_API Material: public internal::Texture {
  private:
    uint32_t id;
    Context* context;
    internal::Pending textureLoad;
    
    static uint32_t lastID;
    
    void swap(Material& mat) noexcept;
    
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
     * @param f Path to material textures (file, folder or zip)
     */
    Material(Context* ctx, const std::string &f);
    
    /**
     * @brief Constructs from bitmap object
     * 
     * Creates a textural material from an image, ceramic tiles, stones,
     * wood, .etc.
     * 
     * @param ctx Conatiner context
     * @param bmp Base image
     */
    Material(Context* ctx, const Bitmap &bmp);
    
    /**
     * @brief Constructs from a set of bitmap objects
     * 
     * Creates a textural material from an image, ceramic tiles, stones,
     * wood, .etc.
     * 
     * @param ctx Conatiner context
     * @param base Base image
     * @param h Height mapping
     * @param norm Normal mapping
     * @param m Metallic, rough, ambient occulation
     * @param e Emissivity
     */
    Material(Context* ctx, const Bitmap& base, const Bitmap& h,
             const Bitmap& norm, const Bitmap& m, const Bitmap& e);
    
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
    Material(Material&& mat) noexcept;
    
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
    Material& operator=(Material&& mat) noexcept;
    
    /**
     * @brief Gets texture ID
     * 
     * @return Material ID
     */
    uint32_t getID() const;
    
    /**
     * @brief Gets the container context
     * 
     * @return Container context
     */
    Context* getContext() const;
};

}

#endif
