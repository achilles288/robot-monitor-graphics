/**
 * @file context_render.cpp
 * @brief 2D/3D graphics context rendering function
 * 
 * Manages the rendering order of 2D/3D objects, handles GPU resources
 * associated with them.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "rmg/context.hpp"

#include <stdexcept>

#include <GL/glew.h>
#include <GL/gl.h>

#include "rmg/font.hpp"
#include "rmg/object.hpp"
#include "rmg/material.hpp"


namespace rmg {

float Context::t1 = 0;
MouseEvent mouseEvent;

/**
 * @brief Draws graphics from lists of objects pushed
 * 
 * This function starts looping as soon as the graphics context
 * starts up.
 */
void Context::render() {
    setCurrent();
    if(!initDone) {
        glewExperimental = true; // Needed for core profile
        if(glewInit() != GLEW_OK) {
            destroy();
            #ifdef WIN32
            throw std::runtime_error("error: Failed to initialize GLEW");
            #else
            throw std::runtime_error("\033[0;1;31merror: \033[0m"
                                     "Failed to initialize GLEW");
            #endif
        }
        int major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        if(major*100 + minor < 3*100 + 2) { // 3.2
            setErrorCode(503);
            #ifdef WIN32
            printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
            throw std::runtime_error("error: Requires OpenGL 3.2. "
                                     "Please check if you have the latest "
                                     "GPU driver.");
            #else
            printf("\033[0;1mOpenGL Version: %s\033[0m\n",
                   glGetString(GL_VERSION));
            throw std::runtime_error("\033[0;1;31merror: \033[0m"
                                     "Requires \033[1mOpenGL 3.2\033[0m. "
                                     "Please check if you have the latest "
                                     "GPU driver.");
            #endif
        }
        startTime = 0;
        startTime = getTime();
        initDone = true;
    }
    if(sizeUpdate) {
        glViewport(0, 0, width, height);
        sizeUpdate = false;
    }
    if(bgUpdate) {
        glClearColor(bgColor.red, bgColor.green, bgColor.blue, 1);
        bgUpdate = false;
    }
    
    float t2 = getTime();
    fps = 1.0f/(t2-t1);
    t1 = t2;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    update();
    if(destroyed)
        throw std::domain_error("Exit on context destruction");
    flush();
}

/**
 * @brief Flushes the drawn graphics by OpenGL onto the screen
 */
void Context::flush() {
    glFlush();
}

/**
 * @brief Gets the frame refresh rate of the context
 * 
 * The more FPS, the smoother the graphics looks.
 * 
 * @return Frame per second
 */
float Context::getFPS() { return fps; }

/**
 * @breif Sets the error code of the context
 * 
 * @param err Error code
 */
void Context::setErrorCode(int err) { errorCode = err; }

/**
 * @breif Gets the error code of the context
 * 
 * @return 0 if no error. 1 for general error code. 503 is usually returned
 *         if there is an error related with OpenGL or GPU driver.
 */
int Context::getErrorCode() { return errorCode; }

/**
 * @brief Idle display loop function
 * 
 * Function that is called for each frame of the context.
 * This function usually does response to events and animation of
 * 2D/3D objects on the context.
 */
void Context::update() {}

/**
 * @brief The function called when the mouse clicks on the context
 * 
 * @param event A set of attributes associated with the event
 */
void Context::onMouseClick(const MouseEvent &event) {}

/**
 * @brief The function called when a mouse button is pressed
 * 
 * @param event A set of attributes associated with the event
 */
void Context::onMousePress(const MouseEvent &event) {}

/**
 * @brief The function called when a mouse button is released
 * 
 * @param event A set of attributes associated with the event
 */
void Context::onMouseRelease(const MouseEvent &event) {}

/**
 * @brief The function called when the mouse pointer moves over the context
 * 
 * @param event A set of attributes associated with the event
 */
void Context::onMouseMove(const MouseEvent &event) {}

/**
 * @brief The function called when the mouse enters or exits te context
 * 
 * @param event A set of attributes associated with the event
 */
void Context::onMouseEntry(const MouseEvent &event) {}

/**
 * @brief The function called when the mouse wheel is scrolled
 * 
 * @param event A set of attributes associated with the event
 */
void Context::onMouseWheel(const MouseEvent &event) {}

/**
 * @brief The function called when a key is hit
 * 
 * @param event A set of attributes associated with the event
 */
void Context::onKeyboard(const KeyboardEvent &event) {}

}
