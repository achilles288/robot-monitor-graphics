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
#include "util/linked_list.hpp"


namespace rmg {

class Context;


/**
 * @brief Dimensions for a glyph
 */
struct GlyphMetrics {
    uint16_t width; ///< Width of glyph
    uint16_t height; ///< Height of glyph
    Vec2i bearing; ///< Offset from baseline to left/top of glyph
    uint16_t advance; ///< Offset to advance to next glyph
};


/**
 * @brief For rendering texts on the context
 */
class RMG_API Font {
  private:
    uint32_t id;
    Context* context;
    internal::SpriteTexture texture;
    internal::Pending texLoad;
    uint16_t size;
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
    Font(Context* ctx, const char* f, uint16_t p=16);
    
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
    uint16_t getSize() const;
    
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


/**
 * @brief A list of fonts stored in a forward-linked list
 */
class RMG_API FontList: public LinkedList<Font> {
    class RMG_API iterator {
      private:
        LinkedList<Font>::Node* next = nullptr;
        Font* data = nullptr;
      
      public:
        iterator(LinkedList<Font>::Node* n, Font* d);
        
        Font& operator * ();
        
        Font* operator -> ();
        
        iterator& operator ++ ();
        
        iterator operator ++ (int);
        
        bool operator == (const iterator& it);
        
        bool operator != (const iterator& it);
    };

  public:
    /**
     * @brief Gets the start of the list
     * 
     * @return An iterator as in C++ STL containers
     */
    iterator begin() const;

    /**
     * @brief Gets the end of the list
     * 
     * @return An iterator as in C++ STL containers
     */
    iterator end() const;
};

}

#endif
