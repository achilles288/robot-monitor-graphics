/**
 * @file color.hpp
 * @brief RGBA and HSLA color models and functions
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "rmg/color.hpp"

#include <algorithm>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdint>


namespace rmg {

/**
 * @brief Default constructor
 */
ColorRGBA::ColorRGBA() {
    red = 1;
    green = 1;
    blue = 1;
    alpha = 1;
}

/**
 * @brief Constructor with RGB values
 * 
 * RGB values are between 0 and 1.
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 */
ColorRGBA::ColorRGBA(float r, float g, float b) {
    red = r;
    green = g;
    blue = b;
    alpha = 1;
}

/**
 * @brief Constructor with RGBA values
 * 
 * RGBA values are between 0 and 1.
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 * @param a Alpha
 */
ColorRGBA::ColorRGBA(float r, float g, float b, float a) {
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

/**
 * @brief Converts RGBA to HSLA
 */
ColorRGBA::operator ColorHSLA() {
    ColorHSLA hsla;
    uint8_t cmax_case;
    float cmax, cmin;
    if(red > green) {
        // Green is min
        cmin = green;
        if(red > blue) {
            // Red is max
            cmax = red;
            cmax_case = 1;
        }
        else {
            // Blue is max
            cmax = blue;
            cmax_case = 3;
        }
    }
    else if(blue > green) {
        // Blue is max and red is min
        cmax = blue;
        cmin = red;
        cmax_case = 3;
    }
    else {
        // Green is max
        cmax = green;
        cmax_case = 2;
        if(red < blue) {
            // Red is min
            cmin = red;
        }
        else {
            // Blue is min
            cmin = blue;
        }
    }
    float diff = cmax - cmin;
    
    // Calculate hue
    if(diff < 0.0001f)
        hsla.hue = 0;
    else if(cmax_case == 1) // If red is max
        hsla.hue = 60.0f * fmod((green-blue)/diff, 6.0f);
    else if(cmax_case == 2) // If green is max
        hsla.hue = 60.0f * ((blue-red)/diff + 2);
    else // If blue is max
        hsla.hue = 60.0f * ((blue-red)/diff + 4);
    
    // Calculate luminance
    hsla.luminance = (cmax+cmin)/2.0f;
    
    // Calculate saturation
    if(diff < 0.0001f)
        hsla.saturation = 0;
    else
        hsla.saturation = diff / (1 - fabs(2*hsla.luminance - 1));
    
    hsla.alpha = alpha;
    return hsla;
}

/**
 * @brief Apply brightness to the color
 * 
 * @param val Brightness value between -1 and 1
 */
void ColorRGBA::applyBrightness(float val) {
    red = std::clamp(red+val, 0.0f, 1.0f);
    green = std::clamp(green+val, 0.0f, 1.0f);
    blue = std::clamp(blue+val, 0.0f, 1.0f);
}

/**
 * @brief Gets the lighter or darker color
 * 
 * @param val Brightness value between -1 and 1
 */
ColorRGBA ColorRGBA::brightness(float val) const {
    ColorRGBA col;
    col.red = std::clamp(red+val, 0.0f, 1.0f);
    col.green = std::clamp(green+val, 0.0f, 1.0f);
    col.blue = std::clamp(blue+val, 0.0f, 1.0f);
    col.alpha = alpha;
    return col;
}

    
/**
 * @brief Default constructor
 */
ColorHSLA::ColorHSLA() {
    hue = 0;
    saturation = 0;
    luminance = 1;
    alpha = 1;
}

/**
 * @brief Constructor with HSL values
 * 
 * Hue is degree unit and between 0 and 360.
 * The rest of the attributes are between 0 and 1.
 * 
 * @param h Hue
 * @param s Saturation
 * @param l Luminance
 */
ColorHSLA::ColorHSLA(float h, float s, float l) {
    hue = h;
    saturation = s;
    luminance = l;
    alpha = 1;
}

/**
 * @brief Constructor with HSLA values
 * 
 * Hue is degree unit and between 0 and 360.
 * The rest of the attributes are between 0 and 1.
 * 
 * @param h Hue
 * @param s Saturation
 * @param l Luminance
 * @param a Alpha
 */
ColorHSLA::ColorHSLA(float h, float s, float l, float a) {
    hue = h;
    saturation = s;
    luminance = l;
    alpha = a;
}

/**
 * @brief Converts HSLA to RGBA
 */
ColorHSLA::operator ColorRGBA() {
    ColorRGBA rgba;
    
    float c = (1 - fabs(2*luminance - 1)) * saturation;
    float x = c * (1 - fabs(fmod(hue/60.0f, 2.0f) - 1));
    float m = luminance - c/2.0f;
    
    if(hue >= 0 && hue < 60) {
        rgba.red = c;
        rgba.green = x;
        rgba.blue = 0;
    }
    else if(hue >= 60 && hue < 120) {
        rgba.red = x;
        rgba.green = c;
        rgba.blue = 0;
    }
    else if(hue >= 120 && hue < 180) {
        rgba.red = 0;
        rgba.green = c;
        rgba.blue = x;
    }
    else if(hue >= 180 && hue < 240) {
        rgba.red = 0;
        rgba.green = x;
        rgba.blue = c;
    }
    else if(hue >= 240 && hue < 300) {
        rgba.red = x;
        rgba.green = 0;
        rgba.blue = c;
    }
    else { // 300 <= hue <= 360
        rgba.red = c;
        rgba.green = 0;
        rgba.blue = x;
    }
    rgba.alpha = alpha;
    return rgba;
}

}
