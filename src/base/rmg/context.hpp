/**
 * @file context.hpp
 * @brief 2D/3D graphics context container
 * 
 * Manages 2D/3D objects with GPU context resources and shader programs.
 * Abstract layer of OpenGL context.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_CONTEXT_H__
#define __RMG_CONTEXT_H__

#ifndef RMG_API
#ifdef _WIN32
#ifdef RMG_EXPORT
#define RMG_API __declspec(dllexport)
#else
#define RMG_API __declspec(dllimport)
#endif
#else
#define RMG_API
#endif
#endif


#include <cstdint>
#include <stdexcept>
#include <map>

#include "camera.hpp"
#include "color.hpp"
#include "font.hpp"
#include "keyboard.hpp"
#include "material.hpp"
#include "mouse.hpp"
#include "object.hpp"
#include "internal/general_shader.hpp"
#include "internal/line3d_shader.hpp"
#include "internal/particle_shader.hpp"
#include "internal/shadow_map_shader.hpp"
#include "internal/object2d_shader.hpp"
#include "internal/context_load.hpp"
#include "math/line_equation.hpp"


namespace rmg {

/**
 * @brief A list of contexts stored in a forward-linked list
 */
class RMG_API ContextList: public LinkedList<Context> {
    class RMG_API iterator {
      private:
        LinkedList<Context>::Node* next = nullptr;
        Context* data = nullptr;
      
      public:
        iterator(LinkedList<Context>::Node* n, Context* d);
        
        Context& operator * ();
        
        Context* operator -> ();
        
        iterator& operator ++ ();
        
        iterator operator ++ (int);
        
        bool operator == (const iterator& it);
        
        bool operator != (const iterator& it);
    };

  public:
    /**
     * @brief Gets the start of the list
     * 
     * @return An iterator as in C++ STL containers
     */
    iterator begin() const;

    /**
     * @brief Gets the end of the list
     * 
     * @return An iterator as in C++ STL containers
     */
    iterator end() const;
};


/**
 * @brief 2D/3D OpenGL graphics context
 *
 * Manages 2D/3D objects with GPU context resources and shader programs.
 * Abstract layer of OpenGL context.
 * 
 * @image html component.svg
 * 
 * The RMGraphics API involves these componets. The user applications have a
 * custom update frame loop function for time events and animations as
 * well as other event events (keyboard, mouse, buttons, .etc) supported by
 * the GUI. In this system, those functions construct and manipulate
 * 2D/3D objects, textures and configure the world model which is camera
 * positions, projection model and context size.
 */
class RMG_API Context {
  private:
    uint32_t id;
    uint16_t width;
    uint16_t height;
    Color bgColor;
    Camera camera;
    Vec3 dlWorldSpace;
    Vec3 dlCameraSpace;
    Color dlColor;
    ObjectList object3d_list;
    ObjectList object2d_list;
    ObjectList particle3d_list;
    ObjectList line3d_list;
    ObjectList text2d_list;
    MaterialList materials;
    FontList fonts;
    
    internal::GeneralShader generalShader;
    internal::ShadowMapShader shadowMapShader;
    internal::Object2DShader object2dShader;
    internal::ParticleShader particleShader;
    internal::Line3DShader line3dShader;
    internal::ContextLoader loader;
    internal::GLContext glContext;
    
    bool initDone;
    float fps;
    bool destroyed;
    int errorCode;
    
    static uint32_t lastContextID;
    static ContextList contextList;
    
  protected:
    /**
     * @brief Sets the error code of the context
     * 
     * @param err Error code
     */
    void setErrorCode(int err);
    
    /**
     * @brief Exception thrown at user exit
     */
    class UserExitException: public std::exception {
      public:
        const char* what() const noexcept override;
    };
    
  public:
    /**
     * @brief Default constructor
     */
    Context();
    
    /**
     * @brief Destructor
     */
    virtual ~Context();
    
    /**
     * @brief Idle display loop function
     * 
     * Function that is called for each frame of the context.
     * This function usually does response to events and animation of
     * 2D/3D objects on the context.
     */
    virtual void update();
    
    /**
     * @brief The callback function after GL context initialization
     */
    virtual void onLoaded();
    
    /**
     * @brief The function called when the context size changes
     */
    virtual void onResize();
    
    /**
     * @brief The function called when the mouse clicks on the context
     * 
     * @param event A set of attributes associated with the event
     */
    virtual void onMouseClick(const MouseEvent &event);
    
    /**
     * @brief The function called when a mouse button is pressed
     * 
     * @param event A set of attributes associated with the event
     */
    virtual void onMousePress(const MouseEvent &event);
    
    /**
     * @brief The function called when a mouse button is released
     * 
     * @param event A set of attributes associated with the event
     */
    virtual void onMouseRelease(const MouseEvent &event);
    
    /**
     * @brief The function called when the mouse pointer moves over the context
     * 
     * @param event A set of attributes associated with the event
     */
    virtual void onMouseMove(const MouseEvent &event);
    
    /**
     * @brief The function called when the mouse enters or exits te context
     * 
     * @param event A set of attributes associated with the event
     */
    virtual void onMouseEntry(const MouseEvent &event);
    
    /**
     * @brief The function called when the mouse wheel is scrolled
     * 
     * @param event A set of attributes associated with the event
     */
    virtual void onMouseWheel(const MouseEvent &event);
    
    /**
     * @brief The function called when a key is pressed
     * 
     * @param event A set of attributes associated with the event
     */
    virtual void onKeyPress(const KeyboardEvent &event);
    
    /**
     * @brief The function called when a pressed key is released
     * 
     * @param event A set of attributes associated with the event
     */
    virtual void onKeyRelease(const KeyboardEvent &event);
    
    /**
     * @brief Gets the running time of the context
     * 
     * @return Running time in seconds
     */
    virtual float getTime() const;
    
    /**
     * @brief Gets the frame refresh rate of the context
     * 
     * The more FPS, the smoother the graphics looks.
     * 
     * @return Frame per second
     */
    float getFPS() const;
    
    /**
     * @brief Gets the ID of the context
     * 
     * @return Context ID
     */
    uint32_t getID() const;
    
    /**
     * @brief Sets OpenGL viewport size
     * 
     * @param w Viewport width
     * @param h Viewport height
     */
    void setContextSize(uint16_t w, uint16_t h);
    
    /**
     * @brief Gets the viewport size
     * 
     * @return Rectangular dimension
     */
    Rect getContextSize() const;
    
    /**
     * @brief Sets context background color
     * 
     * @param r Red
     * @param g Green
     * @param b Blue
     */
    void setBackgroundColor(float r, float g, float b);
    
    /**
     * @brief Sets context background color
     * 
     * @param col RGB color
     */
    void setBackgroundColor(const Color &col);
    
    /**
     * @brief Gets context background color
     * 
     * @return RGB color
     */
    Color getBackgroundColor() const;
    
    /**
     * @brief Gets the camera that displays the context
     * 
     * @return Reference to the immutable camera object
     */
    const Camera& getCamera() const;
    
    /**
     * @brief Sets xyz position of the camera
     * 
     * Sets the translation part of the view matrix.
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param z Z-coordinate
     */
    void setCameraTranslation(float x, float y, float z);
    
    /**
     * @brief Sets xyz position of the camera
     * 
     * Sets the translation part of the view matrix.
     * 
     * @param pos Camera position
     */
    void setCameraTranslation(const Vec3 &pos);
    
    /**
     * @brief Sets rotation of the camera
     * 
     * Sets the view matrix. Rotation of the camera is in Euler angles.
     * Rotation order is ZYX (Yaw-Pitch-Roll).
     * 
     * @param x Roll
     * @param y Pitch
     * @param z Yaw
     */
    void setCameraRotation(float x, float y, float z);
    
    /**
     * @brief Sets rotation of the camera
     * 
     * Sets the view matrix. Rotation of the camera is in Euler angles.
     * Rotation order is ZYX (Yaw-Pitch-Roll).
     * 
     * @param x Roll
     * @param y Pitch
     * @param z Yaw
     * @param unit The previous params are degree or radian
     */
    void setCameraRotation(float x, float y, float z, AngleUnit unit);
    
    /**
     * @brief Sets rotation of the camera
     * 
     * Sets the view matrix. Rotation of the camera is in Euler angles.
     * Rotation order is ZYX (Yaw-Pitch-Roll).
     * 
     * @param rot Euler angles
     */
    void setCameraRotation(const Euler &rot);
    
    /**
     * @brief Gets xyz position of the camera
     * 
     * Gets values from the translation part of the view matrix.
     * 
     * @return XYZ position
     */
    Vec3 getCameraTranslation() const;
    
    /**
     * @brief Gets rotation of the camera
     * 
     * Calculates values from the rotation part of the view matrix.
     * Rotation order is ZYX (Yaw-Pitch-Roll).
     *
     * @return Rotation in Euler angles
     */
    Euler getCameraRotation() const;
    
    /**
     * @brief Sets the projection to perspective mode
     */
    void setPerspectiveProjection();
    
    /**
     * @brief Sets the parameters for perspective projection
     * 
     * Sets the perspective matrix.
     * 
     * @param fov Field of view
     * @param near Minimum clipping distance
     * @param far Maximum clipping distance
     */
    void setPerspectiveProjection(float fov, float near, float far);
    
    /**
     * @brief Sets the projection to orthographic mode
     */
    void setOrthographicProjection();
    
    /**
     * @brief Sets the parameters for orthographic projection
     * 
     * Sets the perspective matrix.
     * 
     * @param fov Viewing distance along Y-axis of the screen
     * @param near Minimum clipping distance
     * @param far Maximum clipping distance
     */
    void setOrthographicProjection(float fov, float near, float far);
    
    /**
     * @brief Sets angle of view for perspective projection
     * 
     * @param fov Field of view
     */
    void setFieldOfView(float fov);
    
    /**
     * @brief Sets minimum distance for depth clipping
     * 
     * @param n Minimum clipping distance
     */
    void setMinimumDistance(float n);
    
    /**
     * @brief Sets maximum distance for depth clipping
     * 
     * @param f Maximum clipping distance
     */
    void setMaximumDistance(float f);
    
    /**
     * @brief Gets angle of view used in perspective projection
     * 
     * @return Field of view
     */
    float getFieldOfView() const;
    
    /**
     * @brief Gets minimum distance for depth clipping
     * 
     * @return Minimum clipping distance
     */
    float getMinimumDistance() const;
    
    /**
     * @brief Gets maximum distance for depth clipping
     * 
     * @return Maximum clipping distance
     */
    float getMaximumDistance() const;
    
    /**
     * @brief Sets the directional lighting color
     * 
     * Directional light takes the main role in fragment shaders and
     * shadow mappings for 3D object viewing.
     * 
     * @param r Red
     * @param g Green
     * @param b Blue
     * @param lum Light intensity
     */
    void setDirectionalLightColor(float r, float g, float b, float lum);
    
    /**
     * @brief Sets the directional lighting color
     * 
     * Directional light takes the main role in fragment shaders and
     * shadow mappings for 3D object viewing.
     * 
     * @param col RGBA color. Alpha component is used as light intensity.
     */
    void setDirectionalLightColor(const Color &col);
    
    /**
     * @brief Gets the directional lighting color
     * 
     * @return RGBA color. Alpha component is used as light intensity.
     */
    Color getDirectionalLightColor() const;
    
    /**
     * @brief Sets the directional lighting angles
     * 
     * Directional light takes the main role in fragment shaders and
     * shadow mappings for 3D object viewing. Rotation order is
     * ZY (Yaw-Pitch). Rolling has no effect.
     * 
     * @param pitch Angle above xy-plane
     * @param yaw Angle about z-axis
     */
    void setDirectionalLightAngles(float pitch, float yaw);
    
    /**
     * @brief Sets the directional lighting angles
     * 
     * Directional light takes the main role in fragment shaders and
     * shadow mappings for 3D object viewing. Rotation order is
     * ZY (Yaw-Pitch). Rolling has no effect.
     * 
     * @param pitch Angle above xy-plane
     * @param yaw Angle about z-axis
     * @param unit Radian or degree
     */
    inline void setDirectionalLightAngles(float pitch, float yaw,
                                          AngleUnit unit)
    {
        if(unit == AngleUnit::Radian)
            setDirectionalLightAngles(pitch, yaw);
        else
            setDirectionalLightAngles(radian(pitch), radian(yaw));
    }
    
    /**
     * @brief Sets the directional lighting angles
     * 
     * Directional light takes the main role in fragment shaders and
     * shadow mappings for 3D object viewing. Rotation order is
     * ZY (Yaw-Pitch). Rolling has no effect.
     * 
     * @param rot Euler angles
     */
    inline void setDirectionalLightAngles(const Euler &rot) {
        setDirectionalLightAngles(rot.pitch, rot.yaw);
    }
    
    /**
     * @brief Gets the directional lighting angles
     * 
     * Rotation order is ZY (Yaw-Pitch). Rolling has no effect and the
     * x in returned instance is always zero.
     * 
     * @return Rotation in Euler angles
     */
    Euler getDirectionalLightAngles() const;
    
    /**
     * @brief Converts world coordinate to screen coordinate
     * 
     * Useful when displaying 2D sprites and texts around 3D objects.
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param z Z-coordinate
     * 
     * @return 2D point on screen
     */
    Rect worldToScreen(float x, float y, float z) const;
    
    /**
     * @brief Converts world coordinate to screen coordinate
     * 
     * Useful when displaying 2D sprites and texts around 3D objects.
     * 
     * @param p 3D point in world space
     * 
     * @return 2D point on screen
     */
    Rect worldToScreen(const Vec3 &p) const;
    
    /**
     * @brief Converts screen coordinate to world coordinate
     * 
     * Useful when interacting 3D objects with a mouse.
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     * 
     * @return Line equation in 3D world
     */
    LineEq screenToWorld(uint16_t x, uint16_t y) const;
    
    /**
     * @brief Converts screen coordinate to world coordinate
     * 
     * Useful when interacting 3D objects with a mouse.
     * 
     * @param p Point on screen
     * 
     * @return Line equation in 3D world
     */
    LineEq screenToWorld(const Rect &p) const;
    
    /**
     * @brief Appends a 2D/3D object to the display list
     * 
     * @param obj 2D/3D object
     */
    void addObject(Object* obj);
    
    /**
     * @brief Appends a material to the list to load GPU resources
     * 
     * @param mat Material
     */
    void addMaterial(Material* mat);
    
    /**
     * @brief Appends a font to the font list for text drawing
     * 
     * @param ft Font
     */
    void addFont(Font* ft);
    
    /**
     * @brief Removes a 2D/3D object from the list cleaning the GPU resources
     * 
     * @param obj 2D/3D object
     */
    void removeObject(Object* obj);
    
    /**
     * @brief Removes a material from the list cleaning the GPU resources
     * 
     * @param mat Material
     */
    void removeMaterial(Material* mat);
    
    /**
     * @brief Removes a font from the list cleaning the GPU resources
     * 
     * @param ft Font
     */
    void removeFont(Font* ft);
    
    /**
     * @brief Gets the number of objects in the object list
     * 
     * @return Total number of objects from lists of every type
     */
    uint64_t getObjectCount() const;
    
    /**
     * @brief Gets the number of materials in the list
     * 
     * @return Number of materials
     */
    uint64_t getMaterialCount() const;
    
    /**
     * @brief Gets the number of fonts in the list
     * 
     * @return Number of fonts
     */
    uint64_t getFontCount() const;
    
    /**
     * @brief Removes all context resources
     * 
     * Clears the lists of objects, textures, fonts and their GPU resources.
     */
    void cleanup();
    
    /**
     * @brief Draws graphics from lists of objects pushed
     * 
     * This function starts looping as soon as the graphics context
     * starts up.
     */
    void render();
    
    /**
     * @brief Makes OpenGL rederer focuses on this context
     * 
     * Whenever functions regarding OpenGL resources is intended to be
     * called, the function needs to be called first especially when working
     * with multiple contexts.
     */
    virtual void setCurrent();
    
    /**
     * @brief Flushes the drawn graphics by OpenGL onto the screen
     */
    virtual void flush();
    
    /**
     * @brief Cleans up GPU resources
     */
    virtual void destroy();
    
    /**
     * @brief To see if the context is still active and usable
     * 
     * return True if the context is destroyed
     */
    bool isDestroyed() const;
    
    /**
     * @brief Gets the current working context
     */
    static Context* getCurrent();
    
    /**
     * @brief Searches context model by ID
     * 
     * @return OpenGL context
     */
    static Context* getContextByID(uint32_t id);
    
    /**
     * @brief Destroys every RMG context cleaning all GPU resources allocated
     */
    static void destroyAll();
    
    /**
     * @brief Gets the error code of the context
     * 
     * @return 0 if no error. 1 for general error code. 503 is usually returned
     *         if there is an error related with OpenGL or GPU driver.
     */
    int getErrorCode() const;
};

/**
 * @brief Static mouse or keyboard event instance where the parameters are
 *        stored
 */
extern RMG_API MouseEvent mouseEvent;

}

#endif
