/**
 * @file bitmap_png.cpp
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

#include <cstdio>
#include <cstdlib>

#define PNG_DEBUG 3
#include <png.h>

#include "rmg/assert.hpp"


namespace rmg {

/**
 * @brief Loads a bitmap from a PNG file
 * 
 * @param file Path to image file
 * 
 * @return Decoded image data
 */
Bitmap Bitmap::loadPNG(const char* file) {
    Bitmap bmp;
    FILE *fp = fopen(file, "rb");
    char header[8];
    
    #ifdef _WIN32
    // Opens the file
    if(!fp) {
        printf("error: File '%s' could not be opened\n", file);
        return Bitmap();
    }
    // Reads the PNG file signiture
    fread(header, 1, 8, fp);
    if(png_sig_cmp((png_const_bytep)header, 0, 8)) {
        printf("error: File '%s' is not recognized as a PNG file\n", file);
        fclose(fp);
        return Bitmap();
    }
    #else
    // Opens the file
    if(!fp) {
        printf("\033[0;1;31merror: \033[0m"
               "File \033[1m'%s'\033[0m "
               "could not be opened\n", file);
        return Bitmap();
    }
    // Reads the PNG file signiture
    fread(header, 1, 8, fp);
    if(png_sig_cmp((png_const_bytep)header, 0, 8)) {
        printf("\033[0;1;31merror: \033[0m"
               "File \033[1m'%s'\033[0m "
               "is not recognized as a PNG file\n", file);
        fclose(fp);
        return Bitmap();
    }
    #endif
    
    // Creates PNG decoder and info reader
    png_structp png_ptr = png_create_read_struct
                              (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    
    // Reads meta data
    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    
    // If the image isn't of 8 bits per channel, scale down to 8-bit datas
    png_set_scale_16(png_ptr);
    png_set_strip_16(png_ptr);
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    
    // For indexed colors
    if(color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png_ptr);
        int num_palette;
        png_colorp palette;
        if(png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette)) {
            png_uint_16p histogram = NULL;
            png_get_hIST(png_ptr, info_ptr, &histogram);
            png_set_quantize(png_ptr, palette, num_palette,
                             PNG_MAX_PALETTE_LENGTH, histogram, 0);
        }
        else {
            #ifdef _WIN32
            printf("error: Failed reading palette '%s'\n", file);
            #else
            printf("\033[0;1;31merror: \033[0m"
                   "Failed reading palette \033[1m'%s'\033[0m\n",
                   file);
            #endif
            fclose(fp);
            return Bitmap();
        }
    }
    
    bmp.width = png_get_image_width(png_ptr, info_ptr);
    bmp.height = png_get_image_height(png_ptr, info_ptr);
    
    int number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);
    
    // Extracting array of data
    size_t rowsize = png_get_rowbytes(png_ptr,info_ptr);
    bmp.channel = (uint8_t) (rowsize / bmp.width);
    
    bmp.data = (uint8_t*) malloc(bmp.height * rowsize);
    png_bytep* row_ptrs = (png_bytep*) malloc(sizeof(png_bytep) * bmp.height);
    for(int y=0; y<bmp.height; y++) {
        row_ptrs[y] = (png_bytep)(bmp.data + y*rowsize);
    }
    png_read_image(png_ptr, row_ptrs);
    
    free(row_ptrs);
    fclose(fp);
    
    return bmp;
}

/**
 * @brief Encodes the bitmap and saves it in a PNG
 * 
 * @param file Path for image file
 */
void Bitmap::savePNG(const char* file) const {
    RMG_ASSERT(data != NULL);
    png_byte color_type;
    if(channel == 1)
        color_type = PNG_COLOR_TYPE_GRAY;
    else if(channel == 2)
        color_type = PNG_COLOR_TYPE_GRAY_ALPHA;
    else if(channel == 3)
        color_type = PNG_COLOR_TYPE_RGB;
    else
        color_type = PNG_COLOR_TYPE_RGBA;
    
    // Creates the file
    FILE *fp = fopen(file, "wb");
    if(!fp) {
        #ifdef _WIN32
        printf("error: Image could not be saved at '%s'\n", file);
        #else
        printf("\033[0;1;31merror: \033[0m"
               "Image could not be saved at \033[1m'%s'\033[0m\n",
               file);
        #endif
        return;
    }
    
    // Initializes stuff
    png_structp png_ptr = png_create_write_struct
                              (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, fp);
    
    // Sets image properties
    png_set_IHDR(
        png_ptr,
        info_ptr,
        width,
        height,
        8,
        color_type,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_BASE,
        PNG_FILTER_TYPE_BASE
    );
    png_write_info(png_ptr, info_ptr);
    
    png_bytep* row_ptrs = (png_bytep*) malloc(sizeof(png_bytep) * height);
    size_t rowsize = width * channel;
    for(int y=0; y<height; y++) {
        row_ptrs[y] = (png_bytep)(data + y*rowsize);
    }
    
    // Write bytes
    png_write_image(png_ptr, row_ptrs);
    
    png_write_end(png_ptr, NULL);
    free(row_ptrs);
    fclose(fp);
}

}
