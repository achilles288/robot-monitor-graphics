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


#define RMG_EXPORT


#include "rmg/bitmap.hpp"

#include <cstdlib>
#include <cstring>
#include <utility>

#include "rmg/assert.hpp"


namespace rmg {

/**
 * @brief Creates a blank bitmap
 * 
 * @param w The width of the image
 * @param h The height of the image
 * @param ch Number of channels of each pixel
 */
Bitmap::Bitmap(uint16_t w, uint16_t h, uint8_t ch) {
    if(ch < 1 || ch > 4)
        return;
    width = w;
    height = h;
    channel = ch;
    size_t size = w * h * ch;
    data = (uint8_t*) malloc(size);
    memset(data, 255, size);
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
        printf("error: Attempted to load unsupported image file '%s'\n",
               file.c_str());
        #else
        printf("\033[0;1;31merror: \033[0m"
               "Attempted to load unsupported image file "
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
    else if(channel == 2)
        return Pixel(ptr[0], ptr[1]);
    else if(channel == 3)
        return Pixel(ptr[0], ptr[1], ptr[2]);
    else
        return Pixel(ptr[0], ptr[1], ptr[2], ptr[3]);
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
        ptr[0] = p.gray;
    else if(channel == 2) {
        ptr[0] = p.gray;
        ptr[1] = p.alpha;
    }
    else if(channel == 3) {
        ptr[0] = p.red;
        ptr[1] = p.green;
        ptr[2] = p.blue;
    }
    else {
        ptr[0] = p.red;
        ptr[1] = p.green;
        ptr[2] = p.blue;
        ptr[3] = p.alpha;
    }
}


static float getLuminance(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t cmax, cmin;
    if(r > g) {
        // Green is min
        cmin = g;
        if(r > b)
            cmax = r; // Red is max
        else
            cmax = b; // Blue is max
        }
    else if(b > g) {
        // Blue is max and red is min
        cmax = b;
        cmin = r;
    }
    else {
        // Green is max
        cmax = g;
        if(r < b)
            cmin = r; // Red is min
        else
            cmin = b; // Blue is min
    }
    return (cmax+cmin)/2.0f;
}


/**
 * @brief Converts the bitmap to a grayscale image
 * 
 * @return A grayscale bitmap image which has only a single channel
 */
Bitmap Bitmap::toGrayscale() const {
    if(channel == 1)
        return *this;
    
    Bitmap bmp = Bitmap(width, height, 1);
    uint8_t* ptr1 = data;
    uint8_t* ptr2 = bmp.data;
    size_t pixelCount = width * height;
    
    if(channel == 2) {
        for(size_t i=0; i<pixelCount; i++) {
            float a = ptr1[1] / 255.0f;
            *ptr2 = a*ptr1[0] + 255.5f - ptr1[1];
            ptr1 += 2;
            ptr2 += 1;
        }
    }
    else if(channel == 3) {
        for(size_t i=0; i<pixelCount; i++) {
            *ptr2 = getLuminance(ptr1[0], ptr1[1], ptr1[2]);
            ptr1 += 3;
            ptr2 += 1;
        }
    }
    else {
        for(size_t i=0; i<pixelCount; i++) {
            float a = ptr1[3] / 255.0f;
            float r = a*ptr1[0] + 255.5f - ptr1[3];
            float g = a*ptr1[1] + 255.5f - ptr1[3];
            float b = a*ptr1[2] + 255.5f - ptr1[3];
            *ptr2 = getLuminance(r, g, b);
            ptr1 += 4;
            ptr2 += 1;
        }
    }
    return bmp;
}

/**
 * @brief Converts the bitmap to a grayscale image with alpha channel
 * 
 * @return A 2-channel bitmap image
 */
Bitmap Bitmap::toGA() const {
    if(channel == 2)
        return *this;
    
    Bitmap bmp = Bitmap(width, height, 2);
    uint8_t* ptr1 = data;
    uint8_t* ptr2 = bmp.data;
    size_t pixelCount = width * height;
    
    if(channel == 1) {
        for(size_t i=0; i<pixelCount; i++) {
            ptr2[0] = ptr1[0];
            ptr2[1] = 255;
            ptr1 += 1;
            ptr2 += 2;
        }
    }
    else if(channel == 3) {
        for(size_t i=0; i<pixelCount; i++) {
            ptr2[0] = getLuminance(ptr1[0], ptr1[1], ptr1[2]);
            ptr2[1] = 255;
            ptr1 += 3;
            ptr2 += 2;
        }
    }
    else {
        for(size_t i=0; i<pixelCount; i++) {
            ptr2[0] = getLuminance(ptr1[0], ptr1[1], ptr1[2]);
            ptr2[1] = ptr1[3];
            ptr1 += channel;
            ptr2 += 2;
        }
    }
    return bmp;
}

/**
 * @brief Converts the bitmap to an RGB image
 * 
 * @return A 3-channel bitmap image
 */
Bitmap Bitmap::toRGB() const {
    if(channel == 3)
        return *this;
    
    Bitmap bmp = Bitmap(width, height, 3);
    uint8_t* ptr1 = data;
    uint8_t* ptr2 = bmp.data;
    size_t pixelCount = width * height;
    
    if(channel == 1) {
        for(size_t i=0; i<pixelCount; i++) {
            ptr2[0] = ptr1[0];
            ptr2[1] = ptr1[0];
            ptr2[2] = ptr1[0];
            ptr1 += 1;
            ptr2 += 3;
        }
    }
    else if(channel == 2) {
        for(size_t i=0; i<pixelCount; i++) {
            float a = ptr1[1] / 255.0f;
            uint8_t val = a*ptr1[0] + 255.5f - ptr1[1];
            ptr2[0] = val;
            ptr2[1] = val;
            ptr2[2] = val;
            ptr1 += 2;
            ptr2 += 3;
        }
    }
    else {
        for(size_t i=0; i<pixelCount; i++) {
            float a = ptr1[3] / 255.0f;
            ptr2[0] = a*ptr1[0] + 255.5f - ptr1[3];
            ptr2[1] = a*ptr1[1] + 255.5f - ptr1[3];
            ptr2[2] = a*ptr1[2] + 255.5f - ptr1[3];
            ptr1 += 4;
            ptr2 += 3;
        }
    }
    return bmp;
}

/**
 * @brief Converts the bitmap to an RGBA image
 * 
 * @return A 4-channel bitmap image
 */
Bitmap Bitmap::toRGBA() const {
    if(channel == 4)
        return *this;
    
    Bitmap bmp = Bitmap(width, height, 4);
    uint8_t* ptr1 = data;
    uint8_t* ptr2 = bmp.data;
    size_t pixelCount = width * height;
    
    if(channel == 1) {
        for(size_t i=0; i<pixelCount; i++) {
            ptr2[0] = *ptr1;
            ptr2[1] = *ptr1;
            ptr2[2] = *ptr1;
            ptr2[3] = 255;
            ptr1 += 1;
            ptr2 += 4;
        }
    }
    else if(channel == 2) {
        for(size_t i=0; i<pixelCount; i++) {
            ptr2[0] = ptr1[0];
            ptr2[1] = ptr1[0];
            ptr2[2] = ptr1[0];
            ptr2[3] = ptr1[1];
            ptr1 += 2;
            ptr2 += 4;
        }
    }
    else {
        for(size_t i=0; i<pixelCount; i++) {
            ptr2[0] = ptr1[0];
            ptr2[1] = ptr1[1];
            ptr2[2] = ptr1[2];
            ptr2[3] = 255;
            ptr1 += 3;
            ptr2 += 4;
        }
    }
    return bmp;
}

/**
 * @brief Pastes an image on the bitmap at some location
 * 
 * @param bmp The bitmap to be copied
 * @param x X-coordinate in the image frame
 * @param y Y-coordinate in the image frame
 */
void Bitmap::paste(const Bitmap& bmp, uint16_t x, uint16_t y) {
    RMG_ASSERT(x > 0 && x < width);
    RMG_ASSERT(y > 0 && y < height);
    
    const uint8_t lut[] = {
        0x10, 0x20, 0x11, 0x22,
        0x10, 0x20, 0x11, 0x22,
        0x33, 0x44, 0x30, 0x40,
        0x33, 0x44, 0x30, 0x40
    };
    uint8_t i = (channel-1)*4 + bmp.channel - 1;
    uint8_t conv = lut[i] & 0x0f;
    uint8_t func = lut[i] & 0xf0;
    
    if(conv == 0x00) {
        if(func == 0x10)
            pasteGray(bmp, x, y);
        else if(func == 0x20)
            pasteGA(bmp, x, y);
        else if(func == 0x30)
            pasteRGB(bmp, x, y);
        else // 0x40
            pasteRGBA(bmp, x, y);
    }
    else {
        Bitmap img;
        if(conv == 0x01)
            img = bmp.toGrayscale();
        else if(conv == 0x02)
            img = bmp.toGA();
        else if(conv == 0x03)
            img = bmp.toRGB();
        else if(conv == 0x04)
            img = bmp.toRGBA();
        
        if(func == 0x10)
            pasteGray(img, x, y);
        else if(func == 0x20)
            pasteGA(img, x, y);
        else if(func == 0x30)
            pasteRGB(img, x, y);
        else // 0x40
            pasteRGBA(img, x, y);
    }
}


void Bitmap::pasteGray(const Bitmap& bmp, uint16_t x, uint16_t y) {
    if(bmp.channel != 1 || channel >= 3)
        return;
    
    uint16_t w = bmp.width;
    uint16_t h = bmp.height;
    if(x + w > width)
        w = width - x;
    if(y + h > height)
        h = height - y;
    
    uint8_t* ptr1 = bmp.data;
    uint8_t* ptr2 = data + (x + y*width)*channel;
    size_t rowJump = (width - w) * channel;
    
    if(channel == 1) {
        for(uint16_t i=0; i<h; i++) {
            for(uint16_t j=0; j<w; j++) {
                *ptr2 = *ptr1;
                ptr1++;
                ptr2++;
            }
            ptr2 += rowJump;
        }
    }
    else {
        for(uint16_t i=0; i<h; i++) {
            for(uint16_t j=0; j<w; j++) {
                ptr2[0] = *ptr1;
                ptr2[1] = 255;
                ptr1 += 1;
                ptr2 += 2;
            }
            ptr2 += rowJump;
        }
    }
}


void Bitmap::pasteGA(const Bitmap& bmp, uint16_t x, uint16_t y) {
    if(bmp.channel != 2 || channel >= 3)
        return;
    
    uint16_t w = bmp.width;
    uint16_t h = bmp.height;
    if(x + w > width)
        w = width - x;
    if(y + h > height)
        h = height - y;
    
    uint8_t* ptr1 = bmp.data;
    uint8_t* ptr2 = data + (x + y*width)*channel;
    size_t rowJump = (width - w) * channel;
    
    if(channel == 1) {
        for(uint16_t i=0; i<h; i++) {
            for(uint16_t j=0; j<w; j++) {
                float a = ptr1[1] / 255.0f;
                ptr2[0] = a*ptr1[0] + (1-a)*ptr2[0] + 0.5f;
                ptr1 += 2;
                ptr2 += 1;
            }
            ptr2 += rowJump;
        }
    }
    else {
        for(uint16_t i=0; i<h; i++) {
            for(uint16_t j=0; j<w; j++) {
                float a1 = ptr1[1] / 255.0f;
                float a2 = ptr2[1] / 255.0f;
                float b = a2*(1-a1);
                float a = a1 + b;
                ptr2[0] = (a1*ptr1[0] + b*ptr2[0]) / a + 0.5f;
                ptr2[1] = a * 255 + 0.5f;
                ptr1 += 2;
                ptr2 += 2;
            }
            ptr2 += rowJump;
        }
    }
}


void Bitmap::pasteRGB(const Bitmap& bmp, uint16_t x, uint16_t y) {
    if(bmp.channel != 3 || channel < 3)
        return;
    
    uint16_t w = bmp.width;
    uint16_t h = bmp.height;
    if(x + w > width)
        w = width - x;
    if(y + h > height)
        h = height - y;
    
    uint8_t* ptr1 = bmp.data;
    uint8_t* ptr2 = data + (x + y*width)*channel;
    size_t rowJump = (width - w) * channel;
    
    if(channel == 3) {
        for(uint16_t i=0; i<h; i++) {
            for(uint16_t j=0; j<w; j++) {
                ptr2[0] = ptr1[0];
                ptr2[1] = ptr1[1];
                ptr2[2] = ptr1[2];
                ptr1 += 3;
                ptr2 += 3;
            }
            ptr2 += rowJump;
        }
    }
    else {
        for(uint16_t i=0; i<h; i++) {
            for(uint16_t j=0; j<w; j++) {
                ptr2[0] = ptr1[0];
                ptr2[1] = ptr1[1];
                ptr2[2] = ptr1[2];
                ptr2[3] = 255;
                ptr1 += 3;
                ptr2 += 4;
            }
            ptr2 += rowJump;
        }
    }
}


void Bitmap::pasteRGBA(const Bitmap& bmp, uint16_t x, uint16_t y) {
    if(bmp.channel != 4 || channel < 3)
        return;
    
    uint16_t w = bmp.width;
    uint16_t h = bmp.height;
    if(x + w > width)
        w = width - x;
    if(y + h > height)
        h = height - y;
    
    uint8_t* ptr1 = bmp.data;
    uint8_t* ptr2 = data + (x + y*width)*channel;
    size_t rowJump = (width - w) * channel;
    
    if(channel == 3) {
        for(uint16_t i=0; i<h; i++) {
            for(uint16_t j=0; j<w; j++) {
                float a = ptr1[3] / 255.0f;
                float b = 1 - a;
                ptr2[0] = a*ptr1[0] + b*ptr2[0] + 0.5f;
                ptr2[1] = a*ptr1[1] + b*ptr2[1] + 0.5f;
                ptr2[2] = a*ptr1[2] + b*ptr2[2] + 0.5f;
                ptr1 += 4;
                ptr2 += 3;
            }
            ptr2 += rowJump;
        }
    }
    else {
        for(uint16_t i=0; i<h; i++) {
            for(uint16_t j=0; j<w; j++) {
                float a1 = ptr1[3] / 255.0f;
                float a2 = ptr2[3] / 255.0f;
                float b = a2*(1-a1);
                float a = a1 + b;
                ptr2[0] = (a1*ptr1[0] + b*ptr2[0]) / a + 0.5f;
                ptr2[1] = (a1*ptr1[1] + b*ptr2[1]) / a + 0.5f;
                ptr2[2] = (a1*ptr1[2] + b*ptr2[2]) / a + 0.5f;
                ptr2[3] = a * 255 + 0.5f;
                ptr1 += 4;
                ptr2 += 4;
            }
            ptr2 += rowJump;
        }
    }
}


/**
 * @brief Compares the two bitmaps
 */
bool Bitmap::operator == (const Bitmap &bmp) const {
    if(bmp.width != width || bmp.width != width || bmp.channel != channel)
        return false;
    
    uint8_t* ptr1 = data;
    uint8_t* ptr2 = bmp.data;
    size_t size = width * height * channel;
    
    for(size_t i=0; i<size; i++) {
        if(*ptr1 != *ptr2)
            return false;
        ptr1++;
        ptr2++;
    }
    return true;
}

/**
 * @brief Compares the two bitmaps
 */
bool Bitmap::operator != (const Bitmap &bmp) const {
    if(bmp.width != width || bmp.width != width || bmp.channel != channel)
        return true;
    
    uint8_t* ptr1 = data;
    uint8_t* ptr2 = bmp.data;
    size_t size = width * height * channel;
    
    for(size_t i=0; i<size; i++) {
        if(*ptr1 != *ptr2)
            return true;
        ptr1++;
        ptr2++;
    }
    return false;
}

}
