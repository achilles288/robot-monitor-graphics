#include <rmg/bitmap.hpp>

#include <algorithm>
#include <utility>

#include <gtest/gtest.h>

#include "../testconf.h"

using namespace rmg;


/**
 * @brief Pixel struct constructor test
 */
TEST(Pixel, constructor) {
    Pixel p1 = Pixel();
    ASSERT_EQ(0, p1.channel);
    
    Pixel p2 = Pixel(53);
    ASSERT_EQ(53, p2.gray);
    ASSERT_EQ(1, p2.channel);
    
    Pixel p3 = Pixel(142, 64, 12);
    ASSERT_EQ(142, p3.red);
    ASSERT_EQ(64, p3.green);
    ASSERT_EQ(12, p3.blue);
    ASSERT_EQ(3, p3.channel);
    
    Pixel p4 = Pixel(87, 213, 165, 109);
    ASSERT_EQ(87, p4.red);
    ASSERT_EQ(213, p4.green);
    ASSERT_EQ(165, p4.blue);
    ASSERT_EQ(109, p4.alpha);
    ASSERT_EQ(4, p4.channel);
}




/**
 * @brief Bitmap class constructor test
 */
TEST(Bitmap, constructor) {
    Bitmap bmp1 = Bitmap();
    ASSERT_EQ(0, bmp1.getWidth());
    ASSERT_EQ(0, bmp1.getHeight());
    ASSERT_EQ(0, bmp1.getChannel());
    ASSERT_EQ((uint8_t*)NULL, bmp1.getPointer());
    
    // Copy constructor test
    Bitmap bmp2 = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/open_png_rgb.png"
    );
    Bitmap bmp3;
    bmp3 = bmp2;
    ASSERT_EQ(bmp2.getWidth(), bmp3.getWidth());
    ASSERT_EQ(bmp2.getHeight(), bmp3.getHeight());
    ASSERT_EQ(bmp2.getChannel(), bmp3.getChannel());
    ASSERT_NE((uint8_t*)NULL, bmp3.getPointer());
    ASSERT_NE(bmp2.getPointer(), bmp3.getPointer());
    
    // Move constructor test
    uint16_t w2 = bmp2.getWidth();
    uint16_t h2 = bmp2.getHeight();
    uint8_t c2 = bmp2.getChannel();
    uint8_t* ptr2 = bmp2.getPointer();
    Bitmap bmp4;
    bmp4 = std::move(bmp2);
    ASSERT_EQ(w2, bmp4.getWidth());
    ASSERT_EQ(h2, bmp4.getHeight());
    ASSERT_EQ(c2, bmp4.getChannel());
    ASSERT_EQ(ptr2, bmp4.getPointer());
    ASSERT_EQ(0, bmp2.getChannel());
    ASSERT_EQ((uint8_t*)NULL, bmp2.getPointer());
}




/**
 * @brief Bitmap PNG read test
 * 
 * Opens the file, reads meta data and decodes the pixel data into the array.
 * Checks the meta data (width, height, channel) and checks color values of
 * certain pixels at some locations.
 */
TEST(Bitmap, loadPNG_gray) {
    Bitmap bmp = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/open_png_gray.png"
    );
    ASSERT_NE((uint8_t*)NULL, bmp.getPointer());
    EXPECT_EQ(120, bmp.getWidth());
    EXPECT_EQ(117, bmp.getHeight());
    EXPECT_EQ(1, bmp.getChannel());
    Pixel p1, p2, p3;
    p1 = bmp.getPixel(30, 27);
    p2 = bmp.getPixel(10, 98);
    p3 = bmp.getPixel(86, 75);
    EXPECT_EQ(98, p1.gray);
    EXPECT_EQ(35, p2.gray);
    EXPECT_EQ(157, p3.gray);
}

TEST(Bitmap, loadPNG_ga) {
    Bitmap bmp = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/open_png_ga.png"
    );
    ASSERT_NE((uint8_t*)NULL, bmp.getPointer());
    EXPECT_EQ(32, bmp.getWidth());
    EXPECT_EQ(80, bmp.getHeight());
    EXPECT_EQ(2, bmp.getChannel());
    Pixel p1, p2, p3;
    p1 = bmp.getPixel(9, 13);
    p2 = bmp.getPixel(20, 29);
    p3 = bmp.getPixel(24, 65);
    ASSERT_EQ(235, p1.gray);
    ASSERT_EQ(130, p1.alpha);
    ASSERT_EQ( 96, p2.gray);
    ASSERT_EQ(255, p2.alpha);
    ASSERT_EQ(  0, p3.alpha);
}

TEST(Bitmap, loadPNG_rgb) {
    Bitmap bmp = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/open_png_rgb.png"
    );
    ASSERT_NE((uint8_t*)NULL, bmp.getPointer());
    EXPECT_EQ(144, bmp.getWidth());
    EXPECT_EQ(128, bmp.getHeight());
    EXPECT_EQ(3, bmp.getChannel());
    Pixel p1, p2, p3;
    p1 = bmp.getPixel(71, 43);
    p2 = bmp.getPixel(26, 106);
    p3 = bmp.getPixel(134, 89);
    ASSERT_EQ(203, p1.red);
    ASSERT_EQ(205, p1.green);
    ASSERT_EQ(213, p1.blue);
    ASSERT_EQ(159, p2.red);
    ASSERT_EQ(143, p2.green);
    ASSERT_EQ(122, p2.blue);
    ASSERT_EQ( 80, p3.red);
    ASSERT_EQ(125, p3.green);
    ASSERT_EQ(  7, p3.blue);
}

TEST(Bitmap, loadPNG_rgba) {
    Bitmap bmp = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/open_png_rgba.png"
    );
    ASSERT_NE((uint8_t*)NULL, bmp.getPointer());
    EXPECT_EQ(32, bmp.getWidth());
    EXPECT_EQ(80, bmp.getHeight());
    EXPECT_EQ(4, bmp.getChannel());
    Pixel p1, p2, p3, p4;
    p1 = bmp.getPixel(9, 13);
    p2 = bmp.getPixel(20, 29);
    p3 = bmp.getPixel(30, 28);
    p4 = bmp.getPixel(24, 65);
    ASSERT_EQ(235, p1.red);
    ASSERT_EQ(234, p1.green);
    ASSERT_EQ(237, p1.blue);
    ASSERT_EQ(130, p1.alpha);
    ASSERT_EQ(191, p2.red);
    ASSERT_EQ(  1, p2.green);
    ASSERT_EQ(  2, p2.blue);
    ASSERT_EQ(255, p2.alpha);
    ASSERT_EQ(133, p3.red);
    ASSERT_EQ(108, p3.green);
    ASSERT_EQ(107, p3.blue);
    ASSERT_EQ(241, p3.alpha);
    ASSERT_EQ(  0, p4.alpha);
}




/**
 * @brief Bitmap TIFF read test
 * 
 * Opens the file, reads meta data and decodes the pixel data into the array.
 * Checks the meta data (width, height, channel) and checks color values of
 * certain pixels at some locations.
 */
TEST(Bitmap, loadTIFF_gray) {
    Bitmap bmp = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/open_tif_gray.tif"
    );
    ASSERT_NE((uint8_t*)NULL, bmp.getPointer());
    EXPECT_EQ(100, bmp.getWidth());
    EXPECT_EQ(75, bmp.getHeight());
    EXPECT_EQ(1, bmp.getChannel());
    Pixel p1, p2, p3;
    p1 = bmp.getPixel(42, 27);
    p2 = bmp.getPixel(16, 42);
    p3 = bmp.getPixel(64, 64);
    EXPECT_EQ(187, p1.gray);
    EXPECT_EQ(21, p2.gray);
    EXPECT_EQ(239, p3.gray);
}

TEST(Bitmap, loadTIFF_rgb) {
    Bitmap bmp = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/open_tif_rgb.tif"
    );
    ASSERT_NE((uint8_t*)NULL, bmp.getPointer());
    EXPECT_EQ(120, bmp.getWidth());
    EXPECT_EQ(120, bmp.getHeight());
    EXPECT_EQ(3, bmp.getChannel());
    Pixel p1, p2, p3;
    p1 = bmp.getPixel(52, 13);
    p2 = bmp.getPixel(82, 54);
    p3 = bmp.getPixel(26, 99);
    ASSERT_EQ( 89, p1.red);
    ASSERT_EQ(104, p1.green);
    ASSERT_EQ( 63, p1.blue);
    ASSERT_EQ(217, p2.red);
    ASSERT_EQ(212, p2.green);
    ASSERT_EQ(206, p2.blue);
    ASSERT_EQ(212, p3.red);
    ASSERT_EQ(180, p3.green);
    ASSERT_EQ(132, p3.blue);
}

TEST(Bitmap, loadTIFF_rgba) {
    Bitmap bmp = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/open_tif_rgba.tif"
    );
    ASSERT_NE((uint8_t*)NULL, bmp.getPointer());
    EXPECT_EQ(65, bmp.getWidth());
    EXPECT_EQ(100, bmp.getHeight());
    EXPECT_EQ(4, bmp.getChannel());
    Pixel p1, p2, p3, p4;
    p1 = bmp.getPixel(35, 24);
    p2 = bmp.getPixel(25, 51);
    p3 = bmp.getPixel(32, 79);
    p4 = bmp.getPixel( 7, 95);
    ASSERT_EQ( 53, p1.red);
    ASSERT_EQ( 20, p1.green);
    ASSERT_EQ(  7, p1.blue);
    ASSERT_EQ(100, p1.alpha);
    ASSERT_EQ(206, p2.red);
    ASSERT_EQ(125, p2.green);
    ASSERT_EQ( 38, p2.blue);
    ASSERT_EQ(255, p2.alpha);
    ASSERT_EQ(255, p3.red);
    ASSERT_EQ(255, p3.green);
    ASSERT_EQ(164, p3.blue);
    ASSERT_EQ(255, p3.alpha);
    ASSERT_EQ(  0, p4.alpha);
}




/**
 * @brief Bitmap PNG write test
 * 
 * Opens a file, edits it and saves it in a new file.
 * To test the output file at logic level, reopen the saved file and test
 * some pixels.
 */
TEST(Bitmap, savePNG) {
    remove(RMGTEST_OUTPUT_PATH "/save_png.png");
    
    // Opens the image file
    Bitmap bmp = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/open_png_rgba.png"
    );
    ASSERT_NE((uint8_t*)NULL, bmp.getPointer());
    ASSERT_EQ(32, bmp.getWidth());
    ASSERT_EQ(80, bmp.getHeight());
    ASSERT_EQ(4, bmp.getChannel());
    
    // Opens edit the bitmap
    uint8_t* data = bmp.getPointer();
    size_t rowsize = bmp.getWidth() * bmp.getChannel();
    for(int x=0; x<bmp.getWidth(); x++) {
        for(int y=0; y<bmp.getHeight(); y++) {
            uint8_t* ptr = data + (x + y*bmp.getWidth()) * bmp.getChannel();
            uint8_t tmp = ptr[0];
            ptr[0] = ptr[1];
            ptr[1] = tmp;
            ptr[2] = (uint8_t) (ptr[2] * 0.75f);
            ptr[3] = (uint8_t) (ptr[3] * 0.55f);
        }
    }
    
    // Saves the bitmap
    bmp.saveFile(RMGTEST_OUTPUT_PATH "/save_png.png");
    
    // Reopens the output image and does logic tests
    Bitmap saved = Bitmap::loadFromFile(
        RMGTEST_OUTPUT_PATH "/save_png.png"
    );
    ASSERT_NE((uint8_t*)NULL, saved.getPointer());
    EXPECT_EQ(32, saved.getWidth());
    EXPECT_EQ(80, saved.getHeight());
    EXPECT_EQ(4, saved.getChannel());
    
    Pixel p1, p2, p3, p4;
    p1 = saved.getPixel(11, 10);
    p2 = saved.getPixel(12, 24);
    p3 = saved.getPixel(23, 41);
    p4 = saved.getPixel( 7, 66);
    ASSERT_EQ(225, p1.red);
    ASSERT_EQ(227, p1.green);
    ASSERT_EQ(172, p1.blue);
    ASSERT_EQ( 56, p1.alpha);
    ASSERT_EQ(  0, p2.red);
    ASSERT_EQ(214, p2.green);
    ASSERT_EQ(  5, p2.blue);
    ASSERT_EQ(140, p2.alpha);
    ASSERT_EQ( 65, p3.red);
    ASSERT_EQ( 82, p3.green);
    ASSERT_EQ( 48, p3.blue);
    ASSERT_EQ(140, p3.alpha);
    ASSERT_EQ(  0, p4.alpha);
}




/**
 * @brief Bitmap TIFF write test
 * 
 * Opens a file, edits it and saves it in a new file.
 * To test the output file at logic level, reopen the saved file and test
 * some pixels.
 */
TEST(Bitmap, saveTIFF_gray) {
    remove(RMGTEST_OUTPUT_PATH "/save_tif_gray.tif");
    
    // Opens the image file
    Bitmap bmp = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/open_tif_gray.tif"
    );
    ASSERT_NE((uint8_t*)NULL, bmp.getPointer());
    ASSERT_EQ(100, bmp.getWidth());
    ASSERT_EQ(75, bmp.getHeight());
    ASSERT_EQ(1, bmp.getChannel());
    
    // Opens edit the bitmap
    uint8_t* data = bmp.getPointer();
    for(int x=0; x<bmp.getWidth(); x++) {
        for(int y=0; y<bmp.getHeight(); y++) {
            uint8_t* ptr = data + (x + y*bmp.getWidth()) * bmp.getChannel();
            ptr[0] = std::min(ptr[0]+48, 255);
        }
    }
    
    // Saves the bitmap
    bmp.saveFile(RMGTEST_OUTPUT_PATH "/save_tif_gray.tif");
    
    // Reopens the output image and does logic tests
    Bitmap saved = Bitmap::loadFromFile(
        RMGTEST_OUTPUT_PATH "/save_tif_gray.tif"
    );
    ASSERT_NE((uint8_t*)NULL, saved.getPointer());
    EXPECT_EQ(100, saved.getWidth());
    EXPECT_EQ(75, saved.getHeight());
    EXPECT_EQ(1, saved.getChannel());
    
    Pixel p1, p2, p3;
    p1 = bmp.getPixel(30, 33);
    p2 = bmp.getPixel(60, 42);
    p3 = bmp.getPixel(56, 67);
    EXPECT_EQ(128, p1.gray);
    EXPECT_EQ(161, p2.gray);
    EXPECT_EQ(255, p3.gray);
}

TEST(Bitmap, saveTIFF_rgba) {
    remove(RMGTEST_OUTPUT_PATH "/save_tif_rgba.tif");
    
    // Opens the image file
    Bitmap bmp = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/open_tif_rgba.tif"
    );
    ASSERT_NE((uint8_t*)NULL, bmp.getPointer());
    ASSERT_EQ(65, bmp.getWidth());
    ASSERT_EQ(100, bmp.getHeight());
    ASSERT_EQ(4, bmp.getChannel());
    
    // Opens edit the bitmap
    uint8_t* data = bmp.getPointer();
    for(int x=0; x<bmp.getWidth(); x++) {
        for(int y=0; y<bmp.getHeight(); y++) {
            uint8_t* ptr = data + (x + y*bmp.getWidth()) * bmp.getChannel();
            uint8_t tmp = ptr[0];
            ptr[0] = ptr[1];
            ptr[1] = ptr[2];
            ptr[2] = (uint8_t) (tmp * 0.8f);
            ptr[3] = (uint8_t) (ptr[3] * 0.7f);
        }
    }
    
    // Saves the bitmap
    bmp.saveFile(RMGTEST_OUTPUT_PATH "/save_tif_rgba.tif");
    
    // Reopens the output image and does logic tests
    Bitmap saved = Bitmap::loadFromFile(
        RMGTEST_OUTPUT_PATH "/save_tif_rgba.tif"
    );
    ASSERT_NE((uint8_t*)NULL, saved.getPointer());
    EXPECT_EQ(65, saved.getWidth());
    EXPECT_EQ(100, saved.getHeight());
    EXPECT_EQ(4, saved.getChannel());
    
    Pixel p1, p2, p3, p4;
    p1 = saved.getPixel(24, 53);
    p2 = saved.getPixel(40, 49);
    p3 = saved.getPixel(43, 70);
    p4 = saved.getPixel( 7, 91);
    ASSERT_EQ(123, p1.red);
    ASSERT_EQ( 38, p1.green);
    ASSERT_EQ(160, p1.blue);
    ASSERT_EQ(178, p1.alpha);
    ASSERT_EQ( 69, p2.red);
    ASSERT_EQ( 22, p2.green);
    ASSERT_EQ( 81, p2.blue);
    ASSERT_EQ(121, p2.alpha);
    ASSERT_EQ(244, p3.red);
    ASSERT_EQ( 83, p3.green);
    ASSERT_EQ(204, p3.blue);
    ASSERT_EQ(178, p3.alpha);
    ASSERT_EQ(  0, p4.alpha);
}




/**
 * @brief Equality operator test
 */
TEST(Bitmap, equals) {
    Bitmap bmp1 = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/open_png_rgb.png"
    );
    Bitmap bmp2 = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/open_png_rgb.png"
    );
    if(!(bmp1 == bmp2))
        FAIL() << "`bmp1 == bmp2` returns false false" << std::endl;
    if(bmp1 != bmp2)
        FAIL() << "`bmp1 != bmp2` returns false true" << std::endl;
    
    Pixel px = Pixel(194, 65, 24);
    bmp2.setPixel(105, 29, px);
    if(bmp1 == bmp2)
        FAIL() << "`bmp1 == bmp2` returns false true" << std::endl;
    if(!(bmp1 != bmp2))
        FAIL() << "`bmp1 != bmp2` returns false false" << std::endl;
}




/**
 * @brief Converts to grayscale image
 * 
 * Converts images with different channels to the grayscale images and compares
 * the output with reference images
 */
TEST(Bitmap, toGrayscale_rgb) {
    Bitmap bmp, out, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_rgb.png");
    out = bmp.toGrayscale();
    
    EXPECT_EQ(1, out.getChannel());
    
    ref = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_rgb_gray.png");
    if(out != ref) {
        out.saveFile(RMGTEST_OUTPUT_PATH "/error_toGrayscale_rgb.png");
        
        FAIL() << "`out != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, toGrayscale_rgba) {
    Bitmap bmp, out, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_rgba.png");
    out = bmp.toGrayscale();
    
    EXPECT_EQ(1, out.getChannel());
    
    ref = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_rgba_gray.png");
    if(out != ref) {
        out.saveFile(RMGTEST_OUTPUT_PATH "/error_toGrayscale_rgba.png");
        
        FAIL() << "`out != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, toGrayscale_rgba_associative) {
    /*
     * The first conversion is RGBA to grayscale.
     * The second conversion is RGBA-RGB-Gray.
     */
    Bitmap bmp, out1, out2;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_rgba.png");
    out1 = bmp.toGrayscale();
    out2 = bmp.toRGB();
    out2 = out2.toGrayscale();
    
    if(out1 != out2)
        FAIL() << "`out1 != out2` bitmaps are not identical";
}




/**
 * @brief Converts to gray alpha image
 * 
 * Converts images with different channels to the gray alpha images and
 * compares the output with reference images
 */
TEST(Bitmap, toGA_gray) {
    Bitmap bmp, out, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_gray.png");
    out = bmp.toGA();
    
    EXPECT_EQ(2, out.getChannel());
    
    ref = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_gray_ga.png");
    if(out != ref) {
        out.saveFile(RMGTEST_OUTPUT_PATH "/error_toGA_gray.png");
        
        FAIL() << "`out != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, toGA_rgb) {
    Bitmap bmp, out, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_rgb.png");
    out = bmp.toGA();
    ref = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_rgb_ga.png");
    
    EXPECT_EQ(2, out.getChannel());
    
    if(out != ref) {
        out.saveFile(RMGTEST_OUTPUT_PATH "/error_toGA_rgb.png");
        
        FAIL() << "`out != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, toGA_rgba) {
    Bitmap bmp, out, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_rgba.png");
    out = bmp.toGA();
    
    EXPECT_EQ(2, out.getChannel());
    
    ref = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_rgba_ga.png");
    if(out != ref) {
        out.saveFile(RMGTEST_OUTPUT_PATH "/error_toGA_rgba.png");
        
        FAIL() << "`out != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}




/**
 * @brief Converts to RGB image
 * 
 * Converts images with different channels to the RGB images and compares
 * the output with reference images
 */
TEST(Bitmap, toRGB_gray) {
    Bitmap bmp, out, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_gray.png");
    out = bmp.toRGB();
    
    EXPECT_EQ(3, out.getChannel());
    
    ref = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_gray_rgb.png");
    if(out != ref) {
        out.saveFile(RMGTEST_OUTPUT_PATH "/error_toRGB_gray.png");
        
        FAIL() << "`out != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, toRGB_rgba) {
    Bitmap bmp, out, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_rgba.png");
    out = bmp.toRGB();
    
    EXPECT_EQ(3, out.getChannel());
    
    ref = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_rgba_rgb.png");
    if(out != ref) {
        out.saveFile(RMGTEST_OUTPUT_PATH "/error_toRGB_rgba.png");
        
        FAIL() << "`out != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}




/**
 * @brief Converts to RGBA image
 * 
 * Converts images with different channels to the RGBA images and compares
 * the output with reference images
 */
TEST(Bitmap, toRGBA_gray) {
    Bitmap bmp, out, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_gray.png");
    out = bmp.toRGBA();
    
    EXPECT_EQ(4, out.getChannel());
    
    ref = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_gray_rgba.png");
    if(out != ref) {
        out.saveFile(RMGTEST_OUTPUT_PATH "/error_toRGBA_gray.png");
        
        FAIL() << "`out != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, toRGBA_rgb) {
    Bitmap bmp, out, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_rgb.png");
    out = bmp.toRGBA();
    
    EXPECT_EQ(4, out.getChannel());
    
    ref = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/convert_rgb_rgba.png");
    if(out != ref) {
        out.saveFile(RMGTEST_OUTPUT_PATH "/error_toRGBA_rgb.png");
        
        FAIL() << "`out != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}




/**
 * @brief Pastes a grayscale image from another source to the bitmap
 * 
 * Pastes different images on different images and compares the output images
 * with the reference images
 */
TEST(Bitmap, pasteGray_gray) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_gray.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_gray.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_gray.png");
    bmp.paste(layer1, 5, 20);
    bmp.paste(layer2, 60, 80);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_gray_gray.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteGray_gray.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, pasteGray_ga) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_ga.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_gray.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_gray.png");
    bmp.paste(layer1, 10, 20);
    bmp.paste(layer2, 70, 40);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_gray_ga.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteGray_ga.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, pasteGray_rgb) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_rgb.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_gray.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_gray.png");
    bmp.paste(layer1, 5, 20);
    bmp.paste(layer2, 60, 80);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_gray_rgb.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteGray_rgb.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, pasteGray_rgba) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_rgba.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_gray.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_gray.png");
    bmp.paste(layer1, 10, 20);
    bmp.paste(layer2, 70, 40);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_gray_rgba.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteGray_rgba.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}




/**
 * @brief Pastes a gray alpha image from another source to the bitmap
 * 
 * Pastes different images on different images and compares the output images
 * with the reference images
 */
TEST(Bitmap, pasteGA_gray) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_gray.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_ga.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_ga.png");
    bmp.paste(layer1, 5, 20);
    bmp.paste(layer2, 60, 80);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_ga_gray.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteGA_gray.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, pasteGA_ga) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_ga.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_ga.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_ga.png");
    bmp.paste(layer1, 10, 20);
    bmp.paste(layer2, 70, 40);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_ga_ga.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteGA_ga.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, pasteGA_rgb) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_rgb.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_ga.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_ga.png");
    bmp.paste(layer1, 5, 20);
    bmp.paste(layer2, 60, 80);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_ga_rgb.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteGA_rgb.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, pasteGA_rgba) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_rgba.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_ga.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_ga.png");
    bmp.paste(layer1, 10, 20);
    bmp.paste(layer2, 70, 40);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_ga_rgba.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteGA_rgba.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}




/**
 * @brief Pastes an RGB image from another source to the bitmap
 * 
 * Pastes different images on different images and compares the output images
 * with the reference images
 */
TEST(Bitmap, pasteRGB_gray) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_gray.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_rgb.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_rgb.png");
    bmp.paste(layer1, 5, 20);
    bmp.paste(layer2, 60, 80);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_gray_gray.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteRGB_gray.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, pasteRGB_ga) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_ga.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_rgb.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_rgb.png");
    bmp.paste(layer1, 10, 20);
    bmp.paste(layer2, 70, 40);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_gray_ga.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteRGB_ga.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, pasteRGB_rgb) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_rgb.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_rgb.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_rgb.png");
    bmp.paste(layer1, 5, 20);
    bmp.paste(layer2, 60, 80);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_rgb_rgb.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteRGB_rgb.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, pasteRGB_rgba) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_rgba.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_rgb.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_rgb.png");
    bmp.paste(layer1, 10, 20);
    bmp.paste(layer2, 70, 40);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_rgb_rgba.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteRGB_rgba.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}




/**
 * @brief Pastes an RGBA image from another source to the bitmap
 * 
 * Pastes different images on different images and compares the output images
 * with the reference images
 */
TEST(Bitmap, pasteRGBA_gray) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_gray.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_rgba.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_rgba.png");
    bmp.paste(layer1, 5, 20);
    bmp.paste(layer2, 60, 80);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_ga_gray.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteRGBA_gray.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, pasteRGBA_ga) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_ga.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_rgba.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_rgba.png");
    bmp.paste(layer1, 10, 20);
    bmp.paste(layer2, 70, 40);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_ga_ga.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteRGBA_ga.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, pasteRGBA_rgb) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_rgb.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_rgba.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_rgba.png");
    bmp.paste(layer1, 5, 20);
    bmp.paste(layer2, 60, 80);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_rgba_rgb.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteRGBA_rgb.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}

TEST(Bitmap, pasteRGBA_rgba) {
    Bitmap bmp, layer1, layer2, ref;
    bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_bg_rgba.png");
    layer1 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_a_rgba.png");
    layer2 = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/paste_b_rgba.png");
    bmp.paste(layer1, 10, 20);
    bmp.paste(layer2, 70, 40);
    
    ref = Bitmap::loadFromFile(
        RMGTEST_RESOURCE_PATH "/expect_paste_rgba_rgba.png"
    );
    
    if(bmp != ref) {
        bmp.saveFile(RMGTEST_OUTPUT_PATH "/error_pasteRGBA_rgba.png");
        
        FAIL() << "`bmp != ref` bitmaps are not identical" << std::endl
               << "See the saved output image in the build directory";
    }
}
