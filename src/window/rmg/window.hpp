/**
 * @file window.hpp
 * @brief Standalone graphical context in a window
 *
 * Uses GLFW framework for window system.
 * GLFW windows and events interact with the 2D/3D graphics components.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_WINDOW_H__
#define __RMG_WINDOW_H__

#ifndef RMG_WINDOW_API
#ifdef _WIN32
#ifdef RMG_WINDOW_EXPORT
#define RMG_WINDOW_API __declspec(dllexport)
#else
#define RMG_WINDOW_API __declspec(dllimport)
#endif
#else
#define RMG_WINDOW_API
#endif
#endif


#include <rmg/context.hpp>
#include "internal/window_callback.hpp"


namespace rmg {

/**
 * @brief Standalone graphical context in a window
 *
 * Uses GLFW framework for window system.
 * GLFW windows and events interact with the 2D/3D graphics components.
 */
class RMG_WINDOW_API Window: public Context {
  private:
    GLFWwindow *glfw_window;
    static ContextList windowList;
    
  protected:
    /**
     * @brief Cleans up GPU resources
     */
    virtual void destroy();
    
  public:
    /**
     * @brief Default constructor
     */
    Window();
    
    /**
     * @brief Destructor cleans up context resources
     */
    virtual ~Window();
    
    /**
     * @brief Gets the running time of the context
     * 
     * @return Running time in seconds
     */
    float getTime() const override;
    
    /**
     * @brief Sets the name of the window
     * 
     * @param name Text displayed on top of the window
     */
    void setWindowName(const char* name);
    
    /**
     * @brief Sets the icon file for the window
     * 
     * @param file Path to the icon file
     */
    void setWindowIcon(const char* file);
    
    /**
     * @brief Sets the dimension of the window
     * 
     * @param w Width of the window
     * @param h Height of the window
     */
    void setWindowSize(uint16_t w, uint16_t h);
    
    /**
     * @brief Gets the dimension of the window
     * 
     * @return Rectangular dimension
     */
    Rect getWindowSize() const;
    
    /**
     * @brief Makes OpenGL rederer focuses on this context
     * 
     * Whenever functions regarding OpenGL resources is intended to be
     * called, the function needs to be called first especially when working
     * with multiple contexts.
     */
    void setCurrent() override;
    
    /**
     * @brief Flushes the drawn graphics by OpenGL onto the screen
     */
    void flush() override;
    
    /**
     * @brief This function runs frame update functions and event polling
     */
    static void mainLoop();
};

}

#endif
