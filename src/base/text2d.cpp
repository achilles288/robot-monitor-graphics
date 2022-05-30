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


namespace rmg {

/**
 * @brief Constructor with loaded font
 * 
 * @param ctx Container context
 * @param ft Loaded font
 * @param s Font size
 * @param txt String to display
 */
Text2D::Text2D(Context* ctx, Font* ft, const char *txt)
       :Object2D(ctx)
{
    RMG_ASSERT(ft->getContext() == ctx);
    font = ft;
    text = std::string(txt);
    type2D = Object2DType::Text;
}

/**
 * @brief Sets the text to display
 * 
 * @param txt String to display
 */
void Text2D::setText(const char* txt) { text = std::string(txt); }

/**
 * @brief Gets the text to display
 * 
 * @return String to display
 */
std::string Text2D::getText() const { return text; }

/**
 * @brief Sets the font of the text object
 * 
 * @param f Loaded font
 */
void Text2D::setFont(Font* f) {
    //RMG_ASSERT(ft->getContext() == getContext());
    font = f;
}

/**
 * @brief Gets the font of the text object
 * 
 * @return Current font of the object
 */
Font* Text2D::getFont() const { return font; }

}
