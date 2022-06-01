/**
 * @file text2d.cpp
 * @brief Renders text as an 2D object
 * 
 * In addition to 2D sprites and 3D models, text rendering is also important
 * for score board and some kind of monitoring.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "rmg/text2d.hpp"

#include "rmg/assert.hpp"

#include <cstring>


namespace rmg {

/**
 * @brief Constructor with loaded font
 * 
 * @param ctx Container context
 * @param ft Loaded font
 */
Text2D::Text2D(Context* ctx, Font* ft)
       :Object2D(ctx)
{
    RMG_ASSERT(ft->getContext() == ctx);
    font = ft;
    text.copy("Text");
    type2D = Object2DType::Text;
}

/**
 * @brief Constructor with loaded font
 * 
 * @param ctx Container context
 * @param ft Loaded font
 * @param txt String to display
 */
Text2D::Text2D(Context* ctx, Font* ft, const char *txt)
       :Object2D(ctx)
{
    RMG_ASSERT(ft->getContext() == ctx);
    font = ft;
    text.copy(txt);
    type2D = Object2DType::Text;
}

/**
 * @brief Sets the text to display
 * 
 * @param txt String to display
 */
void Text2D::setText(const char* txt) { text.copy(txt); }

/**
 * @brief Gets the text to display
 * 
 * @return String to display
 */
const char* Text2D::getText() const { return text.c_str(); }

/**
 * @brief Sets the font of the text object
 * 
 * @param f Loaded font
 */
void Text2D::setFont(Font* ft) {
    RMG_ASSERT(ft->getContext() == getContext());
    font = ft;
}

/**
 * @brief Gets the font of the text object
 * 
 * @return Current font of the object
 */
Font* Text2D::getFont() const { return font; }

/**
 * @brief Sets the horizontal text alignment
 * 
 * @param a Left, center or right text alignment
 */
void Text2D::setTextAlignment(HorizontalAlign a) { textAlign = a; }

/**
 * @brief Gets the horizontal text alignment
 * 
 * @return Left, center or right text alignment
 */
HorizontalAlign Text2D::getTextAlignment() const { return textAlign; }

}
