/**
 * @file bitmap.hpp
 * @brief 2D image loading and manipulation
 * 
 * Opens PNG, TIFF files and uses them for material bmptures or sprite images.
 * Color images or grayscale images.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_BITMAP_H__
#define __RMG_BITMAP_H__

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


#include <cstdint>
#include <string>


namespace rmg {

/**
 * @brief Smallest piece of a digital image
 * 
 * Represents a color value in 8-bit data. 8 bits for grayscale pixel and
 * 32 bits for RGBA color channels.
 */
struct Pixel {
    /**
     * @brief To access either as RGBA or grayscale pixel
     */
    union {
        /**
         * @brief RGBA values
         */
        struct {
            uint8_t red; ///< Red component
            uint8_t green; ///< Green component
            uint8_t blue; ///< Blue component
            uint8_t alpha; ///< Alpha component
        };
        uint32_t value; ///< Grayscale value or combination of RGBA channels
    };
    uint8_t channel; ///< Number of color channels
    
    /**
     * @brief Default constructor
     */
    inline Pixel() {
        value = 0;
        channel = 0;
    }
    
    /**
     * @brief Grayscale pixel constructor
     * 
     * @param val Grayscale value
     */
    inline Pixel(uint8_t val) {
        value = val;
        channel = 1;
    }
    
    /**
     * @brief RGB pixel constructor
     * 
     * @param r Red component
     * @param g Green component
     * @param b Blue component
     */
    inline Pixel(uint8_t r, uint8_t g, uint8_t b) {
        red = r;
        green = g;
        blue = b;
        channel = 3;
    }
    
    /**
     * @brief RGBA pixel constructor
     * 
     * @param r Red component
     * @param g Green component
     * @param b Blue component
     * @param a Alpha component
     */
    inline Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        red = r;
        green = g;
        blue = b;
        alpha = a;
        channel = 4;
    }
};


/**
 * @brief 2D image loading and manipulation
 * 
 * Opens PNG, TIFF files and uses them for material bmptures or sprite images.
 * Color images or grayscale images.
 */
class RMG_API Bitmap {
  private:
    uint16_t width;
    uint16_t height;
    uint8_t channel;
    uint8_t* data;
    
    static Bitmap loadPNG(const std::string& file);
    static Bitmap loadTIFF(const std::string& file);
    void savePNG(const std::string& file) const;
    void saveTIFF(const std::string& file) const;
    
    void swap(Bitmap &bmp) noexcept;
    
  public:
    /**
     * @brief Default constructor
     */
    Bitmap();
    
    /**
     * @brief Destructor
     */
    ~Bitmap();
    
    /**
     * @brief Copy constructor
     * 
     * @param bmp Source
     */
    Bitmap(const Bitmap& bmp);
    
    /**
     * @brief Move constructor
     * 
     * @param bmp Source
     */
    Bitmap(Bitmap&& bmp) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param bmp Source
     */
    Bitmap& operator=(const Bitmap& bmp);
    
    /**
     * @brief Move assignment
     * 
     * @param bmp Source
     */
    Bitmap& operator=(Bitmap&& bmp) noexcept;
    
    /**
     * @brief Loads a bitmap from a file decoding the image data
     * 
     * Supports PNG and TIFF files.
     * 
     * @param file Path to image file
     * 
     * @return Decoded image data
     */
    static Bitmap loadFromFile(const std::string& file);
    
    /**
     * @brief Encodes the bitmap and saves it in a file
     * 
     * Supports PNG and TIFF files.
     * 
     * @param file Path for image file
     */
    void saveFile(const std::string& file) const;
    
    /**
     * @brief Gets the width of the image
     * 
     * @return Image width
     */
    uint16_t getWidth() const;
    
    /**
     * @brief Gets the height of the image
     * 
     * @return Image height
     */
    uint16_t getHeight() const;
    
    /**
     * @brief Gets the number of color channels used in the bitmap
     * 
     * @return Number of channels
     */
    uint8_t getChannel() const;
    
    /**
     * @brief Gets the pointer to the image data array
     * 
     * @return Array pointer
     */
    uint8_t* getPointer();
    
    /**
     * @brief Gets the pixel at some coordinate in the image
     * 
     * @param x X-coordinate in the image frame
     * @param y Y-coordinate in the image frame
     * 
     * @return Pixel value
     */
    Pixel getPixel(uint16_t x, uint16_t y) const;
    
    /**
     * @brief Sets the pixel at some coordinate in the image
     * 
     * @param x X-coordinate in the image frame
     * @param y Y-coordinate in the image frame
     * @param p Pixel value
     */
    void setPixel(uint16_t x, uint16_t y, const Pixel& p);
};

}

#endif
