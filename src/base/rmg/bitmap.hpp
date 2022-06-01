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


#include <cstddef>
#include <cstdint>


namespace rmg {

/**
 * @brief Smallest piece of a digital image
 * 
 * Represents a color value in 8-bit data. 8 bits for grayscale pixel and
 * 32 bits for RGBA color channels.
 */
struct Pixel {
    uint8_t red = 0; ///< Red component
    uint8_t green = 0; ///< Green component
    uint8_t blue = 0; ///< Blue component
    uint8_t gray = 0; ///< Grayscale value
    uint8_t alpha = 0; ///< Alpha component
    uint8_t channel = 0; ///< Number of color channels
    
    /**
     * @brief Default constructor
     */
    Pixel() = default;
    
    /**
     * @brief Grayscale pixel constructor
     * 
     * @param val Grayscale value
     */
    inline Pixel(uint8_t val) {
        gray = val;
        channel = 1;
    }
    
    /**
     * @brief Grayscale alpha pixel constructor
     * 
     * @param g Grayscale value
     * @param a Alpha value
     */
    inline Pixel(uint8_t g, uint8_t a) {
        gray = g;
        alpha = a;
        channel = 2;
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
    uint16_t width = 0;
    uint16_t height = 0;
    uint8_t channel = 0;
    uint8_t* data = NULL;
    
    static Bitmap loadPNG(const char* file);
    static Bitmap loadTIFF(const char* file);
    void savePNG(const char* file) const;
    void saveTIFF(const char* file) const;
    
    void pasteGray(const Bitmap &bmp, int16_t x, int16_t y);
    void pasteGA(const Bitmap &bmp, int16_t x, int16_t y);
    void pasteRGB(const Bitmap &bmp, int16_t x, int16_t y);
    void pasteRGBA(const Bitmap &bmp, int16_t x, int16_t y);
    
    void swap(Bitmap &bmp) noexcept;
    
  public:
    /**
     * @brief Default constructor
     */
    Bitmap() = default;
    
    /**
     * @brief Creates a blank bitmap
     * 
     * @param w The width of the image
     * @param h The height of the image
     * @param ch Number of channels of each pixel
     */
    Bitmap(uint16_t w, uint16_t h, uint8_t ch);
    
    /**
     * @brief Creates a bitmap from dimensions and a data pointer
     * 
     * @param w The width of the image
     * @param h The height of the image
     * @param ch Number of channels of each pixel
     * @param ptr The data pointer
     */
    Bitmap(uint16_t w, uint16_t h, uint8_t ch, uint8_t* ptr);
    
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
    static Bitmap loadFromFile(const char* file);
    
    /**
     * @brief Encodes the bitmap and saves it in a file
     * 
     * Supports PNG and TIFF files.
     * 
     * @param file Path for image file
     */
    void saveFile(const char* file) const;
    
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
    
    /**
     * @brief Converts the bitmap to a grayscale image
     * 
     * @return A grayscale bitmap image which has only a single channel
     */
    Bitmap toGrayscale() const;
    
    /**
     * @brief Converts the bitmap to a grayscale image with alpha channel
     * 
     * @return A 2-channel bitmap image
     */
    Bitmap toGA() const;
    
    /**
     * @brief Converts the bitmap to an RGB image
     * 
     * @return A 3-channel bitmap image
     */
    Bitmap toRGB() const;
    
    /**
     * @brief Converts the bitmap to an RGBA image
     * 
     * @return A 4-channel bitmap image
     */
    Bitmap toRGBA() const;
    
    /**
     * @brief Pastes an image on the bitmap at some location
     * 
     * @param bmp The bitmap to be copied
     * @param x X-coordinate in the image frame
     * @param y Y-coordinate in the image frame
     */
    void paste(const Bitmap& bmp, int16_t x, int16_t y);
    
    /**
     * @brief Crops the bitmap image into a new frame
     * 
     * @param x X-coordinate to crop the image
     * @param y Y-coordinate to crop the image
     * @param w Width of the new image
     * @param h Height of the new image
     */
    void crop(int16_t x, int16_t y, uint16_t w, uint16_t h);
    
    /**
     * @brief Compares the two bitmaps
     */
    bool operator == (const Bitmap &bmp) const;
    
    /**
     * @brief Compares the two bitmaps
     */
    bool operator != (const Bitmap &bmp) const;
};

}

#endif
