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
#include "util/string.hpp"


namespace rmg {

/**
 * @brief Renders text as an 2D object
 * 
 * In addition to 2D sprites and 3D models, text rendering is also important
 * for score board and some kind of monitoring.
 */
class RMG_API Text2D: public Object2D {
  private:
    Font* font = nullptr;
    String text;
    HorizontalAlign textAlign = HorizontalAlign::Center;
    
  public:
    /**
     * @brief Default constructor
     * 
     * @param ctx Container context
     */
    Text2D() = default;
    
    /**
     * @brief Constructor with loaded font
     * 
     * @param ctx Container context
     * @param ft Loaded font
     */
    Text2D(Context* ctx, Font* ft);
    
    /**
     * @brief Constructor with loaded font
     * 
     * @param ctx Container context
     * @param ft Loaded font
     * @param txt String to display
     */
    Text2D(Context* ctx, Font* ft, const char* txt);
    
    /**
     * @brief Sets the text to display
     * 
     * @param txt String to display
     */
    void setText(const char* txt);
    
    /**
     * @brief Gets the text to display
     * 
     * @return String to display
     */
    const char* getText() const;
    
    /**
     * @brief Sets the font of the text object
     * 
     * @param ft Loaded font
     */
    void setFont(Font* ft);
    
    /**
     * @brief Gets the font of the text object
     * 
     * @return Current font of the object
     */
    Font* getFont() const;
    
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
    
    /**
     * @brief Sets the size of the 2D object
     * 
     * @param w Width
     * @param h Height
     */
    void setSize(float w, float h) = delete;
    
    /**
     * @brief Sets the size of the 2D object
     * 
     * @param s Size
     */
    void setSize(const Vec2 &s) = delete;
    
    /**
     * @brief Gets the size of the 2D object
     * 
     * @return Width and height as a rectangular dimension
     */
    Vec2 getSize() const = delete;
};

}

#endif
