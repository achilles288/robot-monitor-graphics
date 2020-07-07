#include <rmg/math/euler.hpp>
#include <rmg/math/mat3.hpp>
#include <rmg/math/mat4.hpp>
#include <rmg/math/vec.hpp>

#include <iostream>

#include <gtest/gtest.h>

using namespace rmg;


/**
 * @brief Vector output stream test
 */
TEST(Ostream, rect) {
    Rect rect = Rect(13, 432);
    testing::internal::CaptureStdout();
    std::cout << rect;
    std::string str = testing::internal::GetCapturedStdout();
    std::string expected = "(13, 432)";
    if(str != expected) {
        FAIL() << "Expected print: " << expected << std::endl
               << "Actual print: " << str << std::endl;
    }
}


TEST(Ostream, vec2) {
    Vec2 v = Vec2(-2.353f, 4.02339f);
    testing::internal::CaptureStdout();
    std::cout << v;
    std::string str = testing::internal::GetCapturedStdout();
    std::string expected = "(-2.3530, 4.0234)";
    if(str != expected) {
        FAIL() << "Expected print: " << expected << std::endl
               << "Actual print: " << str << std::endl;
    }
}


TEST(Ostream, vec3) {
    Vec3 v = Vec3(14.3011f, -7.02339f, 3100013.39f);
    testing::internal::CaptureStdout();
    std::cout << v;
    std::string str = testing::internal::GetCapturedStdout();
    std::string expected = "(14.3011, -7.0234, 3.100e+06)";
    if(str != expected) {
        FAIL() << "Expected print: " << expected << std::endl
               << "Actual print: " << str << std::endl;
    }
}


TEST(Ostream, vec4) {
    Vec4 v = Vec4(-54.3011f, 4.02339f, 2100013.39f, 1);
    testing::internal::CaptureStdout();
    std::cout << v;
    std::string str = testing::internal::GetCapturedStdout();
    std::string expected = "(-54.3011, 4.0234, 2.100e+06, 1.0000)";
    if(str != expected) {
        FAIL() << "Expected print: " << expected << std::endl
               << "Actual print: " << str << std::endl;
    }
}




/**
 * @brief Euler angles output stream test
 */
TEST(Ostream, euler) {
    Euler euler = Euler(120.05f, -45.6f, 163.129f);
    testing::internal::CaptureStdout();
    std::cout << euler;
    std::string str = testing::internal::GetCapturedStdout();
    std::string expected = "(120.0500, -45.6000, 163.1290)";
    if(str != expected) {
        FAIL() << "Expected print: " << expected << std::endl
               << "Actual print: " << str << std::endl;
    }
}




/**
 * @brief Matrix output stream test
 */
TEST(Ostream, mat) {
    Mat3 M = {
      { 101.94f ,  1.29432f, 201532},
      {  -2.172f, -3.12557f,    NAN},
      {   0     ,  0       ,      1}
    };
    testing::internal::CaptureStdout();
    std::cout << M;
    std::string str = testing::internal::GetCapturedStdout();
    
    std::string expected = 
        "\xe2\x94\x8c\xe2\x94\x80"
        "                            "
        "\xe2\x94\x80\xe2\x94\x90\n"
        "\xe2\x94\x82 101.9400,  1.2943, 2.015e+05 \xe2\x94\x82\n"
        "\xe2\x94\x82  -2.1720, -3.1256,       nan \xe2\x94\x82\n"
        "\xe2\x94\x82   0.0000,  0.0000,    1.0000 \xe2\x94\x82\n"
        "\xe2\x94\x94\xe2\x94\x80"
        "                            "
        "\xe2\x94\x80\xe2\x94\x98\n";
    
    if(str != expected) {
        FAIL() << "Expected print:\n" << expected
               << "Actual print:\n" << str << std::endl;
    }
    else
        std::cout << "Test print:\n" << M;
}
