/**
 * @file bitmap.cpp
 * @brief 2D image loading and manipulation
 * 
 * Opens PNG, TIFF files and uses them for material bmptures or sprite images.
 * Color images or grayscale images.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "rmg/bitmap.hpp"

#include <cstdlib>
#include <cstring>
#include <utility>

#include "rmg/assert.hpp"


namespace rmg {

/**
 * @brief Default constructor
 */
Bitmap::Bitmap() {
    width = 0;
    height = 0;
    channel = 0;
    data = NULL;
}

/**
 * @brief Destructor
 */
Bitmap::~Bitmap() {
    free(data);
}

/**
 * @brief Copy constructor
 * 
 * @param bmp Source
 */
Bitmap::Bitmap(const Bitmap& bmp) {
    width = bmp.width;
    height = bmp.height;
    channel = bmp.channel;
    if(bmp.data != NULL) {
        data = (uint8_t*) malloc(width * height * channel);
        memcpy(data, bmp.data, width * height * channel);
    }
    else
        data = NULL;
}

/**
 * @brief Move constructor
 * 
 * @param bmp Source
 */
Bitmap::Bitmap(Bitmap&& bmp) noexcept {
    width = std::exchange(bmp.width, 0);
    height = std::exchange(bmp.height, 0);
    channel = std::exchange(bmp.channel, 0);
    data = std::exchange(bmp.data, nullptr);
}

/**
 * @brief Copy assignment
 * 
 * @param bmp Source
 */
Bitmap& Bitmap::operator=(const Bitmap& bmp) {
    Bitmap tmp = Bitmap(bmp);
    swap(tmp);
    return *this;
}

/**
 * @brief Move assignment
 * 
 * @param bmp Source
 */
Bitmap& Bitmap::operator=(Bitmap&& bmp) noexcept {
    Bitmap tmp = std::move(bmp);
    swap(tmp);
    return *this;
}

void Bitmap::swap(Bitmap &bmp) noexcept {
    std::swap(width, bmp.width);
    std::swap(height, bmp.height);
    std::swap(channel, bmp.channel);
    std::swap(data, bmp.data);
}

/**
 * @brief Loads a bitmap from a file decoding the image data
 * 
 * Supports PNG and TIFF files.
 * 
 * @param file Path to image file
 * 
 * @return Decoded image data
 */
Bitmap Bitmap::loadFromFile(const std::string& file) {
    auto i = file.find_last_of(".");
    std::string ext = "";
    if(i != std::string::npos)
        ext = file.substr(i+1);
    
    if(ext == "png")
        return loadPNG(file);
    else if(ext == "tif" || ext == "tiff")
        return loadTIFF(file);
    else {
        #ifdef WIN32
        printf("error: Attempted to load unsupported file format '%s'\n",
               file.c_str());
        #else
        printf("\033[0;1;31merror: \033[0m"
               "Attempted to load unsupported file format "
               "\033[1m'%s'\033[0m\n", file.c_str());
        #endif
        return Bitmap();
    }
}

/**
 * @brief Encodes the bitmap and saves it in a file
 * 
 * Supports PNG and TIFF files.
 * 
 * @param file Path for image file
 */
void Bitmap::saveFile(const std::string& file) const {
    auto i = file.find_last_of(".");
    std::string ext = "";
    if(i != std::string::npos)
        ext = file.substr(i+1);
    
    if(ext == "png")
        savePNG(file);
    else if(ext == "tif" || ext == "tiff")
        saveTIFF(file);
    else {
        #ifdef WIN32
        printf("error: Attempted to save bitmap in unsupported file format "
               "'%s'\n", file.c_str());
        #else
        printf("\033[0;1;31merror: \033[0m"
               "Attempted to save bitmap in unsupported file format "
               "\033[1m'%s'\033[0m\n", file.c_str());
        #endif
    }
}

/**
 * @brief Gets the width of the image
 * 
 * @return Image width
 */
uint16_t Bitmap::getWidth() const { return width; }

/**
 * @brief Gets the height of the image
 * 
 * @return Image height
 */
uint16_t Bitmap::getHeight() const { return height; }

/**
 * @brief Gets the number of color channels used in the bitmap
 * 
 * @return Number of channels
 */
uint8_t Bitmap::getChannel() const { return channel; }

/**
 * @brief Gets the pointer to the image data array
 * 
 * @return Array pointer
 */
uint8_t* Bitmap::getPointer() { return data; }

/**
 * @brief Gets the pixel at some coordinate in the image
 * 
 * @param x X-coordinate in the image frame
 * @param y Y-coordinate in the image frame
 * 
 * @return Pixel value
 */
Pixel Bitmap::getPixel(uint16_t x, uint16_t y) const {
    RMG_ASSERT(x > 0 && x < width);
    RMG_ASSERT(y > 0 && y < height);
    
    uint8_t* ptr = data + (x + y*width)*channel;
    if(channel == 1)
        return Pixel(ptr[0]);
    else if(channel == 3)
        return Pixel(ptr[0], ptr[1], ptr[2]);
    else if(channel == 4)
        return Pixel(ptr[0], ptr[1], ptr[2], ptr[3]);
    else {
        RMG_ASSERT(channel == 1 || channel == 3 || channel == 4);
        return Pixel();
    }
}

/**
 * @brief Sets the pixel at some coordinate in the image
 * 
 * @param x X-coordinate in the image frame
 * @param y Y-coordinate in the image frame
 * @param p Pixel value
 */
void Bitmap::setPixel(uint16_t x, uint16_t y, const Pixel& p) {
    RMG_ASSERT(x > 0 && x < width);
    RMG_ASSERT(y > 0 && y < height);
    
    uint8_t* ptr = data + (x + y*width)*channel;
    if(channel == 1)
        ptr[0] = p.value & UINT8_MAX;
    else if(channel == 3) {
        ptr[0] = p.red;
        ptr[1] = p.green;
        ptr[2] = p.blue;
    }
    else if(channel == 4) {
        ptr[0] = p.red;
        ptr[1] = p.green;
        ptr[2] = p.blue;
        ptr[3] = p.alpha;
    }
    else
        RMG_ASSERT(channel == 1 || channel == 3 || channel == 4);
}

}
