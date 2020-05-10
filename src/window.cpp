/**
 * @file window.cpp
 * @brief Standalone graphical context in a window
 *
 * Uses GLFW framework for window system.
 * GLFW windows and events interact with the 2D/3D graphics components.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "rmg/window.hpp"

#include <algorithm>
#include <cstdio>
#include <stdexcept>


static bool glfwInitDone = false;


namespace rmg {

void window_mouse_button_callback(GLFWwindow* window, int button,
                                  int action, int mods);

void window_cursor_position_callback(GLFWwindow* window,
                                     double xpos, double ypos);

void window_cursor_enter_callback(GLFWwindow* window, int entered);

void window_scroll_callback(GLFWwindow* window,
                            double xoffset, double yoffset);

void window_key_callback(GLFWwindow* window, int key, int scancode,
                         int action, int mods);


std::vector<Window*> Window::windowList;

/**
 * @brief Default constructor
 */
Window::Window() {
    glfw_window = NULL;
    if(!glfwInitDone) {
        if(!glfwInit()) {
            setErrorCode(503);
            #ifdef WIN32
            printf("error: Failed to initialize GLFW\n");
            #else
            printf("\033[0;1;31merror:\033[0m Failed to initialize GLFW\n");
            #endif
            destroy();
            return;
        }
        glfwInitDone = true;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    // Open a window and create its OpenGL context
    glfw_window = glfwCreateWindow(768, 432, "RMGraphics Window", NULL, NULL);
    if(glfw_window == NULL) {
        setErrorCode(503);
        #ifdef WIN32
        printf("error: Failed to open GLFW window\n");
        #else
        printf("\033[0;1;31merror:\033[0m Failed to open GLFW window\n");
        #endif
        destroy();
		return;
    }
    glfwSetMouseButtonCallback(glfw_window, window_mouse_button_callback);
    glfwSetCursorPosCallback(glfw_window, window_cursor_position_callback);
    glfwSetCursorEnterCallback(glfw_window, window_cursor_enter_callback);
    glfwSetScrollCallback(glfw_window, window_scroll_callback);
    glfwSetKeyCallback(glfw_window, window_key_callback);
    
    glfwSetWindowUserPointer(glfw_window, (void*)this);
    windowList.push_back(this);
}

/**
 * @brief Destructor
 */
Window::~Window() {}

/**
 * @brief Cleans up context resources
 */
void Window::destroy() {
    if(isDestroyed())
        return;
    Context::destroy();
    glfwMakeContextCurrent(NULL);
    glfwDestroyWindow(glfw_window);
    glfw_window = NULL;
    windowList.erase(std::find(
        windowList.begin(),
        windowList.end(),
        this
    ));
}

/**
 * @brief Gets the running time of the context
 * 
 * @return Running time in seconds
 */
float Window::getTime() {
    return glfwGetTime() - startTime;
}

/**
 * @brief Sets the name of the window
 * 
 * @param name Text displayed on top of the window
 */
void Window::setWindowName(const std::string &name) {
    glfwSetWindowTitle(glfw_window, name.c_str());
}

/**
 * @brief Sets the icon file for the window
 * 
 * @param icon Path to the icon file
 */
void Window::setWindowIcon(const std::string &icon) {
    GLFWimage icons[1];
    // icons[0].pixels = load_png(icon.c_str());
    glfwSetWindowIcon(glfw_window, 1, icons);
    // free(icons[0].pixels);
}

/**
 * @brief Sets the dimension of the window
 * 
 * @param w Width of the window
 * @param h Height of the window
 */
void Window::setWindowSize(uint16_t w, uint16_t h) {
    glfwSetWindowSize(glfw_window, w, h);
}

/**
 * @brief Gets the dimension of the window
 * 
 * @return Rectangular dimension
 */
Rect Window::getWindowSize() {
    int x, y;
    glfwGetWindowSize(glfw_window, &x, &y);
    return Rect(x, y);
}

/**
 * @brief Makes OpenGL rederer focuses on this context
 * 
 * Whenever functions regarding OpenGL resources is intended to be
 * called, the function needs to be called first especially when working
 * with multiple contexts.
 */
void Window::setCurrent() {
    glfwMakeContextCurrent(glfw_window);
}

/**
 * @brief Flushes the drawn graphics by OpenGL onto the screen
 */
void Window::flush() {
    glfwSwapBuffers(glfw_window);
}

/**
 * @brief This function runs frame update functions and event polling
 */
void Window::mainLoop() {
    while(windowList.size() > 0) {
        for(auto it=windowList.begin(); it!=windowList.end(); it++) {
            Window* window = *it;
            if(glfwWindowShouldClose(window->glfw_window)) {
                window->destroy();
                break;
            }
            else {
                int w, h;
                glfwGetFramebufferSize(window->glfw_window, &w, &h);
                Rect r = window->getContextSize();
                if(w != r.x || h != r.y)
                    window->setContextSize(w, h);
                
                try {
                    window->render();
                }
                catch(std::runtime_error e) {
                    if(window->getErrorCode() == 0)
                        window->setErrorCode(1);
                    printf("%s\n", e.what());
                    window->destroy();
                    break;
                }
                catch(std::domain_error e) {
                    window->destroy();
                    break;
                }
            }
        }
        glfwPollEvents();
    }
    glfwTerminate();
    glfwInitDone = false;
}


void window_mouse_button_callback(GLFWwindow* window, int button,
                                  int action, int mods)
{
    rmg::Context* ctx = (rmg::Context*) glfwGetWindowUserPointer(window);
    
    uint8_t mask = 0b0000;
    if(button == GLFW_MOUSE_BUTTON_LEFT) {
        mouseEvent.button = rmg::MouseButton::Left;
        mask = RMG_MOUSE_STATE_LEFT;
    }
    else if(button == GLFW_MOUSE_BUTTON_MIDDLE) {
        mouseEvent.button = rmg::MouseButton::Middle;
        mask = RMG_MOUSE_STATE_MIDDLE;
    }
    else if(button == GLFW_MOUSE_BUTTON_RIGHT) {
        mouseEvent.button = rmg::MouseButton::Right;
        mask = RMG_MOUSE_STATE_RIGHT;
    }
    
    if(action == GLFW_PRESS) {
        mouseEvent.mouseStates |= mask;
        mouseEvent.xp = mouseEvent.x;
        mouseEvent.yp = mouseEvent.y;
        ctx->onMousePress(mouseEvent);
    }
    else {
        mouseEvent.mouseStates ^= mouseEvent.mouseStates & mask;
        ctx->onMouseRelease(mouseEvent);
        uint16_t dx = mouseEvent.x - mouseEvent.xp;
        uint16_t dy = mouseEvent.y - mouseEvent.yp;
        if(abs(dx) < 5 && abs(dy) < 5)
            ctx->onMouseClick(mouseEvent);
    }
    mouseEvent.button = rmg::MouseButton::None;
}


void window_cursor_position_callback(GLFWwindow* window,
                                     double xpos, double ypos)
{
    rmg::Context* ctx = (rmg::Context*) glfwGetWindowUserPointer(window);
    
    mouseEvent.dx = xpos - mouseEvent.x;
    mouseEvent.dy = ypos - mouseEvent.y;
    mouseEvent.x = xpos;
    mouseEvent.y = ypos;
    ctx->onMouseMove(mouseEvent);
}


void window_cursor_enter_callback(GLFWwindow* window, int entered)
{
    rmg::Context* ctx = (rmg::Context*) glfwGetWindowUserPointer(window);
    
    if(entered) {
        mouseEvent.mouseStates |= RMG_MOUSE_STATE_ENTRY;
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        mouseEvent.x = xpos;
        mouseEvent.y = ypos;
    }
    else {
        mouseEvent.mouseStates ^= mouseEvent.mouseStates &
                                  RMG_MOUSE_STATE_ENTRY;
    }
    ctx->onMouseEntry(mouseEvent);
}


void window_scroll_callback(GLFWwindow* window,
                            double xoffset, double yoffset)
{
    mouseEvent.scroll = yoffset;
    if(mouseEvent.scroll == 0)
        return;
    rmg::Context* ctx = (rmg::Context*) glfwGetWindowUserPointer(window);
    ctx->onMouseWheel(mouseEvent);
    mouseEvent.scroll = 0;
}


void window_key_callback(GLFWwindow* window, int key, int scancode,
                         int action, int mods)
{
    uint8_t mask = 0b0000;
    if(scancode == 37 || scancode == 105)
        mask = RMG_KEY_STATE_CTRL;
    else if(scancode == 64 || scancode == 108)
        mask = RMG_KEY_STATE_ALT;
    else if(scancode == 50 || scancode == 62)
        mask = RMG_KEY_STATE_SHIFT;
    
    if(action == GLFW_PRESS) {
        mouseEvent.keyStates |= mask;
        rmg::Context* ctx = (rmg::Context*) glfwGetWindowUserPointer(window);
        mouseEvent.keycode = key;
        ctx->onKeyboard(*((rmg::KeyboardEvent*)(&mouseEvent)));
    }
    else if(action == GLFW_RELEASE) {
        mouseEvent.keyStates ^= mouseEvent.keyStates & mask;
    }
}

}
