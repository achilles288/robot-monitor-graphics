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

#include <rmg/object2d.hpp>
#include <rmg/font.hpp>
#include <rmg/text_alignment.hpp>


namespace rmg {

/**
 * @brief Renders text as an 2D object
 * 
 * In addition to 2D sprites and 3D models, text rendering is also important
 * for score board and some kind of monitoring.
 */
class Text2D: public Object2D {
  private:
    Font* font;
    float fontSize;
    std::string text;
    
  public:
    /**
     * @brief Constructor with its container
     * 
     * This constructor doesn't request any other parameters font, font size
     * and this constructor constructs one instance with a preloaded default
     * font and default font size.
     * 
     * @param ctx Container context
     */
    Text2D(Context* ctx);
    
    /**
     * @brief Constructor with path to font file
     * 
     * @param ctx Container context
     * @param f Path to font file
     */
    Text2D(Context* ctx, const std::string &f);
    
    /**
     * @brief Constructor with loaded font
     * 
     * @param ctx Container context
     * @param ft Loaded font
     */
    Text2D(Context* ctx, Font* ft);
    
    /**
     * @brief Constructor with path to font file and font size
     * 
     * @param ctx Container context
     * @param f Path to font file
     * @param s Font size
     */
    Text2D(Context* ctx, const std::string &f, float s);
    
    /**
     * @brief Constructor with loaded font and font size
     * 
     * @param ctx Container context
     * @param ft Loaded font
     * @param s Font size
     */
    Text2D(Context* ctx, Font* ft, float s);
    
    /**
     * @brief Destructor
     */
    virtual ~Text2D();
    
    /**
     * @brief Copy constructor
     * 
     * @param obj Source object
     */
    Text2D(const Text2D& obj);
    
    /**
     * @brief Move constructor
     * 
     * @param obj Source object
     */
    Text2D(Text2D&& obj) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param obj Source object
     */
    Text2D& operator=(const Text2D& obj);
    
    /**
     * @brief Move assignment
     * 
     * @param obj Source object
     */
    Text2D& operator=(Text2D&& obj) noexcept;
    
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
    std::string getText();
    
    /**
     * @brief Sets the font of the text object
     * 
     * @param f Path to font file
     */
    void setFont(const std::string &f);
    
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
    Font* getFont();
    
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
    float getFontSize();
    
    /**
     * @brief Sets the rotation of the text object
     * 
     * Scaling factor of the model matrix changes from size of 2D object to
     * font size.
     * 
     * @param t Rotation in degrees
     */
    void setRotation(float t) override;
};

}

#endif
