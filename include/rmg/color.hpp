/**
 * @file color.hpp
 * @brief RGBA color model and functions
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_COLOR_H__
#define __RMG_COLOR_H__

/**
 * @brief RGBA color model and functions
 */
struct Color {
    float red; /**< Red color component */
    float blue; /**< Blue color component */
    float green; /**< Green color component */
    
    /**
     * @brief Opacity value
     * 
     * In addition to red, blue and green to represent a color, how much the
     * color is opaque or transparent is considered. The less alpha value,
     * the more transparent the color is.
     */
    float alpha;
    
    
    /**
     * @brief Default constructor
     */
    Color();
    
    /**
     * @brief Constructor with RGBA values
     * 
     * @param r Red
     * @param g Green
     * @param b Blue
     * @param a Alpha
     */
    inline Color(float r, float g, float b, float a) {
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }
    
    /**
     * @brief Apply brightness to the color
     * 
     * @param val Brightness value between -1 and 1
     */
    void applyBrightness(float val);
    
    /**
     * @brief Apply contrast to the color
     * 
     * @param val Contrast value between -1 and 1
     */
    void applyContrast(float val);
    
    /**
     * @brief Apply brightness and contrast to the color
     * 
     * @param b Brightness value
     * @param c Contrast value
     */
    void applyBrightnessContrast(float b, float c);
    
    /**
     * @brief Gets the lighter or darker color
     * 
     * @param val Brightness value between -1 and 1
     */
    Color brightness(float val) const;
    
    /**
     * @brief Gets the contrast applied color
     * 
     * @param val Contrast value between -1 and 1
     */
    Color contrast(float val) const;
    
    /**
     * @brief Gets brightness and contrast applied color
     * 
     * @param b Brightness value
     * @param c Contrast value
     */
    Color brightnessContrast(float b, float c) const;
}

#endif
