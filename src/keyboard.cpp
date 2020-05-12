/**
 * @file keyboard.cpp
 * @brief Keyboard event and attributes
 * 
 * Stores a keycode and keyboard states.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "rmg/keyboard.hpp"


namespace rmg {

/**
 * @brief Default constructor
 */
KeyboardEvent::KeyboardEvent() {
    keycode = '\0';
    keyStates = 0b0000;
}

/**
 * @brief Gets the keycode
 * 
 * @return The keycode ('a', 'b', .etc)
 */
int16_t KeyboardEvent::getKeycode() const { return keycode; }

/**
 * @brief If the ctrl key is pressed
 * 
 * @return True if the ctrl is pressed
 */
bool KeyboardEvent::isCtrl() const { return keyStates & RMG_KEY_STATE_CTRL; }

/**
 * @brief If the alt key is pressed
 * 
 * @return True if the alt is pressed
 */
bool KeyboardEvent::isAlt() const { return keyStates & RMG_KEY_STATE_ALT; }

/**
 * @brief If the shift key is pressed
 * 
 * @return True if the shift is pressed
 */
bool KeyboardEvent::isShift() const { return keyStates & RMG_KEY_STATE_SHIFT; }

}
