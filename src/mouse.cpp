/**
 * @file mouse.cpp
 * @brief Stores mouse position and states
 * 
 * Pointer position, pointer position transform and mouse states like
 * which buttons are pressed or released.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "rmg/mouse.hpp"


namespace rmg {

/**
 * @brief Default constructor
 */
MouseEvent::MouseEvent() {
    x = 0;
    y = 0;
    dx = 0;
    dy = 0;
    xp = 65535;
    yp = 65535;
    button = MouseButton::None;
    mouseStates = 0b0000;
    scroll = 0;
}

/**
 * @brief Gets mouse position
 * 
 * @return X-coordinate
 */
uint16_t MouseEvent::getX() const { return x; }

/**
 * @brief Gets mouse position
 * 
 * @return Y-coordinate
 */
uint16_t MouseEvent::getY() const { return y; }

/**
 * @brief Gets change in mouse position
 * 
 * @return Change in x-coordinate
 */
int16_t MouseEvent::getDiffX() const { return dx; }

/**
 * @brief Gets change in mouse position
 * 
 * @return Change in y-coordinate
 */
int16_t MouseEvent::getDiffY() const { return dy; }

/**
 * @brief Gets the mouse button which triggers the event
 * 
 * @return Left, middle or right mouse button
 */
MouseButton MouseEvent::getButton() const { return button; }

/**
 * @brief If the left mouse button is pressed
 * 
 * @return True if the left mouse button is pressed
 */
bool MouseEvent::isLeftPressed() const {
    return mouseStates & RMG_MOUSE_STATE_LEFT;
}

/**
 * @brief If the middle mouse button is pressed
 * 
 * @return True if the middle mouse button is pressed
 */
bool MouseEvent::isMiddlePressed() const {
   return mouseStates & RMG_MOUSE_STATE_MIDDLE;
}

/**
 * @brief If the right mouse button is pressed
 * 
 * @return True if the right mouse button is pressed
 */
bool MouseEvent::isRightPressed() const {
    return mouseStates & RMG_MOUSE_STATE_RIGHT;
}

/**
 * @brief If the mouse pointer is inside the context
 * 
 * @return True if the pointer is inside
 */
bool MouseEvent::isEntered() const {
    return mouseStates & RMG_MOUSE_STATE_ENTRY;
}

/**
 * @brief Gets the mouse scroll value
 */
int8_t MouseEvent::getScroll() const { return scroll; }

}
