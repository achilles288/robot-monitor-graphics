/**
 * @file mouse.hpp
 * @brief Stores mouse position and states
 * 
 * Pointer position, pointer position transform and mouse states like
 * which buttons are pressed or released.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_MOUSE_H__
#define __RMG_MOUSE_H__ ///< Header guard

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


#include "keyboard.hpp"


namespace rmg {

class wxCanvas;

/**
 * @brief To check if the mouse button is left, middle or right
 */
enum class MouseButton {
    None,
    Left,
    Middle,
    Right
};

#define RMG_MOUSE_STATE_LEFT   0b0100 ///< Mouse left button press mask
#define RMG_MOUSE_STATE_MIDDLE 0b0010 ///< Mouse middle button press mask
#define RMG_MOUSE_STATE_RIGHT  0b0001 ///< Mouse right button press mask
#define RMG_MOUSE_STATE_ENTRY  0b1000 ///< Mouse entry state mask


/**
 * @brief Stores mouse position and states
 * 
 * Pointer position, pointer position transform and mouse states like
 * which buttons are pressed or released.
 */
class RMG_API MouseEvent: public KeyboardEvent {
  private:
    int16_t x; ///< X-coordinate on screen
    int16_t y; ///< Y-coordinate on screen
    int16_t dx; ///< Change in X-coordinate
    int16_t dy; ///< Change in Y-coordinate
    int16_t xp; ///< X-coordinate where press event occured
    int16_t yp; ///< Y-coordinate where press event occured
    MouseButton button; ///< The mouse button which cause the event
    uint8_t mouseStates; ///< Which buttons are pressed or released
    int8_t scroll; ///< Scroll value by mouse wheel
    
    friend void window_mouse_button_callback
                    (GLFWwindow* window, int button, int action, int mods);
    
    friend void window_cursor_position_callback
                    (GLFWwindow* window, double xpos, double ypos);
    
    friend void window_cursor_enter_callback
                    (GLFWwindow* window, int entered);
    
    friend void window_scroll_callback
                    (GLFWwindow* window, double xoffset, double yoffset);
    
    friend void window_key_callback(GLFWwindow* window, int key, int scancode,
                                    int action, int mods);
    
    friend class wxCanvas;
    
  public:
    /**
     * @brief Default constructor
     */
    MouseEvent();
    
    /**
     * @brief Gets mouse position
     * 
     * @return X-coordinate
     */
    int16_t getX() const;
    
    /**
     * @brief Gets mouse position
     * 
     * @return Y-coordinate
     */
    int16_t getY() const;
    
    /**
     * @brief Gets change in mouse position
     * 
     * @return Change in x-coordinate
     */
    int16_t getDiffX() const;
    
    /**
     * @brief Gets change in mouse position
     * 
     * @return Change in y-coordinate
     */
    int16_t getDiffY() const;
    
    /**
     * @brief Gets the mouse button which triggers the event
     * 
     * @return Left, middle or right mouse button
     */
    MouseButton getButton() const;
    
    /**
     * @brief If the left mouse button is pressed
     * 
     * @return True if the left mouse button is pressed
     */
    bool isLeftPressed() const;
    
    /**
     * @brief If the middle mouse button is pressed
     * 
     * @return True if the middle mouse button is pressed
     */
    bool isMiddlePressed() const;
    
    /**
     * @brief If the right mouse button is pressed
     * 
     * @return True if the right mouse button is pressed
     */
    bool isRightPressed() const;
    
    /**
     * @brief If the mouse pointer is inside the context
     * 
     * @return True if the pointer is inside
     */
    bool isEntered() const;
    
    /**
     * @brief Gets the mouse scroll value
     */
    int8_t getScroll() const;
};

}

#endif
