/**
 * @file context_renderer.cpp
 * @brief 2D/3D graphics context rendering function
 * 
 * Manages the rendering order of 2D/3D objects, handles GPU resources
 * associated with them.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "rmg/context.hpp"

#include <stdexcept>

#include "rmg/font.hpp"
#include "rmg/object.hpp"
#include "rmg/material.hpp"


static float t1 = 0.0f;


namespace rmg {

RMG_API MouseEvent mouseEvent;

/**
 * @brief Draws graphics from lists of objects pushed
 * 
 * This function starts looping as soon as the graphics context
 * starts up.
 */
void Context::render() {
    setCurrent();
    if(!initDone) {
        int status = glContext.init();
        if(status != 0) {
            setErrorCode(503);
            #ifdef _WIN32
            throw std::runtime_error("error: Failed to initialize GL "
                                     "extensions");
            #else
            throw std::runtime_error("\033[0;1;31merror: \033[0m"
                                     "Failed to initialize GL extensions");
            #endif
        }
        int major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        if(major*100 + minor < 3*100 + 2) { // 3.2
            setErrorCode(503);
            #ifdef _WIN32
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
        generalShader.load();
        shadowMapShader.load();
        particleShader.load();
        object2dShader.load();
        initDone = true;
    }
    
    if(loader.getLoadCount() > 0)
        loader.load();
    
    float t2 = getTime();
    fps = 1.0f/(t2-t1);
    t1 = t2;
    
    uint32_t shadow = shadowMapShader.createShadowMap(object3d_list);
    
    glViewport(0, 0, width, height);
    glClearColor(bgColor.red, bgColor.green, bgColor.blue, 1);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    generalShader.render(
        camera.getViewMatrix(),
        camera.getProjectionMatrix(),
        shadowMapShader.getShadowMatrix(),
        dlCameraSpace,
        dlColor,
        shadow,
        object3d_list
    );
    
    particleShader.render(
        camera.getViewMatrix(),
        camera.getProjectionMatrix(),
        particle3d_list
    );
    
    object2dShader.render(object2d_list);
    internal::glUseProgram(0);
    
    update();
    if(destroyed)
        throw UserExitException();
    
    flush();
}




static Context *current = nullptr;

/**
 * @brief Makes OpenGL rederer focuses on this context
 * 
 * Whenever functions regarding OpenGL resources is intended to be
 * called, the function needs to be called first especially when working
 * with multiple contexts.
 */
void Context::setCurrent() {
    if(initDone) {
      current = this;
      glContext.setCurrent();
    }
}

/**
 * @brief Gets the current working context
 */
Context *Context::getCurrent() { return current; }

/**
 * @brief Flushes the drawn graphics by OpenGL onto the screen
 */
void Context::flush() {
    glFlush();
}

/**
 * @brief Gets the running time of the context
 * 
 * @return Running time in seconds
 */
float Context::getTime() const { return 0; }
    
/**
 * @brief Gets the frame refresh rate of the context
 * 
 * The more FPS, the smoother the graphics looks.
 * 
 * @return Frame per second
 */
float Context::getFPS() const { return fps; }

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
int Context::getErrorCode() const { return errorCode; }

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
 * @brief The function called when a key is pressed
 * 
 * @param event A set of attributes associated with the event
 */
void Context::onKeyPress(const KeyboardEvent &event) {}

/**
 * @brief The function called when a pressed key is released
 * 
 * @param event A set of attributes associated with the event
 */
void Context::onKeyRelease(const KeyboardEvent &event) {}

}
