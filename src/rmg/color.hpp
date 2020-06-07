/**
 * @file color.hpp
 * @brief RGBA and HSLA color models and functions
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_COLOR_H__
#define __RMG_COLOR_H__


namespace rmg {

struct ColorRGBA;
struct ColorHSLA;

/**
 * @brief Uses RGBA as standard color model for the API
 */
using Color = rmg::ColorRGBA;


/**
 * @brief RGBA color model
 * 
 * RGBA stands for red green blue alpha. While it is sometimes described as
 * a color space, it is actually the three-channel RGB color model
 * supplemented with a fourth alpha channel. Alpha indicates how opaque each
 * pixel is and allows an image to be combined over others using alpha
 * compositing, with transparent areas and anti-aliasing of the edges of opaque regions.
 * 
 * @image html rgb.svg
 * 
 * @see ColorHSLA
 */
struct ColorRGBA {
    float red; ///< Red color component
    float blue; ///< Blue color component
    float green; ///< Green color component
    
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
    ColorRGBA();
    
    /**
     * @brief Constructor with RGB values
     * 
     * @param r Red
     * @param g Green
     * @param b Blue
     */
    ColorRGBA(float r, float g, float b);
    
    /**
     * @brief Constructor with RGBA values
     * 
     * @param r Red
     * @param g Green
     * @param b Blue
     * @param a Alpha
     */
    ColorRGBA(float r, float g, float b, float a);
    
    /**
     * @brief Converts RGBA to HSLA
     */
    explicit operator ColorHSLA();
    
    /**
     * @brief Apply brightness to the color
     * 
     * @param val Brightness value between -1 and 1
     */
    void applyBrightness(float val);
    
    /**
     * @brief Gets the lighter or darker color
     * 
     * @param val Brightness value between -1 and 1
     */
    ColorRGBA brightness(float val) const;
};

/**
 * @brief HSLA color model
 * 
 * In HSL, the hue determines what color of the rainbow something is.
 * It’s represented in 360 degrees, like a traditional color wheel.
 * One of the main advantages of HSL over RGB color is that complementary
 * colors are located across from one another, which makes the whole system
 * very intuitive.
 * 
 * @image html hsl_cylinder.png
 * 
 * @see ColorRGBA
 */
struct ColorHSLA {
    float hue; ///< Value in 360 degree of color spectrum
    float saturation; ///< Saturation of the color spectrum
    float luminance; ///< Amount of lightness
    
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
    ColorHSLA();
    
    /**
     * @brief Constructor with HSL values
     * 
     * @param h Hue
     * @param s Saturation
     * @param l Luminance
     */
    ColorHSLA(float h, float s, float l);
    
    /**
     * @brief Constructor with HSLA values
     * 
     * @param h Hue
     * @param s Saturation
     * @param l Luminance
     * @param a Alpha
     */
    ColorHSLA(float h, float s, float l, float a);
    
    /**
     * @brief Converts HSLA to RGBA
     */
    operator ColorRGBA();
};

}

#endif