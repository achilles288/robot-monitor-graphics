/**
 * @file font.cpp
 * @brief For rendering texts on the context
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "rmg/font.hpp"

#include <rmg/config.h>

#include <cstdio>

#include <ft2build.h>
#include FT_FREETYPE_H


namespace rmg {

uint32_t Font::lastID = 0;

/**
 * @brief Constructor loads a font from file
 * 
 * @param ctx Conatiner context
 * @param f Path to font file (.ttf)
 * @param p Font size
 */
Font::Font(Context* ctx, const char* f, uint8_t p) {
    id = ++lastID;
    context = ctx;
    if(f == nullptr)
        f = RMG_RESOURCE_PATH "/font.ttf";
    size = p;
    
    FT_Library ft;
    if(FT_Init_FreeType(&ft)) {
        #ifdef _WIN32
        printf("error: Failed to load FreeType library\n");
        #else
        printf("\033[0;1;31merror: \033[0m Failed to load FreeType library\n");
        #endif
        return;
    }
    FT_Face face;
    if(FT_New_Face(ft, f, 0, &face)) {
        #ifdef _WIN32
        printf("error: Failed to load the font `%s`\n", f);
        #else
        printf("\033[0;1;31merror: \033[0m: Failed to load the font "
               "\033[0;1m`%s`\033[0m\n", f);
        #endif
        return;
    }
    FT_Set_Pixel_Sizes(face, 0, size);
    Bitmap bmp = Bitmap(16*size, 16*size, 1);
    
    for(int i=0; i<256; i++) {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER))
            continue;
        uint16_t w = face->glyph->bitmap.width;
        uint16_t h = face->glyph->bitmap.rows;
        Bitmap glyph = Bitmap(w, h, 1, face->glyph->bitmap.buffer);
        if(w > size || h > size) {
            if(w > size)
                w = size;
            if(h > size)
                h = size;
            glyph.crop(0, 0, w, h);
        }
        uint8_t x = i % 16;
        uint8_t y = i / 16;
        bmp.paste(glyph, x*size, y*size);
        characters[i].width = w;
        characters[i].height = h;
        characters[i].bearing.x = face->glyph->bitmap_left;
        characters[i].bearing.x = face->glyph->bitmap_top;
        characters[i].advance = face->glyph->advance.x;
    }
}

/**
 * @brief Destructor
 */
Font::~Font() {}

/**
 * @brief Gets font ID
 * 
 * @return Font ID
 */
uint32_t Font::getID() const { return id; }

/**
 * @brief Gets the container context
 * 
 * @return Container context
 */
Context* Font::getContext() const { return context; }

/**
 * @brief Gets the font size
 * 
 * @return The font size in pixels
 */
uint8_t Font::getSize() const { return size; }

/**
 * @brief Gets the glyph of a character
 * 
 * @param c The character
 * 
 * @return The glyph containing the metrics
 */
GlyphMetrics Font::getGlyphMetrics(char c) const {
    return characters[(uint8_t) c];
}

/**
 * @brief Gets the pointer to the texture
 * 
 * @return Pointer to the texture
 */
const internal::SpriteTexture *Font::getTexture() const { return &texture; }

/**
 * @brief Gets the texture loader
 * 
 * @return Texture loader
 */
const internal::Pending& Font::getTextureLoad() const { return textureLoad; }

}
