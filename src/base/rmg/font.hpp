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


#include "internal/context_load.hpp"
#include "internal/sprite_load.hpp"
#include "math/vec2.hpp"


namespace rmg {

class Context;


/**
 * @brief Dimensions for a glyph
 */
struct GlyphMetrics {
    uint8_t width; ///< Width of glyph
    uint8_t height; ///< Height of glyph
    Rect bearing; ///< Offset from baseline to left/top of glyph
    uint8_t advance; ///< Offset to advance to next glyph
};


/**
 * @brief For rendering texts on the context
 */
class RMG_API Font {
  private:
    uint32_t id;
    Context* context;
    internal::SpriteTexture texture;
    internal::Pending textureLoad;
    uint8_t size;
    GlyphMetrics characters[256];
    
    static uint32_t lastID;
    
  public:
    /**
     * @brief Constructor loads a font from file
     * 
     * @param ctx Conatiner context
     * @param f Path to font file (.ttf)
     * @param p Font size
     */
    Font(Context* ctx, const char* f, uint8_t p=16);
    
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
    
    /**
     * @brief Gets the font size
     * 
     * @return The font size in pixels
     */
    uint8_t getSize() const;
    
    /**
     * @brief Gets the glyph of a character
     * 
     * @param c The character
     * 
     * @return The glyph containing the metrics
     */
    GlyphMetrics getGlyphMetrics(char c) const;
    
    /**
     * @brief Gets the pointer to the texture
     * 
     * @return Pointer to the texture
     */
    const internal::SpriteTexture *getTexture() const;
    
    /**
     * @brief Gets the texture loader
     * 
     * @return Texture loader
     */
    const internal::Pending& getTextureLoad() const;
};

/**
 * @brief Indication of the use of default font
 */
#define RMG_DEFAULT_FONT nullptr

}

#endif
