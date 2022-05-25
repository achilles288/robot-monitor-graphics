#include "testconf.h"

#include <rmg/bitmap.hpp>

#include <iostream>


using namespace rmg;

#define FNAME "convert_gray"


int main() {
    Bitmap bmp = Bitmap::loadFromFile(RMGTEST_RESOURCE_PATH "/" FNAME ".png");
    bmp.saveFile(RMGTEST_OUTPUT_PATH "/" FNAME ".png");
    Bitmap gray = bmp.toGrayscale();
    gray.saveFile(RMGTEST_OUTPUT_PATH "/" FNAME "_gray.png");
    Bitmap ga = bmp.toGA();
    ga.saveFile(RMGTEST_OUTPUT_PATH "/" FNAME "_ga.png");
    Bitmap rgb = bmp.toRGB();
    rgb.saveFile(RMGTEST_OUTPUT_PATH "/" FNAME "_rgb.png");
    Bitmap rgba = bmp.toRGBA();
    rgba.saveFile(RMGTEST_OUTPUT_PATH "/" FNAME "_rgba.png");
}
