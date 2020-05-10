/**
 * @file keyboard.hpp
 * @brief Keyboard event and attributes
 * 
 * Stores a keycode and keyboard states.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_KEYBOARD_H__
#define __RMG_KEYBOARD_H__ ///< Header guard

#include "internal/window_callback.hpp"

#include <cstdint>


namespace rmg {

#define RMG_KEY_STATE_CTRL  0b001 ///< Keyboard Ctrl mask
#define RMG_KEY_STATE_ALT   0b010 ///< Keyboard Alt mask
#define RMG_KEY_STATE_SHIFT 0b100 ///< Keyboard Shift mask


/**
 * @brief Keyboard event and attributes
 * 
 * Stores a keycode and keyboard states.
 */
class KeyboardEvent {
  private:
    char keycode;  ///< The keycode ('a', 'b', .etc)
    uint8_t keyStates;  ///< Ctrl, Alt and Shift
    
    
    friend void window_mouse_button_callback
                    (GLFWwindow* window, int button, int action, int mods);

    friend void window_cursor_position_callback
                    (GLFWwindow* window, double xpos, double ypos);

    friend void window_cursor_enter_callback
                    (GLFWwindow* window, int entered);
    
    friend void window_scroll_callback
                    (GLFWwindow* window, double xoffset, double yoffset);
    
    friend void window_key_callback(GLFWwindow* window, int key,
                                    int scancode, int action, int mods);
    
    
  public:
    /**
     * @brief Default constructor
     */
    KeyboardEvent();
    
    /**
     * @brief Gets the keycode
     * 
     * @return The keycode ('a', 'b', .etc)
     */
    char getKeycode() const;
    
    /**
     * @brief If the ctrl key is pressed
     * 
     * @return True if the ctrl is pressed
     */
    bool isCtrl() const;
    
    /**
     * @brief If the alt key is pressed
     * 
     * @return True if the alt is pressed
     */
    bool isAlt() const;
    
    /**
     * @brief If the shift key is pressed
     * 
     * @return True if the shift is pressed
     */
    bool isShift() const;
};

}

#endif
