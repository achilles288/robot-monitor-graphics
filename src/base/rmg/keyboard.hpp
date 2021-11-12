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

#ifndef RMG_API
#ifdef _WIN32
#ifdef RMG_EXPORT
#define RMG_API __declspec(dllexport) ///< RMG API
#else
#define RMG_API __declspec(dllimport) ///< RMG API
#endif
#else
#define RMG_API ///< RMG API
#endif
#endif


#include <rmg/internal/window_callback.hpp>

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
class RMG_API KeyboardEvent {
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

#define RMG_KEY_UNKNOWN        -1 ///< Unknown key
#define RMG_KEY_NONE            0 ///< Null key
#define RMG_KEY_BACKSPACE       8 ///< Backspace key
#define RMG_KEY_TAB             9 ///< Tab key
#define RMG_KEY_ENTER          13 ///< Enter key
#define RMG_KEY_SHIFT          16 ///< Shift key
#define RMG_KEY_CTRL           17 ///< Control key
#define RMG_KEY_ALT            18 ///< Alt key
#define RMG_KEY_CAPS_LOCK      20 ///< Caps-lock key
#define RMG_KEY_ESCAPE         27 ///< Escape key
#define RMG_KEY_SPACE          32 ///< Space key
#define RMG_KEY_PAGE_UP        33 ///< Page-up key
#define RMG_KEY_PAGE_DOWN      34 ///< Page-down key
#define RMG_KEY_END            35 ///< End key
#define RMG_KEY_HOME           36 ///< Home key
#define RMG_KEY_ARROW_LEFT     37 ///< Left arrow key
#define RMG_KEY_ARROW_UP       38 ///< Up arrow key
#define RMG_KEY_ARROW_RIGHT    39 ///< Right arrow key
#define RMG_KEY_ARROW_DOWN     40 ///< Down arrow key
#define RMG_KEY_INSERT         45 ///< Insert key
#define RMG_KEY_DELETE         46 ///< Delete key
#define RMG_KEY_0              48 ///< Key 0
#define RMG_KEY_1              49 ///< Key 1
#define RMG_KEY_2              50 ///< Key 2
#define RMG_KEY_3              51 ///< Key 3
#define RMG_KEY_4              52 ///< Key 4
#define RMG_KEY_5              53 ///< Key 5
#define RMG_KEY_6              54 ///< Key 6
#define RMG_KEY_7              55 ///< Key 7
#define RMG_KEY_8              56 ///< Key 8
#define RMG_KEY_9              57 ///< Key 9
#define RMG_KEY_COLON          58 ///< Colon key
#define RMG_KEY_A              65 ///< Key A
#define RMG_KEY_B              66 ///< Key B
#define RMG_KEY_C              67 ///< Key C
#define RMG_KEY_D              68 ///< Key D
#define RMG_KEY_E              69 ///< Key E
#define RMG_KEY_F              70 ///< Key F
#define RMG_KEY_G              71 ///< Key G
#define RMG_KEY_H              72 ///< Key H
#define RMG_KEY_I              73 ///< Key I
#define RMG_KEY_J              74 ///< Key J
#define RMG_KEY_K              75 ///< Key K
#define RMG_KEY_L              76 ///< Key L
#define RMG_KEY_M              77 ///< Key M
#define RMG_KEY_N              78 ///< Key N
#define RMG_KEY_O              79 ///< Key O
#define RMG_KEY_P              80 ///< Key P
#define RMG_KEY_Q              81 ///< Key Q
#define RMG_KEY_R              82 ///< Key R
#define RMG_KEY_S              83 ///< Key S
#define RMG_KEY_T              84 ///< Key T
#define RMG_KEY_U              85 ///< Key U
#define RMG_KEY_V              86 ///< Key V
#define RMG_KEY_W              87 ///< Key W
#define RMG_KEY_X              88 ///< Key X
#define RMG_KEY_Y              89 ///< Key Y
#define RMG_KEY_Z              90 ///< Key Z
#define RMG_KEY_NUM_0          96 ///< Numpad key 0
#define RMG_KEY_NUM_1          97 ///< Numpad key 1
#define RMG_KEY_NUM_2          98 ///< Numpad key 2
#define RMG_KEY_NUM_3          99 ///< Numpad key 3
#define RMG_KEY_NUM_4         100 ///< Numpad key 4
#define RMG_KEY_NUM_5         101 ///< Numpad key 5
#define RMG_KEY_NUM_6         102 ///< Numpad key 6
#define RMG_KEY_NUM_7         103 ///< Numpad key 7
#define RMG_KEY_NUM_8         104 ///< Numpad key 8
#define RMG_KEY_NUM_9         105 ///< Numpad key 9
#define RMG_KEY_NUM_MULTIPLY  106 ///< Numpad multiply key
#define RMG_KEY_NUM_ADD       107 ///< Numpad add key
#define RMG_KEY_NUM_SUBTRACT  109 ///< Numpad subtract key
#define RMG_KEY_NUM_DECIMAL   110 ///< Numpad decimal key
#define RMG_KEY_NUM_DIVIDE    111 ///< Numpad divide key
#define RMG_KEY_F1            112 ///< F1 key
#define RMG_KEY_F2            113 ///< F2 key
#define RMG_KEY_F3            114 ///< F3 key
#define RMG_KEY_F4            115 ///< F4 key
#define RMG_KEY_F5            116 ///< F5 key
#define RMG_KEY_F6            117 ///< F6 key
#define RMG_KEY_F7            118 ///< F7 key
#define RMG_KEY_F8            119 ///< F8 key
#define RMG_KEY_F9            120 ///< F9 key
#define RMG_KEY_F10           121 ///< F10 key
#define RMG_KEY_F11           122 ///< F11 key
#define RMG_KEY_F12           123 ///< F12 key
#define RMG_KEY_NUM_LOCK      144 ///< Numpad-lock key
#define RMG_KEY_EQUAL         187 ///< Equal key
#define RMG_KEY_COMMA         188 ///< Comma key
#define RMG_KEY_DASH          189 ///< Dash key
#define RMG_KEY_DOT           190 ///< Dot key
#define RMG_KEY_SLASH         191 ///< Slash key
#define RMG_KEY_BACKQUOTE     192 ///< Backquote key
#define RMG_KEY_OPEN_BRACKET  219 ///< Open bracket key
#define RMG_KEY_BACKSLASH     220 ///< Backslash key
#define RMG_KEY_CLOSE_BRACKET 221 ///< Close bracket key
#define RMG_KEY_QUOTE         222 ///< Quote key

#endif
