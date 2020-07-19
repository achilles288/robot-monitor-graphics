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

class wxCanvas;

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
    int16_t keycode;  ///< The keycode ('a', 'b', .etc)
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
    
    friend class wxCanvas;
    
    
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
    int16_t getKeycode() const;
    
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

#define RMG_KEY_UNKNOWN        -1
#define RMG_KEY_NONE            0
#define RMG_KEY_BACKSPACE       8
#define RMG_KEY_TAB             9
#define RMG_KEY_ENTER          13
#define RMG_KEY_SHIFT          16
#define RMG_KEY_CTRL           17
#define RMG_KEY_ALT            18
#define RMG_KEY_CAPS_LOCK      20
#define RMG_KEY_ESCAPE         27
#define RMG_KEY_SPACE          32
#define RMG_KEY_PAGE_UP        33
#define RMG_KEY_PAGE_DOWN      34
#define RMG_KEY_END            35
#define RMG_KEY_HOME           36
#define RMG_KEY_ARROW_LEFT     37
#define RMG_KEY_ARROW_UP       38
#define RMG_KEY_ARROW_RIGHT    39
#define RMG_KEY_ARROW_DOWN     40
#define RMG_KEY_INSERT         45
#define RMG_KEY_DELETE         46
#define RMG_KEY_0              48
#define RMG_KEY_1              49
#define RMG_KEY_2              50
#define RMG_KEY_3              51
#define RMG_KEY_4              52
#define RMG_KEY_5              53
#define RMG_KEY_6              54
#define RMG_KEY_7              55
#define RMG_KEY_8              56
#define RMG_KEY_9              57
#define RMG_KEY_COLON          58
#define RMG_KEY_A              65
#define RMG_KEY_B              66
#define RMG_KEY_C              67
#define RMG_KEY_D              68
#define RMG_KEY_E              69
#define RMG_KEY_F              70
#define RMG_KEY_G              71
#define RMG_KEY_H              72
#define RMG_KEY_I              73
#define RMG_KEY_J              74
#define RMG_KEY_K              75
#define RMG_KEY_L              76
#define RMG_KEY_M              77
#define RMG_KEY_N              78
#define RMG_KEY_O              79
#define RMG_KEY_P              80
#define RMG_KEY_Q              81
#define RMG_KEY_R              82
#define RMG_KEY_S              83
#define RMG_KEY_T              84
#define RMG_KEY_U              85
#define RMG_KEY_V              86
#define RMG_KEY_W              87
#define RMG_KEY_X              88
#define RMG_KEY_Y              89
#define RMG_KEY_Z              90
#define RMG_KEY_NUM_0          96
#define RMG_KEY_NUM_1          97
#define RMG_KEY_NUM_2          98
#define RMG_KEY_NUM_3          99
#define RMG_KEY_NUM_4         100
#define RMG_KEY_NUM_5         101
#define RMG_KEY_NUM_6         102
#define RMG_KEY_NUM_7         103
#define RMG_KEY_NUM_8         104
#define RMG_KEY_NUM_9         105
#define RMG_KEY_NUM_MULTIPLY  106
#define RMG_KEY_NUM_ADD       107
#define RMG_KEY_NUM_SUBTRACT  109
#define RMG_KEY_NUM_DECIMAL   110
#define RMG_KEY_NUM_DIVIDE    111
#define RMG_KEY_F1            112
#define RMG_KEY_F2            113
#define RMG_KEY_F3            114
#define RMG_KEY_F4            115
#define RMG_KEY_F5            116
#define RMG_KEY_F6            117
#define RMG_KEY_F7            118
#define RMG_KEY_F8            119
#define RMG_KEY_F9            120
#define RMG_KEY_F10           121
#define RMG_KEY_F11           122
#define RMG_KEY_F12           123
#define RMG_KEY_NUM_LOCK      144
#define RMG_KEY_EQUAL         187
#define RMG_KEY_COMMA         188
#define RMG_KEY_DASH          189
#define RMG_KEY_DOT           190
#define RMG_KEY_SLASH         191
#define RMG_KEY_BACKQUOTE     192
#define RMG_KEY_OPEN_BRACKET  219
#define RMG_KEY_BACKSLASH     220
#define RMG_KEY_CLOSE_BRACKET 221
#define RMG_KEY_QUOTE         222

#endif
