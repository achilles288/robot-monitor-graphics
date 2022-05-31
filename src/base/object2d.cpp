/**
 * @file object2d.cpp
 * @brief 2D graphics displayed on top of the 3D graphics context
 *
 * All 2D objects use common vertex buffer object for shader programs.
 * Simple model matrix. No depth value and drawing order is according to
 * the z-order value (determines which object appears on top).
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "rmg/object2d.hpp"


namespace rmg {

/**
 * @brief Default constructor
 */
Object2D::Object2D() {
    modelMatrix = Mat3();
    rotation = 0.0f;
    size = Vec2(1, 1);
}

/**
 * @brief Constructor with its container
 * 
 * @param ctx Container context
 */
Object2D::Object2D(Context* ctx): Object(ctx) {
    modelMatrix = Mat3();
    rotation = 0.0f;
    size = Vec2(1, 1);
    type = ObjectType::Object2D;
}

/**
 * @brief Swaps the values of member variables between two objects
 * 
 * @param x The other object
 */
void Object2D::swap(Object2D& x) noexcept {
    std::swap(modelMatrix, x.modelMatrix);
    std::swap(rotation, x.rotation);
    std::swap(size, x.size);
    std::swap(zOrder, x.zOrder);
    std::swap(alignment, x.alignment);
    std::swap(type2D, x.type2D);
    Object::swap(x);
}

/**
 * @brief Gets 2D object type
 * 
 * @return Object type
 */
Object2DType Object2D::getObject2DType() const { return type2D; }

/**
 * @brief Sets the reference position or alignment
 * 
 * @param a The position with respect to screen width and height
 */
void Object2D::setAlignment(Alignment a) { alignment = a; }

/**
 * @brief Gets the reference position or alignment
 * 
 * @return The position with respect to screen width and height
 */
Alignment Object2D::getAlignment() const { return alignment; }

/**
 * @brief The matrix composed of all the transformations done by the object
 * 
 * @return Model matrix
 */
const Mat3& Object2D::getModelMatrix() const { return modelMatrix; }

/**
 * @brief Sets the location which the object appears
 * 
 * Assigns values to the model matrix's translation part.
 * Anchor of a 2D object is mostly at the center other than the top
 * left corner as in other 2D graphics API.
 * For Text2D, the anchor is according to text alignment.
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 */
void Object2D::setTranslation(float x, float y) {
    modelMatrix[0][2] = x;
    modelMatrix[1][2] = y;
}

/**
 * @brief Sets the location which the object appears
 * 
 * Assigns values to the model matrix's translation part.
 * Anchor of a 2D object is mostly at the center other than the top
 * left corner as in other 2D graphics API.
 * For Text2D, the anchor is according to text alignment.
 * 
 * @param pos Position vector
 */
void Object2D::setTranslation(const Vec2 &pos) {
    modelMatrix[0][2] = pos.x;
    modelMatrix[1][2] = pos.y;
}

/**
 * @brief Gets the location of the 2D object
 * 
 * @return Position vector
 */
Vec2 Object2D::getTranslation() const {
    return Vec2(modelMatrix[0][2], modelMatrix[1][2]);
}

/**
 * @brief Sets the rotation of the 2D object
 * 
 * @param t Rotation in radian
 */
void Object2D::setRotation(float t) {
    rotation = t;
    modelMatrix[0][0] = cos(t) * size.x;
    modelMatrix[0][1] = -sin(t) * size.y;
    modelMatrix[1][0] = sin(t) * size.x;
    modelMatrix[1][1] = cos(t) * size.y;
}

/**
 * @brief Gets the rotation of the 2D object
 * 
 * @return Rotation in degrees
 */
float Object2D::getRotation() const { return rotation; }

/**
 * @brief Sets the size of the 2D object
 * 
 * @param w Width
 * @param h Height
 */
void Object2D::setSize(float w, float h) {
    size.x = w;
    size.y = h;
    modelMatrix[0][0] = cos(rotation) * w;
    modelMatrix[0][1] = -sin(rotation) * h;
    modelMatrix[1][0] = sin(rotation) * w;
    modelMatrix[1][1] = cos(rotation) * h;
}

/**
 * @brief Sets the size of the 2D object
 * 
 * @param s Size
 */
void Object2D::setSize(const Vec2 &s) {
    size = s;
    modelMatrix[0][0] = cos(rotation) * s.x;
    modelMatrix[0][1] = -sin(rotation) * s.y;
    modelMatrix[1][0] = sin(rotation) * s.x;
    modelMatrix[1][1] = cos(rotation) * s.y;
}

/**
 * @brief Gets the size of the 2D object
 * 
 * @return Width and height as a rectangular dimension
 */
Vec2 Object2D::getSize() const { return size; }

/**
 * @brief Determines which 2D object is on top
 * 
 * This function is necessary when 2 objects overlap.
 * 
 * @param z Z-order
 */
void Object2D::setZOrder(int8_t z) { zOrder = z; }

/**
 * @brief Gets the z-order of the 2D object
 * 
 * @return Z-order
 */
int8_t Object2D::getZOrder() const { return zOrder; }

}
