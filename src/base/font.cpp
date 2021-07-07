/**
 * @file font.cpp
 * @brief For rendering texts on the context
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "rmg/font.hpp"


namespace rmg {

uint32_t Font::lastID = 0;

/**
 * @brief Constructor loads a font from file
 * 
 * @param ctx Conatiner context
 * @param f Path to font file (.ttf)
 */
Font::Font(Context* ctx, const std::string &f) {
    id = ++lastID;
    context = ctx;
    
    
}

/**
 * @brief Destructor
 */
Font::~Font() {}

/**
 * @brief Gets font ID
 * 
 * @return Font ID
 */
uint32_t Font::getID() const { return id; }

/**
 * @brief Gets the container context
 * 
 * @return Container context
 */
Context* Font::getContext() const { return context; }

}
