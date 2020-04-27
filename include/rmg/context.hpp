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

#include <rmg/math/vec.hpp>
#include <rmg/math/euler.hpp>

#include <list>
#include <map>
#include <queue>

#include <cstdint>


namespace rmg {

struct Color;
struct Plane;

class Object;
class Object2D;
class Object3D;
class Particle;
class Line3D;
class Texture;
class Font;

namespace internal {

class VBOLoadPending;
class TexturePending;
class FontPending;
class GeneralShader;
class ShadowMapShader;
class SpriteShader;
class ParticleShader;
class Line3DShader;

}


/**
 * @brief 2D/3D OpenGL graphics context
 *
 * Manages 2D/3D objects with GPU context resources and shader programs.
 * Abstract layer of OpenGL context.
 */
class Context {
  private:
    uint64_t id;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::mat4 VPMatrix;
    float minDistance;
    float maxDistance;
    Vec3 directionalLight;
    Vec3 directionalLightCamera;
    Color directionalLightColor;
    uint16_t width;
    uint16_t height;
    Color bgColor;
    std::map<uint64_t, Object2D*> objects2d;
    std::map<uint64_t, Object3D*> objects3d;
    std::map<uint64_t, Particle*> particles;
    std::map<uint64_t, Line3D*> lines3d;
    std::map<uint64_t, Texture*> textures;
    std::map<uint64_t, Font*> fonts;
    
    internal::GeneralShader generalShader;
    internal::ShadowMapShader shadowMapShader;
    internal::SpriteShader spriteShader;
    internal::ParticleShader particleShader;
    internal::Line3DShader line3dShader;
    
    std::queue
      <internal::VBOLoadPending> vboLoadPending;
    
    std::queue
      <internal::TextureLoadPending> texLoadPending;
    
    std::queue
      <internal::FontLoadPending> fontLoadPending;
    
    static uint64_t lastContextID;
    static std::vector<Context*> contextList;
    
  protected:
    /**
     * @brief States whether the context is ready for GPU resources
     */
    bool initDone;
    
    /**
     * @brief Time counted at the time the context starts up
     */
    uint64_t startTime;
    
    /**
     * @brief Draws graphics from lists of objects pushed
     * 
     * This function starts looping as soon as the graphics context
     * starts up.
     */
    void render();
    
    /**
     * @brief Sets OpenGL viewport size
     * 
     * @param w Viewport width
     * @param h Viewport height
     */
    void setContextSize(uint16_t w, uint16_t h);
    
  public:
    /**
     * @brief Default constructor
     */
    Context();
    
    /**
     * @brief Destructor cleans up context resources
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
     * @brief Gets the running time of the context
     * 
     * @return Running time in milliseconds
     */
    virtual uint64_t getTime();
    
    /**
     * @brief Gets the ID of the context
     * 
     * @return Context ID
     */
    uint64_t getID();
    
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
    Color getBackgroundColor();
    
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
     * Rotation order is ZYX (Yaw-Pitch-Roll). Initial camera direction
     * or X-axis is along the Y-axis of the world (rotation values of
     * (0,0,0)).
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
     * Rotation order is ZYX (Yaw-Pitch-Roll). Initial camera direction
     * or X-axis is along the Y-axis of the world (rotation values of
     * (0,0,0)).
     * 
     * @param x Roll
     * @param y Pitch
     * @param z Yaw
     * @param unit The previous params are degree or radian
     */
    inline void setCameraRotation(float x, float y, float z, AngleUnit unit) {
        if(unit == UNIT_RADIAN)
            setCameraRotation(x, y, z);
        else
            setCameraRotation(radian(x), radian(y), radian(z));
    }
    
    /**
     * @brief Sets rotation of the camera
     * 
     * Sets the view matrix. Rotation of the camera is in Euler angles.
     * Rotation order is ZYX (Yaw-Pitch-Roll).
     * 
     * @param rot Euler angles
     */
    inline void setCameraRotation(const Euler &rot) {
        setCameraRotation(rot.x, rot.y, rot.z);
    }
    
    /**
     * @brief Gets xyz position of the camera
     * 
     * Gets values from the translation part of the view matrix.
     * 
     * @return XYZ position
     */
    Vec3 getCameraTranslation();
    
    /**
     * @brief Gets rotation of the camera
     * 
     * Calculates values from the rotation part of the view matrix.
     * Rotation order is ZYX (Yaw-Pitch-Roll).
     *
     * @return Rotation in Euler angles
     */
    Euler getCameraRotation();
    
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
     * @brief Sets angle of view for perspective projection
     * 
     * @param fov Field of view
     */
    void setFieldOfView(float fov);
    
    /**
     * @brief Sets minimum distance for depth clipping
     * 
     * @param near Minimum clipping distance
     */
    void setMinimumDistance(float near);
    
    /**
     * @brief Sets maximum distance for depth clipping
     * 
     * @param far Maximum clipping distance
     */
    void setMaximumDistance(float far);
    
    /**
     * @brief Gets angle of view used in perspective projection
     * 
     * @return Field of view
     */
    void getFieldOfView();
    
    /**
     * @brief Gets minimum distance for depth clipping
     * 
     * @return Minimum clipping distance
     */
    float getMinimumDistance();
    
    /**
     * @brief Gets maximum distance for depth clipping
     * 
     * @return Maximum clipping distance
     */
    float getMaximumDistance();
    
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
     * RGB color. Light intensity is in place of alpha component.
     * 
     * @return Light color and intensity
     */
    Color getDirectionalLightColor();
    
    /**
     * @brief Sets the directional lighting angles
     * 
     * Directional light takes the main role in fragment shaders and
     * shadow mappings for 3D object viewing. Rotation order is
     * ZY (Yaw-Pitch). Rolling has no effect. Directional light vector
     * with angle values of zeros is pointed towards the Y-axis which
     * is the same as initial camera direction.
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
     * ZY (Yaw-Pitch). Rolling has no effect. Directional light vector
     * with angle values of zeros is pointed towards the Y-axis which
     * is the same as initial camera direction.
     * 
     * @param pitch Angle above xy-plane
     * @param yaw Angle about z-axis
     * @param unit Radian or degree
     */
    inline void setDirectionalLightAngles(float pitch, float yaw,
                                          AngleUnit unit)
    {
        if(unit == UNIT_RADIAN)
            setDirectionalLightAngles(pitch, yaw);
        else
            setDirectionalLightAngles(radian(pitch), radian(yaw));
    }
    
    /**
     * @brief Sets the directional lighting angles
     * 
     * Directional light takes the main role in fragment shaders and
     * shadow mappings for 3D object viewing. Rotation order is
     * ZY (Yaw-Pitch). Rolling has no effect. Directional light vector
     * with angle values of zeros is pointed towards the Y-axis which
     * is the same as initial camera direction.
     * 
     * @param rot Euler angles
     */
    inline void setDirectionalLightAngles(const Vec3 &rot) {
        setDirectionalLightAngles(rot.y, rot.z);
    }
    
    /**
     * @brief Gets the directional lighting angles
     * 
     * Rotation order is ZY (Yaw-Pitch). Rolling has no effect and the
     * x in returned instance is always zero.
     * 
     * @return Rotation in Euler angles
     */
    Vec3 getDirectionalLightAngles(float pitch, float yaw);
    
    /**
     * @brief Converts world coordinate to screen coordinate
     * 
     * Useful when displaying 2D sprites and texts around 3D objects.
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param z Z-coordinate
     */
    Vec2 worldToScreen(float x, float y, float z);
    
    /**
     * @brief Converts world coordinate to screen coordinate
     * 
     * Useful when displaying 2D sprites and texts around 3D objects.
     * 
     * @param p 3D point in world space
     */
    Vec2 worldToScreen(const Vec3 &p);
    
    /**
     * @brief Converts screen coordinate to world coordinate
     * 
     * Useful when interacting 3D objects with a mouse.
     * 
     * @param p Point on screen
     * @param plane Plane in 3D world the mouse interacts
     */
    Vec3 screenToWorld(const Vec2 &p, const Plane &plane);
    
    /**
     * @brief Appends a 2D/3D object to the display list
     * 
     * @param obj 2D/3D object
     */
    void addObject(Object* obj);
    
    /**
     * @brief Appends a texture to the list loading GPU resources
     * 
     * @param tex Texture
     */
    void addTexture(Texture* tex);
    
    /**
     * @brief Appends a font to the font list for text drawing
     * 
     * @param font Font
     */
    void addFont(Font* font);
    
    /**
     * @brief Searches 2D/3D object from the display list
     * 
     * @param id Object ID
     * 
     * @return Resulting object as a pointer. NULL on not found.
     */
    Object* findObject(uint64_t id);
    
    /**
     * @brief Searches texture from loaded texture list
     * 
     * @param id Texture ID
     * 
     * @return Resulting texture as a pointer. NULL on not found.
     */
    Texture* findTexture(uint64_t id);
    
    /**
     * @brief Searches font from loaded font list
     * 
     * @param id Font ID
     * 
     * @return Resulting font as a pointer. NULL on not found.
     */
    Texture* findFont(uint64_t id);
    
    /**
     * @brief Removes the object from the list cleaning the GPU resources
     * 
     * @param id Object ID
     */
    void removeObject(uint64_t id);
    
    /**
     * @brief Removes the object from the list cleaning the GPU resources
     * 
     * @param obj 2D/3D object
     */
    void removeObject(Object* obj);
    
    /**
     * @brief Removes the texture from the list cleaning the GPU resources
     * 
     * @param id Texture ID
     */
    void removeTexture(uint64_t id);
    
    /**
     * @brief Removes the texture from the list cleaning the GPU resources
     * 
     * @param tex Texture
     */
    void removeTexture(Texture* tex);
    
    /**
     * @brief Removes the font from the list cleaning the GPU resources
     * 
     * @param id Texture ID
     */
    void removeFont(uint64_t id);
    
    /**
     * @brief Removes the font from the list cleaning the GPU resources
     * 
     * @param font Font
     */
    void removeFont(Font* font);
    
    /**
     * @brief Removes all context resources
     * 
     * Clears the lists of objects, textures, fonts and their GPU resources.
     */
    void cleanup();
    
    /**
     * @brief Makes OpenGL rederer focuses on this context
     * 
     * Whenever functions regarding OpenGL resources is intended to be
     * called, the function needs to be called first especially when working
     * with multiple contexts.
     */
    virtual void setCurrent();
    
    /**
     * @brief Searches context model by ID
     * 
     * @return OpenGL context
     */
    static Context* getContextByID(uint64_t id);
};

}

#endif
