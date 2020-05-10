/**
 * @file window_callback.hpp
 * @brief Callback functions of rmg::Window
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_WINDOW_CALLBACK_H__
#define __RMG_WINDOW_CALLBACK_H__

#ifdef __cplusplus
extern "C" {
#endif
struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow; ///< GLFW window
#ifdef __cplusplus
}
#endif


namespace rmg {

/**
 * @brief GLFW mouse button callback
 */
void window_mouse_button_callback(GLFWwindow* window, int button,
                                  int action, int mods);

/**
 * @brief GLFW cursor position callback
 */
void window_cursor_position_callback(GLFWwindow* window,
                                     double xpos, double ypos);

/**
 * @brief GLFW cursor enter callback
 */
void window_cursor_enter_callback(GLFWwindow* window, int entered);

/**
 * @brief GLFW mouse scroll callback
 */
void window_scroll_callback(GLFWwindow* window,
                            double xoffset, double yoffset);

/**
 * @brief GLFW key callback
 */
void window_key_callback(GLFWwindow* window, int key, int scancode,
                         int action, int mods);

}

#endif
