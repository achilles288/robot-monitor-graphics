/**
 * @file object.hpp
 * @brief A foundation of all RMG graphical object data structures
 * 
 * Doesn't have much features and not directly used by the context.
 * Stores a unique key and parent context. Common features like textures,
 * color and visibility control.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_OBJECT_H__
#define __RMG_OBJECT_H__

#include <cstdint>

#include "color.hpp"


namespace rmg {

class Context;


/**
 * @brief Type of object (Object3D, Sprite2D, .etc)
 * 
 * Determines which object list to append by the Context and which
 * method of operations by Shader(s) (internal operations).
 */
enum class ObjectType {
    Default,
    Object3D,
    Sprite2D,
    Text2D,
    Particle3D,
    Line3D
};

/**
 * @brief A foundation of all RMG graphical object data structures
 * 
 * Doesn't have much features and not directly used by the context.
 * Stores a unique key and parent context. Common features like textures,
 * color and visibility control.
 */
class Object {
  private:
    uint64_t id;
    Context* context;
    Color color;
    bool hidden;
    
    static uint64_t lastID;
    
  protected:
    /**
     * @brief Type of object (Object3D, Sprite2D, .etc)
     * 
     * Determines which object list to append by the Context and which
     * method of operations by Shader(s) (internal operations).
     */
    ObjectType type;
    
  public:
    /**
     * @brief Constructor with its container
     * 
     * @param ctx Container context
     */
    Object(Context* ctx);
    
    /**
     * @brief Destructor
     */
    virtual ~Object();
    
    /**
     * @brief Copy constructor
     * 
     * @param obj Source object
     */
    Object(const Object& obj);
    
    /**
     * @brief Move constructor
     * 
     * @param obj Source object
     */
    Object(Object&& obj) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param obj Source object
     */
    Object& operator=(const Object& obj);
    
    /**
     * @brief Move assignment
     * 
     * @param obj Source object
     */
    Object& operator=(Object&& obj) noexcept;
    
    /**
     * @brief Gets object ID
     * 
     * @return Object ID
     */
    uint64_t getID();
    
    /**
     * @brief Gets container context
     * 
     * @return Container context
     */
    Context* getContext();
    
    /**
     * @brief Gets object type
     * 
     * @return Object type
     */
    ObjectType getObjectType();
    
    /**
     * @brief Sets object color
     * 
     * @param r Red
     * @param g Green
     * @param b Blue
     */
    void setColor(float r, float g, float b);
    
    /**
     * @brief Sets object color
     * 
     * @param r Red
     * @param g Green
     * @param b Blue
     * @param a Alpha
     */
    void setColor(float r, float g, float b, float a);
    
    /**
     * @brief Sets object color
     * 
     * @param col RGBA color
     */
    void setColor(const Color &col);
    
    /**
     * @brief Gets object color
     * 
     * @return RGBA color
     */
    Color getColor();
    
    /**
     * @brief Sets object visibility
     * 
     * This determines whether the shaders process or skips the object
     * model. Skipping means the object is not shown in the context.
     * 
     * @param hide Hide flag
     */
    void setHidden(bool hide);
    
    /**
     * @brief Whether the object is hidden or not
     * 
     * @return True if the object is hidden
     */
    bool isHidden();
};

}

#endif
