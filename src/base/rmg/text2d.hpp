/**
 * @file text2d.hpp
 * @brief Renders text as an 2D object
 * 
 * In addition to 2D sprites and 3D models, text rendering is also important
 * for score board and some kind of monitoring.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_TEXT_2D_H__
#define __RMG_TEXT_2D_H__

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


#include "font.hpp"
#include "object2d.hpp"


namespace rmg {

/**
 * @brief Renders text as an 2D object
 * 
 * In addition to 2D sprites and 3D models, text rendering is also important
 * for score board and some kind of monitoring.
 */
class RMG_API Text2D: public Object2D {
  private:
    Font* font;
    std::string text;
    
  public:
    /**
     * @brief Default constructor
     * 
     * @param ctx Container context
     */
    Text2D();
    
    /**
     * @brief Constructor with loaded font
     * 
     * @param ctx Container context
     * @param ft Loaded font
     * @param s Font size
     * @param txt String to display
     */
    Text2D(Context* ctx, Font* ft, float s=16, const std::string &txt="Text");
    
    /**
     * @brief Sets the text to display
     * 
     * @param txt String to display
     */
    void setText(const std::string &txt);
    
    /**
     * @brief Gets the text to display
     * 
     * @return String to display
     */
    std::string getText() const;
    
    /**
     * @brief Sets the font of the text object
     * 
     * @param f Loaded font
     */
    void setFont(Font* f);
    
    /**
     * @brief Gets the font of the text object
     * 
     * @return Current font of the object
     */
    Font* getFont() const;
    
    /**
     * @brief Sets the font size of the text object
     * 
     * @param s Font size
     */
    void setFontSize(float s);
    
    /**
     * @brief Gets the font size of the text object
     * 
     * @return Font size
     */
    float getFontSize() const;
    
    /**
     * @brief Sets the horizontal text alignment
     * 
     * @param a Left, center or right text alignment
     */
    void setTextAlignment(HorizontalAlign a);
    
    /**
     * @brief Gets the horizontal text alignment
     * 
     * @return Left, center or right text alignment
     */
    HorizontalAlign getTextAlignment() const;
};

}

#endif
