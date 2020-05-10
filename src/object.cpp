/**
 * @file object.cpp
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


#include "rmg/object.hpp"

#include "rmg/context.hpp"


namespace rmg {

uint64_t Object::lastID = 0;

/**
 * @brief Constructor with its container
 * 
 * @param ctx Container context
 */
Object::Object(Context* ctx) {
    id = ++lastID;
    context = ctx;
    color = Color(1, 1, 1, 1);
    hidden = false;
    type = ObjectType::Default;
}

/**
 * @brief Destructor
 */
Object::~Object() {}

/**
 * @brief Copy constructor
 * 
 * @param obj Source object
 */
Object::Object(const Object& obj) {
    id = ++lastID;
    context = obj.context;
    color = obj.color;
    hidden = obj.hidden;
    type = obj.type;
}

/**
 * @brief Move constructor
 * 
 * @param obj Source object
 */
Object::Object(Object&& obj) noexcept {
    id = obj.id;
    context = obj.context;
    color = obj.color;
    hidden = obj.hidden;
    type = obj.type;
}

/**
 * @brief Copy assignment
 * 
 * @param obj Source object
 */
Object& Object::operator=(const Object& obj) {
    id = ++lastID;
    context = obj.context;
    color = obj.color;
    hidden = obj.hidden;
    type = obj.type;
    return *this;
}

/**
 * @brief Move assignment
 * 
 * @param obj Source object
 */
Object& Object::operator=(Object&& obj) noexcept {
    id = obj.id;
    context = obj.context;
    color = obj.color;
    hidden = obj.hidden;
    type = obj.type;
    return *this;
}

/**
 * @brief Gets object ID
 * 
 * @return Object ID
 */
uint64_t Object::getID() { return id; }

/**
 * @brief Gets container context
 * 
 * @return Container context
 */
Context* Object::getContext() { return context; }

/**
 * @brief Gets object type
 * 
 * @return Object type
 */
ObjectType Object::getObjectType() { return type; }

/**
 * @brief Sets object color
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 * @param a Alpha
 */
void Object::setColor(float r, float g, float b, float a) {
    color.red = r;
    color.green = g;
    color.blue = b;
    color.alpha = a;
}

/**
 * @brief Sets object color
 * 
 * @param col RGBA color
 */
void Object::setColor(const Color &col) { color = col; }

/**
 * @brief Gets object color
 * 
 * @return RGBA color
 */
Color Object::getColor() { return color; }

/**
 * @brief Sets object visibility
 * 
 * This determines whether the shaders process or skips the object
 * model. Skipping means the object is not shown in the context.
 * 
 * @param hide Hide flag
 */
void Object::setHidden(bool hide) { hidden = hide; }

/**
 * @brief Whether the object is hidden or not
 * 
 * @return True if the object is hidden
 */
bool Object::isHidden() { return hidden; }

}
