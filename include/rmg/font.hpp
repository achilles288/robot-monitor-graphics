/**
 * @file font.hpp
 * @brief For rendering texts on the context
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_FONT_H__
#define __RMG_FONT_H__

#include <cstdint>
#include <string>


class rmg::Context;
class rmg::internal::FontLoadPending;


namespace rmg {

/**
 * @brief For rendering texts on the context
 */
class Font {
  private:
    uint32_t id;
    uint32_t loadID;
    Context* context;
    
    friend class internal::FontLoadPending;
    
    static uint64_t lastID;
    static uint64_t generateID();
    
  public:
    /**
     * @brief Constructor loads a font from file
     * 
     * @param ctx Conatiner context
     * @param f Path to font file (.ttf)
     */
    Font(Context* ctx, const std::string &f);
    
    /**
     * @brief Destructor
     */
    virtual ~Font();
    
    /**
     * @brief Copy constructor (deleted)
     * 
     * Copy constructor is not allowed to use since it contains a unique
     * pointer.
     * 
     * @param ft Source font
     */
    Font(const Font& ft) = delete;
    
    /**
     * @brief Move constructor
     * 
     * @param ft Source font
     */
    Font(Font&& ft) noexcept;
    
    /**
     * @brief Copy assignment (deleted)
     * 
     * Copy assignment is not allowed to use since it contains a unique
     * pointer.
     * 
     * @param ft Source font
     */
    Font& operator=(const Font& ft) = delete;
    
    /**
     * @brief Move assignment
     * 
     * @param ft Source font
     */
    Font& operator=(Font&& ft) noexcept;
    
    /**
     * @brief Gets font ID
     * 
     * @return Font ID
     */
    uint32_t getID();
    
    /**
     * @brief Gets the container context
     * 
     * @return Container context
     */
    Context* getContext();
};

}

#endif
