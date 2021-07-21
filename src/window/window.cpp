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


#define RMG_WINDOW_EXPORT


#include "rmg/window.hpp"

#include <algorithm>
#include <cstdio>
#include <stdexcept>
#ifdef _WIN32
#include <Windows.h>
#define sleep(X) Sleep((DWORD)(X))
#else
#include <unistd.h>
#define sleep(X) usleep((__useconds_t)((X)*1000))
#endif

#include <GLFW/glfw3.h>

#include "../base/rmg/assert.hpp"
#include "../base/rmg/bitmap.hpp"
#include "../config/rmg/config.h"


static bool glfwInitDone = false;


namespace rmg {

std::vector<Window*> Window::windowList;

/**
 * @brief Default constructor
 */
Window::Window() {
    glfw_window = NULL;
    if(!glfwInitDone) {
        if(!glfwInit()) {
            setErrorCode(503);
            #ifdef _WIN32
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
        #ifdef _WIN32
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
    
    setWindowIcon(RMG_RESOURCE_PATH "/icons/rmg-app.png");
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
float Window::getTime() const {
    static bool startTimeCounted = false;
    static float startTime = 0.0f;
    if(!startTimeCounted) {
        startTime = (float)glfwGetTime();
        startTimeCounted = true;
    }
    return (float)glfwGetTime() - startTime;
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
 * @param file Path to the icon file
 */
void Window::setWindowIcon(const std::string &file) {
    Bitmap bmp = Bitmap::loadFromFile(file);
    RMG_EXPECT(bmp.getChannel() == 4);
    #ifndef NDEBUG
    if(bmp.getChannel() != 4)
        return;
    #endif
    GLFWimage icons[1];
    icons[0].width = bmp.getWidth();
    icons[0].height = bmp.getHeight();
    icons[0].pixels = bmp.getPointer();
    glfwSetWindowIcon(glfw_window, 1, icons);
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
Rect Window::getWindowSize() const {
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
    Context::setCurrent();
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
        double t1 = glfwGetTime();
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
                catch(std::runtime_error& e) {
                    if(window->getErrorCode() == 0)
                        window->setErrorCode(1);
                    printf("%s\n", e.what());
                    window->destroy();
                    break;
                }
                catch(UserExitException& e2) {
                    break;
                }
            }
        }
        glfwPollEvents();
        double t2 = glfwGetTime();
        double dt = t2 - t1;
        if(dt < 0.0166667f)
            sleep(16.6667f - dt*1000); // Limits to 60 fps
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
        int16_t dx = mouseEvent.x - mouseEvent.xp;
        int16_t dy = mouseEvent.y - mouseEvent.yp;
        if(abs(dx) < 5 && abs(dy) < 5)
            ctx->onMouseClick(mouseEvent);
        mouseEvent.mouseStates ^= mouseEvent.mouseStates & mask;
        ctx->onMouseRelease(mouseEvent);
    }
    mouseEvent.button = rmg::MouseButton::None;
}


void window_cursor_position_callback(GLFWwindow* window,
                                     double xpos, double ypos)
{
    rmg::Context* ctx = (rmg::Context*) glfwGetWindowUserPointer(window);
    
    mouseEvent.dx = (int16_t)xpos - mouseEvent.x;
    mouseEvent.dy = (int16_t)ypos - mouseEvent.y;
    mouseEvent.x = (int16_t)xpos;
    mouseEvent.y = (int16_t)ypos;
    ctx->onMouseMove(mouseEvent);
}


void window_cursor_enter_callback(GLFWwindow* window, int entered)
{
    rmg::Context* ctx = (rmg::Context*) glfwGetWindowUserPointer(window);
    
    if(entered) {
        mouseEvent.mouseStates |= RMG_MOUSE_STATE_ENTRY;
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        mouseEvent.x = (int16_t)xpos;
        mouseEvent.y = (int16_t)ypos;
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
    mouseEvent.scroll = (int8_t)yoffset;
    if(mouseEvent.scroll == 0)
        return;
    rmg::Context* ctx = (rmg::Context*) glfwGetWindowUserPointer(window);
    ctx->onMouseWheel(mouseEvent);
    mouseEvent.scroll = 0;
}


static int16_t GLFWKeycodeToRMGKeycode(int16_t keycode);


void window_key_callback(GLFWwindow* window, int key, int scancode,
                         int action, int mods)
{
    uint8_t mask = 0b0000;
    int16_t rkey = GLFWKeycodeToRMGKeycode((int16_t)key);
    if(rkey == RMG_KEY_CTRL)
        mask = RMG_KEY_STATE_CTRL;
    else if(rkey == RMG_KEY_ALT)
        mask = RMG_KEY_STATE_ALT;
    else if(rkey == RMG_KEY_SHIFT)
        mask = RMG_KEY_STATE_SHIFT;
    
    rmg::Context* ctx = (rmg::Context*) glfwGetWindowUserPointer(window);
    mouseEvent.keycode = rkey;
    if(action == GLFW_PRESS) {
        mouseEvent.keyStates |= mask;
        ctx->onKeyPress(*((rmg::KeyboardEvent*)(&mouseEvent)));
    }
    else if(action == GLFW_RELEASE) {
        mouseEvent.keyStates ^= mouseEvent.keyStates & mask;
        ctx->onKeyRelease(*((rmg::KeyboardEvent*)(&mouseEvent)));
    }
}


static int16_t GLFWKeycodeToRMGKeycode(int16_t keycode) {
    if((keycode >= '0' && keycode <= '9') ||
       (keycode >= 'A' && keycode <= 'Z'))
    {
        return keycode;
    }
    
    static const int16_t table1[] = {
        RMG_KEY_SPACE, // 32
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        RMG_KEY_QUOTE, // 39
        -1,
        -1,
        -1,
        -1,
        RMG_KEY_COMMA, // 44
        RMG_KEY_DASH,
        RMG_KEY_DOT,
        RMG_KEY_SLASH // 47
    };
    if(keycode >= 32 && keycode <= 47)
        return table1[keycode-32];
    
    if(keycode == GLFW_KEY_SEMICOLON)
        return RMG_KEY_COLON;
    if(keycode == GLFW_KEY_EQUAL)
        return RMG_KEY_EQUAL;
    if(keycode == GLFW_KEY_LEFT_BRACKET)
        return RMG_KEY_OPEN_BRACKET;
    if(keycode == GLFW_KEY_BACKSLASH)
        return RMG_KEY_BACKSLASH;
    if(keycode == GLFW_KEY_RIGHT_BRACKET)
        return RMG_KEY_CLOSE_BRACKET;
    if(keycode == GLFW_KEY_GRAVE_ACCENT)
        return RMG_KEY_BACKQUOTE;
    
    static const int16_t table2[] = {
        RMG_KEY_ESCAPE, // 256
        RMG_KEY_ENTER,
        RMG_KEY_TAB,
        RMG_KEY_BACKSPACE,
        RMG_KEY_INSERT,
        RMG_KEY_DELETE,
        RMG_KEY_ARROW_RIGHT,
        RMG_KEY_ARROW_LEFT,
        RMG_KEY_ARROW_DOWN,
        RMG_KEY_ARROW_UP,
        RMG_KEY_PAGE_UP,
        RMG_KEY_PAGE_DOWN,
        RMG_KEY_HOME,
        RMG_KEY_END, // 269
    };
    if(keycode >= 256 && keycode <= 269)
        return table2[keycode-256];
    
    if(keycode == GLFW_KEY_CAPS_LOCK)
        return RMG_KEY_CAPS_LOCK;
    if(keycode == GLFW_KEY_NUM_LOCK)
        return RMG_KEY_NUM_LOCK;
    if(keycode >= GLFW_KEY_F1 && keycode <= GLFW_KEY_F12)
        return keycode + RMG_KEY_F1 - GLFW_KEY_F1;
    
    static const int16_t table3[] = {
        RMG_KEY_NUM_0, // 320
        RMG_KEY_NUM_1,
        RMG_KEY_NUM_2,
        RMG_KEY_NUM_3,
        RMG_KEY_NUM_4,
        RMG_KEY_NUM_5,
        RMG_KEY_NUM_6,
        RMG_KEY_NUM_7,
        RMG_KEY_NUM_8,
        RMG_KEY_NUM_9,
        RMG_KEY_NUM_DECIMAL,
        RMG_KEY_NUM_DIVIDE,
        RMG_KEY_NUM_MULTIPLY,
        RMG_KEY_NUM_SUBTRACT,
        RMG_KEY_NUM_ADD,
        RMG_KEY_ENTER,
        RMG_KEY_EQUAL,
        -1,
        -1,
        -1,
        RMG_KEY_SHIFT,
        RMG_KEY_CTRL,
        RMG_KEY_ALT,
        -1,
        RMG_KEY_SHIFT,
        RMG_KEY_CTRL,
        RMG_KEY_ALT // 346
    };
    if(keycode >= 320 && keycode <= 346)
        return table3[keycode-320];
    
    return -1;
}

}
