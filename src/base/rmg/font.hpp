/**
 * @file font.hpp
 * @brief For rendering texts on the context
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_FONT_H__
#define __RMG_FONT_H__ ///< Header guard

#ifndef RMG_API
#ifdef _WIN32
#ifdef RMG_EXPORT
#define RMG_API __declspec(dllexport) ///< RMG API
#else
#define RMG_API __declspec(dllimport) ///< RMG API
#endif
#else
#define RMG_API ///< RMG API
#endif
#endif


#include <cstdint>
#include <memory>
#include <string>

#include "internal/context_load.hpp"
#include "internal/texture_load.hpp"


namespace rmg {

class Context;


/**
 * @brief For rendering texts on the context
 */
class RMG_API Font {
  private:
    uint32_t id;
    Context* context;
    internal::Texture texture;
    internal::Pending textureLoad;
    
    static uint32_t lastID;
    
    friend class Context;
    
  public:
    /**
     * @brief Constructor loads a font from file
     * 
     * @param ctx Conatiner context
     * @param f Path to font file (.ttf)
     */
    Font(Context* ctx, const std::string &f);
    
    /**
     * @brief Destructor
     */
    virtual ~Font();
    
    /**
     * @brief Copy constructor (deleted)
     * 
     * Copy constructor is not allowed to use since it contains a unique
     * pointer.
     * 
     * @param ft Source font
     */
    Font(const Font& ft) = delete;
    
    /**
     * @brief Move constructor
     * 
     * @param ft Source font
     */
    Font(Font&& ft) noexcept = default;
    
    /**
     * @brief Copy assignment (deleted)
     * 
     * Copy assignment is not allowed to use since it contains a unique
     * pointer.
     * 
     * @param ft Source font
     */
    Font& operator=(const Font& ft) = delete;
    
    /**
     * @brief Move assignment
     * 
     * @param ft Source font
     */
    Font& operator=(Font&& ft) noexcept = default;
    
    /**
     * @brief Gets font ID
     * 
     * @return Font ID
     */
    uint32_t getID() const;
    
    /**
     * @brief Gets the container context
     * 
     * @return Container context
     */
    Context* getContext() const;
};

/**
 * @brief Indication of the use of default font
 */
#define RMG_DEFAULT_FONT nullptr

}

#endif
