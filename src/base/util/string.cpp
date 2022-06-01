/**
 * @file string.cpp
 * @brief String class for RMG library
 * 
 * String class with dynamic character array.
 * 
 * @copyright Copyright (c) 2022 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "../rmg/util/string.hpp"

#include <cstdlib>
#include <cstring>
#include <utility>


#define CL 2


namespace rmg {

/**
 * @brief Default constructor
 */
String::String() {
    length = 0;
    cap = CL;
    data = (char*) malloc(cap + 1);
    data[0] = '\0';
}

/**
 * @breif Destructor
 */
String::~String() {
    if(data != NULL)
        free(data);
}

/**
 * @brief Constructs the string from a C string pointer
 * 
 * @param str Traditional C string pointer
 */
String::String(const char* str) {
    length = strlen(str);
    cap = length + CL;
    data = (char*) malloc(cap + 1);
    memcpy(data, str, length);
    data[length] = '\0';
}

/**
 * @brief Copy constructor
 * 
 * @param str Source string
 */
String::String(const String& str) {
    length = str.length;
    cap = str.cap;
    data = (char*) malloc(cap + 1);
    memcpy(data, str.data, length);
    data[length] = '\0';
}

/**
 * @brief Move constructor
 * 
 * @param str Source string
 */
String::String(String&& str) noexcept {
    data = std::exchange(str.data, nullptr);
    length = std::exchange(str.length, 0);
    cap = std::exchange(str.cap, 0);
}

/**
 * @brief Copy assignment
 * 
 * @param str Source string
 */
String& String::operator = (const String& str) {
    String tmp = String(str);
    std::swap(data, tmp.data);
    std::swap(length, tmp.length);
    std::swap(cap, tmp.cap);
    return *this;
}

/**
 * @brief Move assignment
 * 
 * @param str Source string
 */
String& String::operator = (String&& str) {
    String tmp = String(str);
    std::swap(data, tmp.data);
    std::swap(length, tmp.length);
    std::swap(cap, tmp.cap);
    return *this;
}

/**
 * @brief Gets the string pointer
 * 
 * @return Traditional C string pointer
 */
const char* String::c_str() const { return data; }

/**
 * @brief Gets the length of the string
 * 
 * @return Number of characters
 */
uint16_t String::size() const { return length; }

/**
 * @brief Gets the cap of the string
 * 
 * @return Allocated memory for the string in bytes
 */
uint16_t String::capacity() const { return cap; }

/**
 * @brief Reallocates the array for more cap
 */
void String::resize() {
   cap = length + CL;
   char* tmp = (char*) malloc(cap + 1);
   if(data != NULL) {
       memcpy(tmp, data, length);
       free(data);
   }
   data = tmp;
   data[length] = '\0';
}

/**
 * @brief Copies the string from a string pointer and stores it
 * 
 * @param str Source string
 */
void String::copy(const char* str) {
    if(data == NULL)
        resize();
    length = strlen(str);
    if(length > cap) {
        cap = length + CL;
        char* tmp = (char*) malloc(cap + 1);
        free(data);
        data = tmp;
    }
    memcpy(data, str, length);
    data[length] = '\0';
}

/**
 * @brief Joins the two strings
 * 
 * @param str Source string
 */
void String::concatenate(const char* str) {
    if(data == NULL)
        resize();
    uint16_t n = strlen(str);
    if(length + n > cap) {
        cap = length + n + CL;
        char* tmp = (char*) malloc(cap + 1);
        memcpy(tmp, data, length);
        free(data);
    }
    memcpy(&data[length], str, n);
    length += n;
    data[length] = '\0';
}

/**
 * @brief Gets the characters by array subscription
 */
char const& String::operator [] (uint16_t i) const {
    if(i >= length)
        return data[length];
    return data[i];
}

}
