/**
 * @file bitmap_tiff.cpp
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

#include <cstdio>
#include <cstdlib>
#ifdef _WIN32
#include <Windows.h>
#include <Winbase.h>
#else
#include <unistd.h>
#endif

#include <tiffio.h>

#include "rmg/config.h"


namespace rmg {

/**
 * @brief Loads a bitmap from a TIFF file
 * 
 * @param file Path to image file
 * 
 * @return Decoded image data
 */
Bitmap Bitmap::loadTIFF(const std::string& file) {
    Bitmap bmp;
    TIFF *tif = TIFFOpen(file.c_str(), "r");
    
    if(!tif) {
        #ifdef _WIN32
        printf("error: File '%s' could not be opened\n", file.c_str());
        #else
        printf("\033[0;1;31merror: \033[0m"
               "File \033[1m'%s'\033[0m "
               "could not be opened\n", file.c_str());
        #endif
        return bmp;
    }
    
    uint32_t width, height;
    uint16_t channel;
    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);
    TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &channel);
    bmp.width = width;
    bmp.height = height;
    bmp.channel = (uint8_t) channel;
    size_t bmp_size = width * height * channel;
    bmp.data = (uint8_t*) malloc(bmp_size);
    for(tstrip_t s = 0; s < TIFFNumberOfStrips(tif); s++)
        TIFFReadEncodedStrip(tif, s, bmp.data, (tsize_t) -1);
    TIFFClose(tif);
    return bmp;
}

/**
 * @brief Encodes the bitmap and saves it in a TIFF
 * 
 * @param file Path for image file
 */
void Bitmap::saveTIFF(const std::string& file) const {
    // Creates the file
    TIFF *tif = TIFFOpen(file.c_str(), "w");
    if(!tif) {
        #ifdef _WIN32
        printf("error: Image could not be saved at '%s'\n", file.c_str());
        #else
        printf("\033[0;1;31merror: \033[0m"
               "Image could not be saved at \033[1m'%s'\033[0m\n",
               file.c_str());
        #endif
        return;
    }
    
    // Sets the tags
    TIFFSetField(tif, TIFFTAG_SOFTWARE, "RMGraphics " RMG_VERSION_STRING);
    char hostname[64+1];
    #ifdef _WIN32
    DWORD len = 64+1;
    GetComputerName(hostname, &len);
    #else
    gethostname(hostname, 64+1);
    #endif
    TIFFSetField(tif, TIFFTAG_HOSTCOMPUTER, hostname);
    TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    
    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, width);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, height);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_LZW);
    
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, channel);
    if(channel == 1)
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
    else {
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
        if(channel == 4) {
            uint16_t extras[] = {EXTRASAMPLE_ASSOCALPHA};
            TIFFSetField(tif, TIFFTAG_EXTRASAMPLES, 1, extras);
        }
    }
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tif, TIFFTAG_RESOLUTIONUNIT, RESUNIT_NONE);
    
    uint32_t rowsize = width * channel;
    TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(tif,rowsize));
    
    // Writes the bytes
    for(int y=0; y<height; y++)
        TIFFWriteScanline(tif, &data[y*rowsize], y, 0);
    
    TIFFClose(tif);
}

}
