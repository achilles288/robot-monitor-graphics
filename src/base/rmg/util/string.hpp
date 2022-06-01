/**
 * @file string.hpp
 * @brief String class for RMG library
 * 
 * String class with dynamic character array.
 * 
 * @copyright Copyright (c) 2022 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_STRING_H__
#define __RMG_STRING_H__

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


namespace rmg {

/*
 * @brief String class for RMG library
 * 
 * String class with dynamic character array.
 */
class RMG_API String {
  private:
    char* data;
    uint16_t length;
    uint16_t cap;
    
  public:
    /**
     * @brief Default constructor
     */
    String();
    
    /**
     * @breif Destructor
     */
    ~String();
    
    /**
     * @brief Constructs the string from a C string pointer
     * 
     * @param str Traditional C string pointer
     */
    String(const char* str);
    
    /**
     * @brief Copy constructor
     * 
     * @param str Source string
     */
    String(const String& str);
    
    /**
     * @brief Move constructor
     * 
     * @param str Source string
     */
    String(String&& str) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param str Source string
     */
    String& operator = (const String& str);
    
    /**
     * @brief Move assignment
     * 
     * @param str Source string
     */
    String& operator = (String&& str);
    
    /**
     * @brief Gets the string pointer
     * 
     * @return Traditional C string pointer
     */
    const char* c_str() const;
    
    /**
     * @brief Gets the length of the string
     * 
     * @return Number of characters
     */
    uint16_t size() const;
    
    /**
     * @brief Gets the capacity of the string
     * 
     * @return Allocated memory for the string in bytes
     */
    uint16_t capacity() const;
    
    /**
     * @brief Reallocates the array to reduce unnecessary space
     */
    void resize();
    
    /**
     * @brief Copies the string from a string pointer and stores it
     * 
     * @param str Source string
     */
    void copy(const char* str);
    
    /**
     * @brief Joins the two strings
     * 
     * @param str Source string
     */
    void concatenate(const char* str);
    
    /**
     * @brief Gets the characters by array subscription
     */
    char const& operator [] (uint16_t i) const;
};

}

#endif
