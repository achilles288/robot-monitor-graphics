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


#define RMG_EXPORT


#include "object.hpp"

#include <utility>


namespace rmg {

uint64_t Object::lastID = 0;

/**
 * @brief Default constructor
 */
Object::Object() {
    id = 0;
    context = nullptr;
    color = Color(1, 1, 1, 1);
    hidden = false;
    type = ObjectType::Default;
}

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
    id = std::exchange(obj.id, 0);
    context = std::exchange(obj.context, nullptr);
    color = std::exchange(obj.color, Color(1,1,1,1));
    hidden = std::exchange(obj.hidden, false);
    type = std::exchange(obj.type, ObjectType::Default);
}
    
/**
 * @brief Copy assignment
 * 
 * @param obj Source object
 */
Object& Object::operator=(const Object& obj) {
    Object tmp = Object(obj);
    swap(tmp);
    return *this;
}

/**
 * @brief Move assignment
 * 
 * @param obj Source object
 */
Object& Object::operator=(Object&& obj) noexcept {
    Object tmp = std::move(obj);
    swap(tmp);
    return *this;
}

void Object::swap(Object& x) noexcept {
    std::swap(id, x.id);
    std::swap(context, x.context);
    std::swap(color, x.color);
    std::swap(hidden, x.hidden);
    std::swap(type, x.type);
}

/**
 * @brief Gets object ID
 * 
 * @return Object ID
 */
uint64_t Object::getID() const { return id; }

/**
 * @brief Gets container context
 * 
 * @return Container context
 */
Context* Object::getContext() const { return context; }

/**
 * @brief Gets object type
 * 
 * @return Object type
 */
ObjectType Object::getObjectType() const { return type; }

/**
 * @brief Sets object color
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 */
void Object::setColor(float r, float g, float b) {
    color.red = r;
    color.green = g;
    color.blue = b;
    color.alpha = 1.0f;
}

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
Color Object::getColor() const { return color; }

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
bool Object::isHidden() const { return hidden; }

}
